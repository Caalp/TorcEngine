#pragma once
#include "Renderer/IGPUResource.h"

class BlendState : public IGPUResource
{
public:
	enum BlendType
	{
		Default,
		Transparent,
		AlphaToCoverage,
		NoRenderTargetWrite,
		Additive
	};

	BlendState(const gfx::BlendDesc& desc);
	virtual void* GetDesc() const override;
	virtual void Bind() override;
private:
	gfx::BlendDesc m_desc;
};