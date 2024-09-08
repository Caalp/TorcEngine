#pragma once
#include <Core/Component/Component.h>

namespace Torc
{
	namespace RHI
	{
		namespace DX11
		{
			class Factory_DX11;
		}
		class RHIContext;
		
		namespace DX11
		{
			class SystemComponent : public Component
			{
			public:
				SystemComponent() = default;

				void Activate() override;
				void Deactivate() override;

			private:
				Factory_DX11* m_factory;
				RHIContext* m_rhiContext;
			};
		}
	}
}
