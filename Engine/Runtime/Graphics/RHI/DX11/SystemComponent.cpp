#include "SystemComponent.h"
#include <RHI/Include/base.h>
#include <RHI/RHI.Public/Factory.h>
#include <Core/Environment/Environment.h>

namespace Torc
{
	namespace RHI
	{
		namespace DX11
		{
			void SystemComponent::Activate()
			{
				m_factory = torc_new Factory();

				Core::Environment::Register<Factory>(m_factory);
			}

			void SystemComponent::Deactivate()
			{
				Core::Environment::Unregister<Factory>(m_factory);
				torc_delete m_factory;
			}
		}
	}
}
