//sem.h

// Copyright Querysoft Limited 2015
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef	QOR_SYS_SEM_H_3
#define QOR_SYS_SEM_H_3

#include <sys/ipc.h>
#include "SystemQOR.h"
#include QOR_SYS_PLATFORMSYSTYPES(sem)

//the following symbolic constant for use as a semaphore operation flag:

#define SEM_UNDO				( nsPlatform::SemUndo )				//Set up adjust on exit entry

//the following symbolic constants for use as commands for the semctl() function:

#define GETNCNT					( nsPlatform::SemGetNCnt )			//Get semncnt. 
#define GETPID					( nsPlatform::SemGetPID )			//Get sempid. 
#define GETVAL					( nsPlatform::SemGetVal )			//Get semval. 
#define GETALL					( nsPlatform::SemGetAll )			//Get all cases of semval. 
#define GETZCNT					( nsPlatform::SemGetZCnt )			//Get semzcnt. 
#define SETVAL					( nsPlatform::SemSetVal )			//Set semval. 
#define SETALL					( nsPlatform::SemSetAll )			//Set all cases of semval. 

typedef nsPlatform::semid_ds semid_ds;
typedef nsPlatform::pid_t pid_t;
//typedef nsPlatform::size_t size_t;
typedef nsPlatform::time_t time_t;
typedef nsPlatform::sembuf sembuf;

__QCMP_STARTLINKAGE_C

    __QOR_INTERFACE( __CQOR ) int semctl( int, int, int, ... );
    __QOR_INTERFACE( __CQOR ) int semget( ::key_t, int, int );
    __QOR_INTERFACE( __CQOR ) int semop( int, ::sembuf*, size_t );

__QCMP_ENDLINKAGE_C

#endif//QOR_SYS_SEM_H_3
