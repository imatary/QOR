///RowLayout.h

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif	__QCMP_OPTIMIZEINCLUDE

#ifndef _GUIQOR_VIEW_ROWLAYOUT_H_
#define _GUIQOR_VIEW_ROWLAYOUT_H_

#include "SystemQOR.h"
#include "../Layout.h"

//------------------------------------------------------------------------------
namespace nsMonki
{

	//------------------------------------------------------------------------------
	//Row based layout, X dimension space division
	class __MONKI_INTERFACE CRowLayout : public CLayout
	{
	public:

		CRowLayout( CView* pOwner );
		virtual ~CRowLayout();

		bool operator()( std::vector< CLayoutItem* > VecItems );

	protected:

	};

};

#endif//_GUIQOR_VIEW_ROWLAYOUT_H_
