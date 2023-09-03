#include "pch.h"

#include "Common/StringUtils.h"
#include "Platform/Platform.h"
#include "Platform/Windows/WindowWin64.h"
#include "Core/Logging/Logger.h"

using namespace Torc;

namespace
{
	// index 0 is reserved for main window
	static constexpr uint32_t s_mainWindowIndex = 0u;
	std::vector<WindowWin64*> s_windows(1);

	void WaitUntilWindowIsReady(WindowWin64* wnd)
	{
		while (!(wnd->GetWindowStatus() == WindowWin64::WindowStatus::Ready));
	}
}

bool Platform::Startup()
{
	return true;
}

void Platform::CreateDebugWnd()
{
	WindowWin64::WndCreateParams params{ 0 };

	params.posX = 0;
	params.posY = 0;
	params.width = 800;
	params.height = 600;
	params.caption = "Debug Window";
	params.windowClassName = L"torc_engine_class_debug";
	params.windowStyle = WS_OVERLAPPED | WS_THICKFRAME | WS_VISIBLE;

	s_windows.emplace_back(TE_NEW(DebugWindow, MemoryTag::MEMORY_TAG_PLATFORM, params));
	WaitUntilWindowIsReady(s_windows.back());
}

void Platform::CreateMainWnd()
{
	// create a main window
	WindowBase::WndCreateParams params{ 0 };

	params.posX = 0;
	params.posY = 0;
	params.width = 1280;
	params.height = 720;
	params.caption = "TorcEngine";
	params.windowClassName = L"torc_engine_class";
	params.windowStyle = WS_VISIBLE | WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;

	s_windows[s_mainWindowIndex] = TE_NEW(MainWindow, MemoryTag::MEMORY_TAG_PLATFORM, params);
	WaitUntilWindowIsReady(s_windows[s_mainWindowIndex]);
}

void* Platform::GetMainWindow()
{
	return s_windows[s_mainWindowIndex];
}

void Platform::PrintToDebugWindow(const wchar_t* msg)
{
	DebugWindow* dbgWnd = dynamic_cast<DebugWindow*>(s_windows.back());
	if (dbgWnd == nullptr)
	{
		
		return;
	}
	HWND handle = dbgWnd->m_debugHandle;
	SendMessage(handle, EM_SETSEL,
		GetWindowTextLength(handle),
		GetWindowTextLength(handle));
	SendMessage(handle, EM_REPLACESEL, FALSE, reinterpret_cast<LPARAM>(msg));
}

void Platform::RemoveClosedWindow()
{
	for (std::vector<WindowWin64*>::iterator it = s_windows.begin(); it != s_windows.end(); ++it)
	{
		if ((*it)->GetWindowStatus() == WindowWin64::WindowStatus::Closed)
		{
			TE_DELETE(*it);
			s_windows.erase(it);
			break;
		}
	}
}

void Platform::SetWindowTitleForActiveWindows(const char* title)
{
	for (auto& w : s_windows)
	{
		w->PushTask([&]()
			{ 
				SetWindowTextW((HWND)w->GetWindowHandle(), String::Utils::ConvertToWideChar(title).c_str());
			});
	}
}

void Platform::SetWindowTitleAt(const char* title, int idx)
{
	if (idx < s_windows.size() && s_windows[idx] != nullptr)
	{
		s_windows[idx]->PushTask([&]()
			{
				SetWindowTextW((HWND)s_windows[idx]->GetWindowHandle(), String::Utils::ConvertToWideChar(title).c_str());
			});
	}
	else
	{
		return;
	}
}

int32_t Platform::ProcessMessages() noexcept
{
	//MSG msg;
	//// while queue has messages, remove and dispatch them (but do not block on empty queue)
	//while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	//{

	//	// check for quit because peekmessage does not signal this via return val
	//	if (msg.message == WM_QUIT)
	//	{
	//		// checks and removes recently closed window
	//		RemoveClosedWindow();

	//		if (s_windows.empty())
	//		{
	//			return (int)msg.wParam;
	//		}
	//		// return optional wrapping int (arg to PostQuitMessage is in wparam) signals quit
	//	}

	//	// TranslateMessage will post auxilliary WM_CHAR messages from key msgs
	//	TranslateMessage(&msg);
	//	DispatchMessage(&msg);
	//}
	// return empty optional when not quitting app
	return 1;
}

void Platform::Shutdown()
{
	for (auto& w : s_windows)
	{
		std::packaged_task<void()> task([&]()
			{
				if (!DestroyWindow((HWND)w->GetWindowHandle()))
				{
					DWORD dError = GetLastError();
					char a[64];
					sprintf_s(a, "An error occured while Destroying window error code: %lu!\n", dError);
					OutputDebugStringA(a);
				}
				
			});
		std::future<void> f = task.get_future();

		w->PushTask(task);
		f.get();

		TE_DELETE(w);
	}

	s_windows.clear();
}

void* Platform::MemAlloc(size_t bytes)
{
	return malloc(bytes);
}

void* Platform::MemAllocAligned(size_t bytes, size_t align)
{
	size_t totalBytes = bytes + align;
	uint8_t* rawMem = (uint8_t*)MemAlloc(totalBytes);

	uint8_t* alignedMem = AlignPointer(rawMem, align);
	if (rawMem == alignedMem)
	{
		alignedMem += align;
	}
	ptrdiff_t diff = alignedMem - rawMem;
	alignedMem[-1] = static_cast<uint8_t>(diff & 0xff);
	return alignedMem;
}

void Platform::MemFree(void* block)
{
	free(block);
}

void Platform::MemFreeAligned(void* block, uint8_t aligned)
{
	if (block)
	{
		uint8_t* mem = reinterpret_cast<uint8_t*>(block);
		ptrdiff_t diff = mem[-1];
		diff = (diff == 0) ? 256 : diff;

		uint8_t* adjustedMem = mem - diff;

		//delete[] adjustedMem;
		Torc::Platform::MemFree((void*)adjustedMem);
	}
}

void Platform::MemSet(void* dest, int value, size_t size)
{
	memset(dest, value, size);
}

void Platform::MemCopy(void* dest, void* source, size_t size)
{
	memcpy(dest, source, size);
}

void Platform::GetSystemFrequency(int64_t& frequency)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
}

void Platform::GetSystemPerformanceCounter(int64_t& perfCount)
{
	QueryPerformanceCounter((LARGE_INTEGER*)&perfCount);
}

bool Platform::IsAnyWindowActive()
{
	return s_windows.size() > 0;
}

uintptr_t Torc::Platform::AlignAddress(uintptr_t addr, size_t align)
{
	const size_t mask = align - 1;
	// assert((align & mask) == 0)
	return (addr + mask) & ~mask;
}

uint8_t* Torc::Platform::AlignPointer(uint8_t* ptr, size_t align)
{
	const uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
	const uintptr_t addrAligned = AlignAddress(addr, align);
	return reinterpret_cast<uint8_t*>(addrAligned);
}
