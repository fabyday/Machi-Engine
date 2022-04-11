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
#include <config.h>
#include <string>



 class MACHI_API Application   {


	// platform dependents!
public : 
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	/// 
	/// 
	/// 


	bool _initialize(); 
	bool _run_logic();
	bool _finalize();
	bool run(int argc, char** argv);


public:
	
	using string = std::string;
	
	
	
	virtual ~Application() {};


	static Application* get_instance() {
		if (app_ == nullptr) {
			app_ = new Application;
		}
		return app_;
	};

	Application* set_resolution(int width, int height, bool fullscreen);
	Application* set_resolution(int x, int y, int width, int height, bool fullscreen);
	Application* set_name(string name);

private:
	static Application* app_;
	string app_name_;
	time_t time_;
	bool fullscreen_;
	int x_, y_, width_, height_;


protected:
	virtual bool update();
	virtual bool fixed_update();
	virtual bool render();
	

};