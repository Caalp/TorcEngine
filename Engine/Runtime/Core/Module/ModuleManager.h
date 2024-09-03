#pragma once
#include "Core/Std/String/string.h"
#include <map>

namespace Torc
{
	class Module;

	class ModuleManager
	{
		typedef Std::string ModuleName;
	public:
		Module* CreateModule(const char* moduleName);
		Module* GetModuleByName(const char* moduleName);
	private:
		std::map<ModuleName, Module*> m_modulesMap;
	};
}
