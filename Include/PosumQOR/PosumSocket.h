//PosumSocket.h

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

//Posum socket object

#ifndef POSUMQOR_SOCKET_H_3
#define POSUMQOR_SOCKET_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "PosumQOR/Descriptor.h"

//--------------------------------------------------------------------------------
namespace nsPosum
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __POSUMQOR ) CSocket : public CDescriptor
	{
	public:

		//--------------------------------------------------------------------------------
		CSocket()
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~CSocket()
		{
		}

		/*
			__QOR_INTERFACE( __CQOR ) int accept( int, ::sockaddr* __QCMP_RESTRICT, ::socklen_t* __QCMP_RESTRICT );
	__QOR_INTERFACE( __CQOR ) int bind( int, const ::sockaddr*, ::socklen_t );
	__QOR_INTERFACE( __CQOR ) int connect( int, const ::sockaddr*, ::socklen_t );
	__QOR_INTERFACE( __CQOR ) int getpeername( int, ::sockaddr* __QCMP_RESTRICT, ::socklen_t* __QCMP_RESTRICT );
	__QOR_INTERFACE( __CQOR ) int getsockname( int, ::sockaddr* __QCMP_RESTRICT, ::socklen_t* __QCMP_RESTRICT );
	__QOR_INTERFACE( __CQOR ) int getsockopt( int, int, int, void* __QCMP_RESTRICT, ::socklen_t* __QCMP_RESTRICT );
	__QOR_INTERFACE( __CQOR ) int listen( int, int );
	__QOR_INTERFACE( __CQOR ) ::ssize_t recv( int, void*, size_t, int );
	__QOR_INTERFACE( __CQOR ) ::ssize_t recvfrom( int, void* __QCMP_RESTRICT, size_t, int, ::sockaddr* __QCMP_RESTRICT, ::socklen_t* __QCMP_RESTRICT );
	__QOR_INTERFACE( __CQOR ) ::ssize_t recvmsg( int, ::msghdr*, int );
	__QOR_INTERFACE( __CQOR ) ::ssize_t send( int, const void*, size_t, int );
	__QOR_INTERFACE( __CQOR ) ::ssize_t sendmsg( int, const ::msghdr*, int );
	__QOR_INTERFACE( __CQOR ) ::ssize_t sendto( int, const void*, ::size_t, int, const ::sockaddr*, ::socklen_t);
	__QOR_INTERFACE( __CQOR ) int setsockopt( int, int, int, const void*, ::socklen_t );
	__QOR_INTERFACE( __CQOR ) int shutdown( int, int );
	__QOR_INTERFACE( __CQOR ) int sockatmark( int );
	__QOR_INTERFACE( __CQOR ) int socket( int, int, int );
	__QOR_INTERFACE( __CQOR ) int socketpair( int, int, int, int[ 2 ] );
*/
	};
	
}//nsPosum

#endif//POSUMQOR_SOCKET_H_3