//DescriptorItemBase.h

#ifndef _WINQL_FILESYSTEM_DESCRIPTORITEMBASE_H_
#define _WINQL_FILESYSTEM_DESCRIPTORITEMBASE_H_

#pragma __QCMP_OPTIMIZEINCLUDE

#include "CodeQOR/DataStructures/TMap.h"
#include "WinQL/WinQL.h"
//#include "WinQL/WinQLPolicy.h"
#include "WinQL/CodeServices/Synchronization.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	class CDescriptorPool;

	//--------------------------------------------------------------------------------
	class CDescriptorItemBase
	{
		friend class CDescriptorPool;

	public:

		CDescriptorItemBase( int iDescriptor );
		virtual ~CDescriptorItemBase();
		int Descriptor( void );
		void AddRef();
		void Release();

	protected:

		int m_iDescriptor;

		CDescriptorItemBase();

	private:

		void AssignDescriptor( int iDescriptor );
		void FreeDescriptor( void );

		long m_lRefCount;
	};

};// nsWin32

#endif//_WINQL_FILESYSTEM_DESCRIPTORITEMBASE_H_
