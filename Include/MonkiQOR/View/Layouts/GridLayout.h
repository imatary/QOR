///GridLayout.h

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif	__QCMP_OPTIMIZEINCLUDE

#ifndef _GUIQOR_VIEW_GRIDLAYOUT_H_
#define _GUIQOR_VIEW_GRIDLAYOUT_H_

#include "SystemQOR.h"
#include "../Layout.h"

//------------------------------------------------------------------------------
namespace nsMonki
{
	//------------------------------------------------------------------------------
	//A Grid layout of a fixed number of columns and indefinite number of rows
	//Each column must be of the same width
	class __MONKI_INTERFACE CGridLayout : public CLayout
	{
	public:

		CGridLayout( CView* pOwner );
		virtual ~CGridLayout();

		bool operator()( std::vector< CLayoutItem* > VecItems );

	protected:

	};

};

#endif//_GUIQOR_VIEW_GRIDLAYOUT_H_
