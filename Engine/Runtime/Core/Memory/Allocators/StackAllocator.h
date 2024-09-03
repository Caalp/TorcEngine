#pragma once
#include "Core/Memory/Memory.h"
#include "Core/Std/Threading/Mutex.h"

/**
 * This allocator can be used with containers, specifically with stack type containers.
 */

template<typename T>
class StackAllocator
{
public:
	StackAllocator() = default;
	~StackAllocator();

	/**
	 *  Allocates memory for stack allocator
	 * 
	 * @param size number of bytes to allocate
	 */
	void Allocate(uint32_t sizeInBytes);
	void Allocate(uint32_t sizeInBytes, uint32_t align);

	/*
	* Clears the stack allocator by rolling back stack pointer to begining
	*/
	void Clear();

	/**
	 * Destroys the given memory by rolling back to top of the stack
	 * does not physically release the memory
	 * 
	 * @param elem
	 */
	template<typename E>
	inline void Destroy(E* elem);

	// WARNING: might cause a big performance hit
	template<typename E>
	inline void Destroy_TS(E* elem);

	/**
	 * Returns and initalizes a memory from stack allocators heap
	 * 
	 * @return pointer to the begining of memory region
	 */
	template<typename E>
	inline E* Construct();

	// WARNING: might cause a big performance hit
	template<typename E>
	inline E* Construct_TS();


	uint8_t* GetMarker();
private:

	/**
	 * Resizes entire stack allocator and copies current content
	 * into a new region and discards the old region.
	 * Expensive operation and only called if memory requested when there is no space left
	 * 
	 * @param multiplier determines new capacity of the stack allocator by m_totalSize*multiplier
	 */
	void Resize(uint32_t multiplier = 2);
private:
	uint32_t m_totalSize;
	uint32_t m_inUse;
	uint8_t* m_top;
	bool m_isAligned = false;
	core::Mutex m_mutex;
};


template<typename T>
inline StackAllocator<T>::~StackAllocator()
{
	Clear();
	if (m_isAligned)
	{
		Memory::FreeAligned(m_top);
	}
	else
	{
		Memory::Free(m_top);
	}
}

template<typename T>
inline void StackAllocator<T>::Allocate(uint32_t sizeInBytes)
{
	m_top = (uint8_t*)Memory::Alloc(MemoryTag::MEMORY_TAG_STACK_ALLOCATOR, sizeInBytes);
	m_inUse = 0;
	m_totalSize = sizeInBytes;
}

template<typename T>
inline void StackAllocator<T>::Allocate(uint32_t sizeInBytes, uint32_t align)
{
	m_top = (uint8_t*)Memory::AllocAligned(MemoryTag::MEMORY_TAG_STACK_ALLOCATOR, sizeInBytes, align);
	m_inUse = 0;
	m_totalSize = sizeInBytes;
	m_isAligned = true;
}

template<typename T>
inline void StackAllocator<T>::Clear()
{
	m_top -= m_inUse;
	m_inUse = 0;
}

template<typename T>
template<typename E>
inline void StackAllocator<T>::Destroy(E* elem)
{
	if (m_inUse == 0)
	{
		return; // all empty
	}

	uint32_t totalSizeToFree = sizeof(T);

	// we can only destroy by lifo order
	if (m_top - totalSizeToFree == (uint8_t*)elem)
	{
		m_top = m_top - totalSizeToFree;
		m_inUse -= totalSizeToFree;
	}
}

template<typename T>
template<typename E>
inline void StackAllocator<T>::Destroy_TS(E* elem)
{
	core::ScopedLock m(m_mutex);
	if (m_inUse == 0)
	{
		return; // all empty
	}

	uint32_t totalSizeToFree = sizeof(T);

	// we can only destroy by lifo order
	if (m_top - totalSizeToFree == (uint8_t*)elem)
	{
		m_top = m_top - totalSizeToFree;
		m_inUse -= totalSizeToFree;
	}
}

template<typename T>
template<typename E>
inline E* StackAllocator<T>::Construct()
{
	const size_t bytesToRequest = sizeof(E);

	if (m_inUse + bytesToRequest > m_totalSize)
	{
		return nullptr;
	}

	E* mem = reinterpret_cast<E*>(m_top);
	m_top += bytesToRequest;
	m_inUse += bytesToRequest;
	return mem;
}

template<typename T>
template<typename E>
inline E* StackAllocator<T>::Construct_TS()
{
	const size_t bytesToRequest = sizeof(E);

	core::ScopedLock m(m_mutex);

	if (m_inUse + bytesToRequest > m_totalSize)
	{
		return nullptr;
	}

	E* mem = reinterpret_cast<E*>(m_top);
	m_top += bytesToRequest;
	m_inUse += bytesToRequest;
	return mem;
}

template<typename T>
inline uint8_t* StackAllocator<T>::GetMarker()
{
	return m_top;
}

template<typename T>
inline void StackAllocator<T>::Resize(uint32_t multiplier)
{
}