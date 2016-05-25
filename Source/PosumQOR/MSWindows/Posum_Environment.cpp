//Posum_Environment.cpp
//Windows specific implementation of the Posum CEnvironmentBase class

#include "SystemQOR.h"
#include "PosumQOR/MSWindows/Posum_Environment.h"
#include "WinQL/CodeServices/Process.h"
#include "WinQL/Process/Environment.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsPosum
	{
		//--------------------------------------------------------------------------------
		CEnvironmentImpl::CEnvironmentImpl()
		{
		}

		//--------------------------------------------------------------------------------
		CEnvironmentImpl::~CEnvironmentImpl()
		{
		}

		//--------------------------------------------------------------------------------
		char* CEnvironmentImpl::Get( const char* szName )
		{
			return 0;
		}

		//--------------------------------------------------------------------------------
		int CEnvironmentImpl::Put( const char* szEnvString )
		{
			return 0;
		}

	};//namespace nsPosum
};//namespace nsWin32
