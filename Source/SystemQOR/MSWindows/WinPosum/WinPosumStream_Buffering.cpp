
#include "WinPosum/WinPosumStream.h"
#include "WinPosum/WinPosumStreamImpl.h"
#include "WinPosum/WinPosumStdio.h"
#include <errno.h>
#include <assert.h>
#include <limits.h>

//------------------------------------------------------------------------------
namespace nsWin32
{
	//------------------------------------------------------------------------------
	int CPosumStream::_stbuf()
	{
        int index;

        assert( this != NULL );

        // do nothing if not a tty device 
        if( !_isatty( _fileno() ) )
		{
			return 0;
		}

        // Make sure stream is stdout/stderr and init _stdbuf index
        if( this == stdout )
		{
			index = 0;
		}
        else if ( this == stderr)
		{
			index = 1;
		}
        else
		{
			return 0;
		}

        // Make sure the stream is not already buffered.
        if( IsAnyBuffer() )
		{
			return 0;
		}

        // Allocate a buffer for this stream if we haven't done so yet.
        if( ( _stdbuf[index] == NULL) && ( ( _stdbuf[index] = malloc(_INTERNAL_BUFSIZ) ) == NULL) ) 
		{
			// Cannot allocate buffer. Use _charbuf this time
			_ptr = _base = (char*)&(_charbuf);
			_cnt = _bufsiz = 2;
        }
        else 
		{
			// Set up the buffer
			_ptr = _base = reinterpret_cast< char* >( _stdbuf[ index ] );
			_cnt = _bufsiz = _INTERNAL_BUFSIZ;
        }

        _flag |= (_IOWRT | _IOYOURBUF | _IOFLRTN );

        return 1;
	}

	//------------------------------------------------------------------------------
	void CPosumStream::_ftbuf( int flag )
	{
        assert( flag == 0 || flag == 1 );

        if( flag ) 
		{
			if( _flag & _IOFLRTN ) 
			{
				// Flush the stream and tear down temp buffering.
				_flush();
				_flag &= ~( _IOYOURBUF | _IOFLRTN );
				_bufsiz = 0;
				_base = _ptr = NULL;
			}
        }
	}

