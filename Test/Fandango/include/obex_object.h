/**
	\file obex_object.h
	OBEX object related functions.
	OpenOBEX library - Free implementation of the Object Exchange protocol.

	Copyright (c) 1999, 2000 Dag Brattli, All Rights Reserved.
	Copyright (c) 1999, 2000 Pontus Fuchs, All Rights Reserved.

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

#ifndef OBEX_OBJECT_H
#define OBEX_OBJECT_H

#include "obex_incl.h"
#include "defines.h"

#if ! defined(_WIN32)
#  include <sys/time.h>
#endif
#include <time.h>


class databuffer;
class databuffer_list;
class CObexHeader;
class IObexBody;
class obex_hdr_it;

//------------------------------------------------------------------------------
class CObexObject
{
public:
	CObexObject();
	~CObexObject();

	void SetTXNonHeaderData(databuffer* p);
	databuffer* GetTXNonHeaderData(void);
	void SetTXHeaderQueue(databuffer_list* p);
	databuffer_list* GetTXHeaderQueue(void);
	void SetTXIterator(obex_hdr_it* p);
	obex_hdr_it* GetTXIterator(void);
	void SetRXHeaderQueue(databuffer_list* p);
	databuffer_list* GetRXHeaderQueue(void);
	databuffer* GetRXNonHeaderData(void);
	void SetRXIterator(obex_hdr_it* p);
	obex_hdr_it* GetRXIterator(void);
	obex_cmd GetCommand(void);
	obex_rsp GetResponse(void);
	obex_rsp GetLastResponse(void);
	void SetHeaderOffset(uint16_t offset);
	uint16_t GetHeaderOffset(void);
	uint32_t GetHintedBodyLength(void);
	void SetHintedBodyLength(uint32_t len);
	void SetAbort(bool bAbort);
	bool IsAborting(void);
	void SetResponseMode(obex_rsp_mode ResponseMode);
	obex_rsp_mode GetResponseMode(void);
	void ClearBody(void);
	void SetBody(CObexHeader* p);
	CObexHeader* GetBody(void) const;
	void SetBodyRecv(IObexBody* p);
	IObexBody* GetBodyRecv(void) const;
	size_t get_size(void);
	int addheader( obex* self, CObexObject* object, uint8_t hi, obex_headerdata_t hv, uint32_t hv_size, unsigned int flags );//deprecated
	int getnextheader( uint8_t* hi, obex_headerdata_t* hv, uint32_t* hv_size );
	int reparseheaders( void );
	void setcmd(obex_cmd cmd);
	obex_cmd getcmd() const;
	int setrsp(obex_rsp rsp, obex_rsp lastrsp);
	int get_opcode( bool allowfinalcmd, enum obex_mode mode );
	bool append_data( databuffer* txmsg, size_t tx_left );
	int finished( bool allowfinal );
	int receive_nonhdr_data( const void* msgdata, size_t rx_left );
	int receive_headers( const void* msgdata, size_t tx_left, uint64_t filter );
	int set_body_receiver( IObexBody* b );
	const void * read_body( size_t* size );
	void Suspend(bool bSuspend);
	int suspend(void);
	int resume( void );

private:

	int Receive_Body(CObexHeader* hdr);
	int RecieveOneHeader(CObexHeader* hdr);

	databuffer* tx_nonhdr_data;	// Data before of headers (like CONNECT and SETPATH)
	databuffer_list* tx_headerq;// List of headers to transmit
	obex_hdr_it* tx_it;

	databuffer* rx_nonhdr_data;	// Data before of headers (like CONNECT and SETPATH) 
	databuffer_list* rx_headerq;// List of received headers 
	obex_hdr_it* rx_it;
	obex_hdr_it* it;
	obex_cmd cmd;				// command
	obex_rsp rsp;				// response
	obex_rsp lastrsp;			// response for last packet
	uint16_t headeroffset;		// Where to start parsing headers
	uint32_t hinted_body_len;	// Hinted body-length or 0
	bool abort;					// Request shall be aborted
	obex_rsp_mode rsp_mode;		// OBEX_RSP_MODE_
	bool suspended;				// Temporarily stop transfering object
	CObexHeader* body;			// The body header need some extra help
	IObexBody*	body_rcv;		// Deliver body
};

#endif
