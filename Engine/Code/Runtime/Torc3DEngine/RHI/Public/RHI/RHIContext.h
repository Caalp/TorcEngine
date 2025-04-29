#pragma once

namespace Torc
{
	namespace RHI
	{
		class SwapChain;
		class Device;
		class DeviceContext;

		class RHIContext
		{
		public:
			void SetSwapChain(SwapChain* swapChain);
			SwapChain* GetSwapChain() const;

			void SetDevice(Device* device);
			Device* GetDevice() const;

			void SetDeviceContext(DeviceContext* deviceContext);
			DeviceContext* GetDeviceContext() const;

		private:
			SwapChain* m_swapChain;
			Device* m_device;
			DeviceContext* m_deviceContext;
		};
	}
}
