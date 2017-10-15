//AppocritaQOR.pp

// Copyright Querysoft Limited 2016
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

//Preprocessor build script generator for AppocritaQOR.dll

#include "ModuleHeader.pph"

//Set AppocritaQOR specific definitions and overrides

#define QOR_MODULE_NAME AppocritaQOR

//Append the module specific PP defines to the list from the Operating System
#define QOR_CONFIG_DEFINES_APPOCRITAQOR1 QOR_PP_LIST_APPEND( QOR_CONFIG_DEFINES_OS,("_LIBCPP_DLL") )
#define QOR_CONFIG_DEFINES_APPOCRITAQOR2 QOR_PP_LIST_APPEND( QOR_CONFIG_DEFINES_APPOCRITAQOR1,("_APPOCRITA") )
#define QOR_CONFIG_DEFINES_MODULE QOR_CONFIG_DEFINES_APPOCRITAQOR2

#define QOR_CONFIG_INCLUDES (../../../include)\
(C:\Program Files (x86)\Windows Kits\8.1\Include\um)\
(C:\Program Files (x86)\Windows Kits\8.1\Include\shared)\
(C:\Program Files (x86)\Windows Kits\8.1\Include\winrt)

#define QOR_PP_BUILD_CMP_IGNORE_STANDARD_INC_SELECT 1
#define QOR_PP_BUILD_CMP_CPP_EXCEPTIONS_SELECT 1
#define QOR_PP_BUILD_CMP_BUFFER_SECURITY_SELECT 1
#define QOR_PP_BUILD_CMP_RUNTIME_CHECKS_SELECT 4

//Include this to do any setup needed for a build such as creating folders
#include "BuildQOR/BeginBuild.pph"

//For each group of files that have the same folder and build options, define a group of sources

#define SOURCE_PATH ../../../Source/AppocritaQOR/
#define SOURCES (AppocritaQOR)\
				(Application)\
				(Controller)\
				(Role)\
				(Event)\
				(State)\
				(SubSystem)\
				(Workflow)
#include "BuildQOR/BuildGroup.pph"

#define SOURCE_PATH ../../../Source/AppocritaQOR/Workflows/
#define SOURCES (CmdLineIPOWorkflow)
#include "BuildQOR/BuildGroup.pph"

#define SOURCE_PATH ../../../Source/AppocritaQOR/SubSystems/
#define SOURCES (Threading)\
				(Thread)\
				(Bluetooth)\
				(Networking)
#include "BuildQOR/BuildGroup.pph"

#define SOURCE_PATH ../../../Source/AppocritaQOR/Applications/
#define SOURCES (CmdLineApp)
#include "BuildQOR/BuildGroup.pph"

//Generate the export and import libraries for the module where the linker will require them
#include "LibCmd2.pph"

