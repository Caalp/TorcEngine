#pragma once
#include "RPI/RenderGraph/RenderQueuePass.h"

class MarkMirrorPass : public RenderQueuePass
{
public:
	MarkMirrorPass(const char* passName);
	void Execute() override;
	void Reset();
};