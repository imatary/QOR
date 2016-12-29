//Char_SBU.inl

//implementation of Single Byte Unsigned Character class

//--------------------------------------------------------------------------------
template<> char SBUChar::To_char() const
{
	char cResult = m;
	return cResult;
}

//--------------------------------------------------------------------------------
template<> signed char SBUChar::To_schar() const
{
	signed char scResult = static_cast< signed char >( m );
	return scResult;
}

//--------------------------------------------------------------------------------
template<> unsigned char SBUChar::To_uchar() const
{	
	return m;
}

//--------------------------------------------------------------------------------
template<> unsigned int SBUChar::To_uint() const
{
	return static_cast< unsigned int >( To_int() );
}

//--------------------------------------------------------------------------------
template<> int SBUChar::To_int() const
{
	int iResult = 0;
	size_t n = 1;
	const unsigned char* s = reinterpret_cast< const unsigned char* >( &m );

	if ( !(*s) )
	{
		// handle NULL char
		iResult = 0;
	}
	else
	{
		CLocaleUpdate _loc_update( 0 );
		assert( _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() == 1 || _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() == 2 );

		if ( _loc_update.GetLocaleT()->LocaleInfoPtr()->Handles()[ CLocale::LCCTYPE ] == CLocale::_CLOCALEHANDLE )
		{
			iResult = static_cast< int >( m );
		}
		else
		{
			if( isleadbyte( _loc_update.GetLocaleT() ) )
			{
				// multi-byte char
				if( ( _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() <= 1 ) || ( (int)n < _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() ) || ( _loc_update.GetLocaleT()->LocaleInfoPtr()->CodePage().MultiByteToWideChar( MB_Precomposed | MB_Err_Invalid_Chars, reinterpret_cast< const char* >( s ), _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax(), (wchar_t*)&iResult, 1 ) == 0 ) )
				{
					// validate high byte of mbcs char
					if( ( n < (size_t)_loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() ) || ( ! *( s + 1 ) ) )
					{
						errno = EILSEQ;
						iResult = -1;
					}
				}
				
			}
			else 
			{
				// single byte char
				if ( _loc_update.GetLocaleT()->LocaleInfoPtr()->CodePage().MultiByteToWideChar( MB_Precomposed | MB_Err_Invalid_Chars, reinterpret_cast< const char* >( s ), 1, (wchar_t*)&iResult, 1 ) == 0 )
				{
					errno = EILSEQ;
					iResult = -1;
				}        
			}
		}
	}
	return iResult;
}

//--------------------------------------------------------------------------------
template<> wchar_t SBUChar::To_wchar() const
{
#pragma TODO ("Seems to be recusive, fix this." )
	wchar_t Result = m;//To_wchar();
	return Result;
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::isalnum() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Alpha | Digit ) ? true : false;
	}
	else
	{
		return isalnum( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::isalpha() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Alpha ) ? true : false;
	}
	else
	{
		return isalpha( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::ascii_isalpha() const
{
	bool bResult = ( ( 'A' <= ( m ) && ( m ) <= 'Z') || ( 'a' <= ( m ) && ( m ) <= 'z' ) );
	return bResult;
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::isblank() const
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
template<> bool SBUChar::iscntrl() const
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
template<> bool SBUChar::isdigit() const
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
template<> bool SBUChar::isgraph() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Punct|Alpha|Digit ) ? true : false;
	}
	else
	{
		return isgraph( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::islower() const
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
template<> bool SBUChar::isprint() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Blank|Punct|Alpha|Digit ) ? true : false;
	}
	else
	{
		return isprint( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::ispunct() const
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
template<> bool SBUChar::isspace() const
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
template<> bool SBUChar::isupper() const
{
	if( TheSystem().As< nsWin32::CSystem >()->Locale(QOR_PP_SHARED_OBJECT_ACCESS).LocaleChanged() == false )
	{
		return __fast_ch_check( Upper ) ? true : false;
	}
	else
	{
		return isupper( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::isxdigit() const
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
template<> int SBUChar::toascii() const
{
	return (int)( m & 0x7f );
}

//--------------------------------------------------------------------------------
template<> int SBUChar::tolower() const
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
template<> int SBUChar::ascii_tolower() const
{
	int iResult = ( ( ( ( m ) >= 'A' ) && ( ( m ) <= 'Z' ) ) ? ( ( m ) - 'A' + 'a' ) : ( m ) );
	return iResult;
}

//--------------------------------------------------------------------------------
template<> int SBUChar::toupper() const
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
template<> int SBUChar::ascii_toupper() const
{
	int iResult = ( ( ( ( m ) >= 'a' ) && ( ( m ) <= 'z' ) ) ? ( ( m ) - 'a' + 'A' ) : ( m ) );
	return iResult;
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::isalnum( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Alpha | Digit, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::isalpha( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Alpha, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::isblank( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Blank, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::iscntrl( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Control, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::isdigit( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Digit, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::isgraph( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Punct|Alpha|Digit, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::islower( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Lower, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::isprint( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Blank | Punct | Alpha | Digit, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::ispunct( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Punct, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::isspace( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Space, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::isupper( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Upper, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::isxdigit( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Hex, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> int SBUChar::tolower( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	
	if( isupper( _loc_update.GetLocaleT() ) )
	{
		return _loc_update.GetLocaleT()->LocaleInfoPtr()->CLMap()[ m ];
	}
	else
	{
		return m;
	}	
}

//--------------------------------------------------------------------------------
template<> int SBUChar::toupper( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );

	if ( !islower( _loc_update.GetLocaleT() ) ) 
	{
		return m;
	} 
	else 
	{
		return _loc_update.GetLocaleT()->LocaleInfoPtr()->CUMap()[ m ];
	}
}

//--------------------------------------------------------------------------------
template<> bool SBUChar::isleadbyte( nsWin32::CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate Update( pLocaleThreadData );
	return ( Update.GetLocaleT()->LocaleInfoPtr()->CType()[ static_cast< unsigned char >( m ) ] & LeadByte ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> int SBUChar::todigit() const
{
	if( m < 0x0030 )
	{
		return -1;
	}
	if( m < 0x0030 + 10 )
	{
		return m - 0x0030;
	}
	return -1;
}

//--------------------------------------------------------------------------------
template<> int SBUChar::ischartype( int iFlag, CLocaleThreadData* pLocaleThreadData ) const
{
	int iResult = ( ( pLocaleThreadData != 0 && ( pLocaleThreadData->LocaleInfoPtr()->MBCurMax() ) > 1 ) ? 
		isctype( iFlag, pLocaleThreadData ) : chvalidator( pLocaleThreadData, iFlag ) );
	return iResult;
}

//--------------------------------------------------------------------------------
template<> int SBUChar::isctype( int mask, CLocaleThreadData* plocinfo ) const
{
	CLocaleUpdate _loc_update(plocinfo);
	return _loc_update.GetLocaleT()->LocaleInfoPtr()->CType()[ static_cast< unsigned char >( m ) ] & mask;
}

//--------------------------------------------------------------------------------
template<> int SBUChar::chvalidator( nsWin32::CLocaleThreadData* plocinfo, int mask ) const
{
	CLocaleUpdate _loc_update( plocinfo );
	return ( _loc_update.GetLocaleT()->LocaleInfoPtr()->CType()[ static_cast< unsigned char >( m ) ] & mask );
}


