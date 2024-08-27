#include "Module.h"
#include "Core/Platform/PlatformDefines.h"

#include <Windows.h>
#include <stdlib.h>

Plugin::Plugin(const char* pluginDLL, const char* initFunc, const char* releaseFunc)
	: m_pluginName(pluginDLL)
	, m_initFunc(initFunc)
	, m_releaseFunc(releaseFunc)
	, m_object(nullptr)
{}

Plugin::~Plugin()
{
	if (m_object != nullptr)
	{
		m_pluginReleaseFunc(&m_object);
	}
	TE_FreeLibrary((HINSTANCE)m_pluginInstance);
}

void* Plugin::GetPlugin() const
{
	return m_pluginInstance;
}

const char* Plugin::GetPluginName() const
{
	return m_pluginName;
}

void Plugin::Load()
{
	m_pluginInstance = LoadLibraryA(m_pluginName);
	if (m_pluginInstance == NULL)
	{
		// oh no
		exit(1);
	}
	m_pluginInitFunc = (INITIALIZE_PLUGIN)TE_GetProcessAddress((HINSTANCE)m_pluginInstance, m_initFunc);

	//Release DLL if we werent able to get the function
	if (m_pluginInitFunc == NULL)
	{
		TE_FreeLibrary((HINSTANCE)m_pluginInstance);
		// complain
		exit(1);
	}
	m_pluginReleaseFunc = (INITIALIZE_PLUGIN)TE_GetProcessAddress((HINSTANCE)m_pluginInstance, m_releaseFunc);

	//Release DLL if we werent able to get the function
	if (m_pluginReleaseFunc == NULL)
	{
		TE_FreeLibrary((HINSTANCE)m_pluginInstance);
		// complain
		exit(1);
	}
}

void Plugin::CallInitialize(void** obj)
{
	// order matters here since initialize function 
	// initialized the pointer pointed by obj and later we will release it
	m_pluginInitFunc(obj);
	m_object = *obj;
}