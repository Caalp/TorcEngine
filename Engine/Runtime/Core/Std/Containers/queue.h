#pragma once

#include "Core/Base.h"
#include "Core/Memory/Allocators/PoolAllocator.h"
#include "Core/Std/Threading/Mutex.h"

#include <vector>

template<typename T>
class ThreadSafeVector
{
public:
    ThreadSafeVector() = default;

    void PushBack(T&& val)
    {
        core::ScopedLock sl(m_lock);
        m_storage.push_back(std::forward<T>(val));
    }

    int32 Size()
    {
        core::ScopedLock sl(m_lock);
        return (int32)m_storage.size();
    }

    void Clear()
    {
        core::ScopedLock sl(m_lock);
        m_storage.clear();
    }

    T& operator[](int32 idx)
    {
        core::ScopedLock sl(m_lock);
        return m_storage[idx];
    }

    const T& operator[](int32 idx) const
    {
        core::ScopedLock sl(m_lock);
        return m_storage[idx];
    }

private:
    std::vector<T> m_storage;
    core::Mutex m_lock;
};

template <class T, class Allocator = PoolAllocator>
class ThreadSafeQueue
{
    class Node
    {
    public:
        T value;
        Node* next;
    };
public:
    ThreadSafeQueue() = default;
    
    void Init(size_t numberOfElems)
    { 
        m_allocator.Allocate(numberOfElems * sizeof(Node), sizeof(Node));
        // Initialize the queue head or tail here
        Node* sentinelNode = m_allocator.Construct<Node>();
        sentinelNode->next = NULL;
        m_head = m_tail = sentinelNode;
    }

    void Enqueue(T value)
    {   
        m_mutex.Lock();
        Node* new_node = m_allocator.Construct_TS<Node>();
        new_node->next = NULL;
        new_node->value = value;
        m_tail->next = new_node;
        m_tail = new_node;
        m_mutex.Unlock();       
    }

    bool Dequeue(T* value)
    {
        m_mutex.Lock();
        Node* head = m_head;
        Node* new_head = head->next;
        if(new_head == NULL)
        {
            m_mutex.Unlock();
            return false;
        }
        
        *value = new_head->value;
        m_head= new_head;
        m_mutex.Unlock();
        m_allocator.Destroy_TS(head);
        return true;
    }

    void Clear()
    {
        m_allocator.Clear();
    }

private:
    Node* m_head;
    Node* m_tail;
    Allocator m_allocator;
    core::Mutex m_mutex;
};

template <class T, class Allocator = PoolAllocator>
class Queue_TwoLock
{
    class Node
    {
    public:
        T value;
        Node* next;
    };
public:
    Queue_TwoLock() = default;

    void Init(size_t numberOfElems)
    {
        m_allocator.Allocate(numberOfElems * sizeof(Node), sizeof(Node));
        // Initialize the queue head or tail here
        Node* sentinelNode = m_allocator.Construct<Node>();
        sentinelNode->next = NULL;
        m_head = m_tail = sentinelNode;
    }

    void Enqueue(T value)
    {
        
        Node* new_node = m_allocator.Construct_TS<Node>();
        new_node->next = NULL;
        new_node->value = value;
        m_enqueueLock.Lock();
        m_tail->next = new_node;
        m_tail = new_node;
        m_enqueueLock.Unlock();
    }

    bool Dequeue(T * value)
    {
        m_dequeueLock.Lock();
        Node* head = m_head;
        Node* new_head = head->next;
        if (new_head == NULL)
        {
            m_dequeueLock.Unlock();
            return false;
        }
        *value = new_head->value;
        m_head = new_head;
        m_dequeueLock.Unlock();
        m_allocator.Destroy_TS(head);
        return true;
    }

    void Clear()
    {
        m_allocator.Clear();
    }

private:
    Node* m_head;
    Node* m_tail;
    Allocator m_allocator;
    core::Mutex m_enqueueLock;
    core::Mutex m_dequeueLock;
};

template <class T, class Allocator = PoolAllocator>
class Queue_CS
{
    class Node
    {
    public:
        T value;
        pointer_t<Node> next;
    };
public:
    Queue_CS() = default;

    void Init(size_t numberOfElems)
    {
        m_allocator.Allocate(numberOfElems * sizeof(Node), sizeof(Node));
        // Initialize the queue head or tail here
        Node* sentinelNode = m_allocator.Construct<Node>();
        sentinelNode->next.ptr = NULL; 
        m_head.ptr = m_tail.ptr = sentinelNode;
    }

    void Enqueue(T value)
    {
        pointer_t<Node> tail, next, node;
        node.ptr = m_allocator.Construct_TS<Node>();
        node.ptr->value = value;
        node.ptr->next.ptr = NULL;
        SFENCE;
        while (true)
        {
            tail = m_tail;
            LFENCE;
            next = tail.Address()->next;
            LFENCE;
            if (tail.ptr == m_tail.ptr)
            {
                if (next.Address() == NULL)
                {
                    if (core::CAS(tail.Address()->next, next, (node + next)))
                    {
                        break;
                    }
                }
                else
                {
                    // some other thread already changed next ptr of the tail, but failed swinging tail itself
                    // so complete work of other thread and swing tail for them
                    core::CAS(m_tail, tail, (next + tail));
                }
            }
        }
        // we have already updated next pointer of the tail, now try swinging tail to the new one
        SFENCE;
        core::CAS(m_tail, tail, (node + tail));
    }

    bool Dequeue(T * value)
    {
        // Use LFENCE and SFENCE as mentioned in pseudocode
        pointer_t<Node> head, next, tail;
        while (true)
        {
            head = m_head;
            LFENCE;
            tail = m_tail;
            LFENCE;
            next = head.Address()->next;
            LFENCE;
            if (head.ptr == m_head.ptr)
            {
                if (head.Address() == tail.Address())
                {
                    if (next.Address() == NULL)
                    {
                        return false;
                    }

                    // try swinging the tail first
                    core::CAS(m_tail, tail, (next + tail));
                }
                else
                {
                    *value = next.Address()->value;
                    /*if (m_head.CASWeak(head, next + head))
                    {
                        break;
                    }*/
                    if (core::CAS(m_head, head, (next + head)))
                    {
                        /*char out[64];
                        sprintf_s(out, "CAS2 elem: %p, \n", (next + head).ptr);
                        OutputDebugStringA(out);*/
                        break;
                    }
                }
            }
        }
        m_allocator.Destroy_TS(head.Address());
        return true;
    }

    void Clear()
    {
        m_allocator.Clear();
    }

private:
    pointer_t<Node> m_head;
    pointer_t<Node> m_tail;
    Allocator m_allocator;
};