#pragma once
#include "RHI/RHI.Public/Object.h"
#include "RHI/RHI.Public/RHITypes.h"
namespace Torc
{
	namespace RHI
	{
		class Device : public Object
		{
		public:
			void CreateImageView(Resource* pResource, const ImageDescription* pDesc, CPUDescriptorHandle destDescriptor);
			EResult CreateGraphicsPipelineState(const PSO* pDesc, void** ppPipelineState);
		private:

		};
	}
}
