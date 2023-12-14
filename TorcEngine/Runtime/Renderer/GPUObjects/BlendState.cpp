#include "pch.h"
#include "BlendState.h"
#include "Renderer/Renderer.h"

BlendState::BlendState(const gfx::BlendDesc& desc)
	: m_desc(desc)
{}

void* BlendState::GetDesc() const
{
	return (void*)&m_desc;
}

void BlendState::Bind()
{
}