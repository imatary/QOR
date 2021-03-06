//Event.h

// Copyright Querysoft Limited 2016
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#ifndef _APPOCRITAQOR_EVENT_H_
#define _APPOCRITAQOR_EVENT_H_

#include "CompilerQOR.h"
#include "CodeQOR/Tracing/FunctionContextBase.h"
#include "AppocritaQOR/SubSystems/IThread.h"
#include "AppocritaQOR/Application.h"
#include "AppocritaQOR/IEvent.h"
#include <map>
#include <vector>

//------------------------------------------------------------------------------
namespace nsQOR
{
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __APPOCRITA ) CEvent : public IEvent
	{
	public:

		CEvent();
		CEvent( IApplication& Application );
		virtual ~CEvent();

		virtual void Signal(void);
		virtual void OnSignaled( void );

	protected:

		IApplication& m_Application;
		IThread::ref_type m_Context;

	private:

		CEvent( const CEvent& src );
		CEvent& operator = ( const CEvent& src );		
	};

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __APPOCRITA ) CEventSink : public IEventHandler
	{
	public:

		CEventSink( CEvent::ref_type pEvent = 0 );
		virtual ~CEventSink();
		virtual bool operator()(IEvent::ref_type _event, int iCookie) = 0;
		bool Connect( CEvent::ref_type pEvent );
		void Disconnect();

	protected:

		bool Connected( void );
		CEvent::ref_type m_pEvent;

	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __APPOCRITA ) CEventManager
	{
	public:

		CEventManager();
		~CEventManager();

		void Publish( CEvent::ref_type pEvent );
		void Revoke( CEvent::ref_type pEvent );
		void Raise( CEvent::ref_type pEvent );
		bool Subscribe( IEventHandler::ref_type pSink, CEvent::ref_type pEvent, int iCookie = 0 );
		bool Unsubscribe(IEventHandler::ref_type pSink, CEvent::ref_type pEvent );

	private:

		std::map< IEvent*, std::vector< std::pair< IEventHandler*, int > >* > m_EventSubscriberMap;
	};

}//nsQOR

#endif//_APPOCRITAQOR_EVENT_H_
