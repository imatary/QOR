
#ifndef WINPOSUM_STREAM_H_3
#define WINPOSUM_STREAM_H_3

#include "PosumQOR/PosumStream.h"

//------------------------------------------------------------------------------
namespace nsWin32
{
	class CPosumStream;

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINPOSUM ) CPosumStreamAccessor
	{
	public:

		CPosumStreamAccessor( FILE* pFILE );
		~CPosumStreamAccessor();

		void AddRef( void );
		void Release( void );

		static FILE* Stream( int fd );
		static ::nsPosum::CStream::refType _stdin( void );
		static ::nsPosum::CStream::refType _stdout( void );
		static ::nsPosum::CStream::refType _stderr( void );
		static ::nsPosum::CStream::refType fopen( const char* filename, const char* mode );
		static errno_t fopen_s( ::nsPosum::CStream::refType& ppFile, const char* szFilename, const char* szMode );
		static ::nsPosum::CStream::refType fdopen( int, const char* );
		static ::nsPosum::CStream::refType fmemopen( void* __QCMP_RESTRICT, size_t, const char * );
		::nsPosum::CStream::refType freopen( const char* filename, const char* mode );
		errno_t freopen_s( ::nsPosum::CStream::refType& ppFile, const char* szFilename, const char* szMode );
		static ::nsPosum::CStream::refType open_memstream( char**, size_t* );
		static ::nsPosum::CStream::refType popen( const char*, const char* );
		static ::nsPosum::CStream::refType _popen( const char* command, const char* mode );
		static ::nsPosum::CStream::refType tmpfile( void );
		static errno_t tmpfile_s( ::nsPosum::CStream::refType& ppFile );
		static ::nsPosum::CStream::refType _fsopen( const char* filename, const char* mode, int shflag );
		static ::nsPosum::CStream::refType open_wmemstream( wchar_t**, size_t* );
		static ::nsPosum::CStream::refType _wpopen( const wchar_t* pCommand, const wchar_t* pMode );
		static ::nsPosum::CStream::refType _wfsopen( const wchar_t* pFilename, const wchar_t* pMode );
		::nsPosum::CStream::refType _wfreopen( const wchar_t* pFilename, const wchar_t* pMode );
		errno_t _wfreopen_s( ::nsPosum::CStream::refType& pFile, const wchar_t* pFilename, const wchar_t* pMode );
		static ::nsPosum::CStream::refType _wfopen( const wchar_t* pFilename, const wchar_t* pMode );
		static errno_t _wfopen_s( ::nsPosum::CStream::refType& ppFile, const wchar_t* pFilename, const wchar_t* pMode );

		void clearerr( void );
		errno_t clearerr_s( void );
		int fclose( void );
		int feof( void );
		int ferror( void );
		int fflush( void );
		int fgetc( void );
		int fgetpos( fpos_t* pos );
		char* fgets( char* s, int n );
		int fileno( void );
		int _fileno( void );
		void flockfile( void );
		int fprintf( const char* format, va_list vargs );
		int fprintf_s( const char* format, va_list vargs );
		int fputc( int c );
		int fputs( const char* s );
		size_t fread( void* ptr, size_t size, size_t nmemb );
		size_t fread_s( void* ptr, size_t DstSize, size_t ElementSize, size_t Count );		
		void rewind( void );
		int fscanf( const char* format, va_list vargs );
		int fscanf_s( const char* format, va_list vargs );
		int fseek( long int offset, int whence );
		int fseeko( off_t, int );
		int SeekO( off_t offset, int whence );
		void setbuf( char* buf );
		int setvbuf( char* buf, int mode, size_t size );
		int fsetpos( const fpos_t* pos );
		long int ftell( void );
		off_t ftello( void );
		int ftrylockfile( void );
		void funlockfile( void );
		size_t fwrite( const void* ptr, size_t size, size_t nmemb );
		int getc( void );
		int getc_unlocked( void );
		ssize_t getdelim( char**, size_t*, int );
		ssize_t getline( char**, size_t* );
		int pclose( void );
		int putc( int c );
		int putc_unlocked( int );
		int ungetc( int c );
		int vfprintf( const char* format, va_list arg );
		int vfprintf_s( const char* format, va_list arg );
		int vfscanf( const char* format, va_list arg );
		int _putw( int binint );
		int _getw( void );
		int _fwprintf_l( const wchar_t* format, ::locale_t locale, va_list vargs );
		int _fwprintf_p( const wchar_t* format, va_list vargs);
		int _fwprintf_p_l( const wchar_t* format, ::locale_t locale, va_list vargs );
		int _fwprintf_s_l( const wchar_t* format, ::locale_t locale, va_list vargs );
		int _fwscanf_l( const wchar_t* format, ::locale_t locale, va_list vargs );
		int _fwscanf_s_l( const wchar_t* format, ::locale_t locale, va_list vargs );
		int _fscanf_l( const char* format, ::locale_t locale, va_list vargs );
		int _fscanf_s_l( const char* format, ::locale_t locale, va_list vargs );
		int _fseeki64( Cmp__int64 offset, int origin );
		int _fprintf_l( const char* format, ::locale_t locale, va_list vargs );
		int _fprintf_p( const char* format, va_list vargs );
		int _fprintf_p_l( const char* format, ::locale_t locale, va_list vargs );
		int _fprintf_s_l( const char* format, ::locale_t locale, va_list vargs );
		wint_t fgetwc();
		wchar_t* fgetws( wchar_t* s, int n );
		wint_t fputwc( wchar_t c );
		int fputws( const wchar_t* s );
		int fwide( int mode );
		int fwprintf( const wchar_t* format, va_list vargs );
		int fwscanf( const wchar_t* format, va_list vargs );
		wint_t getwc();		
		wint_t putwc( wchar_t c );
		wint_t ungetwc( wint_t c );
		int vfwprintf( const wchar_t* format, va_list arg );
		int vfwscanf( const wchar_t* format, va_list arg );
		int fwprintf_s( const wchar_t* format, va_list vargs );
		int fwscanf_s( const wchar_t* format, va_list vargs );
		int vfwprintf_s( const wchar_t* format, va_list arg );
		int _vfprintf_l( const char* format, ::locale_t locale, va_list argptr );
		int _vfprintf_p( const char* format, va_list argptr );
		int _vfprintf_p_l( const char* format, ::locale_t locale, va_list argptr );
		int _vfprintf_s_l( const char* format, ::locale_t locale, va_list argptr );
		int _vfwprintf_l( const wchar_t* format, ::locale_t locale, va_list argptr );
		int _vfwprintf_p( const wchar_t* format, va_list argptr );
		int _vfwprintf_p_l( const wchar_t* format, ::locale_t locale, va_list argptr );
		int _vfwprintf_s_l( const wchar_t* format, ::locale_t locale, va_list argptr );

	private:

		CPosumStreamAccessor();
		CPosumStreamAccessor( const CPosumStreamAccessor& );
		CPosumStreamAccessor& operator = ( const CPosumStreamAccessor& );

		::nsPosum::CStream* m_pInterface;
		nsWin32::CPosumStream* m_pImplementation;
	};

}//nsWin32


#endif//WINPOSUM_STREAM_H_3
