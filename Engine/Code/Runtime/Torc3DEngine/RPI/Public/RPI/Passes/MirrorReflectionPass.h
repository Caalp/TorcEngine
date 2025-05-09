#pragma once
#include "RPI/FrameGraph/RenderQueuePass.h"

class MirrorReflectionPass : public RenderQueuePass
{
public:
	MirrorReflectionPass(const char* passName);
	void Execute() override;
	void Reset();
};