/* 
LIMITED LICENSE AGREEMENT

These terms (the "Terms") govern your use of the attached Nokia MVC software package (the "Code"). The Terms are an agreement (the "Agreement") between You and Nokia Corporation including its affiliates and suppliers (collectively "Nokia"). 

"You" (or "Your") shall mean an individual or legal entity exercising permissions granted by this License.

You are not allowed to use the Code if you do not agree to these Terms. You must be at least eighteen (18) years of age to accept these Terms.

 

1. LICENSE AND USE
Subject to these Terms, Nokia hereby grants to You, and you hereby accept, solely under the copyrights licensable by Nokia, a non-exclusive, worldwide, royalty-free copyright license to reproduce, use, publicly display and perform the Code, in source code, object code, and executable form, and to create derivative works of the Code solely to study, demonstrate and experiment with the H.264/MVC standard. You may redistribute or make available the Code or any derivative works thereof to any third party only pursuant to the terms of a license agreement that: (a) contains terms substantially similar to this license agreement; and (b) explicitly names Nokia as a third party beneficiary. 

This License does not grant You permission to use the trade names, trademarks, service marks, or product names of Nokia. 

This Agreement does not grant You any patent rights or other intellectual property rights, except the copyright license above. You assume sole responsibility for securing any other intellectual property rights needed. For example, if patent licenses are required, it is Your responsibility to acquire the licenses at Your own cost. To enquire about patent or other intellectual property rights licenses from Nokia, please contact Nokia Patent Licensing (Request.patentlicense@nokia.com).

2. OWNERSHIP

As between You and Nokia, Nokia retains the ownership of copyrights and all other intellectual property rights, including patent rights to the Code, as well as all Nokia trademarks, service marks, trade names, logos or other words or symbols.

3. FEEDBACK
You may, but you are not obliged to, report Your findings and results of the use of the Code to Nokia ("Feedback"). Giving Feedback to Nokia is completely voluntary. Feedback includes, without limitation, materials as well as ideas or know how (whether presented orally, in written form or otherwise).  With respect to such Feedback, You hereby grant Nokia, solely under Your copyrights, the worldwide, non-exclusive, perpetual, irrevocable, royalty-free rights  (1) to copy and modify Feedback and to create derivative works thereof, (2) to make (and have made), use, import, sell, offer for sale, lease or otherwise distribute any products or services of Nokia containing Feedback, and (3) to sublicense the foregoing rights to the extent a license is necessary for using products or services of Nokia. 

4. WARRANTIES
THE CODE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND EXPRESS OR IMPLIED AND NEITHER NOKIA, ITS LICENSORS OR AFFILIATES NOR THE COPYRIGHT HOLDERS MAKE ANY REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE OR THAT THE CODE WILL NOT INFRINGE ANY THIRD PARTY PATENTS, COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS.  THERE IS NO WARRANTY BY NOKIA OR BY ANY OTHER PARTY THAT THE FUNCTIONS CONTAINED IN THE CODE WILL MEET YOUR REQUIREMENTS OR WILL BE UNINTERRUPTED OR ERROR-FREE.  

5. LIMITATION OF LIABILITY

IN NO EVENT SHALL NOKIA, ITS EMPLOYEES OR SUPPLIERS OR AFFILIATES BE LIABLE FOR ANY LOST PROFITS, REVENUE, SALES, DATA OR COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, PROPERTY DAMAGE, PERSONAL INJURY, INTERRUPTION OF BUSINESS, LOSS OF BUSINESS INFORMATION OR FOR ANY SPECIAL, DIRECT, INDIRECT, INCIDENTAL, ECONOMIC, COVER, PUNITIVE, SPECIAL OR CONSEQUENTIAL DAMAGES, HOWEVER CAUSED AND WHETHER ARISING UNDER CONTRACT, TORT, NEGLIGENCE, OR OTHER THEORY OF LIABILITY ARISING OUT OF THE USE OF OR INABILITY TO USE THE CODE, EVEN IF NOKIA OR ITS EMPLOYEES OR SUPPLIERS OR AFFILIATES ARE ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. BECAUSE SOME COUNTRIES/STATES/ JURISDICTIONS DO NOT ALLOW THE EXCLUSION OR LIMITATION OF LIABILITY, BUT MAY ALLOW LIABILITY TO BE LIMITED, IN SUCH CASES, NOKIA, ITS EMPLOYEES OR LICENSORS OR AFFILIATES' LIABILITY SHALL BE LIMITED TO U.S.$50. 

6. TERM AND TERMINATION
Nokia may terminate this agreement at any time. This agreement terminates automatically if You violate these Terms, if Nokia posts a notice of termination on this site, or if Nokia sends You a written notice of termination.


7. GENERAL
7.1 Indemnification

You agree to defend, indemnify and hold harmless Nokia from and against any and all third party claims either actual or threatened and all liabilities and other expenses of any kind whatsoever arising from any claim by a third party, assessments, losses, costs or damages resulting from or arising out of i) your breach of these Terms, or ii) Your use of the Code.

7.2 Governing Law and Arbitration

Except where prohibited by applicable law or provided otherwise herein, these Terms shall be governed by the laws of New York without regard to its conflicts of law provisions.  

Any dispute relating to these Terms or the Code shall be submitted to binding arbitration in Westchester County, New York within eighteen (18) months of the date the facts giving rise to the suit were known, or should have been known, by the complainant, except that Nokia may seek injunctive or other relief if you have violated or threatened to violate any intellectual property rights. All matters relating to arbitration shall be governed by the Federal Arbitration Act (9 U.S.C. §1 et. seq.). Arbitration shall be conducted by a single arbitrator under the then prevailing Wireless Arbitration Rules of the American Arbitration Association (“AAA”). Each party must submit any claim which would constitute a compulsory counterclaim in litigation or such claim shall be barred. No award of exemplary, special, consequential or punitive damages shall be permitted. The losing party, as determined by the arbitrator, shall pay the arbitration fees. The arbitrator's award shall be binding and may be entered as a judgment and enforceable in any court of competent jurisdiction. Arbitration shall be conducted on an individual, not class-wide basis, and no arbitration shall be joined with an arbitration involving any other person or entity.

7.3 Severability

If any provision contained in these Terms is determined to be invalid or unenforceable, in whole or in part, the remaining provisions and any partially enforceable provision will, nevertheless, be binding and enforceable, and the parties agree to substitute for the invalid provision a valid provision which most closely approximates the intent and economic effect of the invalid provision.

7.4 Export Control

You shall follow all export control laws and regulations relating to the Code. You agree not to export or re-export, as the case may be, the Code to any country without obtaining licenses and permits that may be required under any applicable legislation or regulations.  You shall not license the Code or provide services, nor export or re-export any information, or any process, product or service that is produced under these Terms to any country specified as a prohibited destination in applicable national, state and local, regulations and ordi­nances, including the Regulations of the U.S. Department of Commerce and/or the U.S. State Department, without first obtaining government approval.
*/

#include "armasmdef.h"


#if ARM_ARCH_VERSION <= ARM_ARCH_V5
#define MUL mul
#define MLA mla
#else
#define MUL smulbb
#define MLA smlabb
#endif


#define MBK_SIZE     16
#define BLK_SIZE     4
#define BLK_PER_MB   4
#define IMG_PAD_SIZE 0


	EXTLAB	clip8Buf


	CODE32
	CODESEC



/****************************************************************************
 *
 * mcpGetPred8x8:
 *
 * Parameters:
 *      predY                 Return pointer for predicted luma pixels
 *      predC                 Return pointer for predicted chroma pixels
 *      blkX                  Sub-macroblock horizontal location (in 4x4 blocks)
 *      blkY                  Sub-macroblock vertical location (in 4x4 blocks)
 *      ref                   Reference frame buffer
 *      picWidth              Frame buffer width in pixels
 *      picHeight             Frame buffer height in pixels
 *      motVec                Motion vector
 *
 * Function:
 *      Get motion compensated prediction for 8x8 block.
 *
 * Returns:
 *      -
 *
 ****************************************************************************/

/*
 * void mcpGetPred8x8(u_int8 predPtr[MBK_SIZE][MBK_SIZE],
 *                    u_int8 predC[MBK_SIZE/2][MBK_SIZE],
 *                    int blkX, int blkY, frmBuf_s *ref, int picWidth,
 *                    int picHeight, motVec_s *motVec)
 * {
 */

	ALIGNW
#if defined(COMPILER_ADS)
	GLOBLAB	mcpGetPred8x8
mcpGetPred8x8 PROC
#elif defined(COMPILER_GCC)
	GLOBLAB	mcpGetPred8x8
mcpGetPred8x8:
#elif defined(COMPILER_CCS)
	GLOBLAB	_mcpGetPred8x8
_mcpGetPred8x8
#endif

  /*
   * int i, j;
   * u_int8 *refPtr;
   * int xPos, yPos, xInt, yInt, xFrac, yFrac;
   * int coef0, coef1, coef2, coef3;
   * int c;
   * int tmp;
   * int refWidth, refHeight, refWidthC, refHeightC;
   * int block[2*BLK_SIZE+2+3][2*BLK_SIZE];
   * int lineIdx, colIdx;
   * u_int8 *refC[2];
   * u_int8 (* predPtr)[MBK_SIZE];
   * u_int8 refArea[(2*BLK_SIZE+2+3)*16];
   */


#define LOC_BASE       0
#define LOC_SIZE       696
#define REG_BASE       LOC_SIZE
#define NUM_SAVED_REGS 10
#define ARG_BASE       LOC_SIZE+4*NUM_SAVED_REGS

#define REF_PTR        LOC_BASE+0
#define X_POS          LOC_BASE+4
#define Y_POS          LOC_BASE+8
#define X_INT          LOC_BASE+12
#define Y_INT          LOC_BASE+16
#define X_FRAC         LOC_BASE+20
#define Y_FRAC         LOC_BASE+24
#define REF_WIDTH      LOC_BASE+28
#define REF_HEIGHT     LOC_BASE+32
#define PIC_WIDTH_C    LOC_BASE+36
#define PIC_HEIGHT_C   LOC_BASE+40
#define BLOCK          LOC_BASE+44		// 416 bytes (13*8*4)
#define PRED_PTR       LOC_BASE+460
#define REFC_1         LOC_BASE+464
#define COUNTER_C      LOC_BASE+468

#define PRED_Y         LOC_BASE+472
#define PRED_C         LOC_BASE+476
#define BLK_X          LOC_BASE+480
#define BLK_Y          LOC_BASE+484
#define REF_AREA       LOC_BASE+488		// 208 bytes (13*16)


