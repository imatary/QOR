
#include "WinPosum/WinPosumStream.h"
#include "WinPosum/WinPosumStreamImpl.h"
#include "WinQL/Application/WinQLApplication.h"
#include "WinQL/CodeServices/Locale/WinQLLocale.h"
#include "WinQL/Definitions/Errors.h"
#include "WinQL/Application/ErrorSystem/WinQLDOSError.h"
#include "WinQL/Application/SubSystems/WinQLTerminal.h"
#include <errno.h>
#include <assert.h>
#include <stdlib.h>

//------------------------------------------------------------------------------
namespace nsWin32
{
	//------------------------------------------------------------------------------
	int CPosumStream::_read_nolock(  int fh, void* inputbuf, unsigned cnt )
	{
        int bytes_read = 0;				// number of bytes read
        char* buffer;					// buffer to read to
        int os_read;					// bytes read on OS call
        char *p, *q;					// pointers into buffer
        wchar_t *pu, *qu;				// wchar_t pointers into buffer for UTF16 
        char peekchr;					// peek-ahead character
        wchar_t wpeekchr;				// peek-ahead wchar_t
        Cmp__int64 filepos;				// file position after seek
        unsigned long dosretval;		// o.s. return value
        char tmode;						// textmode - ANSI/UTF-8/UTF-16
        bool fromConsole = 0;			// true when reading from console
        void* buf;						// buffer to read to
        int retval = -2;				// return value
        unsigned inputsize = cnt;

        //_CHECK_FH_CLEAR_OSSERR_RETURN( fh, EBADF, -1 );
        //_VALIDATE_CLEAR_OSSERR_RETURN((fh >= 0 && (unsigned)fh < (unsigned)_nhandle), EBADF, -1);

		if( !( m_chFlags & FOPEN ) )
		{
			errno = EBADF;
			return -1;
		}
        
		if( cnt > IntMax )
		{
			errno = EINVAL;
			return -1;
		}

        if( cnt == 0 || ( m_chFlags & FEOFLAG ) ) 
		{
            return 0;		// nothing to read or at EOF, so return 0 read
        }

		if( inputbuf == NULL )
		{
			errno = EINVAL;
			return -1;
		}

        tmode = m_chTextMode;

        switch( tmode ) 
		{
            case __IOINFO_TM_UTF8 :
                /* For a UTF-8 file, we need 2 buffers, because after reading we
                   need to convert it into UNICODE - MultiByteToWideChar doesn't do
                   in-place conversions. */

                /* MultiByte To WideChar conversion may double the size of the
                   buffer required & hence we divide cnt by 2 */

                /*
                 * Since we are reading UTF8 stream, cnt bytes read may vary
                 * from cnt wchar_t characters to cnt/4 wchar_t characters. For
                 * this reason if we need to read cnt characters, we will
                 * allocate MBCS buffer of cnt. In case cnt is 0, we will
                 * have 4 as minimum value. This will make sure we don't
                 * overflow for reading from pipe case.
                 *
                 *
                 * In this case the numbers of wchar_t characters that we can
                 * read is cnt/2. This means that the buffer size that we will
                 * require is cnt/2.
                 */

                // For UTF8 we want the count to be an even number
				if( !((cnt & 1) == 0) )
				{
					_set_doserrno( 0 );
					errno = EINVAL;
					return -1;
				}

                cnt = (cnt/2) < 4 ? 4 : (cnt/2);

                buf = malloc( cnt );

                if(!buf) 
				{
                    errno = ENOMEM;
                    _set_doserrno( CDOSError::E_nomem );
                    return -1;
                }
                m_i64StartPos = _lseeki64_nolock(fh, 0, FILE_CURRENT);
                break;

            case __IOINFO_TM_UTF16LE :
                // For UTF16 the count always needs to be an even number

				if( !((cnt & 1) == 0) )
				{
					_set_doserrno( 0 );
					errno = EINVAL;
					return -1;
				}

                cnt &= (~1);

                // Fall Through to default

            default :
                // For non-UTF8 files, we need only 1 buffer - make buf point to the users input buffer
                buf = inputbuf;
        }


        buffer = reinterpret_cast< char* >( buf );

        if( ( m_chFlags & ( FPIPE | FDEV ) ) && m_chPipe != LF && cnt != 0 ) 
		{
            // a pipe/device and pipe lookahead non-empty: read the lookahead char
            *buffer++ = m_chPipe;
            ++bytes_read;
            --cnt;
            m_chPipe = LF;           // mark as empty

            // For UTF16, there maybe one more look ahead char. For UTF8, there maybe 2 more look ahead chars
            if( ( tmode != __IOINFO_TM_ANSI) && ( m_achPipeBuffer[0] != LF) && cnt != 0 ) 
			{
                *buffer++ = m_achPipeBuffer[0];
                ++bytes_read;
                --cnt;
                m_achPipeBuffer[0] = LF;   // mark as empty

                if( ( tmode == __IOINFO_TM_UTF8 ) && ( m_achPipeBuffer[1] != LF ) && cnt != 0 ) 
				{
                    *buffer++ = m_achPipeBuffer[1];
                    ++bytes_read;
                    --cnt;
                    m_achPipeBuffer[1] = LF;   // mark as empty
                }
            }
        }


#if !defined(_CRT_APP) || defined(_KERNELX)

        if( _isatty(fh) && ( m_chFlags & FTEXT ) )
        {
            unsigned long dwMode;
			CTerminal* pTerminal = CWin32Application::TheWin32Application()->GetRole()->GetSubSystem( CTerminal::ClassID() ).As< CTerminal >();
			fromConsole = pTerminal->Console()->ScreenBuffer()->GetInputMode( dwMode );
        }

        // read the data from Console
        if( fromConsole && ( tmode == __IOINFO_TM_UTF16LE ) )
        {
			CTerminal* pTerminal = CWin32Application::TheWin32Application()->GetRole()->GetSubSystem( CTerminal::ClassID() ).As< CTerminal >();
			if( !pTerminal->Console()->ScreenBuffer()->Read( buffer, cnt / 2, reinterpret_cast< unsigned long* >( &os_read ), 0 ) )
            {
                CDOSError::MapError( m_ErrorHelper.GetLastError() );
                retval = -1;
                goto error_return;
            }

            os_read *= 2; // In UTF16 mode, ReadConsoleW returns the actual number of wchar_t's read,
                          // so we make sure we update os_read accordingly
        }
        // read the data
        else 
#endif  /* !defined(_CRT_APP) || defined(_KERNELX) */

		if ( !m_pFile->Read( buffer, cnt, reinterpret_cast< unsigned long* >( &os_read ), 0 ) || os_read < 0 || ( size_t )os_read > cnt )
		{
            /* ReadFile has reported an error. recognize two special cases.
             *
             *      1. map ERROR_ACCESS_DENIED to EBADF
             *
             *      2. just return 0 if ERROR_BROKEN_PIPE has occurred. it
             *         means the handle is a read-handle on a pipe for which
             *         all write-handles have been closed and all data has been
             *         read. */

            if( ( dosretval = m_ErrorHelper.GetLastError() ) == ErrorAccessDenied ) 
			{
                // wrong read/write mode should return EBADF, not EACCES
                errno = EBADF;
                _set_doserrno( dosretval );
                retval = -1;
                goto error_return;

            }
            else if( dosretval == ErrorBrokenPipe ) 
			{
                retval = 0;
                goto error_return;
            }
            else 
			{
				CDOSError::MapError( m_ErrorHelper.GetLastError() );
                retval = -1;
                goto error_return;
            }
        }

        bytes_read += os_read;          // update bytes read

        if( m_chFlags & FTEXT ) 
		{
            // now must translate CR-LFs to LFs in the buffer

            // For ANSI & UTF8, we read byte by byte. For UTF16, we need to read 2 bytes (wchar_t's) at a time
            if( tmode != __IOINFO_TM_UTF16LE ) 
			{
                // set CRLF flag to indicate LF at beginning of buffer
                if( ( os_read != 0 ) && ( *(char*)buf == LF ) )
				{
                    m_chFlags |= FCRLF;
				}
                else
				{
                    m_chFlags &= ~FCRLF;
				}

                // convert chars in the buffer: p is src, q is dest
                p = q =reinterpret_cast< char* >( buf );

                while( p < (char *)buf + bytes_read ) 
				{
                    if( *p == CTRLZ ) 
					{
                        // if fh is not a device, set ctrl-z flag
                        if( !( m_chFlags & FDEV) )
						{
                            m_chFlags |= FEOFLAG;
						}
                        else
						{
                            *q++ = *p++;
						}
                        break;              // stop translating
                    }
                    else if( *p != CR )
					{
                        *q++ = *p++;
					}
                    else 
					{
                        // *p is CR, so must check next char for LF 
                        if( p < (char *)buf + bytes_read - 1 ) 
						{
                            if( *( p + 1 ) == LF ) 
							{
                                p += 2;
                                *q++ = LF;  // convert CR-LF to LF
                            }
                            else
							{
                                *q++ = *p++;    // store char normally
							}
                        }
                        else 
						{
                            // This is the hard part.  We found a CR at end of buffer.  We must peek ahead to see if next char is an LF.
                            ++p;

                            dosretval = 0;
							if( ! m_pFile->Read( &peekchr, 1, reinterpret_cast< unsigned long* >( &os_read ), 0 ) )
							{
                                dosretval = m_ErrorHelper.GetLastError();
							}

                            if( dosretval != 0 || os_read == 0 ) 
							{
                                // couldn't read ahead, store CR
                                *q++ = CR;
                            }
                            else 
							{
                                /*
                                 * peekchr now has the extra character -- we now
                                 * have several possibilities:
                                 *
                                 * 1. disk file and char is not LF; just seek
                                 *    back and copy CR
                                 * 2. disk file and char is LF; seek back and
                                 *    discard CR
                                 * 3. disk file, char is LF but this is a
                                 *    one-byte read: store LF, don't seek back
                                 * 4. pipe/device and char is LF; store LF.
                                 * 5. pipe/device and char isn't LF, store CR
                                 *    and put char in pipe lookahead buffer.
                                 */
                                if( m_chFlags & ( FDEV | FPIPE ) ) 
								{
                                    // non-seekable device
                                    if( peekchr == LF )
									{
                                        *q++ = LF;
									}
                                    else 
									{
                                        *q++ = CR;
                                        m_chPipe = peekchr;
                                    }
                                }
                                else 
								{
                                    // disk file
                                    if( q == buf && peekchr == LF ) 
									{
                                        // nothing read yet; must make some progress
                                        *q++ = LF;
                                    }
                                    else 
									{
                                        // seek bac
                                        filepos = _lseeki64_nolock( fh, -1i64, FILE_CURRENT );
                                        if( peekchr != LF )
										{
                                            *q++ = CR;
										}
                                    }
                                }
                            }
                        }
                    }
                }


                //we now change bytes_read to reflect the true number of chars in the buffer
                bytes_read = (int)( q - (char*)buf );

                if( ( tmode == __IOINFO_TM_UTF8 ) && ( bytes_read != 0 ) ) 
				{
                    // UTF8 reads need to be converted into UTF16

                    --q; // q has gone beyond the last char

                    /* If the last byte is a standalone UTF-8 char. We then take the whole buffer. Otherwise we skip back till we come to a lead byte.
					If the leadbyte forms a complete UTF-8 character will the remaining part of the buffer, then again we take the whole buffer. 
					If not, we skip to one byte which should be the final trail byte of the previous UTF-8 char or a standalone UTF-8 character
                     */

                    if( _utf8_is_independent(*q) ) 
					{
                        ++q;
                        // Final byte is standalone, we reset q, because we will now consider the full buffer which we have read
                    }
                    else 
					{
                        int ctr = 1;
                        int cnt_trailbytes;

                        while( !_utf8_is_leadbyte( *q ) && ctr <= 4 && q >= (char *)buf ) 
						{
                            --q;
                            ++ctr;
                        }

                        cnt_trailbytes = _utf8_no_of_trailbytes(*q);

                        if( cnt_trailbytes == 0 ) 
						{
                            // Should have exited the while by finding a lead byte else, the file has incorrect UTF-8 chars
							errno = EILSEQ;
							retval = -1;
							goto error_return;
						}

                        if( cnt_trailbytes + 1 == ctr ) 
						{
                            //The leadbyte + the remaining bytes form a full set
                            q += ctr;
                        }
                        else 
						{
                            // Seek back

                            if( m_chFlags & ( FDEV | FPIPE ) ) 
							{
                                // non-seekable device. Put the extra chars in _pipech & _pipech2. We would have a maximum of 3 extra chars
                                m_chPipe = *q;
                                ++q;

                                if( ctr >= 2 ) 
								{
                                    m_achPipeBuffer[0] = *q;
                                    ++q;
                                }

                                if( ctr == 3 ) 
								{
                                    m_achPipeBuffer[1] = *q;
                                    ++q;
                                }

                                //We need to point q back to beyond whatever we actually took in.
                                q -= ctr;

                            }
                            else 
							{
                                // We have read extra chars, so we seek back
                                filepos = _lseeki64_nolock( fh, -ctr, FILE_CURRENT );
                            }
                        }
                    }

                    bytes_read = (int)(q - (char *)buf);
                    bytes_read = m_StringHelper.MultiByteToWideChar( CCodePage::UTF8, 0, reinterpret_cast< char* >( buf ), bytes_read, reinterpret_cast< wchar_t* >( inputbuf ), inputsize / 2 );

                    if( !bytes_read ) 
					{
						CDOSError::MapError( m_ErrorHelper.GetLastError() );
                        retval = -1;
                        goto error_return;
                    }

                    m_bUTF8Translations = (bytes_read != (int)(q - (char *)buf));

                    // MultiByteToWideChar returns no of wchar_t's. Double it
                    bytes_read = bytes_read*2;
                }
            }
#if !defined(_CRT_APP) || defined(_KERNELX)
            // reading from console && tmode == __IOINFO_TM_UTF16LE */
            else if( fromConsole ) 
			{
                pu = qu = (wchar_t *)buf;
                while( pu < ( (wchar_t*)buf ) + ( bytes_read / 2 ) ) 
				{
                    if( *pu == CTRLZ ) 
					{
                        m_chFlags |= FEOFLAG;
                        break;              // stop translating
                    }
                    else if (*pu != CR )
					{
                        *qu++ = *pu++;
					}
                    else 
					{
                        // *pu is CR, so must check next wchar_t for LF
                        if( pu < ( (wchar_t*)buf ) + ( bytes_read / 2 ) - 1 ) 
						{
                            if( *( pu + 1 ) == LF ) 
							{
                                pu++;
                                *qu++ = LF;  // convert CR-LF to LF
                            }
                            else
							{
                                *qu++ = *pu++;    // store char normally
							}
                        }
                    }
                }

                // we now change bytes_read to reflect the true number of bytes in the buffer
                bytes_read = (int)(qu - (wchar_t*)buf) * 2;
            }
#endif  /* _CRT_APP */
            // NOT reading from console and tmode == __IOINFO_TM_UTF16LE
            else 
			{
                // set CRLF flag to indicate LF at beginning of buffer
                if( ( os_read != 0 ) && ( *(wchar_t *)buf == LF ) )
				{
					m_chFlags |= FCRLF;
				}
                else
				{
                    m_chFlags &= ~FCRLF;
				}

                // convert chars in the buffer: pu is src, qu is dest
                pu = qu = (wchar_t *)buf;

                while( (char *)pu < (char *)buf + bytes_read ) 
				{
                    if( *pu == CTRLZ ) 
					{
                        // if fh is not a device, set ctrl-z flag
                        if( !( m_chFlags & FDEV) )
						{
                            m_chFlags |= FEOFLAG;
						}
                        else
						{
                            *qu++ = *pu++;
						}
                        break;              // stop translating
                    }
                    else if( *pu != CR )
					{
                        *qu++ = *pu++;
					}
                    else 
					{
                        // *pu is CR, so must check next wchar_t for LF
                        if( (char *)pu < (char *)buf + bytes_read - 2 ) 
						{
                            if( *( pu + 1 ) == LF ) 
							{
                                pu += 2;
                                *qu++ = LF;  // convert CR-LF to LF
                            }
                            else
							{
                                *qu++ = *pu++;    // store char normally
							}
                        }
                        else 
						{
                            // This is the hard part.  We found a CR at end of buffer.  We must peek ahead to see if next wchar_t is an LF
                            ++pu;

                            dosretval = 0;
							if( ! m_pFile->Read( &wpeekchr, 2, reinterpret_cast< unsigned long* >(&os_read), 0 ) )
							{
                                dosretval = m_ErrorHelper.GetLastError();
							}

                            if( dosretval != 0 || os_read == 0 ) 
							{
                                // couldn't read ahead, store CR
                                *qu++ = CR;
                            }
                            else 
							{
                                /* peekchr now has the extra character -- we
                                 * now have several possibilities:
                                 * 1. wchar_t is not LF; just seek back and
                                 * copy CR
                                 * 2. wchar_t is LF; seek back and discard CR
                                 * 3. disk file, wchar_t is LF but this is a
                                 * one-byte read: store LF, don't seek back.
                                 */

                                if( m_chFlags & ( FDEV | FPIPE ) ) 
								{
                                    // non-seekable device
                                    if( wpeekchr == LF )
									{
                                        *qu++ = LF;
									}
                                    else 
									{
                                        char * pwpeekchr = (char *)&wpeekchr;
                                        *qu++ = CR;
                                        m_chPipe = *pwpeekchr;
                                        ++pwpeekchr;
                                        m_achPipeBuffer[0] = *pwpeekchr;
                                        m_achPipeBuffer[1] = LF; // Mark as empty
                                    }
                                }
                                else 
								{
                                    if( (char*)qu == buf && wpeekchr == LF ) 
									{
                                        // nothing read yet; must make some progress
                                        *qu++ = LF;
                                    }
                                    else 
									{
                                        // seek back
                                        filepos = _lseeki64_nolock( fh, -2, FILE_CURRENT );
                                        if( wpeekchr != LF )
										{
                                            *qu++ = CR;
										}
                                    }
                                }
                            }
                        }
                    }
                }

                // we now change bytes_read to reflect the true number of chars in the buffer 
                bytes_read = (int)( (char*)qu - (char*)buf );

            }

        }

	error_return:

        if( buf != inputbuf ) 
		{
            free(buf);
        }

        return (retval == -2) ? bytes_read : retval ;
	}

