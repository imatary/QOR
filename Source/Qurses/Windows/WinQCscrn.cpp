/* Public Domain Curses */

#include "Qurses/Windows/pdcwin.h"
#include "WinQL/WinQL.h"
#include "WinQL/Definitions/Constants.h"
#include "WinQL/Definitions/Errors.h"
#include "WinQL/Application/Console/WinQLConsoleScreenBuffer.h"
#include "WinQL/Application/WinQLApplication.h"
#include "WinQL/System/Clock/WinQLTime.h"
#include "WinQL/System/Registry/WinQLRegistry.h"
#include "WinQL/System/WinQLSystem.h"
#include "WinQL/Application/Memory/WinQLMemFile.h"
#include "WinQL/GUI/MessageHandler.h"

RCSID("$Id: pdcscrn.c,v 1.92 2008/07/20 20:12:04 wmcbrine Exp $")

#ifdef CHTYPE_LONG
# define PDC_OFFSET 32
#else
# define PDC_OFFSET  8
#endif

// COLOR_PAIR to attribute encoding table.

unsigned char *pdc_atrtab = (unsigned char *)0;

void* pdc_con_out = (void*)Invalid_Handle_Value;
void* pdc_con_in = (void*)Invalid_Handle_Value;
nsWin32::CConsole::refType Console;

unsigned long pdc_quick_edit;

//------------------------------------------------------------------------------
static short curstoreal[16], realtocurs[16] =
{
    COLOR_BLACK, COLOR_BLUE, COLOR_GREEN, COLOR_CYAN, COLOR_RED,
    COLOR_MAGENTA, COLOR_YELLOW, COLOR_WHITE, COLOR_BLACK + 8,
    COLOR_BLUE + 8, COLOR_GREEN + 8, COLOR_CYAN + 8, COLOR_RED + 8,
    COLOR_MAGENTA + 8, COLOR_YELLOW + 8, COLOR_WHITE + 8
};

enum { PDC_RESTORE_NONE, PDC_RESTORE_BUFFER, PDC_RESTORE_WINDOW };

//------------------------------------------------------------------------------
/* Struct for storing console registry keys, and for use with the 
   undocumented WM_SETCONSOLEINFO message. Originally by James Brown, 
   www.catch22.net. */
static struct
{
    unsigned long    Length;
    nsWin32::Coord	ScreenBufferSize;
    nsWin32::Coord    WindowSize;
    unsigned long    WindowPosX;
    unsigned long    WindowPosY;

    nsWin32::Coord    FontSize;
    unsigned long    FontFamily;
    unsigned long    FontWeight;
    wchar_t    FaceName[32];

    unsigned long    CursorSize;
    unsigned long    FullScreen;
    unsigned long    QuickEdit;
    unsigned long    AutoPosition;
    unsigned long    InsertMode;
    
    unsigned short   ScreenColors;
    unsigned short   PopupColors;
    unsigned long    HistoryNoDup;
    unsigned long    HistoryBufferSize;
    unsigned long    NumberOfHistoryBuffers;
    
    unsigned long ColorTable[16];

    unsigned long    CodePage;
    void*		Hwnd;

    wchar_t    ConsoleTitle[0x100];
} console_info;

static nsWin32::ConsoleScreenBufferInfoEx orig_scr;

nsCodeQOR::CTArray< nsWin32::CharInfo, CWinQLPolicy >* pa_Save = 0;
//static nsWin32::CharInfo* ci_save = 0;
static unsigned long old_console_mode = 0;

static bool is_nt;

