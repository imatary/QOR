/* Public Domain Curses */

#include "Qurses/Windows/pdcwin.h"
#include "SystemQOR.h"
#include <string.h>
#include "WinQL/Definitions/Errors.h"
#include "WinQL/Application/WinQLApplication.h"
#include "WinQL/System/Devices/Keyboard/WinQLKeyboardInput.h"
#include "WinQL/System/WinQLSystem.h"

RCSID("$Id: pdckbd.c,v 1.115 2008/07/20 20:12:04 wmcbrine Exp $")

/*man-start**************************************************************

  Name:                                                         pdckbd

  Synopsis:
        unsigned long PDC_get_input_fd(void);

  Description:
        PDC_get_input_fd() returns the file descriptor that PDCurses 
        reads its input from. It can be used for select().

  Portability                                X/Open    BSD    SYS V
        PDC_get_input_fd                        -       -       -

**man-end****************************************************************/

unsigned long pdc_key_modifiers = 0L;

/* These variables are used to store information about the next
   Input Event. */

static nsCodeQOR::CTArray< nsWin32::InputRecord, CWinQLPolicy > save_ip( 1 );
static MOUSE_STATUS old_mouse_status;
static unsigned long event_count = 0;
static short left_key;
static int key_count = 0;
static int save_press = 0;

#define KEV save_ip[ 0 ].Event.KeyEvent
#define MEV save_ip[ 0 ].Event.MouseEvent

/************************************************************************
 *    Table for key code translation of function keys in keypad mode    *  
 *    These values are for strict IBM keyboard compatibles only         *
 ************************************************************************/

typedef struct
{
    unsigned short normal;
    unsigned short shift;
    unsigned short control;
    unsigned short alt;
    unsigned short extended;
} KPTAB;

