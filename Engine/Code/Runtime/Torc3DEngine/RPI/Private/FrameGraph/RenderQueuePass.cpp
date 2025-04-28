#include "RenderQueuePass.h"
#include "Job.h"

void RenderQueuePass::Accept(const Job& job)
{
	//jobs.emplace_back(std::move(job));
}

void RenderQueuePass::Execute()
{
	BindAll();
	for (auto& job : jobs)
	{
		//job.Execute();
	}
}

void RenderQueuePass::Reset()
{
	jobs.clear();
}