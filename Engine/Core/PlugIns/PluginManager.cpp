#include "PluginManager.h"
using namespace Machi::PlugIns;
IPlugIn* PlugInManager::load_plugin_by_name(MSTRING& name)
{
	return nullptr;
}

bool PlugInManager::unload_plugin_by_name(MSTRING& name)
{
	return false;
}

bool PlugInManager::unload_plugin_by_object(IPlugIn* iplug)
{
	return false;
}
