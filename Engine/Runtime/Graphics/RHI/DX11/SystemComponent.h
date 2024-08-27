#pragma once
#include <Core/Component/Component.h>

namespace Torc
{
	namespace RHI
	{
		class Factory;

		namespace DX11
		{
			class SystemComponent : public Component
			{
			public:
				SystemComponent() = default;

				void Activate() override;
				void Deactivate() override;

			private:
				Factory* m_factory;
			};
		}
	}
}
