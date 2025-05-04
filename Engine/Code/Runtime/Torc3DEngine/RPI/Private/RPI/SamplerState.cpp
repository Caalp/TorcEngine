#include "RPI/SamplerState.h"

namespace RPI
{
	SamplerState::SamplerState(const Torc::RHI::SamplerDescription& desc)
		: m_desc(desc)
	{
	}

	void* SamplerState::GetDesc() const
	{
		return (void*)&m_desc;
	}

	void SamplerState::Bind()
	{
	}
}
