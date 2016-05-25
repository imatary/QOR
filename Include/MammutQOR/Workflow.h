//Workflow.h

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#ifndef _MAMMUTQOR_MODEL_WORKFLOW_H_
#define _MAMMUTQOR_MODEL_WORKFLOW_H_

#include "SystemQOR.h"

//------------------------------------------------------------------------------
namespace nsMammut
{
	class __MAMMUT_INTERFACE CModel;

	//------------------------------------------------------------------------------
	//Base class for WorkFlows
	class __MAMMUT_INTERFACE CWorkflow
	{
	public:

		CWorkflow();
		CWorkflow( CModel& model );
		virtual ~CWorkflow();

		virtual int Apply( CModel& model );
		virtual CModel& Detach( void );
		virtual int Start( void );
	};

};

#endif//_MAMMUTQOR_MODEL_WORKFLOW_H_
