//Char_SB.inl

//implementation of Single Byte Character class

//--------------------------------------------------------------------------------
char SBChar::To_char() const
{
	char cResult = m;
	return cResult;
}

//--------------------------------------------------------------------------------
signed char SBChar::To_schar() const
{
	signed char scResult = m;
	return scResult;
}

//--------------------------------------------------------------------------------
unsigned char SBChar::To_uchar() const
{
	unsigned char ucResult = m;
	return ucResult;
}

//--------------------------------------------------------------------------------
unsigned int SBChar::To_uint() const
{
	unsigned int uiResult = static_cast< unsigned int >( To_int() );
	return uiResult;
}

//--------------------------------------------------------------------------------
template<>
int SBChar::To_int() const
{
	int iResult = 0;
	size_t n = 1;
	const char* s = &m;

	if ( !*s )
	{
		// handle NULL char
		iResult = 0;
	}
	else
	{
		CLocaleUpdate _loc_update( 0 );
		//_ASSERTE ( _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() == 1 || _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() == 2 );

		if ( _loc_update.GetLocaleT()->LocaleInfoPtr()->Handles()[ CLocale::LC_CTYPE ] == CLocale::_CLOCALEHANDLE )
		{
			iResult = (int)m;
		}
		else
		{

			if( isleadbyte( _loc_update.GetLocaleT() ) )
			{
				// multi-byte char
				if( ( _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() <= 1 ) || ( (int)n < _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() ) || ( _loc_update.GetLocaleT()->LocaleInfoPtr()->CodePage().MultiByteToWideChar( MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, s, _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax(), (wchar_t*)&iResult, 1 ) == 0 ) )
				{
					// validate high byte of mbcs char
					if( ( n < (size_t)_loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() ) || ( ! *( s + 1 ) ) )
					{
						//TODO: errno = EILSEQ;
						iResult = -1;
					}
				}
				
			}
			else 
			{
				// single byte char
				if ( _loc_update.GetLocaleT()->LocaleInfoPtr()->CodePage().MultiByteToWideChar( MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, s, 1, (wchar_t*)&iResult, 1 ) == 0 )
				{
					//TODO: errno = EILSEQ;
					iResult = -1;
				}        
			}
		}
	}
	return iResult;
}

//--------------------------------------------------------------------------------
wchar_t SBChar::To_wchar() const
{
	wchar_t wc = 0;
	wchar_t* pwc = &wc;
	const char* s = &m;
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
		//_ASSERTE (_loc_update.GetLocaleT()->locinfo->mb_cur_max == 1 || _loc_update.GetLocaleT()->locinfo->mb_cur_max == 2);

		if( _loc_update.GetLocaleT()->LocaleInfoPtr()->Handles()[ CLocale::LC_CTYPE ] == CLocale::_CLOCALEHANDLE )
		{
			if( pwc )
			{
				*pwc = (wchar_t)(unsigned char)*s;
			}        
		}
		else if( isleadbyte( _loc_update.GetLocaleT() ) )
		{
			// multi-byte char

			if( ( _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() <= 1 ) || ( (int)n < _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() ) || ( _loc_update.GetLocaleT()->LocaleInfoPtr()->CodePage().MultiByteToWideChar( MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, s, _loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax(), pwc, (pwc) ? 1 : 0 ) == 0 ) )
			{
				/* validate high byte of mbcs char */
				if( ( n < (size_t)_loc_update.GetLocaleT()->LocaleInfoPtr()->MBCurMax() ) || ( !*( s + 1 ) ) )
				{
					//TODO:errno = EILSEQ;                
				}
			}
		}
		else 
		{
			// single byte char
			if ( _loc_update.GetLocaleT()->LocaleInfoPtr()->CodePage().MultiByteToWideChar( MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, s, 1, pwc, (pwc) ? 1 : 0 ) == 0 )
			{
				//errno = EILSEQ;            
			}        
		}
	}
	return wc;
}

//--------------------------------------------------------------------------------
bool SBChar::isalnum() const
{
	if( System().Locale().LocaleChanged() == false )
	{
		return __fast_ch_check( _ALPHA | _DIGIT ) ? true : false;
	}
	else
	{
		return isalnum( 0 );
	}
}

//--------------------------------------------------------------------------------
bool SBChar::isalpha() const
{
	if( System().Locale().LocaleChanged() == false )
	{
		return __fast_ch_check( _ALPHA ) ? true : false;
	}
	else
	{
		return isalpha( 0 );
	}
}

//--------------------------------------------------------------------------------
bool SBChar::ascii_isalpha() const
{
	bool bResult = ( ( 'A' <= ( m ) && ( m ) <= 'Z') || ( 'a' <= ( m ) && ( m ) <= 'z' ) );
	return bResult;
}

//--------------------------------------------------------------------------------
bool SBChar::isblank() const
{
	if( System().Locale().LocaleChanged() == false )
	{
		return __fast_ch_check( _BLANK ) ? true : false;
	}
	else
	{
		return isblank( 0 );
	}
}

//--------------------------------------------------------------------------------
bool SBChar::iscntrl() const
{
	if( System().Locale().LocaleChanged() == false )
	{
		return __fast_ch_check( _CONTROL ) ? true : false;
	}
	else
	{
		return iscntrl( 0 );
	}
}

//--------------------------------------------------------------------------------
bool SBChar::isdigit() const
{
	if( System().Locale().LocaleChanged() == false )
	{
		return __fast_ch_check( _DIGIT ) ? true : false;
	}
	else
	{
		return isdigit( 0 );
	}
}

