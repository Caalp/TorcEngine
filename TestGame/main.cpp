#include "pch.h"

#define _CRTDBG_MAP_ALLOC

#include "Core/Application.h"
#include "Platform/SystemInfo.h"

#include "TorcGfx/TorcGfxTypes.h"
#include "Renderer/Renderer.h"
#include "Core/Plugins/PluginLoader.h"
#include "Core/Containers/TwoLockQueue.h"
#include "Core/Containers/Stack.h"
#include "Core/Containers/GenericTaskQueue.h"

#include "Platform/Platform.h"
#include "Core/Memory/Memory.h"
#include "Core/Memory/Allocators/PoolAllocator.h"
#include "Core/IOStream/FileStream.h"

#include "Renderer/CommandBucket.h"
#include "Core/Timer.h"
#include "Core/Containers/FreeList.h"

#include <functional>

#include "TorcGfx/ITorcGfxBackend.h"

using namespace Torc;

#ifdef USE_D3D11_GFX_BACKEND
    // include the dll here
    
#else
    // print out and error here    
#endif

struct debug_state
{
    debug_state() {}
    ~debug_state() { _CrtDumpMemoryLeaks(); }
};

#pragma init_seg(compiler)
debug_state ds;

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

    AppCreateParams params = {};
    params.cmdLineArgs = cmdline;
    Application::Run(&params);  

    return 0;
}