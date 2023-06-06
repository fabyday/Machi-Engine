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

#ifndef __GRAPHIC_MANAGER_H__
#define __GRAPHIC_MANAGER_H__

#include <Platform/types.h>
#include "graphics_config.h"

#include <DX12-RHI/NativeGraphicsManager.h>

#include <memory>

#include "primitive.h"
#include "Renderer.h"
#include "Buffer.h"

namespace Machi {
	namespace Graphics {
		class MACHI_GRAPHICS_API GraphicManager {
			// Platform dependents
		private:
			static GraphicManager* manager_;


			GraphicsContext* graphics_context_;
			static const MUINT frame_count_ = 2;

			SyncronizeObejct* syncronize_object_;

			char* device_name;

			int n_frame_;

			friend class Application;
			//only called in Application
			virtual void initialize();
			virtual void render();
			virtual void destroy();



			GraphicManager() :n_frame_(0) {};

			bool regist_renderer();
			Buffer* make_buffer();

		public:
			static GraphicManager* get_instance();



			std::shared_ptr<Renderer> make_renderer();



		};
	}
}
#endif