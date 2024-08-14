#pragma once
#include "Core/Base.h"

class WindowBase;
struct AppCreateParams;

enum class WindowMessage
{
	WINDOW_MESSAGE_PRINT_TO_WINDOW,
	WINDOW_MESSAGE_CLOSE_WINDOW,
};

namespace Torc
{
	class Platform
	{
	public:
		enum class WindowType
		{
			MainWindow = 0,
			DebugWindow,
			ChildWindow,
			Count
		};

		/**
		* Initialized the Platform layer and any related systems
		*/
		static void Initialize(AppCreateParams* params);

		/**
		* Creates a debug window that runs on its own thread. Debug window reflects log information in real time.
		*/
		static WindowBase* CreateDebugWnd();

		/**
		* Creates a main window which runs on its own thread, and used for rendering.
		*/
		static WindowBase* CreateMainWnd();

		/**
		*/
		static void Release();

		/**
		*/
		static void* MemAlloc(size_t bytes);

		/**
		*/
		static void* MemAllocAligned(size_t bytes, size_t align);

		/**
		*/
		static void MemFree(void* block);

		static void MemFreeAligned(void* block, uint8_t aligned = 0);

		/**
		*/
		static void MemSet(void* dest, int value, size_t size);

		/**
		*/
		static void MemCopy(void* dest, void* source, size_t size);

		/**  */
		static void MemZero(void* dest, size_t size);

		/**
		*/
		static bool GetSystemFrequency(int64_t& frequency);

		/**
		*/
		static bool GetSystemPerformanceCounter(int64_t& perfCount);
		static void GetSystemTime(SystemTime* systemTime);
		static const char* GetEngineRootDirectory();

		static bool SendMessageToWindow(TORC_HWND targetWindow, WindowMessage msg, void* data);

	private:
		static inline uintptr_t AlignAddress(uintptr_t addr, size_t align);
		static inline uint8_t* AlignPointer(uint8_t* ptr, size_t align);
	};
}