//------------------------------------------------------------------------------
static void* _find_console_handle(void)
{
	__QCS_FCONTEXT( "_find_console_handle" );

	nsWin32::CThreadHelper ThreadHelper;
	nsWin32::CTimeHelper TimeHelper;
    TCHAR orgtitle[ 1024 ], temptitle[ 1024 ];
    void* wnd;
	Console = nsWin32::CConsole::TheWin32Console();

	nsWin32::CTString strTitle = Console->Title.Get();
	
	nsWin32::CTString strTempTitle;
	strTempTitle.FormatV( _TXT( "%d/%d" ), TimeHelper.GetTickCount(), nsWin32::CProcess::GetCurrentId() );

	Console->Title.Set( strTempTitle );
   
	ThreadHelper.Sleep( 40 );

	nsWin32::COSWindow::refType RefWindow = nsWin32::COSWindow::Find( 0, strTempTitle );
	wnd = RefWindow.Detach()->Handle()->AsHandle().Detach();

	Console->Title.Set( strTitle );

    return wnd;
}

//------------------------------------------------------------------------------
#define WM_SETCONSOLEINFO (WM_USER + 201)		// Undocumented console message


//------------------------------------------------------------------------------
/* Wrapper around WM_SETCONSOLEINFO. We need to create the necessary 
   section (file-mapping) object in the context of the process which 
   owns the console, before posting the message. Originally by JB. */
static void _set_console_info(void)
{
	__QCS_FCONTEXT( "_set_console_info" );

	nsWin32::ConsoleScreenBufferInfoEx csbi;
	nsWin32::ConsoleCursorInfo cci;
    unsigned long dwConsoleOwnerPid;
    //void* hProcess;
    void* hDupSection;
    //void* ptrView;
	nsWin32::CMessageHandler MessageHandler;
	nsWin32::CConsole::refType Console = nsWin32::CConsole::TheWin32Console();

    // Each-time initialization for console_info

	Console->ScreenBuffer()->GetCursorInfo( cci );
    console_info.CursorSize = cci.dwSize;

	Console->ScreenBuffer()->GetInfoEx( csbi );
    
    console_info.ScreenBufferSize = csbi.dwSize;

    console_info.WindowSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    console_info.WindowSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    console_info.WindowPosX = csbi.srWindow.Left;
    console_info.WindowPosY = csbi.srWindow.Top;

    // Open the process which "owns" the console
	nsWin32::COSWindow::refType refWindow = nsWin32::COSWindow::FromHandle( nsWin32::CWindowHandle( 0, console_info.Hwnd ).Ref() );
	refWindow->GetThreadProcessId( &dwConsoleOwnerPid );

	{
		nsWin32::CRemoteProcess ConsoleProcess( nsWin32::Process_All, false, dwConsoleOwnerPid );
    
		/* Create a SECTION object backed by page-file, then map a view of
		   this section into the owner process so we can write the contents
		   of the CONSOLE_INFO buffer into it */
		nsWin32::CMemFile MemFile( 0, nsWin32::Page_ReadWrite, 0, sizeof( console_info ), 0 );

		{
			nsWin32::CMappedViewOfFile Section( MemFile.Ref(), nsWin32::CMappedViewOfFile::Map_Write | nsWin32::CMappedViewOfFile::Map_Read, 0, 0, sizeof( console_info ) );

			//hSection = CreateFileMapping( Invalid_Handle_Value , 0, nsWin32::Page_ReadWrite, 0, sizeof(console_info), 0);

			// Copy our console structure into the section-object

			//ptrView = MapViewOfFile( hSection, FILE_MAP_WRITE|FILE_MAP_READ, 0, 0, sizeof( console_info ) );

			memcpy( Section(), &console_info, sizeof( console_info ) );

		}

		// Map the memory into owner process
		MemFile.Handle().AsHandle().Duplicate( nsWin32::ThisProcess()->ProcessHandle().Use(), ConsoleProcess.ProcessHandle().Use(), &hDupSection, 0, false, nsWin32::Duplicate_Same_Access );
		//DuplicateHandle( GetCurrentProcess(), hSection, hProcess, &hDupSection, 0, FALSE, DUPLICATE_SAME_ACCESS );

		// Send console window the "update" message
		MessageHandler.Send( nsWin32::COSWindow::FromHandle( nsWin32::CRAIISessionHandle( 0, console_info.Hwnd ).Ref() ), nsWin32::COSWindow::wmSetConsoleInfo, (Cmp_uint_ptr)hDupSection, 0 );
		//SendMessage( console_info.Hwnd, nsWin32::COSWindow::wmSetConsoleInfo, (Cmp_uint_ptr)hDupSection, 0 );    
	}
}

