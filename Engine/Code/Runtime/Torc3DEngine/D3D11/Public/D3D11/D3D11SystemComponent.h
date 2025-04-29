#pragma once
#include <Core/Component/Component.h>

namespace Torc
{
	namespace RHI
	{
		namespace D3D11
		{
			class D3D11Factory;
		}
		class RHIContext;
		
		namespace D3D11
		{
			class D3D11SystemComponent : public Component
			{
			public:
				D3D11SystemComponent() = default;

				void Activate() override;
				void Deactivate() override;

			private:
				D3D11Factory* m_factory;
				RHIContext* m_rhiContext;
			};
		}
	}
}
