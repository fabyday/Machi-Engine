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
#include "../platform_config.h"
#include "types.h"
#include <functional>
#include <timeapi.h>






namespace Machi {
	class Application; // fowoard decl
	namespace Platform {

		class WindowsPlatform;
		extern MACHI_PLATFORM_API WindowsPlatform* g_platform;

		typedef  struct MACHI_PLATFORM_API OSContext {
			HINSTANCE* hInstance;
			HINSTANCE* hPrevInstance;
			MUINT nCmdShow;
			MPWSTR pCmdLine;
		}OSConfig;



		// OS specific function and configure collection.
		class MACHI_PLATFORM_API WindowsPlatform {
		public:

			//Machi::Application* m_app;

			bool initialize(Application* app);
			//bool initialize(Machi::Application* app);
			static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			static HWND get_HWND() { return hwnd_; }

			WindowsPlatform(HINSTANCE* hInstance, HINSTANCE* hPrevInstance, MPWSTR nCmdShow, MUINT  pCmdLine) {
				WindowsPlatform::ctx_ = { hInstance, hPrevInstance, pCmdLine, nCmdShow };
			}
			//Application* m_app;
			//friend class Application;
			~WindowsPlatform() {
				_finalize();
			}

			bool _finalize();

			bool _run_logic();
			bool run(int agrc, char** argv);

			MTIME get_cur_time();


			struct OSContext* get_context();
		public:
			std::function<bool(void)> initialize_function;
			std::function<bool(void)> run_logic;
			std::function<bool(void)> finalize_function;
			//std::function<bool(void)> fixed_update_function;
			//std::function<bool(void)> render_function;

		private:



			Application* m_app;
			static void set_HWND(HWND hwnd) { hwnd_ = hwnd; }
			static HWND hwnd_;
			static struct OSContext ctx_;
		};


		typedef WindowsPlatform Platform;
	}

}