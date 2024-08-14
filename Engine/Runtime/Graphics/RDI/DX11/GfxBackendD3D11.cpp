#include "D3D11Common.h"
#include "GfxBackendD3D11.h"

#include "Core/Platform/Platform.h"

#include "RPI/IGPUResource.h"
#include "RPI/GPUObjects/BlendState.h"
#include "RPI/GPUObjects/RasterizerState.h"
#include "RPI/GPUObjects/SamplerState.h"
#include "RPI/GPUObjects/DepthStencilState.h"
#include "RPI/GPUObjects/RenderTarget.h"
#include "RPI/GPUObjects/PrimitiveTopology.h"
#include "RPI/GPUObjects/Texture.h"
#include "RPI/GPUObjects/Buffer.h"
#include "RPI/GPUObjects/Shader.h"
#include "RPI/GPUObjects/InputLayout.h"
#include "RPI/GPUObjects/DepthStencilBuffer.h"
#include "RDI/RDIShared/HandleRegistry.h"

//#include <DirectXTex/WICTextureLoader/WICTextureLoader11.h>

using namespace typeConverter;

namespace wrl = Microsoft::WRL;

#define RELEASE_COM_OBJ_ARRAY(arrayName, size)\
		for (uint32 i = 0; i < size; i++)\
		{\
			if (arrayName[i])\
				arrayName[i]->Release();\
		}
#define RELEASE_RAW_PTR_ARRAY(arrayName, size)\
		for (uint32 i = 0; i < size; i++)\
		{\
			if (arrayName[i])\
				delete arrayName[i];\
		}

extern "C"
{
	bool TORC_API InitializeGfxBackendPlugin(void** gfxBackend)
	{
		*gfxBackend = new GfxBackendD3D11;
		return true;
	}

	bool TORC_API ReleaseGfxBackendPlugin(void** gfxBackend)
	{
		delete (GfxBackendD3D11*)* gfxBackend;
		return false;
	}
}

static ID3D11Debug* debugDevice;
namespace Utils
{
	std::wstring ConvertToWideChar(const std::string& src)
	{
		std::wstring wstr(src.size() + 1, 0);
		size_t numOfCharsConverted;
		mbstowcs_s(&numOfCharsConverted, wstr.data(), (size_t)(src.size() + 1), src.c_str(), src.size());
		if (numOfCharsConverted > 0)
		{
			wstr.resize(numOfCharsConverted - 1);
			return wstr;
		}
		return {};
	}

	HRESULT CreateTexture(const gfx::TextureDesc& texDesc, ID3D11Device* device, ID3D11Texture2D** tex)
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
		descDepth.BindFlags = ConvertTorcGfxType(texDesc.bindFlags);
		descDepth.CPUAccessFlags = texDesc.cpuAccessFlags;
		descDepth.MiscFlags = texDesc.miscFlags;

