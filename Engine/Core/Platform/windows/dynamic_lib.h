#pragma once 
#include "config.h"
#include "types.h"

namespace Machi {


	namespace Platform {


		struct DLLFunctions {






		};



		MUINT load_dynamic_library(MSTRING& dll_name);
		bool release_dynamic_library(MSTRING& name);
	}
}