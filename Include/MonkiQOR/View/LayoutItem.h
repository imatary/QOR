///LayoutItem.h

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif	__QCMP_OPTIMIZEINCLUDE

#ifndef _GUIQOR_VIEW_LAYOUTITEM_H_
#define _GUIQOR_VIEW_LAYOUTITEM_H_

#include "SystemQOR.h"
#include "ItemExtent.h"

//------------------------------------------------------------------------------
namespace nsMonki
{
	//------------------------------------------------------------------------------
	//Abstract Base class for things that can be layed out
	class __MONKI_INTERFACE CLayoutItem : public CItemExtent
	{
	public:

		CLayoutItem();
		CLayoutItem( const CLayoutItem& src );
		virtual ~CLayoutItem();
		CLayoutItem& operator = ( const CLayoutItem& src );

	protected:

		//Alignment
		//Elastic X
		//Elastic Y
		//Position
	};


};

#endif//_GUIQOR_VIEW_LAYOUTITEM_H_
