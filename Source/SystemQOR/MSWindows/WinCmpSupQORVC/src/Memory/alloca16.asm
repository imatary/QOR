
.486

.MODEL flat

ASSUME fs: NOTHING 

.LIST

extern  _chkstk:near

.CODE

page
;***
; _alloca_probe_16, _alloca_probe_8 - align allocation to 16/8 byte boundary
;
;Purpose:
;       Adjust allocation size so the ESP returned from chkstk will be aligned
;       to 16/8 bit boundary. Call chkstk to do the real allocation.
;
;Entry:
;       EAX = size of local frame
;
;Exit:
;       Adjusted EAX.
;
;Uses:
;       EAX
;
;*******************************************************************************

public  __alloca_probe_16
public  _alloca_probe_8

_alloca_probe_16 proc                   ; 16 byte aligned alloca

        push    ecx
        lea     ecx, [esp] + 8          ; TOS before entering this function
        sub     ecx, eax                ; New TOS
        and     ecx, (16 - 1)           ; Distance from 16 bit align (align down)
        add     eax, ecx                ; Increase allocation size
        sbb     ecx, ecx                ; ecx = 0xFFFFFFFF if size wrapped around
        or      eax, ecx                ; cap allocation size on wraparound
        pop     ecx                     ; Restore ecx
        jmp     _chkstk

alloca_8:                               ; 8 byte aligned alloca
_alloca_probe_8 = alloca_8

        push    ecx
        lea     ecx, [esp] + 8          ; TOS before entering this function
        sub     ecx, eax                ; New TOS
        and     ecx, (8 - 1)            ; Distance from 8 bit align (align down)
        add     eax, ecx                ; Increase allocation Size
        sbb     ecx, ecx                ; ecx = 0xFFFFFFFF if size wrapped around
        or      eax, ecx                ; cap allocation size on wraparound
        pop     ecx                     ; Restore ecx
        jmp     _chkstk

_alloca_probe_16 endp

__alloca_probe_16 = _alloca_probe_16
        end
        
