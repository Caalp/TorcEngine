#include "pch.h"

#include "Platform/Windows/WindowWin64.h"
#include <windowsx.h>

using namespace Torc;
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
	if (m_windowThread.joinable())
	{
		m_windowThread.join();
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
	SetWindowStatus(WindowStatus::Ready);
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	SetWindowStatus(WindowStatus::Closed);
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
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
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
	//UpdateWindow(m_wndHandle);
	return 0;
}

void Torc::WindowWin64::Notify()
{
	if (!PostMessageW((HWND)m_windowHandle, userDefinedMsgs, NULL, NULL))
	{
		TE_ERROR("PostMessage failed!", __FILE__)
	}
}

LRESULT MainWindow::HandleMsg(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
	{
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
	case WM_KEYDOWN:
		break;
	case WM_SYSKEYDOWN:
		break;
	case WM_KEYUP:
		break;
	case WM_SYSKEYUP:
		break;
	case WM_CHAR:
		break;
	case WM_MOUSEMOVE:
	{
		POINT point;
		//GetCursorPos(&point);
		point.x = GET_X_LPARAM(lparam);
		point.y = GET_Y_LPARAM(lparam);
		char buffer[100];
		sprintf_s(buffer, "mouse position: X=%d, Y=%d\n", point.x, point.y);
		OutputDebugStringA(buffer);
	}
	break;
	case WM_MOUSELEAVE:
		OutputDebugStringA("Mouse outside of the client area!\n");
		break;
	case WM_MOUSEHOVER:
		OutputDebugStringA("Mouse hovered over the client area!\n");
		break;
	case WM_LBUTTONDOWN:
	{
		break;
	}
	case WM_RBUTTONDOWN:
	{
		break;
	}
	case WM_LBUTTONUP:
	{
		break;
	}
	case WM_RBUTTONUP:
	{

		break;
	}
	case WM_MOUSEWHEEL:
	{
		break;
	}

	}
	return DefWindowProc((HWND)hWnd, msg, wparam, lparam);
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
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
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

	m_debugHandle = CreateWindow(
		L"EDIT",  // Predefined class; Unicode assumed 
		L"",      // Button text 
		WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL |
		ES_LEFT | ES_MULTILINE | ES_READONLY | ES_AUTOHSCROLL,  // Styles 
		0,         // x position 
		0,         // y position 
		800,        // Button width
		600,        // Button height
		(HWND)this->m_windowHandle,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLongPtr((HWND)this->m_windowHandle, GWLP_HINSTANCE),
		this);      // Pointer not needed.

	if (!m_debugHandle)
	{
		DWORD error = GetLastError();
		// Do stuff with error
		return 0;
	}

	ShowWindow((HWND)m_windowHandle, SW_SHOW);
	//UpdateWindow(m_wndHandle);
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
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_SIZE:
	{
		MoveWindow((HWND)m_windowHandle, 0, 0, LOWORD(lparam), HIWORD(lparam), TRUE);
		return 0;
	}
	}
	return DefWindowProc((HWND)hWnd, msg, wparam, lparam);
}
