#include "Core/System/System.h"
#include "Core/System/SystemComponent.h"
#include "Core/Platform/PlatformComponent.h"

void Torc::System::Initialize()
{
	m_platformComponent = PlatformComponent::Create();
}

void Torc::System::Shutdown()
{
	delete m_platformComponent;
}

void Torc::System::Activate()
{
	m_platformComponent->Activate();
}

void Torc::System::Deactivate()
{
	m_platformComponent->Deactivate();
}
