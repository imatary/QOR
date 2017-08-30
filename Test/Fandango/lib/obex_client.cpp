/**
	\file obex_client.c
	Handle client operations.
	OpenOBEX library - Free implementation of the Object Exchange protocol.

	Copyright (c) 1999-2000 Pontus Fuchs, All Rights Reserved.

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

#include "obex_main.h"
#include "obex_object.h"
struct obex;
class CObexObject;

#include "obex_incl.h"
#include "defines.h"
#include "databuffer.h"

#include <stdlib.h>
#include <stdio.h>

//------------------------------------------------------------------------------
static __inline obex_rsp msg_get_rsp( obex_t* self )
{
	int opcode = self->obex_msg_get_opcode();

	if (opcode < 0)
	{
		return OBEX_RSP_BAD_REQUEST;
	}
	else
	{
		return (obex_rsp)(opcode & ~OBEX_FINAL);
	}
}

//------------------------------------------------------------------------------
static __inline uint16_t msg_get_len( const buf_t* msg)
{
	if (msg) 
	{
		obex_common_hdr_t* hdr = reinterpret_cast< obex_common_hdr_t* >( msg->get() );
		return ntohs(hdr->len);
	} 
	else
	{
		return 0;
	}
}

//------------------------------------------------------------------------------
static result_t obex_client_abort_tx( obex_t* self )
{
	self->substate = SUBSTATE_RX;
	return RESULT_SUCCESS;
}

//------------------------------------------------------------------------------
static result_t obex_client_abort_tx_prepare( obex_t* self )
{
	DEBUG(4, "STATE: ABORT/TX_PREPARE\n");

	if (!self->data_request_init())
	{
		return RESULT_ERROR;
	}

	self->data_request_prepare(OBEX_CMD_ABORT);
	self->substate = SUBSTATE_TX;
	return RESULT_SUCCESS;
}

//------------------------------------------------------------------------------
static result_t obex_client_abort_rx( obex_t* self )
{
	int ret = RESULT_SUCCESS;
	obex_rsp rsp;
	int event = OBEX_EV_LINKERR;

	DEBUG(4, "STATE: ABORT/RX\n");

	if (!self->obex_msg_rx_status())
	{
		return RESULT_SUCCESS;
	}

	rsp = msg_get_rsp(self);

	if (rsp == OBEX_RSP_SUCCESS)
	{
		event = OBEX_EV_ABORT;
	}

	self->deliver_event( (obex_event)event, self->object->GetCommand(), rsp, true );

	if (event == OBEX_EV_LINKERR)
	{
		ret = RESULT_ERROR;
	}

	self->mode = OBEX_MODE_SERVER;
	self->state = STATE_IDLE;
	return (result_t)ret;
}

//------------------------------------------------------------------------------
static result_t obex_client_response_tx( obex_t* self )
{
	obex_cmd cmd = self->object->GetCommand();
	obex_rsp rsp = OBEX_RSP_CONTINUE;

	self->deliver_event( OBEX_EV_PROGRESS, cmd, rsp, false );
	self->substate = SUBSTATE_RX;
	return RESULT_SUCCESS;
}

//------------------------------------------------------------------------------
static result_t obex_client_response_tx_prepare( obex_t* self )
{
	DEBUG(4, "STATE: RESPONSE/TX_PREPARE\n");

	// Sending ABORT is allowed even during SRM
	if (self->object->IsAborting()) 
	{
		self->state = STATE_ABORT;
		return obex_client_abort_tx_prepare(self);
	}

	if (self->object->GetResponseMode() == OBEX_RSP_MODE_NORMAL || (self->object->GetResponseMode() == OBEX_RSP_MODE_SINGLE && self->srm_flags & OBEX_SRM_FLAG_WAIT_REMOTE))
	{
		if (!self->obex_msg_prepare(self->object, TRUE))
		{
			return RESULT_ERROR;
		}
		self->substate = SUBSTATE_TX;

	} 
	else 
	{
		self->substate = SUBSTATE_RX;
	}

	return RESULT_SUCCESS;
}

//------------------------------------------------------------------------------
static result_t obex_client_response_rx(obex_t *self)
{
	obex_rsp rsp;

	DEBUG(4, "STATE: RESPONSE/RX\n");

	if (!self->obex_msg_rx_status())
	{
		return RESULT_SUCCESS;
	}
	rsp = msg_get_rsp(self);

	switch (self->object->GetCommand())
	{
	case OBEX_CMD_CONNECT:
		DEBUG(2, "We expect a connect-rsp\n");
		self->object->SetHeaderOffset(4);
		break;

	case OBEX_CMD_DISCONNECT:
		// Response of a CMD_DISCONNECT needs some special treatment.
		DEBUG(2, "CMD_DISCONNECT done. Resetting MTU!\n");
		self->mtu_tx = OBEX_MINIMUM_MTU;
		self->rsp_mode = OBEX_RSP_MODE_NORMAL;
		self->srm_flags = 0;
		break;

	default:
		break;
	}

	if (!self->object->IsAborting())
	{
		// Receive any headers
		result_t ret = (result_t)(self->obex_msg_receive(self->object));
		if (ret == RESULT_ERROR) 
		{
			self->deliver_event(OBEX_EV_PARSEERR, self->object->GetCommand(), (obex_rsp)0, true);
			self->mode = OBEX_MODE_SERVER;
			self->state = STATE_IDLE;
			self->data_receive_finished();
			return RESULT_ERROR;
		}
	}
	self->data_receive_finished();

	// Response of a CMD_CONNECT needs some special treatment.
	if (self->object->GetCommand() == OBEX_CMD_CONNECT)
	{
		DEBUG(2, "We expect a connect-rsp\n");
		if (rsp != OBEX_RSP_SUCCESS || self->parse_connectframe(self->object) < 0)
		{
			self->deliver_event(OBEX_EV_PARSEERR, self->object->GetCommand(), (obex_rsp)0, true);
			self->mode = OBEX_MODE_SERVER;
			self->state = STATE_IDLE;
			return RESULT_ERROR;
		}
	}

	// Are we done yet?
	if (rsp == OBEX_RSP_CONTINUE) 
	{
		obex_cmd cmd = self->object->GetCommand();

		DEBUG(3, "Continue...\n");
		self->deliver_event(OBEX_EV_CONTINUE, cmd, rsp, false);

		/* Return if the user cancelled the request without sending ABORT.
		 * If ABORT is being sent, we continue as usual and let the normal
		 * tx_prepare() handle it.
		 */
		if (self->object == nullptr)
		{
			return RESULT_SUCCESS;
		}

		self->substate = SUBSTATE_TX_PREPARE;
		return obex_client_response_tx_prepare(self);

	} 
	else 
	{
		obex_cmd cmd = self->object->GetCommand();

		// Notify app that client-operation is done!
		DEBUG(3, "Done! Rsp=%02x!\n", rsp);
		self->deliver_event(OBEX_EV_REQDONE, cmd, rsp, true);
		self->mode = OBEX_MODE_SERVER;
		self->state = STATE_IDLE;
		return RESULT_SUCCESS;
	}
}