//------------------------------------------------------------------------------
// One-time initialization for console_info -- color table and font info from the registry; other values from functions.
static void _init_console_info(void)
{
	__QCS_FCONTEXT( "_init_console_info" );

    unsigned long scrnmode, len;
	
	nsWin32::CRegistry::CKeyRef rehnd;
    //HKEY reghnd;
    int i;
	nsWin32::CConsole::refType Console = nsWin32::CConsole::TheWin32Console();

    console_info.Hwnd = _find_console_handle();
    console_info.Length = sizeof(console_info);

	Console->ScreenBuffer()->GetOutputMode( scrnmode );
    
    console_info.QuickEdit = !!(scrnmode & 0x0040);
    console_info.InsertMode = !!(scrnmode & 0x0020);

    console_info.FullScreen = FALSE;
    console_info.AutoPosition = 0x10000;
    console_info.ScreenColors = SP->orig_back << 4 | SP->orig_fore;
    console_info.PopupColors = 0xf5;
    
    console_info.HistoryNoDup = FALSE;
    console_info.HistoryBufferSize = 50;
    console_info.NumberOfHistoryBuffers = 4;
	
    console_info.CodePage = nsWin32::CConsole::TheWin32Console()->OutputCodePage.Get().ID();

	rehnd.Attach( new nsWin32::CRegKey( *(nsWin32::CSystem::TheSystem().Registry(QOR_PP_SHARED_OBJECT_ACCESS).CurrentUser()), _TXT( "Console" ), 0, nsWin32::CRegKey::Query_Value ), true );
    //RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Console"), 0, KEY_QUERY_VALUE, &reghnd);

    len = sizeof( unsigned long );

    /* Default color table */

    for (i = 0; i < 16; i++)
    {
        TCHAR tname[13];
#if __QOR_UNICODE
		wprintf( tname, _TXT( "ColorTable%02d" ), i );
#else
		sprintf( tname, _TXT( "ColorTable%02d" ), i );
#endif
		rehnd->QueryValueEx( tname, NULL, (byte*)(&(console_info.ColorTable[i])), &len );
        //RegQueryValueExA( reghnd, tname, NULL, NULL, (byte*)(&(console_info.ColorTable[i])), &len );
    }

    /* Font info */
	rehnd->GetValue( _TXT( "FontSize" ), 0, 0, 0, (byte*)(&console_info.FontSize), &len );
	rehnd->GetValue( _TXT( "FontFamily" ), 0, 0, 0, (byte*)(&console_info.FontFamily), &len );
	rehnd->GetValue( _TXT( "FontWeight" ), 0, 0, 0, (byte*)(&console_info.FontWeight), &len );
	/*
    RegQueryValueEx(reghnd, TEXT("FontSize"), NULL, NULL, (byte*)(&console_info.FontSize), &len);
    RegQueryValueEx(reghnd, TEXT("FontFamily"), NULL, NULL, (byte*)(&console_info.FontFamily), &len);
    RegQueryValueEx(reghnd, TEXT("FontWeight"), NULL, NULL, (byte*)(&console_info.FontWeight), &len);
	*/
    len = sizeof(wchar_t) * 32;
	rehnd->GetValue( _TXT( "FaceName" ), 0, 0, 0, (byte*)(console_info.FaceName), &len);
    //RegQueryValueExW(reghnd, L"FaceName", NULL, NULL, (byte*)(console_info.FaceName), &len);

    //RegCloseKey(reghnd);
}

