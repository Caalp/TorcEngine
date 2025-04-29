#pragma once

#ifdef PLATFORM_WINDOWS
#define TE_GetProcessAddress(pluginInstance, functionName) ::GetProcAddress(pluginInstance, functionName)
#define TE_FreeLibrary(pluginInstance) ::FreeLibrary(pluginInstance);
#endif 

#define MAX_PATH_LENGTH 256
