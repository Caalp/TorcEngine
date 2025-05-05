#include "Core/Logging/FileLogger.h"
#include "Core/IO/FileStream.h"
#include "Core/IO/FileIOBase.h"
#include "Core/Std/String/string.h"
#include "Core/IO/Path/Path.h"

namespace Torc
{
	FileLogger::FileLogger()
	{
		Path loggerMainDirectory(Std::string(Platform::GetEngineRootDirectory()) + "\\Logs\\");
		SystemTime currentTime;
		Torc::Platform::GetSystemTime(&currentTime);

		Std::string currentTimeString = SystemTimeToString(currentTime);

		if (!IO::FileIOBase::IsDirectory(loggerMainDirectory))
		{
			// create a sub folder inside the main directory to store log files
			bool isCreated = IO::FileIOBase::CreateNewDirectory(loggerMainDirectory);
			assert(isCreated == true);

			loggerMainDirectory = loggerMainDirectory + currentTimeString + "\\";
			isCreated = IO::FileIOBase::CreateNewDirectory(loggerMainDirectory);
			assert(isCreated == true);
		}
		else
		{
			loggerMainDirectory = loggerMainDirectory + currentTimeString + "\\";
			bool isCreated = IO::FileIOBase::CreateNewDirectory(loggerMainDirectory);
			assert(isCreated == true);
		}

		// create a file for each channel with current time as a part of filename
		std::string channelName = "";
		for (int i = 0; i < (int)LogChannel::Count; ++i)
		{
			switch ((LogChannel)i)
			{
			case LogChannel::LC_Core:
			channelName = "Core";
			break;
			case LogChannel::LC_Platform:
			channelName = "Platform";
			break;
			case LogChannel::LC_GfxBackend:
			channelName = "GFXBackend";
			break;
			case LogChannel::LC_Renderer:
			channelName = "Renderer";
			break;
			default:
			channelName = "Unknown";
			break;
			}

			Path fullFileName = loggerMainDirectory + channelName + "_" + currentTimeString + ".txt";

			FileHandle handle;
			IO::FileIOBase& fileIO = IO::FileIOBase::GetInstance();
			IO::Result result = fileIO.Open(fullFileName, IO::OpenMode::Create | IO::OpenMode::ReadWrite, handle);

			if (result != IO::Result::Success)
			{
				TE_Error(LogChannel::LC_Core, "Opening file is failed %s", fullFileName.GetView().c_str());
				continue;
			}

			LogFileDesc desc;
			desc.filename = fullFileName.GetView().c_str();
			desc.fileHandle = handle;
			desc.bufferInUse = 0;
			desc.currentLogMessageSlot = 0;
			m_logFiles[(LogChannel)i] = desc;
		}
	}

	FileLogger::~FileLogger()
	{
		IO::FileIOBase& fileIO = IO::FileIOBase::GetInstance();
		// flush everything to the file 
		for (auto& [key, value] : m_logFiles)
		{
			uint32 bytesWritten = fileIO.Write(value.fileHandle, (void*)value.buffer, value.bufferInUse);
			assert(bytesWritten == value.bufferInUse);
			fileIO.Close(value.fileHandle);
		}
	}

	void FileLogger::OnLog(const char* msg, LogChannel channel, LogSeverity severity)
	{
		LogFileDesc& desc = m_logFiles[channel];
		uint16 msgLength = strlen(msg);
		if (desc.bufferInUse + msgLength > MAX_MSG_QUEUE_CAPACITY)
		{
			Flush(desc);
		}

		desc.logMessages[desc.currentLogMessageSlot].lgMsgLength = msgLength;
		desc.logMessages[desc.currentLogMessageSlot].ptrToLogMsg = &desc.buffer[desc.bufferInUse];
		Torc::Platform::MemCopy((void*)(desc.buffer + desc.bufferInUse), (void*)msg, msgLength);
		desc.logMessages[desc.currentLogMessageSlot].ptrToLogMsg = desc.buffer + desc.bufferInUse;
		desc.bufferInUse += msgLength;
		desc.currentLogMessageSlot++;
	}

	void FileLogger::Flush(LogFileDesc& logFileDesc)
	{
		// construct a message first
		IO::FileIOBase& fileIO = IO::FileIOBase::GetInstance();
		uint32 bytesWritten = fileIO.Write(logFileDesc.fileHandle, (void*)logFileDesc.buffer, logFileDesc.bufferInUse);
		assert(bytesWritten == logFileDesc.bufferInUse);
		logFileDesc.bufferInUse = 0;
		logFileDesc.currentLogMessageSlot = 0;
		fileIO.SetEof(logFileDesc.fileHandle);
	}
}
