//WinQLGlobal.h

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

#ifndef WINQL_CODESERV_GLOBAL_H_2
#define WINQL_CODESERV_GLOBAL_H_2

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/WinQL.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CGlobalHelper
	{
	public:

		__QCMP_STATIC_CONSTANT( unsigned int, GMem_FIXED			= 0x0000		   );
		__QCMP_STATIC_CONSTANT( unsigned int, GMem_MOVEABLE			= 0x0002		   );
		__QCMP_STATIC_CONSTANT( unsigned int, GMem_NOCOMPACT		= 0x0010		   );
		__QCMP_STATIC_CONSTANT( unsigned int, GMem_NODISCARD		= 0x0020		   );
		__QCMP_STATIC_CONSTANT( unsigned int, GMem_ZEROINIT			= 0x0040		   );
		__QCMP_STATIC_CONSTANT( unsigned int, GMem_MODIFY			= 0x0080		   );
		__QCMP_STATIC_CONSTANT( unsigned int, GMem_DISCARDABLE		= 0x0100		   );
		__QCMP_STATIC_CONSTANT( unsigned int, GMem_NOT_BANKED		= 0x1000		   );
		__QCMP_STATIC_CONSTANT( unsigned int, GMem_SHARE			= 0x2000		   );
		__QCMP_STATIC_CONSTANT( unsigned int, GMem_DDESHARE			= 0x2000		   );
		__QCMP_STATIC_CONSTANT( unsigned int, GMem_NOTIFY			= 0x4000		   );
		__QCMP_STATIC_CONSTANT( unsigned int, GMem_LOWER			= GMem_NOT_BANKED  );
		__QCMP_STATIC_CONSTANT( unsigned int, GMem_VALID_FLAGS		= 0x7F72		   );
		__QCMP_STATIC_CONSTANT( unsigned int, GMem_INVALID_HANDLE	= 0x8000		   );

		__QOR_DECLARE_OCLASS_ID( CGlobalHelper );

		CGlobalHelper();
		~CGlobalHelper();
		void* Alloc( unsigned int uFlags, Cmp_ulong_ptr uBytes ) const;
		unsigned int Flags( void* hMem ) const;
		void* Free( void* hMem ) const;
		void* Handle( const void* pMem ) const;
		void* Lock( void* hMem ) const;
		void* ReAlloc( void* hMem, Cmp_ulong_ptr uBytes, unsigned int uFlags) const;
		Cmp_ulong_ptr Size( void* hMem ) const;
		bool Unlock( void* hMem ) const;
	};

}//nsWin32

#endif//WINQL_CODESERV_GLOBAL_H_2

