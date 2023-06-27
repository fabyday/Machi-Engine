#include "Iplugin.h"
#include <Platform/types.h>



namespace Machi {
	namespace PlugIns {
		class MACHI_PLUGINS_API IImporter : IPlugIn {

		public:
			virtual IPlugIn() = 0;
			virtual ~IPlugIn() {};

			virtual bool Initialize() = 0;
			virtual bool Shutdown() = 0;
			virtual void About(HWND hParent) = 0;
			virtual const std::string GetName() = 0;



			virtual bool import_data_from_file(MSTRING& name, ) = 0;

		}
	}
}