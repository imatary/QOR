/**
	\file obex_object.cpp
	OBEX object related functions.
	OpenOBEX library - Free implementation of the Object Exchange protocol.

	Copyright (c) 1999, 2000 Pontus Fuchs, All Rights Reserved.
	Copyright (c) 1999, 2000 Dag Brattli, All Rights Reserved.

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


#include "obex_main.h"
#include "obex_object.h"
#include "obex_hdr.h"
#include "obex_body.h"
#include "obex_incl.h"
#include "defines.h"
#include "databuffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//------------------------------------------------------------------------------
CObexObject::CObexObject()
{
	setrsp(OBEX_RSP_NOT_IMPLEMENTED, OBEX_RSP_NOT_IMPLEMENTED);
}

//------------------------------------------------------------------------------
/*free_headerq(q)
 Free all headers in a header queue.
*/
static void free_headerq(slist_t *q, const CObexHeader* no_delete)
{
	DEBUG(4, "\n");
	while (!slist_is_empty(q)) 
	{
		CObexHeader* h = (CObexHeader*)(q->get() );
		q = q->remove(h);
		if (h != no_delete)
		{
			delete h;
		}
	}
}

//------------------------------------------------------------------------------
CObexObject::~CObexObject()
{
	// Free the headerqueues
	delete tx_it;
	free_headerq( tx_headerq, body );

	// Free tx non-header data
	if( tx_nonhdr_data)
	{
		delete tx_nonhdr_data;
		tx_nonhdr_data = nullptr;
	}

	// Free the headerqueues
	delete it;
	delete rx_it;
	free_headerq( rx_headerq, body );

	// Free rx non-header data
	if( rx_nonhdr_data )
	{
		delete rx_nonhdr_data;
		rx_nonhdr_data = nullptr;
	}

	if ( body != nullptr )
	{
		delete body;
		body = nullptr;
	}
}

//------------------------------------------------------------------------------
//Set command of object
void CObexObject::setcmd( obex_cmd _cmd )
{
	DEBUG(4,"%02x\n", _cmd);
	cmd = (obex_cmd)(_cmd & ~OBEX_FINAL);
}

//------------------------------------------------------------------------------
//Set the response for an object
int CObexObject::setrsp( obex_rsp _rsp, obex_rsp _lastrsp)
{
	DEBUG(4,"\n");
	rsp = _rsp;
	lastrsp = _lastrsp;
	return 1;
}

//------------------------------------------------------------------------------
size_t CObexObject::get_size()
{
	size_t objlen = 0;

	if (tx_nonhdr_data)
	{
		objlen += tx_nonhdr_data->get_length();
	}

	if( tx_it ) 
	{
		obex_hdr_it _it;
		CObexHeader* hdr;

		_it.init_from(tx_it);

		hdr = _it.get();

		while (hdr != nullptr) 
		{
			objlen += hdr->get_size();

			_it.next();
			hdr = _it.get();
		}
	}

	return objlen;
}


//------------------------------------------------------------------------------
/** Add a header to an objext TX queue
 * @deprecated
 */
