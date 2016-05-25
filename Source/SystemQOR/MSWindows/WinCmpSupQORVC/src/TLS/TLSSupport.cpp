//TLSSupport.cpp

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

#include "WinQL/WinQL.h"
#include "SystemQOR.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "../Source/SystemQOR/MSWindows/WinCmpSupQORVC/include/TLS/TLS.h"
#include "../Source/SystemQOR/MSWindows/WinCmpSupQORVC/include/PE/Sections.h"

__QCMP_STARTLINKAGE_C

//--------------------------------------------------------------------------------
// Thread Local Storage index for this .EXE or .DLL
unsigned long _tls_index = 0;

//--------------------------------------------------------------------------------
// Special symbols to mark start and end of Thread Local Storage area.
#pragma data_seg(".tls")

	#if defined (_M_IA64) || defined (_M_AMD64)
		_CRTALLOC(".tls")
	#endif
		char _tls_start = 0;

//--------------------------------------------------------------------------------
#pragma data_seg(".tls$ZZZ")

	#if defined (_M_IA64) || defined (_M_AMD64)
		_CRTALLOC(".tls$ZZZ")
	#endif
		char _tls_end = 0;

#pragma data_seg()

//--------------------------------------------------------------------------------
// Start section for TLS callback array examined by the OS loader code. If dynamic
// TLS initialization is used, then a pointer to __dyn_tls_init will be placed in 
// .CRT$XLC by inclusion of tlsdyn.obj.  This will cause the .CRT$XD? array of 
// individual TLS variable initialization callbacks to be walked.
_CRTALLOC(".CRT$XLA") nsWin32::fpImage_TLS_Callback __xl_a = 0;

//--------------------------------------------------------------------------------
// NULL terminator for TLS callback array.  This symbol, __xl_z, is never actually 
// referenced anywhere, but it must remain.  The OS loader code walks the TLS 
// callback array until it finds a NULL pointer, so this makes sure the array is 
// properly terminated.
_CRTALLOC(".CRT$XLZ") nsWin32::fpImage_TLS_Callback __xl_z = 0;

//--------------------------------------------------------------------------------
//TODO: Move this to an architecture specific inline
#ifdef _WIN64
	_CRTALLOC(".rdata$T") /*const*/ nsWin32::IMAGE_TLS_DIRECTORY64 _tls_used =
	{
			(Cmp_unsigned_long_long) &_tls_start,        // start of tls data
			(Cmp_unsigned_long_long) &_tls_end,          // end of tls data
			(Cmp_unsigned_long_long) &_tls_index,        // address of tls_index
			(Cmp_unsigned_long_long) (&__xl_a+1),        // pointer to call back array
			(unsigned long) 0,                      // size of tls zero fill
			(unsigned long) 0                       // characteristics
	};

#else  //!_WIN64

_CRTALLOC(".rdata$T") /*const*/ nsWin32::IMAGE_TLS_DIRECTORY _tls_used =
	{
			(unsigned long)(Cmp_ulong_ptr) &_tls_start, // start of tls data
			(unsigned long)(Cmp_ulong_ptr) &_tls_end,   // end of tls data
			(unsigned long)(Cmp_ulong_ptr) &_tls_index, // address of tls_index
			(unsigned long)(Cmp_ulong_ptr) (&__xl_a+1), // pointer to call back array
			(unsigned long) 0,                      // size of tls zero fill
			(unsigned long) 0                       // characteristics
	};

#endif


__QCMP_ENDLINKAGE_C