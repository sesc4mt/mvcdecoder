# 1 "getpred.S"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "getpred.S"

# 1 "../include/armasmdef.h" 1
# 3 "getpred.S" 2
# 20 "getpred.S"
 .extern clip8Buf



 .text
# 53 "getpred.S"
 .align 0




 .global mcpCopyMacroblock
mcpCopyMacroblock:
# 72 "getpred.S"
 stmfd sp!, {r4-r10}





 ldr r4, [sp, #7*4]
 add r5, r4, #2*0






 ldr r6, [r0]
 ldr r7, [r1]
 add r8, r3, #0
 mla r9, r3, r4, r2
 mla r10, r8, r5, r2
 add r6, r6, r9
 add r10, r10, #0
 add r7, r7, r10
# 106 "getpred.S"
 sub r4, r4, #16-4
 sub r5, r5, #16-4
 mov r8, #16
L_loop_copy_mb_lines_y :
 ldmia r7!, {r9-r10}
 stmia r6!, {r9-r10}
 ldr r9, [r7], #4
 ldr r10, [r7], r5
 str r9, [r6], #4
 str r10, [r6], r4
 subs r8, r8, #1
 bne L_loop_copy_mb_lines_y

 add r4, r4, #16-4
 add r5, r5, #16-4
# 129 "getpred.S"
 mov r4, r4, lsr #1
 mov r5, r5, lsr #1
 mov r2, r2, lsr #1
 mov r3, r3, lsr #1






 ldr r6, [r0, #4]
 ldr r7, [r1, #4]
 ldr r0, [r0, #8]
 ldr r1, [r1, #8]
 add r8, r3, #0/2
 mla r9, r3, r4, r2
 mla r10, r8, r5, r2
 add r6, r6, r9
 add r0, r0, r9
 add r10, r10, #0/2
 add r7, r7, r10
 add r1, r1, r10

 sub r4, r4, #8-4
 sub r5, r5, #8-4
 mov r8, #16/2
L_loop_copy_mb_lines_c :
 ldr r9, [r7], #4
 ldr r10, [r7], r5
 str r9, [r6], #4
 str r10, [r6], r4
 ldr r9, [r1], #4
 ldr r10, [r1], r5
 str r9, [r0], #4
 str r10, [r0], r4
 subs r8, r8, #1
 bne L_loop_copy_mb_lines_c



 ldmfd sp!, {r4-r10}
 bx lr



# 206 "getpred.S"
 .align 0




 .global mcpGetPred4x4
mcpGetPred4x4:
# 275 "getpred.S"
 stmfd sp!, {r4-r12, lr}
 sub sp, sp, #376

 str r0, [sp, #0 +216]
 str r1, [sp, #0 +220]
 str r2, [sp, #0 +224]
 str r3, [sp, #0 +228]







 ldr r2, [sp, #376 +4*10 +4]
 ldr r3, [sp, #376 +4*10 +8]
 mov r4, r2, lsr #2
 str r4, [sp, #0 +0]
 mov r2, r2, lsr #1
 str r2, [sp, #0 +56]
 mov r3, r3, lsr #1
 str r3, [sp, #0 +60]





 mov r0, #0
 str r0, [sp, #0 +16]

L_loop_interp_main_y :





 mov r0, #0
 str r0, [sp, #0 +12]

L_loop_interp_main_x :






 ldr r0, [sp, #0 +224]
 ldr r2, [sp, #0 +12]
 ldr r1, [sp, #0 +228]
 ldr r3, [sp, #0 +16]
 add r0, r2, r0
 add r1, r3, r1
# 335 "getpred.S"
 ldr r5, [sp, #376 +4*10 +12]
 ldr r6, [sp, #0 +216]
 add r5, r5, r2, lsl #2
 ldrsh r7, [r5]
 ldrsh r8, [r5, #2]
 add r2, r2, r3, lsl #4
 add r6, r6, r2, lsl #2
 str r6, [sp, #0 +212]
 add r0, r7, r0, lsl #4
 add r1, r8, r1, lsl #4
 str r0, [sp, #0 +24]
 str r1, [sp, #0 +28]

 ldr r6, [sp, #376 +4*10 +0]

 ldr r9, [sp, #376 +4*10 +4]
 ldr r10, [sp, #376 +4*10 +8]

 ldr r7, [r6]
# 363 "getpred.S"
 and r2, r0, #3
 str r2, [sp, #0 +40]
 and r3, r1, #3
 str r3, [sp, #0 +44]
 mov r0, r0, asr #2
 mov r1, r1, asr #2
# 381 "getpred.S"
L_interp_copy :





 orrs r4, r2, r3
 bne L_interp_hf_vs
# 413 "getpred.S"
 sub r4, r9, #4
 sub r5, r10, #4
 cmp r0, r4
 cmpls r1, r5
 bls L_interp_copy_no_bound_checks


 add r8, sp, #0 +232
 mov r3, #4
 bl L_get_ref_area_4xX
 str r0, [sp, #0 +20]
 mov r2, #8
 str r2, [sp, #0 +48]
 b L_interp_copy_cont

L_interp_copy_no_bound_checks :

 mla r0, r9, r1, r0
 str r9, [sp, #0 +48]
 add r7, r7, r0
 str r7, [sp, #0 +20]

L_interp_copy_cont :
# 446 "getpred.S"
 ldr r7, [sp, #0 +20]
 ldr r9, [sp, #0 +48]
 ldr r8, [sp, #0 +212]

 sub r11, r9, #4 -1
 mov r10, #4
L_loop_copy :
 ldrb r0, [r7], #1
 ldrb r1, [r7], #1
 ldrb r2, [r7], #1
 ldrb r3, [r7], r11
 strb r0, [r8], #1
 strb r1, [r8], #1
 strb r2, [r8], #1
 strb r3, [r8], #1+(16 -4)
 subs r10, r10, #1
 bne L_loop_copy
# 475 "getpred.S"
 b L_interp_chroma





L_interp_hf_vs :





 cmp r2, #0
 bne L_interp_hs_vf
# 513 "getpred.S"
 sub r4, r9, #4
 sub r3, r1, #2
 sub r5, r10, #4 +3+2
 cmp r0, r4
 cmpls r3, r5
 bls L_interp_hf_vs_no_bound_checks


 add r8, sp, #0 +232
 sub r1, r1, #2
 mov r3, #4 +2+3
 bl L_get_ref_area_4xX
 add r0, r0, #2*8
 str r0, [sp, #0 +20]
 mov r2, #8
 str r2, [sp, #0 +48]
 b L_interp_hf_vs_cont

L_interp_hf_vs_no_bound_checks :

 mla r0, r9, r1, r0
 str r9, [sp, #0 +48]
 add r7, r7, r0
 str r7, [sp, #0 +20]

L_interp_hf_vs_cont :
# 557 "getpred.S"
 ldr r7, [sp, #0 +20]
 ldr r9, [sp, #0 +48]
 ldr r8, [sp, #0 +212]
 ldr r12, L_clipBufPtr
 sub r7, r7, r9, lsl #1
 mov r11, r9, lsl #3
 rsb r11, r11, #1
 mov r10, #4
L_loop_hf_vs_or_hs_vf :
 ldrb r0, [r7], r9
 ldrb r1, [r7], r9
 ldrb r2, [r7], r9
 ldrb r3, [r7], r9
 ldrb r4, [r7], r9
 ldrb r5, [r7], r9

 rsb r6, r1, r2, lsl #2
 add r6, r6, r3, lsl #2
 sub r6, r6, r4
 add r0, r0, r5
 add r6, r6, r6, lsl #2
 add r6, r0, r6

 ldrb r0, [r7], r9
 ldrb r14, [r12, r6, asr #4]

 rsb r6, r2, r3, lsl #2
 add r6, r6, r4, lsl #2
 sub r6, r6, r5
 add r1, r1, r0
 add r6, r6, r6, lsl #2
 add r6, r1, r6
 strb r14, [r8], #16

 ldrb r1, [r7], r9
 ldrb r14, [r12, r6, asr #4]

 rsb r6, r3, r4, lsl #2
 add r6, r6, r5, lsl #2
 sub r6, r6, r0
 add r2, r2, r1
 add r6, r6, r6, lsl #2
 add r6, r2, r6
 strb r14, [r8], #16

 ldrb r2, [r7], r11
 ldrb r14, [r12, r6, asr #4]

 rsb r6, r4, r5, lsl #2
 add r6, r6, r0, lsl #2
 sub r6, r6, r1
 add r3, r3, r2
 add r6, r6, r6, lsl #2
 add r6, r3, r6
 ldrb r6, [r12, r6, asr #4]

 strb r14, [r8], #16
 subs r10, r10, #1
 strb r6, [r8], #-(4 -1)*16 +1

 bne L_loop_hf_vs_or_hs_vf

L_linear_interp_hf_vs_or_hs_vf :

 ldr r0, [sp, #0 +40]
 ldr r1, [sp, #0 +44]
 mov r2, r0, lsl #31
 orrs r2, r2, r1, lsl #31
 beq L_interp_chroma
# 638 "getpred.S"
 ldr r9, [sp, #0 +48]
 ldr r7, [sp, #0 +20]
 ldr r8, [sp, #0 +212]
 cmp r1, #3
 addeq r7, r7, r9
 add r7, r7, r0, lsr #1
 ldr r4, L_0x7f7f7f7f

 sub r11, r9, #4 -1
 mov r10, #4
L_loop_linear :

 ldrb r0, [r7], #1
 ldrb r1, [r7], #1
 ldrb r2, [r7], #1
 ldrb r3, [r7], r11
 subs r10, r10, #1
 orr r0, r0, r1, lsl #8
 ldr r1, [r8]
 orr r0, r0, r2, lsl #16
 orr r0, r0, r3, lsl #24
 orr r2, r0, r1
 bic r2, r2, r4, ror #7
 and r0, r4, r0, lsr #1
 and r1, r4, r1, lsr #1
 add r0, r0, r1
 add r0, r0, r2
 str r0, [r8], #16
 bne L_loop_linear
# 700 "getpred.S"
 b L_interp_chroma
# 711 "getpred.S"
L_interp_hs_vf :





 cmp r3, #0
 bne L_interp_hh_vs
# 743 "getpred.S"
 sub r2, r0, #2
 sub r4, r9, #4 +2+3
 sub r5, r10, #4
 cmp r2, r4
 cmpls r1, r5
 bls L_interp_hs_vf_no_bound_checks


 add r8, sp, #0 +232
 sub r0, r0, #2
 mov r3, #4
 bl L_get_ref_area_9xX
 add r0, r0, #2
 str r0, [sp, #0 +20]
 mov r2, #16
 str r2, [sp, #0 +48]
 b L_interp_hs_vf_cont

L_interp_hs_vf_no_bound_checks :

 mla r0, r9, r1, r0
 str r9, [sp, #0 +48]
 add r7, r7, r0
 str r7, [sp, #0 +20]

L_interp_hs_vf_cont :
# 787 "getpred.S"
 ldr r7, [sp, #0 +20]
 ldr r11, [sp, #0 +48]
 ldr r8, [sp, #0 +212]
 ldr r12, L_clipBufPtr
 sub r7, r7, #2
 sub r11, r11, #8
 mov r10, #4
L_loop_hs_vf :
 ldrb r0, [r7], #1
 ldrb r1, [r7], #1
 ldrb r2, [r7], #1
 ldrb r3, [r7], #1
 ldrb r4, [r7], #1
 ldrb r5, [r7], #1

 rsb r6, r1, r2, lsl #2
 add r6, r6, r3, lsl #2
 sub r6, r6, r4
 add r0, r0, r5
 add r6, r6, r6, lsl #2
 add r6, r0, r6

 ldrb r0, [r7], #1
 ldrb r14, [r12, r6, asr #4]

 rsb r6, r2, r3, lsl #2
 add r6, r6, r4, lsl #2
 sub r6, r6, r5
 add r1, r1, r0
 add r6, r6, r6, lsl #2
 add r6, r1, r6
 strb r14, [r8], #1

 ldrb r1, [r7], #1
 ldrb r14, [r12, r6, asr #4]

 rsb r6, r3, r4, lsl #2
 add r6, r6, r5, lsl #2
 sub r6, r6, r0
 add r2, r2, r1
 add r6, r6, r6, lsl #2
 add r6, r2, r6
 strb r14, [r8], #1

 ldrb r2, [r7], r11
 ldrb r14, [r12, r6, asr #4]

 rsb r6, r4, r5, lsl #2
 add r6, r6, r0, lsl #2
 sub r6, r6, r1
 add r3, r3, r2
 add r6, r6, r6, lsl #2
 add r6, r3, r6
 ldrb r6, [r12, r6, asr #4]

 strb r14, [r8], #1
 subs r10, r10, #1
 strb r6, [r8], #1+(16 -4)

 bne L_loop_hs_vf
# 860 "getpred.S"
 b L_linear_interp_hf_vs_or_hs_vf






L_interp_hh_vs :
# 886 "getpred.S"
 sub r4, r0, #2
 sub r5, r9, #4 +2+3
 sub r6, r1, #2
 sub r8, r10, #4 +2+3
 cmp r4, r5
 cmpls r6, r8
 bls L_interp_hh_vs_no_bound_checks


 add r8, sp, #0 +232
 sub r0, r0, #2
 sub r1, r1, #2
 mov r3, #4 +2+3
 bl L_get_ref_area_9xX
 add r0, r0, #2*16+2
 str r0, [sp, #0 +20]
 mov r2, #16
 str r2, [sp, #0 +48]
 ldr r2, [sp, #0 +24]
 ldr r3, [sp, #0 +28]
 and r2, r2, #3
 and r3, r3, #3
 b L_interp_hh_vs_cont

L_interp_hh_vs_no_bound_checks :

 mla r0, r9, r1, r0
 str r9, [sp, #0 +48]
 add r7, r7, r0
 str r7, [sp, #0 +20]

L_interp_hh_vs_cont :





 cmp r2, #2
 bne L_interp_vh_hq
# 951 "getpred.S"
 ldr r7, [sp, #0 +20]
 ldr r11, [sp, #0 +48]
 add r8, sp, #0 +64
 sub r7, r7, r11, lsl #1
 sub r7, r7, #2
 sub r11, r11, #8
 mov r10, #4 +2+3
L_loop_hh_vs_horiz :
 ldrb r0, [r7], #1
 ldrb r1, [r7], #1
 ldrb r2, [r7], #1
 ldrb r3, [r7], #1
 ldrb r4, [r7], #1
 ldrb r5, [r7], #1

 rsb r6, r1, r2, lsl #2
 add r6, r6, r3, lsl #2
 sub r6, r6, r4
 add r0, r0, r5
 add r6, r6, r6, lsl #2
 add r6, r0, r6
 str r6, [r8], #4

 ldrb r0, [r7], #1

 rsb r6, r2, r3, lsl #2
 add r6, r6, r4, lsl #2
 sub r6, r6, r5
 add r1, r1, r0
 add r6, r6, r6, lsl #2
 add r6, r1, r6
 str r6, [r8], #4

 ldrb r1, [r7], #1

 rsb r6, r3, r4, lsl #2
 add r6, r6, r5, lsl #2
 sub r6, r6, r0
 add r2, r2, r1
 add r6, r6, r6, lsl #2
 add r6, r2, r6
 str r6, [r8], #4

 ldrb r2, [r7], r11

 rsb r6, r4, r5, lsl #2
 add r6, r6, r0, lsl #2
 sub r6, r6, r1
 add r3, r3, r2
 add r6, r6, r6, lsl #2
 add r6, r3, r6
 str r6, [r8], #4

 subs r10, r10, #1
 bne L_loop_hh_vs_horiz
# 1021 "getpred.S"
 ldr r12, L_clipBufPtr
 add r7, sp, #0 +64
 ldr r8, [sp, #0 +212]
 mov r10, #4
L_loop_hh_vs_vert :
 ldr r0, [r7], #4*4
 ldr r1, [r7], #4*4
 ldr r2, [r7], #4*4
 ldr r3, [r7], #4*4
 ldr r4, [r7], #4*4
 ldr r5, [r7], #4*4

 rsb r6, r1, r2, lsl #2
 add r6, r6, r3, lsl #2
 sub r6, r6, r4
 add r0, r0, r5
 add r6, r6, r6, lsl #2
 add r6, r0, r6

 ldr r0, [r7], #4*4
 ldrb r14, [r12, r6, asr #9]

 rsb r6, r2, r3, lsl #2
 add r6, r6, r4, lsl #2
 sub r6, r6, r5
 add r1, r1, r0
 add r6, r6, r6, lsl #2
 add r6, r1, r6
 strb r14, [r8], #16

 ldr r1, [r7], #4*4
 ldrb r14, [r12, r6, asr #9]

 rsb r6, r3, r4, lsl #2
 add r6, r6, r5, lsl #2
 sub r6, r6, r0
 add r2, r2, r1
 add r6, r6, r6, lsl #2
 add r6, r2, r6
 strb r14, [r8], #16

 ldr r2, [r7], #-8*(4*4)+4
 ldrb r14, [r12, r6, asr #9]

 rsb r6, r4, r5, lsl #2
 add r6, r6, r0, lsl #2
 sub r6, r6, r1
 add r3, r3, r2
 add r6, r6, r6, lsl #2
 add r6, r3, r6
 ldrb r6, [r12, r6, asr #9]

 strb r14, [r8], #16
 subs r10, r10, #1
 strb r6, [r8], #-((4 -1)*16)+1

 bne L_loop_hh_vs_vert

 ldr r1, [sp, #0 +44]
 tst r1, #1
 beq L_interp_chroma
# 1097 "getpred.S"
 add r7, sp, #0 +64 +2*4*4
 ldr r8, [sp, #0 +212]
 ldr r12, L_clipBufPtr
 cmp r1, #3
 addeq r7, r7, #4*4
 mov r10, #4
 ldr r4, L_0x7f7f7f7f
L_loop_linear_hh_vs :

 ldmia r7!, {r0-r3}
 ldrb r0, [r12, r0, asr #4]
 ldrb r1, [r12, r1, asr #4]
 ldrb r2, [r12, r2, asr #4]
 ldrb r3, [r12, r3, asr #4]
 subs r10, r10, #1
 orr r0, r0, r1, lsl #8
 ldr r1, [r8]
 orr r0, r0, r2, lsl #16
 orr r0, r0, r3, lsl #24

 orr r2, r0, r1
 bic r2, r2, r4, ror #7
 and r0, r4, r0, lsr #1
 and r1, r4, r1, lsr #1
 add r0, r0, r1





 add r0, r0, r2
 str r0, [r8], #16
 bne L_loop_linear_hh_vs

 b L_interp_chroma






L_interp_vh_hq :





 cmp r3, #2
 bne L_interp_diagonal
# 1172 "getpred.S"
 ldr r7, [sp, #0 +20]
 ldr r9, [sp, #0 +48]
 add r8, sp, #0 +64
 sub r7, r7, r9, lsl #1
 sub r7, r7, #2
 mov r11, r9, lsl #3
 rsb r11, r11, #1
 mov r10, #4 +2+3
L_loop_vh_hq_vert :
 ldrb r0, [r7], r9
 ldrb r1, [r7], r9
 ldrb r2, [r7], r9
 ldrb r3, [r7], r9
 ldrb r4, [r7], r9
 ldrb r5, [r7], r9

 rsb r6, r1, r2, lsl #2
 add r6, r6, r3, lsl #2
 sub r6, r6, r4
 add r0, r0, r5
 add r6, r6, r6, lsl #2
 add r6, r0, r6
 str r6, [r8], #(4 +2+3)*4

 ldrb r0, [r7], r9

 rsb r6, r2, r3, lsl #2
 add r6, r6, r4, lsl #2
 sub r6, r6, r5
 add r1, r1, r0
 add r6, r6, r6, lsl #2
 add r6, r1, r6
 str r6, [r8], #(4 +2+3)*4

 ldrb r1, [r7], r9

 rsb r6, r3, r4, lsl #2
 add r6, r6, r5, lsl #2
 sub r6, r6, r0
 add r2, r2, r1
 add r6, r6, r6, lsl #2
 add r6, r2, r6
 str r6, [r8], #(4 +2+3)*4

 ldrb r2, [r7], r11

 rsb r6, r4, r5, lsl #2
 add r6, r6, r0, lsl #2
 sub r6, r6, r1
 add r3, r3, r2
 add r6, r6, r6, lsl #2
 add r6, r3, r6
 str r6, [r8], #-3*(4 +2+3)*4+4

 subs r10, r10, #1
 bne L_loop_vh_hq_vert
# 1251 "getpred.S"
 ldr r0, [sp, #0 +40]
 add r7, sp, #0 +64
 ldr r8, [sp, #0 +212]
 ldr r12, L_clipBufPtr
 add r9, sp, #0 +64 +2*4
 cmp r0, #3
 addeq r9, r9, #4
 mov r10, #4
L_loop_vh_hq_horiz :

 ldmia r7!, {r0-r5}

 rsb r6, r1, r2, lsl #2
 add r6, r6, r3, lsl #2
 sub r6, r6, r4
 ldr r14, [r9], #4
 add r6, r6, r6, lsl #2
 add r6, r0, r6
 add r6, r6, r5

 ldrb r14, [r12, r14, asr #4]
 ldrb r0, [r12, r6, asr #9]


 rsb r6, r2, r3, lsl #2
 add r6, r6, r4, lsl #2
 sub r6, r6, r5

 add r14, r14, r0
 add r14, r14, #1
 mov r14, r14, lsr #1
 strb r14, [r8], #1
 ldr r14, [r9], #4

 ldr r0, [r7], #4
 add r6, r6, r6, lsl #2
 add r6, r1, r6
 add r6, r6, r0

 ldrb r14, [r12, r14, asr #4]
 ldrb r1, [r12, r6, asr #9]


 rsb r6, r3, r4, lsl #2
 add r6, r6, r5, lsl #2
 sub r6, r6, r0

 add r14, r14, r1
 add r14, r14, #1
 mov r14, r14, lsr #1
 strb r14, [r8], #1
 ldr r14, [r9], #4

 ldr r1, [r7], #4
 add r6, r6, r6, lsl #2
 add r6, r2, r6
 add r6, r6, r1

 ldrb r14, [r12, r14, asr #4]
 ldrb r2, [r12, r6, asr #9]


 rsb r6, r4, r5, lsl #2
 add r6, r6, r0, lsl #2
 sub r6, r6, r1

 add r14, r14, r2
 add r14, r14, #1
 mov r14, r14, lsr #1
 strb r14, [r8], #1
 ldr r14, [r9], #6*4

 ldr r2, [r7], #4
 add r6, r6, r6, lsl #2
 add r6, r3, r6
 add r6, r6, r2

 ldrb r14, [r12, r14, asr #4]
 ldrb r3, [r12, r6, asr #9]

 subs r10, r10, #1

 add r14, r14, #1
 add r14, r14, r3
 mov r14, r14, lsr #1
 strb r14, [r8], #1+(16 -4)
# 1412 "getpred.S"
 bne L_loop_vh_hq_horiz

 b L_interp_chroma






L_interp_diagonal :
# 1454 "getpred.S"
 ldr r0, [sp, #0 +40]
 ldr r7, [sp, #0 +20]
 ldr r9, [sp, #0 +48]
 ldr r8, [sp, #0 +212]
 ldr r12, L_clipBufPtr
 sub r7, r7, r9, lsl #1
 add r7, r7, r0, lsr #1
 mov r11, r9, lsl #3
 rsb r11, r11, #1
 mov r10, #4
L_loop_diag_vert :
 ldrb r0, [r7], r9
 ldrb r1, [r7], r9
 ldrb r2, [r7], r9
 ldrb r3, [r7], r9
 ldrb r4, [r7], r9
 ldrb r5, [r7], r9

 rsb r6, r1, r2, lsl #2
 add r6, r6, r3, lsl #2
 sub r6, r6, r4
 add r0, r0, r5
 add r6, r6, r6, lsl #2
 add r6, r0, r6

 ldrb r0, [r7], r9
 ldrb r14, [r12, r6, asr #4]

 rsb r6, r2, r3, lsl #2
 add r6, r6, r4, lsl #2
 sub r6, r6, r5
 add r1, r1, r0
 add r6, r6, r6, lsl #2
 add r6, r1, r6
 strb r14, [r8], #16

 ldrb r1, [r7], r9
 ldrb r14, [r12, r6, asr #4]

 rsb r6, r3, r4, lsl #2
 add r6, r6, r5, lsl #2
 sub r6, r6, r0
 add r2, r2, r1
 add r6, r6, r6, lsl #2
 add r6, r2, r6
 strb r14, [r8], #16

 ldrb r2, [r7], r11
 ldrb r14, [r12, r6, asr #4]

 rsb r6, r4, r5, lsl #2
 add r6, r6, r0, lsl #2
 sub r6, r6, r1
 add r3, r3, r2
 add r6, r6, r6, lsl #2
 add r6, r3, r6
 ldrb r6, [r12, r6, asr #4]

 strb r14, [r8], #16
 subs r10, r10, #1
 strb r6, [r8], #-(4 -1)*16 +1

 bne L_loop_diag_vert
# 1536 "getpred.S"
 ldr r1, [sp, #0 +44]
 ldr r7, [sp, #0 +20]
 ldr r11, [sp, #0 +48]
 ldr r8, [sp, #0 +212]
 ldr r12, L_clipBufPtr
 sub r7, r7, #2
 movs r1, r1, lsr #1
 addne r7, r7, r11
 sub r11, r11, #8
 mov r10, #4
 ldr r9, L_0x7f7f7f7f
L_loop_diag_horiz :
 ldrb r0, [r7], #1
 ldrb r1, [r7], #1
 ldrb r2, [r7], #1
 ldrb r3, [r7], #1
 ldrb r4, [r7], #1
 ldrb r5, [r7], #1

 rsb r6, r1, r2, lsl #2
 add r6, r6, r3, lsl #2
 sub r6, r6, r4
 add r6, r6, r6, lsl #2
 add r6, r0, r6
 add r6, r6, r5
 ldrb r14, [r12, r6, asr #4]


 rsb r6, r2, r3, lsl #2
 add r6, r6, r4, lsl #2
 ldrb r0, [r7], #1
 sub r6, r6, r5
 add r6, r6, r6, lsl #2
 add r6, r1, r6
 add r6, r6, r0
 ldrb r1, [r12, r6, asr #4]


 rsb r6, r3, r4, lsl #2
 add r6, r6, r5, lsl #2
 orr r14, r14, r1, lsl #8
 ldrb r1, [r7], #1
 sub r6, r6, r0
 add r6, r6, r6, lsl #2
 add r6, r2, r6
 add r6, r6, r1
 ldrb r2, [r12, r6, asr #4]


 rsb r6, r4, r5, lsl #2
 add r6, r6, r0, lsl #2
 orr r14, r14, r2, lsl #16
 ldrb r2, [r7], r11
 sub r6, r6, r1
 add r6, r6, r6, lsl #2
 add r6, r3, r6
 add r6, r6, r2
 ldrb r3, [r12, r6, asr #4]


 ldr r1, [r8]
 subs r10, r10, #1
 orr r0, r14, r3, lsl #24

 orr r2, r0, r1
 bic r2, r2, r9, ror #7
 and r0, r9, r0, lsr #1
 and r1, r9, r1, lsr #1
 add r0, r0, r1





 add r0, r0, r2
 str r0, [r8], #16

 bne L_loop_diag_horiz
# 1625 "getpred.S"
L_interp_chroma :
# 1640 "getpred.S"
 ldr r0, [sp, #0 +24]
 ldr r1, [sp, #0 +28]

 and r2, r0, #7
 and r3, r1, #7


 mov r0, r0, asr #3
 mov r1, r1, asr #3

 ldr r6, [sp, #376 +4*10 +0]
 ldr r9, [sp, #0 +56]
 ldr r10, [sp, #0 +60]
 ldr r7, [r6, #4]
 ldr r6, [r6, #8]
# 1673 "getpred.S"
 sub r4, r9, #4/2
 sub r5, r10, #4/2
 cmp r0, r4
 cmplo r1, r5
 blo L_interp_chroma_no_bound_checks


 add r8, sp, #0 +232
 bl L_get_ref_area_C
 ldr r0, [sp, #0 +24]
 ldr r1, [sp, #0 +28]
 and r2, r0, #7
 and r3, r1, #7
 add r7, sp, #0 +232
 add r6, sp, #0 +232 +3*3
 mov r9, #3-2
 b L_interp_chroma_cont

L_interp_chroma_no_bound_checks :

 mla r0, r9, r1, r0
 sub r9, r9, #2
 add r7, r7, r0
 add r6, r6, r0

L_interp_chroma_cont :
# 1709 "getpred.S"
 mul r14, r2, r3
 rsb r10, r3, #8
 rsb r12, r14, r3, lsl #3
 rsb r11, r14, r2, lsl #3
 rsb r10, r11, r10, lsl #3






 ldr r0, [sp, #0 +12]
 ldr r1, [sp, #0 +16]
 ldr r8, [sp, #0 +220]
 add r2, r0, r1, lsl #4
 add r8, r8, r2, lsl #1
# 1741 "getpred.S"
 mov r5, #2
L_loop_chroma :




 ldrb r0, [r7], #1
 ldrb r1, [r7], #1
 ldrb r3, [r7], r9
 ldrb r2, [r7], #1
 mul r0, r10, r0
 mla r0, r1, r11, r0
 mul r1, r10, r1
 mla r1, r3, r11, r1
 ldrb r3, [r7], #1
 mla r0, r2, r12, r0
 mla r0, r3, r14, r0
 mla r1, r3, r12, r1
 add r0, r0, #32
 mov r0, r0, lsr #6
 strb r0, [r8], #1
 ldrb r0, [r7], r9
 mul r2, r10, r2
 mla r2, r3, r11, r2
 mla r1, r0, r14, r1
 mul r3, r10, r3
 mla r3, r0, r11, r3
 ldrb r0, [r7], #1
 add r1, r1, #32
 mov r1, r1, lsr #6
 strb r1, [r8], #-1+16
 ldrb r1, [r7], #1
 mla r2, r0, r12, r2
 ldrb r0, [r7]
 mla r2, r1, r14, r2
 mla r3, r1, r12, r3
 mla r3, r0, r14, r3
 add r2, r2, #32
 mov r2, r2, lsr #6
 strb r2, [r8], #1
 add r3, r3, #32
 mov r3, r3, lsr #6
 strb r3, [r8], #-1-16+8
# 1823 "getpred.S"
 mov r7, r6
 subs r5, r5, #1
 bne L_loop_chroma





 ldr r0, [sp, #0 +12]
 add r0, r0, #1
 str r0, [sp, #0 +12]
 cmp r0, #2
 blt L_loop_interp_main_x





 ldr r0, [sp, #0 +16]
 ldr r1, [sp, #376 +4*10 +12]
 ldr r2, [sp, #0 +0]
 add r0, r0, #1
 str r0, [sp, #0 +16]
 cmp r0, #2
 add r1, r1, r2, lsl #2
 str r1, [sp, #376 +4*10 +12]
 blt L_loop_interp_main_y




 add sp, sp, #376
 ldmfd sp!, {r4-r12, lr}
 bx lr
# 1886 "getpred.S"
 .global L_get_ref_area_4xX

L_get_ref_area_4xX :

 bic r4, r1, r1, asr #31
 cmp r4, r10
 subge r4, r10, #1
 mla r7, r9, r4, r7

 cmp r0, #0
 bge L_no_left_bound_4xX





 cmp r0, #-3
 movlt r0, #-3
 and r0, r0, #3
 add r0, r0, r8
 add r8, r8, #1

L_left_bound_copy_lines_4xX :

 ldr r6, [r7]

 adds r1, r1, #1
 cmpgt r10, r1
 addgt r7, r7, r9
 subs r3, r3, #1

 strb r6, [r8], #1
 strb r6, [r8], #1
 strb r6, [r8], #1
 str r6, [r8], #5

 bne L_left_bound_copy_lines_4xX

 bx lr

L_no_left_bound_4xX :

 add r4, r0, #4
 cmp r4, r9
 bgt L_right_bound_4xX





 add r7, r7, r0
 bic r7, r7, #3
 and r0, r0, #3

 subeq r7, r7, #4
 addeq r0, r0, #4

 add r0, r0, r8

L_no_bound_copy_lines_4xX :

 ldmia r7, {r5, r6}

 adds r1, r1, #1
 cmpgt r10, r1
 addgt r7, r7, r9
 subs r3, r3, #1

 stmia r8!, {r5, r6}

 bne L_no_bound_copy_lines_4xX

 bx lr

L_right_bound_4xX :





 cmp r0, r9
 subge r0, r9, #1

 add r7, r7, r9
 and r0, r0, #3
 add r0, r0, r8

L_right_bound_copy_lines_4xX :

 ldr r5, [r7, #-4]

 adds r1, r1, #1
 cmpgt r10, r1
 and r6, r5, #0xff000000
 addgt r7, r7, r9
 orr r6, r6, r6, lsr #8
 subs r3, r3, #1
 orr r6, r6, r6, lsr #16

 stmia r8!, {r5, r6}

 bne L_right_bound_copy_lines_4xX

 bx lr
# 2019 "getpred.S"
 .global L_get_ref_area_9xX

L_get_ref_area_9xX :

 bic r4, r1, r1, asr #31
 cmp r4, r10
 subge r4, r10, #1
 mla r7, r9, r4, r7

 cmp r0, #0
 bge L_no_left_bound_9xX





 cmp r0, #-8
 movlt r0, #-8
 and r0, r0, #7
 add r0, r0, r8

L_left_bound_copy_lines_9xX :

 ldmia r7, {r5, r6}
 adds r1, r1, #1
 and r4, r5, #255
 cmpgt r10, r1
 orr r4, r4, r4, lsl #8
 addgt r7, r7, r9
 orr r4, r4, r4, lsl #16
 subs r3, r3, #1
 str r4, [r8], #4
 stmia r8!, {r4-r6}

 bne L_left_bound_copy_lines_9xX

 bx lr

L_no_left_bound_9xX :

 add r4, r0, #9
 cmp r4, r9
 bgt L_right_bound_9xX





 add r7, r7, r0
 and r0, r0, #3
 sub r7, r7, r0
 add r0, r0, r8

L_no_bound_copy_lines_9xX :

 ldmia r7, {r4-r6}
 adds r1, r1, #1
 cmpgt r10, r1
 addgt r7, r7, r9
 subs r3, r3, #1
 stmia r8!, {r4, r5}
 str r6, [r8], #8

 bne L_no_bound_copy_lines_9xX

 bx lr

L_right_bound_9xX :





 cmp r0, r9
 subge r0, r9, #1

 add r7, r7, r9
 and r0, r0, #7
 add r0, r0, r8

L_right_bound_copy_lines_9xX :

 ldr r4, [r7, #-8]
 ldr r5, [r7, #-4]
 adds r1, r1, #1
 cmpgt r10, r1
 and r6, r5, #0xff000000
 addgt r7, r7, r9
 orr r6, r6, r6, lsr #8
 subs r3, r3, #1
 orr r6, r6, r6, lsr #16
 stmia r8!, {r4-r6}
 str r6, [r8], #4

 bne L_right_bound_copy_lines_9xX

 bx lr
# 2144 "getpred.S"
 .global L_get_ref_area_C

L_get_ref_area_C :
# 2156 "getpred.S"
 mul r1, r9, r1
 mul r10, r9, r10

 mov r2, #3

 cmn r0, #1
 bgt L_no_left_bound_C





 movlt r0, #0
 movge r0, #1

L_left_bound_copy_lines_c :

 bic r4, r1, r1, asr #31
 cmp r4, r10
 subge r4, r10, r9
 add r3, r7, r4
 ldrb r5, [r3], r0
 ldrb r11, [r3]
 add r3, r6, r4
 strb r5, [r8], #1
 ldrb r12, [r3], r0
 strb r5, [r8], #1
 ldrb r5, [r3]
 strb r11, [r8], #1
 strb r12, [r8, #6]
 strb r12, [r8, #7]
 strb r5, [r8, #8]
 add r1, r1, r9
 subs r2, r2, #1
 bne L_left_bound_copy_lines_c

 bx lr

L_no_left_bound_C :

 add r4, r0, #2
 cmp r4, r9
 bge L_right_bound_C





 add r7, r7, r0
 add r6, r6, r0

L_no_bound_copy_lines_c :

 bic r4, r1, r1, asr #31
 cmp r4, r10
 subge r4, r10, r9
 add r3, r7, r4
 ldrb r5, [r3], #1
 ldrb r11, [r3], #1
 ldrb r12, [r3], #1
 add r3, r6, r4
 strb r5, [r8], #1
 strb r11, [r8], #1
 strb r12, [r8], #1
 ldrb r5, [r3], #1
 ldrb r11, [r3], #1
 ldrb r12, [r3], #1
 add r1, r1, r9
 strb r5, [r8, #6]
 strb r11, [r8, #7]
 strb r12, [r8, #8]
 subs r2, r2, #1
 bne L_no_bound_copy_lines_c

 bx lr

L_right_bound_C :





 movle r0, #1
 movgt r0, #0

 sub r4, r9, #1
 sub r4, r4, r0
 add r7, r7, r4
 add r6, r6, r4

L_right_bound_copy_lines_c :

 bic r4, r1, r1, asr #31
 cmp r4, r10
 subge r4, r10, r9
 add r3, r7, r4
 ldrb r5, [r3], r0
 ldrb r11, [r3]
 add r3, r6, r4
 strb r5, [r8], #1
 ldrb r12, [r3], r0
 ldrb r5, [r3]
 strb r11, [r8], #1
 strb r11, [r8], #1
 strb r12, [r8, #6]
 strb r5, [r8, #7]
 strb r5, [r8, #8]
 add r1, r1, r9
 subs r2, r2, #1
 bne L_right_bound_copy_lines_c

 bx lr



L_clipBufPtr :
 .word clip8Buf+512

L_0x7f7f7f7f :
 .word 0x7f7f7f7f







