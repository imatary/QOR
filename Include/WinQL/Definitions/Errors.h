//Errors.h

// Copyright Querysoft Limited 2013
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

//Error codes for use with the Microsoft Windows Operating System
//NOTE: This is clearly very incomplete at Strata-1, > 30000 Windows error codes are known to exist

#ifndef WINQL_ERRORS_H_1
#define WINQL_ERRORS_H_1

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

//--------------------------------------------------------------------------------
namespace nsWin32
{	
	__QCMP_STATIC_CONSTANT( long, OK = 0 );
	__QCMP_STATIC_CONSTANT( long, S_False = 1 );
	__QCMP_STATIC_CONSTANT( long, Success = 0L );
	__QCMP_STATIC_CONSTANT( long, NoError = 0L );
	__QCMP_STATIC_CONSTANT( long, ErrorInvalidFunction				= 1L );
	__QCMP_STATIC_CONSTANT( long, ErrorFileNotFound					= 2L );
	__QCMP_STATIC_CONSTANT( long, ErrorPathNotFound					= 3L );
	__QCMP_STATIC_CONSTANT( long, ErrorTooManyOpenFiles				= 4L );
	__QCMP_STATIC_CONSTANT( long, ErrorAccessDenied					= 5L );
	__QCMP_STATIC_CONSTANT( long, ErrorInvalidHandle				= 6L );
    __QCMP_STATIC_CONSTANT( long, ErrorArenaTrashed					= 7L );
    __QCMP_STATIC_CONSTANT( long, ErrorNotEnoughMemory				= 8L );
    __QCMP_STATIC_CONSTANT( long, ErrorInvalidBlock					= 9L );
    __QCMP_STATIC_CONSTANT( long, ErrorBadEnvironment				= 10L );
    __QCMP_STATIC_CONSTANT( long, ErrorBadFormat					= 11L );
    __QCMP_STATIC_CONSTANT( long, ErrorInvalidAccess				= 12L );
    __QCMP_STATIC_CONSTANT( long, ErrorInvalidData					= 13L );
    __QCMP_STATIC_CONSTANT( long, ErrorInvalidDrive					= 15L );
    __QCMP_STATIC_CONSTANT( long, ErrorCurrentDirectory				= 16L );
    __QCMP_STATIC_CONSTANT( long, ErrorNotSameDevice				= 17L );
    __QCMP_STATIC_CONSTANT( long, ErrorNoMoreFiles					= 18L );
	__QCMP_STATIC_CONSTANT( long, ErrorWriteProtect					= 19L );

	__QCMP_STATIC_CONSTANT( long, ErrorLockViolation				= 33L );
	__QCMP_STATIC_CONSTANT( long, ErrorSharingBufferExceeded		= 36L );

	__QCMP_STATIC_CONSTANT( long, ErrorNotSupported					= 50L );
	__QCMP_STATIC_CONSTANT( long, ErrorBadNetPath					= 53L );
	__QCMP_STATIC_CONSTANT( long, ErrorNetworkAccessDenied			= 65L );
	__QCMP_STATIC_CONSTANT( long, ErrorBadNetName					= 67L );
	__QCMP_STATIC_CONSTANT( long, ErrorFileExists					= 80L );
	__QCMP_STATIC_CONSTANT( long, ErrorCannotMake					= 82L );
	__QCMP_STATIC_CONSTANT( long, ErrorFailI24						= 83L );
	__QCMP_STATIC_CONSTANT( long, ErrorInvalidParameter				= 87L );
	__QCMP_STATIC_CONSTANT( long, ErrorNoProcSlots					= 89L );

