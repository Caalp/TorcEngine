#include "RHI/DX11/Public/DeviceContext_DX11.h"

namespace Torc
{
	namespace RHI
	{
		namespace DX11
		{
			DeviceContext_DX11::DeviceContext_DX11(ID3D11DeviceContext* deviceContext)
				: m_deviceContext(deviceContext)
			{
			}

			ID3D11DeviceContext* DeviceContext_DX11::GetNativeObject() const
			{
				return m_deviceContext;
			}

			void DeviceContext_DX11::ClearDepthStencilViewInternal(CPUDescriptorHandle handle, EClearFlags clearFlags, float depth, uint8_t stencil, uint32_t numRects, const Rect* pRects)
			{

			}

			void DeviceContext_DX11::ClearRenderTargetViewInternal(CPUDescriptorHandle renderTargetView, const float colorRGBA[4], uint32_t numRects, const Rect* pRects)
			{

			}
		}
	}
}
