#include "../../Application/application.h"




Application* machi_main(int argc, char** argv);

int main(int argc, char**argv) {
	Application* app = machi_main(argc, argv);
	bool reval = app->run(0, NULL);
	delete app;
	return reval;
}