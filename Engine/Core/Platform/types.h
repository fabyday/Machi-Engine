#if defined(_WIN64) || defined(_WIN32)
//define something for Windows (64-bit)
#include <Platform/windows/types.h>
#elif defined(__APPLE__)
#include "TargetConditionals.h"
#include <Platform/Apple/types.h>
#if TARGET_OS_IPHONE && TARGET_OS_SIMULATOR
// define something for simulator
// (although, checking for TARGET_OS_IPHONE should not be required).
#elif TARGET_OS_IPHONE && TARGET_OS_MACCATALYST
// define something for Mac's Catalyst
#elif TARGET_OS_IPHONE
// define something for iphone  
#else
#define TARGET_OS_OSX 1
// define something for OSX
#endif
#elif __linux
// linux
#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif



