
#ifndef WINPOSUM_STREAM_IMPL_H_3
#define WINPOSUM_STREAM_IMPL_H_3

#include <stdio.h>
#include "WinQL/WinQL.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "WinQL/Application/Threading/WinQLSynchronization.h"
#include "WinQL/System/FileSystem/WinQLFile.h"
#include "WinQL/Application/ErrorSystem/WinQLErrorHandling.h"
#include "WinQL/System/FileSystem/WinQLFileManagement.h"

//------------------------------------------------------------------------------
namespace nsWin32
{

	class CPosumStream;

	int __cdecl _output_l( CPosumStream* _File, const char *_Format, _locale_t _Locale, va_list _ArgList );
	int __cdecl _woutput_l( CPosumStream* _File, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList );
	int __cdecl _output_s_l( CPosumStream* _File, const char *_Format, _locale_t _Locale, va_list _ArgList );
	int __cdecl _output_p_l( CPosumStream* _File, const char *_Format, _locale_t _Locale, va_list _ArgList );
	int __cdecl _woutput_s_l( CPosumStream* _File, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList );
	int __cdecl _woutput_p_l( CPosumStream* _File, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList );
	int __cdecl _input_l( CPosumStream* _File, const unsigned char*, _locale_t _Locale, va_list _ArgList );
	int __cdecl _winput_l( CPosumStream* _File, const wchar_t*, _locale_t _Locale, va_list _ArgList );
	int __cdecl _input_s_l( CPosumStream* _File, const unsigned char*, _locale_t _Locale, va_list _ArgList );
	int __cdecl _winput_s_l( CPosumStream* _File, const wchar_t*, _locale_t _Locale, va_list _ArgList );

	//------------------------------------------------------------------------------
	class CPosumStream : public FILE
	{
	public:

		typedef int (*OUTPUTFN)( CPosumStream* _File, const char *, _locale_t, va_list );
		typedef int (*WOUTPUTFN)( CPosumStream* _File, const wchar_t *, _locale_t, va_list );
		typedef int (*INPUTFN)( CPosumStream* _File, const unsigned char *, _locale_t, va_list );
		typedef int (*WINPUTFN)( CPosumStream* _File, const wchar_t *, _locale_t, va_list );

		__QCMP_STATIC_CONSTANT( unsigned short, _S_IFMT					= 0xF000 );				// file type mask
		__QCMP_STATIC_CONSTANT( unsigned short, _S_IFDIR				= 0x4000 );				//directory
		__QCMP_STATIC_CONSTANT( unsigned short, _S_IFCHR				= 0x2000 );				//character special
		__QCMP_STATIC_CONSTANT( unsigned short, _S_IFIFO				= 0x1000 );				//pipe
		__QCMP_STATIC_CONSTANT( unsigned short, _S_IFREG				= 0x8000 );				//regular
		__QCMP_STATIC_CONSTANT( unsigned short, _S_IREAD				= 0x0100 );				//read permission, owner
		__QCMP_STATIC_CONSTANT( unsigned short, _S_IWRITE				= 0x0080 );				//write permission, owner
		__QCMP_STATIC_CONSTANT( unsigned short, _S_IEXEC				= 0x0040 );				//execute/search permission, owner

		__QCMP_STATIC_CONSTANT( int, FILE_BEGIN							= 0 );
		__QCMP_STATIC_CONSTANT( int, FILE_CURRENT						= 1 );
		__QCMP_STATIC_CONSTANT( int, FILE_END							= 2 );
		__QCMP_STATIC_CONSTANT( int, BUF_SIZE							= 1025 );				// size of LF translation buffer
		__QCMP_STATIC_CONSTANT( intptr_t, _NO_CONSOLE_FILENO			= (intptr_t)-2 );
		__QCMP_STATIC_CONSTANT( unsigned int, _SMALL_BUFSIZ				= 512 );
		__QCMP_STATIC_CONSTANT( unsigned int, _INTERNAL_BUFSIZ			= 4096 );

		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIONoBuffering		= 0x0004 );				//_IONBF
		__QCMP_STATIC_CONSTANT( unsigned short, _IOYOURBUF				= 0x0100 );
		__QCMP_STATIC_CONSTANT( unsigned short, _IOSETVBUF				= 0x0400 );
		__QCMP_STATIC_CONSTANT( unsigned short, _IOFEOF					= 0x0800 );
		__QCMP_STATIC_CONSTANT( unsigned short, _IOFLRTN				= 0x1000 );
		__QCMP_STATIC_CONSTANT( unsigned short, _IOCTRLZ				= 0x2000 );
		__QCMP_STATIC_CONSTANT( unsigned short, _IOCOMMIT				= 0x4000 );
		__QCMP_STATIC_CONSTANT( unsigned short, _IOLOCKED				= 0x8000 );