	__QCMP_STATIC_CONSTANT( long, ErrorDriveLocked					= 108L );
	__QCMP_STATIC_CONSTANT( long, ErrorBrokenPipe					= 109L );
	__QCMP_STATIC_CONSTANT( long, ErrorDiskFull						= 112L );
	__QCMP_STATIC_CONSTANT( long, ErrorInvalidTargetHandle			= 114L );
	__QCMP_STATIC_CONSTANT( long, ErrorCallNotImplemented			= 120L );
	__QCMP_STATIC_CONSTANT( long, ErrorInsufficientBuffer			= 122L );
	__QCMP_STATIC_CONSTANT( long, ErrorInvalidLevel					= 124L );
	__QCMP_STATIC_CONSTANT( long, ErrorProcNotFound					= 127L );
	__QCMP_STATIC_CONSTANT( long, ErrorWaitNoChildren				= 128L );
	__QCMP_STATIC_CONSTANT( long, ErrorChildNotComplete				= 129L );
	__QCMP_STATIC_CONSTANT( long, ErrorDirectAccessHandle			= 130L );
	__QCMP_STATIC_CONSTANT( long, ErrorNegativeSeek					= 131L );
	__QCMP_STATIC_CONSTANT( long, ErrorSeekOnDevice					= 132L );
	__QCMP_STATIC_CONSTANT( long, ErrorDirNotEmpty					= 145L );
	__QCMP_STATIC_CONSTANT( long, ErrorNotLocked					= 158L );
	__QCMP_STATIC_CONSTANT( long, ErrorBadPathName					= 161L );
	__QCMP_STATIC_CONSTANT( long, ErrorMaxThreadsReached			= 164L );
	__QCMP_STATIC_CONSTANT( long, ErrorLockFailed					= 167L );
	__QCMP_STATIC_CONSTANT( long, ErrorAlreadyExists				= 183L );
	__QCMP_STATIC_CONSTANT( long, ErrorInvalidStartingCodeSeg		= 188L );
	__QCMP_STATIC_CONSTANT( long, ErrorInfLoopInRelocChain			= 202L );
	__QCMP_STATIC_CONSTANT( long, ErrorFilenameExcedRange			= 206L );
	__QCMP_STATIC_CONSTANT( long, ErrorNestingNotAllowed			= 215L );
	__QCMP_STATIC_CONSTANT( long, ErrorPipeBusy						= 231L );
	__QCMP_STATIC_CONSTANT( long, ErrorInvalidAddress				= 487L );
	__QCMP_STATIC_CONSTANT( long, ErrorPipeConnected				= 535L );
	__QCMP_STATIC_CONSTANT( long, ErrorOperationAborted				= 995L );
	__QCMP_STATIC_CONSTANT( long, ErrorIOIncomplete					= 996L );
	__QCMP_STATIC_CONSTANT( long, ErrorIOPending					= 997L );
	__QCMP_STATIC_CONSTANT( long, ErrorNoAccess						= 998L );			//Invalid access to memory location
	__QCMP_STATIC_CONSTANT( long, ErrorNotFound						= 1168L );        
	__QCMP_STATIC_CONSTANT( long, ErrorNotEnoughQuota				= 1816L );


