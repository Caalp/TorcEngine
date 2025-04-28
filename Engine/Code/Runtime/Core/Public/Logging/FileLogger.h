#pragma once
#include "Logging/Logger.h"

namespace Torc
{
	class FileLogger final : public ILogListener
	{
		static constexpr int MIN_MSG_QUEUE_CAPACITY = 32;
		static constexpr int MAX_MSG_QUEUE_CAPACITY = 4096;

		struct LogFileDesc
		{
			std::string filename;
			TORC_HANDLE fileHandle;
			uint8 buffer[MAX_MSG_QUEUE_CAPACITY]; // the buffer storing the messages

			// this is for sorting messages later on system time etc
			// currently its seems redundant since we assign time inside OnLog function
			// but I might use this for something else in the future or I can just delete it entirely
			struct LogMessage
			{
				uint8* ptrToLogMsg;
				uint32 lgMsgLength;
				SystemTime time;
			};

			LogMessage logMessages[MAX_MSG_QUEUE_CAPACITY / MIN_MSG_QUEUE_CAPACITY];
			uint16 bufferInUse;
			uint16 currentLogMessageSlot;
		};

	public:
		FileLogger();
		~FileLogger();

		virtual void OnLog(const char* msg, LogChannel channel, LogSeverity severity);
	private:
		void Flush(LogFileDesc& logFileDesc);

	private:
		std::map<LogChannel, LogFileDesc> m_logFiles;
	};
}
