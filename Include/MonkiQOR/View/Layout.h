///Layout.h

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif	__QCMP_OPTIMIZEINCLUDE

#ifndef _GUIQOR_VIEW_LAYOUT_H_
#define _GUIQOR_VIEW_LAYOUT_H_

#include "SystemQOR.h"
#include "LayoutItem.h"
#include <vector>

//------------------------------------------------------------------------------
namespace nsMonki
{
	class __MONKI_INTERFACE CView;

	//------------------------------------------------------------------------------
	//Base class for View Layout
	class __MONKI_INTERFACE CLayout : public CLayoutItem
	{
	public:

		CLayout( CView* pOwner );
		virtual ~CLayout();

		void SetParent( CLayout* pParent );
		CLayout* GetParent( void );

		bool operator()( std::vector< CLayoutItem* > VecItems );

		virtual bool Min( CSize& MinSize );
		virtual bool Max( CSize& MaxSize );
		virtual bool Ideal( CSize& IdealSize );

		virtual void SetMin( const CSize& MinSize );
		virtual void SetMax( const CSize& MaxSize );
		virtual void SetIdeal( const CSize& IdealSize );

	protected:

		CView* m_pView;
		CLayout* m_pParent;
	};

};

#endif//_GUIQOR_VIEW_LAYOUT_H_
