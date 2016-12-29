//Model.cpp

#include "MammutQOR/Model.h"
#include "AppoCritaQOR/Controller.h"

//------------------------------------------------------------------------------
namespace nsMammut
{

	//------------------------------------------------------------------------------
	CModelItem::CModelItem()
	{
		m_pContainer = 0;
	}

	//------------------------------------------------------------------------------
	CModelItem::CModelItem( CModel* pContainer )
	{
		m_pContainer = pContainer;
		if( m_pContainer )
		{
			m_pContainer->insert( Ref() );
		}
	}

	//------------------------------------------------------------------------------
	CModelItem::~CModelItem()
	{
	}

	//------------------------------------------------------------------------------
	CModelItem::CModelItem( const CModelItem& src )
	{
		m_pContainer = src.m_pContainer;
		if( m_pContainer )
		{
			m_pContainer->insert( Ref() );
		}
		*this = src;
	}

	//------------------------------------------------------------------------------
	CModelItem& CModelItem::operator = ( const CModelItem& src )
	{
		return *this;
	}

	//------------------------------------------------------------------------------
	CModelItem::refType CModelItem::Ref( void )
	{
		return refType( this, false );
	}

	//------------------------------------------------------------------------------
	void CModelItem::Lock( void ) const
	{
	}

	//------------------------------------------------------------------------------
	void CModelItem::Unlock( void ) const
	{
	}

	//------------------------------------------------------------------------------
	CModelItem::refType CModelItem::Clone( void )
	{
		return refType( new CModelItem( *this ), true );		
	}


	__QOR_IMPLEMENT_OCLASS_LUID( CModel );

__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usage: stored in member for later use" )

	//------------------------------------------------------------------------------
	CModel::CModel() : CModelItem(), m_Observable( *this )
	{
	}

	//------------------------------------------------------------------------------
	CModel::CModel( const CModel& src ) : CModelItem(), m_Observable( *this )
	{
		*this = src;
	}

	//------------------------------------------------------------------------------
	CModel::CModel( CModel* pContainer ) : CModelItem(), m_Observable( *this )
	{
		m_pContainer = pContainer;
		if( m_pContainer )
		{
			m_pContainer->insert( Ref() );
		}
	}

__QCMP_WARNING_POP

	//------------------------------------------------------------------------------
	CModel& CModel::operator = ( const CModel& src )
	{
		SetController( src.GetController() );
		CModel::iterator it = src.begin();
		while( it != src.end() )
		{
			this->insert( it->Clone() );
		}
		return *this;
	}

	//------------------------------------------------------------------------------
	CModel::~CModel()
	{
	}

	//------------------------------------------------------------------------------
	CModel::refType CModel::Clone( void )
	{
		return refType( new CModel( *this ), true );		
	}

	//------------------------------------------------------------------------------
	void CModel::SetController( nsQOR::CController* pController )
	{
		m_pController = pController;
	}

	//------------------------------------------------------------------------------
	nsQOR::CController* CModel::GetController( void ) const
	{
		return m_pController;
	}

	//------------------------------------------------------------------------------
    CModel::iterator CModel::begin( void ) const
	{
		return iterator( iterator::CModelNode( const_cast< CModel* >( this ), 0 ) );
	}

	//------------------------------------------------------------------------------
    CModel::iterator CModel::end( void ) const
	{
		return iterator( iterator::CModelNode( const_cast< CModel* >( this ), 0 ) );
	}

	//------------------------------------------------------------------------------
	CModel::iterator CModel::insert( CModel::refType Item )
	{
		return end();
	}

	//------------------------------------------------------------------------------
	void CModel::OnChanged( CModel::refType refItem )
	{
		m_Observable.Update();
	}

	//------------------------------------------------------------------------------
	CModel::refType CModel::operator[]( unsigned long )
	{
		return CModel::refType();
	}

}//nsMammut
