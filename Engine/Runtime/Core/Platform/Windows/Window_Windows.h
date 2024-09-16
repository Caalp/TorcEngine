#pragma once
#define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers
#include <Windows.h>

#include "Core/Windowing/WindowBase.h"

namespace Torc
{
	class WindowWin64 : public WindowBase
	{
		typedef LRESULT(CALLBACK* WndProcFunc)(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);
	public:

		WindowWin64(const WindowWin64&) = delete;
		WindowWin64& operator=(const WindowWin64&) = delete;
		~WindowWin64();

		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept;
		static LRESULT CALLBACK HandleMsgTh(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept;
		virtual LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept = 0;
		virtual void ProcessMessages() noexcept override;
		virtual int32_t CreateWnd(const WndCreateParams& params);
		virtual void Notify() override;
		virtual void SendMessageToWindow(WindowMessage message, void* data) override;

	protected:
		WindowWin64() = default;
		static constexpr uint32_t userDefinedMsgs = 0x0400;

	protected:
		
		HINSTANCE m_instance;
	};

	class MainWindow final : public WindowWin64
	{
	public:
		MainWindow(const WndCreateParams& params);
		~MainWindow() = default;

		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept override;
		virtual const char* GetName() const override;
	};

	class DebugWindow : public WindowWin64
	{
	public:
		DebugWindow(const WndCreateParams& params);
		~DebugWindow();
		virtual int32_t CreateWnd(const WndCreateParams& params) override;
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept override;
		virtual const char* GetName() const override;
		virtual void SendMessageToWindow(WindowMessage message, void* data) override;
		virtual void ProcessMessages() noexcept override;
		HWND m_debugHandle;
	private:
		Std::thread m_thread;
	};
}