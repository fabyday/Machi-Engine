#pragma once
#include "components_config.h"

namespace Machi {



	namespace Components {



		 class  IComponent    {



			
			virtual void initialize() = 0;




			virtual void finalize() = 0;




		};



	}
}