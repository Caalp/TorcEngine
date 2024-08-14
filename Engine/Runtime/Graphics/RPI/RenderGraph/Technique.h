#pragma once
#include "Core/BaseTypes.h"

#include <vector>

class RenderGraph;
class Step;

class Technique
{
	typedef uint64 TechID;
public:
	Technique(const char* techName);
	Technique(const char* techName, uint32 techChannel, bool isActive);
	void Link(RenderGraph& rg);
	TechID GetID() const;
	void AddStep(const Step* step);
	const char* GetName() const;
	void Submit();
private:
	TechID m_id;
	const char* m_name;
	uint32 m_channel;
	bool m_isActive;
	std::vector<Step> m_steps;
};