#define REF            ARG_BASE+0
#define PIC_WIDTH      ARG_BASE+4
#define PIC_HEIGHT     ARG_BASE+8
#define MOT_VEC        ARG_BASE+12
#define CLIP_BUF       ARG_BASE+16


	stmfd	sp!, {r4-r12, lr}		// save 10 regs
	sub	sp, sp, #LOC_SIZE		// alloc space for local variables

	str	r0, [sp, #PRED_Y]
	str	r1, [sp, #PRED_C]

  /*
   * picWidthC = picWidth/2;
   * picHeightC = picHeight/2;
   */

	ldr	r9, [sp, #PIC_WIDTH]
	ldr	r10, [sp, #PIC_HEIGHT]
	mov	r4, r9, lsr #1			// picWidth/2
	mov	r5, r10, lsr #1			// picHeight/2
	str	r4, [sp, #PIC_WIDTH_C]
	str	r5, [sp, #PIC_HEIGHT_C]

  /*
   * // Absolute coordinates of the prediction block
   * xPos = blkX*BLK_SIZE*4 + motVec->x;
   * yPos = blkY*BLK_SIZE*4 + motVec->y;
   * predPtr = (u_int8 (*)[MBK_SIZE])&predY[0][0];
   */

	ldr	r5, [sp, #MOT_VEC]
	ldr	r6, [sp, #PRED_Y]
	ldrsh	r7, [r5]			// vec x
	ldrsh	r8, [r5, #2]			// vec y
	str	r6, [sp, #PRED_PTR]
	add	r0, r7, r2, lsl #4		// xPos = blkX*BLK_SIZE*4 + vec x
	add	r1, r8, r3, lsl #4		// yPos = blkY*BLK_SIZE*4 + vec y

	ldr	r6, [sp, #REF]			// Reference frame

	str	r0, [sp, #X_POS]
	str	r1, [sp, #Y_POS]

	ldr	r7, [r6]			// refPtr = ref->y


      /************************************************************
       *
       *  Luma interpolation
       *
       ************************************************************/


	and	r2, r0, #3			// xFrac = xPos & 3
	str	r2, [sp, #X_FRAC]
	and	r3, r1, #3			// yFrac = yPos & 3
	str	r3, [sp, #Y_FRAC]
	mov	r0, r0, asr #2			// xInt = xPos >> 2
	mov	r1, r1, asr #2			// yInt = yPos >> 2


	// Register content at this point:
	// r0  = xInt
	// r1  = yInt
	// r2  = xFrac
	// r3  = yFrac
	// r7  = refPtr
	// r9  = picWidth
	// r10 = picHeight


LABELDEF(interp_copy)

  /*
   * if (xFrac == 0 && yFrac == 0) {
   */

	orrs	r4, r2, r3
	bne	L_interp_hf_vs

    /* Full-pel precision
     *
     *  O x x x
     *  x x x x
     *  x x x x
     *  x x x x
     *
     */

    /*
     * if (xInt >= 0 && xInt <= picWidth-2*BLK_SIZE &&
     *     yInt >= 0 && yInt <= picHeight-2*BLK_SIZE)
     * {
     *   refPtr += yInt*picWidth + xInt;
     *   refWidth = picWidth;
     * }
     * else {
     *   getRefArea(refPtr, refArea, picWidth, picHeight, xInt, yInt, 2*BLK_SIZE, 2*BLK_SIZE);
     *   refPtr = refArea;
     *   refWidth = 2*BLK_SIZE;
     * }
     */

	sub	r4, r9, #2*BLK_SIZE		// picWidth - 2*BLK_SIZE
	sub	r5, r10, #2*BLK_SIZE		// picHeight - 2*BLK_SIZE
	cmp	r0, r4				// if (unsigned int)xInt <= (picWidth - 2*BLK_SIZE) and
	cmpls	r1, r5				// if (unsigned int)yInt <= (picHeight - 2*BLK_SIZE)
	bls	L_interp_copy_no_bound_checks	// then no bound checks

        // note: this code corresponds to the 'else' block in c code
	add	r8, sp, #REF_AREA
	mov	r3, #2*BLK_SIZE
	bl	L_get_ref_area_XxX
	str	r0, [sp, #REF_PTR]		// refPtr
	mov	r2, #16
	str	r2, [sp, #REF_WIDTH]		// refWidth = 2*BLK_SIZE
	b	L_interp_copy_cont

LABELDEF(interp_copy_no_bound_checks)
        // note: this code corresponds to the 'if' block in c code
	MLA	r0, r9, r1, r0			// picWidth*yInt + xInt
	str	r9, [sp, #REF_WIDTH]		// refWidth = picWidth
	add	r7, r7, r0			// refPtr
	str	r7, [sp, #REF_PTR]

LABELDEF(interp_copy_cont)

    /*
     * for (j = 0; j < BLK_SIZE;  j++) {
     *   predPtr[j][0] = refPtr[j*refWidth + 0];
     *   predPtr[j][1] = refPtr[j*refWidth + 1];
     *   predPtr[j][2] = refPtr[j*refWidth + 2];
     *   predPtr[j][3] = refPtr[j*refWidth + 3];
     *   predPtr[j][4] = refPtr[j*refWidth + 4];
     *   predPtr[j][5] = refPtr[j*refWidth + 5];
     *   predPtr[j][6] = refPtr[j*refWidth + 6];
     *   predPtr[j][7] = refPtr[j*refWidth + 7];
     * }
     */

	ldr	r7, [sp, #REF_PTR]
	ldr	r9, [sp, #REF_WIDTH]
	ldr	r8, [sp, #PRED_PTR]
	mov	r10, #2*BLK_SIZE
#if ARM_ARCH_VERSION < ARM_ARCH_V6
	sub	r11, r9, #2*BLK_SIZE-1		// refWidth - (2*BLK_SIZE-1)
LABELDEF(loop_copy)
	ldrb	r0, [r7], #1
	ldrb	r1, [r7], #1
	ldrb	r2, [r7], #1
	ldrb	r3, [r7], #1
	strb	r0, [r8], #1
	strb	r1, [r8], #1
	strb	r2, [r8], #1
	strb	r3, [r8], #1
	ldrb	r0, [r7], #1
	ldrb	r1, [r7], #1
	ldrb	r2, [r7], #1
	ldrb	r3, [r7], r11
	strb	r0, [r8], #1
	strb	r1, [r8], #1
	strb	r2, [r8], #1
	strb	r3, [r8], #1+(MBK_SIZE-2*BLK_SIZE)
	subs	r10, r10, #1
#else
	sub	r11, r9, #2*BLK_SIZE-4		// refWidth - (2*BLK_SIZE-4)
LABELDEF(loop_copy)
	ldr	r0, [r7], #4
	ldr	r1, [r7], r11
	ldr	r2, [r7], #4
	ldr	r3, [r7], r11
	str	r0, [r8], #4
	str	r1, [r8], #4+(MBK_SIZE-2*BLK_SIZE)
	str	r2, [r8], #4
	str	r3, [r8], #4+(MBK_SIZE-2*BLK_SIZE)
	subs	r10, r10, #2
#endif
	bne	L_loop_copy

	b	L_interp_chroma

  /*
   * }
   */


LABELDEF(interp_hf_vs)

  /*
   * else if (xFrac == 0) {
   */

	cmp	r2, #0
	bne	L_interp_hs_vf

    /* Horizontal fullpel precision, vertical subpel precision
     *
     *  X x x x
     *  o x x x
     *  o x x x
     *  o x x x
     *
     */

    /*
     * if (xInt >= 0 && xInt <= picWidth-2*BLK_SIZE &&
     *     yInt >= 2 && yInt <= picHeight-2*BLK_SIZE-3)
     * {
     *   refPtr += yInt*picWidth + xInt;
     *   refWidth = picWidth;
     * }
     * else {
     *   getRefArea(refPtr, refArea, picWidth, picHeight, xInt, yInt-2, 2*BLK_SIZE, 2*BLK_SIZE+2+3);
     *   refPtr = refArea + 2*2*BLK_SIZE;
     *   refWidth = BLK_SIZE;
     * }
     */

	sub	r4, r9, #2*BLK_SIZE		// picWidth - 2*BLK_SIZE
	sub	r3, r1, #2			// yInt - 2
	sub	r5, r10, #2*BLK_SIZE+3+2	// picHeight - (2*BLK_SIZE+2+3)
	cmp	r0, r4				// if (unsigned int)xInt <= (picWidth - 2*BLK_SIZE) and
	cmpls	r3, r5				// if (unsigned int)yInt-2 <= (picHeight - (2*BLK_SIZE+2+3)
	bls	L_interp_hf_vs_no_bound_checks	// then no bound checks

        // note: this code corresponds to the 'else' block in c code
	add	r8, sp, #REF_AREA
	sub	r1, r1, #2			// y = yInt - 2
	mov	r3, #2*BLK_SIZE+2+3		// area height
	bl	L_get_ref_area_XxX
	add	r0, r0, #2*16
	str	r0, [sp, #REF_PTR]		// refPtr = refArea + 2*BLK_SIZE
	mov	r2, #16
	str	r2, [sp, #REF_WIDTH]		// refWidth = 2*BLK_SIZE
	b	L_interp_hf_vs_cont

LABELDEF(interp_hf_vs_no_bound_checks)
        // note: this code corresponds to the 'if' block in c code
	MLA	r0, r9, r1, r0			// picWidth*yInt + xInt
	str	r9, [sp, #REF_WIDTH]		// refWidth = picWidth
	add	r7, r7, r0			// refPtr
	str	r7, [sp, #REF_PTR]

LABELDEF(interp_hf_vs_cont)

    /*
     * // Vertical interpolation
     * for (j = 0; j < 2*BLK_SIZE;  j++) {
     *   for (i = 0; i < 2*BLK_SIZE;  i++) {
     *     tmp = (
     *       ONEFOURTH1*(refPtr[ j   *refWidth + i] +
     *                   refPtr[(j+1)*refWidth + i]) +
     *       ONEFOURTH2*(refPtr[(j-1)*refWidth + i] +
     *                   refPtr[(j+2)*refWidth + i]) +
     *       ONEFOURTH3*(refPtr[(j-2)*refWidth + i] +
     *                   refPtr[(j+3)*refWidth + i]) + 16
     *     ) >> 5;
     *     predPtr[j][i] = (u_int8) clip(0,255,tmp);
     *   }
     * }
     */

	ldr	r7, [sp, #REF_PTR]
	ldr	r9, [sp, #REF_WIDTH]
	ldr	r8, [sp, #PRED_PTR]
	ldr	r12, L_clipBufPtr
	sub	r7, r7, r9, lsl #1	// refPtr - 2*refWidth
	mov	r11, #MBK_SIZE
	mov	r0, r9, lsl #3		// 8*refWidth
	add	r0, r0, r9, lsl #2	// 12*refWidth
	rsb	r0, r0, #1		// -12*refWidth + 1
	mov	r1, #-(2*BLK_SIZE-1)*MBK_SIZE+1
	bl	L_interpolate_block_1D

LABELDEF(linear_interp_hf_vs_or_hs_vf)

	ldr	r0, [sp, #X_FRAC]
	ldr	r1, [sp, #Y_FRAC]
	mov	r2, r0, lsl #31		// get bit 0 of xFrac
	orrs	r2, r2, r1, lsl #31	// or with bit 0 of yFrac
	beq	L_interp_chroma		// if neither of them is 1 -> no linear interp.

    /*
     * // Linear interp.
     * if ((yFrac&1) != 0) {
     *   lineIdx = yFrac >> 1;
     *   for (j = 0; j < 2*BLK_SIZE;  j++) {
     *     for (i = 0; i < 2*BLK_SIZE;  i++) {
     *       predPtr[j][i] = (u_int8) ((predPtr[j][i] + refPtr[(j+lineIdx)*refWidth+i] + 1) >> 1);
     *     }
     *   }
     */

	ldr	r9, [sp, #REF_WIDTH]
	ldr	r7, [sp, #REF_PTR]
	ldr	r8, [sp, #PRED_PTR]
	cmp	r1, #3			// if yFrac == 3, use lower full pel
	addeq	r7, r7, r9
	add	r7, r7, r0, lsr #1	// if bit 1 of xFrac is 1 (i.e. xFrac is 3), use right full pel
	ldr	r4, L_0x7f7f7f7f
#if ARM_ARCH_VERSION < ARM_ARCH_V6
	sub	r11, r9, #2*BLK_SIZE-1	// refWidth - (2*BLK_SIZE-1)
	mov	r10, #2*BLK_SIZE
LABELDEF(loop_linear)
	// Linear interpolation of four pixels in parallel
	ldrb	r0, [r7], #1		// refpix0
	ldrb	r1, [r7], #1		// refpix1
	ldrb	r2, [r7], #1		// refpix2
	ldrb	r3, [r7], #1		// refpix3
	orr	r0, r0, r1, lsl #8	// refpix = refpix0 | (refpix1<<8)
	ldr	r1, [r8]		// predpix = four predicted pixel values
	orr	r0, r0, r2, lsl #16	// refpix = refpix  | (refpix2<<16)
	orr	r0, r0, r3, lsl #24	// refpix = refpix  | (refpix3<<24)
	orr	r2, r0, r1		// roundval = refpix | predpix
	bic	r2, r2, r4, ror #7	// roundval = roundval & 0x01010101
	and	r0, r4, r0, lsr #1	// refpix  = 0x7f7f7f7f & (refpix >>1)
	and	r1, r4, r1, lsr #1	// predpix = 0x7f7f7f7f & (predpix>>1)
	add	r0, r0, r1		// finalpix = refpix + predpix
	add	r0, r0, r2		// finalpix = finalpix + roundval
	str	r0, [r8], #BLK_SIZE

	ldrb	r0, [r7], #1		// refpix4
	ldrb	r1, [r7], #1		// refpix5
	ldrb	r2, [r7], #1		// refpix6
	ldrb	r3, [r7], r11		// refpix7
	subs	r10, r10, #1		// j--
	orr	r0, r0, r1, lsl #8	// refpix = refpix4 | (refpix5<<8)
	ldr	r1, [r8]		// predpix = four predicted pixel values
	orr	r0, r0, r2, lsl #16	// refpix = refpix  | (refpix6<<16)
	orr	r0, r0, r3, lsl #24	// refpix = refpix  | (refpix7<<24)
	orr	r2, r0, r1		// roundval = refpix | predpix
	bic	r2, r2, r4, ror #7	// roundval = roundval & 0x01010101
	and	r0, r4, r0, lsr #1	// refpix  = 0x7f7f7f7f & (refpix >>1)
	and	r1, r4, r1, lsr #1	// predpix = 0x7f7f7f7f & (predpix>>1)
	add	r0, r0, r1		// finalpix = refpix + predpix
	add	r0, r0, r2		// finalpix = finalpix + roundval
	str	r0, [r8], #MBK_SIZE-BLK_SIZE

	bne	L_loop_linear
#else
	sub	r11, r9, #2*BLK_SIZE-4	// refWidth - (2*BLK_SIZE-4)
	mov	r10, #2*BLK_SIZE
LABELDEF(loop_linear)
	// Linear interpolation of four pixels in parallel
	ldr	r0, [r7], #4		// refpix
	ldr	r1, [r8]		// predpix = four predicted pixel values
	ldr	r5, [r7], r11		// refpix
	ldr	r6, [r8, #BLK_SIZE]	// predpix = four predicted pixel values

	uhadd8	r2, r0, r1		// finalpix = refpix + predpix
	eor	r0, r0, r1		// roundval = refpix | predpix
	bic	r0, r0, r4, ror #7	// roundval = roundval & 0x01010101
	add	r0, r0, r2		// finalpix = finalpix + roundval
	str	r0, [r8], #BLK_SIZE

	subs	r10, r10, #1		// j--

	uhadd8	r3, r5, r6		// finalpix = refpix + predpix
	eor	r5, r5, r6		// roundval = refpix | predpix
	bic	r5, r5, r4, ror #7	// roundval = roundval & 0x01010101
	add	r5, r5, r3		// finalpix = finalpix + roundval
	str	r5, [r8], #MBK_SIZE-BLK_SIZE

	bne	L_loop_linear
#endif

	b	L_interp_chroma

    /*
     * } // end of "if ((yFrac&1) != 0) {"
     */

  /*
   * } // end of "else if (xFrac == 0) {"
   */


LABELDEF(interp_hs_vf)

  /*
   * else if (yFrac == 0) {
   */

	cmp	r3, #0
	bne	L_interp_hh_vs

    /* Horizontal subpel precision, vertical fullpel precision
     *
     *  X o o o
     *  x x x x
     *  x x x x
     *  x x x x
     *
     */

    /*
     * if (xInt >  1 && xInt <  picWidth-2*BLK_SIZE-2 &&
     *     yInt >= 0 && yInt <= picHeight-2*BLK_SIZE)
     * {
     *   refPtr += yInt*picWidth + xInt;
     *   refWidth = picWidth;
     * }
     * else {
     *   getRefArea(refPtr, refArea, picWidth, picHeight, xInt-2, yInt, 2*BLK_SIZE+2+3, 2*BLK_SIZE);
     *   refPtr = refArea + 2;
     *   refWidth = 2*BLK_SIZE+2+3;
     * }
     */

	sub	r2, r0, #2			// xInt - 2
	sub	r4, r9, #2*BLK_SIZE+2+3		// picWidth - 2*BLK_SIZE+2+3
	sub	r5, r10, #2*BLK_SIZE		// picHeight - 2*BLK_SIZE
	cmp	r2, r4				// if (unsigned int)xInt-2 <= (picWidth - (2*BLK_SIZE+2+3)) and
	cmpls	r1, r5				// if (unsigned int)yInt <= (picHeight - 2*BLK_SIZE)
	bls	L_interp_hs_vf_no_bound_checks	// then no bound checks

        // note: this code corresponds to the 'else' block in c code
	add	r8, sp, #REF_AREA
	sub	r0, r0, #2			// xInt - 2
	mov	r3, #2*BLK_SIZE			// area height
	bl	L_get_ref_area_XxX
	add	r0, r0, #2
	str	r0, [sp, #REF_PTR]
	mov	r2, #16
	str	r2, [sp, #REF_WIDTH]		// refWidth = 2*BLK_SIZE+2+3
	b	L_interp_hs_vf_cont

LABELDEF(interp_hs_vf_no_bound_checks)
        // note: this code corresponds to the 'if' block in c code
	MLA	r0, r9, r1, r0			// picWidth*yInt + xInt
	str	r9, [sp, #REF_WIDTH]		// refWidth = picWidth
	add	r7, r7, r0			// refPtr
	str	r7, [sp, #REF_PTR]

LABELDEF(interp_hs_vf_cont)

        /*
         * // Horizontal interpolation
         * for (j = 0; j < 2*BLK_SIZE;  j++) {
         *   for (i = 0; i < 2*BLK_SIZE;  i++) {
         *     tmp = (
         *       ONEFOURTH1*(refPtr[j*refWidth + i  ] +
         *                   refPtr[j*refWidth + i+1]) +
         *       ONEFOURTH2*(refPtr[j*refWidth + i-1] +
         *                   refPtr[j*refWidth + i+2]) +
         *       ONEFOURTH3*(refPtr[j*refWidth + i-2] +
         *                   refPtr[j*refWidth + i+3]) + 16
         *     ) >> 5;
         *     predPtr[j][i] = (u_int8) clip(0,255,tmp);
         *   }
         * }
	 */

	ldr	r7, [sp, #REF_PTR]
	ldr	r0, [sp, #REF_WIDTH]
	ldr	r8, [sp, #PRED_PTR]
	ldr	r12, L_clipBufPtr
	sub	r7, r7, #2		// refPtr - 2
	mov	r9, #1
	mov	r11, #1
	sub	r0, r0, #12		// refWidth - 12
	mov	r1, #1+(MBK_SIZE-2*BLK_SIZE)
	bl	L_interpolate_block_1D


    /*
     * // Linear interp.
     * if ((xFrac&1) != 0) {
     *   colIdx = xFrac >> 1;
     *   for (j = 0; j < 2*BLK_SIZE;  j++) {
     *     for (i = 0; i < 2*BLK_SIZE;  i++) {
     *       predPtr[j][i] = (u_int8) ((predPtr[j][i] + refPtr[j*refWidth+i+colIdx] + 1) >> 1);
     *     }
     *   }
     * }
     */

	b	L_linear_interp_hf_vs_or_hs_vf

  /*
   * }
   */


LABELDEF(interp_hh_vs)

  /*
   * else {
   *
   *   // The Rest of the sub-pel positions require 9x9 reference pixel are
   *   if (xInt > 1 && xInt <  picWidth-2*BLK_SIZE-2 &&
   *       yInt > 1 && yInt <  picHeight-2*BLK_SIZE-2)
   *   {
   *     refPtr += yInt*picWidth + xInt;
   *     refWidth = picWidth;
   *   }
   *   else {
   *     getRefArea(refPtr, refArea, picWidth, picHeight, xInt-2, yInt-2, 2*BLK_SIZE+2+3, 2*BLK_SIZE+2+3);
   *     refPtr = refArea + 2*(2*BLK_SIZE+2+3) + 2;
   *     refWidth = 2*BLK_SIZE+2+3;
   *   }
   */

	sub	r4, r0, #2			// xInt - 2
	sub	r5, r9, #2*BLK_SIZE+2+3		// picWidth - (2*BLK_SIZE+2+3)
	sub	r6, r1, #2			// yInt - 2
	sub	r8, r10, #2*BLK_SIZE+2+3	// picHeight - (2*BLK_SIZE+2+3)
	cmp	r4, r5				// if (unsigned int)xInt-2 <= (picWidth - (2*BLK_SIZE+2+3)) and
	cmpls	r6, r8				// if (unsigned int)yInt-2 <= (picHeight - (2*BLK_SIZE+2+3))
	bls	L_interp_hh_vs_no_bound_checks	// then no bound checks

        // note: this code corresponds to the 'else' block in c code
	add	r8, sp, #REF_AREA
	sub	r0, r0, #2			// xInt - 2
	sub	r1, r1, #2			// yInt - 2
	mov	r3, #2*BLK_SIZE+2+3		// area height
	bl	L_get_ref_area_XxX
	add	r0, r0, #2*16+2
	str	r0, [sp, #REF_PTR]		// refPtr = refArea + 2*(2*BLK_SIZE+2+3) + 2
	mov	r2, #16
	str	r2, [sp, #REF_WIDTH]		// refWidth = 2*BLK_SIZE+2+3
	ldr	r2, [sp, #X_FRAC]
	ldr	r3, [sp, #Y_FRAC]
	b	L_interp_hh_vs_cont

LABELDEF(interp_hh_vs_no_bound_checks)
        // note: this code corresponds to the 'if' block in c code
	MLA	r0, r9, r1, r0			// picWidth*yInt + xInt
	str	r9, [sp, #REF_WIDTH]		// refWidth = picWidth
	add	r7, r7, r0			// refPtr
	str	r7, [sp, #REF_PTR]

LABELDEF(interp_hh_vs_cont)

    /*
     * if (xFrac == 2) {
     */

	cmp	r2, #2
	bne	L_interp_vh_hq

      /* Horizontal 1/2-pel precision, vertical sub-pel precision
       *
       *  X x x x
       *  x x o x
       *  x x o x
       *  x x o x
       *
       */

      /*
       * // horizontal interpolation
       * for (j = -2; j < 2*BLK_SIZE+3;  j++) {
       *   for (i = 0; i < 2*BLK_SIZE;  i++) {
       *     tmp = (
       *       ONEFOURTH1*(refPtr[j*refWidth + i  ] +
       *                   refPtr[j*refWidth + i+1]) +
       *       ONEFOURTH2*(refPtr[j*refWidth + i-1] +
       *                   refPtr[j*refWidth + i+2]) +
       *       ONEFOURTH3*(refPtr[j*refWidth + i-2] +
       *                   refPtr[j*refWidth + i+3]));
       *     block[2+j][i] = tmp;
       *   }
       * }
       */

	ldr	r11, [sp, #REF_WIDTH]
	ldr	r7, [sp, #REF_PTR]
	add	r8, sp, #BLOCK
	sub	r7, r7, r11, lsl #1	// refPtr - 2*refWidth
	sub	r7, r7, #2		// - 2
	mov	r9, #1
	sub	r11, r11, #12		// refWidth - 12
	mov	r10, #4
	mov	r12, #4
	bl	L_interpolate_block_1D_no_clip


      /*
       * // Vertical interpolation
       * for (j = 0; j < 2*BLK_SIZE;  j++) {
       *   for (i = 0; i < 2*BLK_SIZE;  i++) {
       *     tmp2 = (
       *       ONEFOURTH1*((int32)(block[2+j  ][i] + block[2+j+1][i])) +
       *       ONEFOURTH2*((int32)(block[2+j-1][i] + block[2+j+2][i])) +
       *       ONEFOURTH3*((int32)(block[2+j-2][i] + block[2+j+3][i])) + 512
       *     ) >> 10;
       *     predPtr[j][i] = (u_int8) clip(0,255,tmp2);
       *   }
       * }
       */

	ldr	r12, L_clipBufPtr
	add	r7, sp, #BLOCK
	ldr	r8, [sp, #PRED_PTR]
	mov	r10, #2*BLK_SIZE
LABELDEF(loop_hh_vs_vert)
	ldr	r0, [r7], #2*BLK_SIZE*4	// a
	ldr	r1, [r7], #2*BLK_SIZE*4	// b
	ldr	r2, [r7], #2*BLK_SIZE*4	// c
	ldr	r3, [r7], #2*BLK_SIZE*4	// d
	ldr	r4, [r7], #2*BLK_SIZE*4	// e
	ldr	r5, [r7], #2*BLK_SIZE*4	// f
	// {r0,r1,r2,r3,r4,r5} = {a,b,c,d,e,f}
	rsb	r6, r1, r2, lsl #2	//        4* c      - b
	add	r6, r6, r3, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r4		//        4*(c + d) - b - e
	add	r0, r0, r5		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r0, r6		// a + 5*(4*(c + d) - b - e) + f

	ldr	r0, [r7], #2*BLK_SIZE*4	// f
	ldrb	r14, [r12, r6, asr #9]
	// {r1,r2,r3,r4,r5,r0} = {a,b,c,d,e,f}
	rsb	r6, r2, r3, lsl #2	//        4* c      - b
	add	r6, r6, r4, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r5		//        4*(c + d) - b - e
	add	r1, r1, r0		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r1, r6		// a + 5*(4*(c + d) - b - e) + f
	strb	r14, [r8], #MBK_SIZE

	ldr	r1, [r7], #2*BLK_SIZE*4	// f
	ldrb	r14, [r12, r6, asr #9]
	// {r2,r3,r4,r5,r0,r1} = {a,b,c,d,e,f}
	rsb	r6, r3, r4, lsl #2	//        4* c      - b
	add	r6, r6, r5, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r0		//        4*(c + d) - b - e
	add	r2, r2, r1		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r2, r6		// a + 5*(4*(c + d) - b - e) + f
	strb	r14, [r8], #MBK_SIZE

	ldr	r2, [r7], #2*BLK_SIZE*4	// f
	ldrb	r14, [r12, r6, asr #9]
	// {r3,r4,r5,r0,r1,r2} = {a,b,c,d,e,f}
	rsb	r6, r4, r5, lsl #2	//        4* c      - b
	add	r6, r6, r0, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r1		//        4*(c + d) - b - e
	add	r3, r3, r2		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r3, r6		// a + 5*(4*(c + d) - b - e) + f
	strb	r14, [r8], #MBK_SIZE

	ldr	r3, [r7], #2*BLK_SIZE*4	// f
	ldrb	r14, [r12, r6, asr #9]
	// {r4,r5,r0,r1,r2,r3} = {a,b,c,d,e,f}
	rsb	r6, r5, r0, lsl #2	//        4* c      - b
	add	r6, r6, r1, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r2		//        4*(c + d) - b - e
	add	r4, r4, r3		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r4, r6		// a + 5*(4*(c + d) - b - e) + f
	strb	r14, [r8], #MBK_SIZE

	ldr	r4, [r7], #2*BLK_SIZE*4	// f
	ldrb	r14, [r12, r6, asr #9]
	// {r5,r0,r1,r2,r3,r4} = {a,b,c,d,e,f}
	rsb	r6, r0, r1, lsl #2	//        4* c      - b
	add	r6, r6, r2, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r3		//        4*(c + d) - b - e
	add	r5, r5, r4		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r5, r6		// a + 5*(4*(c + d) - b - e) + f
	strb	r14, [r8], #MBK_SIZE

	ldr	r5, [r7], #2*BLK_SIZE*4	// f
	ldrb	r14, [r12, r6, asr #9]
	// {r0,r1,r2,r3,r4,r5} = {a,b,c,d,e,f}
	rsb	r6, r1, r2, lsl #2	//        4* c      - b
	add	r6, r6, r3, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r4		//        4*(c + d) - b - e
	add	r0, r0, r5		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r0, r6		// a + 5*(4*(c + d) - b - e) + f
	strb	r14, [r8], #MBK_SIZE

	ldr	r0, [r7], #-12*(2*BLK_SIZE*4)+4	// f
	ldrb	r14, [r12, r6, asr #9]
	// {r1,r2,r3,r4,r5,r0} = {a,b,c,d,e,f}
	rsb	r6, r2, r3, lsl #2	//        4* c      - b
	add	r6, r6, r4, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r5		//        4*(c + d) - b - e
	add	r1, r1, r0		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r1, r6		// a + 5*(4*(c + d) - b - e) + f
	ldrb	r6, [r12, r6, asr #9]

	strb	r14, [r8], #MBK_SIZE
	subs	r10, r10, #1
	strb	r6, [r8], #-((2*BLK_SIZE-1)*MBK_SIZE)+1

	bne	L_loop_hh_vs_vert

	ldr	r1, [sp, #Y_FRAC]
	tst	r1, #1
	beq	L_interp_chroma


      /*
       * // Linear interp.
       * if ((yFrac&1) != 0) {
       *   lineIdx = 2 + (yFrac >> 1);
       *   for (j = 0; j < 2*BLK_SIZE;  j++) {
       *     for (i = 0; i < 2*BLK_SIZE;  i++) {
       *       tmp = (block[lineIdx+j][i] + 16) >> 5;
       *       predPtr[j][i] = (u_int8) ((predPtr[j][i] + clip(0,255,tmp) + 1) >> 1);
       *     }
       *   }
       * }
       */

	add	r7, sp, #BLOCK+2*2*BLK_SIZE*4
	ldr	r8, [sp, #PRED_PTR]
	ldr	r12, L_clipBufPtr
	cmp	r1, #3			// if yFrac == 3, use lower half-pel
	addeq	r7, r7, #2*BLK_SIZE*4
	mov	r10, #2*BLK_SIZE
	ldr	r4, L_0x7f7f7f7f
LABELDEF(loop_linear_hh_vs)
	// Linear interpolation of four pixels in parallel
	ldmia	r7!, {r0-r3}		// refpix0, refpix1, refpix2, refpix3
	ldrb	r0, [r12, r0, asr #4]	// rounded, normalized and clipped refpix0
	ldrb	r1, [r12, r1, asr #4]	// rounded, normalized and clipped refpix1
	ldrb	r2, [r12, r2, asr #4]	// rounded, normalized and clipped refpix2
	ldrb	r3, [r12, r3, asr #4]	// rounded, normalized and clipped refpix3
	orr	r0, r0, r1, lsl #8	// refpix = refpix0 | (refpix1<<8)
	ldr	r1, [r8]		// predpix = four predicted pixel values
	orr	r0, r0, r2, lsl #16	// refpix = refpix  | (refpix2<<16)
	orr	r0, r0, r3, lsl #24	// refpix = refpix  | (refpix3<<24)
#if ARM_ARCH_VERSION < ARM_ARCH_V6
	orr	r2, r0, r1		// roundval = refpix | predpix
	bic	r2, r2, r4, ror #7	// roundval = roundval & 0x01010101
	and	r0, r4, r0, lsr #1	// refpix  = 0x7f7f7f7f & (refpix >>1)
	and	r1, r4, r1, lsr #1	// predpix = 0x7f7f7f7f & (predpix>>1)
	add	r0, r0, r1		// finalpix = refpix + predpix
#else
	uhadd8	r2, r0, r1		// finalpix = refpix + predpix
	eor	r0, r0, r1		// roundval = refpix | predpix
	bic	r0, r0, r4, ror #7	// roundval = roundval & 0x01010101
#endif
	add	r0, r0, r2		// finalpix = finalpix + roundval
	str	r0, [r8], #BLK_SIZE

	// Linear interpolation of four pixels in parallel
	ldmia	r7!, {r0-r3}		// refpix4, refpix5, refpix6, refpix7
	ldrb	r0, [r12, r0, asr #4]	// rounded, normalized and clipped refpix4
	ldrb	r1, [r12, r1, asr #4]	// rounded, normalized and clipped refpix5
	ldrb	r2, [r12, r2, asr #4]	// rounded, normalized and clipped refpix6
	ldrb	r3, [r12, r3, asr #4]	// rounded, normalized and clipped refpix7
	subs	r10, r10, #1		// j--
	orr	r0, r0, r1, lsl #8	// refpix = refpix4 | (refpix5<<8)
	ldr	r1, [r8]		// predpix = four predicted pixel values
	orr	r0, r0, r2, lsl #16	// refpix = refpix  | (refpix6<<16)
	orr	r0, r0, r3, lsl #24	// refpix = refpix  | (refpix7<<24)
#if ARM_ARCH_VERSION < ARM_ARCH_V6
	orr	r2, r0, r1		// roundval = refpix | predpix
	bic	r2, r2, r4, ror #7	// roundval = roundval & 0x01010101
	and	r0, r4, r0, lsr #1	// refpix  = 0x7f7f7f7f & (refpix >>1)
	and	r1, r4, r1, lsr #1	// predpix = 0x7f7f7f7f & (predpix>>1)
	add	r0, r0, r1		// finalpix = refpix + predpix
#else
	uhadd8	r2, r0, r1		// finalpix = refpix + predpix
	eor	r0, r0, r1		// roundval = refpix | predpix
	bic	r0, r0, r4, ror #7	// roundval = roundval & 0x01010101
#endif
	add	r0, r0, r2		// finalpix = finalpix + roundval
	str	r0, [r8], #MBK_SIZE-BLK_SIZE

	bne	L_loop_linear_hh_vs

	b	L_interp_chroma

    /*
     * }
     */


LABELDEF(interp_vh_hq)

    /*
     * else if (yFrac == 2) {
     */

	cmp	r3, #2
	bne	L_interp_diagonal

      /* Vertical 1/2-pel precision, horizontal 1/4-pel precision
       *
       *  X x x x
       *  x x x x
       *  x o x o
       *  x x x x
       *
       */

      /*
       * // Vertical interpolation
       * for (i = -2; i < 2*BLK_SIZE+3; i++) {
       *   for (j = 0; j < 2*BLK_SIZE; j++) {
       *     tmp = (
       *       ONEFOURTH1*(refPtr[ j   *refWidth + i] +
       *                   refPtr[(j+1)*refWidth + i]) +
       *       ONEFOURTH2*(refPtr[(j-1)*refWidth + i] +
       *                   refPtr[(j+2)*refWidth + i]) +
       *       ONEFOURTH3*(refPtr[(j-2)*refWidth + i] +
       *                   refPtr[(j+3)*refWidth + i]));
       *     block[2+i][j] = tmp;
       *   }
       * }
       */

	ldr	r9, [sp, #REF_WIDTH]
	ldr	r7, [sp, #REF_PTR]
	add	r8, sp, #BLOCK
	sub	r7, r7, r9, lsl #1	// refPtr - 2*refWidth
	sub	r7, r7, #2		// - 2
	mov	r11, r9, lsl #3		// 8*refWidth
	add	r11, r11, r9, lsl #2	// 12*refWidth
	rsb	r11, r11, #1		// -12*refWidth + 1
	mov	r10, #(2*BLK_SIZE+2+3)*4
	mov	r12, #(2*BLK_SIZE-1)*(2*BLK_SIZE+2+3)*4-4
	rsb	r12, r12, #0		// -(2*BLK_SIZE-1)*(2*BLK_SIZE+2+3)*4+4
	bl	L_interpolate_block_1D_no_clip


      /*
       * // Horizontal interpolation
       * for (i = 0; i < 2*BLK_SIZE;  i++) {
       *   for (j = 0; j < 2*BLK_SIZE;  j++) {
       *     tmp2 = (
       *       ONEFOURTH1*((int32)(block[2+i  ][j] + block[2+i+1][j])) +
       *       ONEFOURTH2*((int32)(block[2+i-1][j] + block[2+i+2][j])) +
       *       ONEFOURTH3*((int32)(block[2+i-2][j] + block[2+i+3][j])) + 512
       *     ) >> 10;
       *     predPtr[j][i] = (u_int8) clip(0,255,tmp2);
       *   }
       * }
       * // Linear interp.
       * colIdx = 2 + (xFrac >> 1);
       * for (i = 0; i < 2*BLK_SIZE;  i++) {
       *   for (j = 0; j < 2*BLK_SIZE;  j++) {
       *     tmp = (block[colIdx+i][j] + 16) >> 5;
       *     predPtr[j][i] = (u_int8) ((predPtr[j][i] + clip(0,255,tmp) + 1) >> 1);
       *   }
       * }
       */

	ldr	r0, [sp, #X_FRAC]
	add	r7, sp, #BLOCK
	ldr	r8, [sp, #PRED_PTR]
	ldr	r12, L_clipBufPtr
	add	r9, sp, #BLOCK+2*4
	cmp	r0, #3			// if xFrac == 3, use right half-pel
	addeq	r9, r9, #4
	mov	r10, #2*BLK_SIZE
LABELDEF(loop_vh_hq_horiz)
#if ARM_ARCH_VERSION < ARM_ARCH_V6
	ldmia	r7!, {r0-r5}		// a, b, c, d, e, f
	// {r0,r1,r2,r3,r4,r5} = {a,b,c,d,e,f}
	rsb	r6, r1, r2, lsl #2	//        4* c      - b
	add	r6, r6, r3, lsl #2	//        4*(c + d) - b
	sub     r6, r6, r4		//        4*(c + d) - b - e
	ldr	r14, [r9], #4
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r0, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r5		// a + 5*(4*(c + d) - b - e) + f

	ldrb	r14, [r12, r14, asr #4]
	ldrb	r0, [r12, r6, asr #9]

	// {r1,r2,r3,r4,r5,r0} = {a,b,c,d,e,f}
	rsb	r6, r2, r3, lsl #2	//        4* c      - b
	add	r6, r6, r4, lsl #2	//        4*(c + d) - b
	sub     r6, r6, r5		//        4*(c + d) - b - e

	add	r14, r14, r0
	add	r14, r14, #1
	mov	r14, r14, lsr #1
	strb	r14, [r8], #1
	ldr	r14, [r9], #4

	ldr	r0, [r7], #4		// f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r1, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r0		// a + 5*(4*(c + d) - b - e) + f

	ldrb	r14, [r12, r14, asr #4]
	ldrb	r1, [r12, r6, asr #9]

	// {r2,r3,r4,r5,r0,r1} = {a,b,c,d,e,f}
	rsb	r6, r3, r4, lsl #2	//        4* c      - b
	add	r6, r6, r5, lsl #2	//        4*(c + d) - b
	sub     r6, r6, r0		//        4*(c + d) - b - e

	add	r14, r14, r1
	add	r14, r14, #1
	mov	r14, r14, lsr #1
	strb	r14, [r8], #1
	ldr	r14, [r9], #4

	ldr	r1, [r7], #4		// f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r2, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r1		// a + 5*(4*(c + d) - b - e) + f

	ldrb	r14, [r12, r14, asr #4]
	ldrb	r2, [r12, r6, asr #9]

	// {r3,r4,r5,r0,r1,r2} = {a,b,c,d,e,f}
	rsb	r6, r4, r5, lsl #2	//        4* c      - b
	add	r6, r6, r0, lsl #2	//        4*(c + d) - b
	sub     r6, r6, r1		//        4*(c + d) - b - e

	add	r14, r14, r2
	add	r14, r14, #1
	mov	r14, r14, lsr #1
	strb	r14, [r8], #1
	ldr	r14, [r9], #4

	ldr	r2, [r7], #4		// f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r3, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r2		// a + 5*(4*(c + d) - b - e) + f

	ldrb	r14, [r12, r14, asr #4]
	ldrb	r3, [r12, r6, asr #9]

	// {r4,r5,r0,r1,r2,r3} = {a,b,c,d,e,f}
	rsb	r6, r5, r0, lsl #2	//        4* c      - b
	add	r6, r6, r1, lsl #2	//        4*(c + d) - b
	sub     r6, r6, r2		//        4*(c + d) - b - e

	add	r14, r14, r3
	add	r14, r14, #1
	mov	r14, r14, lsr #1
	strb	r14, [r8], #1
	ldr	r14, [r9], #4

	ldr	r3, [r7], #4		// f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r4, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r3		// a + 5*(4*(c + d) - b - e) + f

	ldrb	r14, [r12, r14, asr #4]
	ldrb	r4, [r12, r6, asr #9]

	// {r5,r0,r1,r2,r3,r4} = {a,b,c,d,e,f}
	rsb	r6, r0, r1, lsl #2	//        4* c      - b
	add	r6, r6, r2, lsl #2	//        4*(c + d) - b
	sub     r6, r6, r3		//        4*(c + d) - b - e

	add	r14, r14, r4
	add	r14, r14, #1
	mov	r14, r14, lsr #1
	strb	r14, [r8], #1
	ldr	r14, [r9], #4

	ldr	r4, [r7], #4		// f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r5, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r4		// a + 5*(4*(c + d) - b - e) + f

	ldrb	r14, [r12, r14, asr #4]
	ldrb	r5, [r12, r6, asr #9]

	// {r0,r1,r2,r3,r4,r5} = {a,b,c,d,e,f}
	rsb	r6, r1, r2, lsl #2	//        4* c      - b
	add	r6, r6, r3, lsl #2	//        4*(c + d) - b
	sub     r6, r6, r4		//        4*(c + d) - b - e

	add	r14, r14, r5
	add	r14, r14, #1
	mov	r14, r14, lsr #1
	strb	r14, [r8], #1
	ldr	r14, [r9], #4

	ldr	r5, [r7], #4		// f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r0, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r5		// a + 5*(4*(c + d) - b - e) + f

	ldrb	r14, [r12, r14, asr #4]
	ldrb	r0, [r12, r6, asr #9]

	// {r1,r2,r3,r4,r5,r0} = {a,b,c,d,e,f}
	rsb	r6, r2, r3, lsl #2	//        4* c      - b
	add	r6, r6, r4, lsl #2	//        4*(c + d) - b
	sub     r6, r6, r5		//        4*(c + d) - b - e

	add	r14, r14, r0
	add	r14, r14, #1
	mov	r14, r14, lsr #1
	strb	r14, [r8], #1
	ldr	r14, [r9], #6*4

	ldr	r0, [r7], #4		// f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r1, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r0		// a + 5*(4*(c + d) - b - e) + f

	ldrb	r14, [r12, r14, asr #4]
	ldrb	r1, [r12, r6, asr #9]

	subs	r10, r10, #1

	add	r14, r14, #1
	add	r14, r14, r1
	mov	r14, r14, lsr #1
	strb	r14, [r8], #1+(MBK_SIZE-2*BLK_SIZE)
#else
	ldmia	r7!, {r0-r5}		// a, b, c, d, e, f
	// {r0,r1,r2,r3,r4,r5} = {a,b,c,d,e,f}
	rsb	r6, r1, r2, lsl #2	//        4* c      - b
	add	r6, r6, r3, lsl #2	//        4*(c + d) - b
	sub     r6, r6, r4		//        4*(c + d) - b - e
	ldr	r14, [r9], #4
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r0, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r5		// a + 5*(4*(c + d) - b - e) + f

	ldrb	r14, [r12, r14, asr #4]
	ldrb	r0, [r12, r6, asr #9]

	// {r1,r2,r3,r4,r5,r0} = {a,b,c,d,e,f}
	rsb	r6, r2, r3, lsl #2	//        4* c      - b
	add	r6, r6, r4, lsl #2	//        4*(c + d) - b
	sub     r6, r6, r5		//        4*(c + d) - b - e

	add	r14, r14, #1
	uhadd16	r14, r14, r0
	ldr	r0, [r7], #4		// f
	strb	r14, [r8], #1
	ldr	r14, [r9], #4

	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r1, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r0		// a + 5*(4*(c + d) - b - e) + f

	ldrb	r14, [r12, r14, asr #4]
	ldrb	r1, [r12, r6, asr #9]

	// {r2,r3,r4,r5,r0,r1} = {a,b,c,d,e,f}
	rsb	r6, r3, r4, lsl #2	//        4* c      - b
	add	r6, r6, r5, lsl #2	//        4*(c + d) - b
	sub     r6, r6, r0		//        4*(c + d) - b - e

	add	r14, r14, #1
	uhadd16	r14, r14, r1
	ldr	r1, [r7], #4		// f
	strb	r14, [r8], #1
	ldr	r14, [r9], #4

	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r2, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r1		// a + 5*(4*(c + d) - b - e) + f

	ldrb	r14, [r12, r14, asr #4]
	ldrb	r2, [r12, r6, asr #9]

	// {r3,r4,r5,r0,r1,r2} = {a,b,c,d,e,f}
	rsb	r6, r4, r5, lsl #2	//        4* c      - b
	add	r6, r6, r0, lsl #2	//        4*(c + d) - b
	sub     r6, r6, r1		//        4*(c + d) - b - e

	add	r14, r14, #1
	uhadd16	r14, r14, r2
	ldr	r2, [r7], #4		// f
	strb	r14, [r8], #1
	ldr	r14, [r9], #4

	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r3, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r2		// a + 5*(4*(c + d) - b - e) + f

	ldrb	r14, [r12, r14, asr #4]
	ldrb	r3, [r12, r6, asr #9]

	// {r4,r5,r0,r1,r2,r3} = {a,b,c,d,e,f}
	rsb	r6, r5, r0, lsl #2	//        4* c      - b
	add	r6, r6, r1, lsl #2	//        4*(c + d) - b
	sub     r6, r6, r2		//        4*(c + d) - b - e

	add	r14, r14, #1
	uhadd16	r14, r14, r3
	ldr	r3, [r7], #4		// f
	strb	r14, [r8], #1
	ldr	r14, [r9], #4

	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r4, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r3		// a + 5*(4*(c + d) - b - e) + f

	ldrb	r14, [r12, r14, asr #4]
	ldrb	r4, [r12, r6, asr #9]

	// {r5,r0,r1,r2,r3,r4} = {a,b,c,d,e,f}
	rsb	r6, r0, r1, lsl #2	//        4* c      - b
	add	r6, r6, r2, lsl #2	//        4*(c + d) - b
	sub     r6, r6, r3		//        4*(c + d) - b - e

	add	r14, r14, #1
	uhadd16	r14, r14, r4
	ldr	r4, [r7], #4		// f
	strb	r14, [r8], #1
	ldr	r14, [r9], #4

	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r5, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r4		// a + 5*(4*(c + d) - b - e) + f

	ldrb	r14, [r12, r14, asr #4]
	ldrb	r5, [r12, r6, asr #9]

	// {r0,r1,r2,r3,r4,r5} = {a,b,c,d,e,f}
	rsb	r6, r1, r2, lsl #2	//        4* c      - b
	add	r6, r6, r3, lsl #2	//        4*(c + d) - b
	sub     r6, r6, r4		//        4*(c + d) - b - e

	add	r14, r14, #1
	uhadd16	r14, r14, r5
	ldr	r5, [r7], #4		// f
	strb	r14, [r8], #1
	ldr	r14, [r9], #4

	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r0, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r5		// a + 5*(4*(c + d) - b - e) + f

	ldrb	r14, [r12, r14, asr #4]
	ldrb	r0, [r12, r6, asr #9]

	// {r1,r2,r3,r4,r5,r0} = {a,b,c,d,e,f}
	rsb	r6, r2, r3, lsl #2	//        4* c      - b
	add	r6, r6, r4, lsl #2	//        4*(c + d) - b
	sub     r6, r6, r5		//        4*(c + d) - b - e

	add	r14, r14, #1
	uhadd16	r14, r14, r0
	ldr	r0, [r7], #4		// f
	strb	r14, [r8], #1
	ldr	r14, [r9], #6*4

	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r1, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r0		// a + 5*(4*(c + d) - b - e) + f

	ldrb	r14, [r12, r14, asr #4]
	ldrb	r1, [r12, r6, asr #9]

	subs	r10, r10, #1

	add	r14, r14, #1
	uhadd16	r14, r14, r1
	strb	r14, [r8], #1+(MBK_SIZE-2*BLK_SIZE)
#endif

	bne	L_loop_vh_hq_horiz

	b	L_interp_chroma

    /*
     * }
     */


LABELDEF(interp_diagonal)

    /*
     * else {
     */

      /* Horizontal&vertical 1/4-pel precision -> diagonal interpolation
       *
       *  X x x x
       *  x o x o
       *  x x x x
       *  x o x o
       *
       */

      /*
       * // Vertical interpolation
       * colIdx = xFrac >> 1;
       * for (j = 0; j < 2*BLK_SIZE; j++) {
       *   for (i = 0; i < 2*BLK_SIZE; i++) {
       *     tmp = (
       *       ONEFOURTH1*(refPtr[ j   *refWidth + i+colIdx] +
       *                   refPtr[(j+1)*refWidth + i+colIdx]) +
       *       ONEFOURTH2*(refPtr[(j-1)*refWidth + i+colIdx] +
       *                   refPtr[(j+2)*refWidth + i+colIdx]) +
       *       ONEFOURTH3*(refPtr[(j-2)*refWidth + i+colIdx] +
       *                   refPtr[(j+3)*refWidth + i+colIdx]) + 16
       *     ) >> 5;
       *     predPtr[j][i] = (u_int8) clip(0,255,tmp);
       *   }
       * }
       */

	ldr	r7, [sp, #REF_PTR]
	ldr	r9, [sp, #REF_WIDTH]
	ldr	r0, [sp, #X_FRAC]
	ldr	r8, [sp, #PRED_PTR]
	ldr	r12, L_clipBufPtr
	sub	r7, r7, r9, lsl #1	// refPtr - 2*refWidth
	add	r7, r7, r0, lsr #1
	mov	r11, #MBK_SIZE
	mov	r0, r9, lsl #3		// 8*refWidth
	add	r0, r0, r9, lsl #2	// 12*refWidth
	rsb	r0, r0, #1		// -12*refWidth + 1
	mov	r1, #-(2*BLK_SIZE-1)*MBK_SIZE+1
	bl	L_interpolate_block_1D


      /*
       * // Horizontal interpolation
       * lineIdx = yFrac >> 1;
       * for (j = 0; j < 2*BLK_SIZE; j++) {
       *   for (i = 0; i < 2*BLK_SIZE; i++) {
       *     tmp = (
       *       ONEFOURTH1*(refPtr[(j+lineIdx)*refWidth + i  ] +
       *                   refPtr[(j+lineIdx)*refWidth + i+1]) +
       *       ONEFOURTH2*(refPtr[(j+lineIdx)*refWidth + i-1] +
       *                   refPtr[(j+lineIdx)*refWidth + i+2]) +
       *       ONEFOURTH3*(refPtr[(j+lineIdx)*refWidth + i-2] +
       *                   refPtr[(j+lineIdx)*refWidth + i+3]) + 16
       *     ) >> 5;
       *     predPtr[j][i] = (u_int8) ((predPtr[j][i] + clip(0,255,tmp) + 1) >> 1);
       *   }
       * }
       */

	ldr	r1, [sp, #Y_FRAC]
	ldr	r7, [sp, #REF_PTR]
	ldr	r11, [sp, #REF_WIDTH]
	ldr	r8, [sp, #PRED_PTR]
	ldr	r12, L_clipBufPtr
	sub	r7, r7, #2		// refPtr - 2
	movs	r1, r1, lsr #1		// lineIdx = yFrac >> 1
	addne	r7, r7, r11		// refPtr += lineIdx*refWidth
	sub	r11, r11, #12		// refWidth - 12
	mov	r10, #2*BLK_SIZE
	ldr	r9, L_0x7f7f7f7f
LABELDEF(loop_diag_horiz)
	ldrb    r0, [r7], #1		// a
	ldrb    r1, [r7], #1		// b
	ldrb    r2, [r7], #1		// c
	ldrb    r3, [r7], #1		// d
	ldrb    r4, [r7], #1 		// e
	ldrb    r5, [r7], #1		// f
	// {r0,r1,r2,r3,r4,r5} = {a,b,c,d,e,f}
	rsb	r6, r1, r2, lsl #2	//        4* c      - b
	add	r6, r6, r3, lsl #2	//        4*(c + d) - b
	sub     r6, r6, r4		//        4*(c + d) - b - e
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r0, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r5		// a + 5*(4*(c + d) - b - e) + f
	ldrb	r14, [r12, r6, asr #4]

	// {r1,r2,r3,r4,r5,r0} = {a,b,c,d,e,f}
	rsb	r6, r2, r3, lsl #2	//        4* c      - b
	add	r6, r6, r4, lsl #2	//        4*(c + d) - b
	ldrb    r0, [r7], #1		// f
	sub     r6, r6, r5		//        4*(c + d) - b - e
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r1, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r0		// a + 5*(4*(c + d) - b - e) + f
	ldrb	r1, [r12, r6, asr #4]

	// {r2,r3,r4,r5,r0,r1} = {a,b,c,d,e,f}
	rsb	r6, r3, r4, lsl #2	//        4* c      - b
	add	r6, r6, r5, lsl #2	//        4*(c + d) - b
	orr	r14, r14, r1, lsl #8
	ldrb    r1, [r7], #1		// f
	sub     r6, r6, r0		//        4*(c + d) - b - e
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r2, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r1		// a + 5*(4*(c + d) - b - e) + f
	ldrb	r2, [r12, r6, asr #4]

	// {r3,r4,r5,r0,r1,r2} = {a,b,c,d,e,f}
	rsb	r6, r4, r5, lsl #2	//        4* c      - b
	add	r6, r6, r0, lsl #2	//        4*(c + d) - b
	orr	r14, r14, r2, lsl #16
	ldrb    r2, [r7], #1		// f
	sub     r6, r6, r1		//        4*(c + d) - b - e
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r3, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r2		// a + 5*(4*(c + d) - b - e) + f
	ldrb	r3, [r12, r6, asr #4]

	// Linear interpolation of four pixels in parallel
	ldr	r6, [r8]		// predpix = four predicted pixel values
	orr	r14, r14, r3, lsl #24	// refpix = refpix  | (refpix3<<24)
#if ARM_ARCH_VERSION < ARM_ARCH_V6
	orr	r3, r14, r6		// roundval = refpix | predpix
	bic	r3, r3, r9, ror #7	// roundval = roundval & 0x01010101
	and	r14, r9, r14, lsr #1	// refpix  = 0x7f7f7f7f & (refpix >>1)
	and	r6, r9, r6, lsr #1	// predpix = 0x7f7f7f7f & (predpix>>1)
	add	r14, r14, r6		// finalpix = refpix + predpix
#else
	uhadd8	r3, r14, r6		// finalpix = refpix + predpix
	eor	r14, r14, r6		// roundval = refpix | predpix
	bic	r14, r14, r9, ror #7	// roundval = roundval & 0x01010101
#endif
	add	r14, r14, r3		// finalpix = finalpix + roundval
	str	r14, [r8], #BLK_SIZE

	// {r4,r5,r0,r1,r2,r3} = {a,b,c,d,e,f}
	rsb	r6, r5, r0, lsl #2	//        4* c      - b
	add	r6, r6, r1, lsl #2	//        4*(c + d) - b
	ldrb    r3, [r7], #1		// f
	sub     r6, r6, r2		//        4*(c + d) - b - e
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r4, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r3		// a + 5*(4*(c + d) - b - e) + f
	ldrb	r14, [r12, r6, asr #4]

	// {r5,r0,r1,r2,r3,r4} = {a,b,c,d,e,f}
	rsb	r6, r0, r1, lsl #2	//        4* c      - b
	add	r6, r6, r2, lsl #2	//        4*(c + d) - b
	ldrb    r4, [r7], #1		// f
	sub     r6, r6, r3		//        4*(c + d) - b - e
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r5, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r4		// a + 5*(4*(c + d) - b - e) + f
	ldrb	r5, [r12, r6, asr #4]

	// {r0,r1,r2,r3,r4,r5} = {a,b,c,d,e,f}
	rsb	r6, r1, r2, lsl #2	//        4* c      - b
	add	r6, r6, r3, lsl #2	//        4*(c + d) - b
	orr	r14, r14, r5, lsl #8
	ldrb    r5, [r7], #1		// f
	sub     r6, r6, r4		//        4*(c + d) - b - e
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r0, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r5		// a + 5*(4*(c + d) - b - e) + f
	ldrb	r0, [r12, r6, asr #4]

	// {r1,r2,r3,r4,r5,r0} = {a,b,c,d,e,f}
	rsb	r6, r2, r3, lsl #2	//        4* c      - b
	add	r6, r6, r4, lsl #2	//        4*(c + d) - b
	orr	r14, r14, r0, lsl #16
	ldrb    r0, [r7], r11		// f
	sub     r6, r6, r5		//        4*(c + d) - b - e
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r1, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r0		// a + 5*(4*(c + d) - b - e) + f
	ldrb	r1, [r12, r6, asr #4]

	// Linear interpolation of four pixels in parallel
	ldr	r6, [r8]		// predpix = four predicted pixel values
	subs	r10, r10, #1		// j--
	orr	r14, r14, r1, lsl #24	// refpix = refpix  | (refpix3<<24)
#if ARM_ARCH_VERSION < ARM_ARCH_V6
	orr	r1, r14, r6		// roundval = refpix | predpix
	bic	r1, r1, r9, ror #7	// roundval = roundval & 0x01010101
	and	r14, r9, r14, lsr #1	// refpix  = 0x7f7f7f7f & (refpix >>1)
	and	r6, r9, r6, lsr #1	// predpix = 0x7f7f7f7f & (predpix>>1)
	add	r14, r14, r6		// finalpix = refpix + predpix
#else
	uhadd8	r1, r14, r6		// finalpix = refpix + predpix
	eor	r14, r14, r6		// roundval = refpix | predpix
	bic	r14, r14, r9, ror #7	// roundval = roundval & 0x01010101
#endif
	add	r14, r14, r1		// finalpix = finalpix + roundval
	str	r14, [r8], #MBK_SIZE-BLK_SIZE

	bne	L_loop_diag_horiz


    /*
     * }
     */

  /*
   * }
   */



LABELDEF(interp_chroma)


  /************************************************************
   *
   *  Chroma interpolation
   *
   ************************************************************/


#define COEF0 r10
#define COEF1 r11
#define COEF2 r12
#define COEF3 r14

	ldr	r0, [sp, #X_POS]
	ldr	r1, [sp, #Y_POS]

	and	r2, r0, #7			// xFrac = xPos&7
	and	r3, r1, #7			// yFrac = yPos&7

        /* Chroma vectors have 1/8 chroma pel precision */
	mov	r0, r0, asr #3			// xInt  = xPos >> 3
	mov	r1, r1, asr #3			// yInt  = yPos >> 3

	ldr	r6, [sp, #REF]
	ldr	r9, [sp, #PIC_WIDTH_C]
	ldr	r10, [sp, #PIC_HEIGHT_C]
	ldr	r7, [r6, #4]			// ref->u
	ldr	r6, [r6, #8]			// ref->v

  /*
   * if (xInt >= 0 && xInt < picWidthC-2*BLK_SIZE/2 &&
   *     yInt >= 0 && yInt < picHeightC-2*BLK_SIZE/2)
   * {
   *   refC[0] = &ref->u[yInt*picWidthC+xInt];
   *   refC[1] = &ref->v[yInt*picWidthC+xInt];
   *   refWidth = picWidthC;
   * }
   * else {
   *   getRefAreaC(ref->u, refArea    , picWidthC, picHeightC, xInt, yInt);
   *   getRefAreaC(ref->v, refArea+5*5, picWidthC, picHeightC, xInt, yInt);
   *   refC[0] = refArea;
   *   refC[1] = refArea+5*5;
   *   refWidth = 3;
   * }
   */

	sub	r4, r9, #2*BLK_SIZE/2
	sub	r5, r10, #2*BLK_SIZE/2
	cmp	r0, r4				// if (unsigned)xInt >= (picWidthC-2*BLK_SIZE/2) and
	cmplo	r1, r5				// if (unsigned)yInt < (picHeightC-2*BLK_SIZE/2)
	blo	L_interp_chroma_no_bound_checks	// then no bound checks

        // note: this code corresponds to the 'else' block in c code
	add	r8, sp, #REF_AREA
	bl	L_get_ref_area_C_5x5		// get 5x5 block (actually 8x5)
	add	r7, sp, #REF_AREA		// refC[0] = refArea
	add	r7, r7, r0			// refC[0] += offset for reference block
	add	r6, r7, #5*8			// refC[1] = refC[0]+5*8
	ldr	r0, [sp, #X_POS]
	ldr	r1, [sp, #Y_POS]
	and	r2, r0, #7			// xFrac = xPos&7
	and	r3, r1, #7			// yFrac = yPos&7
	mov	r9, #8-4			// refWidthC - 4
	b	L_interp_chroma_cont

LABELDEF(interp_chroma_no_bound_checks)
        // note: this code corresponds to the 'if' block in c code
	MLA	r0, r9, r1, r0			// refWidthC*yInt + xInt
	sub	r9, r9, #4			// refWidthC - 4
	add	r7, r7, r0			// refC[0]
	add	r6, r6, r0			// refC[1]

LABELDEF(interp_chroma_cont)


  /* Bilinear interpolation coefficients */
  /*
   * coef3 = xFrac * yFrac;
   * coef2 = 8*yFrac - coef3;
   * coef1 = 8*xFrac - coef3;
   * coef0 = 8*(8 - yFrac) - coef1;
   */

	MUL	COEF3, r2, r3
	rsb	COEF0, r3, #8			// (8-yFrac)
	rsb	COEF2, COEF3, r3, lsl #3	// 8*yFrac - coef3
	rsb	COEF1, COEF3, r2, lsl #3	// 8*xFrac - coef3
	rsb	COEF0, COEF1, COEF0, lsl #3	// 8*(8-yFrac) - coef1

#if ARM_ARCH_VERSION >= ARM_ARCH_V6
	orr	COEF0, COEF0, COEF1, lsl #16
	orr	COEF1, COEF2, COEF3, lsl #16
#endif

	ldr	r8, [sp, #PRED_C]

  /*
   * for (c = 0; c < 2; c++) {
   *   for (j = 0; j < 2*BLK_SIZE/2;  j++) {
   *     for (i = 0; i < 2*BLK_SIZE/2;  i++) {
   *       tmp = (coef0 * refC[comp][(j  )*refWidthC + i  ] +
   *              coef1 * refC[comp][(j  )*refWidthC + i+1] +
   *              coef2 * refC[comp][(j+1)*refWidthC + i  ] +
   *              coef3 * refC[comp][(j+1)*refWidthC + i+1] + 32) >> 6;
   *       predC[blkIdxY*(BLK_SIZE/2)+j][c*(MBK_SIZE/2)+blkIdxX*(BLK_SIZE/2)+i] = tmp;
   *     }
   *   }
   * }
   */

	mov	r5, #2
	str	r5, [sp, #COUNTER_C]
	str	r6, [sp, #REFC_1]

LABELDEF(loop_chroma)

	// reference pixels
	// a0 a1 a2 a3 a4
	// b0 b1 b2 b3 b4
	// c0 c1 c2 c3 c4
	// d0 d1 d2 d3 d4
	// e0 e1 e2 e3 e4

	// interpolated pixels
	// A0 A1 A2 A3
	// B0 B1 B2 B3
	// C0 C1 C2 C3
	// D0 D1 D2 D3

#if ARM_ARCH_VERSION < ARM_ARCH_V6

	// First row

	ldrb	r0, [r7], #1			// a0
	ldrb	r1, [r7], #1			// a1
	ldrb	r2, [r7], #1			// a2
	ldrb	r3, [r7], #1			// a3
	ldrb	r4, [r7], r9			// a4

	MUL	r5, r0, COEF0			// A0 = a0*COEF0
	ldrb	r0, [r7], #1			// b0
	MLA	r5, r1, COEF1, r5		// A0 += a1*COEF1
	MUL	r6, r1, COEF0			// A1 = a1*COEF0
	ldrb	r1, [r7], #1			// b1
	MLA	r5, r0, COEF2, r5		// A0 += b0*COEF2
	MLA	r6, r2, COEF1, r6		// A1 += a2*COEF1
	MLA	r5, r1, COEF3, r5		// A0 += b1*COEF3
	MLA	r6, r1, COEF2, r6		// A1 += b1*COEF2
	add	r5, r5, #32			// A0 rounding
	mov	r5, r5, lsr #6			// A0 normalization
	strb	r5, [r8], #1			// A0 store
	MUL	r5, r2, COEF0			// A2 = a2*COEF0
	ldrb	r2, [r7], #1			// b2
	MLA	r5, r3, COEF1, r5		// A2 += a3*COEF1
	add	r6, r6, #32			// A1 rounding
	MLA	r6, r2, COEF3, r6		// A1 += b2*COEF3
	MLA	r5, r2, COEF2, r5		// A2 += b2*COEF2
	mov	r6, r6, lsr #6			// A1 normalization
	strb	r6, [r8], #1			// A1 store
	MUL	r6, r3, COEF0			// A3 = a3*COEF0
	ldrb	r3, [r7], #1			// b3
	MLA	r6, r4, COEF1, r6		// A3 += a4*COEF1
	ldrb	r4, [r7], r9			// b4
	add	r5, r5, #32			// A2 rounding
	MLA	r5, r3, COEF3, r5		// A2 += b3*COEF3
	MLA	r6, r3, COEF2, r6		// A3 += b3*COEF2
	MLA	r6, r4, COEF3, r6		// A3 += b4*COEF3
	mov	r5, r5, lsr #6			// A2 normalization
	strb	r5, [r8], #1			// A2 store
	add	r6, r6, #32			// A3 rounding
	mov	r6, r6, lsr #6			// A3 normalization
	strb	r6, [r8], #1+MBK_SIZE-BLK_SIZE	// A3 store

	// Second row

	MUL	r5, r0, COEF0			// B0 = b0*COEF0
	ldrb	r0, [r7], #1			// c0
	MLA	r5, r1, COEF1, r5		// B0 += b1*COEF1
	MUL	r6, r1, COEF0			// B1 = b1*COEF0
	ldrb	r1, [r7], #1			// c1
	MLA	r5, r0, COEF2, r5		// B0 += c0*COEF2
	MLA	r6, r2, COEF1, r6		// B1 += b2*COEF1
	MLA	r5, r1, COEF3, r5		// B0 += c1*COEF3
	MLA	r6, r1, COEF2, r6		// B1 += c1*COEF2
	add	r5, r5, #32			// B0 rounding
	mov	r5, r5, lsr #6			// B0 normalization
	strb	r5, [r8], #1			// B0 store
	MUL	r5, r2, COEF0			// B2 = b2*COEF0
	ldrb	r2, [r7], #1			// c2
	MLA	r5, r3, COEF1, r5		// B2 += b3*COEF1
	add	r6, r6, #32			// B1 rounding
	MLA	r6, r2, COEF3, r6		// B1 += c2*COEF3
	MLA	r5, r2, COEF2, r5		// B2 += c2*COEF2
	mov	r6, r6, lsr #6			// B1 normalization
	strb	r6, [r8], #1			// B1 store
	MUL	r6, r3, COEF0			// B3 = b3*COEF0
	ldrb	r3, [r7], #1			// c3
	MLA	r6, r4, COEF1, r6		// B3 += b4*COEF1
	ldrb	r4, [r7], r9			// c4
	add	r5, r5, #32			// B2 rounding
	MLA	r5, r3, COEF3, r5		// B2 += c3*COEF3
	MLA	r6, r3, COEF2, r6		// B3 += c3*COEF2
	MLA	r6, r4, COEF3, r6		// B3 += c4*COEF3
	mov	r5, r5, lsr #6			// B2 normalization
	strb	r5, [r8], #1			// B2 store
	add	r6, r6, #32			// B3 rounding
	mov	r6, r6, lsr #6			// B3 normalization
	strb	r6, [r8], #1+MBK_SIZE-BLK_SIZE	// B3 store

	// Third row

	MUL	r5, r0, COEF0			// C0 = c0*COEF0
	ldrb	r0, [r7], #1			// d0
	MLA	r5, r1, COEF1, r5		// C0 += c1*COEF1
	MUL	r6, r1, COEF0			// C1 = c1*COEF0
	ldrb	r1, [r7], #1			// d1
	MLA	r5, r0, COEF2, r5		// C0 += d0*COEF2
	MLA	r6, r2, COEF1, r6		// C1 += c2*COEF1
	MLA	r5, r1, COEF3, r5		// C0 += d1*COEF3
	MLA	r6, r1, COEF2, r6		// C1 += d1*COEF2
	add	r5, r5, #32			// C0 rounding
	mov	r5, r5, lsr #6			// C0 normalization
	strb	r5, [r8], #1			// C0 store
	MUL	r5, r2, COEF0			// C2 = c2*COEF0
	ldrb	r2, [r7], #1			// d2
	MLA	r5, r3, COEF1, r5		// C2 += c3*COEF1
	add	r6, r6, #32			// C1 rounding
	MLA	r6, r2, COEF3, r6		// C1 += d2*COEF3
	MLA	r5, r2, COEF2, r5		// C2 += d2*COEF2
	mov	r6, r6, lsr #6			// C1 normalization
	strb	r6, [r8], #1			// C1 store
	MUL	r6, r3, COEF0			// C3 = c3*COEF0
	ldrb	r3, [r7], #1			// d3
	MLA	r6, r4, COEF1, r6		// C3 += c4*COEF1
	ldrb	r4, [r7], r9			// d4
	add	r5, r5, #32			// C2 rounding
	MLA	r5, r3, COEF3, r5		// C2 += d3*COEF3
	MLA	r6, r3, COEF2, r6		// C3 += d3*COEF2
	MLA	r6, r4, COEF3, r6		// C3 += d4*COEF3
	mov	r5, r5, lsr #6			// C2 normalization
	strb	r5, [r8], #1			// C2 store
	add	r6, r6, #32			// C3 rounding
	mov	r6, r6, lsr #6			// C3 normalization
	strb	r6, [r8], #1+MBK_SIZE-BLK_SIZE	// C3 store

	// Fourth row

	MUL	r5, r0, COEF0			// D0 = d0*COEF0
	ldrb	r0, [r7], #1			// e0
	MLA	r5, r1, COEF1, r5		// D0 += d1*COEF1
	MUL	r6, r1, COEF0			// D1 = d1*COEF0
	ldrb	r1, [r7], #1			// e1
	MLA	r5, r0, COEF2, r5		// D0 += e0*COEF2
	MLA	r6, r2, COEF1, r6		// D1 += d2*COEF1
	MLA	r5, r1, COEF3, r5		// D0 += e1*COEF3
	MLA	r6, r1, COEF2, r6		// D1 += e1*COEF2
	add	r5, r5, #32			// D0 rounding
	mov	r5, r5, lsr #6			// D0 normalization
	strb	r5, [r8], #1			// D0 store
	MUL	r5, r2, COEF0			// D2 = d2*COEF0
	ldrb	r2, [r7], #1			// e2
	MLA	r5, r3, COEF1, r5		// D2 += d3*COEF1
	add	r6, r6, #32			// D1 rounding
	MLA	r6, r2, COEF3, r6		// D1 += e2*COEF3
	MLA	r5, r2, COEF2, r5		// D2 += e2*COEF2
	mov	r6, r6, lsr #6			// D1 normalization
	strb	r6, [r8], #1			// D1 store
	MUL	r6, r3, COEF0			// D3 = d3*COEF0
	ldrb	r3, [r7], #1			// e3
	MLA	r6, r4, COEF1, r6		// D3 += d4*COEF1
	ldrb	r4, [r7], r9			// e4
	add	r5, r5, #32			// D2 rounding
	MLA	r5, r3, COEF3, r5		// D2 += e3*COEF3
	MLA	r6, r3, COEF2, r6		// D3 += e3*COEF2
	MLA	r6, r4, COEF3, r6		// D3 += e4*COEF3
	mov	r5, r5, lsr #6			// D2 normalization
	strb	r5, [r8], #1			// D2 store
	add	r6, r6, #32			// D3 rounding
	mov	r6, r6, lsr #6			// D3 normalization
	strb	r6, [r8], #-3-3*MBK_SIZE+MBK_SIZE/2	// D3 store

#else

	// ARMv6 spesific code

	// First row

	ldrb	r0, [r7], #1			// a0
	ldrb	r1, [r7], #1			// a1
	ldrb	r2, [r7], #1			// a2
	ldrb	r3, [r7], #1			// a3
	ldrb	r14, [r7], r9			// a4

	orr	r0, r1, r0, lsl #16
	orr	r1, r2, r1, lsl #16
	orr	r2, r3, r2, lsl #16
	orr	r3, r14, r3, lsl #16
	smuadx	r0, COEF0, r0
	smuadx	r1, COEF0, r1
	smuadx	r2, COEF0, r2
	smuadx	r3, COEF0, r3
	ldrb	r4, [r7], #1			// b0
	ldrb	r5, [r7], #1			// b1
	ldrb	r6, [r7], #1			// b2
	ldrb	r12, [r7], #1			// b3
	ldrb	r14, [r7], r9			// b4
	orr	r4, r5, r4, lsl #16
	orr	r5, r6, r5, lsl #16
	orr	r6, r12, r6, lsl #16
	orr	r12, r14, r12, lsl #16
	smladx	r0, COEF1, r4, r0
	smladx	r1, COEF1, r5, r1
	smladx	r2, COEF1, r6, r2
	smladx	r3, COEF1, r12, r3
	add	r0, r0, #32
	add	r1, r1, #32
	add	r2, r2, #32
	add	r3, r3, #32
	mov	r0, r0, lsr #6
	mov	r1, r1, lsr #6
	mov	r2, r2, lsr #6
	mov	r3, r3, lsr #6
	strb	r0, [r8], #1
	strb	r1, [r8], #1
	strb	r2, [r8], #1
	strb	r3, [r8], #1+MBK_SIZE-BLK_SIZE

	// Second row

	smuadx	r4, COEF0, r4
	smuadx	r5, COEF0, r5
	smuadx	r6, COEF0, r6
	smuadx	r12, COEF0, r12
	ldrb	r0, [r7], #1			// c0
	ldrb	r1, [r7], #1			// c1
	ldrb	r2, [r7], #1			// c2
	ldrb	r3, [r7], #1			// c3
	ldrb	r14, [r7], r9			// c4
	orr	r0, r1, r0, lsl #16
	orr	r1, r2, r1, lsl #16
	orr	r2, r3, r2, lsl #16
	orr	r3, r14, r3, lsl #16
	smladx	r4, COEF1, r0, r4
	smladx	r5, COEF1, r1, r5
	smladx	r6, COEF1, r2, r6
	smladx	r12, COEF1, r3, r12
	add	r4, r4, #32
	add	r5, r5, #32
	add	r6, r6, #32
	add	r12, r12, #32
	mov	r4, r4, lsr #6
	mov	r5, r5, lsr #6
	mov	r6, r6, lsr #6
	mov	r12, r12, lsr #6
	strb	r4, [r8], #1
	strb	r5, [r8], #1
	strb	r6, [r8], #1
	strb	r12, [r8], #1+MBK_SIZE-BLK_SIZE

	// Third row

	smuadx	r0, COEF0, r0
	smuadx	r1, COEF0, r1
	smuadx	r2, COEF0, r2
	smuadx	r3, COEF0, r3
	ldrb	r4, [r7], #1			// d0
	ldrb	r5, [r7], #1			// d1
	ldrb	r6, [r7], #1			// d2
	ldrb	r12, [r7], #1			// d3
	ldrb	r14, [r7], r9			// d4
	orr	r4, r5, r4, lsl #16
	orr	r5, r6, r5, lsl #16
	orr	r6, r12, r6, lsl #16
	orr	r12, r14, r12, lsl #16
	smladx	r0, COEF1, r4, r0
	smladx	r1, COEF1, r5, r1
	smladx	r2, COEF1, r6, r2
	smladx	r3, COEF1, r12, r3
	add	r0, r0, #32
	add	r1, r1, #32
	add	r2, r2, #32
	add	r3, r3, #32
	mov	r0, r0, lsr #6
	mov	r1, r1, lsr #6
	mov	r2, r2, lsr #6
	mov	r3, r3, lsr #6
	strb	r0, [r8], #1
	strb	r1, [r8], #1
	strb	r2, [r8], #1
	strb	r3, [r8], #1+MBK_SIZE-BLK_SIZE

	// Fourth row

	smuadx	r4, COEF0, r4
	smuadx	r5, COEF0, r5
	smuadx	r6, COEF0, r6
	smuadx	r12, COEF0, r12
	ldrb	r0, [r7], #1			// e0
	ldrb	r1, [r7], #1			// e1
	ldrb	r2, [r7], #1			// e2
	ldrb	r3, [r7], #1			// e3
	ldrb	r14, [r7], r9			// e4
	orr	r0, r1, r0, lsl #16
	orr	r1, r2, r1, lsl #16
	orr	r2, r3, r2, lsl #16
	orr	r3, r14, r3, lsl #16
	smladx	r4, COEF1, r0, r4
	smladx	r5, COEF1, r1, r5
	smladx	r6, COEF1, r2, r6
	smladx	r12, COEF1, r3, r12
	add	r4, r4, #32
	add	r5, r5, #32
	add	r6, r6, #32
	add	r12, r12, #32
	mov	r4, r4, lsr #6
	mov	r5, r5, lsr #6
	mov	r6, r6, lsr #6
	mov	r12, r12, lsr #6
	strb	r4, [r8], #1
	strb	r5, [r8], #1
	strb	r6, [r8], #1
	strb	r12, [r8], #-3-3*MBK_SIZE+MBK_SIZE/2

#endif

	ldr	r5, [sp, #COUNTER_C]
	ldr	r7, [sp, #REFC_1]
	subs	r5, r5, #1
	str	r5, [sp, #COUNTER_C]
	bne	L_loop_chroma


/*
 * }
 */

	add	sp, sp, #LOC_SIZE		// free stack space
	ldmfd	sp!, {r4-r12, lr}		// restore 10 regs
	bx	lr				// return



	ALIGNW

LABELDEF(clipBufPtr)
	DEFW	clip8Buf+512

LABELDEF(0x7f7f7f7f)
	DEFW	0x7f7f7f7f



/****************************************************************************
 *
 * interpolate_block_1D:
 *
 * Parameters:
 *      r7 = frm          Pointer to reference pixels
 *      r8 = predPtr      Pointer for interpolated pixels
 *      r9 = step         Step in filter direction
 *      r11 = stepP       Step in destination buffer
 *      r12 = clipTab     Pointer to clip table
 *      r0 = step2        Backward step in filter direction
 *      r1 = stepP2       Backward step in destination buffer
 *
 * Function:
 *      Interpolate 8x8 block in one dimension.
 *
 *      The function does not use standard function calling conventions.
 *
 * Returns:
 *      -
 *
 ****************************************************************************/

LABELDEF(interpolate_block_1D)

	stmdb	sp!, {r0, r1, lr}
	mov	r10, #2*BLK_SIZE

LABELDEF(loop_interp_8_pels)

	ldrb    r0, [r7], r9		// a
	ldrb    r1, [r7], r9		// b
	ldrb    r2, [r7], r9		// c
	ldrb    r3, [r7], r9		// d
	ldrb    r4, [r7], r9 		// e
	ldrb    r5, [r7], r9		// f
	// {r0,r1,r2,r3,r4,r5} = {a,b,c,d,e,f}
	rsb	r6, r1, r2, lsl #2	//        4* c      - b
	add	r6, r6, r3, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r4		//        4*(c + d) - b - e
	add	r0, r0, r5		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r0, r6		// a + 5*(4*(c + d) - b - e) + f

	ldrb    r0, [r7], r9		// f
	ldrb	r14, [r12, r6, asr #4]
	// {r1,r2,r3,r4,r5,r0} = {a,b,c,d,e,f}
	rsb	r6, r2, r3, lsl #2	//        4* c      - b
	add	r6, r6, r4, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r5		//        4*(c + d) - b - e
	add	r1, r1, r0		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r1, r6		// a + 5*(4*(c + d) - b - e) + f
	strb	r14, [r8], r11		// #MBK_SIZE

	ldrb    r1, [r7], r9		// f
	ldrb	r14, [r12, r6, asr #4]
	// {r2,r3,r4,r5,r0,r1} = {a,b,c,d,e,f}
	rsb	r6, r3, r4, lsl #2	//        4* c      - b
	add	r6, r6, r5, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r0		//        4*(c + d) - b - e
	add	r2, r2, r1		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r2, r6		// a + 5*(4*(c + d) - b - e) + f
	strb	r14, [r8], r11

	ldrb    r2, [r7], r9		// f
	ldrb	r14, [r12, r6, asr #4]
	// {r3,r4,r5,r0,r1,r2} = {a,b,c,d,e,f}
	rsb	r6, r4, r5, lsl #2	//        4* c      - b
	add	r6, r6, r0, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r1		//        4*(c + d) - b - e
	add	r3, r3, r2		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r3, r6		// a + 5*(4*(c + d) - b - e) + f
	strb	r14, [r8], r11

	ldrb    r3, [r7], r9		// f
	ldrb	r14, [r12, r6, asr #4]
	// {r3,r4,r5,r0,r1,r2} = {a,b,c,d,e,f}
	rsb	r6, r5, r0, lsl #2	//        4* c      - b
	add	r6, r6, r1, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r2		//        4*(c + d) - b - e
	add	r4, r4, r3		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r4, r6		// a + 5*(4*(c + d) - b - e) + f
	strb	r14, [r8], r11

	ldrb    r4, [r7], r9		// f
	ldrb	r14, [r12, r6, asr #4]
	// {r3,r4,r5,r0,r1,r2} = {a,b,c,d,e,f}
	rsb	r6, r0, r1, lsl #2	//        4* c      - b
	add	r6, r6, r2, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r3		//        4*(c + d) - b - e
	add	r5, r5, r4		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r5, r6		// a + 5*(4*(c + d) - b - e) + f
	strb	r14, [r8], r11

	ldrb    r5, [r7], r9		// f
	ldrb	r14, [r12, r6, asr #4]
	// {r3,r4,r5,r0,r1,r2} = {a,b,c,d,e,f}
	rsb	r6, r1, r2, lsl #2	//        4* c      - b
	add	r6, r6, r3, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r4		//        4*(c + d) - b - e
	add	r0, r0, r5		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r0, r6		// a + 5*(4*(c + d) - b - e) + f
	ldr	r0, [sp]		// Load step value
	strb	r14, [r8], r11
	ldrb	r14, [r12, r6, asr #4]

	ldrb    r0, [r7], r0		// f
	// {r3,r4,r5,r0,r1,r2} = {a,b,c,d,e,f}
	rsb	r6, r2, r3, lsl #2	//        4* c      - b
	add	r6, r6, r4, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r5		//        4*(c + d) - b - e
	add	r1, r1, r0		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r1, r6		// a + 5*(4*(c + d) - b - e) + f
	ldr	r0, [sp, #4]		// Load step value
	ldrb	r6, [r12, r6, asr #4]

	subs	r10, r10, #1

	strb	r14, [r8], r11
	strb	r6, [r8], r0		// #-(2*BLK_SIZE-1)*MBK_SIZE+1

	bne	L_loop_interp_8_pels

	ldr	lr, [sp, #8]
	add	sp, sp, #12
	bx	lr



/****************************************************************************
 *
 * interpolate_block_1D_no_clip:
 *
 * Parameters:
 *      r7 = frm          Pointer to reference pixels
 *      r8 = predPtr      Pointer for interpolated pixels
 *      r9 = step         Step in filter direction
 *      r10 = stepP       Step in destination buffer
 *      r11 = step2       Backward step in filter direction
 *      r12 = stepP2      Backward step in destination buffer
 *
 * Function:
 *      Interpolate 8x8 block in one dimension.
 *
 *      Uses only registers for passing function parameters. This is not
 *      standard calling convention.
 *
 * Returns:
 *      -
 *
 ****************************************************************************/

LABELDEF(interpolate_block_1D_no_clip)

	str	lr, [sp, #-4]!
	mov	r14, #2*BLK_SIZE+2+3

LABELDEF(loop_interp_8_pels_no_clip)

	ldrb    r0, [r7], r9		// a
	ldrb    r1, [r7], r9		// b
	ldrb    r2, [r7], r9		// c
	ldrb    r3, [r7], r9		// d
	ldrb    r4, [r7], r9 		// e
	ldrb    r5, [r7], r9		// f
	// {r0,r1,r2,r3,r4,r5} = {a,b,c,d,e,f}
	rsb	r6, r1, r2, lsl #2	//        4* c      - b
	add	r6, r6, r3, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r4		//        4*(c + d) - b - e
	add	r0, r0, r5		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r0, r6		// a + 5*(4*(c + d) - b - e) + f
	str     r6, [r8], r10

	ldrb    r0, [r7], r9		// f
	// {r1,r2,r3,r4,r5,r0} = {a,b,c,d,e,f}
	rsb	r6, r2, r3, lsl #2	//        4* c      - b
	add	r6, r6, r4, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r5		//        4*(c + d) - b - e
	add	r1, r1, r0		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r1, r6		// a + 5*(4*(c + d) - b - e) + f
	str     r6, [r8], r10

	ldrb    r1, [r7], r9		// f
	// {r2,r3,r4,r5,r0,r1} = {a,b,c,d,e,f}
	rsb	r6, r3, r4, lsl #2	//        4* c      - b
	add	r6, r6, r5, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r0		//        4*(c + d) - b - e
	add	r2, r2, r1		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r2, r6		// a + 5*(4*(c + d) - b - e) + f
	str     r6, [r8], r10

	ldrb    r2, [r7], r9		// f
	// {r3,r4,r5,r0,r1,r2} = {a,b,c,d,e,f}
	rsb	r6, r4, r5, lsl #2	//        4* c      - b
	add	r6, r6, r0, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r1		//        4*(c + d) - b - e
	add	r3, r3, r2		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r3, r6		// a + 5*(4*(c + d) - b - e) + f
	str     r6, [r8], r10

	ldrb    r3, [r7], r9		// f
	// {r4,r5,r0,r1,r2,r3} = {a,b,c,d,e,f}
	rsb	r6, r5, r0, lsl #2	//        4* c      - b
	add	r6, r6, r1, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r2		//        4*(c + d) - b - e
	add	r4, r4, r3		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r4, r6		// a + 5*(4*(c + d) - b - e) + f
	str     r6, [r8], r10

	ldrb    r4, [r7], r9		// f
	// {r5,r0,r1,r2,r3,r4} = {a,b,c,d,e,f}
	rsb	r6, r0, r1, lsl #2	//        4* c      - b
	add	r6, r6, r2, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r3		//        4*(c + d) - b - e
	add	r5, r5, r4		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r5, r6		// a + 5*(4*(c + d) - b - e) + f
	str     r6, [r8], r10

	ldrb    r5, [r7], r9		// f
	// {r0,r1,r2,r3,r4,r5} = {a,b,c,d,e,f}
	rsb	r6, r1, r2, lsl #2	//        4* c      - b
	add	r6, r6, r3, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r4		//        4*(c + d) - b - e
	add	r0, r0, r5		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r0, r6		// a + 5*(4*(c + d) - b - e) + f
	str     r6, [r8], r10

	subs	r14, r14, #1

	ldrb    r0, [r7], r11		// f
	// {r1,r2,r3,r4,r5,r0} = {a,b,c,d,e,f}
	rsb	r6, r2, r3, lsl #2	//        4* c      - b
	add	r6, r6, r4, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r5		//        4*(c + d) - b - e
	add	r1, r1, r0		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r1, r6		// a + 5*(4*(c + d) - b - e) + f
	str     r6, [r8], r12

	bne	L_loop_interp_8_pels_no_clip

	ldr	lr, [sp], #4
	bx	lr


/****************************************************************************
 *
 * get_ref_area_XxX:
 *
 * Parameters:
 *      r0 = x            Horizontal block position
 *      r1 = y            Vetrtical block position
 *      r3 = h            Block height
 *      r7 = frm          Pointer to frame buffer
 *      r8 = buf          Destination pointer
 *      r9 = picWidth     Picture width
 *      r10 = picHeight   Picture height
 *
 * Function:
 *      Copy 16*h pixel block from reference frame. Handles boundary conditions
 *
 *      Uses only registers for passing function parameters. This is not
 *      standard calling convention.
 *      
 * Returns:
 *      r0 = pointer to reference pixels
 *
 ****************************************************************************/

	GLOBLAB	L_get_ref_area_XxX

LABELDEF(get_ref_area_XxX)

	bic	r4, r1, r1, asr #31	// yc = y < 0 ? 0 : y
	cmp	r4, r10			// compare yc with picHeight
	subge	r4, r10, #1		// if (yc >= picHeight) yc = picHeight - 1
	MLA	r7, r9, r4, r7		// linePtr = frm + yc * picWidth

	cmp	r0, #0
	bge	L_no_left_bound_XxX	// jump if x >= 0

	cmp	r0, #-4			// compare x with -4
	bge	L_left_bound_XxX_minus_4
	cmp	r0, #-8			// compare x with -8
	bge	L_left_bound_XxX_minus_8

	//
	// Copy 4 reference pixels and replicate 12 left edge pixels
	//

	cmp	r0, #-12		// compare x with -12
	movlt	r0, #-12		// if (x < -12) x = -12
	and	r0, r0, #3		// word_offset = x & 3
	add	r0, r0, r8		// retBuf = buf + word_offset
LABELDEF(left_bound_copy_lines_XxX_minus_12)
	ldr	r5, [r7]
	adds	r1, r1, #1		// y++
	and	r4, r5, #255
	cmpgt	r10, r1			// if (y > 0) then compare picHeight with y
	orr	r4, r4, r4, lsl #8
	addgt	r7, r7, r9		// if (y > 0 && picHeight > y) linePtr += picWidth
	orr	r4, r4, r4, lsl #16
	subs	r3, r3, #1		// h--
	str	r4, [r8], #4
	str	r4, [r8], #4
	stmia	r8!, {r4-r5}
	bne	L_left_bound_copy_lines_XxX_minus_12	// until h == 0
	bx	lr			// Return

	//
	// Copy 8 reference pixels and replicate 8 left edge pixels
	//

LABELDEF(left_bound_XxX_minus_8)
	and	r0, r0, #3		// word_offset = x & 3
	add	r0, r0, r8		// retBuf = buf + word_offset
LABELDEF(left_bound_copy_lines_XxX_minus_8)
	ldmia	r7, {r5, r6}
	adds	r1, r1, #1		// y++
	and	r4, r5, #255
	cmpgt	r10, r1			// if (y > 0) then compare picHeight with y
	orr	r4, r4, r4, lsl #8
	addgt	r7, r7, r9		// if (y > 0 && picHeight > y) linePtr += picWidth
	orr	r4, r4, r4, lsl #16
	subs	r3, r3, #1		// h--
	str	r4, [r8], #4
	stmia	r8!, {r4-r6}
	bne	L_left_bound_copy_lines_XxX_minus_8	// until h == 0
	bx	lr			// Return

	//
	// Copy 12 reference pixels and replicate 4 left edge pixels
	//

LABELDEF(left_bound_XxX_minus_4)
	and	r0, r0, #3		// word_offset = x & 3
	add	r0, r0, r8		// retBuf = buf + word_offset
LABELDEF(left_bound_copy_lines_XxX_minus_4)
	ldmia	r7, {r5, r6, r11}
	adds	r1, r1, #1		// y++
	and	r4, r5, #255
	cmpgt	r10, r1			// if (y > 0) then compare picHeight with y
	orr	r4, r4, r4, lsl #8
	addgt	r7, r7, r9		// if (y > 0 && picHeight > y) linePtr += picWidth
	orr	r4, r4, r4, lsl #16
	subs	r3, r3, #1		// h--
	stmia	r8!, {r4-r6, r11}
	bne	L_left_bound_copy_lines_XxX_minus_4	// until h == 0
	bx	lr			// Return


LABELDEF(no_left_bound_XxX)

	subs	r4, r9, r0		// picWidth - x
	suble	r0, r9, #1		// if (x >= picWidth) x = picWidth - 1

	add	r7, r7, r0		// frm += x
	and	r0, r0, #3		// wordOffset = x & 3
	sub	r7, r7, r0		// frm -= wordOffset (align to word boundary)
	add	r0, r0, r8		// retBuf = buf + wordOffset

	cmp	r4, #8					// compare (picWidth - x) with 8
	ble	L_right_bound_XxX_8_or_12		// jump if (picWidth - x) <= 8
	cmp	r4, #12					// compare (picWidth - x) with 12
	ble	L_right_bound_copy_lines_XxX_plus_4	// jump if (picWidth - x) <= 12

	//
	// Copy 16 reference pixels per row
	//

LABELDEF(no_bound_copy_lines_XxX)
	ldmia	r7, {r4-r6, r11}
	adds	r1, r1, #1		// y++
	cmpgt	r10, r1			// if (y > 0) then compare picHeight with y
	addgt	r7, r7, r9		// if (y > 0 && picHeight > y) linePtr += picWidth
	subs	r3, r3, #1		// h--
	stmia	r8!, {r4-r6, r11}
	bne	L_no_bound_copy_lines_XxX	// until h == 0
	bx	lr			// Return

	//
	// Copy 12 reference pixels and replicate 4 right edge pixels
	//

LABELDEF(right_bound_copy_lines_XxX_plus_4)
	ldmia	r7, {r4-r6}
	adds	r1, r1, #1		// y++
	cmpgt	r10, r1			// if (y > 0) then compare picHeight with y
	and	r11, r6, #0xff000000
	addgt	r7, r7, r9		// if (y > 0 && picHeight > y) linePtr += picWidth
	orr	r11, r11, r11, lsr #8
	subs	r3, r3, #1		// h--
	orr	r11, r11, r11, lsr #16
	stmia	r8!, {r4-r6, r11}
	bne	L_right_bound_copy_lines_XxX_plus_4	// until h == 0
	bx	lr			// Return


LABELDEF(right_bound_XxX_8_or_12)
	cmp	r4, #4					// compare (picWidth - x) with 4
	ble	L_right_bound_copy_lines_XxX_plus_12	// jump if (picWidth - x) <= 4

	//
	// Copy 8 reference pixels and replicate 8 right edge pixels
	//

LABELDEF(right_bound_copy_lines_XxX_plus_8)
	ldmia	r7, {r4-r5}
	adds	r1, r1, #1		// y++
	cmpgt	r10, r1			// if (y > 0) then compare picHeight with y
	and	r6, r5, #0xff000000
	addgt	r7, r7, r9		// if (y > 0 && picHeight > y) linePtr += picWidth
	orr	r6, r6, r6, lsr #8
	subs	r3, r3, #1		// h--
	orr	r6, r6, r6, lsr #16
	stmia	r8!, {r4-r6}
	str	r6, [r8], #4
	bne	L_right_bound_copy_lines_XxX_plus_8	// until h == 0
	bx	lr			// Return

	//
	// Copy 4 reference pixels and replicate 12 right edge pixels
	//

LABELDEF(right_bound_copy_lines_XxX_plus_12)
	ldr	r5, [r7]
	adds	r1, r1, #1		// y++
	cmpgt	r10, r1			// if (y > 0) then compare picHeight with y
	and	r6, r5, #0xff000000
	addgt	r7, r7, r9		// if (y > 0 && picHeight > y) linePtr += picWidth
	orr	r6, r6, r6, lsr #8
	subs	r3, r3, #1		// h--
	orr	r6, r6, r6, lsr #16
	stmia	r8!, {r5-r6}
	str	r6, [r8], #4
	str	r6, [r8], #4
	bne	L_right_bound_copy_lines_XxX_plus_12	// until h == 0
	bx	lr			// Return



/****************************************************************************
 *
 * get_ref_area_C_5x5:
 *
 * Parameters:
 *      r0 = x            Horizontal block position
 *      r1 = y            Vetrtical block position
 *      r6 = frmV         Pointer to V frame buffer
 *      r7 = frmU         Pointer to U frame buffer
 *      r8 = buf          Destination pointer
 *      r9 = picWidthC    Picture width in chroma samples
 *      r10 = picHeightC  Picture height in chroma samples
 *
 * Function:
 *      Copy 5*5 block of chroma samples from both chrominance reference frames. 
 *      Check for picture boundary conditions. Note that 8*5 pixels are actually
 *      copied.
 *
 *      Uses only registers for passing function parameters. This is not
 *      standard calling convention.
 *      
 * Returns:
 *      r0 = offset for the block in destination buffer
 *
 ****************************************************************************/

	GLOBLAB	L_get_ref_area_C_5x5

LABELDEF(get_ref_area_C_5x5)

	// free registers:
	// r2
	// r3
	// r4
	// r5
	// r11
	// r12

	MUL	r1, r9, r1		// lineOffs = picWidthC * y
	MUL	r10, r9, r10		// lineOffsMax = picWidthC * picHeightC
	add	r11, r8, #5*8

	mov	r2, #5			// i = 5

	cmp	r0, #0			// compare x with 0
	bge	L_no_left_bound_C	// jump if x >= 0

	//
	// x < 0 -> replicate left edge pixels
	//

	adds	r0, r0, #4		// x = x - (-4)  =>  x = x + 4
	movmi	r0, #0			// offs = x < 0 ? 0 : x
LABELDEF(left_bound_copy_lines_c)
	bic	r4, r1, r1, asr #31	// lineOffs2 = lineOffs < 0 ? 0 : lineOffs
	cmp	r4, r10			// compare lineOffs2 with lineOffsMax
	subge	r4, r10, r9		// if (lineOffs2 >= lineOffsMax) lineOffs2 = lineOffsMax - picWidthC
	ldr	r5, [r7, r4]		// pixU = frmU[lineOffs2]
	add	r1, r1, r9		// lineOffs += picWidthC
	strb	r5, [r8], #1
	strb	r5, [r8], #1
	strb	r5, [r8], #1
	strb	r5, [r8], #1
	str	r5, [r8], #4
	ldr	r5, [r6, r4]		// pixV = frmV[lineOffs2]
	subs	r2, r2, #1		// i--
	strb	r5, [r11], #1
	strb	r5, [r11], #1
	strb	r5, [r11], #1
	strb	r5, [r11], #1
	str	r5, [r11], #4
	bne	L_left_bound_copy_lines_c	// until i == 0
	bx	lr

LABELDEF(no_left_bound_C)

	add	r4, r0, #4		// x2 = x + 4
	cmp	r4, r9			// compare x + 4 with picWidthC
	bge	L_right_bound_C		// jump if x + 4 >= picWidthC

	//
	// x+4 < picWidth -> copy middle pixel
	//

	add	r7, r7, r0		// frmU += x
	add	r6, r6, r0		// frmV += x
	and	r0, r0, #3		// offs
	sub	r7, r7, r0		// frmU -= offs  (align at word boundary)
	sub	r6, r6, r0		// frmV -= offs  (align at word boundary)
LABELDEF(no_bound_copy_lines_c)
	bic	r4, r1, r1, asr #31	// lineOffs2 = lineOffs < 0 ? 0 : lineOffs
	cmp	r4, r10			// compare lineOffs2 with lineOffsMax
	subge	r4, r10, r9		// if (lineOffs2 >= lineOffsMax) lineOffs2 = lineOffsMax - picWidthC
	add	r3, r7, r4		// linePtr = frmU + lineOffs2
	ldmia	r3, {r5, r12}
	add	r1, r1, r9		// lineOffs += picWidthC
	stmia	r8!, {r5, r12}
	add	r3, r6, r4		// linePtr = frmV + lineOffs2
	ldmia	r3, {r5, r12}
	subs	r2, r2, #1		// i--
	stmia	r11!, {r5, r12}
	bne	L_no_bound_copy_lines_c	// until i == 0
	bx	lr

LABELDEF(right_bound_C)

	//
	// x+4 >= picWidth -> replicate right edge pixels
	//

	sub	r4, r9, #4		// picWidthC - 4
	add	r7, r7, r4		// frmU += picWidthC - 4
	add	r6, r6, r4		// frmV += picWidthC - 4
	sub	r0, r0, r4		// offs = x - (picWidthC - 4)
	cmp	r0, #3			// if offs > 3
	movgt	r0, #3			// then offs = 3
LABELDEF(right_bound_copy_lines_c)
	bic	r4, r1, r1, asr #31	// lineOffs2 = lineOffs < 0 ? 0 : lineOffs
	cmp	r4, r10			// compare lineOffs2 with lineOffsMax
	subge	r4, r10, r9		// if (lineOffs2 >= lineOffsMax) lineOffs2 = lineOffsMax - picWidthC
	ldr	r5, [r7, r4]		// pixU = frmU[lineOffs2]
	add	r1, r1, r9		// lineOffs += picWidthC
	and	r12, r5, #0xff000000
	orr	r12, r12, r12, lsr #8
	orr	r12, r12, r12, lsr #16
	stmia	r8!, {r5, r12}
	ldr	r5, [r6, r4]		// pixU = frmV[lineOffs2]
	subs	r2, r2, #1		// i--
	and	r12, r5, #0xff000000
	orr	r12, r12, r12, lsr #8
	orr	r12, r12, r12, lsr #16
	stmia	r11!, {r5, r12}
	bne	L_right_bound_copy_lines_c	// until i == 0
	bx	lr




	ENDP



	ENDFILE
