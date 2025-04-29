#pragma once
#include "IGPUResource.h"

namespace RPI
{
	class RasterizerState : public IGPUResource
	{
	public:
		enum RasterizerType
		{
			Default,
			NoCull,
			CullClockwise,
			Wireframe
		};
		RasterizerState(const Torc::RHI::RasterizerDescription& desc);
		virtual void* GetDesc() const override;
		virtual void Bind() override;
	private:
		Torc::RHI::RasterizerDescription m_desc;
		RasterizerType m_rsType;
	};
}
