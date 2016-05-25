//FileSystem.cpp

#include "SystemQOR.h"
#include <errno.h>
#include <limits.h>
#include "WinQL/WinQLSystem.h"
#include "WinQL/CodeServices/Handle.h"
#include "WinQL/CodeServices/Process.h"
#include "PosumQOR/MSWindows/FileSystem.h"
#include "PosumQOR/MSWindows/Posum_Stream.h"
#include "WinQAPI/Kernel32.h"

template < typename _CountofType, size_t _SizeOfArray >
		char ( *__countof_helper( UNALIGNED _CountofType ( &_Array )[ _SizeOfArray ] ) )[ _SizeOfArray ];
#		define _countof( _Array ) sizeof( *__countof_helper( _Array ) )

//--------------------------------------------------------------------------------
namespace nsWin32
{
	CFileSystem TheWindowsLowLevelFileSystem;

	//--------------------------------------------------------------------------------
	CFileSystem& FileSystem( void )
	{
		return TheWindowsLowLevelFileSystem;
	}

	//--------------------------------------------------------------------------------
	CFileSystem::CFileSystem()
	{
		m_pDescriptorPool = nsCodeQOR::CTSingleton< CDescriptorPool >::Instance();
		m_fmode = 0x08000;//OBinary;
		m_commode = CStreamData::_IOCOMMIT;
		m_umaskval = 0;

		//nsWin32::CConsole::__initconin();
		//nsWin32::CConsole::__initconout();

		//Pre-assign stdin, stdout, stderr
		//new nsPosum::CPosumStreamDescriptor( CConsole::ConsoleInputFile() );
		//new nsPosum::CPosumStreamDescriptor( CConsole::ConsoleOutputFile() );
		//new nsPosum::CPosumStreamDescriptor( CConsole::ConsoleOutputFile() );

	}

	//--------------------------------------------------------------------------------
	CFileSystem::~CFileSystem()
	{
		nsCodeQOR::CTSingleton< CDescriptorPool >::Release( m_pDescriptorPool );
	}

//	//--------------------------------------------------------------------------------
	CConsoleHelper	CFileSystem::m_sConsoleHelper;
	CErrorHelper	CFileSystem::m_sErrorHelper;
	//nsCodeServices::CThreadHelper	CFileSystem::m_sThreadHelper;
	CStringHelper	CFileSystem::m_sStringHelper;
	//CTimeHelper						CFileSystem::m_Win32TimeHelper;
	CInterlockedHelper		CFileSystem::m_sInterlockedHelper;
//	//nsComms::CPipeHelper			CFileSystem::m_sPipeHelper;
//
//	//--------------------------------------------------------------------------------
	char CFileSystem::sachLookupTrailBytes[ 256 ] =
	{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
			3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0
	};
//
	//--------------------------------------------------------------------------------
	int CFileSystem::Commit( CFileData& FileData )
	{
		int iResult = 0;

		FileData.Lock();

		if ( FileData.GetFlagsOpen() )
		{
			if( ! FileData.GetOSFile()->FlushBuffers() )
			{
				iResult = m_sErrorHelper.GetLastError();
			}
		}

		// map the OS return code to C errno value and return code
		if( iResult != 0 )
		{
			nsWin32::GetCurrentWin32Thread()->Data().DOSErrorNumber() = iResult;
			*(nsBaseCRT::CCRTErrorDomain::ErrNo()) = EBADF;
			iResult = -1;
		}

		FileData.Unlock();

		return iResult;
	}

	//--------------------------------------------------------------------------------
	Cmp__int64 CFileSystem::Seek( CFileData& FileData, Cmp__int64 i64Pos, int iMethod )
	{
		CFileData::FilePos NewPos;				// new file position
		unsigned long ulErr;		// error code from API call
		NewPos.bigint = i64Pos;

		FileData.Lock();

		if( FileData.GetOSFile()->Handle() == Invalid_Handle_Value )
		{
			*(nsBaseCRT::CCRTErrorDomain::ErrNo()) = EBADF;
			FileData.Unlock();
			return( __QCMP_i64_SUFFIX(-1) );
		}

		if( ( ( NewPos.twoints.lowerhalf = FileData.GetOSFile()->SetPointer( NewPos.twoints.lowerhalf, &( NewPos.twoints.upperhalf ), iMethod ) ) == -1L ) && ( ( ulErr = m_sErrorHelper.GetLastError() ) != 0 ) )
		{
			//TODO: CDOSError::MapError( ulErr );
			FileData.Unlock();
			return( __QCMP_i64_SUFFIX(-1) );
		}

		FileData.SetFlagsEOF( false ); // clear the ctrl-z flag on the file
		FileData.Unlock();
		return( NewPos.bigint );
	}

