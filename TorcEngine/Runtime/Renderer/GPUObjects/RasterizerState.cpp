#include "pch.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState(const gfx::RasterizerDesc& desc)
	: m_desc(desc)
{}

void* RasterizerState::GetDesc() const
{
	return (void*)&m_desc;
}

void RasterizerState::Bind()
{
	LOG_INFO(LogChannel::LC_Renderer, "RasterizerState::Bind");
}