//------------------------------------------------------------------------------
static KPTAB kptab[] =
{
   {0,          0,         0,           0,          0   }, /* 0  */
   {0,          0,         0,           0,          0   }, /* 1   vkLBUTTON */
   {0,          0,         0,           0,          0   }, /* 2   vkRBUTTON */
   {0,          0,         0,           0,          0   }, /* 3   vkCANCEL  */
   {0,          0,         0,           0,          0   }, /* 4   vkMBUTTON */
   {0,          0,         0,           0,          0   }, /* 5   */
   {0,          0,         0,           0,          0   }, /* 6   */
   {0,          0,         0,           0,          0   }, /* 7   */
   {0x08,       0x08,      0x7F,        ALT_BKSP,   0   }, /* 8   vkBACK    */
   {0x09,       KEY_BTAB,  CTL_TAB,     ALT_TAB,    999 }, /* 9   vkTAB     */
   {0,          0,         0,           0,          0   }, /* 10  */
   {0,          0,         0,           0,          0   }, /* 11  */
   {KEY_B2,     0x35,      CTL_PAD5,    ALT_PAD5,   0   }, /* 12  vkCLEAR   */
   {0x0D,       0x0D,      CTL_ENTER,   ALT_ENTER,  1   }, /* 13  vkRETURN  */
   {0,          0,         0,           0,          0   }, /* 14  */
   {0,          0,         0,           0,          0   }, /* 15  */
   {0,          0,         0,           0,          0   }, /* 16  vkSHIFT   HANDLED SEPARATELY */
   {0,          0,         0,           0,          0   }, /* 17  vkCONTROL HANDLED SEPARATELY */
   {0,          0,         0,           0,          0   }, /* 18  vkMENU    HANDLED SEPARATELY */
   {0,          0,         0,           0,          0   }, /* 19  vkPAUSE   */
   {0,          0,         0,           0,          0   }, /* 20  vkCAPITAL HANDLED SEPARATELY */
   {0,          0,         0,           0,          0   }, /* 21  vkHANGUL  */
   {0,          0,         0,           0,          0   }, /* 22  */
   {0,          0,         0,           0,          0   }, /* 23  vkJUNJA   */
   {0,          0,         0,           0,          0   }, /* 24  vkFINAL   */
   {0,          0,         0,           0,          0   }, /* 25  vkHANJA   */
   {0,          0,         0,           0,          0   }, /* 26  */
   {0x1B,       0x1B,      0x1B,        ALT_ESC,    0   }, /* 27  vkESCAPE  */
   {0,          0,         0,           0,          0   }, /* 28  vkCONVERT */
   {0,          0,         0,           0,          0   }, /* 29  vkNONCONVERT */
   {0,          0,         0,           0,          0   }, /* 30  vkACCEPT  */
   {0,          0,         0,           0,          0   }, /* 31  vkMODECHANGE */
   {0x20,       0x20,      0x20,        0x20,       0   }, /* 32  vkSPACE   */
   {KEY_A3,     0x39,      CTL_PAD9,    ALT_PAD9,   3   }, /* 33  vkPRIOR   */
   {KEY_C3,     0x33,      CTL_PAD3,    ALT_PAD3,   4   }, /* 34  vkNEXT    */
   {KEY_C1,     0x31,      CTL_PAD1,    ALT_PAD1,   5   }, /* 35  vkEND     */
   {KEY_A1,     0x37,      CTL_PAD7,    ALT_PAD7,   6   }, /* 36  vkHOME    */
   {KEY_B1,     0x34,      CTL_PAD4,    ALT_PAD4,   7   }, /* 37  vkLEFT    */
   {KEY_A2,     0x38,      CTL_PAD8,    ALT_PAD8,   8   }, /* 38  vkUP      */
   {KEY_B3,     0x36,      CTL_PAD6,    ALT_PAD6,   9   }, /* 39  vkRIGHT   */
   {KEY_C2,     0x32,      CTL_PAD2,    ALT_PAD2,   10  }, /* 40  vkDOWN    */
   {0,          0,         0,           0,          0   }, /* 41  vkSELECT  */
   {0,          0,         0,           0,          0   }, /* 42  vkPRINT   */
   {0,          0,         0,           0,          0   }, /* 43  vkEXECUTE */
   {0,          0,         0,           0,          0   }, /* 44  vkSNAPSHOT*/
   {PAD0,       0x30,      CTL_PAD0,    ALT_PAD0,   11  }, /* 45  vkINSERT  */
   {PADSTOP,    0x2E,      CTL_PADSTOP, ALT_PADSTOP,12  }, /* 46  vkDELETE  */
   {0,          0,         0,           0,          0   }, /* 47  vkHELP    */
   {0x30,       0x29,      0,           ALT_0,      0   }, /* 48  */
   {0x31,       0x21,      0,           ALT_1,      0   }, /* 49  */
   {0x32,       0x40,      0,           ALT_2,      0   }, /* 50  */
   {0x33,       0x23,      0,           ALT_3,      0   }, /* 51  */
   {0x34,       0x24,      0,           ALT_4,      0   }, /* 52  */
   {0x35,       0x25,      0,           ALT_5,      0   }, /* 53  */
   {0x36,       0x5E,      0,           ALT_6,      0   }, /* 54  */
   {0x37,       0x26,      0,           ALT_7,      0   }, /* 55  */
   {0x38,       0x2A,      0,           ALT_8,      0   }, /* 56  */
   {0x39,       0x28,      0,           ALT_9,      0   }, /* 57  */
   {0,          0,         0,           0,          0   }, /* 58  */
   {0,          0,         0,           0,          0   }, /* 59  */
   {0,          0,         0,           0,          0   }, /* 60  */
   {0,          0,         0,           0,          0   }, /* 61  */
   {0,          0,         0,           0,          0   }, /* 62  */
   {0,          0,         0,           0,          0   }, /* 63  */
   {0,          0,         0,           0,          0   }, /* 64  */
   {0x61,       0x41,      0x01,        ALT_A,      0   }, /* 65  */
   {0x62,       0x42,      0x02,        ALT_B,      0   }, /* 66  */
   {0x63,       0x43,      0x03,        ALT_C,      0   }, /* 67  */
   {0x64,       0x44,      0x04,        ALT_D,      0   }, /* 68  */
   {0x65,       0x45,      0x05,        ALT_E,      0   }, /* 69  */
   {0x66,       0x46,      0x06,        ALT_F,      0   }, /* 70  */
   {0x67,       0x47,      0x07,        ALT_G,      0   }, /* 71  */
   {0x68,       0x48,      0x08,        ALT_H,      0   }, /* 72  */
   {0x69,       0x49,      0x09,        ALT_I,      0   }, /* 73  */
   {0x6A,       0x4A,      0x0A,        ALT_J,      0   }, /* 74  */
   {0x6B,       0x4B,      0x0B,        ALT_K,      0   }, /* 75  */
   {0x6C,       0x4C,      0x0C,        ALT_L,      0   }, /* 76  */
   {0x6D,       0x4D,      0x0D,        ALT_M,      0   }, /* 77  */
   {0x6E,       0x4E,      0x0E,        ALT_N,      0   }, /* 78  */
   {0x6F,       0x4F,      0x0F,        ALT_O,      0   }, /* 79  */
   {0x70,       0x50,      0x10,        ALT_P,      0   }, /* 80  */
   {0x71,       0x51,      0x11,        ALT_Q,      0   }, /* 81  */
   {0x72,       0x52,      0x12,        ALT_R,      0   }, /* 82  */
   {0x73,       0x53,      0x13,        ALT_S,      0   }, /* 83  */
   {0x74,       0x54,      0x14,        ALT_T,      0   }, /* 84  */
   {0x75,       0x55,      0x15,        ALT_U,      0   }, /* 85  */
   {0x76,       0x56,      0x16,        ALT_V,      0   }, /* 86  */
   {0x77,       0x57,      0x17,        ALT_W,      0   }, /* 87  */
   {0x78,       0x58,      0x18,        ALT_X,      0   }, /* 88  */
   {0x79,       0x59,      0x19,        ALT_Y,      0   }, /* 89  */
   {0x7A,       0x5A,      0x1A,        ALT_Z,      0   }, /* 90  */
   {0,          0,         0,           0,          0   }, /* 91  vkLWIN    */
   {0,          0,         0,           0,          0   }, /* 92  vkRWIN    */
   {0,          0,         0,           0,          0   }, /* 93  vkAPPS    */
   {0,          0,         0,           0,          0   }, /* 94  */
   {0,          0,         0,           0,          0   }, /* 95  */
   {0x30,       0,         CTL_PAD0,    ALT_PAD0,   0   }, /* 96  vkNUMPAD0 */
   {0x31,       0,         CTL_PAD1,    ALT_PAD1,   0   }, /* 97  vkNUMPAD1 */
   {0x32,       0,         CTL_PAD2,    ALT_PAD2,   0   }, /* 98  vkNUMPAD2 */
   {0x33,       0,         CTL_PAD3,    ALT_PAD3,   0   }, /* 99  vkNUMPAD3 */
   {0x34,       0,         CTL_PAD4,    ALT_PAD4,   0   }, /* 100 vkNUMPAD4 */
   {0x35,       0,         CTL_PAD5,    ALT_PAD5,   0   }, /* 101 vkNUMPAD5 */
   {0x36,       0,         CTL_PAD6,    ALT_PAD6,   0   }, /* 102 vkNUMPAD6 */
   {0x37,       0,         CTL_PAD7,    ALT_PAD7,   0   }, /* 103 vkNUMPAD7 */
   {0x38,       0,         CTL_PAD8,    ALT_PAD8,   0   }, /* 104 vkNUMPAD8 */
   {0x39,       0,         CTL_PAD9,    ALT_PAD9,   0   }, /* 105 vkNUMPAD9 */
   {PADSTAR,   SHF_PADSTAR,CTL_PADSTAR, ALT_PADSTAR,999 }, /* 106 vkMULTIPLY*/
   {PADPLUS,   SHF_PADPLUS,CTL_PADPLUS, ALT_PADPLUS,999 }, /* 107 vkADD     */
   {0,          0,         0,           0,          0   }, /* 108 vkSEPARATOR     */
   {PADMINUS, SHF_PADMINUS,CTL_PADMINUS,ALT_PADMINUS,999}, /* 109 vkSUBTRACT*/
   {0x2E,       0,         CTL_PADSTOP, ALT_PADSTOP,0   }, /* 110 vkDECIMAL */
   {PADSLASH,  SHF_PADSLASH,CTL_PADSLASH,ALT_PADSLASH,2 }, /* 111 vkDIVIDE  */
   {KEY_F(1),   KEY_F(13), KEY_F(25),   KEY_F(37),  0   }, /* 112 vkF1      */
   {KEY_F(2),   KEY_F(14), KEY_F(26),   KEY_F(38),  0   }, /* 113 vkF2      */
   {KEY_F(3),   KEY_F(15), KEY_F(27),   KEY_F(39),  0   }, /* 114 vkF3      */
   {KEY_F(4),   KEY_F(16), KEY_F(28),   KEY_F(40),  0   }, /* 115 vkF4      */
   {KEY_F(5),   KEY_F(17), KEY_F(29),   KEY_F(41),  0   }, /* 116 vkF5      */
   {KEY_F(6),   KEY_F(18), KEY_F(30),   KEY_F(42),  0   }, /* 117 vkF6      */
   {KEY_F(7),   KEY_F(19), KEY_F(31),   KEY_F(43),  0   }, /* 118 vkF7      */
   {KEY_F(8),   KEY_F(20), KEY_F(32),   KEY_F(44),  0   }, /* 119 vkF8      */
   {KEY_F(9),   KEY_F(21), KEY_F(33),   KEY_F(45),  0   }, /* 120 vkF9      */
   {KEY_F(10),  KEY_F(22), KEY_F(34),   KEY_F(46),  0   }, /* 121 vkF10     */
   {KEY_F(11),  KEY_F(23), KEY_F(35),   KEY_F(47),  0   }, /* 122 vkF11     */
   {KEY_F(12),  KEY_F(24), KEY_F(36),   KEY_F(48),  0   }, /* 123 vkF12     */

   /* 124 through 218 */

   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},

   {0x5B,       0x7B,      0x1B,        ALT_LBRACKET,0  }, /* 219 */
   {0x5C,       0x7C,      0x1C,        ALT_BSLASH, 0   }, /* 220 */
   {0x5D,       0x7D,      0x1D,        ALT_RBRACKET,0  }, /* 221 */
   {0,          0,         0x27,        ALT_FQUOTE, 0   }, /* 222 */
   {0,          0,         0,           0,          0   }, /* 223 */
   {0,          0,         0,           0,          0   }, /* 224 */
   {0,          0,         0,           0,          0   }  /* 225 */
};