	//--------------------------------------------------------------------------------
	int CFileSystem::InitRead( CFileData& FileData, void*& pvInputBuffer, unsigned& uCount, void*& pRawBuffer )
	{
		int iResult = 0;
		switch( FileData.GetTextMode() )
		{
		case CFileData::__IOINFO_TM_UTF8 :
			/* For a UTF-8 file, we need 2 buffers, because after reading we need to convert it into
			UNICODE - MultiByteToWideChar doesn't do in-place conversions. */

			/* MultiByte To WideChar conversion may double the size of the buffer required & hence we
			divide uCount by 2 */

			/* Since we are reading UTF8 stream, uCount bytes read may vary from uCount wchar_t
			characters to uCount/4 wchar_t characters. For this reason if we need to read uCount
			characters, we will allocate MBCS buffer of uCount. In case uCount is 0, we will have 4
			as minimum value. This will make sure we don't overflow for reading from pipe case.

			In this case the numbers of wchar_t characters that we can read is uCount/2. This means
			that the buffer size that we will require is uCount/2.
				*/

			// For UTF8 we want the count to be an even number
			//_VALIDATE_CLEAR_OSSERR_RETURN(((uCount & 1) == 0), EINVAL, -1);

			uCount = ( uCount / 2) < 4 ? 4 : ( uCount / 2 );

			pRawBuffer = malloc( uCount );

			if( !pRawBuffer )
			{
				*(nsBaseCRT::CCRTErrorDomain::ErrNo()) = ENOMEM;
				nsWin32::GetCurrentWin32Thread()->Data().DOSErrorNumber() = ENOMEM;//E_nomem;
				iResult = -1;
				break;
			}

			FileData.SetStartPos( Seek( FileData, 0, nsWin32::File_Current ) );
			break;

		case CFileData::__IOINFO_TM_UTF16LE :

			// For UTF16 the count always needs to be an even number
			//_VALIDATE_CLEAR_OSSERR_RETURN(((uCount & 1) == 0), EINVAL, -1);

			uCount &= (~1);

			// Fall Through to default

		default :

			// For non-UTF8 files, we need only 1 buffer - make pRawBuffer point to the users input buffer
			pRawBuffer = pvInputBuffer;
		}

		return iResult;
	}

	//--------------------------------------------------------------------------------
	void CFileSystem::InitReadPipe( CFileData& FileData, char*& pchBuffer, int& iBytesRead, unsigned& uCount )
	{
		// a pipe/device and pipe lookahead non-empty: read the lookahead * char
		*pchBuffer++ = FileData.GetPipeBuffer();
		++iBytesRead;
		--uCount;
		FileData.GetPipeBuffer() = CFileData::LF;// mark as empty

		// For UTF16, there maybe one more look ahead char. For UTF8, there maybe 2 more look ahead chars
		if( ( FileData.GetTextMode() != CFileData::__IOINFO_TM_ANSI ) && ( FileData.GetUnicodePipeBuffer()[ 0 ] != CFileData::LF ) && uCount != 0 )
		{
			*pchBuffer++ = FileData.GetUnicodePipeBuffer()[ 0 ];
			++iBytesRead;
			--uCount;
			FileData.GetUnicodePipeBuffer()[ 0 ] = CFileData::LF;   // mark as empty

			if( ( FileData.GetTextMode() == CFileData::__IOINFO_TM_UTF8 ) && ( FileData.GetUnicodePipeBuffer()[ 1 ] != CFileData::LF ) && uCount != 0 )
			{
				*pchBuffer++ = FileData.GetUnicodePipeBuffer()[ 1 ];
				++iBytesRead;
				--uCount;
				FileData.GetUnicodePipeBuffer()[ 1 ] = CFileData::LF;   // mark as empty
			}
		}
	}

	//--------------------------------------------------------------------------------
	int CFileSystem::Read( CFileData& FileData, void* pvInputBuffer, unsigned uCount )
	{
		FileData.Lock();
		if( uCount == 0 || ( FileData.GetFlagsEOF() ) )
		{
			FileData.Unlock();
			return 0;// nothing to read or at EOF, so return 0 read
		}

		int iBytesRead		= 0;		// number of bytes read
		char* pchBuffer		= 0;		// buffer to read to
		int iOSBytesRead	= 0;		// bytes read on OS call
		unsigned long ulDOSResult	= 0;		// o.s. return value
		//char chTextMode		= FileData.GetTextMode();	// textmode - ANSI/UTF-8/UTF-16
		void* pRawBuffer	= 0;		// buffer to read to
		int iResult			= -2;		// return value
		unsigned uInputSize = uCount;

		if( !FileData.GetFlagsOpen() )
		{
			*(nsBaseCRT::CCRTErrorDomain::ErrNo()) = EBADF;
			FileData.Unlock();
			return -1;
		}

		if( uCount > INT_MAX )
		{
			*(nsBaseCRT::CCRTErrorDomain::ErrNo()) = EINVAL;
			FileData.Unlock();
			return -1;
		}

		if( pvInputBuffer == 0 )
		{
			*(nsBaseCRT::CCRTErrorDomain::ErrNo()) = EINVAL;
			FileData.Unlock();
			return -1;
		}

		if( InitRead( FileData, pvInputBuffer, uCount, pRawBuffer ) == 0 )
		{
			pchBuffer = (char*)pRawBuffer;

			if( ( FileData.GetFlagsFPIPE() | FileData.GetFlagsFDEV() ) && ( FileData.GetPipeBuffer() != CFileData::LF ) && uCount != 0 )
			{
				InitReadPipe( FileData, pchBuffer, iBytesRead, uCount );
			}

			// read the data
			if( !FileData.GetOSFile()->Read( pchBuffer, uCount, (unsigned long*)&iOSBytesRead, 0 ) || iOSBytesRead < 0 || (size_t)iOSBytesRead > uCount )
			{
				OnReadError( iResult, ulDOSResult );
			}
			else
			{
				iBytesRead += iOSBytesRead;          // update bytes read

				if( FileData.GetFlagsFTEXT() )
				{
					PostReadText( FileData, iOSBytesRead, pRawBuffer, ulDOSResult, iBytesRead, iResult, pvInputBuffer, uInputSize );
				}
			}
		}

		if( pRawBuffer != pvInputBuffer )
		{
			free( pRawBuffer );
		}

		return ( iResult == -2 ) ? iBytesRead : iResult ;
	}