int CObexObject::addheader(obex_t *self, CObexObject* object, uint8_t hi, obex_headerdata_t hv, uint32_t hv_size, unsigned int flags)
{
	int ret;
	CObexHeader* hdr;
	const void *value;
	uint32_t bq4;
	size_t size;
	obex_hdr_id id = (obex_hdr_id)(hi & OBEX_HDR_ID_MASK);
	obex_hdr_type type = (obex_hdr_type)(hi & OBEX_HDR_TYPE_MASK);
	unsigned int flags2 = OBEX_FL_COPY;

	DEBUG(4, "\n");

	if (object == nullptr)
	{
		object = self->object;
	}

	if (object == nullptr)
	{
		return -1;
	}

	if (id == OBEX_HDR_ID_BODY_END)
	{
		id = OBEX_HDR_ID_BODY;
		if (object->body)
		{
			flags &= OBEX_FL_STREAM_DATAEND;
		}
	}

	if (id == OBEX_HDR_ID_BODY) 
	{
		if (flags & OBEX_FL_STREAM_DATAEND) 
		{
			// End of stream marker
			if (object->body == nullptr) 
			{
				// A body with a single chunk.
				hdr = CObexHeader::ptr_create(OBEX_HDR_ID_BODY_END, OBEX_HDR_TYPE_BYTES, hv.bs, hv_size);
				hdr = CObexHeader::stream_create(self, hdr);
				hdr->stream_finish();
			} 
			else 
			{
				// Set the remaining data on the BODY header...
				object->body->set_data( hv.bs, hv_size );
				object->body->stream_finish();
				object->body = nullptr;
				// ...and add the BODY_END header to the end
				hdr = CObexHeader::ptr_create(OBEX_HDR_ID_BODY_END, OBEX_HDR_TYPE_BYTES, NULL, 0);
			}
			ret = 1;
			goto out;

		} 
		else if (flags & OBEX_FL_STREAM_CONTINUE)
		{
			// Continue stream after all other headers
			if (object->body == nullptr)
			{
				return -1;
			}
			object->body->stream_finish();
			hdr = CObexHeader::ptr_create(id, OBEX_HDR_TYPE_BYTES, hv.bs, hv_size);
			hdr = CObexHeader::stream_create(self, hdr);
			object->body = hdr;
			ret = 1;
			goto out;

		} 
		else if (flags & OBEX_FL_STREAM_DATA) 
		{
			// Stream data
			if (object->body == nullptr)
			{
				return -1;
			}
			object->body->set_data( hv.bs, hv_size );
			return 1;

		} 
		else if (flags & OBEX_FL_STREAM_START) 
		{
			// Is this a stream?
			DEBUG(3, "Adding stream\n");
			if (object->body)
				return -1;
			hdr = CObexHeader::ptr_create(id, OBEX_HDR_TYPE_BYTES, hv.bs, hv_size);
			hdr = CObexHeader::stream_create(self, hdr);
			object->body = hdr;
			ret = 1;
			goto out;
		}
	}

	switch (type) 
	{
	case OBEX_HDR_TYPE_UINT32:
		DEBUG(2, "4BQ header %d\n", hv.bq4);
		bq4 = htonl(hv.bq4);
		value = &bq4;
		size = 4;
		break;

	case OBEX_HDR_TYPE_UINT8:
		DEBUG(2, "1BQ header %d\n", hv.bq1);
		value = &hv.bq1;
		size = 1;
		break;

	case OBEX_HDR_TYPE_BYTES:
		DEBUG(2, "BS  header size %d\n", hv_size);
		value = hv.bs;
		size = hv_size;
		break;

	case OBEX_HDR_TYPE_UNICODE:
		DEBUG(2, "Unicode header size %d\n", hv_size);
		value = hv.bs;
		size = hv_size;
		break;

	default:
		return -1;
	}

	if (hi == OBEX_HDR_EMPTY) 
	{
		DEBUG(2, "Empty header\n");
		id = OBEX_HDR_ID_INVALID;
		type = OBEX_HDR_TYPE_INVALID;
		value = NULL;
		size = 0;
		flags2 = 0;
	}

	flags2 |= (flags & OBEX_FL_SUSPEND);
	hdr = CObexHeader::create(id, type, value, size, flags2);
	if (!hdr)
		return -1;

	ret = (int)hdr->get_size();
	// Check if you can send this header without violating MTU or OBEX_FIT_ONE_PACKET 
	if (!hdr->is_splittable() && (flags & OBEX_FL_FIT_ONE_PACKET)) 
	{
		int maxlen = self->obex_msg_getspace(object, flags);
		if (maxlen < ret) 
		{
			DEBUG(0, "Header to big\n");
			delete hdr;
			return -1;
		}
	}

out:
	object->tx_headerq = object->tx_headerq->append(hdr);

	if (object->tx_it == nullptr)
	{
		object->tx_it = new obex_hdr_it(object->tx_headerq);
	}

	return ret;
}

//------------------------------------------------------------------------------
obex_cmd CObexObject::getcmd() const
{
	return cmd;
}

//------------------------------------------------------------------------------
int CObexObject::get_opcode( bool allowfinal, obex_mode mode )
{
	int opcode = -1;

	// Decide which command to use, and if to use final-bit
	DEBUG(4, "allowfinalcmd: %d mode:%d\n", allowfinal, mode);

	switch (mode) 
	{
	case OBEX_MODE_SERVER:
		if( finished( allowfinal ) )
		{
			opcode = lastrsp;
		}
		else
		{
			opcode = rsp;
		}
		opcode |= OBEX_FINAL;
		break;

	case OBEX_MODE_CLIENT:
		opcode = cmd;
		// Have more headers (or body) to send?
		if (finished(allowfinal))
		{
			opcode |= OBEX_FINAL;
		}
		break;

	default:
		break;
	}

	return opcode;
}

