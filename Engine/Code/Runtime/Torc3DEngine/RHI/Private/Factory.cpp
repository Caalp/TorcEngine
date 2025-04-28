#include "Factory.h"
#include "RHI/RHI.Public/SwapChain.h"

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
