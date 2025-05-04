#pragma once
#include <Core/Component/Component.h>

namespace Torc
{
	namespace RHI
	{

		class SwapChain;
		class Device;

		class Factory
		{
		public:
			virtual ~Factory() = default;

			SwapChain* CreateSwapChain();
			Device* CreateDevice();
		private:
			virtual SwapChain* CreateSwapChainInternal() = 0;
			virtual Device* CreateDeviceInternal() = 0;
		};
	}
}
