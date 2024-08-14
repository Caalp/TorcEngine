#pragma once
#include "RPI/IGPUResource.h"
#include "RDI/RDIShared/TorcGfxTypes.h"

class BlendState : public IGPUResource
{
public:

	struct BlendID
	{
		typedef decltype(m_resourceID) IDType;
		union
		{
			IDType id;

			struct
			{
				IDType enabled: 1;
				IDType alphaToCoverageEnabled: 1;
				IDType independentBlend: 1;
				IDType src: 5;
				IDType dst: 5;
				IDType op: 3;
				IDType srcAlpha: 5;
				IDType dstAlpha: 5;
				IDType opAlpha: 3;
				IDType colorEnable: 4;

			};
		};
	};

	enum BlendType
	{
		Default,
		Transparent,
		AlphaToCoverage,
		NoRenderTargetWrite,
		Additive
	};

	BlendState(const gfx::BlendDesc& desc);
	virtual void* GetDesc() const override;
	virtual void Bind() override;
private:
	gfx::BlendDesc m_desc;
};