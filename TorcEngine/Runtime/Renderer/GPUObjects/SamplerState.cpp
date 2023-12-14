#include "pch.h"
#include "SamplerState.h"

SamplerState::SamplerState(const gfx::SamplerDesc& desc)
	: m_desc(desc)
{}

void* SamplerState::GetDesc() const
{
	return (void*)&m_desc;
}

void SamplerState::Bind()
{
	LOG_INFO(LogChannel::LC_Renderer, "SamplerState::Bind");
}