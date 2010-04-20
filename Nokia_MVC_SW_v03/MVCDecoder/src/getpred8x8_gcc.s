# 1 "getpred8x8.S"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "getpred8x8.S"

# 1 "../include/armasmdef.h" 1
# 3 "getpred8x8.S" 2
# 20 "getpred8x8.S"
 .extern clip8Buf



 .text
# 58 "getpred8x8.S"
 .align 0




 .global mcpGetPred8x8
mcpGetPred8x8:
# 122 "getpred8x8.S"
 stmfd sp!, {r4-r12, lr}
 sub sp, sp, #696

 str r0, [sp, #0 +472]
 str r1, [sp, #0 +476]






 ldr r9, [sp, #696 +4*10 +4]
 ldr r10, [sp, #696 +4*10 +8]
 mov r4, r9, lsr #1
 mov r5, r10, lsr #1
 str r4, [sp, #0 +36]
 str r5, [sp, #0 +40]
# 147 "getpred8x8.S"
 ldr r5, [sp, #696 +4*10 +12]
 ldr r6, [sp, #0 +472]
 ldrsh r7, [r5]
 ldrsh r8, [r5, #2]
 str r6, [sp, #0 +460]
 add r0, r7, r2, lsl #4
 add r1, r8, r3, lsl #4

 ldr r6, [sp, #696 +4*10 +0]

 str r0, [sp, #0 +4]
 str r1, [sp, #0 +8]

 ldr r7, [r6]
# 170 "getpred8x8.S"
 and r2, r0, #3
 str r2, [sp, #0 +20]
 and r3, r1, #3
 str r3, [sp, #0 +24]
 mov r0, r0, asr #2
 mov r1, r1, asr #2
# 188 "getpred8x8.S"
L_interp_copy :





 orrs r4, r2, r3
 bne L_interp_hf_vs
# 220 "getpred8x8.S"
 sub r4, r9, #2*4
 sub r5, r10, #2*4
 cmp r0, r4
 cmpls r1, r5
 bls L_interp_copy_no_bound_checks


 add r8, sp, #0 +488
 mov r3, #2*4
 bl L_get_ref_area_XxX
 str r0, [sp, #0 +0]
 mov r2, #16
 str r2, [sp, #0 +28]
 b L_interp_copy_cont

L_interp_copy_no_bound_checks :

 mla r0, r9, r1, r0
 str r9, [sp, #0 +28]
 add r7, r7, r0
 str r7, [sp, #0 +0]

L_interp_copy_cont :
# 257 "getpred8x8.S"
 ldr r7, [sp, #0 +0]
 ldr r9, [sp, #0 +28]
 ldr r8, [sp, #0 +460]
 mov r10, #2*4

 sub r11, r9, #2*4 -1
L_loop_copy :
 ldrb r0, [r7], #1
 ldrb r1, [r7], #1
 ldrb r2, [r7], #1
 ldrb r3, [r7], #1
 strb r0, [r8], #1
 strb r1, [r8], #1
 strb r2, [r8], #1
 strb r3, [r8], #1
 ldrb r0, [r7], #1
 ldrb r1, [r7], #1
 ldrb r2, [r7], #1
 ldrb r3, [r7], r11
 strb r0, [r8], #1
 strb r1, [r8], #1
 strb r2, [r8], #1
 strb r3, [r8], #1+(16 -2*4)
 subs r10, r10, #1
# 294 "getpred8x8.S"
 bne L_loop_copy

 b L_interp_chroma






L_interp_hf_vs :





 cmp r2, #0
 bne L_interp_hs_vf
# 335 "getpred8x8.S"
 sub r4, r9, #2*4
 sub r3, r1, #2
 sub r5, r10, #2*4 +3+2
 cmp r0, r4
 cmpls r3, r5
 bls L_interp_hf_vs_no_bound_checks


 add r8, sp, #0 +488
 sub r1, r1, #2
 mov r3, #2*4 +2+3
 bl L_get_ref_area_XxX
 add r0, r0, #2*16
 str r0, [sp, #0 +0]
 mov r2, #16
 str r2, [sp, #0 +28]
 b L_interp_hf_vs_cont

L_interp_hf_vs_no_bound_checks :

 mla r0, r9, r1, r0
 str r9, [sp, #0 +28]
 add r7, r7, r0
 str r7, [sp, #0 +0]

L_interp_hf_vs_cont :
# 379 "getpred8x8.S"
 ldr r7, [sp, #0 +0]
 ldr r9, [sp, #0 +28]
 ldr r8, [sp, #0 +460]
 ldr r12, L_clipBufPtr
 sub r7, r7, r9, lsl #1
 mov r11, #16
 mov r0, r9, lsl #3
 add r0, r0, r9, lsl #2
 rsb r0, r0, #1
 mov r1, #-(2*4 -1)*16 +1
 bl L_interpolate_block_1D

L_linear_interp_hf_vs_or_hs_vf :

 ldr r0, [sp, #0 +20]
 ldr r1, [sp, #0 +24]
 mov r2, r0, lsl #31
 orrs r2, r2, r1, lsl #31
 beq L_interp_chroma
# 410 "getpred8x8.S"
 ldr r9, [sp, #0 +28]
 ldr r7, [sp, #0 +0]
 ldr r8, [sp, #0 +460]
 cmp r1, #3
 addeq r7, r7, r9
 add r7, r7, r0, lsr #1
 ldr r4, L_0x7f7f7f7f

 sub r11, r9, #2*4 -1
 mov r10, #2*4
L_loop_linear :

 ldrb r0, [r7], #1
 ldrb r1, [r7], #1
 ldrb r2, [r7], #1
 ldrb r3, [r7], #1
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
 str r0, [r8], #4

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
 str r0, [r8], #16 -4

 bne L_loop_linear
# 483 "getpred8x8.S"
 b L_interp_chroma
# 494 "getpred8x8.S"
L_interp_hs_vf :





 cmp r3, #0
 bne L_interp_hh_vs
# 526 "getpred8x8.S"
 sub r2, r0, #2
 sub r4, r9, #2*4 +2+3
 sub r5, r10, #2*4
 cmp r2, r4
 cmpls r1, r5
 bls L_interp_hs_vf_no_bound_checks


 add r8, sp, #0 +488
 sub r0, r0, #2
 mov r3, #2*4
 bl L_get_ref_area_XxX
 add r0, r0, #2
 str r0, [sp, #0 +0]
 mov r2, #16
 str r2, [sp, #0 +28]
 b L_interp_hs_vf_cont

L_interp_hs_vf_no_bound_checks :

 mla r0, r9, r1, r0
 str r9, [sp, #0 +28]
 add r7, r7, r0
 str r7, [sp, #0 +0]

L_interp_hs_vf_cont :
# 570 "getpred8x8.S"
 ldr r7, [sp, #0 +0]
 ldr r0, [sp, #0 +28]
 ldr r8, [sp, #0 +460]
 ldr r12, L_clipBufPtr
 sub r7, r7, #2
 mov r9, #1
 mov r11, #1
 sub r0, r0, #12
 mov r1, #1+(16 -2*4)
 bl L_interpolate_block_1D
# 594 "getpred8x8.S"
 b L_linear_interp_hf_vs_or_hs_vf






L_interp_hh_vs :
# 620 "getpred8x8.S"
 sub r4, r0, #2
 sub r5, r9, #2*4 +2+3
 sub r6, r1, #2
 sub r8, r10, #2*4 +2+3
 cmp r4, r5
 cmpls r6, r8
 bls L_interp_hh_vs_no_bound_checks


 add r8, sp, #0 +488
 sub r0, r0, #2
 sub r1, r1, #2
 mov r3, #2*4 +2+3
 bl L_get_ref_area_XxX
 add r0, r0, #2*16+2
 str r0, [sp, #0 +0]
 mov r2, #16
 str r2, [sp, #0 +28]
 ldr r2, [sp, #0 +20]
 ldr r3, [sp, #0 +24]
 b L_interp_hh_vs_cont

L_interp_hh_vs_no_bound_checks :

 mla r0, r9, r1, r0
 str r9, [sp, #0 +28]
 add r7, r7, r0
 str r7, [sp, #0 +0]

L_interp_hh_vs_cont :





 cmp r2, #2
 bne L_interp_vh_hq
# 683 "getpred8x8.S"
 ldr r11, [sp, #0 +28]
 ldr r7, [sp, #0 +0]
 add r8, sp, #0 +44
 sub r7, r7, r11, lsl #1
 sub r7, r7, #2
 mov r9, #1
 sub r11, r11, #12
 mov r10, #4
 mov r12, #4
 bl L_interpolate_block_1D_no_clip
# 709 "getpred8x8.S"
 ldr r12, L_clipBufPtr
 add r7, sp, #0 +44
 ldr r8, [sp, #0 +460]
 mov r10, #2*4
L_loop_hh_vs_vert :
 ldr r0, [r7], #2*4*4
 ldr r1, [r7], #2*4*4
 ldr r2, [r7], #2*4*4
 ldr r3, [r7], #2*4*4
 ldr r4, [r7], #2*4*4
 ldr r5, [r7], #2*4*4

 rsb r6, r1, r2, lsl #2
 add r6, r6, r3, lsl #2
 sub r6, r6, r4
 add r0, r0, r5
 add r6, r6, r6, lsl #2
 add r6, r0, r6

 ldr r0, [r7], #2*4*4
 ldrb r14, [r12, r6, asr #9]

 rsb r6, r2, r3, lsl #2
 add r6, r6, r4, lsl #2
 sub r6, r6, r5
 add r1, r1, r0
 add r6, r6, r6, lsl #2
 add r6, r1, r6
 strb r14, [r8], #16

 ldr r1, [r7], #2*4*4
 ldrb r14, [r12, r6, asr #9]

 rsb r6, r3, r4, lsl #2
 add r6, r6, r5, lsl #2
 sub r6, r6, r0
 add r2, r2, r1
 add r6, r6, r6, lsl #2
 add r6, r2, r6
 strb r14, [r8], #16

 ldr r2, [r7], #2*4*4
 ldrb r14, [r12, r6, asr #9]

 rsb r6, r4, r5, lsl #2
 add r6, r6, r0, lsl #2
 sub r6, r6, r1
 add r3, r3, r2
 add r6, r6, r6, lsl #2
 add r6, r3, r6
 strb r14, [r8], #16

 ldr r3, [r7], #2*4*4
 ldrb r14, [r12, r6, asr #9]

 rsb r6, r5, r0, lsl #2
 add r6, r6, r1, lsl #2
 sub r6, r6, r2
 add r4, r4, r3
 add r6, r6, r6, lsl #2
 add r6, r4, r6
 strb r14, [r8], #16

 ldr r4, [r7], #2*4*4
 ldrb r14, [r12, r6, asr #9]

 rsb r6, r0, r1, lsl #2
 add r6, r6, r2, lsl #2
 sub r6, r6, r3
 add r5, r5, r4
 add r6, r6, r6, lsl #2
 add r6, r5, r6
 strb r14, [r8], #16

 ldr r5, [r7], #2*4*4
 ldrb r14, [r12, r6, asr #9]

 rsb r6, r1, r2, lsl #2
 add r6, r6, r3, lsl #2
 sub r6, r6, r4
 add r0, r0, r5
 add r6, r6, r6, lsl #2
 add r6, r0, r6
 strb r14, [r8], #16

 ldr r0, [r7], #-12*(2*4*4)+4
 ldrb r14, [r12, r6, asr #9]

 rsb r6, r2, r3, lsl #2
 add r6, r6, r4, lsl #2
 sub r6, r6, r5
 add r1, r1, r0
 add r6, r6, r6, lsl #2
 add r6, r1, r6
 ldrb r6, [r12, r6, asr #9]

 strb r14, [r8], #16
 subs r10, r10, #1
 strb r6, [r8], #-((2*4 -1)*16)+1

 bne L_loop_hh_vs_vert

 ldr r1, [sp, #0 +24]
 tst r1, #1
 beq L_interp_chroma
# 829 "getpred8x8.S"
 add r7, sp, #0 +44 +2*2*4*4
 ldr r8, [sp, #0 +460]
 ldr r12, L_clipBufPtr
 cmp r1, #3
 addeq r7, r7, #2*4*4
 mov r10, #2*4
 ldr r4, L_0x7f7f7f7f
L_loop_linear_hh_vs :

 ldmia r7!, {r0-r3}
 ldrb r0, [r12, r0, asr #4]
 ldrb r1, [r12, r1, asr #4]
 ldrb r2, [r12, r2, asr #4]
 ldrb r3, [r12, r3, asr #4]
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
 str r0, [r8], #4


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
 str r0, [r8], #16 -4

 bne L_loop_linear_hh_vs

 b L_interp_chroma






L_interp_vh_hq :





 cmp r3, #2
 bne L_interp_diagonal
# 929 "getpred8x8.S"
 ldr r9, [sp, #0 +28]
 ldr r7, [sp, #0 +0]
 add r8, sp, #0 +44
 sub r7, r7, r9, lsl #1
 sub r7, r7, #2
 mov r11, r9, lsl #3
 add r11, r11, r9, lsl #2
 rsb r11, r11, #1
 mov r10, #(2*4 +2+3)*4
 mov r12, #(2*4 -1)*(2*4 +2+3)*4-4
 rsb r12, r12, #0
 bl L_interpolate_block_1D_no_clip
# 965 "getpred8x8.S"
 ldr r0, [sp, #0 +20]
 add r7, sp, #0 +44
 ldr r8, [sp, #0 +460]
 ldr r12, L_clipBufPtr
 add r9, sp, #0 +44 +2*4
 cmp r0, #3
 addeq r9, r9, #4
 mov r10, #2*4
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
 ldr r14, [r9], #4

 ldr r2, [r7], #4
 add r6, r6, r6, lsl #2
 add r6, r3, r6
 add r6, r6, r2

 ldrb r14, [r12, r14, asr #4]
 ldrb r3, [r12, r6, asr #9]


 rsb r6, r5, r0, lsl #2
 add r6, r6, r1, lsl #2
 sub r6, r6, r2

 add r14, r14, r3
 add r14, r14, #1
 mov r14, r14, lsr #1
 strb r14, [r8], #1
 ldr r14, [r9], #4

 ldr r3, [r7], #4
 add r6, r6, r6, lsl #2
 add r6, r4, r6
 add r6, r6, r3

 ldrb r14, [r12, r14, asr #4]
 ldrb r4, [r12, r6, asr #9]


 rsb r6, r0, r1, lsl #2
 add r6, r6, r2, lsl #2
 sub r6, r6, r3

 add r14, r14, r4
 add r14, r14, #1
 mov r14, r14, lsr #1
 strb r14, [r8], #1
 ldr r14, [r9], #4

 ldr r4, [r7], #4
 add r6, r6, r6, lsl #2
 add r6, r5, r6
 add r6, r6, r4

 ldrb r14, [r12, r14, asr #4]
 ldrb r5, [r12, r6, asr #9]


 rsb r6, r1, r2, lsl #2
 add r6, r6, r3, lsl #2
 sub r6, r6, r4

 add r14, r14, r5
 add r14, r14, #1
 mov r14, r14, lsr #1
 strb r14, [r8], #1
 ldr r14, [r9], #4

 ldr r5, [r7], #4
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
 ldr r14, [r9], #6*4

 ldr r0, [r7], #4
 add r6, r6, r6, lsl #2
 add r6, r1, r6
 add r6, r6, r0

 ldrb r14, [r12, r14, asr #4]
 ldrb r1, [r12, r6, asr #9]

 subs r10, r10, #1

 add r14, r14, #1
 add r14, r14, r1
 mov r14, r14, lsr #1
 strb r14, [r8], #1+(16 -2*4)
# 1274 "getpred8x8.S"
 bne L_loop_vh_hq_horiz

 b L_interp_chroma






L_interp_diagonal :
# 1316 "getpred8x8.S"
 ldr r7, [sp, #0 +0]
 ldr r9, [sp, #0 +28]
 ldr r0, [sp, #0 +20]
 ldr r8, [sp, #0 +460]
 ldr r12, L_clipBufPtr
 sub r7, r7, r9, lsl #1
 add r7, r7, r0, lsr #1
 mov r11, #16
 mov r0, r9, lsl #3
 add r0, r0, r9, lsl #2
 rsb r0, r0, #1
 mov r1, #-(2*4 -1)*16 +1
 bl L_interpolate_block_1D
# 1349 "getpred8x8.S"
 ldr r1, [sp, #0 +24]
 ldr r7, [sp, #0 +0]
 ldr r11, [sp, #0 +28]
 ldr r8, [sp, #0 +460]
 ldr r12, L_clipBufPtr
 sub r7, r7, #2
 movs r1, r1, lsr #1
 addne r7, r7, r11
 sub r11, r11, #12
 mov r10, #2*4
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
 ldrb r2, [r7], #1
 sub r6, r6, r1
 add r6, r6, r6, lsl #2
 add r6, r3, r6
 add r6, r6, r2
 ldrb r3, [r12, r6, asr #4]


 ldr r6, [r8]
 orr r14, r14, r3, lsl #24

 orr r3, r14, r6
 bic r3, r3, r9, ror #7
 and r14, r9, r14, lsr #1
 and r6, r9, r6, lsr #1
 add r14, r14, r6





 add r14, r14, r3
 str r14, [r8], #4


 rsb r6, r5, r0, lsl #2
 add r6, r6, r1, lsl #2
 ldrb r3, [r7], #1
 sub r6, r6, r2
 add r6, r6, r6, lsl #2
 add r6, r4, r6
 add r6, r6, r3
 ldrb r14, [r12, r6, asr #4]


 rsb r6, r0, r1, lsl #2
 add r6, r6, r2, lsl #2
 ldrb r4, [r7], #1
 sub r6, r6, r3
 add r6, r6, r6, lsl #2
 add r6, r5, r6
 add r6, r6, r4
 ldrb r5, [r12, r6, asr #4]


 rsb r6, r1, r2, lsl #2
 add r6, r6, r3, lsl #2
 orr r14, r14, r5, lsl #8
 ldrb r5, [r7], #1
 sub r6, r6, r4
 add r6, r6, r6, lsl #2
 add r6, r0, r6
 add r6, r6, r5
 ldrb r0, [r12, r6, asr #4]


 rsb r6, r2, r3, lsl #2
 add r6, r6, r4, lsl #2
 orr r14, r14, r0, lsl #16
 ldrb r0, [r7], r11
 sub r6, r6, r5
 add r6, r6, r6, lsl #2
 add r6, r1, r6
 add r6, r6, r0
 ldrb r1, [r12, r6, asr #4]


 ldr r6, [r8]
 subs r10, r10, #1
 orr r14, r14, r1, lsl #24

 orr r1, r14, r6
 bic r1, r1, r9, ror #7
 and r14, r9, r14, lsr #1
 and r6, r9, r6, lsr #1
 add r14, r14, r6





 add r14, r14, r1
 str r14, [r8], #16 -4

 bne L_loop_diag_horiz
# 1498 "getpred8x8.S"
L_interp_chroma :
# 1513 "getpred8x8.S"
 ldr r0, [sp, #0 +4]
 ldr r1, [sp, #0 +8]

 and r2, r0, #7
 and r3, r1, #7


 mov r0, r0, asr #3
 mov r1, r1, asr #3

 ldr r6, [sp, #696 +4*10 +0]
 ldr r9, [sp, #0 +36]
 ldr r10, [sp, #0 +40]
 ldr r7, [r6, #4]
 ldr r6, [r6, #8]
# 1546 "getpred8x8.S"
 sub r4, r9, #2*4/2
 sub r5, r10, #2*4/2
 cmp r0, r4
 cmplo r1, r5
 blo L_interp_chroma_no_bound_checks


 add r8, sp, #0 +488
 bl L_get_ref_area_C_5x5
 add r7, sp, #0 +488
 add r7, r7, r0
 add r6, r7, #5*8
 ldr r0, [sp, #0 +4]
 ldr r1, [sp, #0 +8]
 and r2, r0, #7
 and r3, r1, #7
 mov r9, #8-4
 b L_interp_chroma_cont

L_interp_chroma_no_bound_checks :

 mla r0, r9, r1, r0
 sub r9, r9, #4
 add r7, r7, r0
 add r6, r6, r0

L_interp_chroma_cont :
# 1583 "getpred8x8.S"
 mul r14, r2, r3
 rsb r10, r3, #8
 rsb r12, r14, r3, lsl #3
 rsb r11, r14, r2, lsl #3
 rsb r10, r11, r10, lsl #3






 ldr r8, [sp, #0 +476]
# 1610 "getpred8x8.S"
 mov r5, #2
 str r5, [sp, #0 +468]
 str r6, [sp, #0 +464]

L_loop_chroma :
# 1633 "getpred8x8.S"
 ldrb r0, [r7], #1
 ldrb r1, [r7], #1
 ldrb r2, [r7], #1
 ldrb r3, [r7], #1
 ldrb r4, [r7], r9

 mul r5, r0, r10
 ldrb r0, [r7], #1
 mla r5, r1, r11, r5
 mul r6, r1, r10
 ldrb r1, [r7], #1
 mla r5, r0, r12, r5
 mla r6, r2, r11, r6
 mla r5, r1, r14, r5
 mla r6, r1, r12, r6
 add r5, r5, #32
 mov r5, r5, lsr #6
 strb r5, [r8], #1
 mul r5, r2, r10
 ldrb r2, [r7], #1
 mla r5, r3, r11, r5
 add r6, r6, #32
 mla r6, r2, r14, r6
 mla r5, r2, r12, r5
 mov r6, r6, lsr #6
 strb r6, [r8], #1
 mul r6, r3, r10
 ldrb r3, [r7], #1
 mla r6, r4, r11, r6
 ldrb r4, [r7], r9
 add r5, r5, #32
 mla r5, r3, r14, r5
 mla r6, r3, r12, r6
 mla r6, r4, r14, r6
 mov r5, r5, lsr #6
 strb r5, [r8], #1
 add r6, r6, #32
 mov r6, r6, lsr #6
 strb r6, [r8], #1+16 -4



 mul r5, r0, r10
 ldrb r0, [r7], #1
 mla r5, r1, r11, r5
 mul r6, r1, r10
 ldrb r1, [r7], #1
 mla r5, r0, r12, r5
 mla r6, r2, r11, r6
 mla r5, r1, r14, r5
 mla r6, r1, r12, r6
 add r5, r5, #32
 mov r5, r5, lsr #6
 strb r5, [r8], #1
 mul r5, r2, r10
 ldrb r2, [r7], #1
 mla r5, r3, r11, r5
 add r6, r6, #32
 mla r6, r2, r14, r6
 mla r5, r2, r12, r5
 mov r6, r6, lsr #6
 strb r6, [r8], #1
 mul r6, r3, r10
 ldrb r3, [r7], #1
 mla r6, r4, r11, r6
 ldrb r4, [r7], r9
 add r5, r5, #32
 mla r5, r3, r14, r5
 mla r6, r3, r12, r6
 mla r6, r4, r14, r6
 mov r5, r5, lsr #6
 strb r5, [r8], #1
 add r6, r6, #32
 mov r6, r6, lsr #6
 strb r6, [r8], #1+16 -4



 mul r5, r0, r10
 ldrb r0, [r7], #1
 mla r5, r1, r11, r5
 mul r6, r1, r10
 ldrb r1, [r7], #1
 mla r5, r0, r12, r5
 mla r6, r2, r11, r6
 mla r5, r1, r14, r5
 mla r6, r1, r12, r6
 add r5, r5, #32
 mov r5, r5, lsr #6
 strb r5, [r8], #1
 mul r5, r2, r10
 ldrb r2, [r7], #1
 mla r5, r3, r11, r5
 add r6, r6, #32
 mla r6, r2, r14, r6
 mla r5, r2, r12, r5
 mov r6, r6, lsr #6
 strb r6, [r8], #1
 mul r6, r3, r10
 ldrb r3, [r7], #1
 mla r6, r4, r11, r6
 ldrb r4, [r7], r9
 add r5, r5, #32
 mla r5, r3, r14, r5
 mla r6, r3, r12, r6
 mla r6, r4, r14, r6
 mov r5, r5, lsr #6
 strb r5, [r8], #1
 add r6, r6, #32
 mov r6, r6, lsr #6
 strb r6, [r8], #1+16 -4



 mul r5, r0, r10
 ldrb r0, [r7], #1
 mla r5, r1, r11, r5
 mul r6, r1, r10
 ldrb r1, [r7], #1
 mla r5, r0, r12, r5
 mla r6, r2, r11, r6
 mla r5, r1, r14, r5
 mla r6, r1, r12, r6
 add r5, r5, #32
 mov r5, r5, lsr #6
 strb r5, [r8], #1
 mul r5, r2, r10
 ldrb r2, [r7], #1
 mla r5, r3, r11, r5
 add r6, r6, #32
 mla r6, r2, r14, r6
 mla r5, r2, r12, r5
 mov r6, r6, lsr #6
 strb r6, [r8], #1
 mul r6, r3, r10
 ldrb r3, [r7], #1
 mla r6, r4, r11, r6
 ldrb r4, [r7], r9
 add r5, r5, #32
 mla r5, r3, r14, r5
 mla r6, r3, r12, r6
 mla r6, r4, r14, r6
 mov r5, r5, lsr #6
 strb r5, [r8], #1
 add r6, r6, #32
 mov r6, r6, lsr #6
 strb r6, [r8], #-3-3*16 +16/2
# 1925 "getpred8x8.S"
 ldr r5, [sp, #0 +468]
 ldr r7, [sp, #0 +464]
 subs r5, r5, #1
 str r5, [sp, #0 +468]
 bne L_loop_chroma






 add sp, sp, #696
 ldmfd sp!, {r4-r12, lr}
 bx lr



 .align 0

L_clipBufPtr :
 .word clip8Buf+512

L_0x7f7f7f7f :
 .word 0x7f7f7f7f
# 1975 "getpred8x8.S"
L_interpolate_block_1D :

 stmdb sp!, {r0, r1, lr}
 mov r10, #2*4

L_loop_interp_8_pels :

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
 strb r14, [r8], r11

 ldrb r1, [r7], r9
 ldrb r14, [r12, r6, asr #4]

 rsb r6, r3, r4, lsl #2
 add r6, r6, r5, lsl #2
 sub r6, r6, r0
 add r2, r2, r1
 add r6, r6, r6, lsl #2
 add r6, r2, r6
 strb r14, [r8], r11

 ldrb r2, [r7], r9
 ldrb r14, [r12, r6, asr #4]

 rsb r6, r4, r5, lsl #2
 add r6, r6, r0, lsl #2
 sub r6, r6, r1
 add r3, r3, r2
 add r6, r6, r6, lsl #2
 add r6, r3, r6
 strb r14, [r8], r11

 ldrb r3, [r7], r9
 ldrb r14, [r12, r6, asr #4]

 rsb r6, r5, r0, lsl #2
 add r6, r6, r1, lsl #2
 sub r6, r6, r2
 add r4, r4, r3
 add r6, r6, r6, lsl #2
 add r6, r4, r6
 strb r14, [r8], r11

 ldrb r4, [r7], r9
 ldrb r14, [r12, r6, asr #4]

 rsb r6, r0, r1, lsl #2
 add r6, r6, r2, lsl #2
 sub r6, r6, r3
 add r5, r5, r4
 add r6, r6, r6, lsl #2
 add r6, r5, r6
 strb r14, [r8], r11

 ldrb r5, [r7], r9
 ldrb r14, [r12, r6, asr #4]

 rsb r6, r1, r2, lsl #2
 add r6, r6, r3, lsl #2
 sub r6, r6, r4
 add r0, r0, r5
 add r6, r6, r6, lsl #2
 add r6, r0, r6
 ldr r0, [sp]
 strb r14, [r8], r11
 ldrb r14, [r12, r6, asr #4]

 ldrb r0, [r7], r0

 rsb r6, r2, r3, lsl #2
 add r6, r6, r4, lsl #2
 sub r6, r6, r5
 add r1, r1, r0
 add r6, r6, r6, lsl #2
 add r6, r1, r6
 ldr r0, [sp, #4]
 ldrb r6, [r12, r6, asr #4]

 subs r10, r10, #1

 strb r14, [r8], r11
 strb r6, [r8], r0

 bne L_loop_interp_8_pels

 ldr lr, [sp, #8]
 add sp, sp, #12
 bx lr
# 2111 "getpred8x8.S"
L_interpolate_block_1D_no_clip :

 str lr, [sp, #-4]!
 mov r14, #2*4 +2+3

L_loop_interp_8_pels_no_clip :

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
 str r6, [r8], r10

 ldrb r0, [r7], r9

 rsb r6, r2, r3, lsl #2
 add r6, r6, r4, lsl #2
 sub r6, r6, r5
 add r1, r1, r0
 add r6, r6, r6, lsl #2
 add r6, r1, r6
 str r6, [r8], r10

 ldrb r1, [r7], r9

 rsb r6, r3, r4, lsl #2
 add r6, r6, r5, lsl #2
 sub r6, r6, r0
 add r2, r2, r1
 add r6, r6, r6, lsl #2
 add r6, r2, r6
 str r6, [r8], r10

 ldrb r2, [r7], r9

 rsb r6, r4, r5, lsl #2
 add r6, r6, r0, lsl #2
 sub r6, r6, r1
 add r3, r3, r2
 add r6, r6, r6, lsl #2
 add r6, r3, r6
 str r6, [r8], r10

 ldrb r3, [r7], r9

 rsb r6, r5, r0, lsl #2
 add r6, r6, r1, lsl #2
 sub r6, r6, r2
 add r4, r4, r3
 add r6, r6, r6, lsl #2
 add r6, r4, r6
 str r6, [r8], r10

 ldrb r4, [r7], r9

 rsb r6, r0, r1, lsl #2
 add r6, r6, r2, lsl #2
 sub r6, r6, r3
 add r5, r5, r4
 add r6, r6, r6, lsl #2
 add r6, r5, r6
 str r6, [r8], r10

 ldrb r5, [r7], r9

 rsb r6, r1, r2, lsl #2
 add r6, r6, r3, lsl #2
 sub r6, r6, r4
 add r0, r0, r5
 add r6, r6, r6, lsl #2
 add r6, r0, r6
 str r6, [r8], r10

 subs r14, r14, #1

 ldrb r0, [r7], r11

 rsb r6, r2, r3, lsl #2
 add r6, r6, r4, lsl #2
 sub r6, r6, r5
 add r1, r1, r0
 add r6, r6, r6, lsl #2
 add r6, r1, r6
 str r6, [r8], r12

 bne L_loop_interp_8_pels_no_clip

 ldr lr, [sp], #4
 bx lr
# 2235 "getpred8x8.S"
 .global L_get_ref_area_XxX

L_get_ref_area_XxX :

 bic r4, r1, r1, asr #31
 cmp r4, r10
 subge r4, r10, #1
 mla r7, r9, r4, r7

 cmp r0, #0
 bge L_no_left_bound_XxX

 cmp r0, #-4
 bge L_left_bound_XxX_minus_4
 cmp r0, #-8
 bge L_left_bound_XxX_minus_8





 cmp r0, #-12
 movlt r0, #-12
 and r0, r0, #3
 add r0, r0, r8
L_left_bound_copy_lines_XxX_minus_12 :
 ldr r5, [r7]
 adds r1, r1, #1
 and r4, r5, #255
 cmpgt r10, r1
 orr r4, r4, r4, lsl #8
 addgt r7, r7, r9
 orr r4, r4, r4, lsl #16
 subs r3, r3, #1
 str r4, [r8], #4
 str r4, [r8], #4
 stmia r8!, {r4-r5}
 bne L_left_bound_copy_lines_XxX_minus_12
 bx lr





L_left_bound_XxX_minus_8 :
 and r0, r0, #3
 add r0, r0, r8
L_left_bound_copy_lines_XxX_minus_8 :
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
 bne L_left_bound_copy_lines_XxX_minus_8
 bx lr





L_left_bound_XxX_minus_4 :
 and r0, r0, #3
 add r0, r0, r8
L_left_bound_copy_lines_XxX_minus_4 :
 ldmia r7, {r5, r6, r11}
 adds r1, r1, #1
 and r4, r5, #255
 cmpgt r10, r1
 orr r4, r4, r4, lsl #8
 addgt r7, r7, r9
 orr r4, r4, r4, lsl #16
 subs r3, r3, #1
 stmia r8!, {r4-r6, r11}
 bne L_left_bound_copy_lines_XxX_minus_4
 bx lr


L_no_left_bound_XxX :

 subs r4, r9, r0
 suble r0, r9, #1

 add r7, r7, r0
 and r0, r0, #3
 sub r7, r7, r0
 add r0, r0, r8

 cmp r4, #8
 ble L_right_bound_XxX_8_or_12
 cmp r4, #12
 ble L_right_bound_copy_lines_XxX_plus_4





L_no_bound_copy_lines_XxX :
 ldmia r7, {r4-r6, r11}
 adds r1, r1, #1
 cmpgt r10, r1
 addgt r7, r7, r9
 subs r3, r3, #1
 stmia r8!, {r4-r6, r11}
 bne L_no_bound_copy_lines_XxX
 bx lr





L_right_bound_copy_lines_XxX_plus_4 :
 ldmia r7, {r4-r6}
 adds r1, r1, #1
 cmpgt r10, r1
 and r11, r6, #0xff000000
 addgt r7, r7, r9
 orr r11, r11, r11, lsr #8
 subs r3, r3, #1
 orr r11, r11, r11, lsr #16
 stmia r8!, {r4-r6, r11}
 bne L_right_bound_copy_lines_XxX_plus_4
 bx lr


L_right_bound_XxX_8_or_12 :
 cmp r4, #4
 ble L_right_bound_copy_lines_XxX_plus_12





L_right_bound_copy_lines_XxX_plus_8 :
 ldmia r7, {r4-r5}
 adds r1, r1, #1
 cmpgt r10, r1
 and r6, r5, #0xff000000
 addgt r7, r7, r9
 orr r6, r6, r6, lsr #8
 subs r3, r3, #1
 orr r6, r6, r6, lsr #16
 stmia r8!, {r4-r6}
 str r6, [r8], #4
 bne L_right_bound_copy_lines_XxX_plus_8
 bx lr





L_right_bound_copy_lines_XxX_plus_12 :
 ldr r5, [r7]
 adds r1, r1, #1
 cmpgt r10, r1
 and r6, r5, #0xff000000
 addgt r7, r7, r9
 orr r6, r6, r6, lsr #8
 subs r3, r3, #1
 orr r6, r6, r6, lsr #16
 stmia r8!, {r5-r6}
 str r6, [r8], #4
 str r6, [r8], #4
 bne L_right_bound_copy_lines_XxX_plus_12
 bx lr
# 2433 "getpred8x8.S"
 .global L_get_ref_area_C_5x5

L_get_ref_area_C_5x5 :
# 2445 "getpred8x8.S"
 mul r1, r9, r1
 mul r10, r9, r10
 add r11, r8, #5*8

 mov r2, #5

 cmp r0, #0
 bge L_no_left_bound_C





 adds r0, r0, #4
 movmi r0, #0
L_left_bound_copy_lines_c :
 bic r4, r1, r1, asr #31
 cmp r4, r10
 subge r4, r10, r9
 ldr r5, [r7, r4]
 add r1, r1, r9
 strb r5, [r8], #1
 strb r5, [r8], #1
 strb r5, [r8], #1
 strb r5, [r8], #1
 str r5, [r8], #4
 ldr r5, [r6, r4]
 subs r2, r2, #1
 strb r5, [r11], #1
 strb r5, [r11], #1
 strb r5, [r11], #1
 strb r5, [r11], #1
 str r5, [r11], #4
 bne L_left_bound_copy_lines_c
 bx lr

L_no_left_bound_C :

 add r4, r0, #4
 cmp r4, r9
 bge L_right_bound_C





 add r7, r7, r0
 add r6, r6, r0
 and r0, r0, #3
 sub r7, r7, r0
 sub r6, r6, r0
L_no_bound_copy_lines_c :
 bic r4, r1, r1, asr #31
 cmp r4, r10
 subge r4, r10, r9
 add r3, r7, r4
 ldmia r3, {r5, r12}
 add r1, r1, r9
 stmia r8!, {r5, r12}
 add r3, r6, r4
 ldmia r3, {r5, r12}
 subs r2, r2, #1
 stmia r11!, {r5, r12}
 bne L_no_bound_copy_lines_c
 bx lr

L_right_bound_C :





 sub r4, r9, #4
 add r7, r7, r4
 add r6, r6, r4
 sub r0, r0, r4
 cmp r0, #3
 movgt r0, #3
L_right_bound_copy_lines_c :
 bic r4, r1, r1, asr #31
 cmp r4, r10
 subge r4, r10, r9
 ldr r5, [r7, r4]
 add r1, r1, r9
 and r12, r5, #0xff000000
 orr r12, r12, r12, lsr #8
 orr r12, r12, r12, lsr #16
 stmia r8!, {r5, r12}
 ldr r5, [r6, r4]
 subs r2, r2, #1
 and r12, r5, #0xff000000
 orr r12, r12, r12, lsr #8
 orr r12, r12, r12, lsr #16
 stmia r11!, {r5, r12}
 bne L_right_bound_copy_lines_c
 bx lr