//--------------------------------------------------------------------------------
bool SBChar::isgraph() const
{
	if( System().Locale().LocaleChanged() == false )
	{
		return __fast_ch_check( _PUNCT|_ALPHA|_DIGIT ) ? true : false;
	}
	else
	{
		return isgraph( 0 );
	}
}

//--------------------------------------------------------------------------------
bool SBChar::islower() const
{
	if( System().Locale().LocaleChanged() == false )
	{
		return __fast_ch_check( _LOWER ) ? true : false;
	}
	else
	{
		return islower( 0 );
	}
}

//--------------------------------------------------------------------------------
bool SBChar::isprint() const
{
	if( System().Locale().LocaleChanged() == false )
	{
		return __fast_ch_check( _BLANK|_PUNCT|_ALPHA|_DIGIT ) ? true : false;
	}
	else
	{
		return isprint( 0 );
	}
}

//--------------------------------------------------------------------------------
bool SBChar::ispunct() const
{
	if( System().Locale().LocaleChanged() == false )
	{
		return __fast_ch_check( _PUNCT ) ? true : false;
	}
	else
	{
		return ispunct( 0 );
	}
}

//--------------------------------------------------------------------------------
bool SBChar::isspace() const
{
	if( System().Locale().LocaleChanged() == false )
	{
		return __fast_ch_check( _SPACE ) ? true : false;
	}
	else
	{
		return isspace( 0 );
	}
}

//--------------------------------------------------------------------------------
bool SBChar::isupper() const
{
	if( System().Locale().LocaleChanged() == false )
	{
		return __fast_ch_check( _UPPER ) ? true : false;
	}
	else
	{
		return isupper( 0 );
	}
}

//--------------------------------------------------------------------------------
bool SBChar::isxdigit() const
{
	if( System().Locale().LocaleChanged() == false )
	{
		return __fast_ch_check( _HEX ) ? true : false;
	}
	else
	{
		return isxdigit( 0 );
	}
}

//--------------------------------------------------------------------------------
int SBChar::toascii() const
{
	return (int)( m & 0x7f );
}

//--------------------------------------------------------------------------------
int SBChar::tolower() const
{
	if( System().Locale().LocaleChanged() == false )
	{
		return ascii_tolower();
	}
	else
	{
		return tolower( 0 );
	}
}

//--------------------------------------------------------------------------------
template<>
int SBChar::ascii_tolower() const
{
	int iResult = ( ( ( ( m ) >= 'A' ) && ( ( m ) <= 'Z' ) ) ? ( ( m ) - 'A' + L'a' ) : ( m ) );
	return iResult;
}

//--------------------------------------------------------------------------------
int SBChar::toupper() const
{
	if( System().Locale().LocaleChanged() == false )
	{
		return ascii_toupper();
	}
	else
	{
		return toupper( 0 );
	}
}

//--------------------------------------------------------------------------------
template<>
int SBChar::ascii_toupper() const
{
	int iResult = ( ( ( ( m ) >= 'a' ) && ( ( m ) <= 'z' ) ) ? ( ( m ) - 'a' + 'A' ) : ( m ) );
	return iResult;
}

//--------------------------------------------------------------------------------
template<>
bool SBChar::isalnum( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( _ALPHA | _DIGIT, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<>
bool SBChar::isalpha( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( _ALPHA, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<>
bool SBChar::isblank( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( _BLANK, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<>
bool SBChar::iscntrl( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( _CONTROL, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<>
bool SBChar::isdigit( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( _DIGIT, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<>
bool SBChar::isgraph( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( _PUNCT|_ALPHA|_DIGIT, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<>
bool SBChar::islower( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( _LOWER, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<>
bool SBChar::isprint( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( _BLANK|_PUNCT|_ALPHA|_DIGIT, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<>
bool SBChar::ispunct( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( _PUNCT, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<>
bool SBChar::isspace( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( _SPACE, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<>
bool SBChar::isupper( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( _UPPER, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<>
bool SBChar::isxdigit( CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate _loc_update( pLocaleThreadData );
	return ischartype( _HEX, _loc_update.GetLocaleT() ) ? true : false;
}

//--------------------------------------------------------------------------------
template<>
int SBChar::tolower( CLocaleThreadData* pLocaleThreadData ) const
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
template<>
int SBChar::toupper( CLocaleThreadData* pLocaleThreadData ) const
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
template<>
bool SBChar::isleadbyte( nsWi32::CLocaleThreadData* pLocaleThreadData ) const
{
	CLocaleUpdate Update( pLocaleThreadData );
	return ( Update.GetLocaleT()->LocaleInfoPtr()->CType()[ (unsigned char)m ] & _LEADBYTE ) ? true : false;
}

//--------------------------------------------------------------------------------
int SBChar::todigit() const
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
template<>
int SBChar::ischartype( int iFlag, CLocaleThreadData* pLocaleThreadData ) const
{
	int iResult = ( ( pLocaleThreadData != 0 && ( pLocaleThreadData->LocaleInfoPtr()->MBCurMax() ) > 1 ) ? 
		isctype( iFlag, pLocaleThreadData ) : chvalidchk( iFlag, pLocaleThreadData ) );
	return iResult;
}

//--------------------------------------------------------------------------------
template<>
int SBChar::isctype( int mask, CLocaleThreadData* plocinfo ) const
{
	CLocaleUpdate _loc_update(plocinfo);
	return _loc_update.GetLocaleT()->LocaleInfoPtr()->CType()[ m ] & mask;
}

//--------------------------------------------------------------------------------
template<>
int SBChar::chvalidator( nsWin32::CLocaleThreadData* plocinfo, int mask ) const
{
	CLocaleUpdate _loc_update( plocinfo );
	return ( _loc_update.GetLocaleT()->LocaleInfoPtr()->CType()[ m ] & mask );
}

