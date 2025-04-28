#include "Module/Module.h"

namespace Torc
{
	Module::Module(const char* moduleName)
		: m_moduleName(moduleName)
	{}

	const char* Module::GetModuleName() const
	{
		return m_moduleName;
	}
}
