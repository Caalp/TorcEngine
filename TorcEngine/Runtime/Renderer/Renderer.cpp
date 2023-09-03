#include "pch.h"

#include "Renderer/Renderer.h"
#include "TorcGfx/ITorcGfxBackend.h"
#include "Core/Plugins/Plugin.h"
#include "Core/Plugins/PluginLoader.h"

using namespace Torc;

namespace
{
	static Renderer* s_renderer = nullptr;
}

Renderer::Renderer(gfx::GfxBackendParams& gfxParams)
{
	PluginLoader* loader = PluginLoader::GetInstance();
	Plugin* plugin = loader->GetPlugin(gfxParams.backendDLLName);
	if (plugin == nullptr)
	{
		TE_ERROR("Pluging is not loaded correctly\n")
	}
	plugin->CallInitialize((void**)&m_gfxBackend);

	//gfxParams.gfxDevice = &m_gfxDevice;
	//gfxParams.gfxContext = &m_gfxContext;
	//gfxParams.gfxSwapChain = &m_gfxSwapChain;

	m_isInitialized = m_gfxBackend->InitializeGfxBackend(gfxParams);
}

Torc::Renderer::~Renderer()
{
	m_gfxBackend->ReleaseGfxBackend();
}

bool Renderer::Initialize(gfx::GfxBackendParams& gfxParams)
{
	if (s_renderer == nullptr)
	{
		s_renderer = new Renderer(gfxParams);
	}
	
	return s_renderer->m_isInitialized;
}

Renderer* Renderer::GetInstance()
{
	return s_renderer;
}

void Renderer::Release()
{
	delete s_renderer;
}

BlendStateHandle Renderer::CreateBlendState(const gfx::BlendDesc& params)
{
	BlendStateHandle handle = { m_blendStateHandles.Allocate() };
	m_gfxBackend->CreateBlendState(handle, params);
	return handle;
}

RasterizerStateHandle Torc::Renderer::CreateRasterizerState(const gfx::RasterizerDesc& params)
{
	RasterizerStateHandle handle = { m_rasterizerStateHandles.Allocate() };
	m_gfxBackend->CreateRasterizerState(handle, params);
	return handle;
}

SamplerStateHandle Torc::Renderer::CreateSamplerState(const gfx::SamplerDesc& params)
{
	SamplerStateHandle handle = { m_samplerStateHandles.Allocate() };
	m_gfxBackend->CreateSamplerState(handle, params);
	return handle;
}

DepthStencilStateHandle Torc::Renderer::CreateDepthStencilState(const gfx::DepthStencilDesc& params)
{
	DepthStencilStateHandle handle = { m_depthStencilStateHandles.Allocate() };
	//m_gfxBackend->CreateDepthStencilState(handle, params);
	return handle;
}

void Torc::Renderer::SetBlendState(BlendStateHandle handle, const float blendFactor[4], uint32_t blendMask)
{

}