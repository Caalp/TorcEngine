#include "pch.h"

#include "Core/Application.h"
#include "Core/Timer.h"
#include "Core/Logging/DebugWindowLogger.h"
#include "Platform/Platform.h"
#include "Platform/Windows/Window_Windows64.h"
#include "Platform/PlatformInput.h"

#include <windowsx.h>
#include <Dbt.h>

#define IDC_MAIN_EDIT 102

using namespace Torc;
static DebugWindowLogger* debugWindowLogger = nullptr;

namespace
{
	bool WindowResize(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		int32_t w = LOWORD(lParam);
		int32_t h = HIWORD(lParam);

		// Get window and client rects
		RECT clientRect;
		RECT wndRect;

		GetClientRect(hWnd, &clientRect);
		GetWindowRect(hWnd, &wndRect);

		return true;
	}
}

WindowWin64::~WindowWin64()
{
	if (m_windowStatus != WindowBase::WindowStatus::Closed)
	{
		DestroyWindow((HWND)m_windowHandle);
	}
}

LRESULT WindowWin64::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept
{
	if (msg == WM_NCCREATE) // sent WM_CREATE when a window is created
	{
		//defines initialization parameters passed to window application parameters same as CreateWindowEx
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lparam);
		WindowWin64* const pWnd = static_cast<WindowWin64*>(pCreate->lpCreateParams);
		//Stores and sets user initialized data to window
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WindowWin64::HandleMsgTh));

		return pWnd->HandleMsg(hWnd, msg, wparam, lparam);

	}
	return DefWindowProc(hWnd, msg, wparam, lparam);
}
LRESULT WindowWin64::HandleMsgTh(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept
{
	WindowWin64* const pWnd = reinterpret_cast<WindowWin64*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	return pWnd->HandleMsg(hWnd, msg, wparam, lparam);
}

void WindowWin64::ProcessMessages() noexcept
{
	if (!m_taskQueue.Empty())
	{
		Notify();
	}

	MSG msg;
	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

int32_t WindowWin64::CreateWnd(const WndCreateParams& params)
{
	SetWindowStatus(WindowStatus::Registering);
	m_windowParams = params;

	HINSTANCE instance = GetModuleHandle(nullptr);
	m_instance = instance;

	// Define and register class 
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instance; // GetHandle to the current application
	wc.hIcon = params.icon ? (HICON)params.icon : LoadIcon(instance, IDI_APPLICATION);
	wc.hCursor = params.cursor ? (HCURSOR)params.cursor : LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = params.windowClassName ? params.windowClassName : L"torc_engine_class";

	RegisterClassEx(&wc);

	std::wstring wstr = std::wstring(wc.lpszClassName);
	std::string str = std::string(wstr.begin(), wstr.end());

	RECT wr;
	wr.left = params.posX;
	wr.right = params.width + wr.left;
	wr.top = params.posY;
	wr.bottom = params.height + wr.top;
	AdjustWindowRect(&wr, params.windowStyle, FALSE);

	SetWindowStatus(WindowStatus::Creating);
	// Create Window
	m_windowHandle = CreateWindowA(str.c_str(),
		params.caption,
		params.windowStyle,
		params.posX - wr.left,
		params.posY - wr.top,
		wr.right - wr.left,
		wr.bottom - wr.top,
		params.parent ? (HWND)params.parent : nullptr,
		nullptr,
		instance, this);

	if (!m_windowHandle)
	{
		DWORD error = GetLastError();
		// Do stuff with error
		return 0;
	}

	ShowWindow((HWND)m_windowHandle, SW_SHOW);
	SetWindowStatus(WindowStatus::Ready);
	return 0;
}

void Torc::WindowWin64::Notify()
{
	if (m_windowStatus != WindowStatus::Ready)
	{
		return;
	}

	if (!PostMessageW((HWND)m_windowHandle, userDefinedMsgs, NULL, NULL))
	{
		LOG_ERROR(LogChannel::LC_Platform, "PostMessage failed! %s", __FILE__)
	}
}

void Torc::WindowWin64::SendMessageToWindow(WindowMessage message, void* data)
{
	switch (message)
	{
	case WindowMessage::WINDOW_MESSAGE_PRINT_TO_WINDOW:
		break;
	case WindowMessage::WINDOW_MESSAGE_CLOSE_WINDOW:
		SendMessageA(m_windowHandle, WM_CLOSE, 0, 0);
		break;
	default:
		break;
	}
}

Torc::MainWindow::MainWindow(const WndCreateParams& params)
{
	this->CreateWnd(params);
}

LRESULT MainWindow::HandleMsg(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept
{
	// imgui editor is one of the listeners
	OnWindowEvent(hWnd, msg, wparam, lparam);

	switch (msg)
	{
	case WM_DEVICECHANGE:
	{
		// NOTE(cagri): DEV_BROADCAST_DEVICEINTERFACE && RegisterDeviceNotification can be used to register this window
		// for specifically for HID devices msdn's system defined setup classes available with guid etc for each type
		gEnv->application->OnSystemEvent(SystemEvent::SYSTEM_EVENT_DEVICE_CHANGED, (UINT_PTR)hWnd, lparam, true);
		return true;
	}
	break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
	{
		SetWindowStatus(WindowStatus::Closed);
		gEnv->application->OnSystemEvent(SystemEvent::SYSTEM_EVENT_MAIN_WINDOW_CLOSED, (UINT_PTR)hWnd, 0);
		PostQuitMessage(0);
		break;
	}
	case WM_USER:
		m_taskQueue.ExecuteTask();
		break;
	case WM_SETTEXT:
		break;
	case WM_KILLFOCUS:
		break;
	case WM_EXITSIZEMOVE:
	{
		gEnv->application->OnSystemEvent(SystemEvent::SYSTEM_EVENT_WINDOW_RESIZED, (UINT_PTR)hWnd, lparam, true);
	}
	break;
	case WM_MOUSEMOVE:
	case WM_INPUT:
		//gEnv->input->InputEventMessage((void*)hWnd, msg, wparam, lparam);
		break;
	//case WM_KILLFOCUS:
	case WM_SETFOCUS:
		gEnv->application->OnSystemEvent(SystemEvent::SYSTEM_EVENT_WINDOW_SET_FOCUSE, (UINT_PTR)hWnd, lparam, true);
	break;

	}
	return DefWindowProc((HWND)hWnd, msg, wparam, lparam);
}

const char* Torc::MainWindow::GetName() const
{
	return "MainWindow";
}

Torc::DebugWindow::DebugWindow(const WndCreateParams& params)
{
	m_thread.Start(([this, params]() {
		this->CreateWnd(params);
		this->ProcessMessages();
		}));
}

Torc::DebugWindow::~DebugWindow()
{
	// NOTE(cagri): Later main thread will be calling delete on this object which will invoke
	// desctructor.
	m_thread.WaitToFinish();
	gEnv->logger->RemoveListener(debugWindowLogger);
	delete debugWindowLogger;
}

int32_t DebugWindow::CreateWnd(const WndCreateParams& params)
{
	SetWindowStatus(WindowStatus::Registering);
	m_windowParams = params;

	HINSTANCE instance = GetModuleHandle(nullptr);
	m_instance = instance;

	// Define and register class 
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instance; // GetHandle to the current application
	wc.hIcon = params.icon ? (HICON)params.icon : LoadIcon(instance, IDI_APPLICATION);
	wc.hCursor = params.cursor ? (HCURSOR)params.cursor : LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = params.windowClassName ? params.windowClassName : L"torc_engine_class";

	RegisterClassEx(&wc);

	std::wstring wstr = std::wstring(wc.lpszClassName);
	std::string str = std::string(wstr.begin(), wstr.end());

	RECT wr;
	wr.left = params.posX;
	wr.right = params.width + wr.left;
	wr.top = params.posY;
	wr.bottom = params.height + wr.top;
	AdjustWindowRect(&wr, params.windowStyle, FALSE);

	SetWindowStatus(WindowStatus::Creating);
	// Create Window
	m_windowHandle = CreateWindowA(str.c_str(),
		params.caption,
		params.windowStyle,
		params.posX - wr.left,
		params.posY - wr.top,
		wr.right - wr.left,
		wr.bottom - wr.top,
		(HWND)params.parent,
		nullptr,
		instance, this);

	if (!m_windowHandle)
	{
		DWORD error = GetLastError();
		LOG_ERROR(LogChannel::LC_Platform, "Failed to Create DebugWindow, Invalid Handle!");
		return 0;
	}
	gEnv->logger->RegisterListener(debugWindowLogger = new DebugWindowLogger(m_windowHandle));
	ShowWindow((HWND)m_windowHandle, SW_SHOW);
	SetWindowStatus(WindowStatus::Ready);
	return 0;
}

LRESULT DebugWindow::HandleMsg(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept
{
	switch (msg)
	{
	case WM_USER:
		m_taskQueue.ExecuteTask();
		break;
	case WM_CREATE:
	{
		m_debugHandle = CreateWindowEx(WS_EX_CLIENTEDGE,
			L"EDIT",
			L"",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL |
			ES_LEFT | ES_MULTILINE | ES_READONLY | ES_AUTOHSCROLL,
			0,
			0,
			780,
			560,
			hWnd,
			(HMENU)IDC_MAIN_EDIT,
			GetModuleHandle(NULL),
			NULL);
		HGDIOBJ hfDefault = GetStockObject(DEFAULT_GUI_FONT);
		SendMessage(m_debugHandle,
			WM_SETFONT,
			(WPARAM)hfDefault,
			MAKELPARAM(FALSE, 0));
		SendMessage(m_debugHandle,
			WM_SETTEXT,
			NULL,
			NULL);
		SendMessage(m_debugHandle, EM_SETLIMITTEXT, 4'000'000'000, 0);
	}
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
	{
		SetWindowStatus(WindowStatus::Closed);
		gEnv->application->OnSystemEvent(SystemEvent::SYSTEM_EVENT_WINDOW_CLOSED, (UINT_PTR)hWnd, 0, true);
		PostQuitMessage(0);
		break;
	}	
	}
	return DefWindowProc((HWND)hWnd, msg, wparam, lparam);
}

const char* Torc::DebugWindow::GetName() const
{
	return "DebugWindow";
}

void Torc::DebugWindow::SendMessageToWindow(WindowMessage message, void* data)
{
	WindowWin64::SendMessageToWindow(message, data);

	switch (message)
	{
	case WindowMessage::WINDOW_MESSAGE_PRINT_TO_WINDOW:
	{
		int ndx = GetWindowTextLength(m_debugHandle);
		SendMessageA(m_debugHandle, EM_SETSEL, (WPARAM)ndx, (LPARAM)ndx);
		SendMessageA(m_debugHandle, EM_REPLACESEL, 0, (LPARAM)data);
	}
	break;
	default:
		break;
	}
}

void Torc::DebugWindow::ProcessMessages() noexcept
{
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}