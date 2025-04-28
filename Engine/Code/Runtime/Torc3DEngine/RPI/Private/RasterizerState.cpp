#include "RasterizerState.h"
#include "RDI/RDIShared/ITorcGfxBackend.h"

RasterizerState::RasterizerState(const gfx::RasterizerDesc& desc)
	: m_desc(desc)
{}

void* RasterizerState::GetDesc() const
{
	return (void*)&m_desc;
}

void RasterizerState::Bind()
{
	m_gfx->BindRasterizerState(this);
}