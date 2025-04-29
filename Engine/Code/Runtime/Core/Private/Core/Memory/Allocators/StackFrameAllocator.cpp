#include "Memory/Allocators/StackFrameAllocator.h"

StackFrameAllocator::~StackFrameAllocator()
{
	Clear();
	delete[] m_top;
}

void StackFrameAllocator::Allocate(uint32_t sizeInBytes)
{
	m_top = new uint8_t[sizeInBytes];
	m_inUse = 0;
	m_totalSize = sizeInBytes;
}

void StackFrameAllocator::Clear()
{
	// roll back m_top back to begining of the memory region
	m_top -= m_inUse;
	m_inUse = 0;
}

uint8_t* StackFrameAllocator::GetMarker() const
{
	return m_top - m_headerSizeInBytes;
}

void StackFrameAllocator::Resize(uint32_t multiplier)
{}