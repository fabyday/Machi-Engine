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


#include <Platform/config.h>
#include <stdio.h>
#include <string>
#include <Platform/types.h>
//#include <Platform/windows/windows_platform.h>
namespace Machi {
	//forward declartion
	typedef struct OSContext OSConfig;

	class MACHI_API OS {
	private:
		OSContext* m_ctx;
		static OS* instance_;

		int argc;
		char** argv;

		OS();
	public:

		OS& set_context(OSContext* ctx) {
			m_ctx = ctx;
			return *this;
		}

		OSContext* get_context() {
			return m_ctx;
		}

		static OS* get_instance();
		//load_dynamic_library();
		MSTRING get_current_directory();
		MINT32 make_process();
		bool open_console();

	};
}