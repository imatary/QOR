/**
 * @file obex_hdr.h
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

#include "databuffer.h"
#include "obex_incl.h"
#include "defines.h"

//------------------------------------------------------------------------------
class IObexHeader
{
public:

	unsigned int flags;
	size_t offset;

	virtual obex_hdr_id get_id(void) = 0;
	virtual obex_hdr_type get_type(void) = 0;
	virtual size_t get_size() = 0;
	virtual size_t get_data_size(void) = 0;
	virtual const void* get_data_ptr(void) = 0;
	virtual bool set_data(const void* data, size_t size) = 0;
	virtual size_t append(databuffer* buf, size_t max_size) = 0;
	virtual bool is_finished(void) = 0;
	virtual void stream_finish(void) = 0;

	void *data;
};

// Copy the data to the header instance
#define OBEX_FL_COPY		(1 <<  0)

//------------------------------------------------------------------------------
class CObexHeader : public IObexHeader
{
public:

	CObexHeader();
	CObexHeader(void* _data);
	~CObexHeader();

	void Init(void* _data);

	static CObexHeader* Create(obex_hdr_id id, obex_hdr_type type, const void* data, size_t size, unsigned int flags);

	bool is_splittable(void);

	virtual obex_hdr_id get_id(void);
	virtual obex_hdr_type get_type(void);
	virtual size_t get_size();
	virtual size_t get_data_size(void);
	virtual const void* get_data_ptr(void);
	virtual bool set_data(const void* data, size_t size);
	virtual size_t append(databuffer* buf, size_t max_size);
	virtual bool is_finished(void);
	virtual void stream_finish(void) {}

	
	static CObexHeader* create(obex_hdr_id id, obex_hdr_type type, const void* data, size_t size, unsigned int flags);
	static CObexHeader* membuf_create(obex_hdr_id id, obex_hdr_type type, const void* data, size_t size);
	static CObexHeader* ptr_create(obex_hdr_id id, obex_hdr_type type, const void* data, size_t size);
	static CObexHeader* stream_create(obex* obex, CObexHeader* data);
	static CObexHeader* ptr_parse(const void* msgdata, size_t size);

private:

	static void* membuf_new(obex_hdr_id id, obex_hdr_type type, const void *value, size_t size);
};

//------------------------------------------------------------------------------
class CMemBufferObexHeader : public CObexHeader
{
public:

	CMemBufferObexHeader(obex_hdr_id id, obex_hdr_type type, const void* data, size_t size);
	virtual ~CMemBufferObexHeader();

	virtual obex_hdr_id get_id(void);
	virtual obex_hdr_type get_type(void);
	virtual size_t get_size();
	virtual size_t get_data_size(void);
	virtual const void* get_data_ptr(void);
	virtual bool set_data(const void* data, size_t size);

	obex_hdr_id id;
	obex_hdr_type type;
	databuffer* buf;

	databuffer* get_data_buffer(void);
};

//------------------------------------------------------------------------------
class CPtrObexHeader : public CObexHeader
{
public:

	CPtrObexHeader();
	CPtrObexHeader(obex_hdr_id id, obex_hdr_type type, const void* data, size_t size);
	virtual ~CPtrObexHeader();

	virtual obex_hdr_id get_id(void);
	virtual obex_hdr_type get_type(void);
	virtual size_t get_size();
	virtual size_t get_data_size(void);
	virtual const void* get_data_ptr(void);
	virtual bool set_data(const void* data, size_t size);

	obex_hdr_id id;
	obex_hdr_type type;
	size_t size;
	const void* value;
};

//------------------------------------------------------------------------------
class CStreamObexHeader : public CObexHeader
{
public:

	CStreamObexHeader(obex* pobex, CObexHeader* pdata);
	~CStreamObexHeader();

	virtual obex_hdr_id get_id(void);
	virtual obex_hdr_type get_type(void);
	virtual size_t get_size();
	virtual size_t get_data_size(void);
	virtual const void* get_data_ptr(void);
	virtual bool set_data(const void* data, size_t size);
	virtual size_t append(databuffer* buf, size_t max_size);
	virtual bool is_finished(void);

	obex* obex;
	CObexHeader* data;		/** Pointer to streaming data */
	size_t s_offset;			/** Current offset in buf */
	bool s_stop;				/** End of stream */

	virtual void stream_finish(void);
	void refresh(void);
	void finish(void);
};

//------------------------------------------------------------------------------
class obex_hdr_it 
{
public:

	obex_hdr_it();
	obex_hdr_it(databuffer_list*);
	~obex_hdr_it();

	void init_from(const obex_hdr_it* from);
	CObexHeader* get() const;
	void next();
	bool equals(const obex_hdr_it* b) const;

private:
	databuffer_list* list;
	int is_valid;
};

