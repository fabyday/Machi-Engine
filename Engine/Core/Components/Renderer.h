#include "components_config.h"
#include "IComponent.h"
namespace Machi {



	namespace Components {



		class MACHI_COMPONENTS_API RendererComponent : public IComponent {

			bool m_is_visible;
			void render();

		public:


		};



	}
}