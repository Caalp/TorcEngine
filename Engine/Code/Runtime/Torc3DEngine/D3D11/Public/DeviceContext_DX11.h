#pragma once
#include "RHI/DX11/Include/base.h"
#include <RHI/RHI.Public/DeviceContext.h>

namespace Torc
{
	namespace RHI
	{
		namespace DX11
		{
			class DeviceContext_DX11 : public RHI::DeviceContext
			{
			public:
				DeviceContext_DX11(ID3D11DeviceContext* deviceContext);
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
