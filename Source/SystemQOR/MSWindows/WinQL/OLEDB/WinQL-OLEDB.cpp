//WinQL-OLEDB.cpp

// Copyright Querysoft Limited 2015
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

#include "WinQL/WinQL.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "CodeQOR/DataTypes/GUID.h"
#include "CodeQOR.h"

//------------------------------------------------------------------------------
//Only for shared library builds as one of a network of Dlls
#if ( !defined(QOR_MONOLITHIC) && defined(_USRDLL))

__QCMP_STARTLINKAGE_C

//------------------------------------------------------------------------------
//This provides a unique identifier for the WinQL-OLEDB QOR Library. 
//The presence of this entry point identifies WinQL-OLEDB as a QOR library with delayed
//static initialization and an accessible Module Context
__QCMP_EXPORT nsCodeQOR::mxGUID* QORidentity( void )
{
	// {D464C2A3-6F8C-4557-99C9-9CEEED9535D2}
	static nsCodeQOR::mxGUID WinQL_OLEDB = { 0xd464c2a3, 0x6f8c, 0x4557,{ 0x99, 0xc9, 0x9c, 0xee, 0xed, 0x95, 0x35, 0xd2 } };
	return &WinQL_OLEDB;
}

__QCMP_ENDLINKAGE_C

//------------------------------------------------------------------------------
//Provide a Module Context that represents the WinQL-OLEDB DLL
nsCodeQOR::CLoadableModuleBase& ThisModule( void )
{
	static nsCodeQOR::CLoadableModuleBase WinQLModule( "Querysoft Open Runtime OLE DB class library for Microsoft Windows" );
	return WinQLModule;
}

#endif//( !defined(QOR_MONOLITHIC) && defined(_USRDLL))
