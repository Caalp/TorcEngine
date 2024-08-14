#pragma once
#include "RPI/IGPUResource.h"

class Buffer : public IGPUResource
{
public:
	Buffer(const gfx::BufferDesc& desc);
	virtual ~Buffer();
	virtual void* GetDesc() const override;
	virtual void Bind() override;

	static Buffer* CreateBuffer(const gfx::BufferDesc& desc);
	
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