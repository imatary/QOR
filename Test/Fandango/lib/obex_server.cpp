/**
	\file obex_server.c
	Handle server operations.
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
class obex;
class CObexObject;

#include "obex_incl.h"
#include "defines.h"
#include "databuffer.h"

#include <stdlib.h>
#include <stdio.h>

 //------------------------------------------------------------------------------
__inline obex_cmd obex::msg_get_cmd() const
{
	int opcode = obex_msg_get_opcode();

	if (opcode < 0)
		return OBEX_CMD_ABORT;
	else
		return (obex_cmd)(opcode & ~OBEX_FINAL);
}

//------------------------------------------------------------------------------
__inline int obex::msg_get_final() const
{
	int opcode = obex_msg_get_opcode();

	if (opcode < 0)
		return 0;
	else
		return opcode & OBEX_FINAL;
}

//------------------------------------------------------------------------------
static result_t obex_server_abort_tx(obex_t *self)
{
	enum obex_cmd cmd = OBEX_CMD_ABORT;

	if (self->object)
	{
		cmd = self->object->GetCommand();
	}

	self->deliver_event(self->abort_event, cmd, (obex_rsp)0, true);
	self->state = STATE_IDLE;

	return RESULT_SUCCESS;
}

//------------------------------------------------------------------------------
static result_t obex_server_abort_tx_prepare(obex_t *self, enum obex_rsp opcode, enum obex_event event)
{
	DEBUG(4, "STATE: ABORT/PREPARE_TX\n");

	self->abort_event = event;
	self->state = STATE_ABORT;
	self->substate = SUBSTATE_TX;

	if (!self->data_request_init())
	{
		return RESULT_ERROR;
	}

	self->data_request_prepare( opcode | OBEX_FINAL);
	return RESULT_SUCCESS;
}

//------------------------------------------------------------------------------
/** Generate response to ABORT request from client */
static result_t obex_server_abort_by_client(obex_t *self)
{
	return obex_server_abort_tx_prepare(self, OBEX_RSP_SUCCESS, OBEX_EV_ABORT);
}

//------------------------------------------------------------------------------
/** Generate response when application has set object_t::abort to true */
static result_t obex_server_abort_by_application(obex_t *self)
{
	// Use the error code provided by the application...
	obex_rsp opcode = self->object->GetLastResponse();

	/** ...but do not send continue/success. */
	if (opcode == OBEX_RSP_CONTINUE || opcode == OBEX_RSP_SUCCESS)
	{
		opcode = OBEX_RSP_INTERNAL_SERVER_ERROR;
	}

	return obex_server_abort_tx_prepare(self, opcode, OBEX_EV_ABORT);
}

//------------------------------------------------------------------------------
/** Generate response when we failed to parse the request packet */
static result_t obex_server_bad_request(obex_t *self)
{
	return obex_server_abort_tx_prepare(self, OBEX_RSP_BAD_REQUEST, OBEX_EV_PARSEERR);
}

//------------------------------------------------------------------------------
static result_t obex_server_response_tx_prepare(obex_t *self)
{
	DEBUG(4, "STATE: RESPONSE/PREPARE_TX\n");

	if (self->object->IsAborting())
	{
		return obex_server_abort_by_application(self);
	}

	/* As a server, the final bit is always SET, and the "real final" packet
	 * is distinguished by being SUCCESS instead of CONTINUE.
	 * So, force the final bit here. */
	if (!self->obex_msg_prepare(self->object, TRUE))
	{
		return RESULT_ERROR;
	}

	self->substate = SUBSTATE_TX;
	return RESULT_SUCCESS;
}

//------------------------------------------------------------------------------
static result_t obex_server_response_tx(obex_t *self)
{
	int cmd = self->object->GetCommand();

	// Made some progress 
	self->deliver_event( OBEX_EV_PROGRESS, (obex_cmd)cmd, (obex_rsp)0, false);
	if( self->object->finished( TRUE ) )
	{
		self->state = STATE_IDLE;
		/* Response sent and object finished! */
		if (cmd == OBEX_CMD_DISCONNECT) 
		{
			DEBUG(2, "CMD_DISCONNECT done. Resetting MTU!\n");
			self->mtu_tx = OBEX_MINIMUM_MTU;
			self->rsp_mode = OBEX_RSP_MODE_NORMAL;
			self->srm_flags = 0;
		}
		self->deliver_event(OBEX_EV_REQDONE, (obex_cmd)cmd, (obex_rsp)0, true);

	} 
	else if (self->object->GetResponseMode() == OBEX_RSP_MODE_SINGLE && !(self->srm_flags & OBEX_SRM_FLAG_WAIT_LOCAL))
	{
		self->substate = SUBSTATE_TX_PREPARE;
		return obex_server_response_tx_prepare(self);

	} 
	else 
	{
		self->substate = SUBSTATE_RX;
	}

	return RESULT_SUCCESS;
}

