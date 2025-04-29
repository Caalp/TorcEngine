#pragma once
#include "Core/Base.h"
#include "Core/System/ISystem.h"

#include <vector>

template<uint32 _SIZE> class CString;
typedef CString<256> StandartLogMsg;

enum class LogChannel
{
	LC_Core = 0,
	LC_GfxBackend,
	LC_Renderer,
	LC_Platform,
	Count
};

enum class LogSeverity
{
	LS_Info,
	LS_Warn,
	LS_Error
};

class ILogListener
{
public:
	virtual ~ILogListener() {}
	virtual void OnLog(const char* msg, LogChannel channel, LogSeverity severity) = 0;
};

class ILogger
{
public:
	virtual ~ILogger() {}
	virtual void Log(const char* msg, LogChannel channel, LogSeverity severity, ...) = 0;
	virtual void RegisterListener(ILogListener* listener) = 0;
	virtual void RemoveListener(ILogListener* listener) = 0;
};

class LoggerBase : public ILogger
{
public:
	LoggerBase();
	~LoggerBase();
	virtual void Log(const char* msg, LogChannel channel, LogSeverity severity, ...) override;

	virtual void RegisterListener(ILogListener* listener) override;
	virtual void RemoveListener(ILogListener* listener) override;
private:
	// TODO(cagri): later replace this with concurrent container
	std::vector<ILogListener*> m_logListeners;
};

static const char* FormStrFromVarArgs(const char* t, ...)
{ 
	return ""; 
}

#ifdef _DEBUG
#define TE_Info(channel, msg, ...)\
	gEnv->logger->Log("[INFO] "##msg, channel, LogSeverity::LS_Info, __VA_ARGS__);

#define TE_Warning(channel, msg, ...)\
	gEnv->logger->Log("[WARN] "##msg, channel, LogSeverity::LS_Warn, __VA_ARGS__);

#define TE_Error(channel, msg, ...)\
	gEnv->logger->Log("[ERROR] "##msg, channel, LogSeverity::LS_Error, __VA_ARGS__);

#define TE_TraceInfo(msg, ...)
	//Torc::Logger(__FILE__, __FUNCTION__, __LINE__, "[INFO] "##msg, __VA_ARGS__).LogInfo();

#define ASSERT(expr,msg,...)\
	if(!(expr))\
	{\
	 MessageBoxA(0,\
		"NoNO",\
	"Assertion", 0);\
	 DebugBreak();\
	}

#define TE_Assert(expr,msg,...)\
	if(!(expr))\
	{\
	 MessageBoxA(0,\
		"NoNO",\
	"Assertion", 0);\
	 DebugBreak();\
	}
#else
#define TE_Info(channel, msg, ...)
#define TE_Warning(channel, msg, ...)
#define TE_Error(channel, msg, ...)
#define TE_TraceInfo(channel, msg, ...)
#define ASSERT(channel, msg, ...)
#endif