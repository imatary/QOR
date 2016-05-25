
#include "WinPosum/WinPosumStream.h"
#include "WinPosum/WinPosumStreamImpl.h"
#include <errno.h>

//------------------------------------------------------------------------------
namespace nsWin32
{
	//------------------------------------------------------------------------------
	int __cdecl _winput_l( CPosumStream* _File, const wchar_t*, _locale_t _Locale, va_list _ArgList )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int __cdecl _input_s_l( CPosumStream* _File, const unsigned char*, _locale_t _Locale, va_list _ArgList )
	{
		return 0;
	}

	//--------------------------------------------------------------------------------
	int __cdecl _winput_s_l( CPosumStream* _File, const wchar_t*, _locale_t _Locale, va_list _ArgList )
	{
		return 0;
	}

	//--------------------------------------------------------------------------------
	int __cdecl _woutput ( const wchar_t* format, va_list argptr )
	{
		return 0;//OutputW( format, 0, false, false, argptr );
	}

	//--------------------------------------------------------------------------------
	int __cdecl _woutput_l ( CPosumStream* pStream, const wchar_t* format, localeinfo_struct* plocinfo, va_list argptr )
	{
		return 0;//OutputW( format, plocinfo, false, false, argptr );
	}

	//--------------------------------------------------------------------------------
	int __cdecl _woutput_p ( CPosumStream* pStream, const wchar_t* format, va_list argptr )
	{
		return 0;//OutputW( format, 0, false, true, argptr );
	}

	//--------------------------------------------------------------------------------
	int __cdecl _woutput_p_l ( CPosumStream* pStream, const wchar_t* format, localeinfo_struct* plocinfo, va_list argptr )
	{
		return 0;//OutputW( format, plocinfo, false, true, argptr );
	}

	//--------------------------------------------------------------------------------
	int __cdecl _woutput_s ( CPosumStream* pStream, const wchar_t* format, va_list argptr )
	{
		return 0;//OutputW( format, 0, true, false, argptr );
	}

	//--------------------------------------------------------------------------------
	int __cdecl _woutput_s_l ( CPosumStream* pStream, const wchar_t* format, localeinfo_struct* plocinfo, va_list argptr )
	{
		return 0;//OutputW( format, plocinfo, true, false, argptr );
	}

	//--------------------------------------------------------------------------------
	int __cdecl _output( CPosumStream* pStream, const char* format, va_list argptr )
	{
		return 0;//OutputA( format, 0, false, false, argptr );
	}
	
	//--------------------------------------------------------------------------------
	int __cdecl _output_l ( CPosumStream* pStream, const char* format, localeinfo_struct* plocinfo, va_list argptr )
	{
		return 0;//OutputA( format, plocinfo, false, false, argptr );
	}
	
	//--------------------------------------------------------------------------------
	int __cdecl _output_p ( CPosumStream* pStream, const char* format, va_list argptr )
	{
		return 0;//OutputA( format, 0, false, true, argptr );
	}

	//--------------------------------------------------------------------------------
	int __cdecl _output_p_l ( CPosumStream* pStream, const char* format, localeinfo_struct* plocinfo, va_list argptr )
	{
		return 0;//OutputA( format, plocinfo, false, true, argptr );
	}

	//--------------------------------------------------------------------------------
	int __cdecl _output_s ( CPosumStream* pStream, const char* format, va_list argptr )
	{
		return 0;//OutputA( format, 0, true, false, argptr );
	}

