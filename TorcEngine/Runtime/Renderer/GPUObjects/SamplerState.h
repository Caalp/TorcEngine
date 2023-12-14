#pragma once
#include "Renderer/IGPUResource.h"

class SamplerState : public IGPUResource
{
public:
	SamplerState(const gfx::SamplerDesc& desc);
	virtual void* GetDesc() const override;
	virtual void Bind() override;
private:
	gfx::SamplerDesc m_desc;
};