//------------------------------------------------------------------------------
bool CObexObject::append_data( buf_t* txmsg, size_t tx_left )
{
	// Don't do anything if object is suspended
	if (suspended)
	{
		return false;
	}

	// Add nonheader-data first if any (SETPATH, CONNECT)
	if(tx_nonhdr_data) 
	{
		DEBUG(4, "Adding %lu bytes of non-headerdata\n", (unsigned long)tx_nonhdr_data->get_length());

		txmsg->append(tx_nonhdr_data->get(), tx_nonhdr_data->get_length());
		delete tx_nonhdr_data;
		tx_nonhdr_data = nullptr;
	}

	DEBUG(4, "4\n");

	// Take headers from the tx queue and try to stuff as many as possible into the tx-msg
	if( tx_it ) 
	{
		bool has_body_header = false;
		CObexHeader* h = tx_it->get();
		
		while( h != nullptr && !suspended && tx_left > 0 ) 
		{
			obex_hdr_id id = h->get_id();

			if( id == OBEX_HDR_ID_BODY || id == OBEX_HDR_ID_BODY_END )
			{
				if (has_body_header)
				{
					break;
				}
				has_body_header = true;
			}

			if( id != OBEX_HDR_ID_INVALID ) 
			{
				size_t ret = h->append( txmsg, tx_left );
				if (ret == 0)
				{
					break;
				}
				tx_left -= ret;
			}
		
			if( h->is_finished() ) 
			{
				if (h->flags & OBEX_FL_SUSPEND)
				{
					suspended = true;
				}

				tx_it->next();
				h = tx_it->get();
			}
		}
	}

	return true;
}

//------------------------------------------------------------------------------
int CObexObject::finished( bool allowfinal )
{
	return( !suspended && (!tx_it || !tx_it->get()) && allowfinal );
}


//------------------------------------------------------------------------------
//Return the next header in the rx-queue
int CObexObject::getnextheader( uint8_t* hi, obex_headerdata_t* hv, uint32_t* hv_size )
{
	const uint8_t* bq1;
	const uint32_t* bq4;
	CObexHeader* h;

	DEBUG(4, "\n");

	// No more headers
	if (slist_is_empty(rx_headerq))
	{
		return 0;
	}

	if (!it)
	{
		it = new obex_hdr_it(rx_headerq);
	}

	if (!it)
	{
		return -1;
	}

	h = it->get();
	if (h == nullptr)
	{
		return 0;
	}

	it->next();

	*hi = h->get_id() | h->get_type();
	*hv_size= (uint32_t) h->get_data_size();

	switch( h->get_type() ) 
	{
	case OBEX_HDR_TYPE_BYTES:
	case OBEX_HDR_TYPE_UNICODE:
		hv->bs = (const uint8_t*)(h->get_data_ptr() );
		break;

	case OBEX_HDR_TYPE_UINT32:
		bq4 = (const uint32_t*)(h->get_data_ptr());
		hv->bq4 = ntohl(*bq4);
		break;

	case OBEX_HDR_TYPE_UINT8:
		bq1 = (const uint8_t*)(h->get_data_ptr());
		hv->bq1 = bq1[0];
		break;

	default:
		return -1;
	}

	return 1;
}


//------------------------------------------------------------------------------
//Allow the user to re-parse the headers in the rx-queue
int CObexObject::reparseheaders()
{

	DEBUG(4, "\n");

	// Check that there is no more active headers
	if (it) 
	{
		delete it;
		it = nullptr;
	}

	// Success
	return 1;
}


//------------------------------------------------------------------------------
//Process non-header data from an incoming message.
int CObexObject::receive_nonhdr_data( const void* msgdata, size_t rx_left )
{
	DEBUG(4, "\n");

	if (headeroffset == 0)
	{
		return 0;
	}

	if( headeroffset > rx_left )
	{
		return -1;
	}

	// Copy any non-header data (like in CONNECT and SETPATH)
	rx_nonhdr_data = new membuf( headeroffset );
	
	if (!rx_nonhdr_data)
	{
		return -1;
	}

	rx_nonhdr_data->append(msgdata, headeroffset);

	DEBUG(4, "Command has %lu bytes non-headerdata\n", (unsigned long)rx_nonhdr_data->get_length());

	return 0;
}

