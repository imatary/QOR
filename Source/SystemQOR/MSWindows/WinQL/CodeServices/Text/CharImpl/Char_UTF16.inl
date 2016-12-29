//Char_MB.inl

//implementation of Multi Byte Character class

//--------------------------------------------------------------------------------
template<> char UTF16Char::To_char() const
{
	char result = static_cast< char >( To_uchar() );
	return result;
}

//--------------------------------------------------------------------------------
template<> signed char UTF16Char::To_schar() const
{
	signed char result = static_cast< signed char >( To_uchar() );
	return result;
}

//--------------------------------------------------------------------------------
template<> unsigned char UTF16Char::To_uchar() const
{
	unsigned char result;
	
	//_VALIDATE_RETURN_ERRCODE(sizeInBytes <= INT_MAX, EINVAL);

	CLocaleUpdate _loc_update( 0 );

	if ( _loc_update.GetLocaleT()->LocaleInfoPtr()->Handles()[ CLocale::LCCTYPE ] == CLocale::_CLOCALEHANDLE )
	{
		if ( m > 255 )  // validate high byte
		{
			result = 0;
			errno = EILSEQ;
		}
		else
		{
			result = (unsigned char)m;
		}
        return result;
	}
	else
	{
		int size;
		int defused = 0;

		if( ( ( size = _loc_update.GetLocaleT()->LocaleInfoPtr()->CodePage().WideCharToMultiByte( 0, (const wchar_t*)c_str(), 1, (char*)&result, (int)CLocale::mb_cur_max(), NULL, &defused ) ) == 0 ) || ( defused ) )
		{
			nsWin32::CErrorHelper ErrorHelper;
			if ( size == 0 && ErrorHelper.GetLastError() == ErrorInsufficientBuffer )
			{
				result = 0;
				//_VALIDATE_RETURN_ERRCODE(("Buffer too small", 0), ERANGE);
			}
			errno = EILSEQ;
			return result;
		}			
	}

	return result;
}

//--------------------------------------------------------------------------------
template<> unsigned int UTF16Char::To_uint() const
{
	return m;
}

//--------------------------------------------------------------------------------
template<> int UTF16Char::To_int() const
{
	int iResult = static_cast< int >( m );
	return iResult;
}