	//------------------------------------------------------------------------------
	int CPosumStream::fflush( void )
	{
		int rc = 0;

		//if stream is NULL, flush all streams

		if( this == NULL )
		{
			return( nsDetail::CPosumStdio::_Instance().flsall( nsDetail::CPosumStdio::FlushNULL ) );
		}

		flockfile();

		__try 
		{
			rc = _fflush_nolock();
		}
		__finally 
		{
			funlockfile();
		}

		return(rc);
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_fflush_nolock()
	{
		// if stream is NULL, flush all streams

		if( this == NULL )
		{
			return( nsDetail::CPosumStdio::_Instance().flsall( nsDetail::CPosumStdio::FlushNULL ) );
		}

		if( _flush() != 0 ) 
		{
			// _flush failed, don't attempt to commit
			return(EOF);
		}

		// commit to ensure data is written to disk

		if( _flag & _IOCOMMIT ) 
		{
			return( _commit( _fileno() ) ? EOF : 0 );
		}

		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_flush()
	{
        int rc = 0; // assume good return
        int nchar;

        if( ( _flag & ( _IOREAD | _IOWRT ) ) == _IOWRT && IsBigBuffer() && (nchar = (int)( _ptr - _base ) ) > 0 )
        {
			if( _write( _fileno(), _base, nchar ) == nchar ) 
			{
				// if this is a read/write file, clear _IOWRT so that next operation can be a read
				if( _IORW & _flag )
				{
					_flag &= ~_IOWRT;
				}
			}
			else 
			{
				_flag |= _IOERR;
				rc = EOF;
			}
        }

        _ptr = _base;
        _cnt = 0;

        return rc;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_commit( int filedes )
	{
        int retval = 0;

        // if filedes out of range, complain
        //_CHECK_FH_RETURN( filedes, EBADF, -1 );
        //_VALIDATE_RETURN((filedes >= 0 && (unsigned)filedes < (unsigned)_nhandle), EBADF, -1);

		if( !( m_chFlags & FOPEN ) )
		{
			errno = EBADF;
			return -1;
		}

		flockfile();

		__try 
		{
            if( m_chFlags & FOPEN ) 
			{
				if( ! m_pFile->FlushBuffers() )
				{
					retval = m_ErrorHelper.GetLastError();
				}
				else 
				{
					retval = 0;     // return success
				}

				// map the OS return code to C errno value and return code
				if( retval == 0 )
				{
					goto good;
				}

				_set_doserrno( retval );
            }

	        errno = EBADF;
		    retval = -1;

			//assert(("Invalid file descriptor. File possibly closed by a different thread",0));
good :
        ; 
		}
        __finally 
		{
			funlockfile();
        }

        return retval;
	}

	//------------------------------------------------------------------------------
	void CPosumStream::setbuf( char* buffer )
	{
		assert( this != NULL );

        if( buffer == NULL )
		{
			setvbuf( NULL, _IONBF, 0 );
		}
        else
		{
			setvbuf( buffer, _IOFBF, BUFSIZ );
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStream::setvbuf( char* buffer, int type, size_t size )
	{
        int retval = 0;   // assume good return

		if( this == 0 )
		{
			errno = EINVAL;
			return -1;
		}

        //(1) Make sure type is one of the three legal values.
        //(2) If we are buffering, make sure size is between 2 and INT_MAX.

		if( !( (type == _IONBF) || (type == _IOFBF) || (type == _IOLBF) ) )
		{
			errno = EINVAL;
			return -1;
		}

        if ((type == _IOFBF) || (type == _IOLBF))
        {
			if( !( (2 <= size) && (size <= INT_MAX) ) )
			{
				errno = EINVAL;
				return -1;
			}
        }

        //force size to be even by masking down to the nearest multiple of 2
         
        size &= (size_t)~1;

        //Init stream pointers
         

        //Lock the file
        flockfile();
        
        __try 
		{

        //Flush the current buffer and free it, if it is ours.
         
        _flush();
        _freebuf();

        /* Clear a bunch of bits in stream->_flag (all bits related to
         * buffering and those which used to be in stream2->_flag2). Most
         * of these should never be set when setvbuf() is called, but it
         * doesn't cost anything to be safe.
         */
        _flag &= ~( _IOMYBUF | _IOYOURBUF | _IONBF | _IOSETVBUF | _IOFEOF | _IOFLRTN | _IOCTRLZ );

        //CASE 1: No Buffering.
         
        if( type & _IONBF ) 
		{
			_flag |= _IONBF;
			buffer = (char *)&(_charbuf);
			size = 2;
        }

        /* NOTE: Cases 2 and 3 (below) cover type == _IOFBF or type == _IOLBF
         * Line buffering is treated as the same as full buffering, so the
         * _IOLBF bit in stream->_flag is never set. Finally, since _IOFBF is
         * defined to be 0, full buffering is simply assumed whenever _IONBF
         * is not set.
         */

        //CASE 2: Default Buffering -- Allocate a buffer for the user.
         
        else if( buffer == NULL ) 
		{
            if( ( buffer = reinterpret_cast< char* >( malloc(size) ) ) == NULL ) 
			{
				retval = -1;
				goto done;
			}
			_flag |= _IOMYBUF | _IOSETVBUF;
        }

        //CASE 3: User Buffering -- Use the buffer supplied by the user.
        else 
		{
			_flag |= _IOYOURBUF | _IOSETVBUF;
        }

        //Common return for all cases.
         
        _bufsiz = (int)size;
        _ptr = _base = buffer;
        _cnt = 0;
done:
		;
		}
        __finally 
		{
			funlockfile();
        }

        return retval;
	}


	//------------------------------------------------------------------------------
	void CPosumStream::_getbuf()
	{
		assert( this != NULL );

        // Try to get a big buffer
        if( _base = reinterpret_cast< char* >( malloc( _INTERNAL_BUFSIZ ) ) )
        {
			// Got a big buffer
			_flag |= _IOMYBUF;
			_bufsiz = _INTERNAL_BUFSIZ;
        }
        else 
		{
			// Did NOT get a buffer - use single char buffering.
			_flag |= _IONBF;
			_base = (char *)&(_charbuf);
			_bufsiz = 2;
        }

        _ptr = _base;
        _cnt = 0;

        return;
	}

	//------------------------------------------------------------------------------
	void CPosumStream::_freebuf()
	{
		assert( this != NULL );

		if( IsInUse() && IsMyBuffer() )
		{
			free( _base );
			_flag &= ~(_IOMYBUF | _IOSETVBUF);
			_base = _ptr = NULL;
			_cnt = 0;
		}
	}

}//nsWin32


