//View.cpp

#include "MonkiQOR.h"
#include "MonkiQOR/View.h"

//------------------------------------------------------------------------------
namespace nsMonki
{
	//------------------------------------------------------------------------------
	CView::CView() : m_pController( 0 ), m_pParent( 0 )
	{
	}

	//------------------------------------------------------------------------------
	CView::CView( nsAppocrita::CController* pController, CView* pParent ) : m_pController( pController ), m_pParent( pParent )
	{
	}

	//------------------------------------------------------------------------------
	CView::~CView()
	{
	}

	//------------------------------------------------------------------------------
	void CView::SetController( nsAppocrita::CController* pController )
	{
		m_pController = pController;
	}

	//------------------------------------------------------------------------------
	nsAppocrita::CController* CView::GetController( void )
	{
		return m_pController;
	}

	//------------------------------------------------------------------------------
	void CView::SetParent( CView* pParent )
	{
		m_pParent = pParent;
	}

	//------------------------------------------------------------------------------
	CView* CView::GetParent( void )
	{
		return m_pParent;
	}


	/*
	//------------------------------------------------------------------------------
	CCompoundView::~CCompoundView()
	{
	}
	*/
}//namespace nsMonki

