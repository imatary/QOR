/**
	\file databuffer.h
	Network buffer handling routines.
	OpenOBEX library - Free implementation of the Object Exchange protocol.

	Copyright (c) 2005 Herton Ronaldo Krzesinski, All Rights Reserved.

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

#ifndef DATABUFFER_H
#define DATABUFFER_H

#define __need_size_t
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

 //------------------------------------------------------------------------------
 // Implements a single linked list
class databuffer_list 
{
public:

	bool is_empty(void);
	databuffer_list* remove(void* element );
	bool has_more( void );
	databuffer_list* append(void* element);
	void* get(void);
	databuffer_list* Next(void);

private:
	void* data;
	databuffer_list* next;
};
typedef databuffer_list slist_t;

//------------------------------------------------------------------------------
// This implements an abstracted data buffer.
class databuffer
{
public:

	databuffer(size_t default_size);
	virtual ~databuffer();

	virtual size_t get_offset( void );
	virtual void set_offset( size_t offset);
	virtual size_t get_size( void );
	virtual int set_size(size_t new_size);
	virtual size_t get_length() const;
	virtual void* get(void) const;
	virtual void clear(size_t len);
	virtual int append(const void *data, size_t len);

};

typedef databuffer buf_t;

//----------------------------------------------------------------------------------------
class membuf : public databuffer
{
public:

	membuf(size_t default_size);
	virtual ~membuf();

	size_t get_offset(void);
	void set_offset(size_t offset);
	size_t get_size(void);
	int set_size(size_t new_size);
	size_t get_length(void);
	void* get(void);
	void clear(size_t len);
	int append(const void *data, size_t len);

protected:

	uint8_t* buffer;
	size_t buffer_size;
	size_t offset;
	size_t data_len;

};

#define slist_is_empty(l) ((l) == NULL)

#endif
