#include "D3D11Common.h"
#include "GfxBackendD3D11.h"
#include "TorcGfx/HandleRegistry.h"

#include <assert.h> // replace with torc header


using namespace typeConverter;

extern "C"
{
	bool TORC_API InitializeGfxBackendPlugin(void** gfxBackend)
	{
		*gfxBackend = new GfxBackendD3D11;
		return true;
	}

	bool TORC_API ReleaseGfxBackendPlugin(void** gfxBackend)
	{
		delete *gfxBackend;
		return false;
	}
}

namespace
{
	void CreateTexture(const gfx::TextureDesc& texDesc, ID3D11Device* device, ID3D11Texture2D** tex)
	{
		D3D11_TEXTURE2D_DESC descDepth;
		descDepth.Width = texDesc.width;
		descDepth.Height = texDesc.height;
		descDepth.MipLevels = texDesc.mipLevels;
		descDepth.ArraySize = texDesc.arraySize;
		descDepth.Format = (DXGI_FORMAT)ConvertTorcGfxType(texDesc.format);
		descDepth.SampleDesc.Count = texDesc.sampleDesc.count;
		descDepth.SampleDesc.Quality = texDesc.sampleDesc.quality;
		descDepth.Usage = (D3D11_USAGE)ConvertTorcGfxType(texDesc.usage);
		descDepth.BindFlags = texDesc.bindFlags;
		descDepth.CPUAccessFlags = texDesc.cpuAccessFlags;
		descDepth.MiscFlags = texDesc.miscFlags;

		device->CreateTexture2D(&descDepth, nullptr, tex);
	}
}


bool GfxBackendD3D11::InitializeGfxBackend(gfx::GfxBackendParams& gfxParams)
{
	m_gfxInitParam = gfxParams;
	// we call create function for corresponding backend API
	// Create swap chain description
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferDesc.Width = gfxParams.SwapChainDesc.width;
	swapChainDesc.BufferDesc.Height = gfxParams.SwapChainDesc.height;
	swapChainDesc.BufferDesc.Format = (DXGI_FORMAT)typeConverter::ConvertTorcGfxType(gfxParams.SwapChainDesc.format);
	swapChainDesc.BufferDesc.RefreshRate.Numerator = gfxParams.SwapChainDesc.refreshRateNumerator;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = gfxParams.SwapChainDesc.refreshRateDenominator;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.SampleDesc.Count = gfxParams.SwapChainDesc.samplingParams.count;
	swapChainDesc.SampleDesc.Quality = gfxParams.SwapChainDesc.samplingParams.quality;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = (HWND)gfxParams.targetWindow;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0u,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		m_swapChain.GetAddressOf(),
		m_device.GetAddressOf(),
		nullptr,
		m_context.GetAddressOf());

	if (hr != S_OK)
	{
		// log
		return false;
	}

	return true;
}

bool GfxBackendD3D11::ReleaseGfxBackend()
{
	return true;
}

void GfxBackendD3D11::CreateBlendState(BlendStateHandle handle, const gfx::BlendDesc& params)
{
	const uint32_t renderTargetIndex = 0u;
	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable = params.alphaToCoverageEnable;
	desc.IndependentBlendEnable = params.independentBlendEnable;
	desc.RenderTarget[renderTargetIndex].BlendEnable = params.blendEnable;
	desc.RenderTarget[renderTargetIndex].SrcBlend = (D3D11_BLEND)ConvertTorcGfxType(params.srcBlend);
	desc.RenderTarget[renderTargetIndex].DestBlend = (D3D11_BLEND)ConvertTorcGfxType(params.destBlend);
	desc.RenderTarget[renderTargetIndex].BlendOp = (D3D11_BLEND_OP)ConvertTorcGfxType(params.blendOp);
	desc.RenderTarget[renderTargetIndex].SrcBlendAlpha = (D3D11_BLEND)ConvertTorcGfxType(params.srcBlendAlpha);
	desc.RenderTarget[renderTargetIndex].DestBlendAlpha = (D3D11_BLEND)ConvertTorcGfxType(params.destBlendAlpha);
	desc.RenderTarget[renderTargetIndex].BlendOpAlpha = (D3D11_BLEND_OP)ConvertTorcGfxType(params.blendOpAlpha);
	desc.RenderTarget[renderTargetIndex].RenderTargetWriteMask = (uint8_t)ConvertTorcGfxType(params.rtWriteMask);


	HRESULT hr = m_device->CreateBlendState(&desc, &m_blendStates[handle.idx]);

	if (hr == S_OK)
	{
	}
}

