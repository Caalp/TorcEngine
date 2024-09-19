#pragma once
#include <RHI/RHI.Public/Device.h>

struct ID3D11Device;

namespace Torc
{
	namespace RHI
	{
		namespace DX11
		{
			class Device_DX11 : public RHI::Device
			{
				friend class SwapChain_DX11;
			public:
				Device_DX11() = default;
				ID3D11Device* GetNativeObject() const;		

			private:
				void CreateImageViewInternal(Resource* pResource, const ImageDescription* pDesc, CPUDescriptorHandle destDescriptor) override;
				EResult CreateGraphicsPipelineStateInternal(const PSO* pDesc, void** ppPipelineState) override;
				void CreateRenderTargetViewInternal(Resource* pResource, const ImageView* pDesc, CPUDescriptorHandle destDescriptor) override;

			private:
				ID3D11Device* m_device;
			};
		}
	}
}
