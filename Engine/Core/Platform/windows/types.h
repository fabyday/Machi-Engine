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
#pragma once

#include <Windows.h>
#include <string>
#include <sys/stat.h>
#if defined(_UNICODE) || defined(UNICODE)
#define MSTRING std::wstring
#define to_string to_wstring
#define MTEXT(x) L##x

typedef struct _stat64i32 _sel_stat;
#define MSTAT _sel_stat
#define MSTAT_FUNC(x, y) _wstat((x), (y))

#else 
#define MSTRING std::string 
typedef struct stat _sel_stat;
#define MSTAT _sel_stat; 
#define MSTAT_FUNC(x, y) stat((x),(y))
#define MTEXT(x) ##x
#endif

#define MCHAR WCHAR
#define MUCHAR unsigned char

#define MINT8 INT8
#define MINT16 INT16
#define MINT32 INT32
#define MINT64 INT64
#define MINT MINT32

#define MUINT8 INT8
#define MUINT16 INT16
#define MUINT32 INT32

#define MUINT UINT
#define MUINT64 UINT64

#define MLPWCHAR WCHAR*
#define MWCHAR WCHAR
#define MPWSTR PWSTR

#define MLONG LONG
#define MLONGLONG long long
#define MSIZE_T long long
#define MFLOAT float


#define MDOUBLE double 