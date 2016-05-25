//StringHelper.cpp

//#include "stdafx.h"
#include "WinQL/CodeServices/Text/StringHelper.h"
#include "WinQL/CodeServices/Locale/Locale.h"

//------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	unsigned short CCRTStringHelper::GetLevel1CharType( CLocale& Locale, TCHAR& tCh )
	{
		unsigned short wResult = 0;
		GetCharType( Locale, nsWin32::CT_CType1, tCh, wResult );
		return wResult;
	}

	//--------------------------------------------------------------------------------
	unsigned short CCRTStringHelper::GetLevel2CharType( CLocale& Locale, TCHAR& tCh )
	{
		unsigned short wResult = 0;
		GetCharType( Locale, nsWin32::CT_CType2, tCh, wResult );
		return wResult;
	}

	//--------------------------------------------------------------------------------
	unsigned short CCRTStringHelper::GetLevel3CharType( CLocale& Locale, TCHAR& tCh )
	{
		unsigned short wResult = 0;
		GetCharType( Locale, nsWin32::CT_CType3, tCh, wResult );
		return wResult;
	}

	//--------------------------------------------------------------------------------
	unsigned short CCRTStringHelper::GetLevel1CharTypeA( CLocale& Locale, char& Ch )
	{
		unsigned short wResult = 0;
		GetCharTypeA( Locale, nsWin32::CT_CType1, Ch, wResult );
		return wResult;
	}

	//--------------------------------------------------------------------------------
	unsigned short CCRTStringHelper::GetLevel2CharTypeA( CLocale& Locale, char& Ch )
	{
		unsigned short wResult = 0;
		GetCharTypeA( Locale, nsWin32::CT_CType2, Ch, wResult );
		return wResult;
	}

	//--------------------------------------------------------------------------------
	unsigned short CCRTStringHelper::GetLevel3CharTypeA( CLocale& Locale, char& Ch )
	{
		unsigned short wResult = 0;
		GetCharTypeA( Locale, nsWin32::CT_CType3, Ch, wResult );
		return wResult;
	}

	//--------------------------------------------------------------------------------
	bool CCRTStringHelper::GetCharTypeA( CLocale& Locale, unsigned long dwInfoType, char& Ch, unsigned short& wCharType )
	{
		bool bResult = m_Win32StringHelper.GetStringTypeA( Locale.ID(), dwInfoType, &Ch, 1, &wCharType ) ? true : false;
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CCRTStringHelper::GetCharType( CLocale& Locale, unsigned long dwInfoType, TCHAR& tCh, unsigned short& wCharType )
	{
		bool bResult = m_Win32StringHelper.GetStringTypeExT( Locale.ID(), dwInfoType, &tCh, 1, &wCharType ) ? true : false;
		return bResult;
	}


};//namespace nsWin32