//------------------------------------------------------------------------------
// close the physical screen -- may restore the screen to its state before PDC_scr_open(); miscellaneous cleanup
void PDC_scr_close( void )
{
	__QCS_FCONTEXT( "PDC_scr_close" );

	nsWin32::Coord origin;
	nsWin32::SmallRect rect;

    PDC_reset_shell_mode();

    if (SP->_restore != PDC_RESTORE_NONE)
    {
        if (SP->_restore == PDC_RESTORE_WINDOW)
        {
            rect.Top = orig_scr.srWindow.Top;
            rect.Left = orig_scr.srWindow.Left;
            rect.Bottom = orig_scr.srWindow.Bottom;
            rect.Right = orig_scr.srWindow.Right;
        }
        else    /* PDC_RESTORE_BUFFER */
        {
            rect.Top = rect.Left = 0;
            rect.Bottom = orig_scr.dwSize.Y - 1;
            rect.Right = orig_scr.dwSize.X - 1;
        }

        origin.X = origin.Y = 0;

		if( !nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->WriteOutput( *pa_Save, orig_scr.dwSize, origin, rect ) )
		{
			return ;
		}
		/*
        if( !WriteConsoleOutput( pdc_con_out, ci_save, orig_scr.dwSize, origin, &rect ) )
		{
            return;
		}
		*/
    }

    if (SP->visibility != 1)
        curs_set(1);

    /* Position cursor to the bottom left of the screen. */

    PDC_gotoyx(PDC_get_buffer_rows() - 2, 0);
}

//------------------------------------------------------------------------------
void PDC_scr_free(void)
{
	__QCS_FCONTEXT( "PDC_scr_free" );

    if( SP )
	{
        free(SP);
	}

    if( pdc_atrtab )
	{
        free(pdc_atrtab);
	}

    pdc_atrtab = (unsigned char *)NULL;
}


