; ========================================================
; invalid_input_6.as
; Tests .extern defined locally (both orders) and First Pass errors
; ========================================================

mcro ValidMacro
    add $1, $2, $3
    sub $3, $4, $5
mcroend

; --- CONFLICT 1 SETUP ---
.extern ExternFirstLbl
.extern RealExtern

StartCode: ValidMacro

; Error 55: Declared as extern above, but defined locally here
ExternFirstLbl: move $1, $2

; --- CONFLICT 2 SETUP ---
LocalFirstLbl:  la RealExtern

; Error 55: Defined locally above, but declared as extern here
.extern LocalFirstLbl

; Error 40: Branch to an external label (second pass)
             bne $4, $5, RealExtern

; Error 30: Illegal opcode
             badopcode $1, $2

; Error 33: Illegal register name
             move $35, $2

; Error 35: Illegal consecutive commas
             add $1,, $2, $3

; Error 38: Unrecognized operand type
             la 15

; Error 53: Non-numeric in data directive
DataOne:     .dh 10, X, 30

; Error 54: Missing quotes
DataTwo:     .asciz "No closing quote