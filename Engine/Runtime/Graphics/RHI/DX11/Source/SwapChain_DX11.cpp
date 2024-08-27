#include "RHI/DX11/Public/SwapChain_DX11.h"
#include "RHI/DX11/Public/RHITypeConverter.h"

#include "RHI/DX11/Include/base.h"
namespace Torc
{
	namespace RHI
	{
		SwapChain* SwapChain::Create()
		{
			return new DX11::SwapChain_DX11();
		}

		namespace DX11
		{
			Result SwapChain_DX11::ResizeBuffersInternal(uint32 width, uint32 height, Format newFormat, uint32 swapChainFlags)
			{
				return Result();
			}

			Result SwapChain_DX11::PresentInternal()
			{
				if (FAILED(m_swapChain->Present(0, 0)))
				{
					return Result::Failure;
				}
				return Result::Success;
			}

			Result SwapChain_DX11::InitInternal(const SwapChainDescription& description, void* wnd, bool isMultiSampled)
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

				//HRESULT hr = D3D11CreateDeviceAndSwapChain(
				//	nullptr,
				//	D3D_DRIVER_TYPE_HARDWARE,
				//	nullptr,
				//	0,
				//	nullptr,
				//	0,
				//	D3D11_SDK_VERSION,
				//	&swapChainDesc,
				//	m_swapChain.GetAddressOf(),
				//	m_device.GetAddressOf(),
				//	nullptr,
				//	m_context.GetAddressOf());

				//if (FAILED(hr))
				//{
				//	//TE_Error()
				//	return Result::Failure;
				//}
				return Result::Success;
			}
		}
	}
}
