#pragma once
#include "Memory/Memory.h"

#include <type_traits>

//template<typename, typename = void>
//struct has_member : std::false_type{};
//
//template<typename T>
//struct has_member < T, std::void_t<decltype(T::idx)>> : std::true_type {};

template<typename T, uint32_t count, typename Allocator = void>
class FreeList
{
	struct Node
	{
		Node* next;
		T val;
	};

public:
	template<typename E = Allocator, std::enable_if_t<(std::is_same<E, void>::value == true), bool> = true>
	FreeList()
		: m_capacity(count)
		, m_size((uint32)sqrtf(count))
	{
		m_freeList = (Node*)Memory::Alloc(MemoryTag::MEMORY_TAG_FREE_LIST, sizeof(Node) * m_size);
		m_head = m_freeList;

		// set pointers
		for (uint32_t i = 0; i < m_size - 1; i++)
		{
			m_freeList[i].next = &m_freeList[i + 1];		
		}
		m_freeList[m_size - 1].next = nullptr;
		m_currentNode = m_freeList;
		m_inUseList = nullptr;
	}

	template<typename E = Allocator, std::enable_if_t<(!std::is_same<E, void>::value == true),bool> = true>
	FreeList()
	{
		// TODO(cagri): Implement
	}

	~FreeList()
	{
		Memory::Free(m_head);
	}

	T* Allocate()
	{
		// we have no free node left allocate more and continue
		if (m_freeList == nullptr)
		{
			if (m_capacity == m_size)
			{
				return nullptr;
			}

			uint32 newSize = m_size * 2;
			if (newSize > m_capacity)
			{
				newSize = m_capacity;
			}
			Resize(newSize);
		}

		// get a free node from free list and prepend to the inUseList
		Node* temp = m_freeList;
		m_freeList = m_freeList->next;

		temp->next = m_inUseList;
		m_inUseList = temp;
		
		return &m_inUseList->val;
	}

	void Release(T elem)
	{
		// traverse the list and find the node
		Node* curr;
		Node* prev;
		prev = curr = m_inUseList;
		while (curr != nullptr)
		{
			// we found the node, take it out of list and add beginning of the free list
			if (curr->val == elem)
			{
				prev->next = curr->next;
				if (curr == m_inUseList)
				{
					m_inUseList = curr->next;
				}
				curr->next = m_freeList;
				m_freeList = curr;
				break;
			}

			// continue
			prev = curr;
			curr = curr->next;
		}
	}

	T* Next()
	{
		Node* temp = m_currentNode;
		m_currentNode = m_currentNode->next;
		return &temp->val;
	}

	void Reset()
	{
		m_currentNode = m_freeList;
	}

private:
	void Resize(uint32 newSize)
	{
		Node* newList = (Node*)Memory::Alloc(MemoryTag::MEMORY_TAG_FREE_LIST, sizeof(Node) * newSize);

		// set pointers
		for (uint32_t i = 0; i < newSize - 1; i++)
		{
			newList[i].next = &newList[i + 1];
		}
		newList[newSize - 1].next = nullptr;

		Node* temp0 = m_inUseList;
		Node* temp1 = newList;

		while (temp0 != nullptr)
		{
			if (temp0 == m_currentNode)
			{
				m_currentNode = temp1;
			}
			temp1->val = temp0->val;
			temp1 = temp1->next;
			temp0 = temp0->next;
		}
		
		Memory::Free(m_head);
		m_head = newList;
		
		m_freeList = temp1;
		m_inUseList = newList;

		m_size = newSize;
	}

private:
	Node* m_freeList;
	Node* m_inUseList;
	Node* m_currentNode;
	Node* m_head;
	uint32 m_capacity;
	uint32 m_size;
};
