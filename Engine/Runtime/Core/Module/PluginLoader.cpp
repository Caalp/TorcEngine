#include "PluginLoader.h"
#include "Core/Module/Module.h"
#include "Core/Module/PluginRegistry.h"
#include "Core/TorcSystem/ISystem.h"

bool PluginLoader::Initialize(SystemGlobalEnvironment& env)
{
	env.pluginLoader = this;
	return true;
}

void PluginLoader::Release()
{
	for (auto& [key, val] : m_plugins)
	{
		delete val;
	}
	m_plugins.clear();
}

void PluginLoader::LoadPlugins()
{
	for (auto elem : pluginRegistry)
	{
		Load(elem.first, elem.second.first, elem.second.second);
	}
}

Plugin* PluginLoader::GetPlugin(const char* name)
{
	auto plugin = m_plugins.find(name);
	if (plugin == m_plugins.end())
	{
		return nullptr;
	}
	return plugin->second;
}

void PluginLoader::Load(const char* name, const char* initFunc, const char* releaseFunc)
{
	// TODO: after this check we can add another check if given function is loaded
	// if we are loading different function from given dll, this should be allowed 
	// which is currently not supported.
	if (m_plugins.find(name) != m_plugins.end())
	{
		// plugin is already loaded
		return;
	}
	Plugin* plugin = new Plugin(name, initFunc, releaseFunc);
	plugin->Load();
	m_plugins[name] = plugin;
}