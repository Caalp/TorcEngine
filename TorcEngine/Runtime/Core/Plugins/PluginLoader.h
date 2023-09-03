#pragma once


namespace Torc
{
	class Plugin;

	class PluginLoader
	{
	public:
		static PluginLoader* GetInstance();
		static bool Release();
	
		void LoadPlugins();
		Plugin* GetPlugin(const char* name);

	private:
		void Load(const char* name, const char* initFunc, const char* releaseFunc);
		PluginLoader() = default;
		~PluginLoader();
	private:
		std::map<std::string, Plugin*> m_plugins;
	};
}
