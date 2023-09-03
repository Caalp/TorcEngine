#include "pch.h"
#include "StackAllocator.h"

StackAllocator::~StackAllocator()
{
	Clear();
	delete[] m_top;
}

void StackAllocator::Allocate(uint32_t sizeInBytes)
{
	m_top = new uint8_t[sizeInBytes];
	m_inUse = 0;
	m_totalSize = sizeInBytes;
}

void StackAllocator::Clear()
{
	// roll back m_top back to begining of the memory region
	m_top -= m_inUse;
	m_inUse = 0;
}

uint8_t* StackAllocator::GetMarker() const
{
	return m_top - m_headerSizeInBytes;
}

void StackAllocator::Resize(uint32_t multiplier)
{

}
