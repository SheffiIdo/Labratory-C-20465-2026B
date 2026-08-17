; ========================================================
; error_preproc.as
; Tests Pre-processor lexical rules
; ========================================================

; ERROR: Reserved word (opcode) used as macro name
mcro add
    subi $1, $2, 5
mcroend

; ERROR: Illegal characters in macro name.
mcro $4
    hlt
mcroend