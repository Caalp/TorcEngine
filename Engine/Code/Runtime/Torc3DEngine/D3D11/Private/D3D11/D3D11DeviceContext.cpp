#include "D3D11/D3D11DeviceContext.h"

namespace Torc
{
	namespace RHI
	{
		namespace D3D11
		{
			D3D11DeviceContext::D3D11DeviceContext(ID3D11DeviceContext* deviceContext)
				: m_deviceContext(deviceContext)
			{
			}

			ID3D11DeviceContext* D3D11DeviceContext::GetNativeObject() const
			{
				return m_deviceContext;
			}

			void D3D11DeviceContext::ClearDepthStencilViewInternal(CPUDescriptorHandle handle, EClearFlags clearFlags, float depth, uint8_t stencil, uint32_t numRects, const Rect* pRects)
			{

			}

			void D3D11DeviceContext::ClearRenderTargetViewInternal(CPUDescriptorHandle renderTargetView, const float colorRGBA[4], uint32_t numRects, const Rect* pRects)
			{

			}
		}
	}
}
