#include "pch.h"
#include "RenderTarget.h"
#include "Texture.h"
#include "Renderer/Renderer.h"
#include "Renderer/GPUObjects/DepthStencilBuffer.h"

RenderTarget* RenderTarget::Create(const gfx::RenderTargetDesc& desc)
{
	if (desc.textureDesc.bindFlags & gfx::TORC_GFX_RESOURCE_BIND_FLAG::BIND_SHADER_RESOURCE)
	{
		return new ShaderResourceRenderTarget(desc);
	}

	return new RenderTarget(desc);
}

RenderTarget::RenderTarget(const gfx::RenderTargetDesc& desc)
	: m_desc(desc)
{
	if (HasMatchingDepthStencilBuffer())
	{
		m_depthStencilBuffer = new DepthStencilBuffer(desc.textureDesc);
	}
}

RenderTarget::~RenderTarget()
{
	if (m_depthStencilBuffer)
	{
		delete m_depthStencilBuffer;
	}
}

void* RenderTarget::GetDesc() const
{
	return (void*)&m_desc;
}

void RenderTarget::Bind()
{
}

bool RenderTarget::IsShaderResource() const
{
	return (m_desc.textureDesc.bindFlags & gfx::TORC_GFX_RESOURCE_BIND_FLAG::BIND_SHADER_RESOURCE) > 0;
}

void RenderTarget::SetDepthStencilBuffer(DepthStencilBuffer* dssView)
{
	m_depthStencilBuffer = dssView;
}

DepthStencilBuffer* RenderTarget::GetDepthStencilBuffer()
{
	return m_depthStencilBuffer;
}

bool RenderTarget::HasMatchingDepthStencilBuffer() const
{
	return m_depthStencilBuffer != nullptr;
}

ShaderResourceRenderTarget::ShaderResourceRenderTarget(const gfx::RenderTargetDesc& desc)
	: RenderTarget(desc)
{
	m_texture = new Texture(desc.textureDesc);
}

ShaderResourceRenderTarget::~ShaderResourceRenderTarget()
{
	delete m_texture;
}

void ShaderResourceRenderTarget::BindAsShaderResource()
{
	m_texture->Bind();
}

void ShaderResourceRenderTarget::SetShaderResource(Texture* srvTex)
{
	if (m_texture)
	{
		delete m_texture;
	}
	m_texture = srvTex;
}