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


#include "application_config.h"
#include <Platform/platform.h>
#include <Platform/types.h>
#include <Platform/inputs.h>
#include <Components/Renderer.h>
//#include <Platform/windows/windows_platform.h>
//#include <World/SceneManager.h>


#define SEC2MILSEC(x) ((x)*1000)
#define MIN2MILSEC(x) ((x)*SEC2MILSEC(x))
#define HOUR2MILSEC(x) ((x)*MIN2MILSEC(x))


namespace Machi {

	class MACHI_APPLICATION_API Application {


	private:
		static Application* app_;
		MSTRING app_name_;
		MTIME m_total_game_time; // it include paused time. full game time.
		MTIME m_game_world_time; // except game paused time.


		MTIME m_prev_time;

		MTIME m_delta_time;

		MTIME m_fixed_update_time;
		MTIME m_fixed_update_time_checker;
		bool m_is_paused;
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
		// this 4 method is initialized by system. 
		bool _initialize();
		bool _run_logic();
		bool _finalize();
		//bool run(int argc, char** argv);


		~Application() {
			_finalize();
		};



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
		bool is_full_screen() const { return fullscreen_; }
		void set_fullscreen(bool fullscreen) { fullscreen_ = fullscreen; }


		Application() {
			set_fixed_update_time(SEC2MILSEC(0.02f));
		};
		//size configuration
		int x_, y_, width_, height_;
		inline void set_fixed_update_time(MTIME miltime) { m_fixed_update_time = miltime; };
		inline MTIME get_fixed_upate_time() { return m_fixed_update_time; };
		inline MTIME get_delta_time() { return m_delta_time; };
		void calc_delta();

	public:
		// game app overload this method. it will be executed at first time.
		virtual bool initialize() { return false; };
		virtual bool finalize() { return false; };
		virtual bool update();
		virtual bool fixed_update();
		virtual bool render();

		// for testing 
		Machi::Components::MeshRendererComponent* m_renderer;
		void set_renderer(Machi::Components::MeshRendererComponent* renderer) {
			m_renderer = renderer;
		}

		/*virtual bool on_key_pressed();
		virtual bool on_key_clicked();
		virtual bool on_key_released();
		*///

	};


}
#endif // ! __APPLICATION_H__ 