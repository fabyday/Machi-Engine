#pragma once

#include <string>
#include <stdint.h>
#if defined(_UNICODE) || defined(UNICODE)
#define MSTRING std::wstring
#else
#define MSTRING std::string 
#endif


#define MCHAR WCHAR

#define MINT8 int8_t
#define MINT16 int16_t
#define MINT32 int32_t
#define MINT64 int64_t
#define MINT MINT32

#define MUINT8 u_int8_t
#define MUINT16 u_int16_t
#define MUINT32 u_int_32_t

#define MUINT u_int32_t

#define MLENGTH size_t

#define MLPWCHAR WCHAR*
#define MWCHAR WCHAR
#define MPWSTR PWSTR

#define MLONG LONG

#define MFLOAT float


#define MDOUBLE double 