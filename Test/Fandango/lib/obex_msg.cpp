/**
 * @file obex_msg.c
 *
 * Bridge between obex object and raw message buffer.
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

#include "obex_incl.h"
#include "defines.h"
#include "obex_main.h"
#include "obex_object.h"
#include "obex_hdr.h"
#include "defines.h"

//------------------------------------------------------------------------------
static unsigned int obex_srm_tx_flags_decode (uint8_t flag)
{
	switch (flag) 
	{
	case 0x00:
		return OBEX_SRM_FLAG_WAIT_LOCAL;

	case 0x01:
		return OBEX_SRM_FLAG_WAIT_REMOTE;

	case 0x02:
		return (OBEX_SRM_FLAG_WAIT_LOCAL | OBEX_SRM_FLAG_WAIT_REMOTE);

	default:
		return 0;
	}
}

//------------------------------------------------------------------------------
static unsigned int obex_srm_rx_flags_decode (uint8_t flag)
{
	switch (flag) 
	{
	case 0x00:
		return OBEX_SRM_FLAG_WAIT_REMOTE;

	case 0x01:
		return OBEX_SRM_FLAG_WAIT_LOCAL;

	case 0x02:
		return (OBEX_SRM_FLAG_WAIT_LOCAL | OBEX_SRM_FLAG_WAIT_REMOTE);

	default:
		return 0;
	}
}

//------------------------------------------------------------------------------
bool obex::obex_msg_post_prepare(const obex_hdr_it *from, const obex_hdr_it *to)
{
	obex_hdr_it it;
	CObexHeader* hdr;

	it.init_from(from);
	hdr = it.get();

	// loop over all headers in that are non-NULL and finished...
	while (hdr != nullptr && hdr->is_finished()) 
	{
		if (rsp_mode == OBEX_RSP_MODE_SINGLE && hdr->get_id() == OBEX_HDR_ID_SRM_FLAGS)
		{
			const uint8_t* data = (const uint8_t*)(hdr->get_data_ptr() );

			srm_flags &= ~OBEX_SRM_FLAG_WAIT_REMOTE;
			srm_flags |= obex_srm_tx_flags_decode(data[0]);
		}

		/* ...but only in the range [from..to]. The last entry
		 * must be included if it is finished. */
		if( it.equals(to))
		{
			break;
		}

		it.next();
		hdr = it.get();
	}

	return true;
}

//------------------------------------------------------------------------------
bool obex::obex_msg_prepare(CObexObject* pobject, bool allowfinal )
{
	buf_t* txmsg = tx_msg;
	uint16_t tx_left = mtu_tx - sizeof(obex_common_hdr);
	int real_opcode;
	obex_hdr_it it;

	it.init_from(object->GetTXIterator());

	if (!data_request_init())
	{
		return false;
	}

	if (!pobject->append_data(txmsg, tx_left))
	{
		return false;
	}

	real_opcode = object->get_opcode( allowfinal, mode );
	DEBUG(4, "Generating packet with opcode %d\n", real_opcode);
	data_request_prepare( real_opcode);

	return obex_msg_post_prepare(&it, object->GetTXIterator());
}

//------------------------------------------------------------------------------
int obex::obex_msg_getspace(CObexObject* pobject, unsigned int flags )
{
	size_t objlen = sizeof(obex_common_hdr);

	if (flags & OBEX_FL_FIT_ONE_PACKET)
		objlen += pobject->get_size();

	return mtu_tx - objlen;
}

//------------------------------------------------------------------------------
/** Check if the RX message buffer contains at least one full message. */
bool obex::obex_msg_rx_status() const
{
	buf_t *msg = rx_msg;
	obex_common_hdr_t* hdr = (obex_common_hdr_t*)(msg->get());

	return (msg->get_length() >= sizeof(*hdr) && msg->get_length() >= ntohs(hdr->len));
}

//------------------------------------------------------------------------------
/** Check if the TX message buffer was sent completely */
bool obex::obex_msg_tx_status() const
{
	buf_t *msg = tx_msg;

	return (msg->get_length() == 0);
}

//------------------------------------------------------------------------------
int obex::obex_msg_get_opcode() const
{
	buf_t *msg = rx_msg;
	obex_common_hdr_t* hdr = (obex_common_hdr_t*)(msg->get());

	if (!obex_msg_rx_status())
	{
		return -1;
	}

	return hdr->opcode;
}

//------------------------------------------------------------------------------
size_t obex::obex_msg_get_len() const
{
	buf_t* msg = rx_msg;
	obex_common_hdr_t* hdr;

	if (!obex_msg_rx_status())
	{
		return 0;
	}

	hdr = (obex_common_hdr_t*)(msg->get());
	return (size_t)ntohs(hdr->len);
}

//------------------------------------------------------------------------------
void obex::obex_msg_pre_receive()
{
	if(rsp_mode == OBEX_RSP_MODE_SINGLE)
	{
		srm_flags &= ~OBEX_SRM_FLAG_WAIT_LOCAL;
	}
}


//------------------------------------------------------------------------------
int obex::obex_msg_post_receive()
{
	CObexHeader* hdr;

	if (!object->GetRXIterator())
	{
		return 0;
	}

	// loop over all new headers
	hdr = object->GetRXIterator()->get();
	while (hdr != nullptr) 
	{
		if (rsp_mode == OBEX_RSP_MODE_SINGLE && hdr->get_id() == OBEX_HDR_ID_SRM_FLAGS)
		{
			const uint8_t* data = (const uint8_t*)(hdr->get_data_ptr());

			srm_flags |= obex_srm_rx_flags_decode(data[0]);
		}

		object->GetRXIterator()->next();
		hdr = object->GetRXIterator()->get();
	}

	return 0;
}

//------------------------------------------------------------------------------
int obex::obex_msg_receive_filtered(CObexObject* pobject, uint64_t filter, bool first_run )
{
	buf_t *msg = rx_msg;
	size_t len;
	const uint8_t* data;
	int hlen;

	DEBUG(4, "\n");

	if (!obex_msg_rx_status())
	{
		return 0;
	}

	data = (const uint8_t*)(msg->get());
	len = sizeof(obex_common_hdr);
	
	if (first_run)
	{
		obex_msg_pre_receive();
	}

	data += len;
	len = obex_msg_get_len() - len;
	if (first_run && len > 0)
	{
		if (pobject->receive_nonhdr_data(data, len) < 0)
		{
			return -1;
		}
	}

	data += pobject->GetHeaderOffset();
	len -= pobject->GetHeaderOffset();
	if (len > 0) 
	{
		hlen = pobject->receive_headers( data, len, filter );
		if (hlen < 0)
		{
			return hlen;
		}
	}	

	return obex_msg_post_receive();
}

//------------------------------------------------------------------------------
int obex::obex_msg_receive(CObexObject* pobject)
{
	return obex_msg_receive_filtered( pobject, 0, TRUE);
}
