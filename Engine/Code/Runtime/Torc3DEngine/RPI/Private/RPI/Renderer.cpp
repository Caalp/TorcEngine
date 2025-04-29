#include <wrl.h>
#include <WinUser.h>
#include <debugapi.h>

#include "Renderer.h"
#include <Core/Module/Module.h>
#include <Core/Module/ModuleManager.h>

#include "BlendState.h"
#include "RasterizerState.h"
#include "DepthStencilState.h"
#include "SamplerState.h"
#include "Buffer.h"
#include "RenderTarget.h"
#include "Shader.h"
#include "Texture.h"

#include <Core/Logging/Logger.h>


//static const std::map<ResourceDescID::ResourceType, size_t> s_descIDToTypeID = 
//{ 
//	{ResourceDescID::ResourceType::DSS, DepthStencilStateHandle::type_id},
//	{ResourceDescID::ResourceType::RS, RasterizerStateHandle::type_id},
//	{ResourceDescID::ResourceType::SS, SamplerStateHandle::type_id},
//	{ResourceDescID::ResourceType::BS, BlendStateHandle::type_id},
//};
//
//#define DEFINE_RESOURCE_CREATE_FUNCTION(resourceName, descriptor, handleRegistry)\
//	resourceName##Handle Renderer::Create##resourceName(const gfx::descriptor& params)\
//	{\
//		ResourceDescID::IDType descID = ResourceDescID::GetID(params);\
//		if (m_descMap.count(descID))\
//		{\
//			const ResourceDescID::ResourceType resType = ResourceDescID::GetResourceType(descID);\
//			const size_t typeID = s_descIDToTypeID.at(resType);\
//			for (int i = 0; i < m_resources[typeID].size(); ++i)\
//			{\
//				auto res = m_resources[typeID][i];\
//				if (res != nullptr && descID == res->m_resourceID)\
//				{\
//					m_descMap[descID]++;\
//					return {(uint32)i};\
//				}\
//			}\
//		}\
//		resourceName##Handle handle = { handleRegistry.Allocate() };\
//		resourceName* rs = new resourceName(params);\
//		if (!m_gfxBackend->Create##resourceName(rs))\
//		{\
//			handle = { handleRegistry.Release(handle.idx) };\
//			delete rs;\
//			return handle;\
//		}\
//		ASSERT(m_resources[handle.type_id][handle.idx] == nullptr, "Resource is not released properly!");\
//		m_resources[handle.type_id][handle.idx] = rs;\
//		m_descMap[descID] = 1;\
//		return handle;\
//	}\
//
//
//DEFINE_RESOURCE_CREATE_FUNCTION(BlendState, BlendDesc, m_blendStateHandles)
//DEFINE_RESOURCE_CREATE_FUNCTION(RasterizerState, RasterizerDesc, m_rasterizerStateHandles)
//DEFINE_RESOURCE_CREATE_FUNCTION(SamplerState, SamplerDesc, m_samplerStateHandles)
//DEFINE_RESOURCE_CREATE_FUNCTION(DepthStencilState, DepthStencilDesc, m_depthStencilStateHandles)
//
//#undef DEFINE_RESOURCE_CREATE_FUNCTION
//
//Renderer::Renderer()
//	: m_isInitialized(false)
//	, m_gfxBackend(nullptr)
//{
//	m_resources[BlendStateHandle::type_id] = std::vector<IGPUResource*>(MAX_HANDLE_COUNT_BLEND_STATE, nullptr);
//	m_resources[RasterizerStateHandle::type_id] = std::vector<IGPUResource*>(MAX_HANDLE_COUNT_RASTERIZER_STATE, nullptr);
//	m_resources[SamplerStateHandle::type_id] = std::vector<IGPUResource*>(MAX_HANDLE_COUNT_SAMPLER_STATE, nullptr);
//	m_resources[DepthStencilStateHandle::type_id] = std::vector<IGPUResource*>(MAX_HANDLE_COUNT_DEPTH_STENCIL_STATE, nullptr);
//	m_resources[BufferHandle::type_id] = std::vector<IGPUResource*>(MAX_HANDLE_COUNT_BUFFERS, nullptr);
//	m_resources[ShaderHandle::type_id] = std::vector<IGPUResource*>(MAX_HANDLE_COUNT_SHADER, nullptr);
//	m_resources[RenderTargetHandle::type_id] = std::vector<IGPUResource*>(MAX_HANDLE_COUNT_RT, nullptr);
//	m_resources[ShaderResourceHandle::type_id] = std::vector<IGPUResource*>(MAX_HANDLE_COUNT_RT, nullptr);
//}
//
//Renderer::~Renderer()
//{
//}
//
//bool Renderer::Initialize(SystemGlobalEnvironment& env, gfx::GfxBackendParams& params)
//{
//	PluginLoader* loader = gEnv->pluginLoader;
//	if (loader)
//	{
//		Plugin* plugin = loader->GetPlugin(params.backendDLLName);
//		if (plugin == nullptr)
//		{
//			TE_Error(LogChannel::LC_Platform, "Pluging is not loaded correctly\n")
//		}
//		plugin->CallInitialize((void**)&m_gfxBackend);
//
//		m_isInitialized = m_gfxBackend->Initialize(env, params);
//	}
//
//	env.rr = this;
//	env.gfx = m_gfxBackend;
//	return m_isInitialized;
//}
//
//void Renderer::Release()
//{
//	// before releasing backend release resources we have
//	for (auto& [key, val] : m_resources)
//	{
//		for (IGPUResource* res : val)
//		{
//			if (res)
//			{
//				delete res;
//			}
//		}
//		val.clear();
//	}
//	m_resources.clear();
//
//	if (m_gfxBackend)
//		m_gfxBackend->Release();
//}
//
//void Renderer::OnWindowResize(uint32 width, uint32 height)
//{
//}
//
//void Renderer::Update()
//{
//}
//
//void Renderer::BeginFrame()
//{
//	IEditor* editor = gEnv->editor;
//	if (editor)
//	{
//		editor->OnFrameBegin();
//	}
//}
//
//void Renderer::EndFrame()
//{
//	IEditor* editor = gEnv->editor;
//	if (editor)
//	{
//		editor->OnFrameEnd();
//	}
//
//	m_gfxBackend->EndFrame();
//}
//
//void Renderer::ClearBackBuffer(math::Vec4f color)
//{
//	m_gfxBackend->ClearBackBuffer(color.x, color.y, color.z, color.w);
//}
//
//void Renderer::ClearRenderTarget(RenderTarget* rt, math::Vec4f color)
//{
//	m_gfxBackend->ClearRenderTarget(rt, color.x, color.y, color.z, color.w);
//}
//
//void Renderer::ClearDepthStencil(DepthStencilStateHandle dssHandle,
//								 bool clearDepth,
//								 bool clearStencil,
//								 float depthValueClearTo,
//								 uint8 stencilValueClearTo)
//{
//	DepthStencilState* dss = (DepthStencilState*)m_resources[dssHandle.type_id][dssHandle.idx];
//	m_gfxBackend->ClearDepthStencil(dss, clearDepth,
//									clearStencil, depthValueClearTo, stencilValueClearTo);
//}
//
//void Renderer::ClearDepthStencil(void* dss, bool clearDepth, bool clearStencil, float depthValueClearTo, uint8 stencilValueClearTo)
//{
//	ASSERT(dss != nullptr, "DepthStencilState object is NULL %s", __FUNC__);
//	m_gfxBackend->ClearDepthStencil(dss, clearDepth,
//									clearStencil, depthValueClearTo, stencilValueClearTo);
//}
//
//DepthStencilStateHandle Renderer::CreateDepthStencilState(const gfx::DepthStencilDesc& dsDesc, const gfx::TextureDesc& texDesc)
//{
//	DepthStencilStateHandle handle = { m_depthStencilStateHandles.Allocate() };
//	DepthStencilState* dss = new DepthStencilState(dsDesc);
//	if (!m_gfxBackend->CreateDepthStencilState(dss))
//	{
//		handle = { m_depthStencilStateHandles.Release(handle.idx) };
//		delete dss;
//		return handle;
//	}
//	ASSERT(m_resources[handle.type_id][handle.idx] == nullptr, "Resource is not released properly!");
//	m_resources[handle.type_id][handle.idx] = dss; \
//		return handle;
//}
//
//RenderTargetHandle Renderer::CreateRenderTarget(const gfx::RenderTargetDesc& desc)
//{
//	RenderTargetHandle handle = { m_rtHandles.Allocate() };
//	RenderTarget* rt = RenderTarget::Create(desc);
//	if (!m_gfxBackend->CreateRenderTarget(rt, desc.createMatchingDepthView))
//	{
//		handle = { m_rtHandles.Release(handle.idx) };
//		delete rt;
//		return handle;
//	}
//	ASSERT(m_resources[handle.type_id][handle.idx] == nullptr, "Resource is not released properly!");
//	m_resources[handle.type_id][handle.idx] = rt;\
//		return handle;
//}
//
//BufferHandle Renderer::CreateBuffer(const gfx::BufferDesc& bufferDesc)
//{
//	BufferHandle handle = { m_bufferHandles.Allocate() };
//	Buffer* buffer = new Buffer(bufferDesc);
//	if (!m_gfxBackend->CreateBuffer(buffer))
//	{
//		handle = { m_bufferHandles.Release(handle.idx) };
//		delete buffer;
//		return handle;
//	}
//	ASSERT(m_resources[handle.type_id][handle.idx] == nullptr,
//		   "Resource is not released properly!");
//	m_resources[handle.type_id][handle.idx] = buffer;
//	return handle;
//}
//
//Texture* Renderer::CreateTexture(const gfx::TextureDesc& desc)
//{
//	Texture* texture = new Texture(desc);
//	if (!m_gfxBackend->CreateTexture(texture))
//	{
//		delete texture;
//		return nullptr;
//	}
//	return texture;
//}
//
//ShaderResourceHandle Renderer::CreateShaderResource(Texture* res)
//{
//	/*ShaderResourceHandle handle = { handleRegistry.Allocate() }; \
//		resourceName* rs = new resourceName(params); \
//		if (!m_gfxBackend->Create##resourceName(rs))\
//		{\
//			handle = { handleRegistry.Release(handle.idx) }; \
//			delete rs; \
//			return handle; \
//		}\
//			ASSERT(m_resources[handle.type_id][handle.idx] == nullptr, "Resource is not released properly!"); \
//			m_resources[handle.type_id][handle.idx] = rs; \
//			return handle; \*/
//	return {};
//}
//
//void Renderer::BindPrimitiveTopology(gfx::TORC_GFX_PRIMITIVE_TOPOLOGY topology)
//{
//	m_gfxBackend->BindPrimitiveTopology(topology);
//}
//
//void Renderer::BindBlendState(BlendStateHandle handle, const float blendFactor[4],
//							 uint32_t blendMask)
//{
//	ASSERT(IsValid(handle), "Invalid BlendStateHandle %s", __FUNC__);
//	BlendState* rt = (BlendState*)m_resources[handle.type_id][handle.idx];
//	m_gfxBackend->BindBlendState(rt, blendFactor, blendMask);
//}
//
//void Renderer::BindBlendState(BlendStateHandle handle)
//{
//	ASSERT(IsValid(handle), "Invalid BlendStateHandle %s", __FUNC__);
//	BlendState* rt = (BlendState*)m_resources[handle.type_id][handle.idx];
//	m_gfxBackend->BindBlendState(rt);
//}
//
//void Renderer::BindBlendState(BlendState* bs, const float blendFactor[4], uint32_t blendMask)
//{
//	ASSERT(bs != nullptr, "BlendState object is NULL %s", __FUNC__);
//	m_gfxBackend->BindBlendState(bs, blendFactor, blendMask);
//}
//
//void Renderer::BindBlendState(BlendState* bs)
//{
//	ASSERT(bs != nullptr, "BlendState object is NULL %s", __FUNC__);
//	m_gfxBackend->BindBlendState(bs);
//}
//
//void Renderer::BindRenderTarget(RenderTargetHandle rtHandle)
//{
//	ASSERT(IsValid(rtHandle), "Invalid Render Target Handle");
//	RenderTarget* rt = (RenderTarget*)m_resources[rtHandle.type_id][rtHandle.idx];
//	m_gfxBackend->BindRenderTarget(rt);
//}
//
//void Renderer::BindRenderTarget(RenderTargetHandle rtHandle, DepthStencilStateHandle dssHandle)
//{
//	ASSERT(IsValid(rtHandle), "Invalid RenderTargetHandle %s", __FUNC__);
//	ASSERT(IsValid(dssHandle), "Invalid DepthStencilStateHandle %s", __FUNC__);
//
//	RenderTarget* rt = (RenderTarget*)m_resources[rtHandle.type_id][rtHandle.idx];
//	DepthStencilState* dss = (DepthStencilState*)m_resources[dssHandle.type_id][dssHandle.idx];
//	m_gfxBackend->BindRenderTarget(rt, dss);
//}
//
//void Renderer::BindRenderTarget(RenderTarget* rt)
//{
//	ASSERT(rt != nullptr, "RenderTarget object is NULL %s", __FUNC__);
//	m_gfxBackend->BindRenderTarget(rt);
//}
//
//void Renderer::BindRenderTarget(RenderTarget* rt, DepthStencilState* dss)
//{
//	ASSERT(rt != nullptr, "RenderTarget object is NULL %s", __FUNC__);
//	ASSERT(dss != nullptr, "DepthStencilState object is NULL %s", __FUNC__);
//	m_gfxBackend->BindRenderTarget(rt, dss);
//}
//
//void Renderer::BindBuffer(BufferHandle bufferHandle)
//{
//	ASSERT(IsValid(bufferHandle), "Invalid BufferHandle %s", __FUNC__);
//	Buffer* buffer = (Buffer*)m_resources[bufferHandle.type_id][bufferHandle.idx];
//	m_gfxBackend->BindBuffer(buffer);
//}
//
//void Renderer::BindBuffer(Buffer* buffer)
//{
//	ASSERT(buffer != nullptr, "Buffer object is NULL %s", __FUNC__);
//	m_gfxBackend->BindBuffer(buffer);
//}
//
//void Renderer::BindShader(ShaderHandle shaderHandle)
//{
//	ASSERT(IsValid(shaderHandle), "Invalid ShaderHandle %s", __FUNC__);
//	Shader* buffer = (Shader*)m_resources[shaderHandle.type_id][shaderHandle.idx];
//	m_gfxBackend->BindShader(buffer);
//}
//
//void Renderer::BindShader(Shader* shader)
//{
//	ASSERT(shader != nullptr, "Shader object is NULL %s", __FUNC__);
//	m_gfxBackend->BindShader(shader);
//}
//
//void Renderer::BindViewport(gfx::ViewportDesc viewportDesc)
//{
//	m_gfxBackend->BindViewport(viewportDesc);
//}
//
//void Renderer::BindShaderResource(ShaderResourceHandle handle,
//								  ShaderHandle shaderHandle,
//								  uint32 startSlot,
//								  uint32 numViews)
//{
//	m_gfxBackend->BindShaderResource(handle, shaderHandle, startSlot, numViews);
//}
//
//void* Renderer::GetShaderResource(ShaderResourceHandle srHandle)
//{
//	return m_gfxBackend->GetShaderResource(srHandle);
//}
//
//void Renderer::ResetRenderTarget(bool useMainDepth)
//{
//	m_gfxBackend->BindMainRenderTarget(useMainDepth);
//}
//
//IGPUResource* Renderer::GetResourceByHandle(ResourceHandle handle)
//{
//	return m_resources[handle.id][handle.idx];
//}
//
//void Renderer::ReleaseInternalResource(IGPUResource* resource)
//{
//	m_gfxBackend->ReleaseResource(resource);
//}
//
//void Renderer::ReleaseInternalResourceByHandle(ResourceHandle handle)
//{
//	if (IsValid(handle))
//	{
//		auto resVec = m_resources.find(handle.id);
//		if (resVec != m_resources.end())
//		{
//			if (handle.idx < resVec->second.size() && resVec->second[handle.idx])
//			{
//				m_gfxBackend->ReleaseResource(resVec->second[handle.idx]);
//			}
//		}
//	}
//}
//
//ShaderHandle Renderer::CompileShader(const char* name,
//									 int32 shaderType,
//									 const char* entryPoint)
//{
//	ShaderHandle handle = { m_shaderHandles.Allocate() };
//	Shader* shader = new Shader();
//	if (!m_gfxBackend->CompileShader(shader, name, (Shader::Type)shaderType, entryPoint))
//	{
//		handle = { m_shaderHandles.Release(handle.idx) };
//		delete shader;
//		return handle;
//	}
//
//	ASSERT(m_resources[handle.type_id][handle.idx] == nullptr,
//		   "Resource is not released properly!");
//	m_resources[handle.type_id][handle.idx] = shader;
//	return handle;
//}
//
//void Renderer::DrawAABB(const AABB& box, math::Vec4f color)
//{
//
//	static bool init = false;
//	static BufferHandle vb;
//	static BufferHandle psCBHandle;
//
//	static int size = 6;
//	struct VertexData
//	{
//		DirectX::XMFLOAT3 pos;
//		DirectX::XMFLOAT3 color;
//	};
//
//	if (!init)
//	{
//		std::vector<VertexData> vertices(size);
//
//		/*vertices[0] = { { -5.0, -5.0, 0.0 }, {1.0f, 0.0f, 0.0f} };
//		vertices[1] = { { 0.0,  5.0, 0.0 } , {0.0f, 1.0f , 0.0f} };
//		vertices[2] = { { 5.0, -5.0, 0.0 } , {0.0f, 0.0f , 1.0f} };
//		vertices[3] = { { 10.0,  5.0, 0.0 } , {1.0f, 1.0f , 1.0f} };
//		vertices[4] = { { 15.0, -5.0, 0.0 } , {1.0f, 1.0f , 0.0f} };
//		vertices[5] = { { 20.0,  5.0, 0.0 } , {0.0f, 1.0f , 1.0f} };*/
//
//		vertices[0] = { { 5.5f, -0.5f, -0.5f }, {1.0f, 0.0f, 1.0f} };
//		vertices[1] = { { 5.5f, 0.5f, -0.5f }, {1.0f, 0.0f, 1.0f} };
//		vertices[2] = { { 10.5f, -0.5f, -0.5f }, {1.0f, 0.0f, 1.0f} };
//		vertices[3] = { { 10.5f, 0.5f, -0.5f }, {1.0f, 0.0f, 1.0f} };
//		vertices[4] = { { 10.5f, 0.5f, 0.5f }, {1.0f, 0.0f, 1.0f} };
//		vertices[5] = { { 10.5f, -0.5f, 0.5f }, {1.0f, 0.0f, 1.0f} };
//
//		//// bottom
//		//vertices[0] = { box.center.x - box.extends.x, box.center.y - box.extends.y, box.center.z - box.extends.z };
//		//vertices[1] = { box.center.x - box.extends.x, box.center.y - box.extends.y, box.center.z + box.extends.z };
//		//vertices[2] = { box.center.x + box.extends.x, box.center.y - box.extends.y, box.center.z + box.extends.z };
//		//vertices[3] = { box.center.x + box.extends.x, box.center.y - box.extends.y, box.center.z - box.extends.z };
//		//vertices[4] = { box.center.x - box.extends.x, box.center.y - box.extends.y, box.center.z - box.extends.z };
//
//		////front
//		//vertices[5] = { box.center.x - box.extends.x, box.center.y + box.extends.y, box.center.z - box.extends.z };
//		//vertices[6] = { box.center.x + box.extends.x, box.center.y + box.extends.y, box.center.z - box.extends.z };
//		//vertices[7] = { box.center.x + box.extends.x, box.center.y - box.extends.y, box.center.z - box.extends.z };
//
//		//// right
//		//vertices[8] = { box.center.x + box.extends.x, box.center.y + box.extends.y, box.center.z - box.extends.z };
//		//vertices[9] = { box.center.x + box.extends.x, box.center.y + box.extends.y, box.center.z + box.extends.z };
//		//vertices[10] = { box.center.x + box.extends.x, box.center.y - box.extends.y, box.center.z + box.extends.z };
//
//		//// back
//		//vertices[11] = { box.center.x + box.extends.x, box.center.y + box.extends.y, box.center.z + box.extends.z };
//		//vertices[12] = { box.center.x - box.extends.x, box.center.y + box.extends.y, box.center.z + box.extends.z };
//		//vertices[13] = { box.center.x - box.extends.x, box.center.y - box.extends.y, box.center.z + box.extends.z };
//
//		//// left
//		//vertices[14] = { box.center.x - box.extends.x, box.center.y + box.extends.y, box.center.z + box.extends.z };
//		//vertices[15] = { box.center.x - box.extends.x, box.center.y + box.extends.y, box.center.z - box.extends.z };
//
//		gfx::BufferDesc vbeDesc{};
//		vbeDesc.numBuffers = 1;
//		vbeDesc.startSlot = 0;
//		vbeDesc.stride = sizeof(VertexData);
//		vbeDesc.bindFlags = gfx::TORC_GFX_RESOURCE_BIND_FLAG::BIND_VERTEX_BUFFER;
//
//		gfx::SubResourceData initData{};
//		initData.sysMem = vertices.data();
//		initData.byteWidth = (uint32)vertices.size() * sizeof(VertexData);
//		initData.structureByteStride = (uint32)sizeof(VertexData);
//		vbeDesc.data = initData;
//
//		vb = CreateBuffer(vbeDesc);
//
//		gfx::BufferDesc cbd3Desc{};
//		cbd3Desc.usage = gfx::TORC_GFX_RESOURCE_USAGE::USAGE_GPU_READ;
//		cbd3Desc.cpuAccessFlags = gfx::TORC_GFX_CPU_ACCESS_FLAG::NO_ACCESS;
//		cbd3Desc.cbType = gfx::BufferDesc::ConstantBufferType::PS;
//		cbd3Desc.bindFlags = gfx::TORC_GFX_RESOURCE_BIND_FLAG::BIND_CONSTANT_BUFFER;
//		cbd3Desc.startSlot = 0;
//		cbd3Desc.numBuffers = 1;
//
//		gfx::SubResourceData InitData5{};
//		InitData5.sysMem = &color;
//		InitData5.byteWidth = 16;
//		InitData5.structureByteStride = 0u;
//		cbd3Desc.data = InitData5;
//
//		psCBHandle = CreateBuffer(cbd3Desc);
//
//
//		init = true;
//	}
//
//	BindPrimitiveTopology(gfx::TORC_GFX_PRIMITIVE_TOPOLOGY::PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//
//	BindBuffer(vb);
//	BindBuffer(psCBHandle);
//	m_gfxBackend->Draw(size, 0);
//}

