//WinQLApplication.h

// Copyright Querysoft Limited 2013, 2016, 2017
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

//WinQL Application object

#ifndef WINQL_APPLICATION_H_3
#define WINQL_APPLICATION_H_3

#include "SystemQOR.h"
#include "CodeQOR/Instancing/STMember.h"
#include "CodeQOR/ClassReg/ClassRegEntry.h"
#include "AppocritaQOR/Application.h"
#include "AppocritaQOR/Workflow.h"
#include "WinQL/Application/Process/WinQLProcess.h"
#include "WinQL/Application/Threading/WinQLEvent.h"
#include "WinQL/Application/ErrorSystem/WinQLErrorSystem.h"
#include "AppocritaQOR/Role.h"
#include "WinQL/Application/Console/WinQLConsole.h"
//#include "WinQL/OSGUI/GUI.h"
//#include "WinQL/Application/Process/WinQLEnvironment.h"
#include "WinQL/Application/Resources/WinQLResourceManager.h"
//#include "WinQL/OSGUI/Theme/ThemeData.h"
#include "WinQL/System/User/WinQLUser.h"
//#include "WinQL/CodeServices/Locale/Locale.h"
//#include "WinQL/Application/Memory/WinQLMemory.h"
#include "WinQL/Application/RecoveryAndRestart/WinQLAppRecovery.h"
#include "WinQL/Application/RecoveryAndRestart/WinQLAppRestart.h"
#include "WinQL/Application/Comms/IPC/Atoms/WinQLAtoms.h"
#include "WinQL/GUI/MessageHandler.h"
#include "algorithm"
#include "vector"



//--------------------------------------------------------------------------------
namespace nsWin32
{
	class __QOR_INTERFACE( __WINQL ) CWin32Application;

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CApplicationEvent : public CEvent
	{
	public:

		CApplicationEvent( CWin32Application& Application );
		virtual ~CApplicationEvent();

		virtual void OnSignaled( void );

	private:

		CApplicationEvent();

		CWin32Application& m_Application;
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CWin32Application : public nsQOR::IApplication
	{
		friend class CApplicationEvent;

	public:

		__QOR_DECLARE_OCLASS_ID( CWin32Application );

		static nsCodeQOR::CTExternalRegEntry< CWin32Application > RegEntry;

		CWin32Application();
		virtual ~CWin32Application();

		nsCodeQOR::CTLRef< CProcess > Process( void );

		//Command Line
		//CEnvironment::refType Environment( void );
		
		CConsole::ref_type Console( void );			//Console - optional
		//DesktopEnvironment - optional

		bool SetAutoRestart( const CWString& strCommandLine, unsigned long ulFlags  );
		void ClearAutoRestart( void );

		bool SetAutoRecovery( unsigned long ulPingIntervalMilliseconds );
		void ClearAutoRecovery( void );

		//Comms/IPC
		nsCodeQOR::CSTMember< CLocalAtomTable > LocalAtomTable;
		
		//CResourceManager::refType Resources( void );
		//CUser::ref_type User( void );

		//CLocale::refType Locale( void );		
		//CErrorSystem::refType ErrorSystem( void );
		//CMemoryManager::ref_type Memory( void );		
		//CThreadManager::refType Threads( void );
		//CTimerManager::refType Timers( void );
		//CModuleManager::refType Modules( void );
		//CSecurityManager::refType Security( void );		
		//CGUI::refType GUI( void );		

		static ref_type TheWin32Application( void );


		virtual void SetRole( nsQOR::IRole::ref_type Role );
		virtual nsQOR::IRole::ref_type GetRole( void );

		virtual void SetWorkflow( nsQOR::IWorkflow::ref_type pWorkflow );
		virtual nsQOR::IWorkflow::ref_type GetWorkflow( void );
		virtual void SetOuter( IApplication::ref_type Application );
		virtual void Setup( void );
		virtual void Shutdown( void );

		virtual int Run( void );															//main loop
		virtual int Run( nsQOR::IWorkflow::ref_type pWorkflow );
		virtual void EnqueueEvent( nsQOR::IEvent::ref_type pEvent );
		virtual void Stop( void );															//call to break main loop on next event
		virtual void OnIdle( void );
		void AddWaitableObject( CWaitableObject::ref_type );
		void RemoveWaitableObject( CWaitableObject::ref_type );

		unsigned long GetIdleWaitMilliseconds( void );
		void SetIdleWaitMilliseconds( unsigned long ulMilliseconds );

	private:

		void ProcessEvent( void );

		CAppRestart::refType m_Restart;
		CAppRecovery::refType m_Recovery;
		nsQOR::IRole::ref_type m_Role;
		nsQOR::IWorkflow::ref_type m_pWorkflow;

		nsCodeQOR::CSTMember< CMessageHandler > m_MessageHandler;
		
		std::vector< const void* > m_Handles;
		std::vector< CWaitableObject* > m_VecWaitableObjects;
		std::deque< nsQOR::IEvent* > m_AppEventQueue;
		unsigned long m_ulIdleWaitMillseconds;
		bool m_bStopping;															//flag to break out of run loop
		CApplicationEvent m_AppEvent;
		IApplication::ref_type m_OuterApplication;									//gives access to the generic layer IApplication derived outer instance ( reverse pimpl )

		void RunLoop( void );
	};

}//nsWin32

#endif//WINQL_APPLICATION_H_3

