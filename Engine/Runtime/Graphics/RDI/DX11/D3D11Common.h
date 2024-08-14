#pragma once

#include <Windows.h>

#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3d11.h>
#include <wrl.h>

#include <vector>
#include <memory>

#include "Core/BaseTypes.h"
#include "Core/Logging/Logger.h"
#include "TypeConverterD3D11.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")
#pragma comment(lib,"dxguid.lib") // needed for IID_ID3D11ShaderReflection

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
#define MAX_HANDLE_COUNT_BUFFERS 1024
#define MAX_HANDLE_COUNT_SHADER 1024

// undefine succeeded macro defined in winerror header
#undef SUCCEEDED

#define SUCCEEDED(expr) (expr == S_OK)

#define LOG_GFX_INFO(msg, ...)\
	gEnv->logger->Log("[INFO] "##msg, LogChannel::LC_GfxBackend, LogSeverity::LS_Info, __VA_ARGS__);

#define LOG_GFX_WARN(msg, ...)\
	gEnv->logger->Log("[WARN] "##msg, LogChannel::LC_GfxBackend, LogSeverity::LS_Warn, __VA_ARGS__);

#define LOG_GFX_ERROR(msg, ...)\
	gEnv->logger->Log("[ERROR] "##msg, LogChannel::LC_GfxBackend, LogSeverity::LS_Error, __VA_ARGS__);