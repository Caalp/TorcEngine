#include "pch.h"

#include "Renderer/Renderer.h"
#include "Core/Plugins/Plugin.h"
#include "Core/Plugins/PluginLoader.h"

#include "Renderer/GPUObjects/BlendState.h"
#include "Renderer/GPUObjects/RasterizerState.h"
#include "Renderer/GPUObjects/DepthStencilState.h"
#include "Renderer/GPUObjects/SamplerState.h"
#include "Renderer/GPUObjects/Buffer.h"
#include "Renderer/GPUObjects/RenderTarget.h"
#include "Renderer/GPUObjects/Shader.h"
#include "Renderer/GPUObjects/Texture.h"

#define DEFINE_RESOURCE_CREATE_FUNCTION(resourceName, descriptor, handleRegistry)\
	resourceName##Handle Renderer::Create##resourceName(const gfx::descriptor& params)\
	{\
		resourceName##Handle handle = { handleRegistry.Allocate() };\
		resourceName* rs = new resourceName(params);\
		if (!m_gfxBackend->Create##resourceName(rs))\
		{\
			handle = { handleRegistry.Release(handle.idx) };\
			delete rs;\
			return handle;\
		}\
		ASSERT(m_resources[handle.type_id][handle.idx] == nullptr, "Resource is not released properly!");\
		m_resources[handle.type_id][handle.idx] = rs;\
		return handle;\
	}\


DEFINE_RESOURCE_CREATE_FUNCTION(BlendState, BlendDesc, m_blendStateHandles)
DEFINE_RESOURCE_CREATE_FUNCTION(RasterizerState, RasterizerDesc, m_rasterizerStateHandles)
DEFINE_RESOURCE_CREATE_FUNCTION(SamplerState, SamplerDesc, m_samplerStateHandles)
DEFINE_RESOURCE_CREATE_FUNCTION(DepthStencilState, DepthStencilDesc, m_depthStencilStateHandles)

#undef DEFINE_RESOURCE_CREATE_FUNCTION

Renderer::Renderer()
	: m_isInitialized(false)
	, m_gfxBackend(nullptr)
{
	m_resources[BlendStateHandle::type_id] = std::vector<IGPUResource*>(MAX_HANDLE_COUNT_BLEND_STATE, nullptr);
	m_resources[RasterizerStateHandle::type_id] = std::vector<IGPUResource*>(MAX_HANDLE_COUNT_RASTERIZER_STATE, nullptr);
	m_resources[SamplerStateHandle::type_id] = std::vector<IGPUResource*>(MAX_HANDLE_COUNT_SAMPLER_STATE, nullptr);
	m_resources[DepthStencilStateHandle::type_id] = std::vector<IGPUResource*>(MAX_HANDLE_COUNT_DEPTH_STENCIL_STATE, nullptr);
	m_resources[BufferHandle::type_id] = std::vector<IGPUResource*>(MAX_HANDLE_COUNT_BUFFERS, nullptr);
	m_resources[ShaderHandle::type_id] = std::vector<IGPUResource*>(MAX_HANDLE_COUNT_SHADER, nullptr);
	m_resources[RenderTargetHandle::type_id] = std::vector<IGPUResource*>(MAX_HANDLE_COUNT_RT, nullptr);
	m_resources[ShaderResourceHandle::type_id] = std::vector<IGPUResource*>(MAX_HANDLE_COUNT_RT, nullptr);
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize(SystemGlobalEnvironment& env, gfx::GfxBackendParams& params)
{
	PluginLoader* loader = gEnv->pluginLoader;
	if (loader)
	{
		Plugin* plugin = loader->GetPlugin(params.backendDLLName);
		if (plugin == nullptr)
		{
			LOG_ERROR(LogChannel::LC_Platform, "Pluging is not loaded correctly\n")
		}
		plugin->CallInitialize((void**)&m_gfxBackend);

		m_isInitialized = m_gfxBackend->Initialize(env, params);
	}

	env.rr = this;
	return m_isInitialized;
}

void Renderer::Release()
{
	// before releasing backend release resources we have
	for (auto& [key, val] : m_resources)
	{
		for (IGPUResource* res : val)
		{
			if (res)
			{
				delete res;
			}
		}
		val.clear();
	}
	m_resources.clear();

	if (m_gfxBackend)
		m_gfxBackend->Release();
}

void Renderer::OnWindowResize(uint32 width, uint32 height)
{
}

void Renderer::BeginFrame()
{
	IEditor* editor = gEnv->editor;
	if (editor)
	{
		editor->OnFrameBegin();
	}
}

void Renderer::EndFrame()
{
	IEditor* editor = gEnv->editor;
	if (editor)
	{
		editor->OnFrameEnd();
	}

	m_gfxBackend->EndFrame();
}

void Renderer::ClearBackBuffer(math::Vec4f color)
{
	m_gfxBackend->ClearBackBuffer(color.x, color.y, color.z, color.w);
}

void Renderer::ClearRenderTarget(RenderTarget* rt, math::Vec4f color)
{
	m_gfxBackend->ClearRenderTarget(rt, color.x, color.y, color.z, color.w);
}

void Renderer::ClearDepthStencil(DepthStencilStateHandle dssHandle,
								 bool clearDepth,
								 bool clearStencil,
								 float depthValueClearTo,
								 uint8 stencilValueClearTo)
{
	DepthStencilState* dss = (DepthStencilState*)m_resources[dssHandle.type_id][dssHandle.idx];
	m_gfxBackend->ClearDepthStencil(dss, clearDepth,
									clearStencil, depthValueClearTo, stencilValueClearTo);
}

void Renderer::ClearDepthStencil(void* dss, bool clearDepth, bool clearStencil, float depthValueClearTo, uint8 stencilValueClearTo)
{
	ASSERT(dss != nullptr, "DepthStencilState object is NULL %s", __FUNC__);
	m_gfxBackend->ClearDepthStencil(dss, clearDepth,
									clearStencil, depthValueClearTo, stencilValueClearTo);
}

DepthStencilStateHandle Renderer::CreateDepthStencilState(const gfx::DepthStencilDesc& dsDesc, const gfx::TextureDesc& texDesc)
{
	DepthStencilStateHandle handle = { m_depthStencilStateHandles.Allocate() };
	DepthStencilState* dss = new DepthStencilState(dsDesc);
	if (!m_gfxBackend->CreateDepthStencilState(dss))
	{
		handle = { m_depthStencilStateHandles.Release(handle.idx) };
		delete dss;
		return handle;
	}
	ASSERT(m_resources[handle.type_id][handle.idx] == nullptr, "Resource is not released properly!");
	m_resources[handle.type_id][handle.idx] = dss; \
		return handle;
}

RenderTargetHandle Renderer::CreateRenderTarget(const gfx::RenderTargetDesc& desc)
{
	RenderTargetHandle handle = { m_rtHandles.Allocate() };
	RenderTarget* rt = RenderTarget::Create(desc);
	if (!m_gfxBackend->CreateRenderTarget(rt, desc.createMatchingDepthView))
	{
		handle = { m_rtHandles.Release(handle.idx) };
		delete rt;
		return handle;
	}
	ASSERT(m_resources[handle.type_id][handle.idx] == nullptr, "Resource is not released properly!");
	m_resources[handle.type_id][handle.idx] = rt; \
		return handle;
}

BufferHandle Renderer::CreateBuffer(const gfx::BufferDesc& bufferDesc)
{
	BufferHandle handle = { m_bufferHandles.Allocate() };
	Buffer* buffer = new Buffer(bufferDesc);
	if (!m_gfxBackend->CreateBuffer(buffer))
	{
		handle = { m_bufferHandles.Release(handle.idx) };
		delete buffer;
		return handle;
	}
	ASSERT(m_resources[handle.type_id][handle.idx] == nullptr,
		   "Resource is not released properly!");
	m_resources[handle.type_id][handle.idx] = buffer;
	return handle;
}

Texture* Renderer::CreateTexture(const gfx::TextureDesc& desc)
{
	Texture* texture = new Texture(desc);
	if (!m_gfxBackend->CreateTexture(texture))
	{
		delete texture;
		return nullptr;
	}
	return texture;
}

ShaderResourceHandle Renderer::CreateShaderResource(Texture* res)
{
	/*ShaderResourceHandle handle = { handleRegistry.Allocate() }; \
		resourceName* rs = new resourceName(params); \
		if (!m_gfxBackend->Create##resourceName(rs))\
		{\
			handle = { handleRegistry.Release(handle.idx) }; \
			delete rs; \
			return handle; \
		}\
			ASSERT(m_resources[handle.type_id][handle.idx] == nullptr, "Resource is not released properly!"); \
			m_resources[handle.type_id][handle.idx] = rs; \
			return handle; \*/
	return {};
}

void Renderer::SetPrimitiveTopology(gfx::TORC_GFX_PRIMITIVE_TOPOLOGY topology)
{
	m_gfxBackend->SetPrimitiveTopology(topology);
}

void Renderer::SetBlendState(BlendStateHandle handle, const float blendFactor[4],
							 uint32_t blendMask)
{
	ASSERT(IsValid(handle), "Invalid BlendStateHandle %s", __FUNC__);
	BlendState* rt = (BlendState*)m_resources[handle.type_id][handle.idx];
	m_gfxBackend->SetBlendState(rt, blendFactor, blendMask);
}

void Renderer::SetBlendState(BlendStateHandle handle)
{
	ASSERT(IsValid(handle), "Invalid BlendStateHandle %s", __FUNC__);
	BlendState* rt = (BlendState*)m_resources[handle.type_id][handle.idx];
	m_gfxBackend->SetBlendState(rt);
}

void Renderer::SetBlendState(BlendState* bs, const float blendFactor[4], uint32_t blendMask)
{
	ASSERT(bs != nullptr, "BlendState object is NULL %s", __FUNC__);
	m_gfxBackend->SetBlendState(bs, blendFactor, blendMask);
}

void Renderer::SetBlendState(BlendState* bs)
{
	ASSERT(bs != nullptr, "BlendState object is NULL %s", __FUNC__);
	m_gfxBackend->SetBlendState(bs);
}

void Renderer::SetRenderTarget(RenderTargetHandle rtHandle)
{
	ASSERT(IsValid(rtHandle), "Invalid Render Target Handle");
	RenderTarget* rt = (RenderTarget*)m_resources[rtHandle.type_id][rtHandle.idx];
	m_gfxBackend->SetRenderTarget(rt);
}

void Renderer::SetRenderTarget(RenderTargetHandle rtHandle, DepthStencilStateHandle dssHandle)
{
	ASSERT(IsValid(rtHandle), "Invalid RenderTargetHandle %s", __FUNC__);
	ASSERT(IsValid(dssHandle), "Invalid DepthStencilStateHandle %s", __FUNC__);

	RenderTarget* rt = (RenderTarget*)m_resources[rtHandle.type_id][rtHandle.idx];
	DepthStencilState* dss = (DepthStencilState*)m_resources[dssHandle.type_id][dssHandle.idx];
	m_gfxBackend->SetRenderTarget(rt, dss);
}

void Renderer::SetRenderTarget(RenderTarget* rt)
{
	ASSERT(rt != nullptr, "RenderTarget object is NULL %s", __FUNC__);
	m_gfxBackend->SetRenderTarget(rt);
}

void Renderer::SetRenderTarget(RenderTarget* rt, DepthStencilState* dss)
{
	ASSERT(rt != nullptr, "RenderTarget object is NULL %s", __FUNC__);
	ASSERT(dss != nullptr, "DepthStencilState object is NULL %s", __FUNC__);
	m_gfxBackend->SetRenderTarget(rt, dss);
}

void Renderer::SetBuffer(BufferHandle bufferHandle)
{
	ASSERT(IsValid(bufferHandle), "Invalid BufferHandle %s", __FUNC__);
	Buffer* buffer = (Buffer*)m_resources[bufferHandle.type_id][bufferHandle.idx];
	m_gfxBackend->SetBuffer(buffer);
}

void Renderer::SetBuffer(Buffer* buffer)
{
	ASSERT(buffer != nullptr, "Buffer object is NULL %s", __FUNC__);
	m_gfxBackend->SetBuffer(buffer);
}

void Renderer::SetShader(ShaderHandle shaderHandle)
{
	ASSERT(IsValid(shaderHandle), "Invalid ShaderHandle %s", __FUNC__);
	Shader* buffer = (Shader*)m_resources[shaderHandle.type_id][shaderHandle.idx];
	m_gfxBackend->SetShader(buffer);
}

void Renderer::SetShader(Shader* shader)
{
	ASSERT(shader != nullptr, "Shader object is NULL %s", __FUNC__);
	m_gfxBackend->SetShader(shader);
}

void Renderer::SetViewport(gfx::ViewportDesc viewportDesc)
{
	m_gfxBackend->SetViewport(viewportDesc);
}

void Renderer::BindShaderResource(ShaderResourceHandle handle,
								  ShaderHandle shaderHandle,
								  uint32 startSlot,
								  uint32 numViews)
{
	m_gfxBackend->BindShaderResource(handle, shaderHandle, startSlot, numViews);
}

void* Renderer::GetShaderResource(ShaderResourceHandle srHandle)
{
	return m_gfxBackend->GetShaderResource(srHandle);
}

void Renderer::ResetRenderTarget(bool useMainDepth)
{
	m_gfxBackend->SetMainRenderTarget(useMainDepth);
}

IGPUResource* Renderer::GetResourceByHandle(ResourceHandle handle)
{
	return m_resources[handle.id][handle.idx];
}

void Renderer::ReleaseInternalResource(IGPUResource* resource)
{
	m_gfxBackend->ReleaseResource(resource);
}

void Renderer::ReleaseInternalResourceByHandle(ResourceHandle handle)
{
	if (IsValid(handle))
	{
		auto resVec = m_resources.find(handle.id);
		if (resVec != m_resources.end())
		{
			IGPUResource* res = resVec->second[handle.idx];
			if (res)
			{
				m_gfxBackend->ReleaseResource(res);
			}
		}
	}
}

ShaderHandle Renderer::CompileShader(const char* name,
									 int32 shaderType,
									 const char* entryPoint)
{
	ShaderHandle handle = { m_shaderHandles.Allocate() };
	Shader* shader = new Shader();
	if (!m_gfxBackend->CompileShader(shader, name, (Shader::Type)shaderType, entryPoint))
	{
		handle = { m_shaderHandles.Release(handle.idx) };
		delete shader;
		return handle;
	}

	ASSERT(m_resources[handle.type_id][handle.idx] == nullptr,
		   "Resource is not released properly!");
	m_resources[handle.type_id][handle.idx] = shader;
	return handle;
}