//mock_funcs.h

#ifndef _UNITTEST_MOCK_FUNCS_H_
#define _UNITTEST_MOCK_FUNCS_H_

#include "Mock.h"

//------------------------------------------------------------------------------
namespace nsUnitTesting
{
	// mock function providers

	//------------------------------------------------------------------------------
	template< typename Z, typename Y >
	class mockFuncs : public mock<Z> 
	{

	private: 

		mockFuncs();

	public:

		//------------------------------------------------------------------------------
		template <int X>
		Y expectation0()
		{
			MockRepository *repo = mock<Z>::repo;
			return repo->template DoExpectation<Y>(this, mock<Z>::translateX(X), tuple<>());
		}

		//------------------------------------------------------------------------------
		template <int X, typename A>
		Y expectation1(A a)
		{
			MockRepository *repo = mock<Z>::repo;
			return repo->template DoExpectation<Y>(this, mock<Z>::translateX(X), tuple<A>(a));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B>
		Y expectation2(A a, B b)
		{
			MockRepository *repo = mock<Z>::repo;
			return repo->template DoExpectation<Y>(this, mock<Z>::translateX(X), tuple<A,B>(a,b));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C>
		Y expectation3(A a, B b, C c)
		{
			MockRepository *repo = mock<Z>::repo;
			return repo->template DoExpectation<Y>(this, mock<Z>::translateX(X), tuple<A,B,C>(a,b,c));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D>
		Y expectation4(A a, B b, C c, D d)
		{
			MockRepository *repo = mock<Z>::repo;
			return repo->template DoExpectation<Y>(this, mock<Z>::translateX(X), tuple<A,B,C,D>(a,b,c,d));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E>
		Y expectation5(A a, B b, C c, D d, E e)
		{
			MockRepository *repo = mock<Z>::repo;
			return repo->template DoExpectation<Y>(this, mock<Z>::translateX(X), tuple<A,B,C,D,E>(a,b,c,d,e));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F>
		Y expectation6(A a, B b, C c, D d, E e, F f)
		{
			MockRepository *repo = mock<Z>::repo;
			return repo->template DoExpectation<Y>(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F>(a,b,c,d,e,f));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G>
		Y expectation7(A a, B b, C c, D d, E e, F f, G g)
		{
			MockRepository *repo = mock<Z>::repo;
			return repo->template DoExpectation<Y>(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G>(a,b,c,d,e,f,g));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H>
		Y expectation8(A a, B b, C c, D d, E e, F f, G g, H h)
		{
			MockRepository *repo = mock<Z>::repo;
			return repo->template DoExpectation<Y>(this, mock<Z>::translateX(X), new tuple<A,B,C,D,E,F,G,H>(a,b,c,d,e,f,g,h));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I>
		Y expectation9(A a, B b, C c, D d, E e, F f, G g, H h, I i)
		{
			MockRepository *repo = mock<Z>::repo;
			return repo->template DoExpectation<Y>(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G,H,I>(a,b,c,d,e,f,g,h,i));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J>
		Y expectation10(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j)
		{
			MockRepository *repo = mock<Z>::repo;
			return repo->template DoExpectation<Y>(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G,H,I,J>(a,b,c,d,e,f,g,h,i,j));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K>
		Y expectation11(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k)
		{
			MockRepository *repo = mock<Z>::repo;
			return repo->template DoExpectation<Y>(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G,H,I,J,K>(a,b,c,d,e,f,g,h,i,j,k));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L>
		Y expectation12(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k, L l)
		{
			MockRepository *repo = mock<Z>::repo;
			return repo->template DoExpectation<Y>(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G,H,I,J,K,L>(a,b,c,d,e,f,g,h,i,j,k,l));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L, typename M>
		Y expectation13(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k, L l, M m)
		{
			MockRepository *repo = mock<Z>::repo;
			return repo->template DoExpectation<Y>(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G,H,I,J,K,L,M>(a,b,c,d,e,f,g,h,i,j,k,l,m));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L, typename M, typename N>
		Y expectation14(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k, L l, M m, N n)
		{
			MockRepository *repo = mock<Z>::repo;
			return repo->template DoExpectation<Y>(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G,H,I,J,K,L,M,N>(a,b,c,d,e,f,g,h,i,j,k,l,m,n));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L, typename M, typename N, typename O>
		Y expectation15(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k, L l, M m, N n, O o)
		{
			MockRepository *repo = mock<Z>::repo;
			return repo->template DoExpectation<Y>(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G,H,I,J,K,L,M,N,O>(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L, typename M, typename N, typename O, typename P>
		Y expectation16(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k, L l, M m, N n, O o, P p)
		{
			MockRepository *repo = mock<Z>::repo;
			return repo->template DoExpectation<Y>(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P>(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p));
		}
	};


	//------------------------------------------------------------------------------
	template <typename Z>
	class mockFuncs<Z, void> : public mock<Z> 
	{
	private: 

		mockFuncs();

	public:

		//------------------------------------------------------------------------------
		template <int X>
		void expectation0()
		{
			MockRepository *repo = mock<Z>::repo;
			repo->DoVoidExpectation(this, mock<Z>::translateX(X), tuple<>());
		}

		//------------------------------------------------------------------------------
		template <int X, typename A>
		void expectation1(A a)
		{
			MockRepository *repo = mock<Z>::repo;
			repo->DoVoidExpectation(this, mock<Z>::translateX(X), tuple<A>(a));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B>
		void expectation2(A a, B b)
		{
			MockRepository *repo = mock<Z>::repo;
			repo->DoVoidExpectation(this, mock<Z>::translateX(X), tuple<A,B>(a,b));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C>
		void expectation3(A a, B b, C c)
		{
			MockRepository *repo = mock<Z>::repo;
			repo->DoVoidExpectation(this, mock<Z>::translateX(X), tuple<A,B,C>(a,b,c));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D>
		void expectation4(A a, B b, C c, D d)
		{
			MockRepository *repo = mock<Z>::repo;
			repo->DoVoidExpectation(this, mock<Z>::translateX(X), tuple<A,B,C,D>(a,b,c,d));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E>
		void expectation5(A a, B b, C c, D d, E e)
		{
			MockRepository *repo = mock<Z>::repo;
			repo->DoVoidExpectation(this, mock<Z>::translateX(X), tuple<A,B,C,D,E>(a,b,c,d,e));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F>
		void expectation6(A a, B b, C c, D d, E e, F f)
		{
			MockRepository *repo = mock<Z>::repo;
			repo->DoVoidExpectation(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F>(a,b,c,d,e,f));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G>
		void expectation7(A a, B b, C c, D d, E e, F f, G g)
		{
			MockRepository *repo = mock<Z>::repo;
			repo->DoVoidExpectation(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G>(a,b,c,d,e,f,g));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H>
		void expectation8(A a, B b, C c, D d, E e, F f, G g, H h)
		{
			MockRepository *repo = mock<Z>::repo;
			repo->DoVoidExpectation(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G,H>(a,b,c,d,e,f,g,h));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I>
		void expectation9(A a, B b, C c, D d, E e, F f, G g, H h, I i)
		{
			MockRepository *repo = mock<Z>::repo;
			repo->DoVoidExpectation(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G,H,I>(a,b,c,d,e,f,g,h,i));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J>
		void expectation10(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j)
		{
			MockRepository *repo = mock<Z>::repo;
			repo->DoVoidExpectation(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G,H,I,J>(a,b,c,d,e,f,g,h,i,j));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K>
		void expectation11(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k)
		{
			MockRepository *repo = mock<Z>::repo;
			repo->DoVoidExpectation(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G,H,I,J,K>(a,b,c,d,e,f,g,h,i,j,k));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L>
		void expectation12(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k, L l)
		{
			MockRepository *repo = mock<Z>::repo;
			repo->DoVoidExpectation(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G,H,I,J,K,L>(a,b,c,d,e,f,g,h,i,j,k,l));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L, typename M>
		void expectation13(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k, L l, M m)
		{
			MockRepository *repo = mock<Z>::repo;
			repo->DoVoidExpectation(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G,H,I,J,K,L,M>(a,b,c,d,e,f,g,h,i,j,k,l,m));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L, typename M, typename N>
		void expectation14(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k, L l, M m, N n)
		{
			MockRepository *repo = mock<Z>::repo;
			repo->DoVoidExpectation(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G,H,I,J,K,L,M,N>(a,b,c,d,e,f,g,h,i,j,k,l,m,n));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L, typename M, typename N, typename O>
		void expectation15(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k, L l, M m, N n, O o)
		{
			MockRepository *repo = mock<Z>::repo;
			repo->DoVoidExpectation(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G,H,I,J,K,L,M,N,O>(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o));
		}

		//------------------------------------------------------------------------------
		template <int X, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename K, typename L, typename M, typename N, typename O, typename P>
		void expectation16(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k, L l, M m, N n, O o, P p)
		{
			MockRepository *repo = mock<Z>::repo;
			repo->DoVoidExpectation(this, mock<Z>::translateX(X), tuple<A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P>(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p));
		}
	};

}//nsUnitTesting

#endif//_UNITTEST_MOCK_FUNCS_H_

