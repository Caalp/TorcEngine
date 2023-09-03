#pragma once
#include "Logger.h"

#ifdef _DEBUG
#define TE_INFO(msg, ...)\
	Torc::Logger("[INFO] "##msg, __VA_ARGS__).LogInfo();

#define TE_INFO_TRACE(msg, ...)\
	Torc::Logger(__FILE__, __FUNCTION__, __LINE__, "[INFO] "##msg, __VA_ARGS__).LogInfo();

#define TE_WARN(msg, ...)\
	Torc::Logger("[WARN] "##msg, __VA_ARGS__).LogWarning();

#define TE_ERROR(msg, ...)\
	Torc::Logger("[ERROR] "##msg, __VA_ARGS__).LogError();

#define TE_ASSERT(expr,msg,...)\
	if(!(expr))\
	{\
	 MessageBoxA(0,\
	Torc::Logger(__FILE__, __FUNCTION__, __LINE__, msg).MessageString(),\
	"Assertion", 0);\
	 DebugBreak();\
	}
#else
#define logInfo(msg)
#define logWarning(msg)
#define logError(msg)
#define assertw(expr,msg,...)
#define assertf(msg,...)
#endif