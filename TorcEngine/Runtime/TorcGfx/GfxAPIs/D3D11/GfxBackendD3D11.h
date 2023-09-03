#pragma once
#include "TorcGfx/ITorcGfxBackend.h"

class GfxBackendD3D11 : public gfx::ITorcGfxBackend
{
public:
	virtual bool InitializeGfxBackend(gfx::GfxBackendParams& gfxParams) override;
	virtual bool ReleaseGfxBackend() override;

	virtual void CreateBlendState(BlendStateHandle handle, const gfx::BlendDesc& params) override;
	virtual void CreateRasterizerState(RasterizerStateHandle handle, const gfx::RasterizerDesc& params) override;
	virtual void CreateSamplerState(SamplerStateHandle handle, const gfx::SamplerDesc& params) override;
	virtual void CreateDepthStencilState(DepthStencilStateHandle handle, const gfx::TextureDesc texDesc, const gfx::DepthStencilDesc& depthDesc) override;
	virtual void CreateRenderTarget(RenderTargetHandle handle, const gfx::RenderTargetDesc& params) override;
	virtual void CreateRenderTarget(RenderTargetHandle handle, const gfx::TextureDesc& texDesc) override;
	virtual void CreateShaderResourceView() override;

	
	virtual void SetBlendState(BlendStateHandle handle) override;
	virtual void SetBlendState(BlendStateHandle handle, const float blendFactor[4], uint32_t blendMask) override;
	virtual void SetRasterizerState(RasterizerStateHandle handle) override;
	virtual void SetSamplerState(SamplerStateHandle handle) override;
	virtual void SetDepthStencilState(DepthStencilStateHandle handle, uint32_t stencilRef) override;
	virtual void SetRenderTarget(RenderTargetHandle handle) override;
	virtual void SetRenderTarget(RenderTargetHandle handle, DepthStencilStateHandle depthStencilHandle) override;
	virtual void CreateAndSetViewPort(gfx::ViewPortDesc viewPortDesc) override;
	virtual void CreateAndSetViewPort(uint32_t viewPortCount, gfx::ViewPortDesc* viewPortDesc) override;
	
private:
	gfx::GfxBackendParams m_gfxInitParam;

	Microsoft::WRL::ComPtr<ID3D11Device> m_device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;


	ID3D11BlendState* m_blendStates[MAX_HANDLE_COUNT_BLEND_STATE];
	ID3D11SamplerState* m_samplerStates[MAX_HANDLE_COUNT_BLEND_STATE];
	ID3D11RasterizerState* m_rasterizerStates[MAX_HANDLE_COUNT_RASTERIZER_STATE];
	ID3D11DepthStencilState* m_depthStencilStates[MAX_HANDLE_COUNT_DEPTH_STENCIL_STATE];

	ID3D11RenderTargetView* m_renderTargetViews[MAX_HANDLE_COUNT_RENDER_TARGET];
	ID3D11DepthStencilView* m_depthStencilStateViews[MAX_HANDLE_COUNT_DEPTH_STENCIL_STATE];
};