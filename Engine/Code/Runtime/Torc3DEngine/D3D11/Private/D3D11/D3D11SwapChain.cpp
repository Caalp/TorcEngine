#include "D3D11/D3D11SwapChain.h"
#include "D3D11/D3D11TypeConverter.h"

#include "D3D11/D3D11Base.h"

#include <Core/Environment/Environment.h>
#include <Core/Memory/Memory_defs.h>
#include <RHI/RHIContext.h>


#include "D3D11/D3D11Device.h"
#include "D3D11/D3D11DeviceContext.h"
#include "D3D11/D3D11Image.h"

namespace Torc
{
	namespace RHI
	{
		namespace D3D11
		{
			EResult D3D11SwapChain::ResizeBuffersInternal(uint32 width, uint32 height, EResourceFormat newFormat, uint32 swapChainFlags)
			{
				return EResult();
			}

			EResult D3D11SwapChain::PresentInternal()
			{
				if (FAILED(m_swapChain->Present(0, 0)))
				{
					return EResult::Failure;
				}
				return EResult::Success;
			}

			EResult D3D11SwapChain::InitInternal(const SwapChainDescription& description, void* wnd, bool isMultiSampled)
			{
				DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
				swapChainDesc.BufferDesc.Width = description.m_width;
				swapChainDesc.BufferDesc.Height = description.m_height;
				swapChainDesc.BufferDesc.Format = (DXGI_FORMAT)ConvertType(description.m_format);
				swapChainDesc.BufferDesc.RefreshRate.Numerator = description.m_refreshRateNumerator;
				swapChainDesc.BufferDesc.RefreshRate.Denominator = description.m_refreshRateDenominator;
				swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
				swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
				swapChainDesc.SampleDesc.Count = 1;
				swapChainDesc.SampleDesc.Quality = 0;
				swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				swapChainDesc.BufferCount = description.m_numBuffers;
				swapChainDesc.OutputWindow = (HWND)wnd;
				swapChainDesc.Windowed = TRUE;
				swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
				swapChainDesc.Flags = 0;

				RHIContext* rhiContext = Interface<RHIContext>::Get();

				namespace wrl = Microsoft::WRL;

				ID3D11Device* nativeDevice = nullptr;
				ID3D11DeviceContext* nativeContext = nullptr;

				HRESULT hr = D3D11CreateDeviceAndSwapChain(
					nullptr,
					D3D_DRIVER_TYPE_HARDWARE,
					nullptr,
					0,
					nullptr,
					0,
					D3D11_SDK_VERSION,
					&swapChainDesc,
					&m_swapChain,
					&nativeDevice,
					nullptr,
					&nativeContext
					);

				if (FAILED(hr))
				{
					//TE_Error()
					return EResult::Failure;
				}

				D3D11Device* device = torc_new D3D11Device();
				device->m_device = nativeDevice;
				D3D11DeviceContext* deviceContext = torc_new D3D11DeviceContext(nativeContext);

				rhiContext->SetDeviceContext(deviceContext);
				rhiContext->SetDevice(device);

				return EResult::Success;
			}

			void D3D11SwapChain::GetBufferInternal(uint32_t bufferIdx, Image** pImages)
			{
				if (bufferIdx < 0)
				{
					return;
				}

				Image* image = *pImages;
				ResourceDesc desc = image->GetDesc();
				if (desc.m_dimension == EResourceDimension::RESOURCE_DIMENSION_TEXTURE2D)
				{
					void* bufferPtr;
					m_swapChain->GetBuffer(bufferIdx, IID_ID3D11Texture2D, &bufferPtr);
					((D3D11Image2D*)image)->SetResource(bufferPtr);
				}
			}
		}
	}
}
