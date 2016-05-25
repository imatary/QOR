//WinQLSEH.cpp

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
#include "WinQL/Application/ErrorSystem/WinQLSEH.h"
#include "WinQAPI/Kernel32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsCodeServices
	{
		using namespace nsWinQAPI;

		__QOR_IMPLEMENT_OCLASS_LUID( CStructuredExceptionHelper );

		//--------------------------------------------------------------------------------
		CStructuredExceptionHelper::CStructuredExceptionHelper()
		{
			_WINQ_FCONTEXT( "CStructuredExceptionHelper::CStructuredExceptionHelper" );
		}

		//--------------------------------------------------------------------------------
		CStructuredExceptionHelper::~CStructuredExceptionHelper()
		{
			_WINQ_FCONTEXT( "CStructuredExceptionHelper::~CStructuredExceptionHelper" );
		}

		//--------------------------------------------------------------------------------
		void* CStructuredExceptionHelper::AddVectoredContinueHandler( unsigned long FirstHandler, nsWin32::PVECTORED_EXCEPTION_HANDLER VectoredHandler )
		{
			_WINQ_FCONTEXT( "CStructuredExceptionHelper::AddVectoredContinueHandler" );
			return CKernel32::AddVectoredContinueHandler( FirstHandler, reinterpret_cast< ::PVECTORED_EXCEPTION_HANDLER >( VectoredHandler ) );
		}

		//--------------------------------------------------------------------------------
		void* CStructuredExceptionHelper::AddVectoredExceptionHandler( unsigned long FirstHandler, nsWin32::PVECTORED_EXCEPTION_HANDLER VectoredHandler )
		{
			_WINQ_FCONTEXT( "CStructuredExceptionHelper::AddVectoredExceptionHandler" );
			return CKernel32::AddVectoredExceptionHandler( FirstHandler, reinterpret_cast< ::PVECTORED_EXCEPTION_HANDLER >( VectoredHandler ) );
		}

		//--------------------------------------------------------------------------------
		void CStructuredExceptionHelper::RaiseException( unsigned long dwExceptionCode, unsigned long dwExceptionFlags, unsigned long nNumberOfArguments, const Cmp_ulong_ptr* lpArguments )
		{
			_WINQ_FCONTEXT( "CStructuredExceptionHelper::RaiseException" );
			CKernel32::RaiseException( dwExceptionCode, dwExceptionFlags, nNumberOfArguments, lpArguments );
		}

		//--------------------------------------------------------------------------------
		unsigned long CStructuredExceptionHelper::RemoveVectoredContinueHandler( void* Handler )
		{
			_WINQ_FCONTEXT( "CStructuredExceptionHelper::RemoveVectoredContinueHandler" );
			return CKernel32::RemoveVectoredContinueHandler( Handler );
		}

		//--------------------------------------------------------------------------------
		unsigned long CStructuredExceptionHelper::RemoveVectoredExceptionHandler( void* VectoredHandlerHandle )
		{
			_WINQ_FCONTEXT( "CStructuredExceptionHelper::RemoveVectoredExceptionHandler" );
			return CKernel32::RemoveVectoredExceptionHandler( VectoredHandlerHandle );
		}

		//--------------------------------------------------------------------------------
		unsigned char CStructuredExceptionHelper::RtlAddFunctionTable( nsWin32::pRuntimeFunction FunctionTable, unsigned long EntryCount, Cmp_unsigned__int64 BaseAddress, Cmp_unsigned_long_long TargetGp )
		{
			_WINQ_FCONTEXT( "CStructuredExceptionHelper::RtlAddFunctionTable" );
			return CKernel32::RtlAddFunctionTable( reinterpret_cast< ::PRUNTIME_FUNCTION >( FunctionTable ), EntryCount, BaseAddress, TargetGp );
		}

		//--------------------------------------------------------------------------------
		void CStructuredExceptionHelper::RtlCaptureContext( nsWin32::PCONTEXT ContextRecord )
		{
			_WINQ_FCONTEXT( "CStructuredExceptionHelper::RtlCaptureContext" );
			CKernel32::RtlCaptureContext( reinterpret_cast< ::PCONTEXT >( ContextRecord ) );
		}

		//--------------------------------------------------------------------------------
		unsigned char CStructuredExceptionHelper::RtlDeleteFunctionTable( nsWin32::pRuntimeFunction FunctionTable )
		{
			_WINQ_FCONTEXT( "CStructuredExceptionHelper::RtlDeleteFunctionTable" );
			return CKernel32::RtlDeleteFunctionTable( reinterpret_cast< ::PRUNTIME_FUNCTION >( FunctionTable ) );
		}

		//--------------------------------------------------------------------------------
		unsigned char CStructuredExceptionHelper::RtlInstallFunctionTableCallback( Cmp_unsigned__int64 TableIdentifier, Cmp_unsigned__int64 BaseAddress, unsigned long Length, void* Callback, void* Context, const wchar_t* OutOfProcessCallbackDll )
		{
			_WINQ_FCONTEXT( "CStructuredExceptionHelper::RtlInstallFunctionTableCallback" );
			return CKernel32::RtlInstallFunctionTableCallback( TableIdentifier, BaseAddress, Length, Callback, Context, OutOfProcessCallbackDll );
		}

		//--------------------------------------------------------------------------------
		void CStructuredExceptionHelper::RtlRestoreContext( nsWin32::PCONTEXT ContextRecord, nsWin32::PEXCEPTION_RECORD ExceptionRecord )
		{
			_WINQ_FCONTEXT( "CStructuredExceptionHelper::RtlRestoreContext" );
			CKernel32::RtlRestoreContext( reinterpret_cast< ::PCONTEXT >( ContextRecord ), reinterpret_cast< ::PEXCEPTION_RECORD >( ExceptionRecord  ) );
		}

		//--------------------------------------------------------------------------------
		nsWin32::LPTOP_LEVEL_EXCEPTION_FILTER CStructuredExceptionHelper::SetUnhandledExceptionFilter( nsWin32::LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter )
		{
			_WINQ_FCONTEXT( "CStructuredExceptionHelper::SetUnhandledExceptionFilter" );
			return reinterpret_cast< nsWin32::LPTOP_LEVEL_EXCEPTION_FILTER >( CKernel32::SetUnhandledExceptionFilter( reinterpret_cast< ::LPTOP_LEVEL_EXCEPTION_FILTER >( lpTopLevelExceptionFilter ) ) );
		}

	}//nsCodeServices

}//nsWin32

