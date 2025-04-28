#include "RHI/DX11/Public/Device_DX11.h"
#include "RHI/DX11/Include/base.h"
#include "RHI/DX11/Public/Image_DX11.h"

namespace Torc
{
	namespace RHI
	{
		namespace DX11
		{
			ID3D11Device* Device_DX11::GetNativeObject() const
			{
				return m_device;
			}

			void Device_DX11::CreateImageViewInternal(Resource* pResource, const ImageDescription* pDesc, CPUDescriptorHandle destDescriptor)
			{
			}

			EResult Device_DX11::CreateGraphicsPipelineStateInternal(const PSO* pDesc, void** ppPipelineState)
			{
				return EResult();
			}

			void Device_DX11::CreateRenderTargetViewInternal(Resource* pResource, const ImageView* pDesc, CPUDescriptorHandle destDescriptor)
			{
				ID3D11Texture2D* tex = ((Image2D_DX11*)pResource)->GetResource();
				D3D11_RENDER_TARGET_VIEW_DESC viewDesc;
				ID3D11RenderTargetView* rtv;
				if (FAILED(m_device->CreateRenderTargetView((ID3D11Resource*)tex, &viewDesc, &rtv)))
				{

				}
			}
		}
	}
}
