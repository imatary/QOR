//Controller.cpp

#include "AppocritaQOR/AppocritaQOR.h"
#include "AppocritaQOR/Controller.h"
#include "MonkiQOR/View.h"
//------------------------------------------------------------------------------
namespace nsAppocrita
{
	//------------------------------------------------------------------------------
	CController::CController() : m_pModel( 0 ), m_pParent( 0 )
	{
	}

	//------------------------------------------------------------------------------
	CController::CController( nsMammut::CModel* pModel, CController* pParent ) : m_pModel( pModel ), m_pParent( pParent )
	{
	}

	//------------------------------------------------------------------------------
	CController::~CController()
	{
	}

	//------------------------------------------------------------------------------
	CController* CController::GetParent( void )
	{
		return m_pParent;
	}

	//------------------------------------------------------------------------------
	void CController::SetParent( CController* pParent )
	{
		m_pParent = pParent;
	}

	//------------------------------------------------------------------------------
	void CController::SetModelType( const nsCodeQOR::mxGUID* )
	{
	}

	//------------------------------------------------------------------------------
	bool CController::SetModel( nsMammut::CModel* pModel )
	{
		m_pModel = pModel;
		return true;
	}

	//------------------------------------------------------------------------------
	nsMammut::CModel* CController::GetModel( void )
	{
		return m_pModel;
	}
	/*
	//------------------------------------------------------------------------------
	nsMonki::CView* CController::GetView( void )
	{
		return m_pView;
	}

	//------------------------------------------------------------------------------
	nsMonki::CView* CController::CreateView( void )
	{
		return 0;
	}
	*/
	void CController::SetChildFactory( const nsCodeQOR::mxGUID* pClassID, nsCodeQOR::CClassInstanceFactory* pFactory )
	{
	}

	//------------------------------------------------------------------------------
	CController::refType CController::Child( const nsCodeQOR::mxGUID*, unsigned int uiIndex )
	{
		refType Ref;
		return Ref;
	}

	//------------------------------------------------------------------------------
	CCompoundController::CCompoundController() : CController(), CBaseControllerVector()
	{
	}

	//------------------------------------------------------------------------------
	CCompoundController::CCompoundController( nsMammut::CModel* pModel, CCompoundController* pParent ) : CController( pModel, pParent ), CBaseControllerVector()
	{
	}

	//------------------------------------------------------------------------------
	CCompoundController::~CCompoundController()
	{
	}

}//nsAppocrita

