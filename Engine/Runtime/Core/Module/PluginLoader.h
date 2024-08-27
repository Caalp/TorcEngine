#pragma once
#include "Core/TorcSystem/ISystem.h"
#include <map>

class Plugin;

class PluginLoader
{
public:
	PluginLoader() = default;

	bool Initialize(SystemGlobalEnvironment& env);
	void Release();

	void LoadPlugins();
	Plugin* GetPlugin(const char* name);

private:
	void Load(const char* name, const char* initFunc, const char* releaseFunc);
	
private:
	std::map<std::string, Plugin*> m_plugins;
};