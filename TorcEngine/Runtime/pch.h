#pragma once

#ifdef TORC_PLATFORM_WIN64
#include <wrl.h>
#include <WinUser.h>
#include <Windows.h>
#if defined(_DEBUG) && !defined(TORC_EDITOR)
//must define both _CRTDBG_MAP_ALLOC and _CRTDBG_MAP_ALLOC_NEW
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW

#include <stdlib.h>
//#include <crtdbg.h>
////if you won't use this macro you'll get all new as called from crtdbg.h      
//#define DEBUG_NEW   new( _CLIENT_BLOCK, __FILE__, __LINE__)
//#define new DEBUG_NEW
#endif
#endif

#include <cstdint>
#include <iostream>
#include <ostream>
#include <fstream>

#include <memory>
#include <set>
#include <string>


#include <stdlib.h>
#include <crtdbg.h>

#include <Psapi.h>
#include <map>
#include <vector>

#include <future>
#include <type_traits>

#include <deque>
#include <bitset>

#include "BasicTypes.h"
#include "Core/TorcSystem/ISystem.h"


#include "Core/Threading/Thread.h"
#include "Core/Threading/Mutex.h"
#include "Core/Threading/Atomic.h"


#ifdef TORC_DLL_EXPORT
#define TORC_API __declspec(dllexport)
#else
#define TORC_API __declspec(dllimport)
#endif

#define _FORCE_INLINE_ __forceinline


#include "Core/Common/String.h"
#include "Core/Common/UtilMacros.h"
#include "Core/Logging/Logger.h"
#include "Core/Memory/Memory.h"
#include "Core/Math.h"