		HRESULT hr = (device->CreateTexture2D(&descDepth, nullptr, tex));
		LOG_GFX_INFO("CreateTexture result: %d", hr);
		return hr;
	}

	HRESULT CreateDSSView(const gfx::TextureDesc& desc, ID3D11Device* device, ID3D11DeviceContext* context, ID3D11DepthStencilView** outDSSView)
	{
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = TRUE;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
		wrl::ComPtr<ID3D11DepthStencilState> dss;

		if (!SUCCEEDED(device->CreateDepthStencilState(&dsDesc, dss.GetAddressOf())))
		{
			LOG_GFX_ERROR("Depth State Creation Failed %s, %s", __FUNCTION__, __FILE__);
			return S_FALSE;
		}

		context->OMSetDepthStencilState(dss.Get(), 1u);
		wrl::ComPtr<ID3D11Texture2D> depthTex;
		D3D11_TEXTURE2D_DESC  depthTexDesc;
		ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
		depthTexDesc.Width = desc.width;
		depthTexDesc.Height = desc.height;
		depthTexDesc.MipLevels = 1;
		depthTexDesc.ArraySize = 1;
		depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthTexDesc.SampleDesc.Count = 1;
		depthTexDesc.SampleDesc.Quality = 0;
		depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthTexDesc.CPUAccessFlags = 0;
		depthTexDesc.MiscFlags = 0;

		if (!SUCCEEDED(device->CreateTexture2D(&depthTexDesc, nullptr, depthTex.GetAddressOf())))
		{
			dss->Release();
			LOG_GFX_ERROR("Depth Texture Creation Failed %s, %s", __FUNCTION__, __FILE__);
			return S_FALSE;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC dsv;
		ZeroMemory(&dsv, sizeof(dsv));
		dsv.Format = depthTexDesc.Format;
		dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsv.Texture2D.MipSlice = 0;

		if (!SUCCEEDED(device->CreateDepthStencilView(depthTex.Get(), &dsv, outDSSView)))
		{
			dss->Release();
			depthTex->Release();
			LOG_GFX_ERROR("Depth View Creation Failed %s, %s", __FUNCTION__, __FILE__);
			return S_FALSE;
		}

		return S_OK;
	}
/*
	//requires <dxcapi.h> and <d3d12shader.h>
	void ShaderCompilationTest()
	{
		// Create instances for utils and compilers
		IDxcUtils* utils;
		IDxcCompiler3* compiler;
		::DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&utils));
		::DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&compiler));
		IDxcIncludeHandler* includeHandler;
		utils->CreateDefaultIncludeHandler(&includeHandler);

		std::vector<LPCWSTR> compilationArgs =
		{
			L"-E", // entry point
			L"main",
			L"-T", // target profile
			L"ps_6_0"
			DXC_ARG_PACK_MATRIX_ROW_MAJOR,
			DXC_ARG_WARNINGS_ARE_ERRORS,
			DXC_ARG_ALL_RESOURCES_BOUND,
			DXC_ARG_DEBUG
		};

		// use -D for defines if needed

		Microsoft::WRL::ComPtr<IDxcBlobEncoding> sourceBlob{};
		utils->LoadFile(L"", nullptr, &sourceBlob);

		DxcBuffer buff;
		buff.Ptr = sourceBlob->GetBufferPointer();
		buff.Size = sourceBlob->GetBufferSize();
		buff.Encoding = 0u;

		// shader compilation
		Microsoft::WRL::ComPtr<IDxcOperationResult> compiled{};
		Microsoft::WRL::ComPtr<IDxcResult> compiled3{};

		// this is compile function for IDxcCompiler
		HRESULT hr = compiler->Compile(
			sourceBlob.Get(),
			L"BasicPS.hlsl",
			L"main",
			L"ps_6_0",
			compilationArgs.data(),
			(uint32_t)compilationArgs.size(),
			NULL,
			0,
			includeHandler,
			compiled.GetAddressOf());

		// this is compile function for IDxcCompiler3
		HRESULT hr = compiler->Compile(
			&buff, 
			compilationArgs.data(), 
			compilationArgs.size(), 
			includeHandler, 
			IID_PPV_ARGS(compiled3.GetAddressOf()));

		if (SUCCEEDED(hr))
		{
			compiled->GetStatus(&hr);
		}
		if (!SUCCEEDED(hr))
		{
			if (compiled)
			{
				Microsoft::WRL::ComPtr<IDxcBlobEncoding> errorsBlob;
				hr = compiled->GetErrorBuffer(&errorsBlob);
				if (SUCCEEDED(hr) && errorsBlob)
				{
					wprintf(L"Compilation failed with errors:\n%hs\n",
						(const char*)errorsBlob->GetBufferPointer());
				}
			}
			// else 
		}

		// else read the code
		Microsoft::WRL::ComPtr<IDxcBlob> codeBlob;
		compiled->GetResult(codeBlob.GetAddressOf());
		
		Microsoft::WRL::ComPtr<IDxcBlob> reflectionBlob;
		compiled3->GetOutput(DXC_OUT_REFLECTION, IID_PPV_ARGS(reflectionBlob.GetAddressOf()), NULL);

		DxcBuffer reflectionBuffer;
		reflectionBuffer.Ptr = reflectionBlob->GetBufferPointer();
		reflectionBuffer.Size = reflectionBlob->GetBufferSize();
		reflectionBuffer.Encoding = 0;
		
		Microsoft::WRL::ComPtr<ID3D12ShaderReflection> shaderReflection{};
		utils->CreateReflection(&reflectionBuffer, IID_PPV_ARGS(&shaderReflection));
		D3D12_SHADER_DESC shaderDesc{};
		shaderReflection->GetDesc(&shaderDesc);
	}
*/
}

SystemGlobalEnvironment* gEnv;

bool GfxBackendD3D11::Initialize(SystemGlobalEnvironment& _env, gfx::GfxBackendParams& gfxParams)
{
	gEnv = &_env;
	m_gfxInitParam = gfxParams;
	uint32 flags = 0u;

#ifdef _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	//env = &_env;

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
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;//DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.Flags = 0;//DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		flags,
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

#ifdef _DEBUG
	m_device->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDevice));
