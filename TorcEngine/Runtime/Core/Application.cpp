#include "pch.h"

#include "Common/StringUtils.h"
#include "Core/Application.h"
#include "Core/Plugins/PluginLoader.h"
#include "Core/Logging/Logger.h"
#include "Platform/Platform.h"
#include "Platform/WindowBase.h"
#include "Renderer/Renderer.h"



using namespace Torc;

namespace
{
	static std::unique_ptr<Application> s_application;
}


Application* Application::Instance()
{
	return s_application.get();
}

bool Application::Initialize(void* appConfig)
{
	TE_ASSERT(s_application.get() == nullptr, "Trying to initialize Application object which is already initialized."
		"Only single instance of Application is allowed!");

	// init app singleton here
	s_application.reset(new Application);
	s_application->m_createParams = *(AppCreateParams*)appConfig;

	// initialize debug window first
	if (strstr(s_application->m_createParams.cmdLineArgs, "debugWindow"))
	{
		Platform::CreateDebugWnd();
		// Initialize logger
		Logger::Register(std::make_unique<LogToDebugWindow>());
		TE_INFO("Logger LogToDebugWindow class registered as a listener\n");
	}

	// Create main window first
	Platform::CreateMainWnd();

	// Load plugings first
	PluginLoader::GetInstance()->LoadPlugins();

	gfx::GfxBackendParams gfxParams;
	gfxParams.backendDLLName = "GfxD3D11.dll";
	gfxParams.targetWindow = ((WindowBase*)Platform::GetMainWindow())->GetWindowHandle();
	gfxParams.SwapChainDesc = { };
	gfxParams.SwapChainDesc.format = gfx::TORC_GFX_RESOURCE_DATA_FORMAT::FORMAT_R8G8B8A8_UNORM;
	gfxParams.SwapChainDesc.samplingParams.count = 1;
	gfxParams.SwapChainDesc.samplingParams.quality = 0;

	bool isRendererInitialized = Renderer::Initialize(gfxParams);

	if (isRendererInitialized == false)
	{
		return false;
	}
			
	// Create and show window
	Platform::Startup();

	return true;
}
bool Application::Run(void* appConfig)
{
	if (!Application::Initialize(appConfig))
	{
		Shutdown();
		return false;
	}


	Application& app = *Application::Instance();
	app.m_isRunning = true;
	app.m_isSuspended = false;
	std::string test = "TorcEngine";
	int dot = 0;
	while (Torc::Platform::IsAnyWindowActive())
	{
		test += ".";
		dot++;
		Platform::SetWindowTitleForActiveWindows(test.c_str());
		Sleep(10);
		Platform::RemoveClosedWindow();

		if (dot == 200)
		{
			dot = 0;
			test = "TorcEngine";
		}
	}

	Shutdown();
	return false;
}

void Application::Shutdown()
{
	
	
	Renderer::Release();
	
	PluginLoader::Release();
	Logger::Shutdown();

	Platform::Shutdown();
	s_application.reset(nullptr);
	
}

