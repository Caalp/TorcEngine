#include "RPI/Texture.h"

namespace RPI
{
	Texture::Texture(const Torc::RHI::ImageDescription& desc)
		: m_desc(desc)
	{
	}

	void* Texture::GetDesc() const
	{
		return (void*)&m_desc;
	}

	void Texture::Bind()
	{
	}
}