	//--------------------------------------------------------------------------------
	void CFileSystem::PostReadText( CFileData& FileData, int& iOSBytesRead, void*& pRawBuffer, unsigned long& ulDOSResult, int& iBytesRead, int& iResult, void*& pvInputBuffer, unsigned& uInputSize )
	{
		Cmp__int64 i64FilePos	= 0;		// file position after seek
		char chPeek			= 0;		// peek-ahead character
		char* p				= 0;
		char* q				= 0;		// pointers into buffer

		// now must translate CR-LFs to LFs in the buffer

		// For ANSI & UTF8, we read byte by byte.
		// For UTF16, we need to read 2 bytes (wchar_t's) at a time
		if( FileData.GetTextMode() != CFileData::__IOINFO_TM_UTF16LE )
		{
			// set CRLF flag to indicate LF at beginning of buffer
			if( ( iOSBytesRead != 0 ) && ( *(char *)pRawBuffer == CFileData::LF ) )
			{
				FileData.SetFlagsCRLF( true );
			}
			else
			{
				FileData.SetFlagsCRLF( false );
			}

			// convert chars in the buffer: p is src, q is dest
			p = q = (char*)pRawBuffer;
			while( p < (char *)pRawBuffer + iBytesRead )
			{
				if( *p == CFileData::CTRLZ )
				{
					// if fh is not a device, set ctrl-z flag
					if( !( FileData.GetFlagsFDEV() ) )
					{
						FileData.SetFlagsEOF( true );
					}
					else
					{
						*q++ = *p++;
					}
					break;              // stop translating
				}
				else if( *p != CFileData::CR )
				{
					*q++ = *p++;
				}
				else
				{
					// *p is CR, so must check next char for LF
					if( p < (char *)pRawBuffer + iBytesRead - 1 )
					{
						if( *( p + 1 ) == CFileData::LF )
						{
							p += 2;
							*q++ = CFileData::LF;  // convert CR-LF to LF
						}
						else
						{
							*q++ = *p++; // store char normally
						}
					}
					else
					{
						// This is the hard part.  We found a CR at end of buffer.  We must peek ahead to see if next char is an LF.
						++p;

						ulDOSResult = 0;
						if( !FileData.GetOSFile()->Read( &chPeek, 1, (unsigned long*)&iOSBytesRead, 0 ) )
						{
							ulDOSResult = m_sErrorHelper.GetLastError();
						}

						if( ulDOSResult != 0 || iOSBytesRead == 0 )
						{
							// couldn't read ahead, store CR
							*q++ = CFileData::CR;
						}
						else
						{
							/* chPeek now has the extra character -- we now
								* have several possibilities:
								*
								* 1. disk file and char is not LF; just seek
								*    back and copy CR
								* 2. disk file and char is LF; seek back and
								*    discard CR
								* 3. disk file, char is LF but this is a
								*    one-byte read: store LF, don't seek back
								* 4. pipe/device and char is LF; store LF.
								* 5. pipe/device and char isn't LF, store CR
								*    and put char in pipe lookahead buffer.
								*/
							if( FileData.GetFlagsFDEV() | FileData.GetFlagsFPIPE() )
							{
								// non-seekable device
								if( chPeek == CFileData::LF )
								{
									*q++ = CFileData::LF;
								}
								else
								{
									*q++ = CFileData::CR;
									FileData.GetPipeBuffer() = chPeek;
								}
							}
							else
							{
								// disk file
								if( q == pRawBuffer && chPeek == CFileData::LF )
								{
									// nothing read yet; must make some progress
									*q++ = CFileData::LF;
								}
								else
								{
									// seek back
									i64FilePos = Seek( FileData, __QCMP_i64_SUFFIX(-1), nsWin32::File_Current );
									if( chPeek != CFileData::LF )
									{
										*q++ = CFileData::CR;
									}
								}
							}
						}
					}
				}
			}

			// we now change bytes_read to reflect the true number of chars in the buffer
			iBytesRead = (int)( q - (char *)pRawBuffer );

			FileData.SetTextMode( CFileData::__IOINFO_TM_UTF8 );

			if( iBytesRead != 0 )
			{
				// UTF8 reads need to be converted into UTF16

				--q; // q has gone beyond the last char

				/* If the last byte is a standalone UTF-8 char. We then take the whole buffer.
				Otherwise we skip back till we come to a lead byte. If the leadbyte forms a
				complete UTF-8 character will the remaining part of the buffer, then again we
				take the whole buffer. If not, we skip to one byte which should be the final
				trail byte of the previous UTF-8 char or a standalone UTF-8 character
					*/

				if( UTF8IsIndependent( *q ) )
				{
					++q;// Final byte is standalone, we reset q, because we will now consider the full buffer which we have read
				}
				else
				{
					int ctr = 1;
					int cnt_trailbytes;

					while( !UTF8IsLeadByte( *q ) && ctr <= 4 && q >= (char *)pRawBuffer )
					{
						--q;
						++ctr;
					}

					cnt_trailbytes = UTF8TrailBytes( *q );

					if( cnt_trailbytes == 0 )
					{
						/*Should have exited the while by finding a lead
							* byte else, the file has incorrect UTF-8 chars
							*/
						*(nsBaseCRT::CCRTErrorDomain::ErrNo()) = EILSEQ;
						iResult = -1;
						return;
					}

					if( cnt_trailbytes + 1 == ctr )
					{
						q += ctr;//The leadbyte + the remaining bytes form a full set
					}
					else
					{
						// Seek back
						if( FileData.GetFlagsFDEV() | FileData.GetFlagsFPIPE() )
						{
							/*non-seekable device. Put the extra chars in _pipech & _pipech2.
							We would have a maximum of 3 extra chars
								*/
							FileData.GetPipeBuffer() = *q;
							++q;

							if( ctr >= 2 )
							{
								FileData.GetUnicodePipeBuffer()[ 0 ] = *q;
								++q;
							}

							if( ctr == 3 )
							{
								FileData.GetUnicodePipeBuffer()[ 1 ] = *q;
								++q;
							}

							q -= ctr;// We need to point q back to beyond whatever we actually took in.
						}
						else
						{
							// We have read extra chars, so we seek back
							i64FilePos = Seek( FileData, -ctr, nsWin32::File_Current );
						}
					}
				}

				iBytesRead = (int)( q - (char *)pRawBuffer );
				iBytesRead = 0;//TODO: m_sStringHelper.MultiByteToWideChar( CCodePage::UTF8, 0, (const char*)pRawBuffer, iBytesRead, (wchar_t*)pvInputBuffer, uInputSize / 2 );

				if( !iBytesRead )
				{
					//TODO: CDOSError::MapError( m_sErrorHelper.GetLastError() );
					iResult = -1;
					return;
				}

				FileData.Buffering().SetUTF8Translations( ( iBytesRead != (int)(q - (char *)pRawBuffer) ) ? true : false );

				// MultiByteToWideChar returns no of wchar_t's. Double it
				iBytesRead = iBytesRead * 2;
			}
		}
		else
		{
			PostReadTextUTF16LE( FileData, iOSBytesRead, pRawBuffer, ulDOSResult, iBytesRead, iResult, pvInputBuffer, uInputSize );
		}
	}

