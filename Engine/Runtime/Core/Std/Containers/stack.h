#pragma once
#include "Core/Base.h"
#include "Core/Memory/Allocators/StackAllocator.h"
#include "Core/Std/Threading/Atomic.h"

template <class T, class Allocator = StackAllocator<T>>
class Stack_TS
{
    class Node
    {
    public:
        T value;
        Node* next;
    };

public:
    Stack_TS() = default;
    void Init(uint32_t numberOfElems);
    bool Push(T value);
    bool Pop();
    bool Push_TS(T value);
    bool Pop_TS();
    bool Top(T* val);
    void Clear();

private:
    Node* m_top;
    core::Mutex m_mutex;
    Allocator m_allocator;
};

template<class T, class Allocator>
inline void Stack_TS<T, Allocator>::Init(uint32_t numberOfElems)
{
    m_allocator.Allocate(numberOfElems * sizeof(Node));

    Node* sentinelNode = (Node*)m_allocator.Construct<Node>();
    sentinelNode->next = NULL;
    m_top = sentinelNode;
}

template<class T, class Allocator>
inline bool Stack_TS<T, Allocator>::Push(T value)
{
	Node* newNode = m_allocator.Construct<Node>();
	if (newNode == nullptr)
	{
		return false;
	}
	newNode->value = value;
	newNode->next = m_top;
	m_top = newNode;
	return true;
}

template<class T, class Allocator>
inline bool Stack_TS<T, Allocator>::Pop()
{
    if (m_top->next == NULL)
    {
        return false;
    }

    Node* tmp = m_top;
    m_top = tmp->next;

    // Roll stack top pointer back
    m_allocator.Destroy(tmp);   
    return true;
}

template<class T, class Allocator>
inline bool Stack_TS<T, Allocator>::Push_TS(T value)
{
    m_mutex.Lock();
    Node* newNode = (Node*)m_allocator.Construct<Node>();
    if (newNode == nullptr)
    {
        m_mutex.Unlock();
        return false;
    }
    newNode->value = value;
    newNode->next = m_top;
    m_top = newNode;
    m_mutex.Unlock();
    return true;
}

template<class T, class Allocator>
inline bool Stack_TS<T, Allocator>::Pop_TS()
{
    m_mutex.Lock();
    if (m_top->next == NULL)
    {
        m_mutex.Unlock();
        return false;
    }

    Node* tmp = m_top;
    m_top = tmp->next;

    // Roll stack top pointer back
    m_allocator.Destroy(tmp);
    m_mutex.Unlock();

    return true;
}


template<class T, class Allocator>
inline bool Stack_TS<T, Allocator>::Top(T* val)
{
    m_mutex.Lock();
    if (m_top->next == NULL)
    {
        m_mutex.Unlock();
        return false;
    }
    *val = m_top->value;
    m_mutex.Unlock();
    
    return true;
}

template<class T, class Allocator>
inline void Stack_TS<T, Allocator>::Clear()
{
    m_size = 0;
    m_allocator.Clear();
}

#if defined(_MSC_VER)
#define LFENCE _mm_lfence()
#define SFENCE _mm_sfence()
#elif defined(__GNUC__) || defined (__GNUG__)
#define LFENCE asm volatile("lfence" : : : "memory")
#define SFENCE asm volatile("sfence" : : : "memory")
#endif

template <class T, class Allocator = StackAllocator<T>>
class Stack_CS
{
    class Node
    {
    public:
        T value;
        pointer_t <Node> next;
    };

public:
    Stack_CS() = default;
    void Init(uint32_t numberOfElems);
    bool Push(T value);
    bool Pop();
    bool Top(T* value);
    void Clear();
    
private:
    core::Atomic<pointer_t<Node>> m_top;
    Allocator m_allocator;
};

template<class T, class Allocator>
inline void Stack_CS<T, Allocator>::Init(uint32_t numberOfElems)
{
    m_allocator.Allocate(numberOfElems * sizeof(Node));

    Node* sentinelNode = (Node*)m_allocator.Construct<Node>();
    sentinelNode->next.ptr = NULL;
    pointer_t<Node> tempTop;
    tempTop.ptr = sentinelNode;

    m_top.Store(tempTop);
}

template<class T, class Allocator>
inline bool Stack_CS<T, Allocator>::Push(T value)
{
    pointer_t<Node> newNode, oldTop;
    newNode.ptr = (Node*)m_allocator.Construct_TS<Node>();
    if (newNode.ptr == nullptr)
    {
        return false;
    }
    newNode.ptr->value = value;
    newNode.ptr->next.ptr = NULL;
    SFENCE;
    while (true)
    {
        oldTop = m_top.Load();
        LFENCE;
        newNode.Address()->next = oldTop;
        LFENCE;

        if (m_top.CASWeak(oldTop, newNode + oldTop))
        {
            return true;
        }

    }
    return true;
}

template<class T, class Allocator>
inline bool Stack_CS<T, Allocator>::Pop()
{
    pointer_t<Node> oldTop, newTop;
    while (true)
    {
        oldTop = m_top;
        LFENCE;
        if (oldTop.Address()->next.ptr == NULL)
        {
            return false;
        }
        newTop = oldTop.Address()->next;
        LFENCE;

        if (m_top.CASWeak(oldTop, newTop + oldTop))
        {
            m_allocator.Destroy_TS(oldTop.Address());
            return true;
        }
    }
}

template<class T, class Allocator>
inline bool Stack_CS<T, Allocator>::Top(T* value)
{
    pointer_t<Node> top = m_top.Load();
    if (top.Address()->next.ptr == NULL)
    {
        return false;
    }

    *value = top.Address()->value;
    return true;
}

template<class T, class Allocator>
inline void Stack_CS<T, Allocator>::Clear()
{
    m_allocator.Clear();
}