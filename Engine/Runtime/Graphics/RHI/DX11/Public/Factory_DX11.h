#pragma once
#include "RHI/DX11/Include/base.h"
#include <RHI/RHI.Public/Factory.h>

namespace Torc
{
	namespace RHI
	{
		namespace DX11
		{
			class Factory_DX11 : public RHI::Factory
			{
			public :
				Factory_DX11() = default;

			private:
				SwapChain* CreateSwapChainInternal() override;
				Device* CreateDeviceInternal() override;
			
			};
		}
	}
}
