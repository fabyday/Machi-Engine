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
#include "types.h"
#include "config.h"
#include <stdio.h>
#include <io.h>
#include <Windows.h>
#include "../../OS/OS.h"
#include "os_native.h"


static void RedirectStream(const char* p_file_name, const char* p_mode, FILE* p_cpp_stream, const DWORD p_std_handle) {
	const HANDLE h_existing = GetStdHandle(p_std_handle);
	if (h_existing != INVALID_HANDLE_VALUE) { // Redirect only if attached console have a valid handle.
		const HANDLE h_cpp = reinterpret_cast<HANDLE>(_get_osfhandle(_fileno(p_cpp_stream)));
		if (h_cpp == INVALID_HANDLE_VALUE) { // Redirect only if it's not already redirected to the pipe or file.
			FILE* fp = p_cpp_stream;
			freopen_s(&fp, p_file_name, p_mode, p_cpp_stream); // Redirect stream.
			setvbuf(p_cpp_stream, nullptr, _IONBF, 0); // Disable stream buffering.
		}
	}
}

static void RedirectIOToConsole() {
	if (AttachConsole(ATTACH_PARENT_PROCESS)) {
		RedirectStream("CONIN$", "r", stdin, STD_INPUT_HANDLE);
		RedirectStream("CONOUT$", "w", stdout, STD_OUTPUT_HANDLE);
		RedirectStream("CONOUT$", "w", stderr, STD_ERROR_HANDLE);
		printf("\n"); // Make sure our output is starting from the new line.
	}
}




OS::OS() {

}


std::string 
OS::get_current_directory() {
	return "test";
}


INT32 
OS::make_process() {
	return -1;
}