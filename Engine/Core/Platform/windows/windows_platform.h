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
#include <Windows.h>
//#include <Application/application.h>

#include "types.h"
#include <functional>


typedef  struct OSContext {
	HINSTANCE* hInstance;
	HINSTANCE* hPrevInstance;
	MUINT nCmdShow;
	MPWSTR pCmdLine;
}OSConfig;




namespace Machi {

	class WindowsPlatform;
	extern WindowsPlatform* g_platform;



	// OS specific function and configure collection.
	class WindowsPlatform {
	public:
		bool initialize(const MWCHAR* name, MUINT x, MUINT y, MUINT width, MUINT height);
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		static HWND get_HWND() { return hwnd_; }
		
		WindowsPlatform(HINSTANCE* hInstance, HINSTANCE* hPrevInstance, MUINT nCmdShow, MPWSTR pCmdLine) {
			WindowsPlatform::ctx_ = { hInstance, hPrevInstance, nCmdShow, pCmdLine };
		}
		//Application* m_app;
		//friend class Application;
		~WindowsPlatform() {
			_finalize();
		}

		bool _finalize();

		bool _run_logic();
		bool run(int agrc, char** argv);


		struct OSContext* get_context();
	public:
		std::function<bool(void)> update_function;
		std::function<bool(void)> render_function;

	private:




		static void set_HWND(HWND hwnd) { hwnd_ = hwnd; }
		static HWND hwnd_;
		static struct OSContext ctx_;
	};


	typedef WindowsPlatform Platform;
}