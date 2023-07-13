
#ifndef MACHI_ENGINE_INPUTS_H
#define MACHI_ENGINE_INPUTS_H
#include "platform_config.h"
#include "types.h"

#if defined(__APPLE__)
//#include ""
#elif defined(_WIN64) || defined(_WIN32)
#include "windows/inputs.h"
#endif

#include <vector>
#include <functional>
namespace Machi {

	namespace Platform {

		class MACHI_PLATFORM_API InputManager { // key & mouse Input manager

			static InputManager* _instance;
		
			std::vector<std::function<bool(int, int)>> m_key_listener_functions;
			std::vector<std::function<bool(int, int)>> m_mouse_listener_functions;
			std::vector<std::function<bool(int, int)>> m_gamepad_listener_functions;
			enum class state { MACHI_KEY_PRESSED, MACHI_KEY_RELEASED, MACHI_KEY_CLICKED};
			enum class mouse_axis {MACHI_X_AXIS, MACHI_Y_AXIS};
			
		public:
			static InputManager& get_instance() {
				if (_instance == nullptr) {
					_instance = new InputManager();
				}
				return *_instance;
			}

			bool notify_key(MUINT key, state key_state); // this is called main loop
			void add_key_listener();
			bool current_query_key(MUINT key, state key_state);

			MDOUBLE get_mouse_delta_movement();
			
		};


	}
}


#endif //MACHI_ENGINE_INPUTS_H