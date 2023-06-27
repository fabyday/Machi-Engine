namespace Machi {
	namespace Geometry {


		class Mesh {
		public:
			enum class element_type {
				VERTEX_ALLOCATE,
				FACE_ALLOCATE,
				NORMAL_ALLOCATE,
				TEX_COORDINATE_ALLOCATE,
			};


			typedef struct mesh_attribute
			{
				MUINT m_vertice_size;
				MUINT m_face_size;
				MUINT m_normal_size;
			}attr;


			void* m_vertice;
			void* m_faces;
			void* m_normals;
			void* m_tex_coord;
		public:
			Mesh();
			Mesh(MUINT vertice, MUINT face_size, MUINT normal_size){}
			void allocate(element_type type, MSIZE_T bytes);
			

		};


	}
}