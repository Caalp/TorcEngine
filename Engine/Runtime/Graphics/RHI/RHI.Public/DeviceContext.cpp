#include "RHI/RHI.Public/DeviceContext.h"

namespace Torc
{
	namespace RHI
	{
		void DeviceContext::ClearDepthStencilView(
			CPUDescriptorHandle handle,
			EClearFlags clearFlags,
			float depth,
			uint8_t stencil,
			uint32_t numRects,
			const Rect* pRects
		)
		{
			ClearDepthStencilViewInternal(handle, clearFlags, depth, stencil, numRects, pRects);
		}

		void DeviceContext::ClearRenderTargetView(
			CPUDescriptorHandle renderTargetView,
			const float colorRGBA[4],
			uint32_t numRects,
			const Rect* pRects
		)
		{
			ClearRenderTargetViewInternal(renderTargetView, colorRGBA, numRects, pRects);
		}
	}
}
