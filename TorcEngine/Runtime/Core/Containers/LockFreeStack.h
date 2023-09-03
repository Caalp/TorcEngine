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
//class LockFreeStack
//{
//    pointer_t<Node<T>> s_top;
//    CustomAllocator my_allocator_;
//public:
//    LockFreeStack() : my_allocator_()
//    {
//        std::cout << "Using LockFreeStack\n";
//    }
//
//    void initStack(long t_my_allocator_size)
//    {
//        std::cout << "Using Allocator\n";
//        my_allocator_.initialize(t_my_allocator_size, sizeof(Node<T>));
//        // Perform any necessary initializations
//        Node<T>* sentinel_node = (Node<T>* )my_allocator_.newNode();
//        sentinel_node->next.ptr = NULL;
//        s_top.ptr = sentinel_node;
//    }
//
//    /**
//     * Create a new node with value `value` and update it to be the top of the stack.
//     * This operation must always succeed.
//     */
//    void push(T value)
//    {
//        pointer_t<Node<T>> new_node, old_top;
//        new_node.ptr = (Node<T>*)my_allocator_.newNode();
//        new_node.ptr->value = value;
//        new_node.ptr->next.ptr = NULL;
//        SFENCE;
//        while(true)
//        {
//            old_top = s_top;
//            LFENCE;
//            new_node.address()->next = old_top;
//            LFENCE;
//            if(CAS(&s_top, old_top, new_node+old_top))
//            {
//                return;
//            }
//        }
//    }
//
//    /**
//     * If the stack is empty: return false.
//     * Otherwise: copy the value at the top of the stack into `value`, update
//     * the top to point to the next element in the stack, and return true.
//     */
//    bool pop(T *value)
//    {   
//        pointer_t<Node<T>> old_top, new_top;
//        while(true)
//        {
//            old_top = s_top;
//            LFENCE;
//            if (old_top.address()->next.ptr == NULL)
//            {
//                return false;
//            }
//            new_top = old_top.address()->next;
//            LFENCE;
//            if (CAS(&s_top, old_top, new_top+old_top))
//            {
//                *value = old_top.address()->value;
//                my_allocator_.freeNode(old_top.address());
//                return true;
//            }       
//        }
//    }
//
//    void cleanup()
//    {
//        my_allocator_.cleanup();
//    }
//};
