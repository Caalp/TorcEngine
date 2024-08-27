#pragma once
#include "RHI/Include/base.h"
#include "RHI/RHI.Public/RHITypes.h"
#include "RHI/RHI.Public/Object.h"

namespace Torc
{
	namespace RHI
	{
		enum class Result
		{
			Success,
			Failure
		};

		struct SwapChainDescription
		{
			uint32_t	m_width; // zero width means to use default width of the window 
			uint32_t	m_height; // zero height means to use default height of the window
			uint32_t	m_refreshRateNumerator;
			uint32_t	m_refreshRateDenominator;
			uint32_t	m_numBuffers;
			Format		m_format;
		};

		class SwapChain : public Object
		{
		public:
			static SwapChain* Create();
			Result Init(const SwapChainDescription& description, void* wnd, bool isMultiSampled = false);
			int GetNumBuffers() const;
			Result ResizeBuffers(uint32 width,
								 uint32 height,
								 Format	newFormat,
								 uint32 swapChainFlags);
			Result Present();
		private:
			virtual Result ResizeBuffersInternal(uint32 width,
												 uint32 height,
												 Format newFormat,
												 uint32 swapChainFlags) = 0;
			virtual Result PresentInternal() = 0;
			virtual Result InitInternal(const SwapChainDescription& description, void* wnd, bool isMultiSampled) = 0;

			SwapChainDescription m_description;
			bool m_isMultiSampled;
		};
	}
}
