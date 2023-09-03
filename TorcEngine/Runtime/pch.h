#pragma once

#ifdef TORC_PLATFORM_WIN64
#include <wrl.h>
#ifdef _DEBUG
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

#include <filesystem>
#include <thread>
#include <future>

#include <deque>

#ifdef TORC_DLL_EXPORT
#define TORC_API __declspec(dllexport)
#else
#define TORC_API __declspec(dllimport)
#endif

#include "Core/Logging/LoggerMacros.h"
#include "Core/Memory/Memory.h"
