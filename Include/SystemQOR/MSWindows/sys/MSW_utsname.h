//MSW_utsname.h

#ifndef SYSTEMQOR_MSW_SYS_UTSNAME_H_3
#define SYSTEMQOR_MSW_SYS_UTSNAME_H_3

#include "SystemQOR/Posix/sys/Baseutsname.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __QSYS ) Cutsname : public nsBaseCRT::Csys_utsname
	{
	public:	

        Cutsname();
        virtual ~Cutsname();

		virtual int uname( utsname* );

	private:

		Cutsname( const Cutsname& );
		Cutsname& operator = ( const Cutsname& );
	};
}//nsWin32

#endif//SYSTEMQOR_MSW_SYS_UTSNAME_H_3
