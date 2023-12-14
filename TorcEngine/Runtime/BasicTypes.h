#pragma once

#ifdef _WIN64
typedef HWND TORC_HWND;
typedef HANDLE TORC_HANDLE;
#else
typedef void* TORC_HWND;
typedef void* TORC_HANDLE;
#endif

typedef char int8;
typedef unsigned char uint8;

typedef short int16;
typedef unsigned short uint16;

typedef int int32;
typedef unsigned int uint32;

typedef long long int64;
typedef unsigned long long uint64;

typedef struct SystemTime {
    uint16 year;
    uint16 month;
    uint16 dayOfWeek;
    uint16 day;
    uint16 hour;
    uint16 minute;
    uint16 second;
    uint16 milliseconds;
} SystemTime;


template<class P>
struct pointer_t
{
    P* ptr;

    inline P* Address() const
    {
        return reinterpret_cast<P*>((reinterpret_cast<uintptr_t>(ptr) & ~((uint64_t)0xffff << 48)));
    }

    inline uint16_t Count() const
    {
        return reinterpret_cast<uintptr_t>(ptr) >> 48;
    }

    inline pointer_t operator+(const pointer_t& rhs) const
    {
        return { (P*)(((uint64_t)(rhs.Count() + 1)) << 48 | (uintptr_t)this->Address()) };
    }
};