#endif

	// get backbuffer
	wrl::ComPtr<ID3D11Texture2D> backBuffer;
	SUCCEEDED(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer));

	uint32_t width = gfxParams.SwapChainDesc.width;
	uint32_t height = gfxParams.SwapChainDesc.height;

	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	rtvDesc.Format = ConvertTorcGfxType(gfxParams.SwapChainDesc.format);
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0u;

	SUCCEEDED(m_device->CreateRenderTargetView(backBuffer.Get(), &rtvDesc, m_mainRTV.GetAddressOf()));

	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	wrl::ComPtr<ID3D11DepthStencilState> dss;

	SUCCEEDED(m_device->CreateDepthStencilState(&dsDesc, dss.GetAddressOf()));
	m_context->OMSetDepthStencilState(dss.Get(), 1u);

	wrl::ComPtr<ID3D11Texture2D> depthTex;
	D3D11_TEXTURE2D_DESC  depthTexDesc;
	ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
	depthTexDesc.Width = width;
	depthTexDesc.Height = height;
	depthTexDesc.MipLevels = 1;
	depthTexDesc.ArraySize = 1;
	depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthTexDesc.SampleDesc.Count = 1;
	depthTexDesc.SampleDesc.Quality = 0;
	depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTexDesc.CPUAccessFlags = 0;
	depthTexDesc.MiscFlags = 0;
	SUCCEEDED(m_device->CreateTexture2D(&depthTexDesc, nullptr, depthTex.GetAddressOf()));

	D3D11_DEPTH_STENCIL_VIEW_DESC dsv;
	ZeroMemory(&dsv, sizeof(dsv));
	dsv.Format = depthTexDesc.Format;
	dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsv.Texture2D.MipSlice = 0;

	SUCCEEDED(m_device->CreateDepthStencilView(depthTex.Get(), &dsv, m_dsView.GetAddressOf()));

	m_context->OMSetRenderTargets(1u, m_mainRTV.GetAddressOf(), m_dsView.Get());

	D3D11_VIEWPORT viewPort;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = (float)width;
	viewPort.Height = (float)height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	m_context->RSSetViewports(1u, &viewPort);

	m_rt = new RenderTarget({});
	m_rt->m_underlyingType = (void*)m_mainRTV.Get();


	m_ds = new DepthStencilBuffer({});
	m_ds->m_underlyingType = (void*)m_dsView.Get();


	m_context->OMSetBlendState(0, 0, 0xffffffff);

	D3D11_RASTERIZER_DESC rsDesc = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT{});
	rsDesc.FillMode = D3D11_FILL_SOLID;
	rsDesc.CullMode = D3D11_CULL_BACK;

	ID3D11RasterizerState* rs;

	m_device->CreateRasterizerState(&rsDesc, &rs);
	m_context->RSSetState(rs);

	rs->Release();

	LOG_GFX_INFO("GFXBackend Initialized Successfully");
	return true;
}

bool GfxBackendD3D11::Release()
{
#ifdef _DEBUG
	if (debugDevice)
	{
		OutputDebugStringA("Reporting LiveObjects on GFXBackend after calling Release:\n");
		debugDevice->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL | D3D11_RLDO_IGNORE_INTERNAL);
		debugDevice->Release();
		debugDevice = nullptr;
	}
#endif

	delete m_rt;
	delete m_ds;
	return true;
}

void GfxBackendD3D11::EndFrame()
{
	if (!SUCCEEDED(m_swapChain->Present(0u, 0u)))
	{
		// NOTE(cagri): falls in here when window is minimized!!
		LOG_GFX_ERROR("Present function has failed!\n");
	}

	m_context->ClearDepthStencilView(m_dsView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0u);
}

void GfxBackendD3D11::ClearBackBuffer(float r, float g, float b, float a)
{
	FLOAT rgba[4] = { r, g, b, a };
	m_context->ClearRenderTargetView(m_mainRTV.Get(), rgba);
}

void GfxBackendD3D11::ClearRenderTarget(RenderTarget* rt, float r, float g, float b, float a)
{
	FLOAT rgba[4] = { r, g, b, a };
	m_context->ClearRenderTargetView((ID3D11RenderTargetView*)(rt->m_underlyingType), rgba);
}

void GfxBackendD3D11::BindPrimitiveTopology(PrimitiveTopology* topology)
{
	m_context->IASetPrimitiveTopology(ConvertTorcGfxType(*(gfx::TORC_GFX_PRIMITIVE_TOPOLOGY*)topology->GetDesc()));
}

void GfxBackendD3D11::BindPrimitiveTopology(gfx::TORC_GFX_PRIMITIVE_TOPOLOGY topology)
{
	m_context->IASetPrimitiveTopology(ConvertTorcGfxType(topology));
}

bool GfxBackendD3D11::CreateBlendState(BlendState* bs)
{
	const gfx::BlendDesc& params = *(gfx::BlendDesc*)bs->GetDesc();
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

	return SUCCEEDED(m_device->CreateBlendState(&desc, (ID3D11BlendState**)&bs->m_underlyingType));
}

bool GfxBackendD3D11::CreateRasterizerState(RasterizerState* rs)
{
	const gfx::RasterizerDesc& params = *(gfx::RasterizerDesc*)rs->GetDesc();
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

	return SUCCEEDED(m_device->CreateRasterizerState(&desc, (ID3D11RasterizerState**)&rs->m_underlyingType));
}

bool GfxBackendD3D11::CreateSamplerState(SamplerState* ss)
{
	const gfx::SamplerDesc& params = *(gfx::SamplerDesc*)ss->GetDesc();
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

	return SUCCEEDED(m_device->CreateSamplerState(&desc, (ID3D11SamplerState**)&ss->m_underlyingType));
}

