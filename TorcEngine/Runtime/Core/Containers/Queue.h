//#include "../common/allocator.h"
//#include <mutex>
//template <class T>
//class Node
//{
//public:
//    T value;
//    Node<T>* next;
//};
//
//template <class T, class Allocator = std::allocator<T>>
//class OneLockQueue
//{
//public:
//    OneLockQueue()
//    {
//        //std::cout << "Using OneLockQueue\n";
//    }
//
//    void initQueue(long t_my_allocator_size){
//        std::cout << "Using Allocator\n";
//        my_allocator_.initialize(t_my_allocator_size, sizeof(Node<T>));
//        // Initialize the queue head or tail here
//        Node<T>* sentinel_node = (Node<T>* )my_allocator_.newNode();
//        sentinel_node->next = NULL;
//        m_head = m_tail = sentinel_node;
//    }
//
//    void enqueue(T value)
//    {   
//        Node<T>* new_node = (Node<T>*)my_allocator_.newNode();
//        new_node->next = NULL;
//        new_node->value = value;
//        m_mutex.lock();
//        m_tail->next = new_node;
//        m_tail = new_node;
//        m_mutex.unlock();       
//    }
//
//    bool dequeue(T* value)
//    {
//        m_mutex.lock();
//        Node<T>* head = m_head;
//        Node<T>* new_head = head->next;
//        if(new_head == NULL)
//        {
//            m_mutex.unlock();
//            return false;
//        }
//        *value = new_head->value;
//        m_head= new_head;
//        m_mutex.unlock();
//        my_allocator_.freeNode(head);
//        return true;
//    }
//
//    void cleanup()
//    {
//        my_allocator_.cleanup();
//    }
//private:
//    Node<T>* m_head;
//    Node<T>* m_tail;
//    Allocator m_allocator;
//    std::mutex m_mutex;
//};