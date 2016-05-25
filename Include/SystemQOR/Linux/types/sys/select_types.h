#ifndef SYSTEMQOR_LIN_TYPES_SYS_SELECTTYPES_H_3
#define SYSTEMQOR_LIN_TYPES_SYS_SELECTTYPES_H_3

#include "SystemQOR/Linux/LIN_features.h"

#define __NEED_size_t
#define __NEED_time_t
#define __NEED_suseconds_t
#define __NEED_struct_timeval
#define __NEED_struct_timespec
#define __NEED_sigset_t

#include QOR_SYS_ARCHHEADER(alltypes.h)

//------------------------------------------------------------------------------
namespace nsLinux
{

#define FD_SETSIZE 1024

    typedef unsigned long fd_mask;

    //------------------------------------------------------------------------------
    struct fd_set
    {
        unsigned long fds_bits[ FD_SETSIZE / 8 / sizeof( long ) ];
    };

//#define FD_ZERO(s) do { int __i; unsigned long *__b=(s)->fds_bits; for(__i=sizeof (fd_set)/sizeof (long); __i; __i--) *__b++=0; } while(0)
//#define FD_SET(d, s)   ((s)->fds_bits[(d)/(8*sizeof(long))] |= (1UL<<((d)%(8*sizeof(long)))))
//#define FD_CLR(d, s)   ((s)->fds_bits[(d)/(8*sizeof(long))] &= ~(1UL<<((d)%(8*sizeof(long)))))
//#define FD_ISSET(d, s) !!((s)->fds_bits[(d)/(8*sizeof(long))] & (1UL<<((d)%(8*sizeof(long)))))

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
#   define NFDBITS (8*(int)sizeof(long))
#endif

}//nsLinux


#endif//SYSTEMQOR_LIN_TYPES_SYS_SELECTTYPES_H_3
