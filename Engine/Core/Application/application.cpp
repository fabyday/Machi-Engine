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
#include "application.h"
#include <iostream>
#include <Graphics/GraphicManager.h>
#include <Logger/Logger.h>
Machi::Application* Machi::Application::app_ = nullptr;


bool
Machi::Application::render() {


	using namespace Machi::Graphics;
	auto gmng = GraphicManager::get_instance();
	gmng->render();
	return true;
}

bool
Machi::Application::update() {
	return true;
}


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




void Machi::Application::calc_delta()
{
	const MTIME tmp_cur_time = Machi::Platform::g_platform->get_cur_time();
	m_delta_time = Machi::Platform::g_platform->get_cur_time() - m_prev_time;
	m_prev_time = tmp_cur_time;
}

bool Machi::Application::_initialize() {
	using namespace Machi;
	auto& logger = Machi::Logger::MLogger::get_instance();
	logger.info(MACHI_DEFAULT_CONSOLE_LOGGER_NAME, "Application::_initialize : init device.");



	Graphics::GraphicManager::get_instance()->initialize();
	
	
	
	
	logger.info(MACHI_DEFAULT_CONSOLE_LOGGER_NAME, "Application::initialize : init main game.");
	logger.info(MACHI_DEFAULT_CONSOLE_LOGGER_NAME, "Application::initialize : init game clock.");

	m_total_game_time = 0;
	m_game_world_time = 0;
	m_fixed_update_time_checker = 0;
	m_prev_time = Machi::Platform::g_platform->get_cur_time();
	this->initialize();
	return true;
}
bool Machi::Application::_run_logic() {

	auto& logger = Machi::Logger::MLogger::get_instance();
	calc_delta();
	const MTIME delta_time = get_delta_time();
	m_total_game_time += delta_time;
	m_fixed_update_time_checker += delta_time;

	if(!m_is_paused)
		m_game_world_time += delta_time;
	
	//logger.debug(MACHI_DEFAULT_CONSOLE_LOGGER_NAME,"delta time : {} m_fixed_time {}", delta_time, m_fixed_update_time_checker);
	if (m_fixed_update_time_checker >= get_fixed_upate_time()) {
		fixed_update();
		m_fixed_update_time_checker = 0;
	}

	update();

	Graphics::GraphicManager::get_instance()->render();

	return true;
}

bool Machi::Application::_finalize() {
	this->finalize();
	return true;
}
//bool Machi::Application::run(int argc, char** argv){
//	this->initialize();
//
//    return true;
//}


