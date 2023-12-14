#pragma once
#include "Renderer/IGPUResource.h"

class RasterizerState : public IGPUResource
{
public:
	enum RasterizerType
	{
		Default,
		NoCull,
		CullClockwise
	};
	RasterizerState(const gfx::RasterizerDesc& desc);
	virtual void* GetDesc() const override;
	virtual void Bind() override;
private:
	gfx::RasterizerDesc m_desc;
	RasterizerType m_rsType;
};