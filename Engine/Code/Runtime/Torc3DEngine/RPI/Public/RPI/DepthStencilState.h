#pragma once
#include "IGPUResource.h"

namespace RPI
{
	class DepthStencilState : public IGPUResource
	{
	public:
		enum DSSType
		{
			Default,
			Mirror,
			DrawReflection,
			NoDoubleBlend,
			NoDepthWrite,
			LessOrEqual
		};

		DepthStencilState(const Torc::RHI::DepthStencilDescription& dssDesc);
		virtual void* GetDesc() const override;
		virtual void Bind() override;
	private:
		Torc::RHI::DepthStencilDescription m_desc;
	};
}
