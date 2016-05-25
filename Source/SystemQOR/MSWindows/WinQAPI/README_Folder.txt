README_Folder.txt

Describes the content of and any rules for the containing folder.

Strata:		1
Path:		/Strata-1/SystemQOR/MSWindows/WinQAPI
Purpose:	Implements QOR Windows API ( WinQAPI )
			
Content:	A set of thin stateless or minimal state wrappers over the Win32 API.
		These wrappers classify the API into classes that are simply containers for functional areas or
		more usually containers for specific API Dlls
		They also secure each and every API call against bad parameters and return errors wherever possible.
		The purpose is take the take the Win32API from a crash prone C API with many extant varaints and version
		to a single C++ API which is to the extend possible crash proof and adapts seemlessly to different versions
		of Windows.
		This is done using, levelling up where possible and levelling down only where absolutely necessary.
		All remaining functional deficits becomes soft errors that can be handled gracefully at runtime.



			
			