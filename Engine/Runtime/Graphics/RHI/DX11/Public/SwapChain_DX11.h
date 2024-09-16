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
				EResult ResizeBuffersInternal(uint32 width,
											 uint32 height,
											 EResourceFormat newFormat,
											 uint32 swapChainFlags) override;
				EResult PresentInternal() override;
				EResult InitInternal(const SwapChainDescription& description, void* wnd, bool isMultiSampled) override;
				void GetBufferInternal(uint32_t bufferIdx, Image** pImages) override;
			private:
				IDXGISwapChain* m_swapChain;
			};
		}
	}
}
