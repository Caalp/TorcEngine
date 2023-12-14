#pragma once
#include "TorcGfx/TorcgfxTypes.h"
#include "TorcGfx/HandleRegistry.h"
#include "TorcGfx/ITorcGfxBackend.h"
#include "Core/TorcSystem/ISystem.h"

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
	bool Initialize(SystemGlobalEnvironment& env, gfx::GfxBackendParams& params);
	void Release();

	void OnWindowResize(uint32 width, uint32 height);

	void Update()
	{}

	void BeginFrame();
	void EndFrame();

	void ClearBackBuffer(math::Vec4f color);
	void ClearRenderTarget(RenderTarget* rt, math::Vec4f color);
	void ClearDepthStencil(DepthStencilStateHandle dssHandle, bool clearDepth, 
						   bool clearStencil, float depthValueClearTo, uint8 stencilValueClearTo);
	void ClearDepthStencil(void* dss, bool clearDepth,
						   bool clearStencil, float depthValueClearTo, uint8 stencilValueClearTo);
	BlendStateHandle CreateBlendState(const gfx::BlendDesc& params);
	RasterizerStateHandle CreateRasterizerState(const gfx::RasterizerDesc& params);
	SamplerStateHandle CreateSamplerState(const gfx::SamplerDesc& params);
	DepthStencilStateHandle CreateDepthStencilState(const gfx::DepthStencilDesc& dsDesc,
													const gfx::TextureDesc& texDesc);

	DepthStencilStateHandle CreateDepthStencilState(const gfx::DepthStencilDesc& dsDesc);
	RenderTargetHandle CreateRenderTarget(const gfx::RenderTargetDesc& desc);
	BufferHandle CreateBuffer(const gfx::BufferDesc& bufferDesc);
	ShaderResourceHandle CreateShaderResource(const gfx::TextureDesc& desc);
	Texture* CreateTexture(const gfx::TextureDesc& desc);
	ShaderResourceHandle CreateShaderResource(Texture* res);

	void SetPrimitiveTopology(gfx::TORC_GFX_PRIMITIVE_TOPOLOGY topology);
	void SetBlendState(BlendStateHandle handle, const float blendFactor[4], uint32_t blendMask);
	void SetBlendState(BlendStateHandle handle);
	void SetBlendState(BlendState* bs);
	void SetBlendState(BlendState* bs, const float blendFactor[4], uint32_t blendMask);
	void SetRenderTarget(RenderTargetHandle handle);
	void SetRenderTarget(RenderTargetHandle handle, DepthStencilStateHandle dssHandle);
	void SetRenderTarget(RenderTarget* rt);
	void SetRenderTarget(RenderTarget* rt, DepthStencilState* dss);
	void SetBuffer(BufferHandle bufferHandle);
	void SetBuffer(Buffer* buffer);
	void SetShader(ShaderHandle shaderHandle);
	void SetShader(Shader* shader);
	
	void SetViewport(gfx::ViewportDesc viewportDesc);
	void BindShaderResource(ShaderResourceHandle handle, ShaderHandle shaderHandle, 
							uint32 startSlot, uint32 numViews);

	void* GetShaderResource(ShaderResourceHandle srHandle);
	void ResetRenderTarget(bool useMainDepth);
	gfx::ITorcGfxBackend* GetGFXBackend() { return m_gfxBackend; }

	IGPUResource* GetResourceByHandle(ResourceHandle handle);
	void ReleaseInternalResource(IGPUResource* resource);
	void ReleaseInternalResourceByHandle(ResourceHandle handle);
	ShaderHandle CompileShader(const char* name, int32 shaderType,
							   const char* entryPoint = "main");
private:
	bool m_isInitialized;
	gfx::ITorcGfxBackend* m_gfxBackend; // NOTE(cagri): we can also inherit from plugin and call release explicitly
	HandleRegistry<MAX_HANDLE_COUNT_BLEND_STATE> m_blendStateHandles;
	HandleRegistry<MAX_HANDLE_COUNT_RASTERIZER_STATE> m_rasterizerStateHandles;
	HandleRegistry<MAX_HANDLE_COUNT_SAMPLER_STATE> m_samplerStateHandles;
	HandleRegistry<MAX_HANDLE_COUNT_DEPTH_STENCIL_STATE> m_depthStencilStateHandles;
	HandleRegistry<MAX_HANDLE_COUNT_BUFFERS> m_bufferHandles;
	HandleRegistry<MAX_HANDLE_COUNT_SHADER> m_shaderHandles;
	HandleRegistry<MAX_HANDLE_COUNT_RT> m_rtHandles;
	HandleRegistry<MAX_HANDLE_COUNT_RT> m_shaderResourceHandles;

	std::map<decltype(ResourceHandle::id), std::vector<IGPUResource*>> m_resources;
};