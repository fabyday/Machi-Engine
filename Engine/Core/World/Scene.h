#include "world_config.h"
#include <Components/ComponentManager.h>
#include <memory>
namespace Machi {
	namespace World {



		class MACHI_WORLD_API Scene {
			std::shared_ptr<Machi::Components::ComponentManager> m_scene_component_manager;


			void test2();
		};
	}
}