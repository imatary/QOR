//SharedBootStrap.h

#ifndef _LINQL_SHARED_BOOTSTRAP_H_
#define _LINQL_SHARED_BOOTSTRAP_H_

#include "CodeQOR/Modules/LoadableModuleBase.h"

//------------------------------------------------------------------------------
namespace nsLinux
{
	//------------------------------------------------------------------------------
	class /*__LINQL_INTERFACE*/ CSharedBootStrap : public nsCodeQOR::CLoadableModuleBase
	{
	public:

	protected:

		CSharedBootStrap();
		CSharedBootStrap( void* );
		virtual ~CSharedBootStrap();

		bool m_bStaticInitialised;
	};
}

#endif//_LINQL_SHARED_BOOTSTRAP_H_
