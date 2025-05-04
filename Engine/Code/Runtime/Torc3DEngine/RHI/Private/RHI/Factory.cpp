#include "RHI/Factory.h"
#include "RHI/SwapChain.h"

namespace Torc
{
	namespace RHI
	{
		SwapChain* Factory::CreateSwapChain()
		{
			return CreateSwapChainInternal();
		}

		Device* Factory::CreateDevice()
		{
			return CreateDeviceInternal();
		}
	}
}
