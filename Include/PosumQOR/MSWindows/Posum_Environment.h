//Posum_Environment.h

#ifndef _WINQL_POSUM_ENVIRONMENT_H_
#define _WINQL_POSUM_ENVIRONMENT_H_

#include "PosumQOR/Environment.h"
#include "CodeQOR/ClassReg/ClassRegEntry.h"
//#include "WinQL/WinQLPolicy.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CPosumEnvironmentFactory : public nsCodeQOR::CTClassRegEntry< nsPosum::CEnvironment >
	{
	public:

		CPosumEnvironmentFactory(){};
		virtual ~CPosumEnvironmentFactory(){};

		//--------------------------------------------------------------------------------
		virtual void* Instance( void )
		{			
			void* pResult = new CPosumEnvironmentImpl();
			return pResult;
		}
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CPosumEnvironmentImpl : public ::nsPosum::CEnvironment
	{
	public:
		CPosumEnvironmentImpl();
		virtual ~CPosumEnvironmentImpl();
		virtual char* Get( const char* szName );
		virtual int Put( const char* szEnvString );

	private:

		static CPosumEnvironmentFactory ThePosumEnvironmentFactory;
	};

}// nsWin32

#endif//_WINQL_POSUM_ENVIRONMENT_H_
