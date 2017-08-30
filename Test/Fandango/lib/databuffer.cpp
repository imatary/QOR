/**
	\file databuffer.c
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

#include "databuffer.h"
#include "obex_main.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

 //------------------------------------------------------------------------------
bool databuffer_list::has_more()
{
	return (!slist_is_empty(this) && !slist_is_empty(next));
}

//------------------------------------------------------------------------------
void* databuffer_list::get()
{
	if (slist_is_empty(this))
	{
		return nullptr;
	}
	else
	{
		return data;
	}
}

//------------------------------------------------------------------------------
databuffer_list* databuffer_list::Next(void)
{
	return next;
}

//------------------------------------------------------------------------------
slist_t* databuffer_list::append(void *element)
{
	slist_t *node, *p;

	node = new slist_t;	
	assert(node != nullptr);

	node->data = element;
	node->next = nullptr;
	if (!this)
	{
		return node;
	}
	p = this;
	while (p->next)
	{
		p = p->next;
	}
	p->next = node;
	return this;
}

//------------------------------------------------------------------------------
bool databuffer_list::is_empty(void)
{
	return this == nullptr ? true : false;
}

//------------------------------------------------------------------------------
slist_t * databuffer_list::remove(void *element)
{
	slist_t* prev, *pnext;

	prev = this;
	pnext = this;
	while (pnext != nullptr) 
	{
		if (pnext->data == element) 
		{
			// if first element, update list pointer
			if (pnext == this) 
			{
				pnext = pnext->next;
				//list = list->next;
				//prev = list;
				delete this;
				//free(next);
				//next = prev;
				return pnext;
			} 
			else 
			{
				prev->next = pnext->next;
				delete pnext;// free(next);
				return prev;
			}
		}
		prev = pnext;
		pnext = pnext->next;
	}
	return prev;
}

//------------------------------------------------------------------------------
databuffer::databuffer(size_t default_size)
{
}

//------------------------------------------------------------------------------
databuffer::~databuffer()
{

}

//------------------------------------------------------------------------------
size_t databuffer::get_offset()
{
	return 0;
}

//------------------------------------------------------------------------------
void databuffer::set_offset(size_t offset)
{
}

//------------------------------------------------------------------------------
size_t databuffer::get_size()
{
	return 0;
}

//------------------------------------------------------------------------------
int databuffer::set_size(size_t new_size)
{
	return 0;
}

//------------------------------------------------------------------------------
size_t databuffer::get_length() const
{
	return 0;
}

//------------------------------------------------------------------------------
void* databuffer::get() const
{
	return nullptr;
}

//------------------------------------------------------------------------------
void databuffer::clear(size_t len)
{
}

//------------------------------------------------------------------------------
int databuffer::append(const void *data, size_t len)
{
	return -EINVAL;
}

//------------------------------------------------------------------------------
void buf_dump(buf_t *p, const char *label)
{
	unsigned int i, n;

	if (!p || !label)
		return;

	n = 0;
	for (i = 0; i < p->get_length(); ++i) 
	{
		if (n == 0)
		{
			log_debug("%s%s(%04x):", log_debug_prefix, label, i);
		}
		log_debug(" %02X", *((uint8_t *)p->get() + i));
		if (n >= 0xF || i == p->get_length() - 1) 
		{
			log_debug("\n");
			n = 0;
		} 
		else
		{
			n++;
		}
	}
}
