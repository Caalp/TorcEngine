#pragma once

#ifdef _WIN64
typedef void* TORC_HWND;
typedef void* TORC_HANDLE;
typedef void* FileHandle;
#else
typedef void* TORC_HWND;
typedef void* TORC_HANDLE;
#endif

typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;


typedef int8_t int8;
typedef uint8_t uint8;
typedef uint8_t byte;

typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;
typedef int64_t int64;
typedef uint64_t uint64;

typedef __int64 INT_PTR, * PINT_PTR;
typedef unsigned __int64 UINT_PTR, * PUINT_PTR;

typedef __int64 LONG_PTR, * PLONG_PTR;
typedef unsigned __int64 ULONG_PTR, * PULONG_PTR;

typedef struct {
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

#include <string>
#include <memory>

namespace TE
{
    using Name = std::string;
}

namespace TEStd
{
    template<typename T>
    using RefCountedPtr = std::shared_ptr<T>;

    using string = std::string;
}
