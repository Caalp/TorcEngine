#pragma once
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
	{
		m_freeList = (Node*)Memory::Alloc(sizeof(Node) * count, sizeof(Node), MemoryTag::MEMORY_TAG_FREE_LIST);
		m_head = m_freeList;

		// set pointers
		for (uint32_t i = 0; i < count - 1; i++)
		{
			m_freeList[i].next = &m_freeList[i + 1];
		}
		m_freeList[count - 1].next = nullptr;
		m_currentNode = m_freeList;
		m_inUseList = nullptr;
	}

	template<typename E = Allocator, std::enable_if_t<(!std::is_same<E, void>::value == true),bool> = true>
	FreeList()
	{}

	~FreeList()
	{
		TE_DELETE_ALIGNED(m_head);
	}

	T* Allocate()
	{
		// we have no free node left allocate more and continue
		if (m_freeList == nullptr)
		{
			return nullptr;
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
		Node* temp;
		temp = m_inUseList;
		while (temp != nullptr)
		{
			// we found the node, take it out of list and add beginning of the free list
			if (temp->val == elem)
			{
				m_inUseList = temp->next;			
				temp->next = m_freeList;
				m_freeList = temp;
				break;
			}

			// continue
			temp = temp->next;
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
	Node* m_freeList;
	Node* m_inUseList;
	Node* m_currentNode;
	Node* m_head;
};