//------------------------------------------------------------------------------
static result_t obex_client_request_tx( obex_t* self )
{
	self->deliver_event(OBEX_EV_PROGRESS, self->object->GetCommand(), (obex_rsp)0, false);
	if( self->object->finished( TRUE ) )
	{
		self->state = STATE_RESPONSE;
	}

	self->substate = SUBSTATE_RX;
	return RESULT_SUCCESS;
}

//------------------------------------------------------------------------------
static result_t obex_client_request_tx_prepare(obex_t *self)
{
	DEBUG(4, "STATE: REQUEST/TX_PREPARE\n");

	if (self->object->IsAborting())
	{
		self->state = STATE_ABORT;
		return obex_client_abort_tx_prepare(self);
	}

	if (!self->obex_msg_prepare(self->object, TRUE))
	{
		return RESULT_ERROR;
	}

	self->substate = SUBSTATE_TX;
	return RESULT_SUCCESS;
}

//------------------------------------------------------------------------------
static result_t obex_client_request_rx(obex_t *self)
{
	obex_rsp rsp;

	DEBUG(4, "STATE: REQUEST/RX\n");

	if (!self->obex_msg_rx_status())
	{
		return RESULT_SUCCESS;
	}
	rsp = msg_get_rsp(self);

	// Any errors from peer? Win2k will send RSP_SUCCESS after every fragment sent so we have to accept that too.
	switch (rsp) 
	{
	case OBEX_RSP_SUCCESS:
	case OBEX_RSP_CONTINUE:
		break;

	default:
		DEBUG(0, "STATE_SEND. request not accepted.\n");
		self->deliver_event( OBEX_EV_REQDONE, self->object->GetCommand(), rsp, true);
		/* This is not an Obex error, it is just that the peer
		 * doesn't accept the request */
		self->data_receive_finished();
		return RESULT_SUCCESS;
	}

	if (!self->object->IsAborting())
	{
		int ret = self->obex_msg_receive(self->object);
		if (ret < 0) 
		{
			self->deliver_event( OBEX_EV_PARSEERR, self->object->GetCommand(), (obex_rsp)0, true);
			self->mode = OBEX_MODE_SERVER;
			self->state = STATE_IDLE;
			self->data_receive_finished();
			return RESULT_ERROR;
		}
	}

	self->data_receive_finished();
	self->substate = SUBSTATE_TX_PREPARE;
	return obex_client_request_tx_prepare(self);
}

//------------------------------------------------------------------------------
//Function obex_client ()
//Handle client operations
result_t obex::client()
{
	DEBUG(4, "\n");

	switch (state) 
	{
	case STATE_REQUEST:
		switch (substate) 
		{
		case SUBSTATE_RX:
			return obex_client_request_rx(this);

		case SUBSTATE_TX_PREPARE:
			return obex_client_request_tx_prepare(this);

		case SUBSTATE_TX:
			return obex_client_request_tx(this);

		default:
			break;
		}
		break;

	case STATE_RESPONSE:
		switch (substate) 
		{
		case SUBSTATE_RX:
			return obex_client_response_rx(this);

		case SUBSTATE_TX_PREPARE:
			return obex_client_response_tx_prepare(this);

		case SUBSTATE_TX:
			return obex_client_response_tx(this);

		default:
			break;
		}
		break;

	case STATE_ABORT:
		switch (substate) 
		{
		case SUBSTATE_RX:
			return obex_client_abort_rx(this);

		case SUBSTATE_TX_PREPARE:
			return obex_client_abort_tx_prepare(this);

		case SUBSTATE_TX:
			return obex_client_abort_tx(this);

		default:
			break;
		}
		break;

	default:
		DEBUG(0, "Unknown state\n");
		break;
	}

	return RESULT_ERROR;
}
