#include "pch.h"
#include "PrimitiveTopology.h"

PrimitiveTopology::PrimitiveTopology(gfx::TORC_GFX_PRIMITIVE_TOPOLOGY topology)
	: m_topology(topology)
{}

void* PrimitiveTopology::GetDesc() const
{
	return (void*)&m_topology;
}

void PrimitiveTopology::Bind()
{
	LOG_INFO(LogChannel::LC_Renderer, "PrimitiveTopology::Bind");
}