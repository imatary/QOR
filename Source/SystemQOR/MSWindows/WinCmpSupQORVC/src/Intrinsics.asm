
.486 

.MODEL flat

ASSUME fs: NOTHING 

ZERO SEGMENT 

__except_list EQU 0
@feat		 EQU	 1

ZERO ENDS

EXTRN __except_handler4:NEAR
EXTRN ___security_cookie:NEAR
EXTRN @__security_check_cookie@4:NEAR
EXTRN ?CatchGuardHandler@GuardDescriptor@EH@nsCompiler@@CA?AW4_EXCEPTION_DISPOSITION@nsWin32@@PAVExceptionRecord@23@PAVCatchGuardRN@123@PAUCONTEXT@5@PAX@Z:NEAR
EXTRN ?UnwindHandler@SEH@nsCompiler@@YA?AW4_EXCEPTION_DISPOSITION@@PAVExceptionRecord@12@PAVExceptionFrame@12@PAUCONTEXT@nsWin32@@PAX@Z:NEAR

.safeseh    ?CatchGuardHandler@GuardDescriptor@EH@nsCompiler@@CA?AW4_EXCEPTION_DISPOSITION@nsWin32@@PAVExceptionRecord@23@PAVCatchGuardRN@123@PAUCONTEXT@5@PAX@Z			
.safeseh    ?UnwindHandler@SEH@nsCompiler@@YA?AW4_EXCEPTION_DISPOSITION@@PAVExceptionRecord@12@PAVExceptionFrame@12@PAUCONTEXT@nsWin32@@PAX@Z

PUBLIC __tls_array
PUBLIC __fltused
PUBLIC __ldused
PUBLIC __except_list 
PUBLIC __SEH_prolog
PUBLIC __SEH_epilog
PUBLIC __SEH_prolog4
PUBLIC __SEH_epilog4
PUBLIC __EH_prolog
PUBLIC __EH_prolog3
PUBLIC __EH_epilog3
PUBLIC __EH_prolog3_catch
PUBLIC __EH_prolog3_catch_GS
PUBLIC __EH_epilog3_catch_GS

__tls_array	 EQU	 2ch
__fltused	 EQU	 9876h
__ldused	 EQU	 9876h

.CODE

__SEH_prolog PROC NEAR
push	    offset __except_handler4
mov	    eax,dword ptr fs:[00000000h] 
push	    eax  
mov	    eax,dword ptr [esp+10h]
mov	    dword ptr [esp+10h],ebp
lea	    ebp,[esp+10h]
sub	    esp,eax 
push	    ebx  
push	    esi  
push	    edi  
mov	    eax,dword ptr [ebp-8] 
mov	    dword ptr [ebp-18h],esp 
push	    eax  
mov	    eax,dword ptr [ebp-4] 
mov	    dword ptr [ebp-4],0FFFFFFFFh 
mov	    dword ptr [ebp-8],eax 
lea	    eax,[ebp-10h] 
mov	    dword ptr fs:[00000000h],eax 
ret		 
__SEH_prolog ENDP

__SEH_prolog4 PROC NEAR
push	    offset __except_handler4
mov	    eax,dword ptr fs:[00000000h] 
push	    eax  
mov	    eax,dword ptr [esp+10h]
mov	    dword ptr [esp+10h],ebp
lea	    ebp,[esp+10h]
sub	    esp,eax 
push	    ebx  
push	    esi  
push	    edi  
mov	    eax,dword ptr [ebp-8] 
mov	    dword ptr [ebp-18h],esp 
push	    eax  
mov	    eax,dword ptr [ebp-4] 
mov	    dword ptr [ebp-4],0FFFFFFFFh 
mov	    dword ptr [ebp-8],eax 
lea	    eax,[ebp-10h] 
mov	    dword ptr fs:[00000000h],eax 
ret		 
__SEH_prolog4 ENDP

__SEH_epilog PROC NEAR
mov	    ecx,dword ptr [ebp-10h] 
mov	    dword ptr fs:[0],ecx 
pop	    ecx  
pop	    edi  
pop	    esi  
pop	    ebx  
leave		 
push	    ecx  
ret	      
__SEH_epilog ENDP

__SEH_epilog4 PROC NEAR
mov	    ecx,dword ptr [ebp-10h] 
mov	    dword ptr fs:[0],ecx 
pop	    ecx  
pop	    edi  
pop	    esi  
pop	    ebx  
leave		 
push	    ecx  
ret	      
__SEH_epilog4 ENDP

__EH_prolog PROC NEAR
push	    0FFFFFFFFh 
push	    eax  
mov	    eax,dword ptr fs:[00000000h] 
push	    eax  
mov	    eax,dword ptr [esp+0Ch] 
mov	    dword ptr fs:[0],esp 
mov	    dword ptr [esp+0Ch],ebp 
lea	    ebp,[esp+0Ch] 
push	    eax  
ret  
__EH_prolog ENDP	   

__EH_prolog3 PROC NEAR
push	    0FFFFFFFFh 
push	    eax  
mov	    eax,dword ptr fs:[00000000h] 
push	    eax  
mov	    eax,dword ptr [esp+0Ch] 
mov	    dword ptr fs:[0],esp 
mov	    dword ptr [esp+0Ch],ebp 
lea	    ebp,[esp+0Ch] 
push	    eax  
ret  
__EH_prolog3 ENDP	   

__EH_epilog3 PROC NEAR
mov         ecx,dword ptr [ebp-0Ch] 
mov         dword ptr fs:[0],ecx 
pop         ecx  
pop         edi  
pop         edi  
pop         esi  
pop         ebx  
mov         esp,ebp 
pop         ebp  
push        ecx  
ret          
__EH_epilog3 ENDP

__EH_epilog3_catch_GS PROC NEAR
mov         ecx,dword ptr [ebp-14h] 
xor         ecx,ebp 
call        @__security_check_cookie@4
jmp         __EH_epilog3
__EH_epilog3_catch_GS ENDP

__EH_prolog3_catch_GS PROC NEAR
push        eax  
push        dword ptr fs:[0] 
lea         eax,[esp+0Ch] 
sub         esp,dword ptr [esp+0Ch] 
push        ebx  
push        esi  
push        edi  
mov         dword ptr [eax],ebp 
mov         ebp,eax 
mov         eax,dword ptr [___security_cookie] 
xor         eax,ebp 
push        eax  
mov         dword ptr [ebp-14h],eax 
mov         dword ptr [ebp-10h],esp 
push        dword ptr [ebp-4] 
mov         dword ptr [ebp-4],0FFFFFFFFh 
lea         eax,[ebp-0Ch] 
mov         dword ptr fs:[00000000h],eax 
ret
__EH_prolog3_catch_GS ENDP

__EH_prolog3_catch PROC NEAR
push	    0FFFFFFFFh 
push	    eax  
mov	    eax,dword ptr fs:[00000000h] 
push	    eax  
mov	    eax,dword ptr [esp+0Ch] 
mov	    dword ptr fs:[0],esp 
mov	    dword ptr [esp+0Ch],ebp 
lea	    ebp,[esp+0Ch] 
push	    eax  
ret  
__EH_prolog3_catch ENDP	  

__EH_epilog PROC NEAR
mov         ecx,dword ptr [ebp-0Ch] 
mov         dword ptr fs:[0],ecx 
pop         ecx  
pop         edi  
pop         edi  
pop         esi  
pop         ebx  
mov         esp,ebp 
pop         ebp  
push        ecx  
ret          
__EH_epilog ENDP
	  
END






