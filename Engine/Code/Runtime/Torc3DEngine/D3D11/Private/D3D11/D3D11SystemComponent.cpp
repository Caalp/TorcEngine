#include "D3D11/D3D11SystemComponent.h"
#include <Core/Base.h>
#include <Core/Environment/Environment.h>

#include <RHI/RHIContext.h>
#include "D3D11/D3D11Factory.h"

namespace Torc
{
	namespace RHI
	{
		namespace D3D11
		{
			void D3D11SystemComponent::Activate()
			{
				m_factory = torc_new D3D11Factory();
				Core::Environment::Register<Factory>((Factory*)m_factory);

				m_rhiContext = torc_new RHI::RHIContext();
				Core::Environment::Register<RHIContext>(m_rhiContext);
			}

			void D3D11SystemComponent::Deactivate()
			{
				Core::Environment::Unregister<Factory>((Factory*)m_factory);
				torc_delete m_factory;

				Core::Environment::Unregister<RHIContext>(m_rhiContext);
				torc_delete m_rhiContext;
			}
		}
	}
}
