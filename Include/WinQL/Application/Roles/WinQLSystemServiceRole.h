//WinQLSystemServiceRole.h

// Copyright Querysoft Limited 2016
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

//WinQL Application Role for System Services

#ifndef WINQL_APPROLESYSTEMSERVICE_H_1
#define WINQL_APPROLESYSTEMSERVICE_H_1

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/CodeServices/Text/WinString.h"
#include "AppocritaQOR/Role.h"
#include "WinQL/Application/ErrorSystem/WinQLErrorSystem.h"
#include "WinQL/Application/Subsystems/WinQLThreading.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	class __QOR_INTERFACE( __WINQL ) CWin32Application;

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CSystemServiceRole : public nsQOR::CRoleImplBase
	{
	public:
		__QOR_DECLARE_OCLASS_ID( CSystemServiceRole );

		__QOR_DECLARE_REF_TYPE( CSystemServiceRole );

		CSystemServiceRole();
		virtual ~CSystemServiceRole();
		CSystemServiceRole( const CSystemServiceRole& src );
		CSystemServiceRole& operator = ( const CSystemServiceRole& src );

		ref_type Ref( void )
		{
			return ref_type( this );
		}

		virtual void Setup( CWin32Application& );
		virtual void Shutdown( CWin32Application& );

		bool Run( void );
		void Stop( void );

		void Install( CTString& strDisplayName, unsigned long ulStartType, CTString& strDependencies, CTString& strAccount, CTString& strPassword );
		void Uninstall( void );

	protected:

		virtual void OnStart( unsigned long ulArgc, TCHAR** szArgv );
		virtual void OnStop( void );
		virtual void OnPause( void );
		virtual void OnContinue( void );
		virtual void OnShutdown( void );

		void SetServiceStatus( unsigned long ulCurrentState, unsigned long ulWin32ExitCode = NoError, unsigned long ulWaitHint = 0 );
		void WriteEventLogEntry( const TCHAR* szMessage, unsigned short usType );
		void WriteErrorLogEntry( const TCHAR* szFunction, unsigned long ulError );

	private:

		static void __QCMP_STDCALLCONVENTION ServiceMain( unsigned long ulArgc, TCHAR** lpszArgv );
		static void __QCMP_STDCALLCONVENTION ServiceCtrlHandler( unsigned long ulCtrl );

		void Start( unsigned long ulArgc, TCHAR** pszArgv );
		void Pause( void );
		void Continue( void );
		void Shutdown( void );

		nsQOR::CThreading m_Threading;

		CTString m_strName;
		SERVICE_STATUS m_Status;
		ServiceStatusHandle m_StatusHandle;

	};

}//nsWin32

#endif//WINQL_APPROLESYSTEMSERVICE_H_1