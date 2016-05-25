///Size.h

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif	__QCMP_OPTIMIZEINCLUDE

#ifndef _GUIQOR_VIEW_LAYOUT_SIZE_H_
#define _GUIQOR_VIEW_LAYOUT_SIZE_H_

#include "SystemQOR.h"

//------------------------------------------------------------------------------
namespace nsMonki
{
	//------------------------------------------------------------------------------
	//2D Size Data
	class __MONKI_INTERFACE CSize
	{
	public:

		CSize();
		CSize( unsigned long x, unsigned long y );
		CSize( const CSize& src );
		~CSize();
		CSize& operator = ( const CSize& src );

		unsigned long Area( void );
		unsigned long X( void );
		unsigned long Y( void );
		void Set( unsigned long x, unsigned long y);

	protected:

		unsigned long m_X;
		unsigned long m_Y;
	};

};

#endif//_GUIQOR_VIEW_LAYOUT_SIZE_H_
