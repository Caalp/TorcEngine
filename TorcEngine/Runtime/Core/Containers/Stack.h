#include "Core/Memory/Allocators/StackAllocator.h"

template <class T, class Allocator = StackAllocator>
class Stack_TS
{
public:
    Stack_TS();

    bool Push(T value);
    bool Pop();
    T Top();
    void Clear();

private:
    T* m_top;
    uint32_t m_size;
    std::mutex m_mutex;
    Allocator m_allocator;
};

template<class T, class Allocator>
inline Stack_TS<T, Allocator>::Stack_TS()
{
    m_allocator.Allocate(5*sizeof(T));
    m_size = 0;
}

template<class T, class Allocator>
inline bool Stack_TS<T, Allocator>::Push(T value)
{
    m_mutex.lock();
    T* newNode = m_allocator.Construct<T>();
    if (newNode == nullptr)
    {
        m_mutex.unlock();
        return false;
    }
    *newNode = value;
    m_top = newNode;
    m_size++;
    m_mutex.unlock();
    return true;
}

template<class T, class Allocator>
inline bool Stack_TS<T, Allocator>::Pop()
{
    m_mutex.lock();
    if (m_size == 0)
    {
        m_mutex.unlock();
        return false;
    }

    // Roll stack top pointer back
    m_allocator.Destroy(m_top);
    m_top = (T*)m_allocator.GetMarker() - 1;
    m_size--;
    m_mutex.unlock();
    
    return true;
}

template<class T, class Allocator>
inline T Stack_TS<T, Allocator>::Top()
{
    T value;
    m_mutex.lock();
    if (m_size == 0)
    {
        m_mutex.unlock();
        return -1;
    }
    value = *m_top;
    m_mutex.unlock();
    return value;
}

template<class T, class Allocator>
inline void Stack_TS<T, Allocator>::Clear()
{
    m_size = 0;
    m_allocator.Clear();
}

#define LFENCE asm volatile("lfence" : : : "memory")
#define SFENCE asm volatile("sfence" : : : "memory")

template<class P>
struct pointer_t
{
    P* ptr;

    P* address() const
    {
        return reinterpret_cast<P*>((reinterpret_cast<uintptr_t>(ptr) & ~((uint64_t)0xffff << 48)));
    }
    uint32_t count() const
    {
        return reinterpret_cast<uintptr_t>(ptr) >> 48;
    }
    inline pointer_t operator+(const pointer_t& rhs) const
    {
        return {(P*)(((uint64_t)(rhs.count()+1)) << 48 | (uintptr_t)this->address())};
    }
};
//
//template <class T, class Allocator = StackAllocator>
//class Stack_CS
//{
//public:
//    Stack_CS();
//    bool Push(T value);
//    bool Pop(T* value);
//    T Top();
//    void Clear();
//    
//private:
//    pointer_t<T> m_top;
//    Allocator m_allocator;
//    m_size;
//};
//
//template<class T, class Allocator>
//inline Stack_CS<T, Allocator>::Stack_CS()
//{
//    m_allocator.Allocate(5);
//    m_size = 0;
//}
//
//template<class T, class Allocator>
//inline bool Stack_CS<T, Allocator>::Push(T value)
//{
//    pointer_t<T> newNode, oldTop;
//    newNode.ptr = (T*)m_allocator.Construct();
//    *newNode.ptr = value;
//    SFENCE;
//    while (true)
//    {
//        oldTop = m_top;
//        LFENCE;
//        newNode.address()->next = old_top;
//        LFENCE;
//        if (CAS(&m_top, oldTop, newNode + oldTop))
//        {
//            return;
//        }
//    }
//}
//
//template<class T, class Allocator>
//inline bool Stack_CS<T, Allocator>::Pop(T* value)
//{
//    pointer_t<T> oldTop, newTop;
//    while (true)
//    {
//        oldTop = m_top;
//        LFENCE;
//        if (oldTop.address()->next.ptr == NULL)
//        {
//            return false;
//        }
//        newTop = oldTop.address()->next;
//        LFENCE;
//        if (CAS(&m_top, oldTop, newTop + oldTop))
//        {
//            *value = oldTop.address()->value;
//            m_allocator.Destroy();
//            return true;
//        }
//    }
//}
//
//template<class T, class Allocator>
//inline T Stack_CS<T, Allocator>::Top()
//{
//    return T();
//}
//
//template<class T, class Allocator>
//inline void Stack_CS<T, Allocator>::Clear()
//{
//    m_allocator.Clear();
//}