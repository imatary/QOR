
#include "WinPosum/WinPosumStream.h"
#include "WinPosum/WinPosumStreamImpl.h"
#include "WinPosum/WinPosumStdio.h"
#include "WinQL/Application/ErrorSystem/WinQLDOSError.h"
#include <errno.h>

//------------------------------------------------------------------------------
namespace nsWin32
{
	//------------------------------------------------------------------------------
	int CPosumStream::fclose( void )
	{
		int result = EOF;

		if( this == 0 )
		{
			errno = EINVAL;
			return EOF;
		}
		
		// If stream is a string, simply clear flag and return EOF
		if( _flag & _IOSTRG )
		{
			_flag = 0;
		}		
		else		// Stream is a real file.
		{
			flockfile();
	        __try 
			{
			    result = _fclose_nolock();
			}
			__finally 
			{
				funlockfile();
			}
		}

		return result;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_fclose_nolock()
	{
        int result = EOF;

		if( this == 0 )
		{
			errno = EINVAL;
			return EOF;
		}

        if( IsInUse() )
		{
			// Stream is in use:
			//(1) flush stream
			//(2) free the buffer
			//(3) close the file
			//(4) delete the file if temporary

			result = _flush();
			_freebuf();

			if( _close( _fileno() ) < 0 )
			{
				result = EOF;
			}
			else if( _tmpfname != NULL ) 
			{
				//temporary file (i.e., one created by tmpfile() call). 
				//delete, if necessary (don't have to on Windows NT because it was done by the system when the handle was closed). also, free up the heap block holding the pathname.
				free( _tmpfname );
				_tmpfname = NULL;
			}
        }

        _flag = 0;
        return result;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_close( int fh )
	{
        int r = 0;
        
        //_CHECK_FH_CLEAR_OSSERR_RETURN( fh, EBADF, -1 );
        //_VALIDATE_CLEAR_OSSERR_RETURN((fh >= 0 && (unsigned)fh < (unsigned)_nhandle), EBADF, -1);
        //_VALIDATE_CLEAR_OSSERR_RETURN((_osfile(fh) & FOPEN), EBADF, -1);

		flockfile();

        __try 
		{
            if ( m_chFlags & FOPEN )
			{
				r = _close_nolock( fh );
			}
            else 
			{
                errno = EBADF;
                r = -1;
                //assert(("Invalid file descriptor. File possibly closed by a different thread",0));
            }
        }
        __finally 
		{
			funlockfile();
        }

        return r;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_close_nolock( int fh )
	{
        unsigned long dosretval;

		/* Close the underlying OS file handle. Special cases:
         *      1. If _get_osfhandle(fh) is INVALID_HANDLE_VALUE, don't try
         *         to actually close it. Just reset the lowio info so the
         *         handle can be reused. The standard handles are setup like
         *         this in Windows app, or a background app.
         *      2. If fh is STDOUT or STDERR, and if STDOUT and STDERR are
         *         mapped to the same OS file handle, skip the CloseHandle
         *         is skipped (without error). STDOUT and STDERR are the only
         *         handles for which this support is provided. Other handles
         *         are mapped to the same OS file handle only at the
         *         programmer's risk.
         */

		if( _file > 2 )
		{
			delete m_pFile;
			m_pFile = 0;

			CDOSError::MapError( m_ErrorHelper.GetLastError() );
		}

		/*
        if( ( _get_osfhandle( fh ) == (intptr_t)INVALID_HANDLE_VALUE) || (((fh == 1 && (_osfile(2) & FOPEN)) || (fh == 2 && (_osfile(1) & FOPEN))) && (_get_osfhandle(1) == _get_osfhandle(2)) ) || CloseHandle( (HANDLE)_get_osfhandle(fh) ) )
        {
			dosretval = 0L;
        }
        else
		{
			
		}
		*/

		nsDetail::CPosumStdio::_Instance().FreeHandle( _file );

        //_free_osfhnd(fh);

		m_chFlags = 0;					//clear file flags

        if( dosretval ) 
		{
            // OS error
            return -1;
        }

        return 0;
	}

}//nsWin32

