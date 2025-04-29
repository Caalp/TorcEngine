#include "Buffer.h"

#include <Core/Logging/Logger.h>

namespace RPI
{
    Buffer::Buffer(const BufferDescriptor& desc)
        : m_descriptor(desc)
    {
    }

    Buffer::~Buffer()
    {
        TE_Info(LogChannel::LC_Renderer, "~Buffer() Called");
    }

    Buffer* Buffer::CreateBuffer(const BufferDescriptor& desc)
    {
        return nullptr;
    }
}
