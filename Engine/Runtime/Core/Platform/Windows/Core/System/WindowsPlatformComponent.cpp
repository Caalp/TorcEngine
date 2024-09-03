#include "WindowsPlatformComponent.h"
#include "Core/Platform/Windows/Core/IO/FIleIO.h"

namespace Torc
{
	void WindowsPlatformComponent::Activate()
	{
		//m_fileIO = new IO::Windows::FileIO();
		//IO::FileIOBase::SetInstance(m_fileIO);
	}

	void WindowsPlatformComponent::Deactivate()
	{
		//IO::FileIOBase::SetInstance(nullptr);
		//delete m_fileIO;
	}
}
