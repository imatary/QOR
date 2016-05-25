#ifndef SYSTEMQOR_LIN_TYPES_SYS_TIMETYPES_H_3
#define SYSTEMQOR_LIN_TYPES_SYS_TIMETYPES_H_3

#include "SystemQOR/Linux/LIN_features.h"

#define __NEED_time_t
#define __NEED_suseconds_t
#define __NEED_struct_timeval

#include QOR_SYS_ARCHHEADER( alltypes.h )

#include "SystemQOR/Linux/types/sys/select_types.h"

//------------------------------------------------------------------------------
namespace nsLinux
{
    //------------------------------------------------------------------------------
    struct itimerval
    {
        timeval it_interval;
        timeval it_value;
    };

    //------------------------------------------------------------------------------
    struct timezone
    {
        int tz_minuteswest;
        int tz_dsttime;
    };

    __QCMP_STATIC_CONSTANT( int, ITimerReal     = 0 );

}//nsLinux

#endif//SYSTEMQOR_LIN_TYPES_SYS_TIMETYPES_H_3
