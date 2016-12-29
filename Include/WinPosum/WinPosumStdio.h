
#ifndef WINPOSUM_STDIO_H_3
#define WINPOSUM_STDIO_H_3

#include "CompilerQOR.h"
#include "SystemQOR.h"
#include <deque>
#include <map>
#include "WinPosumStreamImpl.h"

//------------------------------------------------------------------------------
namespace nsWin32
{
	//------------------------------------------------------------------------------
	namespace nsDetail
	{
		//------------------------------------------------------------------------------
		class __QOR_INTERFACE( __WINPOSUM ) CPosumStdio
		{
		public:

			__QCMP_STATIC_CONSTANT( int, STDIO_HANDLES_COUNT = 3 );
			__QCMP_STATIC_CONSTANT( unsigned long, STD_INPUT_HANDLE = ( (unsigned long)-10 ) );
			__QCMP_STATIC_CONSTANT( unsigned long, STD_OUTPUT_HANDLE = ( (unsigned long)-11 ) );
			__QCMP_STATIC_CONSTANT( unsigned long, STD_ERROR_HANDLE = ( (unsigned long)-12 ) );

			__QCMP_STATIC_CONSTANT( intptr_t, _NO_CONSOLE_FILENO = (intptr_t)-2 );
			__QCMP_STATIC_CONSTANT( unsigned char, FOPEN = 0x01 );// file void* open
			__QCMP_STATIC_CONSTANT( unsigned char, FEOFLAG = 0x02 );// end of file has been encountered
			__QCMP_STATIC_CONSTANT( unsigned char, FCRLF = 0x04 );// CR-LF across read buffer (in text mode)
			__QCMP_STATIC_CONSTANT( unsigned char, FPIPE = 0x08 );// file void* refers to a pipe
			__QCMP_STATIC_CONSTANT( unsigned char, FNOINHERIT = 0x10 );// file void* opened _O_NOINHERIT
			__QCMP_STATIC_CONSTANT( unsigned char, FAPPEND = 0x20 );// file void* opened O_APPEND
			__QCMP_STATIC_CONSTANT( unsigned char, FDEV = 0x40 );// file void* refers to device
			__QCMP_STATIC_CONSTANT( unsigned char, FTEXT = 0x80 );// file void* is in text mode
			
			//------------------------------------------------------------------------------
			enum eFlush
			{
				FlushNULL		= 0,
				FlushAll		= 1
			};

			static CPosumStdio& _Instance( void );

			~CPosumStdio();

			int _setmaxstdio( unsigned int uiMax );
			int _getmaxstdio( void );
			CPosumStream* _getstream( void );

			errno_t _umask_s( int mode, int* poldmode );
			int _umask( int mode );
			int _umaskval( void );

			int flsall( int flushflag );

			void FreeHandle( int iFile );

			errno_t _set_fmode( int mode );
			errno_t _get_fmode( int* pMode );

			CPosumStream* StreamFromID( int fd );
			
			inline int stdhndl( int fh )
			{
				return ( ( fh == 0 ) ? STD_INPUT_HANDLE : ( ( fh == 1 ) ? STD_OUTPUT_HANDLE : STD_ERROR_HANDLE ) );
			}

		private:

			CPosumStdio();

			void Initialize( const STARTUPINFO& StartupInfo );
			void AllocateStreams( unsigned int uiCount );
			void AllocateStream( bool bLock = true );
			void FreeStreams();

			bool& _exitflag( void );
			int _flushall( void );			
			int _fcloseall( void );		
			int _rmtmp( void );

			unsigned int m_uiNextStream;									//The maximum stream identifier allocated so far, always counts from 0 to m_uiMaxStreams
			unsigned int m_uiInitialStreams;								//Initial number of streams to set up including standard ones
			unsigned int m_uiMaxStreams;									//Maximum stream identifier to allow

			std::deque< int > m_VecFreeLRUList;								//Stream identifiers that are free
			std::map< const int, CPosumStream* > m_DescriptorStreamMap;		//Map from stream identifiers to stream objects

			CCriticalSection m_MapSection;
			CCriticalSection m_FreeListSection;

			bool m_bExitFlag;

			int m_umaskval;
			long m_fmode;

			CInterlockedHelper m_InterlockedHelper;

		};

	}//nsDetail

}//nsWin32

#endif//WINPOSUM_STDIO_H_3

