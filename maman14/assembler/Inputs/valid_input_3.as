; ========================================================
; valid_input_3.as
; Tests mixed data sizes, byte alignment, and extended loops
; ========================================================
.entry StrData
.entry NumData
.extern PutChar
.extern GetChar

mcro InitLoop
            move $16, $0
            add  $16, $1, $17
            la   StrData
mcroend

mcro ProcessData
            and $17, $18, $19
            or  $19, $20, $21
            nor $21, $22, $23
mcroend

InitLoop
MainPrg:    call GetChar
LoopStart:  bne $16, $31, Skip
            call PutChar
ProcessData
Skip:       ori $16, -1, $16
            addi $17, 5, $17
            bgt $17, $0, LoopStart
            jmp EndPrg
EndPrg:     hlt
StrData:    .asciz "Loop Test String"
NumData:    .db 5, 10, 15, 20
            .dh 500, -500, 1000, -1000
            .dw 100000, 200000, 300000, 400000