bool GfxBackendD3D11::CreateDepthStencilState(DepthStencilState* dss)
{
	gfx::DepthStencilDesc depthDesc = *(gfx::DepthStencilDesc*)dss->GetDesc();

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
	if (!SUCCEEDED(m_device->CreateDepthStencilState(&dsDesc, (ID3D11DepthStencilState**)&dss->m_underlyingType)))
	{
		return false;
	}
	return true;
}

bool GfxBackendD3D11::CreateRenderTarget(RenderTarget* rt, bool createMatchingDepthView)
{
	ID3D11Texture2D* rtvTexture;
	// create a texture with bind-flag render_target_view
	if (SUCCEEDED(Utils::CreateTexture(((gfx::RenderTargetDesc*)(rt->GetDesc()))->textureDesc, m_device.Get(), &rtvTexture)))
	{
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
		rtvDesc.Format = ConvertTorcGfxType(((gfx::RenderTargetDesc*)(rt->GetDesc()))->format);
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvDesc.Texture2D.MipSlice = 0u;
		HRESULT hr = m_device->CreateRenderTargetView(rtvTexture, &rtvDesc, (ID3D11RenderTargetView**)&rt->m_underlyingType);

		if (createMatchingDepthView)
		{
			ID3D11DepthStencilView* dssView;
			DepthStencilBuffer* dsBuffer = rt->GetDepthStencilBuffer();
			if (!SUCCEEDED(Utils::CreateDSSView(((gfx::RenderTargetDesc*)(rt->GetDesc()))->textureDesc,
									 m_device.Get(),
									 m_context.Get(),
									 (ID3D11DepthStencilView**)&dsBuffer->m_underlyingType)))
			{
				LOG_GFX_ERROR("DSView Creation for RT failed func: %s, file: %s", __FUNCTION__, __FILE__);
			}
		}

		if (rt->IsShaderResource())
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			srvDesc.Format = ConvertTorcGfxType(gfx::TORC_GFX_RESOURCE_DATA_FORMAT::FORMAT_B8G8R8A8_UNORM);
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;//ConvertTorcGfxType(gfx::TORC_GFX_SRV_DIMENSION_TEXTURE2D);
			srvDesc.Texture2D.MipLevels = 1u;
			srvDesc.Texture2D.MostDetailedMip = 0u;

			ID3D11RenderTargetView* srv = (ID3D11RenderTargetView*)rt->m_underlyingType;
			ID3D11Resource* resource;
			srv->GetResource(&resource);

			HRESULT hr = (m_device->CreateShaderResourceView(resource, &srvDesc,
															 (ID3D11ShaderResourceView**)&rt->GetShaderResource()->m_underlyingType));
			if (!SUCCEEDED(hr))
			{
				LOG_GFX_ERROR("ShaderResourceView Creation for RT failed func: %s, file: %s", __FUNCTION__, __FILE__);
			}
		}

		if (SUCCEEDED(hr))
		{
			return true;
		}
		rtvTexture->Release();
	}
	return false;
}

bool GfxBackendD3D11::CreateShaderResourceView(Texture* texture)
{
	ID3D11Texture2D* textureResource;

	// create a texture with bind-flag render_target_view
	if (SUCCEEDED(Utils::CreateTexture(*(gfx::TextureDesc*)texture->GetDesc(), m_device.Get(), &textureResource)))
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = ConvertTorcGfxType(gfx::TORC_GFX_RESOURCE_DATA_FORMAT::FORMAT_B8G8R8A8_UNORM);
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;//ConvertTorcGfxType(gfx::TORC_GFX_SRV_DIMENSION_TEXTURE2D);
		srvDesc.Texture2D.MipLevels = 1u;
		srvDesc.Texture2D.MostDetailedMip = 0u;

		HRESULT hr = (m_device->CreateShaderResourceView((ID3D11Resource*)textureResource, &srvDesc, 
														 (ID3D11ShaderResourceView**)&texture->m_underlyingType));
		if (SUCCEEDED(hr))
		{
			return true;
		}
		textureResource->Release();
	}
	
	return false;
}

bool GfxBackendD3D11::CreateShaderResourceView(ShaderResourceRenderTarget* rt)
{
	ID3D11ShaderResourceView* srv = (ID3D11ShaderResourceView*)rt->m_underlyingType;
	ID3D11Resource* resource;
	srv->GetResource(&resource);
	if (resource)
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = ConvertTorcGfxType(gfx::TORC_GFX_RESOURCE_DATA_FORMAT::FORMAT_B8G8R8A8_UNORM);
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;//ConvertTorcGfxType(gfx::TORC_GFX_SRV_DIMENSION_TEXTURE2D);
		srvDesc.Texture2D.MipLevels = 1u;
		srvDesc.Texture2D.MostDetailedMip = 0u;
		HRESULT hr = (m_device->CreateShaderResourceView(resource, &srvDesc,
														 (ID3D11ShaderResourceView**)&rt->m_underlyingType));
		if (SUCCEEDED(hr))
		{
			return true;
		}
	}

	return false;
}

