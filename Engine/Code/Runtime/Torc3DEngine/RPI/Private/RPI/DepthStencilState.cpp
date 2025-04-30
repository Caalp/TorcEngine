#include "RPI/DepthStencilState.h"

namespace RPI
{
	DepthStencilState::DepthStencilState(const Torc::RHI::DepthStencilDescription& dssDesc)
		: m_desc(dssDesc)
	{
	}

	void* DepthStencilState::GetDesc() const
	{
		return (void*)&m_desc;
	}

	void DepthStencilState::Bind()
	{
	}
}
