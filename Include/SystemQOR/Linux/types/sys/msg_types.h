#ifndef SYSTEMQOR_LIN_TYPES_SYS_MSGTYPES_H_3
#define SYSTEMQOR_LIN_TYPES_SYS_MSGTYPES_H_3

#include "SystemQOR/Linux/LIN_features.h"

#define __NEED_pid_t
#define __NEED_time_t
#define __NEED_ssize_t

#include QOR_SYS_ARCHHEADER(alltypes.h)

#include "SystemQOR/Linux/types/sys/ipc_types.h"

//------------------------------------------------------------------------------
namespace nsLinux
{
    typedef unsigned int msgqnum_t;
    typedef unsigned int msglen_t;

    //------------------------------------------------------------------------------
    struct msqid_ds
    {
        ipc_perm msg_perm;      //Operation permission structure
        msgqnum_t msg_qnum;     //Number of messages currently on queue
        msglen_t msg_qbytes;    //Maximum number of bytes allowed on queue
        pid_t msg_lspid;        //Process ID of last msgsnd
        pid_t msg_lrpid;        //Process ID of last msgrcv
        time_t msg_stime;       //Time of last msgsnd
        time_t msg_rtime;       //Time of last msgrcv
        time_t msg_ctime;       //Time of last change
    };

}//nsLinux


#endif//SYSTEMQOR_LIN_TYPES_SYS_MSGTYPES_H_3
