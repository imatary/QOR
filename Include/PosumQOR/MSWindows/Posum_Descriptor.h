//Posum_Descriptor.h

#ifndef _WINQL_POSUM_DESCRIPTOR_H_
#define _WINQL_POSUM_DESCRIPTOR_H_

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "PosumQOR/Descriptor.h"
#include "PosumQOR/MSWindows/FileSystem.h"
#include "PosumQOR/MSWindows/FileData.h"
#include "DescriptorItem.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsPosum
	{
		//--------------------------------------------------------------------------------
		class CPosumDescriptor
		{
		public:

			//--------------------------------------------------------------------------------
			CPosumDescriptor(): m_pFileSystem( &( FileSystem() ) )
			{
			}

			//--------------------------------------------------------------------------------
			virtual ~CPosumDescriptor()
			{
				m_pFileSystem->Close( m_FileData );
			}

			//--------------------------------------------------------------------------------
			virtual long read( void* p, size_t size )
			{
				long Result = m_pFileSystem->Read( m_FileData, p, size );
				return Result;
			}

			//--------------------------------------------------------------------------------
			virtual ssize_t write( const void* pBuffer, size_t nBytes )
			{
				ssize_t Result = m_pFileSystem->Write( m_FileData, pBuffer, nBytes );
				return Result;
			}

			//--------------------------------------------------------------------------------
			virtual int close( void )
			{
				delete this;
				return 0;
			}

		protected:

			nsWin32::CFileData m_FileData;
			nsWin32::CFileHelper m_FileHelper;
			nsWin32::CFileSystem* m_pFileSystem;

		};

		typedef CDescriptorItem< CPosumDescriptor, ::nsPosum::CDescriptor > CPosumDescriptorDescriptor;

	};// nsPosum

};// nsWin32

#endif//_WINQL_POSUM_DESCRIPTOR_H_
