#include "SamplerState.h"
#include "RDI/RDIShared/ITorcGfxBackend.h"

SamplerState::SamplerState(const gfx::SamplerDesc& desc)
	: m_desc(desc)
{
	m_resourceID = ResourceDescID::GetID(desc);
}

void* SamplerState::GetDesc() const
{
	return (void*)&m_desc;
}

void SamplerState::Bind()
{
	m_gfx->BindSamplerState(this);
}