//------------------------------------------------------------------------------
static KPTAB ext_kptab[] =
{
   {0,          0,              0,              0,          }, /* MUST BE EMPTY */
   {PADENTER,   SHF_PADENTER,   CTL_PADENTER,   ALT_PADENTER}, /* 13 */
   {PADSLASH,   SHF_PADSLASH,   CTL_PADSLASH,   ALT_PADSLASH}, /* 111 */
   {KEY_PPAGE,  KEY_SPREVIOUS,  CTL_PGUP,       ALT_PGUP    }, /* 33 */
   {KEY_NPAGE,  KEY_SNEXT,      CTL_PGDN,       ALT_PGDN    }, /* 34 */
   {KEY_END,    KEY_SEND,       CTL_END,        ALT_END     }, /* 35 */
   {KEY_HOME,   KEY_SHOME,      CTL_HOME,       ALT_HOME    }, /* 36 */
   {KEY_LEFT,   KEY_SLEFT,      CTL_LEFT,       ALT_LEFT    }, /* 37 */
   {KEY_UP,     KEY_SUP,        CTL_UP,         ALT_UP      }, /* 38 */
   {KEY_RIGHT,  KEY_SRIGHT,     CTL_RIGHT,      ALT_RIGHT   }, /* 39 */
   {KEY_DOWN,   KEY_SDOWN,      CTL_DOWN,       ALT_DOWN    }, /* 40 */
   {KEY_IC,     KEY_SIC,        CTL_INS,        ALT_INS     }, /* 45 */
   {KEY_DC,     KEY_SDC,        CTL_DEL,        ALT_DEL     }, /* 46 */
   {PADSLASH,   SHF_PADSLASH,   CTL_PADSLASH,   ALT_PADSLASH}, /* 191 */
};

