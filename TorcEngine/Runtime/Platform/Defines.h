#pragma once

#ifdef TORC_PLATFORM_WIN64
#define GetProcessAddress(pluginInstance, functionName) ::GetProcAddress(pluginInstance, functionName)
#define FreeLibrary(pluginInstance) ::FreeLibrary(pluginInstance);
#endif 

#define MAX_PATH_LENGTH 256
