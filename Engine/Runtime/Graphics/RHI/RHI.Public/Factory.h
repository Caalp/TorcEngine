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
			SwapChain* CreateSwapChain();
			Device* CreateDevice() { return nullptr; }

		private:

		};
	}
}