//------------------------------------------------------------------------------
// open the physical screen -- allocate SP, miscellaneous intialization, and may save the existing screen for later restoration 
int PDC_scr_open( int argc, char **argv )
{
	__QCS_FCONTEXT( "PDC_scr_open" );

    nsWin32::Coord bufsize, origin;
	nsWin32::SmallRect rect;
    const char *str;
	nsWin32::ConsoleScreenBufferInfoEx csbi;
	memset( &csbi, 0, sizeof( nsWin32::ConsoleScreenBufferInfoEx ) );
	csbi.cbSize = sizeof( nsWin32::ConsoleScreenBufferInfoEx );
    int i;

    SP = reinterpret_cast< SCREEN* >( calloc( 1, sizeof( SCREEN ) ) );
    pdc_atrtab = reinterpret_cast< unsigned char* >( calloc( PDC_COLOR_PAIRS * PDC_OFFSET, 1 ) );

    if (!SP || !pdc_atrtab)
	{
        return ERR;
	}

    for (i = 0; i < 16; i++)
	{
        curstoreal[realtocurs[i]] = i;
	}

	Console = nsWin32::CConsole::TheWin32Console();

	Console->ScreenBuffer()->GetInfoEx( csbi );

	nsWin32::CCRTFile* pinFile = Console->ConsoleInputFile();
	nsWin32::CCRTFile* poutFile = Console->ConsoleOutputFile();


	pdc_con_in = Console->ConsoleInputFile()->Handle()->Use();
	pdc_con_out = Console->ConsoleOutputFile()->Handle()->Use();

	
	if( Console->ConsoleInputFile()->GetType() != nsWin32::File_Type_Char )
    {
        fprintf(stderr, "\nRedirection is not supported.\n");
        exit(1);
    }
	
    is_nt = !( nsWin32::CSystem::TheSystem().Information(QOR_PP_SHARED_OBJECT_ACCESS).GetVersion() & 0x80000000 );

	Console->ScreenBuffer()->GetInfoEx( csbi );

	memset( &orig_scr, 0, sizeof( nsWin32::ConsoleScreenBufferInfoEx ) );
	orig_scr.cbSize = sizeof( nsWin32::ConsoleScreenBufferInfoEx );
	Console->ScreenBuffer()->GetInfoEx( orig_scr );
	Console->ScreenBuffer()->GetOutputMode( old_console_mode );

    // preserve QuickEdit Mode setting for use in PDC_mouse_set() when the mouse is not enabled -- other console input settings are cleared

    pdc_quick_edit = old_console_mode & 0x0040;

    SP->lines = (str = getenv("LINES")) ? atoi(str) : PDC_get_rows();
    SP->cols = (str = getenv("COLS")) ? atoi(str) : PDC_get_columns();

    SP->mouse_wait = PDC_CLICK_PERIOD;
    SP->audible = TRUE;

    if (SP->lines < 2 || SP->lines > csbi.dwMaximumWindowSize.Y)
    {
        fprintf(stderr, "LINES value must be >= 2 and <= %d: got %d\n",
                csbi.dwMaximumWindowSize.Y, SP->lines);

        return ERR;
    }

    if (SP->cols < 2 || SP->cols > csbi.dwMaximumWindowSize.X)
    {
        fprintf(stderr, "COLS value must be >= 2 and <= %d: got %d\n",
                csbi.dwMaximumWindowSize.X, SP->cols);

        return ERR;
    }

    SP->orig_fore = csbi.wAttributes & 0x0f;
    SP->orig_back = (csbi.wAttributes & 0xf0) >> 4;

    SP->orig_attr = TRUE;

    SP->_restore = PDC_RESTORE_NONE;

    if( getenv( "PDC_RESTORE_SCREEN" ) )
    {
        // Attempt to save the complete console buffer

		pa_Save = new nsCodeQOR::CTArray< nsWin32::CharInfo, CWinQLPolicy >( orig_scr.dwSize.X * orig_scr.dwSize.Y );
        //ci_save = malloc( orig_scr.dwSize.X * orig_scr.dwSize.Y * sizeof( nsWin32::CharInfo ) );

        if (!pa_Save)
        {
            PDC_LOG(("PDC_scr_open() - malloc failure (1)\n"));

            return ERR;
        }

        bufsize.X = orig_scr.dwSize.X;
        bufsize.Y = orig_scr.dwSize.Y;

        origin.X = origin.Y = 0;

        rect.Top = rect.Left = 0;
        rect.Bottom = orig_scr.dwSize.Y  - 1;
        rect.Right = orig_scr.dwSize.X - 1;

		if( ! Console->ScreenBuffer()->ReadOutput( pa_Save->GetAddressOfData(), bufsize, origin, rect ) )
        //if (!ReadConsoleOutput(pdc_con_out, ci_save, bufsize, origin, &rect))
        {
            // We can't save the complete buffer, so try and save just the displayed window

			delete pa_Save;
            //free(ci_save);
			pa_Save = 0;
            //ci_save = NULL;

            bufsize.X = orig_scr.srWindow.Right - orig_scr.srWindow.Left + 1;
            bufsize.Y = orig_scr.srWindow.Bottom - orig_scr.srWindow.Top + 1;

			pa_Save = new nsCodeQOR::CTArray< nsWin32::CharInfo, CWinQLPolicy >( bufsize.X * bufsize.Y );
			//ci_save = malloc(bufsize.X * bufsize.Y * sizeof(nsWin32::CharInfo) );

            if (!pa_Save)
            {
                PDC_LOG(("PDC_scr_open() - malloc failure (2)\n"));

                return ERR;
            }

            origin.X = origin.Y = 0;

            rect.Top = orig_scr.srWindow.Top;
            rect.Left = orig_scr.srWindow.Left;
            rect.Bottom = orig_scr.srWindow.Bottom;
            rect.Right = orig_scr.srWindow.Right;

			if( ! Console->ScreenBuffer()->ReadOutput( pa_Save->GetAddressOfData(), bufsize, origin, rect ) )
            {
#ifdef PDCDEBUG
                CHAR LastError[256];

                FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), LastError, 256, NULL );

                PDC_LOG(("PDC_scr_open() - %s\n", LastError));
#endif
				delete pa_Save;
                //free(ci_save);
				pa_Save = 0;
                //ci_save = NULL;

                return ERR;
            }

            SP->_restore = PDC_RESTORE_WINDOW;
        }
        else
            SP->_restore = PDC_RESTORE_BUFFER;
    }

    SP->_preserve = (getenv("PDC_PRESERVE_SCREEN") != NULL);

    PDC_reset_prog_mode();

    SP->mono = FALSE;

    return nsWin32::OK;
}

