#include "D3D11Factory.h"
#include "D3D11Device.h"
#include "D3D11SwapChain.h"

namespace Torc
{
	namespace RHI
	{
		namespace D3D11
		{
			SwapChain* D3D11Factory::CreateSwapChainInternal()
			{
				return new D3D11SwapChain();
			}

			Device* D3D11Factory::CreateDeviceInternal()
			{
				return new D3D11Device();
			}
		}
	}
}
