#pragma once
#include "RPI/FrameGraph/RenderQueuePass.h"

class SkyBoxPass :public RasterPass
{
public:
	SkyBoxPass(const PassDescriptor& desc);

	static Pass* Create(const PassDescriptor& desc);
	static TEStd::RefCountedPtr<PassTemplate> CreatePassTemplate();
	void Execute() override;
	void Reset() override;
private:


};