		__QCMP_STATIC_CONSTANT( unsigned char, FOPEN					= 0x01 );				// file open
		__QCMP_STATIC_CONSTANT( unsigned char, FEOFLAG					= 0x02 );				// end of file has been encountered
		__QCMP_STATIC_CONSTANT( unsigned char, FCRLF					= 0x04 );				// CR-LF across read buffer (in text mode)
		__QCMP_STATIC_CONSTANT( unsigned char, FPIPE					= 0x08 );				// file refers to a pipe
		__QCMP_STATIC_CONSTANT( unsigned char, FNOINHERIT				= 0x10 );				// file opened _O_NOINHERIT
		__QCMP_STATIC_CONSTANT( unsigned char, FAPPEND					= 0x20 );				// file opened O_APPEND
		__QCMP_STATIC_CONSTANT( unsigned char, FDEV						= 0x40 );				// file refers to device
		__QCMP_STATIC_CONSTANT( unsigned char, FTEXT					= 0x80 );				// file is in text mode

		__QCMP_STATIC_CONSTANT( int, _SH_DENYRW							= 0x10 );				// deny read/write mode
		__QCMP_STATIC_CONSTANT( int, _SH_DENYWR							= 0x20 );				// deny write mode
		__QCMP_STATIC_CONSTANT( int, _SH_DENYRD							= 0x30 );				// deny read mode
		__QCMP_STATIC_CONSTANT( int, _SH_DENYNO							= 0x40 );				// deny none mode
		__QCMP_STATIC_CONSTANT( int, _SH_SECURE							= 0x80 );				// secure mode

		__QCMP_STATIC_CONSTANT( int, OReadOnly							= 0x00000 );			//open for reading only
		__QCMP_STATIC_CONSTANT( int, OWriteOnly							= 0x00001 );			//open for writing only
		__QCMP_STATIC_CONSTANT( int, OReadWrite							= 0x00002 );			//open for reading and writing
		__QCMP_STATIC_CONSTANT( int, OAppend							= 0x00008 );			//writes done at eof
		__QCMP_STATIC_CONSTANT( int, OCreate							= 0x00100 );			//create and open file
		__QCMP_STATIC_CONSTANT( int, OTruncate							= 0x00200 );			//open and truncate
		__QCMP_STATIC_CONSTANT( int, OExclusive							= 0x00400 );			//open only if file doesn't already exist

		__QCMP_STATIC_CONSTANT( int, OText								= 0x04000 );			//file mode is text (translated). OText files have <cr><lf> sequences translated to <lf> on read()'s, and <lf> sequences translated to <cr><lf> on write()'s
		__QCMP_STATIC_CONSTANT( int, OBinary							= 0x08000 );			//file mode is binary (untranslated)
		__QCMP_STATIC_CONSTANT( int, OWText								= 0x10000 );			//file mode is UTF16 (translated)
		__QCMP_STATIC_CONSTANT( int, OU16Text							= 0x20000 );			//file mode is UTF16 no BOM (translated)
		__QCMP_STATIC_CONSTANT( int, OU8Text							= 0x40000 );			//file mode is UTF8  no BOM (translated)

		__QCMP_STATIC_CONSTANT( int, __IOINFO_TM_ANSI					= 0 );					// Regular Text
		__QCMP_STATIC_CONSTANT( int, __IOINFO_TM_UTF8					= 1 );					// UTF8 Encoded
		__QCMP_STATIC_CONSTANT( int, __IOINFO_TM_UTF16LE				= 2 );					// UTF16 Little Endian Encoded
		__QCMP_STATIC_CONSTANT( unsigned char, LF						= 10 );					// line feed
		__QCMP_STATIC_CONSTANT( unsigned char, CR						= 13 );					// carriage return
		__QCMP_STATIC_CONSTANT( unsigned char, CTRLZ					= 26 );					// ctrl-z means eof for text

