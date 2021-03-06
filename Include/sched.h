//sched.h

// Copyright Querysoft Limited 2013
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

#ifndef	QOR_SCHED_H_3
#define QOR_SCHED_H_3

#include <time.h>
#include "SystemQOR.h"
#include QOR_SYS_PLATFORMTYPES(sched)

typedef nsPlatform::pid_t pid_t;
typedef nsPlatform::time_t time_t;
typedef nsPlatform::timespec timespec;
typedef nsPlatform::sched_param sched_param;

#define SCHED_FIFO			( nsPlatform::SchedFIFO )		//[PS|TPS]  First in-first out (FIFO) scheduling policy.  
#define SCHED_RR			( nsPlatform::SchedRR )			//[PS|TPS]  Round robin scheduling policy.  
#define SCHED_SPORADIC		( nsPlatform::SchedSporadic )	//[SS|TSP]  Sporadic server scheduling policy.  
#define SCHED_OTHER			( nsPlatform::SchedOther )		//[PS|TPS]  Another scheduling policy.  
#define SCHED_MIN			( nsPlatform::SchedMin )
#define SCHED_MAX			( nsPlatform::SchedMax )

__QCMP_STARTLINKAGE_C

	__QOR_INTERFACE( __CQOR ) int sched_get_priority_max( int );
	__QOR_INTERFACE( __CQOR ) int sched_get_priority_min( int );
	__QOR_INTERFACE( __CQOR ) int sched_getparam( ::pid_t, ::sched_param* );
	__QOR_INTERFACE( __CQOR ) int sched_getscheduler( ::pid_t );
	__QOR_INTERFACE( __CQOR ) int sched_rr_get_interval( ::pid_t, ::timespec* );
	__QOR_INTERFACE( __CQOR ) int sched_setparam( ::pid_t, const ::sched_param* );
	__QOR_INTERFACE( __CQOR ) int sched_setscheduler( ::pid_t, int, const ::sched_param* );
	__QOR_INTERFACE( __CQOR ) int sched_yield( void );

__QCMP_ENDLINKAGE_C

#endif//QOR_SCHED_H_3
