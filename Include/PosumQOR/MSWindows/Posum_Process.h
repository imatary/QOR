//Posum_Process.h

#ifndef _WINQL_POSUM_PROCESS_H_
#define _WINQL_POSUM_PROCESS_H_

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include <errno.h>
#include "CodeQOR/DataStructures/TLRef.h"
#include "SystemQOR/MSWindows/types/stdio_types.h"
#include "PosumQOR/Process.h"
#include "DescriptorItem.h"
#include "Posum_File.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsPosum
	{
		//--------------------------------------------------------------------------------
		class CPosumProcess : public CPosumFile
		{
		public:

			CPosumProcess( const char* szPath, int iFlags, va_list vargs ) : CPosumFile( szPath, iFlags, vargs ){};
			virtual ~CPosumProcess(){};

		private:

		};

		//--------------------------------------------------------------------------------
		class CPosumProcessDescriptor : public CDescriptorItem< CPosumProcess, ::nsPosum::CProcessInterface >
		{
		public:

			CPosumProcessDescriptor( const char* szPath, int iFlags, va_list vargs ){}
			virtual ~CPosumProcessDescriptor(){}
			
		};

	};// nsPosum

};// nsWin32

#endif//_WINQL_POSUM_STREAM_H_
