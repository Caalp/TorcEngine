#pragma once
#include "Renderer/IGPUResource.h"

class DepthStencilBuffer : public IGPUResource
{
public:
	DepthStencilBuffer(const gfx::TextureDesc& desc);
	virtual void* GetDesc() const override;
	virtual void Bind() override;
private:
	gfx::TextureDesc m_desc;
};