//WinPosum.cpp

#include "CodeQOR/DataTypes/GUID.h"
#include "CodeQOR/Modules/LoadableModuleBase.h"

//------------------------------------------------------------------------------
//Only for shared library builds as a network of Dlls
#ifndef QOR_MONOLITHIC
#ifdef _USRDLL

__QCMP_STARTLINKAGE_C

extern int _cdecl QORStaticInit( void );

//------------------------------------------------------------------------------
__QCMP_EXPORT int _cdecl QORinit( void )
{
	QORStaticInit();
	return 1;
}

//------------------------------------------------------------------------------
__QCMP_EXPORT nsCodeQOR::mxGUID* QORidentity(void)
{
	// {BC26D453-1662-43F1-8C95-FA27B1F5298F}
	static nsCodeQOR::mxGUID WinPosumQOR = { 0xbc26d453, 0x1662, 0x43f1, { 0x8c, 0x95, 0xfa, 0x27, 0xb1, 0xf5, 0x29, 0x8f } };
	return &WinPosumQOR;
}

__QCMP_ENDLINKAGE_C

//------------------------------------------------------------------------------
nsCodeQOR::CLoadableModuleBase& ThisModule(void)
{
	static nsCodeQOR::CLoadableModuleBase CQORModule("Querysoft Open Runtime Windows Posix Object library");
	return CQORModule;
}

//------------------------------------------------------------------------------
const char* __QCMP_LOCAL ThisModuleVersion(void)
{
	return QOR_PP_STRINGIZE(__DATE__:__TIME__);
}

#endif//_USRDLL
#endif//QOR_MONOLITHIC
