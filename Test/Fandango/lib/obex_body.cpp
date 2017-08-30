/**
 * @file obex_body.cpp
 *
 * OBEX body reception releated functions.
 * OpenOBEX library - Free implementation of the Object Exchange protocol.
 *
 * Copyright (c) 1999, 2000 Pontus Fuchs, All Rights Reserved.
 * Copyright (c) 1999, 2000 Dag Brattli, All Rights Reserved.
 * Copyright (c) 2012 Hendrik Sattler, All Rights Reserved.
 * Copyright (c) 2016 Querysoft Ltd, All Rights Reserved.
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

#include "obex_body.h"
#include "obex_hdr.h"
#include "obex_main.h"
#include "obex_object.h"

//------------------------------------------------------------------------------
int CObexBodyStream::rcv(void* self, CObexHeader* hdr)
{
	obex_t* obex = reinterpret_cast< obex_t* >(self);
	CObexObject* object = obex->object;
	obex_cmd cmd = object->getcmd();
	obex_hdr_id id = hdr->get_id();
	obex_hdr_type type = hdr->get_type();
	size_t len = hdr->get_data_size();

	DEBUG(4, "\n");

	// Spare the app this empty nonlast body-hdr
	if (hdr->get_id() == OBEX_HDR_ID_BODY && hdr->get_data_size() == 0)
	{
		return 1;
	}

	// Notify app that data has arrived
	object->SetBody( hdr );
	obex->deliver_event(OBEX_EV_STREAMAVAIL, (obex_cmd)cmd, (obex_rsp)0, FALSE);
	object->SetBody( nullptr );

	// If end send EOS to app
	if (id == OBEX_HDR_ID_BODY_END && len != 0)
	{
		object->SetBody( CObexHeader::ptr_create(id, type, nullptr, 0) );
		obex->deliver_event(OBEX_EV_STREAMAVAIL, (obex_cmd)cmd, (obex_rsp)0, FALSE);
		object->ClearBody();	
	}

	return 1;
}

//------------------------------------------------------------------------------
const void* CObexBodyStream::read(void* self, size_t* size)
{
	obex_t* obex = reinterpret_cast< obex_t* >(self);
	CObexObject* object = obex->object;
	const void* buf = object->GetBody()->get_data_ptr();

	if (buf && size)
	{
		*size = object->GetBody()->get_data_size();
	}
	return buf;
}

//------------------------------------------------------------------------------
CObexBodyStream::CObexBodyStream( obex_t* obex )
{
	data = obex;
}

//------------------------------------------------------------------------------
int CObexBodyBuffered::rcv(void* self, CObexHeader* hdr)
{
	CObexObject* object = reinterpret_cast< CObexObject*>(self);
	const void* pdata = hdr->get_data_ptr();
	size_t len = hdr->get_data_size();

	DEBUG(4, "This is a body-header.\n");

	if (!object->GetBody())
	{
		int alloclen = hdr->get_data_size();

		if (object->GetHintedBodyLength())
		{
			alloclen = object->GetHintedBodyLength();
		}

		DEBUG(4, "Allocating new body-buffer. Len=%d\n", alloclen);
		object->SetBody( CObexHeader::membuf_create(OBEX_HDR_ID_BODY, OBEX_HDR_TYPE_BYTES, pdata, len) );
		if (!object->GetBody())
		{
			return -1;
		}
	}
	else
	{
		databuffer* buf = ((CMemBufferObexHeader*)object->GetBody())->get_data_buffer();
		if( buf->append( pdata, len ) < 0 )
		{
			return -1;
		}
	}

	if (hdr->get_id() == OBEX_HDR_ID_BODY_END)
	{
		hdr = object->GetBody();
		object->SetBody( nullptr );

		// Add element to rx-list
		object->SetRXHeaderQueue( object->GetRXHeaderQueue()->append( hdr ) );

		if (object->GetRXIterator() == nullptr)
		{
			object->SetRXIterator( new obex_hdr_it(object->GetRXHeaderQueue()) );
		}
	}

	return 1;
}

//------------------------------------------------------------------------------
const void* CObexBodyBuffered::read(void* self, size_t* size)
{
	CObexObject* object = reinterpret_cast< CObexObject* >(self);
	const void* buf = object->GetBody()->get_data_ptr();

	if (buf && size)
	{
		*size = object->GetBody()->get_data_size();
	}
	return buf;
}

//------------------------------------------------------------------------------
CObexBodyBuffered::CObexBodyBuffered(CObexObject* object)
{
	data = object;
}
