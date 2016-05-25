#include <errno.h>
#include "LinQSys/syscall.h"

//------------------------------------------------------------------------------
namespace nsLinux
{
    //------------------------------------------------------------------------------
    long __syscall_ret( unsigned long r )
    {
        if( r > -4096UL )
        {
            errno = -r;
            return -1;
        }
        return r;
    }

}//nsLinux
