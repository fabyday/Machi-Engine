#include <Platform/types.h>
#include <Platform/inputs.h>
#include <functional>
class InputManager {
	
	
	enum KeyState {
		KeyPressed,
		KeyReleased,
		KeyClicked
	};
private:
	MUINT m_key;
	



public:

	MUINT add_mouse_drag_listener(std::function<void(MUINT key)>);
	MUINT add_mouse_clicked_listener(std::function<void(MUINT key)>);
	MUINT add_mouse_released_listener(std::function<void(MUINT key)>);
	MUINT add_mouse_pressed_listener(std::function<void(MUINT key)>);

	MUINT add_key_release_listener(std::function<void(MUINT key)>);
	MUINT add_key_pressed_listener(std::function<void(MUINT key)>);
	MUINT add_key_clicked_listener(std::function<void(MUINT key)>);
	bool remove_listener(MUINT handle);

};