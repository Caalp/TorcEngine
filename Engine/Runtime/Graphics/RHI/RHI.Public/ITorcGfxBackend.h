#pragma once
#include "Core/System/ISystem.h"
#include "RDI/RDIShared/TorcGfxTypes.h"

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
class DepthStencilBuffer;
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
		virtual RenderTarget* GetMainRT() = 0;
		virtual DepthStencilBuffer* GetMainDepthBuffer() = 0;

		virtual void ClearBackBuffer(float r, float g, float b, float a) = 0;
		virtual void ClearRenderTarget(RenderTarget* rt, float r, float g, float b, float a) = 0;

		virtual void BindPrimitiveTopology(PrimitiveTopology* topology) = 0;
		virtual void BindPrimitiveTopology(TORC_GFX_PRIMITIVE_TOPOLOGY topology) = 0;

		virtual void BindBlendState(BlendState* bs) = 0;
		virtual void BindBlendState(BlendState* bs, const float blendFactor[4], uint32_t blendMask) = 0;
		virtual void BindRasterizerState(RasterizerState* rs) = 0;
		virtual void BindSamplerState(SamplerState* ss) = 0;
		virtual void BindDepthStencilState(DepthStencilState* dss, uint32_t stencilRef) = 0;
		virtual void BindRenderTarget(RenderTarget* rt) = 0;
		virtual void BindRenderTarget(RenderTarget* rt, DepthStencilState* dss) = 0;
		virtual void BindBuffer(Buffer* buffer) = 0;
		virtual void CreateAndSetViewport(gfx::ViewportDesc viewPortDesc) = 0;
		virtual void CreateAndSetViewport(uint32_t viewPortCount, gfx::ViewportDesc* viewPortDesc) = 0;
		virtual void BindViewport(ViewportDesc viewportDesc) = 0;
		virtual void BindShader(Shader* shader) = 0;
		virtual void BindShaderResource(ShaderResourceHandle handle, ShaderHandle shaderHandle, 
										uint32 startSlot, uint32 numViews) = 0;
		virtual void DrawIndexed(uint32 indexCount, uint32 startIndexLocation, int32 baseVertexLocation) = 0;
		virtual void Draw(uint32 vertexCount, int32 baseVertexLocation) = 0;

		virtual void UpdateConstantBuffer(Buffer* buffer, void* newData, uint32 size) = 0;

		virtual void* GetShaderResource(ShaderResourceHandle srHandle) = 0;
		virtual void BindMainRenderTarget(bool withMainDepth) = 0;
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


typedef void(*CommandCallback)(void* data);

struct DrawCommand
{
	static gfx::ITorcGfxBackend*& gfx;
	virtual void Execute() = 0;
};

struct DrawIndexed : DrawCommand
{
	uint32 indexCount;
	uint32 startIndexLocation;
	int32 baseVertexLocation;

	virtual void Execute()
	{
		gEnv->gfx->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
	}

	//static CommandCallback func;
};

struct Draw : DrawCommand
{
	uint32 vertexCount;
	int32 baseVertexLocation;

	virtual void Execute()
	{
		gEnv->gfx->Draw(vertexCount, baseVertexLocation);
	}

	//static CommandCallback func;
};

static void DrawIndexFunc(void* data)
{
	DrawIndexed* d = reinterpret_cast<DrawIndexed*>(data);
	gEnv->gfx->DrawIndexed(d->indexCount, d->startIndexLocation, d->baseVertexLocation);
}

static void DrawFunc(void* data)
{
	Draw* d = reinterpret_cast<Draw*>(data);
	gEnv->gfx->Draw(d->vertexCount, d->baseVertexLocation);
}
