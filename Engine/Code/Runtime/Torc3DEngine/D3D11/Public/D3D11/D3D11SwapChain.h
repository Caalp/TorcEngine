#pragma once
#include <RHI/SwapChain.h>

struct IDXGISwapChain;

namespace Torc
{
	namespace RHI
	{
		namespace D3D11
		{
			class D3D11SwapChain : public RHI::SwapChain
			{
			public :
				D3D11SwapChain() = default;

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
