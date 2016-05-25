//DescriptorBase.h

#ifndef _WINQL_FILESYSTEM_DESCRIPTORBASE_H_
#define _WINQL_FILESYSTEM_DESCRIPTORBASE_H_

#pragma __QCMP_OPTIMIZEINCLUDE

#include "SystemQOR/MSWindows/types/sys/types_types.h"
#include "WinQL/WinQL.h"
//#include "WinQL/WinQLPolicy.h"
#include "WinQL/CodeServices/Synchronization.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	class CDescriptorPool;
	class CDescriptorItemBase;

	//--------------------------------------------------------------------------------
	class CDescriptor
	{
	public:

		CDescriptor();
		CDescriptor( int i );
		virtual ~CDescriptor();
		operator int( void );

	protected:

		int m_i;
		CDescriptorPool* m_pPool;
		CDescriptorItemBase* m_pItem;

	private:

		bool AcquireItem( void );
	};

};// nsWin32

#endif//_WINQL_FILESYSTEM_DESCRIPTORBASE_H_
