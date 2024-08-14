#pragma once
#include "RPI/IGPUResource.h"

class DepthStencilBuffer : public IGPUResource
{
public:
	DepthStencilBuffer(const gfx::TextureDesc& desc);
	virtual void* GetDesc() const override;
	virtual void Bind() override;
private:
	gfx::TextureDesc m_desc;
};

class OutputOnlyDepthBuffer : public DepthStencilBuffer
{
public:
	OutputOnlyDepthBuffer(const gfx::TextureDesc& desc);
	OutputOnlyDepthBuffer(DepthStencilBuffer* buffer);
};

class ShaderResourceDepthBuffer : public DepthStencilBuffer
{
public:
	ShaderResourceDepthBuffer(const gfx::TextureDesc& desc);
};
