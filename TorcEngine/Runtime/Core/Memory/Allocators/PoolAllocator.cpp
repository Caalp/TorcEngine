#include "pch.h"
#include "PoolAllocator.h"
#include "Core/Memory/Memory.h"

namespace
{
	void DebugPrintAddr(size_t sizeInBytes, size_t align, uint8_t* freeBlock)
	{
		for (int i = 0; i < (sizeInBytes / align); i++)
		{
			char cc[64];
			uint64_t addr = *(uint64_t*)(freeBlock + (align * i));
			sprintf_s(cc, "%d addr: %llx\n", i, addr);
			OutputDebugStringA(cc);
		}
	}
}

PoolAllocator::PoolAllocator() 
	: m_memory(nullptr)
	, m_freeBlock()
{}

PoolAllocator::~PoolAllocator()
{
	Memory::FreeAligned(m_memory);
}

void PoolAllocator::Allocate(size_t sizeInBytes, size_t align)
{
	assert(align % 64 == 0);
	if (!m_memory)
	{
		m_blockSize = align;
		m_memory = (uint8_t*)Memory::AllocAligned(MemoryTag::MEMORY_TAG_POOL_ALLOCATOR, sizeInBytes, align);

		m_freeBlock.ptr = m_memory;

		int i;
		for (i = 0; i < (sizeInBytes / align); i++)
		{
			*((uint64_t*)(m_memory + (align * i))) = reinterpret_cast<uint64_t>(m_memory + (align * (i + 1)));
		}

		// set last nodes next free block section to 0xffffffffffffffff
		// so we can make sure that it is the last node
		*(uint64_t*)(m_memory + (align * i)) = NULL;
	}
}

void PoolAllocator::Clear()
{
	// add everything to the freelist
}