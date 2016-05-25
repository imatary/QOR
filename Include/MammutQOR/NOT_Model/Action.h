///Action.h

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif	__QCMP_OPTIMIZEINCLUDE

#ifndef _GUIQOR_MODEL_ACTION_H_
#define _GUIQOR_MODEL_ACTION H_

#include "SystemQOR.h"

//------------------------------------------------------------------------------
namespace nsQOR
{
	class CModel;

	//------------------------------------------------------------------------------
	//Base class for Actions
	class __MONKI_INTERFACE CAction
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

#endif//_GUIQOR_MODEL_ACTION_H_
