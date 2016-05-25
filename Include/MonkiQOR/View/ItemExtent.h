///ItemExtent.h

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif	__QCMP_OPTIMIZEINCLUDE

#ifndef _GUIQOR_VIEW_LAYOUT_ITEMEXTENT_H_
#define _GUIQOR_VIEW_LAYOUT_ITEMEXTENT_H_

#include "SystemQOR.h"
#include "Size.h"

//------------------------------------------------------------------------------
namespace nsMonki
{
	//------------------------------------------------------------------------------
	//Min Max and Ideal dimensions for an item in arbitrary units
	class __MONKI_INTERFACE CItemExtent
	{
	public:

		CItemExtent();
		CItemExtent( const CItemExtent& src );
		virtual ~CItemExtent();
		CItemExtent& operator = ( const CItemExtent& src );

		virtual bool Min( CSize& MinSize );
		virtual bool Max( CSize& MaxSize );
		virtual bool Ideal( CSize& IdealSize );

		virtual void SetMin( const CSize& MinSize );
		virtual void SetMax( const CSize& MaxSize );
		virtual void SetIdeal( const CSize& IdealSize );

	protected:

		CSize m_MinSize;
		CSize m_IdealSize;
		CSize m_MaxSize;

	private:

		bool m_bMinSet;
		bool m_bMaxSet;
		bool m_bIdealSet;
	};

};

#endif//_GUIQOR_VIEW_LAYOUT_ITEMEXTENT_H_
