//Projects.pp
//A Shell and compiler neutral preprocessor file which provides the list of overall projects to BuildQOR
//A Project is all the ways to build a related set of binaries
//Each project name references a .pp project build script in the same folder as this file
//Example: Adding (Magnificent) to the definition of QOR_PROJECTS implies the presence of Magnificent.pp

#define QOR_PROJECTS\
		(QOR)

#include "BuildQOR/BuildProjects.pph"
