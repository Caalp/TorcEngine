#include "RPI/RasterizerState.h"

namespace RPI
{
	RasterizerState::RasterizerState(const Torc::RHI::RasterizerDescription& desc)
		: m_desc(desc)
	{
	}

	void* RasterizerState::GetDesc() const
	{
		return (void*)&m_desc;
	}

	void RasterizerState::Bind()
	{
	}
}
