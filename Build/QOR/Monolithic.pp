//QOR Strata Monolithic build file
//Build QOR as a single binary
#define QOR_MONOLITHIC
#include "BuildQOR/PreBuild.pph"
		
#define QOR_LIBS \
		(WinCmpSupQORVC)\
		(WinUsrExeBootCon)\
		(WinUsrExeBootWin)
		
#define QOR_MODULES \
		(QORStrata1)
		
#define QOR_APPLICATIONS \
		(TeaForTwo)

//#include "BuildQOR/BuildLibraries.pph"
#include "BuildQOR/BuildModules.pph"
#include "BuildQOR/BuildApplications.pph"
