#include "components_config.h"
#include "IComponent.h"
#include <Geometry/Material.h>
namespace Machi {



	namespace Components {



		class  IRendererComponent : public IComponent {

			bool m_is_visible;

		public:




			virtual void initialize() = 0;
			virtual void finalize() = 0;
			virtual void add_material(Machi::Geometry::Material* mat) = 0;
		};



	}
}