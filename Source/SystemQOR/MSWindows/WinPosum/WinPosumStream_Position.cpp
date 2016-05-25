
#include "WinPosum/WinPosumStream.h"
#include "WinPosum/WinPosumStreamImpl.h"
#include "WinQL/Application/ErrorSystem/WinQLDOSError.h"
#include <errno.h>
#include <assert.h>

//------------------------------------------------------------------------------
namespace nsWin32
{
	//------------------------------------------------------------------------------	
	void CPosumStream::rewind( void )
	{
		int fd;

		if( this == NULL )
		{
			return;
		}

		fd = _fileno();

		// Lock the file
		flockfile();

		__try 
		{
			// Flush the stream
			_flush();

			// Clear errors
			_flag &= ~(_IOERR|_IOEOF);
			m_chFlags &= ~(FEOFLAG);

			// Set flags
			// [note: _flush set _cnt=0 and _ptr=_base]
			if( _flag & _IORW )
			{
				_flag &= ~(_IOREAD|_IOWRT);
			}

			// Position to beginning of file
			if( _lseek( fd, 0L, 0 ) == -1 )
			{
				_flag |= _IOERR;
			}
		}
		__finally 
		{
			// unlock stream
			funlockfile();
		}
	}
	
	//------------------------------------------------------------------------------
	int CPosumStream::fgetpos( fpos_t* pos )
	{
		if( this == 0 || pos == 0 )
		{
			errno = EINVAL;
			return -1;
		}

		if( ( *pos = _ftelli64() ) != -1i64 )
		{
			return(0);
		}
		else
		{
			return(-1);
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStream::fsetpos( const fpos_t* pos )
	{
		if( this == NULL || pos == NULL )
		{
			errno = EINVAL;
			return -1;
		}
        
        return( _fseeki64( *pos, SEEK_SET ) );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::fseek( long int offset, int whence )
	{
		return fseeko( static_cast< off_t >( offset ), whence );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::fseeko( off_t offset, int whence )
	{
		return _fseeki64( static_cast< Cmp__int64 >( offset ), whence );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_fseeki64( Cmp__int64 offset, int whence )
	{
	    int retval = 0;

		if( this == 0 )
		{
			errno = EINVAL;
			return -1;
		}

		if( !( ( whence == SEEK_SET ) || ( whence == SEEK_CUR ) || ( whence == SEEK_END ) ) )
		{
			errno = EINVAL;
			return -1;
		}

		flockfile();

		__try 
		{
			retval = _fseeki64_nolock( offset, whence );
		}
		__finally 
		{
			funlockfile();
		}

		return(retval);
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_fseeki64_nolock( Cmp__int64 offset, int whence )
	{
		assert( this != 0 );

		if ( !IsInUse() || ((whence != SEEK_SET) && (whence != SEEK_CUR) && (whence != SEEK_END ) ) ) 
		{
			errno = EINVAL;
			return -1;
		}

		// Clear EOF flag
		_flag &= ~_IOEOF;

		// If seeking relative to current location, then convert to a seek relative to beginning of file.  This accounts for buffering, etc. by letting ftell() tell us where we are.

		if( whence == SEEK_CUR ) 
		{
			offset += _ftelli64_nolock();
			whence = SEEK_SET;
		}

		// Flush buffer as necessary */

		_flush();

		// If file opened for read/write, clear flags since we don't know what the user is going to do next. If the file was opened for read access only, decrease _bufsiz so that the next _filbuf won't cost quite so much

		if( _flag & _IORW )
		{
			_flag &= ~(_IOWRT|_IOREAD);
		}
		else if( ( _flag & _IOREAD ) && ( _flag & _IOMYBUF ) && !( _flag & _IOSETVBUF ) )
		{
			_bufsiz = _SMALL_BUFSIZ;
		}

		// Seek to the desired locale and return.

		return( _lseeki64( _fileno(), offset, whence ) == -1i64 ? -1 : 0 );
	}

	//------------------------------------------------------------------------------
	long int CPosumStream::ftell( void )
	{
		return static_cast< long >( ftello() );
	}

	//------------------------------------------------------------------------------
	off_t CPosumStream::ftello()
	{
		off_t retval = 0;

		if( this == 0 )
		{
			errno = EINVAL;
			return -1;
		}

		flockfile();

		__try 
		{
			retval = _ftell_nolock();
		}
		__finally 
		{
			funlockfile();
		}

		return retval;
	}

	//------------------------------------------------------------------------------
	long CPosumStream::_ftell_nolock()
	{
        unsigned int offset;
        long filepos;
        char* p;
        char* max;
        int fd;
        unsigned int rdcnt;
        char tmode;

		if( this == 0 )
		{
			errno = EINVAL;
			return -1;
		}
       
        fd = _fileno();

        if( _cnt < 0 )
		{
            _cnt = 0;
		}

        if( ( filepos = _lseek( fd, 0L, SEEK_CUR ) ) < 0L )
		{
            return(-1L);
		}

        // _lseek validates fd, so it's now ok to retrieve the textmode
        tmode = m_chTextMode;

        if( ! IsBigBuffer() )            // _IONBF or no buffering designated
		{
            return( filepos - _cnt );
		}

        offset = (unsigned)( _ptr - _base );

        if( _flag & ( _IOWRT | _IOREAD ) ) 
		{
            if( tmode == __IOINFO_TM_UTF8 && m_bUTF8Translations )
            {
                size_t curpos = (size_t)( _ptr - _base) / sizeof(wchar_t);

                if( _cnt == 0 )
				{
                    return filepos;
				}
                else 
				{
                    unsigned long bytes_read;
                    char buf[ _INTERNAL_BUFSIZ ];

                    __int64 basepos = _lseeki64( fd, m_i64StartPos, SEEK_SET );

                    if( basepos != m_i64StartPos )
					{
                        return (-1);
					}

					if( ! m_pFile->Read( buf, _INTERNAL_BUFSIZ, &bytes_read, 0 ) )
					{
                        return (-1);
					}

                    if( _lseek( fd, filepos, SEEK_SET ) < 0 )
					{
                        return -1;
					}

                    if( curpos > bytes_read )
					{
                        return (-1);
					}

                    p = buf;
                    while( curpos-- && ( p < buf + bytes_read ) )
                    {
                        if( *p == CR ) 
						{
                            // *p is CR, so must check next char for LF
                            if( p < (char *)buf + bytes_read - 1) 
							{
                                if( *(p + 1) == LF ) 
								{
                                    p ++;
                                }
                            }
                        }
                        else 
						{
                            p += _utf8_no_of_trailbytes(*p);
                        }
                        p++;
                    }
                    return (long) (basepos + (size_t)(p - buf));
                }
            }
            if( m_chFlags & FTEXT )
			{
                for( p = _base; p < _ptr; p++ )
				{
                    if( *p == '\n' )  // adjust for '\r'
					{
                        offset++;
					}
				}
			}
        }
        else if( !( _flag & _IORW ) ) 
		{
            errno = EINVAL;
            return(-1L);
        }

        if( filepos == 0L )
		{
            return((long)offset);
		}

        if( _flag & _IOREAD )
		{
            if( _cnt == 0 )  // filepos holds correct location
			{
                offset = 0;
			}
            else 
			{

                // Subtract out the number of unread bytes left in the buffer. 
				// [We can't simply use _iob[]._bufsiz because the last read may have hit EOF and, thus, the buffer was not completely filled.] 

                rdcnt = _cnt + (unsigned)( _ptr - _base );

                // If text mode, adjust for the cr/lf substitution. If binary mode, we're outta here.
                if( m_chFlags & FTEXT ) 
				{
                    // (1) If we're not at eof, simply copy _bufsiz onto rdcnt to get the # of untranslated chars read. 
					// (2) If we're at eof, we must look through the buffer expanding the '\n' chars one at a time.

                    // [NOTE: Performance issue -- it is faster to do the two _lseek() calls than to blindly go through and expand the '\n' chars regardless of whether we're at eof or not.]

                    if( _lseek( fd, 0L, SEEK_END ) == filepos ) 
					{

                        max = _base + rdcnt;
                        for( p = _base; p < max; p++ )
						{
                            if( *p == '\n' )
							{                                
                                rdcnt++;// adjust for '\r'
							}
						}

                        // If last byte was ^Z, the lowio read didn't tell us about it. Check flag and bump count, if necessary.

                        if ( _flag & _IOCTRLZ )
						{
                            ++rdcnt;
						}
                    }
                    else 
					{
                        if( _lseek( fd, filepos, SEEK_SET ) < 0 )
						{
                            return (-1);
						}

                        /* We want to set rdcnt to the number of bytes originally read into the stream buffer (before crlf->lf translation). 
						In most cases, this will just be _bufsiz. However, the buffer size may have been changed, due to fseek optimization, 
						at the END of the last _filbuf call. */

                        if( ( rdcnt <= _SMALL_BUFSIZ ) && ( _flag & _IOMYBUF ) && !( _flag & _IOSETVBUF ) )
                        {
                            // The translated contents of the buffer is small and we are not at eof. The buffer size must have been set to _SMALL_BUFSIZ during the last _filbuf call.
                            rdcnt = _SMALL_BUFSIZ;
                        }
                        else
						{
                            rdcnt = _bufsiz;
						}

                        // If first byte in untranslated buffer was a '\n', assume it was preceeded by a '\r' which was discarded by the previous read operation and count the '\n'.
                        if( m_chFlags & FCRLF )
						{
                            ++rdcnt;
						}
                    }

                    if( tmode == __IOINFO_TM_UTF8 )
					{
                        rdcnt /= sizeof(wchar_t);
					}
                }

                filepos -= (long)rdcnt;

            }
		}

        if( tmode == __IOINFO_TM_UTF8 )
		{
            offset /= sizeof( wchar_t );
		}

        return( filepos + (long)offset );
	}

	//------------------------------------------------------------------------------
	Cmp__int64 CPosumStream::_ftelli64()
	{
		Cmp__int64 retval = 0;

		if( this == 0 )
		{
			errno = EINVAL;
			return -1;
		}

		flockfile();

		__try 
		{
			retval = _ftelli64_nolock();
		}
		__finally 
		{
			funlockfile();
		}

		return retval;
	}

	//------------------------------------------------------------------------------
	Cmp__int64 CPosumStream::_ftelli64_nolock()
	{
        size_t offset;
        Cmp__int64 filepos;
        char *p;
        char *max;
        int fd;
        size_t rdcnt;
        char tmode;

        assert( this != 0 );

        fd = _fileno();

        if( _cnt < 0 )
		{
			_cnt = 0;
		}

        if( ( filepos = _lseeki64( fd, 0i64, SEEK_CUR ) ) < 0L )
		{
			return(-1i64);
		}

        // _lseek164 validates fd, so it's now ok to retrieve the textmode
        tmode = m_chTextMode;

        if( !IsBigBuffer() )            /* _IONBF or no buffering designated */
		{
			return( filepos - _cnt );
		}

        offset = (size_t)( _ptr - _base );

        if( _flag & (_IOWRT|_IOREAD) ) 
		{
            if( tmode == __IOINFO_TM_UTF8 && m_bUTF8Translations )
            {
                size_t curpos = (size_t)( _ptr - _base ) / sizeof(wchar_t);

                if( _cnt == 0 )
				{
                    return filepos;
				}
                else 
				{
                    unsigned long bytes_read;
                    char buf[ _INTERNAL_BUFSIZ ];

                    __int64 basepos = _lseeki64( fd, m_i64StartPos, SEEK_SET );

                    if( basepos !=  m_i64StartPos )
					{
                        return (-1);
					}

					if( ! m_pFile->Read( buf, _INTERNAL_BUFSIZ, &bytes_read, 0 ) )                    
					{
                        return (-1);
					}

                    if( _lseeki64( fd, filepos, SEEK_SET ) < 0 )
					{
                        return -1;
					}

                    if( curpos > bytes_read )
					{
                        return (-1);
					}

                    p = buf;
                    while( curpos-- && (p < buf + bytes_read ) )
                    {
                        if( *p == CR ) 
						{
                            // *p is CR, so must check next char for LF
                            if( p < (char *)buf + bytes_read - 1 ) 
							{
                                if( *( p + 1 ) == LF ) 
								{
                                    p ++;
                                }
                            }
                        }
                        else 
						{
                            p += _utf8_no_of_trailbytes(*p);
                        }
                        p++;
                    }
                    return basepos + (size_t)(p - buf);
                }
            }

            if ( m_chFlags & FTEXT )
			{
				for( p = _base; p < _ptr; p++ )
				{
					if( *p == '\n' )  // adjust for '\r'
					{
						offset++;
					}
				}
			}
        }
        else if( !( _flag & _IORW ) ) 
		{
            errno = EINVAL;
            return (-1i64);
        }

        if( filepos == 0i64 )
		{
			return((__int64)offset);
		}

        if( _flag & _IOREAD ) 
		{
            if( _cnt == 0 )  // filepos holds correct location
			{
				offset = 0;
			}
            else 
			{
                /* Subtract out the number of unread bytes left in the
                    buffer. [We can't simply use _iob[]._bufsiz because
                    the last read may have hit EOF and, thus, the buffer
                    was not completely filled.] */

                rdcnt = _cnt + (size_t)( _ptr - _base );

                /* If text mode, adjust for the cr/lf substitution. If
                    binary mode, we're outta here. */
                if( m_chFlags & FTEXT ) 
				{
                    /* (1) If we're not at eof, simply copy _bufsiz
                        onto rdcnt to get the # of untranslated
                        chars read. (2) If we're at eof, we must
                        look through the buffer expanding the '\n'
                        chars one at a time. */

                    /* [NOTE: Performance issue -- it is faster to
                        do the two _lseek() calls than to blindly go
                        through and expand the '\n' chars regardless
                        of whether we're at eof or not.] */

                    if( _lseeki64( fd, 0i64, SEEK_END ) == filepos ) 
					{
                        max = _base + rdcnt;
                        for( p = _base; p < max; p++ )
						{
							if( *p == '\n' )
							{	// adjust for '\r'
								rdcnt++;
							}
						}

                        // If last byte was ^Z, the lowio read didn't tell us about it.  Check flag and bump count, if necessary.
                        if( _flag & _IOCTRLZ )
						{
							++rdcnt;
						}
                    }
                    else 
					{
                        if( _lseeki64( fd, filepos, SEEK_SET ) < 0 )
						{
                            return (-1);
						}

                        /* We want to set rdcnt to the number
                            of bytes originally read into the
                            stream buffer (before crlf->lf
                            translation). In most cases, this
                            will just be _bufsiz. However, the
                            buffer size may have been changed,
                            due to fseek optimization, at the
                            END of the last _filbuf call. */

                        if( ( rdcnt <= _SMALL_BUFSIZ ) && ( _flag & _IOMYBUF ) && !( _flag & _IOSETVBUF ) )
                        {
                            // The translated contents of the buffer is small and we are not at eof. The buffer size must have been set to _SMALL_BUFSIZ during the last _filbuf call.
                            rdcnt = _SMALL_BUFSIZ;
                        }
                        else
						{
							rdcnt = _bufsiz;
						}

                        // If first byte in untranslated buffer was a '\n', assume it was preceeded by a '\r' which was discarded by the previous read operation and count the '\n'.
                        if ( m_chFlags & FCRLF )
						{
                            ++rdcnt;
						}
                    }

                }

                if( tmode == __IOINFO_TM_UTF8 )
				{
                    rdcnt /= sizeof(wchar_t);
				}

                filepos -= (__int64)rdcnt;

            }
		}

        if( tmode == __IOINFO_TM_UTF8 )
		{
            offset /= sizeof(wchar_t);
		}

        return( filepos + (__int64)offset );
	}

	//------------------------------------------------------------------------------
	Cmp__int64 CPosumStream::_lseeki64( int fh, Cmp__int64 pos, int mthd )
	{
        __int64 r = -1i64;

        //_CHECK_FH_CLEAR_OSSERR_RETURN( fh, EBADF, -1i64 );
        //_VALIDATE_CLEAR_OSSERR_RETURN((fh >= 0 && (unsigned)fh < (unsigned)_nhandle), EBADF, -1i64);

		if( !( m_chFlags & FOPEN ) )
		{
			errno = EBADF;
			return -1i64;
		}

		flockfile();
        __try 
		{
			// make sure the file is open (after locking)
            if ( m_chFlags & FOPEN )
			{
				r = _lseeki64_nolock( fh, pos, mthd );  /* seek */
			}
			else 
			{
				errno = EBADF;
				_set_doserrno( 0 );  // not OS error
				r =  -1i64;
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
	Cmp__int64 CPosumStream::_lseeki64_nolock ( int fh, Cmp__int64 pos, int mthd )
	{
        LARGE_INTEGER newpos;       // new file position

        if( !m_pFile || m_pFile->Handle()->IsInvalid() )
        {
            errno = EBADF;
            //_ASSERTE(("Invalid file descriptor. File possibly closed by a different thread",0));
            return( -1i64 );
        }


		if( !m_pFile->SetPointerEx( *(LARGE_INTEGER*)&pos, &newpos, mthd  ) )
        {
			CDOSError::MapError( m_ErrorHelper.GetLastError() );
			return( -1i64 );
        }

        m_chFlags &= ~FEOFLAG;			// clear the ctrl-z flag on the file
        return( newpos.QuadPart );		// return
	}

	//------------------------------------------------------------------------------
	long CPosumStream::_lseek( int fh, long pos, int mthd )
	{
        int r = 0;

        //_CHECK_FH_CLEAR_OSSERR_RETURN( fh, EBADF, -1 );
        //_VALIDATE_CLEAR_OSSERR_RETURN((fh >= 0 && (unsigned)fh < (unsigned)_nhandle), EBADF, -1);

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
				r = _lseek_nolock( fh, pos, mthd );
			}
			else 
			{
				errno = EBADF;
				_set_doserrno( 0 );
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
	long CPosumStream::_lseek_nolock( int fh, long pos, int mthd )
	{
        LARGE_INTEGER  large_pos;        // file position
        LARGE_INTEGER  saved_pos;        // original file position
        LARGE_INTEGER  new_pos;          // new file position

        // tell o.s. to seek

        large_pos.QuadPart = 0;

        // Save the current file pointer

		if( ! m_pFile->SetPointerEx( large_pos, &saved_pos, File_Current ) )
		{
            CDOSError::MapError( m_ErrorHelper.GetLastError() );
            return -1;
        }

        // Try to set the new file pointer
        large_pos.QuadPart = pos;

		if( ! m_pFile->SetPointerEx( large_pos, &new_pos, mthd ) )
		{
            CDOSError::MapError( m_ErrorHelper.GetLastError() );
            return -1;
        }

        // The call succeeded, but the new file pointer location is too large for the return type or a negative value.
        // So, restore file pointer to saved location and return error.
        if( new_pos.u.HighPart != 0 ) 
		{
			m_pFile->SetPointerEx( saved_pos, NULL, File_Begin );
            errno = EINVAL;
            return -1;
        }

		m_chFlags &= ~FEOFLAG;        // clear the ctrl-z flag on the file
        return new_pos.u.LowPart;       // return
	}

}//nsWin32