//------------------------------------------------------------------------------
//Calls SetConsoleWindowInfo with the given parameters, but fits them  if a scoll bar shrinks the maximum possible value. 
//The rectangle must at least fit in a half-sized window.
static int _fit_console_window( void* con_out, const nsWin32::SmallRect * rect)
{
	__QCS_FCONTEXT( "_fit_console_window" );
	nsWin32::SmallRect run;
    short mx, my;

	if( nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetWindowInfo( true, *rect ) )
    //if( SetConsoleWindowInfo( con_out, TRUE, rect ) )
	{
        return 1;
	}

    run = *rect;
    run.Right /= 2;
    run.Bottom /= 2;

    mx = run.Right;
    my = run.Bottom;

	if( nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetWindowInfo( true, run ) )
    //if( !SetConsoleWindowInfo( con_out, TRUE, &run ) )
	{
        return 0;
	}

    for (run.Right = rect->Right; run.Right >= mx; run.Right--)
	{
		if( nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetWindowInfo( true, run ) )
        //if( SetConsoleWindowInfo( con_out, TRUE, &run ) )
		{
            break;
		}
	}

    if (run.Right < mx)
        return 0;

    for (run.Bottom = rect->Bottom; run.Bottom >= my; run.Bottom--)
	{
		if( nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetWindowInfo( true, run ) )
        //if( SetConsoleWindowInfo( con_out, TRUE, &run ) )
		{
            return 1;
		}
	}

    return 0;
}

//------------------------------------------------------------------------------
// the core of resize_term()
int PDC_resize_screen( int nlines, int ncols )
{
	__QCS_FCONTEXT( "PDC_resize_screen" );

	nsWin32::SmallRect rect;
    nsWin32::Coord size, max;

    if( nlines < 2 || ncols < 2 )
	{
        return ERR;
	}

	max = nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->GetLargestWindowSize();
    //max = GetLargestConsoleWindowSize(pdc_con_out);

    rect.Left = rect.Top = 0;
    rect.Right = ncols - 1;

    if( rect.Right > max.X )
	{
        rect.Right = max.X;
	}

    rect.Bottom = nlines - 1;

    if (rect.Bottom > max.Y)
        rect.Bottom = max.Y;

    size.X = rect.Right + 1;
    size.Y = rect.Bottom + 1;

    _fit_console_window(pdc_con_out, &rect);
	nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetSize( size );
    //SetConsoleScreenBufferSize(pdc_con_out, size);
    _fit_console_window(pdc_con_out, &rect);
    //SetConsoleScreenBufferSize(pdc_con_out, size);
	nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetSize( size );
	nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetActive();
    //SetConsoleActiveScreenBuffer(pdc_con_out);

    return nsWin32::OK;
}

//------------------------------------------------------------------------------
void PDC_reset_prog_mode( void )
{
    __QCS_FCONTEXT( "PDC_reset_prog_mode" );

    if( is_nt )
    {
        nsWin32::Coord bufsize;
		nsWin32::SmallRect rect;

        bufsize.X = orig_scr.srWindow.Right - orig_scr.srWindow.Left + 1;
        bufsize.Y = orig_scr.srWindow.Bottom - orig_scr.srWindow.Top + 1;

        rect.Top = rect.Left = 0;
        rect.Bottom = bufsize.Y - 1;
        rect.Right = bufsize.X - 1;

		nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetSize( bufsize );
        //SetConsoleScreenBufferSize(pdc_con_out, bufsize);
		nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetWindowInfo( true, rect );
        //SetConsoleWindowInfo(pdc_con_out, TRUE, &rect);
		nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetSize( bufsize );
        //SetConsoleScreenBufferSize(pdc_con_out, bufsize);
		nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetActive();
        //SetConsoleActiveScreenBuffer(pdc_con_out);
    }

    PDC_mouse_set();
}

