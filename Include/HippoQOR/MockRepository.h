//MockRepository.h

//Mock repository

#ifndef _UNITTESTING_MOCKREPO_H_
#define _UNITTESTING_MOCKREPO_H_

#ifdef	__CQOR_OPTIMIZEINCLUDE
#pragma __CQOR_OPTIMIZEINCLUDE
#endif//__CQOR_OPTIMIZEINCLUDE

#include <list>
#include "HippoQOR/Call.h"
#include "HippoQOR/base_mock.h"
#include "HippoQOR/Mock.h"
#include "HippoQOR/FunctionIndex.h"
#include "HippoQOR/mock_funcs.h"

#ifdef _MSC_VER
#	define OnCall(obj, func) RegisterExpect_<__COUNTER__, nsUnitTesting::DontCare>(obj, &func, #func, __FILE__, __LINE__)
#	define ExpectCall(obj, func) RegisterExpect_<__COUNTER__, nsUnitTesting::Once>(obj, &func, #func, __FILE__, __LINE__)
#	define NeverCall(obj, func) RegisterExpect_<__COUNTER__, nsUnitTesting::Never>(obj, &func, #func, __FILE__, __LINE__)
#	define OnCallOverload(obj, func) RegisterExpect_<__COUNTER__, nsUnitTesting::DontCare>(obj, func, #func, __FILE__, __LINE__)
#	define ExpectCallOverload(obj, func) RegisterExpect_<__COUNTER__, nsUnitTesting::Once>(obj, func, #func, __FILE__, __LINE__)
#	define NeverCallOverload(obj, func) RegisterExpect_<__COUNTER__, nsUnitTesting::Never>(obj, func, #func, __FILE__, __LINE__)
#else
#	define OnCall(obj, func) RegisterExpect_<__LINE__, nsUnitTesting::DontCare>(obj, &func, #func, __FILE__, __LINE__)
#	define ExpectCall(obj, func) RegisterExpect_<__LINE__, nsUnitTesting::Once>(obj, &func, #func, __FILE__, __LINE__)
#	define NeverCall(obj, func) RegisterExpect_<__LINE__, nsUnitTesting::Never>(obj, &func, #func, __FILE__, __LINE__)
#	define OnCallOverload(obj, func) RegisterExpect_<__LINE__, nsUnitTesting::DontCare>(obj, func, #func, __FILE__, __LINE__)
#	define ExpectCallOverload(obj, func) RegisterExpect_<__LINE__, nsUnitTesting::Once>(obj, func, #func, __FILE__, __LINE__)
#	define NeverCallOverload(obj, func) RegisterExpect_<__LINE__, nsUnitTesting::Never>(obj, func, #func, __FILE__, __LINE__)
#endif
#undef I

//--------------------------------------------------------------------------------
namespace nsUnitTesting
{

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __HIPPO ) MockRepository 
	{
	private:
	
		friend __QOR_INTERFACE( __HIPPO ) inline std::ostream &operator<<(std::ostream &os, const MockRepository &repo);

		std::list<base_mock *> mocks;
		std::list<Call *> neverCalls;
		std::list<Call *> expectations;
		std::list<Call *> optionals;

	public:

		bool autoExpect;
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z>
		TCall<Y> &RegisterExpect_(Z2 *mck, Y (Z::*func)(), const char *funcName, const char *fileName, unsigned long lineNo);
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A>
		TCall<Y,A> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A), const char *funcName, const char *fileName, unsigned long lineNo);
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B>
		TCall<Y,A,B> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B), const char *funcName, const char *fileName, unsigned long lineNo);
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C>
		TCall<Y,A,B,C> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C), const char *funcName, const char *fileName, unsigned long lineNo);
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D>
		TCall<Y,A,B,C,D> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D), const char *funcName, const char *fileName, unsigned long lineNo);
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E>
		TCall<Y,A,B,C,D,E> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E), const char *funcName, const char *fileName, unsigned long lineNo);
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F>
		TCall<Y,A,B,C,D,E,F> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F), const char *funcName, const char *fileName, unsigned long lineNo);
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F, typename G>
		TCall<Y,A,B,C,D,E,F,G> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G), const char *funcName, const char *fileName, unsigned long lineNo);
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H>
		TCall<Y,A,B,C,D,E,F,G,H> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H), const char *funcName, const char *fileName, unsigned long lineNo);
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I>
		TCall<Y,A,B,C,D,E,F,G,H,I> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I), const char *funcName, const char *fileName, unsigned long lineNo);
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J>
		TCall<Y,A,B,C,D,E,F,G,H,I,J> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J), const char *funcName, const char *fileName, unsigned long lineNo);
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K), const char *funcName, const char *fileName, unsigned long lineNo);
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L), const char *funcName, const char *fileName, unsigned long lineNo);
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L, typename M>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M), const char *funcName, const char *fileName, unsigned long lineNo);
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L,
				  typename M, typename N>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M,N), const char *funcName, const char *fileName, unsigned long lineNo);
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L,
				  typename M, typename N, typename O>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O), const char *funcName, const char *fileName, unsigned long lineNo);
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L,
				  typename M, typename N, typename O, typename P>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P), const char *funcName, const char *fileName, unsigned long lineNo);

		//GCC 3.x doesn't seem to understand overloading on const or non-const member function. Volatile appears to work though.
