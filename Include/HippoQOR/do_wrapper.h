//do_wrapper.h

#ifndef _UNITTESTING_DOWRAPPER_H_
#define _UNITTESTING_DOWRAPPER_H_

#include "base_tuple.h"
#include "null_type.h"

//------------------------------------------------------------------------------
namespace nsUnitTesting
{
	//------------------------------------------------------------------------------
	// Do() function wrapping
	class VirtualDestructable 
	{ 
	public: 
	
		virtual ~VirtualDestructable();
	};

	//------------------------------------------------------------------------------
	template <typename Y>
	class TupleInvocable : public VirtualDestructable 
	{
	public:
		virtual Y operator()(const base_tuple &tupl) = 0;
	};

#undef I

	//------------------------------------------------------------------------------
	template <typename Y,
			  typename A = NullType, typename B = NullType, typename C = NullType, typename D = NullType, 
			  typename E = NullType, typename F = NullType, typename G = NullType, typename H = NullType, 
			  typename I = NullType, typename J = NullType, typename K = NullType, typename L = NullType, 
			  typename M = NullType, typename N = NullType, typename O = NullType, typename P = NullType>
	class Invocable : public TupleInvocable<Y>
	{
	public:
		virtual Y operator()(A a = A(), B b = B(), C c = C(), D d = D(), E e = E(), F f = F(), G g = G(), H h = H(), I i = I(), J j = J(), K k = K(), L l = L(), M m = M(), N n = N(), O o = O(), P p = P()) = 0;
		virtual Y operator()(const base_tuple &tupl) {
			const tuple<A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> &rTupl = reinterpret_cast<const tuple<A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> &>(tupl);
			return (*this)(rTupl.a, rTupl.b, rTupl.c, rTupl.d, rTupl.e, rTupl.f, rTupl.g, rTupl.h, 
				rTupl.i, rTupl.j, rTupl.k, rTupl.l, rTupl.m, rTupl.n, rTupl.o, rTupl.p);
		}
	};

	//------------------------------------------------------------------------------
	template <typename T, typename Y,
			  typename A, typename B, typename C, typename D, 
			  typename E, typename F, typename G, typename H, 
			  typename I, typename J, typename K, typename L, 
			  typename M, typename N, typename O, typename P>
	class DoWrapper : public Invocable<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P> 
	{
		T &t;
	public:
		DoWrapper(T &t) : t(t) {}
		virtual Y operator()(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k, L l, M m, N n, O o, P p)
		{
			return t(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
		}
		using Invocable<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P>::operator();
	};

	//------------------------------------------------------------------------------
	template <typename T, typename Y,
			  typename A, typename B, typename C, typename D, 
			  typename E, typename F, typename G, typename H, 
			  typename I, typename J, typename K, typename L, 
			  typename M, typename N, typename O>
	class DoWrapper<T,Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,NullType> : public Invocable<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O> 
	{
		T &t;
	public:
		DoWrapper(T &t) : t(t) {}
		virtual Y operator()(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k, L l, M m, N n, O o, NullType)
		{
			return t(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o);
		}
		using Invocable<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O>::operator();
	};

	//------------------------------------------------------------------------------
	template <typename T, typename Y,
			  typename A, typename B, typename C, typename D, 
			  typename E, typename F, typename G, typename H, 
			  typename I, typename J, typename K, typename L, 
			  typename M, typename N>
	class DoWrapper<T,Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N,NullType,NullType> : public Invocable<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N> 
	{
		T &t;
	public:
		DoWrapper(T &t) : t(t) {}
		virtual Y operator()(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k, L l, M m, N n, NullType, NullType)
		{
			return t(a,b,c,d,e,f,g,h,i,j,k,l,m,n);
		}
		using Invocable<Y,A,B,C,D,E,F,G,H,I,J,K,L,M,N>::operator();
	};

