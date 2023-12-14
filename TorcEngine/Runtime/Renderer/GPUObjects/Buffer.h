#pragma once
#include "Renderer/IGPUResource.h"

class Buffer : public IGPUResource
{
public:
	Buffer(const gfx::BufferDesc& desc);
	virtual ~Buffer();
	virtual void* GetDesc() const override;
	virtual void Bind() override;

	//virtual void GetConstantBufferType() const = 0;
	//virtual uint32 GetStartSlot() const = 0;
	//virtual uint32 GetNumberOfBuffers() const = 0;
	//virtual uint32 GetOffset() const = 0;
	//virtual uint32 GetStride() const = 0;
	//virtual gfx::TORC_GFX_RESOURCE_DATA_FORMAT GetFormat() const = 0;
	
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
	gfx::BufferDesc m_desc;
};