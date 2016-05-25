//GUI.h

#ifndef WINQL_GUI_H_3
#define WINQL_GUI_H_3

#include "WinQL/Definitions/Data.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class CGUI
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CGUI );

		CGUI();
		virtual ~CGUI();

	private:

		CGUI( const CGUI& );
		CGUI& operator = ( const CGUI& );
	};

}//nsWin32

#endif//WINQL_GUI_H_3
