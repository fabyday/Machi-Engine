#include "io_config.h"
#include <Platform/types.h>
#include <Geometry/Mesh.h>
namespace Machi {


	namespace IO {

		class MACHI_IO_API OBJReader {
			
		public:
			static bool read_mesh(const MSTRING& name, Machi::Geometry::Mesh* meshes, int& read_mesh_num);
			static bool write_mesh(MSTRING& name, Machi::Geometry::Mesh* mesh);




		};

	}
}