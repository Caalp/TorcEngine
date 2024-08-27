#pragma once

#include <Core/Base.h>
#include <Core/TorcStd/Containers/freelist.h>
#include <typeinfo>
#include <functional>

static constexpr uint32 k_invalidHandle = UINT32_MAX;

/*
* Currently using algorithm presented from here. 
*  TODO(cagri): test and replace this later.
* https://stackoverflow.com/questions/48896142/is-it-possible-to-get-hash-values-as-compile-time-constants
*/
template <typename T>
constexpr size_t HashString(const T& toHash)
{
	// For this example, I'm requiring size_t to be 64-bit, but you could
	// easily change the offset and prime used to the appropriate ones
	// based on sizeof(size_t).
	static_assert(sizeof(size_t) == 8);

	// FNV-1a 64 bit algorithm
	size_t result = 0xcbf29ce484222325; // FNV offset basis
	for (char c : toHash) {
		result ^= c;
		result *= 1099511628211; // FNV prime
	}
	return result;
}

struct ResourceHandle
{
	union {
		uint32 handle;
		struct
		{
			uint32 idx : 24;
			uint32 cycle : 8;
		};
	};
	size_t id;
};

static bool IsValid(ResourceHandle handle) { return handle.handle != k_invalidHandle; };

#define IMPLEMENT_HANDLE(_name)\
	struct _name { union {\
					uint32 handle;\
					struct{\
					uint32 idx : 24;\
					uint32 cycle : 8;\
					};\
					};\
				  static constexpr size_t type_id = HashString(std::string_view(#_name));\
				  operator ResourceHandle() const {return {handle, type_id};}\
				};\
	static bool IsValid(_name handle) { return handle.handle != k_invalidHandle;}

IMPLEMENT_HANDLE(BlendStateHandle)
IMPLEMENT_HANDLE(RasterizerStateHandle)
IMPLEMENT_HANDLE(SamplerStateHandle)
IMPLEMENT_HANDLE(DepthStencilStateHandle)
IMPLEMENT_HANDLE(RenderTargetHandle)
IMPLEMENT_HANDLE(ViewPortHandle)
IMPLEMENT_HANDLE(BufferHandle)
IMPLEMENT_HANDLE(ShaderHandle)
IMPLEMENT_HANDLE(TextureHandle)
IMPLEMENT_HANDLE(ShaderResourceHandle)

template<uint32_t MaxCapacity>
class THandleRegistry
{
	using TKey = uint32;

	struct Key
	{
		union
		{
			TKey id;
			struct
			{
				TKey handle : 24;
				TKey cycle : 8;
			};
		};

		bool operator==(Key rhs) { return this->id == rhs.id; }
	};

public:
	THandleRegistry()
		: m_maxValue(0)
		, m_handles()
	{

	}

	TKey Allocate()
	{
		Key* handle = m_handles.Allocate();
		if (handle == nullptr)
		{
			return k_invalidHandle;
		}
		if (handle->id > 0 && handle->handle < m_maxValue)
		{
			handle->cycle += 1;
		}
		else
		{
			handle->handle = m_maxValue++;
			handle->cycle = 1;
		}
		return (*handle).id;
	}

	TKey Release(TKey handle)
	{
		m_handles.Release(Key{ handle });
		return k_invalidHandle;
	}

private:
	uint32 m_maxValue;
	FreeList<Key, MaxCapacity> m_handles;
};