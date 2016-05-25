//===------------------------ memory.cpp ----------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "CompilerQOR.h"

#if		__QCMP_SUPPORTS( __QCMP_FEATURE_TEMPLATE_PARTIAL_SPECIALIZATION )

#include "memory"

#ifdef __MINGW32__
extern bool __sync_bool_compare_and_swap( long volatile*, long, long );
#endif // __MINGW32__

//--------------------------------------------------------------------------------
namespace std
{

	//--------------------------------------------------------------------------------
	bad_weak_ptr::~bad_weak_ptr() __QCMP_THROW
	{
	}

	//--------------------------------------------------------------------------------
	const char* bad_weak_ptr::what() const __QCMP_THROW
	{
		return "bad_weak_ptr";
	}

	//--------------------------------------------------------------------------------
	void declare_reachable(void*)
	{
	}

	//--------------------------------------------------------------------------------
	void declare_no_pointers(char*, size_t)
	{
	}

	//--------------------------------------------------------------------------------
	void undeclare_no_pointers(char*, size_t)
	{
	}

	//--------------------------------------------------------------------------------
	pointer_safety get_pointer_safety() __QCMP_THROW
	{
		return pointer_safety::relaxed;
	}

	//--------------------------------------------------------------------------------
	void* __undeclare_reachable( void* p )
	{
		return p;
	}

	//--------------------------------------------------------------------------------
	void* align( size_t alignment, size_t size, void*& ptr, size_t& space )
	{
		void* r = nullptr;
		if (size <= space)
		{
			char* p1 = static_cast<char*>(ptr);
			char* p2 = (char*)( (size_t)( p1 + ( alignment - 1 ) ) & 0-alignment );
			size_t d = static_cast<size_t>(p2 - p1);
			if (d <= space - size)
			{
				r = p2;
				ptr = r;
				space -= d;
			}
		}
		return r;
	}

}//std

#endif//	__QCMP_SUPPORTS( __QCMP_FEATURE_TEMPLATE_PARTIAL_SPECIALIZATION )
