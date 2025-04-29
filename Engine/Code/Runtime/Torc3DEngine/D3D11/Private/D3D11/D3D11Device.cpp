#include "D3D11Device.h"
#include "D3D11Base.h"
#include "D3D11Image.h"

namespace Torc
{
	namespace RHI
	{
		namespace D3D11
		{
			ID3D11Device* D3D11Device::GetNativeObject() const
			{
				return m_device;
			}

			void D3D11Device::CreateImageViewInternal(Resource* pResource, const ImageDescription* pDesc, CPUDescriptorHandle destDescriptor)
			{
			}

			EResult D3D11Device::CreateGraphicsPipelineStateInternal(const PSO* pDesc, void** ppPipelineState)
			{
				return EResult();
			}

			void D3D11Device::CreateRenderTargetViewInternal(Resource* pResource, const ImageView* pDesc, CPUDescriptorHandle destDescriptor)
			{
				ID3D11Texture2D* tex = ((D3D11Image2D*)pResource)->GetResource();
				D3D11_RENDER_TARGET_VIEW_DESC viewDesc;
				ID3D11RenderTargetView* rtv;
				if (FAILED(m_device->CreateRenderTargetView((ID3D11Resource*)tex, &viewDesc, &rtv)))
				{

				}
			}
		}
	}
}
