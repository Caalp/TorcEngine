#pragma once
#include "IGPUResource.h"

namespace RPI
{
	class DepthStencilBuffer : public IGPUResource
	{
	public:
		DepthStencilBuffer(const Torc::RHI::ImageDescription& desc);
		virtual void* GetDesc() const override;
		virtual void Bind() override;
	private:
		Torc::RHI::ImageDescription m_desc;
	};

	class OutputOnlyDepthBuffer : public DepthStencilBuffer
	{
	public:
		OutputOnlyDepthBuffer(const Torc::RHI::ImageDescription& desc);
		OutputOnlyDepthBuffer(DepthStencilBuffer* buffer);
	};

	class ShaderResourceDepthBuffer : public DepthStencilBuffer
	{
	public:
		ShaderResourceDepthBuffer(const Torc::RHI::ImageDescription& desc);
	};
}
