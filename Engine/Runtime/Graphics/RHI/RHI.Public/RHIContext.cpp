#include "RHI/RHI.Public/RHIContext.h"

namespace Torc
{
	namespace RHI
	{
		void RHIContext::SetSwapChain(SwapChain* swapChain)
		{
			m_swapChain = swapChain;
		}

		SwapChain* RHIContext::GetSwapChain() const
		{
			return m_swapChain;
		}

		void RHIContext::SetDevice(Device* device)
		{
			m_device = device;
		}

		Device* RHIContext::GetDevice() const
		{
			return m_device;
		}

		void RHIContext::SetDeviceContext(DeviceContext* deviceContext)
		{
			m_deviceContext = deviceContext;
		}

		DeviceContext* RHIContext::GetDeviceContext() const
		{
			return m_deviceContext;
		}
	}
}
