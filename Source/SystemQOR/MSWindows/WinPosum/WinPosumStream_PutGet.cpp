
#include "WinPosum/WinPosumStream.h"
#include "WinPosum/WinPosumStreamImpl.h"
#include "WinQL/Application/WinQLApplication.h"
#include <errno.h>

//------------------------------------------------------------------------------
namespace nsWin32
{
	//------------------------------------------------------------------------------
	int CPosumStream::_fgetc_nolock()
	{
		return (--_cnt >= 0 ? 0xff & *_ptr++ : _filbuf() );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_fputc_nolock( int _c )
	{
		return ( --_cnt >= 0 ? 0xff & (*_ptr++ = (char)(_c) ) :  _flsbuf( _c ) );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_getc_nolock()
	{
		return _fgetc_nolock();
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_putc_nolock( int _c )
	{
		return _fputc_nolock( _c );
	}

	//------------------------------------------------------------------------------

//#define _getchar_nolock()           _getc_nolock(stdin)
//#define _putchar_nolock(_c)         _putc_nolock((_c),stdout)
//#define _getwchar_nolock()          _getwc_nolock(stdin)
//#define _putwchar_nolock(_c)        _putwc_nolock((_c),stdout)

	//------------------------------------------------------------------------------
	int CPosumStream::fgetc( void )
	{
		int retval = 0;

		if( this == NULL )
		{
			errno = EINVAL;
			return EOF;
		}
	
		flockfile();
		__try 
		{
			int fn;
			
			if( !( ( _flag & _IOSTRG ) || ( fn = _fileno(), ( ( m_chTextMode == __IOINFO_TM_ANSI ) && !m_bchUnicode ) ) ) )
			{
				errno = EINVAL;
				retval= EOF;
			}

			if(retval==0)
			{
				retval = _getc_nolock();
			}
		}
		__finally 
		{
			funlockfile();
		}

		return(retval);
	}

	//------------------------------------------------------------------------------
	char* CPosumStream::fgets( char* string, int count )
	{
		char* pointer = string;
		char* retval = string;
		int ch;

		if( this == NULL || string == NULL || count <= 0 )
		{
			errno = EINVAL;
			return NULL;
		}

	    // The C Standard states the input buffer should remain unchanged if EOF is encountered immediately. Hence we do not blank out the input buffer here

		flockfile();
		__try 
		{
			int fn;
			
			if( !( ( _flag & _IOSTRG ) || ( fn = _fileno(), ( ( m_chTextMode == __IOINFO_TM_ANSI ) && !m_bchUnicode ) ) ) )
			{
				errno = EINVAL;
				retval = NULL;
			}

			if( retval != NULL )
			{
				while( --count )
				{
					if( ( ch = _fgetc_nolock() ) == EOF )
					{
						if( pointer == string ) 
						{
							retval=NULL;
							goto done;
						}

						break;
					}

					if( ( *pointer++ = (char)ch ) == '\n' )
					{
						break;
					}
				}

				*pointer = '\0';
			}

done: ;
		}
		__finally 
		{
			funlockfile();
		}

		return retval;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::fputc( int ch )
	{
		int retval=0;

		if( this == NULL )
		{
			errno = EINVAL;
			return EOF;
		}

		flockfile();
		__try 
		{

			int fn;
			
			if( !( ( _flag & _IOSTRG ) || ( fn = _fileno(), ( ( m_chTextMode == __IOINFO_TM_ANSI ) && !m_bchUnicode ) ) ) )
			{
				errno = EINVAL;
				retval = EOF;
			}

			if( retval == 0 )
			{
				retval = _putc_nolock( ch );
			}
		}
		__finally 
		{
			funlockfile();
		}

		return(retval);

	}

	//------------------------------------------------------------------------------
	int CPosumStream::fputs( const char* string)
	{
		int buffing;
		size_t length;
		size_t ndone = 0;

		if( string == NULL || this == NULL )
		{
			errno = EINVAL;
			return EOF;
		}

		int fn;

		if( !( ( _flag & _IOSTRG ) || ( fn = _fileno(), ( ( m_chTextMode == __IOINFO_TM_ANSI ) && !m_bchUnicode ) ) ) )
		{
			errno = EINVAL;
			return EOF;
		}

		length = strlen(string);

		flockfile();

		__try 
		{
			buffing = _stbuf();
			ndone = _fwrite_nolock( string, 1, length );
			_ftbuf( buffing );
		}
		__finally 
		{
			funlockfile();
		}

		return(ndone == length ? 0 : EOF);
	}

	//------------------------------------------------------------------------------
	int CPosumStream::getc( void )
	{
		int retval=0;

		if( this == NULL )
		{
			errno = EINVAL;
			return EOF;
		}

		flockfile();

		__try 
		{
			int fn;

			if( !( ( _flag & _IOSTRG ) || ( fn = _fileno(), ( ( m_chTextMode == __IOINFO_TM_ANSI ) && !m_bchUnicode ) ) ) )
			{
				errno = EINVAL;
				retval = EOF;
			}

			if( retval == 0 )
			{
				retval = _getc_nolock();
			}
		}
		__finally 
		{
			funlockfile();
		}

		return retval;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::getc_unlocked( void )
	{
		return _getc_nolock();
	}

	//------------------------------------------------------------------------------
	ssize_t CPosumStream::getdelim( char**, size_t*, int )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	ssize_t CPosumStream::getline( char**, size_t* )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::putc( int ch )
	{
		int retval=0;

		if( this == NULL )
		{
			errno = EINVAL;
			return EOF;
		}

		flockfile();

		__try 
		{
			int fn;

			if( !( ( _flag & _IOSTRG ) || ( fn = _fileno(), ( ( m_chTextMode == __IOINFO_TM_ANSI ) && !m_bchUnicode ) ) ) )
			{
				errno = EINVAL;
				retval = EOF;
			}

			if (retval==0)
			{
				retval = _putc_nolock( ch );
			}
		}
		__finally 
		{
			funlockfile();
		}

		return(retval);

	}

	//------------------------------------------------------------------------------
	int CPosumStream::putc_unlocked( int c )
	{
		return _putc_nolock( c );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::ungetc( int ch )
	{
        int retval = 0;

		if( this == NULL )
		{
			errno = EINVAL;
			return EOF;
		}

		flockfile();
        
		__try 
		{
			retval = _ungetc_nolock( ch );
        }
        __finally
		{
			funlockfile();
        }

        return retval;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_ungetc_nolock( int ch )
	{
		int fn;

		if( !( ( _flag & _IOSTRG ) || ( fn = _fileno(), ( ( m_chTextMode == __IOINFO_TM_ANSI ) && !m_bchUnicode ) ) ) )
		{
			errno = EINVAL;
			return EOF;
		}

        // Stream must be open for read and can NOT be currently in write mode. Also, ungetc() character cannot be EOF.

        if( ( ch == EOF) || !( ( _flag & _IOREAD ) || ( ( _flag & _IORW ) && !( _flag & _IOWRT ) ) ) )
		{
			return EOF;
		}

        // If stream is unbuffered, get one.
        if( _base == NULL )
        {
            _getbuf();
        }

        // now we know _base != NULL; since file must be buffered

        if( _ptr == _base ) 
		{
			if( _cnt )
			{ // my back is against the wall; i've already done ungetc, and there's no room for this one 
				return EOF;
			}

			_ptr++;
        }

        if( _flag & _IOSTRG ) 
		{
			// If stream opened by sscanf do not modify buffer
			if( *--_ptr != (char)ch ) 
			{
				++_ptr;
				return EOF;
			}
        } 
		else
		{
			*--_ptr = (char)ch;
		}

        _cnt++;
        _flag &= ~_IOEOF;
        _flag |= _IOREAD;       // may already be set

        return( 0xff & ch );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_putw( int binint )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_getw( void )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	wint_t CPosumStream::fgetwc()
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	wchar_t* CPosumStream::fgetws( wchar_t* s, int n )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	wint_t CPosumStream::fputwc( wchar_t c )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::fputws( const wchar_t* s )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	wint_t CPosumStream::getwc()
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	wint_t CPosumStream::putwc( wchar_t c )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	wint_t CPosumStream::ungetwc( wint_t c )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	wint_t CPosumStream::_putwch_nolock( wchar_t ch )
	{
		unsigned long cchWritten = 0;

		// write character to console file handle

		if( !CWin32Application::TheWin32Application()->Console()->ScreenBuffer()->Write( &ch, 1, &cchWritten ) )
		{
			return WEOF;
		}

		return ch;
	}

}//nsWin32

