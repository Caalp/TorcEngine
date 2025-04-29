#include "DepthStencilBuffer.h"

namespace RPI
{
	DepthStencilBuffer::DepthStencilBuffer(const Torc::RHI::ImageDescription& desc)
		: m_desc(desc)
	{
	}

	void* DepthStencilBuffer::GetDesc() const
	{
		return nullptr;
	}

	void DepthStencilBuffer::Bind()
	{
		//m_gfx->BindDepthBuffer(this);
	}

	OutputOnlyDepthBuffer::OutputOnlyDepthBuffer(const Torc::RHI::ImageDescription& desc)
		: DepthStencilBuffer(desc)
	{
	}

	OutputOnlyDepthBuffer::OutputOnlyDepthBuffer(DepthStencilBuffer* buffer)
		: DepthStencilBuffer({})
	{
	}

	ShaderResourceDepthBuffer::ShaderResourceDepthBuffer(const Torc::RHI::ImageDescription& desc)
		: DepthStencilBuffer(desc)
	{
	}
}
