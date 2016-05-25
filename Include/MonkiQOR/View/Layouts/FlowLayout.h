///FlowLayout.h

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif	__QCMP_OPTIMIZEINCLUDE

#ifndef _GUIQOR_VIEW_FLOWLAYOUT_H_
#define _GUIQOR_VIEW_FLOWLAYOUT_H_

#include "SystemQOR.h"
#include "../Layout.h"

//------------------------------------------------------------------------------
namespace nsMonki
{
	//------------------------------------------------------------------------------
	//A Row layout of indefinite X dimension broken across a Column of fixed X dimension
	class __MONKI_INTERFACE CFlowLayout : public CLayout
	{
	public:

		CFlowLayout( CView* pOwner );
		virtual ~CFlowLayout();

		bool operator()( std::vector< CLayoutItem* > VecItems );

	protected:

	};

};

#endif//_GUIQOR_VIEW_FLOWLAYOUT_H_
