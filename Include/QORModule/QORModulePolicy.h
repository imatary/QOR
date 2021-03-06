//QORModulePolicy.h

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

//Policy class for QORModule

#ifndef QORMODULE_POLICY_H_3
#define QORMODULE_POLICY_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CodeQOR/SyncObjects/NullSection.h"
#include "CodeQOR/SyncObjects/NullMutex.h"
#include "CodeQOR/SyncObjects/NullSemaphore.h"
#include "CodeQOR/SyncObjects/SectionLock.h"
#include "CodeQOR/SyncObjects/NullLock.h"

//--------------------------------------------------------------------------------
namespace nsCodeQOR
{	
	class CDefaultSource;
}//nsCodeQOR


//The CPolicy class sets the policies for everything in the namespace built by the owning module
//Any other module including policy dependent headers from this module must first declare its own
//CPolicy class to determine the appropriate defaults.
//--------------------------------------------------------------------------------
class CPolicy
{
public:

	//default container initial sizes
	__QCMP_STATIC_CONSTANT( unsigned long, DEFAULT_INITIAL_ARRAY_SIZE = 8 );

	//Error system parameters
	__QCMP_STATIC_CONSTANT( unsigned char, MAX_ERROR_PARAMETERS = 10 );

	//Synchronization policy, CodeQOR does not understand threading as it's platform ignorant
	//Do not use the Code QOR sync policy anywhere where multi threading may occur
	typedef nsCodeQOR::CNullSection										TThreadSyncSinglePrimitive;
	typedef nsCodeQOR::CNullSemaphore									TThreadSyncMultiPrimitive;
	typedef nsCodeQOR::CNullMutex										TThreadWaitableSinglePrimitive;
	typedef nsCodeQOR::CSectionLock< TThreadSyncSinglePrimitive >		TThreadSyncSingleLock;
	typedef nsCodeQOR::CNullLock										TThreadLock;

	typedef nsCodeQOR::CDefaultSource									TAllocationSource;
};


#endif//QORMODULE_POLICY_H_3
