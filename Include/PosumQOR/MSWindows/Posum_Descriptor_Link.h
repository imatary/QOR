//Posum_Descriptor_Link.h

#ifndef _WINQL_POSUM_DESC_LINK_H_
#define _WINQL_POSUM_DESC_LINK_H_

#include "PosumQOR/Descriptor.h"
#include "PosumQOR/Process.h"
#include "WinQL/WinQL.h"
#include "WinQL/CodeServices/Process.h"

#include "PosumQOR/MSWindows/FileSystem.h"

#include "PosumQOR/MSWindows/Posum_Descriptor.h"
#include "PosumQOR/MSWindows/Posum_File.h"
#include "PosumQOR/MSWindows/Posum_Stream.h"
#include "PosumQOR/MSWindows/Posum_Process.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsPosum
	{
		//--------------------------------------------------------------------------------
		template< class TDescriptorItem >
		class CLink
		{
		public:

			//--------------------------------------------------------------------------------
			CLink( int nFD ) : m_pFileSystem( &( FileSystem() ) )
			, m_FD( nFD )
			{
			}

			//--------------------------------------------------------------------------------
			CLink( const CLink& src ) : m_pFileSystem( &( FileSystem() ) )
			, m_FD( src.m_FD )
			{
				
			}

			//--------------------------------------------------------------------------------
			~CLink()
			{
			}
	
			//--------------------------------------------------------------------------------
			TDescriptorItem* Ref( void )
			{
				return dynamic_cast< TDescriptorItem* >( m_pFileSystem->DescriptorPool().GetItem( m_FD ).operator nsWin32::CDescriptorItemBase*() );
			}

		protected:

			nsWin32::CFileSystem* m_pFileSystem;
			int m_FD;			

			CLink() : m_pFileSystem( &( FileSystem() ) )
			, m_FD( -1  )
			{
			}

		private:
			
			CLink& operator = ( const CLink& src );
		};

		typedef CLink< CPosumDescriptorDescriptor > CDescriptorLink;

		//--------------------------------------------------------------------------------
		class CFileLink : public CLink< CPosumFileDescriptor >
		{

		public:

			//--------------------------------------------------------------------------------
			CFileLink( int nFD ) : CLink< CPosumFileDescriptor >( nFD )
			{
			}

			//--------------------------------------------------------------------------------
			CFileLink( const char* szPath, int iFlags, va_list vargs ) : CLink< CPosumFileDescriptor >()
			{
				CPosumFileDescriptor* pPosumFileDescriptor = new CPosumFileDescriptor( szPath, iFlags, vargs );
				m_FD = pPosumFileDescriptor->Descriptor();
			}

			//--------------------------------------------------------------------------------
			CFileLink( const CFileLink& src ) : CLink< CPosumFileDescriptor >( src )
			{
				
			}

			//--------------------------------------------------------------------------------
			~CFileLink()
			{
			}
	
		private:

			CFileLink();
			CFileLink& operator = ( const CFileLink& src );
		};
		
		typedef CLink< CPosumStreamDescriptor > CStreamLink;
		typedef CLink< CPosumProcessDescriptor > CProcessLink;

	}// nsPosum

}// nsWin32

#endif//_WINQL_POSUM_DESC_LINK_H_

