//Timer.h

//Posum Timer object

#ifndef _POSUMQOR_TIMER_H_
#define _POSUMQOR_TIMER_H_

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "Descriptor.h"

//--------------------------------------------------------------------------------
namespace nsPosum
{
	//--------------------------------------------------------------------------------
	class CTimer : public CDescriptor
	{
	public:

		//--------------------------------------------------------------------------------
		CTimer()
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~CTimer()
		{
		}
		
	};

};//namespace nsPosum

#endif//_POSUMQOR_TIMER_H_
