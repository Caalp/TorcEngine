#include "Memory/Memory.h"
#include "Base.h"
#include "Platform/Platform.h"
namespace
{
	size_t m_usage[(uint32_t)MemoryTag::COUNT];
	static const char* memoryTagToString[] =
	{
		"MEMORY_TAG_UNSPECIFIED",
		"MEMORY_TAG_CORE",
		"MEMORY_TAG_PLATFORM",
		"MEMORY_TAG_GAME_CORE",
		"MEMORY_TAG_RENDERER",
		"MEMORY_TAG_STACK_ALLOCATOR",
		"MEMORY_TAG_POOL_ALLOCATOR",
		"MEMORY_TAG_LINEAR_ALLOCATOR",
		"MEMORY_TAG_ENTITY",
		"MEMORY_TAG_FILE_IO",
		"MEMORY_TAG_FREE_LIST"
	};
	static constexpr uint64_t size = (sizeof(memoryTagToString) / sizeof(memoryTagToString[0]));
	static_assert((uint32_t)MemoryTag::COUNT == size);

	inline size_t ByteToMb(size_t bytes)
	{
		return (size_t)bytes / 100'000;
	}
}

bool Memory::Initialize()
{
	return true;
}

bool Memory::Release()
{
	return true;
}

void Memory::PrintMemoryUsageInfo()
{
	for (uint32_t i = 0; i < (uint32_t)MemoryTag::COUNT; i++)
	{
		char dbgStr[64];
		sprintf_s(dbgStr, "%s -> %lld Bytes\n", memoryTagToString[i], m_usage[i]);
	}
}

void* Memory::_Alloc(size_t bytes, MemoryTag memTag)
{
	m_usage[(uint8_t)memTag] += bytes;
	return Torc::Platform::MemAlloc(bytes);
}

void* Memory::_AllocAligned(size_t bytes, size_t align, MemoryTag memTag)
{
	//m_usage[(uint8_t)memTag] += (bytes + align);
	return Torc::Platform::MemAllocAligned(bytes, align);
}

void Memory::_Free(void* bytes)
{
	Torc::Platform::MemFree(bytes);
}

void Memory::_FreeAligned(void* bytes)
{
	Torc::Platform::MemFreeAligned(bytes);
}