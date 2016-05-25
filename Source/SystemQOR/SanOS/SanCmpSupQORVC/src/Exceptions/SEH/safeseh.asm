
.486

.MODEL  flat

EXTRN ?CatchGuardHandler@GuardDescriptor@EH@nsCompiler@@CA?AW4_EXCEPTION_DISPOSITION@nsWin32@@PAVExceptionRecord@23@PAVCatchGuardRN@123@PAUCONTEXT@5@PAX@Z:NEAR
EXTRN ?UnwindHandler@SEH@nsCompiler@@YA?AW4_EXCEPTION_DISPOSITION@@PAVExceptionRecord@12@PAVExceptionFrame@12@PAUCONTEXT@nsWin32@@PAX@Z:NEAR

NominalAsmHandler PROTO

.safeseh    ?CatchGuardHandler@GuardDescriptor@EH@nsCompiler@@CA?AW4_EXCEPTION_DISPOSITION@nsWin32@@PAVExceptionRecord@23@PAVCatchGuardRN@123@PAUCONTEXT@5@PAX@Z			
.safeseh    ?UnwindHandler@SEH@nsCompiler@@YA?AW4_EXCEPTION_DISPOSITION@@PAVExceptionRecord@12@PAVExceptionFrame@12@PAUCONTEXT@nsWin32@@PAX@Z

.CODE

NominalAsmHandler PROC
NominalAsmHandler ENDP

END

