//FileSystem.h

//Posum File System object

#ifndef POSUMQOR_FILESYSTEM_H_2
#define POSUMQOR_FILESYSTEM_H_2

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include <utime.h>
#include "File.h"

//--------------------------------------------------------------------------------
namespace nsPosum
{
	//--------------------------------------------------------------------------------
	class CFileSystem
	{
	public:

		//--------------------------------------------------------------------------------
		CFileSystem()
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~CFileSystem()
		{
		}
		
		virtual int UTime( const char*, const utimbuf* );//utime
		virtual int Access( const char*, int );//access
		virtual int Link( const char*, const char* );//link
		virtual int Unlink( const char* );//unlink
		virtual CFile Open( const char* szPath, int iFlags, va_list vargs );//open

	};

}//nsPosum

#endif//POSUMQOR_FILESYSTEM_H_2
