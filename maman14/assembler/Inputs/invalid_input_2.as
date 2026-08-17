; ========================================================
; error_passes.as
; Tests First and Second Pass error handling
; ========================================================

; ERROR: Label contains an illegal character (underscore)
BAD_LABEL: add $1, $2, $3

; ERROR: Label starts with a number
1BadLabel: move $2, $3

; ERROR: Duplicate label definition
StartLbl: add $1, $2, $3
StartLbl: move $2, $3

; ERROR: Missing comma in instruction
    add $1 $2, $3

; ERROR: Undefined label used as operand (Caught in Second Pass)
    bne $1, $2, MissingLbl