//--------------------------------------------------------------------------------
template<> wchar_t UTF16Char::To_wchar() const
{
	wchar_t wc = 0;
	wchar_t* pwc = &wc;
	const char* s = reinterpret_cast< const char* >( &m );
	size_t n = 1;
	
    if ( !s || n == 0 )
	{
        // indicate do not have state-dependent encodings, handle zero length string        
	}
    else if ( !*s )
    {
        // handle NULL char
        if( pwc )
		{
            *pwc = 0;
		}
    }
	else
	{
		CLocaleUpdate _loc_update( 0 );
		assert( _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() == 1 || _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() == 2 );

		if( _loc_update.GetLocaleT()->LocaleInfoPtr()->Handles()[ CLocale::LCCTYPE ] == CLocale::_CLOCALEHANDLE )
		{
			if( pwc )
			{
				*pwc = (wchar_t)(unsigned char)*s;
			}        
		}
		else if( isleadbyte( _loc_update.GetLocaleT() ) )
		{
			// multi-byte char

			if( ( _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() <= 1 ) || ( (int)n < _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() ) || ( _loc_update.GetLocaleT()->LocaleInfoPtr()->CodePage().MultiByteToWideChar( MB_Precomposed | MB_Err_Invalid_Chars, s, _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax(), pwc, (pwc) ? 1 : 0 ) == 0 ) )
			{
				// validate high byte of mbcs char
				if( ( n < (size_t)_loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() ) || ( !*( s + 1 ) ) )
				{
					errno = EILSEQ;                
				}
			}
		}
		else 
		{
			// single byte char
			if ( _loc_update.GetLocaleT()->LocaleInfoPtr()->CodePage().MultiByteToWideChar( MB_Precomposed | MB_Err_Invalid_Chars, s, 1, pwc, (pwc) ? 1 : 0 ) == 0 )
			{
				errno = EILSEQ;            
			}        
		}
	}
	return wc;
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isalnum() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Alpha|Digit ) ? true : false;
	}
	else
	{
		return isalnum( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isalpha() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Alpha ) ? true : false;
	}
	else
	{
		return ( isalpha )( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::ascii_isalpha() const
{
	bool bResult = ( ( L'A' <= ( m ) && ( m ) <= L'Z') || ( L'a' <= ( m ) && ( m ) <= L'z' ) );
	return bResult;
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isblank() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Blank ) ? true : false;
	}
	else
	{
		return isblank( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::iscntrl() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Control ) ? true : false;
	}
	else
	{
		return iscntrl( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isdigit() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Digit ) ? true : false;
	}
	else
	{
		return isdigit( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isgraph() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Punct | Alpha | Digit ) ? true : false;
	}
	else
	{
		return isgraph( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::islower() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Lower ) ? true : false;
	}
	else
	{
		return islower( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isprint() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Blank | Punct | Alpha | Digit ) ? true : false;
	}
	else
	{
		return isprint( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::ispunct() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Punct ) ? true : false;
	}
	else
	{
		return ispunct( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isspace() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Space ) ? true : false;
	}
	else
	{
		return isspace( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isupper() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Upper ) ? true : false;
	}
	else
	{
		return isupper( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isxdigit() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Hex ) ? true : false;
	}
	else
	{
		return isxdigit( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> int UTF16Char::toascii() const
{
	return (int)( m & 0x7f );
}

//--------------------------------------------------------------------------------
template<> int UTF16Char::tolower() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale()().LocaleChanged() == false )
	{
		return ascii_tolower();
	}
	else
	{
		return tolower( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> int UTF16Char::ascii_tolower() const
{
	int iResult = ( ( ( ( m ) >= L'A' ) && ( ( m ) <= L'Z' ) ) ? ( ( m ) - L'A' + L'a' ) : ( m ) );
	return iResult;
}

//--------------------------------------------------------------------------------
template<> int UTF16Char::toupper() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale()().LocaleChanged() == false )
	{
		return ascii_toupper();
	}
	else
	{
		return toupper( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> int UTF16Char::ascii_toupper() const
{
	int iResult = ( ( ( ( m ) >= L'a' ) && ( ( m ) <= L'z' ) ) ? ( ( m ) - L'a' + L'A' ) : ( m ) );
	return iResult;
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isalnum( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Alpha | Digit, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isalpha( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Alpha, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isblank( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Blank, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::iscntrl( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Control, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isdigit( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Digit, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isgraph( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Punct | Alpha | Digit, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::islower( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Lower, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isprint( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Blank | Punct | Alpha | Digit, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::ispunct( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Punct, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isspace( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Space, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isupper( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Upper, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isxdigit( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Hex, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> int UTF16Char::tolower( CLocaleThreadData* pLocaleThreadData ) const
{
	int size;
	unsigned char inbuffer[ 3 ];
	CAString outbuffer;
	outbuffer.Reserve( 3 );
	CLocaleUpdate _loc_update( pLocaleThreadData );

	// if checking case of m does not require API call, do it
	if ( (unsigned)m < 256 )
	{
		if( isupper( _loc_update.GetLocaleT() ) )
		{
			return _loc_update.GetLocaleT()->LocaleInfoPtr()->CLMap()[ m ];
		}
		else
		{
			return m;
		}
	}

	// convert int m to multibyte string
	IChar c = m >> 8 & 0xff;
	if ( _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() > 1 && c.isleadbyte( _loc_update.GetLocaleT() ) )
	{
		inbuffer[ 0 ] = c;				// put lead-byte at start of str
		inbuffer[ 1 ] = static_cast< unsigned char >( m );
		inbuffer[ 2 ] = 0;
		size = 2;
	} 
	else 
	{
		// this is an undefined behavior, should probably use towlower instead
		//TODO: errno = EILSEQ;
		inbuffer[ 0 ] = static_cast< unsigned char >( c );
		inbuffer[ 1 ] = 0;
		size = 1;
	}

	// convert to lowercase
	if( 0 == ( size = CSetLoc::__crtLCMapStringA( _loc_update.GetLocaleT(), _loc_update.GetLocaleT()->LocaleInfoPtr()->Handles()[ CLocale::LCCTYPE ], LCMap_LowerCase, (const char*)inbuffer, size, outbuffer(), /*3,*/ _loc_update.GetLocaleT()->LocaleInfoPtr()->CodePage(), true ) ) )
	{
		return m;
	}

	// construct integer return value
	if( size == 1 )
	{
		return ( static_cast< int >( outbuffer.GetBuffer()[ 0 ] ) );
	}
	else
	{
		return ( static_cast< int >( outbuffer.GetBuffer()[ 1 ] ) | ( static_cast< int >( outbuffer.GetBuffer()[ 0 ] ) << 8 ) );
	}
}

//--------------------------------------------------------------------------------
template<> int UTF16Char::toupper( CLocaleThreadData* pLocaleThreadData ) const
{
	//wint_t widechar;
	CWString strWideChar;

	if( m == WEOF )
	{
		return m;
	}

	CLocaleUpdate _loc_update( pLocaleThreadData );

	if( _loc_update.GetLocaleT()->LocaleInfoPtr()->Handles()[ CLocale::LCCTYPE ] == CLocale::_CLOCALEHANDLE )
	{
		return ascii_toupper();
	}

	// if checking case of m does not require API call, do it
	if( m < 256 ) 
	{
		if ( !islower( _loc_update.GetLocaleT() ) ) 
		{
			return m;
		} 
		else 
		{
			return _loc_update.GetLocaleT()->LocaleInfoPtr()->CUMap()[ m ];
		}
	}

	// convert wide char to uppercase
	if( 0 == CSetLoc::__crtLCMapStringW( _loc_update.GetLocaleT(), _loc_update.GetLocaleT()->LocaleInfoPtr()->Handles()[ CLocale::LCCTYPE ], LCMap_UpperCase, (const wchar_t*)c_str(), 1, strWideChar(), /*1,*/ _loc_update.GetLocaleT()->LocaleInfoPtr()->CodePage() ) )
	{
		return m;
	}

	return strWideChar.GetBuffer()[0];
}

//--------------------------------------------------------------------------------
template<> bool UTF16Char::isleadbyte( nsWin32::CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ( _loc_update.GetLocaleT()->LocaleInfoPtr()->CType()[ static_cast< unsigned char >( m ) ] & LeadByte ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> int UTF16Char::todigit() const
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
template<> int UTF16Char::ischartype( int iFlag, CLocaleThreadData* pLocaleThreadData ) const
{
	int iResult = ( ( pLocaleThreadData != 0 && ( pLocaleThreadData->LocaleInfoPtr()->MBCurMax() ) > 1 ) ? 
		isctype( iFlag, pLocaleThreadData ) : chvalidator( pLocaleThreadData, iFlag ) );
	return iResult;
}

//--------------------------------------------------------------------------------
template<> int UTF16Char::isctype( int mask, CLocaleThreadData* plocinfo ) const
{
	int size;
	unsigned short chartype;
	char buffer[3];
	CLocaleUpdate _loc_update(plocinfo);

	// c valid between -1 and 255
	if ( m >= -1 && m <= 255 )
	{
		return _loc_update.GetLocaleT()->LocaleInfoPtr()->CType()[ m ] & mask;
	}

	IChar c = ( m >> 8 & 0xff );
	if( c.isleadbyte( _loc_update.GetLocaleT() ) )
	{
		buffer[ 0 ] = c;			// put lead-byte at start of str
		buffer[ 1 ] = static_cast< char >( m );
		buffer[ 2 ] = 0;
		size = 2;
	} 
	else 
	{
		buffer[ 0 ] = static_cast< char >( m );
		buffer[ 1 ] = 0;
		size = 1;
	}

	if ( 0 == CSetLoc::__crtGetStringTypeA( _loc_update.GetLocaleT(), CT_CType1, buffer, size, &chartype, _loc_update.GetLocaleT()->LocaleInfoPtr()->CodePage(), _loc_update.GetLocaleT()->LocaleInfoPtr()->Handles()[ CLocale::LCCTYPE ], true ) )
	{
		return 0;
	}

	return static_cast< int >( chartype & mask );
}

//--------------------------------------------------------------------------------
template<> int UTF16Char::chvalidator( nsWin32::CLocaleThreadData* plocinfo, int mask ) const
{
	CLocaleUpdate _loc_update( plocinfo );

	//assert( (unsigned)(c + 1) <= 256 );

	if( m >= -1 && m <= 255 )
	{
		return ( _loc_update.GetLocaleT()->LocaleInfoPtr()->CType()[ m ] & mask );
	}
	else
	{
		return ( _loc_update.GetLocaleT()->LocaleInfoPtr()->CType()[ -1 ] & mask );
	}
}


