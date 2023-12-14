#pragma once
#include "Core/TorcSystem/ISystem.h"

class DebugWindowLogger : public ILogListener
{
public:
	DebugWindowLogger(TORC_HWND debugWindowHandle);
	~DebugWindowLogger();
	virtual void OnLog(const char* msg, LogChannel channel, LogSeverity severity)  override;
private:
	TORC_HWND m_debugWindowHandle;
	typedef std::vector<StandartLogMsg> LogList;
	LogList m_logList;
};