/* End of kptab[] */

//------------------------------------------------------------------------------
unsigned long PDC_get_input_fd( void )
{
	__QCS_FCONTEXT( "PDC_get_input_fd" );
    return 0L;
}

//------------------------------------------------------------------------------
void PDC_set_keyboard_binary( bool on )
{
	__QCS_FCONTEXT( "PDC_set_keyboard_binary" );
}

//------------------------------------------------------------------------------
// check if a key or mouse event is waiting
bool PDC_check_key( void )
{
	__QCS_FCONTEXT( "PDC_check_key" );

    if (key_count > 0)
        return TRUE;

	nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->GetNumberOfInputEvents( event_count );

    return (event_count != 0);
}

/* _get_key_count returns 0 if save_ip doesn't contain an event which
   should be passed back to the user. This function filters "useless"
   events.

   The function returns the number of keys waiting. This may be > 1
   if the repetition of real keys pressed so far are > 1.

   Returns 0 on NUMLOCK, CAPSLOCK, SCROLLLOCK.

   Returns 1 for SHIFT, ALT, CTRL only if no other key has been pressed
   in between, and SP->return_key_modifiers is set; these are returned
   on keyup.

   Normal keys are returned on keydown only. The number of repetitions
   are returned. Dead keys (diacritics) are omitted. See below for a
   description.
*/
//------------------------------------------------------------------------------
static int _get_key_count( void )
{
	__QCS_FCONTEXT( "_get_key_count" );

    int num_keys = 0, vk;

    vk = KEV.wVirtualKeyCode;

    if( KEV.bKeyDown )
    {
        /* key down */

        save_press = 0;

		if( vk == nsWin32::CKeyboard::vkCAPITAL || vk == nsWin32::CKeyboard::vkNUMLOCK || vk == nsWin32::CKeyboard::vkSCROLL )
        {
            /* throw away these modifiers */
        }
        else if( vk == nsWin32::CKeyboard::vkSHIFT || vk == nsWin32::CKeyboard::vkCONTROL || vk == nsWin32::CKeyboard::vkMENU )
        {
            /* These keys are returned on keyup only. */

            save_press = vk;
			//TODO:nsWin32::CKeyboard* pKeyboard = ( (nsWin32::CSystem::TheSystem().Keyboard()).operator nsWin32::CKeyboard *() );
            switch( vk )
            {
            case nsWin32::CKeyboard::vkSHIFT:
				//TODO:left_key = pKeyboard->Ref(QOR_PP_SHARED_OBJECT_ACCESS).GetKeyState(nsWin32::CKeyboard::vkLSHIFT);
                break;
            case nsWin32::CKeyboard::vkCONTROL:
				//TODO:left_key = pKeyboard->Ref(QOR_PP_SHARED_OBJECT_ACCESS).GetKeyState(nsWin32::CKeyboard::vkLCONTROL);
                break;
            case nsWin32::CKeyboard::vkMENU:
				//TODO:left_key = pKeyboard->Ref(QOR_PP_SHARED_OBJECT_ACCESS).GetKeyState(nsWin32::CKeyboard::vkLMENU);
				break;
            }
        }
        else
        {
            /* Check for diacritics. These are dead keys. Some locales 
               have modified characters like umlaut-a, which is an "a" 
               with two dots on it. In some locales you have to press a 
               special key (the dead key) immediately followed by the 
               "a" to get a composed umlaut-a. The special key may have 
               a normal meaning with different modifiers. */

            //TODO:if( KEV.uChar.UnicodeChar || !( nsWin32::CSystem::TheSystem().Keyboard()->Ref(QOR_PP_SHARED_OBJECT_ACCESS).MapVKey( vk, 2 ) & 0x80000000 ) )
			{
                num_keys = KEV.wRepeatCount;
			}
        }
    }
    else
    {
        /* key up */

        /* Only modifier keys or the results of ALT-numpad entry are
           returned on keyup */

        if ((vk == nsWin32::CKeyboard::vkMENU && KEV.uChar.UnicodeChar) ||
           ((vk == nsWin32::CKeyboard::vkSHIFT || vk == nsWin32::CKeyboard::vkCONTROL || vk == nsWin32::CKeyboard::vkMENU) &&
             vk == save_press))
        {
            save_press = 0;
            num_keys = 1;
        }
    }

    PDC_LOG(("_get_key_count() - returning: num_keys %d\n", num_keys));

    return num_keys;
}

