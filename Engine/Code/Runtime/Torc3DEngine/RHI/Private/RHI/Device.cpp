#include "RHI/Device.h"

namespace Torc
{
	namespace RHI
	{
		void Device::CreateImageView(Resource* pResource, const ImageDescription* pDesc, CPUDescriptorHandle destDescriptor)
		{
			CreateImageViewInternal(pResource, pDesc, destDescriptor);
		}

		EResult Device::CreateGraphicsPipelineState(const PSO* pDesc, void** ppPipelineState)
		{
			return CreateGraphicsPipelineStateInternal(pDesc, ppPipelineState);
		}

		void Device::CreateRenderTargetView(Resource* pResource, const ImageView* pDesc, CPUDescriptorHandle destDescriptor)
		{
			CreateRenderTargetViewInternal(pResource, pDesc, destDescriptor);
		}
	}
}
