#pragma once
#include "Std/Threading/Atomic.h"

class PoolAllocator
{
	template<class P>
	struct pointer_t
	{
		P* ptr;

		P* Address() const
		{
			return reinterpret_cast<P*>((reinterpret_cast<uintptr_t>(ptr) & ~((uint64_t)0xffff << 48)));
		}

		uint16_t Count() const
		{
			return reinterpret_cast<uintptr_t>(ptr) >> 48;
		}

		pointer_t operator+(const pointer_t& rhs) const
		{
			return { (P*)(((uint64_t)(rhs.Count() + 1)) << 48 | (uintptr_t)this->Address()) };
		}
	};
public:
	PoolAllocator();
	~PoolAllocator();

	/**
	 *  Allocates memory for the pool allocator
	 *
	 * @param size number of bytes to allocate
	 */
	void Allocate(size_t sizeInBytes, size_t align);

	/**
	 * Returns and initalizes a memory from pool allocators free list
	 *
	 * @return pointer to the begining of memory region
	 */
	template<typename T, typename... Args>
	T* Construct(Args... args);

	template<typename T, typename... Args>
	T* Construct_TS(Args... args);

	/**
	 * Destroys the given memory by adding the block to the free list
	 * does not physically release the memory
	 *
	 * @param elem
	 */
	template<typename T>
	void Destroy(T* elem);

	template<typename T>
	void Destroy_TS(T* elem);

	/*
	* Clears the pool allocator by ...
	*/
	void Clear();

private:
	uint8_t* m_memory;
	pointer_t<uint8_t> m_freeBlock;
	uint64_t m_blockSize;
};

template<typename T, typename ...Args>
inline T* PoolAllocator::Construct(Args... args)
{
	// if don't have any block to give, just return nullptr
	if (m_freeBlock.Address() == nullptr)
	{
		return nullptr;
	}
	
	//TE_ASSERT(sizeof(T) > m_blockSize);

	uint8_t* mem = m_freeBlock.Address();

	// update the free block
	// if we are using up the last available block we set next available one to nullptr
	m_freeBlock.ptr = reinterpret_cast<uint8_t*>(*(uint64_t*)m_freeBlock.Address());
	//m_freeBlock = nextFreeBlock;
	
	new(mem) T(args...);
	return (T*)mem;
}

template<typename T, typename ...Args>
inline T* PoolAllocator::Construct_TS(Args... args)
{
	// if don't have any block to give, just return nullptr
	if (m_freeBlock.Address() == nullptr)
	{
		return nullptr;
	}

	//TE_ASSERT(sizeof(T) > m_blockSize);
	pointer_t<uint8_t> mem, next;
	while (true)
	{
		mem = m_freeBlock;
		next.ptr = reinterpret_cast<uint8_t*>(*(uint64_t*)mem.Address());

		// update the free block
		// if we are using up the last available block we set next available one to nullptr
		//uint8_t* nextFreeBlock = reinterpret_cast<uint8_t*>(*(uint64_t*)mem);
		if (core::CAS(m_freeBlock, mem, next + m_freeBlock))
		{
			/*char out[128];
			sprintf_s(out, "C mem: %p, nextFreeBlock: %llx\n", mem, nextFreeBlock);
			OutputDebugStringA(out);*/
			break;
		}
			
	}

	new(mem.Address()) T(args...);
	return (T*)mem.Address();
}

template<typename T>
inline void PoolAllocator::Destroy(T* elem)
{
	/*if (elem == nullptr)
	{
		return;
	}*/

	// call destructor manually before releasing the object
	elem->~T();

	// check if we don't have any block available, if don't have 
	// any block available and adding one we have to first mark it as last block
	// by storing 0xffffffffffffffff in the first 8 byte section of the block
	*(uint64_t*)elem = ((uint64_t)m_freeBlock.Address());
	m_freeBlock = (uint8_t*)elem;

	// TODO(cagri): we can zero out the block after releasing, if don't want to return stale memory
	// and have some pointers to hold onto it
}

template<typename T>
inline void PoolAllocator::Destroy_TS(T* elem)
{
	if (elem == nullptr)
	{
		return;
	}

	// call destructor manually before releasing the object
	elem->~T();
	pointer_t<uint8_t> mem, next;
	while (true)
	{
		mem = m_freeBlock;

		// check if we don't have any block available, if don't have 
		// any block available and adding one we have to first mark it as last block
		// by storing 0xffffffffffffffff in the first 8 byte section of the block
		*(uint64_t*)elem = ((uint64_t)mem.Address());
		next.ptr = (uint8_t*)elem;
		if (core::CAS(m_freeBlock, mem, next + m_freeBlock))
		{
			/*char out[128];
			sprintf_s(out, "D freeBlock: %p\n",m_freeBlock.ptr);
			OutputDebugStringA(out);*/
			break;
		}
			
	}
	// TODO: we can zero out the block after releasing, if don't want to return stale memory
	// and have some pointers to hold onto it
}