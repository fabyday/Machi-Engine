#include "geometry_config.h"
#include <DataStruct/UnsafeVector.h>
#include <Platform/types.h>
#include <vector>
namespace Machi {
	namespace Geometry {


		class MACHI_GEOMETRY_API Mesh {
		public:
			enum class element_type {
				VERTEX,
				FACE,
				NORMAL,
				TEX_COORDINATE,
			};

			enum class element_size_type {
				DEFAULT, 
				ELEM2,
				ELEM3,
				ELEM4
			};
			typedef struct mesh_attribute
			{
				MSIZE_T m_vertice_size = 0;
				MSIZE_T m_face_size = 0;
				MSIZE_T m_normal_size = 0;
				MSIZE_T m_texcoord_size = 0;
				MSIZE_T m_color_size = 0;
			}attribute;

			attribute attr;
			void* m_vertice;
			
			void* m_faces;
			void* m_face_elem_nums; // each face size;
			MUINT m_face_elem_nums_size;
			bool m_is_all_face_size_same; // if this is true, m_face_elem_nums contains just 1 elem.
			
			void* m_normals;
			void* m_tex_coord;
			void* m_color;
		public:
			Mesh() :m_vertice(NULL), m_normals(NULL), m_tex_coord(NULL), m_color(NULL), m_faces(NULL), 
				m_face_elem_nums(NULL), m_face_elem_nums_size(-1), m_is_all_face_size_same(false) 
			{};

			Mesh(MUINT vertice, MUINT face_size, MUINT normal_size) {}
			
			void allocate(element_type type, MSIZE_T size);
			
			inline bool is_allocated(element_type type) {
				switch (type) {
				case element_type::VERTEX:
				{
					if (attr.m_vertice_size)
						return true;
				}
				break;
				case element_type::FACE:
				{
					if (attr.m_face_size)
						return true;
				}
				break;
				case element_type::NORMAL:
				{
					if (attr.m_face_size)
						return true;
				}
				break;
				case element_type::TEX_COORDINATE:
				{
					if(attr.m_texcoord_size)
						return true;
				}
				break;
				}
				return false;
			}

			template<element_type t>
			struct PreDefArrayViewType {
				using   type =  Machi::DataStructure::PredefArrayView<MDOUBLE> ;
			};

			template<>
			struct PreDefArrayViewType<element_type::FACE> {
				using  type =  Machi::DataStructure::PredefArrayView<MUINT> ;
			};

			template<element_type ET>
			typename PreDefArrayViewType<ET>::type get_elem_view(MUINT index) {
				using ret_type = typename PreDefArrayViewType<ET>::type;
				if constexpr (ET == element_type::FACE) {
					return ret_type{reinterpret_cast<MUINT*>(m_faces), 3};
				}
				else if constexpr(ET == element_type::VERTEX ){
					return ret_type(reinterpret_cast<MDOUBLE*>(m_vertice) + index * 3, 3);
				}
				else if constexpr (ET == element_type::NORMAL) {
					return ret_type(reinterpret_cast<MDOUBLE*>(m_normals) + index * 3, 3);
				}
				else if constexpr (ET == element_type::TEX_COORDINATE) {
					return ret_type(reinterpret_cast<MDOUBLE*>(m_tex_coord) + index * 2, 2);
				}
			}


			bool set_face_nums(MUCHAR size);
			bool set_face_nums(const std::vector<MUCHAR>& sizes);

			MDOUBLE& get_as_array(element_type type, MUINT index);
			bool copy(element_type type, void* src, MUINT size);
		};


	}
}