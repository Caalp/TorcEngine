#pragma once
#include "RPI/IGPUResource.h"

namespace RDI
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
		core::Atomic<int32> m_refCount;
	};

	struct BufferDescriptor
	{
		Buffer::Type m_type;
		uint64        m_byteWidth;
		UINT        BindFlags;
		UINT        CPUAccessFlags;
		UINT        MiscFlags;
		UINT        StructureByteStride;
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

		Buffer(const gfx::BufferDesc& desc);
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
		RDI::Buffer* m_buffer; // RDI buffer
	};
}
