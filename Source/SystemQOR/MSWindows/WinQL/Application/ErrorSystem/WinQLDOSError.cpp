//WinQLDOSError.cpp

// Copyright Querysoft Limited 2012 - . All rights reserved.
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

#include "WinQL/Application/ErrorSystem/WinQLDOSError.h"
#include "WinQL/Application/Threading/WinQLThread.h"
#include <errno.h>

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//------------------------------------------------------------------------------
	CDOSError::errentry CDOSError::errtable[] = 
	{
        {  ErrorInvalidFunction,			EINVAL    },  /* 1 */
        {  ErrorFileNotFound,				ENOENT    },  /* 2 */
        {  ErrorPathNotFound,				ENOENT    },  /* 3 */
        {  ErrorTooManyOpenFiles,			EMFILE    },  /* 4 */
        {  ErrorAccessDenied,				EACCES    },  /* 5 */
        {  ErrorInvalidHandle,				EBADF     },  /* 6 */
        {  ErrorArenaTrashed,				ENOMEM    },  /* 7 */
        {  ErrorNotEnoughMemory,			ENOMEM    },  /* 8 */
        {  ErrorInvalidBlock,				ENOMEM    },  /* 9 */
        {  ErrorBadEnvironment,				E2BIG     },  /* 10 */
        {  ErrorBadFormat,					ENOEXEC   },  /* 11 */
        {  ErrorInvalidAccess,				EINVAL    },  /* 12 */
        {  ErrorInvalidData,				EINVAL    },  /* 13 */
        {  ErrorInvalidDrive,				ENOENT    },  /* 15 */
        {  ErrorCurrentDirectory,			EACCES    },  /* 16 */
        {  ErrorNotSameDevice,				EXDEV     },  /* 17 */
        {  ErrorNoMoreFiles,				ENOENT    },  /* 18 */
        {  ErrorLockViolation,				EACCES    },  /* 33 */
        {  ErrorBadNetPath,					ENOENT    },  /* 53 */
        {  ErrorNetworkAccessDenied,		EACCES    },  /* 65 */
        {  ErrorBadNetName,					ENOENT    },  /* 67 */
        {  ErrorFileExists,					EEXIST    },  /* 80 */
        {  ErrorCannotMake,					EACCES    },  /* 82 */
        {  ErrorFailI24,					EACCES    },  /* 83 */
        {  ErrorInvalidParameter,			EINVAL    },  /* 87 */
        {  ErrorNoProcSlots,				EAGAIN    },  /* 89 */
        {  ErrorDriveLocked,				EACCES    },  /* 108 */
        {  ErrorBrokenPipe,					EPIPE     },  /* 109 */
        {  ErrorDiskFull,					ENOSPC    },  /* 112 */
        {  ErrorInvalidTargetHandle,		EBADF     },  /* 114 */
        {  ErrorInvalidHandle,				EINVAL    },  /* 124 */
        {  ErrorWaitNoChildren,				ECHILD    },  /* 128 */
        {  ErrorChildNotComplete,			ECHILD    },  /* 129 */
        {  ErrorDirectAccessHandle,			EBADF     },  /* 130 */
        {  ErrorNegativeSeek,				EINVAL    },  /* 131 */
        {  ErrorSeekOnDevice,				EACCES    },  /* 132 */
        {  ErrorDirNotEmpty,				ENOTEMPTY },  /* 145 */
        {  ErrorNotLocked,					EACCES    },  /* 158 */
        {  ErrorBadPathName,				ENOENT    },  /* 161 */
        {  ErrorMaxThreadsReached,			EAGAIN    },  /* 164 */
        {  ErrorLockFailed,					EACCES    },  /* 167 */
        {  ErrorAlreadyExists,				EEXIST    },  /* 183 */
        {  ErrorFilenameExcedRange,			ENOENT    },  /* 206 */
        {  ErrorNestingNotAllowed,			EAGAIN    },  /* 215 */
        {  ErrorNotEnoughQuota,				ENOMEM    }    /* 1816 */
	};

	// size of the table
#define ERRTABLESIZE (sizeof(errtable)/sizeof(errtable[0]))
// The following two constants must be the minimum and maximum values in the (contiguous) range of Exec Failure errors.
#define MIN_EXEC_ERROR ErrorInvalidStartingCodeSeg
#define MAX_EXEC_ERROR ErrorInfLoopInRelocChain

// These are the low and high value in the range of errors that are access violations
#define MIN_EACCES_RANGE ErrorWriteProtect
#define MAX_EACCES_RANGE ErrorSharingBufferExceeded

	//--------------------------------------------------------------------------------
	void CDOSError::MapError( unsigned long ulOSErrNo )
	{
		Set( ulOSErrNo );
		errno = Get_errno_FromOSErr( ulOSErrNo );
	}

	//--------------------------------------------------------------------------------
	void CDOSError::Set( unsigned long ulOSErrNo )
	{
		CThread* pThread = t_pCurrentWin32Thread;
		if( pThread != 0 )
		{
			pThread->Data().DOSErrorNumber() = ulOSErrNo;
		}
	}

	//--------------------------------------------------------------------------------
	int CDOSError::Get_errno_FromOSErr( unsigned long ulOSErrNo )
	{
		int i;

		// check the table for the OS error code
		for( i = 0; i < ERRTABLESIZE; ++i ) 
		{
			if( ulOSErrNo == errtable[ i ].oscode ) 
			{
				return  errtable[ i ].errnocode;
			}
		}

		// The error code wasn't in the table.  We check for a range of 
		// EACCES errors or exec failure errors (ENOEXEC).  Otherwise   
		// EINVAL is returned.

		if( ulOSErrNo >= MIN_EACCES_RANGE && ulOSErrNo <= MAX_EACCES_RANGE )
		{
			return EACCESS;
		}
		else if( ulOSErrNo >= MIN_EXEC_ERROR && ulOSErrNo <= MAX_EXEC_ERROR )
		{
			return ENOEXEC;
		}
		else
		{
			return EINVAL;
		}
	}

}//nsWin32

