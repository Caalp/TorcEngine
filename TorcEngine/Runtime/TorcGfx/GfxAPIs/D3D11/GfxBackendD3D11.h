#pragma once
#include "TorcGfx/ITorcGfxBackend.h"

class GfxBackendD3D11 final : public gfx::ITorcGfxBackend
{
	friend class Renderer;
public:
	virtual bool Initialize(SystemGlobalEnvironment& env, gfx::GfxBackendParams& gfxParams) override;
	virtual bool Release() override;
	virtual void StartFrame() override {};
	virtual void EndFrame() override;
	virtual void* GetDevice() override { return (void*)m_device.Get(); }
	virtual void* GetContext() override { return (void*)m_context.Get(); }
	virtual void ClearBackBuffer(float r, float g, float b, float a) override;
	virtual void ClearRenderTarget(RenderTarget* rt, float r, float g, float b, float a) override;
	virtual void SetPrimitiveTopology(PrimitiveTopology* topology) override;
	virtual void SetPrimitiveTopology(gfx::TORC_GFX_PRIMITIVE_TOPOLOGY topology) override;
	virtual bool CreateBlendState(BlendState* bs) override;
	virtual bool CreateRasterizerState(RasterizerState* rs) override;
	virtual bool CreateSamplerState(SamplerState* ss) override;
	virtual bool CreateDepthStencilState(DepthStencilState* dss) override;
	virtual bool CreateRenderTarget(RenderTarget* rt, bool createMatchingDepthView = true) override;
	virtual bool CreateShaderResourceView(Texture* rt) override;
	virtual bool CreateShaderResourceView(ShaderResourceRenderTarget* rt) override;
	//virtual bool CreateBuffer(Buffer* buffer, const gfx::SubResourceData* data) override;
	virtual bool CreateBuffer(IGPUResource* buffer) override;
	virtual bool CreateTexture(IGPUResource* bufferResource) override;
	virtual void SetBlendState(BlendState* bs) override;
	virtual void SetBlendState(BlendState* bs, const float blendFactor[4], uint32_t blendMask) override;
	virtual void SetRasterizerState(RasterizerState* rs) override;
	virtual void SetSamplerState(SamplerState* ss) override;
	virtual void SetDepthStencilState(DepthStencilState* dss, uint32_t stencilRef) override;
	virtual void SetRenderTarget(RenderTarget* rt) override;
	virtual void SetRenderTarget(RenderTarget* rt, DepthStencilState* dss) override;
	virtual void SetBuffer(Buffer* buffer) override;
	virtual void SetShader(Shader* shader) override;
	virtual void BindShaderResource(ShaderResourceHandle handle, ShaderHandle shaderHandle, 
									uint32 startSlot, uint32 numViews) override;
	virtual void DrawIndexed(uint32 indexCount, uint32 startIndexLocation, int baseVertexLocation) override;
	virtual void CreateAndSetViewport(gfx::ViewportDesc viewPortDesc) override;
	virtual void CreateAndSetViewport(uint32_t viewPortCount, gfx::ViewportDesc* viewPortDesc) override;
	virtual void SetViewport(gfx::ViewportDesc viewportDesc) override;
	virtual void* GetShaderResource(ShaderResourceHandle srHandle) override;
	virtual void SetMainRenderTarget(bool withMainDepth) override;
	virtual void ClearDepthStencil(DepthStencilState* dssHandle, bool clearDepth, bool clearStencil, 
								   float depthValueClearTo, uint8 stencilValueClearTo) override;
	virtual void ClearDepthStencil(void* dssHandle, bool clearDepth, bool clearStencil,
								   float depthValueClearTo, uint8 stencilValueClearTo) override;
	virtual void ReleaseResource(IGPUResource* resource) override;

	virtual bool CompileShader(Shader* shader, const char* name, int32 shaderType,
							   const char* entryPoint = "main") override;
protected:
	gfx::GfxBackendParams m_gfxInitParam;

	Microsoft::WRL::ComPtr<ID3D11Device> m_device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;

	Microsoft::WRL::ComPtr <ID3D11RenderTargetView> m_mainRTV;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pdsView;
};