#include "pch.h"
#include "DebugWindowLogger.h"

DebugWindowLogger::DebugWindowLogger(TORC_HWND debugWindowHandle)
	: m_debugWindowHandle(debugWindowHandle)
{}

DebugWindowLogger::~DebugWindowLogger()
{}

void DebugWindowLogger::OnLog(const char* msg, LogChannel channel, LogSeverity severity)
{
	bool successfullySent = false;
	// first handle cached ones
	if (m_logList.size() > 0)
	{
		LogList::iterator begin = m_logList.begin();
		LogList::iterator end = m_logList.end();
		while (begin != end)
		{
			successfullySent = Torc::Platform::SendMessageToWindow(m_debugWindowHandle, WindowMessage::WINDOW_MESSAGE_PRINT_TO_WINDOW, (void*)(begin->c_str()));
			if (successfullySent)
			{
				m_logList.erase(begin);
				begin = m_logList.begin();
			}
			begin++;
		}
	}
	
	// get the msg, pack and send it to the debug window
	successfullySent = Torc::Platform::SendMessageToWindow(m_debugWindowHandle, WindowMessage::WINDOW_MESSAGE_PRINT_TO_WINDOW, (void*)msg);
	if (!successfullySent)
	{
		m_logList.push_back(msg);
	}
}