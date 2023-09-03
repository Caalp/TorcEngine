#pragma once

#include "Core/Containers/FreeList.h"

static constexpr uint16_t k_invalidHandle = UINT16_MAX;

#define IMPLEMENT_HANDLE(name)\
	struct name { uint16_t idx;};\
	static bool IsValid(name handle) { return handle.idx == k_invalidHandle;}

IMPLEMENT_HANDLE(BlendStateHandle)
IMPLEMENT_HANDLE(RasterizerStateHandle)
IMPLEMENT_HANDLE(SamplerStateHandle)
IMPLEMENT_HANDLE(DepthStencilStateHandle)
IMPLEMENT_HANDLE(RenderTargetHandle)
IMPLEMENT_HANDLE(ViewPortHandle)


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