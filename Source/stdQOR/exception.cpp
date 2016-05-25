//===------------------------ exception.cpp -------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include <stdlib.h>
#include <string.h>

#include "exception"

#if __APPLE__
  #include <cxxabi.h>

  using namespace __cxxabiv1;
  #define HAVE_DEPENDENT_EH_ABI 1
  #ifndef _LIBCPPABI_VERSION
    using namespace __cxxabiapple;
    // On Darwin, there are two STL shared libraries and a lower level ABI
    // shared libray.  The globals holding the current terminate handler and
    // current unexpected handler are in the ABI library.
    #define __terminate_handler  __cxxabiapple::__cxa_terminate_handler
    #define __unexpected_handler __cxxabiapple::__cxa_unexpected_handler
  #endif  // _LIBCPPABI_VERSION
#elif defined(LIBCXXRT)
  #include <cxxabi.h>
  using namespace __cxxabiv1;
  #define HAVE_DEPENDENT_EH_ABI 1
#else  // __APPLE__
  static std::terminate_handler  __terminate_handler;
  static std::unexpected_handler __unexpected_handler;
#endif  // __APPLE__

namespace std
{

#if !defined(LIBCXXRT) && !defined(_LIBCPPABI_VERSION) && !defined( __MINGW32__ )

	// libcxxrt provides implementations of these functions itself.
	unexpected_handler set_unexpected(unexpected_handler func) __QCMP_THROW
	{
		return ( unexpected_handler )( __sync_lock_test_and_set( (volatile long*)&__unexpected_handler, (Cmp_int_ptr)func) );
	}

	unexpected_handler get_unexpected() __QCMP_THROW
	{
		return ( unexpected_handler )( __sync_fetch_and_add( ( volatile long*)&__unexpected_handler, (Cmp_int_ptr)0 ) );
	}

	__QCMP_DECLARE_NORETURN void unexpected()
	{
		(*get_unexpected())();
		// unexpected handler should not return
		terminate();
	}

	terminate_handler set_terminate(terminate_handler func) __QCMP_THROW
	{
		return ( terminate_handler )( __sync_lock_test_and_set( ( volatile long* )&__terminate_handler, (Cmp_int_ptr)func ) );
	}

	terminate_handler get_terminate() __QCMP_THROW
	{
		return ( terminate_handler )( __sync_fetch_and_add( ( volatile long* )&__terminate_handler, (int)0 ) );
	}

	__QCMP_DECLARE_NORETURN void __QCMP_CALLCON terminate() __QCMP_THROW
	{
	#ifdef _EXCEPTIONS
		try
		{
	#endif  // _LIBCPP_NO_EXCEPTIONS
			(*get_terminate())();
			// handler should not return
			::abort ();
	#ifdef _EXCEPTIONS
		}
		catch (...)
		{
			// handler should not throw exception
			::abort ();
		}
	#endif  // _LIBCPP_NO_EXCEPTIONS
	}
#endif // !defined(LIBCXXRT) && !defined(_LIBCPPABI_VERSION)


#ifndef LIBCXXRT
#ifndef __MINGW32__
	bool uncaught_exception() __QCMP_THROW
	{
	#if __APPLE__
		// on Darwin, there is a helper function so __cxa_get_globals is private
		return __cxa_uncaught_exception();
	#elif LIBCXXRT
		__cxa_eh_globals * globals = __cxa_get_globals();
		return (globals->uncaughtExceptions != 0);
	#elif __QCMP_SUPPORTS( 1 )
		return false;//TODO: look in thread context for data
	#else  // __APPLE__
	#	pragma warning( "uncaught_exception not yet implemented" )
		::abort();
	#endif  // __APPLE__
	}
#endif
	#ifndef _LIBCPPABI_VERSION
	/*
	exception::exception() __QCMP_THROW0()
	{
	}
	*/
	/*
	exception::exception( char const* const& message, bad_alloc_marker* ) __QCMP_THROW0()
	{
	}

	exception::exception( exception const& src ) __QCMP_THROW0()
	{
	}

	exception& exception::operator = ( exception const& src ) __QCMP_THROW0()
	{
		return *this;
	}
	*/
#endif  // _LIBCPPABI_VERSION
#endif //LIBCXXRT

	namespace
	{
		const Cmp_uint_ptr BADALLOC_FLAG = Cmp_uint_ptr(1) << (sizeof(Cmp_uint_ptr) * /*CHAR_BIT*/8 - 1);
		const char		s_DefaultMessage[]			=	"std::exception";
		const char		s_DefaultBadAllocMessage[]	=	"std::bad_alloc";

