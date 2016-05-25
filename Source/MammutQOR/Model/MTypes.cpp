//MTypes.cpp

#include "MammutQOR.h"
#include "SystemQOR.h"
#include "MammutQOR/Model/MTypes.h"

//------------------------------------------------------------------------------
namespace nsMammut
{
	//------------------------------------------------------------------------------
	CMLongDouble::CMLongDouble() : nsCodeQOR::LongDouble()
	{
	}

	//------------------------------------------------------------------------------
	CMLongDouble::CMLongDouble( const CMLongDouble& x ) : nsCodeQOR::LongDouble( x )
	{ 
	}

	//------------------------------------------------------------------------------
    CMLongDouble::CMLongDouble( Cmp_C_long_double& x ) : nsCodeQOR::LongDouble( x )
	{
	}
	
	//------------------------------------------------------------------------------
	std::ostream& operator << ( std::ostream& os, const CMLongDouble& mld )
	{
		os << mld.m;
		return os;
	}
	

	//------------------------------------------------------------------------------
	CMUint16::CMUint16() : nsCodeQOR::UInt16()
	{
	}

	//------------------------------------------------------------------------------
	CMUint16::CMUint16(const CMUint16& x) : nsCodeQOR::UInt16(x)
	{
	}

	//------------------------------------------------------------------------------
	CMUint16::CMUint16(Cmp_C_unsigned__int16& x) : nsCodeQOR::UInt16(x)
	{
	}

	//------------------------------------------------------------------------------
	std::ostream& operator << (std::ostream& os, const CMUint16& mu16)
	{
		os << mu16.m;
		return os;
	}

}//nsMammut

/*
 //------------------------------------------------------------------------------
nsCodeQOR::Bool nsCodeQOR::operator==( nsMammut::CMUint16 const& cmp1, nsMammut::CMUint16 const& cmp2 )
{
	return nsCodeQOR::Bool( cmp1.m == cmp2.m );
}
*/