#if !defined(__GNUC__) || __GNUC__ > 3

		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z>
		TCall<Y> &RegisterExpect_(Z2 *mck, Y (Z::*func)() volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)())(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A>
		TCall<Y,A> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A) volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B>
		TCall<Y,A,B> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B) volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C>
		TCall<Y,A,B,C> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C) volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D>
		TCall<Y,A,B,C,D> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D) volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E>
		TCall<Y,A,B,C,D,E> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E) volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F>
		TCall<Y,A,B,C,D,E,F> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F) volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G>
		TCall<Y,A,B,C,D,E,F,G> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G) volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H>
		TCall<Y,A,B,C,D,E,F,G,H> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H) volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I>
		TCall<Y,A,B,C,D,E,F,G,H,I> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I) volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J>
		TCall<Y,A,B,C,D,E,F,G,H,I,J> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J) volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K) volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J,K))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L) volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J,K,L))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L,
				  typename M>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M) volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J,K,L,M))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L,
				  typename M, typename N>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M,N) volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J,K,L,M,N))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L,
				  typename M, typename N, typename O>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L,
				  typename M, typename N, typename O, typename P>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P))(func), funcName, fileName, lineNo); }

		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z>
		TCall<Y> &RegisterExpect_(Z2 *mck, Y (Z::*func)() const volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)())(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A>
		TCall<Y,A> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A) const volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B>
		TCall<Y,A,B> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B) const volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C>
		TCall<Y,A,B,C> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C) const volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D>
		TCall<Y,A,B,C,D> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D) const volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E>
		TCall<Y,A,B,C,D,E> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E) const volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F>
		TCall<Y,A,B,C,D,E,F> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F) const volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G>
		TCall<Y,A,B,C,D,E,F,G> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G) const volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H>
		TCall<Y,A,B,C,D,E,F,G,H> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H) const volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I>
		TCall<Y,A,B,C,D,E,F,G,H,I> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I) const volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J>
		TCall<Y,A,B,C,D,E,F,G,H,I,J> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J) const volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K) const volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J,K))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L) const volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J,K,L))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L,
				  typename M>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M) const volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J,K,L,M))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L,
				  typename M, typename N>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M,N) const volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J,K,L,M,N))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L,
				  typename M, typename N, typename O>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) const volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L,
				  typename M, typename N, typename O, typename P>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) const volatile, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P))(func), funcName, fileName, lineNo); }

		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z>
		TCall<Y> &RegisterExpect_(Z2 *mck, Y (Z::*func)() const, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)())(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A>
		TCall<Y,A> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A) const, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B>
		TCall<Y,A,B> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B) const, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C>
		TCall<Y,A,B,C> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C) const, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D>
		TCall<Y,A,B,C,D> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D) const, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E>
		TCall<Y,A,B,C,D,E> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E) const, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F>
		TCall<Y,A,B,C,D,E,F> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F) const, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G>
		TCall<Y,A,B,C,D,E,F,G> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G) const, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H>
		TCall<Y,A,B,C,D,E,F,G,H> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H) const, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I>
		TCall<Y,A,B,C,D,E,F,G,H,I> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I) const, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J>
		TCall<Y,A,B,C,D,E,F,G,H,I,J> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J) const, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J))(func), funcName, fileName, lineNo); }
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K) const, const char *funcName, const char *fileName, unsigned long lineNo) { return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J,K))(func), funcName, fileName, lineNo); }

		//--------------------------------------------------------------------------------
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L) const, const char *funcName, const char *fileName, unsigned long lineNo) 
		{ 
			return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J,K,L))(func), funcName, fileName, lineNo); 
		}

		//--------------------------------------------------------------------------------
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L,
				  typename M>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M) const, const char *funcName, const char *fileName, unsigned long lineNo) 
		{ 
			return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J,K,L,M))(func), funcName, fileName, lineNo); 
		}

		//--------------------------------------------------------------------------------
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L,
				  typename M, typename N>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M,N) const, const char *funcName, const char *fileName, unsigned long lineNo) 
		{ 
			return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J,K,L,M,N))(func), funcName, fileName, lineNo); 
		}

		//--------------------------------------------------------------------------------
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L,
				  typename M, typename N, typename O>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) const, const char *funcName, const char *fileName, unsigned long lineNo) 
		{ 
			return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O))(func), funcName, fileName, lineNo); 
		}
		
		//--------------------------------------------------------------------------------
		template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, 
				  typename A, typename B, typename C, typename D, 
				  typename E, typename F, typename G, typename H,
				  typename I, typename J, typename K, typename L,
				  typename M, typename N, typename O, typename P>
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> &RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) const, const char *funcName, const char *fileName, unsigned long lineNo) 
		{ 
			return RegisterExpect_<X,expect>(mck, (Y(Z::*)(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P))(func), funcName, fileName, lineNo); 
		}
