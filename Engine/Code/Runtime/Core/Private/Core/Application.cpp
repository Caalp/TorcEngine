#include "Core/Application.h"

#include "Core/Std/String/string_utils.h"
#include "Core/Profiling/Timer.h"
#include "Core/Module/ModuleManager.h"
#include "Core/Logging/Logger.h"

#include "Core/Platform/Platform.h"
#include "Core/Windowing/WindowBase.h"
#include "Core/Input/PlatformInput.h"
#include "Core/Input/BaseInput.h"
#include "Core/Profiling/SystemTimer.h"
#include "Core/Logging/DebugWindowLogger.h"
#include "Core/Logging/FileLogger.h"

#include <RapidJSON/document.h>
#include <CityHash/city.h>
#include "Core/Component/Entity.h"
#include "Core/Component/Component.h"

#include <stdarg.h>

using namespace Torc;

extern SystemGlobalEnvironment* gEnv = nullptr;

void PrintDebug(const char* str, ...)
{
	char dbg[256];

	va_list args;
	va_start(args, str);
	vsnprintf(dbg, _countof(dbg), str, args);
	va_end(args);

}

namespace
{
	SystemGlobalEnvironment env;
	//Renderer rr;
	ModuleManager moduleManager;
	ILogger* logger;
	WindowBase* mainWnd = nullptr;
	WindowBase* debugWnd = nullptr;
	SystemTimer sysTimer;
}

namespace Torc
{
	Application::Application()
		: m_quit(false)
		, m_paused(false)
		, m_fileLogger(nullptr)
		, m_debugWindowLogger(nullptr)
	{
		gEnv = &env;
		gEnv->mainThreadId = Std::this_thread::get_id();
		gEnv->application = this;

		//m_ecFactory = new EntityComponentFactory;
	}

	Application::~Application()
	{

	}

	bool Application::Initialize(AppCreateParams& createParams)
	{

		ProcessCMDArgs(createParams.cmdLineArgs);

		//TODO(cagri): gEnv should be initialized by the constructor
		logger = new LoggerBase;
		gEnv->logger = logger;

		m_createParams = createParams;

		if (createParams.isEditor)
		{
			gEnv->editor->Initialize();
		}
		Torc::Platform::Initialize(&createParams);

		if (IsLogToFileEnabled())
		{
			m_fileLogger = new Torc::FileLogger;
			gEnv->logger->RegisterListener(m_fileLogger);
		}

		if (IsDebugWindowEnabled())
		{
			// Initialize logger
			m_windows.emplace_back(WindowBasePtr{ Platform::CreateDebugWnd() });
		}

		mainWnd = Platform::CreateMainWnd();
		//ASSERT(mainWnd != nullptr, "MainWindow initialization failed.");
		OnSystemEvent(SystemEvent::SYSTEM_EVENT_MAIN_WINDOW_INITIALIZED, 0, 0);

		m_windows.emplace_back(WindowBasePtr{ mainWnd });

		// main window is needed for the majority of the systems below, so need to make sure that main window is exist
		m_platformInput = new PlatformInput;
		m_platformInput->Initialize(*gEnv, mainWnd);
		m_baseInput.Initialize(*gEnv);
		m_mouse.Initialize(&m_baseInput);
		m_keyboard.Initialize(&m_baseInput);

		if (IsDebugInputDeviceEnabled())
		{
			m_dbgDevice.Initialize(&m_baseInput);
		}

		/*gfx::GfxBackendParams gfxParams;
		gfxParams.backendDLLName = "TE.GfxD3D11.dll";
		gfxParams.targetWindow = mainWnd->GetWindowHandle();
		gfxParams.SwapChainDesc = { };
		gfxParams.SwapChainDesc.width = createParams.wndWidth;
		gfxParams.SwapChainDesc.height = createParams.wndHeight;
		gfxParams.SwapChainDesc.format = gfx::TORC_GFX_RESOURCE_DATA_FORMAT::FORMAT_R8G8B8A8_UNORM;
		gfxParams.SwapChainDesc.samplingParams.count = 1;
		gfxParams.SwapChainDesc.samplingParams.quality = 0;*/

		// TODO(cagri): These logs will not be printed to log window because it is not initialized fully
		// log window is running on a separate thread, take care of this later!
		/*TE_Info(LogChannel::LC_Core, "Initializing Renderer...");
		bool isRendererInitialized = rr.Initialize(*gEnv, gfxParams);*/

		/*ASSERT(isRendererInitialized == true, "Renderer Init Failed.");
		for (ISystemEventListener* listener : m_listeners)
		{
			listener->OnSystemEvent(SystemEvent::SYSTEM_EVENT_RENDERER_INITIALIZED, 0, 0);
		}*/

		return true;
	}

