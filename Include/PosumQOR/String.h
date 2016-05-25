//String.h

//Posum String object

#ifndef _POSUMQOR_STRING_H_
#define _POSUMQOR_STRING_H_

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

//--------------------------------------------------------------------------------
namespace nsPosum
{
	//--------------------------------------------------------------------------------
	class CString
	{
	public:

		CString();
		CString( const CString& src );
		CString& operator = ( const CString& src );
		virtual ~CString();

		//All the C library char* string functions represented on the interface over the owned char*

	protected:

		char* m_pChars;
	};

}//nsPosum

#endif//_POSUMQOR_STRING_H_
