//QORModule.pp

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

//Preprocessor build script generator for QORModule.lib

#include "LibraryHeader.pph"

//Set QORModule specific definitions and overrides

//Append the library specific PP defines to the list from the Operating System
#define QOR_CONFIG_DEFINES_USESLIBCPP QOR_PP_LIST_APPEND( QOR_CONFIG_DEFINES_OS,("_LIBCPP_DLL") )
#define QOR_CONFIG_DEFINES_MODULE QOR_CONFIG_DEFINES_USESLIBCPP

#define QOR_LIB_NAME QORModule
#define QOR_MODULE_NAME QORModule

#define QOR_CONFIG_INCLUDES (../../../include)\
(../../Source/SystemQOR/MSWindows/WinCmpSupQORVC/include/Exceptions/SEH)\
(C:\Program Files (x86)\Windows Kits\8.1\Include\um)\
(C:\Program Files (x86)\Windows Kits\8.1\Include\shared)\
(C:\Program Files (x86)\Windows Kits\8.1\Include\winrt)

//Include this to do any setup needed for a build such as creating folders
#include "BuildQOR/BeginBuild.pph"

//For each group of files that have the same folder and build options, define a group of sources

#define SOURCE_PATH ../../../Source/CodeQOR/Modules/
#define SOURCES (LibraryBase)
#include "BuildQOR/BuildGroup.pph"

//Define the paths to look on for link time static dependencies
#define QOR_LIB_PATHS (.)

//Define the list of link time static dependencies 
#define QOR_LIBS

//Include this to link the outputs of the translation units compiled above into a static library
#include "BuildQOR/BuildStaticLib.pph"

