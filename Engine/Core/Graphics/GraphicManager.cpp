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


#include "GraphicManager.h"
#include <Logger/Logger.h>
#include <Components/ComponentManager.h>

using namespace Machi::Graphics;
using namespace Machi;
GraphicManager* GraphicManager::manager_ = nullptr;

GraphicManager*
GraphicManager::get_instance() {
	if (GraphicManager::manager_ == nullptr) {
		GraphicManager::manager_ = new GraphicManager();
	}
	return GraphicManager::manager_;
}

std::shared_ptr<Renderer> GraphicManager::make_renderer()
{
	std::shared_ptr<Renderer> p = std::shared_ptr<Renderer>();
	regist_renderer(p);
	return p;
}


bool GraphicManager::regist_renderer(std::shared_ptr<Renderer> regist_renderer)
{
	if (regist_renderer.get() == nullptr)
		return false;
	m_registed_renderer.push_back(regist_renderer);

	return true;
}


void
GraphicManager::initialize() {
	auto& logger = Machi::Logger::MLogger::get_instance();
	logger.info(MACHI_DEFAULT_CONSOLE_LOGGER_NAME, MTEXT("Graphics::initialize : init graphcis Manager"));
	NativeGraphics::NativeGraphicsManager::get_instance()->initialize();
}


void
GraphicManager::render() {
	auto& logger = Logger::MLogger::get_instance();
	// for testing.
	for (auto iter = m_registed_renderer.begin(); iter != m_registed_renderer.end(); iter++) {

		NativeGraphics::NativeGraphicsManager::get_instance()->render();
	}

	


	logger.debug(MACHI_DEFAULT_CONSOLE_LOGGER_NAME, MTEXT("render ed"));
}

void
GraphicManager::destroy() {


}




Buffer*
GraphicManager::make_buffer() {
    return nullptr;
}
