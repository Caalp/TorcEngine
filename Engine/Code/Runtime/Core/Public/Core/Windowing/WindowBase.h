#pragma once

#include "Core/Base.h"
#include "Core/JobSystem/GenericTaskQueue.h"
#include "Core/Std/Threading/Thread.h"
#include "Core/System/ISystem.h"

class WindowBase : public IWindowEventDispatcher
{
public:
	enum class WindowStatus
	{
		NotExist,
		Creating,
		Registering,
		Ready,
		Closing,
		Closed,
		Count
	};

	struct WndCreateParams
	{
		uint16_t posX;
		uint16_t posY;
		uint16_t width;
		uint16_t height;
		uint32_t windowStyle; // TODO: define engine specific types
		const char* caption;
		const wchar_t* windowClassName; // should be unique for each window or they will share wndproc
		void* parent; 
		void* icon;
		void* cursor;
	};

	virtual ~WindowBase() = default;

	TORC_HWND GetWindowHandle() const;
	WindowStatus GetWindowStatus() const;
	void SetWindowStatus(WindowStatus status);

	virtual bool RegisterListener(IWindowEventListener* pListener, const char* szName) override;
	virtual bool RemoveListener(IWindowEventListener* pListener) override;
	virtual void OnWindowEvent(TORC_HWND hWnd, uint32 msg, uint64 wparam, uint64 lparam, bool force_queue = false) override;
	virtual void Update() override {};

	template<typename F>
	void PushTask(F&& task);

	// TODO: instead of directly handling messages we can store them and process later on
	virtual void SendMessageToWindow(WindowMessage message, void* data) = 0;
	virtual void Notify() = 0;
	virtual void ProcessMessages() noexcept = 0;
	virtual const char* GetName() const = 0;
protected:
	GenericTaskQueue m_taskQueue;
	TORC_HWND m_windowHandle;
	WndCreateParams m_windowParams;
	WindowStatus m_windowStatus{ WindowStatus::NotExist };
};

template<typename F>
inline void WindowBase::PushTask(F&& task)
{
	m_taskQueue.PushTask(std::forward<F>(task));
	Notify();
}