#pragma once

struct BlendStateHandle;
struct RasterizerStateHandle;
struct SamplerStateHandle;
struct DepthStencilStateHandle;
struct RenderTargetHandle;
struct ViewPortHandle;


//struct ShaderDesc
//{
//	std::string name;
//	size_t hash;
//	void* byteCode;
//};

namespace gfx
{
	struct GfxBackendParams;
	class IGfxContext;

	class ITorcGfxBackend
	{
	public:
		virtual bool InitializeGfxBackend(GfxBackendParams& gfxParams) = 0;
		virtual bool ReleaseGfxBackend() = 0;

		virtual void CreateBlendState(BlendStateHandle handle, const BlendDesc& params) = 0;
		virtual void CreateRasterizerState(RasterizerStateHandle handle, const RasterizerDesc& params) = 0;
		virtual void CreateSamplerState(SamplerStateHandle handle, const SamplerDesc& params) = 0;
		virtual void CreateDepthStencilState(DepthStencilStateHandle handle, const gfx::TextureDesc texDesc, const gfx::DepthStencilDesc& depthDesc) = 0;
		virtual void CreateRenderTarget(RenderTargetHandle handle, const RenderTargetDesc& params) = 0;
		virtual void CreateShaderResourceView() = 0;
		//virtual void CreateShader(ShaderDesc) = 0;

		/**
		 * Given TextureDesc create a texture and then create a render target for it 
		 * TextureDesc should have binding flag as render target
		 * 
		 * @param handle to the render target
		 * @param texDesc texture desc that is used for creating render target
		 */
		virtual void CreateRenderTarget(RenderTargetHandle handle, const TextureDesc& texDesc) = 0;
		
		//virtual void CreateRenderTarget(RenderTargetHandle handle, TextureHandle texDesc) = 0;
		virtual void SetBlendState(BlendStateHandle handle) = 0;
		virtual void SetBlendState(BlendStateHandle handle, const float blendFactor[4], uint32_t blendMask) = 0;
		virtual void SetRasterizerState(RasterizerStateHandle handle) = 0;
		virtual void SetSamplerState(SamplerStateHandle handle) = 0;
		virtual void SetDepthStencilState(DepthStencilStateHandle handle, uint32_t stencilRef) = 0;
		virtual void SetRenderTarget(RenderTargetHandle handle) = 0;
		virtual void SetRenderTarget(RenderTargetHandle handle, DepthStencilStateHandle depthStencilHandle) = 0;
		virtual void CreateAndSetViewPort(gfx::ViewPortDesc viewPortDesc) = 0;
		virtual void CreateAndSetViewPort(uint32_t viewPortCount, gfx::ViewPortDesc* viewPortDesc) = 0;
	};
}