
#include "WinPosum/WinPosumStream.h"
#include "WinPosum/WinPosumStdio.h"
#include "WinPosum/WinPosumStreamImpl.h"
#include "WinQL/Application/WinQLApplication.h"
#include "WinQL/CodeServices/Locale/WinQLLocale.h"
#include "WinQL/Definitions/Errors.h"
#include "WinQL/Application/ErrorSystem/WinQLDOSError.h"
#include <errno.h>
#include <assert.h>

//------------------------------------------------------------------------------
namespace nsWin32
{
	//------------------------------------------------------------------------------
	CPosumStreamAccessor::CPosumStreamAccessor( FILE* pFILE ) : m_pImplementation( reinterpret_cast< nsWin32::CPosumStream* >( pFILE ) )
	{
	}

	//------------------------------------------------------------------------------	
	CPosumStreamAccessor::~CPosumStreamAccessor()
	{
	}

	//------------------------------------------------------------------------------	
	void CPosumStreamAccessor::AddRef( void )
	{
		if( m_pImplementation )
		{
			m_pImplementation->AddRef();
		}
	}

	//------------------------------------------------------------------------------	
	void CPosumStreamAccessor::Release( void )
	{
		if( m_pImplementation )
		{
			if( !m_pImplementation->Release() )
			{
				m_pImplementation = 0;
			}
		}
	}

	//------------------------------------------------------------------------------
	FILE* CPosumStreamAccessor::Stream( int fd )
	{
		return nsDetail::CPosumStdio::_Instance().StreamFromID( fd );
	}

	//------------------------------------------------------------------------------
	::nsPosum::CStream::refType CPosumStreamAccessor::_stdin( void )
	{
		return ::nsPosum::CStream::refType( new ::nsPosum::CStream( nsWin32::CPosumStream::_stdin() ) );
	}

	//------------------------------------------------------------------------------
	::nsPosum::CStream::refType CPosumStreamAccessor::_stdout( void )
	{
		return ::nsPosum::CStream::refType( new ::nsPosum::CStream( nsWin32::CPosumStream::_stdout() ) );
	}

	//------------------------------------------------------------------------------
	::nsPosum::CStream::refType CPosumStreamAccessor::_stderr( void )
	{
		return ::nsPosum::CStream::refType( new ::nsPosum::CStream( nsWin32::CPosumStream::_stderr() ) );
	}

	//------------------------------------------------------------------------------
	::nsPosum::CStream::refType CPosumStreamAccessor::fopen( const char* filename, const char* mode )
	{
		return ::nsPosum::CStream::refType( new ::nsPosum::CStream( nsWin32::CPosumStream::fopen( filename, mode ) ) );
	}

	//------------------------------------------------------------------------------
	::nsPosum::CStream::refType CPosumStreamAccessor::fdopen( int fd, const char* mode )
	{
		return ::nsPosum::CStream::refType( new ::nsPosum::CStream( nsWin32::CPosumStream::fdopen( fd, mode ) ) );
	}

	//------------------------------------------------------------------------------
	::nsPosum::CStream::refType CPosumStreamAccessor::fmemopen( void* pVoid, size_t size, const char* sz )
	{
		return ::nsPosum::CStream::refType( new ::nsPosum::CStream( nsWin32::CPosumStream::fmemopen( pVoid, size, sz ) ) );
	}
		
	//------------------------------------------------------------------------------
	errno_t CPosumStreamAccessor::fopen_s( ::nsPosum::CStream::refType& ppFile, const char* szFilename, const char* szMode )
	{
		ppFile = ::nsPosum::CStream::refType( new ::nsPosum::CStream( nsWin32::CPosumStream::fopen( szFilename, szMode ) ) );
		return 0;//TODO:
	}
		
	//------------------------------------------------------------------------------
	::nsPosum::CStream::refType CPosumStreamAccessor::freopen( const char* filename, const char* mode )
	{
		return ::nsPosum::CStream::refType( new ::nsPosum::CStream( m_pImplementation->freopen( filename, mode ) ) );
	}
		
	//------------------------------------------------------------------------------
	errno_t CPosumStreamAccessor::freopen_s( ::nsPosum::CStream::refType& ppFile, const char* szFilename, const char* szMode )
	{
		ppFile = ::nsPosum::CStream::refType( new ::nsPosum::CStream( m_pImplementation->freopen( szFilename, szMode ) ) );
		return 0;//TODO:
	}

	//------------------------------------------------------------------------------
	::nsPosum::CStream::refType CPosumStreamAccessor::open_memstream( char** ppsz, size_t* pSize )
	{
		return ::nsPosum::CStream::refType( new ::nsPosum::CStream( nsWin32::CPosumStream::open_memstream( ppsz, pSize ) ) );
	}

	//------------------------------------------------------------------------------
	::nsPosum::CStream::refType CPosumStreamAccessor::popen( const char* command, const char* mode )
	{
		return ::nsPosum::CStream::refType( new ::nsPosum::CStream( nsWin32::CPosumStream::popen( command, mode ) ) );
	}

	//------------------------------------------------------------------------------
	::nsPosum::CStream::refType CPosumStreamAccessor::_popen( const char* command, const char* mode )
	{
		return ::nsPosum::CStream::refType( new ::nsPosum::CStream( nsWin32::CPosumStream::popen( command, mode ) ) );
	}

	//------------------------------------------------------------------------------
	::nsPosum::CStream::refType CPosumStreamAccessor::tmpfile( void )
	{
		return ::nsPosum::CStream::refType( new ::nsPosum::CStream( nsWin32::CPosumStream::tmpfile() ) );
	}
		
	//------------------------------------------------------------------------------
	errno_t CPosumStreamAccessor::tmpfile_s( ::nsPosum::CStream::refType& ppFile )
	{
		ppFile = ::nsPosum::CStream::refType( new ::nsPosum::CStream( nsWin32::CPosumStream::tmpfile() ) );
		return 0;//TODO:
	}
		
	//------------------------------------------------------------------------------
	::nsPosum::CStream::refType CPosumStreamAccessor::_fsopen( const char* filename, const char* mode, int shflag )
	{
		return ::nsPosum::CStream::refType( new ::nsPosum::CStream( nsWin32::CPosumStream::_fsopen( filename, mode, shflag ) ) );
	}

	//------------------------------------------------------------------------------
	::nsPosum::CStream::refType CPosumStreamAccessor::open_wmemstream( wchar_t** ppwsz, size_t* pSize )
	{
		return ::nsPosum::CStream::refType( new ::nsPosum::CStream( nsWin32::CPosumStream::open_wmemstream( ppwsz, pSize ) ) );
	}

	//------------------------------------------------------------------------------
	::nsPosum::CStream::refType CPosumStreamAccessor::_wpopen( const wchar_t* pCommand, const wchar_t* pMode )
	{
		return ::nsPosum::CStream::refType( new ::nsPosum::CStream( nsWin32::CPosumStream::_wpopen( pCommand, pMode ) ) );
	}

	//------------------------------------------------------------------------------
	::nsPosum::CStream::refType CPosumStreamAccessor::_wfsopen( const wchar_t* pFilename, const wchar_t* pMode )
	{
		return ::nsPosum::CStream::refType( new ::nsPosum::CStream( nsWin32::CPosumStream::_wfsopen( pFilename, pMode ) ) );
	}

	//------------------------------------------------------------------------------
	::nsPosum::CStream::refType CPosumStreamAccessor::_wfreopen( const wchar_t* pFilename, const wchar_t* pMode )
	{
		return ::nsPosum::CStream::refType( new ::nsPosum::CStream( m_pImplementation->_wfreopen( pFilename, pMode ) ) );
	}

	//------------------------------------------------------------------------------
	errno_t CPosumStreamAccessor::_wfreopen_s( ::nsPosum::CStream::refType& pFile, const wchar_t* pFilename, const wchar_t* pMode )
	{
		pFile = ::nsPosum::CStream::refType( new ::nsPosum::CStream( m_pImplementation->_wfreopen( pFilename, pMode ) ) );
		return 0;//TODO:
	}

	//------------------------------------------------------------------------------
	::nsPosum::CStream::refType CPosumStreamAccessor::_wfopen( const wchar_t* pFilename, const wchar_t* pMode )
	{
		return ::nsPosum::CStream::refType( new ::nsPosum::CStream( nsWin32::CPosumStream::_wfopen( pFilename, pMode ) ) );			
	}
		
