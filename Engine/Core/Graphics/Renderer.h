#pragma once
#include "graphics_config.h"



#include <Geometry/Mesh.h>
#include "IResource.h"
#include "Buffer.h"
#include "Texture.h"

 
namespace Machi {

	namespace Graphics {


		class MACHI_GRAPHICS_API Renderer {

			


			std::vector<std::shared_ptr<Machi::Geometry::Mesh>> m_mesh;
			std::vector<std::shared_ptr<IResource>> m_resource; 

		public:
			std::shared_ptr<Machi::Geometry::Mesh> get_mesh();
			Renderer& set_static_mesh(std::shared_ptr<Machi::Geometry::Mesh> m_mesh);

			//Renderer& connect_to();
			//Renderer& disconnect_to();



		};



	}
}