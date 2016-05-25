/* Public Domain Curses */

/* $Id: pdcwin.h,v 1.6 2008/07/13 06:36:32 wmcbrine Exp $ */

#ifdef PDC_WIDE
# define UNICODE
#endif

//#include <windows.h>
#include "Qurses/QursesPolicy.h"
#include "WinQL/WinQL.h"
#undef MOUSE_MOVED
#include "Qurses/curspriv.h"

extern unsigned char *pdc_atrtab;
extern void* pdc_con_out, *pdc_con_in;
extern unsigned long pdc_quick_edit;

extern int PDC_get_buffer_rows( void );
