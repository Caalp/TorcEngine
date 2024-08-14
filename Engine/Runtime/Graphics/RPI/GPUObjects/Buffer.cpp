#include "Buffer.h"
#include "RDI/RDIShared/ITorcGfxBackend.h"

#include "Core/Logging/Logger.h"

Buffer::Buffer(const gfx::BufferDesc& desc)
	: m_desc(desc)
{}

Buffer::~Buffer()
{
    TE_Info(LogChannel::LC_Renderer, "~Buffer() Called");
}

void* Buffer::GetDesc() const
{
    return (void*)&m_desc;
}

void Buffer::Bind()
{
    m_gfx->BindBuffer(this);
}

Buffer* Buffer::CreateBuffer(const gfx::BufferDesc& desc)
{
    Buffer* temp = new Buffer(desc);
    if (!gEnv->gfx->CreateBuffer(temp))
    {
        delete temp;
        return nullptr;
    }
    return temp;
}
