#pragma once
#include "RPI/IGPUResource.h"

class RasterizerState : public IGPUResource
{
public:
	enum RasterizerType
	{
		Default,
		NoCull,
		CullClockwise,
		Wireframe
	};
	RasterizerState(const gfx::RasterizerDesc& desc);
	virtual void* GetDesc() const override;
	virtual void Bind() override;
private:
	gfx::RasterizerDesc m_desc;
	RasterizerType m_rsType;
};