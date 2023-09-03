#pragma once

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
	template<typename T>
	void Destroy(T* elem);

	/**
	 * Returns and initalizes a memory from stack allocators heap
	 * 
	 * @return pointer to the begining of memory region
	 */
	template<typename T>
	T* Construct();


	uint8_t* GetMarker() const;
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
	uint32_t m_totalSize; // max number of T elements block can fit;
	uint32_t m_inUse;
	uint8_t* m_top;
	const uint8_t m_headerSizeInBytes = 1;
};

template<typename T>
inline void StackAllocator::Destroy(T* elem)
{
	if (m_inUse == 0)
	{
		return; // all empty
	}

	// read size of the block from header
	uint8_t blockSize = m_top[-1];
	uint32_t totalSizeToFree = blockSize + m_headerSizeInBytes;
	// we can only destroy by lifo order
	if (m_top - totalSizeToFree == (uint8_t*)elem)
	{
		m_top = m_top - totalSizeToFree;
		m_inUse -= totalSizeToFree;
	}
}

template<typename T>
inline T* StackAllocator::Construct()
{
	const size_t bytesToRequest = sizeof(T) + m_headerSizeInBytes;
	
	if (m_inUse + bytesToRequest > m_totalSize)
	{
		return nullptr;
	}
	T* mem = reinterpret_cast<T*>(m_top);
	m_top += bytesToRequest;
	m_top[-1] = sizeof(T); // which can be between 0 and 255;
	m_inUse += bytesToRequest;
	return mem;
}