	//--------------------------------------------------------------------------------
	void CFileSystem::PostReadTextUTF16LE( CFileData& FileData, int& iOSBytesRead, void*& pRawBuffer, unsigned long& ulDOSResult, int& iBytesRead, int& iResult, void*& pvInputBuffer, unsigned& uInputSize )
	{
		Cmp__int64 i64FilePos	= 0;		// file position after seek
		wchar_t wchPeek		= 0;		// peek-ahead wchar_t
		wchar_t* pu			= 0;
		wchar_t* qu			= 0;		// wchar_t pointers into buffer for UTF16

		// set CRLF flag to indicate LF at beginning of buffer
		if( ( iOSBytesRead != 0) && ( *(wchar_t *)pRawBuffer == CFileData::LF ) )
		{
			FileData.SetFlagsCRLF( true );
		}
		else
		{
			FileData.SetFlagsCRLF( false );
		}

		// convert chars in the buffer: pu is src, qu is dest
		pu = qu = (wchar_t *)pRawBuffer;
		while( (char *)pu < (char *)pRawBuffer + iBytesRead )
		{
			if ( *pu == CFileData::CTRLZ )
			{
				// if fh is not a device, set ctrl-z flag
				if( !( FileData.GetFlagsFDEV() ) )
				{
					FileData.SetFlagsEOF( true );
				}
				else
				{
					*qu++ = *pu++;
				}
				break;              // stop translating
			}
			else if( *pu != CFileData::CR )
			{
				*qu++ = *pu++;
			}
			else
			{
				// *pu is CR, so must check next wchar_t for LF
				if( (char *)pu < (char *)pRawBuffer + iBytesRead - 2 )
				{
					if( *(pu+1) == CFileData::LF )
					{
						pu += 2;
						*qu++ = CFileData::LF;  // convert CR-LF to LF
					}
					else
					{
						*qu++ = *pu++;    // store char normally
					}
				}
				else
				{
					// This is the hard part.  We found a CR at end of buffer.  We must peek ahead to see if next wchar_t is an LF.
					++pu;

					ulDOSResult = 0;
					if( !FileData.GetOSFile()->Read( &wchPeek, 2, (unsigned long*)&iOSBytesRead, 0 ) )
					{
						ulDOSResult = m_sErrorHelper.GetLastError();
					}

					if( ulDOSResult != 0 || iOSBytesRead == 0 )
					{
						// couldn't read ahead, store CR
						*qu++ = CFileData::CR;
					}
					else
					{	/* chPeek now has the extra character -- we
							* now have several possibilities:
							* 1. wchar_t is not LF; just seek back and
							* copy CR
							* 2. wchar_t is LF; seek back and discard CR
							* 3. disk file, wchar_t is LF but this is a
							* one-byte read: store LF, don't seek back.
							*/
						if( FileData.GetFlagsFDEV() | FileData.GetFlagsFPIPE() )
						{
							// non-seekable device
							if( wchPeek == CFileData::LF )
							{
								*qu++ = CFileData::LF;
							}
							else
							{
								char* pwpeekchr = (char *)&wchPeek;
								*qu++ = CFileData::CR;
								FileData.GetPipeBuffer() = *pwpeekchr;
								++pwpeekchr;
								FileData.GetUnicodePipeBuffer()[ 0 ] = *pwpeekchr;
								FileData.GetUnicodePipeBuffer()[ 1 ] = CFileData::LF; // Mark as empty
							}
						}
						else
						{
							if( (char *)qu == pRawBuffer && wchPeek == CFileData::LF )
							{
								*qu++ = CFileData::LF;// nothing read yet; must make some progress
							}
							else
							{	// seek back
								i64FilePos = Seek( FileData, -2, nsWin32::File_Current );
								if( wchPeek != CFileData::LF )
								{
									*qu++ = CFileData::CR;
								}
							}
						}
					}
				}
			}
		}

		// we now change iBytesRead to reflect the true number of chars in the buffer
		iBytesRead = (int)( (char *)qu - (char *)pRawBuffer );
	}

