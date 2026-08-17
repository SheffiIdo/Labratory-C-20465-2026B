; ========================================================
; invalid_input_5.as
; Tests Second Pass resolution errors
; ========================================================

; Error 58: Declared as both entry and extern
.extern ConflictLbl
.entry ConflictLbl

; Error 57: Defined as entry, but never created in the file
.entry MissingEntry

Main: add $3, $5, $9
      move $2, $4

; Error 39: Branching to a label that does not exist
      bne $31, $0, FakeLoop

      la DataBlock

; Error 39: Jumping to a label that does not exist
      jmp NowhereLabel

; Error 40: Branch to extern
    bgt $1, $2, ConflictLbl

      hlt

DataBlock: .db 10, 20, 30