#endif

		template <typename Z> void BasicRegisterExpect(mock<Z> *zMock, int funcIndex, void (base_mock::*func)(), int X);
		template <typename Z> Z DoExpectation(base_mock *mock, int funcno, const base_tuple &tuple);

		void DoVoidExpectation(base_mock *mock, int funcno, const base_tuple &tuple);
		MockRepository();
		~MockRepository();
		void reset() ;
		void VerifyAll();

		template <typename base> base *InterfaceMock();
		template <typename base> base *ClassMock();
	};

	//--------------------------------------------------------------------------------
	template< typename Z >
	void MockRepository::BasicRegisterExpect( mock< Z >* zMock, int funcIndex, void (base_mock::*func)(), int X )
	{
		if (zMock->funcMap[funcIndex] == -1)
		{
			zMock->funcs[funcIndex] = nsCompiler::CCompiler::GetNonVirtualMemberFunctionAddress<void (*)()>(func);
			zMock->funcMap[funcIndex] = X;
		}
	}

	//--------------------------------------------------------------------------------
	// Mock repository implementation
	template< int X, RegistrationType expect, typename Z2, typename Y, typename Z >
	TCall< Y >& MockRepository::RegisterExpect_( Z2* mck, Y (Z::*func)(), const char* funcName, const char* fileName, unsigned long lineNo ) 
	{
		int funcIndex = GetFunctionIndex( func );
		Y (mockFuncs<Z2, Y>::*mfp)();
		mfp = &mockFuncs<Z2, Y>::template expectation0<X>;
		BasicRegisterExpect( reinterpret_cast< mock<Z2>* >( mck ), funcIndex, reinterpret_cast< void (base_mock::*)() >( mfp ), X );
		TCall<Y> *call = new TCall<Y>(expect, reinterpret_cast<base_mock *>(mck), funcIndex, lineNo, funcName, fileName);
		switch(expect)
		{
		case Never: neverCalls.push_back(call); break;
		case DontCare: optionals.push_back(call); break;
		case Once:
			if (autoExpect && expectations.size() > 0) 
			{
				call->previousCalls.push_back(expectations.back());
			}
			expectations.push_back(call);
			break;
		}
		return *call;
	}

	//--------------------------------------------------------------------------------
	template< int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A >
	TCall< Y, A >& MockRepository::RegisterExpect_( Z2* mck, Y (Z::*func)(A), const char* funcName, const char* fileName, unsigned long lineNo ) 
	{
		int funcIndex = GetFunctionIndex(func);
		Y (mockFuncs<Z2, Y>::*mfp)(A);
		mfp = &mockFuncs<Z2, Y>::template expectation1<X,A>;
		BasicRegisterExpect(reinterpret_cast<mock<Z2> *>(mck), 
							funcIndex,
							reinterpret_cast<void (base_mock::*)()>(mfp),X);
		TCall<Y,A> *call = new TCall<Y,A>(expect, reinterpret_cast<base_mock *>(mck), funcIndex, lineNo, funcName, fileName);
		switch(expect)
		{
		case Never: neverCalls.push_back(call); break;
		case DontCare: optionals.push_back(call); break;
		case Once:
			if (autoExpect && expectations.size() > 0) 
			{
				call->previousCalls.push_back(expectations.back());
			}
			expectations.push_back(call);
			break;
		}
		return *call;
	}

	//--------------------------------------------------------------------------------
	template< int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B>
	TCall<Y,A,B> &MockRepository::RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B), const char *funcName, const char *fileName, unsigned long lineNo) 
	{
		int funcIndex = GetFunctionIndex(func);
		Y (mockFuncs<Z2, Y>::*mfp)(A,B);
		mfp = &mockFuncs<Z2, Y>::template expectation2<X,A,B>;
		BasicRegisterExpect(reinterpret_cast<mock<Z2> *>(mck), 
							funcIndex,
							reinterpret_cast<void (base_mock::*)()>(mfp),X);
		TCall<Y,A,B> *call = new TCall<Y,A,B>(expect, reinterpret_cast<base_mock *>(mck), funcIndex, lineNo, funcName, fileName);
		switch(expect)
		{
		case Never: neverCalls.push_back(call); break;
		case DontCare: optionals.push_back(call); break;
		case Once:
			if (autoExpect && expectations.size() > 0) 
			{
				call->previousCalls.push_back(expectations.back());
			}
			expectations.push_back(call);
			break;
		}
		return *call;
	}

	//--------------------------------------------------------------------------------
	template< int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C>
	TCall<Y,A,B,C> &MockRepository::RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C), const char *funcName, const char *fileName, unsigned long lineNo) 
	{
		int funcIndex = GetFunctionIndex(func);
		Y (mockFuncs<Z2, Y>::*mfp)(A,B,C);
		mfp = &mockFuncs<Z2, Y>::template expectation3<X,A,B,C>;
		BasicRegisterExpect(reinterpret_cast<mock<Z2> *>(mck), 
							funcIndex,
							reinterpret_cast<void (base_mock::*)()>(mfp),X);
		TCall<Y,A,B,C> *call = new TCall<Y,A,B,C>(expect, reinterpret_cast<base_mock *>(mck), funcIndex, lineNo, funcName, fileName);
		switch(expect)
		{
		case Never: neverCalls.push_back(call); break;
		case DontCare: optionals.push_back(call); break;
		case Once:
			if (autoExpect && expectations.size() > 0) 
			{
				call->previousCalls.push_back(expectations.back());
			}
			expectations.push_back(call);
			break;
		}
		return *call;
	}

	//--------------------------------------------------------------------------------
	template<int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D>
	TCall<Y,A,B,C,D> &MockRepository::RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D), const char *funcName, const char *fileName, unsigned long lineNo) 
	{
		int funcIndex = GetFunctionIndex(func);
		Y (mockFuncs<Z2, Y>::*mfp)(A,B,C,D);
		mfp = &mockFuncs<Z2, Y>::template expectation4<X,A,B,C,D>;
		BasicRegisterExpect(reinterpret_cast<mock<Z2> *>(mck), 
							funcIndex,
							reinterpret_cast<void (base_mock::*)()>(mfp),X);
		TCall<Y,A,B,C,D> *call = new TCall<Y,A,B,C,D>(expect, reinterpret_cast<base_mock *>(mck), funcIndex, lineNo, funcName, fileName);
		switch(expect)
		{
		case Never: neverCalls.push_back(call); break;
		case DontCare: optionals.push_back(call); break;
		case Once:
			if (autoExpect && expectations.size() > 0) 
			{
				call->previousCalls.push_back(expectations.back());
			}
			expectations.push_back(call);
			break;
		}
		return *call;
	}

	//--------------------------------------------------------------------------------
	template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E>
	TCall<Y,A,B,C,D,E> &MockRepository::RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E), const char *funcName, const char *fileName, unsigned long lineNo) 
	{
		int funcIndex = GetFunctionIndex(func);
		Y (mockFuncs<Z2, Y>::*mfp)(A,B,C,D,E);
		mfp = &mockFuncs<Z2, Y>::template expectation5<X,A,B,C,D,E>;
		BasicRegisterExpect(reinterpret_cast<mock<Z2> *>(mck), 
							funcIndex,
							reinterpret_cast<void (base_mock::*)()>(mfp),X);
		TCall<Y,A,B,C,D,E> *call = new TCall<Y,A,B,C,D,E>(expect, reinterpret_cast<base_mock *>(mck), funcIndex, lineNo, funcName, fileName);
		switch(expect)
		{
		case Never: neverCalls.push_back(call); break;
		case DontCare: optionals.push_back(call); break;
		case Once:
			if (autoExpect && expectations.size() > 0) 
			{
				call->previousCalls.push_back(expectations.back());
			}
			expectations.push_back(call);
			break;
		}
		return *call;
	}

	//--------------------------------------------------------------------------------
	template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F>
	TCall<Y,A,B,C,D,E,F> &MockRepository::RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F), const char *funcName, const char *fileName, unsigned long lineNo) 
	{
		int funcIndex = GetFunctionIndex(func);
		Y (mockFuncs<Z2, Y>::*mfp)(A,B,C,D,E,F);
		mfp = &mockFuncs<Z2, Y>::template expectation6<X,A,B,C,D,E,F>;
		BasicRegisterExpect(reinterpret_cast<mock<Z2> *>(mck), 
							funcIndex,
							reinterpret_cast<void (base_mock::*)()>(mfp),X);
		TCall<Y,A,B,C,D,E,F> *call = new TCall<Y,A,B,C,D,E,F>(expect, reinterpret_cast<base_mock *>(mck), funcIndex, lineNo, funcName, fileName);
		switch(expect)
		{
		case Never: neverCalls.push_back(call); break;
		case DontCare: optionals.push_back(call); break;
		case Once:
			if (autoExpect && expectations.size() > 0) 
			{
				call->previousCalls.push_back(expectations.back());
			}
			expectations.push_back(call);
			break;
		}
		return *call;
	}

	//--------------------------------------------------------------------------------
	template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F, typename G>
	TCall<Y,A,B,C,D,E,F,G> &MockRepository::RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G), const char *funcName, const char *fileName, unsigned long lineNo) 
	{
		int funcIndex = GetFunctionIndex(func);
		Y (mockFuncs<Z2, Y>::*mfp)(A,B,C,D,E,F,G);
		mfp = &mockFuncs<Z2, Y>::template expectation7<X,A,B,C,D,E,F,G>;
		BasicRegisterExpect(reinterpret_cast<mock<Z2> *>(mck), 
							funcIndex,
							reinterpret_cast<void (base_mock::*)()>(mfp),X);
		TCall<Y,A,B,C,D,E,F,G> *call = new TCall<Y,A,B,C,D,E,F,G>(expect, reinterpret_cast<base_mock *>(mck), funcIndex, lineNo, funcName, fileName);
		switch(expect)
		{
		case Never: neverCalls.push_back(call); break;
		case DontCare: optionals.push_back(call); break;
		case Once:
			if (autoExpect && expectations.size() > 0) 
			{
				call->previousCalls.push_back(expectations.back());
			}
			expectations.push_back(call);
			break;
		}
		return *call;
	}

	//--------------------------------------------------------------------------------
	template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H>
	TCall<Y,A,B,C,D,E,F,G,H> &MockRepository::RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H), const char *funcName, const char *fileName, unsigned long lineNo) 
	{
		int funcIndex = GetFunctionIndex(func);
		Y (mockFuncs<Z2, Y>::*mfp)(A,B,C,D,E,F,G,H);
		mfp = &mockFuncs<Z2, Y>::template expectation8<X,A,B,C,D,E,F,G,H>;
		BasicRegisterExpect(reinterpret_cast<mock<Z2> *>(mck), 
							funcIndex,
							reinterpret_cast<void (base_mock::*)()>(mfp),X);
		TCall<Y,A,B,C,D,E,F,G,H> *call = new TCall<Y,A,B,C,D,E,F,G,H>(expect, reinterpret_cast<base_mock *>(mck), funcIndex, lineNo, funcName, fileName);
		switch(expect)
		{
		case Never: neverCalls.push_back(call); break;
		case DontCare: optionals.push_back(call); break;
		case Once:
			if (autoExpect && expectations.size() > 0) 
			{
				call->previousCalls.push_back(expectations.back());
			}
			expectations.push_back(call);
			break;
		}
		return *call;
	}

	//--------------------------------------------------------------------------------
	template<int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I >
	TCall<Y,A,B,C,D,E,F,G,H,I> &MockRepository::RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I), const char *funcName, const char *fileName, unsigned long lineNo) 
	{
		int funcIndex = GetFunctionIndex(func);
		Y (mockFuncs<Z2, Y>::*mfp)(A,B,C,D,E,F,G,H,I);
		mfp = &mockFuncs<Z2, Y>::template expectation9<X,A,B,C,D,E,F,G,H,I>;
		BasicRegisterExpect(reinterpret_cast<mock<Z2> *>(mck), 
							funcIndex,
							reinterpret_cast<void (base_mock::*)()>(mfp),X);
		TCall<Y,A,B,C,D,E,F,G,H,I> *call = new TCall<Y,A,B,C,D,E,F,G,H,I>(expect, reinterpret_cast<base_mock *>(mck), funcIndex, lineNo, funcName, fileName);
		switch(expect)
		{
		case Never: neverCalls.push_back(call); break;
		case DontCare: optionals.push_back(call); break;
		case Once:
			if (autoExpect && expectations.size() > 0) 
			{
				call->previousCalls.push_back(expectations.back());
			}
			expectations.push_back(call);
			break;
		}
		return *call;
	}

	//--------------------------------------------------------------------------------
	template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J>
	TCall<Y,A,B,C,D,E,F,G,H,I,J> &MockRepository::RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J), const char *funcName, const char *fileName, unsigned long lineNo) 
	{
		int funcIndex = GetFunctionIndex(func);
		Y (mockFuncs<Z2, Y>::*mfp)(A,B,C,D,E,F,G,H,I,J);
		mfp = &mockFuncs<Z2, Y>::template expectation10<X,A,B,C,D,E,F,G,H,I,J>;
		BasicRegisterExpect(reinterpret_cast<mock<Z2> *>(mck), 
							funcIndex,
							reinterpret_cast<void (base_mock::*)()>(mfp),X);
		TCall<Y,A,B,C,D,E,F,G,H,I,J> *call = new TCall<Y,A,B,C,D,E,F,G,H,I,J>(expect, reinterpret_cast<base_mock *>(mck), funcIndex, lineNo, funcName, fileName);
		switch(expect)
		{
		case Never: neverCalls.push_back(call); break;
		case DontCare: optionals.push_back(call); break;
		case Once:
			if (autoExpect && expectations.size() > 0) 
			{
				call->previousCalls.push_back(expectations.back());
			}
			expectations.push_back(call);
			break;
		}
		return *call;
	}

	//--------------------------------------------------------------------------------
	template <int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K>
	TCall<Y,A,B,C,D,E,F,G,H,I,J,K> &MockRepository::RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K), const char *funcName, const char *fileName, unsigned long lineNo) 
	{
		int funcIndex = GetFunctionIndex(func);
		Y (mockFuncs<Z2, Y>::*mfp)(A,B,C,D,E,F,G,H,I,J,K);
		mfp = &mockFuncs<Z2, Y>::template expectation11<X,A,B,C,D,E,F,G,H,I,J,K>;
		BasicRegisterExpect(reinterpret_cast<mock<Z2> *>(mck), 
							funcIndex,
							reinterpret_cast<void (base_mock::*)()>(mfp),X);
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K> *call = new TCall<Y,A,B,C,D,E,F,G,H,I,J,K>(expect, reinterpret_cast<base_mock *>(mck), funcIndex, lineNo, funcName, fileName);
		switch(expect)
		{
		case Never: neverCalls.push_back(call); break;
		case DontCare: optionals.push_back(call); break;
		case Once:
			if (autoExpect && expectations.size() > 0) 
			{
				call->previousCalls.push_back(expectations.back());
			}
			expectations.push_back(call);
			break;
		}
		return *call;
	}

	//--------------------------------------------------------------------------------
	template< int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L >
	TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L> &MockRepository::RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L), const char *funcName, const char *fileName, unsigned long lineNo) 
	{
		int funcIndex = GetFunctionIndex(func);
		Y (mockFuncs<Z2, Y>::*mfp)(A,B,C,D,E,F,G,H,I,J,K,L);
		mfp = &mockFuncs<Z2, Y>::template expectation12<X,A,B,C,D,E,F,G,H,I,J,K,L>;
		BasicRegisterExpect(reinterpret_cast<mock<Z2> *>(mck), 
							funcIndex,
							reinterpret_cast<void (base_mock::*)()>(mfp),X);
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L> *call = new TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L>(expect, reinterpret_cast<base_mock *>(mck), funcIndex, lineNo, funcName, fileName);
		switch(expect)
		{
		case Never: neverCalls.push_back(call); break;
		case DontCare: optionals.push_back(call); break;
		case Once:
			if (autoExpect && expectations.size() > 0) 
			{
				call->previousCalls.push_back(expectations.back());
			}
			expectations.push_back(call);
			break;
		}
		return *call;
	}

	//--------------------------------------------------------------------------------
	template< int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L, typename M >
	TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M> &MockRepository::RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M), const char *funcName, const char *fileName, unsigned long lineNo) 
	{
		int funcIndex = GetFunctionIndex(func);
		Y (mockFuncs<Z2, Y>::*mfp)(A,B,C,D,E,F,G,H,I,J,K,L,M);
		mfp = &mockFuncs<Z2, Y>::template expectation13<X,A,B,C,D,E,F,G,H,I,J,K,L,M>;
		BasicRegisterExpect(reinterpret_cast<mock<Z2> *>(mck), 
							funcIndex,
							reinterpret_cast<void (base_mock::*)()>(mfp),X);
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M> *call = new TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M>(expect, reinterpret_cast<base_mock *>(mck), funcIndex, lineNo, funcName, fileName);
		switch(expect)
		{
		case Never: neverCalls.push_back(call); break;
		case DontCare: optionals.push_back(call); break;
		case Once:
			if (autoExpect && expectations.size() > 0) 
			{
				call->previousCalls.push_back(expectations.back());
			}
			expectations.push_back(call);
			break;
		}
		return *call;
	}

	//--------------------------------------------------------------------------------
	template< int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L, typename M, typename N >
	TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N> &MockRepository::RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M,N), const char *funcName, const char *fileName, unsigned long lineNo) 
	{
		int funcIndex = GetFunctionIndex(func);
		Y (mockFuncs<Z2, Y>::*mfp)(A,B,C,D,E,F,G,H,I,J,K,L,M,N);
		mfp = &mockFuncs<Z2, Y>::template expectation14<X,A,B,C,D,E,F,G,H,I,J,K,L,M,N>;
		BasicRegisterExpect(reinterpret_cast<mock<Z2> *>(mck), 
							funcIndex, 
							reinterpret_cast<void (base_mock::*)()>(mfp),X);
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N> *call = new TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N>(expect, reinterpret_cast<base_mock *>(mck), funcIndex, lineNo, funcName, fileName);
		switch(expect)
		{
		case Never: neverCalls.push_back(call); break;
		case DontCare: optionals.push_back(call); break;
		case Once:
			if (autoExpect && expectations.size() > 0) 
			{
				call->previousCalls.push_back(expectations.back());
			}
			expectations.push_back(call);
			break;
		}
		return *call;
	}

	//--------------------------------------------------------------------------------
	template< int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L, typename M, typename N, typename O >
	TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O> &MockRepository::RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O), const char *funcName, const char *fileName, unsigned long lineNo) 
	{
		int funcIndex = GetFunctionIndex(func);
		Y (mockFuncs<Z2, Y>::*mfp)(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O);
		mfp = &mockFuncs<Z2, Y>::template expectation15<X,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O>;
		BasicRegisterExpect(reinterpret_cast<mock<Z2> *>(mck), 
							funcIndex, 
							reinterpret_cast<void (base_mock::*)()>(mfp),X);
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O> *call = new TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O>(expect, reinterpret_cast<base_mock *>(mck), funcIndex, lineNo, funcName, fileName);
		switch(expect)
		{
		case Never: neverCalls.push_back(call); break;
		case DontCare: optionals.push_back(call); break;
		case Once:
			if (autoExpect && expectations.size() > 0) 
			{
				call->previousCalls.push_back(expectations.back());
			}
			expectations.push_back(call);
			break;
		}
		return *call;
	}

	//--------------------------------------------------------------------------------
	template< int X, RegistrationType expect, typename Z2, typename Y, typename Z, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L, typename M, typename N, typename O, typename P >
	TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> &MockRepository::RegisterExpect_(Z2 *mck, Y (Z::*func)(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P), const char *funcName, const char *fileName, unsigned long lineNo) 
	{
		int funcIndex = GetFunctionIndex(func);
		Y (mockFuncs<Z2, Y>::*mfp)(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P);
		mfp = &mockFuncs<Z2, Y>::template expectation16<X,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P>;
		BasicRegisterExpect(reinterpret_cast<mock<Z2> *>(mck), 
							funcIndex,
							reinterpret_cast<void (base_mock::*)()>(mfp),X);
		TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> *call = new TCall<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P>(expect, reinterpret_cast<base_mock *>(mck), funcIndex, lineNo, funcName, fileName);
		switch(expect)
		{
		case Never: neverCalls.push_back(call); break;
		case DontCare: optionals.push_back(call); break;
		case Once:
			if (autoExpect && expectations.size() > 0) 
			{
				call->previousCalls.push_back(expectations.back());
			}
			expectations.push_back(call);
			break;
		}
		return *call;
	}

	//--------------------------------------------------------------------------------
	template< typename Z > Z MockRepository::DoExpectation( base_mock* mock, int funcno, const base_tuple& tuple ) 
	{
		for (std::list<Call *>::iterator i = expectations.begin(); i != expectations.end(); ++i) 
		{
			Call *call = *i;
			if (call->mock == mock &&
				call->funcIndex == funcno &&
				call->matchesArgs(tuple) &&
				!call->satisfied)
			{
				bool allSatisfy = true;
				for (std::list<Call *>::iterator callsBefore = call->previousCalls.begin();
					callsBefore != call->previousCalls.end(); ++callsBefore)
				{
					if (!(*callsBefore)->satisfied)
					{
						allSatisfy = false;
					}
				}
				if (!allSatisfy) continue;

				call->satisfied = true;

				if (call->eHolder)
					call->eHolder->rethrow();

    			if (call->retVal)
					return ((ReturnValueWrapper<Z> *)call->retVal)->rv;

    			if (call->functor != NULL)
    				return (*(TupleInvocable<Z> *)(call->functor))(tuple);

			throw NoResultSetUpException(call->getArgs(), call->funcName);
			}
		}
		for (std::list<Call *>::iterator i = neverCalls.begin(); i != neverCalls.end(); ++i) 
		{
			Call *call = *i;
			if (call->mock == mock &&
				call->funcIndex == funcno &&
				call->matchesArgs(tuple))
			{
				bool allSatisfy = true;
				for (std::list<Call *>::iterator callsBefore = call->previousCalls.begin();
					callsBefore != call->previousCalls.end(); ++callsBefore)
				{
					if (!(*callsBefore)->satisfied)
					{
						allSatisfy = false;
					}
				}
				if (!allSatisfy) continue;

				call->satisfied = true;

				throw ExpectationException(this, call->getArgs(), call->funcName);
			}
		}
		for (std::list<Call *>::iterator i = optionals.begin(); i != optionals.end(); ++i) 
		{
			Call *call = *i;
			if (call->mock == mock &&
				call->funcIndex == funcno &&
				call->matchesArgs(tuple))
			{
				bool allSatisfy = true;
				for (std::list<Call *>::iterator callsBefore = call->previousCalls.begin();
					callsBefore != call->previousCalls.end(); ++callsBefore)
				{
					if (!(*callsBefore)->satisfied)
					{
						allSatisfy = false;
					}
				}
				if (!allSatisfy) continue;

				call->satisfied = true;
			
				if (call->eHolder)
					call->eHolder->rethrow();

    			if (call->retVal)
					return ((ReturnValueWrapper<Z> *)call->retVal)->rv;
        
        		if (call->functor != NULL)
        			return (*(TupleInvocable<Z> *)(call->functor))(tuple);
        
				throw NoResultSetUpException(call->getArgs(), call->funcName);
			}
		}
		const char *funcName = NULL;
		for (std::list<Call *>::iterator i = expectations.begin(); i != expectations.end() && !funcName; ++i) 
		{
			Call *call = *i;
			if (call->mock == mock &&
				call->funcIndex == funcno)
				funcName = call->funcName;
		}
		for (std::list<Call *>::iterator i = neverCalls.begin(); i != neverCalls.end() && !funcName; ++i) 
		{
			Call *call = *i;
			if (call->mock == mock &&
				call->funcIndex == funcno)
			funcName = call->funcName;
		}
		for (std::list<Call *>::iterator i = optionals.begin(); i != optionals.end() && !funcName; ++i) 
		{
			Call *call = *i;
			if (call->mock == mock &&
				call->funcIndex == funcno)
			funcName = call->funcName;
		}
		throw ExpectationException(this, &tuple, funcName);
	}

	//--------------------------------------------------------------------------------
	template< typename base > base* MockRepository::InterfaceMock() 
	{
		mock<base> *m = new mock<base>(this);
		mocks.push_back(m);
		return reinterpret_cast<base *>(m);
	}

	//--------------------------------------------------------------------------------
	template< typename base > base* MockRepository::ClassMock() 
	{
		classMock<base> *m = new classMock<base>(this);
		mocks.push_back(m);
		return reinterpret_cast<base *>(m);
	}

	__QOR_INTERFACE( __HIPPO ) inline std::ostream& operator << ( std::ostream& os, const Call& call );
	__QOR_INTERFACE( __HIPPO ) inline std::ostream& operator << ( std::ostream& os, const MockRepository& repo );
	//inline void BaseException::setException( const char* description, MockRepository* repo );

}//nsUnitTesting

#endif//_UNITTESTING_MOCKREPO_H_
