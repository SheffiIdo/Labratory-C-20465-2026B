; ========================================================
; valid_input_4.as
; Tests sequential macros and fragmented data collection
; ========================================================
.extern ExtFuncA
.extern ExtFuncB
.entry FinalVal
.entry CodeLabel

mcro MacA
            la DataOne
            call ExtFuncA
            move $1, $2
            addi $2, 10, $3
mcroend

mcro MacB
            bne $2, $3, CodeLabel
            jmp $5
            sub $6, $7, $8
            and $8, $9, $10
mcroend

StartCode:  la DataTwo
MacA
DataOne:    .db 1, 2, 3, 4
            .dh 12, 14
CodeLabel:  call ExtFuncB
MacB
            ori $10, 5, $11
            bgt $11, $0, StartCode
            hlt
DataTwo:    .asciz "Fragmented"
FinalVal:   .dw -1, 100, 200