#pragma once
#include "FrameGraph/RenderQueuePass.h"

class MarkMirrorPass : public RenderQueuePass
{
public:
	MarkMirrorPass(const char* passName);
	void Execute() override;
	void Reset();
};