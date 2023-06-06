//MIT License 
//Copyright(c) 2022 fabyday
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
#pragma once

#include "windows_platform.h"
#include <Windows.h>

#include <Application/application.h>
#include <OS/OS.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <functional>


// main function hijacking.
Machi::Application* machi_main(int argc, char** argv); // User impl.

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow){
	using namespace Machi;
	/*OSConfig config;
	config.hInstance = &hInstance;
	config.hPrevInstance = &hPrevInstance;
	config.pCmdLine = pCmdLine;
	config.nCmdShow = nCmdShow;*/

	//other code
	spdlog::info("Window Platform Start...");
	Machi::g_platform = new Machi::WindowsPlatform(&hInstance, &hPrevInstance, pCmdLine, nCmdShow);
	Machi::OS::get_instance()->set_context(Machi::g_platform->get_context());
#ifdef MACHI_EDITOR_MODE

#endif // MACHI_EDITOR_MODE

	Application* app = machi_main(__argc, __argv);
	
	Machi::g_platform->update_function = std::bind(&Application::update, app);
	Machi::g_platform->fixed_update_function = std::bind(&Application::fixed_update, app);
	Machi::g_platform->render_function = std::bind(&Application::render, app);
	
	Machi::g_platform->initialize(app->get_appname().c_str(), app->get_x_pos(), app->get_y_pos(), app->get_width(), app->get_height());
	
	int ret = Machi::g_platform->run(__argc, __argv);

	delete app;

	return ret;
}