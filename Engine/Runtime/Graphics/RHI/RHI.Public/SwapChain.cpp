#include "SwapChain.h"
#include <RHI/RHI.Public/Factory.h>
#include <Core/Environment/Environment.h>


namespace Torc
{
	namespace RHI
	{
		SwapChain* SwapChain::Create()
		{
			return Torc::Interface<Factory>::Get()->CreateSwapChain();
		}

		EResult SwapChain::Init(const SwapChainDescription& description, void* wnd, bool isMultiSampled)
		{
			m_description = description;
			m_isMultiSampled = isMultiSampled;

			return InitInternal(m_description, wnd, m_isMultiSampled);
		}
		
		int SwapChain::GetNumBuffers() const
		{
			return m_description.m_numBuffers;
		}
		
		EResult SwapChain::ResizeBuffers(uint32 newWidth, uint32 newHeight, EResourceFormat newFormat, uint32 swapChainFlags)
		{
			return ResizeBuffersInternal(newWidth, newHeight, newFormat, swapChainFlags);
		}
		
		EResult SwapChain::Present()
		{
			return PresentInternal();
		}

		void SwapChain::GetBuffer(uint32_t bufferIdx, Image** pImages)
		{
			GetBufferInternal(bufferIdx, pImages);
		}
	}
}
