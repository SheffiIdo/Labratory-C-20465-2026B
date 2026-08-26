; ========================================================
; invalid_input_3.as
; Tests Pre-processor limits and macro edge cases
; ========================================================

; Error 5: Macro declared without a name
mcro
    add $1, $2, $3
mcroend

; Error 6 & 7: Extra text after name and mcroend
mcro BAD_TEXT extra_stuff
    sub $4, $5, $6
mcroend extra_stuff

; Error 13 : Name too long
mcro THIS_MACRO_NAME_IS_WAY_TOO_LONG_AND_EXCEEDS_THE_THIRTY_ONE_CHAR_LIMIT
    move $1, $2
mcroend

; Error 9: Duplicate definition
mcro VALID_NAME
    hlt
mcroend

mcro VALID_NAME
    la K
mcroend

; Error 10: Illegal characters
mcro BAD-NAME!
    add $1, $2, $3
mcroend

; Error 11: Nested macros
mcro OUTER_MACRO
    mcro INNER_MACRO
        hlt
    mcroend
mcroend

; Error 12: Missing mcroend
mcro NO_END_MACRO
    add $1, $2, $3