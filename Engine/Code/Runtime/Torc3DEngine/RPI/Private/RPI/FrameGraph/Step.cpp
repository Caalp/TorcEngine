#include "RPI/FrameGraph/Step.h"
#include "RPI/FrameGraph/RenderGraph.h"

#include <Core/Logging/Logger.h>
#include <RHI/HandleRegistry.h>

Step::Step(const char* targetPassName) 
	: m_targetPassName(targetPassName)
	, m_targetPass(nullptr)
	, m_isLinked(false)
{}

void Step::AddBindable(ResourceHandle bindableResource)
{
	//m_bindables.push_back(bindableResource);
}

void Step::AddBindable(IGPUResource* bindable)
{
	m_bindables.push_back(bindable);
}

void Step::SetDrawCommand(DrawCommand* drawCmd)
{
	m_drawCommand = drawCmd;
}

void Step::Submit()
{
	//m_targetPass->Accept(Job{ *this,d });
}

void Step::Link(RenderGraph* rg)
{
	if (!m_targetPass)
	{
		RenderQueuePass* rqp = rg->GetRenderQueuePass(m_targetPassName);
		if (rqp == nullptr)
		{
			TE_TraceInfo("Target RenderPass %s is not found!", m_targetPassName);
			return;
		}
		m_targetPass = rqp;
	}
}

void Step::Bind() const
{
	//OutputDebugString(typeid(mDrawFunc.get()).name());
	//DrawExample* dw = dynamic_cast<DrawExample*>(mDrawFunc.get());
	/*for (auto& elem : bindables)
	{
		elem->Bind(gfx);
	}*/
}

void Step::Draw() const
{
}

const char* Step::GetTargetPassName() const
{
	return m_targetPassName;
}

bool Step::IsLinked() const
{
	return m_isLinked;
}