bool GfxBackendD3D11::CreateBuffer(IGPUResource* buffer)
{
	D3D11_BUFFER_DESC desc;
	gfx::BufferDesc* bufferDesc = (gfx::BufferDesc*)buffer->GetDesc();
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = ConvertTorcGfxType(bufferDesc->usage);
	desc.MiscFlags = ConvertTorcGfxType(bufferDesc->miscFlags);
	desc.CPUAccessFlags = ConvertTorcGfxType(bufferDesc->cpuAccessFlags);
	desc.BindFlags = ConvertTorcGfxType(bufferDesc->bindFlags);

	gfx::SubResourceData* data = &bufferDesc->data;
	desc.ByteWidth = data->byteWidth;
	desc.StructureByteStride = data->structureByteStride;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = data->sysMem;
	initData.SysMemPitch = data->sysMemPitch;
	initData.SysMemSlicePitch = data->sysMemSlicePitch;

	HRESULT hr = m_device->CreateBuffer(&desc, &initData, 
										(ID3D11Buffer**)&buffer->m_underlyingType);
	
	return SUCCEEDED(hr);
}

bool GfxBackendD3D11::CreateTexture(IGPUResource* texture)
{
	ID3D11Texture2D* textureResource;

	// create a texture with bind-flag render_target_view
	if (SUCCEEDED(Utils::CreateTexture(*(gfx::TextureDesc*)texture->GetDesc(), m_device.Get(), &textureResource)))
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = ConvertTorcGfxType(gfx::TORC_GFX_RESOURCE_DATA_FORMAT::FORMAT_B8G8R8A8_UNORM);
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1u;
		srvDesc.Texture2D.MostDetailedMip = 0u;

		HRESULT hr = (m_device->CreateShaderResourceView((ID3D11Resource*)textureResource, &srvDesc,
														 (ID3D11ShaderResourceView**)&texture->m_underlyingType));
		if (SUCCEEDED(hr))
		{
			return true;
		}
	}

	textureResource->Release();
	return false;
}