	struct TestComponent0
	{
		const char* name;
		int size;
	};

	struct TestComponent1
	{
		int size;
	};

	struct TestComponent2
	{
		int size;
		float v;
		double s;
	};

	struct TestComp : Torc::Component
	{

	};

	bool Application::Run(main mainLoop)
	{
		core::Timer timer;
		timer.Start();
		core::Timer::ElapsedTime fTime{};

		std::string filepath = "C:/Users/calp/source/repos/TorcEngine/TorcEngine/Assets/wall.bmp";

		using namespace Torc::Core;

		//Entity* entity0 = m_ecManager->Create();
		//bool addResult = entity0->AssignComponent(tc);
		/*
			resolving asset paths:
			look up from most inner directory to outward one by one

			img: texture -> i.e. img:Assets/wall.bmp
			tech: technique
			shader:
			pass:
			mat:
			sound:
			cfg:
		*/

		//Asset
			//GetRefCount
			//IsLoaded
			//GetId
			//GetPath
			//GetAssetType
			//GetStatus
			//GetFullpath
			//GetName
			//GetSize


		// AssetManager
			// GetAssetCount
			// GetUnloadedAssetCount
			// GetLoadedAssetCount
			// GetMemoryUsage
			// GetAssetDatabase

		// AssetDatabase


		//Torc::FileStream fs;
		//TORC_HANDLE file = fs::OpenFile(filepath.c_str(), FileAccessMode::Access_Read, FileShareMode::Share_None, FileCreationFlag::Open_Existing);

		uint8* data = nullptr;
		rapidjson::Document document;
		const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";


		document.Parse(json);
		assert(document.HasMember("hello"));
		assert(document["hello"].IsString());

		char msg[64];
		sprintf_s(msg, "hello = %s\n", document["hello"].GetString());

		int i = 0;
		while (!m_quit)
		{
			sysTimer.UpdateTimer();

			mainWnd->ProcessMessages();

			m_baseInput.Update();

			//gEnv->rr->BeginFrame();

			if (m_baseInput.IsKeyDown(KeyCode::KC_A) && m_baseInput.IsKeyDown(KeyCode::KC_B))
			{
				TE_Info(LogChannel::LC_Core, "AAAAAAAAAAAAAA");
			}
			if (m_baseInput.IsKeyDown(KeyCode::KC_Gamepad_A) && m_baseInput.IsKeyDown(KeyCode::KC_Gamepad_B))
			{
				TE_Info(LogChannel::LC_Core, "BBBBBBBBBBBBBB");
			}

			// NOTE(cagri): this is here for only testing purposes
			mainLoop();

			//gEnv->rr->EndFrame();

			// TODO(cagri): should we do this at the beginning of the frame, then we should care about 
			// handling potential null pointers ??
			// process events from beginning of the frame if any
			ProcessSavedEventsIfAny();

			fTime = timer.Elapsed();
			//TE_Info(LogChannel::LC_Core, "FrameTime: %lf", sysTimer.GetRawFrameTime());
		}
		return false;
	}

	void Application::Release()
	{
		m_platformInput->Release();

		Platform::Release();

		delete logger;
		if (m_fileLogger)
			delete m_fileLogger;
		if (m_debugWindowLogger)
			delete m_debugWindowLogger;

		m_baseInput.Release();
		delete m_platformInput;
		Torc::Platform::MemZero((void*)gEnv, sizeof(SystemGlobalEnvironment));

		logger = nullptr;
		mainWnd = nullptr;
		debugWnd = nullptr;
		env = { 0 };
		gEnv = nullptr;
	}