//------------------------------------------------------------------------------
static result_t obex_server_response_rx(obex_t *self)
{
	enum obex_cmd cmd;

	DEBUG(4, "STATE: RESPONSE/RECEIVE_RX\n");

	if (!self->obex_msg_rx_status()) 
	{
		if (self->object->GetResponseMode() == OBEX_RSP_MODE_SINGLE && !(self->srm_flags & OBEX_SRM_FLAG_WAIT_LOCAL))
		{
			self->substate = SUBSTATE_TX_PREPARE;
			return obex_server_response_tx_prepare(self);
		}

		return RESULT_SUCCESS;
	}

	/* Single response mode makes it possible for the client to send
	 * the next request (e.g. PUT) while still receiving the last
	 * multi-packet response. So we must not consume any request
	 * except ABORT. For Normal response mode, this other request is an
	 * error. */
	cmd = self->msg_get_cmd();
	if (cmd == OBEX_CMD_ABORT) 
	{
		DEBUG(1, "Got OBEX_ABORT request!\n");
		self->data_receive_finished();
		return obex_server_abort_by_client(self);

	} 
	else if (cmd == self->object->getcmd() ) 
	{
		int ret = self->obex_msg_receive(self->object);
		self->data_receive_finished();
		if (ret < 0)
		{
			return obex_server_bad_request(self);
		}

		self->substate = SUBSTATE_TX_PREPARE;
		return obex_server_response_tx_prepare(self);

	} 
	else 
	{
		if (self->object->GetResponseMode() == OBEX_RSP_MODE_SINGLE)
		{
			self->substate = SUBSTATE_TX_PREPARE;
			return obex_server_response_tx_prepare(self);
		}

		self->data_receive_finished();
		return obex_server_bad_request(self);
	}
}

//------------------------------------------------------------------------------
static result_t obex_server_request_tx(obex_t *self)
{
	obex_cmd cmd = self->object->GetCommand();
	obex_rsp rsp = self->object->GetResponse();

	if (rsp == OBEX_RSP_CONTINUE) 
	{
		self->deliver_event(OBEX_EV_PROGRESS, cmd, rsp, false);
		self->substate = SUBSTATE_RX;

	} 
	else 
	{
		self->deliver_event( OBEX_EV_REQDONE, cmd, rsp, true);
		self->state = STATE_IDLE;
	}

	return RESULT_SUCCESS;
}

//------------------------------------------------------------------------------
static result_t obex_server_request_tx_prepare(obex_t *self)
{
	DEBUG(4, "STATE: REQUEST/PREPARE_TX\n");

	if (self->object->GetResponseMode() == OBEX_RSP_MODE_NORMAL || (self->object->GetResponseMode() == OBEX_RSP_MODE_SINGLE && self->srm_flags & OBEX_SRM_FLAG_WAIT_REMOTE))
	{
		if (self->object->IsAborting())
		{
			return obex_server_abort_by_application(self);
		}

		if (!self->obex_msg_prepare(self->object, FALSE))
		{
			return RESULT_ERROR;
		}

		self->substate = SUBSTATE_TX;
		return RESULT_SUCCESS;

	} 
	else 
	{
		self->substate = SUBSTATE_RX;
		return RESULT_SUCCESS;
	}
}

