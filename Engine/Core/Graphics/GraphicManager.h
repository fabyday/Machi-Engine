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

#ifndef __GRAPHIC_MANAGER_H__
#define __GRAPHIC_MANAGER_H__

#include "primitive.h"
#include <Platform/types.h>
#include "../Application/application.h"

namespace Machi{

class GraphicManager {
// Platform dependents
private : 
	static GraphicManager* manager_;
	GraphicsContext* graphics_context_;
	static const MUINT frame_count_= 2;
	
	SyncronizeObejct* syncronize_object_;

	friend Machi::Application;

	int n_frame_;


	//only called in Application
	virtual void initialize(Machi::Application* app);
	virtual void render();
	virtual void destroy();
	GraphicManager() :n_frame_(1) {};

public : 
	static GraphicManager* get_instance();
	

	bool regist_renderer();
	Buffer* make_buffer();
	BufferView* make_buffer_view(Buffer& buf);



        };
}
#endif