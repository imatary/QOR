//DescriptorPool.h

#ifndef _QSYS_MSW_FILESYSTEM_DESCRIPTORPOOL_H_
#define _QSYS_MSW_FILESYSTEM_DESCRIPTORPOOL_H_

#pragma __QCMP_OPTIMIZEINCLUDE

#include "CodeQOR/DataStructures/TMap.h"
#include "CodeQOR/Instancing/Singleton.h"
#include "CodeQOR/DataStructures/TCRef.h"
#include "WinQL/WinQL.h"
//#include "WinQL/WinQLPolicy.h"
#include "WinQL/CodeServices/Synchronization.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	class CDescriptorItemBase;

	//--------------------------------------------------------------------------------
	class CDescriptorPool
	{
		friend class CDescriptorItemBase;
		friend class CFileSystem;

		__QOR_DECLARE_SINGLETON( CDescriptorPool );

	public:

		nsCodeQOR::CTCRef< CDescriptorItemBase > GetItem( int iDescriptor );

	private:

		nsCodeQOR::CTArray< int > m_FreeList;							//Free list of available descriptors
		nsCodeQOR::CTMap< int, CDescriptorItemBase* > m_InUseMap;		//Map of in use descriptors to CDescriptorItemBase

		void GenerateDescriptor( unsigned int uiCount );//Generate a new descriptor into the free list
		void AssignDescriptor( CDescriptorItemBase* pItem );
		void FreeDescriptor( CDescriptorItemBase* pItem );

		long m_lNextToGen;
	};

};// nsWin32

#endif//_QSYS_MSW_FILESYSTEM_DESCRIPTORPOOL_H_
