#pragma once
#include "Input/BaseInput.h"
#include "System/ISystem.h"
#include "Windowing/WindowBase.h"
#include "Input/Mouse.h"
#include "Input/Keyboard.h"
#include "Input/Gamepad.h"
#include "Memory/Memory.h"
#include "Std/String/String.h"
#include "Component/ApplicationComponent.h"
#include "RTTI/RttiMacros.h"
#include "Std/Threading/thread.h"

#include <memory>

typedef void(*main)();

class PlatformInput;
class DebugWindowLogger;

namespace Torc
{
	class FileLogger;
}

struct AppCreateParams
{
	uint16_t wndPosX;
	uint16_t wndPosY;
	uint16_t wndWidth;
	uint16_t wndHeight;
	const char* wndCaption;
	const char* cmdLineArgs;
	bool isEditor;
};

namespace Torc
{
	class Application
		: ApplicationComponent
		, public ISystemEventDispatcher
		, public IWindowEventListener
	{
	public:
		TORC_RTTI(Application, "{E41B911E-387F-4099-A23D-F986A05A2220}", ApplicationComponent, ISystemEventDispatcher, IWindowEventListener);

		Application();
		~Application();
		bool Initialize(AppCreateParams& createParams);
		bool Run(main loop);
		void Release();

		float GetPrevFrameDt() const;

		virtual bool RegisterListener(ISystemEventListener* pListener, const char* szName) override;
		virtual bool RemoveListener(ISystemEventListener* pListener) override;
		virtual void OnSystemEvent(SystemEvent event, UINT_PTR wparam, UINT_PTR lparam, bool force_queue = false) override;
		virtual bool OnWindowEvent(TORC_HWND hWnd, uint32 msg, uint64 wparam, uint64 lparam) override;
		virtual void Update() override;

		bool RegisterWindowEventListener(IWindowEventListener* listener, const char* listenerName);
		bool RemoveWindowEventListener(IWindowEventListener* listener);
		bool HasQuit() const;

		WindowBase* GetMainWindow();
		void SetMainWindow(WindowBase* mainWindow);

		WindowBase* GetDebugWindow();
		void SetDebugWindow(WindowBase* debugWindow);

		TORC_HWND GetMainWindowHandle() const;

		void SetEditorInstance(IEditor* editor);
		void ProcessCMDArgs(const char* args);

		bool IsLogToFileEnabled() const;
		bool IsDebugWindowEnabled() const;
		bool IsDebugInputDeviceEnabled() const;

		ILogger* GetLogger();
		PlatformInput* GetPlatformInput();
		BaseInput* GetBaseInput();
		Application* GetApplication();

		Std::thread::id GetMainThreadId() const;

		// Component impl
		Std::string GetName() const override { return _torcGetClassName(); }

	private:
		void ProcessSavedEventsIfAny();

		struct EventSaved
		{
			SystemEvent event;
			UINT_PTR wparam;
			UINT_PTR lparam;
		};

		struct CustomDeleter
		{
			void operator ()(WindowBase* wnd)
			{
				wnd->~WindowBase();
				Memory::Free(wnd);
			}
		};

		typedef std::unique_ptr<WindowBase, CustomDeleter> WindowBasePtr;
		typedef CString<32> CMDArg;
		typedef std::vector<CMDArg> CMDArgs;

		bool m_paused;
		bool m_quit;
		AppCreateParams m_createParams;
		std::vector<ISystemEventListener*> m_listeners;
		std::vector<WindowBasePtr> m_windows;

		ThreadSafeVector<EventSaved> m_savedEvents;
		BaseInput m_baseInput;

		Mouse m_mouse;
		Keyboard m_keyboard;
		DebugDevice m_dbgDevice;
		CMDArgs m_cmdArgList;

		Torc::FileLogger* m_fileLogger;
		DebugWindowLogger* m_debugWindowLogger;

		PlatformInput* m_platformInput;
	};
}

