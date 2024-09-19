#pragma once
#include "RHI/RHI.Public/Object.h"
#include "RHI/RHI.Internal/Descriptor.h"

namespace Torc
{
	namespace RHI
	{
		class Resource;
		class ImageView;
		class PSO;
		struct ImageDescription;

		class Device : public Object
		{
		public:
			void CreateImageView(Resource* pResource, const ImageDescription* pDesc, CPUDescriptorHandle destDescriptor);
			EResult CreateGraphicsPipelineState(const PSO* pDesc, void** ppPipelineState);
			void CreateRenderTargetView(Resource* pResource, const ImageView* pDesc, CPUDescriptorHandle destDescriptor);
		private:
			virtual void CreateImageViewInternal(Resource* pResource, const ImageDescription* pDesc, CPUDescriptorHandle destDescriptor) = 0;
			virtual EResult CreateGraphicsPipelineStateInternal(const PSO* pDesc, void** ppPipelineState) = 0;
			virtual void CreateRenderTargetViewInternal(Resource* pResource, const ImageView* pDesc, CPUDescriptorHandle destDescriptor) = 0;
		};
	}
}