		inline
		bool IsDefaultMessage(char const *s)
		{
			return s == s_DefaultMessage || s == s_DefaultBadAllocMessage;
		}

		inline
		char const *AddBadAllocFlag(char const *s)
		{
			return (char const *)(BADALLOC_FLAG | (Cmp_uint_ptr)s);
		}

		inline
		char const *StripBadAllocFlag(char const *s)
		{
			return (char const *)(~(BADALLOC_FLAG) & (Cmp_uint_ptr)s);
		}

		inline
		bool IsBadAllocString(char const *s)
		{
			return	s == s_DefaultBadAllocMessage || StripBadAllocFlag(s) == s;
		}
	}
#if ( __QCMP_COMPILER != __QCMP_GCC )
	/*
	//--------------------------------------------------------------------------------
    std::bad_alloc::bad_alloc( char const * message ) : std::exception( message, static_cast< bad_alloc_marker* > ( 0 ) )
    {
    }
	*/
	//--------------------------------------------------------------------------------
	std::bad_alloc::~bad_alloc()
	{
	}
	/*
	//--------------------------------------------------------------------------------
	std::bad_alloc::bad_alloc( const std::bad_alloc& )
	{
		//private copy constructor, cannot be called
	}
	*/
	//--------------------------------------------------------------------------------
	const char* std::bad_alloc::what() const __QCMP_THROW
	{
		return 0;// m_What;
	}
#endif//__MINGW32__
	//--------------------------------------------------------------------------------
	exception_ptr::~exception_ptr() __QCMP_THROW
	{
	#if HAVE_DEPENDENT_EH_ABI
		__cxa_decrement_exception_refcount(__ptr_);
	#else
	#	pragma TODO( "exception_ptr not yet implemented" )
		::abort();
	#endif  // __APPLE__
	}

	exception_ptr::exception_ptr(const exception_ptr& other) __QCMP_THROW
		: __ptr_(other.__ptr_)
	{
	#if HAVE_DEPENDENT_EH_ABI
		__cxa_increment_exception_refcount(__ptr_);
	#else
	#	pragma TODO( "exception_ptr not yet implemented" )
		::abort();
	#endif  // __APPLE__
	}

	exception_ptr& exception_ptr::operator=(const exception_ptr& other) __QCMP_THROW
	{
	#if HAVE_DEPENDENT_EH_ABI
		if (__ptr_ != other.__ptr_)
		{
			__cxa_increment_exception_refcount(other.__ptr_);
			__cxa_decrement_exception_refcount(__ptr_);
			__ptr_ = other.__ptr_;
		}
		return *this;
	#else  // __APPLE__
	#	pragma TODO( "exception_ptr not yet implemented" )
		::abort();
		return *this;
	#endif  // __APPLE__
	}


	exception_ptr current_exception() __QCMP_THROW
	{
#if HAVE_DEPENDENT_EH_ABI
		// be nicer if there was a constructor that took a ptr, then
		// this whole function would be just:
		//    return exception_ptr(__cxa_current_primary_exception());
		exception_pt ptr;
		ptr.__ptr_ = __cxa_current_primary_exception();
		return ptr;
#else  // __APPLE__
#pragma TODO( "exception_ptr not yet implemented" )
		::abort();
		exception_ptr ptr;
		return ptr;
#endif  // __APPLE__
	}

	__QCMP_DECLARE_NORETURN void rethrow_exception(exception_ptr p)
	{
#if HAVE_DEPENDENT_EH_ABI
		__cxa_rethrow_primary_exception(p.__ptr_);
		// if p.__ptr_ is NULL, above returns so we terminate
		terminate();
#else  // __APPLE__
	#	pragma TODO( "exception_ptr not yet implemented" )
		::abort();
#endif  // __APPLE__
	}

#ifndef __MINGW32__
	/*
	exception::exception(char const * const & message) __QCMP_THROW0() : m_What(_strdup(message))
	{
		if (m_What == 0)
		{
			m_What = s_DefaultMessage;
		}
	}
	*/
	exception::~exception() __QCMP_THROW0()
	{
		/*if (!IsDefaultMessage(m_What))
		{
			free(const_cast<char*>(StripBadAllocFlag(m_What)));
		}*/
	}

	char const * exception::what() const __QCMP_THROW0()
	{
		return 0;//StripBadAllocFlag( m_What );
	}
#endif//__MINGW32__
} // std
