mcro LOAD_VAL1
      la     val1
      jmp    NEXT
mcroend

mcro CALL_VARS
      call   val1
      jmp    $4
      la     wNumber
mcroend

.entry NEXT
.extern wNumber
STR:  .asciz "aBcd"
MAIN: add    $3,$5,$9
LOOP: ori    $9,-5,$2
LOAD_VAL1
NEXT: move   $20,$4
LIST: .db    6,-9
      bgt    $4,$2,END
      la     K
      sw     $0,4,$10
      bne    $31,$9,LOOP
CALL_VARS
.extern val1
      .dh    27056
K:    .dw    31,-12
END:  hlt
.entry K