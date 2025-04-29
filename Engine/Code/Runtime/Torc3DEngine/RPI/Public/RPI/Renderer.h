#pragma once
#include "IGPUResource.h"
#include "FrameGraph/RenderGraph.h"

#include <Core/Math/MathUtils.h>

#define MAX_HANDLE_COUNT_BLEND_STATE 100
#define MAX_HANDLE_COUNT_RASTERIZER_STATE 100
#define MAX_HANDLE_COUNT_SAMPLER_STATE 100
#define MAX_HANDLE_COUNT_DEPTH_STENCIL_STATE 100
#define MAX_HANDLE_COUNT_BUFFERS 1024
#define MAX_HANDLE_COUNT_SHADER 1024
#define MAX_HANDLE_COUNT_RT 8

class BlendState;
class RasterizerState;
class SamplerState;
class DepthStencilState;
class IGPUResource;

struct AABB
{
	math::Vec3f center;
	math::Vec3f extends;
};

namespace gfx
{
	class ITorcGfxBackend;

	struct BlendDesc;
	struct TextureDesc;
}

class IEditorHook
{
public:
	virtual void Initialize() = 0;
};

class DebugRenderer
{
public:
};

class GPUResourceManager
{
public:

private:
};

class Renderer
{
	friend class ITorcgfxBackend;
public:

	Renderer();
	~Renderer();

	/**
	 * Takes parameters which are used to create and initialize swapchain and gfx backend.
	 * Function also internally creates and initalized pointers for device and context as well as loading the dll
	 * that contains specified backend.
	 *
	 * @param params which contains necessary values that will be used for initializing rendering backend.
	 */
//	bool Initialize(SystemGlobalEnvironment& env, gfx::GfxBackendParams& params);
//	void Release();
//
//	void OnWindowResize(uint32 width, uint32 height);
//
//	void Update();
//
//	void BeginFrame();
//	void EndFrame();
//
//	void ClearBackBuffer(math::Vec4f color);
//	void ClearRenderTarget(RenderTarget* rt, math::Vec4f color);
//	void ClearDepthStencil(DepthStencilStateHandle dssHandle, bool clearDepth, 
//						   bool clearStencil, float depthValueClearTo, uint8 stencilValueClearTo);
//	void ClearDepthStencil(void* dss, bool clearDepth,
//						   bool clearStencil, float depthValueClearTo, uint8 stencilValueClearTo);
//	BlendStateHandle CreateBlendState(const gfx::BlendDesc& params);
//	RasterizerStateHandle CreateRasterizerState(const gfx::RasterizerDesc& params);
//	SamplerStateHandle CreateSamplerState(const gfx::SamplerDesc& params);
//	DepthStencilStateHandle CreateDepthStencilState(const gfx::DepthStencilDesc& dsDesc,
//													const gfx::TextureDesc& texDesc);
//
//	DepthStencilStateHandle CreateDepthStencilState(const gfx::DepthStencilDesc& dsDesc);
//	RenderTargetHandle CreateRenderTarget(const gfx::RenderTargetDesc& desc);
//	BufferHandle CreateBuffer(const gfx::BufferDesc& bufferDesc);
//	ShaderResourceHandle CreateShaderResource(const gfx::TextureDesc& desc);
//	Texture* CreateTexture(const gfx::TextureDesc& desc);
//	ShaderResourceHandle CreateShaderResource(Texture* res);
//
//	void BindPrimitiveTopology(gfx::TORC_GFX_PRIMITIVE_TOPOLOGY topology);
//	void BindBlendState(BlendStateHandle handle, const float blendFactor[4], uint32_t blendMask);
//	void BindBlendState(BlendStateHandle handle);
//	void BindBlendState(BlendState* bs);
//	void BindBlendState(BlendState* bs, const float blendFactor[4], uint32_t blendMask);
//	void BindRenderTarget(RenderTargetHandle handle);
//	void BindRenderTarget(RenderTargetHandle handle, DepthStencilStateHandle dssHandle);
//	void BindRenderTarget(RenderTarget* rt);
//	void BindRenderTarget(RenderTarget* rt, DepthStencilState* dss);
//	void BindBuffer(BufferHandle bufferHandle);
//	void BindBuffer(Buffer* buffer);
//	void BindShader(ShaderHandle shaderHandle);
//	void BindShader(Shader* shader);
//	
//	void BindViewport(gfx::ViewportDesc viewportDesc);
//	void BindShaderResource(ShaderResourceHandle handle, ShaderHandle shaderHandle, 
//							uint32 startSlot, uint32 numViews);
//
//	void* GetShaderResource(ShaderResourceHandle srHandle);
//	void ResetRenderTarget(bool useMainDepth);
//	gfx::ITorcGfxBackend* GetGFXBackend() { return m_gfxBackend; }
//
//	IGPUResource* GetResourceByHandle(ResourceHandle handle);
//	void ReleaseInternalResource(IGPUResource* resource);
//	void ReleaseInternalResourceByHandle(ResourceHandle handle);
//
//	// TODO(cagri): We can factor this function out as plugin
//	ShaderHandle CompileShader(const char* name, int32 shaderType,
//							   const char* entryPoint = "main");
//
//	void DrawAABB(const AABB& box, math::Vec4f color);
//private:
//	bool m_isInitialized;
//	gfx::ITorcGfxBackend* m_gfxBackend; // NOTE(cagri): we can also inherit from plugin and call release explicitly
//	THandleRegistry<MAX_HANDLE_COUNT_BLEND_STATE> m_blendStateHandles;
//	THandleRegistry<MAX_HANDLE_COUNT_RASTERIZER_STATE> m_rasterizerStateHandles;
//	THandleRegistry<MAX_HANDLE_COUNT_SAMPLER_STATE> m_samplerStateHandles;
//	THandleRegistry<MAX_HANDLE_COUNT_DEPTH_STENCIL_STATE> m_depthStencilStateHandles;
//	THandleRegistry<MAX_HANDLE_COUNT_BUFFERS> m_bufferHandles;
//	THandleRegistry<MAX_HANDLE_COUNT_SHADER> m_shaderHandles;
//	THandleRegistry<MAX_HANDLE_COUNT_RT> m_rtHandles;
//	THandleRegistry<MAX_HANDLE_COUNT_RT> m_shaderResourceHandles;
//
//	std::map<decltype(ResourceHandle::id), std::vector<IGPUResource*>> m_resources;
//	std::map<ResourceDescID::IDType, uint32> m_descMap;
};