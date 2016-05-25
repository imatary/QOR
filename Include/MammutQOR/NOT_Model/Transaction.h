///Transaction.h

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif	__QCMP_OPTIMIZEINCLUDE

#ifndef _GUIQOR_MODEL_TRANSACTION_H_
#define _GUIQOR_MODEL_TRANSACTION_H_

#include "SystemQOR.h"
#include "Action.h"

//------------------------------------------------------------------------------
namespace nsQOR
{
	//------------------------------------------------------------------------------
	//Base class for Transactions
	class __MONKI_INTERFACE CTransaction : public CAction
	{
	public:

		CTransaction();
		CTransaction( CModel& model );
		virtual ~CTransaction();

		virtual int Apply( CModel& model );
		virtual CModel& Detach( void );

		virtual int Do( void );
		virtual int Undo( void );
		virtual int AddAction( CAction& action );

	};
};

#endif//_GUIQOR_MODEL_TRANSACTION_H_
