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
 * mcpCopyMacroblock:
 *
 * Parameters:
 *      reco                  Reconstruction frame
 *      ref                   Reference frame
 *      pixX                  Horizontal pixel position
 *      pixY                  Vertical pixel position
 *      picWidth              Frame width in pixels
 *
 * Function:
 *      Copy macroblock data to reconstruction frame from
 *      co-located macroblock ín reference frame.
 *      
 * Returns:
 *      -
 *
 ****************************************************************************/

/*
 * void mcpCopyMacroblock(frmBuf_s *reco, frmBuf_s *ref,
 *                        int pixX, int pixY, int picWidth)
 * {
 */

	ALIGNW
#if defined(COMPILER_ADS)
	GLOBLAB	mcpCopyMacroblock
mcpCopyMacroblock PROC
#elif defined(COMPILER_GCC)
	GLOBLAB	mcpCopyMacroblock
mcpCopyMacroblock:
#elif defined(COMPILER_CCS)
	GLOBLAB	_mcpCopyMacroblock
_mcpCopyMacroblock
#endif

  /*
   * u_int8 *recoPtr;
   * u_int8 *refPtr;
   * int c, i, j;
   * int refWidth = picWidth + 2*IMG_PAD_SIZE;
   */

	stmfd	sp!, {r4-r10}			// save 7 regs

	// r0 = reco
	// r1 = ref
	// r2 = pixX
	// r3 = pixY
	ldr	r4, [sp, #7*4]			// picWidth (after 7 saved regs)
	add	r5, r4, #2*IMG_PAD_SIZE		// refWidth

  /*
   * recoPtr = &reco->y[pixY*picWidth+pixX];
   * refPtr = &ref->y[(pixY+IMG_PAD_SIZE)*refWidth+pixX+IMG_PAD_SIZE];
   */

	ldr	r6, [r0]			// reco->y
	ldr	r7, [r1]			// ref->y
	add	r8, r3, #IMG_PAD_SIZE		// pixY+IMG_PAD_SIZE
	MLA	r9, r3, r4, r2			// idxRec = pixY*picWidth + pixX
	MLA	r10, r8, r5, r2			// idxRef = (pixY+IMG_PAD_SIZE)*refWidth + pixX
	add	r6, r6, r9			// reco->y + idxRec
	add	r10, r10, #IMG_PAD_SIZE		// idxRef += IMG_PAD_SIZE
	add	r7, r7, r10			// ref->y + idxRef

  /*
   * for (j = 0; j < MBK_SIZE; j++, recoPtr+=picWidth, refPtr+=refWidth) {
   *   for (i = 0; i < MBK_SIZE; i+=4) {
   *     recoPtr[i+0] = refPtr[i+0];
   *     recoPtr[i+1] = refPtr[i+1];
   *     recoPtr[i+2] = refPtr[i+2];
   *     recoPtr[i+3] = refPtr[i+3];
   *   }
   * }
   */

	sub	r4, r4, #16-4			// picWidth - 12
	sub	r5, r5, #16-4			// refWidth - 12
	mov	r8, #MBK_SIZE			// 16 lines
LABELDEF(loop_copy_mb_lines_y)
	ldmia	r7!, {r9-r10}
	stmia	r6!, {r9-r10}
	ldr	r9, [r7], #4
	ldr	r10, [r7], r5
	str	r9, [r6], #4
	str	r10, [r6], r4
	subs	r8, r8, #1
	bne	L_loop_copy_mb_lines_y

	add	r4, r4, #16-4			// restore picWidth
	add	r5, r5, #16-4			// restore refWidth

  /*
   * picWidth >>= 1;
   * refWidth >>= 1;
   * pixX >>= 1;
   * pixY >>= 1;
   */

	mov	r4, r4, lsr #1			// picWidth>>1
	mov	r5, r5, lsr #1			// refWidth>>1
	mov	r2, r2, lsr #1			// pixX>>1
	mov	r3, r3, lsr #1			// pixY>>1

  /*
   * recoPtr = &reco->u[pixY*picWidth+pixX];
   * refPtr = &ref->u[(pixY+IMG_PAD_SIZE/2)*refWidth+pixX+IMG_PAD_SIZE/2];
   */

	ldr	r6, [r0, #4]			// reco->u
	ldr	r7, [r1, #4]			// ref->u
	ldr	r0, [r0, #8]			// reco->v
	ldr	r1, [r1, #8]			// ref->v
	add	r8, r3, #IMG_PAD_SIZE/2		// pixY+IMG_PAD_SIZE/2
	MLA	r9, r3, r4, r2			// idxRec = pixX + pixY*picWidth
	MLA	r10, r8, r5, r2			// idxRef = pixX + (pixY+IMG_PAD_SIZE/2)*refWidth
	add	r6, r6, r9			// reco->u + idxRec
	add	r0, r0, r9			// reco->v + idxRec
	add	r10, r10, #IMG_PAD_SIZE/2	// idxRef += IMG_PAD_SIZE/2
	add	r7, r7, r10			// ref->u + idxRef
	add	r1, r1, r10			// ref->u + idxRef

	sub	r4, r4, #8-4			// picWidth - 4
	sub	r5, r5, #8-4			// refWidth - 4
	mov	r8, #MBK_SIZE/2			// 8 lines
LABELDEF(loop_copy_mb_lines_c)
	ldr	r9, [r7], #4
	ldr	r10, [r7], r5
	str	r9, [r6], #4
	str	r10, [r6], r4
	ldr	r9, [r1], #4
	ldr	r10, [r1], r5
	str	r9, [r0], #4
	str	r10, [r0], r4
	subs	r8, r8, #1
	bne	L_loop_copy_mb_lines_c
/*
 * }
 */
	ldmfd	sp!, {r4-r10}			// restore 7 regs
	bx	lr				// return


	ENDP


/****************************************************************************
 *
 * mcpGetPred4x4:
 *
 * Parameters:
 *      predY                 Return pointer for predicted luma pixels
 *      predC                 Return pointer for predicted chroma pixels
 *      blkX0                 Sub-macroblock horizontal location
 *      blkY0                 Sub-macroblock vertical location
 *      ref                   Reference frame buffer
 *      picWidth              Frame buffer width in pixels
 *      picHeight             Frame buffer height in pixels
 *      motVecs               Motion vector buffer
 *
 * Function:
 *      Get motion compensated prediction for 4x4 blokcs within 8x8 sub-macroblock.
 *
 * Returns:
 *      -
 *
 ****************************************************************************/

/*
 * void mcpGetPred4x4(u_int8 predY[MBK_SIZE][MBK_SIZE],
 *                    u_int8 predC[MBK_SIZE/2][MBK_SIZE],
 *                    int blkX0, int blkY0, frmBuf_s *ref, int picWidth,
 *                    int picHeight, motVec_s *motVecs)
 * {
 */

	ALIGNW
#if defined(COMPILER_ADS)
	GLOBLAB	mcpGetPred4x4
mcpGetPred4x4 PROC
#elif defined(COMPILER_GCC)
	GLOBLAB	mcpGetPred4x4
mcpGetPred4x4:
#elif defined(COMPILER_CCS)
	GLOBLAB	_mcpGetPred4x4
_mcpGetPred4x4
#endif

  /*
   * int blksPerLine;
   * int blkX, blkY;
   * int blkIdxX, blkIdxY;
   * int i, j;
   * u_int8 *refPtr;
   * int xPos, yPos, xInt, yInt, xFrac, yFrac;
   * int coef0, coef1, coef2, coef3;
   * int c;
   * int tmp;
   * int refWidth, refHeight, refWidthC, refHeightC;
   * int block[BLK_SIZE+2+3][BLK_SIZE];
   * int lineIdx, colIdx;
   * u_int8 *refC[2];
   * u_int8 (* predPtr)[MBK_SIZE];
   */

#define LOC_BASE       0
#define LOC_SIZE       376
#define REG_BASE       LOC_SIZE
#define NUM_SAVED_REGS 10
#define ARG_BASE       LOC_SIZE+4*NUM_SAVED_REGS

#define BLKS_PER_LINE  LOC_BASE+0
#define BLK_X          LOC_BASE+4
#define BLK_Y          LOC_BASE+8
#define BLK_IDX_X      LOC_BASE+12
#define BLK_IDX_Y      LOC_BASE+16
#define REF_PTR        LOC_BASE+20
#define X_POS          LOC_BASE+24
#define Y_POS          LOC_BASE+28
#define X_INT          LOC_BASE+32
#define Y_INT          LOC_BASE+36
#define X_FRAC         LOC_BASE+40
#define Y_FRAC         LOC_BASE+44
#define REF_WIDTH      LOC_BASE+48
#define REF_HEIGHT     LOC_BASE+52
#define PIC_WIDTH_C    LOC_BASE+56
#define PIC_HEIGHT_C   LOC_BASE+60
#define BLOCK          LOC_BASE+64		// 144 bytes (9*4*4)
#define REF_FRM        LOC_BASE+208
#define PRED_PTR       LOC_BASE+212

#define PRED_Y         LOC_BASE+216
#define PRED_C         LOC_BASE+220
#define BLK_X_0        LOC_BASE+224
#define BLK_Y_0        LOC_BASE+228
#define REF_AREA       LOC_BASE+232		// 144 bytes (9*16)


#define REF            ARG_BASE+0
#define PIC_WIDTH      ARG_BASE+4
#define PIC_HEIGHT     ARG_BASE+8
#define MOT_VECS       ARG_BASE+12
#define CLIP_BUF       ARG_BASE+16


	stmfd	sp!, {r4-r12, lr}		// save 10 regs
	sub	sp, sp, #LOC_SIZE		// alloc space for local variables

	str	r0, [sp, #PRED_Y]
	str	r1, [sp, #PRED_C]
	str	r2, [sp, #BLK_X_0]
	str	r3, [sp, #BLK_Y_0]

  /*
   * blksPerLine = picWidth/BLK_SIZE;
   * picWidthC = picWidth/2;
   * picHeightC = picHeight/2;
   */

	ldr	r2, [sp, #PIC_WIDTH]
	ldr	r3, [sp, #PIC_HEIGHT]
	mov	r4, r2, lsr #2			// blksPerLine = picWidth/4
	str	r4, [sp, #BLKS_PER_LINE]
	mov	r2, r2, lsr #1			// picWidth/2
	str	r2, [sp, #PIC_WIDTH_C]
	mov	r3, r3, lsr #1			// picHeight/2
	str	r3, [sp, #PIC_HEIGHT_C]

  /*
   * for (blkIdxY = 0; blkIdxY < BLK_PER_MB; blkIdxY++) {
   */

	mov	r0, #0
	str	r0, [sp, #BLK_IDX_Y]

LABELDEF(loop_interp_main_y)

    /*
     * for (blkIdxX = 0; blkIdxX < BLK_PER_MB; blkIdxX++) {
     */

	mov	r0, #0
	str	r0, [sp, #BLK_IDX_X]

LABELDEF(loop_interp_main_x)

      /*
       * blkX = blkX0 + blkIdxX;
       * blkY = blkY0 + blkIdxY;
       */

	ldr	r0, [sp, #BLK_X_0]
	ldr	r2, [sp, #BLK_IDX_X]
	ldr	r1, [sp, #BLK_Y_0]
	ldr	r3, [sp, #BLK_IDX_Y]
	add	r0, r2, r0			// blkX
	add	r1, r3, r1			// blkY

      /*
       * // Absolute coordinates of the prediction block
       * xPos = blkX*BLK_SIZE*4 + motVecs[blkIdxX].x;
       * yPos = blkY*BLK_SIZE*4 + motVecs[blkIdxX].y;
       * predPtr = (u_int8 (*)[MBK_SIZE])&predY[blkIdxY*BLK_SIZE][blkIdxX*BLK_SIZE];
       */

	ldr	r5, [sp, #MOT_VECS]
	ldr	r6, [sp, #PRED_Y]
	add	r5, r5, r2, lsl #2		// &motVecs[blkIdxX]
	ldrsh	r7, [r5]			// vec x
	ldrsh	r8, [r5, #2]			// vec y
	add	r2, r2, r3, lsl #4		// blkIdxY*MBK_SIZE + blkIdxX
	add	r6, r6, r2, lsl #2		// &predY[blkIdxY*BLK_SIZE][blkIdxX*BLK_SIZE]
	str	r6, [sp, #PRED_PTR]
	add	r0, r7, r0, lsl #4		// xPos = blkX*BLK_SIZE*4 + vec x
	add	r1, r8, r1, lsl #4		// yPos = blkY*BLK_SIZE*4 + vec y
	str	r0, [sp, #X_POS]
	str	r1, [sp, #Y_POS]

	ldr	r6, [sp, #REF]			// Reference frame

	ldr	r9, [sp, #PIC_WIDTH]
	ldr	r10, [sp, #PIC_HEIGHT]

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
         * if (xInt >= 0 && xInt <= picWidth-BLK_SIZE &&
         *     yInt >= 0 && yInt <= picHeight-BLK_SIZE)
         * {
         *   refPtr += yInt*picWidth + xInt;
         *   refWidth = picWidth;
         * }
         * else {
         *   getRefArea(refPtr, refArea, picWidth, picHeight, xInt, yInt, BLK_SIZE, BLK_SIZE);
         *   refPtr = refArea;
         *   refWidth = BLK_SIZE;
         * }
         */

	sub	r4, r9, #BLK_SIZE		// picWidth - BLK_SIZE
	sub	r5, r10, #BLK_SIZE		// picHeight - BLK_SIZE
	cmp	r0, r4				// if (unsigned int)xInt <= (picWidth - BLK_SIZE) and
	cmpls	r1, r5				// if (unsigned int)yInt <= (picHeight - BLK_SIZE)
	bls	L_interp_copy_no_bound_checks	// then no bound checks

        // note: this code corresponds to the 'else' block in c code
	add	r8, sp, #REF_AREA
	mov	r3, #BLK_SIZE
	bl	L_get_ref_area_4xX
	str	r0, [sp, #REF_PTR]		// refPtr
	mov	r2, #8
	str	r2, [sp, #REF_WIDTH]		// refWidth = 8
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
         * }
         */

	ldr	r7, [sp, #REF_PTR]
	ldr	r9, [sp, #REF_WIDTH]
	ldr	r8, [sp, #PRED_PTR]
#if ARM_ARCH_VERSION < ARM_ARCH_V6
	sub	r11, r9, #BLK_SIZE-1		// refWidth - (BLK_SIZE-1)
	mov	r10, #BLK_SIZE
LABELDEF(loop_copy)
	ldrb	r0, [r7], #1
	ldrb	r1, [r7], #1
	ldrb	r2, [r7], #1
	ldrb	r3, [r7], r11
	strb	r0, [r8], #1
	strb	r1, [r8], #1
	strb	r2, [r8], #1
	strb	r3, [r8], #1+(MBK_SIZE-BLK_SIZE)
	subs	r10, r10, #1
	bne	L_loop_copy
#else
	// ARMv6 supports unaligned 32-bit loads
	ldr	r0, [r7], r9
	ldr	r1, [r7], r9
	ldr	r2, [r7], r9
	ldr	r3, [r7], r9
	str	r0, [r8], #MBK_SIZE
	str	r1, [r8], #MBK_SIZE
	str	r2, [r8], #MBK_SIZE
	str	r3, [r8], #MBK_SIZE
#endif

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
         * if (xInt >= 0 && xInt <= picWidth-BLK_SIZE &&
         *     yInt >= 2 && yInt <= picHeight-BLK_SIZE-3)
         * {
         *   refPtr += yInt*picWidth + xInt;
         *   refWidth = picWidth;
         * }
         * else {
         *   getRefArea(refPtr, refArea, picWidth, picHeight, xInt, yInt-2, BLK_SIZE, BLK_SIZE+2+3);
         *   refPtr = refArea + 2*BLK_SIZE;
         *   refWidth = BLK_SIZE;
         * }
         */

	sub	r4, r9, #BLK_SIZE		// picWidth - BLK_SIZE
	sub	r3, r1, #2			// yInt - 2
	sub	r5, r10, #BLK_SIZE+3+2		// picHeight - (BLK_SIZE+2+3)
	cmp	r0, r4				// if (unsigned int)xInt <= (picWidth - BLK_SIZE) and
	cmpls	r3, r5				// if (unsigned int)yInt-2 <= (picHeight - (BLK_SIZE+2+3)
	bls	L_interp_hf_vs_no_bound_checks	// then no bound checks

        // note: this code corresponds to the 'else' block in c code
	add	r8, sp, #REF_AREA
	sub	r1, r1, #2			// y = yInt - 2
	mov	r3, #BLK_SIZE+2+3		// area height
	bl	L_get_ref_area_4xX
	add	r0, r0, #2*8
	str	r0, [sp, #REF_PTR]		// refPtr = refArea + 2*BLK_SIZE
	mov	r2, #8
	str	r2, [sp, #REF_WIDTH]		// refWidth = 8
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
         * for (j = 0; j < BLK_SIZE;  j++) {
         *   for (i = 0; i < BLK_SIZE;  i++) {
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
	mov	r11, r9, lsl #3		// 8*refWidth
	rsb	r11, r11, #1		// -8*refWidth + 1
	mov	r10, #BLK_SIZE
LABELDEF(loop_hf_vs_or_hs_vf)
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
	strb	r14, [r8], #MBK_SIZE

	ldrb    r1, [r7], r9		// f
	ldrb	r14, [r12, r6, asr #4]
	// {r2,r3,r4,r5,r0,r1} = {a,b,c,d,e,f}
	rsb	r6, r3, r4, lsl #2	//        4* c      - b
	add	r6, r6, r5, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r0		//        4*(c + d) - b - e
	add	r2, r2, r1		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r2, r6		// a + 5*(4*(c + d) - b - e) + f
	strb	r14, [r8], #MBK_SIZE

	ldrb    r2, [r7], r11		// f
	ldrb	r14, [r12, r6, asr #4]
	// {r3,r4,r5,r0,r1,r2} = {a,b,c,d,e,f}
	rsb	r6, r4, r5, lsl #2	//        4* c      - b
	add	r6, r6, r0, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r1		//        4*(c + d) - b - e
	add	r3, r3, r2		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r3, r6		// a + 5*(4*(c + d) - b - e) + f
	ldrb	r6, [r12, r6, asr #4]

	strb	r14, [r8], #MBK_SIZE
	subs	r10, r10, #1
	strb	r6, [r8], #-(BLK_SIZE-1)*MBK_SIZE+1

	bne	L_loop_hf_vs_or_hs_vf

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
         *   for (j = 0; j < BLK_SIZE;  j++) {
         *     for (i = 0; i < BLK_SIZE;  i++) {
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
	sub	r11, r9, #BLK_SIZE-1	// refWidth - (BLK_SIZE-1)
	mov	r10, #BLK_SIZE
LABELDEF(loop_linear)
	// Linear interpolation of four pixels in parallel
	ldrb	r0, [r7], #1		// refpix0
	ldrb	r1, [r7], #1		// refpix1
	ldrb	r2, [r7], #1		// refpix2
	ldrb	r3, [r7], r11		// refpix3
	subs	r10, r10, #1		// j--
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
	str	r0, [r8], #MBK_SIZE
	bne	L_loop_linear
#else
	// 1st and 2nd lines
	ldr	r0, [r7], r9		// refpix = four reference pixels
	ldr	r1, [r8]		// predpix = four predicted pixel values
	ldr	r5, [r7], r9		// refpix = four reference pixels
	ldr	r6, [r8, #MBK_SIZE]	// predpix = four predicted pixel values
	eor	r2, r0, r1		// roundval = refpix ^ predpix
	bic	r2, r2, r4, ror #7	// roundval = roundval & 0x01010101
	eor	r3, r5, r6		// roundval = refpix ^ predpix
	bic	r3, r3, r4, ror #7	// roundval = roundval & 0x01010101
	uhadd8	r0, r0, r1		// finalpix = (refpix + predpix) >> 1
	uhadd8	r5, r5, r6		// finalpix = (refpix + predpix) >> 1
	add	r0, r0, r2		// finalpix = finalpix + roundval
	add	r5, r5, r3		// finalpix = finalpix + roundval
	str	r0, [r8], #MBK_SIZE
	str	r5, [r8], #MBK_SIZE
	// 3rd and 4nd lines
	ldr	r0, [r7], r9		// refpix = four reference pixels
	ldr	r1, [r8]		// predpix = four predicted pixel values
	ldr	r5, [r7], r9		// refpix = four reference pixels
	ldr	r6, [r8, #MBK_SIZE]	// predpix = four predicted pixel values
	eor	r2, r0, r1		// roundval = refpix ^ predpix
	bic	r2, r2, r4, ror #7	// roundval = roundval & 0x01010101
	eor	r3, r5, r6		// roundval = refpix ^ predpix
	bic	r3, r3, r4, ror #7	// roundval = roundval & 0x01010101
	uhadd8	r0, r0, r1		// finalpix = (refpix + predpix) >> 1
	uhadd8	r5, r5, r6		// finalpix = (refpix + predpix) >> 1
	add	r0, r0, r2		// finalpix = finalpix + roundval
	add	r5, r5, r3		// finalpix = finalpix + roundval
	str	r0, [r8], #MBK_SIZE
	str	r5, [r8], #MBK_SIZE
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
         * if (xInt >  1 && xInt <  picWidth-BLK_SIZE-2 &&
         *     yInt >= 0 && yInt <= picHeight-BLK_SIZE)
         * {
         *   refPtr += yInt*picWidth + xInt;
         *   refWidth = picWidth;
         * }
         * else {
         *   getRefArea(refPtr, refArea, picWidth, picHeight, xInt-2, yInt, BLK_SIZE+2+3, BLK_SIZE);
         *   refPtr = refArea + 2;
         *   refWidth = BLK_SIZE+2+3;
         * }
         */

	sub	r2, r0, #2			// xInt - 2
	sub	r4, r9, #BLK_SIZE+2+3		// picWidth - BLK_SIZE+2+3
	sub	r5, r10, #BLK_SIZE		// picHeight - BLK_SIZE
	cmp	r2, r4				// if (unsigned int)xInt-2 <= (picWidth - (BLK_SIZE+2+3)) and
	cmpls	r1, r5				// if (unsigned int)yInt <= (picHeight - BLK_SIZE)
	bls	L_interp_hs_vf_no_bound_checks	// then no bound checks

        // note: this code corresponds to the 'else' block in c code
	add	r8, sp, #REF_AREA
	sub	r0, r0, #2			// xInt - 2
	mov	r3, #BLK_SIZE			// area height
	bl	L_get_ref_area_9xX
	add	r0, r0, #2
	str	r0, [sp, #REF_PTR]
	mov	r2, #16
	str	r2, [sp, #REF_WIDTH]		// refWidth = 16
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
         * for (j = 0; j < BLK_SIZE;  j++) {
         *   for (i = 0; i < BLK_SIZE;  i++) {
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
	ldr	r11, [sp, #REF_WIDTH]
	ldr	r8, [sp, #PRED_PTR]
	ldr	r12, L_clipBufPtr
	sub	r7, r7, #2		// refPtr - 2
	sub	r11, r11, #8		// refWidth - 8
	mov	r10, #BLK_SIZE
LABELDEF(loop_hs_vf)
	ldrb    r0, [r7], #1		// a
	ldrb    r1, [r7], #1		// b
	ldrb    r2, [r7], #1		// c
	ldrb    r3, [r7], #1		// d
	ldrb    r4, [r7], #1 		// e
	ldrb    r5, [r7], #1		// f
	// {r0,r1,r2,r3,r4,r5} = {a,b,c,d,e,f}
	rsb	r6, r1, r2, lsl #2	//        4* c      - b
	add	r6, r6, r3, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r4		//        4*(c + d) - b - e
	add	r0, r0, r5		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r0, r6		// a + 5*(4*(c + d) - b - e) + f

	ldrb    r0, [r7], #1		// f
	ldrb	r14, [r12, r6, asr #4]
	// {r1,r2,r3,r4,r5,r0} = {a,b,c,d,e,f}
	rsb	r6, r2, r3, lsl #2	//        4* c      - b
	add	r6, r6, r4, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r5		//        4*(c + d) - b - e
	add	r1, r1, r0		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r1, r6		// a + 5*(4*(c + d) - b - e) + f
	strb	r14, [r8], #1

	ldrb    r1, [r7], #1		// f
	ldrb	r14, [r12, r6, asr #4]
	// {r2,r3,r4,r5,r0,r1} = {a,b,c,d,e,f}
	rsb	r6, r3, r4, lsl #2	//        4* c      - b
	add	r6, r6, r5, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r0		//        4*(c + d) - b - e
	add	r2, r2, r1		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r2, r6		// a + 5*(4*(c + d) - b - e) + f
	strb	r14, [r8], #1

	ldrb    r2, [r7], r11		// f
	ldrb	r14, [r12, r6, asr #4]
	// {r3,r4,r5,r0,r1,r2} = {a,b,c,d,e,f}
	rsb	r6, r4, r5, lsl #2	//        4* c      - b
	add	r6, r6, r0, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r1		//        4*(c + d) - b - e
	add	r3, r3, r2		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r3, r6		// a + 5*(4*(c + d) - b - e) + f
	ldrb	r6, [r12, r6, asr #4]

	strb	r14, [r8], #1
	subs	r10, r10, #1
	strb	r6, [r8], #1+(MBK_SIZE-BLK_SIZE)

	bne	L_loop_hs_vf

        /*
         * // Linear interp.
         * if ((xFrac&1) != 0) {
         *   colIdx = xFrac >> 1;
         *   for (j = 0; j < BLK_SIZE;  j++) {
         *     for (i = 0; i < BLK_SIZE;  i++) {
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
       *   if (xInt > 1 && xInt <  picWidth-BLK_SIZE-2 &&
       *       yInt > 1 && yInt <  picHeight-BLK_SIZE-2)
       *   {
       *     refPtr += yInt*picWidth + xInt;
       *     refWidth = picWidth;
       *   }
       *   else {
       *     getRefArea(refPtr, refArea, picWidth, picHeight, xInt-2, yInt-2, BLK_SIZE+2+3, BLK_SIZE+2+3);
       *     refPtr = refArea + 2*(BLK_SIZE+2+3) + 2;
       *     refWidth = BLK_SIZE+2+3;
       *   }
       */

	sub	r4, r0, #2			// xInt - 2
	sub	r5, r9, #BLK_SIZE+2+3		// picWidth - (BLK_SIZE+2+3)
	sub	r6, r1, #2			// yInt - 2
	sub	r8, r10, #BLK_SIZE+2+3		// picHeight - (BLK_SIZE+2+3)
	cmp	r4, r5				// if (unsigned int)xInt-2 <= (picWidth - (BLK_SIZE+2+3)) and
	cmpls	r6, r8				// if (unsigned int)yInt-2 <= (picHeight - (BLK_SIZE+2+3))
	bls	L_interp_hh_vs_no_bound_checks	// then no bound checks

        // note: this code corresponds to the 'else' block in c code
	add	r8, sp, #REF_AREA
	sub	r0, r0, #2			// xInt - 2
	sub	r1, r1, #2			// yInt - 2
	mov	r3, #BLK_SIZE+2+3		// area height
	bl	L_get_ref_area_9xX
	add	r0, r0, #2*16+2
	str	r0, [sp, #REF_PTR]		// refPtr = refArea + 2*16 + 2
	mov	r2, #16
	str	r2, [sp, #REF_WIDTH]		// refWidth = 16
	ldr	r2, [sp, #X_POS]
	ldr	r3, [sp, #Y_POS]
	and	r2, r2, #3			// xFrac = xPos&3
	and	r3, r3, #3			// yFrac = yPos&3
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
           * for (j = -2; j < BLK_SIZE+3;  j++) {
           *   for (i = 0; i < BLK_SIZE;  i++) {
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

	ldr	r7, [sp, #REF_PTR]
	ldr	r11, [sp, #REF_WIDTH]
	add	r8, sp, #BLOCK
	sub	r7, r7, r11, lsl #1	// refPtr - 2*refWidth
	sub	r7, r7, #2		// - 2
	sub	r11, r11, #8		// refWidth - 8
	mov	r10, #BLK_SIZE+2+3
LABELDEF(loop_hh_vs_horiz)
	ldrb    r0, [r7], #1		// a
	ldrb    r1, [r7], #1		// b
	ldrb    r2, [r7], #1		// c
	ldrb    r3, [r7], #1		// d
	ldrb    r4, [r7], #1 		// e
	ldrb    r5, [r7], #1		// f
	// {r0,r1,r2,r3,r4,r5} = {a,b,c,d,e,f}
	rsb	r6, r1, r2, lsl #2	//        4* c      - b
	add	r6, r6, r3, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r4		//        4*(c + d) - b - e
	add	r0, r0, r5		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r0, r6		// a + 5*(4*(c + d) - b - e) + f
	str     r6, [r8], #4

	ldrb    r0, [r7], #1		// f
	// {r1,r2,r3,r4,r5,r0} = {a,b,c,d,e,f}
	rsb	r6, r2, r3, lsl #2	//        4* c      - b
	add	r6, r6, r4, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r5		//        4*(c + d) - b - e
	add	r1, r1, r0		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r1, r6		// a + 5*(4*(c + d) - b - e) + f
	str     r6, [r8], #4

	ldrb    r1, [r7], #1		// f
	// {r2,r3,r4,r5,r0,r1} = {a,b,c,d,e,f}
	rsb	r6, r3, r4, lsl #2	//        4* c      - b
	add	r6, r6, r5, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r0		//        4*(c + d) - b - e
	add	r2, r2, r1		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r2, r6		// a + 5*(4*(c + d) - b - e) + f
	str     r6, [r8], #4

	ldrb    r2, [r7], r11		// f
	// {r3,r4,r5,r0,r1,r2} = {a,b,c,d,e,f}
	rsb	r6, r4, r5, lsl #2	//        4* c      - b
	add	r6, r6, r0, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r1		//        4*(c + d) - b - e
	add	r3, r3, r2		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r3, r6		// a + 5*(4*(c + d) - b - e) + f
	str     r6, [r8], #4

	subs	r10, r10, #1
	bne	L_loop_hh_vs_horiz

          /*
           * // Vertical interpolation
           * for (j = 0; j < BLK_SIZE;  j++) {
           *   for (i = 0; i < BLK_SIZE;  i++) {
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
	mov	r10, #BLK_SIZE
LABELDEF(loop_hh_vs_vert)
	ldr	r0, [r7], #BLK_SIZE*4	// a
	ldr	r1, [r7], #BLK_SIZE*4	// b
	ldr	r2, [r7], #BLK_SIZE*4	// c
	ldr	r3, [r7], #BLK_SIZE*4	// d
	ldr	r4, [r7], #BLK_SIZE*4	// e
	ldr	r5, [r7], #BLK_SIZE*4	// f
	// {r0,r1,r2,r3,r4,r5} = {a,b,c,d,e,f}
	rsb	r6, r1, r2, lsl #2	//        4* c      - b
	add	r6, r6, r3, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r4		//        4*(c + d) - b - e
	add	r0, r0, r5		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r0, r6		// a + 5*(4*(c + d) - b - e) + f

	ldr	r0, [r7], #BLK_SIZE*4	// f
	ldrb	r14, [r12, r6, asr #9]
	// {r1,r2,r3,r4,r5,r0} = {a,b,c,d,e,f}
	rsb	r6, r2, r3, lsl #2	//        4* c      - b
	add	r6, r6, r4, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r5		//        4*(c + d) - b - e
	add	r1, r1, r0		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r1, r6		// a + 5*(4*(c + d) - b - e) + f
	strb	r14, [r8], #MBK_SIZE

	ldr	r1, [r7], #BLK_SIZE*4	// f
	ldrb	r14, [r12, r6, asr #9]
	// {r2,r3,r4,r5,r0,r1} = {a,b,c,d,e,f}
	rsb	r6, r3, r4, lsl #2	//        4* c      - b
	add	r6, r6, r5, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r0		//        4*(c + d) - b - e
	add	r2, r2, r1		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r2, r6		// a + 5*(4*(c + d) - b - e) + f
	strb	r14, [r8], #MBK_SIZE

	ldr	r2, [r7], #-8*(BLK_SIZE*4)+4	// f
	ldrb	r14, [r12, r6, asr #9]
	// {r3,r4,r5,r0,r1,r2} = {a,b,c,d,e,f}
	rsb	r6, r4, r5, lsl #2	//        4* c      - b
	add	r6, r6, r0, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r1		//        4*(c + d) - b - e
	add	r3, r3, r2		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r3, r6		// a + 5*(4*(c + d) - b - e) + f
	ldrb	r6, [r12, r6, asr #9]

	strb	r14, [r8], #MBK_SIZE
	subs	r10, r10, #1
	strb	r6, [r8], #-((BLK_SIZE-1)*MBK_SIZE)+1

	bne	L_loop_hh_vs_vert

	ldr	r1, [sp, #Y_FRAC]
	tst	r1, #1
	beq	L_interp_chroma


          /*
           * // Linear interp.
           * if ((yFrac&1) != 0) {
           *   lineIdx = 2 + (yFrac >> 1);
           *   for (j = 0; j < BLK_SIZE;  j++) {
           *     for (i = 0; i < BLK_SIZE;  i++) {
           *       tmp = (block[lineIdx+j][i] + 16) >> 5;
           *       predPtr[j][i] = (u_int8) ((predPtr[j][i] + clip(0,255,tmp) + 1) >> 1);
           *     }
           *   }
           * }
           */

	add	r7, sp, #BLOCK+2*BLK_SIZE*4
	ldr	r8, [sp, #PRED_PTR]
	ldr	r12, L_clipBufPtr
	cmp	r1, #3			// if yFrac == 3, use lower half-pel
	addeq	r7, r7, #BLK_SIZE*4
	mov	r10, #BLK_SIZE
	ldr	r4, L_0x7f7f7f7f
LABELDEF(loop_linear_hh_vs)
	// Linear interpolation of four pixels in parallel
	ldmia	r7!, {r0-r3}		// refpix0, refpix1, refpix2, refpix3
	ldrb	r0, [r12, r0, asr #4]	// rounded, normalized and clipped refpix0
	ldrb	r1, [r12, r1, asr #4]	// rounded, normalized and clipped refpix1
	ldrb	r2, [r12, r2, asr #4]	// rounded, normalized and clipped refpix2
	ldrb	r3, [r12, r3, asr #4]	// rounded, normalized and clipped refpix3
	subs	r10, r10, #1		// j--
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
	eor	r0, r0, r1		// roundval = refpix ^ predpix
	bic	r0, r0, r4, ror #7	// roundval = roundval & 0x01010101
#endif
	add	r0, r0, r2		// finalpix = finalpix + roundval
	str	r0, [r8], #MBK_SIZE
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
           * for (i = -2; i < BLK_SIZE+3; i++) {
           *   for (j = 0; j < BLK_SIZE; j++) {
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

	ldr	r7, [sp, #REF_PTR]
	ldr	r9, [sp, #REF_WIDTH]
	add	r8, sp, #BLOCK
	sub	r7, r7, r9, lsl #1	// refPtr - 2*refWidth
	sub	r7, r7, #2		// - 2
	mov	r11, r9, lsl #3		// 8*refWidth
	rsb	r11, r11, #1		// -8*refWidth + 1
	mov	r10, #BLK_SIZE+2+3
LABELDEF(loop_vh_hq_vert)
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
	str     r6, [r8], #(BLK_SIZE+2+3)*4

	ldrb    r0, [r7], r9		// f
	// {r1,r2,r3,r4,r5,r0} = {a,b,c,d,e,f}
	rsb	r6, r2, r3, lsl #2	//        4* c      - b
	add	r6, r6, r4, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r5		//        4*(c + d) - b - e
	add	r1, r1, r0		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r1, r6		// a + 5*(4*(c + d) - b - e) + f
	str     r6, [r8], #(BLK_SIZE+2+3)*4

	ldrb    r1, [r7], r9		// f
	// {r2,r3,r4,r5,r0,r1} = {a,b,c,d,e,f}
	rsb	r6, r3, r4, lsl #2	//        4* c      - b
	add	r6, r6, r5, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r0		//        4*(c + d) - b - e
	add	r2, r2, r1		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r2, r6		// a + 5*(4*(c + d) - b - e) + f
	str     r6, [r8], #(BLK_SIZE+2+3)*4

	ldrb    r2, [r7], r11		// f
	// {r3,r4,r5,r0,r1,r2} = {a,b,c,d,e,f}
	rsb	r6, r4, r5, lsl #2	//        4* c      - b
	add	r6, r6, r0, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r1		//        4*(c + d) - b - e
	add	r3, r3, r2		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r3, r6		// a + 5*(4*(c + d) - b - e) + f
	str     r6, [r8], #-3*(BLK_SIZE+2+3)*4+4

	subs	r10, r10, #1
	bne	L_loop_vh_hq_vert

          /*
           * // Horizontal interpolation
           * for (i = 0; i < BLK_SIZE;  i++) {
           *   for (j = 0; j < BLK_SIZE;  j++) {
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
           * for (i = 0; i < BLK_SIZE;  i++) {
           *   for (j = 0; j < BLK_SIZE;  j++) {
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
	mov	r10, #BLK_SIZE
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
	ldr	r14, [r9], #6*4

	ldr	r2, [r7], #4		// f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r3, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r2		// a + 5*(4*(c + d) - b - e) + f

	ldrb	r14, [r12, r14, asr #4]
	ldrb	r3, [r12, r6, asr #9]

	subs	r10, r10, #1

	add	r14, r14, #1
	add	r14, r14, r3
	mov	r14, r14, lsr #1
	strb	r14, [r8], #1+(MBK_SIZE-BLK_SIZE)
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
	ldr	r14, [r9], #6*4

	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r3, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r2		// a + 5*(4*(c + d) - b - e) + f

	ldrb	r14, [r12, r14, asr #4]
	ldrb	r3, [r12, r6, asr #9]

	subs	r10, r10, #1

	add	r14, r14, #1
	uhadd16	r14, r14, r3
	strb	r14, [r8], #1+(MBK_SIZE-BLK_SIZE)
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
           * for (j = 0; j < BLK_SIZE; j++) {
           *   for (i = 0; i < BLK_SIZE; i++) {
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

	ldr	r0, [sp, #X_FRAC]
	ldr	r7, [sp, #REF_PTR]
	ldr	r9, [sp, #REF_WIDTH]
	ldr	r8, [sp, #PRED_PTR]
	ldr	r12, L_clipBufPtr
	sub	r7, r7, r9, lsl #1	// refPtr - 2*refWidth
	add	r7, r7, r0, lsr #1
	mov	r11, r9, lsl #3		// 8*refWidth
	rsb	r11, r11, #1		// -8*refWidth + 1
	mov	r10, #BLK_SIZE
LABELDEF(loop_diag_vert)
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
	strb	r14, [r8], #MBK_SIZE

	ldrb    r1, [r7], r9		// f
	ldrb	r14, [r12, r6, asr #4]
	// {r2,r3,r4,r5,r0,r1} = {a,b,c,d,e,f}
	rsb	r6, r3, r4, lsl #2	//        4* c      - b
	add	r6, r6, r5, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r0		//        4*(c + d) - b - e
	add	r2, r2, r1		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r2, r6		// a + 5*(4*(c + d) - b - e) + f
	strb	r14, [r8], #MBK_SIZE

	ldrb    r2, [r7], r11		// f
	ldrb	r14, [r12, r6, asr #4]
	// {r3,r4,r5,r0,r1,r2} = {a,b,c,d,e,f}
	rsb	r6, r4, r5, lsl #2	//        4* c      - b
	add	r6, r6, r0, lsl #2	//        4*(c + d) - b
	sub	r6, r6, r1		//        4*(c + d) - b - e
	add	r3, r3, r2		// a                         + f
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r3, r6		// a + 5*(4*(c + d) - b - e) + f
	ldrb	r6, [r12, r6, asr #4]

	strb	r14, [r8], #MBK_SIZE
	subs	r10, r10, #1
	strb	r6, [r8], #-(BLK_SIZE-1)*MBK_SIZE+1

	bne	L_loop_diag_vert

          /*
           * // Horizontal interpolation
           * lineIdx = yFrac >> 1;
           * for (j = 0; j < BLK_SIZE; j++) {
           *   for (i = 0; i < BLK_SIZE; i++) {
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
	sub	r11, r11, #8		// refWidth - 8
	mov	r10, #BLK_SIZE
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
	ldrb    r2, [r7], r11		// f
	sub     r6, r6, r1		//        4*(c + d) - b - e
	add     r6, r6, r6, lsl #2	//     5*(4*(c + d) - b - e)
	add	r6, r3, r6		// a + 5*(4*(c + d) - b - e)
	add	r6, r6, r2		// a + 5*(4*(c + d) - b - e) + f
	ldrb	r3, [r12, r6, asr #4]

	// Linear interpolation of four pixels in parallel
	ldr	r1, [r8]		// predpix = four predicted pixel values
	subs	r10, r10, #1		// j--
	orr	r0, r14, r3, lsl #24	// refpix = refpix  | (refpix3<<24)
#if ARM_ARCH_VERSION < ARM_ARCH_V6
	orr	r2, r0, r1		// roundval = refpix | predpix
	bic	r2, r2, r9, ror #7	// roundval = roundval & 0x01010101
	and	r0, r9, r0, lsr #1	// refpix  = 0x7f7f7f7f & (refpix >>1)
	and	r1, r9, r1, lsr #1	// predpix = 0x7f7f7f7f & (predpix>>1)
	add	r0, r0, r1		// finalpix = refpix + predpix
#else
	uhadd8	r2, r0, r1		// finalpix = refpix + predpix
	eor	r0, r0, r1		// roundval = refpix ^ predpix
	bic	r0, r0, r9, ror #7	// roundval = roundval & 0x01010101
#endif
	add	r0, r0, r2		// finalpix = finalpix + roundval
	str	r0, [r8], #MBK_SIZE

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
	ldr	r7, [r6, #4]			// refFrm->u
	ldr	r6, [r6, #8]			// refFrm->v

      /*
       * if (xInt >= 0 && xInt < picWidthC-BLK_SIZE/2 &&
       *     yInt >= 0 && yInt < picHeightC-BLK_SIZE/2)
       * {
       *   refC[0] = &ref->u[yInt*picWidthC+xInt];
       *   refC[1] = &ref->v[yInt*picWidthC+xInt];
       *   refWidth = picWidthC;
       * }
       * else {
       *   getRefAreaC(ref->u, refArea    , picWidthC, picHeightC, xInt, yInt);
       *   getRefAreaC(ref->v, refArea+3*3, picWidthC, picHeightC, xInt, yInt);
       *   refC[0] = refArea;
       *   refC[1] = refArea+3*3;
       *   refWidth = 3;
       * }
       */

	sub	r4, r9, #BLK_SIZE/2
	sub	r5, r10, #BLK_SIZE/2
	cmp	r0, r4				// if (unsigned)xInt >= (picWidthC-2) and
	cmplo	r1, r5				// if (unsigned)yInt < (picHeightC-2)
	blo	L_interp_chroma_no_bound_checks	// then no bound checks

        // note: this code corresponds to the 'else' block in c code
	add	r8, sp, #REF_AREA
	bl	L_get_ref_area_C
	ldr	r0, [sp, #X_POS]
	ldr	r1, [sp, #Y_POS]
	and	r2, r0, #7			// xFrac = xPos&7
	and	r3, r1, #7			// yFrac = yPos&7
	add	r7, sp, #REF_AREA		// refC[0] = refArea
	add	r6, sp, #REF_AREA+3*3		// refC[1] = refArea+3*3
	mov	r9, #3-2			// refWidthC = 3
	b	L_interp_chroma_cont

LABELDEF(interp_chroma_no_bound_checks)
        // note: this code corresponds to the 'if' block in c code
	MLA	r0, r9, r1, r0			// refWidthC*yInt + xInt
	sub	r9, r9, #2			// refWidthC - 2
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

	ldr	r0, [sp, #BLK_IDX_X]
	ldr	r1, [sp, #BLK_IDX_Y]
	ldr	r8, [sp, #PRED_C]
	add	r2, r0, r1, lsl #4		// blkIdxY*MBK_SIZE+blkIdxX
	add	r8, r8, r2, lsl #1		// &predC[blkIdxY*(BLK_SIZE/2)+j][blkIdxX*(BLK_SIZE/2)+i]


      /*
       * for (c = 0; c < 2; c++) {
       *   for (j = 0; j < BLK_SIZE/2;  j++) {
       *     for (i = 0; i < BLK_SIZE/2;  i++) {
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
LABELDEF(loop_chroma)
	// a b c
	// d e f
	// g h i
#if ARM_ARCH_VERSION < ARM_ARCH_V6
	ldrb	r0, [r7], #1			// a
	ldrb	r1, [r7], #1			// b
	ldrb	r3, [r7], r9			// c
	ldrb	r2, [r7], #1			// d
	MUL	r0, COEF0, r0 			// p0  = coef0 * a
	MLA	r0, r1, COEF1, r0		// p0 += coef1 * b
	MUL	r1, COEF0, r1			// p1  = coef0 * b
	MLA	r1, r3, COEF1, r1		// p1 += coef1 * c
	ldrb	r3, [r7], #1			// e
	MLA	r0, r2, COEF2, r0		// p0 += coef2 * d
	MLA	r0, r3, COEF3, r0		// p0 += coef3 * e
	MLA	r1, r3, COEF2, r1		// p1 += coef2 * e
	add	r0, r0, #32			// rounding constant
	mov	r0, r0, lsr #6			// normalize
	strb	r0, [r8], #1			// store p0 and move to next pixel
	ldrb	r0, [r7], r9			// f
	MUL	r2, COEF0, r2			// p2  = coef0 * d
	MLA	r2, r3, COEF1, r2		// p2 += coef1 * e
	MLA	r1, r0, COEF3, r1		// p1 += coef3 * f
	MUL	r3, COEF0, r3			// p3  = coef0 * e
	MLA	r3, r0, COEF1, r3		// p3 += coef1 * f
	ldrb	r0, [r7], #1			// g
	add	r1, r1, #32			// rounding constant
	mov	r1, r1, lsr #6			// normalize
	strb	r1, [r8], #-1+16		// store p1 and move to first pixel of next line
	ldrb	r1, [r7], #1			// h
	MLA	r2, r0, COEF2, r2		// p2 += coef2 * g
	ldrb	r0, [r7]			// i
	MLA	r2, r1, COEF3, r2		// p2 += coef3 * h
	MLA	r3, r1, COEF2, r3		// p3 += coef2 * h
	MLA	r3, r0, COEF3, r3		// p3 += coef3 * i
	add	r2, r2, #32			// rounding constant
	mov	r2, r2, lsr #6			// normalize
	strb	r2, [r8], #1			// store p2
	add	r3, r3, #32			// rounding constant
	mov	r3, r3, lsr #6			// normalize
	strb	r3, [r8], #-1-16+8		// store p3 and move to first pixel of V block
#else
	// This version uses ARMv6 SIMD instructions
	ldrb	r0, [r7], #1			// a
	ldrb	r1, [r7], #1			// b
	ldrb	r2, [r7], r9			// c
	ldrb	r3, [r7], #1			// d
	ldrb	r4, [r7], #1			// e
	ldrb	r12, [r7], r9			// f
	orr	r0, r1, r0, lsl #16
	orr	r1, r2, r1, lsl #16
	smuadx	r0, COEF0, r0
	smuadx	r1, COEF0, r1
	orr	r3, r4, r3, lsl #16
	orr	r4, r12, r4, lsl #16
	smladx	r0, COEF1, r3, r0
	smladx	r1, COEF1, r4, r1
	ldrb	r2, [r7], #1			// g
	ldrb	r12, [r7], #1			// h
	ldrb	r14, [r7], r9			// i
	smuadx	r3, COEF0, r3
	smuadx	r4, COEF0, r4
	orr	r2, r12, r2, lsl #16
	orr	r12, r14, r12, lsl #16
	smladx	r3, COEF1, r2, r3
	smladx	r4, COEF1, r12, r4
	add	r0, r0, #32
	add	r1, r1, #32
	mov	r0, r0, lsr #6
	mov	r1, r1, lsr #6
	strb	r0, [r8], #1			// store p0 and move to next pixel
	strb	r1, [r8], #-1+16		// store p1 and move to first pixel of next line
	add	r3, r3, #32
	add	r4, r4, #32
	mov	r3, r3, lsr #6
	mov	r4, r4, lsr #6
	strb	r3, [r8], #1			// store p2
	strb	r4, [r8], #-1-16+8		// store p3 and move to first pixel of V block
#endif

	mov	r7, r6
	subs	r5, r5, #1
	bne	L_loop_chroma

    /*
     * }
     */

	ldr	r0, [sp, #BLK_IDX_X]
	add	r0, r0, #1
	str	r0, [sp, #BLK_IDX_X]
	cmp	r0, #2
	blt	L_loop_interp_main_x

  /*
   * }
   */

	ldr	r0, [sp, #BLK_IDX_Y]
	ldr	r1, [sp, #MOT_VECS]
	ldr	r2, [sp, #BLKS_PER_LINE]
	add	r0, r0, #1
	str	r0, [sp, #BLK_IDX_Y]
	cmp	r0, #2
	add	r1, r1, r2, lsl #2		// motVecs += blksPerLine
	str	r1, [sp, #MOT_VECS]
	blt	L_loop_interp_main_y

/*
 * }
 */
	add	sp, sp, #LOC_SIZE		// free stack space
	ldmfd	sp!, {r4-r12, lr}		// restore 10 regs
	bx	lr				// return



/****************************************************************************
 *
 * get_ref_area_4xX:
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
 *      Copy 4*h pixel block from reference frame. Check for
 *      any picture boundary crossings.
 *
 *      Destination width will be 8.
 *
 *      Uses registers to pass parameters. Does not use stack.
 *      
 * Returns:
 *      r0 - pointer to refArea
 *
 ****************************************************************************/

	GLOBLAB	L_get_ref_area_4xX

LABELDEF(get_ref_area_4xX)

	bic	r4, r1, r1, asr #31	// yc = y < 0 ? 0 : y
	cmp	r4, r10			// compare yc with picHeight
	subge	r4, r10, #1		// if (yc >= picHeight) yc = picHeight - 1
	MLA	r7, r9, r4, r7		// linePtr = frm + yc * picWidth

	cmp	r0, #0
	bge	L_no_left_bound_4xX	// jump if x >= 0

	//
	// x < 0  ->  replicate left edge pixels
	//

	cmp	r0, #-3			// compare x with -3
	movlt	r0, #-3			// if (x < -3) x = -3
	and	r0, r0, #3		// word_offset = x & 3
	add	r0, r0, r8		// retBuf = buf + word_offset
	add	r8, r8, #1		// buf++

LABELDEF(left_bound_copy_lines_4xX)

	ldr	r6, [r7]

	adds	r1, r1, #1		// y++
	cmpgt	r10, r1			// if (yc > 0) then compare picHeight with yc
	addgt	r7, r7, r9		// if (yc > 0 && picHeight > yc) linePtr += picWidth
	subs	r3, r3, #1		// h--

	strb	r6, [r8], #1
	strb	r6, [r8], #1
	strb	r6, [r8], #1
	str	r6, [r8], #5

	bne	L_left_bound_copy_lines_4xX	// until h == 0

	bx	lr			// Return

LABELDEF(no_left_bound_4xX)

	add	r4, r0, #4		// x + 4
	cmp	r4, r9			// compare x + 4 with picWidth
	bgt	L_right_bound_4xX	// jump if x + 4 > picWidth

	//
	// x + 4 <= picWidth  ->  copy middle pixel
	//

	add	r7, r7, r0		// frm += x
	bic	r7, r7, #3		// frm &= 0xfffffffc
	and	r0, r0, #3		// word_offset = x & 3

	subeq	r7, r7, #4		// if (x + 4 == picWidth) frm -= 4
	addeq	r0, r0, #4		// if (x + 4 == picWidth) word_offset += 4

	add	r0, r0, r8		// retBuf = buf + word_offset

LABELDEF(no_bound_copy_lines_4xX)

	ldmia	r7, {r5, r6}

	adds	r1, r1, #1		// y++
	cmpgt	r10, r1			// if (yc > 0) then compare picHeight with yc
	addgt	r7, r7, r9		// if (yc > 0 && picHeight > yc) linePtr += picWidth
	subs	r3, r3, #1		// h--

	stmia	r8!, {r5, r6}

	bne	L_no_bound_copy_lines_4xX	// until h == 0

	bx	lr			// Return

LABELDEF(right_bound_4xX)

	//
	// x+4 > picWidth -> replicate right edge pixels
	//

	cmp	r0, r9			// compare x with picWidth
	subge	r0, r9, #1		// if (x >= picWidth) x = picWidth - 1

	add	r7, r7, r9		// frm += picWidth
	and	r0, r0, #3		// wordOffset = x & 3
	add	r0, r0, r8		// retBuf = buf + wordOffset

LABELDEF(right_bound_copy_lines_4xX)

	ldr	r5, [r7, #-4]

	adds	r1, r1, #1		// y++
	cmpgt	r10, r1			// if (yc > 0) then compare picHeight with yc
	and	r6, r5, #0xff000000
	addgt	r7, r7, r9		// if (yc > 0 && picHeight > yc) linePtr += picWidth
	orr	r6, r6, r6, lsr #8
	subs	r3, r3, #1		// h--
	orr	r6, r6, r6, lsr #16

	stmia	r8!, {r5, r6}

	bne	L_right_bound_copy_lines_4xX	// until h == 0

	bx	lr			// Return



/****************************************************************************
 *
 * get_ref_area_9xX:
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
 *      Copy 9*h pixel block from reference frame. Check for
 *      any picture boundary crossings.
 *
 *      Destination width will be 16.
 *
 *      Uses registers to pass parameters. Does not use stack.
 *      
 * Returns:
 *      r0 - pointer to refArea
 *
 ****************************************************************************/

	GLOBLAB	L_get_ref_area_9xX

LABELDEF(get_ref_area_9xX)

	bic	r4, r1, r1, asr #31	// yc = y < 0 ? 0 : y
	cmp	r4, r10			// compare yc with picHeight
	subge	r4, r10, #1		// if (yc >= picHeight) yc = picHeight - 1
	MLA	r7, r9, r4, r7		// linePtr = frm + yc * picWidth

	cmp	r0, #0
	bge	L_no_left_bound_9xX	// jump if x >= 0

	//
	// x < 0  ->  replicate left edge pixels
	//

	cmp	r0, #-8			// compare x with -8
	movlt	r0, #-8			// if (x < -8) x = -8
	and	r0, r0, #7		// word_offset = x & 7
	add	r0, r0, r8		// retBuf = buf + word_offset

LABELDEF(left_bound_copy_lines_9xX)

	ldmia	r7, {r5, r6}
	adds	r1, r1, #1		// y++
	and	r4, r5, #255
	cmpgt	r10, r1			// if (yc > 0) then compare picHeight with yc
	orr	r4, r4, r4, lsl #8
	addgt	r7, r7, r9		// if (yc > 0 && picHeight > yc) linePtr += picWidth
	orr	r4, r4, r4, lsl #16
	subs	r3, r3, #1		// h--
	str	r4, [r8], #4
	stmia	r8!, {r4-r6}

	bne	L_left_bound_copy_lines_9xX	// until h == 0

	bx	lr			// Return

LABELDEF(no_left_bound_9xX)

	add	r4, r0, #9		// x + 9
	cmp	r4, r9			// compare x + 9 with picWidth
	bgt	L_right_bound_9xX	// jump if x + 9 > picWidth

	//
	// x + 9 <= picWidth  ->  copy middle pixel
	//

	add	r7, r7, r0		// frm += x
	and	r0, r0, #3		// word_offset = x & 3
	sub	r7, r7, r0		// frm -= word_offset
	add	r0, r0, r8		// retBuf = buf + word_offset

LABELDEF(no_bound_copy_lines_9xX)

	ldmia	r7, {r4-r6}
	adds	r1, r1, #1		// y++
	cmpgt	r10, r1			// if (yc > 0) then compare picHeight with yc
	addgt	r7, r7, r9		// if (yc > 0 && picHeight > yc) linePtr += picWidth
	subs	r3, r3, #1		// h--
	stmia	r8!, {r4, r5}
	str	r6, [r8], #8

	bne	L_no_bound_copy_lines_9xX	// until h == 0

	bx	lr			// Return

LABELDEF(right_bound_9xX)

	//
	// x + 9 > picWidth  ->  replicate right edge pixels
	//

	cmp	r0, r9			// compare x with picWidth
	subge	r0, r9, #1		// if (x >= picWidth) x = picWidth - 1

	add	r7, r7, r9		// frm += picWidth
	and	r0, r0, #7		// wordOffset = x & 7
	add	r0, r0, r8		// retBuf = buf + wordOffset

LABELDEF(right_bound_copy_lines_9xX)

	ldr	r4, [r7, #-8]
	ldr	r5, [r7, #-4]
	adds	r1, r1, #1		// y++
	cmpgt	r10, r1			// if (yc > 0) then compare picHeight with yc
	and	r6, r5, #0xff000000
	addgt	r7, r7, r9		// if (yc > 0 && picHeight > yc) linePtr += picWidth
	orr	r6, r6, r6, lsr #8
	subs	r3, r3, #1		// h--
	orr	r6, r6, r6, lsr #16
	stmia	r8!, {r4-r6}
	str	r6, [r8], #4

	bne	L_right_bound_copy_lines_9xX	// until h == 0

	bx	lr			// Return




/****************************************************************************
 *
 * get_ref_area_C:
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
 *      Copy w*h sized block of chroma samples from reference frame. Check for
 *      any picture boundary crossings.
 *
 *      Uses registers to pass parameters. Does not use stack.
 *      
 * Returns:
 *      -
 *
 ****************************************************************************/

	GLOBLAB	L_get_ref_area_C

LABELDEF(get_ref_area_C)

	// free regs:
	// r2
	// r3
	// r4
	// r5
	// r11
	// r12

	MUL	r1, r9, r1		// lineOffs = picWidthC * y
	MUL	r10, r9, r10		// lineOffsMax = picWidthC * picHeightC

	mov	r2, #3			// i = 3

	cmn	r0, #1			// compare x with -1
	bgt	L_no_left_bound_C	// jump if x > -1

	//
	// x < 0 -> replicate left edge pixels
	//

	movlt	r0, #0			// if (x <  -1) inc = 0
	movge	r0, #1			// if (x >= -1) inc = 1

LABELDEF(left_bound_copy_lines_c)

	bic	r4, r1, r1, asr #31	// lineOffs2 = lineOffs < 0 ? 0 : lineOffs
	cmp	r4, r10			// compare lineOffs2 with lineOffsMax
	subge	r4, r10, r9		// if (lineOffs2 >= lineOffsMax) lineOffs2 = lineOffsMax - picWidthC
	add	r3, r7, r4		// linePtr = frpU + lineOffs2
	ldrb	r5, [r3], r0		// pixU1 = *linePtr, linePtr += inc
	ldrb	r11, [r3]		// pixU2 = *linePtr
	add	r3, r6, r4		// linePtr = frpV + lineOffs2
	strb	r5, [r8], #1		// *buf++ = pixU1
	ldrb	r12, [r3], r0		// pixV1 = *linePtr, linePtr += inc
	strb	r5, [r8], #1		// *buf++ = pixU1
	ldrb	r5, [r3]		// pixV2 = *linePtr
	strb	r11, [r8], #1		// *buf++ = pixU2
	strb	r12, [r8, #6]		// buf[6] = pixV1
	strb	r12, [r8, #7]		// buf[7] = pixV1
	strb	r5, [r8, #8]		// buf[8] = pixV2
	add	r1, r1, r9		// lineOffs += picWidthC
	subs	r2, r2, #1		// i--
	bne	L_left_bound_copy_lines_c	// until i == 0

	bx	lr

LABELDEF(no_left_bound_C)

	add	r4, r0, #2		// x2 = x + 2
	cmp	r4, r9			// compare x + 2 with picWidthC
	bge	L_right_bound_C		// jump if x + 2 >= picWidthC

	//
	// x+2 < picWidth -> copy middle pixel
	//

	add	r7, r7, r0		// frmU += x
	add	r6, r6, r0		// frmV += x

LABELDEF(no_bound_copy_lines_c)

	bic	r4, r1, r1, asr #31	// lineOffs2 = lineOffs < 0 ? 0 : lineOffs
	cmp	r4, r10			// compare lineOffs2 with lineOffsMax
	subge	r4, r10, r9		// if (lineOffs2 >= lineOffsMax) lineOffs2 = lineOffsMax - picWidthC
	add	r3, r7, r4		// linePtr = frpU + lineOffs2
	ldrb	r5, [r3], #1		// pixU1 = *linePtr++
	ldrb	r11, [r3], #1		// pixU2 = *linePtr++
	ldrb	r12, [r3], #1		// pixU3 = *linePtr++
	add	r3, r6, r4		// linePtr = frpV + lineOffs2
	strb	r5, [r8], #1		// *buf++ = pixU1
	strb	r11, [r8], #1		// *buf++ = pixU2
	strb	r12, [r8], #1		// *buf++ = pixU3
	ldrb	r5, [r3], #1		// pixV1 = *linePtr++
	ldrb	r11, [r3], #1		// pixV2 = *linePtr++
	ldrb	r12, [r3], #1		// pixV3 = *linePtr++
	add	r1, r1, r9		// lineOffs += picWidthC
	strb	r5, [r8, #6]		// *buf++ = pixU1
	strb	r11, [r8, #7]		// *buf++ = pixU2
	strb	r12, [r8, #8]		// *buf++ = pixU3
	subs	r2, r2, #1		// i--
	bne	L_no_bound_copy_lines_c	// until i == 0

	bx	lr

LABELDEF(right_bound_C)

	//
	// x+2 >= picWidth -> replicate right edge pixels
	//

	movle	r0, #1			// if (x+2 <= picWidthC) inc = 1
	movgt	r0, #0			// if (x+2 >  picWidthC) inc = 0

	sub	r4, r9, #1		// picWidthC - 1
	sub	r4, r4, r0		// picWidthC - 1 - inc
	add	r7, r7, r4		// frmU += picWidthC - 1 - inc
	add	r6, r6, r4		// frmV += picWidthC - 1 - inc

LABELDEF(right_bound_copy_lines_c)

	bic	r4, r1, r1, asr #31	// lineOffs2 = lineOffs < 0 ? 0 : lineOffs
	cmp	r4, r10			// compare lineOffs2 with lineOffsMax
	subge	r4, r10, r9		// if (lineOffs2 >= lineOffsMax) lineOffs2 = lineOffsMax - picWidthC
	add	r3, r7, r4		// linePtr = frpU + lineOffs2
	ldrb	r5, [r3], r0		// pixU1 = *linePtr, linePtr += inc
	ldrb	r11, [r3]		// pixU2 = *linePtr
	add	r3, r6, r4		// linePtr = frpV + lineOffs2
	strb	r5, [r8], #1		// *buf++ = pixU1
	ldrb	r12, [r3], r0		// pixV1 = *linePtr, linePtr += inc
	ldrb	r5, [r3]		// pixV2 = *linePtr
	strb	r11, [r8], #1		// *buf++ = pixU2
	strb	r11, [r8], #1		// *buf++ = pixU2
	strb	r12, [r8, #6]		// buf[6] = pixV1
	strb	r5, [r8, #7]		// buf[7] = pixV2
	strb	r5, [r8, #8]		// buf[8] = pixV2
	add	r1, r1, r9		// lineOffs += picWidthC
	subs	r2, r2, #1		// i--
	bne	L_right_bound_copy_lines_c	// until i == 0

	bx	lr



LABELDEF(clipBufPtr)
	DEFW	clip8Buf+512

LABELDEF(0x7f7f7f7f)
	DEFW	0x7f7f7f7f


	ENDP



	ENDFILE