	//--------------------------------------------------------------------------------
	void CFileSystem::OnReadError( int& iResult, unsigned long& ulDOSResult )
	{
		/* ReadFile has reported an error. recognize two special cases.
			*
			*      1. map ERROR_ACCESS_DENIED to EBADF
			*
			*      2. just return 0 if ERROR_BROKEN_PIPE has occurred. it
			*         means the handle is a read-handle on a pipe for which
			*         all write-handles have been closed and all data has been
			*         read. */

		if( ( ulDOSResult = m_sErrorHelper.GetLastError() ) == nsWin32::ErrorAccessDenied )
		{
			// wrong read/write mode should return EBADF, not EACCES
			*(nsBaseCRT::CCRTErrorDomain::ErrNo()) = EBADF;
			nsWin32::GetCurrentWin32Thread()->Data().DOSErrorNumber() = ulDOSResult;
			iResult = -1;
		}
		else if ( ulDOSResult == nsWin32::ErrorBrokenPipe )
		{
			iResult = 0;
		}
		else
		{
			//TODO: CDOSError::MapError( ulDOSResult );
			iResult = -1;
		}
	}

	//--------------------------------------------------------------------------------
	int CFileSystem::Write( CFileData& FileData, const void* buf, unsigned cnt )
	{
		int r = 0;                          // return value

		if( !FileData.GetFlagsOpen() )
		{
			*(nsBaseCRT::CCRTErrorDomain::ErrNo()) = EBADF;
			return -1;
		}

		if( cnt > 0 )
		{
			//r = _write_nolock( fh, buf, cnt );    // write bytes

			int lfcount;            // count of line feeds
			int charcount;          // count of chars written so far
			int written;            // count of chars written on this write
			unsigned long dosretval = 0;	// o.s. return value
			char tmode;				// textmode - ANSI or UTF-16
			bool toConsole = 0;     // true when writing to console
			bool isCLocale = 0;     // true when locale handle is C locale

			lfcount = charcount = 0;        /* nothing written yet */

			//_VALIDATE_CLEAR_OSSERR_RETURN( (buf != NULL), EINVAL, -1 );

			tmode = FileData.GetTextMode();

			if( tmode == CFileData::__IOINFO_TM_UTF16LE || tmode == CFileData::__IOINFO_TM_UTF8 )
			{
				// For a UTF-16 file, the count must always be an even number
				if( !( ( cnt & 1 ) == 0 ) )
				{
					*(nsBaseCRT::CCRTErrorDomain::ErrNo()) = EINVAL;
					return -1;
				}
			}

			if( FileData.GetFlagsFAPPEND() )
			{
				// appending - seek to end of file; ignore error, because maybe file doesn't allow seeking
				Seek( FileData, 0, nsWin32::File_End );
			}

			// check for text mode with LF's in the buffer

			/*Note that in case the handle belongs to Console, write file will
			* generate garbage output. For user to print these characters
			* correctly, we will need to print ANSI.
			*
			* Also note that in case of printing to Console, we still have to
			* convert the characters to console codepage.
			*/

			if( _isatty( FileData ) && ( FileData.GetFlagsFTEXT() ) )
			{
				unsigned long dwMode;
				nsWin32::CScreenBuffer Console( 0, FileData.GetOSFile()->Handle() );
				isCLocale = true;//( nsWin32::nsCodeServices::GetCurrentWin32Thread()->Data().m_LocaleData.LocaleInfoPtr()->Handles()[ CLocale::LCCTYPE ] == CLocale::_CLOCALEHANDLE );
				toConsole = m_sConsoleHelper.GetDisplayMode( &dwMode );
			}

			// don't need double conversion if it's ANSI mode C locale
			if( toConsole && !( isCLocale && ( tmode == CFileData::__IOINFO_TM_ANSI ) ) )
			{
				WriteUConsole( FileData, buf, tmode, cnt, lfcount, charcount, dosretval );
			}
			else if( FileData.GetFlagsFTEXT() )
			{
				WriteText( FileData, buf, dosretval, cnt, tmode, lfcount, written, charcount );
			}
			else
			{
				// binary mode, no translation
				if( FileData.GetOSFile()->Write( (void*)buf, cnt, (unsigned long*)&written, 0 ) )
				{
					dosretval = 0;
					charcount = written;
				}
				else
				{
					dosretval = m_sErrorHelper.GetLastError();
				}
			}

			if( charcount == 0 )
			{
				/* If nothing was written, first check if an o.s. error, otherwise we return -1 and
				set errno to ENOSPC, unless a device and first char was CTRL-Z */
				if( dosretval != 0 )
				{
					// o.s. error happened, map error
					if( dosretval == nsWin32::ErrorAccessDenied )
					{
						// wrong read/write mode should return EBADF, not EACCES
						*(nsBaseCRT::CCRTErrorDomain::ErrNo()) = EBADF;
						nsWin32::GetCurrentWin32Thread()->Data().DOSErrorNumber() = dosretval;
					}
					else
					{
						//TODO: CDOSError::MapError( dosretval );
						r = -1;
					}
				}
				else if( ( FileData.GetFlagsFDEV() ) && *(char *)buf == CFileData::CTRLZ )
				{
					r = 0;
				}
				else
				{
					*(nsBaseCRT::CCRTErrorDomain::ErrNo()) = ENOSPC;
					nsWin32::GetCurrentWin32Thread()->Data().DOSErrorNumber() = 0;
					r = -1;
				}
			}
			else
			{
				// return adjusted bytes written
				r = ( charcount - lfcount );
			}
		}
		else
		{
			*(nsBaseCRT::CCRTErrorDomain::ErrNo()) = EBADF;
			nsWin32::GetCurrentWin32Thread()->Data().DOSErrorNumber() = 0;
			r = -1;
		}

		return r;
	}

