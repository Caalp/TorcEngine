#include "Technique.h"
#include "Step.h"

Technique::Technique(const char* techName)
	: m_name(techName)
	, m_isActive(true)
{}

Technique::Technique(const char* techName, uint32 techChannel, bool isActive)
	: m_name(techName)
	, m_isActive(isActive)
	, m_channel(techChannel)
{}

void Technique::Link(RenderGraph& rg)
{
	// Link each step to its target pass
	for (auto& s : m_steps)
	{
		s.Link(&rg);
	}
}

void Technique::Submit()
{
	if (!m_isActive)
	{
		return;
	}

	for (auto& s : m_steps)
	{
		//s.Submit(d);
	}
}

Technique::TechID Technique::GetID() const
{
	return m_id;
}

void Technique::AddStep(const Step* step)
{
	//assert(this->step == nullptr);
	m_steps.push_back(*step);
}

const char* Technique::GetName() const
{
	return m_name;
}