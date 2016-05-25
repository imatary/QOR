//Mock.h

//Mock classes

#ifndef _UNITTEST_MOCK_H_
#define _UNITTEST_MOCK_H_

#ifdef	__CQOR_OPTIMIZEINCLUDE
#pragma __CQOR_OPTIMIZEINCLUDE
#endif//__CQOR_OPTIMIZEINCLUDE

#include "CompilerQOR.h"
#include "HippoQOR/base_mock.h"
#include "HippoQOR/FunctionIndex.h"
#include "HippoQOR/TestExceptions.h"

#ifndef VIRT_FUNC_LIMIT 
#	define VIRT_FUNC_LIMIT 1024
#elif VIRT_FUNC_LIMIT > 1024
#	error Adjust the code to support more than 1024 virtual functions before setting the VIRT_FUNC_LIMIT above 1024
#endif

//--------------------------------------------------------------------------------
namespace nsUnitTesting
{
	//--------------------------------------------------------------------------------
	// mock types
	template <class T>
	class mock : public base_mock 
	{
		friend class MockRepository;

		unsigned char remaining[ sizeof( T ) ];

		//--------------------------------------------------------------------------------
		void NotImplemented() 
		{ 
			throw NotImplementedException(repo); 
		}

	protected:

		void *oldVft;
		void (*funcs[VIRT_FUNC_LIMIT])();
		MockRepository *repo;

	public:

		int funcMap[VIRT_FUNC_LIMIT];

		//--------------------------------------------------------------------------------
		mock( MockRepository* repo ) : repo(repo)
		{
			for (int i = 0; i < VIRT_FUNC_LIMIT; i++) 
			{
				funcs[i] = nsCompiler::CCompiler::GetNonVirtualMemberFunctionAddress<void (*)()>(&mock<T>::NotImplemented);
				funcMap[i] = -1;
			}
			memset(remaining, 0, sizeof(remaining));
			oldVft = base_mock::rewriteVft(funcs);
		}

		//--------------------------------------------------------------------------------
		int translateX(int x) 
		{
			for (int i = 0; i < VIRT_FUNC_LIMIT; i++) 
			{
				if (funcMap[i] == x) return i;
			}
			return -1;
		}
	};

	//--------------------------------------------------------------------------------
	template <class T>
	class classMock : public mock<T>
	{
		void *backupVft;

	public:

		//--------------------------------------------------------------------------------
		classMock( MockRepository* repo) : mock<T>(repo)
		{
			mock< T >::oldVft = base_mock::rewriteVft( (void *)mock< T >::funcs );
			new(this)T();
			backupVft = base_mock::rewriteVft( (void *)mock<T>::funcs );
		}

		//--------------------------------------------------------------------------------
		~classMock()
		{
			base_mock::rewriteVft( backupVft );
			((T *)this)->~T();
		}
	};

}//nsUnitTesting

#endif//_UNITTEST_MOCK_H_
