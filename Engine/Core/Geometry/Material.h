#include "geometry_config.h"
#include <Platform/types.h>
namespace Machi {
	namespace Geometry {


		class MACHI_GEOMETRY_API Material {

			MSTRING name;



			MDOUBLE ambient[3];
			MDOUBLE diffuse[3];
			MDOUBLE specular[3];
			MDOUBLE transmittance[3];
			MDOUBLE emission[3];
			MDOUBLE shininess;
			MDOUBLE ior;       // index of refraction
			MDOUBLE dissolve;  // 1 == opaque; 0 == fully transparent
			// illumination model (see http://www.fileformat.info/format/material/)
			int illum;



		}

	}
}