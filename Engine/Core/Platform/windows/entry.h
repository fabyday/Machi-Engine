#include "../../Application/application.h"




Application* app;




int main() {
	app = new Application();
	bool reval = app->run(0, NULL);
	delete app;
	return reval;
}