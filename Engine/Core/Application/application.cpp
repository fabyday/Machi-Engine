//MIT License
//Copyright(c) 2022 Ji Hyun Roh
//
//
//Permission is hereby granted, free of charge, to any person
//obtaining a copy of this softwareand associated documentation
//files(the "Software"), to deal in the Software without
//restriction, including without limitation the rights to use,
//copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the
//Software is furnished to do so, subject to the following
//conditions :
//
//The above copyright noticeand this permission notice shall be
//included in all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//OTHER DEALINGS IN THE SOFTWARE.
#include "application.h"
#include <iostream>

Machi::Application* Machi::Application::app_ = nullptr;


bool
Machi::Application::render() {
	return true;
}



//bool
//Machi::Application::update() {
//	return true;
//}


bool
Machi::Application::fixed_update() {
	return true;
}


Machi::Application*
Machi::Application::set_resolution(MINT x, MINT y, MINT width, MINT height, bool fullscreen) {
	this->x_ = x; this->y_ = y;
	this->width_ = width; this->height_ = height;
	this->fullscreen_ = fullscreen;

	return this;
}




Machi::Application*
Machi::Application::set_resolution(MINT width, MINT height, bool fullscreen) {
	return set_resolution(0, 0, width, height, fullscreen);
}



Machi::Application*
Machi::Application::set_name(MSTRING name) {
	this->app_name_ = name;
	return this;
}




bool Machi::Application::_initialize(){

    return true;
}
bool Machi::Application::_run_logic(){

    return true;
}

bool Machi::Application::_finalize(){
    return true;
}
bool Machi::Application::run(int argc, char** argv){
    return true;
}


