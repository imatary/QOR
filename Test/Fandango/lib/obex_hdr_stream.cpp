/**
 * @file obex_hdr_stream.c
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

#include "obex_hdr.h"
#include "obex_main.h"
#include "obex_object.h"

//------------------------------------------------------------------------------
CStreamObexHeader::~CStreamObexHeader()
{
	delete data;
}

//------------------------------------------------------------------------------
obex_hdr_id CStreamObexHeader::get_id()
{
	return data->get_id();
}

//------------------------------------------------------------------------------
obex_hdr_type CStreamObexHeader::get_type()
{
	return data->get_type();
}

//------------------------------------------------------------------------------
void CStreamObexHeader::refresh()
{
	if (!s_stop) 
	{
		//struct obex* pobex = obex;
		CObexObject* object = obex->object;
		obex_cmd cmd = object->getcmd();

		// Ask app for more data if no more
		set_data( nullptr, 0);
		s_offset = 0;
		obex->deliver_event(OBEX_EV_STREAMEMPTY, cmd, (obex_rsp)0, FALSE);
		DEBUG(4, "s_size=%lu, s_stop=%d\n", (unsigned long)(data->get_data_size()), s_stop);
	}
}

//------------------------------------------------------------------------------
size_t CStreamObexHeader::get_data_size()
{
	size_t data_size = data->get_data_size() - s_offset;

	if( data_size == 0 ) 
	{
		refresh();
		data_size = data->get_data_size() - s_offset;
	}
	return data_size;
}

//------------------------------------------------------------------------------
const void* CStreamObexHeader::get_data_ptr()
{
	const void* ptr = data->get_data_ptr();

	if (ptr == nullptr)
	{
		return nullptr;
	}
	else
	{
		return (uint8_t*)ptr + s_offset;
	}
}

//------------------------------------------------------------------------------
size_t CStreamObexHeader::append( databuffer* buf, size_t size )
{
	size_t ret = 0;
	const void *ptr;
	size_t data_size = get_data_size();

	// this function _must_ only be called _after_ get_data_size()
	ptr = get_data_ptr();
	
	if (data_size == 0 || ptr == nullptr)
	{
		return 0;
	}

	if (size < data_size) 
	{
		DEBUG(4, "More data than tx_left. Buffer will not be empty\n");
		buf->append(ptr, size);
		s_offset += size;
		ret += size;

	} 
	else 
	{
		DEBUG(4, "Less data than tx_left. Buffer will be empty\n");
		ptr = get_data_ptr();
		buf->append(ptr, data_size);
		s_offset += data_size;
		ret += data_size;
	}

	return ret;
}

//------------------------------------------------------------------------------
bool CStreamObexHeader::is_finished()
{
	return s_stop && (get_data_size() == 0);
}

//------------------------------------------------------------------------------
CStreamObexHeader::CStreamObexHeader( class obex* pobex, CObexHeader* pdata) : CObexHeader( )
{
	obex = pobex;
	data = pdata;
}

//------------------------------------------------------------------------------
CObexHeader* CObexHeader::stream_create( obex* obex, CObexHeader* data)
{
	return new CStreamObexHeader(obex, data);
}

//------------------------------------------------------------------------------
void CStreamObexHeader::finish()
{
	s_stop = true;
}

//------------------------------------------------------------------------------
void CStreamObexHeader::stream_finish()
{
	s_stop = true;
}
