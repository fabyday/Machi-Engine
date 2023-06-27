#pragma once 
#include "plugins_config.h"
#include <Platform/types.h>
#define PLUGIN_INITIALIZER(CLS_NAME)\
extern "C" MACHI_PLUGINS_API IPlugIn* create_plugin(){\
	return new CLS_NAME;\
}\





namespace Machi {
	namespace PlugIns {
		class MACHI_PLUGINS_API IPlugIn {

		public:
			virtual ~IPlugIn() {};

			virtual bool Initialize() = 0;
			virtual bool Shutdown() = 0;
			virtual void About(HWND hParent) = 0;
			virtual const MSTRING GetName() = 0;

		};
	}
}