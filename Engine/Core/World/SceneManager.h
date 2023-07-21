#include "world_config.h"
#include <Components/ComponentManager.h>
#include <memory>
#include "Scene.h"
namespace Machi {
	namespace World {



		class MACHI_WORLD_API SceneManager {
			std::shared_ptr<Scene> m_current_scene;
			//std::shared_ptr<Scene> m_default_scene;
			static SceneManager* _scene_manager_instance;

			std::shared_ptr<Scene> get_current_scene() {
				return m_current_scene;
			}


			SceneManager* get_instance() {
				if (_scene_manager_instance == nullptr) {
					_scene_manager_instance = new SceneManager;
				}
				return this;
			}
			


		};
	}
}