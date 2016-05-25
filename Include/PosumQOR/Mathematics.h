//Mathematics.h

//Posum Mathematics object

#ifndef _POSUMQOR_MATHEMATICS_H_
#define _POSUMQOR_MATHEMATICS_H_

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

//--------------------------------------------------------------------------------
namespace nsPosum
{
	//--------------------------------------------------------------------------------
	//Consider a calculation context within which variables can be declared, values or sets and functions and operations e.g a<b or cos(a) can be performed
	//and the results assigned to variables
	//Effectively a domain specific language for discrete mathemathics with a functional interface
	class CMathematics
	{
	public:

		//--------------------------------------------------------------------------------
		CMathematics()
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~CMathematics()
		{
		}
		
	};

};//namespace nsPosum

#endif//_POSUMQOR_MATHEMATICS_H_
