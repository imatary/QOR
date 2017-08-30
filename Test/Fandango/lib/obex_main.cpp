/**
	\file obex_main.c
	Implementation of the Object Exchange Protocol OBEX.
	OpenOBEX library - Free implementation of the Object Exchange protocol.

	Copyright (c) 2000 Pontus Fuchs, All Rights Reserved.
	Copyright (c) 1998, 1999 Dag Brattli, All Rights Reserved.

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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef _WIN32
#include <winsock2.h>
#else /* _WIN32 */

#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>

#endif /* _WIN32 */
#include <errno.h>

#include "obex_main.h"
#include "obex_transport.h"
#include "obex_object.h"
class obex;
#include "obex_hdr.h"
#include "obex_incl.h"
#include "defines.h"
#include "databuffer.h"

#include <openobex/obex_const.h>

int obex_debug;
int obex_dump;

//------------------------------------------------------------------------------
void obex_library_init(void)
{
	char *env;

#if OBEX_DEBUG
	obex_debug = OBEX_DEBUG;
#else
	obex_debug = -1;
#endif
	env = getenv("OBEX_DEBUG");
	if (env)
		obex_debug = atoi(env);

#if OBEX_DUMP
	obex_dump = OBEX_DUMP;
#else
	obex_dump = 0;
#endif
	env = getenv("OBEX_DUMP");
	if (env)
		obex_dump = atoi(env);
}

//------------------------------------------------------------------------------
obex::obex(obex_event_t _eventcb, unsigned int _flags)
{
	eventcb = _eventcb;
	init_flags = _flags;
	mode = OBEX_MODE_SERVER;
	state = STATE_IDLE;
	rsp_mode = OBEX_RSP_MODE_NORMAL;

	/* Safe values.
	 * Both self->mtu_rx and self->mtu_tx_max can be increased by app
	 * self->mtu_tx will be whatever the other end sends us - Jean II */
	mtu_tx = OBEX_MINIMUM_MTU;
	set_mtu(OBEX_DEFAULT_MTU, OBEX_DEFAULT_MTU);
}

//------------------------------------------------------------------------------
obex::~obex()
{
	if (trans)
	{
		obex_transport_cleanup(this);
	}

	if (tx_msg)
	{
		delete tx_msg;
	}

	if (rx_msg)
	{
		delete rx_msg;
	}
}

//------------------------------------------------------------------------------
int obex::set_mtu(uint16_t _mtu_rx, uint16_t _mtu_tx_max)
{
	if (mtu_rx < OBEX_MINIMUM_MTU /*|| mtu_rx > OBEX_MAXIMUM_MTU*/)
	{
		return -E2BIG;
	}

	if (mtu_tx_max < OBEX_MINIMUM_MTU /*|| mtu_tx_max > OBEX_MAXIMUM_MTU*/)
	{
		return -E2BIG;
	}

	// Change MTUs
	mtu_rx = _mtu_rx;
	mtu_tx_max = _mtu_tx_max;

	// (Re)Allocate transport buffers
	if (rx_msg)
	{
		rx_msg->set_size(mtu_rx);
	}
	else
	{
		rx_msg = new membuf(mtu_rx);
	}

	if (rx_msg == nullptr)
	{
		return -ENOMEM;
	}

	if(tx_msg)
	{
		tx_msg->set_size(mtu_tx_max);
	}
	else
	{
		tx_msg = new membuf(mtu_tx_max);
	}

	if (tx_msg == nullptr)
	{
		return -ENOMEM;
	}

	return 0;
}

//------------------------------------------------------------------------------
/* Function obex_response_to_string(rsp)
 *
 *    Return a string of an OBEX-response
 */
char *obex_response_to_string(int rsp)
{
	switch (rsp) 
	{
	case OBEX_RSP_CONTINUE:
		return "Continue";
	case OBEX_RSP_SWITCH_PRO:
		return "Switching protocols";
	case OBEX_RSP_SUCCESS:
		return "OK, Success";
	case OBEX_RSP_CREATED:
		return "Created";
	case OBEX_RSP_ACCEPTED:
		return "Accepted";
	case OBEX_RSP_NO_CONTENT:
		return "No Content";
	case OBEX_RSP_BAD_REQUEST:
		return "Bad Request";
	case OBEX_RSP_UNAUTHORIZED:
		return "Unauthorized";
	case OBEX_RSP_PAYMENT_REQUIRED:
		return "Payment required";
	case OBEX_RSP_FORBIDDEN:
		return "Forbidden";
	case OBEX_RSP_NOT_FOUND:
		return "Not found";
	case OBEX_RSP_METHOD_NOT_ALLOWED:
		return "Method not allowed";
	case OBEX_RSP_CONFLICT:
		return "Conflict";
	case OBEX_RSP_INTERNAL_SERVER_ERROR:
		return "Internal server error";
	case OBEX_RSP_NOT_IMPLEMENTED:
		return "Not implemented!";
	case OBEX_RSP_DATABASE_FULL:
		return "Database full";
	case OBEX_RSP_DATABASE_LOCKED:
		return "Database locked";
	default:
		return "Unknown response";
	}
}


