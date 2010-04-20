# 1 "loop.S"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "loop.S"

# 1 "../include/armasmdef.h" 1
# 3 "loop.S" 2



 .text
# 36 "loop.S"
 .align 0




 .global loopLuma
loopLuma:
# 78 "loop.S"
 stmfd sp!, {r4-r11}
 str lr, [sp, #-4]!
 sub sp, sp, #24

 str r0, [sp, #0]

 ldr r6, L_alphaTabPtr
 ldr r7, L_betaTabPtr
 ldr r8, L_clipTabPtr




 ldr r9, [r3, #0]
 ldr r10, [r3, #4]

 ldrb r11, [r6, r9]
 ldrb r12, [r7, r10]
 add r14, r8, r9, lsl #2
 str r14, [sp, #12]
 str r11, [sp, #4]
 str r12, [sp, #8]




 ldr r9, [r2, #0]
 ldr r10, [r2, #4]

 ldrb r2, [r6, r9]
 ldrb r3, [r7, r10]
 add r14, r8, r9, lsl #2

 ldr r8, [sp, #24 +4*9 +4]

 b L_filt_row_col_skip




L_filt_row_col_loop :

 ldr r14, [sp, #12]
 ldr r2, [sp, #4]
 ldr r3, [sp, #8]

L_filt_row_col_skip :

 str r14, [sp, #16]

 ldr r10, [sp, #24 +4*9 +0]
 mov r7, #4



L_filt_blks_loop :

 ands r5, r8, #3
 addeq r0, r0, r10, lsl #2
 beq L_filt_next_block

 str r8, [sp, #24 +4*9 +4]
 ldr r8, [sp, #16]
 sub r5, r5, #1
 str r7, [sp, #20]
 ldrb r4, [r8, r5]
 mov r5, #4



L_filt_loop :







 ldrb r7, [r0, -r1]
 ldrb r8, [r0]
 ldrb r6, [r0, -r1, lsl #1]
 ldrb r9, [r0, r1]






 subs r10, r7, r8
 submi r10, r8, r7
 subs r11, r6, r7
 submi r11, r7, r6
 subs r12, r8, r9
 submi r12, r9, r8
 cmp r10, r2
 cmplt r11, r3
 cmplt r12, r3
 bge L_next_line


L_weak_filter :





 add r10, r1, r1, lsl #1
 ldrb r10, [r0, -r10]
 ldrb r11, [r0, r1, lsl #1]
 mov r14, r4
L_check_left_filt :
 subs r12, r7, r10
 submi r12, r10, r7
 cmp r12, r3
 bge L_check_right_filt
L_filt_left_pix :
 add r12, r7, r10, lsl #1
 add r12, r12, r8
 add r12, r12, #1
 rsb r12, r6, r12, asr #2
 cmn r12, r4
 rsblt r12, r4, #0
 cmp r12, r4
 movgt r12, r4
 add r12, r6, r12
 strb r12, [r0, -r1, lsl #1]
 add r14, r14, #1
L_check_right_filt :
 subs r12, r8, r11
 submi r12, r11, r8
 cmp r12, r3
 bge L_filt_middle_pix
L_filt_right_pix :
 add r12, r7, r11, lsl #1
 add r12, r12, r8
 add r12, r12, #1
 rsb r12, r9, r12, asr #2
 cmn r12, r4
 rsblt r12, r4, #0
 cmp r12, r4
 movgt r12, r4
 add r12, r9, r12
 strb r12, [r0, r1]
 add r14, r14, #1

L_filt_middle_pix :
 sub r10, r8, r7
 add r10, r6, r10, lsl #2
 sub r10, r10, r9
 add r10, r10, #4
 mov r6, #255
 mov r10, r10, asr #3
 cmn r10, r14
 rsblt r10, r14, #0
 cmp r10, r14
 movgt r10, r14
 add r11, r7, r10
 cmp r11, r6
 bichi r11, r6, r11, asr #31
 strb r11, [r0, -r1]
 sub r11, r8, r10
 cmp r11, r6
 bichi r11, r6, r11, asr #31
 strb r11, [r0]

L_next_line :
 ldr r10, [sp, #24 +4*9 +0]
 subs r5, r5, #1
 add r0, r0, r10
 bne L_filt_loop

 ldr r8, [sp, #24 +4*9 +4]
 ldr r7, [sp, #20]

L_filt_next_block :
 movs r8, r8, lsr #2
 subnes r7, r7, #1
 bne L_filt_blks_loop

 ldr r0, [sp, #0]
 ldr r5, [sp, #24 +4*9 +8]
 cmp r8, #0
 add r0, r0, r1, lsl #2
 subnes r5, r5, #1
 str r0, [sp, #0]
 str r5, [sp, #24 +4*9 +8]
 bne L_filt_row_col_loop


 add sp, sp, #24
 ldr lr, [sp], #4
 ldmfd sp!, {r4-r11}
 bx lr



# 301 "loop.S"
 .align 0




 .global loopLumaIntraMbEdge
loopLumaIntraMbEdge:
# 318 "loop.S"
 stmfd sp!, {r4-r11}
 str lr, [sp, #-4]!




 ldr r6, L_alphaTabPtr
 ldr r7, L_betaTabPtr
 ldr r4, [sp, #36]
 mov r5, #16
 ldrb r2, [r6, r2]
 ldrb r3, [r7, r3]


L_filt_intra_loop :
# 341 "loop.S"
 ldrb r7, [r0, -r1]
 ldrb r8, [r0]
 ldrb r6, [r0, -r1, lsl #1]
 ldrb r9, [r0, r1]






 subs r10, r7, r8
 submi r10, r8, r7
 subs r11, r6, r7
 submi r11, r7, r6
 subs r12, r8, r9
 submi r12, r9, r8
 cmp r10, r2
 cmplt r11, r3
 cmplt r12, r3
 bge L_next_line_intra

 sub r11, r10, #2
 cmp r11, r2, asr #2
 blt L_filt_intra_left

L_short_filt :

 add r14, r7, r6, lsl #1
 add r14, r14, r9
 add r14, r14, #2
 add r6, r6, r9, lsl #1
 add r6, r6, r8
 add r6, r6, #2
 mov r14, r14, asr #2
 mov r6, r6, asr #2
 strb r14, [r0, -r1]
 strb r6, [r0]
 b L_next_line_intra

L_filt_intra_left :
 add r10, r1, r1, lsl #1
 ldrb r10, [r0, -r10]
 ldrb r11, [r0, r1, lsl #1]
 subs r12, r7, r10
 submi r12, r10, r7
 cmp r12, r3
 blt L_long_filt_left
L_short_filt_left :
 add r14, r7, r6, lsl #1
 add r14, r14, r9
 add r14, r14, #2
 mov r14, r14, asr #2
 strb r14, [r0, -r1]
 b L_filt_intra_right
L_long_filt_left :


 add r12, r6, r7
 add r12, r12, r8
 add r12, r12, #2
 add r14, r10, r12, lsl #1
 add r14, r14, r9
 add r12, r10, r12
 mov r14, r14, asr #3
 strb r14, [r0, -r1]
 mov r14, r12, asr #2
 strb r14, [r0, -r1, lsl #1]
 ldrb r14, [r0, -r1, lsl #2]
 add r12, r12, r10, lsl #1
 add r12, r12, #2
 add r12, r12, r14, lsl #1
 add r14, r1, r1, lsl #1
 mov r12, r12, asr #3
 strb r12, [r0, -r14]

L_filt_intra_right :

 subs r12, r8, r11
 submi r12, r11, r8
 cmp r12, r3
 blt L_long_filt_right
L_short_filt_right :
 add r14, r6, r9, lsl #1
 add r14, r14, r8
 add r14, r14, #2
 mov r14, r14, asr #2
 strb r14, [r0]
 b L_next_line_intra
L_long_filt_right :
 add r12, r7, r8
 add r12, r12, r9
 add r12, r12, #2
 add r10, r1, r1, lsl #1
 add r14, r6, r12, lsl #1
 add r14, r14, r11
 add r12, r12, r11
 mov r14, r14, asr #3
 strb r14, [r0]
 mov r14, r12, asr #2
 strb r14, [r0, r1]
 ldrb r14, [r0, r10]
 add r12, r12, r11, lsl #1
 add r12, r12, #2
 add r12, r12, r14, lsl #1
 mov r12, r12, asr #3
 strb r12, [r0, r1, lsl #1]

L_next_line_intra :
 subs r5, r5, #1
 add r0, r0, r4
 bne L_filt_intra_loop

 ldr lr, [sp], #4
 ldmfd sp!, {r4-r11}
 bx lr



# 490 "loop.S"
 .align 0




 .global loopChroma
loopChroma:
# 535 "loop.S"
 stmfd sp!, {r4-r11}
 str lr, [sp, #-4]!
 sub sp, sp, #32

 str r0, [sp, #0]

 ldr r6, L_alphaTabPtr
 ldr r7, L_betaTabPtr
 ldr r8, L_clipTabPtr




 ldr r9, [r3, #8]
 ldr r10, [r3, #12]
 ldrb r11, [r6, r9]
 ldrb r12, [r7, r10]
 add r14, r8, r9, lsl #2
 str r14, [sp, #12]
 str r11, [sp, #4]
 str r12, [sp, #8]




 ldr r9, [r2, #8]
 ldr r10, [r2, #12]
 ldrb r2, [r6, r9]
 ldrb r3, [r7, r10]
 add r14, r8, r9, lsl #2

 ldr r11, [sp, #32 +4*9 +0]

 ldr r8, [sp, #32 +4*9 +4]

 b L_c_filt_row_col_skip





L_c_filt_row_col_loop :

 ldr r14, [sp, #12]
 ldr r2, [sp, #4]
 ldr r3, [sp, #8]

L_c_filt_row_col_skip :

 str r14, [sp, #16]

 mov r7, #4
 ldr r0, [sp, #0]
 ldr r6, [sp, #32 +4*9 +8]




L_c_filt_blks_loop :

 ands r5, r8, #3
 beq L_c_filt_next_block

 str r8, [sp, #32 +4*9 +4]
 ldr r8, [sp, #16]
 sub r5, r5, #1
 str r7, [sp, #20]
 ldrb r4, [r8, r5]

 mov r5, #0






 str r0, [sp, #24]
 str r6, [sp, #28]

 add r4, r4, #1



L_c_filt_loop :
# 627 "loop.S"
 ldrb r7, [r0, -r1]
 ldrb r8, [r0]
 ldrb r6, [r0, -r1, lsl #1]
 ldrb r9, [r0, r1]






 subs r10, r7, r8
 submi r10, r8, r7
 subs r12, r6, r7
 submi r12, r7, r6
 subs r14, r8, r9
 submi r14, r9, r8
 cmp r10, r2
 cmplt r12, r3
 cmplt r14, r3
 bge L_c_next_line

L_c_weak_filter :





 sub r10, r8, r7
 sub r6, r6, r9
 add r10, r6, r10, lsl #2
 add r10, r10, #4
 mov r6, #255
 mov r10, r10, asr #3
 cmn r10, r4
 rsblt r10, r4, #0
 cmp r10, r4
 movgt r10, r4
 add r9, r7, r10
 cmp r9, r6
 bichi r9, r6, r9, asr #31
 strb r9, [r0, -r1]
 sub r9, r8, r10
 cmp r9, r6
 bichi r9, r6, r9, asr #31
 strb r9, [r0]

L_c_next_line :
 adds r5, r5, #0x40000000
 add r0, r0, r11
 ldrvs r0, [sp, #28]
 bcc L_c_filt_loop

 ldr r8, [sp, #32 +4*9 +4]
 ldr r7, [sp, #20]

 ldr r0, [sp, #24]
 ldr r6, [sp, #28]

L_c_filt_next_block :
 movs r8, r8, lsr #2
 subnes r7, r7, #1
 add r0, r0, r11, lsl #1
 add r6, r6, r11, lsl #1
 bne L_c_filt_blks_loop

 movs r8, r8, lsr #4*2

 ldr r0, [sp, #0]
 ldr r6, [sp, #32 +4*9 +8]
 ldr r5, [sp, #32 +4*9 +12]
 add r0, r0, r1, lsl #2
 add r6, r6, r1, lsl #2
 subnes r5, r5, #1
 str r0, [sp, #0]
 str r6, [sp, #32 +4*9 +8]
 str r5, [sp, #32 +4*9 +12]
 bne L_c_filt_row_col_loop

 add sp, sp, #32
 ldr lr, [sp], #4
 ldmfd sp!, {r4-r11}
 bx lr



# 740 "loop.S"
 .align 0




 .global loopChromaIntraMbEdge
loopChromaIntraMbEdge:
# 758 "loop.S"
 stmfd sp!, {r4-r11}





 ldr r11, [sp, #32]
 ldr r6, L_alphaTabPtr
 ldr r7, L_betaTabPtr
 mov r5, #0
 ldrb r2, [r6, r2]
 ldrb r3, [r7, r3]







L_c_filt_intra_loop :
# 786 "loop.S"
 ldrb r7, [r0, -r1]
 ldrb r8, [r0]
 ldrb r6, [r0, -r1, lsl #1]
 ldrb r9, [r0, r1]






 subs r10, r7, r8
 submi r10, r8, r7
 subs r12, r6, r7
 submi r12, r7, r6
 subs r4, r8, r9
 submi r4, r9, r8
 cmp r10, r2
 cmplt r12, r3
 cmplt r4, r3
 bge L_c_next_line_intra

 add r10, r7, r6, lsl #1
 add r6, r6, r9, lsl #1
 add r10, r10, r9
 add r6, r6, r8
 add r10, r10, #2
 add r6, r6, #2
 mov r10, r10, asr #2
 mov r6, r6, asr #2
 strb r10, [r0, -r1]
 strb r6, [r0]

L_c_next_line_intra :
 adds r5, r5, #0x10000000
 add r0, r0, r11
 ldrvs r0, [sp, #36]
 bcc L_c_filt_intra_loop

 ldmfd sp!, {r4-r11}
 bx lr






 .align 0
L_alphaTabPtr :
 .word L_alphaTab
L_betaTabPtr :
 .word L_betaTab
L_clipTabPtr :
 .word L_clipTab



 .section .rodata


 .byte 0, 0, 0, 0, 0, 0, 0, 0
 .byte 0, 0, 0, 0
L_alphaTab :
 .byte 0, 0, 0, 0, 0, 0, 0, 0
 .byte 0, 0, 0, 0, 0, 0, 0, 0
 .byte 4, 4, 5, 6, 7, 8, 9, 10
 .byte 12, 13, 15, 17, 20, 22, 25, 28
 .byte 32, 36, 40, 45, 50, 56, 63, 71
 .byte 80, 90,101,113,127,144,162,182
 .byte 203,226,255,255

 .byte 255,255,255,255,255,255,255,255
 .byte 255,255,255,255



 .byte 0, 0, 0, 0, 0, 0, 0, 0
 .byte 0, 0, 0, 0
L_betaTab :
 .byte 0, 0, 0, 0, 0, 0, 0, 0
 .byte 0, 0, 0, 0, 0, 0, 0, 0
 .byte 2, 2, 2, 3, 3, 3, 3, 4
 .byte 4, 4, 6, 6, 7, 7, 8, 8
 .byte 9, 9,10,10,11,11,12,12
 .byte 13,13,14,14,15,15,16,16
 .byte 17,17,18,18

 .byte 18,18,18,18,18,18,18,18
 .byte 18,18,18,18



 .byte 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
 .byte 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
 .byte 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
L_clipTab :
 .byte 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
 .byte 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
 .byte 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
 .byte 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
 .byte 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1
 .byte 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1
 .byte 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2
 .byte 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 2, 3, 3
 .byte 1, 2, 3, 3, 2, 2, 3, 3, 2, 2, 4, 4, 2, 3, 4, 4
 .byte 2, 3, 4, 4, 3, 3, 5, 5, 3, 4, 6, 6, 3, 4, 6, 6
 .byte 4, 5, 7, 7, 4, 5, 8, 8, 4, 6, 9, 9, 5, 7,10,10
 .byte 6, 8,11,11, 6, 8,13,13, 7,10,14,14, 8,11,16,16
 .byte 9,12,18,18,10,13,20,20,11,15,23,23,13,17,25,25

 .byte 13,17,25,25,13,17,25,25,13,17,25,25,13,17,25,25
 .byte 13,17,25,25,13,17,25,25,13,17,25,25,13,17,25,25
 .byte 13,17,25,25,13,17,25,25,13,17,25,25,13,17,25,25