	float Application::GetPrevFrameDt() const
	{
		return (float)sysTimer.GetAverageFrameTime();
	}

	bool Application::RegisterListener(ISystemEventListener* pListener, const char* szName)
	{
		for (auto& l : m_listeners)
		{
			if (l == pListener)
			{
				return false;
			}
		}

		m_listeners.push_back(pListener);
		return true;
	}

	bool Application::RemoveListener(ISystemEventListener* pListener)
	{
		return false;
	}

	void Application::OnSystemEvent(SystemEvent event, UINT_PTR wparam, UINT_PTR lparam, bool forceQueue)
	{
		if (forceQueue)
		{
			m_savedEvents.PushBack({ event, wparam, lparam });
			return;
		}

		switch (event)
		{
		case SYSTEM_EVENT_GAME_PAUSED:
			m_paused = true;
			break;
		case SYSTEM_EVENT_GAME_RESUMED:
			m_paused = false;
			break;
		case SYSTEM_EVENT_ENGINE_SHUTDOWN:
			m_quit = true;
			break;
		case SYSTEM_EVENT_WINDOW_CLOSED:
		{
			// save event to the queue and process next frame
			m_savedEvents.PushBack({ event, wparam, lparam });
			return;
		}
		break;
		case SYSTEM_EVENT_MAIN_WINDOW_CLOSED:
		{
			// NOTE(cagri): sending engine shutdown event to the systems from main window closed event
			// reason is for that subsystems should not be caring whether we have a window or not they are only 
			// dependent on the engine itself which can run without a window as well. Application is interested in 
			// window messages and handling it.
			// 
			// send shutdown event to listeners this frame to tell engine is shutting down
			// we will deal with window closed event in next frame
			m_savedEvents.PushBack({ event, wparam, lparam });
			for (ISystemEventListener* listener : m_listeners)
			{
				listener->OnSystemEvent(SystemEvent::SYSTEM_EVENT_ENGINE_SHUTDOWN, 0, 0);
			}
			return;
		}
		break;
		case SYSTEM_EVENT_WINDOW_RESIZED:
		{
			// currently only renderer will be interested with this event and we can handle it from here
			if (GetMainWindowHandle() == (TORC_HWND)wparam)
			{
				uint32 width = (uint64)lparam & 0xffff;
				uint32 height = ((uint64)lparam >> 16) & 0xffff;
				//gEnv->rr->OnWindowResize(width, height);
			}
		}
		break;
		case SYSTEM_EVENT_DEVICE_CHANGED:
		{
			m_baseInput.HandleDeviceChange();
		}
		break;
		default:
			break;
		}

		for (ISystemEventListener* listener : m_listeners)
		{
			listener->OnSystemEvent(event, wparam, lparam);
		}
	}

	bool Application::OnWindowEvent(TORC_HWND hWnd, uint32 msg, uint64 wparam, uint64 lparam)
	{
		return false;
	}

	void Application::Update()
	{}

	bool Application::RegisterWindowEventListener(IWindowEventListener* listener, const char* listenerName)
	{
		return mainWnd->RegisterListener(listener, listenerName);
	}

	bool Application::RemoveWindowEventListener(IWindowEventListener* listener)
	{
		return mainWnd->RemoveListener(listener);
	}

	bool Application::HasQuit() const
	{
		return m_quit;
	}

	WindowBase* Application::GetMainWindow()
	{
		return mainWnd;
	}

	void Application::SetMainWindow(WindowBase* mainWindow)
	{
		mainWnd = mainWindow;
	}

	WindowBase* Application::GetDebugWindow()
	{
		return debugWnd;
	}

	void Application::SetDebugWindow(WindowBase* debugWindow)
	{
		debugWnd = debugWindow;
	}

	TORC_HWND Application::GetMainWindowHandle() const
	{
		return (TORC_HWND)mainWnd->GetWindowHandle();
	}

	void Application::SetEditorInstance(IEditor* editor)
	{
		gEnv->editor = editor;
	}

