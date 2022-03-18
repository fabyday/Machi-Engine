
#include <Windows.h>

#include "types.h"
#include "inputs.h"





#define UNIVERSAL_APPLICATION WinApplication

class UNIVERSAL_APPLICATION {


public:
	using string = std::string;
	virtual ~UNIVERSAL_APPLICATION() {};
	
	bool run_OS_specific();
	bool run(int argc, char** argv);




	static UNIVERSAL_APPLICATION* get_instance() {
		if (app_ == nullptr) {
			app_ = new UNIVERSAL_APPLICATION();
		}
		return app_;
	};

private:

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static UNIVERSAL_APPLICATION* app_;
	string app_name_;
	time_t time_;
	HINSTANCE hinstance_;

	//viewport
	
	MUINT x_, y_, width_, height_;
	HWND hwnd_;
	bool _initialize();
	bool _run_logic();
	bool _finalize();

protected:
	virtual bool update();
	virtual bool fixed_update();
	virtual bool render();

};
