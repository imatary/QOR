//tuple.h

#ifndef _UNITTEST_TUPLE_H_
#define _UNITTEST_TUPLE_H_

#include "SystemQOR.h"
#include "HippoQOR/null_type.h"
#include "HippoQOR/comparer.h"
#include "HippoQOR/print_arg.h"
#include "HippoQOR/base_tuple.h"

//------------------------------------------------------------------------------
namespace nsUnitTesting
{
#	undef I

	//------------------------------------------------------------------------------
	template <typename A = NullType, typename B = NullType, typename C = NullType, typename D = NullType, 
			  typename E = NullType, typename F = NullType, typename G = NullType, typename H = NullType, 
			  typename I = NullType, typename J = NullType, typename K = NullType, typename L = NullType, 
			  typename M = NullType, typename N = NullType, typename O = NullType, typename P = NullType>
	class tuple : public base_tuple
	{

	public:

		typename no_cref<A>::type a;
		typename no_cref<B>::type b;
		typename no_cref<C>::type c;
		typename no_cref<D>::type d;
		typename no_cref<E>::type e;
		typename no_cref<F>::type f;
		typename no_cref<G>::type g;
		typename no_cref<H>::type h;
		typename no_cref<I>::type i;
		typename no_cref<J>::type j;
		typename no_cref<K>::type k;
		typename no_cref<L>::type l;
		typename no_cref<M>::type m;
		typename no_cref<N>::type n;
		typename no_cref<O>::type o;
		typename no_cref<P>::type p;

		//------------------------------------------------------------------------------
		tuple(typename no_cref<A>::type a = typename no_cref<A>::type(), typename no_cref<B>::type b = typename no_cref<B>::type(), 
			  typename no_cref<C>::type c = typename no_cref<C>::type(), typename no_cref<D>::type d = typename no_cref<D>::type(), 
			  typename no_cref<E>::type e = typename no_cref<E>::type(), typename no_cref<F>::type f = typename no_cref<F>::type(), 
			  typename no_cref<G>::type g = typename no_cref<G>::type(), typename no_cref<H>::type h = typename no_cref<H>::type(),
			  typename no_cref<I>::type i = typename no_cref<I>::type(), typename no_cref<J>::type j = typename no_cref<J>::type(), 
			  typename no_cref<K>::type k = typename no_cref<K>::type(), typename no_cref<L>::type l = typename no_cref<L>::type(), 
			  typename no_cref<M>::type m = typename no_cref<M>::type(), typename no_cref<N>::type n = typename no_cref<N>::type(), 
			  typename no_cref<O>::type o = typename no_cref<O>::type(), typename no_cref<P>::type p = typename no_cref<P>::type())
			  : a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p)
		{
		}

		//------------------------------------------------------------------------------
		bool operator==(const base_tuple &bo) const 
		{
			const tuple<A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> &to = (const tuple<A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> &)bo;
		return (comparer<A>::compare(a, to.a) &&
				comparer<B>::compare(b, to.b) &&
				comparer<C>::compare(c, to.c) &&
				comparer<D>::compare(d, to.d) &&
				comparer<E>::compare(e, to.e) &&
				comparer<F>::compare(f, to.f) &&
				comparer<G>::compare(g, to.g) &&
				comparer<H>::compare(h, to.h) &&
				comparer<I>::compare(i, to.i) &&
				comparer<J>::compare(j, to.j) &&
				comparer<K>::compare(k, to.k) &&
				comparer<L>::compare(l, to.l) &&
				comparer<M>::compare(m, to.m) &&
				comparer<N>::compare(n, to.n) &&
				comparer<O>::compare(o, to.o) &&
						comparer<P>::compare(p, to.p));
		}

		//------------------------------------------------------------------------------
		virtual void printTo(std::ostream &os) const
		{
			os << "(";
			printArg<A>::print(os, a, false);
			printArg<B>::print(os, b, true);
			printArg<C>::print(os, c, true);
			printArg<D>::print(os, d, true);
			printArg<E>::print(os, e, true);
			printArg<F>::print(os, f, true);
			printArg<G>::print(os, g, true);
			printArg<H>::print(os, h, true);
			printArg<I>::print(os, i, true);
			printArg<J>::print(os, j, true);
			printArg<K>::print(os, k, true);
			printArg<L>::print(os, l, true);
			printArg<M>::print(os, m, true);
			printArg<N>::print(os, n, true);
			printArg<O>::print(os, o, true);
			printArg<P>::print(os, p, true);
			os << ")";
		}
	};

}//nsUnitTesting

#endif//_UNITTEST_TUPLE_H_
