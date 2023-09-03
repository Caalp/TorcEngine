#include "pch.h"
#include "PluginLoader.h"
#include "Core/Plugins/Plugin.h"
#include "Core/Plugins/PluginRegistry.h"

using namespace Torc;

namespace
{
	static PluginLoader* s_pluginLoader;
}

PluginLoader* PluginLoader::GetInstance()
{
	if (s_pluginLoader == nullptr)
	{
		s_pluginLoader = new PluginLoader;
	}
	return s_pluginLoader;
}

bool Torc::PluginLoader::Release()
{
	delete s_pluginLoader;

	return true;
}

void Torc::PluginLoader::LoadPlugins()
{
	for (auto elem : pluginRegistry)
	{
		Load(elem.first, elem.second.first, elem.second.second);
	}
}

Plugin* Torc::PluginLoader::GetPlugin(const char* name)
{
	auto plugin = m_plugins.find(name);
	if (plugin == m_plugins.end())
	{
		return nullptr;
	}
	return plugin->second;
}

void Torc::PluginLoader::Load(const char* name, const char* initFunc, const char* releaseFunc)
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

Torc::PluginLoader::~PluginLoader()
{
	for (auto& [key, val] : m_plugins)
	{
		delete val;
	}
	m_plugins.clear();
}

