//WinQLComponentImpl.h

// Copyright Querysoft Limited 2013, 2015, 2017
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

//Base class for implementing IComponent for MMC snapin

#ifndef WINQL_COM_COMPONENTIMPL_H_3
#define WINQL_COM_COMPONENTIMPL_H_3

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/Definitions/Constants.h"
#include "WinQL/Definitions/Security.h"
#include "WinQL/Definitions/Interfaces.h"
#include "WinQL/COM/Server/BaseParts/WinQLTInterfaceMember.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	//Server side IComponent
	class __QOR_INTERFACE( __WINQL_COM ) CComponentImpl : public CInterfaceImplBase< IComponent >
	{
	public:

		__QOR_DECLARE_COMCLASS_ID( CComponentImpl );

		CComponentImpl( CIUnknownImplBase<>* pImpl );
		virtual ~CComponentImpl();

        virtual long __QCMP_STDCALLCONVENTION Initialize( IConsole* lpConsole );        
        virtual long __QCMP_STDCALLCONVENTION Notify( IDataObject* lpDataObject, MMC_NOTIFY_TYPE event, Cmp_long_ptr arg, Cmp_long_ptr param);
        virtual long __QCMP_STDCALLCONVENTION Destroy( Cmp_long_ptr cookie);
        virtual long __QCMP_STDCALLCONVENTION QueryDataObject(  Cmp_long_ptr cookie, DATA_OBJECT_TYPES type, IDataObject** ppDataObject );
        virtual long __QCMP_STDCALLCONVENTION GetResultViewType( Cmp_long_ptr cookie, TCHAR** ppViewType, long* pViewOptions );
        virtual long __QCMP_STDCALLCONVENTION GetDisplayInfo( RESULTDATAITEM* pResultDataItem );
        virtual long __QCMP_STDCALLCONVENTION CompareObjects( IDataObject* lpDataObjectA, IDataObject* lpDataObjectB );        

	private:

		CComponentImpl();
		CComponentImpl( const CComponentImpl& );
		CComponentImpl& operator = ( const CComponentImpl& );
	};

}//nsWin32

#endif//WINQL_COM_COMPONENTIMPL_H_3

