#pragma once
#include "Pageable.h"
#include <RHI/RHICommon.h>
#include <RHI/RHITypeDesc.h>

namespace Torc
{
	namespace RHI
	{
		class Resource : public Pageable
		{
			friend class Device;
		public:

			virtual EResult Map(
				uint32_t Subresource,
				const Range* pReadRange,
				void** ppData) = 0;

			virtual void Unmap(
				uint32_t Subresource,
				const Range* pWrittenRange) = 0;

			virtual ResourceDesc GetDesc(void) = 0;

			virtual GPUVirtualAddress GetGPUVirtualAddress(void) = 0;

			virtual EResult WriteToSubresource(
				uint32_t DstSubresource,
				const Box* pDstBox,
				const void* pSrcData,
				uint32_t SrcRowPitch,
				uint32_t SrcDepthPitch) = 0;

			virtual EResult ReadFromSubresource(
				void* pDstData,
				uint32_t DstRowPitch,
				uint32_t DstDepthPitch,
				uint32_t SrcSubresource,
				const Box* pSrcBox) = 0;

			/*virtual EResult GetHeapProperties(
				D3D12_HEAP_PROPERTIES* pHeapProperties,
				D3D12_HEAP_FLAGS* pHeapFlags) = 0;*/

		private:
			virtual void SetResource(void* pResource) = 0;

			Device* m_device;
		};
	}
}
