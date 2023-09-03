#include "pch.h"
#include "WindowBase.h"

void* WindowBase::GetWindowHandle() const
{
    return m_windowHandle;
}

WindowBase::WindowStatus WindowBase::GetWindowStatus() const
{
	return m_windowStatus.load();
}

void WindowBase::SetWindowStatus(WindowStatus status)
{
	m_windowStatus.store(status);
}