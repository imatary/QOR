//This BuildQOR project definition file is C preprocessor script from which 
//BuildQOR will generate Shell scripts to build variants of the project

//Start by defining the project. 

//This must be an exact match of this file's filename without extension
#define QOR_PROJECT QOR

//Include the shell script template to begin a project
#include "ProjectHeader.sth"

//Define the targets for which to build  this project
#define QOR_TARGETS ((x86)(MSWindows)(Win95))\
					((x86)(MSWindows)(WinXP))\
					((x64)(MSWindows)(Win10))

//Define build forms for each way of linking the project
#define QOR_FORMS \
		(Modular)\
		(Monolithic)

//Define the project configurations to build. Each must match a .h configuration header
#define QOR_CONFIGS (Default)

//Define the types of build to preform. Levels of debugging info vs optimization
#define QOR_TYPES \
		(Debug)\
		(Release)

//Include the BuildQOR script to build the targets		
#include "BuildQOR/BuildTargets.pph"