	//--------------------------------------------------------------------------------
	void CFileSystem::WriteUConsole( CFileData& FileData, const void*& pvBuffer, char& chTMode, unsigned int& uiCount, int& iLFCount, int& iCharCount, unsigned long& ulDOSResult )
	{
		unsigned int consoleCP = m_sConsoleHelper.GetCP();
		char mboutbuf[ MB_LEN_MAX ];
		wchar_t tmpchar;
		int size = 0;
		int written = 0;
		char* pch;

		for( pch = (char *)pvBuffer; (unsigned)( pch - (char *)pvBuffer ) < uiCount; )
		{
			bool bCR;

			if( chTMode == CFileData::__IOINFO_TM_ANSI )
			{
				bCR = *pch == CFileData::LF;
				//Here we need to do double convert. i.e. convert from multibyte to unicode
				// and then from unicode to multibyte in Console codepage.

				//TODO:
				/*
				if( !( SBChar(*pch).isleadbyte( 0 ) ) )
				{
					if( mbtowc( &tmpchar, pch, 1 ) == -1 )
					{
						break;
					}
				}
				else if( ( uiCount - ( pch - (char*)pvBuffer ) ) > 1 )
				{
					if( mbtowc( &tmpchar, pch, 2 ) == -1 )
					{
						break;
					}
					//Increment pch to accomodate DBCS character.
					++pch;
				}
				else
				{
					break;
				}
				*/
				++pch;
			}
			else if( chTMode == CFileData::__IOINFO_TM_UTF8 || chTMode == CFileData::__IOINFO_TM_UTF16LE )
			{
				/*Note that bCR set above is not valid in case of UNICODE
				* stream. We need to set it using unicode character.
				*/
				tmpchar = *(wchar_t*)pch;
				bCR = tmpchar == CFileData::LF;
				pch += 2;
			}

			if( chTMode == CFileData::__IOINFO_TM_ANSI )
			{
				if( ( size = m_sStringHelper.WideCharToMultiByte( consoleCP, 0, &tmpchar, 1, mboutbuf, sizeof( mboutbuf ), 0, 0 ) ) == 0 )
				{
					break;
				}
				else
				{
					if( FileData.GetOSFile()->Write( mboutbuf, size, (unsigned long*)&written, 0 ) )
					{
						iCharCount += written;
						if( written < size )
						{
							break;
						}
					}
					else
					{
						ulDOSResult = m_sErrorHelper.GetLastError();
						break;
					}
				}

				if( bCR )
				{
					size = 1;
					mboutbuf[0] = CFileData::CR;
					if( FileData.GetOSFile()->Write( mboutbuf, size, (unsigned long*)&written, 0 ) )
					{
						if( written < size )
						{
							break;
						}
						iLFCount ++;
						iCharCount++;
					}
					else
					{
						ulDOSResult = m_sErrorHelper.GetLastError();
						break;
					}
				}
			}
			else if ( chTMode == CFileData::__IOINFO_TM_UTF8 || chTMode == CFileData::__IOINFO_TM_UTF16LE )
			{
				if ( PutWCh( tmpchar ) == tmpchar )
				{
					iCharCount++;
				}
				else
				{
					ulDOSResult = m_sErrorHelper.GetLastError();
					break;
				}
				if (bCR) // emit carriage return
				{
					size = 1;
					tmpchar = CFileData::CR;
					if ( PutWCh( tmpchar ) == tmpchar )
					{
						iCharCount++;
						iLFCount++;
					}
					else
					{
						ulDOSResult = m_sErrorHelper.GetLastError();
						break;
					}
				}
			}
		}
	}

