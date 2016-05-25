
#ifndef SYSTEMQOR_LIN_TYPES_SYS_IPCTYPES_H_3
#define SYSTEMQOR_LIN_TYPES_SYS_IPCTYPES_H_3

#include "SystemQOR/Linux/LIN_features.h"

#define __NEED_key_t
#define __NEED_mode_t
#define __NEED_gid_t
#define __NEED_uid_t

#include QOR_SYS_ARCHHEADER(alltypes.h)

namespace nsLinux
{
    //compatibility
    struct ipc_perm
    {
        uid_t uid;
        gid_t gid;
        uid_t cuid;
        gid_t cgid;
        mode_t mode;
    };
}//nsLinux


#endif//SYSTEMQOR_LIN_TYPES_SYS_IPCTYPES_H_3
