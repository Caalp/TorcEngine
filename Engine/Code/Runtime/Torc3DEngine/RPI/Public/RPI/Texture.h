#pragma once
#include "IGPUResource.h"

namespace RPI
{
	class Texture : public IGPUResource
	{
	public:
		Texture(const Torc::RHI::ImageDescription& desc);
		virtual void* GetDesc() const override;
		virtual void Bind() override;
	protected:
		uint32 m_slot;
		Torc::RHI::ImageDescription m_desc;
	};
}
