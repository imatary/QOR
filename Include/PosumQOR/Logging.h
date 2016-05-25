//Logging.h

//Posum Logging object

#ifndef _POSUMQOR_LOGGING_H_
#define _POSUMQOR_LOGGING_H_

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "Descriptor.h"

//--------------------------------------------------------------------------------
namespace nsPosum
{
	//--------------------------------------------------------------------------------
	class CSystemLog : public CDescriptor
	{
	public:

		//--------------------------------------------------------------------------------
		CSystemLog()
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~CSystemLog()
		{
		}

		virtual void close( void );	//__CQOR_INTERFACE void closelog()
		virtual int open( const char*, int, int );//__CQOR_INTERFACE void openlog( const char*, int, int )

		int SetMask( int );//__CQOR_INTERFACE int setlogmask( int )
		void Log( int, const char*, ... );//__CQOR_INTERFACE void syslog( int, const char*, ... )
	};

};//namespace nsPosum

#endif//_POSUMQOR_LOGGING_H_