//------------------------------------------------------------------------------
/* _process_key_event returns -1 if the key in save_ip should be
   ignored. Otherwise it returns the keycode which should be returned
   by PDC_get_key(). save_ip must be a key event.

   CTRL-ALT support has been disabled, when is it emitted plainly?  */
static int _process_key_event( void )
{
	__QCS_FCONTEXT( "_process_key_event" );

    int key = (unsigned short)KEV.uChar.UnicodeChar;
    unsigned short vk = KEV.wVirtualKeyCode;
    unsigned long state = KEV.dwControlKeyState;

    int idx;
    bool enhanced;

    SP->key_code = TRUE;

    /* Save the key modifiers if required. Do this first to allow to
       detect e.g. a pressed CTRL key after a hit of NUMLOCK. */

    if (SP->save_key_modifiers)
    {
		if (state & ( nsWin32::Left_Alt_Pressed | nsWin32::Right_Alt_Pressed ))
            pdc_key_modifiers |= PDC_KEY_MODIFIER_ALT;

		if (state & nsWin32::Shift_Pressed )
            pdc_key_modifiers |= PDC_KEY_MODIFIER_SHIFT;

		if ( state & ( nsWin32::Left_Ctrl_Pressed | nsWin32::Right_Ctrl_Pressed ) )
            pdc_key_modifiers |= PDC_KEY_MODIFIER_CONTROL;

        if ( state & nsWin32::NumLock_On )
            pdc_key_modifiers |= PDC_KEY_MODIFIER_NUMLOCK;
    }

    /* Handle modifier keys hit by themselves */

    switch (vk)
    {
    case nsWin32::CKeyboard::vkSHIFT: /* shift */
        if (!SP->return_key_modifiers)
            return -1;

        return (left_key & 0x8000) ? KEY_SHIFT_L : KEY_SHIFT_R;

    case nsWin32::CKeyboard::vkCONTROL: /* control */
        if (!SP->return_key_modifiers)
            return -1;

        return (left_key & 0x8000) ? KEY_CONTROL_L : KEY_CONTROL_R;

    case nsWin32::CKeyboard::vkMENU: /* alt */
        if (!key)
        {
            if (!SP->return_key_modifiers)
                return -1;

            return (left_key & 0x8000) ? KEY_ALT_L : KEY_ALT_R;
        }
    }

    /* The system may emit Ascii or Unicode characters depending on
       whether ReadConsoleInputA or ReadConsoleInputW is used.

       Normally, if key != 0 then the system did the translation
       successfully. But this is not true for LEFT_ALT (different to
       RIGHT_ALT). In case of LEFT_ALT we can get key != 0. So
       check for this first. */

	if (key && ( !(state & nsWin32::Left_Alt_Pressed ) || (state & nsWin32::Right_Alt_Pressed) ))
    {
        /* This code should catch all keys returning a printable
           character. Characters above 0x7F should be returned as
           positive codes. But if'ndef NUMKEYPAD we have to return
           extended keycodes for keypad codes. */

#ifndef NUMKEYPAD
        if (kptab[vk].extended == 0)
#endif
        {
            SP->key_code = FALSE;
            return key;
        }
    }

    /* This case happens if a functional key has been entered. */

	if ((state & nsWin32::Enhanced_Key ) && (kptab[vk].extended != 999))
    {
        enhanced = TRUE;
        idx = kptab[vk].extended;
    }
    else
    {
        enhanced = FALSE;
        idx = vk;
    }

	if (state & nsWin32::Shift_Pressed )
        key = enhanced ? ext_kptab[idx].shift : kptab[idx].shift;

	else if (state & ( nsWin32::Left_Ctrl_Pressed | nsWin32::Right_Ctrl_Pressed ) )
        key = enhanced ? ext_kptab[idx].control : kptab[idx].control;

	else if (state & ( nsWin32::Left_Alt_Pressed | nsWin32::Right_Alt_Pressed ) )
        key = enhanced ? ext_kptab[idx].alt : kptab[idx].alt;

    else
        key = enhanced ? ext_kptab[idx].normal : kptab[idx].normal;

    if (key < KEY_CODE_YES)
        SP->key_code = FALSE;

    return key;
}

