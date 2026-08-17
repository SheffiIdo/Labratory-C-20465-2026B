; ========================================================
; valid_input_2.as
; Tests whitespace, extreme numbers, and complex routing
; ========================================================

.entry FinalData
.extern ExtFunc

mcro do_math
        add   $31,  $0,   $15
        sub   $15,  $15,  $15
mcroend

StartLbl:   la    FinalData
            call  ExtFunc
            do_math
            jmp   EndCode

EndCode:    hlt

; Testing extreme boundaries (32-bit dw, 16-bit dh, 8-bit db)
FinalData:  .dw   2147483647, -2147483648
            .dh   32767, -32768
            .db   127, -128
            .asciz "  Spaces! "