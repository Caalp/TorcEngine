#include "WindowsPlatformComponent.h"
#include <Core/Platform/PlatformComponent.h>
#include <Platform/IO/FIleIO.h>

namespace Torc
{
	PlatformComponent* PlatformComponent::Create()
	{
		return new WindowsPlatformComponent();
	}

	WindowsPlatformComponent::WindowsPlatformComponent()
	{
		int a = 5;
		int b = a;
	}

	WindowsPlatformComponent::~WindowsPlatformComponent()
	{
		int a = 5;
	}

	void WindowsPlatformComponent::Activate()
	{
		m_fileIO = new IO::Windows::FileIO();
		IO::FileIOBase::SetInstance(m_fileIO);
	}

	void WindowsPlatformComponent::Deactivate()
	{
		IO::FileIOBase::SetInstance(nullptr);
		delete m_fileIO;
	}
}
