//UnitTest.h

//Unit Test Base class

#ifndef _CODEQOR_UNITTEST_H_
#define _CODEQOR_UNITTEST_H_

#include "HippoQOR/UnitTestBase.h"
//#include "InterfaceItem.h"

#ifdef	__CQOR_OPTIMIZEINCLUDE
#pragma __CQOR_OPTIMIZEINCLUDE
#endif//__CQOR_OPTIMIZEINCLUDE

//--------------------------------------------------------------------------------
namespace nsUnitTesting
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __HIPPO ) CUnitTest : public CUnitTestCollection
	{
	public:

		//--------------------------------------------------------------------------------
		CUnitTest()
		{
			m_Item = this;
			UnitTests()->Append(m_Item);
		}

		//--------------------------------------------------------------------------------
		virtual ~CUnitTest(){}

		//--------------------------------------------------------------------------------
		virtual bool Test()
		{
			return false;
		}

	};
	/*
	//--------------------------------------------------------------------------------
	class CSubTest : public CUnitTestCollection
	{
	public:

		//--------------------------------------------------------------------------------
		CSubTest( CUnitTest& Parent )
		{
			m_Item = this;
			Parent.Append( m_Item );
		}

		//--------------------------------------------------------------------------------
		virtual bool Test()
		{
			return false;
		}

	private:

		CSubTest();//No default constructor
	};

	//--------------------------------------------------------------------------------
	template< class T, class TBase = CUnitTest >
	class CClassTest : public TBase
	{
	public:

		//--------------------------------------------------------------------------------
		virtual bool Test()
		{
			T* pT = TestInstance();
			bool bResult = Test( pT );
			ReleaseInstance( pT );
			return bResult;
		}

		//--------------------------------------------------------------------------------
		virtual bool Test( T* pT )
		{
			return false;
		}

		//--------------------------------------------------------------------------------
		virtual T* TestInstance( void )
		{
			return new T();
		}

		//--------------------------------------------------------------------------------
		virtual void ReleaseInstance( T* pT )
		{
			delete pT;
		}

		static CClassTest Test_Instance;
	};

	//------------------------------------------------------------------------------
	template< class T >
	class CMemberCall
	{
		public:

		typedef int( T::*Proc )( void );	//Default procedure pointer type

		//------------------------------------------------------------------------------
		template< typename ret > ret Call( T* pT, const Proc pProc ) const
		{
			typedef ret( T::*fPtr )( void );

			fPtr FP = reinterpret_cast< fPtr >( pProc );

			if( FP != 0 )
			{
				return (pT->*FP)();
			}

			//TODO: Raise an error

			ret R1;
			return R1;
		}
	};

	//--------------------------------------------------------------------------------
	template< class T, class TParamSet >
	class CMemberTest : public CSubTest
	{
	public:

		typedef typename TMemberPointer< T, TParamSet >::fp tfp;

		//--------------------------------------------------------------------------------
		CMemberTest( T* pT, CUnitTest& Parent, tfp pFunc ) : CSubTest( Parent )
		{
			m_pT = pT;
			m_Functor.Attach( m_pT, pFunc );
		}

		//--------------------------------------------------------------------------------		
		CInterfaceItem< T, TParamSet >& Functor()
		{			
			return m_Functor;
		}

	protected:		
		
		CInterfaceItem< T, TParamSet > m_Functor;
		T* m_pT;
	};
	*/
	//--------------------------------------------------------------------------------
	//No Errors can be returned
	namespace TestNoError
	{
		bool Test( ... );
	}

	//--------------------------------------------------------------------------------
	//Zero signifies error
	namespace TestErrorZero
	{
		bool Test( int i );
	}

	//--------------------------------------------------------------------------------
	//Non zero signifies error
	namespace TestErrorNonZero
	{
		bool Test( int i );
	}

	//--------------------------------------------------------------------------------
	//negative signifies error
	namespace TestErrorNegative
	{
		bool Test( int i );
	}

}//namespace nsUnitTesting


#endif//_CODEQOR_UNITTEST_H_
