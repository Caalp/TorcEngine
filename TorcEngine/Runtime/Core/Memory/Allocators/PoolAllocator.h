#pragma once

class PoolAllocator
{
public:
	PoolAllocator();
	~PoolAllocator();

	/**
	 *  Allocates memory for the pool allocator
	 *
	 * @param size number of bytes to allocate
	 */
	void Allocate(uint32_t sizeInBytes, size_t align);

	/**
	 * Returns and initalizes a memory from pool allocators free list
	 *
	 * @return pointer to the begining of memory region
	 */
	template<typename T, typename... Args>
	T* Construct(Args... args);

	/**
	 * Destroys the given memory by adding the block to the free list
	 * does not physically release the memory
	 *
	 * @param elem
	 */
	template<typename T>
	void Destroy(T* elem);

	/*
	* Clears the pool allocator by ...
	*/
	void Clear();

private:
	uint8_t* m_memory;
	uint8_t* m_freeBlock;
	uint64_t m_blockSize;
};

template<typename T, typename ...Args>
inline T* PoolAllocator::Construct(Args... args)
{
	// if don't have any block to give, just return nullptr
	if (m_freeBlock == nullptr)
	{
		return nullptr;
	}
	
	//TE_ASSERT(sizeof(T) > m_blockSize);

	uint8_t* mem = m_freeBlock;

	// update the free block
	// if we are using up the last available block we set next available one to nullptr
	uint8_t* nextFreeBlock = (*(uint64_t*)m_freeBlock == 0xffffffffffffffff) ? nullptr : reinterpret_cast<uint8_t*>(*(uint64_t*)m_freeBlock);
	m_freeBlock = nextFreeBlock;

	new(mem) T(args...);
	return (T*)mem;
}

template<typename T>
inline void PoolAllocator::Destroy(T* elem)
{
	if (elem == nullptr)
	{
		return;
	}

	// call destructor manually before releasing the object
	elem->~T();

	// check if we don't have any block available, if don't have 
	// any block available and adding one we have to first mark it as last block
	// by storing 0xffffffffffffffff in the first 8 byte section of the block
	*(uint64_t*)elem = (m_freeBlock == nullptr) ? 0xffffffffffffffff : ((uint64_t)m_freeBlock);
	m_freeBlock = (uint8_t*)elem;

	// TODO: we can zero out the block after releasing, if don't want to return stale memory
	// and have some pointers to hold onto it
}