	//------------------------------------------------------------------------------
	template <typename T, typename Y,
			  typename A, typename B, typename C, typename D, 
			  typename E, typename F, typename G, typename H, 
			  typename I, typename J, typename K, typename L, 
			  typename M>
	class DoWrapper<T,Y,A,B,C,D,E,F,G,H,I,J,K,L,M,NullType,NullType,NullType> : public Invocable<Y,A,B,C,D,E,F,G,H,I,J,K,L,M> 
	{
		T &t;
	public:
		DoWrapper(T &t) : t(t) {}
		virtual Y operator()(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k, L l, M m, NullType, NullType, NullType)
		{
			return t(a,b,c,d,e,f,g,h,i,j,k,l,m);
		}
		using Invocable<Y,A,B,C,D,E,F,G,H,I,J,K,L,M>::operator();
	};

	//------------------------------------------------------------------------------
	template <typename T, typename Y,
			  typename A, typename B, typename C, typename D, 
			  typename E, typename F, typename G, typename H, 
			  typename I, typename J, typename K, typename L>
	class DoWrapper<T,Y,A,B,C,D,E,F,G,H,I,J,K,L,NullType,NullType,NullType,NullType> : public Invocable<Y,A,B,C,D,E,F,G,H,I,J,K,L> 
	{
		T &t;
	public:
		DoWrapper(T &t) : t(t) {}
		virtual Y operator()(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k, L l, NullType, NullType, NullType, NullType)
		{
			return t(a,b,c,d,e,f,g,h,i,j,k,l);
		}
		using Invocable<Y,A,B,C,D,E,F,G,H,I,J,K,L>::operator();
	};

	//------------------------------------------------------------------------------
	template <typename T, typename Y,
			  typename A, typename B, typename C, typename D, 
			  typename E, typename F, typename G, typename H, 
			  typename I, typename J, typename K>
	class DoWrapper<T,Y,A,B,C,D,E,F,G,H,I,J,K,NullType,NullType,NullType,NullType,NullType> : public Invocable<Y,A,B,C,D,E,F,G,H,I,J,K> 
	{
		T &t;
	public:
		DoWrapper(T &t) : t(t) {}
		virtual Y operator()(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, K k, NullType, NullType, NullType, NullType, NullType)
		{
			return t(a,b,c,d,e,f,g,h,i,j,k);
		}
		using Invocable<Y,A,B,C,D,E,F,G,H,I,J,K>::operator();
	};

	//------------------------------------------------------------------------------
	template <typename T, typename Y,
			  typename A, typename B, typename C, typename D, 
			  typename E, typename F, typename G, typename H, 
			  typename I, typename J>
	class DoWrapper<T,Y,A,B,C,D,E,F,G,H,I,J,NullType,NullType,NullType,NullType,NullType,NullType> : public Invocable<Y,A,B,C,D,E,F,G,H,I,J> 
	{
		T &t;
	public:
		DoWrapper(T &t) : t(t) {}
		virtual Y operator()(A a, B b, C c, D d, E e, F f, G g, H h, I i, J j, NullType, NullType, NullType, NullType, NullType, NullType)
		{
			return t(a,b,c,d,e,f,g,h,i,j);
		}
		using Invocable<Y,A,B,C,D,E,F,G,H,I,J>::operator();
	};

	//------------------------------------------------------------------------------
	template <typename T, typename Y,
			  typename A, typename B, typename C, typename D, 
			  typename E, typename F, typename G, typename H, 
			  typename I>
	class DoWrapper<T,Y,A,B,C,D,E,F,G,H,I,NullType,NullType,NullType,NullType,NullType,NullType,NullType>  : public Invocable<Y,A,B,C,D,E,F,G,H,I>
	{
		T &t;
	public:
		DoWrapper(T &t) : t(t) {}
		virtual Y operator()(A a, B b, C c, D d, E e, F f, G g, H h, I i, NullType, NullType, NullType, NullType, NullType, NullType, NullType)
		{
			return t(a,b,c,d,e,f,g,h,i);
		}
		using Invocable<Y,A,B,C,D,E,F,G,H,I>::operator();
	};

	//------------------------------------------------------------------------------
	template <typename T, typename Y,
			  typename A, typename B, typename C, typename D, 
			  typename E, typename F, typename G, typename H>
	class DoWrapper<T,Y,A,B,C,D,E,F,G,H,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType> : public Invocable<Y,A,B,C,D,E,F,G,H> 
	{
		T &t;
	public:
		DoWrapper(T &t) : t(t) {}
		virtual Y operator()(A a, B b, C c, D d, E e, F f, G g, H h, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType)
		{
			return t(a,b,c,d,e,f,g,h);
		}
		using Invocable<Y,A,B,C,D,E,F,G,H>::operator();
	};