		__QCMP_STATIC_CONSTANT( int, ORaw								= OBinary );			//file mode is binary (untranslated)
		__QCMP_STATIC_CONSTANT( int, ONoInherit							= 0x00080 );			//child process doesn't inherit file // Open handle inherit bit
		__QCMP_STATIC_CONSTANT( int, OTemporary							= 0x00040 );			//temporary file bit// Temporary file bit - file is deleted when last handle is closed
		__QCMP_STATIC_CONSTANT( int, OShortLived						= 0x01000 );			//temporary storage file, try not to flush// temporary access hint
		__QCMP_STATIC_CONSTANT( int, OObtainDir							= 0x02000 );			//get information about a directory
		__QCMP_STATIC_CONSTANT( int, OSequential						= 0x00020 );			//file access is primarily sequential sequential/random access hints
		__QCMP_STATIC_CONSTANT( int, ORandom							= 0x00010 );			//file access is primarily random

		__QCMP_STATIC_CONSTANT( unsigned short, UTF16LE_BOM				= 0xFEFF );				// UTF16 Little Endian Byte Order Mark
		__QCMP_STATIC_CONSTANT( unsigned short, UTF16BE_BOM				= 0xFFFE );				// UTF16 Big Endian Byte Order Mark
		__QCMP_STATIC_CONSTANT( unsigned short, BOM_MASK				= 0xFFFF );				// Mask for testing Byte Order Mark
		__QCMP_STATIC_CONSTANT( unsigned int,   UTF8_BOM				= 0xBFBBEF );			// UTF8 Byte Order Mark
		__QCMP_STATIC_CONSTANT( int, UTF16_BOMLEN						= 2 );					// No of Bytes in a UTF16 BOM
		__QCMP_STATIC_CONSTANT( int, UTF8_BOMLEN						= 3 );					// No of Bytes in a UTF8 BOM

		CPosumStream();
		CPosumStream( const CPosumStream& src );
		CPosumStream( const char* filename, const char* mode );					//fopen constructor

		CPosumStream& operator = ( const CPosumStream& src );
		~CPosumStream();

		static CPosumStream* _stdin( void );
		static CPosumStream* _stdout( void );
		static CPosumStream* _stderr( void );

		static CPosumStream* fopen( const char* filename, const char* mode );
		static CPosumStream* fdopen( int, const char* );
		static CPosumStream* _fdopen( int fd, const char* mode );
		static CPosumStream* fmemopen( void* , size_t, const char * );
		CPosumStream*  freopen( const char* filename, const char* mode );
		static CPosumStream*  open_memstream( char**, size_t* );
		static CPosumStream*  popen( const char*, const char* );
		static CPosumStream*  _popen( const char* command, const char* mode );
		static CPosumStream*  tmpfile( void );
		static CPosumStream*  _fsopen( const char* filename, const char* mode, int shflag );
		static CPosumStream*  open_wmemstream( wchar_t**, size_t* );
		static CPosumStream*  _wpopen( const wchar_t* pCommand, const wchar_t* pMode );
		static CPosumStream*  _wfsopen( const wchar_t* pFilename, const wchar_t* pMode );
		CPosumStream* _wfreopen( const wchar_t* pFilename, const wchar_t* pMode );
		static CPosumStream* _wfopen( const wchar_t* pFilename, const wchar_t* pMode );

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

		long AddRef( void );
		long Release( void );


		//Internal 

		bool IsInUse( void );
		bool IsWrite( void );

		int _fflush_nolock( void );
		int _fclose_nolock( void );
		void ResetStreamData( void );

	private:

		
		void ResetFILEData( void );

		int _fseeki64_nolock( Cmp__int64 offset, int whence );
		long _ftell_nolock( void );
		Cmp__int64 _ftelli64( void );
		Cmp__int64 _ftelli64_nolock( void );
		Cmp__int64 _lseeki64_nolock ( int fh, Cmp__int64 pos, int mthd );
		
		void _freebuf( void );
		size_t _fwrite_nolock( const void* buffer, size_t size, size_t num );
		int _flsbuf( int ch );
		void _getbuf( void );
		int _write( int fh, const void* buf, unsigned cnt );
		int _write_nolock ( int fh, const void* buf, unsigned cnt );
		wint_t _putwch_nolock( wchar_t ch );
		
