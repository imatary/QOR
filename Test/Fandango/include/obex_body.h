/**
 * @file obex_body.h
 *
 * OBEX body reception releated functions.
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

#ifndef OBEX_BODY_H
#define OBEX_BODY_H

#include <stdlib.h>
#include "defines.h"

class obex;
class CObexHeader;
class CObexObject;

typedef obex obex_t;

//------------------------------------------------------------------------------
class IObexBody
{
public:
	virtual int rcv(void* data, CObexHeader* hdr) = 0;
	virtual const void* read ( void* data, size_t* size) = 0;
	void* data;
};

//------------------------------------------------------------------------------
class CObexBodyStream : public IObexBody
{
public:

	CObexBodyStream( obex_t* obex);

	virtual int rcv(void* data, CObexHeader* hdr);
	virtual const void* read(void* data, size_t* size);

	//obex_t* data;
};

//------------------------------------------------------------------------------
class CObexBodyBuffered : public IObexBody
{
public:
	CObexBodyBuffered(CObexObject* object);

	virtual int rcv(void* data, CObexHeader* hdr);
	virtual const void* read(void* data, size_t* size);

	//CObexObject* data;
};

#endif /* OBEX_BODY_H */