	//--------------------------------------------------------------------------------
	int CFileSystem::WriteText( CFileData& FileData, const void*& pvBuffer, unsigned long& ulDOSResult, unsigned int& uiCount, char& chTMode, int& iLFCount, int& iWritten, int& iCharCount )
	{
		int iResult = 0;
		// text mode, translate LF's to CR/LF's on output
		ulDOSResult = 0;          // no OS error yet

		if( chTMode == CFileData::__IOINFO_TM_ANSI )
		{
			char ch;				// current character
			char* p = 0, *q = 0;	// pointers into buf and lfbuf resp.
			char lfbuf[ CFileData::BUF_SIZE ];
			p = (char *)pvBuffer;        // start at beginning of buffer
			while( (unsigned)( p - (char *)pvBuffer ) < uiCount )
			{
				q = lfbuf;      // start at beginning of lfbuf
				// fill the lf buf, except maybe last char
				while( q - lfbuf < sizeof( lfbuf ) - 1 && (unsigned)( p - (char *)pvBuffer ) < uiCount )
				{
					ch = *p++;
					if( ch == CFileData::LF )
					{
						++iLFCount;
						*q++ = CFileData::CR;
					}
					*q++ = ch;
				}

				// write the lf buf and update total
				if( FileData.GetOSFile()->Write( lfbuf, (int)( q - lfbuf ), (unsigned long*)&iWritten, 0 ) )
				{
					iCharCount += iWritten;
					if( iWritten < q - lfbuf )
					{
						break;
					}
				}
				else
				{
					ulDOSResult = m_sErrorHelper.GetLastError();
					break;
				}
			}
		}
		else if( chTMode == CFileData::__IOINFO_TM_UTF16LE )
		{
			char lfbuf[ CFileData::BUF_SIZE ];
			wchar_t wch;            /* current wide char */
			wchar_t* pu = (wchar_t*)pvBuffer;
			wchar_t* qu = NULL;

			while( (unsigned)( (char *)pu - (char *)pvBuffer) < uiCount )
			{
				qu = (wchar_t*)lfbuf; // start at beginning of lfbuf

				// fill the lf buf, except maybe last wchar_t
				while( ( ( (char *)qu - lfbuf ) < ( sizeof( lfbuf ) - 2 ) ) && ( (unsigned)( (char*)pu - (char*)pvBuffer ) < uiCount ) )
				{
					wch = *pu++;
					if( wch == CFileData::LF )
					{
						iLFCount+=2;
						*qu++ = CFileData::CR;
					}
					*qu++ = wch;
				}

				// write the lf buf and update total
				if( FileData.GetOSFile()->Write( lfbuf, (int)( (char*)qu - lfbuf ), (unsigned long*)&iWritten, 0 ) )
				{
					iCharCount += iWritten;
					if( iWritten < ( (char *)qu - lfbuf ) )
					{
						break;
					}
				}
				else
				{
					ulDOSResult = m_sErrorHelper.GetLastError();
					break;
				}
			}
		}
		else
		{
			/*Let's divide the lfbuf in 1:2 wher 1 is for storing widecharacters and 2 if for
			converting it to UTF8.  This takes into account the worst case scenario where all
			the UTF8 characters are 4 byte long. */
			char utf8_buf[ ( CFileData::BUF_SIZE * 2 ) / 3 ];
			wchar_t utf16_buf[ CFileData::BUF_SIZE / 6 ];

			wchar_t wch;            // current wide char
			wchar_t* pu = (wchar_t*)pvBuffer;
			wchar_t* qu = 0;

			pu = (wchar_t*)pvBuffer;
			while( (unsigned)( (char *)pu - (char *)pvBuffer ) < uiCount )
			{
				int bytes_converted = 0;
				qu = utf16_buf; // start at beginning of lfbuf

				while( ( ( (char *)qu - (char *)utf16_buf ) < ( sizeof( utf16_buf ) - 2 ) ) && ( (unsigned)( (char *)pu - (char *)pvBuffer ) < uiCount ) )
				{
					wch = *pu++;
					if( wch == CFileData::LF )
					{
						// no need to count the linefeeds here: we calculate the written chars in another way
						*qu++ = CFileData::CR;
					}
					*qu++ = wch;
				}

				bytes_converted = 0;//TODO:
				/*m_sStringHelper.WideCharToMultiByte( CCodePage::UTF8, 0, utf16_buf,
				( (int)( (char *)qu - (char *)utf16_buf ) ) / 2,
				utf8_buf, sizeof( utf8_buf ), 0, 0 );*/

				if( bytes_converted == 0 )
				{
					ulDOSResult = m_sErrorHelper.GetLastError();
					break;
				}
				else
				{
					/* Here we need to make every attempt to write all the converted characters.
					The resaon behind this is, incase half the bytes of a UTF8 character is written,
					it may currupt whole of the stream or file.
					The loop below will make sure we exit only if all the bytes converted are written
					(which makes sure no partial MBCS is written) or there was some error in the stream.*/
					int bytes_written = 0;
					do
					{
						if( FileData.GetOSFile()->Write( utf8_buf + bytes_written, bytes_converted - bytes_written, (unsigned long*)&iWritten, 0 ) )
						{
							bytes_written += iWritten;
						}
						else
						{
							ulDOSResult = m_sErrorHelper.GetLastError();
							break;
						}
					} while( bytes_converted > bytes_written );

					/*Only way the condition below could be true is if there was en error. In case
					of error we need to break this loop as well.*/
					if( bytes_converted > bytes_written )
					{
						break;
					}
					// if this chunk has been committed successfully, update charcount
					iCharCount = (int)((char *)pu - (char *)pvBuffer);
				}
			}
		}
		return iResult;
	}

