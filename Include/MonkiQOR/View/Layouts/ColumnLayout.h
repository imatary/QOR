///ColumnLayout.h

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif	__QCMP_OPTIMIZEINCLUDE

#ifndef _GUIQOR_VIEW_COLUMNLAYOUT_H_
#define _GUIQOR_VIEW_COLUMNLAYOUT_H_

#include "SystemQOR.h"
#include "../Layout.h"

//------------------------------------------------------------------------------
namespace nsMonki
{
	//------------------------------------------------------------------------------
	//Column based layout, Y dimension space division
	class __MONKI_INTERFACE CColumnLayout : public CLayout
	{
	public:

		CColumnLayout( CView* pOwner );
		virtual ~CColumnLayout();

		bool operator()( std::vector< CLayoutItem* > VecItems );

	protected:

	};

};

#endif//_GUIQOR_VIEW_COLUMNLAYOUT_H_
