//WinPosumStringPool.h

#ifndef WINPOSUM_STRINGPOOL_H_3
#define WINPOSUM_STRINGPOOL_H_3

#include "CompilerQOR.h"
#include "SystemQOR.h"
#include "WinQL/CodeServices/Text/WinString.h"

//------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------	
	class __QOR_INTERFACE( __CODEQOR ) CWinPosumStringSource : public nsCodeQOR::CDefaultSource
	{
	public:

		CWinPosumStringSource();
		~CWinPosumStringSource();
		CWinPosumStringSource( const CWinPosumStringSource& src );
		CWinPosumStringSource& operator = ( const CWinPosumStringSource& src );

		virtual byte* Source( unsigned int uiByteCount );
		virtual void Free( byte* pMemory, unsigned int /*uiByteCount*/ );

	};

	//------------------------------------------------------------------------------
	//Pool of underlying WinQL strings over the character type which can be looked up from raw pointers
	//These will allocated form known ranges of memory so that raw pointers can be validated.

	template< class char_t >
	class __QOR_INTERFACE( __WINPOSUM ) CPosumStringPool
	{
	public:

		typedef CString< char_t, CWinPosumStringSource > CPosumPooledString;

		CPosumStringPool();
		~CPosumStringPool();

		//vector of pool pages 64k
		//bit tree for each page to determine what is allocated
		//10 - something is allocated in the first half, nothing in the second half
		//0100 - the second half of that first half is in use, and so on down to the minimum allocation size.

		//search down the tree for space only as far as any space found would be big enough for the string
		//The bit tree itself will grow - need some way to manage that, probably allocate it separately.

		bool ValidateAddress( Cmp_ulong_ptr Address );

		CPosumPooledString* FromRawPointer( const char_t* pRaw );
	};

}//nsWin32


#endif//WINPOSUM_STRINGPOOL_H_3