	//--------------------------------------------------------------------------------
	int __cdecl _output_s_l ( CPosumStream* pStream, const char* format, localeinfo_struct* plocinfo, va_list argptr )
	{
		return 0;//OutputA( format, plocinfo, true, false, argptr );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::fprintf( const char* format, va_list vargs )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::fprintf_s( const char* format, va_list vargs )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::fscanf( const char* format, va_list vargs )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::fscanf_s( const char* format, va_list vargs )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::vfprintf( const char* format, va_list arg )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::vfprintf_s( const char* format, va_list arg )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::vfscanf( const char* format, va_list arg )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_fwprintf_l( const wchar_t* format, ::locale_t locale, va_list vargs )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_fwprintf_p( const wchar_t* format, va_list vargs)
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_fwprintf_p_l( const wchar_t* format, ::locale_t locale, va_list vargs )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_fwprintf_s_l( const wchar_t* format, ::locale_t locale, va_list vargs )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_fwscanf_l( const wchar_t* format, ::locale_t locale, va_list vargs )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_fwscanf_s_l( const wchar_t* format, ::locale_t locale, va_list vargs )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_fscanf_l( const char* format, ::locale_t locale, va_list vargs )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_fscanf_s_l( const char* format, ::locale_t locale, va_list vargs )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_fprintf_l( const char* format, ::locale_t locale, va_list vargs )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_fprintf_p( const char* format, va_list vargs )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_fprintf_p_l( const char* format, ::locale_t locale, va_list vargs )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_fprintf_s_l( const char* format, ::locale_t locale, va_list vargs )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::fwprintf( const wchar_t* format, va_list vargs )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::fwscanf( const wchar_t* format, va_list vargs )
	{
		return 0;
	}
	
	//------------------------------------------------------------------------------
	int CPosumStream::vfwprintf( const wchar_t* format, va_list arg )
	{
		return vfwprintf_helper( _woutput_l, format, 0, arg );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::vfwscanf( const wchar_t* format, va_list arg )
	{
		return vfwscanf_fn( _winput_l, format, 0, arg );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::fwprintf_s( const wchar_t* format, va_list vargs )
	{
		return _vfwprintf_s_l( format, 0, vargs );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::fwscanf_s( const wchar_t* format, va_list vargs )
	{
		return vfwscanf_fn( _winput_s_l, format, 0, vargs );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::vfwprintf_s( const wchar_t* format, va_list arg )
	{
		return vfwprintf_helper( _woutput_s_l, format, 0, arg );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_vfprintf_l( const char* format, ::locale_t locale, va_list argptr )
	{
		return vfprintf_helper( _output_l, format, locale, argptr );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_vfprintf_p( const char* format, va_list argptr )
	{
		return vfprintf_helper( _output_p_l, format, 0, argptr );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_vfprintf_p_l( const char* format, ::locale_t locale, va_list argptr )
	{
		return vfprintf_helper( _output_p_l, format, locale, argptr );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_vfprintf_s_l( const char* format, ::locale_t locale, va_list argptr )
	{
		return vfprintf_helper( _output_s_l, format, locale, argptr );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_vfwprintf_l( const wchar_t* format, ::locale_t locale, va_list argptr )
	{
		return vfwprintf_helper( _woutput_l, format, locale, argptr );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_vfwprintf_p( const wchar_t* format, va_list argptr )
	{
		return vfwprintf_helper( _woutput_p_l, format, 0, argptr );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_vfwprintf_p_l( const wchar_t* format, ::locale_t locale, va_list argptr )
	{
		return vfwprintf_helper( _woutput_p_l, format, locale, argptr );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_vfwprintf_s_l( const wchar_t* format, ::locale_t locale, va_list argptr )
	{
		return vfwprintf_helper( _woutput_s_l, format, locale, argptr );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::vfwprintf_helper( WOUTPUTFN woutfn, const wchar_t* format, _locale_t plocinfo, va_list ap )
	{
        int buffing;
        int retval = 0;

		if( this == NULL || format == NULL )
		{
			errno = EINVAL;
			return -1;
		}

		flockfile();
        __try 
		{
			buffing = _stbuf();
			retval = woutfn( this, format, plocinfo, ap );
			_ftbuf(buffing);
        }
        __finally 
		{
            funlockfile();
        }

        return(retval);
	}

	//------------------------------------------------------------------------------
	int CPosumStream::vfprintf_helper( OUTPUTFN outfn, const char* format, _locale_t plocinfo, va_list ap )
	{
        int buffing;
        int retval = 0;

		if( this == NULL || format == NULL )
		{
			errno = EINVAL;
			return -1;
		}

		flockfile();

		__try 
		{
			int fn;
			
			if( !( ( _flag & _IOSTRG ) || ( fn = _fileno(), ( ( m_chTextMode == __IOINFO_TM_ANSI ) && !m_bchUnicode ) ) ) )
			{
				errno = EINVAL;
				retval= -1;
			}

			if( retval == 0 )
			{
				buffing = _stbuf();
				retval = outfn( this, format, plocinfo, ap );
				_ftbuf( buffing );
			}

        }
        __finally 
		{
            funlockfile();
        }

        return retval;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::vfwscanf_fn( WINPUTFN winputfn, const wchar_t* format, _locale_t plocinfo, va_list arglist )
	{
		int retval = 0;

		if( this == NULL || format == NULL )
		{
			errno = EINVAL;
			return EOF;
		}

		flockfile();
		__try 
		{
			retval = (winputfn( this, format, plocinfo, arglist ) );
		}
		__finally 
		{
			funlockfile();
		}

		return retval;
	}

}//nsWin32
