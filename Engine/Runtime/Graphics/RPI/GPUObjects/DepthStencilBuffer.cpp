#include "DepthStencilBuffer.h"
#include "RDI/RDIShared/ITorcGfxBackend.h"

DepthStencilBuffer::DepthStencilBuffer(const gfx::TextureDesc& desc)
	: m_desc(desc)
{}

void* DepthStencilBuffer::GetDesc() const
{
	return nullptr;
}

void DepthStencilBuffer::Bind()
{
	//m_gfx->BindDepthBuffer(this);
}

OutputOnlyDepthBuffer::OutputOnlyDepthBuffer(const gfx::TextureDesc& desc)
	: DepthStencilBuffer(desc)
{
}

OutputOnlyDepthBuffer::OutputOnlyDepthBuffer(DepthStencilBuffer* buffer)
	: DepthStencilBuffer({})
{
}

ShaderResourceDepthBuffer::ShaderResourceDepthBuffer(const gfx::TextureDesc& desc)
	: DepthStencilBuffer(desc)
{
}