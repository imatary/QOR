//WinQLSystemLocale.cpp

// Copyright Querysoft Limited 2013
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include "WinQL/WinQL.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/System/Locale/WinQLSystemLocale.h"
#include "SystemQOR/MSWindows/MSW_tchar.h"
#include "WinQL/System/WinQLSystem.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID( CSystemLocale );

	//--------------------------------------------------------------------------------
	bool CSystemLocale::EnumAllCodePagesProc( TCHAR* strCodePage )
	{
		_WINQ_SFCONTEXT( "CSystemLocale::EnumAllCodePagesProc" );
		bool bResult = false;
		__QOR_PROTECT
		{
			TCHAR* pEnd = 0;
			unsigned long ulCodePage = _tcstoul( strCodePage, &pEnd, 0 );
			bResult = CSystem::Instance().Locale()().AddCodePage( static_cast< unsigned int >( ulCodePage ) );
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CSystemLocale::AddCodePage( unsigned int uiPage )
	{
		_WINQ_SFCONTEXT( "CSystemLocale::AddCodePage" );
		bool bResult = false;
		__QOR_PROTECT
		{
			CCodePage* pCodePage = new CCodePage( uiPage );
			nsCodeQOR::CTMapPair< unsigned long, CCodePage* > pair( static_cast< unsigned long >( uiPage ), pCodePage );
			m_apCodePages.Append( pCodePage );
			m_MapCodePages.Append( pair );
			bResult = true;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	CSystemLocale::CSystemLocale() : nsWin32::CLocale(), m_bCodePagesEnumerated( false ), m_bLocaleChanged( false )
	{
		_WINQ_FCONTEXT( "CSystemLocale::CSystemLocale" );
		__QOR_PROTECT
		{
			m_ID = m_Win32LocaleHelper.GetSystemDefaultLCID();
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CSystemLocale::~CSystemLocale()
	{
		_WINQ_FCONTEXT( "CSystemLocale::~CSystemLocale" );
	}

	//--------------------------------------------------------------------------------
	unsigned short CSystemLocale::GetDefaultLangID()
	{
		_WINQ_FCONTEXT( "CSystemLocale::GetDefaultLangID" );
		unsigned short LangID = 0;
		__QOR_PROTECT
		{
			LangID = m_Win32LocaleHelper.GetSystemDefaultLangID();
		}__QOR_ENDPROTECT
		return LangID;
	}
			
	//--------------------------------------------------------------------------------
	unsigned long CSystemLocale::GetDefaultLCID()
	{
		_WINQ_FCONTEXT( "CSystemLocale::GetDefaultLCID" );
		unsigned long LcId = 0;
		__QOR_PROTECT
		{
			LcId = m_Win32LocaleHelper.GetSystemDefaultLCID();
		}__QOR_ENDPROTECT
		return LcId;
	}
			
	//--------------------------------------------------------------------------------
	int CSystemLocale::GetDefaultLocaleName( CWStringRef strLocaleName )
	{
		_WINQ_FCONTEXT( "CSystemLocale::GetDefaultLocaleName" );
		int iResult = 0;
		__QOR_PROTECT
		{
			iResult = m_Win32LocaleHelper.GetSystemDefaultLocaleName( strLocaleName );
		}__QOR_ENDPROTECT
		return iResult;
	}
			
	//--------------------------------------------------------------------------------
	bool CSystemLocale::EnumLocalesEx( Locale_EnumProcEx lpLocaleEnumProcEx, unsigned long dwFlags, Cmp_long_ptr lParam, void* lpReserved )
	{
		_WINQ_FCONTEXT( "CSystemLocale::EnumLocalesEx" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = m_Win32LocaleHelper.EnumSystemLocalesEx( lpLocaleEnumProcEx, dwFlags, lParam ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}
			
	//--------------------------------------------------------------------------------
	bool CSystemLocale::EnumLocales( Locale_EnumProc lpLocaleEnumProc, unsigned long dwFlags )
	{
		_WINQ_FCONTEXT( "CSystemLocale::EnumLocales" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = m_Win32LocaleHelper.EnumSystemLocalesT( lpLocaleEnumProc, dwFlags ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CSystemLocale::EnumLanguageGroups( LanguageGroup_EnumProc pLangGroupEnumProc, unsigned long dwFlags, Cmp_long_ptr lParam )
	{
		_WINQ_FCONTEXT( "CSystemLocale::EnumLanguageGroups" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = m_Win32LocaleHelper.EnumSystemLanguageGroupsT( pLangGroupEnumProc, dwFlags, lParam ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CSystemLocale::EnumGeoIDs( unsigned long GeoClass, unsigned long ParentGeoId, Geo_EnumProc lpGeoEnumProc )
	{
		_WINQ_FCONTEXT( "CSystemLocale::EnumGeoIDs" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = m_Win32LocaleHelper.EnumSystemGeoID( GeoClass, ParentGeoId, lpGeoEnumProc ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}
	//--------------------------------------------------------------------------------
	bool CSystemLocale::EnumCodePages( CodePage_EnumProc lpCodePageEnumProc, unsigned long dwFlags )
	{
		_WINQ_FCONTEXT( "CSystemLocale::EnumCodePages" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = m_Win32LocaleHelper.EnumSystemCodePagesT( lpCodePageEnumProc, dwFlags ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	nsWin32::CCodePage* CSystemLocale::CodePage( unsigned int uiPageIndex )
	{
		_WINQ_FCONTEXT( "CSystemLocale::CodePage" );
		nsWin32::CCodePage* pCodePage = 0;
		__QOR_PROTECT
		{
			if( m_bCodePagesEnumerated == false )
			{
				EnumCodePages( (CodePage_EnumProc)&EnumAllCodePagesProc, CP_Installed );
				m_bCodePagesEnumerated = true;
			}
			pCodePage = m_apCodePages[ uiPageIndex ];
		}__QOR_ENDPROTECT
		return pCodePage;
	}

	//--------------------------------------------------------------------------------
	bool CSystemLocale::LocaleChanged()
	{
		_WINQ_FCONTEXT( "CSystemLocale::LocaleChanged" );
		return m_bLocaleChanged;
	}

	//--------------------------------------------------------------------------------
	void CSystemLocale::SetLocaleChanged()
	{
		_WINQ_FCONTEXT( "CSystemLocale::SetLocaleChanged" );
		m_bLocaleChanged = true;
	}

}//nsWin32