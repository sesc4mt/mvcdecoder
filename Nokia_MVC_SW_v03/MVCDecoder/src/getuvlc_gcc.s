# 1 "getuvlc.S"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "getuvlc.S"

# 1 "../include/armasmdef.h" 1
# 3 "getuvlc.S" 2



 .text
# 75 "getuvlc.S"
 .align 0




 .global vldGetUVLC
vldGetUVLC:






 ldr r1, [r0, #12]
 ldr r2, [r0, #16]
 subs r1, r1, #7
 bge L_enought_bits
 str r4, [sp, #-4]!
 ldr r4, [r0, #4]
 ldr r3, [r0, #8]
 ldr r12, [r0, #0]
 sub r4, r4, #1
 cmp r3, r4
 ldrleb r4, [r12, r3]
 mov r2, r2, lsl #16
 add r3, r3, #1
 add r1, r1, #16
 orrle r2, r2, r4, lsl #8
 ldrltb r4, [r12, r3]
 add r3, r3, #1
 str r3, [r0, #8]
 orrlt r2, r2, r4
 str r2, [r0, #16]
 ldr r4, [sp], #4

L_enought_bits :

 ldr r3, L_uvlcLookupPtr


 mov r12, #127
 and r2, r12, r2, lsr r1

 ldrb r3, [r3, r2]

 add r1, r1, #7


 cmp r2, #8
 subge r1, r1, r3, lsr #4
 strge r1, [r0, #12]
 andge r0, r3, #15
 bxge lr





 stmfd sp!, {r4-r6}


 mov r5, r3


 ldr r2, [r0, #16]
 ldr r3, [r0, #8]
 ldr r4, [r0, #4]
 ldr r12, [r0, #0]

 cmp r1, #24
 bgt L_enought_bits2


L_not_enought_bits :
 cmp r3, r4
 mov r2, r2, lsl #8
 ldrltb r6, [r12, r3]
 add r3, r3, #1
 add r1, r1, #8
 orrlt r2, r2, r6
 cmp r1, #24
 ble L_not_enought_bits

L_enought_bits2 :
# 171 "getuvlc.S"
 rsb r6, r1, #32
 mov r6, r2, lsl r6

 mov r6, r6, lsl r5
 orr r6, r6, #1
L_find_one_bit :
 adds r6, r6, r6
 addcc r5, r5, #1
 bcc L_find_one_bit




 cmp r5, #33/2
 bgt L_uvlc_error

 sub r1, r1, r5
 add r5, r5, #1



 subs r1, r1, r5
 bge L_enought_bits3
 cmp r3, r4
 mov r2, r2, lsl #8
 ldrltb r6, [r12, r3]
 add r3, r3, #1
 add r1, r1, #8
 orrlt r2, r2, r6

L_enought_bits3 :

 str r1, [r0, #12]
 str r2, [r0, #16]
 str r3, [r0, #8]

 mvn r12, #0
 mov r2, r2, lsr r1
 bic r2, r2, r12, lsl r5

 sub r2, r2, #1

 cmp r2, r12, lsr #16
 bgt L_uvlc_error

 mov r0, r2

 ldmfd sp!, {r4-r6}
 bx lr

L_uvlc_error :

 ldr r1, L_BIB_ERR_BIT_ERROR_value
 str r1, [r0, #20]
 mov r0, #0
 ldmfd sp!, {r4-r6}
 bx lr



 .align 0

L_uvlcLookupPtr :
 .word L_uvlcLookup

L_BIB_ERR_BIT_ERROR_value :
 .word -4






 .section .rodata





L_uvlcLookup :
 .byte 7, 6, 5, 5, 4, 4, 4, 4
 .byte 7*16+7, 7*16+8, 7*16+9,7*16+10,7*16+11,7*16+12,7*16+13,7*16+14
 .byte 5*16+3, 5*16+3, 5*16+3, 5*16+3, 5*16+4, 5*16+4, 5*16+4, 5*16+4
 .byte 5*16+5, 5*16+5, 5*16+5, 5*16+5, 5*16+6, 5*16+6, 5*16+6, 5*16+6
 .byte 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1
 .byte 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1
 .byte 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2
 .byte 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2
 .byte 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0
 .byte 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0
 .byte 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0
 .byte 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0
 .byte 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0
 .byte 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0
 .byte 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0
 .byte 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0




