//Signal.h

//Posum Signal object

#ifndef _POSUMQOR_SIGNAL_H_
#define _POSUMQOR_SIGNAL_H_

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "Descriptor.h"

//--------------------------------------------------------------------------------
namespace nsPosum
{
	//--------------------------------------------------------------------------------
	class CSignal : public CDescriptor
	{
	public:

		//--------------------------------------------------------------------------------
		CSignal()
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~CSignal()
		{
		}
		
	};

};//namespace nsPosum

#endif//_POSUMQOR_SIGNAL_H_
