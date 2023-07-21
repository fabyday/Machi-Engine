#include "components_config.h"
#include "IComponent.h"
#include "IRenderer.h"
#include <Geometry/Material.h>
#include <Geometry/Mesh.h>
#include <Graphics/Renderer.h>
namespace Machi {



	namespace Components {



		class MACHI_COMPONENTS_API MeshRendererComponent : public IRendererComponent {

			bool m_is_visible;
			std::shared_ptr<Machi::Graphics::Renderer> m_renderer;
			std::vector<std::shared_ptr<Machi::Geometry::Material>> m_material;
			std::vector<std::shared_ptr<Machi::Geometry::Mesh>> m_meshes;
		public:
			virtual void initialize();
			virtual void finalize();
			virtual void add_material(Machi::Geometry::Material* mat);
			virtual void add_meshes(Machi::Geometry::Mesh* mesh);
		};



	}
}