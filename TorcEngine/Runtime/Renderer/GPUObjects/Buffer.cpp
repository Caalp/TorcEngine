#include "pch.h"
#include "Buffer.h"

Buffer::Buffer(const gfx::BufferDesc& desc)
	: m_desc(desc)
{}

Buffer::~Buffer()
{
    LOG_INFO(LogChannel::LC_Renderer, "~Buffer() Called");
}

void* Buffer::GetDesc() const
{
    return (void*)&m_desc;
}

void Buffer::Bind()
{
}