#include "ModuleManager.h"
#include "Core/Module/Module.h"
#include "Core/Logging/Logger.h"

namespace Torc
{
	Module* ModuleManager::CreateModule(const char* moduleName)
	{
		void* moduleInstance = Platform::LoadDLL(moduleName);
		if (moduleInstance == NULL)
		{
			// oh no
			TE_Error(LogChannel::LC_Core, "Couldn't load the module %s", moduleName);
		}
		Std::string methodName = (Std::string{ "CreateModule_" } + Std::string{ moduleName });
		Module::InitFunc initFunc = (Module::InitFunc)Platform::RetrieveMethodFromDLL(moduleInstance, methodName.c_str());

		//Release DLL if we werent able to get the function
		if (initFunc == NULL)
		{
			Platform::FreeDLL(moduleInstance);
			TE_Error(LogChannel::LC_Core, "Couldn't retrieve method %s from module %s", methodName.c_str(), moduleName);
		}

		if (m_modulesMap.find({ moduleName }) != m_modulesMap.end())
		{
			m_modulesMap[ModuleName{moduleName}] = initFunc(moduleName);
		}
		return m_modulesMap[ModuleName{ moduleName }];
	}

	Module* ModuleManager::GetModuleByName(const char* name)
	{
		auto module = m_modulesMap.find(name);
		if (module == m_modulesMap.end())
		{
			return nullptr;
		}
		return module->second;
	}
}
