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
#ifndef  __APPLICATION_H__
#define __APPLICATION_H__


#include <Platform/config.h>
#include <Platform/types.h>
#include <Platform/inputs.h>
namespace Machi {

	class MACHI_API Application {


	private:
		static Application* app_;
		MSTRING app_name_;
		time_t time_;
		bool fullscreen_;
		// platform dependents!
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		/// 
		/// 
		/// 

	public:
		bool _initialize();
		bool _run_logic();
		bool _finalize();
		bool run(int argc, char** argv);


		~Application() {};



		static Application* get_instance() {
			if (app_ == nullptr) {
				app_ = new Application();
			}
			return new Application();
		};

		Application* set_resolution(MINT width, MINT height, bool fullscreen);
		Application* set_resolution(MINT x, MINT y, MINT width, MINT height, bool fullscreen);
		Application* set_name(MSTRING name);

		const MSTRING& get_appname() const { return app_name_; };

		inline int get_x_pos() const { return x_; }
		inline int get_y_pos() const { return y_; }
		inline int get_width() const { return width_; }
		inline int get_height() const { return height_; }
		inline bool is_full_screen() const { return fullscreen_; }


		Application() {};
		//size configuration
		int x_, y_, width_, height_;


	public:
		virtual bool update();
		virtual bool fixed_update();
		
		virtual bool render();
		
		
		
		/*virtual bool on_key_pressed();
		virtual bool on_key_clicked();
		virtual bool on_key_released();
		*///

	};


}
#endif // ! __APPLICATION_H__ 