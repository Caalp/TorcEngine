#include "DepthStencilState.h"
#include "RDI/RDIShared/ITorcGfxBackend.h"

DepthStencilState::DepthStencilState(const gfx::DepthStencilDesc& dssDesc)
	: m_desc(dssDesc)
{
	m_resourceID = ResourceDescID::GetID(dssDesc);
}

void* DepthStencilState::GetDesc() const
{
	return (void*)&m_desc;
}

void DepthStencilState::Bind()
{
	m_gfx->BindDepthStencilState(this, 0);
}