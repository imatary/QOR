//Char_UN.inl

//implementation of UNicode Character class

//--------------------------------------------------------------------------------
template<> char UTF32Char::To_char() const
{
	char cResult = static_cast< char >( To_int() );
	return cResult;
}

//--------------------------------------------------------------------------------
template<> signed char UTF32Char::To_schar() const
{
	signed char scResult = static_cast< signed char >( To_int() );
	return scResult;
}

//--------------------------------------------------------------------------------
template<> unsigned char UTF32Char::To_uchar() const
{
	unsigned char ucResult = static_cast< unsigned char >( To_int() );
	return ucResult;
}

//--------------------------------------------------------------------------------
template<> unsigned int UTF32Char::To_uint() const
{
	unsigned int uiResult = static_cast< unsigned int >( To_int() );
	return uiResult;
}

//--------------------------------------------------------------------------------
template<> int UTF32Char::To_int() const
{
	int iResult = 0;
	char* dst = reinterpret_cast< char* >( &iResult );
	wchar_t wchar = m;    
    //errno_t e;
	size_t sizeInBytes = 2;    
    
    if ( dst == NULL && sizeInBytes > 0 )
    {
        // indicate do not have state-dependent encodings
        iResult = 0;
    }
	else
	{
		iResult = -1;

		// validation section
		// we need to cast sizeInBytes to int, so we make sure we are not going to truncate sizeInBytes
		//_VALIDATE_RETURN_ERRCODE(sizeInBytes <= INT_MAX, EINVAL);

		CLocaleUpdate _loc_update( 0 );

		if ( _loc_update.GetLocaleT()->LocaleInfoPtr()->Handles()[ CLocale::LCCTYPE ] == CLocale::_CLOCALEHANDLE )
		{
			if ( wchar > 255 )  // validate high byte
			{
				if ( dst != NULL && sizeInBytes > 0 )
				{
					memset( dst, 0, sizeInBytes );
				}
				errno = EILSEQ;
			}
			else
			{
				if ( dst != NULL )
				{
					//_VALIDATE_RETURN_ERRCODE(sizeInBytes > 0, ERANGE);
					*dst = (char) wchar;
				}
			}
		}
		else
		{
			int size;
			int defused = false;

			if ( ( ( size = _loc_update.GetLocaleT()->LocaleInfoPtr()->CodePage().WideCharToMultiByte( 0, &wchar, 1, dst, (int)sizeInBytes, NULL, &defused ) ) == 0 ) || ( defused ) )
			{
				nsWin32::CErrorHelper ErrorHelper;
				if( size == 0 && ErrorHelper.GetLastError() == ErrorInsufficientBuffer )
				{
					if( dst != NULL && sizeInBytes > 0 )
					{
						memset( dst, 0, sizeInBytes );
					}
					//_VALIDATE_RETURN_ERRCODE(("Buffer too small", 0), ERANGE);
				}
				errno = EILSEQ;				
			}
		}
	}

	return iResult;
}

