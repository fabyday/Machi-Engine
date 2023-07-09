
#ifndef MACHI_ENGINE_INPUTS_H
#define MACHI_ENGINE_INPUTS_H
#include "platform_config.h"
#include "types.h"

#if defined(__APPLE__)
//#include ""
#elif defined(_WIN64) || defined(_WIN32)
#include "windows/inputs.h"
#endif
namespace Machi {


	namespace Platform {

		class MACHI_PLATFORM_API InputManager { // key & mouse Input manager

			static InputManager* _instance;
		

			enum class state {MACHI_KEY_PRESSED, MACHI_KEY_RELEASED};
		public:
			static InputManager& get_instance() {
				if (_instance == nullptr) {
					_instance = new InputManager();
				}
				return *_instance;
			}

			bool notify_key(MUINT key, state key_state); // this is called main loop
			void add_key_listener();
			
			
		};


	}
}


#endif //MACHI_ENGINE_INPUTS_H