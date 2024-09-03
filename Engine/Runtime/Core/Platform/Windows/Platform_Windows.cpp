#include "Core/Platform/Windows/Window_Windows.h"
#include "Core/TorcStd/String/string_utils.h"
#include "Core/Logging/Logger.h"
#include "Core/TorcSystem/ISystem.h"
#include "Core/Platform/Platform.h"

#include "Core/Input/PlatformInput.h"
#include "Core/Application.h"

namespace Torc
{
	static AppCreateParams appParams;
	static std::vector<WindowBase*> windowList;

	static WindowBase* GetWindowByHandle(TORC_HWND windowHandle)
	{
		for (auto& wnd : windowList)
		{
			if (wnd == nullptr)
			{
				continue;
			}

			TORC_HWND w = wnd->GetWindowHandle();
			if (w == windowHandle)
			{
				return wnd;
			}
		}
		return nullptr;
	}

	void Platform::Initialize(AppCreateParams* params)
	{
		appParams = *params;
	}

	WindowBase* Platform::CreateDebugWnd()
	{
		WindowBase::WndCreateParams params{ 0 };

		params.posX = 0;
		params.posY = 0;
		params.width = 800;
		params.height = 600;
		params.caption = "Debug Window";
		params.windowClassName = L"torc_engine_class_debug";
		params.windowStyle = WS_CAPTION;

		DebugWindow* window = Memory::Alloc<DebugWindow>(MemoryTag::MEMORY_TAG_PLATFORM, params);
		windowList.push_back(window);
		return window;
	}

	WindowBase* Platform::CreateMainWnd()
	{
		// create a main window
		WindowBase::WndCreateParams params{ 0 };

		params.posX = appParams.wndPosX;
		params.posY = appParams.wndPosY;
		params.width = appParams.wndWidth;
		params.height = appParams.wndHeight;
		params.caption = appParams.wndCaption;
		params.windowClassName = L"torc_engine_class";
		params.windowStyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_THICKFRAME;

		MainWindow* window = Memory::Alloc<MainWindow>(MemoryTag::MEMORY_TAG_PLATFORM, params);
		windowList.push_back(window);
		return window;
	}

	//void Platform::PrintToDebugWindow(const wchar_t* msg)
	//{
	//	DebugWindow* dbgWnd = dynamic_cast<DebugWindow*>(s_windows.back());
	//	if (dbgWnd == nullptr)
	//	{
	//		return;
	//	}
	//	std::wstring wmsg = msg;
	//	dbgWnd->PushTask([wmsg, handle = dbgWnd->m_debugHandle]()
	//		{
	//			SendMessage(handle, EM_SETSEL,
	//				GetWindowTextLength(handle),
	//				GetWindowTextLength(handle));
	//			SendMessage(handle, EM_REPLACESEL, FALSE, reinterpret_cast<LPARAM>(wmsg.c_str()));
	//		});
	//}

	void Platform::Release()
	{
		windowList.clear();
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

	void Torc::Platform::MemZero(void* dest, size_t size)
	{
		memset(dest, NULL, size);
	}

	bool Platform::GetSystemFrequency(int64_t& frequency)
	{
		return QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	}

	bool Platform::GetSystemPerformanceCounter(int64_t& perfCount)
	{
		return QueryPerformanceCounter((LARGE_INTEGER*)&perfCount);
	}

	void Platform::GetSystemTime(SystemTime* systemTime)
	{
		SYSTEMTIME win32SysTime;
		::GetSystemTime(&win32SysTime);

		*systemTime = { win32SysTime.wYear, win32SysTime.wMonth, win32SysTime.wDayOfWeek, win32SysTime.wDay, win32SysTime.wHour, win32SysTime.wMinute, win32SysTime.wSecond, win32SysTime.wMilliseconds };
	}

	const char* Platform::GetEngineRootDirectory()
	{
		return "";
	}

	bool Platform::SendMessageToWindow(TORC_HWND targetWindow, WindowMessage msg, void* data)
	{
		WindowBase* window = GetWindowByHandle(targetWindow);
		if (window == nullptr)
			return false;
		window->SendMessageToWindow(msg, data);
		return true;
	}

	uintptr_t Platform::AlignAddress(uintptr_t addr, size_t align)
	{
		const size_t mask = align - 1;
		// assert((align & mask) == 0)
		return (addr + mask) & ~mask;
	}

	uint8_t* Platform::AlignPointer(uint8_t* ptr, size_t align)
	{
		const uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
		const uintptr_t addrAligned = AlignAddress(addr, align);
		return reinterpret_cast<uint8_t*>(addrAligned);
	}

	void* Platform::LoadDLL(const char* lib)
	{

	}

	void* Platform::RetrieveMethodFromDLL(void* moduleInstance, const char* methodName)
	{

	}

	 void Platform::FreeDLL(void* moduleInstance)
	{

	}
}
