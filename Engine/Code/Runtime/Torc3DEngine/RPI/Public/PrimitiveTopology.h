#pragma once
#include "RPI/IGPUResource.h"

namespace gfx
{
	enum class TORC_GFX_PRIMITIVE_TOPOLOGY : uint8;
}

class PrimitiveTopology : public IGPUResource
{
public:
	PrimitiveTopology(gfx::TORC_GFX_PRIMITIVE_TOPOLOGY topology);
	virtual void* GetDesc() const override;
	virtual void Bind() override;
private:
	gfx::TORC_GFX_PRIMITIVE_TOPOLOGY m_topology;
};