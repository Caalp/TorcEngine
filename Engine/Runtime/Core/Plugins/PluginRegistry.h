#pragma once
#include <set>

static std::set<std::pair<const char*,std::pair<const char*, const char*>>> pluginRegistry = {
	{"DX11.dll", {"InitializeGfxBackendPlugin", "ReleaseGfxBackendPlugin"}}
};