/**
	\file obex_main.h
	Implementation of the Object Exchange Protocol OBEX.
	OpenOBEX library - Free implementation of the Object Exchange protocol.

	Copyright (c) 1998, 1999, 2000 Dag Brattli, All Rights Reserved.
	Copyright (c) 1999, 2000 Pontus Fuchs, All Rights Reserved.

	OpenOBEX is free software; you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation; either version 2.1 of
	the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with OpenOBEX. If not, see <http://www.gnu.org/>.
 */

#ifndef OBEX_MAIN_H
#define OBEX_MAIN_H

#include "obex_incl.h"
#include "defines.h"

#include <time.h>

class databuffer;
class CObexObject;
class obex_hdr_it;

#include "obex_transport.h"
#include "defines.h"
#include "debug.h"

void obex_library_init(void);

//------------------------------------------------------------------------------
class obex 
{
public:

	obex(obex_event_t eventcb, unsigned int flags);
	virtual ~obex();

	uint16_t mtu_tx;		/* Maximum OBEX TX packet size */
	uint16_t mtu_rx;		/* Maximum OBEX RX packet size */
	uint16_t mtu_tx_max;		/* Maximum TX we can accept */

	obex_state state;
	obex_substate substate;
	enum obex_mode mode;
	obex_rsp_mode rsp_mode;	/* OBEX_RSP_MODE_* */

	unsigned int init_flags;
	unsigned int srm_flags;		/* Flags for single response mode */

	databuffer* tx_msg;	/* Reusable transmit message */
	databuffer* rx_msg;	/* Reusable receive message */

	CObexObject* object;	/* Current object being transfered */
	obex_event_t eventcb;		/* Event-callback */
	obex_event abort_event;	/**< event for application when server aborts */

	obex_transport_t* trans;	/* Transport being used */

	obex_interface_t* interfaces;	/* Array of discovered interfaces */
	int interfaces_number;		/* Number of discovered interfaces */

	void* userdata;		/* For user */

	//client
	result_t client(void);

	//server
	result_t server(void);

	int insert_connectframe(CObexObject* object );
	int parse_connectframe(CObexObject* object );

	//obex_msg
	bool obex_msg_prepare(CObexObject* object, bool allowfinal);
	int obex_msg_getspace(CObexObject* object, unsigned int flags);
	bool obex_msg_post_prepare(const obex_hdr_it *from, const obex_hdr_it *to);
	bool obex_msg_rx_status(void) const;
	bool obex_msg_tx_status(void) const;
	int obex_msg_get_opcode(void) const;
	size_t obex_msg_get_len(void) const;
	void obex_msg_pre_receive(void);
	int obex_msg_receive_filtered(CObexObject* object, uint64_t filter, bool first_run );
	int obex_msg_receive(CObexObject* object);
	int obex_msg_post_receive(void);
	__inline obex_cmd msg_get_cmd(void) const;
	__inline int msg_get_final(void) const;

	//obex
	void deliver_event( obex_event event, obex_cmd cmd, obex_rsp rsp, bool delete_object);
	result_t handle_input(void);
	result_t work(void);
	obex_data_direction get_data_direction(void);
	result_t data_indication( void );
	void data_receive_finished();
	int set_mtu(uint16_t mtu_rx, uint16_t mtu_tx_max);
	bool data_request_init( void );
	int cancelrequest(int nice);
	void data_request_prepare(int opcode);
};

// Common header used by all frames
#pragma pack(1)
struct obex_common_hdr 
{
	uint8_t  opcode;
	uint16_t len;
};
#pragma pack()

typedef obex_common_hdr obex_common_hdr_t;

//int obex_get_buffer_status(databuffer *msg);


char *obex_response_to_string(int rsp);

#endif//
