//LnxQLPolicy.h

//LnxQL Policy object
//The policy class for up integrating the Linux QOR library

#ifndef _LNXQL_POLICY_H_
#define _LNXQL_POLICY_H_

//--------------------------------------------------------------------------------
namespace nsLinux
{
	//--------------------------------------------------------------------------------
	class /*__LNXQL_INTERFACE*/ CPolicy
	{
		
	public:
		
		__QCMP_STATIC_CONSTANT( unsigned long, DEFAULT_INITIAL_ARRAY_SIZE = 8 );
		
		//typedef nsSync::CCriticalSection TThreadsyncSinglePrimitive;
		//typedef nsSync::CCriticalSectionLock TThreadSyncSingleLock;
		typedef int TThreadLock;
	};
	
};//nsLinux

#endif //_LNXQL_POLICY_H_