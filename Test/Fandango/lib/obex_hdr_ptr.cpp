/**
 * @file obex_hdr_ptr.c
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
#include "debug.h"

#ifndef _WIN32
#include <arpa/inet.h>
#endif
#include <string.h>

/*
//------------------------------------------------------------------------------
struct obex_hdr_ptr 
{
	obex_hdr_id id;
	obex_hdr_type type;
	size_t size;
	const void *value;
};
*/
//------------------------------------------------------------------------------
CPtrObexHeader::~CPtrObexHeader()
{

}

//------------------------------------------------------------------------------
obex_hdr_id CPtrObexHeader::get_id()
{
	return id;
}

//------------------------------------------------------------------------------
obex_hdr_type CPtrObexHeader::get_type()
{
	return type;
}

//------------------------------------------------------------------------------
size_t CPtrObexHeader::get_data_size()
{
	return size;
}

//------------------------------------------------------------------------------
const void* CPtrObexHeader::get_data_ptr()
{
	return value;
}

//------------------------------------------------------------------------------
bool CPtrObexHeader::set_data( const void* _data, size_t _size)
{
	value = _data;
	size = _size;
	return true;
}

//------------------------------------------------------------------------------
CPtrObexHeader::CPtrObexHeader()
{
}

//------------------------------------------------------------------------------
CPtrObexHeader::CPtrObexHeader(obex_hdr_id _id, obex_hdr_type _type, const void* _data, size_t _size) : CObexHeader()
{
	id = _id;
	type = _type;
	size = _size;
	value = _data;
}

//------------------------------------------------------------------------------
CObexHeader* CObexHeader::ptr_create( obex_hdr_id id,  obex_hdr_type type, const void *data, size_t size)
{
	CPtrObexHeader* ptr = new CPtrObexHeader(id, type, data, size);
	return ptr;
}

//------------------------------------------------------------------------------
CObexHeader* CObexHeader::ptr_parse( const void* msgdata, size_t size )
{	
	uint16_t hsize;

	if (size < 1)
	{
		return nullptr;
	}

	CPtrObexHeader* ptr = new CPtrObexHeader();

	ptr->id =(obex_hdr_id)( ((uint8_t *)msgdata)[0] & OBEX_HDR_ID_MASK );
	ptr->type =(obex_hdr_type) ( ((uint8_t *)msgdata)[0] & OBEX_HDR_TYPE_MASK );

	switch (ptr->type) 
	{
	case OBEX_HDR_TYPE_UNICODE:
	case OBEX_HDR_TYPE_BYTES:
		if (size < 3)
			goto err;
		memcpy(&hsize, (uint8_t *)msgdata + 1, 2);
		ptr->size = ntohs(hsize) - 3;
		if (size < (3 + ptr->size))
			goto err;
		ptr->value = (uint8_t *)msgdata + 3;
		break;

	case OBEX_HDR_TYPE_UINT8:
		if (size < 2)
			goto err;
		ptr->size = 1;
		ptr->value = (uint8_t *)msgdata + 1;
		break;

	case OBEX_HDR_TYPE_UINT32:
		if (size < 5)
			goto err;
		ptr->size = 4;
		ptr->value = (uint8_t *)msgdata + 1;
		break;

	default:
		goto err;
	}

	return ptr;

err:
	DEBUG(1, "Header too big.\n");
	free(ptr);
	return NULL;
}
