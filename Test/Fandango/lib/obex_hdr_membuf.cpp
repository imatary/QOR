/**
 * @file obex_hdr_membuf.cpp
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

#include <membuf.h>
#include <obex_hdr.h>

#include <string.h>

//------------------------------------------------------------------------------
CMemBufferObexHeader::CMemBufferObexHeader( obex_hdr_id _id,  obex_hdr_type _type, const void* _value, size_t _size )
{
	id = _id;
	type = _type;
	buf = new membuf(_size);
	if (buf == nullptr) 
	{
		throw;
	}

	buf->append(_value, _size);
}

//------------------------------------------------------------------------------
CMemBufferObexHeader::~CMemBufferObexHeader()
{
	delete buf;
}

//------------------------------------------------------------------------------
obex_hdr_id CMemBufferObexHeader::get_id()
{
	return id;
}

//------------------------------------------------------------------------------
obex_hdr_type CMemBufferObexHeader::get_type()
{
	return type;
}

//------------------------------------------------------------------------------
size_t CMemBufferObexHeader::get_data_size()
{
	return buf->get_length();
}

//------------------------------------------------------------------------------
const void* CMemBufferObexHeader::get_data_ptr()
{
	return buf->get();
}

//------------------------------------------------------------------------------
bool CMemBufferObexHeader::set_data(const void* _data, size_t size )
{
	buf->clear( buf->get_length() );
	if (buf->set_size(size) != 0)
	{
		return false;
	}
	memcpy(buf->get(), _data, size);
	return true;
}

/*
//------------------------------------------------------------------------------
CMemBufferObexHeader::CMemBufferObexHeader(obex_hdr_id _id, obex_hdr_type _type, const void* _data, size_t _size) : CObexHeader()
{
	id = _id;
	type = _type;
	buf = ::membuf_create(_size);
	if ( buf == nullptr )
	{
		throw;
	}

	buf_append( buf, _data, _size);

	CObexHeader::Init(buf);
}
*/
//------------------------------------------------------------------------------
CObexHeader* CObexHeader::membuf_create( obex_hdr_id id, obex_hdr_type type, const void* data, size_t size)
{
	return new CMemBufferObexHeader(id, type, data, size);
}

//------------------------------------------------------------------------------
databuffer* CMemBufferObexHeader::get_data_buffer()
{
	return buf;
}
