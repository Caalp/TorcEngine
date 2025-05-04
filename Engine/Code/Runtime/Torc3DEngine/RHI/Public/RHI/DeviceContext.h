#pragma once
#include "RHIObject.h"
#include "RHIEnumTypes.h"
#include "Descriptor.h"

namespace Torc
{
	namespace RHI
	{
		class Rect;

		class DeviceContext : public Object
		{
		public:

			void ClearDepthStencilView(
				CPUDescriptorHandle handle,
				EClearFlags clearFlags,
				float depth,
				uint8_t stencil,
				uint32_t numRects = 0,
				const Rect* pRects = nullptr
			);

			void ClearRenderTargetView(
				CPUDescriptorHandle renderTargetView,
				const float colorRGBA[4],
				uint32_t numRects,
				const Rect* pRects
			);

		private:

			virtual void ClearDepthStencilViewInternal(
				CPUDescriptorHandle handle,
				EClearFlags clearFlags,
				float depth,
				uint8_t stencil,
				uint32_t numRects = 0,
				const Rect* pRects = nullptr
			) = 0;

			virtual void ClearRenderTargetViewInternal(
				CPUDescriptorHandle renderTargetView,
				const float colorRGBA[4],
				uint32_t numRects,
				const Rect* pRects
			) = 0;
		};
	}
}