	//------------------------------------------------------------------------------
	size_t CPosumStream::fread( void* ptr, size_t size, size_t nmemb )
	{
		 return fread_s( ptr, Size_Max, size, nmemb );
	}

	//------------------------------------------------------------------------------
	size_t CPosumStream::_fread_nolock( void *buffer, size_t elementSize, size_t count )
	{
		// assumes there is enough space in the destination buffer
		return _fread_nolock_s( buffer, Size_Max, elementSize, count );
	}

	//------------------------------------------------------------------------------
	size_t CPosumStream::fread_s( void* buffer, size_t bufferSize, size_t elementSize, size_t count )
	{
		size_t retval = 0;

		if( elementSize == 0 || count == 0)
		{
			return 0;
		}

		// only checking for stream == NULL here for _lock_str()
		// the rest of the validation is in _fread_nolock_s()
		if( this == NULL )
		{
			if( bufferSize != Size_Max )
			{
				memset( buffer, 0, bufferSize );
			}

			errno = EINVAL;
			return 0;
		}

		flockfile();
		__try
		{
			// do the read; _fread_nolock_s will make sure we do not buffer overrun 
			retval = _fread_nolock_s(buffer, bufferSize, elementSize, count );
		}
		__finally
		{
			funlockfile();
		}

		return retval;
	}