	//------------------------------------------------------------------------------	
	errno_t CPosumStreamAccessor::_wfopen_s( ::nsPosum::CStream::refType& ppFile, const wchar_t* pFilename, const wchar_t* pMode )
	{
		ppFile = ::nsPosum::CStream::refType( new ::nsPosum::CStream( nsWin32::CPosumStream::_wfopen( pFilename, pMode ) ) );
		return 0;//TODO:
	}
		
	//------------------------------------------------------------------------------	
	void CPosumStreamAccessor::clearerr( void )
	{
		if( m_pImplementation )
		{
			m_pImplementation->clearerr();
		}
		else
		{
			errno = EBADF;
		}
	}

	//------------------------------------------------------------------------------
	errno_t CPosumStreamAccessor::clearerr_s( void )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->clearerr_s();
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fclose( void )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fclose();
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::feof( void )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->feof();
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::ferror( void )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->ferror();
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fflush( void )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fflush();
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fgetc( void )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fgetc();
		}
		else
		{
			errno = EBADF;
			return EOF;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fgetpos( fpos_t* pos )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fgetpos( pos );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	char* CPosumStreamAccessor::fgets( char* s, int n )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fgets( s, n );
		}
		else
		{
			errno = EBADF;
			return 0;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fileno( void )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fileno();
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_fileno( void )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fileno();
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	void CPosumStreamAccessor::flockfile( void )
	{
		if( m_pImplementation )
		{
			m_pImplementation->flockfile();
		}
		else
		{
			errno = EBADF;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fprintf( const char* format, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fprintf( format, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fprintf_s( const char* format, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fprintf_s( format, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fputc( int c )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fputc( c );
		}
		else
		{
			errno = EBADF;
			return EOF;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fputs( const char* s )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fputs( s );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	size_t CPosumStreamAccessor::fread( void* ptr, size_t size, size_t nmemb )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fread( ptr, size, nmemb );
		}
		else
		{
			errno = EBADF;
			return 0;
		}
	}

	//------------------------------------------------------------------------------
	size_t CPosumStreamAccessor::fread_s( void* ptr, size_t DstSize, size_t ElementSize, size_t Count )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fread_s( ptr, DstSize, ElementSize, Count );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	void CPosumStreamAccessor::rewind( void )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->rewind();
		}
		else
		{
			errno = EBADF;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fscanf( const char* format, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fscanf( format, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fscanf_s( const char* format, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fscanf_s( format, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fseek( long int offset, int whence )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fseek( offset, whence );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fseeko( off_t offset, int whence )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fseeko( offset, whence );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	void CPosumStreamAccessor::setbuf( char* buf )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->setbuf( buf );
		}
		else
		{
			errno = EBADF;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::setvbuf( char* buf, int mode, size_t size )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->setvbuf( buf, mode, size );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fsetpos( const fpos_t* pos )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fsetpos( pos );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	long int CPosumStreamAccessor::ftell( void )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->ftell();
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	off_t CPosumStreamAccessor::ftello( void )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->ftello();
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::ftrylockfile( void )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->ftrylockfile();
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	void CPosumStreamAccessor::funlockfile( void )
	{
		if( m_pImplementation )
		{
			m_pImplementation->funlockfile();
		}
		else
		{
			errno = EBADF;
		}
	}

	//------------------------------------------------------------------------------
	size_t CPosumStreamAccessor::fwrite( const void* ptr, size_t size, size_t nmemb )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fwrite( ptr, size, nmemb );
		}
		else
		{
			errno = EBADF;
			return 0;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::getc( void )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->getc();
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::getc_unlocked( void )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->getc_unlocked();
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	ssize_t CPosumStreamAccessor::getdelim( char** ppsz, size_t* pSize, int n )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->getdelim( ppsz, pSize, n );
		}
		else
		{
			errno = EBADF;
			return 0;
		}
	}

	//------------------------------------------------------------------------------
	ssize_t CPosumStreamAccessor::getline( char** ppsz, size_t* pSize )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->getline( ppsz, pSize );
		}
		else
		{
			errno = EBADF;
			return 0;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::pclose( void )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->pclose();
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::putc( int c )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->putc( c );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::putc_unlocked( int c )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->putc_unlocked( c );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::ungetc( int c )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->ungetc( c );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::vfprintf( const char* format, va_list arg )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->vfprintf( format, arg );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::vfprintf_s( const char* format, va_list arg )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->vfprintf_s( format, arg );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::vfscanf( const char* format, va_list arg )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->vfscanf( format, arg );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_putw( int binint )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_putw( binint );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_getw( void )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_getw();
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_fwprintf_l( const wchar_t* format, ::locale_t locale, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_fwprintf_l( format, locale, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_fwprintf_p( const wchar_t* format, va_list vargs)
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_fwprintf_p( format, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_fwprintf_p_l( const wchar_t* format, ::locale_t locale, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_fwprintf_p_l( format, locale, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_fwprintf_s_l( const wchar_t* format, ::locale_t locale, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_fwprintf_s_l( format, locale, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_fwscanf_l( const wchar_t* format, ::locale_t locale, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_fwscanf_l( format, locale, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_fwscanf_s_l( const wchar_t* format, ::locale_t locale, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_fwscanf_s_l( format, locale, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_fscanf_l( const char* format, ::locale_t locale, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_fscanf_l( format, locale, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_fscanf_s_l( const char* format, ::locale_t locale, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_fscanf_s_l( format, locale, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_fseeki64( Cmp__int64 offset, int origin )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_fseeki64( offset, origin );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_fprintf_l( const char* format, ::locale_t locale, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_fprintf_l( format, locale, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_fprintf_p( const char* format, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_fprintf_p( format, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_fprintf_p_l( const char* format, ::locale_t locale, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_fprintf_p_l( format, locale, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_fprintf_s_l( const char* format, ::locale_t locale, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_fprintf_s_l( format, locale, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	wint_t CPosumStreamAccessor::fgetwc()
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fgetwc();
		}
		else
		{
			errno = EBADF;
			return WEOF;
		}
	}

	//------------------------------------------------------------------------------
	wchar_t* CPosumStreamAccessor::fgetws( wchar_t* s, int n )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fgetws( s, n );
		}
		else
		{
			errno = EBADF;
			return 0;
		}
	}

	//------------------------------------------------------------------------------
	wint_t CPosumStreamAccessor::fputwc( wchar_t c )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fputwc( c );
		}
		else
		{
			errno = EBADF;
			return WEOF;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fputws( const wchar_t* s )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fputws( s );
		}
		else
		{
			errno = EBADF;
			return WEOF;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fwide( int mode )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fwide( mode );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fwprintf( const wchar_t* format, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fwprintf( format, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fwscanf( const wchar_t* format, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fwscanf( format, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	wint_t CPosumStreamAccessor::getwc()
	{
		if( m_pImplementation )
		{
			return m_pImplementation->getwc();
		}
		else
		{
			errno = EBADF;
			return WEOF;
		}
	}

	//------------------------------------------------------------------------------		
	wint_t CPosumStreamAccessor::putwc( wchar_t c )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->putwc( c );
		}
		else
		{
			errno = EBADF;
			return WEOF;
		}
	}

	//------------------------------------------------------------------------------
	wint_t CPosumStreamAccessor::ungetwc( wint_t c )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->ungetwc( c );
		}
		else
		{
			errno = EBADF;
			return WEOF;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::vfwprintf( const wchar_t* format, va_list arg )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->vfwprintf( format, arg );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::vfwscanf( const wchar_t* format, va_list arg )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->vfwscanf( format, arg );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fwprintf_s( const wchar_t* format, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fwprintf_s( format, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::fwscanf_s( const wchar_t* format, va_list vargs )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fwscanf_s( format, vargs );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::vfwprintf_s( const wchar_t* format, va_list arg )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->fwprintf_s( format, arg );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_vfprintf_l( const char* format, ::locale_t locale, va_list argptr )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_vfprintf_l( format, locale, argptr );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_vfprintf_p( const char* format, va_list argptr )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_vfprintf_p( format, argptr );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_vfprintf_p_l( const char* format, ::locale_t locale, va_list argptr )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_vfprintf_p_l( format, locale, argptr );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_vfprintf_s_l( const char* format, ::locale_t locale, va_list argptr )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_vfprintf_s_l( format, locale, argptr );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_vfwprintf_l( const wchar_t* format, ::locale_t locale, va_list argptr )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_vfwprintf_l( format, locale, argptr );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_vfwprintf_p( const wchar_t* format, va_list argptr )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_vfwprintf_p( format, argptr );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_vfwprintf_p_l( const wchar_t* format, ::locale_t locale, va_list argptr )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_vfwprintf_p_l( format, locale, argptr );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	int CPosumStreamAccessor::_vfwprintf_s_l( const wchar_t* format, ::locale_t locale, va_list argptr )
	{
		if( m_pImplementation )
		{
			return m_pImplementation->_vfwprintf_s_l( format, locale, argptr );
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}

	//--------------------------------------------------------------------------------
	char CPosumStream::sachLookupTrailBytes[ 256 ] =
	{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
			3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0
	};

	//------------------------------------------------------------------------------
	void* CPosumStream::_stdbuf[ 2 ] = { NULL, NULL };

	//------------------------------------------------------------------------------
	CPosumStream::CPosumStream()
	{
		_ptr = 0;
		_cnt = 0;
		_base = 0;
		_flag = 0;
		_file = 0;
		_charbuf = 0;
		_bufsiz = 0;
		_tmpfname = 0;

		m_chFlags = 0;				// attributes of file (e.g., open in text mode?)
		m_chPipe = 0;				// one char buffer for void*s opened on pipes
		m_chTextMode = 0;			// __IOINFO_TM_ANSI or __IOINFO_TM_UTF8 or __IOINFO_TM_UTF16LE
		m_bchUnicode = 0;			// Was the file opened as unicode?		
		m_i64StartPos = 0;			// File position that matches buffer start
		m_bUTF8Translations = false;// Buffer contains translations other than CRLF
		m_dbcsBuffer = 0;			// Buffer for the lead byte of dbcs when converting from dbcs to unicode
		m_dbcsBufferUsed = false;	// Bool for the lead byte buffer is used or not
		m_lRefCount = 0;			//Count of external references
		m_pFile = 0;				//WinQL layer file object
	}

	//------------------------------------------------------------------------------
	CPosumStream::CPosumStream( const CPosumStream& src )
	{
		*this = src;
	}

	//------------------------------------------------------------------------------
	CPosumStream& CPosumStream:: operator = ( const CPosumStream& src )
	{
		if( &src != this )
		{
			if( _flag & _IOLOCKED )
			{
				funlockfile();
			}

			_flag = src._flag;

			if( _flag & _IOLOCKED )
			{
				flockfile();
			}

			m_chFlags = src.m_chFlags;
			m_chPipe = src.m_chPipe;
			m_chTextMode = src.m_chTextMode;
			m_bchUnicode = src.m_bchUnicode;
			m_achPipeBuffer[ 0 ] = src.m_achPipeBuffer[ 0 ];
			m_achPipeBuffer[ 1 ] = src.m_achPipeBuffer[ 1 ];
			m_i64StartPos = src.m_i64StartPos;
			m_bUTF8Translations = src.m_bUTF8Translations;
			m_dbcsBuffer = src.m_dbcsBuffer;
			m_dbcsBufferUsed = src.m_dbcsBufferUsed;
			m_pFile = src.m_pFile;
			_ptr = src._ptr;
			_cnt = src._cnt;
			_base = src._base;
			_file = src._file;
			_charbuf = src._charbuf;
			_bufsiz = src._bufsiz;
			_tmpfname = src._tmpfname;
		}
		return *this;
	}

	//------------------------------------------------------------------------------
	//fopen constructor
	CPosumStream::CPosumStream( const char* filename, const char* mode )
	{
		ResetStreamData();

        if( *filename == '\0' )
        {
			errno = EINVAL;
        }
		else
		{
			CCriticalSectionLock Lock( m_Lock );			
			//LOpen( filename, mode, _SH_DENYNO );			// open the stream
		}
	}

	//------------------------------------------------------------------------------
	CPosumStream::~CPosumStream()
	{
	}

	//------------------------------------------------------------------------------
	void CPosumStream::ResetStreamData( void )
	{
		ResetFILEData();
		
        m_chFlags = 0;
        m_chPipe = '\0';
		m_chTextMode = 0;
		m_bchUnicode = 0;
        m_achPipeBuffer[ 0 ] = '\0';
		m_achPipeBuffer[ 1 ] = '\0';
        m_i64StartPos = 0;
        m_bUTF8Translations = false;
        m_dbcsBuffer = '\0';
        m_dbcsBufferUsed = false;
		m_pFile = 0;
	}

	//------------------------------------------------------------------------------
	void CPosumStream::SetLowLevelFlags( byte Flags )
	{
		m_chFlags = Flags;
	}

	//------------------------------------------------------------------------------
	void CPosumStream::SetLowLevelFile( CFile* pFile )
	{
		m_pFile = pFile;
	}

	//------------------------------------------------------------------------------
	void CPosumStream::ResetFILEData( void )
	{
		_ptr = 0;
		_cnt = 0;
		_base = 0;
		_flag = 0;
		_file = 0;
		_charbuf = 0;
		_bufsiz = 0;
		_tmpfname = 0;
	}

	//------------------------------------------------------------------------------
	CPosumStream* CPosumStream::_stdin( void )
	{
		return nsDetail::CPosumStdio::_Instance().StreamFromID( 0 );
	}

	//------------------------------------------------------------------------------
	CPosumStream* CPosumStream::_stdout( void )
	{
		return nsDetail::CPosumStdio::_Instance().StreamFromID( 1 );
	}

	//------------------------------------------------------------------------------
	CPosumStream* CPosumStream::_stderr( void )
	{
		return nsDetail::CPosumStdio::_Instance().StreamFromID( 2 );
	}

	//------------------------------------------------------------------------------
	CPosumStream* CPosumStream::fdopen( int, const char* )
	{
		return 0;//TODO:
	}

	//------------------------------------------------------------------------------
	CPosumStream* CPosumStream::fmemopen( void* __QCMP_RESTRICT, size_t, const char * )
	{
		return 0;//TODO:
	}

	//------------------------------------------------------------------------------
	CPosumStream* CPosumStream::freopen( const char* filename, const char* mode )
	{
		return 0;//TODO:
	}

	//------------------------------------------------------------------------------
	CPosumStream* CPosumStream::open_memstream( char**, size_t* )
	{
		return 0;//TODO:
	}

	//------------------------------------------------------------------------------
	CPosumStream* CPosumStream::popen( const char*, const char* )
	{
		return 0;//TODO:
	}

	//------------------------------------------------------------------------------
	CPosumStream* CPosumStream::_popen( const char* command, const char* mode )
	{
		return 0;//TODO:
	}

	//------------------------------------------------------------------------------
	CPosumStream* CPosumStream::tmpfile( void )
	{
		return 0;//TODO:
	}

	//------------------------------------------------------------------------------
	CPosumStream* CPosumStream::open_wmemstream( wchar_t**, size_t* )
	{
		return 0;//TODO:
	}

	//------------------------------------------------------------------------------
	CPosumStream* CPosumStream::_wpopen( const wchar_t* pCommand, const wchar_t* pMode )
	{
		return 0;//TODO:
	}

	//------------------------------------------------------------------------------
	CPosumStream* CPosumStream::_wfsopen( const wchar_t* pFilename, const wchar_t* pMode )
	{
		return 0;//TODO:
	}

	//------------------------------------------------------------------------------
	CPosumStream* CPosumStream::_wfreopen( const wchar_t* pFilename, const wchar_t* pMode )
	{
		return 0;//TODO:
	}

	//------------------------------------------------------------------------------
	CPosumStream* CPosumStream::_wfopen( const wchar_t* pFilename, const wchar_t* pMode )
	{
		return 0;//TODO:
	}

	//------------------------------------------------------------------------------
	long CPosumStream::AddRef( void )
	{
		return ++m_lRefCount;
	}

	//------------------------------------------------------------------------------
	long CPosumStream::Release( void )
	{
		long lResult = --m_lRefCount;
		if( lResult <= 0 )
		{
			fclose();
			delete this;
		}
		return lResult;
	}

	//------------------------------------------------------------------------------
	void CPosumStream::clearerr()
	{
		clearerr_s();
	}

	//------------------------------------------------------------------------------
	errno_t CPosumStream::clearerr_s( void )
	{
		if( this == NULL )
		{
			errno = EINVAL;
			return EINVAL;
		}

		flockfile();
        
        __try 
		{            
            _flag &= ~( _IOERR | _IOEOF );	// Clear stdio level flags
            m_chFlags &= ~(FEOFLAG);		// Clear lowio level flags
        }
        __finally 
		{
            funlockfile();
        }

	    return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::feof( void )
	{
		if( this == 0 )
		{
			errno = EINVAL;
			return 0;
		}
        
        return( ( _flag & _IOEOF ) );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::ferror( void )
	{
		if( this == 0 )
		{
			errno = EINVAL;
			return 0;
		}
        
        return( ( _flag & _IOERR) );
	}

	//------------------------------------------------------------------------------
	int CPosumStream::fileno( void )
	{
		return _file;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_fileno( void )
	{
		return _file;
	}

	//------------------------------------------------------------------------------
	//file://D:\Develop\susv4\functions\pclose.html
	int CPosumStream::pclose( void )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	//file://D:\Develop\susv4\functions\fwide.html
	int CPosumStream::fwide( int mode )
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	void CPosumStream::flockfile( void )
	{
		m_Lock.Acquire();
		_flag |= _IOLOCKED;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::ftrylockfile( void )
	{
		int iResult = !m_Lock.TryEnter();

		if( iResult == 0 )
		{
			_flag |= _IOLOCKED;
		}

		return iResult;
	}

	//------------------------------------------------------------------------------
	void CPosumStream::funlockfile( void )
	{
		_flag &= ~_IOLOCKED;
		m_Lock.Release();
	}

	//------------------------------------------------------------------------------
	CPosumStream* CPosumStream::fopen( const char* file, const char* mode )
	{
        return( CPosumStream::_fsopen( file, mode, _SH_DENYNO ) );
	}

	//------------------------------------------------------------------------------
	CPosumStream* CPosumStream::_fsopen( const char* file, const char* mode ,int shflag )
	{
		CPosumStream* stream = 0;

		if( file == NULL || mode == NULL || *mode == '\0' )
		{
			errno = EINVAL;
			return 0;
		}


		// Get a free stream
		// [NOTE: _getstream() returns a locked stream.]

		if( ( stream = nsDetail::CPosumStdio::_Instance()._getstream() ) == NULL)
		{
			errno = EMFILE;
			return NULL;
		}

		//TODO: Exception handling removed as we're missing __local_unwind4 from Strata-2 Win32 support
		//__try 
		{
			/* We deliberately don't hard-validate for empty strings here. All other invalid
			path strings are treated as runtime errors by the inner code in _open and openfile.
			This is also the appropriate treatment here. Since fopen is the primary access point
			for file strings it might be subjected to direct user input and thus must be robust to
			that rather than aborting. The CRT and OS do not provide any other path validator (because
			WIN32 doesn't allow such things to exist in full generality).
			*/

			if( *file == '\0' )
			{
				errno = EINVAL;
				return NULL;
			}

			stream->_openfile( file, mode, shflag, stream );
	
		}
		//__finally 		
		{
			if( stream )
			{
				stream->funlockfile();
			}
		}

		return stream;
	}

	// set default file commit mode to commit
	int _commode = CPosumStream::_IOCOMMIT;

	//------------------------------------------------------------------------------
	void CPosumStream::_openfile( const char* filename, const char* mode, int shflag, CPosumStream* str )
	{
        int modeflag = 0;
        int streamflag = _commode;
        int commodeset = 0;
        int scanset    = 0;
        int filedes;
        bool encodingFlag = false;

		assert( filename != NULL );
        assert( mode != NULL );
        assert( str != NULL );

        /* Parse the user's specification string as set flags in
               (1) modeflag - system call flags word
               (2) streamflag - stream handle flags word. */

		ParseMode( mode, modeflag, streamflag );

        // Try to open the file.  Note that if neither 't' nor 'b' is specified, _sopen will use the default. */

        if( _sopen_s( &filedes, filename, modeflag, shflag, _S_IREAD | _S_IWRITE ) != 0 )
		{
			return;
		}

		// Init pointers

        _flag = streamflag;
        _cnt = 0;
        _tmpfname = _base = _ptr = NULL;

        _file = filedes;
	}

	//------------------------------------------------------------------------------
	errno_t CPosumStream::_sopen_s( int* pfh, const char* path, int oflag, int shflag, int pmode )
	{
		// Last parameter passed as 1 because we want to validate pmode from the secure open_s
		return _sopen_helper(path, oflag, shflag, pmode, pfh, 1);
	}

	//------------------------------------------------------------------------------
	errno_t CPosumStream::_sopen_helper( const char* path, int oflag, int shflag, int pmode, int * pfh, int bSecure )
	{
        errno_t retval = 0;
        int unlock_flag = 0;

		if( pfh == NULL )
		{
			errno = EINVAL;
			return EINVAL;
		}
        
        *pfh = -1;

		if( path == NULL )
		{
			errno = EINVAL;
			return EINVAL;
		}
        
        if( bSecure )
		{
			if( !( (pmode & ( ~( _S_IREAD | _S_IWRITE ) ) ) == 0 ) )
			{
				errno = EINVAL;
				return EINVAL;
			}
		}

        __try 
		{
            retval = _sopen_nolock( &unlock_flag, pfh, path, oflag, shflag, pmode, bSecure );
        }
        __finally 
		{
            if ( unlock_flag )
            {
                if (retval)
                {
                    m_chFlags &= ~FOPEN;
                }
				funlockfile();
            }
        }

        // in error case, ensure *pfh is -1
        if( retval != 0 )
        {
            *pfh = -1;
        }

        return retval;
	}

	//------------------------------------------------------------------------------
	errno_t CPosumStream::_sopen_nolock( int* punlock_flag, int* pfh, const char* path, int oflag, int shflag, int pmode, int bSecure )
	{
		wchar_t* pathw = 0;
		int retval;

		// At this point we know path is not null
		if( !__copy_path_to_wide_string( path, &pathw ) )
		{
			return -1;
		}

		// call the wide-char variant
		retval = _wsopen_nolock( punlock_flag, pfh, pathw, oflag, shflag, pmode, bSecure );

		free( pathw ); // _free_crt leaves errno alone if everything completes as expected

		return retval;
	}

	//------------------------------------------------------------------------------
	bool CPosumStream::__copy_path_to_wide_string( const char* path, wchar_t** outPath )
	{
		int len;
		unsigned int codePage = CCodePage::ACP;

		if( path == NULL || outPath == NULL )
		{
			errno = EINVAL;
			return false;
		}

#if !defined (_CORESYS) && !defined (_CRT_APP)
		if( !true/*__crtIsPackagedApp()*/ && !m_FileHelper.AreApisANSI() )
		{
			codePage = CCodePage::OEMCP;
		}
#endif  /* !defined (_CORESYS) && !defined (_CRT_APP) */

		*outPath = NULL;

		// get the buffer size needed for conversion
		if ( (len = m_StringHelper.MultiByteToWideChar(codePage, 0 /* Use default flags */, path, -1, 0, 0 ) ) == 0 )
		{
			CDOSError::MapError( m_ErrorHelper.GetLastError() );
			return false;
		}

		// allocate enough space for path wide char
		if ( (*outPath = (wchar_t*)malloc( len * sizeof(wchar_t) ) ) == NULL )
		{
			// malloc should set the errno
			return false;
		}

		// now do the conversion
		if ( m_StringHelper.MultiByteToWideChar( codePage, 0 /* Use default flags */, path, -1, *outPath, len ) == 0 )
		{
			CDOSError::MapError( m_ErrorHelper.GetLastError() );
			free(*outPath);
			*outPath = NULL;
			return false;
		}

		return true;
	}

	//------------------------------------------------------------------------------
	errno_t CPosumStream::_wsopen_nolock( int* punlock_flag, int* pfh, const wchar_t* path, int oflag, int shflag, int pmode, int bSecure )
	{
        Cmp__int64 filepos;						// length of file - 1
        wchar_t ch;								// character at end of file
        char fileflags;							// _osfile flags
        int fmode = 0;

        void* osfh;								// OS handle of opened file
        unsigned long fileaccess;               // OS file access (requested)
        unsigned long fileshare;                // OS file sharing mode
        unsigned long filecreate = 0;           // OS method of opening/creating
        unsigned long fileattrib;               // OS file attributes 
        unsigned long fileattribflags;          // OS file flags
        unsigned long isdev = 0;                // device indicator in low byte

        SECURITY_ATTRIBUTES SecurityAttributes;
        char tmode = __IOINFO_TM_ANSI;			// textmode - ANSI/UTF-8/UTF-16
        errno_t retvalue = 0;

        SecurityAttributes.nLength = sizeof( SecurityAttributes );
        SecurityAttributes.lpSecurityDescriptor = NULL;

        if( oflag & ONoInherit ) 
		{
            SecurityAttributes.bInheritHandle = false;
            fileflags = FNOINHERIT;
        }
        else 
		{
            SecurityAttributes.bInheritHandle = true;
            fileflags = 0;
        }

        errno = nsDetail::CPosumStdio::_Instance()._get_fmode(&fmode);
		
		if( errno != Success )
		{
			return errno;
		}

        // figure out binary/text mode
        if( ( oflag & OBinary ) == 0 )
		{
            if( oflag & ( OText | OWText | OU16Text | OU8Text ) )
			{
                fileflags |= FTEXT;
			}
            else if( fmode != OBinary )   // check default mode
			{
                fileflags |= FTEXT;
			}
		}

        //decode the access flags
        
        switch( oflag & ( OReadOnly | OWriteOnly | OReadWrite ) ) 
		{

            case OReadOnly:         // read access
                    fileaccess = Generic_Read;
                    break;

            case OWriteOnly:         // write access

                    // giving it read access as well because in append (a, not a+), we need to read the BOM to determine the encoding (ie. ANSI, UTF8, UTF16)
                    if( ( oflag & OAppend ) && ( oflag & ( OWText | OU16Text | OU8Text ) ) != 0 )
                    {
                        fileaccess = Generic_Read | Generic_Write;
                    }
                    else
                    {
                        fileaccess = Generic_Write;
                    }
                    break;

            case OReadWrite:           // read and write access
                    fileaccess = Generic_Read | Generic_Write;
                    break;

            default:                // error, bad oflag
                    _set_doserrno( 0 ); // not an OS error
                    *pfh = -1;
					return EINVAL;
                    //_VALIDATE_RETURN_ERRCODE(( "Invalid open flag" , 0 ), EINVAL);

        }

        //decode sharing flags
         
        switch ( shflag ) 
		{

            case _SH_DENYRW:        // exclusive access
                fileshare = 0L;
                break;

            case _SH_DENYWR:        // share read access
                fileshare = File_Share_Read;
                break;

            case _SH_DENYRD:        // share write access
                fileshare = File_Share_Write;
                break;

            case _SH_DENYNO:        // share read and write access
                fileshare = File_Share_Read | File_Share_Write;
                break;

            case _SH_SECURE:       // share read access only if read-only
                if (fileaccess == Generic_Read )
                    fileshare = File_Share_Read;
                else
                    fileshare = 0L;
                break;

            default:               // error, bad shflag
                _set_doserrno( 0 ); // not an OS error
                *pfh = -1;
				return EINVAL;
                //_VALIDATE_RETURN_ERRCODE(( "Invalid sharing flag" , 0 ), EINVAL);
        }

        //decode open/create method flags
         
        switch( oflag & ( OCreate | OExclusive | OTruncate ) ) 
		{
            case 0:
            case OExclusive:                   // ignore EXCL w/o CREAT
                filecreate = Open_Existing;
                break;

            case OCreate:
                filecreate = Open_Always;
                break;

            case OCreate | OExclusive:
            case OCreate | OTruncate | OExclusive:
                filecreate = Create_New;
                break;

            case OTruncate:
            case OTruncate | OExclusive:        // ignore EXCL w/o CREAT
                filecreate = Truncate_Existing;
                break;

            case OCreate | OTruncate:
                filecreate = Create_Always;
                break;

            default:
                // this can't happen ... all cases are covered
                _set_doserrno( 0 );
                *pfh = -1;
				return EINVAL;
                //_VALIDATE_RETURN_ERRCODE(( "Invalid open flag" , 0 ), EINVAL);
        }

        //decode file attribute flags if _O_CREAT was specified
         
        fileattrib = File_Attribute_Normal; // default
        fileattribflags = 0;


        if( oflag & OCreate ) 
		{
            if( !( ( pmode & ~( nsDetail::CPosumStdio::_Instance()._umaskval() ) ) & _S_IWRITE ) )
			{
                fileattrib = File_Attribute_ReadOnly;
			}
        }

        //Set temporary file (delete-on-close) attribute if requested.
        if( oflag & OTemporary ) 
		{
            fileattribflags |= File_Flag_Delete_On_Close;//FILE_FLAG_DELETE_ON_CLOSE;
            fileaccess |= Delete;//DELETE;
            fileshare |= File_Share_Delete;//FILE_SHARE_DELETE;
        }

        //Set temporary file (delay-flush-to-disk) attribute if requested.
         
        if( oflag & OShortLived )
		{
            fileattrib |= File_Attribute_Temporary;//FILE_ATTRIBUTE_TEMPORARY;
		}

        //Set directory access attribute if requested.
         
        if( oflag & OObtainDir )
		{
            fileattribflags |= File_Flag_Backup_Semantics;//FILE_FLAG_BACKUP_SEMANTICS;
		}

        //Set sequential or random access attribute if requested.
         
        if( oflag & OSequential )
		{
            fileattribflags |= File_Flag_Sequential_Scan;//FILE_FLAG_SEQUENTIAL_SCAN;
		}
        else if ( oflag & ORandom )
		{
            fileattribflags |= File_Flag_Random_Access;//FILE_FLAG_RANDOM_ACCESS;
		}

        /*get an available handle.
         *
         * multi-thread note: the returned handle is locked!
         */
		/*
        if( ( *pfh = _alloc_osfhnd() ) == -1 ) 
		{
            _doserrno = 0L;         // not an OS error
            *pfh = -1;
            errno = EMFILE;
            return errno;          // return error to caller
        }
		*/
        /* Beyond this do not set *pfh = -1 on errors for MT.
            Because the caller needs to release the lock on the
            handle */

        *punlock_flag = 1;

        //try to open/create the file
         
        if( ( m_pFile = __createFile( path, fileaccess, fileshare, &SecurityAttributes, filecreate, fileattrib, fileattribflags ) ) == (void*)(-1) )
        {
            if( ( fileaccess & ( Generic_Read| Generic_Write ) ) == ( Generic_Read | Generic_Write ) && ( oflag & OWriteOnly ) )
            {
               //We just failed on CreateFile(), because we might be trying open something for read while it cannot be read (eg. pipes or devices).
               //So try again with GENERIC_WRITE and we will have to use the default encoding.  We won't be able to determine the encoding from reading the BOM.

                fileaccess &= ~Generic_Read;

                if( ( m_pFile = __createFile( path, fileaccess, fileshare, &SecurityAttributes, filecreate, fileattrib, fileattribflags ) ) == (void*)(-1) )
                {
                    /* OS call to open/create file failed! map the error, release the lock, and return -1. note that it's not necessary to
                     * call _free_osfhnd (it hasn't been used yet), but we do need to clear the FOPEN that was set by _alloc_osfhnd.
                     */
                    m_chFlags &= ~FOPEN;
                    CDOSError::MapError( m_ErrorHelper.GetLastError() );
                    retvalue = errno;
                    goto exit;
                }
            }
            else
            {
                /*OS call to open/create file failed! map the error, release the lock, and return -1. note that it's not necessary to call _free_osfhnd (it hasn't been used yet), but we do need
                 * to clear the FOPEN that was set by _alloc_osfhnd.
                 */
                m_chFlags &= ~FOPEN;
                CDOSError::MapError( m_ErrorHelper.GetLastError() );
                retvalue = errno;
                goto exit;
            }
        }

#if !defined(_CRT_APP) || defined(_KERNELX)
        // find out what type of file (file/device/pipe)
        if ( (isdev = m_pFile->GetType() ) == File_Type_Unknown ) 
		{
            unsigned long dwLastError = 0;
            m_chFlags &= ~FOPEN;
            CDOSError::MapError( m_ErrorHelper.GetLastError() );

			delete m_pFile;
			m_pFile = 0;
            
            if( dwLastError == Success )
            {
               /*If GetFileType returns FILE_TYPE_UNKNOWN but doesn't fail,
                * GetLastError returns ERROR_SUCCESS.
                * This function is not designed to deal with unknown types of files
                * and must return an error.
               */
               errno = EACCES;
            }
            retvalue = errno;
            goto exit;
        }

        // use isdev value to set flags
        if( isdev == File_Type_Char )
		{
            fileflags |= FDEV;
		}
        else if( isdev == File_Type_Pipe ) 
		{
            fileflags |= FPIPE;
        }
#endif  /* _CRT_APP */

        //the file is open. now, set the info in _osfhnd array
         
        //_set_osfhnd(*pfh, (intptr_t)osfh);

        //mark the handle as open. store flags gathered so far in _osfile array.
        
        fileflags |= FOPEN;
        
		m_chFlags = fileflags;

        /* TextMode set to ANSI by default, if we find a BOM, then we reset it to the appropriate type below */
        m_chTextMode = __IOINFO_TM_ANSI;

        if( !(fileflags & (FDEV|FPIPE)) && (fileflags & FTEXT) && (oflag & OReadWrite) )
        {
            /* We have a text mode file.  If it ends in CTRL-Z, we wish to remove the CTRL-Z character, so that appending will work.
               We do this by seeking to the end of file, reading the last byte, and shortening the file if it is a CTRL-Z. */

            if ((filepos = _lseeki64_nolock(*pfh, -1, SEEK_END)) == -1) 
			{
                // OS error -- should ignore negative seek error, since that means we had a zero-length file.
				int err;
				_get_doserrno( &err );
                if( err != ErrorNegativeSeek ) 
				{
                    _close_nolock(*pfh);
                    retvalue = errno;
                    goto exit;
                }
            }
            else 
			{
                // Seek was OK, read the last char in file. The last char is a CTRL-Z if and only if _read returns 0 and ch ends up with a CTRL-Z.
                ch = 0;
                if( _read_nolock( *pfh, &ch, 1 ) == 0 && ch == 26 ) 
				{
                    // read was OK and we got CTRL-Z! Wipe it out!
                    if( _chsize_nolock( *pfh, filepos ) == -1 )
                    {
                        _close_nolock(*pfh);
                        retvalue = errno;
                        goto exit;
                    }
                }

                // now rewind the file to the beginning
                if( ( filepos = _lseeki64_nolock( *pfh, 0, SEEK_SET ) ) == -1 ) 
				{
                    _close_nolock(*pfh);
                    retvalue = errno;
                    goto exit;
                }
            }
        }

        if( fileflags & FTEXT ) 
		{

            int count;

            // Set default tmode per oflag. BOM will change the defualt.
            // If oflag does not specify file type get type from _fmode 
            if( ( oflag & ( OText | OWText | OU16Text | OU8Text ) ) == 0 )
            {
                // Type specified in default mode? 
                if ( (fmode & ( OText | OWText | OU16Text | OU8Text ) ) == 0)
				{
                    oflag |= OText; // default to ANSI
				}
                else
				{
                    oflag |= fmode & ( OText | OWText | OU16Text | OU8Text );
				}
            }

            // Now oflags should be set to one of the text modes
            assert( (oflag & ( OText | OWText | OU16Text | OU8Text ) ) != 0 );

            switch( oflag & ( OText | OWText | OU16Text | OU8Text ) )
            {
            case OText :
                tmode = __IOINFO_TM_ANSI;
                break;
            case OWText :
            case OWText | OText :
                if ( (oflag & ( OWriteOnly | OCreate | OTruncate ) ) == ( OWriteOnly | OCreate| OTruncate ) )
				{
                    tmode = __IOINFO_TM_UTF16LE;
				}
                break;
            case OU16Text :
            case OU16Text | OText :
                tmode = __IOINFO_TM_UTF16LE;
                break;

            case OU8Text :
            case OU8Text | OText :
                tmode = __IOINFO_TM_UTF8;
                break;
            }

            /* If the file hasn't been opened with the UNICODE flags then we
            have nothing to do - textmode's already set to default specified in oflag */
            if((oflag & ( OWText | OU16Text | OU8Text ) ) != 0 ) 
			{

                int bom = 0;
                int bWriteBom = 0;
                int bCheckBom = 0;

                if ( !(fileflags & FDEV) ) 
				{
                    switch ( fileaccess & ( Generic_Read | Generic_Write ) ) 
					{

                    case Generic_Read:
                        {
                                bCheckBom = 1;
                                break;
                        }

                    case Generic_Write:
                        {
                            switch ( filecreate ) 
							{
                                // Write BOM if empty file
                            case Open_Existing :
                            case Open_Always :
                            {
                                /* Check if the file contains at least one byte */
                                /* Fall through otherwise */
                                if( _lseeki64_nolock(*pfh, 0, SEEK_END) != 0) 
								{
                                    if(_lseeki64_nolock(*pfh, 0, SEEK_SET) == -1) 
									{
                                        _close_nolock(*pfh);
                                        retvalue = errno;
                                        goto exit;
                                    }
                                    break;
                                }
                            }

                            /* New or truncated file. Always write BOM */
                            case Create_New :
                            case Create_Always :
                            case Truncate_Existing :
                            {
                                bWriteBom = 1;
                                break;
                            }

                            }
                            break;
                        }

                    case Generic_Read | Generic_Write :
                        {
                            switch ( filecreate ) 
							{
                                // Check for existing BOM, Write BOM if empty file 
                            case Open_Existing :
                            case Open_Always :
                            {
                                // Check if the file contains at least one byte
                                // Fall through otherwise
                                if( _lseeki64_nolock( *pfh, 0, SEEK_END ) != 0 ) 
								{
                                    if( _lseeki64_nolock( *pfh, 0, SEEK_SET ) == -1 ) 
									{
                                        _close_nolock( *pfh );
                                        retvalue = errno;
                                        goto exit;
                                    }
                                    bCheckBom = 1;
                                }
                                else 
								{
                                    bWriteBom = 1; // reset if file is not zero size
                                }
                                break;
                            }

                            // New or truncated file. Always write BOM
                            case Create_New :
							case Truncate_Existing :
							case Create_Always :
                            {
                                bWriteBom = 1;
                                break;
                            }

                            }
                            break;
                        }
                    }
                }

                if ( bCheckBom ) 
				{
                    count = _read_nolock(*pfh, &bom, UTF8_BOMLEN);

                    //Internal Validation. This branch should never be taken if bWriteBom is 1 and count > 0
                    
                    if (count > 0 && bWriteBom == 1) 
					{
                        assert(0 && "Internal Error");
                        bWriteBom = 0;
                    }

                    switch( count ) 
					{
                        case -1 :
                            _close_nolock(*pfh);
                            retvalue = errno;
                            goto exit;

                        case UTF8_BOMLEN:
                            if(bom == UTF8_BOM) {
                                tmode = __IOINFO_TM_UTF8;
                                break;
                            }

                        case UTF16_BOMLEN:
                            if((bom & BOM_MASK) == UTF16BE_BOM) 
							{
                                _close_nolock(*pfh);
                                assert(0 && "Only UTF-16 little endian & UTF-8 is supported for reads");
                                retvalue = errno = EINVAL;
                                goto exit;
                            }

                            if((bom & BOM_MASK) == UTF16LE_BOM) 
							{
                                /* We have read 3 bytes, so we should seek back
                                1 byte */
                                if((filepos = _lseeki64_nolock(*pfh, UTF16_BOMLEN, SEEK_SET)) == -1) 
								{
                                    _close_nolock(*pfh);
                                    retvalue = errno;
                                    goto exit;
                                }
                                tmode = __IOINFO_TM_UTF16LE;
                                break;
                            }

                            // Fall through to default case to lseek to beginning of file

                        default:
                            if((filepos = _lseeki64_nolock(*pfh, 0, SEEK_SET)) == -1) 
							{
                                // No BOM, so we should seek back to the beginning of the file
                                _close_nolock(*pfh);
                                retvalue = errno;
                                goto exit;
                            }
                            break;
                    }
                }

                if( bWriteBom ) 
				{
                    int written = 0;
                    int bomlen = 0;
                    bom = 0;

                    // If we are creating a new file, we write a UTF-16LE or UTF8 BOM
                    switch (tmode)
                    {
                    case __IOINFO_TM_UTF16LE :
                        {
                            bom = UTF16LE_BOM;
                            bomlen = UTF16_BOMLEN;
                            break;
                        }
                    case __IOINFO_TM_UTF8 :
                        {
                            bom = UTF8_BOM;
                            bomlen = UTF8_BOMLEN;
                            break;
                        }
                    }

                    while (bomlen > written) 
					{
                        int tmp = 0;
                        // Note that write may write less than bomlen characters, but not really fail. Retry till write fails or till we wrote all the characters.
                        if ((tmp = _write(*pfh, ((char *)(&bom)) + written, bomlen - written)) == -1) 
						{
                            _close_nolock(*pfh);
                            retvalue = errno;
                            goto exit;
                        }
                        written += tmp;
                    }
                }
            }
        }

        m_chTextMode = tmode;
        m_bchUnicode = ( ( oflag & OWText ) == 0 ) ? 0 : 1;


        //Set FAPPEND flag if appropriate. Don't do this for devices or pipes.
         
        if( !( fileflags & ( FDEV | FPIPE ) ) && ( oflag & OAppend ) )
		{
            m_chFlags |= FAPPEND;
		}

        //re-open the file with write access only if we opened the file with read access to read the BOM before
        if( ( fileaccess & ( Generic_Read | Generic_Write ) ) == ( Generic_Read | Generic_Write ) && ( oflag & OWriteOnly ) )
        {
            // we will have to reopen the file again with the write access (but not read)
			delete m_pFile;
			m_pFile = 0;
            
            fileaccess &= ~Generic_Read;
            // we want to use OPEN_EXISTING here, because the user can open the an non-existing
            // file for append with _O_EXCL flag
            filecreate = Open_Existing;
            if( ( m_pFile = __createFile(path, fileaccess, fileshare, &SecurityAttributes, filecreate, fileattrib, fileattribflags )) == (void*)(-1) )
            {
                /* OS call to open/create file failed! map the error, release
                 * the lock, and return -1. Note that it's *necessary* to
                 * call _free_osfhnd (unlike the situation before), because we have
                 * already set the file handle in the _ioinfo structure
                 */
                CDOSError::MapError( m_ErrorHelper.GetLastError() );
                m_chFlags &= ~FOPEN;
                retvalue = errno;
                goto exit;
            }
            else
            {
                // We were able to open the file successfully, set the file
                // handle in the _ioinfo structure, then we are done.  All
                // the fileflags should have been set properly already.
                //_osfhnd(*pfh) = (intptr_t)osfh;
            }
        }

exit:
        return retvalue;
	}

	//------------------------------------------------------------------------------
	CFile* CPosumStream::__createFile( const wchar_t* path, unsigned long fileaccess, unsigned long fileshare, SECURITY_ATTRIBUTES* lpSecurityAttributes, unsigned long filecreate, unsigned long fileattrib, unsigned long fileflags )
	{
		return new CFile( path, fileaccess, fileshare, lpSecurityAttributes, filecreate, fileattrib | fileflags, 0 );
	}

	//------------------------------------------------------------------------------
	errno_t CPosumStream::_chsize_s( int filedes, Cmp__int64 size )
	{
        int r = 0;                          // return value

        //_CHECK_FH_CLEAR_OSSERR_RETURN_ERRCODE( filedes, EBADF );
        //_VALIDATE_CLEAR_OSSERR_RETURN_ERRCODE((filedes >= 0 && (unsigned)filedes < (unsigned)_nhandle), EBADF);
        //_VALIDATE_CLEAR_OSSERR_RETURN_ERRCODE((_osfile(filedes) & FOPEN), EBADF);
        //_VALIDATE_CLEAR_OSSERR_RETURN_ERRCODE((size >= 0), EINVAL);

		flockfile();

        __try 
		{
            if ( m_chFlags & FOPEN )
			{
				r = _chsize_nolock(filedes,size);
			}
            else 
			{
				//assert(("Invalid file descriptor. File possibly closed by a different thread",0));
				r = errno = EBADF;
            }
        }
        __finally 
		{
			funlockfile();
        }

        return r;
	}

	//------------------------------------------------------------------------------
	errno_t CPosumStream::_chsize_nolock( int filedes, Cmp__int64 size )
	{
        Cmp__int64 filend;
        Cmp__int64 extend;
        Cmp__int64 place;
        int cnt;
        int oldmode;
        Cmp__int64 retval = 0; // assume good return
        errno_t err = 0;

		// Get current file position and seek to end
        if( ( ( place = _lseeki64_nolock( filedes, 0i64, SEEK_CUR ) ) == -1i64 ) || ( ( filend = _lseeki64_nolock( filedes, 0i64, SEEK_END ) ) == -1i64 ) )
		{
            return errno;
		}

        extend = size - filend;

        // Grow or shrink the file as necessary

        if( extend > 0i64 ) 
		{
            // extending the file
			CHeap ProcessHeap;
			
            char *bl = reinterpret_cast< char* >( ProcessHeap.Alloc( CHeap::Zero_Memory, _INTERNAL_BUFSIZ ) );

            if( !bl ) 
			{
                err = errno = ENOMEM;
                retval= -1i64;
            } 
			else 
			{
                oldmode = _setmode_nolock( filedes, OBinary );

                // pad out with nulls
                do  
				{
                    cnt = (extend >= (__int64)_INTERNAL_BUFSIZ ) ? _INTERNAL_BUFSIZ : (int)extend;

                    if( ( cnt = _write_nolock( filedes, bl, (extend >= (__int64)_INTERNAL_BUFSIZ) ? _INTERNAL_BUFSIZ : (int)extend ) ) == -1 )
                    {
                        // Error on write
						int err = 0;
						_get_doserrno( &err );
                        if( err == ErrorAccessDenied )
						{
                            err = errno = EACCES;
						}

                        retval = cnt;
                        break;  // leave write loop
                    }
                }
                while ((extend -= (__int64)cnt) > 0i64);

                _setmode_nolock(filedes, oldmode);

				ProcessHeap.Free( 0, bl );
            }

            // retval set correctly
        }
        else if( extend < 0i64 ) 
		{
            // shortening the file

            //Set file pointer to new eof...and truncate it there.
             
            retval = _lseeki64_nolock( filedes, size, SEEK_SET );

            if( retval != -1i64 )
            {
                if( ( retval = m_pFile->SetEOF() ? 0 : -1 ) == -1 )
                {
                    err = errno = EACCES;
                    _set_doserrno( m_ErrorHelper.GetLastError() );
                }
            }
        }

        // else
        // no file change needed
        // retval = 0;

        if(retval == -1 || ( _lseeki64_nolock( filedes, place, SEEK_SET ) == -1i64 ) )
        {
            return errno;
        }

        return 0;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_chsize( int filedes, long size )
	{
		errno_t e;
		e = _chsize_s( filedes, (Cmp__int64)size );
		return e == 0 ? 0 : -1 ;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_setmode( int fh, int mode )
	{
        int retval = 0;

		if( !( ( mode == OText ) || ( mode == OBinary ) || ( mode == OWText ) || ( mode == OU8Text ) || ( mode == OU16Text ) ) )
		{
			errno = EINVAL;
			return -1;
		}


        //_CHECK_FH_RETURN( fh, EBADF, -1 );
        //_VALIDATE_RETURN((fh >= 0 && (unsigned)fh < (unsigned)_nhandle), EBADF, -1);
        //_VALIDATE_RETURN((_osfile(fh) & FOPEN), EBADF, -1);

		flockfile();

        __try 
		{
			if( m_chFlags & FOPEN )
			{
				// set the text/binary mode
				retval = _setmode_nolock(fh, mode);
			}
			else 
			{
				errno = EBADF;
				//_ASSERTE(("Invalid file descriptor. File possibly closed by a different thread",0));
				retval = -1;
			}
        }
        __finally 
		{
			// unlock the file
			funlockfile();
        }

        // Return to user (_setmode_nolock sets errno, if needed)
        return retval;
	}

	//------------------------------------------------------------------------------
	int CPosumStream::_setmode_nolock( int fh, int mode )
	{
        int oldmode;
        int oldtextmode;

        oldmode = m_chFlags & FTEXT;
        oldtextmode = m_chTextMode;

        switch( mode ) 
		{
            case OBinary :
                m_chFlags &= ~FTEXT;
                break;

            case OText :
                m_chFlags |= FTEXT;
                m_chTextMode = __IOINFO_TM_ANSI;
                break;

            case OU8Text :
                m_chFlags |= FTEXT;
                m_chTextMode = __IOINFO_TM_UTF8;
                break;

            case OU16Text :
            case OWText :
                m_chFlags |= FTEXT;
                m_chTextMode = __IOINFO_TM_UTF16LE;
                break;
        }

        if( oldmode == 0 ) 
		{
            return OBinary;
        }

        if( oldtextmode == __IOINFO_TM_ANSI ) 
		{
            return OText;
        }
        else 
		{
            return OWText;
        }
	}

	//------------------------------------------------------------------------------
	bool CPosumStream::IsString( void )
	{
		return ( _flag & _IOSTRG ) ? true : false;
	}

	//------------------------------------------------------------------------------
	bool CPosumStream::IsEOF( void )
	{
		return ( _flag & _IOEOF ) ? true : false;
	}

	//------------------------------------------------------------------------------
	bool CPosumStream::IsError( void )
	{
		return ( _flag & _IOERR ) ? true : false;
	}

	//------------------------------------------------------------------------------
	bool CPosumStream::IsReadWrite( void )
	{
		return ( _flag & _IORW ) ? true : false;
	}

	//------------------------------------------------------------------------------
	bool CPosumStream::IsRead( void )
	{
		return ( _flag & _IOREAD ) ? true : false;
	}

	//------------------------------------------------------------------------------
	bool CPosumStream::IsWrite( void )
	{
		return ( _flag & _IOWRT ) ? true : false;
	}

	//------------------------------------------------------------------------------
	bool CPosumStream::IsInUse( void )
	{
		return ( _flag & (_IOREAD|_IOWRT|_IORW) ) ? true : false;
	}

	//------------------------------------------------------------------------------
	bool CPosumStream::IsMyBuffer( void )
	{
		return ( _flag & _IOMYBUF ) ? true : false;
	}

	//------------------------------------------------------------------------------
	bool CPosumStream::IsNoBuffer( void )
	{
		return ( _flag & _IONBF ) ? true : false;
	}

	//------------------------------------------------------------------------------
	bool CPosumStream::IsYourBuffer( void )
	{
		return ( _flag & _IOYOURBUF ) ? true : false;
	}

	//------------------------------------------------------------------------------
	bool CPosumStream::IsBigBuffer( void )
	{
		return ( _flag & (_IOMYBUF | _IOYOURBUF ) ) ? true : false;
	}

	//------------------------------------------------------------------------------
	bool CPosumStream::IsAnyBuffer( void )
	{
		return ( _flag & ( _IOMYBUF|_IONBF|_IOYOURBUF ) ) ? true : false;
	}

	//#define str_locked(s)   ((s)->_flag & (_IOLOCKED))

	//------------------------------------------------------------------------------
	bool CPosumStream::ParseMode( const char* szMode, int& iModeFlags, int& iStreamFlags )
	{
		bool bResult		= false;

		bool bComModeSet	= false;
		bool bScanSet		= false;
		bool bEncodingFlag	= false;

		char* pszMode = const_cast< char* >( szMode );

		if( pszMode )
		{
			while( *pszMode == ' ' )// Skip leading spaces
			{
				++pszMode;
			}

			switch( *pszMode )
			{
			case 'r':
				iModeFlags = OReadOnly;
				iStreamFlags |= _IOREAD;
				break;
			case 'w':
				iModeFlags = OWriteOnly | OCreate | OTruncate;
				iStreamFlags |= _IOWRT;
				break;
			case 'a':
				iModeFlags = OWriteOnly | OCreate | OAppend;
				iStreamFlags |= _IOWRT;
				break;
			default:
				return bResult;
			}

			bResult = true;
			bool bContinue = true;
			while( *pszMode && bContinue )
			{
				switch( *pszMode )
				{
				case ' ':
				break;

				case '+':
				if( iModeFlags & OReadWrite )
				{
					bContinue = false;
				}
				else
				{
					iModeFlags |= OReadWrite;
					iModeFlags &= ~(OReadOnly | OWriteOnly);
					iStreamFlags |= _IORW;
					iStreamFlags &= ~(_IOREAD | _IOWRT);
				}
				break;

				case 'b':

				if( iModeFlags & ( OText | OBinary ) )
				{
					bContinue = false;
				}
				else
				{
					iModeFlags |= OBinary;
				}
				break;

				case 't':

				if( iModeFlags & ( OText | OBinary ) )
				{
					bContinue = false;
				}
				else
				{
					iModeFlags |= OText;
				}
				break;

				case 'c':

				if( bComModeSet )
				{
					bContinue = false;
				}
				else
				{
					bComModeSet = true;
					iStreamFlags |= _IOCOMMIT;
				}
				break;

				case 'n':
				if( bComModeSet )
				{
					bContinue = false;
				}
				else
				{
					bComModeSet = true;
					iStreamFlags &= ~_IOCOMMIT;
				}
				break;

				case 'S':
				if( bScanSet )
				{
					bContinue = false;
				}
				else
				{
					bScanSet = true;
					iModeFlags |= OSequential;
				}
				break;

				case 'R':
				if( bScanSet )
				{
					bContinue = false;
				}
				else
				{
					bScanSet = true;
					iModeFlags |= ORandom;
				}
				break;

				case 'T':
				if( iModeFlags & OShortLived )
				{
					bContinue = false;
				}
				else
				{
					iModeFlags |= OShortLived;
				}
				break;

				case 'D':
				if( iModeFlags & OTemporary )
				{
					bContinue = false;
				}
				else
				{
					iModeFlags |= OTemporary;
				}
				break;

				case 'N':
				iModeFlags |= ONoInherit;
				break;

				case ',':
				bEncodingFlag = 1;
				bContinue = false;
				break;

				default:
				//_VALIDATE_RETURN(("Invalid file open mode",0), EINVAL, NULL);
				return bResult;
				}
			}
		}

		if( bEncodingFlag )
		{
			static const char ccsField[] = "ccs=";
			static const char utf8encoding[] = "UTF-8";
			static const char utf16encoding[] = "UTF-16LE";
			static const char unicodeencoding[] = "UNICODE";

			// Skip spaces
			while( *pszMode == ' ' )
			{
				++pszMode;
			}

			//The length that we want to compare is numbers of elements in csField -1 since this number also contains NULL terminator

			if( strncmp( ccsField, pszMode, ( _countof( ccsField ) ) - 1 ) != 0 )
			{
				//_VALIDATE_RETURN(("Invalid file open mode",0), EINVAL, NULL);
				bResult = false;
				return bResult;
			}

			pszMode += _countof( ccsField ) - 1;

			if( stricmp( pszMode, utf8encoding ) == 0 )
			{
				pszMode += _countof( utf8encoding ) - 1;
				iModeFlags |= OU8Text;
			}
			else if( stricmp( pszMode, utf16encoding ) == 0 )
			{
				pszMode += _countof( utf16encoding ) - 1;
				iModeFlags |= OU16Text;
			}
			else if( stricmp( szMode, unicodeencoding ) == 0 )
			{
				pszMode += _countof( unicodeencoding ) - 1;
				iModeFlags |= OWText;
			}
			else
			{
				//_VALIDATE_RETURN(("Invalid file open mode",0), EINVAL, NULL);
				bResult = false;
				return bResult;
			}
		}

		while( *pszMode == ' ' )// Skip trailing spaces
		{
			++pszMode;
		}

		return bResult;
	}

}//nsWin32


