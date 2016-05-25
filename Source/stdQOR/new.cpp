//===--------------------------- new.cpp ----------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include <stdlib.h>

#include "new"

#if __APPLE__
    #include <cxxabi.h>

    #ifndef _LIBCPPABI_VERSION
        // On Darwin, there are two STL shared libraries and a lower level ABI
        // shared libray.  The global holding the current new handler is
        // in the ABI library and named __cxa_new_handler.
        #define __new_handler __cxxabiapple::__cxa_new_handler
    #endif
#else  // __APPLE__
    static std::new_handler __new_handler;
#endif

#if !defined (LIBCXXRT) // && !defined(_LIBCPPABI_VERSION)

// Implement all new and delete operators as weak definitions
// in this shared library, so that they can be overriden by programs
// that define non-weak copies of the functions.

#ifndef __MINGW32__
__attribute__((__weak__, __visibility__("default")))
void*
operator new(size_t size, const std::nothrow_t&)
{
    void* p = 0;
#ifdef _EXCEPTIONS
    try
    {
#endif  // _LIBCPP_NO_EXCEPTIONS
        p = ::operator new(size);
#ifdef _EXCEPTIONS
    }
    catch (...)
    {
    }
#endif  // _LIBCPP_NO_EXCEPTIONS
    return p;
}
#endif
__attribute__((__weak__, __visibility__("default")))
void*
operator new[](size_t size)
#if ( __QCMP_COMPILER != __QCMP_GCC )
//#if !__has_feature(cxx_noexcept)
    throw(std::bad_alloc)
//#endif
#endif
{
    return ::operator new(size);
}

__attribute__((__weak__, __visibility__("default")))
void*
operator new[](size_t size, const std::nothrow_t&) __QCMP_THROW
{
    void* p = 0;
#ifdef __EXCEPTIONS
    try
    {
#endif  // _LIBCPP_NO_EXCEPTIONS
        p = ::operator new[](size);
#ifdef __EXCEPTIONS
    }
    catch (...)
    {
    }
#endif  // _LIBCPP_NO_EXCEPTIONS
    return p;
}


__attribute__((__weak__, __visibility__("default")))
void
operator delete(void* ptr, const std::nothrow_t&) __QCMP_THROW
{
    ::operator delete(ptr);
}

#if ( ! ( __QCMP_COMPILER == __QCMP_MSVC && _MSC_VER >= 1900 ) )
__attribute__((__weak__, __visibility__("default")))
void
operator delete[] (void* ptr) __QCMP_THROW
{
    ::operator delete (ptr);
}
#endif

__attribute__((__weak__, __visibility__("default")))
void
operator delete[] (void* ptr, const std::nothrow_t&) __QCMP_THROW
{
    ::operator delete[](ptr);
}

#endif  // !_LIBCPPABI_VERSION && !LIBCXXRT

namespace std
{

//const nothrow_t nothrow = {};

#ifndef _LIBCPPABI_VERSION
#ifndef __MINGW32__

new_handler set_new_handler( new_handler handler ) __QCMP_THROW
{
    return __new_handler = handler;//__sync_lock_test_and_set( &__new_handler, handler );
}

new_handler get_new_handler() __QCMP_THROW
{
    return __new_handler;//__sync_fetch_and_add( &__new_handler, (new_handler)0 );
}
#endif __MINGW32__

#endif //LIBCXXRT

void
__throw_bad_alloc()
{
#ifndef _LIBCPP_NO_EXCEPTIONS
    //throw bad_alloc( "bad alloc");
#endif
}


}  // std

