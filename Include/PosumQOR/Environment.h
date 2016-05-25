//Environment.h

//Posum Environment object

#ifndef _POSUMQOR_ENVIRONMENT_H_
#define _POSUMQOR_ENVIRONMENT_H_

#ifdef	__QCMP_OPTIMIZEINCLUDE
		__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CodeQOR/ClassReg/ClassRegEntry.h"

//--------------------------------------------------------------------------------
namespace nsPosum
{
	//--------------------------------------------------------------------------------
	class CEnvironment
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CEnvironment );

		CEnvironment();
		virtual ~CEnvironment();
		CEnvironment& operator=( CEnvironment& src );

		virtual char* Get( const char* szName );
		virtual int Put( const char* szEnvString );

	private:

		CEnvironment* m_pEnvironmentImpl;
		//__CQOR_INTERFACE char* getenv( const char* name );
		//__CQOR_INTERFACE errno_t getenv_s( size_t* pReturnSize, char* pDstBuf, size_t DstSize, const char* pszVarName );
		//__CQOR_INTERFACE int putenv( const char* envstring );
		//__CQOR_INTERFACE int _putenv( const char* envstring );

	};

}//nsPosum

#endif//_POSUMQOR_ENVIRONMENT_H_
