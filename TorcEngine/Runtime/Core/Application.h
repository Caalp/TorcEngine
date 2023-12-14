#pragma once
#include "Core/Input/BaseInput.h"
#include "Core/TorcSystem/ISystem.h"
#include "Platform/WindowBase.h"
#include "Core/Input/Mouse.h"
#include "Core/Input/Keyboard.h"
#include "Core/Input/Gamepad.h"

typedef void(*main)();

class PlatformInput;
class FileLogger;
class DebugWindowLogger;

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

class Application : public ISystemEventDispatcher, public IWindowEventListener
{
public:
	Application();
	bool Initialize(AppCreateParams& createParams);
	bool Run(main loop);
	void Release();

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

	uint64 GetMainThreadId() const;

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

	FileLogger* m_fileLogger;
	DebugWindowLogger* m_debugWindowLogger;

	PlatformInput* m_platformInput;
};