		void _openfile( const char* filename, const char* mode, int shflag, CPosumStream* str );
		errno_t _sopen_s( int* pfh, const char* path, int oflag, int shflag, int pmode );
		errno_t _sopen_helper( const char* path, int oflag, int shflag, int pmode, int * pfh, int bSecure );
		errno_t _sopen_nolock( int* punlock_flag, int* pfh, const char* path, int oflag, int shflag, int pmode, int bSecure );
		bool __copy_path_to_wide_string( const char* path, wchar_t** outPath );
		errno_t _wsopen_nolock( int* punlock_flag, int* pfh, const wchar_t* path, int oflag, int shflag, int pmode, int bSecure );
		CFile* __createFile( const wchar_t* path, unsigned long fileaccess, unsigned long fileshare, SECURITY_ATTRIBUTES* lpSecurityAttributes, unsigned long filecreate, unsigned long fileattrib, unsigned long fileflags );
		errno_t _chsize_s( int filedes, Cmp__int64 size );
		errno_t _chsize_nolock( int filedes, Cmp__int64 size );
		int _chsize( int filedes, long size );
		int _setmode( int fh, int mode );
		int _setmode_nolock ( int fh, int mode );
		int _read_nolock(  int fh, void* inputbuf, unsigned cnt );
		size_t _fread_nolock( void *buffer, size_t elementSize, size_t count );
		size_t _fread_nolock_s( void *buffer, size_t bufferSize, size_t elementSize, size_t num );
		int _filbuf( void );
		int _read( int fh, void* buf, unsigned cnt );
		int _fgetc_nolock( void );
		int _fputc_nolock( int _c );
		int _getc_nolock( void );
		int _putc_nolock( int _c );
		int _ungetc_nolock( int ch );
		int _stbuf( void );
		void _ftbuf( int flag );
		int vfwprintf_helper( WOUTPUTFN woutfn, const wchar_t* format, _locale_t plocinfo, va_list ap );
		int vfprintf_helper( OUTPUTFN outfn, const char* format, _locale_t plocinfo, va_list ap );
		int vfwscanf_fn( WINPUTFN winputfn, const wchar_t* format, _locale_t plocinfo, va_list arglist );
		int _commit( int filedes );
		int _close( int fh );
		int _close_nolock( int fh );
		long _lseek( int fh, long pos, int mthd );
		long _lseek_nolock( int fh, long pos, int mthd );
		Cmp__int64 _lseeki64( int fh, Cmp__int64 pos, int mthd );

		//----------------------------------------------------------------------------------------
		int _utf8_no_of_trailbytes( char c)
		{
			return sachLookupTrailBytes[(unsigned char)c];
		}

		int _flush( void );

		bool IsString( void );
		bool IsEOF( void );
		bool IsError( void );
		bool IsReadWrite( void );
		bool IsRead( void );
		
		
		bool IsMyBuffer( void );
		bool IsNoBuffer( void );
		bool IsYourBuffer( void );
		bool IsBigBuffer( void );
		bool IsAnyBuffer( void );
		bool ParseMode( const char* szMode, int& iModeFlags, int& iStreamFlags );

		CCriticalSection m_Lock;

        unsigned char m_chFlags;	// attributes of file (e.g., open in text mode?)
        char m_chPipe;				// one char buffer for void*s opened on pipes
		char m_chTextMode : 7;		// __IOINFO_TM_ANSI or __IOINFO_TM_UTF8 or __IOINFO_TM_UTF16LE
		char m_bchUnicode : 1;      // Was the file opened as unicode?
        char m_achPipeBuffer[ 2 ];	// 2 more peak ahead chars for UNICODE mode
        Cmp__int64 m_i64StartPos;	// File position that matches buffer start
        bool m_bUTF8Translations;	// Buffer contains translations other than CRLF
        char m_dbcsBuffer;			// Buffer for the lead byte of dbcs when converting from dbcs to unicode
        bool m_dbcsBufferUsed;		// Bool for the lead byte buffer is used or not

		shared_long m_lRefCount;	//Count of external references

		CFile* m_pFile;					//WinQL layer file object
		CErrorHelper m_ErrorHelper;		//WinQL Error helper
		CStringHelper m_StringHelper;	//WinQL string and character conversion helper
		CFileHelper m_FileHelper;		//WinQL File system helper

		static char sachLookupTrailBytes[ 256 ];
		static void* _stdbuf[ 2 ];// = { NULL, NULL};
	};

}//nsWin32

#endif//WINPOSUM_STREAM_IMPL_H_3
