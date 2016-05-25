//StringHelper.h

//WWL String discrimination and extended data helper

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#ifndef _WINQL_CS_TXT_STRINGHELPER_H_
#define _WINQL_CS_TXT_STRINGHELPER_H_

#include "WinQL/CodeServices/StringServices.h"
#include "WinQL/OSServices/I18n.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{

	class CLocale;

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( WINQL ) CCRTStringHelper
	{
	public:

		//--------------------------------------------------------------------------------
		CCRTStringHelper()
		{
		}

		//--------------------------------------------------------------------------------
		~CCRTStringHelper()
		{
		}

		unsigned short GetLevel1CharType( CLocale& Locale, TCHAR& tCh );
		unsigned short GetLevel2CharType( CLocale& Locale, TCHAR& tCh );
		unsigned short GetLevel3CharType( CLocale& Locale, TCHAR& tCh );
		unsigned short GetLevel1CharTypeA( CLocale& Locale, char& Ch );		
		unsigned short GetLevel2CharTypeA( CLocale& Locale, char& Ch );		
		unsigned short GetLevel3CharTypeA( CLocale& Locale, char& Ch );

		//--------------------------------------------------------------------------------
		unsigned short GetLevel1CharTypeW( wchar_t& wCh )
		{
			unsigned short wResult = 0;
			GetCharTypeW( nsWin32::CBaseStringHelper::CTType1 , wCh, wResult );
			return wResult;
		}

		//--------------------------------------------------------------------------------
		unsigned short GetLevel2CharTypeW( wchar_t& wCh )
		{
			unsigned short wResult = 0;
			GetCharTypeW( nsWin32::CBaseStringHelper::CTType2, wCh, wResult );
			return wResult;
		}

		//--------------------------------------------------------------------------------
		unsigned short GetLevel3CharTypeW( wchar_t& wCh )
		{
			unsigned short wResult = 0;
			GetCharTypeW( nsWin32::CBaseStringHelper::CTType3, wCh, wResult );
			return wResult;
		}

		//--------------------------------------------------------------------------------
		bool GetCharTypeW( unsigned long dwInfoType, wchar_t& wCh, unsigned short& wCharType )
		{
			bool bResult = m_Win32StringHelper.GetStringTypeW( dwInfoType, &wCh, 1, &wCharType ) ? true : false;
			return bResult;
		}

		bool GetCharTypeA( CLocale& Locale, unsigned long dwInfoType, char& Ch, unsigned short& wCharType );
		bool GetCharType( CLocale& Locale, unsigned long dwInfoType, TCHAR& tCh, unsigned short& wCharType );

		//--------------------------------------------------------------------------------
		int FoldString( unsigned long dwMapFlags, const TCHAR* lpSrcStr, int cchSrc, TCHAR* lpDestStr, int cchDest )
		{
			int iResult = m_Win32StringHelper.FoldStringT( dwMapFlags, lpSrcStr, cchSrc, lpDestStr, cchDest );
			return iResult;
		}

		//--------------------------------------------------------------------------------
		char* CharLowerA( char* lpsz )
		{
			char* strResult = m_Win32StringHelper.CharLowerA( lpsz );
			return strResult;
		}

		//--------------------------------------------------------------------------------
		wchar_t* CharLowerW( wchar_t* lpwsz )
		{
			wchar_t* strResult = m_Win32StringHelper.CharLowerW( lpwsz );
			return strResult;
		}

		//--------------------------------------------------------------------------------
		unsigned long CharLowerBuffA( char* lpsz, unsigned long cchLength )
		{
			unsigned long dwResult = m_Win32StringHelper.CharLowerBuffA( lpsz, cchLength );
			return dwResult;
		}

		//--------------------------------------------------------------------------------
		unsigned long CharLowerBuffW( wchar_t* lpwsz, unsigned long cchLength )
		{
			unsigned long dwResult = m_Win32StringHelper.CharLowerBuffW( lpwsz, cchLength );
			return dwResult;
		}

		//--------------------------------------------------------------------------------
		TCHAR* CharNext( const TCHAR* lpsz )
		{
			TCHAR* strResult = m_Win32StringHelper.CharNextT( lpsz );
			return strResult;
		}

		//--------------------------------------------------------------------------------
		TCHAR* CharPrev( const TCHAR* lpszStart, const TCHAR* lpszCurrent )
		{
			TCHAR* strResult = m_Win32StringHelper.CharPrevT( lpszStart, lpszCurrent );
			return strResult;
		}

		//--------------------------------------------------------------------------------
		bool CharToOem( const TCHAR* lpszSrc, char* lpszDst )
		{
			bool bResult = m_Win32StringHelper.CharToOemT( lpszSrc, lpszDst );
			return bResult;
		}

		//--------------------------------------------------------------------------------
		bool CharToOemBuffA( const char* lpszSrc, char* lpszDst, unsigned long cchDstLength )
		{
			bool bResult = m_Win32StringHelper.CharToOemBuffA( lpszSrc, lpszDst, cchDstLength );
			return bResult;
		}

		//--------------------------------------------------------------------------------
		bool CharToOemBuffW( const wchar_t* lpwszSrc, char* lpszDst, unsigned long cchDstLength )
		{
			bool bResult = m_Win32StringHelper.CharToOemBuffW( lpwszSrc, lpszDst, cchDstLength );
			return bResult;
		}

		//--------------------------------------------------------------------------------
		TCHAR* CharUpper( TCHAR* lpsz )
		{
			TCHAR* strResult = m_Win32StringHelper.CharUpperT( lpsz );
			return strResult;
		}

		//--------------------------------------------------------------------------------
		unsigned long CharUpperBuffA( char* lpsz, unsigned long cchLength )
		{
			unsigned long dwResult = m_Win32StringHelper.CharUpperBuffA( lpsz, cchLength );
			return dwResult;
		}

		//--------------------------------------------------------------------------------
		unsigned long CharUpperBuffW( wchar_t* lpwsz, unsigned long cchLength )
		{
			unsigned long dwResult = m_Win32StringHelper.CharUpperBuffW( lpwsz, cchLength );
			return dwResult;
		}

		//--------------------------------------------------------------------------------
		bool IsCharAlpha( TCHAR tCh )
		{
			bool bResult = m_Win32StringHelper.IsCharAlphaT( tCh );
			return bResult;
		}

		//--------------------------------------------------------------------------------
		bool IsCharAlphaNumeric( TCHAR tCh )
		{
			bool bResult = m_Win32StringHelper.IsCharAlphaNumericT( tCh );
			return bResult;
		}

		//--------------------------------------------------------------------------------
		bool IsCharLower( TCHAR tCh )
		{
			bool bResult = m_Win32StringHelper.IsCharLowerT( tCh );
			return bResult;
		}

		//--------------------------------------------------------------------------------
		bool IsCharUpper( TCHAR tCh )
		{
			bool bResult = m_Win32StringHelper.IsCharUpperT( tCh );
			return bResult;
		}

		//--------------------------------------------------------------------------------
		int LoadStringA( nsWin32::InstanceHandle hInstance, unsigned int uID, char* lpBuffer, int nBufferMax )
		{
			int iResult = m_Win32StringHelper.LoadStringA( hInstance, uID, lpBuffer, nBufferMax );
			return iResult;
		}

		//--------------------------------------------------------------------------------
		int LoadStringW( nsWin32::InstanceHandle hInstance, unsigned int uID, wchar_t* lpBuffer, int nBufferMax )
		{
			int iResult = m_Win32StringHelper.LoadStringW( hInstance, uID, lpBuffer, nBufferMax );
			return iResult;
		}

		//--------------------------------------------------------------------------------
		bool OemToChar( const char* lpszSrc, TCHAR* lpszDst )
		{
			bool bResult = m_Win32StringHelper.OemToCharT( lpszSrc, lpszDst );
			return bResult;
		}

		//--------------------------------------------------------------------------------
		bool OemToCharBuffA( const char* lpszSrc, char* lpszDst, unsigned long cchDstLength )
		{
			bool bResult = m_Win32StringHelper.OemToCharBuffA( lpszSrc, lpszDst, cchDstLength );
			return bResult;
		}

		//--------------------------------------------------------------------------------
		bool OemToCharBuffW( const wchar_t* lpwszSrc, wchar_t* lpwszDst, unsigned long cchDstLength )
		{
			bool bResult = m_Win32StringHelper.OemToCharBuffW( lpwszSrc, lpwszDst, cchDstLength );
			return bResult;
		}

		//--------------------------------------------------------------------------------
		int wvsprintfA( char* lpOutput, const char* lpFmt, va_list arglist )
		{
			int iResult = m_Win32StringHelper.wvsprintfA( lpOutput, lpFmt, arglist );
			return iResult;
		}

		//--------------------------------------------------------------------------------
		int wvsprintfW( wchar_t* lpOutput, const wchar_t* lpFmt, va_list arglist )
		{
			int iResult = m_Win32StringHelper.wvsprintfW( lpOutput, lpFmt, arglist );
			return iResult;
		}

		//--------------------------------------------------------------------------------
		int Compare( unsigned long Locale, unsigned long dwCmpFlags, const TCHAR* lpString1, int cchCount1, const TCHAR* lpString2, int cchCount2 )
		{
			int iResult = m_Win32StringHelper.CompareStringT( Locale, dwCmpFlags, lpString1, cchCount1, lpString2, cchCount2 );
			return iResult;
		}

		//--------------------------------------------------------------------------------
		int CompareStringEx( const wchar_t* lpLocaleName, unsigned long dwCmpFlags, const wchar_t* lpString1, int cchCount1, const wchar_t* lpString2, int cchCount2, nsWin32::NLSVersionInfo* lpVersionInformation, void* lpReserved, Cmp_long_ptr lParam )
		{
			int iResult = 0;//TODO: m_Win32BaseStringHelper.CompareStringEx(lpLocaleName, dwCmpFlags, lpString1, cchCount1, lpString2, cchCount2, lpVersionInformation, lpReserved, lParam);
			return iResult;
		}

	protected:

		nsWin32::CBaseStringHelper m_Win32BaseStringHelper;
		nsWin32::CStringHelper m_Win32StringHelper;
	};

}//nsWin32

#endif//_WINQL_CS_TXT_STRINGHELPER_H_

