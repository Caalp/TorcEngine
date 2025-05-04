#pragma once
#include "IGPUResource.h"

namespace RPI
{
	class SamplerState : public IGPUResource
	{
	public:
		SamplerState(const Torc::RHI::SamplerDescription& desc);
		virtual void* GetDesc() const override;
		virtual void Bind() override;
	private:
		Torc::RHI::SamplerDescription m_desc;
	};
}
