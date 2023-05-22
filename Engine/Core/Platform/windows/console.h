#include "config.h"
#include "types.h"
#include <stdio.h>
#include <io.h>
#include <Windows.h>
//#include "windows_platform.h"

#include <filesystem>
#include <iostream>


#include <spdlog/spdlog.h>

namespace fs = std::filesystem;

void RedirectStream(const char* p_file_name, const char* p_mode, FILE* p_cpp_stream, const DWORD p_std_handle);
void RedirectIOToConsole();