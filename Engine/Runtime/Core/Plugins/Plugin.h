#pragma once

class Plugin
{
	typedef bool (*INITIALIZE_PLUGIN)(void** obj);
	typedef bool (*RELEASE_PLUGIN)(void** obj);
public:
	Plugin(const char* pluginDLL, const char* initFunc, const char* releaseFunc);
	~Plugin();

	void Load();
	void CallInitialize(void** obj);

	void* GetPlugin() const;
	const char* GetPluginName() const;

private:
	void* m_object; // initialized object
	void* m_pluginInstance;
	const char* m_pluginName;
	const char* m_initFunc;
	const char* m_releaseFunc;
	INITIALIZE_PLUGIN m_pluginInitFunc;
	RELEASE_PLUGIN m_pluginReleaseFunc;
};