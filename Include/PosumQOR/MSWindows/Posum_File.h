//Posum_File.h

#ifndef _WINQL_POSUM_FILE_H_
#define _WINQL_POSUM_FILE_H_

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include <errno.h>
#include "CodeQOR/DataStructures/TLRef.h"
#include "SystemQOR/MSWindows/types/stdio_types.h"
#include "PosumQOR/File.h"
#include "Posum_Descriptor.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsPosum
	{
		//--------------------------------------------------------------------------------
		class CPosumFile : public CPosumDescriptor
		{
		public:

			CPosumFile( const char* szPath, int iFlags, va_list vargs );
			CPosumFile( nsWin32::CFile* pOSFile );
			virtual ~CPosumFile();

			virtual int fadvise( off_t offset, off_t len, int advice );

		};
		/*
		//--------------------------------------------------------------------------------
		class CPosumFileDescriptor : public CDescriptorItem< CPosumFile, ::nsPosum::CFileInterface >
		{
		public:

			CPosumFileDescriptor( const char* szPath, int iFlags, va_list vargs );
			CPosumFileDescriptor( nsWin32::CFile* pOSFile );
			virtual ~CPosumFileDescriptor();			
			
			virtual int Control( int cmd, va_list vargs );

		private:

			CPosumFileDescriptor();
		};
		*/
	}// nsPosum

}// nsWin32


#endif//_WINQL_POSUM_FILE_H_

