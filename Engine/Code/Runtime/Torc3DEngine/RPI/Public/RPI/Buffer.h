#pragma once
#include "IGPUResource.h"
#include <Core/Std/Threading/atomic.h>

namespace RHI
{
	class Buffer;
}

namespace RPI
{
	class RefCountedBase
	{
	public:
		virtual ~RefCountedBase()
		{

		}

		int32 GetRefCount() const
		{
			return m_refCount;
		}

	private:
		Std::atomic<int32> m_refCount;
	};

	struct BufferDescriptor
	{
		//Buffer::Type m_type;
		uint64        m_byteWidth;
		uint32        BindFlags;
		uint32        CPUAccessFlags;
		uint32        MiscFlags;
		uint32        StructureByteStride;
	};

	struct BufferView
	{

		void* data;
	};

	class Buffer : public RefCountedBase
	{
	public:
		enum class Type
		{
			ConstantBuffer,
			StagingBuffer, // for copy
			DynamicBuffer,
			VertexBuffer,
			IndexBuffer

		};

		Buffer(const BufferDescriptor& desc);
		virtual ~Buffer();
		BufferDescriptor GetDescriptor() const;

		static Buffer* CreateBuffer(const BufferDescriptor & desc);

		template<typename T>
		void CreateSubResourceAndInit(T* data, uint32 elemCount)
		{
			if (!m_desc.data)
			{
				m_desc.data = new gfx::SubResourceData;
				m_desc.data->byteWidth = sizeof(T) * elemCount;
				m_desc.data->structureByteStride = sizeof(T);
				m_desc.data->sysMem = (void*)data;
			}
			else
			{
				m_desc.data->byteWidth = sizeof(T) * elemCount;
				m_desc.data->structureByteStride = sizeof(T);
				m_desc.data->sysMem = (void*)data;
			}
		}

	protected:
		BufferDescriptor m_descriptor;
		RHI::Buffer* m_buffer;
	};
}
