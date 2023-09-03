#include "pch.h"
#include "Logger.h"
#include "Platform/Platform.h"

using namespace Torc;

namespace
{
	inline std::wstring to_wchar(const char* str)
	{
		std::string str1 = str;
		std::wstring wstr(str1.begin(), str1.end());
		return wstr;
	}

	static std::set<std::unique_ptr<Logger::Listener>> s_listeners;
}

Logger::Logger(const char* file, const char* function, int line, const char* msg)
{
	snprintf(m_msg, _countof(m_msg), " [FILE]  %s, [FUNC] %s, [LINE] %d, %s\n", file, function, line, msg);
}
Logger::Logger(const char* msg, ...)
{
	TE_ASSERT(strlen(msg) < _countof(m_msg), "Logger.cpp: logger msg length is larger than buffer size!");
	std::time_t r = std::time(nullptr);
	ctime_s(m_msg, _countof(m_msg), &r);
	size_t len = strlen(m_msg);

	va_list args;
	va_start(args, msg);
	m_msg[len - 1] = ' ';
	vsnprintf(m_msg + (len), _countof(m_msg), msg, args);
	va_end(args);
}

void Logger::Initialize()
{
	// doesn't do anything
}

void Logger::Shutdown()
{
	s_listeners.clear();
}

void Logger::Register(std::unique_ptr<Listener> listener)
{
	for (auto it = s_listeners.begin(); it != s_listeners.end(); ++it)
	{
		const char* t1 = (*it)->GetListenerType();
		const char* t2 = listener->GetListenerType();

		if (strcmp(t1, t2) == 0)
		{
			// we can assert here
			TE_ASSERT(false, "Trying to register same type of Logger twice this"
				" will cause unnecessary function calls. This is unexceptable!");
			return;
		}
	}
	s_listeners.insert(std::move(listener));
}

void Logger::Unregister(std::unique_ptr<Listener> listener)
{
	s_listeners.erase(listener);
}

void Logger::LogInfo()
{
	for (const auto& listener : s_listeners)
	{
		// check if listener is listening for current channel
		if (listener->GetChannels() & LOG_LISTEN_INFO)
		{
			listener->LogInfo(m_msg);
		}
	}
}

void Logger::LogError()
{
	for (const auto& listener : s_listeners)
	{
		// check if listener is listening for current channel
		if (listener->GetChannels() & LOG_LISTEN_ERROR)
		{
			listener->LogError(m_msg);
		}
	}
}

void Logger::LogWarning()
{
	for (const auto& listener : s_listeners)
	{
		// check if listener is listening for current channel
		if (listener->GetChannels() & LOG_LISTEN_WARNING)
		{
			listener->LogWarning(m_msg);
		}
	}
}

void LogToDebugWindow::LogError(const char* msg)
{
	//TorcPlatform::PrintToDebugWindow(to_wchar(msg).c_str());
	printf("%s", msg);
}

void LogToDebugWindow::LogInfo(const char* msg)
{
	//TorcPlatform::PrintToDebugWindow(to_wchar(msg).c_str());
	printf("%s", msg);
}

void LogToDebugWindow::LogWarning(const char* msg)
{
	//TorcPlatform::PrintToDebugWindow(to_wchar(msg).c_str());
	printf("%s", msg);
}

