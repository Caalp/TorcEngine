#include "BlendState.h"
#include "RPI/Renderer.h"

BlendState::BlendState(const gfx::BlendDesc& desc)
	: m_desc(desc)
{
	m_resourceID = ResourceDescID::GetID(desc);
}

void* BlendState::GetDesc() const
{
	return (void*)&m_desc;
}

void BlendState::Bind()
{
	m_gfx->BindBlendState(this);
}