//------------------------------------------------------------------------------
static result_t obex_server_request_rx(obex_t *self, int first)
{
	int deny = 0;
	uint64_t filter;
	enum obex_cmd cmd;
	int final;

	DEBUG(4, "STATE: REQUEST/RECEIVE_RX\n");

	if (!self->obex_msg_rx_status())
		return RESULT_SUCCESS;
	cmd = self->msg_get_cmd();
	final = self->msg_get_final();

	/* Abort? */
	if (cmd == OBEX_CMD_ABORT) 
	{
		DEBUG(1, "Got OBEX_ABORT request!\n");
		self->data_receive_finished();
		return obex_server_abort_by_client(self);

	} 
	else if (cmd != self->object->getcmd() ) 
	{
		/* The cmd-field of this packet is not the
		 * same as int the first fragment. Bail out! */
		self->data_receive_finished();
		return obex_server_bad_request(self);
	}

	/* Get the non-header data and look at all non-body headers.
	 * Leaving the body headers out here has advantages:
	 * - we don't need to assign a data buffer if the user rejects
	 *   the request
	 * - the user can inspect all first-packet headers before
	 *   deciding about stream mode
	 * - the user application actually received the REQCHECK when
	 *   always using stream mode
	 */
	filter = (1 << OBEX_HDR_ID_BODY | 1 << OBEX_HDR_ID_BODY_END);
	
	/* Some commands needs special treatment (data outside headers) */
	switch (cmd) 
	{
	case OBEX_CMD_CONNECT:
		self->object->SetHeaderOffset( 4 );
		break;

	case OBEX_CMD_SETPATH:
		self->object->SetHeaderOffset( 2 );
		break;

	default:
		break;
	}

	if (self->obex_msg_receive_filtered(self->object, filter, true) < 0) 
	{
		self->data_receive_finished();
		return obex_server_bad_request(self);
	}

	/* Let the user decide whether to accept or deny a
	 * multi-packet request by examining all headers in
	 * the first packet */
	if (first)
	{
		self->deliver_event( OBEX_EV_REQCHECK, cmd, (obex_rsp)0, false);
	}

	/* Everything except 0x1X and 0x2X means that the user
	 * callback denied the request. In the denied cases
	 * treat the last packet as a final one but don't
	 * bother about body headers and don't signal
	 * OBEX_EV_REQ. */
	switch ((self->object->GetResponse() & ~OBEX_FINAL) & 0xF0) 
	{
	case OBEX_RSP_CONTINUE:
	case OBEX_RSP_SUCCESS:
		if (self->obex_msg_receive_filtered( self->object, ~filter, FALSE) < 0)
		{
			self->data_receive_finished();
			return obex_server_bad_request(self);
		}
		break;

	default:
		final = 1;
		deny = 1;
		break;
	}

	self->data_receive_finished();

	/* Connect needs some extra special treatment */
	if (cmd == OBEX_CMD_CONNECT) 
	{
		DEBUG(4, "Got CMD_CONNECT\n");
		if (!final || self->parse_connectframe(self->object) < 0)
		{
			return obex_server_bad_request(self);
		}
	}

	if (!final) 
	{
		self->substate = SUBSTATE_TX_PREPARE;
		return obex_server_request_tx_prepare(self);

	} 
	else 
	{
		/* Tell the app that a whole request has arrived. While this event is delivered the
		 * app should append the headers that should be in the response */
		if (!deny) 
		{
			DEBUG(4, "We got a request!\n");
			self->deliver_event( OBEX_EV_REQ, cmd, (obex_rsp)0, false);
		}

		// More connect-magic woodoo stuff
		if (cmd == OBEX_CMD_CONNECT)
		{
			self->insert_connectframe(self->object);
		}

		self->state = STATE_RESPONSE;
		self->substate = SUBSTATE_TX_PREPARE;
		return obex_server_response_tx_prepare(self);
	}
}

//------------------------------------------------------------------------------
static result_t obex_server_idle(obex_t *self)
{
	enum obex_cmd cmd;

	/* Nothing has been recieved yet, so this is probably a new request */
	DEBUG(4, "STATE: IDLE\n");
	
	if (!self->obex_msg_rx_status())
		return RESULT_SUCCESS;
	cmd = self->msg_get_cmd();

	if (self->object) 
	{
		/* What shall we do here? I don't know!*/
		DEBUG(0, "Got a new server-request while already having one!\n");
		return RESULT_ERROR;
	}

	/* If ABORT command is done while we are not handling another command,
	 * we don't need to send a request hint to the application */
	if (cmd == OBEX_CMD_ABORT) 
	{
		DEBUG(1, "Got OBEX_ABORT request!\n");
		self->data_receive_finished();
		return obex_server_abort_by_client(self);
	}

	self->object = new CObexObject();
	if (self->object == NULL) 
	{
		DEBUG(1, "Allocation of object failed!\n");
		return RESULT_ERROR;
	}
	/* Remember the initial command of the request.*/
	self->object->setcmd( cmd );
	self->object->SetResponseMode( self->rsp_mode );

	/* Hint app that something is about to come so that the app can deny a PUT-like request early, or set the header-offset */
	self->deliver_event( OBEX_EV_REQHINT, cmd, (obex_rsp)0, false);

	/* Check the response from the REQHINT event */
	switch ((self->object->GetResponse() & ~OBEX_FINAL) & 0xF0) 
	{
	case OBEX_RSP_CONTINUE:
	case OBEX_RSP_SUCCESS:
		self->state = STATE_REQUEST;
		self->substate = SUBSTATE_RX;
		return obex_server_request_rx(self, 1);

	default:
		self->data_receive_finished();
		self->state = STATE_RESPONSE;
		self->substate = SUBSTATE_TX_PREPARE;
		return obex_server_response_tx_prepare(self);
	}
}

//------------------------------------------------------------------------------
/*Function obex_server ()
 *
   Handle server-operations
 */
result_t obex::server()
{
	DEBUG(4, "\n");

	switch (state) 
	{
	case STATE_IDLE:
		return obex_server_idle(this);

	case STATE_REQUEST:
		switch (substate) 
		{
		case SUBSTATE_RX:
			return obex_server_request_rx(this, 0);

		case SUBSTATE_TX_PREPARE:
			return obex_server_request_tx_prepare(this);

		case SUBSTATE_TX:
			return obex_server_request_tx(this);

		default:
			break;
		}
		break;

	case STATE_RESPONSE:
		switch (substate) 
		{
		case SUBSTATE_RX:
			return obex_server_response_rx(this);

		case SUBSTATE_TX_PREPARE:
			return obex_server_response_tx_prepare(this);

		case SUBSTATE_TX:
			return obex_server_response_tx(this);

		default:
			break;
		}
		break;

	case STATE_ABORT:
		switch (substate) 
		{
		case SUBSTATE_TX:
			return obex_server_abort_tx(this);

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
