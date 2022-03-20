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
#include <stdio.h>
#include <io.h>
#include <Windows.h>
#include <string>


//forward declartion
typedef struct OSContext OSConfig;

class MACHI_API OS {
private:
	static OSContext* context_;
	static OS* instance_;

	OS();
	int argc;
	char** argv;
public:

	static void set_context(OSContext* ctx) {
		context_ = ctx;
	}

	static OSContext* get_context() {
		return context_;
	}

	static OS* get_instance() {
		
		if (instance_ == nullptr)
			instance_ = new OS();
		return instance_;
	}
	//load_dynamic_library();
	std::string get_current_directory();
	INT32 make_process();
	

	










};