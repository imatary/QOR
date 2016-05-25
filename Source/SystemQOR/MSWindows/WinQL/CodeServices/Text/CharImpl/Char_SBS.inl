//Char_SBS.inl

//implementation of Single Byte Signed Character class

//--------------------------------------------------------------------------------
template<> char SBSChar::To_char() const
{
	char cResult = m;
	return cResult;
}

//--------------------------------------------------------------------------------
template<> signed char SBSChar::To_schar() const
{
	return m;
}

//--------------------------------------------------------------------------------
template<> unsigned char SBSChar::To_uchar() const
{
	unsigned char ucResult = static_cast< unsigned char >( m );
	return ucResult;
}

//--------------------------------------------------------------------------------
template<> unsigned int SBSChar::To_uint() const
{
	SBSChar* p = reinterpret_cast< SBSChar* >( const_cast< signed char* >( &m ) );
	unsigned int uiResult = static_cast< unsigned int >( p->To_int() );
	return uiResult;
}

//--------------------------------------------------------------------------------
template<> int SBSChar::To_int() const
{
	int iResult = 0;
	size_t n = 1;
	const signed char* s = reinterpret_cast< const signed char* >( &m );

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
template<> wchar_t SBSChar::To_wchar() const
{
	//TODO: This looks self recursive. If so, fix it!
	SBSChar* p = reinterpret_cast< SBSChar* >( const_cast< signed char* >( &m ) );
	wchar_t Result = p->To_wchar();
	return Result;
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::isalnum() const
{
	if( CSystem::Instance().Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Alpha | Digit ) ? true : false;
	}
	else
	{
		return isalnum( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::isalpha() const
{
	if( CSystem::Instance().Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Alpha ) ? true : false;
	}
	else
	{
		return isalpha( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::ascii_isalpha() const
{
	bool bResult = ( ( 'A' <= ( m ) && ( m ) <= 'Z') || ( 'a' <= ( m ) && ( m ) <= 'z' ) );
	return bResult;
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::isblank() const
{
	if( CSystem::Instance().Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Blank ) ? true : false;
	}
	else
	{
		return isblank( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::iscntrl() const
{
	if( CSystem::Instance().Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Control ) ? true : false;
	}
	else
	{
		return iscntrl( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::isdigit() const
{
	if( CSystem::Instance().Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Digit ) ? true : false;
	}
	else
	{
		return isdigit( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::isgraph() const
{
	if( CSystem::Instance().Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Punct|Alpha|Digit ) ? true : false;
	}
	else
	{
		return isgraph( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::islower() const
{
	if( CSystem::Instance().Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Lower ) ? true : false;
	}
	else
	{
		return islower( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::isprint() const
{
	if( CSystem::Instance().Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Blank|Punct|Alpha|Digit ) ? true : false;
	}
	else
	{
		return isprint( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::ispunct() const
{
	if( CSystem::Instance().Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Punct ) ? true : false;
	}
	else
	{
		return ispunct( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::isspace() const
{
	if( CSystem::Instance().Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Space ) ? true : false;
	}
	else
	{
		return isspace( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::isupper() const
{
	if( CSystem::Instance().Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Upper ) ? true : false;
	}
	else
	{
		return isupper( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::isxdigit() const
{
	if( CSystem::Instance().Locale()().LocaleChanged() == false )
	{
		return __fast_ch_check( Hex ) ? true : false;
	}
	else
	{
		return isxdigit( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> int SBSChar::toascii() const
{
	return (int)( m & 0x7f );
}

//--------------------------------------------------------------------------------
template<> int SBSChar::tolower() const
{
	if( CSystem::Instance().Locale()().LocaleChanged() == false )
	{
		return ascii_tolower();
	}
	else
	{
		return tolower( 0 );
	}
}

//--------------------------------------------------------------------------------

template<> int SBSChar::ascii_tolower() const
{
	int iResult = ( ( ( ( m ) >= 'A' ) && ( ( m ) <= 'Z' ) ) ? ( ( m ) - 'A' + L'a' ) : ( m ) );
	return iResult;
}

//--------------------------------------------------------------------------------
template<> int SBSChar::toupper() const
{
	if( CSystem::Instance().Locale()().LocaleChanged() == false )
	{
		return ascii_toupper();
	}
	else
	{
		return toupper( 0 );
	}
}

//--------------------------------------------------------------------------------
template<> int SBSChar::ascii_toupper() const
{
	int iResult = ( ( ( ( m ) >= 'a' ) && ( ( m ) <= 'z' ) ) ? ( ( m ) - 'a' + 'A' ) : ( m ) );
	return iResult;
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::isalnum( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Alpha | Digit, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::isalpha( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Alpha, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::isblank( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Blank, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::iscntrl( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Control, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::isdigit( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Digit , _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::isgraph( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Punct|Alpha|Digit , _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::islower( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Lower, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::isprint( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Blank|Punct|Alpha|Digit, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::ispunct( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Punct, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::isspace( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Space, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::isupper( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Upper, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> bool SBSChar::isxdigit( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( Hex, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> int SBSChar::tolower( CLocaleThreadData* pLocaleThreadData ) const
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
template<> int SBSChar::toupper( CLocaleThreadData* pLocaleThreadData ) const
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
template<> bool SBSChar::isleadbyte( nsWin32::CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate Update( pLocaleThreadData );
	return ( Update.GetLocaleT()->LocaleInfoPtr()->CType()[ (unsigned char)m ] & LeadByte ) ? true : false;
}

//--------------------------------------------------------------------------------
template<> int SBSChar::todigit() const
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
template<> int SBSChar::ischartype( int iFlag, CLocaleThreadData* pLocaleThreadData ) const
{
	int iResult = ( ( pLocaleThreadData != 0 && ( pLocaleThreadData->LocaleInfoPtr()->MBCurMax() ) > 1 ) ? 
		isctype( iFlag, pLocaleThreadData ) : chvalidator( pLocaleThreadData, iFlag ) );
	return iResult;
}

//--------------------------------------------------------------------------------
template<> int SBSChar::isctype( int mask, CLocaleThreadData* plocinfo ) const
{
	CLocaleUpdate _loc_update(plocinfo);
	return _loc_update.GetLocaleT()->LocaleInfoPtr()->CType()[ (unsigned char)m ] & mask;
}

//--------------------------------------------------------------------------------
template<> int SBSChar::chvalidator( nsWin32::CLocaleThreadData* plocinfo, int mask ) const
{
	CLocaleUpdate _loc_update( plocinfo );
	return ( _loc_update.GetLocaleT()->LocaleInfoPtr()->CType()[ (unsigned char)m ] & mask );
}


