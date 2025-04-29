#pragma once
#include <RHI/Device.h>

struct ID3D11Device;

namespace Torc
{
	namespace RHI
	{
		namespace D3D11
		{
			class D3D11Device : public RHI::Device
			{
				friend class D3D11SwapChain;
			public:
				D3D11Device() = default;
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