//------------------------------------------------------------------------------
static int _process_mouse_event( void )
{
	__QCS_FCONTEXT( "_process_mouse_event" );
    static const unsigned long button_mask[] = {1, 4, 2};
    short action, shift_flags = 0;
    int i;

    save_press = 0;
    SP->key_code = TRUE;

    memset(&pdc_mouse_status, 0, sizeof(MOUSE_STATUS));

    /* Handle scroll wheel */

    if (MEV.dwEventFlags == 4)
    {
        pdc_mouse_status.changes = (MEV.dwButtonState & 0xFF000000) ?
            PDC_MOUSE_WHEEL_DOWN : PDC_MOUSE_WHEEL_UP;

        pdc_mouse_status.x = -1;
        pdc_mouse_status.y = -1;

        memset(&old_mouse_status, 0, sizeof(old_mouse_status));

        return KEY_MOUSE;
    }

    action = (MEV.dwEventFlags == 2) ? BUTTON_DOUBLE_CLICKED :
            ((MEV.dwEventFlags == 1) ? BUTTON_MOVED : BUTTON_PRESSED);

    for (i = 0; i < 3; i++)
        pdc_mouse_status.button[i] =
            (MEV.dwButtonState & button_mask[i]) ? action : 0;

    if (action == BUTTON_PRESSED && MEV.dwButtonState & 7 && SP->mouse_wait)
    {
        /* Check for a click -- a PRESS followed immediately by a release */

        if (!event_count)
        {
            napms(SP->mouse_wait);
			nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->GetNumberOfInputEvents( event_count );
            //GetNumberOfConsoleInputEvents(pdc_con_in, &event_count);
        }

        if (event_count)
        {
			nsCodeQOR::CTArray< nsWin32::InputRecord, CWinQLPolicy > ip( 1 );
            unsigned long count;
            bool have_click = FALSE;

			nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->PeekInput( ip, count );
            //PeekConsoleInput(pdc_con_in, &ip, 1, &count);

            for (i = 0; i < 3; i++)
            {
                if (pdc_mouse_status.button[i] == BUTTON_PRESSED &&
                    !(ip[ 0 ].Event.MouseEvent.dwButtonState & button_mask[i]))
                {
                    pdc_mouse_status.button[i] = BUTTON_CLICKED;
                    have_click = TRUE;
                }
            }

            /* If a click was found, throw out the event */

            if (have_click)
			{
				nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->ReadInput( ip, count );
			}
        }
    }

    pdc_mouse_status.x = MEV.dwMousePosition.X;
    pdc_mouse_status.y = MEV.dwMousePosition.Y;

    pdc_mouse_status.changes = 0;

    for (i = 0; i < 3; i++)
    {
        if (old_mouse_status.button[i] != pdc_mouse_status.button[i])
            pdc_mouse_status.changes |= (1 << i);

        if (pdc_mouse_status.button[i] == BUTTON_MOVED)
        {
            /* Discard non-moved "moves" */

            if (pdc_mouse_status.x == old_mouse_status.x &&
                pdc_mouse_status.y == old_mouse_status.y)
                return -1;

            /* Motion events always flag the button as changed */

            pdc_mouse_status.changes |= (1 << i);
            pdc_mouse_status.changes |= PDC_MOUSE_MOVED;
            break;
        }
    }

    old_mouse_status = pdc_mouse_status;

    /* Treat click events as release events for comparison purposes */

    for (i = 0; i < 3; i++)
    {
        if (old_mouse_status.button[i] == BUTTON_CLICKED ||
            old_mouse_status.button[i] == BUTTON_DOUBLE_CLICKED)
            old_mouse_status.button[i] = BUTTON_RELEASED;
    }

    /* Check for SHIFT/CONTROL/ALT */

    if( MEV.dwControlKeyState & ( nsWin32::Left_Alt_Pressed | nsWin32::Right_Alt_Pressed ) )
	{
        shift_flags |= BUTTON_ALT;
	}

	if( MEV.dwControlKeyState & ( nsWin32::Left_Ctrl_Pressed | nsWin32::Right_Ctrl_Pressed ) )
	{
        shift_flags |= BUTTON_CONTROL;
	}

	if( MEV.dwControlKeyState & nsWin32::Shift_Pressed )
	{
        shift_flags |= BUTTON_SHIFT;
	}

    if (shift_flags)
    {
        for (i = 0; i < 3; i++)
        {
            if (pdc_mouse_status.changes & (1 << i))
                pdc_mouse_status.button[i] |= shift_flags;
        }
    }

    return KEY_MOUSE;
}


