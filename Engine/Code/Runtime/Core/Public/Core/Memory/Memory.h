#pragma once

/**
 * TODO: Define macros such as TE_NEW, TE_DELETE for ease of use
 */

enum class MemoryTag
{
	MEMORY_TAG_UNSPECIFIED = 0u,
	MEMORY_TAG_CORE,
	MEMORY_TAG_PLATFORM,
	MEMORY_TAG_GAME_CORE,
	MEMORY_TAG_RENDERER,
	MEMORY_TAG_STACK_ALLOCATOR,
	MEMORY_TAG_POOL_ALLOCATOR,
	MEMORY_TAG_LINEAR_ALLOCATOR,
	MEMORY_TAG_ENTITY,
	MEMORY_TAG_FILE_IO,
	MEMORY_TAG_FREE_LIST,
	COUNT
};

class Memory
{
public:
	static bool Initialize();
	static bool Release();
	static void PrintMemoryUsageInfo();

	template<typename T, class Allocator, typename... Args>
	static T* AllocCustom(MemoryTag memTag, Allocator& allocator, Args... args);

	template<typename T, typename... Args>
	static T* Alloc(MemoryTag memTag, Args... args);

	static void* Alloc(MemoryTag memTag, size_t size);

	template<typename T, typename... Args>
	static T* AllocAligned(MemoryTag memTag, size_t align, Args... args);

	static void* AllocAligned(MemoryTag memTag, size_t size, size_t align);

	template<typename T>
	static void Free(T* mem);

	template<typename T>
	static void FreeAligned(T* mem);

private:
	static void* _Alloc(size_t bytes, MemoryTag memTag = MemoryTag::MEMORY_TAG_UNSPECIFIED);
	static void* _AllocAligned(size_t bytes, size_t align, MemoryTag memTag = MemoryTag::MEMORY_TAG_UNSPECIFIED);
	static void _Free(void* bytes);
	static void _FreeAligned(void* bytes);
};

template<typename T, class Allocator, typename ...Args>
inline T* Memory::AllocCustom(MemoryTag memTag, Allocator& allocator, Args... args)
{
	T* mem = allocator.Construct<T>();
	new(mem) T(args...);
	return mem;
}

template<typename T, typename ...Args>
inline T* Memory::Alloc(MemoryTag memTag, Args... args)
{
	T* mem = (T*)Memory::_Alloc(sizeof(T));
	new(mem) T(args...);
	return mem;
}

__forceinline void* Memory::Alloc(MemoryTag memTag, size_t size)
{
	return Memory::_Alloc(size);
}

template<typename T, typename ...Args>
inline T* Memory::AllocAligned(MemoryTag memTag, size_t align, Args... args)
{
	T* mem = (T*)Memory::_AllocAligned(sizeof(T), align);
	new(mem) T(args...);
	return mem;
}

__forceinline void* Memory::AllocAligned(MemoryTag memTag, size_t size, size_t align)
{
	return Memory::_AllocAligned(size, align);
}

template<typename T>
inline void Memory::Free(T* mem)
{
	mem->~T();
	_Free((void*)mem);
}

template<typename T>
inline void Memory::FreeAligned(T* mem)
{
	mem->~T();
	_FreeAligned((void*)mem);
}