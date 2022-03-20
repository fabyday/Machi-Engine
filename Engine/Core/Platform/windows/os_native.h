#pragma once
#include <Windows.h>
#include "types.h"
typedef  struct OSContext {
	HINSTANCE* hInstance;
	HINSTANCE* hPrevInstance;
	MUINT nCmdShow;
	MPWSTR pCmdLine;
}OSConfig;