//------------------------------------------------------------------------------
/*Function obex_deliver_event ()
 *    Deliver an event to app.
*/
void obex::deliver_event( obex_event event, obex_cmd cmd, obex_rsp rsp, bool delete_object )
{
	CObexObject* pobject = this->object;

	if (delete_object)
	{
		this->object = nullptr;
	}

	eventcb( this, pobject, mode, event, cmd, rsp );

	if( delete_object )
	{
		delete pobject;
	}
}

//------------------------------------------------------------------------------
bool obex::data_request_init()
{
	buf_t* msg = tx_msg;
	int err;

	msg->clear(msg->get_length());
	err = msg->set_size(mtu_tx);
	
	if (err)
	{
		return false;
	}
	msg->append(nullptr, sizeof(obex_common_hdr));
	return true;
}


//------------------------------------------------------------------------------
/** Prepare response or command code along with optional headers/data to send.
 *
 * The caller is supposed to reserve the size of struct obex_common_hdr at the
 * begin of the message buffer, e.g. using data_request_init()
 *
 * @param self the obex instance
 * @param msg the message buffer
 * @opcode the message opcode
 */
void obex::data_request_prepare(int opcode)
{
	buf_t *msg = tx_msg;
	obex_common_hdr_t* hdr = (obex_common_hdr_t*)(msg->get());

	// alignment is assured here
	hdr->opcode = opcode;
	hdr->len = htons((uint16_t)msg->get_length());

	//DUMPBUFFER(1, "Tx", msg);
}

//------------------------------------------------------------------------------
/** Transmit some data from the TX message buffer. */
static bool obex_data_request_transmit(obex_t *self)
{
	buf_t *msg = self->tx_msg;

	if (msg->get_length()) 
	{
		ssize_t status = obex_transport_write(self, msg);
		if (status > 0)
		{
			msg->clear(status);
		}
		else if (status < 0) 
		{
			DEBUG(4, "Send error\n");
			return false;
		}
	}
	return true;
}

//------------------------------------------------------------------------------
static result_t obex_mode(obex_t *self)
{
	switch (self->mode) 
	{
	case OBEX_MODE_SERVER:
		return self->server();

	case OBEX_MODE_CLIENT:
		return self->client();

	default:
		return RESULT_ERROR;
	}
}

//------------------------------------------------------------------------------
obex_data_direction obex::get_data_direction()
{
	if (state == STATE_IDLE)
	{
		return OBEX_DATA_IN;
	}
	else if (substate == SUBSTATE_RX)
	{
		return OBEX_DATA_IN;
	}
	else if (substate == SUBSTATE_TX)
	{
		return OBEX_DATA_OUT;
	}
	else
		return OBEX_DATA_NONE;
}

//------------------------------------------------------------------------------
result_t obex::handle_input()
{
	result_t ret = obex_transport_handle_input(this);

	if (ret != RESULT_SUCCESS)
	{
		return ret;
	}

	if (obex_transport_is_server(this)) 
	{
		DEBUG(4, "Data available on server socket\n");
		if (init_flags & OBEX_FL_KEEPSERVER)
		{
			// Tell the app to perform the OBEX_Accept()
			deliver_event(OBEX_EV_ACCEPTHINT, (obex_cmd)0, (obex_rsp)0, FALSE);
		}
		else
		{
			obex_transport_accept(this, this);
		}

		return RESULT_SUCCESS;
	} 
	else 
	{
		DEBUG(4, "Data available on client socket\n");
		return (result_t)(data_indication());
	}
}

//------------------------------------------------------------------------------
static bool obex_check_srm_input(obex_t *self)
{
	if (self->object->GetResponseMode() == OBEX_RSP_MODE_SINGLE && !(self->srm_flags & OBEX_SRM_FLAG_WAIT_LOCAL) &&
	    ((self->mode == OBEX_MODE_CLIENT && self->state == STATE_REQUEST) || (self->mode == OBEX_MODE_SERVER && self->state == STATE_RESPONSE)))
	{
		result_t ret = self->handle_input();
		if (ret == RESULT_TIMEOUT) 
		{
			self->substate = SUBSTATE_TX_PREPARE;
			return false;
		}
	}
	return true;
}

