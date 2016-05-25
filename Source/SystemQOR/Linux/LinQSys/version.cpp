#ifdef SHARED

#include "LinQSys/version.h"

namespace nsLinux
{
    static const char version[] = VERSION;

    //------------------------------------------------------------------------------
    const char *__libc_get_version()
    {
        return version;
    }
}//nsLinux

#endif
