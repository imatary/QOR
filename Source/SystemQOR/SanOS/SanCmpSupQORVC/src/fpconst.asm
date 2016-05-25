;-----------------------------------------------------------------------------
; fpconst.asm - floating point constants
;-----------------------------------------------------------------------------
                .486
_DATA           segment DWORD public USE32 'DATA'
                assume  DS:FLAT

                public  __infinity

__infinity      db      6 dup(0), 0f0h, 07fh    ; Floating point infinity

_DATA           ends

                end
