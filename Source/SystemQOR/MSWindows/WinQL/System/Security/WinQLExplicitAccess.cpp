//WinQLExplicitAccess.cpp

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

#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/System/Security/WinQLExplicitAccess.h"
#include "WinQAPI/AdvAPI32.h"

using namespace nsWinQAPI;

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID( CExplicitAccessArray );

	//--------------------------------------------------------------------------------
	bool operator != ( const ExplicitAccess& Ac1, const ExplicitAccess& Ac2 )
	{
		return !( 
			( Ac1.grfAccessPermissions == Ac2.grfAccessPermissions ) &&
			( Ac1.grfAccessMode == Ac2.grfAccessMode ) &&
			( Ac1.grfInheritance == Ac2.grfInheritance ) &&
			( Ac1.Trustee == Ac2.Trustee ) );
	}

	//--------------------------------------------------------------------------------
	CExplicitAccessArray::CExplicitAccessArray( unsigned long ulSize ) : CTArray< nsWin32::ExplicitAccess, CPolicy >( ulSize ), m_AdvAPI32Library( CAdvAPI32::Instance() )
	{
		_WINQ_FCONTEXT( "CExplicitAccessArray::CExplicitAccessArray" );
	}

	//--------------------------------------------------------------------------------
	CExplicitAccessArray::~CExplicitAccessArray()
	{
		_WINQ_FCONTEXT( "CExplicitAccessArray::~CExplicitAccessArray" );
	}

	//--------------------------------------------------------------------------------
	void CExplicitAccessArray::Append( void )
	{
		_WINQ_FCONTEXT( "CExplicitAccessArray::Append" );
        __QOR_PROTECT
        {
			if ( m_ulCurrentSize == m_ulMaxSize ) 
			{
				unsigned long ulOldCount = m_ulMaxSize;
				m_ulMaxSize *= 2;			
				m_ArrayData = nsCodeQOR::mem_traits< ExplicitAccess >::CTAllocator::Reallocate( m_ArrayData, ulOldCount, m_ulMaxSize, true );
			}

			m_ulCurrentSize += 1;
        }__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	void CExplicitAccessArray::BuildItem( unsigned long ulIndex, TCHAR* pTrusteeName, DWORD AccessPermissions, nsWin32::AccessMode AccessMode, DWORD Inheritance )
	{
		_WINQ_FCONTEXT( "CExplicitAccessArray::BuildItem" );
        __QOR_PROTECT
        {
			if( ulIndex < m_ulCurrentSize )
			{
				m_AdvAPI32Library.BuildExplicitAccessWithName( reinterpret_cast< ::PEXPLICIT_ACCESS >( &m_ArrayData[ ulIndex ] ), pTrusteeName, AccessPermissions, static_cast< ::ACCESS_MODE >( AccessMode ), Inheritance );
			}
        }__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	bool CExplicitAccessArray::BuiltItem( unsigned long ulIndex, unsigned long grfAccessPermissions, nsWin32::AccessMode grfAccessMode, unsigned long grfInheritance, nsWin32::Trustee& Trustee )
	{
		_WINQ_FCONTEXT( "CExplicitAccessArray::BuildItem" );
		bool bResult = false;
		if( ulIndex < m_ulCurrentSize )
		{
			m_ArrayData[ ulIndex ].grfAccessPermissions = grfAccessPermissions;
			m_ArrayData[ ulIndex ].grfAccessMode = grfAccessMode;
			m_ArrayData[ ulIndex ].grfInheritance = grfInheritance;
			m_ArrayData[ ulIndex ].Trustee = Trustee;
			bResult = true;
		}
		return bResult;
	}

}//nsWin32