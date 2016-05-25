
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

		private:

			CPosumStdio();

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
			std::map< const int, CPosumStream > m_DescriptorStreamMap;		//Map from stream identifiers to stream objects

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

