//Action.h

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#ifndef _MAMMUTQOR_MODEL_ACTION_H_
#define _MAMMUTQOR_MODEL_ACTION H_

#include "SystemQOR.h"

//------------------------------------------------------------------------------
namespace nsMammut
{
	class __MAMMUT_INTERFACE CModel;

	//------------------------------------------------------------------------------
	//Base class for Actions
	class __MAMMUT_INTERFACE CAction
	{
	public:

		CAction();
		CAction( CModel& model );
		virtual ~CAction();

		virtual int Apply( CModel& model );
		virtual CModel& Detach( void );
		virtual int Do( void );
		virtual int Undo( void );
	};

};

#endif//_MAMMUTQOR_MODEL_ACTION_H_
