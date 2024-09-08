#include "SystemComponent.h"
#include <RHI/Include/base.h>
#include <Core/Environment/Environment.h>

#include <RHI/RHI.Public/RHIContext.h>
#include "RHI/DX11/Public/Factory_DX11.h"

namespace Torc
{
	namespace RHI
	{
		namespace DX11
		{
			void SystemComponent::Activate()
			{
				m_factory = torc_new DX11::Factory_DX11();
				Core::Environment::Register<Factory>((Factory*)m_factory);

				m_rhiContext = torc_new RHI::RHIContext();
				Core::Environment::Register<RHIContext>(m_rhiContext);
			}

			void SystemComponent::Deactivate()
			{
				Core::Environment::Unregister<Factory>((Factory*)m_factory);
				torc_delete m_factory;

				Core::Environment::Unregister<RHIContext>(m_rhiContext);
				torc_delete m_rhiContext;
			}
		}
	}
}