	void Application::ProcessCMDArgs(const char* args)
	{
		/*
		* Note: multiple args are separated by space
		* Args argument will be in the form of --testArg0--testArg1 etc
		* so as we go, we find index of the - in the string and iterate through
		* until none is left. As we extract args we store them in a list.
		*/

		const char* const argSeparator = "--";
		const char* dash = strstr(args, argSeparator);
		while (dash != nullptr)
		{
			// we assume a valid argument always has -- in the start of it 
			const char* dash2 = strstr(dash + 1, argSeparator);
			uint64 strLen = (uint64)dash2 - (uint64)dash - 3;
			if (dash2 == nullptr)
				strLen = strlen(dash) - 2; // additional -1 for second -
			CMDArg arg;

			// -2 for - at the begining and space at the end so we dont capture them
			Torc::Platform::MemCopy(arg.Data(), (void*)(dash + 2), strLen);
			m_cmdArgList.emplace_back(arg);
			dash = dash2;
		}
	}

	bool Application::IsLogToFileEnabled() const
	{
		const auto& iter = std::find_if(m_cmdArgList.begin(), m_cmdArgList.end(),
			[](CMDArg arg) -> bool { return (arg == CMDArg("noLogToFile")); });
		return (iter == m_cmdArgList.end());
	}

	bool Application::IsDebugWindowEnabled() const
	{
		const auto& iter = std::find_if(m_cmdArgList.begin(), m_cmdArgList.end(),
			[](CMDArg arg) -> bool { return (arg == CMDArg("debugWindow")); });
		return (iter != m_cmdArgList.end());
	}

	bool Application::IsDebugInputDeviceEnabled() const
	{
		const auto& iter = std::find_if(m_cmdArgList.begin(), m_cmdArgList.end(),
			[](CMDArg arg) -> bool { return (arg == CMDArg("debugInputDevice")); });
		return (iter != m_cmdArgList.end());
	}

	ILogger* Application::GetLogger()
	{
		return gEnv->logger;
	}

	PlatformInput* Application::GetPlatformInput()
	{
		return gEnv->platformInput;
	}

	BaseInput* Application::GetBaseInput()
	{
		return &m_baseInput;
	}

	Application* Application::GetApplication()
	{
		return gEnv->application;
	}

	Std::thread::id Application::GetMainThreadId() const
	{
		return gEnv->mainThreadId;
	}

	void Application::ProcessSavedEventsIfAny()
	{
		if (m_savedEvents.Size() == 0)
		{
			return;
		}
		// process saved events
		for (int i = 0; i < m_savedEvents.Size(); i++)
		{
			switch (m_savedEvents[i].event)
			{
			case SYSTEM_EVENT_WINDOW_CLOSED:
			{
				m_windows.erase(std::remove_if(m_windows.begin(), m_windows.end(),
					[&](const auto& val) {
						if (val->GetWindowHandle() == (void*)m_savedEvents[i].wparam)
						{
							val->SendMessageToWindow(WindowMessage::WINDOW_MESSAGE_CLOSE_WINDOW, 0);
							return true;
						}
						return false;
					}));
			}
			break;
			case SYSTEM_EVENT_MAIN_WINDOW_CLOSED: // main window emits this message, so it is already existed
			{
				// debug window is watching this for variable to
				// quit its message loop
				// NOTE(cagri): in the future we can replace this with work queue
				// or something similar so thread doesn't spin for nothing
				m_quit = true;
				m_windows.erase(std::remove_if(m_windows.begin(), m_windows.end(),
					[&](const auto& val) {
						if (val.get() != mainWnd)
						{
							// only send message to other windows and erase main one
							val->SendMessageToWindow(WindowMessage::WINDOW_MESSAGE_CLOSE_WINDOW, 0);
							return false;
						}
						return true;
					}));

				/*for (int wndIndex = 0; wndIndex < (int)m_windows.size(); ++wndIndex)
				{
					if (m_windows[wndIndex].get() != mainWnd)
					{
						m_windows[wndIndex]->SendMessageToWindow(WindowMessage::WINDOW_MESSAGE_CLOSE_WINDOW, 0);
					}
				}*/
			}
			break;
			default:
				OnSystemEvent(m_savedEvents[i].event, m_savedEvents[i].wparam, m_savedEvents[i].lparam);
				break;
			}
		}
		m_savedEvents.Clear();
	}
}
