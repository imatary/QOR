/**
 * @file obex_hdr.c
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
#include "defines.h"

#include <string.h>

 //------------------------------------------------------------------------------
CObexHeader* CObexHeader::Create(obex_hdr_id id, obex_hdr_type type, const void* data, size_t size, unsigned int flags)
{
	CObexHeader* hdr = nullptr;
	const unsigned int save_flags = OBEX_FL_SUSPEND;

	if (flags & OBEX_FL_COPY)
	{
		hdr = new CMemBufferObexHeader(id, type, data, size);
	}
	else
	{
		hdr = new CPtrObexHeader(id, type, data, size);
	}

	if (!hdr)
	{
		return nullptr;
	}

	hdr->flags |= (flags & save_flags);
	return hdr;
}

//------------------------------------------------------------------------------
CObexHeader* CObexHeader::create( obex_hdr_id id,  obex_hdr_type type, const void* value, size_t size, unsigned int flags)
{
	CObexHeader* hdr = nullptr;
	const unsigned int save_flags = OBEX_FL_SUSPEND;

	if (flags & OBEX_FL_COPY)
	{
		hdr = CObexHeader::membuf_create(id, type, value, size);
	}
	else
	{
		hdr = CObexHeader::ptr_create(id, type, value, size);
	}

	if (!hdr)
	{
		return nullptr;
	}

	hdr->flags |= (flags & save_flags);
	return hdr;
}


//------------------------------------------------------------------------------
CObexHeader::CObexHeader()
{
	data = nullptr;
}

//------------------------------------------------------------------------------
CObexHeader::CObexHeader(void* _data)
{
	Init(data);
}

//------------------------------------------------------------------------------
void CObexHeader::Init(void* _data)
{
	data = _data;
}

//------------------------------------------------------------------------------
CObexHeader::~CObexHeader()
{
	data = nullptr;
}

//------------------------------------------------------------------------------
obex_hdr_id CObexHeader::get_id()
{
	return OBEX_HDR_ID_INVALID;
}

//------------------------------------------------------------------------------
obex_hdr_type CObexHeader::get_type()
{
	return OBEX_HDR_TYPE_INVALID;
}

//------------------------------------------------------------------------------
static size_t obex_hdr_get_hdr_size( CObexHeader* hdr )
{
	switch (hdr->get_type())
	{
	case OBEX_HDR_TYPE_UINT8:
	case OBEX_HDR_TYPE_UINT32:
		return 1;

	case OBEX_HDR_TYPE_BYTES:
	case OBEX_HDR_TYPE_UNICODE:
		return 3;

	default:
		return 0;
	}
}

//------------------------------------------------------------------------------
size_t CObexHeader::get_data_size()
{
	return (size_t)0;
}

//------------------------------------------------------------------------------
size_t CObexHeader::get_size()
{
	size_t hdr_size = obex_hdr_get_hdr_size(this);
	size_t data_size = get_data_size();

	return hdr_size + data_size;
}

//------------------------------------------------------------------------------
const void* CObexHeader::get_data_ptr()
{
	return nullptr;
}

//------------------------------------------------------------------------------
bool CObexHeader::set_data( const void* _data, size_t size)
{
	return false;
}

//------------------------------------------------------------------------------
bool CObexHeader::is_splittable()
{
	return ( get_id() == OBEX_HDR_ID_BODY && get_type() == OBEX_HDR_TYPE_BYTES );
}

//------------------------------------------------------------------------------
static size_t obex_hdr_append_data(CObexHeader* hdr, databuffer *buf, size_t size)
{
	buf->append(hdr->get_data_ptr(), size);
	hdr->offset += size;
	return size;
}

#define MIN_DATA_SIZE 1

/** Append the header to a buffer
 * @param hdr the header instance
 * @param buf the buffer to append to
 * @param size maximum number of bytes to append to the buffer
 * @return the actual number of appended bytes
 */
size_t CObexHeader::append( databuffer *buf, size_t max_size)
{
	size_t actual = 0;
	uint8_t *h;
	size_t buflen = buf->get_length();
	size_t hdr_size = obex_hdr_get_hdr_size(this);
	size_t data_size = get_data_size();

	if (((hdr_size + data_size) > max_size && !is_splittable()) || hdr_size + MIN_DATA_SIZE > max_size)
	{
		return 0;
	}

	buf->append(nullptr, hdr_size);
	h = (uint8_t *)buf->get() + buflen;
	actual += hdr_size;
	while (max_size > actual && data_size != 0) 
	{
		size_t ret;

		if (data_size > (max_size - actual)) 
		{
			if (is_splittable())
			{
				data_size = max_size - actual;
			}
			else
			{
				return 0;
			}
		}

		if (get_type() == OBEX_HDR_TYPE_UINT8 && data_size != 1)
		{
			if (data_size < 1)
			{
				uint8_t dummy = 0;
				buf->append(&dummy, 1);
				ret = 1;

			} else
				ret = obex_hdr_append_data(this, buf, 1);

		} 
		else if ( get_type() == OBEX_HDR_TYPE_UINT32 && data_size != 4)
		{
			if (data_size < 4)
			{
				uint32_t dummy = 0;
				buf->append(&dummy, 4);
				ret = 1;

			} else
				ret = obex_hdr_append_data(this, buf, 4);

		} 
		else
		{
			ret = obex_hdr_append_data(this, buf, data_size);
		}

		actual += ret;
		if (ret == 0 )
			break;

		data_size = get_data_size();
	} ;

	h[0] = get_id() | get_type();
	
	if (hdr_size > 1) 
	{
		h[1] = (actual >> 8) & 0xFF;
		h[2] = actual & 0xFF;
	}

	return actual;
}

//------------------------------------------------------------------------------
bool CObexHeader::is_finished()
{
	return get_data_size() == 0 ? true : false;
}

//------------------------------------------------------------------------------
void obex_hdr_it::init_from( const obex_hdr_it* from )
{
	if (from) 
	{
		list = from->list;
		is_valid = from->is_valid;
	} 
	else 
	{
		list = nullptr;
		is_valid = false;
	}
}

//------------------------------------------------------------------------------
obex_hdr_it::obex_hdr_it()
{
	list = nullptr;
	is_valid = false;;
}

//------------------------------------------------------------------------------
obex_hdr_it::obex_hdr_it(databuffer_list* _list)
{
	list = _list;
	is_valid = true;
}

//------------------------------------------------------------------------------
obex_hdr_it::~obex_hdr_it()
{
	list = nullptr;
}

//------------------------------------------------------------------------------
CObexHeader* obex_hdr_it::get() const
{
	if (is_valid)
	{
		return reinterpret_cast< CObexHeader* >( list->get() );
	}
	else
	{
		return nullptr;
	}
}

//------------------------------------------------------------------------------
void obex_hdr_it::next()
{
	is_valid = list->has_more();

	if (is_valid)
	{
		list = list->Next();
	}
}

//------------------------------------------------------------------------------
bool obex_hdr_it::equals(const obex_hdr_it* b) const
{
	return b && (memcmp(this, b, sizeof(obex_hdr_it)) == 0) ? true : false;
}