//------------------------------------------------------------------------------
/*Function obex_work (self)
 *
 *    Do some work on the current transferred object.
*/
result_t obex::work()
{
	result_t ret;

	if (state == STATE_IDLE) 
	{
		ret = handle_input();
		if (ret != RESULT_SUCCESS)
		{
			return ret;
		}
	} 
	else if (substate == SUBSTATE_RX) 
	{
		if (obex_check_srm_input(this)) 
		{
			ret = handle_input();
			if (ret != RESULT_SUCCESS)
			{
				return ret;
			}
		}
	} 
	else if (substate == SUBSTATE_TX) 
	{
		if (!obex_msg_tx_status()) 
		{
			if (!obex_data_request_transmit(this)) 
			{
				obex_cmd cmd = OBEX_CMD_ABORT;

				if (object)
				{
					cmd = object->getcmd();
				}
		
				deliver_event( OBEX_EV_LINKERR, cmd, (obex_rsp)0, TRUE);
				mode = OBEX_MODE_SERVER;
				state = STATE_IDLE;
				return RESULT_ERROR;
			}

			if (!obex_msg_tx_status())
			{
				return RESULT_TIMEOUT;
			}
		}
	}

	return obex_mode(this);
}


//------------------------------------------------------------------------------
// Read a message from transport into the RX message buffer.
result_t obex::data_indication()
{
	obex_common_hdr_t* hdr;
	buf_t *msg;
	int actual;
	unsigned int size;

	DEBUG(4, "\n");

	obex_return_val_if_fail(this != NULL, RESULT_ERROR);

	msg = rx_msg;

	/* First we need 3 bytes to be able to know how much data to read */
	if (msg->get_length() < sizeof(*hdr))  
	{
		size_t readsize = sizeof(*hdr) - msg->get_length();
		actual = obex_transport_read(this, readsize);

		DEBUG(4, "Got %d bytes\n", actual);

		/* Check if we are still connected */
		/* do not error if the data is from non-empty but partial buffer (custom transport) */
		if (actual < 0) 
		{
			deliver_event( OBEX_EV_LINKERR, (obex_cmd)0, (obex_rsp)0, TRUE);
			return RESULT_ERROR;
		}
		if (actual == 0)
			return RESULT_TIMEOUT;
	}

	// If we have 3 bytes data we can decide how big the packet is
	if (msg->get_length() >= sizeof(*hdr)) 
	{
		hdr = (obex_common_hdr_t*)(msg->get() );
		size = ntohs(hdr->len);

		actual = 0;
		if (msg->get_length() < size) 
		{
			size_t readsize = size - msg->get_length();
			actual = obex_transport_read(this, readsize);

			/* Check if we are still connected */
			/* do not error if the data is from non-empty
			 * but partial buffer (custom transport) */
			if (actual < 0) 
			{
				deliver_event( OBEX_EV_LINKERR, (obex_cmd)0, (obex_rsp)0, TRUE);
				return RESULT_ERROR;
			}
			if (actual == 0)
				return RESULT_TIMEOUT;
		}
	} 
	else 
	{
		/* Wait until we have at least 3 bytes data */
		DEBUG(3, "Need at least 3 bytes got only %lu!\n", (unsigned long)msg->get_length());
		return RESULT_SUCCESS;
        }

	/* New data has been inserted at the end of message */
	DEBUG(1, "Got %d bytes msg len=%lu\n", actual, (unsigned long)msg->get_length());

	/*
	 * Make sure that the buffer we have, actually has the specified
	 * number of bytes. If not the frame may have been fragmented, and
	 * we will then need to read more from the socket.
	 */

	/* Make sure we have a whole packet */
	if (size > msg->get_length()) 
	{
		DEBUG(3, "Need more data, size=%d, len=%lu!\n", size, (unsigned long)msg->get_length());

		/* I'll be back! */
		return RESULT_SUCCESS;
	}

	//DUMPBUFFER(2, "Rx", msg);

	return RESULT_SUCCESS;
}

//------------------------------------------------------------------------------
// Remove message from RX message buffer after evaluation
void obex::data_receive_finished()
{
	buf_t* msg = rx_msg;
	unsigned int size = obex_msg_get_len();

	DEBUG(4, "Pulling %u bytes\n", size);
	msg->clear(size);
}

//------------------------------------------------------------------------------
/*Function obex_cancel_request ()
 *
 *    Cancel an ongoing request
 */
int obex::cancelrequest(int nice)
{
	// If we have no ongoing request do nothing
	if (object == nullptr)
	{
		return 0;
	}

	// Abort request without sending abort
	if (!nice) 
	{
		// Deliver event will delete the object
		deliver_event( OBEX_EV_ABORT, (obex_cmd)0, (obex_rsp)0, TRUE);
		tx_msg->clear(tx_msg->get_length());
		rx_msg->clear(rx_msg->get_length());

		// Since we didn't send ABORT to peer we are out of sync and need to disconnect transport immediately, so we signal link error to app
		deliver_event( OBEX_EV_LINKERR, (obex_cmd)0, (obex_rsp)0, FALSE);
		return 1;

	} 
	else 
	{
		// The client or server code will take action at the right time.
		object->SetAbort( true );
		return 1;
	}
}