	//------------------------------------------------------------------------------
	template <typename T, typename Y,
			  typename A, typename B, typename C, typename D, 
			  typename E, typename F, typename G>
	class DoWrapper<T,Y,A,B,C,D,E,F,G,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType> : public Invocable<Y,A,B,C,D,E,F,G> 
	{
		T &t;
	public:
		DoWrapper(T &t) : t(t) {}
		virtual Y operator()(A a, B b, C c, D d, E e, F f, G g, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType)
		{
			return t(a,b,c,d,e,f,g);
		}
		using Invocable<Y,A,B,C,D,E,F,G>::operator();
	};

	//------------------------------------------------------------------------------
	template <typename T, typename Y,
			  typename A, typename B, typename C, typename D, 
			  typename E, typename F>
	class DoWrapper<T,Y,A,B,C,D,E,F,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType> : public Invocable<Y,A,B,C,D,E,F> 
	{
		T &t;
	public:
		DoWrapper(T &t) : t(t) {}
		virtual Y operator()(A a, B b, C c, D d, E e, F f, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType)
		{
			return t(a,b,c,d,e,f);
		}
		using Invocable<Y,A,B,C,D,E,F>::operator();
	};

	//------------------------------------------------------------------------------
	template <typename T, typename Y,
			  typename A, typename B, typename C, typename D, 
			  typename E>
	class DoWrapper<T,Y,A,B,C,D,E,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType> : public Invocable<Y,A,B,C,D,E> 
	{
		T &t;
	public:
		DoWrapper(T &t) : t(t) {}
		virtual Y operator()(A a, B b, C c, D d, E e, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType)
		{
			return t(a,b,c,d,e);
		}
		using Invocable<Y,A,B,C,D,E>::operator();
	};

	//------------------------------------------------------------------------------
	template <typename T, typename Y,
			  typename A, typename B, typename C, typename D>
	class DoWrapper<T,Y,A,B,C,D,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType> : public Invocable<Y,A,B,C,D> 
	{
		T &t;
	public:
		DoWrapper(T &t) : t(t) {}
		virtual Y operator()(A a, B b, C c, D d, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType)
		{
			return t(a,b,c,d);
		}
		using Invocable<Y,A,B,C,D>::operator();
	};

	//------------------------------------------------------------------------------
	template <typename T, typename Y,
			  typename A, typename B, typename C>
	class DoWrapper<T,Y,A,B,C,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType> : public Invocable<Y,A,B,C> 
	{
		T &t;
	public:
		DoWrapper(T &t) : t(t) {}
		virtual Y operator()(A a, B b, C c, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType)
		{
			return t(a,b,c);
		}
		using Invocable<Y,A,B,C>::operator();
	};

	//------------------------------------------------------------------------------
	template <typename T, typename Y, typename A, typename B>
	class DoWrapper<T,Y,A,B,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType> : public Invocable<Y,A,B> 
	{
		T &t;
	public:
		DoWrapper(T &t) : t(t) {}
		virtual Y operator()(A a, B b, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType)
		{
			return t(a,b);
		}
		using Invocable<Y,A,B>::operator();
	};

	//------------------------------------------------------------------------------
	template <typename T, typename Y, typename A>
	class DoWrapper<T,Y,A,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType> : public Invocable<Y,A> 
	{
		T &t;
	public:
		DoWrapper(T &t) : t(t) {}
		virtual Y operator()(A a, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType)
		{
			return t(a);
		}
		using Invocable<Y,A>::operator();
	};

	//------------------------------------------------------------------------------
	template <typename T, typename Y>
	class DoWrapper<T,Y,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType,NullType> : public Invocable<Y> 
	{
		T &t;
	public:
		DoWrapper(T &t) : t(t) {}
		virtual Y operator()(NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType, NullType)
		{
			return t();
		}
		using Invocable<Y>::operator();
	};

}//nsUnitTesting

#endif//_UNITTESTING_DOWRAPPER_H_
