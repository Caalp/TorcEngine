#pragma once
#include "Renderer/IGPUResource.h"

class Texture : public IGPUResource
{
public:
	Texture(const gfx::TextureDesc& desc);
	virtual void* GetDesc() const override;
	virtual void Bind() override;
protected:
	uint32 m_slot;
	gfx::TextureDesc m_desc;
};