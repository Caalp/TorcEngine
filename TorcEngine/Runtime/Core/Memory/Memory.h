#pragma once

enum class MemoryTag : uint8_t
{
	MEMORY_TAG_UNSPECIFIED = 0u,
	MEMORY_TAG_CORE,
	MEMORY_TAG_PLATFORM,
	MEMORY_TAG_GAME_CORE,
	MEMORY_TAG_RENDERER,
	MEMORY_TAG_STACK_ALLOCATOR,
	MEMORY_TAG_POOL_ALLOCATOR,
	MEMORY_TAG_ENTITY,
	MEMORY_TAG_FILE_IO,
	MEMORY_TAG_FREE_LIST,
	COUNT
};

class Memory
{
public:
	//struct MemroyInitParams
	//{
	//	uint32_t stackAllocatorSize;
	//	uint32_t poolAllocatorSize;
	//};
	//struct MemoryBlock
	//{
	//	uint64_t addr : 48;
	//	uint64_t alignment : 3;
	//	uint64_t tag : 5;
	//	uint64_t size : 8;

	//	operator void* () const { return (void*)addr; }
	//};
public:

	static bool Initialize();
	static bool Release();
	static void PrintMemoryUsageInfo();

	static void* Alloc(size_t bytes, size_t align, MemoryTag memTag);

	template<typename T, class Allocator, typename... Args>
	static T* Alloc(Allocator& allocator, size_t align, Args... args);

	template<typename T, typename... Args>
	static T* Alloc(size_t align, MemoryTag memTag, Args... args);

	template<typename T, typename... Args>
	static T* Alloc(MemoryTag memTag, Args... args);


	template<typename T>
	static void Free(T* mem);

	template<typename T>
	static void FreeAligned(T* mem);

private:
	static void* Alloc(size_t bytes, MemoryTag memTag = MemoryTag::MEMORY_TAG_UNSPECIFIED);
	static void* AllocAligned(size_t bytes, size_t align, MemoryTag memTag = MemoryTag::MEMORY_TAG_UNSPECIFIED);

	static void Free(void* bytes);
	static void FreeAligned(void* bytes);

};

template<typename T, class Allocator, typename... Args>
inline T* Memory::Alloc(Allocator& allocator, size_t align, Args... args)
{
	T* mem = allocator.Construct<T>();
	new(mem) T(args...);
	return mem;
}

template<typename T, typename... Args>
inline T* Memory::Alloc(size_t align, MemoryTag memTag, Args... args)
{
	T* mem = (T*)AllocAligned(sizeof(T), align);
	new(mem) T(args...);
	return mem;
}

template<typename T, typename... Args>
inline T* Memory::Alloc(MemoryTag memTag, Args... args)
{
	T* mem = (T*)Memory::Alloc(sizeof(T));
	new(mem) T(args...);
	return mem;
}

template<typename T>
inline void Memory::Free(T* mem)
{
	mem->~T();
	Free((void*)mem);
}

template<typename T>
inline void Memory::FreeAligned(T* mem)
{
	mem->~T();
	FreeAligned((void*)mem);
}


#define TE_NEW(type, ...)\
	Memory::Alloc<type>(__VA_ARGS__)

#define TE_DELETE(type, ...)\
	Memory::Free(type, __VA_ARGS__)

#define TE_DELETE_ALIGNED(type, ...)\
	Memory::FreeAligned(type, __VA_ARGS__)

//#define TE_DELETE(type, ...)\
//	new(__VA_ARGS__) type
