/* Public Domain Curses */

#include "Qurses/Windows/pdcwin.h"
#include "WinQL/System/WinQLSystem.h"
#include "WinQL/Application/Memory/WinQLGlobal.h"

RCSID("$Id: pdcclip.c,v 1.30 2008/07/14 04:24:52 wmcbrine Exp $")

/*man-start**************************************************************

  Name:                                                         clipboard

  Synopsis:
        int PDC_getclipboard(char **contents, long *length);
        int PDC_setclipboard(const char *contents, long length);
        int PDC_freeclipboard(char *contents);
        int PDC_clearclipboard(void);

  Description:
        PDC_getclipboard() gets the textual contents of the system's 
        clipboard. This function returns the contents of the clipboard 
        in the contents argument. It is the responsibilitiy of the 
        caller to free the memory returned, via PDC_freeclipboard().
        The length of the clipboard contents is returned in the length 
        argument.

        PDC_setclipboard copies the supplied text into the system's 
        clipboard, emptying the clipboard prior to the copy.

        PDC_clearclipboard() clears the internal clipboard.

  Return Values:
        indicator of success/failure of call.
        PDC_CLIP_SUCCESS        the call was successful
        PDC_CLIP_MEMORY_ERROR   unable to allocate sufficient memory for 
                                the clipboard contents
        PDC_CLIP_EMPTY          the clipboard contains no text
        PDC_CLIP_ACCESS_ERROR   no clipboard support

  Portability                                X/Open    BSD    SYS V
        PDC_getclipboard                        -       -       -
        PDC_setclipboard                        -       -       -
        PDC_freeclipboard                       -       -       -
        PDC_clearclipboard                      -       -       -

**man-end****************************************************************/

#if __QOR_UNICODE
# define PDC_TEXT nsWin32::CClipboard::CF_UNICODEText
#else
# define PDC_TEXT nsWin32::CClipboard::CF_OEMText
#endif

//------------------------------------------------------------------------------
int PDC_getclipboard( char** contents, long* length )
{
	__QCS_FCONTEXT( "PDC_getclipboard" );

    void* handle;
    long len;
	nsWin32::CGlobalHelper GlobalHelper;

	nsWin32::CClipboardSession::refType RefSession = nsWin32::CSystem::TheSystem().Clipboard(QOR_PP_SHARED_OBJECT_ACCESS).Session( nsWin32::COSWindow::refType() );

	if( RefSession.IsNull() )
	{
        return PDC_CLIP_ACCESS_ERROR;
	}

	
    if( ( handle = RefSession->GetData( PDC_TEXT ) ) == 0 )
    {
        return PDC_CLIP_EMPTY;
    }

#if __QOR_UNICODE
    len = wcslen((wchar_t *)handle) * 3;
#else
    len = strlen((char *)handle);
#endif
	*contents = (char *)GlobalHelper.Alloc( nsWin32::CGlobalHelper::GMem_FIXED, len + 1 );

    if (!*contents)
    {
        return PDC_CLIP_MEMORY_ERROR;
    }

#if __QOR_UNICODE
    len = PDC_wcstombs((char *)*contents, (wchar_t *)handle, len);
#else
    strcpy((char *)*contents, (char *)handle);
#endif
    *length = len;

    return PDC_CLIP_SUCCESS;
}

//------------------------------------------------------------------------------
int PDC_setclipboard(const char *contents, long length)
{
	__QCS_FCONTEXT( "PDC_setclipboard" );
    void* ptr1;
	nsWin32::mxChar* ptr2;
	nsWin32::CGlobalHelper GlobalHelper;

	nsWin32::CClipboardSession::refType RefSession = nsWin32::CSystem::TheSystem().Clipboard(QOR_PP_SHARED_OBJECT_ACCESS).Session( nsWin32::COSWindow::refType() );

	if( RefSession.IsNull() )
	{
        return PDC_CLIP_ACCESS_ERROR;
	}

	ptr1 = GlobalHelper.Alloc( nsWin32::CGlobalHelper::GMem_MOVEABLE | nsWin32::CGlobalHelper::GMem_DDESHARE, (length + 1) * sizeof(TCHAR) );

    if( !ptr1 )
	{
        return PDC_CLIP_MEMORY_ERROR;
	}

    ptr2 = reinterpret_cast< nsWin32::mxChar* >( GlobalHelper.Lock( ptr1 ) );

#if __QOR_UNICODE
    PDC_mbstowcs((wchar_t *)ptr2, contents, length);
#else
    memcpy( (char*)ptr2, contents, length + 1 );
#endif

	GlobalHelper.Unlock( ptr1 );
    
	RefSession->Empty();
    
	
    if( !RefSession->SetData( PDC_TEXT, ptr1 ) )
    {
		GlobalHelper.Free( ptr1 );
        return PDC_CLIP_ACCESS_ERROR;
    }

	GlobalHelper.Free( ptr1 );
    return PDC_CLIP_SUCCESS;
}

//------------------------------------------------------------------------------
int PDC_freeclipboard( char* contents )
{
	__QCS_FCONTEXT( "PDC_freeclipboard" );

	nsWin32::CGlobalHelper GlobalHelper;
	GlobalHelper.Free( contents );

    return PDC_CLIP_SUCCESS;
}

//------------------------------------------------------------------------------
int PDC_clearclipboard( void )
{
    __QCS_FCONTEXT( "PDC_clearclipboard" );

	nsWin32::CClipboardSession::refType RefSession = nsWin32::CSystem::TheSystem().Clipboard(QOR_PP_SHARED_OBJECT_ACCESS).Session( nsWin32::COSWindow::refType() );
	RefSession->Empty();

    return PDC_CLIP_SUCCESS;
}
