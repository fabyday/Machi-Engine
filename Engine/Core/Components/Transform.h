#include "components_config.h"
#include "IComponent.h"
#include <Platform/types.h>
namespace Machi {



	namespace Components {



		class MACHI_COMPONENTS_API Transform : public IComponent {
			
			
			MDOUBLE m_loc_xyz[3]; // location
			MDOUBLE m_rot_xyz[3];// euler angle



			



		};



	}
}