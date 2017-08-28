/**
 * @file obex_transport_sock.h
 *
 * OBEX header releated functions.
 * OpenOBEX library - Free implementation of the Object Exchange protocol.
 *
 * Copyright (c) 2012 Hendrik Sattler, All Rights Reserved.
 *
 * OpenOBEX is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with OpenOBEX. If not, see <http://www.gnu.org/>.
 */

#ifndef OBEX_TRANSPORT_SOCK_H
#define OBEX_TRANSPORT_SOCK_H

#ifdef _WIN32
#include <winsock2.h>
#define socket_t SOCKET
#else
#include <sys/socket.h>
#include <sys/types.h>
#define socket_t int
#define INVALID_SOCKET -1
#endif

#include "defines.h"

//------------------------------------------------------------------------------
/** a socket instance */
struct obex_sock 
{	
	int domain;										/** socket domain */
	int proto;										/** socket protocol */
	socket_t fd;									/** the kernel descriptor for this socket */
	sockaddr_storage local;							/** the local address of this socket */
	sockaddr_storage remote;						/** the remote address of this socket */
	socklen_t addr_size;							/** the address size of this socket type */
	unsigned int flags;								/** socket OBEX_FL_* flags */
	bool (*set_sock_opts)(socket_t);				/** callback to set transport-specific socket options */
};

bool obex_transport_sock_init(void);
void obex_transport_sock_cleanup(void);

socket_t create_stream_socket(int domain, int proto, unsigned int flags);
bool close_socket(socket_t fd);

obex_sock* obex_transport_sock_create(int domain, int proto, socklen_t addr_size, unsigned int flags);

void obex_transport_sock_destroy( obex_sock *sock);
socket_t obex_transport_sock_get_fd( obex_sock *sock);
bool obex_transport_sock_set_local( obex_sock *sock, const sockaddr *addr, socklen_t len);
bool obex_transport_sock_set_remote( obex_sock *sock, const sockaddr *addr, socklen_t len);
bool obex_transport_sock_connect( obex_sock *sock);
bool obex_transport_sock_listen( obex_sock *sock);
obex_sock * obex_transport_sock_accept( obex_sock *sock);
bool obex_transport_sock_disconnect( obex_sock *sock);
ssize_t obex_transport_sock_send( obex_sock *sock,  databuffer *msg, int64_t timeout);
result_t obex_transport_sock_wait( obex_sock *sock, int64_t timeout);
ssize_t obex_transport_sock_recv( obex_sock *sock, void *buf, int buflen);
result_t obex_transport_sock_handle_input( obex_sock *sock, obex_t *self);

#endif /* OBEX_TRANSPORT_SOCK_H */