//--------------------------------------------------------------------------------
template<> wchar_t UTF32Char::To_wchar() const
{
	return m;
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isalnum() const
{
	_WINQ_FCONTEXT( "UTF32Char::isalnum" );
	bool bResult = false;
	bResult = ( isctype( Alpha | Digit, 0 ) ? true : false );
	return bResult;
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isalpha() const
{
	return ( isctype( Alpha, 0 ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::ascii_isalpha() const
{
	bool bResult = ( ( L'A' <= ( m ) && ( m ) <= L'Z') || ( L'a' <= ( m ) && ( m ) <= L'z' ) );
	return bResult;
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isblank() const
{
	return ( isctype( Blank, 0 ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::iscntrl() const
{
	return ( isctype( Control, 0 ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isdigit() const
{
	return ( isctype( Digit, 0 ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isgraph() const
{
	return ( isctype( Punct | Alpha | Digit, 0 ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::islower() const
{
	return ( isctype( Lower, 0 ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isprint() const
{
	return ( isctype( Blank | Punct | Alpha | Digit, 0 ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::ispunct() const
{
	return ( isctype( Punct, 0 ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isspace() const
{
	return ( isctype( Space, 0 ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isupper() const
{
	return ( isctype( Upper, 0 ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isxdigit() const
{
	CLocaleUpdate LocaleUpdate( 0 );
	return isctype( Hex, LocaleUpdate.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> int UTF32Char::toascii() const
{
	return static_cast< int >( m & 0x7f );
}

//--------------------------------------------------------------------------------
template<> int UTF32Char::tolower() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale(QOR_PP_SYNCHRONIZE)().LocaleChanged() == false )
	{
		return ascii_tolower();
	}
	else
	{
		return tolower( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> int UTF32Char::ascii_tolower() const
{
	int iResult = ( ( ( ( m ) >= L'A' ) && ( ( m ) <= L'Z' ) ) ? ( ( m ) - L'A' + L'a' ) : ( m ) );
	return iResult;
}

//--------------------------------------------------------------------------------
template<> int UTF32Char::toupper() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale(QOR_PP_SYNCHRONIZE)().LocaleChanged() == false )
	{
		return ascii_toupper();
	}
	else
	{
		return toupper( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> int UTF32Char::ascii_toupper() const
{
	int iResult = ( ( ( ( m ) >= L'a' ) && ( ( m ) <= L'z' ) ) ? ( ( m ) - L'a' + L'A' ) : ( m ) );
	return iResult;
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isalnum( nsWin32::CLocaleThreadData* plocinfo ) const
{
	return ( isctype( Alpha | Digit, plocinfo ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isalpha( nsWin32::CLocaleThreadData* plocinfo ) const
{
	return ( isctype( Alpha, plocinfo ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isblank( nsWin32::CLocaleThreadData* plocinfo ) const
{
	return ( isctype( Blank, plocinfo ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::iscntrl( nsWin32::CLocaleThreadData* plocinfo ) const
{
	return ( isctype( Control, plocinfo ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isdigit( nsWin32::CLocaleThreadData* plocinfo ) const
{
	return ( isctype( Digit, plocinfo ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isgraph( nsWin32::CLocaleThreadData* plocinfo ) const
{
	return ( isctype( Punct | Alpha | Digit, plocinfo ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::islower( nsWin32::CLocaleThreadData* plocinfo ) const
{
	return ( isctype( Lower, plocinfo ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isprint( nsWin32::CLocaleThreadData* plocinfo ) const
{
	return ( isctype( Blank | Punct | Alpha | Digit, plocinfo ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::ispunct( nsWin32::CLocaleThreadData* plocinfo ) const
{
	return ( isctype( Punct, plocinfo ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isspace( nsWin32::CLocaleThreadData* plocinfo ) const
{
	return ( isctype( Space, plocinfo ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isupper( nsWin32::CLocaleThreadData* plocinfo ) const
{
	return ( isctype( Upper, plocinfo ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isxdigit( CLocaleThreadData* pLocaleThreadData ) const
{
	return ( isctype( Hex, pLocaleThreadData ) ? true : false );
}

//--------------------------------------------------------------------------------
template<> int UTF32Char::tolower( CLocaleThreadData* pLocaleThreadData ) const
{
    wint_t widechar;

    if( m == WEOF )
	{
        widechar = m;
	}
	else
	{
		CLocaleUpdate _loc_update( pLocaleThreadData );

		if ( _loc_update.GetLocaleT()->LocaleInfoPtr()->Handles()[ CLocale::LCCTYPE ] == CLocale::_CLOCALEHANDLE )
		{
			widechar = static_cast< wint_t >( ascii_tolower() );
		}
		else
		{
			CWString strW;
			strW.Reserve( 1 );
			// if checking case of c does not require API call, do it
			if ( m < 256 )
			{
				if( !isupper( _loc_update.GetLocaleT() ) )
				{
					widechar = m;
				} 
				else 
				{
					widechar = _loc_update.GetLocaleT()->LocaleInfoPtr()->CLMap()[ m ];
				}
			}
			else if ( 0 == CSetLoc::__crtLCMapStringW( _loc_update.GetLocaleT(), _loc_update.GetLocaleT()->LocaleInfoPtr()->Handles()[ CLocale::LCCTYPE ], LCMap_LowerCase, (const wchar_t*)c_str(), 1, strW(), /*1,*/ _loc_update.GetLocaleT()->LocaleInfoPtr()->CodePage() ) )
			{	// convert wide char to lowercase 
				widechar = m;
			}
			else
			{
				widechar = strW.GetBuffer()[ 0 ];
			}
		}
	}
    return widechar;
}

//--------------------------------------------------------------------------------
template<> int UTF32Char::toupper( CLocaleThreadData* pLocaleThreadData ) const
{
    wint_t widechar;

    if( m == WEOF )
	{
        widechar = m;
	}
	else
	{
		CLocaleUpdate _loc_update( pLocaleThreadData );

		if ( _loc_update.GetLocaleT()->LocaleInfoPtr()->Handles()[ CLocale::LCCTYPE ] == CLocale::_CLOCALEHANDLE )
		{
			widechar = static_cast< wint_t >( ascii_toupper() );
		}
		else
		{
			CWString strW;
			// if checking case of c does not require API call, do it
			if ( m < 256 ) 
			{
				if ( !islower( _loc_update.GetLocaleT() ) ) 
				{
					widechar = m;
				} 
				else 
				{
					widechar = _loc_update.GetLocaleT()->LocaleInfoPtr()->CUMap()[ m ];
				}
			}
			else if ( 0 == CSetLoc::__crtLCMapStringW( _loc_update.GetLocaleT(), _loc_update.GetLocaleT()->LocaleInfoPtr()->Handles()[ CLocale::LCCTYPE ], LCMap_UpperCase, (const wchar_t*)c_str(), 1, strW(), /*1,*/ _loc_update.GetLocaleT()->LocaleInfoPtr()->CodePage() ) )
			{	// convert wide char to uppercase				
				widechar = m;
			}
			else
			{
				widechar = strW.GetBuffer()[ 0 ];
			}
		}
	}
    return widechar;
}

//--------------------------------------------------------------------------------
template<> bool UTF32Char::isleadbyte(nsWin32::CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ( _loc_update.GetLocaleT()->LocaleInfoPtr()->CType()[ static_cast< unsigned char >( m ) ] & LeadByte ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> int UTF32Char::todigit() const
{
#	define DIGIT_RANGE_TEST(zero)	\
	if( m < zero )					\
		return -1;					\
	if( m < zero + 10 )				\
	{								\
		return m - zero;			\
	}

	DIGIT_RANGE_TEST( 0x0030 )		// 0030;DIGIT ZERO
	if( m < 0xFF10)					// FF10;FULLWIDTH DIGIT ZERO
	{
		DIGIT_RANGE_TEST(0x0660)    // 0660;ARABIC-INDIC DIGIT ZERO
		DIGIT_RANGE_TEST(0x06F0)    // 06F0;EXTENDED ARABIC-INDIC DIGIT ZERO
		DIGIT_RANGE_TEST(0x0966)    // 0966;DEVANAGARI DIGIT ZERO
		DIGIT_RANGE_TEST(0x09E6)    // 09E6;BENGALI DIGIT ZERO
		DIGIT_RANGE_TEST(0x0A66)    // 0A66;GURMUKHI DIGIT ZERO
		DIGIT_RANGE_TEST(0x0AE6)    // 0AE6;GUJARATI DIGIT ZERO
		DIGIT_RANGE_TEST(0x0B66)    // 0B66;ORIYA DIGIT ZERO
		DIGIT_RANGE_TEST(0x0C66)    // 0C66;TELUGU DIGIT ZERO
		DIGIT_RANGE_TEST(0x0CE6)    // 0CE6;KANNADA DIGIT ZERO
		DIGIT_RANGE_TEST(0x0D66)    // 0D66;MALAYALAM DIGIT ZERO
		DIGIT_RANGE_TEST(0x0E50)    // 0E50;THAI DIGIT ZERO
		DIGIT_RANGE_TEST(0x0ED0)    // 0ED0;LAO DIGIT ZERO
		DIGIT_RANGE_TEST(0x0F20)    // 0F20;TIBETAN DIGIT ZERO
		DIGIT_RANGE_TEST(0x1040)    // 1040;MYANMAR DIGIT ZERO
		DIGIT_RANGE_TEST(0x17E0)    // 17E0;KHMER DIGIT ZERO
		DIGIT_RANGE_TEST(0x1810)    // 1810;MONGOLIAN DIGIT ZERO


		return -1;
	}
#undef DIGIT_RANGE_TEST

									// FF10;FULLWIDTH DIGIT ZERO
	if( m < 0xFF10 + 10 )
	{
		return m - 0xFF10;
	}
	return -1;
}

//--------------------------------------------------------------------------------
template<> int UTF32Char::ischartype( int mask, CLocaleThreadData* pLocaleThreadData ) const
{		
	if( m == WEOF )
	{
		return 0;
	}

	if( m < 256 )
	{
		return (int)( CharData::sc_usWCType[ m ] & mask );
	}

	wint_t d = 0;

	if ( TheSystem().As< nsWin32::CSystem >()->Locale(QOR_PP_SYNCHRONIZE)().LocaleChanged() == false )
	{			
		CLocaleThreadData __initiallocalestructinfo;
		if ( CSetLoc::__crtGetStringTypeW( &__initiallocalestructinfo, CT_CType1, (const wchar_t*)c_str(), 1, reinterpret_cast< unsigned short* >( &d ), __initiallocalestructinfo.LocaleInfoPtr()->CodePage(), __initiallocalestructinfo.LocaleInfoPtr()->Handles()[ CLocale::LCCTYPE ] ) == 0 )
		{
			d = 0;
		}
	}
	else   
    {
		CLocaleUpdate _loc_update( pLocaleThreadData );

		if ( CSetLoc::__crtGetStringTypeW( _loc_update.GetLocaleT(), CT_CType1, (const wchar_t*)c_str(), 1, reinterpret_cast< unsigned short* >( &d ), _loc_update.GetLocaleT()->LocaleInfoPtr()->CodePage(), _loc_update.GetLocaleT()->LocaleInfoPtr()->Handles()[ CLocale::LCCTYPE ] ) == 0 )
		{
			d = 0;
		}
	}

	return (int)( d & mask );
}

//--------------------------------------------------------------------------------
template<> int UTF32Char::isctype( int mask, nsWin32::CLocaleThreadData* plocinfo ) const
{
	_WINQ_FCONTEXT( "UTF32Char::isctype" );
	int iResult = 0;
	__QOR_PROTECT
	{
		wint_t d = 0;

		if( m == WEOF )
		{
			iResult = 0;
		}
		else
		{
			if( m < 256 )
			{
				iResult = (int)( CharData::sc_usWCType[ m ] & mask );
			}
			else
			{
				if( TheSystem().As< nsWin32::CSystem >()->Locale(QOR_PP_SYNCHRONIZE)().LocaleChanged() == false )
				{
					CLocaleThreadData __initiallocalestructinfo;
					//TODO:if ( CSetLoc::__crtGetStringTypeW( &__initiallocalestructinfo, CT_CType1, c_str(), 1, reinterpret_cast< unsigned short* >( &d ), __initiallocalestructinfo.LocaleInfoPtr()->CodePage(), __initiallocalestructinfo.LocaleInfoPtr()->Handles()[ CLocale::LCCTYPE ] ) == 0 )
					{
						d = 0;
					}
				}
				else
				{
					CLocaleUpdate _loc_update( plocinfo );
					//TODO:if ( CSetLoc::__crtGetStringTypeW( _loc_update.GetLocaleT(), CT_CType1, c_str(), 1, reinterpret_cast< unsigned short* >( &d ), _loc_update.GetLocaleT()->LocaleInfoPtr()->CodePage(), _loc_update.GetLocaleT()->LocaleInfoPtr()->Handles()[ CLocale::LCCTYPE ] ) == 0 )
					{
						d = 0;
					}
				}

				iResult = (int)( d & mask );
			}
		}

	}__QOR_ENDPROTECT

	return iResult;
}

//--------------------------------------------------------------------------------
template<> int UTF32Char::chvalidator( nsWin32::CLocaleThreadData* plocinfo, int mask ) const
{
	CLocaleUpdate _loc_update( plocinfo );
	return ( _loc_update.GetLocaleT()->LocaleInfoPtr()->CType()[ static_cast< unsigned char >( m ) ] & mask );
}
