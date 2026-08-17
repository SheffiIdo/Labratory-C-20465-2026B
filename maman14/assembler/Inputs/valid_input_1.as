; ========================================================
; valid_test.as
; Tests macros, data images, branches, and externals
; ========================================================

.entry MainStart
.entry DataBlock
.extern ExternalFunc

mcro init_regs
    add $1, $2, $3
    move $3, $4
mcroend

init_regs

MainStart: la DataBlock
           bne $31, $0, LoopJump
           call ExternalFunc

LoopJump:  jmp $14
           hlt

DataBlock: .db 127, -128, 0
           .db 42, 10