void GfxBackendD3D11::CreateRasterizerState(RasterizerStateHandle handle, const gfx::RasterizerDesc& params)
{
	D3D11_RASTERIZER_DESC desc;
	desc.FillMode = (D3D11_FILL_MODE)ConvertTorcGfxType(params.fillMode);
	desc.CullMode = (D3D11_CULL_MODE)ConvertTorcGfxType(params.cullMode);
	desc.FrontCounterClockwise = params.frontCCW;
	desc.DepthBias = params.depthBias;
	desc.DepthBiasClamp = params.depthBiasClamp;
	desc.SlopeScaledDepthBias = params.slopeScaledDepthBias;
	desc.DepthClipEnable = params.depthClipEnable;
	desc.ScissorEnable = params.scissorEnable;
	desc.MultisampleEnable = params.multisampleEnable;
	desc.AntialiasedLineEnable = params.antialiasedLineEnable;

	HRESULT hr = m_device->CreateRasterizerState(&desc, &m_rasterizerStates[handle.idx]);

	if (hr == S_OK)
	{
	}
}

void GfxBackendD3D11::CreateSamplerState(SamplerStateHandle handle, const gfx::SamplerDesc& params)
{
	D3D11_SAMPLER_DESC desc;
	desc.Filter = ConvertTorcGfxType(params.filter);
	desc.AddressU = ConvertTorcGfxType(params.addressU);
	desc.AddressV = ConvertTorcGfxType(params.addressV);
	desc.AddressW = ConvertTorcGfxType(params.addressW);
	desc.MipLODBias = params.mipLODBias;
	desc.MaxAnisotropy = params.maxAnisotropy;
	desc.ComparisonFunc = (D3D11_COMPARISON_FUNC)ConvertTorcGfxType(params.comparisonFunc);
	desc.BorderColor[0] = params.borderColor[0];
	desc.BorderColor[1] = params.borderColor[1];
	desc.BorderColor[2] = params.borderColor[2];
	desc.BorderColor[3] = params.borderColor[3];
	desc.MinLOD = params.minLOD;
	desc.MaxLOD = params.maxLOD;

	HRESULT hr = m_device->CreateSamplerState(&desc, &m_samplerStates[handle.idx]);

	if (hr == S_OK)
	{
	}
}

void GfxBackendD3D11::CreateDepthStencilState(DepthStencilStateHandle handle, const gfx::TextureDesc texDesc, const gfx::DepthStencilDesc& depthDesc)
{
	ID3D11Texture2D* texDepthStencil = nullptr;
	CreateTexture(texDesc, m_device.Get(), &texDepthStencil);
	if (texDepthStencil != nullptr)
	{
		D3D11_DEPTH_STENCIL_DESC dsDesc;

		// Depth test parameters
		dsDesc.DepthEnable = depthDesc.depthEnable;
		dsDesc.DepthWriteMask = ConvertTorcGfxType(depthDesc.depthWrite);
		dsDesc.DepthFunc = ConvertTorcGfxType(depthDesc.depthFunc);

		// Stencil test parameters
		dsDesc.StencilEnable = depthDesc.stencilEnable;
		dsDesc.StencilReadMask = depthDesc.stencilReadMask;
		dsDesc.StencilWriteMask = depthDesc.stencilWriteMask;

		// Stencil operations if pixel is front-facing
		dsDesc.FrontFace.StencilFailOp = ConvertTorcGfxType(depthDesc.frontFace.stencilFailOp);
		dsDesc.FrontFace.StencilDepthFailOp = ConvertTorcGfxType(depthDesc.frontFace.stencilDepthFailOp);
		dsDesc.FrontFace.StencilPassOp = ConvertTorcGfxType(depthDesc.frontFace.stencilPassOp);
		dsDesc.FrontFace.StencilFunc = ConvertTorcGfxType(depthDesc.frontFace.stencilFunc);

		// Stencil operations if pixel is back-facing
		dsDesc.BackFace.StencilFailOp = ConvertTorcGfxType(depthDesc.backFace.stencilFailOp);
		dsDesc.BackFace.StencilDepthFailOp = ConvertTorcGfxType(depthDesc.backFace.stencilDepthFailOp);
		dsDesc.BackFace.StencilPassOp = ConvertTorcGfxType(depthDesc.backFace.stencilPassOp);
		dsDesc.BackFace.StencilFunc = ConvertTorcGfxType(depthDesc.backFace.stencilFunc);

		// Create depth stencil state
		m_device->CreateDepthStencilState(&dsDesc, &m_depthStencilStates[handle.idx]);

		//D3D11_DEPTH_STENCIL_VIEW_DESC dsViewDesc;
		//dsViewDesc.

		m_device->CreateDepthStencilView(texDepthStencil, nullptr, &m_depthStencilStateViews[handle.idx]);
	}
	texDepthStencil->Release();
}

