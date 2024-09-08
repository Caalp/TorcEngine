#pragma once
#include <RHI/RHI.Public/SwapChain.h>

struct IDXGISwapChain;

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
				IDXGISwapChain* m_swapChain;
			};
		}
	}
}
