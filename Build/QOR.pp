//This BuildQOR project definition file is C preprocessor script from which 
//BuildQOR will generate Shell scripts to build variants of the project

//Start by defining the project. 

//This must be an exact match of this file's filename without extension
#define QOR_PROJECT QOR

//Include the shell script template to begin a project
#include "ProjectHeader.sth"

//Define the targets for which to build  this project
//((X86_32)(SANOS)(0))
//((X86_64)(MSW)(WIN10))
#define QOR_TARGETS ((X86_32)(MSW)(WIN10))

//Define build forms for each way of linking the project
//The names can be anything but must be matched by a .pp file under a folder named by QOR_PROJECT e.g. QOR\Modular.pp
//(Monolithic)
#define QOR_FORMS (Modular)
//Specialize QOR_FORMS so that on Windows we only build Modular
#define QOR_FORMS_MSW (Modular)

//Define the project configurations to build. Each must match a Config.h configuration header e.g. DefaultConfig.h
//(ASCII)
#define QOR_CONFIGS (Unicode)

//TODO: Make these specializations override QOR CONFIGS
#define QOR_CONFIGS_SANOS (ASCII)
#define QOR_CONFIGS_X86_64 (Unicode)

//Define the types of build to preform. Levels of debugging info vs optimization
#define QOR_TYPES \
		(Debug)
//(Release)

//Include the BuildQOR script to build the targets		
#include "BuildQOR/BuildTargets.pph"
