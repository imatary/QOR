//Call.h

//Call wrapper

#ifndef _UNITTEST_CALL_H_
#define _UNITTEST_CALL_H_

#ifdef	__CQOR_OPTIMIZEINCLUDE
#pragma __CQOR_OPTIMIZEINCLUDE
#endif//__CQOR_OPTIMIZEINCLUDE

#include <list>
#include "HippoQOR/base_tuple.h"
#include "HippoQOR/base_mock.h"
#include "HippoQOR/TestExceptions.h"
#include "HippoQOR/do_wrapper.h"

//--------------------------------------------------------------------------------
namespace nsUnitTesting
{
	//--------------------------------------------------------------------------------
	enum RegistrationType 
	{
		Never,
		Once,
		DontCare
	};

	//--------------------------------------------------------------------------------
	class ReturnValueHolder 
	{
	public:
		virtual ~ReturnValueHolder();
	};

	//--------------------------------------------------------------------------------
	template <class T>
	class ReturnValueWrapper : public ReturnValueHolder 
	{
	public:

		//--------------------------------------------------------------------------------
		typename no_cref<T>::type rv;
		ReturnValueWrapper(T rv) : rv(rv) 
		{
		}
	};

	//--------------------------------------------------------------------------------
	//Call wrapping
	class Call 
	{

	public:

		virtual bool matchesArgs(const base_tuple &tuple) = 0;
		ReturnValueHolder* retVal;
		ExceptionHolder* eHolder;
		base_mock* mock;
		VirtualDestructable* functor;
		int funcIndex;
		std::list< Call* > previousCalls;
		RegistrationType expectation;
		bool satisfied;
		int lineno;
		const char* funcName;
		const char* fileName;

	protected:

		Call( RegistrationType expectation, base_mock* mock, int funcIndex, int X, const char* funcName, const char* fileName );

	public:

		virtual const base_tuple *getArgs() const = 0;
		virtual ~Call();
	};

	__QOR_INTERFACE( __HIPPO ) std::ostream& operator << ( std::ostream &os, const Call &call );

	//--------------------------------------------------------------------------------
	template< typename Y, typename A = NullType, typename B = NullType, typename C = NullType, typename D = NullType, typename E = NullType, typename F = NullType, typename G = NullType, typename H = NullType, typename I = NullType, typename J = NullType, typename K = NullType, typename L = NullType, typename M = NullType, typename N = NullType, typename O = NullType, typename P = NullType >
	class TCall : public Call 
	{
	private:

		tuple< A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P >* args;

	public:
	
		//--------------------------------------------------------------------------------
		const base_tuple *getArgs() const 
		{ 
			return args; 
		}
		
		//--------------------------------------------------------------------------------
		TCall( RegistrationType expectation, base_mock* mock, int funcIndex, int X, const char* funcName, const char* fileName ) : Call( expectation, mock, funcIndex, X, funcName, fileName ), args( 0 ) 
		{
		}

		//--------------------------------------------------------------------------------
		~TCall() 
		{
			delete args; 
		}

		//--------------------------------------------------------------------------------
		bool matchesArgs(const base_tuple &tupl) 
		{ 
			return !args || *args == reinterpret_cast<const tuple<A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> &>(tupl); 
		}

		//--------------------------------------------------------------------------------
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> &With(A a = A(), B b = B(), C c = C(), D d = D(), E e = E(), F f = F(), G g = G(), H h = H(), I i = I(), J j = J(), K k = K(), L l = L(), M m = M(), N n = N(), O o = O(), P p = P()) 
		{ 
			args = new tuple<A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P>(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p); 
			return *this; 
		}

		//--------------------------------------------------------------------------------
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> &After(Call &call) 
		{ 
			previousCalls.push_back(&call);
			return *this; 
		}

		//--------------------------------------------------------------------------------
		template <typename T>
		Call &Do(T &function) 
		{ 
			functor = new DoWrapper<T,Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P>(function); return *this; 
		}

		//--------------------------------------------------------------------------------
		Call &Return(Y obj) 
		{ 
			retVal = new ReturnValueWrapper<Y>(obj); return *this; 
		}

		//--------------------------------------------------------------------------------
		template <typename Ex>
		Call &Throw(Ex exception) 
		{ 
			eHolder = new ExceptionWrapper<Ex>(exception); return *this; 
		}

	};

	//--------------------------------------------------------------------------------
	template <typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L, typename M, typename N, typename O, typename P >
	class TCall< void,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> : public Call 
	{
	private:

		tuple<A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> *args;

	public:

		const base_tuple *getArgs() const 
		{ 
			return args; 
		}
			
		TCall(RegistrationType expectation, base_mock *mock, int funcIndex, int X, const char *funcName, const char *fileName) : Call(expectation, mock, funcIndex, X, funcName, fileName), args(0) 
		{
		}

		~TCall() 
		{ 
			delete args; 
		}

		bool matchesArgs(const base_tuple &tupl) 
		{ 
			return (!args) || (*args == reinterpret_cast<const tuple<A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> &>(tupl)); 
		}


		TCall<void,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> &With(A a = A(), B b = B(), C c = C(), D d = D(), E e = E(), F f = F(), G g = G(), H h = H(), I i = I(), J j = J(), K k = K(), L l = L(), M m = M(), N n = N(), O o = O(), P p = P()) 
		{ 
			args = new tuple<A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P>(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p); 
			return *this; 
		}

		TCall<void,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> &After(Call &call) 
		{ 
			previousCalls.push_back(&call);
			return *this; 
		}

		template <typename T>
		Call &Do(T &function) 
		{ 
			functor = new DoWrapper<T,void,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P>(function); return *this; 
		}

		template <typename Ex>
		Call &Throw(Ex exception) 
		{ 
			eHolder = new ExceptionWrapper<Ex>(exception); return *this; 
		}
	};

}//nsUnitTesting

#endif//_UNITTEST_CALL_H_
