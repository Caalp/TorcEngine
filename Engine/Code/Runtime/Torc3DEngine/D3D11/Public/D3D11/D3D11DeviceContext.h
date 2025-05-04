#pragma once
#include "D3D11Base.h"
#include <RHI/DeviceContext.h>

namespace Torc
{
	namespace RHI
	{
		namespace D3D11
		{
			class D3D11DeviceContext : public RHI::DeviceContext
			{
			public:
				D3D11DeviceContext(ID3D11DeviceContext* deviceContext);
				ID3D11DeviceContext* GetNativeObject() const;

			private:

				void ClearDepthStencilViewInternal(
					CPUDescriptorHandle handle,
					EClearFlags clearFlags,
					float depth,
					uint8_t stencil,
					uint32_t numRects = 0,
					const Rect* pRects = nullptr
				) override;

				void ClearRenderTargetViewInternal(
					CPUDescriptorHandle renderTargetView,
					const float colorRGBA[4],
					uint32_t numRects,
					const Rect* pRects
				) override;
			private:
				ID3D11DeviceContext* m_deviceContext;
			};
		}
	}
}
