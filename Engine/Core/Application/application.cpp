#include "application.h"
#include <iostream>
bool
Application::render() {
	return true;
}

bool
Application::run(int argc, char** argv){



	int j = 0;
	for (int j = 0; j < 10; j++) {
		std::cout << "hello world" << std::endl;
	}




	return true;
}

bool
Application::update() {
	return true;
}