//------------------------------------------------------------------------------
int CObexObject::Receive_Body(CObexHeader* hdr)
{
	obex_hdr_id id = hdr->get_id();

	DEBUG(4, "\n");

	if (id == OBEX_HDR_ID_BODY || id == OBEX_HDR_ID_BODY_END) 
	{
		
		if (!GetBodyRecv())
		{
			SetBodyRecv(new CObexBodyBuffered(this));
		}
		
		if (!GetBodyRecv())
		{
			return -1;
		}

		if (GetBodyRecv()->rcv(GetBodyRecv()->data, hdr) < 0)
		{
			return -1;
		}

		if (id == OBEX_HDR_ID_BODY) 
		{
			DEBUG(4, "Normal body fragment...\n");
			// We have already handled this data!
		}

		return 1;

	} 
	else if ( hdr->get_id() == OBEX_HDR_ID_LENGTH && !GetBody())
	{
		// The length MAY be useful when receiving body.
		uint32_t value;
		memcpy(&value, hdr->get_data_ptr(), sizeof(value));
		SetHintedBodyLength( ntohl(value) );
		DEBUG(4, "Hinted body len is %d\n", GetHintedBodyLength());
	}

	return 0;
}


//------------------------------------------------------------------------------
int CObexObject::RecieveOneHeader( CObexHeader* hdr )
{
	obex_hdr_id id = hdr->get_id();
	obex_hdr_type type = hdr->get_type();
	const void *data = hdr->get_data_ptr();
	size_t len = hdr->get_data_size();

	DEBUG(4, "\n");

	hdr = CObexHeader::membuf_create(id, type, data, len);
	if (hdr == nullptr)
	{
		return -1;
	}

	// Add element to rx-list
	SetRXHeaderQueue( GetRXHeaderQueue()->append( hdr ) );

	if( GetRXIterator() == nullptr)
	{
		SetRXIterator( new obex_hdr_it(GetRXHeaderQueue()) );
	}

	return 0;
}


//------------------------------------------------------------------------------
/* CObexObject::receive_headers()
 *
 *    Add any incoming headers to headerqueue but does not remove them from
 *    the message buffer.
 *    Returns the total number of bytes of the added headers or -1;
 */
int CObexObject::receive_headers( const void* msgdata, size_t tx_left, uint64_t filter )
{
	size_t offset = 0;
	int consumed = 0;
	const uint64_t body_filter = (1 << OBEX_HDR_ID_BODY | 1 << OBEX_HDR_ID_BODY_END);

	DEBUG(4, "\n");

	while (offset < tx_left) 
	{
		CObexHeader* hdr = CObexHeader::ptr_parse((uint8_t *)msgdata + offset, tx_left - offset);
		size_t hlen;
		int err = 0;
		uint64_t header_bit;

		if (hdr == nullptr)
		{
			break;
		}

		hlen = hdr->get_size();
		DEBUG(4, "Header: type=%02x, id=%02x, size=%ld\n", hdr->get_type(), hdr->get_id(), (unsigned long)hlen);

		/* Push the body header data either to the application
		 * or to an internal receive buffer.
		 * This also uses the length header in the latter case
		 * but the filter is not checked for it as it's only an
		 * optimisation (currently only works if BODY header is
		 * part of first message).
		 */
		if( hdr && ( filter & body_filter ) == 0 ) 
		{
			int used = Receive_Body(hdr);
			
			if (used != 0) 
			{
				delete hdr;
				hdr = NULL;
			}
			if (used < 0)
			{
				err = -1;
			}
			if (used > 0)
			{
				consumed += hlen;
			}
		}

		/* This adds all headers to an internal list of headers that the application can walk easily. Body headers are only added
		 * if not in streaming mode and only after end-of-body was received.
		 */
		if (hdr) 
		{
			obex_hdr_id id = hdr->get_id();

			header_bit = (uint64_t) 1 << id;

			if( !( filter & header_bit ) ) 
			{
				err = RecieveOneHeader(hdr);
				consumed += hlen;
			}
			delete hdr;
		}

		if (err)
		{
			return err;
		}

		offset += hlen;
	}

	return consumed;
}


//------------------------------------------------------------------------------
int CObexObject::set_body_receiver( IObexBody* b )
{
	if (!body_rcv)
	{
		body_rcv = b;
	}

	return ( body_rcv == b );
}

