; ========================================================
; invalid_input_4.as
; Tests First Pass operand/label validation
; ========================================================

.extern EXTLBL
.entry MISSINGENTRY

; Error 30: Illegal opcode
BADLABEL add $1, $2, $3

; Error 52: Reserved word as label
add: move $1, $2

; Error 51: Duplicate label
DUP: add $1, $2, $3
DUP: sub $4, $5, $6

; Error 55: Extern defined locally
EXTLBL: hlt

; Error 31, 33, 34, 35, 36
    add $1, $2
    sub $1, $2, $3 extra_text
    move $32, $1
    add $1 $2, $3
    add $1, , $2, $3
    add ,$1, $2, $3

; Error 33: Unrecognized operand type
    bne 5, $2, DUP

; Error 53 & 54: Bad data directives
    .db 12, abc, 14
    .asciz "missing_quote