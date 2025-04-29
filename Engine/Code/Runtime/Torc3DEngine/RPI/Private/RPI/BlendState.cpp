#include "RPI/BlendState.h"

BlendState::BlendState(const Torc::RHI::BlendDescription& desc)
	: m_desc(desc)
{
	//m_resourceID = ResourceDescID::GetID(desc);
}

void* BlendState::GetDesc() const
{
	return (void*)&m_desc;
}

void BlendState::Bind()
{
}