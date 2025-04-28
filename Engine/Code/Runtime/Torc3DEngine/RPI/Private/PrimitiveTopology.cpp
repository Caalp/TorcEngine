#include "PrimitiveTopology.h"
#include "RDI/RDIShared/ITorcGfxBackend.h"

PrimitiveTopology::PrimitiveTopology(gfx::TORC_GFX_PRIMITIVE_TOPOLOGY topology)
	: m_topology(topology)
{}

void* PrimitiveTopology::GetDesc() const
{
	return (void*)&m_topology;
}

void PrimitiveTopology::Bind()
{
	m_gfx->BindPrimitiveTopology(this);
}