#include "pch.h"
#include "DepthStencilState.h"

DepthStencilState::DepthStencilState(const gfx::DepthStencilDesc& dssDesc)
	: m_desc(dssDesc)
{}

void* DepthStencilState::GetDesc() const
{
	return (void*)&m_desc;
}

void DepthStencilState::Bind()
{
	LOG_INFO(LogChannel::LC_Renderer, "DepthStencilState::Bind");
}