README_Folder.txt

Describes the content of and any rules for the containing folder.

Strata:		1
Path:		/Strata-1/SystemQOR/MSWindows/WinSharedBootstrap
Purpose:	Provides a Windows specific bootstrap library for shared libraries (DLLs)
		A static library WinSharedBootStrap.lib is built from these sources and the linked into each QOR DLL.
		If you write a library that links with the QOR your Windows build will also need link in this library.
Content:	
		DLLMain.cpp - 		DLL Entry point
		BootStrap.cpp/.h	Object to implement library setup and teardown
			
			