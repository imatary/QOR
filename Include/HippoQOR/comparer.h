//comparer.h

#ifndef _UNITTESTING_COMPARER_H_
#define _UNITTESTING_COMPARER_H_

//------------------------------------------------------------------------------
namespace nsUnitTesting
{
	//------------------------------------------------------------------------------
	template <typename X>
	struct no_cref 
	{ 
		typedef X type; 
	};

	//------------------------------------------------------------------------------
	template <typename X>
	struct no_cref<const X &> 
	{ 
		typedef X type; 
	};

	//------------------------------------------------------------------------------
	struct NotComparable 
	{ 
		template <typename T> NotComparable(const T&) 
		{
		} 
	};

	//------------------------------------------------------------------------------
	inline bool operator==(NotComparable, NotComparable);

	//------------------------------------------------------------------------------
	template <typename T>
	struct comparer
	{
		//------------------------------------------------------------------------------
		static inline bool compare(T a, T b)
		{
			return a == b;
		}
	};

}//nsUnitTesting

#endif//_UNITTESTING_COMPARER_H_