int __cdecl _XcptFilter ( unsigned long xcptnum, nsWin32::PEXCEPTION_POINTERS pxcptinfoptrs )
{
        //struct _XCPT_ACTION * pxcptact;
        //_PHNDLR phandler;
        //void *oldpxcptinfoptrs;
        //int oldfpecode;
        //int indx;

        //_ptiddata ptd = _getptd_noexit();
        //if (!ptd) {
        //    // we can't deal with it - pass it on.
        //    return(EXCEPTION_CONTINUE_SEARCH);
        //}

        //pxcptact = xcptlookup(xcptnum, ptd->_pxcptacttab);

        //if (pxcptact == NULL)
        //{
        //    phandler = SIG_DFL;
        //}
        //else
        //{
        //    phandler = pxcptact->XcptAction;
        //}

        ///*
        // * first, take care of all unrecognized exceptions and exceptions with
        // * XcptAction values of SIG_DFL.
        // */
        //if ( phandler == SIG_DFL )
        //        return(EXCEPTION_CONTINUE_SEARCH);



        ///*
        // * next, weed out all of the exceptions that need to be handled by
        // * dying, perhaps with a runtime error message
        // */
        //if ( phandler == SIG_DIE ) {
        //        /*
        //         * reset XcptAction (in case of recursion) and drop into the
        //         * except-clause.
        //         */
        //        pxcptact->XcptAction = SIG_DFL;
        //        return(EXCEPTION_EXECUTE_HANDLER);
        //}

        ///*
        // * next, weed out all of the exceptions that are simply ignored
        // */
        //if ( phandler == SIG_IGN )
        //        /*
        //         * resume execution
        //         */
        //        return(EXCEPTION_CONTINUE_EXECUTION);

        ///*
        // * the remaining exceptions all correspond to C signals which have
        // * signal handlers associated with them. for some, special setup
        // * is required before the signal handler is called. in all cases,
        // * if the signal handler returns, -1 is returned by this function
        // * to resume execution at the point where the exception occurred.
        // */

        ///*
        // * save the old value of _pxcptinfoptrs (in case this is a nested
        // * exception/signal) and store the current one.
        // */
        //oldpxcptinfoptrs = PXCPTINFOPTRS;
        //PXCPTINFOPTRS = pxcptinfoptrs;

        ///*
        // * call the user-supplied signal handler
        // *
        // * floating point exceptions must be handled specially since, from
        // * the C point-of-view, there is only one signal. the exact identity
        // * of the exception is passed in the global variable _fpecode.
        // */
        //if ( pxcptact->SigNum == SIGFPE ) {

        //        /*
        //         * reset the XcptAction field to the default for all entries
        //         * corresponding to SIGFPE.
        //         */
        //        for ( indx = _First_FPE_Indx ;
        //              indx < _First_FPE_Indx + _Num_FPE ;
        //              indx++ )
        //        {
        //                ( (struct _XCPT_ACTION *)(ptd->_pxcptacttab) +
        //                  indx )->XcptAction = SIG_DFL;
        //        }

        //        /*
        //         * Save the current _fpecode in case it is a nested floating
        //         * point exception (not clear that we need to support this,
        //         * but it's easy).
        //         */
        //        oldfpecode = FPECODE;

        //        /*
        //         * there are no exceptions corresponding to
        //         * following _FPE_xxx codes:
        //         *
        //         *      _FPE_UNEMULATED
        //         *      _FPE_SQRTNEG
        //         *
        //         * futhermore, STATUS_FLOATING_STACK_CHECK is
        //         * raised for both floating point stack under-
        //         * flow and overflow. thus, the exception does
        //         * not distinguish between _FPE_STACKOVERLOW
        //         * and _FPE_STACKUNDERFLOW. arbitrarily, _fpecode
        //         * is set to the former value.
        //         *
        //         * the following should be a switch statement but, alas, the
        //         * compiler doesn't like switching on unsigned longs...
        //         */
        //        if ( pxcptact->XcptNum == STATUS_FLOAT_DIVIDE_BY_ZERO )

        //                FPECODE = _FPE_ZERODIVIDE;

        //        else if ( pxcptact->XcptNum == STATUS_FLOAT_INVALID_OPERATION )

        //                FPECODE = _FPE_INVALID;

        //        else if ( pxcptact->XcptNum == STATUS_FLOAT_OVERFLOW )

        //                FPECODE = _FPE_OVERFLOW;

        //        else if ( pxcptact->XcptNum == STATUS_FLOAT_UNDERFLOW )

        //                FPECODE = _FPE_UNDERFLOW;

        //        else if ( pxcptact->XcptNum == STATUS_FLOAT_DENORMAL_OPERAND )

        //                FPECODE = _FPE_DENORMAL;

        //        else if ( pxcptact->XcptNum == STATUS_FLOAT_INEXACT_RESULT )

        //                FPECODE = _FPE_INEXACT;

        //        else if ( pxcptact->XcptNum == STATUS_FLOAT_STACK_CHECK )

        //                FPECODE = _FPE_STACKOVERFLOW;

        //        else if ( pxcptact->XcptNum == STATUS_FLOAT_MULTIPLE_TRAPS )

        //                FPECODE = _FPE_MULTIPLE_TRAPS;

        //        else if ( pxcptact->XcptNum == STATUS_FLOAT_MULTIPLE_FAULTS )

        //                FPECODE = _FPE_MULTIPLE_FAULTS;

        //        /*
        //         * call the SIGFPE handler. note the special code to support
        //         * old MS-C programs whose SIGFPE handlers expect two args.
        //         *
        //         * NOTE: THE CAST AND CALL BELOW DEPEND ON __cdecl BEING
        //         * CALLER CLEANUP!
        //         */
        //        (*(void (__cdecl *)(int, int))phandler)(SIGFPE, FPECODE);

        //        /*
        //         * restore the old value of _fpecode
        //         */
        //        FPECODE = oldfpecode;
        //}
        //else {
        //        /*
        //         * reset the XcptAction field to the default, then call the
        //         * user-supplied handler
        //         */
        //        pxcptact->XcptAction = SIG_DFL;
        //        (*phandler)(pxcptact->SigNum);
        //}

        ////restore the old value of _pxcptinfoptrs
        // 
        //PXCPTINFOPTRS = oldpxcptinfoptrs;

        return(EXCEPTION_CONTINUE_EXECUTION);

}

int __cdecl __CppExceptionFilter( unsigned long xcptnum, nsWin32::PEXCEPTION_POINTERS pxcptinfoptrs )
{
    if (xcptnum==('msc'|0xE0000000)) 
	{
        return _XcptFilter(xcptnum,pxcptinfoptrs);
    } 
	else 
	{
        return EXCEPTION_CONTINUE_SEARCH;
    }
}