	//--------------------------------------------------------------------------------
	wint_t CFileSystem::PutWCh( wchar_t ch )
	{
		//int size;
		int num_written;
		static int use_w = 2;
		//char mbc[ MB_LEN_MAX + 1 ];
		if( use_w )
		{
			if( nsWin32::CConsole::ConsoleOutputFile() == (nsWin32::CFile*)(-2) )
			{
				nsWin32::CConsole::__initconout();
			}

			// write character to console file handle

			if( nsWin32::CConsole::ConsoleOutputFile() == (nsWin32::CFile*)(-1) )
			{
				return WEOF;
			}
			else if( !nsWinQAPI::CKernel32::WriteConsoleW( nsWin32::CConsole::ConsoleOutputFile()->Handle(), (void*)&ch, 1, (unsigned long*)&num_written, 0 ) )
			{
				if( use_w == 2 && m_sErrorHelper.GetLastError() == nsWin32::ErrorCallNotImplemented )
				{
					use_w = 0;
				}
				else
				{
					return WEOF;
				}
			}
			else
			{
				use_w = 1;
			}
		}

		if ( use_w == 0 )
		{
			/*TODO:
			size = m_sStringHelper.WideCharToMultiByte( m_sConsoleHelper.GetOutputCP(), 0, (wchar_t*)&ch, 1, mbc, MB_LEN_MAX, 0, 0 );
			if( ( nsWin32::nsOSServices::CConsole::s_pConsoleOutput == (nsWin32::nsFileSystem::CFile*)(-1) ) || !nsWinQAPI::CKernel32::WriteConsole( nsWin32::nsOSServices::CConsole::s_pConsoleOutput->Handle(), (void*)mbc, size, (unsigned long*)&num_written, 0 ) )
			{
				// return error indicator
				*/
				return WEOF;
			//}
		}
		return ch;
	}

	//--------------------------------------------------------------------------------
	int CFileSystem::Close( CFileData& FileData )
	{
		int iResult = 0;

		{
			FileData.Lock();

			if( FileData.GetFlagsOpen() )
			{

				unsigned long dwDOSResult = 0;

				/*Close the underlying OS file handle. Special cases:
				*      1. If _get_osfhandle(fh) is Invalid_Handle_Value, don't try
				*         to actually close it. Just reset the lowio info so the
				*         handle can be reused. The standard handles are setup like
				*         this in Windows app, or a background app.
				*      2. If fh is STDOUT or STDERR, and if STDOUT and STDERR are
				*         mapped to the same OS file handle, skip the CloseHandle
				*         is skipped (without error). STDOUT and STDERR are the only
				*         handles for which this support is provided. Other handles
				*         are mapped to the same OS file handle only at the
				*         programmer's risk.
				*/

				if( ( FileData.GetOSFile()->Handle() == Invalid_Handle_Value ) ||  ( ( ( FileData.Buffering().GetFile() == 1 && ( FileData.GetFlagsOpen() ) ) ||
					( FileData.Buffering().GetFile() == 2 && ( FileData.GetFlagsOpen() ) ) ) /*&& ( s_pStdOut->m_pFile->Handle() == s_pStdErr->m_pFile->Handle() )*/ ) )
				{
					FileData.SetOSFile( 0 );
					dwDOSResult = 0L;
				}
				else
				{
					delete FileData.GetOSFile();
					FileData.SetOSFile( 0 );
				}

				dwDOSResult = m_sErrorHelper.GetLastError();

				FileData.ResetFlags();// clear file flags

				if( dwDOSResult )
				{
					// OS error
					//TODO: CDOSError::MapError( dwDOSResult );
					iResult = -1;
				}

				iResult = 0;
			}
			else
			{
				*(nsBaseCRT::CCRTErrorDomain::ErrNo()) = EBADF;
				iResult = -1;
			}

			FileData.Unlock();
		}

		return iResult;
	}

};//namespace nsWin32