void GfxBackendD3D11::CreateRenderTarget(RenderTargetHandle handle, const gfx::RenderTargetDesc& params)
{
}

void GfxBackendD3D11::CreateRenderTarget(RenderTargetHandle handle, const gfx::TextureDesc& texDesc)
{
	// create a texture with bind-flag render_target_view
	ID3D11Texture2D* rtvTexture;
	CreateTexture(texDesc, m_device.Get(), &rtvTexture);
	
	m_device->CreateRenderTargetView(rtvTexture, nullptr, &m_renderTargetViews[handle.idx]);
	
	rtvTexture->Release();
}

void GfxBackendD3D11::CreateShaderResourceView()
{
}

void GfxBackendD3D11::SetBlendState(BlendStateHandle handle)
{
	float b[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_context->OMSetBlendState(m_blendStates[handle.idx], b, ~0);
}

void GfxBackendD3D11::SetBlendState(BlendStateHandle handle, const float blendFactor[4], uint32_t blendMask)
{
	m_context->OMSetBlendState(m_blendStates[handle.idx], blendFactor, blendMask);
}

void GfxBackendD3D11::SetRasterizerState(RasterizerStateHandle handle)
{
	m_context->RSSetState(m_rasterizerStates[handle.idx]);
}

void GfxBackendD3D11::SetSamplerState(SamplerStateHandle handle)
{
	//m_context->VSGetSamplers()
}

void GfxBackendD3D11::SetDepthStencilState(DepthStencilStateHandle handle, uint32_t stencilRef)
{
	m_context->OMSetDepthStencilState(m_depthStencilStates[handle.idx], stencilRef);
}

void GfxBackendD3D11::SetRenderTarget(RenderTargetHandle handle)
{
}

void GfxBackendD3D11::SetRenderTarget(RenderTargetHandle handle, DepthStencilStateHandle depthStencilHandle)
{
	m_context->OMSetRenderTargets(1u, &m_renderTargetViews[handle.idx], m_depthStencilStateViews[depthStencilHandle.idx]);
}

void GfxBackendD3D11::CreateAndSetViewPort(gfx::ViewPortDesc viewPortDesc)
{
	D3D11_VIEWPORT viewPort;
	viewPort.TopLeftX = viewPortDesc.topLeftX;
	viewPort.TopLeftY = viewPortDesc.topLeftY;
	viewPort.Width = viewPortDesc.width;
	viewPort.Height = viewPortDesc.height;
	viewPort.MinDepth = viewPortDesc.minDepth;
	viewPort.MaxDepth = viewPortDesc.maxDepth;

	m_context->RSSetViewports(1u, &viewPort);
}

void GfxBackendD3D11::CreateAndSetViewPort(uint32_t viewPortCount, gfx::ViewPortDesc* viewPortDesc)
{
	// TODO: replace new and delete with engine implementation of new and delete
	D3D11_VIEWPORT* viewPorts = new D3D11_VIEWPORT[viewPortCount];
	for (uint32_t i = 0; i < viewPortCount; i++)
	{
		viewPorts[i].TopLeftX = viewPortDesc[i].topLeftX;
		viewPorts[i].TopLeftY = viewPortDesc[i].topLeftY;
		viewPorts[i].Width = viewPortDesc[i].width;
		viewPorts[i].Height = viewPortDesc[i].height;
		viewPorts[i].MinDepth = viewPortDesc[i].minDepth;
		viewPorts[i].MaxDepth = viewPortDesc[i].maxDepth;
	}

	m_context->RSSetViewports(viewPortCount, viewPorts);

	delete[] viewPorts;
}