void GfxBackendD3D11::BindBlendState(BlendState* bs)
{
	float b[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_context->OMSetBlendState((ID3D11BlendState*)bs->m_underlyingType, b, ~0);
}

void GfxBackendD3D11::BindBlendState(BlendState* bs, const float blendFactor[4], uint32_t blendMask)
{
	m_context->OMSetBlendState((ID3D11BlendState*)bs->m_underlyingType, blendFactor, blendMask);
}

void GfxBackendD3D11::BindRasterizerState(RasterizerState* rs)
{
	m_context->RSSetState((ID3D11RasterizerState*)rs->m_underlyingType);
}

void GfxBackendD3D11::BindSamplerState(SamplerState* ss)
{
	m_context->PSSetSamplers(0, 1, (ID3D11SamplerState**)&ss->m_underlyingType);
}

void GfxBackendD3D11::BindDepthStencilState(DepthStencilState* dss, uint32_t stencilRef)
{
	m_context->OMSetDepthStencilState((ID3D11DepthStencilState*)dss->m_underlyingType, stencilRef);
}

void GfxBackendD3D11::BindRenderTarget(RenderTarget* rt)
{
	m_context->OMSetRenderTargets(1u, 
								  (ID3D11RenderTargetView**)&rt->m_underlyingType, 
								  (rt->HasMatchingDepthStencilBuffer()) ? 
								  (ID3D11DepthStencilView*)(rt->GetDepthStencilBuffer()->m_underlyingType) : m_dsView.Get());
}

void GfxBackendD3D11::BindRenderTarget(RenderTarget* rt, DepthStencilState* dss)
{
	m_context->OMSetRenderTargets(1u,
								  (ID3D11RenderTargetView**)&rt->m_underlyingType,
								  (ID3D11DepthStencilView*)dss->m_underlyingType);
}

void GfxBackendD3D11::BindBuffer(Buffer* buffer)
{
	Buffer* buff = buffer;
	gfx::BufferDesc* buffDesc = (gfx::BufferDesc*)buffer->GetDesc();
	switch (((gfx::BufferDesc*)buff->GetDesc())->bindFlags)
	{
	case gfx::TORC_GFX_RESOURCE_BIND_FLAG::BIND_INDEX_BUFFER:
		m_context->IASetIndexBuffer((ID3D11Buffer*)buff->m_underlyingType, 
									ConvertTorcGfxType(buffDesc->format),
									buffDesc->offset);
		break;
	case gfx::TORC_GFX_RESOURCE_BIND_FLAG::BIND_VERTEX_BUFFER:
		m_context->IASetVertexBuffers(buffDesc->startSlot,
									  buffDesc->numBuffers,
									  (ID3D11Buffer**)&buff->m_underlyingType, 
									  &buffDesc->stride, &buffDesc->offset);
		break;
	case gfx::TORC_GFX_RESOURCE_BIND_FLAG::BIND_CONSTANT_BUFFER:
		switch (buffDesc->cbType)
		{
		case gfx::BufferDesc::ConstantBufferType::VS:
			m_context->VSSetConstantBuffers(buffDesc->startSlot,
											buffDesc->numBuffers,
											(ID3D11Buffer**)&buff->m_underlyingType);
			break;
		case gfx::BufferDesc::ConstantBufferType::PS:
			m_context->PSSetConstantBuffers(buffDesc->startSlot,
											buffDesc->numBuffers,
											(ID3D11Buffer**)&buff->m_underlyingType);
			break;
		case gfx::BufferDesc::ConstantBufferType::GS:
			m_context->GSSetConstantBuffers(buffDesc->startSlot,
											buffDesc->numBuffers,
											(ID3D11Buffer**)&buff->m_underlyingType);
			break;
		case gfx::BufferDesc::ConstantBufferType::HS:
			m_context->HSSetConstantBuffers(buffDesc->startSlot,
											buffDesc->numBuffers,
											(ID3D11Buffer**)&buff->m_underlyingType);
			break;
		case gfx::BufferDesc::ConstantBufferType::DS:
			m_context->DSSetConstantBuffers(buffDesc->startSlot,
											buffDesc->numBuffers,
											(ID3D11Buffer**)&buff->m_underlyingType);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void GfxBackendD3D11::BindShader(Shader* shader)
{
	switch (shader->GetShaderType())
	{
	case Shader::Type::VS:
		m_context->VSSetShader((ID3D11VertexShader*)shader->m_underlyingType, NULL, 0u);
		m_context->IASetInputLayout((ID3D11InputLayout*)shader->GetInputLayout()->m_underlyingType);
		break;
	case Shader::Type::PS:
		m_context->PSSetShader((ID3D11PixelShader*)shader->m_underlyingType, NULL, 0u);
		break;
	}
}

void GfxBackendD3D11::BindShaderResource(ShaderResourceHandle handle, ShaderHandle shaderHandle, uint32 startSlot, uint32 numViews)
{
	/*assert(IsValid(handle) && IsValid(shaderHandle));
	switch (m_shaders[shaderHandle.idx]->type)
	{
	case Shader::Type::PS:
		m_context->PSSetShaderResources(startSlot, numViews, &m_shaderResourceViews[handle.idx]);
		break;
	case Shader::Type::VS:
		m_context->VSSetShaderResources(startSlot, numViews, &m_shaderResourceViews[handle.idx]);
		break;
	default:
		break;
	}*/
}

void GfxBackendD3D11::DrawIndexed(uint32 indexCount, uint32 startIndexLocation, int32 baseVertexLocation)
{
	m_context->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
}

void GfxBackendD3D11::Draw(uint32 vertexCount, int32 baseVertexLocation)
{
	m_context->Draw(vertexCount, baseVertexLocation);
}

void GfxBackendD3D11::UpdateConstantBuffer(Buffer* buffer, void* newData, uint32 size)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	//  Disable GPU access to the vertex buffer data.
	m_context->Map(((ID3D11Buffer*)buffer->m_underlyingType), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	//  Update the vertex buffer here.
	memcpy(mappedResource.pData, newData, size);
	//  Reenable GPU access to the vertex buffer data.
	m_context->Unmap(((ID3D11Buffer*)buffer->m_underlyingType), 0);
}

void GfxBackendD3D11::CreateAndSetViewport(gfx::ViewportDesc viewPortDesc)
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

void GfxBackendD3D11::CreateAndSetViewport(uint32_t viewPortCount, gfx::ViewportDesc* viewPortDesc)
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

void GfxBackendD3D11::BindViewport(gfx::ViewportDesc viewportDesc)
{
	D3D11_VIEWPORT viewPort;
	viewPort.TopLeftX = viewportDesc.topLeftX;
	viewPort.TopLeftY = viewportDesc.topLeftY;
	viewPort.Width = viewportDesc.width;
	viewPort.Height = viewportDesc.height;
	viewPort.MinDepth = viewportDesc.minDepth;
	viewPort.MaxDepth = viewportDesc.maxDepth;

	m_context->RSSetViewports(1u, &viewPort);
}

void* GfxBackendD3D11::GetShaderResource(ShaderResourceHandle srHandle)
{
	/*assert(IsValid(srHandle));
	return (void*)m_shaderResourceViews[srHandle.idx];*/
	return NULL;
}

void GfxBackendD3D11::BindMainRenderTarget(bool withMainDepth)
{
	/*if (!withMainDepth)
	{
		m_context->OMSetDepthStencilState(NULL, NULL);
	}*/
	m_context->OMSetRenderTargets(1u, m_mainRTV.GetAddressOf(), 
		(withMainDepth) ? m_dsView.Get() : NULL);
	
	//TODO(cagri): store these values somewhere so we don't have to query each time
	ID3D11Resource* rsc;
	m_mainRTV->GetResource(&rsc);

	D3D11_TEXTURE2D_DESC desc;
	((ID3D11Texture2D*)rsc)->GetDesc(&desc);

	D3D11_VIEWPORT viewPort;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = (float)desc.Width;
	viewPort.Height = (float)desc.Height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	m_context->RSSetViewports(1u, &viewPort);
}

void GfxBackendD3D11::ClearDepthStencil(DepthStencilState* dss, bool clearDepth, bool clearStencil,
										float depthValueClearTo, uint8 stencilValueClearTo)
{
	uint32 clearFlags = 0u;
	clearFlags |= (clearDepth) ? D3D11_CLEAR_DEPTH : 0u;
	clearFlags |= (clearStencil) ? D3D11_CLEAR_STENCIL : 0u;

	m_context->ClearDepthStencilView((ID3D11DepthStencilView*)dss->m_underlyingType, clearFlags, depthValueClearTo, stencilValueClearTo);
}

void GfxBackendD3D11::ClearDepthStencil(void* dss, bool clearDepth, bool clearStencil, float depthValueClearTo, uint8 stencilValueClearTo)
{
	uint32 clearFlags = 0u;
	clearFlags |= (clearDepth) ? D3D11_CLEAR_DEPTH : 0u;
	clearFlags |= (clearStencil) ? D3D11_CLEAR_STENCIL : 0u;

	m_context->ClearDepthStencilView((ID3D11DepthStencilView*)dss, clearFlags, depthValueClearTo, stencilValueClearTo);
}

void GfxBackendD3D11::ReleaseResource(IGPUResource* resource)
{
	if (resource && resource->m_underlyingType)
	{
		((IUnknown*)resource->m_underlyingType)->Release();
		resource->m_underlyingType = nullptr;
	}
}

bool GfxBackendD3D11::CompileShader(Shader* shader, const char* name, int32 shaderType, const char* entryPoint)
{
	uint32_t flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(_DEBUG)
	flags |= D3DCOMPILE_DEBUG;
#endif

	std::string targetProfile;

	switch (shaderType)
	{
	case Shader::Type::PS:
	targetProfile = "ps_5_0";
	break;
	case Shader::Type::VS:
	targetProfile = "vs_5_0";
	break;
	default:
	break;
	}

	const D3D_SHADER_MACRO defines[] =
	{
		"EXAMPLE_DEFINE", "1",
		NULL, NULL
	};

	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile(
		Utils::ConvertToWideChar(name).c_str(),
		defines,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint,
		targetProfile.c_str(),
		flags,
		0,
		&shaderBlob,
		&errorBlob);


	if (errorBlob)
	{
		OutputDebugStringA((char*)errorBlob->GetBufferPointer());
	}
	//assert(SUCCEEDED(hr) == true);

	ID3D11ShaderReflection* shaderReflection;
	hr = D3DReflect(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&shaderReflection);

	if (!shaderReflection)
	{
		shaderBlob->Release();
		errorBlob->Release();
	}

	D3D11_SHADER_DESC shaderDesc;

	shaderReflection->GetDesc(&shaderDesc);
	uint32_t m = D3D11_SHVER_GET_TYPE(shaderDesc.Version);
	D3D11_SHADER_VERSION_TYPE type = (D3D11_SHADER_VERSION_TYPE)m;

	std::vector<D3D11_SIGNATURE_PARAMETER_DESC> inputParamDesc(shaderDesc.InputParameters);
	std::vector<D3D11_SHADER_INPUT_BIND_DESC> shaderInputBindDesc(shaderDesc.BoundResources);

	for (uint32_t i = 0; i < shaderDesc.InputParameters; i++)
	{
		shaderReflection->GetInputParameterDesc(i, &inputParamDesc[i]);
	}

	for (uint32_t i = 0; i < shaderDesc.BoundResources; i++)
	{
		shaderReflection->GetResourceBindingDesc(i, &shaderInputBindDesc[i]);
	}

	ShaderMetaData* md = shader->CreateNewMetaData();
	md->name = name;
	md->byteCode = shaderBlob->GetBufferPointer();
	md->hash = std::hash<std::string>{}(md->name);
	md->type = (Shader::Type)shaderType;
	md->byteCodeSize = shaderBlob->GetBufferSize();

	//D3D_REGISTER_COMPONENT_FLOAT32
	//D3D_REGISTER_COMPONENT_UINT32
	// MASK: 0xf, 0x7, 0x3, 0x1 each register can hold up to 4 component and mask shows how many of them are currently being use

	// if we are dealing with vertex shader, lets create D3D11_INPUT_ELEMENT_DESC with it
	if (type == D3D11_SHADER_VERSION_TYPE::D3D11_SHVER_VERTEX_SHADER)
	{
		D3D11_INPUT_ELEMENT_DESC* inputLayout = new D3D11_INPUT_ELEMENT_DESC[inputParamDesc.size()];
		for (size_t i = 0; i < inputParamDesc.size(); i++)
		{
			const D3D11_SIGNATURE_PARAMETER_DESC p = inputParamDesc[i];
			DXGI_FORMAT format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
			if (p.ComponentType == D3D_REGISTER_COMPONENT_TYPE::D3D_REGISTER_COMPONENT_FLOAT32)
			{
				switch (p.Mask)
				{
				case 0xf:
				format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
				break;
				case 0x7:
				format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
				break;
				case 0x3:
				format = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
				break;
				case 0x1:
				format = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
				break;
				default:
				break;
				}
			}
			else if (p.ComponentType == D3D_REGISTER_COMPONENT_TYPE::D3D_REGISTER_COMPONENT_UINT32)
			{
				switch (p.Mask)
				{
				case 0xf:
				format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_UINT;
				break;
				case 0x7:
				format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_UINT;
				break;
				case 0x3:
				format = DXGI_FORMAT::DXGI_FORMAT_R32G32_UINT;
				break;
				case 0x1:
				format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
				break;
				default:
				break;
				}
			}

			D3D11_INPUT_CLASSIFICATION inputClassification = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
			uint32_t instanceDataStepRate = 0u;
			if (i == 0 && inputParamDesc.size() > 1)
			{
				bool comp = !strcmp(p.SemanticName, inputParamDesc[i + 1].SemanticName);
				inputClassification = (comp) ? D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_INSTANCE_DATA : D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
				instanceDataStepRate = (comp) ? 1u : 0u;
			}
			else if (i > 0 && i < inputParamDesc.size() - 1)
			{
				if (!strcmp(p.SemanticName, inputParamDesc[i - 1].SemanticName) || !strcmp(p.SemanticName, inputParamDesc[i + 1].SemanticName))
				{
					inputClassification = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_INSTANCE_DATA;
					instanceDataStepRate = 1u;
				}
				else
				{
					inputClassification = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
					instanceDataStepRate = 0u;
				}
			}
			else if (i == 0 && inputParamDesc.size() == 1)
			{
				inputClassification = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
				instanceDataStepRate = 0u;
			}
			else
			{
				bool comp = !strcmp(p.SemanticName, inputParamDesc[i - 1].SemanticName);
				inputClassification = (comp) ? D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_INSTANCE_DATA : D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
				instanceDataStepRate = (comp) ? 1u : 0u;
			}

			//switch
			// TODO(cagri): p.Register should not be used here if we are using only on input slot
			//inputLayout[i] = { p.SemanticName, p.SemanticIndex, format, p.Register, D3D11_APPEND_ALIGNED_ELEMENT, inputClassification, instanceDataStepRate };
			inputLayout[i] = { p.SemanticName, p.SemanticIndex, format, 0, D3D11_APPEND_ALIGNED_ELEMENT, inputClassification, instanceDataStepRate };
		}

		InputLayout* il = new InputLayout();
		m_device->CreateInputLayout(inputLayout, (uint32)inputParamDesc.size(), 
									md->byteCode, (SIZE_T)md->byteCodeSize, 
									(ID3D11InputLayout**)&il->m_underlyingType);
		delete[] inputLayout;
		shader->SetInputLayout(il);
	}

	//shader->inputLayout;
	// store info about constant buffers, and shader resources so we can bind textures etc by name
	// we can also store type of resource if needed D3D_SHADER_INPUT_TYPE
	for (uint32_t i = 0; i < shaderDesc.BoundResources; i++)
	{
		//md->resourceMap[shaderInputBindDesc[i].Name] = shaderInputBindDesc[i].BindPoint;
	}

	switch (shaderType)
	{
	case Shader::Type::VS:
	{
		ID3D11VertexShader* vs;
		hr = m_device->CreateVertexShader(md->byteCode, md->byteCodeSize, nullptr, &vs);

		if (hr == S_OK)
		{
			shader->m_underlyingType = (void*)vs;
		}
		else
		{
			OutputDebugStringA("Vertex Shader Creation failed\n");
		}
	}
	break;
	case Shader::Type::PS:
	{
		ID3D11PixelShader* ps;
		hr = m_device->CreatePixelShader(md->byteCode, md->byteCodeSize, nullptr, &ps);

		if (hr == S_OK)
		{
			shader->m_underlyingType = (void*)ps;
		}
		else
		{
			OutputDebugStringA("Pixel Shader Creation failed\n");
		}
	}
	break;
	}
	if (shaderBlob)
		shaderBlob->Release();
	if (errorBlob)
		errorBlob->Release();
	if (shaderReflection)
		shaderReflection->Release();
	shader->SetShaderType((Shader::Type)shaderType);
	return true;
}