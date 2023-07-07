#include "../platform_config.h"
#include "types.h"
#include <stdio.h>
#include <io.h>
#include <Windows.h>
//#include "windows_platform.h"

#include <filesystem>
#include <functional>
#include <iostream>


namespace fs = std::filesystem;

enum class ConsoleStatus{RUNNING, SHUTDOWN};


void MACHI_PLATFORM_API RedirectStream(const char* p_file_name, const char* p_mode, FILE* p_cpp_stream, const DWORD p_std_handle);
void MACHI_PLATFORM_API RedirectIOToConsole();
void MACHI_PLATFORM_API addConsoleEventHandler();
void MACHI_PLATFORM_API addConsoleEventHandler(std::function<void(ConsoleStatus)> function);
void MACHI_PLATFORM_API ColseConsole();
