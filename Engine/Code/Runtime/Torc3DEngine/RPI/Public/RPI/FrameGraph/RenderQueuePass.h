#pragma once
#include "BindingPass.h"

#include <vector>

class Job;

// renderingPass
class RenderQueuePass : public BindingPass
{
public:
	using BindingPass::BindingPass;
	void Accept(const Job& job);
	void Execute();
	void Reset() override;
private:
	std::vector<Job*> jobs;
};