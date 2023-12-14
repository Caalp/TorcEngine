#include "pch.h"
#include "Texture.h"

Texture::Texture(const gfx::TextureDesc& desc)
	: m_desc(desc)
{}

void* Texture::GetDesc() const
{
	return (void*)&m_desc;
}

void Texture::Bind()
{}