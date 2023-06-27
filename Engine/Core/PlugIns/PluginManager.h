#include "Iplugin.h"
#include "plugins_config.h"
#include <Platform/types.h>
#include <vector>
namespace Machi {
	namespace PlugIns {
		class MACHI_PLUGINS_API PlugInManager {



			PlugInManager* manager_;
			std::vector<IPlugIn*> m_plugins;
		public:
			PlugInManager* get_instance() {
				if( manager_ == nullptr)
					manager_ = new PlugInManager;
				return manager_;
			}



			IPlugIn* load_plugin_by_name(MSTRING& name);
			bool unload_plugin_by_name(MSTRING& name);
			bool unload_plugin_by_object(IPlugIn* iplug);

		};
	}
}