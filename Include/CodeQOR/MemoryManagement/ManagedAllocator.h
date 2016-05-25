// ManagedAllocator.h

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

//Allocations of managed instances

#ifndef CODEQOR_MEMMAN_MANAGEDALLOCATOR_H_2
#define CODEQOR_MEMMAN_MANAGEDALLOCATOR_H_2

#include "SystemQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include <new>
#include "CodeQOR/Traits/MemoryTraits.h"
#include "CodeQOR/DataStructures/TPointer.h"
#include "CodeQOR/MemoryManagement/SmallObjectHeap.h"
#include "CodeQOR/MemoryManagement/FastHeap.h"

//--------------------------------------------------------------------------------
namespace nsCodeQOR
{
#	define tp( _TYPE_ ) nsCodeQOR::TPointer< _TYPE_ >
#	define _tp( _TYPE_ ) typedef tp( _TYPE_ ) __QCMP_JOIN( tp_, _TYPE_ )

//	e.g. _tp( CObject );// gives typedef nsCodeQOR::TPointer< CObject > tp_Object; creating a manager pointer to CObject type

	__QOR_INTERFACE( __CODEQOR ) CFastHeap& FastHeap( void );
	__QOR_INTERFACE( __CODEQOR ) CSmallObjectHeap& SmallObjectHeap( void );

	//--------------------------------------------------------------------------------
	template< typename T >
	TPointer< T > New( Cmp_uint_ptr uiCount = 1 )
	{
		return SmallObjectHeap().AllocateBoxed< T >( uiCount );
	}

	//--------------------------------------------------------------------------------
	template< typename T >
	T* UnsafeNew( Cmp_uint_ptr uiCount = 1 )
	{
		return SmallObjectHeap().AllocateUnboxed< T >( uiCount );
	}

	//--------------------------------------------------------------------------------
	template< typename T >
	T* FastNew( Cmp_uint_ptr uiCount = 1, unsigned int uiLine = 0, const char* pFile = 0 )
	{
		return FastHeap().Allocate< T >( uiCount, uiLine, pFile );
	}

	//--------------------------------------------------------------------------------
	template< typename T >
	void FastFree( T* pT, Cmp_uint_ptr uiCount )
	{
		FastHeap().Free< T >( pT, uiCount );
	}

}//namespace nsCodeQOR

#endif//CODEQOR_MEMMAN_MANAGEDALLOCATOR_H_2