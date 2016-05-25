#ifndef SYSTEMQOR_LIN_TYPES_SYS_MMANTYPES_H_3
#define SYSTEMQOR_LIN_TYPES_SYS_MMANTYPES_H_3

#include "SystemQOR/Linux/LIN_features.h"

#define __NEED_off_t
#define __NEED_mode_t
#define __NEED_size_t

#include QOR_SYS_ARCHHEADER(alltypes.h)

//------------------------------------------------------------------------------
namespace nsLinux
{
    //------------------------------------------------------------------------------
    struct posix_typed_mem_info
    {
        size_t posix_tmi_length;        //Maximum length which may be allocated from a types memory object
    };

}//nsLinux


#endif//SYSTEMQOR_LIN_TYPES_SYS_MMANTYPES_H_3
