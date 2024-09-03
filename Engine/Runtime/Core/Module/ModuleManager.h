#pragma once
#include "Core/TorcStd/String/string.h"
#include <map>

namespace Torc
{
	class Module;

	class ModuleManager
	{
		typedef TorcStd::string ModuleName;
	public:
		Module* CreateModule(const char* moduleName);
		Module* GetModuleByName(const char* moduleName);
	private:
		std::map<ModuleName, Module*> m_modulesMap;
	};
}
