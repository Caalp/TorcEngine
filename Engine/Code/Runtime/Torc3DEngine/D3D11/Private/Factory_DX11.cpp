#include "RHI/DX11/Public/Factory_DX11.h"
#include "RHI/DX11/Public/Device_DX11.h"
#include "RHI/DX11/Public/SwapChain_DX11.h"

namespace Torc
{
	namespace RHI
	{
		namespace DX11
		{
			SwapChain* Factory_DX11::CreateSwapChainInternal()
			{
				return new SwapChain_DX11();
			}

			Device* Factory_DX11::CreateDeviceInternal()
			{
				return new Device_DX11();
			}
		}
	}
}