	__QCMP_STATIC_CONSTANT( long, E_NotImpl							= 0x80004001L );
	__QCMP_STATIC_CONSTANT( long, E_NoInterface						= 0x80004002L );
	__QCMP_STATIC_CONSTANT( long, E_Pointer							= 0x80004003L );
	__QCMP_STATIC_CONSTANT( long, E_Fail							= 0x80004005L );	// Unspecified error	
	__QCMP_STATIC_CONSTANT( long, Class_E_ClassNotAvailable			= 0x80040111L );
	__QCMP_STATIC_CONSTANT( long, E_Unexpected						= 0x8000FFFFL );
	__QCMP_STATIC_CONSTANT( long, E_OutOfMemory						= 0x8007000EL );
	__QCMP_STATIC_CONSTANT( long, E_InvalidArg						= 0x80070057L );	

#define FACILITY_XPS                     82
#define FACILITY_XAML                    43
#define FACILITY_USN                     129
#define FACILITY_BLBUI                   128
#define FACILITY_SPP                     256
#define FACILITY_WSB_ONLINE              133
#define FACILITY_DLS                     153
#define FACILITY_BLB_CLI                 121
#define FACILITY_BLB                     120
#define FACILITY_WSBAPP                  122
#define FACILITY_WPN                     62
#define FACILITY_WMAAECMA                1996
#define FACILITY_WINRM                   51
#define FACILITY_WINPE                   61
#define FACILITY_WINDOWSUPDATE           36
#define FACILITY_WINDOWS_STORE           63
#define FACILITY_WINDOWS_SETUP           48
#define FACILITY_WINDOWS_DEFENDER        80
#define FACILITY_WINDOWS_CE              24
#define FACILITY_WINDOWS                 8
#define FACILITY_WINCODEC_DWRITE_DWM     2200
#define FACILITY_WIA                     33
#define FACILITY_WER                     27
#define FACILITY_WEP                     2049
#define FACILITY_WEB_SOCKET              886
#define FACILITY_WEB                     885
#define FACILITY_USERMODE_VOLSNAP        130
#define FACILITY_USERMODE_VOLMGR         56
#define FACILITY_VISUALCPP               109
#define FACILITY_USERMODE_VIRTUALIZATION 55
#define FACILITY_USERMODE_VHD            58
#define FACILITY_URT                     19
#define FACILITY_UMI                     22
#define FACILITY_UI                      42
#define FACILITY_TPM_SOFTWARE            41
#define FACILITY_TPM_SERVICES            40
#define FACILITY_TIERING                 131
#define FACILITY_SYNCENGINE              2050
#define FACILITY_SXS                     23
#define FACILITY_STORAGE                 3
#define FACILITY_STATE_MANAGEMENT        34
#define FACILITY_SSPI                    9
#define FACILITY_USERMODE_SPACES         231
#define FACILITY_SOS                     160
#define FACILITY_SCARD                   16
#define FACILITY_SHELL                   39
#define FACILITY_SETUPAPI                15
#define FACILITY_SECURITY                9
#define FACILITY_SDIAG                   60
#define FACILITY_USERMODE_SDBUS          2305
#define FACILITY_RPC                     1
#define FACILITY_RESTORE                 256
#define FACILITY_SCRIPT                  112
#define FACILITY_PARSE                   113
#define FACILITY_RAS                     83
#define FACILITY_POWERSHELL              84
#define FACILITY_PLA                     48
#define FACILITY_PIDGENX                 2561
#define FACILITY_P2P_INT                 98
#define FACILITY_P2P                     99
#define FACILITY_OPC                     81
#define FACILITY_ONLINE_ID               134
#define FACILITY_WIN32                   7
#define FACILITY_CONTROL                 10
#define FACILITY_WEBSERVICES             61
#define FACILITY_NULL                    0
#define FACILITY_NDIS                    52
#define FACILITY_NAP                     39
#define FACILITY_MOBILE                  1793
#define FACILITY_METADIRECTORY           35
#define FACILITY_MSMQ                    14
#define FACILITY_MEDIASERVER             13
#define FACILITY_MBN                     84
#define FACILITY_LINGUISTIC_SERVICES     305
#define FACILITY_LEAP                    2184
#define FACILITY_JSCRIPT                 2306
#define FACILITY_INTERNET                12
#define FACILITY_ITF                     4
#define FACILITY_INPUT                   64
#define FACILITY_USERMODE_HYPERVISOR     53
#define FACILITY_ACCELERATOR             1536
#define FACILITY_HTTP                    25
#define FACILITY_GRAPHICS                38
#define FACILITY_FWP                     50
#define FACILITY_FVE                     49
#define FACILITY_USERMODE_FILTER_MANAGER 31
#define FACILITY_EAS                     85
#define FACILITY_EAP                     66
#define FACILITY_DXGI_DDI                2171
#define FACILITY_DXGI                    2170
#define FACILITY_DPLAY                   21
#define FACILITY_DMSERVER                256
#define FACILITY_DISPATCH                2
#define FACILITY_DIRECTORYSERVICE        37
#define FACILITY_DIRECTMUSIC             2168
#define FACILITY_DIRECT3D11              2172
#define FACILITY_DIRECT3D10              2169
#define FACILITY_DIRECT2D                2201
#define FACILITY_DAF                     100
#define FACILITY_DEPLOYMENT_SERVICES_UTIL 260
#define FACILITY_DEPLOYMENT_SERVICES_TRANSPORT_MANAGEMENT 272
#define FACILITY_DEPLOYMENT_SERVICES_TFTP 264
#define FACILITY_DEPLOYMENT_SERVICES_PXE 263
#define FACILITY_DEPLOYMENT_SERVICES_MULTICAST_SERVER 289
#define FACILITY_DEPLOYMENT_SERVICES_MULTICAST_CLIENT 290
#define FACILITY_DEPLOYMENT_SERVICES_MANAGEMENT 259
#define FACILITY_DEPLOYMENT_SERVICES_IMAGING 258
#define FACILITY_DEPLOYMENT_SERVICES_DRIVER_PROVISIONING 278
#define FACILITY_DEPLOYMENT_SERVICES_SERVER 257
#define FACILITY_DEPLOYMENT_SERVICES_CONTENT_PROVIDER 293
#define FACILITY_DEPLOYMENT_SERVICES_BINLSVC 261
#define FACILITY_DEFRAG                  2304
#define FACILITY_DEBUGGERS               176
#define FACILITY_CONFIGURATION           33
#define FACILITY_COMPLUS                 17
#define FACILITY_USERMODE_COMMONLOG      26
#define FACILITY_CMI                     54
#define FACILITY_CERT                    11
#define FACILITY_BLUETOOTH_ATT           101
#define FACILITY_BCD                     57
#define FACILITY_BACKGROUNDCOPY          32
#define FACILITY_AUDIOSTREAMING          1094
#define FACILITY_AUDCLNT                 2185
#define FACILITY_AUDIO                   102
#define FACILITY_ACTION_QUEUE            44
#define FACILITY_ACS                     20
#define FACILITY_AAF                     18

	// DllRegisterServer/DllUnregisterServer status codes
#define SEVERITY_SUCCESS			0
#define SEVERITY_ERROR				1
#define SELFREG_E_FIRST				MakeSCode( SEVERITY_ERROR,   FACILITY_ITF, 0x0200 )
#define SELFREG_E_LAST				MakeSCode( SEVERITY_ERROR,   FACILITY_ITF, 0x020F )
#define SELFREG_S_FIRST				MakeSCode( SEVERITY_SUCCESS, FACILITY_ITF, 0x0200 )
#define SELFREG_S_LAST				MakeSCode( SEVERITY_SUCCESS, FACILITY_ITF, 0x020F )
#define SELFREG_E_TYPELIB           (SELFREG_E_FIRST+0)		// failed to register/unregister type library
#define SELFREG_E_CLASS             (SELFREG_E_FIRST+1)

}//nsWin32

#endif//WINQL_ERRORS_H_1