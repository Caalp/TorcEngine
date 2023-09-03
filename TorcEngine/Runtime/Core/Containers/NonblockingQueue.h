//#include "../common/allocator.h"
//#include "../common/utils.h"
//
//#define LFENCE asm volatile("lfence" : : : "memory")
//#define SFENCE asm volatile("sfence" : : : "memory")
//
//template<class P>
//struct pointer_t
//{
//    P* ptr;
//
//    P* address() const
//    {
//        return reinterpret_cast<P*>((reinterpret_cast<uintptr_t>(ptr) & ~((uint64_t)0xffff << 48)));
//    }
//    uint count() const
//    {
//        return reinterpret_cast<uintptr_t>(ptr) >> 48;
//    }
//    inline pointer_t operator+(const pointer_t& rhs) const
//    {
//        return {(P*)(((uint64_t)(rhs.count()+1)) << 48 | (uintptr_t)this->address())};
//    }
//};
//
//template <class T>
//class Node
//{
//public:
//    T value;
//    pointer_t<Node<T>> next;
//};
//
//template <class T>
//class NonBlockingQueue
//{
//    pointer_t<Node<T>> q_head;
//    pointer_t<Node<T>> q_tail;
//    CustomAllocator my_allocator_;
//public:
//    
//    NonBlockingQueue() : my_allocator_()
//    {
//        std::cout << "Using NonBlockingQueue\n";
//    }
//
//    void initQueue(long t_my_allocator_size){
//        std::cout << "Using Allocator\n";
//        my_allocator_.initialize(t_my_allocator_size, sizeof(Node<T>));
//        // Initialize the queue head or tail here
//        Node<T>* newNode = (Node<T>*)my_allocator_.newNode();
//        newNode->next.ptr = NULL;
//        q_head.ptr = q_tail.ptr = newNode;
//    }
//
//    void enqueue(T value)
//    {
//        // Use LFENCE and SFENCE as mentioned in pseudocode
//        pointer_t<Node<T>> tail, next, node;     
//        node.ptr = (Node<T>*)my_allocator_.newNode();
//        node.ptr->value = value;
//        node.ptr->next.ptr = NULL;
//        SFENCE;
//        while(true)
//        {
//            tail = q_tail;
//            LFENCE;
//            next = tail.address()->next;
//            LFENCE;
//            if (tail.ptr == q_tail.ptr)
//            {
//                if (next.address() == NULL)
//                {
//                    // try setting tail's next pointer to new node
//                    if (CAS(&tail.address()->next, next, node + next))
//                    {
//                        break;
//                    }
//                }
//                else
//                {
//                    // some other thread already changed next ptr of the tail, but failed swinging tail itself
//                    // so complete work of other thread and swing tail for them
//                    CAS(&q_tail, tail, next+tail); // ELABEL                   
//                }
//            }
//        }
//        // we have already updated next pointer of the tail, now try swinging tail to the new one
//        SFENCE;
//        CAS(&q_tail, tail, node + tail);
//    }
//
//    bool dequeue(T *value)
//    {
//        // Use LFENCE and SFENCE as mentioned in pseudocode
//        pointer_t<Node<T>> head, next, tail;
//        while(true)
//        {
//            head = q_head;
//            LFENCE;
//            tail = q_tail;
//            LFENCE;
//            next = head.address()->next;
//            LFENCE;           
//            if (head.ptr == q_head.ptr)
//            {
//                if(head.address() == tail.address())
//                {
//                    if(next.address() == NULL)
//                    {
//                        return false;
//                    }
//                    
//                    // try swinging the tail first
//                    CAS(&q_tail, tail, next + tail); //DLABEL
//                }
//                else
//                {
//                    *value = next.address()->value;
//                    if(CAS(&q_head, head, next + head))
//                    {
//                        break;
//                    }
//                }
//            }
//        }
//        my_allocator_.freeNode(head.address());
//        return true;
//    }
//
//    void cleanup()
//    {
//        my_allocator_.cleanup();
//    }
//};