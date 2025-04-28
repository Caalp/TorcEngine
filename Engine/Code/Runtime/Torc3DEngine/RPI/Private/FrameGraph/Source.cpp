#include "Source.h"

//std::string& Source::GetSinkName() const
//{
//	// TODO: insert return statement here
//}

Source::Source(const char* sourceName)
	: m_name(sourceName)
{
}

const char* Source::GetName() const
{
	return m_name;
}

//std::shared_ptr<BufferResource> Source::GetSource()
//{
//	return std::shared_ptr<BufferResource>();
//}
