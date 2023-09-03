#pragma once

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
		static bool Startup();

		/**
		* Creates a debug window that runs on its own thread. Debug window reflects log information in real time.
		*/
		static void CreateDebugWnd();

		/**
		* Creates a main window which runs on its own thread, and used for rendering.
		*/
		static void CreateMainWnd();

		/**
		 * This function retrieves pointer to platform specific window class.
		 * To have leverage the functionality explicit casting to WindowBase required.
		 * In short all window classes are derived from WindowBase class.
		 * 
		 * @return void pointer to MainWindow class 
		 */
		static void* GetMainWindow();

		/**
		* Removes closed window from active windows list.
		*/
		static void RemoveClosedWindow();

		/**
		* 
		*/
		static void SetWindowTitleForActiveWindows(const char* title);

		/**
		*/
		static void SetWindowTitleAt(const char* title, int idx);

		/**
		*/
		static void PrintToDebugWindow(const wchar_t* msg);

		/**
		*/
		static void Shutdown();

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
		static int32_t ProcessMessages() noexcept;

		/**
		*/
		static void GetSystemFrequency(int64_t& frequency);

		/**
		*/
		static void GetSystemPerformanceCounter(int64_t& perfCount);

		/**
		*/
		static bool IsAnyWindowActive();

	private:
		static inline uintptr_t AlignAddress(uintptr_t addr, size_t align);
		static inline uint8_t* AlignPointer(uint8_t* ptr, size_t align);
	};
}