//------------------------------------------------------------------------------
void PDC_reset_shell_mode( void )
{
    __QCS_FCONTEXT( "PDC_reset_shell_mode" );

    if( is_nt )
    {
		nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetSize( orig_scr.dwSize );
		nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetWindowInfo( true, orig_scr.srWindow );
		nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetSize( orig_scr.dwSize );
		nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetWindowInfo( true, orig_scr.srWindow );
		nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetActive();
    }

	nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetOutputMode( old_console_mode );
}

//------------------------------------------------------------------------------
void PDC_restore_screen_mode(int i)
{
}

//------------------------------------------------------------------------------
void PDC_save_screen_mode(int i)
{
}

//------------------------------------------------------------------------------
void PDC_init_pair( short pair, short fg, short bg )
{
	__QCS_FCONTEXT( "PDC_init_pair" );

    unsigned char att, temp_bg;
    chtype i;

    fg = curstoreal[fg];
    bg = curstoreal[bg];

    for (i = 0; i < PDC_OFFSET; i++)
    {
        att = fg | (bg << 4);

        if (i & (A_REVERSE >> PDC_ATTR_SHIFT))
            att = bg | (fg << 4);
        if (i & (A_UNDERLINE >> PDC_ATTR_SHIFT))
            att = 1;
        if (i & (A_INVIS >> PDC_ATTR_SHIFT))
        {
            temp_bg = att >> 4;
            att = temp_bg << 4 | temp_bg;
        }
        if (i & (A_BOLD >> PDC_ATTR_SHIFT))
            att |= 8;
        if (i & (A_BLINK >> PDC_ATTR_SHIFT))
            att |= 128;

        pdc_atrtab[pair * PDC_OFFSET + i] = att;
    }
}

//------------------------------------------------------------------------------
int PDC_pair_content(short pair, short *fg, short *bg)
{
	__QCS_FCONTEXT( "PDC_pair_content" );

    *fg = realtocurs[pdc_atrtab[pair * PDC_OFFSET] & 0x0F];
    *bg = realtocurs[(pdc_atrtab[pair * PDC_OFFSET] & 0xF0) >> 4];

    return nsWin32::OK;
}

//------------------------------------------------------------------------------
bool PDC_can_change_color(void)
{
	__QCS_FCONTEXT( "PDC_can_change_color" );
    return is_nt;
}

//------------------------------------------------------------------------------
int PDC_color_content(short color, short *red, short *green, short *blue)
{
	__QCS_FCONTEXT( "PDC_color_content" );

    unsigned long col;

    if (!console_info.Hwnd)
	{
        _init_console_info();
	}

    col = console_info.ColorTable[ curstoreal[ color ] ];

    *red = DIVROUND( GetRedValue( col) * 1000, 255 );
    *green = DIVROUND( GetGreenValue( col) * 1000, 255 );
    *blue = DIVROUND( GetBlueValue( col) * 1000, 255 );

    return nsWin32::OK;
}

//------------------------------------------------------------------------------
int PDC_init_color(short color, short red, short green, short blue)
{
	__QCS_FCONTEXT( "PDC_init_color" );

    if( !console_info.Hwnd )
	{
        _init_console_info();
	}

    console_info.ColorTable[ curstoreal[ color ] ] =
        RedGreenBlue( DIVROUND( red * 255, 1000 ), DIVROUND( green * 255, 1000 ), DIVROUND( blue * 255, 1000 ) );

    _set_console_info();

    return nsWin32::OK;
}
