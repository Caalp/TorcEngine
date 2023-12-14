#pragma once
#include "Core/TorcSystem/ISystem.h"
#include "TorcGfx/TorcGfxTypes.h"

struct BlendStateHandle;
struct RasterizerStateHandle;
struct SamplerStateHandle;
struct DepthStencilStateHandle;
struct RenderTargetHandle;
struct ViewPortHandle;
struct BufferHandle;
struct ShaderHandle;
struct ShaderResourceHandle;

class IGPUResource;
class BlendState;
class RasterizerState;
class SamplerState;
class DepthStencilState;
class RenderTarget;
class PrimitiveTopology;
class Texture;
class Buffer;
class Shader;
class InputLayout;
class ShaderResourceRenderTarget;

struct Material
{
	std::string pixelShader;
	std::string vertexShader;
};

namespace gfx
{
	class ITorcGfxBackend
	{
	public:
		virtual bool Initialize(SystemGlobalEnvironment& env, GfxBackendParams& gfxParams) = 0;
		virtual bool Release() = 0;
		virtual bool CreateBlendState(BlendState* bs) = 0;
		virtual bool CreateRasterizerState(RasterizerState* rs) = 0;
		virtual bool CreateSamplerState(SamplerState* ss) = 0;
		virtual bool CreateDepthStencilState(DepthStencilState* dss) = 0;
		virtual bool CreateRenderTarget(RenderTarget* rt, bool createMatchingDepthView = true) = 0;
		virtual bool CreateShaderResourceView(Texture* rt) = 0;
		virtual bool CreateShaderResourceView(ShaderResourceRenderTarget* rt) = 0;
		virtual bool CreateBuffer(IGPUResource* bufferResource) = 0;
		virtual bool CreateTexture(IGPUResource* bufferResource) = 0;
						
		virtual void StartFrame() = 0;
		virtual void EndFrame() = 0;

		virtual void* GetDevice() = 0;
		virtual void* GetContext() = 0;

		virtual void ClearBackBuffer(float r, float g, float b, float a) = 0;
		virtual void ClearRenderTarget(RenderTarget* rt, float r, float g, float b, float a) = 0;

		virtual void SetPrimitiveTopology(PrimitiveTopology* topology) = 0;
		virtual void SetPrimitiveTopology(TORC_GFX_PRIMITIVE_TOPOLOGY topology) = 0;

		virtual void SetBlendState(BlendState* bs) = 0;
		virtual void SetBlendState(BlendState* bs, const float blendFactor[4], uint32_t blendMask) = 0;
		virtual void SetRasterizerState(RasterizerState* rs) = 0;
		virtual void SetSamplerState(SamplerState* ss) = 0;
		virtual void SetDepthStencilState(DepthStencilState* dss, uint32_t stencilRef) = 0;
		virtual void SetRenderTarget(RenderTarget* rt) = 0;
		virtual void SetRenderTarget(RenderTarget* rt, DepthStencilState* dss) = 0;
		virtual void SetBuffer(Buffer* buffer) = 0;
		virtual void CreateAndSetViewport(gfx::ViewportDesc viewPortDesc) = 0;
		virtual void CreateAndSetViewport(uint32_t viewPortCount, gfx::ViewportDesc* viewPortDesc) = 0;
		virtual void SetViewport(ViewportDesc viewportDesc) = 0;
		virtual void SetShader(Shader* shader) = 0;
		virtual void BindShaderResource(ShaderResourceHandle handle, ShaderHandle shaderHandle, 
										uint32 startSlot, uint32 numViews) = 0;
		virtual void DrawIndexed(uint32 indexCount, uint32 startIndexLocation, int baseVertexLocation) = 0;

		virtual void* GetShaderResource(ShaderResourceHandle srHandle) = 0;
		virtual void SetMainRenderTarget(bool withMainDepth) = 0;
		virtual void ClearDepthStencil(DepthStencilState* dss, bool clearDepth, 
									   bool clearStencil, float depthValueClearTo, uint8 stencilValueClearTo) = 0;
		virtual void ClearDepthStencil(void* dss, bool clearDepth,
									   bool clearStencil, float depthValueClearTo, uint8 stencilValueClearTo) = 0;
		virtual void ReleaseResource(IGPUResource* resource) = 0;

		/**
		 * Compiles shaders and stores them in the index pointed by the handle.
		 * Entry point and target profile parameters are optional if they are not mentioned main is assumed as entry point
		 *
		 * @param handle unique handle to the compiled shader
		 * @param name filepath/name of the shader hlsl
		 * @param entryPoint enry point for shader code
		 * @param targetProfile vs_5_0, ps_5_0 and so on depending on shader model and backend
		 * @return returns true if compilation is successfull otherwise false
		 */
		virtual bool CompileShader(Shader* shader, const char* name,
								   int32 shaderType, const char* entryPoint = "main") = 0;
	};
}