#pragma once

#include <Windows.h>

#include <directxmath.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <wrl.h>

//#include <string>

//#include "Core/Logging/Logger.h"
#include "TorcGfx/GfxAPIs/D3D11/TypeConverterD3D11.h"

#pragma comment(lib,"d3d11.lib")


#ifdef TORC_DLL_EXPORT
#define TORC_API __declspec(dllexport)
#else
#define TORC_API __declspec(dllimport)
#endif


#define MAX_HANDLE_COUNT_BLEND_STATE 100
#define MAX_HANDLE_COUNT_RASTERIZER_STATE 100
#define MAX_HANDLE_COUNT_SAMPLER_STATE 100
#define MAX_HANDLE_COUNT_DEPTH_STENCIL_STATE 100
#define MAX_HANDLE_COUNT_RENDER_TARGET 8