//------------------------------------------------------------------------------
// return the next available key or mouse event 
int PDC_get_key(void)
{
	__QCS_FCONTEXT( "PDC_get_key" );

    pdc_key_modifiers = 0L;

    if (!key_count)
    {
        unsigned long count;

		nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->ReadInput( save_ip, count );

        event_count--;

		if (save_ip[0].EventType == nsWin32::Mouse_Event )
		{
            key_count = 1;
		}
		else if (save_ip[0].EventType == nsWin32::Key_Event )
		{
            key_count = _get_key_count();
		}
    }

    if (key_count)
    {
        key_count--;

        switch (save_ip[0].EventType)
        {
		case nsWin32::Key_Event:
            return _process_key_event();

		case nsWin32::Mouse_Event:
            return _process_mouse_event();
        }
    }

    return -1;
}

//------------------------------------------------------------------------------
// discard any pending keyboard or mouse input -- this is the core routine for flushinp()
void PDC_flushinp(void)
{
    __QCS_FCONTEXT( "PDC_flushinp" );

	nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->FlushInputBuffer();	
}

//------------------------------------------------------------------------------
int PDC_mouse_set(void)
{
	__QCS_FCONTEXT( "PDC_mouse_set" );
    /* If turning on mouse input: Set ENABLE_MOUSE_INPUT, and clear 
       all other flags, including the extended flags;
       If turning off the mouse: Set QuickEdit Mode to the status it 
       had on startup, and clear all other flags */

	nsWin32::CConsole::TheWin32Console()->ScreenBuffer()->SetInputMode( SP->_trap_mbe ? ( nsWin32::CConsole::Mouse_Input | 0x0080 ) : ( pdc_quick_edit | 0x0080 ) );

    memset(&old_mouse_status, 0, sizeof(old_mouse_status));

    return nsWin32::OK;
}

//------------------------------------------------------------------------------
int PDC_modifiers_set(void)
{
	__QCS_FCONTEXT( "PDC_modifiers_set" );
    return nsWin32::OK;
}
