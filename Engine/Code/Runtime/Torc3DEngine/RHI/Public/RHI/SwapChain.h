#pragma once
#include "Core/Base.h"
#include "RHIEnumTypes.h"
#include "RHIObject.h"

namespace Torc
{
	namespace RHI
	{
		class Image;

		struct SwapChainDescription
		{
			uint32_t			m_width; // zero width means to use default width of the window 
			uint32_t			m_height; // zero height means to use default height of the window
			uint32_t			m_refreshRateNumerator;
			uint32_t			m_refreshRateDenominator;
			uint32_t			m_numBuffers;
			EResourceFormat		m_format;
		};

		class SwapChain : public Object
		{
		public:
			static SwapChain* Create();
			EResult Init(const SwapChainDescription& description, void* wnd, bool isMultiSampled = false);
			int GetNumBuffers() const;
			EResult ResizeBuffers(uint32 width,
								 uint32 height,
								 EResourceFormat newFormat,
								 uint32 swapChainFlags);
			EResult Present();
			void GetBuffer(uint32_t bufferIdx, Image** pImages);
		private:
			virtual EResult ResizeBuffersInternal(uint32 width,
												 uint32 height,
												  EResourceFormat newFormat,
												 uint32 swapChainFlags) = 0;
			virtual EResult PresentInternal() = 0;
			virtual EResult InitInternal(const SwapChainDescription& description, void* wnd, bool isMultiSampled) = 0;
			virtual void GetBufferInternal(uint32_t bufferIdx, Image** pImages) = 0;

			SwapChainDescription m_description;
			bool m_isMultiSampled;
		};
	}
}
