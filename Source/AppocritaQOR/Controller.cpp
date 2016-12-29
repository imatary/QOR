//Controller.cpp

#include "AppocritaQOR/AppocritaQOR.h"
#include "AppocritaQOR/Controller.h"
#include "MonkiQOR/View.h"
//------------------------------------------------------------------------------
namespace nsQOR
{
	//------------------------------------------------------------------------------
	CController::CController() : m_pModel( 0 ), m_Parent( 0 )
	{
	}

	//------------------------------------------------------------------------------
	CController::CController( nsMammut::CModel* pModel, CController::ref_type Parent ) : m_pModel( pModel ), m_Parent( Parent )
	{
	}

	//------------------------------------------------------------------------------
	CController::~CController()
	{
	}

	//------------------------------------------------------------------------------
	CController::ref_type CController::GetParent( void )
	{
		return m_Parent->Ref();
	}

	//------------------------------------------------------------------------------
	void CController::SetParent( CController::ref_type Parent )
	{
		m_Parent = Parent->Ref();
	}

	//------------------------------------------------------------------------------
	void CController::SetModel( nsMammut::CModel* pModel )
	{
		m_pModel = pModel;
	}

	//------------------------------------------------------------------------------
	nsMammut::CModel* CController::GetModel( void )
	{
		return m_pModel;
	}

	//------------------------------------------------------------------------------
	void CController::AddChild( CController::ref_type Child )
	{
		m_Children.push_back( Child.operator->() );
	}

	//------------------------------------------------------------------------------
	void CController::RemoveChild( CController::ref_type Child )
	{
		IController* pTarget = Child.operator->();
		m_Children.erase( std::remove_if( m_Children.begin(), m_Children.end(), [ pTarget ]( IController* Element)->bool
		{ 
			return Element == pTarget;
		} ), m_Children.end() );
	}

}//nsQOR

