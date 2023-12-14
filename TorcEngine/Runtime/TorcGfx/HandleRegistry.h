#pragma once
#include "Core/Common/Containers/FreeList.h"
#include <typeinfo>
#include <functional>

static constexpr uint16_t k_invalidHandle = UINT16_MAX;

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
	uint16 idx;
	uint16 cycle;
	size_t id;
};

static bool IsValid(ResourceHandle handle) { return handle.idx != k_invalidHandle; };

#define IMPLEMENT_HANDLE(_name)\
	struct _name { uint16 idx {UINT16_MAX};\
				   uint16 cycle {UINT16_MAX};\
				  static constexpr size_t type_id = HashString(std::string_view(#_name));\
				  operator ResourceHandle() const {return {idx, cycle, type_id};}\
				};\
	static bool IsValid(_name handle) { return handle.idx != k_invalidHandle;}

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

template<uint32_t Count>
class HandleRegistry
{
public:
	HandleRegistry()
		: m_maxHandleCount(Count)
		, m_handles()
	{
		// initialize freelist with index values beforehand
		for (int i = 0; i < Count; i++)
		{
			uint16_t* val = m_handles.Next();
			*val = i;
		}
		m_handles.Reset();
	}

	uint16_t Allocate()
	{
		uint16_t* handle = m_handles.Allocate();
		if (handle == nullptr)
		{
			return k_invalidHandle;
		}
		return *handle;
	}

	uint16_t Release(uint16_t handle)
	{
		m_handles.Release(handle);
		return k_invalidHandle;
	}

private:
	uint16_t m_maxHandleCount;
	FreeList<uint16_t, Count> m_handles;
};