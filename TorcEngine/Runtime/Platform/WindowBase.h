#pragma once
#include "Core/Containers/GenericTaskQueue.h"

class WindowBase
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

	void* GetWindowHandle() const;
	WindowStatus GetWindowStatus() const;
	void SetWindowStatus(WindowStatus status);

	template<typename F>
	void PushTask(F&& task);

	virtual void Notify() = 0;

protected:
	GenericTaskQueue m_taskQueue;
	void* m_windowHandle;
	WndCreateParams m_windowParams;
	std::thread m_windowThread;
	std::atomic<WindowStatus> m_windowStatus{ WindowStatus::NotExist };
};

template<typename F>
inline void WindowBase::PushTask(F&& task)
{
	m_taskQueue.PushTask(std::forward<F>(task));
	Notify();
}
