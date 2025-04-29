#pragma once
#include "D3D11Base.h"
#include <RHI/Factory.h>

namespace Torc
{
	namespace RHI
	{
		namespace D3D11
		{
			class D3D11Factory : public RHI::Factory
			{
			public :
				D3D11Factory() = default;

			private:
				SwapChain* CreateSwapChainInternal() override;
				Device* CreateDeviceInternal() override;
			};
		}
	}
}
