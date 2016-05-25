//WinPosumString.h

#ifndef WINPOSUM_STRING_H_3
#define WINPOSUM_STRING_H_3

#include "CompilerQOR.h"
#include "SystemQOR.h"

//------------------------------------------------------------------------------
namespace nsWin32
{
	//------------------------------------------------------------------------------
	template< class char_t >
	class __QOR_INTERFACE( __WINPOSUM ) CPosumString
	{
	public:

		CPosumString();
		CPosumString( char_t* pRawBuffer );
		~CPosumString();

		operator char_t*();

		//locale
		//code page if it's C locale
		//length in chars
		
		//All the standard string functions
	};
}//nsWin32

#endif//WINPOSUM_STRING_H_3
