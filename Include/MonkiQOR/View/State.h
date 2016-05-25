///State.h

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif	__QCMP_OPTIMIZEINCLUDE

#ifndef _GUIQOR_VIEW_STATE_H_
#define _GUIQOR_VIEW_STATE_H_

#include "SystemQOR.h"

//------------------------------------------------------------------------------
namespace nsMonki
{
	class __MONKI_INTERFACE CView;

	//------------------------------------------------------------------------------
	//Base class for View State
	class __MONKI_INTERFACE CState
	{
	public:

		CState( CView* pOwner );
		virtual ~CState();

		void SetParent( CState* pParent );
		CState* GetParent( void );

	protected:

		CView* m_pView;
		CState* m_pParent;
	};


};

#endif//_GUIQOR_VIEW_STATE_H_