	//------------------------------------------------------------------------------
	size_t CPosumStream::_fread_nolock_s( void *buffer, size_t bufferSize, size_t elementSize, size_t num )
	{
		char* data;                     // point inside the destination buffer to where we need to copy the read chars
		size_t dataSize;                // space left in the destionation buffer (in bytes)
		size_t total;                   // total bytes to read
		size_t count;                   // num bytes left to read
		unsigned streambufsize;         // size of stream buffer
		unsigned nbytes;                // how much to read now
		unsigned nread;                 // how much we did read
		int c;                          // a temp char

	    // initialize local vars
		if( elementSize == 0 || num == 0 )
		{
			return 0;
		}

		if( buffer == NULL )
		{
			errno = EINVAL;
			return 0;
		}

		data = reinterpret_cast< char* >( buffer );
		dataSize = bufferSize;
		
		if( this == NULL || num > ( Size_Max / elementSize ) )
		{
			if( bufferSize != Size_Max )
			{
				memset( buffer, 0, bufferSize );
			}

			if( this == NULL )
			{
				errno = EINVAL;
				return 0;
			}
			
			if( num > ( Size_Max / elementSize ) )
			{
				errno = EINVAL;
				return 0;
			}
		}


		count = total = elementSize * num;

		if( IsAnyBuffer() )
		{
			// already has buffer, use its size
			streambufsize = _bufsiz;
		}
		else
		{
			// assume will get _INTERNAL_BUFSIZ buffer
			streambufsize = _INTERNAL_BUFSIZ;
		}

		// here is the main loop -- we go through here until we're done
		while( count != 0 ) 
		{
			// if the buffer exists and has characters, copy them to user buffer
			if( IsAnyBuffer() && _cnt != 0 )
			{
				if( _cnt < 0 )
				{
					//assert(("Inconsistent Stream Count. Flush between consecutive read and write", _cnt >= 0));
					_flag |= _IOERR;
					return ( total - count ) / elementSize;
				}

				// how much do we want?
				nbytes = ( count < (size_t)_cnt ) ? (unsigned)count : _cnt;
				if( nbytes > dataSize )
				{
					if( bufferSize != Size_Max )
					{
						memset( buffer, 0, bufferSize );
					}

					errno = ERANGE;
					return 0;
					//_VALIDATE_RETURN(("buffer too small", 0), ERANGE, 0)
				}

				memcpy_s( data, dataSize, _ptr, nbytes );

				// update stream and amt of data read 
				count -= nbytes;
				_cnt -= nbytes;
				_ptr += nbytes;
				data += nbytes;
				dataSize -= nbytes;
			}
			else if( count >= streambufsize )
			{
				// If we have more than streambufsize chars to read, get data by calling read with an integral number of bufsiz blocks.  Note that if the stream is text mode, read will return less chars than we ordered.

				if( streambufsize )
				{
					// In 64bit apps size_t is bigger than unsigned (which is 32bit even in 64 bit machines), so we need to split the read into INT_MAX chunks
					// since _read() only support up to _signed_ int (even though the in parameter is unsigned).
					
					if( count > INT_MAX )
					{
						// calc chars to read -- the largest multiple of streambufsize smaller then INT_MAX
						 
						nbytes = (unsigned)( INT_MAX - INT_MAX % streambufsize );
					}
					else
					{
						// calc chars to read -- (count/streambufsize) * streambufsize
						nbytes = (unsigned)( count - count % streambufsize );
					}
				}
				else
				{
					nbytes = (count > INT_MAX)?(unsigned)INT_MAX: (unsigned)count;
				}

				if( nbytes > dataSize )
				{
					if( bufferSize != Size_Max )
					{
						memset(buffer, 0, bufferSize );
					}
					
					errno = ERANGE;
					return 0;
					//_VALIDATE_RETURN(("buffer too small", 0), ERANGE, 0)
				}

				nread = _read_nolock( _fileno(), data, nbytes );
				if( nread == 0 ) 
				{
					// end of file -- out of here
					_flag |= _IOEOF;
					return ( total - count ) / elementSize;
				}
				else if( nread == (unsigned)-1 ) 
				{
					// error -- out of here
					_flag |= _IOERR;
					return ( total - count ) / elementSize;
				}

				// update count and data to reflect read 
				count -= nread;
				data += nread;
				dataSize -= nread;
			}
			else
			{
				// less than streambufsize chars to read, so call _filbuf to fill buffer
				if( ( c = _filbuf() ) == EOF ) 
				{
					// error or eof, stream flags set by _filbuf
					return ( total - count ) / elementSize;
				}

				// _filbuf returned a char -- store it
				if( dataSize == 0 )
				{
					if (bufferSize != Size_Max )
					{
						memset(buffer, 0, bufferSize );
					}

					errno = ERANGE;
					return 0;
					//_VALIDATE_RETURN(("buffer too small", 0), ERANGE, 0)
				}

				*data++ = (char) c;
				--count;
				--dataSize;

				// update buffer size
				streambufsize = _bufsiz;
			}
		}

		// we finished successfully, so just return num
		return num;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_filbuf()
	{
		if( this == NULL )
		{
			errno = EINVAL;
			return EOF;
		}

        if( ! IsInUse() || _flag & _IOSTRG )
		{
			return EOF;
		}

        if( _flag & _IOWRT )
        {
            _flag |= _IOERR;
            return EOF;
        }

        _flag |= _IOREAD;

        // Get a buffer, if necessary.

        if( !IsAnyBuffer() )
        {
            _getbuf();
        }
        else
        {
            _ptr = _base;
        }

        _cnt = _read( _fileno(), _base, _bufsiz );

        if( ( _cnt == 0 ) || ( _cnt == -1 ) ) 
		{
            _flag |= _cnt ? _IOERR : _IOEOF;
            _cnt = 0;
            return EOF;
        }

        if( !( _flag & ( _IOWRT | _IORW ) ) && ( ( _fileno() & ( FTEXT | FEOFLAG ) ) == ( FTEXT | FEOFLAG ) ) )
        {
            _flag |= _IOCTRLZ;
        }

        // Check for small _bufsiz (_SMALL_BUFSIZ). If it is small and if it is our buffer, then this must be the first _filbuf after
        // an fseek on a read-access-only stream. Restore _bufsiz to its larger value (_INTERNAL_BUFSIZ) so that the next _filbuf call,
        //  if one is made, will fill the whole buffer.

        if( ( _bufsiz == _SMALL_BUFSIZ ) && ( _flag & _IOMYBUF ) && !( _flag & _IOSETVBUF ) )
        {
            _bufsiz = _INTERNAL_BUFSIZ;
        }

        _cnt--;
        return( 0xff & *_ptr++ );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_read( int fh, void* buf, unsigned cnt )
	{
        int r = 0;

        //_CHECK_FH_CLEAR_OSSERR_RETURN( fh, EBADF, -1 );
        //_VALIDATE_CLEAR_OSSERR_RETURN((fh >= 0 && (unsigned)fh < (unsigned)_nhandle), EBADF, -1);

		if( !( m_chFlags & FOPEN ))
		{
			errno = EBADF;
			return -1;
		}

		flockfile();

        __try 
		{
            if ( m_chFlags & FOPEN )
			{
                r = _read_nolock(fh, buf, cnt); // read bytes
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
	size_t CPosumStream::fwrite( const void* buffer, size_t size, size_t count )
	{
		size_t retval = 0;

		if( size == 0 || count == 0 )
		{
			return 0;
		}

		if( this == 0 )
		{
			errno = EINVAL;
			return 0;
		}

		flockfile();

		__try 
		{
			retval = _fwrite_nolock( buffer, size, count );
		}
		__finally 
		{
			funlockfile();
		}

		return retval;
	}

	//------------------------------------------------------------------------------
	size_t CPosumStream::_fwrite_nolock( const void* buffer, size_t size, size_t num )
	{
        const char* data;               // point to where data comes from next
        size_t total;                   // total bytes to write
        size_t count;                   // num bytes left to write
        unsigned bufsize;               // size of stream buffer 
        unsigned nbytes;                // number of bytes to write now
        unsigned nactuallywritten;      // number of bytes actually written by write() call
        unsigned nwritten;              // number of bytes we consider written 
        int c;                          // a temp char 

        if( size == 0 || num == 0 )
		{
            return 0;
		}

		if( this == 0 )
		{
			errno = EINVAL;
			return 0;
		}
        
		if( buffer == 0 )
		{
			errno = EINVAL;
			return 0;
		}

        if( num > ( Size_Max / size ) )
		{
			errno = EINVAL;
			return 0;
		}

        data = reinterpret_cast< const char* >( buffer );
        count = total = size * num;

        if( IsAnyBuffer() )	// already has buffer, use its size
		{
			bufsize = _bufsiz;
		}
        else
		{					// assume will get _INTERNAL_BUFSIZ buffer
			bufsize = _INTERNAL_BUFSIZ;
		}

        // here is the main loop -- we go through here until we're done
        while (count != 0) 
		{
            // if the buffer is big and has room, copy data to buffer
            if( IsBigBuffer() && _cnt != 0 ) 
			{     
				if( _cnt < 0 ) 
				{
                    assert(("Inconsistent Stream Count. Flush between consecutive read and write", _cnt >= 0));
                    _flag |= _IOERR;
                    return (total - count) / size;
                }

                // how much do we want?
                nbytes = ( count < (unsigned)_cnt) ? (unsigned)count : _cnt;
                memcpy( _ptr, data, nbytes );

                // update stream and amount of data written
                count -= nbytes;
                _cnt -= nbytes;
                _ptr += nbytes;
                data += nbytes;
            }
            else if( count >= bufsize ) 
			{
                /* If we have more than bufsize chars to write, write
                    data by calling write with an integral number of
                    bufsiz blocks.  If we reach here and we have a big
                    buffer, it must be full so _flush it. */

                if( IsBigBuffer() ) 
				{
                    if( _flush() ) 
					{
                        // error, stream flags set -- we're outof here
                        return ( total - count ) / size;
                    }
                }

                // calc chars to read -- (count/bufsize) * bufsize
                nbytes = ( bufsize ? (unsigned)(count - count % bufsize) : (unsigned)count );

                nactuallywritten = _write( _fileno(), data, nbytes);
                    
				if( nactuallywritten == (unsigned)EOF) 
				{
                    // error -- out of here
                    _flag |= _IOERR;
                    return (total - count) / size;
                }

                /* VSWhidbey#326224 - _write can return more bytes than we requested due unicode involved conversions in text files.
                    But we do not care about how many bytes were written as long as the number is at least as big as we wanted.
                */
                nwritten = (nactuallywritten > nbytes ? nbytes : nactuallywritten);

                // update count and data to reflect write

                count -= nwritten;
                data += nwritten;

                if( nactuallywritten < nbytes ) 
				{
                    // error -- out of here
                    _flag |= _IOERR;
                    return (total - count) / size;
                }
            }
            else 
			{
                // buffer full and not enough chars to do direct write, so do a _flsbuf. 
                c = *data;  // _flsbuf write one char, this is it
                if( _flsbuf( c ) == EOF ) 
				{
					// error or eof, stream flags set by _flsbuf
					return (total - count) / size;
                }

                // _flsbuf wrote a char -- update count
                ++data;
                --count;

                // update buffer size */
                bufsize = _bufsiz > 0 ? _bufsiz : 1;
            }
        }

        // we finished successfully, so just return num
        return num;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_flsbuf( int ch )
	{
        int charcount;
        int written;
        int fh;

		assert( this != NULL );

        fh = _fileno();

        if( !( _flag & (_IOWRT|_IORW) ) ) 
		{
			errno = EBADF;
			_flag |= _IOERR;
			return( EOF );
        } 
		else if( ( _flag & _IOSTRG ) ) 
		{
			errno = ERANGE;
			_flag |= _IOERR;
			return( EOF );
        }

        /* Check that _IOREAD is not set or, if it is, then so is _IOEOF. Note that _IOREAD and IOEOF both being set implies switching from read to
           write at end-of-file, which is allowed by ANSI. Note that resetting the _cnt and _ptr fields amounts to doing an fflush() on the stream
           in this case. Note also that the _cnt field has to be reset to 0 for the error path as well (i.e., _IOREAD set but _IOEOF not set) as
           well as the non-error path. */

        if( _flag & _IOREAD ) 
		{
			_cnt = 0;
			if( _flag & _IOEOF ) 
			{
				_ptr = _base;
				_flag &= ~_IOREAD;
			}
			else 
			{
				_flag |= _IOERR;
				return( EOF );
			}
        }

		_flag |= _IOWRT;
		_flag &= ~_IOEOF;
        written = charcount = _cnt = 0;

        // Get a buffer for this stream, if necessary.
        if( !IsAnyBuffer() ) 
		{
			/* Do NOT get a buffer if (1) stream is stdout/stderr, and
            (2) stream is NOT a tty. [If stdout/stderr is a tty, we do NOT set up single char buffering. This is so that later temporary buffering will not be thwarted by the _IONBF bit being set (see _stbuf/_ftbuf usage).]
			*/
			if( !( ( ( this == stdout ) || ( this == stderr ) ) && ( _isatty(fh) ) ) )
			{
				_getbuf();
			}

        }

        // If big buffer is assigned to stream...
        if( IsBigBuffer() ) 
		{
			//assert( ("inconsistent IOB fields", _ptr - _base >= 0 ) );

			charcount = (int)( _ptr - _base );
			_ptr = _base + sizeof( char );
			_cnt = _bufsiz - (int)sizeof( char );

			if( charcount > 0 )
			{
				written = _write( fh, _base, charcount );
			}
			else
			{
				if( m_chFlags & FAPPEND )
				{
					if( _lseeki64( fh, 0L, SEEK_END ) == -1 )
					{
						_flag |= _IOERR;
						return( EOF );
					}
				}
			}
			*_base = (char)ch;
        }
        else 		// Perform single character output (either _IONBF or no buffering)
		{
			charcount = sizeof(char);
			written = _write( fh, &ch, charcount );
        }

        // See if the _write() was successful.
        if( written != charcount ) 
		{
			_flag |= _IOERR;
			return( EOF );
        }

        return( ch & 0xff );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_write( int fh, const void* buf, unsigned cnt )
	{
        int r = 0;                      // return value

        // validate handle
		if( fh == _NO_CONSOLE_FILENO )
		{
			_set_doserrno( 0 );
			errno = EBADF;
			return -1;
		}

        int _Expr_val = !!((fh >= 0 ));//&& (unsigned)fh < (unsigned)_nhandle));
        assert( ( _Expr_val ) );//, _WTXT("(fh >= 0 && (unsigned)fh < (unsigned)_nhandle)") );
        if( !( _Expr_val ) )
        {
            _set_doserrno( 0 );
            errno = EBADF;
			//TODO: Raise invalid parameter error
            return -1;
        }

        //_VALIDATE_CLEAR_OSSERR_RETURN((_osfile(fh) & FOPEN), EBADF, -1);

        flockfile();

        __try 
		{
            if( m_chFlags & FOPEN )
			{
				r = _write_nolock(fh, buf, cnt);    // write bytes
			}
            else
			{
				errno = EBADF;
				_set_doserrno( 0 );  // not o.s. error
				r = -1;
				//_ASSERTE(("Invalid file descriptor. File possibly closed by a different thread",0));
            }
        }
        __finally 
		{
			funlockfile();
        }

        return r;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_write_nolock ( int fh, const void* buf, unsigned cnt )
	{
        int lfcount = 0;								// count of line feeds
        int charcount = 0;								// count of chars written so far
        int written;									// count of chars written on this write
        unsigned long dosretval = 0;					// o.s. return value
        char tmode ;									// textmode - ANSI or UTF-16
#if !defined(_CRT_APP) || defined(_KERNELX)
        bool toConsole = false;							// true when writing to console
        bool isCLocale = false;							// true when locale handle is C locale
#endif  /* !defined(_CRT_APP) || defined(_KERNELX) */

        if( cnt == 0 )
		{
			return 0;							// nothing to do
		}

		assert( buf != NULL );
        if( buf == NULL )
        {
            _set_doserrno( 0 );
            errno = EINVAL;
			//TODO: Raise Invalid parameter error
            return -1;
        }

        tmode = m_chTextMode;

        if( tmode == __IOINFO_TM_UTF16LE || tmode == __IOINFO_TM_UTF8 )
        {
            // For a UTF-16 file, the count must always be an even number
			assert( ( cnt & 1 ) == 0 );
			if( ( cnt & 1 ) != 0 )
			{
				_set_doserrno( 0 );
				errno = EINVAL;
				//TODO: Raiseinvalid parameter error
				return -1;
			}
        }

        if( m_chFlags & FAPPEND ) 
		{
            // appending - seek to end of file; ignore error, because maybe file doesn't allow seeking
            (void)_lseeki64_nolock( fh, 0, FILE_END );
        }

        // check for text mode with LF's in the buffer

        /* Note that in case the handle belongs to Console, write file will generate garbage output. For user to print these characters correctly, we will need to print ANSI.
         * Also note that in case of printing to Console, we still have to convert the characters to console codepage. */

#if !defined(_CRT_APP) || defined(_KERNELX)
        if( _isatty(fh) && ( m_chFlags & FTEXT ) )
        {
            unsigned long dwMode = 0;
            //_ptiddata ptd = _getptd();
			
            //isCLocale = (ptd->ptlocinfo->locale_name[LC_CTYPE] == NULL);

			isCLocale = ( GetCurrentWin32Thread()->LocaleInfoPtr()->Category( CLocale::LCCTYPE ).CatLocale() == NULL ) ? true : false;
			
			CTerminal* pTerminal = CWin32Application::TheWin32Application()->GetRole()->GetSubSystem( CTerminal::ClassID() ).As< CTerminal >();
            toConsole = pTerminal->Console()->ScreenBuffer()->GetInputMode( dwMode );
        }

        // don't need double conversion if it's ANSI mode C locale
        if( toConsole && !( isCLocale && ( tmode == __IOINFO_TM_ANSI ) ) ) 
		{			
			CTerminal* pTerminal = CWin32Application::TheWin32Application()->GetRole()->GetSubSystem( CTerminal::ClassID() ).As< CTerminal >();
            unsigned int consoleCP = pTerminal->Console()->OutputCodePage().ID();
            char mboutbuf[ MBLenMax ];
            wchar_t tmpchar = 0;
            int size = 0;
            int written = 0;
            char *pch;

            for (pch = (char *)buf; (unsigned)(pch - (char *)buf) < cnt; ) 
			{
                int bCR = 0;

                if( tmode == __IOINFO_TM_ANSI ) 
				{
                    bCR = *pch == LF;
                    // Here we need to do double convert. i.e. convert from multibyte to unicode and then from unicode to multibyte in Console codepage.
                    // Here, we have take into account that _write() might be called byte by byte, so when we see a lead byte without a trail byte, we have to store it and return no error.
                     
                    if( m_dbcsBufferUsed ) 
					{
                        // we got something buffered, join it with the lead byte and convert
                        assert( isleadbyte( m_dbcsBuffer ) );
                        mboutbuf[ 0 ] = m_dbcsBuffer;
                        mboutbuf[ 1 ] = *pch;
                        // reseting the flag
                        m_dbcsBufferUsed = 0;

                        if( mbtowc( &tmpchar, mboutbuf, 2 ) == -1 ) 
						{
                            break;
                        }
                    } 
					else 
					{
                        if (isleadbyte(*pch)) 
						{
                            if ((cnt - (pch - (char*)buf)) > 1) 
							{
                                // and we have more bytes to read, just convert
                                if( mbtowc( &tmpchar, pch, 2 ) == -1 ) 
								{
                                    break;
                                }
                                // Increment pch to accomodate DBCS character.
                                ++pch;
                            } 
							else 
							{
                                // and we ran out of bytes to read, buffer the lead byte
                                m_dbcsBuffer = *pch;
                                m_dbcsBufferUsed = 1;

                                // lying that we actually wrote the last character, so it doesn't error
                                charcount++;
                                break;
                            }
                        } 
						else 
						{
                            // single char conversion
                            if( mbtowc( &tmpchar, pch, 1 ) == -1 ) 
							{
                                break;
                            }
                        }
                    }
                    ++pch;
                } 
				else if( tmode == __IOINFO_TM_UTF8 || tmode == __IOINFO_TM_UTF16LE ) 
				{
                    //Note that bCR set above is not valid in case of UNICODE stream. We need to set it using unicode character.
                    tmpchar = *(wchar_t *)pch;
                    bCR = tmpchar == LF;
                    pch += 2;
                }

                if( tmode == __IOINFO_TM_ANSI )
                {
                    if( ( size = m_StringHelper.WideCharToMultiByte( consoleCP, 0, &tmpchar, 1, mboutbuf, sizeof(mboutbuf), NULL, NULL ) ) == 0 ) 
					{
                        break;
                    } 
					else 
					{
						if( m_pFile->Write( mboutbuf, size, reinterpret_cast< unsigned long* >( &written ), 0 ) )
						{
                            /* When we are converting, some convertion can result in 2 mbcs char -> 1 wchar -> 1 mbcs
                             * (ie. printing out Japanese characters in English ConsoleCP,
                             * the Japanese char will be converted to a single question mark)
                             * Therefore, we want to use how many bytes we converted + lfcount
                             * instead of how many bytes we actually wrote
                             */
                            charcount = lfcount + (int)(pch - (char*) buf);
                            if( written < size )
							{
                                break;
							}
                        } 
						else 
						{
                            dosretval = m_ErrorHelper.GetLastError();
                            break;
                        }
                    }

                    if( bCR ) 
					{
                        size = 1;
                        mboutbuf[ 0 ] = CR;
						if( m_pFile->Write( mboutbuf, size, reinterpret_cast< unsigned long* >( &written ), 0 ) )
						{
                            if( written < size )
							{
                                break;
							}
                            lfcount ++;
                            charcount++;
                        } 
						else 
						{
                            dosretval = m_ErrorHelper.GetLastError();
                            break;
                        }
                    }
                }
                else if( tmode == __IOINFO_TM_UTF8 || tmode == __IOINFO_TM_UTF16LE )
                {
                    if( _putwch_nolock( tmpchar ) == tmpchar )
                    {
                        charcount+=2;
                    }
                    else
                    {
                        dosretval = m_ErrorHelper.GetLastError();
                        break;
                    }

                    if( bCR ) // emit carriage return
                    {
                        size = 1;
                        tmpchar = CR;
                        if( _putwch_nolock( tmpchar ) == tmpchar )
                        {
                            charcount++;
                            lfcount++;
                        }
                        else
                        {
                            dosretval = m_ErrorHelper.GetLastError();
                            break;
                        }
                    }
                }
            }
        } else 
#endif  // !defined(_CRT_APP) || defined(_KERNELX)
        if( m_chFlags & FTEXT ) 
		{
            // text mode, translate LF's to CR/LF's on output

            dosretval = 0;          // no OS error yet

            if( tmode == __IOINFO_TM_ANSI ) 
			{
                char ch;                    // current character
                char* p = NULL, *q = NULL;  // pointers into buf and lfbuf resp.
                char lfbuf[ BUF_SIZE ];
                p = (char *)buf;        // start at beginning of buffer
                while( (unsigned)(p - (char *)buf) < cnt ) 
				{
                    q = lfbuf;      // start at beginning of lfbuf 

                    // fill the lf buf, except maybe last char
                    while( q - lfbuf < sizeof(lfbuf) - 1 && (unsigned)(p - (char *)buf ) < cnt ) 
					{
                        ch = *p++;
                        if( ch == LF ) 
						{
                            ++lfcount;
                            *q++ = CR;
                        }
                        *q++ = ch;
                    }

                    // write the lf buf and update total
					if( m_pFile->Write( lfbuf, (int)(q - lfbuf), reinterpret_cast< unsigned long* >( &written ), 0 ) )
                    {
                        charcount += written;
                        if (written < q - lfbuf)
                            break;
                    }
                    else 
					{
                        dosretval = m_ErrorHelper.GetLastError();
                        break;
                    }
                }
            } 
			else if ( tmode == __IOINFO_TM_UTF16LE )
			{
                char lfbuf[ BUF_SIZE ];
                wchar_t wch;            // current wide char
                wchar_t *pu = (wchar_t *)buf;
                wchar_t *qu = NULL;

                while( (unsigned)((char *)pu - (char *)buf) < cnt ) 
				{
                    qu = (wchar_t *)lfbuf; // start at beginning of lfbuf

                    // fill the lf buf, except maybe last wchar_t
                    while( ( ( (char *)qu - lfbuf ) < ( sizeof( lfbuf ) - 2 ) ) && ( (unsigned)((char *)pu - (char *)buf ) < cnt ) ) 
					{
                        wch = *pu++;
                        if( wch == LF ) 
						{
                            lfcount+=2;
                            *qu++ = CR;
                        }
                        *qu++ = wch;
                    }

                    // write the lf buf and update total
					if( m_pFile->Write( lfbuf, (int)((char*)qu - lfbuf), reinterpret_cast< unsigned long* >(&written), 0 ) )
                    {
                        charcount += written;
                        if (written < ((char *)qu - lfbuf))
                            break;
                    }
                    else 
					{
                        dosretval = m_ErrorHelper.GetLastError();
                        break;
                    }
                }
            } 
			else 
			{
                // Let's divide the lfbuf in 1:2 wher 1 is for storing widecharacters and 2 if for converting it to UTF8.  
				// This takes into account the worst case scenario where all the UTF8 characters are 4 byte long.
                char utf8_buf[ (BUF_SIZE*2) / 3 ];
                wchar_t utf16_buf[ BUF_SIZE / 6 ];

                wchar_t wch;            // current wide char
                wchar_t *pu = (wchar_t *)buf;
                wchar_t *qu = NULL;

                pu = (wchar_t *)buf;
                while( (unsigned)((char *)pu - (char *)buf) < cnt ) 
				{
                    int bytes_converted = 0;
                    qu = utf16_buf; // start at beginning of lfbuf

                    while( ( ( (char *)qu - (char *)utf16_buf ) < (sizeof(utf16_buf) - 2 ) ) && ( (unsigned)( (char *)pu - (char *)buf ) < cnt ) ) 
					{
                        wch = *pu++;
                        if( wch == LF ) 
						{
                            // no need to count the linefeeds here: we calculate the written chars in another way
                            *qu++ = CR;
                        }
                        *qu++ = wch;
                    }

					bytes_converted = m_StringHelper.WideCharToMultiByte( CCodePage::UTF8, 0, utf16_buf, ((int)((char *)qu - (char *)utf16_buf))/2, utf8_buf, sizeof(utf8_buf), 0, 0 );

                    if( bytes_converted == 0 ) 
					{
                        dosretval = m_ErrorHelper.GetLastError();
                        break;
                    } 
					else 
					{
                        // Here we need to make every attempt to write all the converted characters. 
						//The resaon behind this is incase half the bytes of a UTF8 character is written, it may currupt whole of the stream or file.
                        // The loop below will make sure we exit only if all the bytes converted are written (which makes sure no partial MBCS is written) or there was some error in the stream.
                        int bytes_written = 0;
                        do
						{
							if( m_pFile->Write( utf8_buf + bytes_written, bytes_converted - bytes_written, reinterpret_cast< unsigned long* >( &written ), 0 ) )
							{
                                bytes_written += written;
                            } 
							else 
							{
                                dosretval = m_ErrorHelper.GetLastError();
                                break;
                            }
                        }while ( bytes_converted > bytes_written);

                        // Only way the condition below could be true is if there was en error. 
						//In case of error we need to break this loop as well.

                        if( bytes_converted > bytes_written ) 
						{
                            break;
                        }
                        // if this chunk has been committed successfully, update charcount
                        charcount = (int)((char *)pu - (char *)buf);
                    }
                }
            }
        }
        else 
		{
            // binary mode, no translation
			if( m_pFile->Write( buf, cnt, reinterpret_cast< unsigned long* >( &written ), 0 ) )
            {
				dosretval = 0;
				charcount = written;
            }
            else
			{
				dosretval = m_ErrorHelper.GetLastError();
			}
        }

        if( charcount == 0 ) 
		{
			// If nothing was written, first check if an o.s. error, otherwise we return -1 and set errno to ENOSPC, unless a device and first char was CTRL-Z
			if( dosretval != 0 ) 
			{
                // o.s. error happened, map error
                if( dosretval == ErrorAccessDenied ) 
				{
                    // wrong read/write mode should return EBADF, not EACCES
					errno = EBADF;
					_set_doserrno( dosretval );
                }
                else
				{
					CDOSError::MapError( m_ErrorHelper.GetLastError() );
				}
                return -1;
			}
			else if( ( m_chFlags & FDEV ) && *(char *)buf == CTRLZ )
			{
				return 0;
			}
			else 
			{
				errno = ENOSPC;
				_set_doserrno( 0 );  // no o.s. error
				return -1;
			}
        }
        else
		{
			// return adjusted bytes written
			return charcount - lfcount;
		}
	}

}//nsWin32

