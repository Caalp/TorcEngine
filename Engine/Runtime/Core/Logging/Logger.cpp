#include "Logger.h"
#include "Core/Application.h"
#include "Core/Logging/FileLogger.h"

#include <stdarg.h>

namespace
{
	inline std::wstring to_wchar(const char* str)
	{
		std::string str1 = str;
		std::wstring wstr(str1.begin(), str1.end());
		return wstr;
	}
	Std::mutex lock;
}

LoggerBase::LoggerBase()
{}

LoggerBase::~LoggerBase()
{
	m_logListeners.clear();
}

void LoggerBase::Log(const char* msg, LogChannel channel, LogSeverity severity, ...)
{
	va_list args;
	va_start(args, severity);

	SystemTime currentTime;
	Torc::Platform::GetSystemTime(&currentTime);
	std::string currTimeStr = SystemTimeToString(currentTime);

	CString<256> fixedSizeString;
	vsnprintf(fixedSizeString.Data(), fixedSizeString.Capacity(), msg, args);

	va_end(args);

	CString<256> temp = (currTimeStr + " " + std::string(fixedSizeString.c_str()) + "\n").c_str();
	
	Std::scoped_lock{ lock };
	for (auto& listener : m_logListeners)
	{	
		listener->OnLog(temp.c_str(), channel, severity);
	}
}

void LoggerBase::RegisterListener(ILogListener* listener)
{
	Std::scoped_lock{ lock };
	std::vector<ILogListener*>::iterator begin = m_logListeners.begin();
	std::vector<ILogListener*>::iterator end = m_logListeners.end();
	for (auto i = begin; i != end; i++)
	{
		if ((*i) == listener)
		{
			return;
		}
	}
	m_logListeners.emplace_back(std::move(listener));
}

void LoggerBase::RemoveListener(ILogListener* listener)
{
	Std::scoped_lock{ lock };
	std::vector<ILogListener*>::iterator begin = m_logListeners.begin();
	std::vector<ILogListener*>::iterator end = m_logListeners.end();
	for (auto i = begin; i != end; i++)
	{
		if ((* i) == listener)
		{
			m_logListeners.erase(i);
			break;
		}
	}
}
