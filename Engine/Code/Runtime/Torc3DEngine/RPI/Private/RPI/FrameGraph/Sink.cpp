#include "RPI/FrameGraph/Sink.h"


Sink::Sink(const char* sinkName)
	: m_sinkName(sinkName)
{
}

void Sink::SetPassName(const char* passName)
{
	m_sinkPassName = passName;
}

void Sink::SetTargetName(const char* targetName)
{
	m_sinkTargetName = targetName;
}

const char* Sink::GetName() const
{
	return m_sinkName;
}

const char* Sink::GetPassName() const
{
	return m_sinkPassName;
}

const char* Sink::GetTargetName() const
{
	return m_sinkTargetName;
}