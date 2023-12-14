#pragma once
#include "Renderer/IGPUResource.h"

class DepthStencilState : public IGPUResource
{
public:
	enum DSSType
	{
		Default,
		Mirror,
		DrawReflection,
		NoDoubleBlend,
		NoDepthWrite,
		LessOrEqual
	};

	DepthStencilState(const gfx::DepthStencilDesc& dssDesc);
	virtual void* GetDesc() const override;
	virtual void Bind() override;
private:
	gfx::DepthStencilDesc m_desc;
};
