#include "pch.h"

#include "FileLogger.h"
#include "Platform/FileSystem.h"

FileLogger::FileLogger()
{
	std::string loggerMainDirectory = std::string(Torc::Platform::GetEngineRootDirectory()) + "\\Logs\\";
	SystemTime currentTime;
	Torc::Platform::GetSystemTime(&currentTime);

	std::string currentTimeString = SystemTimeToString(currentTime);

	if (!fs::IsDirectory(loggerMainDirectory.c_str()))
	{
		// create a sub folder inside the main directory to store log files
		bool isCreated = fs::CreateNewDirectory(loggerMainDirectory.c_str());
		assert(isCreated == true);

		loggerMainDirectory = loggerMainDirectory + currentTimeString + "\\";
		isCreated = fs::CreateNewDirectory(loggerMainDirectory.c_str());
		assert(isCreated == true);
	}
	else
	{
		loggerMainDirectory = loggerMainDirectory + currentTimeString + "\\";
		bool isCreated = fs::CreateNewDirectory(loggerMainDirectory.c_str());
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

		std::string fullFileName = loggerMainDirectory + channelName + "_" + currentTimeString + ".txt";
		TORC_HANDLE fileHandle = fs::OpenFile(fullFileName.c_str(), FileAccessMode::Access_Write, FileShareMode::Share_None, FileCreationFlag::Create_Always);

		LogFileDesc desc;
		desc.filename = std::move(fullFileName);
		desc.fileHandle = fileHandle;
		desc.bufferInUse = 0;
		desc.currentLogMessageSlot = 0;
		m_logFiles[(LogChannel)i] = desc;
	}
}

FileLogger::~FileLogger()
{
	// flush everything to the file 
	for (auto& [key, value] : m_logFiles)
	{
		uint32 bytesWritten = fs::WriteFile(value.fileHandle, (void*)value.buffer, value.bufferInUse);
		assert(bytesWritten == value.bufferInUse);
		fs::CloseFile(value.fileHandle);
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
	uint32 bytesWritten = fs::WriteFile(logFileDesc.fileHandle, (void*)logFileDesc.buffer, logFileDesc.bufferInUse);
	assert(bytesWritten == logFileDesc.bufferInUse);
	logFileDesc.bufferInUse = 0;
	logFileDesc.currentLogMessageSlot = 0;
	fs::SetEndOfFile(logFileDesc.fileHandle);
}