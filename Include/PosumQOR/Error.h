//Error.h

//Posum Error object

#ifndef _POSUMQOR_ERROR_H_
#define _POSUMQOR_ERROR_H_

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

//--------------------------------------------------------------------------------
namespace nsPosum
{
	//--------------------------------------------------------------------------------
	//Get and Set error number, strerror and perror
	class CError
	{
	public:

		//--------------------------------------------------------------------------------
		CError()
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~CError()
		{
		}
		
	};

};//namespace nsPosum

#endif//_POSUMQOR_ERROR_H_
