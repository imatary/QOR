//Basemqueue.cpp

// Copyright Querysoft Limited 2013
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include "SystemQOR/Posix/Basemqueue.h"
#include <errno.h>
#include "CodeQOR/Tracing/FunctionContextBase.h"

//--------------------------------------------------------------------------------
namespace nsBaseCRT
{
	__QOR_IMPLEMENT_OCLASS_LUID( Cmqueue );

	//------------------------------------------------------------------------------
	Cmqueue::Cmqueue()
	{
		__QCS_MEMBER_FCONTEXT( "Cmqueue::Cmqueue" );
	}

	//------------------------------------------------------------------------------
	Cmqueue::~Cmqueue()
	{
		__QCS_MEMBER_FCONTEXT( "Cmqueue::~Cmqueue" );
	}

	//------------------------------------------------------------------------------
	int Cmqueue::mq_close( mqd_t )
	{
		__QCS_MEMBER_FCONTEXT( "Cmqueue::mq_close" );
		errno = ENOSYS;
		return 0;
	}

	//------------------------------------------------------------------------------
	int Cmqueue::mq_getattr( mqd_t, mq_attr* )
	{
		__QCS_MEMBER_FCONTEXT( "Cmqueue::mq_getattr" );
		errno = ENOSYS;
		return 0;
	}

	//------------------------------------------------------------------------------
	int Cmqueue::mq_notify( mqd_t, const sigevent* )
	{
		__QCS_MEMBER_FCONTEXT( "Cmqueue::mq_notify" );
		errno = ENOSYS;
		return 0;
	}

	//------------------------------------------------------------------------------
	mqd_t Cmqueue::mq_open( const char*, int, va_list vargs )
	{
		__QCS_MEMBER_FCONTEXT( "Cmqueue::mq_open" );
		errno = ENOSYS;
		return 0;
	}

	//------------------------------------------------------------------------------
	ssize_t Cmqueue::mq_receive( mqd_t, char*, size_t, unsigned* )
	{
		__QCS_MEMBER_FCONTEXT( "Cmqueue::mq_receive" );
		errno = ENOSYS;
		return 0;
	}

	//------------------------------------------------------------------------------
	int Cmqueue::mq_send( mqd_t, const char*, size_t, unsigned )
	{
		__QCS_MEMBER_FCONTEXT( "Cmqueue::mq_send" );
		errno = ENOSYS;
		return 0;
	}

	//------------------------------------------------------------------------------
	int Cmqueue::mq_setattr( mqd_t, const mq_attr* __QCMP_RESTRICT, mq_attr* __QCMP_RESTRICT )
	{
		__QCS_MEMBER_FCONTEXT( "Cmqueue::mq_setattr" );
		errno = ENOSYS;
		return 0;
	}

	//------------------------------------------------------------------------------
	ssize_t Cmqueue::mq_timedreceive( mqd_t, char* __QCMP_RESTRICT, size_t, unsigned* __QCMP_RESTRICT, const timespec* __QCMP_RESTRICT )
	{
		__QCS_MEMBER_FCONTEXT( "Cmqueue::mq_timedreceive" );
		errno = ENOSYS;
		return 0;
	}

	//------------------------------------------------------------------------------
	int Cmqueue::mq_timedsend( mqd_t, const char*, size_t, unsigned, const timespec* )
	{
		__QCS_MEMBER_FCONTEXT( "Cmqueue::mq_timedsend" );
		errno = ENOSYS;
		return 0;
	}

	//------------------------------------------------------------------------------
	int Cmqueue::mq_unlink( const char* )
	{
		__QCS_MEMBER_FCONTEXT( "Cmqueue::mq_unlink" );
		errno = ENOSYS;
		return 0;
	}
	
}//nsBaseCRT