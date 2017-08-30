//Modular.pp
//QOR Modular build preprocessor script file
//Use this file to define the libs, modules and applications that are built for this project
#undef QOR_MONOLITHIC
		
//Each library name listed here implies a .pp file in this folder defining the library build e.g. WinSharedBootstrap.pp which will build WinSharedBootstrap.lib
#define QOR_LIBS (WinCmpSupQORVC)\
		(QORModule)\
		(WinSharedBootstrap)\
		(WinUsrExeBootCon)\
		(WinUsrExeBootWin)
		
//Each module name listed here implies a .pp file in this folder defining the compile phase for a shared library e.g. CompilerQOR.pp which will compile CompilerQOR
//and a second *Link.pp file which defines the link phase e.g. CompilerQORLink.pp which will link CompilerQOR.dll
#define QOR_MODULES (CodeQOR)(ArchQOR)(CompilerQOR)(SystemQOR)(CQOR)(stdQOR)(PosumQOR)(WinPosumQOR)(MonkiQOR)(AppocritaQOR)(MammutQOR)(BluefootQOR)(WINQAPI)(WinQL)(WinQLGUI)(WinQLCOM)

//Each executable name listed here implies a .pp file in this folder defining a build  e.g. TeaForTwo.pp which will build TeaForTwo.exe
#define QOR_APPLICATIONS\
		(Fandango)\
		(Qosh)\
		(TeaForTwo)\
		(CodeQORTest)\
		(Winner)


#include "BuildQOR/BuildLibraries.pph"
#include "BuildQOR/BuildModules.pph"
#include "BuildQOR/BuildApplications.pph"
