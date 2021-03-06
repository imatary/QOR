//WinQLBoundaryDescriptor.cpp

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
#include "WinQL/Application/Threading/WinQLBoundaryDescriptor.h"
#include "WinQAPI/Kernel32.h"

//------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	__QOR_IMPLEMENT_OCLASS_LUID( CBoundaryDescriptor );

	//--------------------------------------------------------------------------------
	CBoundaryDescriptor::CBoundaryDescriptor( const TCHAR* Name, unsigned long Flags )
	{
		_WINQ_FCONTEXT( "CBoundaryDescriptor::CBoundaryDescriptor" );
		__QOR_PROTECT
		{
			m_Handle = CKernel32::CreateBoundaryDescriptor( Name, Flags );
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CBoundaryDescriptor::~CBoundaryDescriptor()
	{
		_WINQ_FCONTEXT( "CBoundaryDescriptor::~CBoundaryDescriptor" );
		__QOR_PROTECT
		{
			CKernel32::DeleteBoundaryDescriptor( m_Handle.Use() );
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	bool CBoundaryDescriptor::AddSID( void* RequiredSid )
	{
		_WINQ_FCONTEXT( "CBoundaryDescriptor::AddSID" );
		bool bResult = false;
		__QOR_PROTECT
		{
			void* pHandle = m_Handle.Use();
			bResult = CKernel32::AddSIDToBoundaryDescriptor( &pHandle, RequiredSid ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CBoundaryDescriptor::AddSID( const TCHAR* strSID )
	{
		_WINQ_FCONTEXT( "CBoundaryDescriptor::AddSID" );
		bool bResult = false;
		__QOR_PROTECT
		{					
			CSID SID( strSID );
			bResult = AddSID( SID.Data() );
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CBoundaryDescriptor::AddSID( CSID& RequiredSid )
	{
		_WINQ_FCONTEXT( "CBoundaryDescriptor::AddSID" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = AddSID( RequiredSid.Data() );
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CTCRef< CSyncHandle > CBoundaryDescriptor::Handle()
	{
		nsCodeQOR::CTCRef< CSyncHandle > refHandle = &m_Handle;
		return refHandle;
	}

}//nsWin32
