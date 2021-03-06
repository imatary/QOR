//RTC.h

// Copyright Querysoft Limited 2013
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

//Declares the RunTime Check API
//Calls to these functions are injected by MSVC depending on compilation options
//Mostly stubs here until we work out what they are supposed to do and how

#ifndef WINCMPSUPVC_RTC_H_1
#define WINCMPSUPVC_RTC_H_1

__QCMP_STARTLINKAGE_C

//------------------------------------------------------------------------------
typedef enum _RTC_ErrorNumber 
{
	_RTC_CHKSTK = 0,
	_RTC_CVRT_LOSS_INFO,
	_RTC_CORRUPT_STACK,
	_RTC_UNINIT_LOCAL_USE,
	_RTC_CORRUPTED_ALLOCA,
	_RTC_ILLEGAL
} _RTC_ErrorNumber;

#define _RTC_ERRTYPE_IGNORE -1
#define _RTC_ERRTYPE_ASK    -2

typedef int ( __cdecl *_RTC_error_fn )( int, const char*, int, const char*, const char*, ... );
typedef int ( __cdecl *_RTC_error_fnW )( int, const wchar_t*, int, const wchar_t*, const wchar_t*, ... );

int				__cdecl _RTC_NumErrors(void);
const char *	__cdecl _RTC_GetErrDesc(_RTC_ErrorNumber  _Errnum);
int				__cdecl _RTC_SetErrorType(_RTC_ErrorNumber  _Errnum, int _ErrType);
_RTC_error_fn	__cdecl _RTC_SetErrorFunc(_RTC_error_fn);
_RTC_error_fnW	__cdecl _RTC_SetErrorFuncW(_RTC_error_fnW);

void __cdecl _RTC_Initialize(void);
void __cdecl _RTC_Terminate(void);

_RTC_error_fn __cdecl _CRT_RTC_INIT( void* _Res0, void** _Res1, int _Res2, int _Res3, int _Res4 );
_RTC_error_fnW __cdecl _CRT_RTC_INITW( void* _Res0, void** _Res1, int _Res2, int _Res3, int _Res4 );
    
typedef struct _RTC_vardesc 
{
    int addr;
    int size;
    char* name;
} _RTC_vardesc;

typedef struct _RTC_framedesc 
{
    int varCount;
    _RTC_vardesc* variables;
} _RTC_framedesc;
  
#pragma pack(push, 1)
    //  Structure padded under 32-bit x86, to get consistent execution between 32/64 targets.
    typedef struct _RTC_ALLOCA_NODE 
	{
        __int32 guard1;
        struct _RTC_ALLOCA_NODE* next;
#if defined (_M_IX86)
        __int32 dummypad;
#endif
        size_t allocaSize;
#if defined (_M_IX86)
        __int32 dummypad2;
#endif
        __int32 guard2[3];
    } _RTC_ALLOCA_NODE;
#pragma pack(pop)

// Shortening convert checks - name indicates src bytes to target bytes
// Signedness is NOT checked
char   __fastcall _RTC_Check_2_to_1(short _Src);
char   __fastcall _RTC_Check_4_to_1(int _Src);
char   __fastcall _RTC_Check_8_to_1(__int64 _Src);
short  __fastcall _RTC_Check_4_to_2(int _Src);
short  __fastcall _RTC_Check_8_to_2(__int64 _Src);
int    __fastcall _RTC_Check_8_to_4(__int64 _Src);

// These unsupported functions are deprecated in native mode and not supported at all in /clr mode
void   __fastcall _RTC_CheckStackVars( void* _Esp, _RTC_framedesc* _Fd);
void   __fastcall _RTC_CheckStackVars2( void* _Esp, _RTC_framedesc* _Fd, _RTC_ALLOCA_NODE* _AllocaList );
void   __fastcall _RTC_AllocaHelper( _RTC_ALLOCA_NODE* _PAllocaBase, size_t _CbSize, _RTC_ALLOCA_NODE** _PAllocaInfoList );

// Unintialized Local call
void __cdecl _RTC_UninitUse( const char* _Varname );

// Subsystem initialization stuff
void __cdecl _RTC_Shutdown(void);
void __cdecl _RTC_InitBase(void);

void* _ReturnAddress();

__QCMP_ENDLINKAGE_C

#endif//WINCMPSUPVC_RTC_H_1