//------------------------------------------------------------------------------
const void* CObexObject::read_body( size_t* size )
{
	return body_rcv->read( body_rcv->data, size );
}

//------------------------------------------------------------------------------
int CObexObject::suspend()
{
	if (suspended)
	{
		return -1;
	}

	suspended = true;
	return 0;
}

//------------------------------------------------------------------------------
int CObexObject::resume()
{
	if (!suspended)
	{
		return -1;
	}

	suspended = false;
	return 0;
}

//------------------------------------------------------------------------------
void CObexObject::SetTXNonHeaderData(databuffer* p)
{
	tx_nonhdr_data = p;
}

//------------------------------------------------------------------------------
databuffer* CObexObject::GetTXNonHeaderData(void)
{
	return tx_nonhdr_data;
}

//------------------------------------------------------------------------------
void CObexObject::SetTXHeaderQueue(databuffer_list* p)
{
	tx_headerq = p;
}

//------------------------------------------------------------------------------
databuffer_list* CObexObject::GetTXHeaderQueue(void)
{
	return tx_headerq;
}

//------------------------------------------------------------------------------
void CObexObject::SetTXIterator(obex_hdr_it* p)
{
	tx_it = p;
}

//------------------------------------------------------------------------------
obex_hdr_it* CObexObject::GetTXIterator(void)
{
	return tx_it;
}

//------------------------------------------------------------------------------
void CObexObject::SetRXHeaderQueue(databuffer_list* p)
{
	rx_headerq = p;
}

//------------------------------------------------------------------------------
databuffer_list* CObexObject::GetRXHeaderQueue(void)
{
	return rx_headerq;
}

//------------------------------------------------------------------------------
databuffer* CObexObject::GetRXNonHeaderData()
{
	return rx_nonhdr_data;
}

//------------------------------------------------------------------------------
void CObexObject::SetRXIterator(obex_hdr_it* p)
{
	rx_it = p;
}

//------------------------------------------------------------------------------
obex_hdr_it* CObexObject::GetRXIterator(void)
{
	return rx_it;
}

//------------------------------------------------------------------------------
obex_cmd CObexObject::GetCommand(void)
{
	return cmd;
}

//------------------------------------------------------------------------------
obex_rsp CObexObject::GetResponse(void)
{
	return rsp;
}
/*
//------------------------------------------------------------------------------
void CObexObject::SetLastResponse(obex_rsp LastResponse)
{
	lastrsp = LastResponse;
}
*/
//------------------------------------------------------------------------------
obex_rsp CObexObject::GetLastResponse(void)
{
	return lastrsp;
}

//------------------------------------------------------------------------------
void CObexObject::SetHeaderOffset(uint16_t offset)
{
	headeroffset = offset;
}

//------------------------------------------------------------------------------
uint16_t CObexObject::GetHeaderOffset(void)
{
	return headeroffset;
}

//------------------------------------------------------------------------------
uint32_t CObexObject::GetHintedBodyLength()
{
	return hinted_body_len;
}

//------------------------------------------------------------------------------
void CObexObject::SetHintedBodyLength(uint32_t len)
{
	hinted_body_len = len;
}

//------------------------------------------------------------------------------
void CObexObject::SetAbort(bool bAbort)
{
	abort = bAbort;
}

//------------------------------------------------------------------------------
bool CObexObject::IsAborting()
{
	return abort;
}

//------------------------------------------------------------------------------
void CObexObject::SetResponseMode(obex_rsp_mode ResponseMode)
{
	rsp_mode = ResponseMode;
}

//------------------------------------------------------------------------------
obex_rsp_mode CObexObject::GetResponseMode()
{
	return rsp_mode;
}

//------------------------------------------------------------------------------
void CObexObject::Suspend(bool bSuspend)
{
	suspended = bSuspend;
}

//------------------------------------------------------------------------------
void CObexObject::ClearBody(void)
{
	delete body;
	body = nullptr;
}

//------------------------------------------------------------------------------
void CObexObject::SetBody(CObexHeader* p)
{
	body = p;
}

//------------------------------------------------------------------------------
CObexHeader* CObexObject::GetBody(void) const
{
	return body;
}

//------------------------------------------------------------------------------
void CObexObject::SetBodyRecv(IObexBody* p)
{
	body_rcv = p;
}

//------------------------------------------------------------------------------
IObexBody* CObexObject::GetBodyRecv() const
{
	return body_rcv;
}