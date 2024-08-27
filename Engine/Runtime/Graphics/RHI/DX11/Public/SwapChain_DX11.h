#pragma once
#include "RHI/DX11/Include/base.h"
#include <RHI/RHI.Public/SwapChain.h>

namespace Torc
{
	namespace RHI
	{
		namespace DX11
		{
			class SwapChain_DX11 : public SwapChain
			{
			public :
				SwapChain_DX11() = default;

			private:
				Result ResizeBuffersInternal(uint32 width,
											 uint32 height,
											 Format newFormat,
											 uint32 swapChainFlags) override;
				Result PresentInternal() override;
				Result InitInternal(const SwapChainDescription& description, void* wnd, bool isMultiSampled) override;
			private:
				Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
			};
		}
	}
}
