#include "RPI/FrameGraph/Pass.h"

Pass::Pass(const char* passName) 
	: m_passName(passName)
	, m_isLinked(false)
{}

Pass::Pass(const PassDescriptor& descriptor)
	: m_descriptor(descriptor)
{

}

const std::string& Pass::GetName() const
{
	return m_passName;
}