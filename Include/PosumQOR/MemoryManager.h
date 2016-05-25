//MemoryManager.h

//Posum Memory Manager object

#ifndef _POSUMQOR_MEMORY_H_
#define _POSUMQOR_MEMORY_H_

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

//--------------------------------------------------------------------------------
namespace nsPosum
{
	//--------------------------------------------------------------------------------
	class CMemoryManager
	{
	public:

		//--------------------------------------------------------------------------------
		CMemoryManager()
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~CMemoryManager()
		{
		}

		//malloc
		//free
		//realloc
		//sys v shared memory and memory protection
	};

};//namespace nsPosum

#endif//_POSUMQOR_MEMORY_H_
