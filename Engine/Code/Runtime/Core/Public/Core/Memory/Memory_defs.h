#pragma once

#define torc_new new
#define torc_delete delete

#define TORC_CLASS_ALLOCATOR(ClassType, AllocatorType)\
	void* operator new(size_t size)\
	{\
		return AllocatorType::New<ClassType>(size);\
	}\
	void operator delete(void* p)\
	{\
		AllocatorType::Delete<ClassType>(p);\
	}	
