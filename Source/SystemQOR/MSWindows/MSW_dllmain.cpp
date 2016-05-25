//MSW_dllmain.cpp : Defines the entry point for the DLL application.

#include "SystemQOR.h"

#if		(QOR_SYS_OS == QOR_SYS_MSW)

#ifdef _USRDLL

#include "SystemQOR/MSWindows/MSW_BootStrap.h"
#include "CodeQOR/MemoryManagement/ManagedAllocator.h"
#include "CodeQOR/Tracing/FunctionContextBase.h"
#include "WinQL/CodeServices/Dll.h"
#include "WinQL/CodeServices/PerformanceHelper.h"
#include "../CQOR/include/MSwindows/excpt.h"

int __cdecl __CppExceptionFilter( unsigned long _ExceptionNum, nsWin32::_EXCEPTION_POINTERS* _ExceptionPtr );

__QCMP_STARTLINKAGE_C

//------------------------------------------------------------------------------
int __stdcall BaseQORInit( void* hDllHandle, unsigned long ulReason, void* pReserved )
{
	switch( ulReason )
	{
	case DLL_PROCESS_ATTACH:
		{
			//Start-up code only gets executed when the process is initialized
			CBaseQORBootStrap::Instance().ProcessAttach(); // increment process attach notification
			break;
		}
	case DLL_PROCESS_DETACH:
		{
			CBaseQORBootStrap& refBootStrap( CBaseQORBootStrap::Instance() );
			if ( refBootStrap.ProcessAttached() )
			{
				refBootStrap.ProcessDetach();
                
				__try
				{
					refBootStrap.Terminate();
				}
				__finally 
				{
				}
			}
			else
			{
				return 0;	// no prior process attach, just return
			}
			break;
		}
	case DLL_THREAD_ATTACH:
		{
			/*
			_ptiddata ptd;

			// Initialize FlsGetValue function pointer
			__set_flsgetvalue();

			if ( ((ptd = _calloc_crt(1, sizeof(struct _tiddata))) != NULL))
			{
				if (FLS_SETVALUE(__flsindex, (LPVOID)ptd) ) {
					//Initialize of per-thread data
                     
					_initptd(ptd, NULL);

					ptd->_tid = GetCurrentThreadId();
					ptd->_thandle = (uintptr_t)(-1);
				} else
				{
					_free_crt(ptd);
					return FALSE;
				}
			} else
			{
				return FALSE;
			}
			*/
			break;
	    }
	case DLL_THREAD_DETACH:
		{
			//_freeptd(NULL);         // free up per-thread CRT data
			break;
		}
	}
    return 1;
}

static int __cdecl BaseQORStartup( void* hDllHandle, unsigned long ulReason, void* pReserved );

//------------------------------------------------------------------------------
//Run Time initialisation and termination
__declspec(noinline) int __cdecl BaseQORStartup( void* hDllHandle, unsigned long ulReason, void* pReserved )
{
    int iRetCode = 1;

    //If this is a process detach notification, check that a process is attached
	if( ( ulReason == DLL_PROCESS_DETACH ) && ( !CBaseQORBootStrap::Instance().ProcessAttached() ) )
	{
        return 0;
	}

    __try 
	{
        if ( ulReason == DLL_PROCESS_ATTACH || ulReason == DLL_THREAD_ATTACH )
        {
			iRetCode = BaseQORInit( hDllHandle, ulReason, pReserved );
        }

        if( ( ulReason == DLL_PROCESS_ATTACH ) && !iRetCode )
        {            
            BaseQORInit( hDllHandle, DLL_PROCESS_DETACH, pReserved );
        }

        if( ( ulReason == DLL_PROCESS_DETACH ) || ( ulReason == DLL_THREAD_DETACH ) )
        {
            iRetCode = BaseQORInit( hDllHandle, ulReason, pReserved );
        }
    } 
	__except ( __CppExceptionFilter( GetExceptionCode(), GetExceptionInformation() ) ) 
	{
        return 0;
    }

    return iRetCode;
}

//------------------------------------------------------------------------------
//The external initial entry point for this Windows DLL
int __stdcall _DllMainCRTStartup( void* hDllHandle, unsigned long ulReason, void* pReserved )
{
	if ( ulReason == DLL_PROCESS_ATTACH )					//if this is called as part of process startup
	{
		CBaseQORBootStrap::InitializeSecurityCookie();		//The very first thing we have to do is intialise the security cookie
	}

	return BaseQORStartup( hDllHandle, ulReason, pReserved );
}

/*
//------------------------------------------------------------------------------
int __stdcall DllMain( void* hModule, unsigned long ul_reason_for_call, void* lpReserved )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return 1;
}
*/

__QCMP_ENDLINKAGE_C

#endif//_USRDLL

#endif//(QOR_SYS_OS == QOR_SYS_MSW)
