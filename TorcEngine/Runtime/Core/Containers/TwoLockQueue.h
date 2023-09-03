#include "Core/Memory/Allocators/StackAllocator.h"

template <class T,  class Allocator = StackAllocator>
class TwoLockQueue
{
    template <class T>
    class Node
    {
    public:
        T value;
        Node<T>* next;
    };
public:
    TwoLockQueue();
    TwoLockQueue(uint32_t size);

    void Enqueue(T value);
    T Dequeue();

    void Clear();
private:
    const uint32_t m_defaultQueueSize = 10u;
    Node<T>* m_head;
    Node<T>* m_tail;
    std::mutex m_enqueueLock;
    std::mutex m_dequeueLock;
    Allocator m_allocator;
};

template<class T, class Allocator>
inline TwoLockQueue<T, Allocator>::TwoLockQueue()
{
    m_allocator.Initialize(m_defaultQueueSize + 1);

    Node<T>* sentinelNode = m_allocator.Allocate();
    sentinelNode->next = nullptr;
    m_head = m_tail = sentinelNode;
}

template<class T, class Allocator>
inline TwoLockQueue<T, Allocator>::TwoLockQueue(uint32_t size)
{
    m_allocator.Initialize(size + 1);

    Node<T>* sentinelNode = m_allocator.Allocate();
    sentinelNode->next = nullptr;
    m_head = m_tail = sentinelNode;
}

template<class T, class Allocator>
inline void TwoLockQueue<T, Allocator>::Enqueue(T value)
{
	Node<T>* newNode = (Node<T>*)m_allocator.Allocate();
    if (newNode == nullptr)
    {
        return;
    }
	newNode->next = nullptr;
	newNode->value = value;
	m_enqueueLock.lock();
	m_tail->next = newNode;
	m_tail = newNode;
	m_enqueueLock.unlock();
}

template<class T, class Allocator>
inline T TwoLockQueue<T, Allocator>::Dequeue()
{
    T val;
    m_dequeueLock.lock();
    Node<T>* head = m_head;
    Node<T>* newHead = head->next;
    if (newHead == nullptr)
    {
        m_dequeueLock.unlock();
        return val;
    }
    val = newHead->value;
    m_head = newHead;
    m_dequeueLock.unlock();
    m_allocator.Free(head);

    return val;
}

template<class T, class Allocator>
inline void TwoLockQueue<T, Allocator>::Clear()
{
    ~m_allocator();
}
