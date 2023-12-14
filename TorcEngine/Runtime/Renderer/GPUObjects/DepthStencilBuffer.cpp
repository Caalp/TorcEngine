#include "pch.h"
#include "DepthStencilBuffer.h"

DepthStencilBuffer::DepthStencilBuffer(const gfx::TextureDesc& desc)
	: m_desc(desc)
{}

void* DepthStencilBuffer::GetDesc() const
{
	return nullptr;
}

void DepthStencilBuffer::Bind()
{
	LOG_INFO(LogChannel::LC_Renderer, "DepthStencilBuffer::Bind");
}