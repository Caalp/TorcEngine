#include "pch.h"
#include "WindowBase.h"

namespace
{
	std::vector<IWindowEventListener*> listeners;
}

TORC_HWND WindowBase::GetWindowHandle() const
{
    return m_windowHandle;
}

WindowBase::WindowStatus WindowBase::GetWindowStatus() const
{
	return m_windowStatus;
}

void WindowBase::SetWindowStatus(WindowStatus status)
{
	m_windowStatus = status;
}

bool WindowBase::RegisterListener(IWindowEventListener* pListener, const char* szName)
{
	for (auto& l : listeners)
	{
		if (l == pListener)
		{
			return false;
		}
	}

	listeners.push_back(pListener);
	return true;
}

bool WindowBase::RemoveListener(IWindowEventListener* pListener)
{
	return false;
}


void WindowBase::OnWindowEvent(TORC_HWND hWnd, uint32 msg, uint64 wparam, uint64 lparam, bool force_queue)
{
	for (IWindowEventListener* listener : listeners)
	{
		listener->OnWindowEvent(hWnd, msg, wparam, lparam);
	}
}