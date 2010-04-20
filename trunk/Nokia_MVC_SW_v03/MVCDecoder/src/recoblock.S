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


#if ARM_ARCH_VERSION > ARM_ARCH_V5
#define MUL   smulbb
#define MULEQ smulbbeq
#define MULNE smulbbne
#else
#define MUL   mul
#define MULEQ muleq
#define MULNE mulne
#endif


	CODE32
	CODESEC

/*
 *
 * pedRecoBlock:
 *
 * Parameters:
 *      pred                  Predicted pixels for a block
 *      coef                  Transformed&quantized coefficients for a block
 *      reco                  Reconstructed pixels
 *      recoWidth             Width of reco. buffer in pixels
 *      isDc                  Does block have separate DC coefficient
 *      dcValue               DC coefficient
 *      qp                    Quantization parameter
 *
 * Function:
 *      Dequantize and inverse transform coefficients and add result
 *      with prediction.
 *
 * Returns:
 *      -
 */

/*
 * void pedRecoBlock(u_int8 pred[BLK_SIZE][MBK_SIZE],
 *                   int coef[BLK_SIZE][BLK_SIZE],
 *                   u_int8 *reco, int recoWidth,
 *                   int isDc, int dcValue, int qp)
 * {
 */

	ALIGNW
#if defined(COMPILER_ADS)
	GLOBLAB	pedRecoBlock
pedRecoBlock PROC
#elif defined(COMPILER_GCC)
	GLOBLAB	pedRecoBlock
pedRecoBlock:
#elif defined(COMPILER_CCS)
	GLOBLAB	_pedRecoBlock
_pedRecoBlock
#endif

#define LOC_BASE       0
#define LOC_SIZE       64
#define REG_BASE       LOC_SIZE
#define NUM_SAVED_REGS 8
#define ARG_BASE       LOC_SIZE+4*NUM_SAVED_REGS

#define TMP_BLK        LOC_BASE+0

#define IS_DC          ARG_BASE+0
#define DC_VALUE       ARG_BASE+4
#define QP             ARG_BASE+8

	stmfd	sp!, {r4-r11}			// save 8 regs
	sub	sp, sp, #LOC_SIZE		// alloc space for local variables


	//
	// Dequantization and horizontal inverse transform
	//

	ldr	r6, [sp, #QP]			// qp
	ldr	r12, L_deq_tab_ptr		// deq_tab
	add	r4, r6, r6, lsl #1		// qp/6 = (qp*43)>>8 = (qp + qp*2 + qp*8 + qp*32) >> 8
	add	r4, r4, r6, lsl #3		// ...
	add	r4, r4, r6, lsl #5		// ...
	mov	r4, r4, lsr #8			// ...
	add	r7, r4, r4, lsl #1		// (qp/6)*3
	sub	r6, r6, r7, lsl #1		// qp%6 = qp - (qp/6)*3*2
	add	r12, r12, r6, lsl #3		// &deq_tab[8*(qp%6)]

	ldr	r6, [sp, #IS_DC]		// load isDc flag
	mov	r5, #4				// loop counter
	add	r11, sp, #TMP_BLK		// temp block for transformed coefs
	cmp	r6, #1				// test isDc against 1  (z-flag = (isDc == 1) ? 1 : 0)
	ldr	r6, [sp, #DC_VALUE]		// A = dcValue

LABELDEF(loop_idct_horiz)
	ldrb	r9, [r12], #1			// dequantCoef0
	ldrb	r10, [r12], #1			// dequantCoef1
	ldr	r7, [r1], #8			// load A
	ldr	r8, [r1], #-4			// load C
	mov	r9, r9, lsl r4			// dequantCoef0 <<= (qp/6)
	MULNE	r6, r9, r7			// if (isDc != 1) A = A * dequantCoef0 (this overwrites A only if z-flag == 0)
	ldr	r7, [r1], #8			// load B
	MUL	r8, r9, r8			// C *= dequantCoef0
	mov	r10, r10, lsl r4		// dequantCoef1 <<= (qp/6)
	ldr	r9, [r1], #4			// load D
	MUL	r7, r10, r7			// B *= dequantCoef1
	add	r6, r6, r8			// E = A + C
	MUL	r9, r10, r9			// D *= dequantCoef1
	sub	r8, r6, r8, lsl #1		// G = A - C
	add	r10, r7, r9, asr #1		// F = B + (D>>1)
	rsb	r9, r9, r7, asr #1		// H = (B>>1) - D
	add	r6, r6, r10			// a = E + F
	sub	r10, r6, r10, lsl #1		// d = E - F
	add	r8, r8, r9			// b = G + H
	sub	r9, r8, r9, lsl #1		// c = G - H
	stmia	r11!, {r6, r8, r9, r10}		// store inverse transformed coefs (a, b, c, d)
	subs	r5, r5, #1			// i-- (this clear the z-flag for the next loop iteration)
	bne	L_loop_idct_horiz


	//
	// Vertical inverse transform and pixel reconstruction
	//

	add	r1, sp, #TMP_BLK
	add	r4, r3, r3, lsl #1		// 3*recoWidth
	rsb	r4, r4, #1			// -3*recoWidth + 1
	mov	r5, #4
#if ARM_ARCH_VERSION < ARM_ARCH_V6
	mov	r12, #255			// clipping boundary
#endif
LABELDEF(loop_idct_vert_recon)
	ldr	r6, [r1], #16			// A
	ldr	r7, [r1], #16			// B
	ldr	r8, [r1], #16			// C
	ldr	r9, [r1], #-48+4		// D
	add	r6, r6, r8			// E = A + C
	sub	r8, r6, r8, lsl #1		// G = A - C
	add	r10, r7, r9, asr #1		// F = B + (D>>1)
	rsb	r9, r9, r7, asr #1		// H = (B>>1) - D
	add	r6, r6, r10			// a = E + F
	sub	r10, r6, r10, lsl #1		// d = E - F
	ldrb	r7, [r0], #16			// get prediction value
	add	r8, r8, r9			// b = G + H
	add	r6, r6, #32			// add rounding constant ro residual
	sub	r9, r8, r9, lsl #1		// c = G - H

#if ARM_ARCH_VERSION < ARM_ARCH_V6

	// round and clip 1st pixel
	add	r6, r7, r6, asr #6		// normalize residual and add prediction to it
	cmp	r6, r12				// compare r6 with 255
	ldrb	r7, [r0], #16			// get next prediction value
	bichi	r6, r12, r6, asr #31		// clip pixel value to the range of [0,255]
	add	r8, r8, #32
	strb	r6, [r2], r3			// store reconstructed pixel to frame buffer

	// round and clip 2nd pixel
	add	r8, r7, r8, asr #6
	cmp	r8, r12
	ldrb	r7, [r0], #16			// get next prediction value
	bichi	r8, r12, r8, asr #31
	add	r9, r9, #32
	strb	r8, [r2], r3

	// round and clip 3rd pixel
	add	r9, r7, r9, asr #6
	cmp	r9, r12
	ldrb	r7, [r0], #-48+1
	bichi	r9, r12, r9, asr #31
	add	r10, r10, #32
	strb	r9, [r2], r3

	// round and clip 4th pixel
	add	r10, r7, r10, asr #6
	cmp	r10, r12
	bichi	r10, r12, r10, asr #31
	subs	r5, r5, #1
	strb	r10, [r2], r4

#else

	// round and clip 1st pixel
	add	r6, r7, r6, asr #6		// normalize residual and add prediction to it
	ldrb	r7, [r0], #16			// get next prediction value
	usat	r6, #8, r6			// clip pixel value to the range of [0,255]
	add	r8, r8, #32
	strb	r6, [r2], r3			// store reconstructed pixel to frame buffer

	// round and clip 2nd pixel
	add	r8, r7, r8, asr #6
	ldrb	r7, [r0], #16			// get next prediction value
	usat	r8, #8, r8			// clip pixel value to the range of [0,255]
	add	r9, r9, #32
	strb	r8, [r2], r3

	// round and clip 3rd pixel
	add	r9, r7, r9, asr #6
	ldrb	r7, [r0], #-48+1
	usat	r9, #8, r9			// clip pixel value to the range of [0,255]
	add	r10, r10, #32
	strb	r9, [r2], r3

	// round and clip 4th pixel
	add	r10, r7, r10, asr #6
	usat16	r10, #8, r10			// use usat16 to avoid early reg stall
	subs	r5, r5, #1
	strb	r10, [r2], r4

#endif

	bne	L_loop_idct_vert_recon


	add	sp, sp, #LOC_SIZE	// free stack space
	ldmfd	sp!, {r4-r11}		// pull 8 regs from stack
	bx	lr			// return


	ENDP


/*
 *
 * pedRecoBlockNoAC:
 *
 * Parameters:
 *      pred                  Predicted pixels
 *      reco                  Reconstructed pixels
 *      recoWidth             Width of reco. buffer in pixels
 *      dcValue               DC coefficient
 *
 * Function:
 *      All AC coefficients are zero - reconstruct using DC only.
 *
 * Returns:
 *      -
 */

/*
 *  void pedRecoBlockNoAC(u_int8 pred[BLK_SIZE][MBK_SIZE],
 *                        u_int8 *reco, int recoWidth,
 *                        int dcValue)
 * {
 */

	ALIGNW
#if defined(COMPILER_ADS)
	GLOBLAB	pedRecoBlockNoAC
pedRecoBlockNoAC PROC
#elif defined(COMPILER_GCC)
	GLOBLAB	pedRecoBlockNoAC
pedRecoBlockNoAC:
#elif defined(COMPILER_CCS)
	GLOBLAB	_pedRecoBlockNoAC
_pedRecoBlockNoAC
#endif

	stmfd	sp!, {r4-r7}		// save 4 regs

#if ARM_ARCH_VERSION < ARM_ARCH_V6

	sub	r2, r2, #3		// recoWidth - 3
	add	r3, r3, #32		// recoDCint = (dcValue + ITR_DEQUANT_ROUND)
	mov	r3, r3, asr #6		// recoDCint >>= ITR_DEQUANT_BITS
	mov	r12, #255
	mov	r4, #4			// 4 lines
LABELDEF(loop_reco_no_ac)
	ldrb	r5, [r0], #1
	ldrb	r6, [r0], #1
	ldrb	r7, [r0], #1
	add	r5, r5, r3		// sum up prediction and DC value
	cmp	r5, r12			// compare r5 with 255
	bichi	r5, r12, r5, asr #31	// if ((unsigned int)r5 > 255) r5 = 255 & ~((int)r5 >> 31)
	strb	r5, [r1], #1
	add	r6, r6, r3		// sum up prediction and DC value
	cmp	r6, r12			// compare r6 with 255
	bichi	r6, r12, r6, asr #31	// if ((unsigned int)r6 > 255) r6 = 255 & ~((int)r6 >> 31)
	strb	r6, [r1], #1
	ldrb	r6, [r0], #1+12
	add	r7, r7, r3		// sum up prediction and DC value
	cmp	r7, r12			// compare r7 with 255
	bichi	r7, r12, r7, asr #31	// if ((unsigned int)r7 > 255) r7 = 255 & ~((int)r7 >> 31)
	strb	r7, [r1], #1
	add	r6, r6, r3		// sum up prediction and DC value
	cmp	r6, r12			// compare r6 with 255
	bichi	r6, r12, r6, asr #31	// if ((unsigned int)r6 > 255) r6 = 255 & ~((int)r6 >> 31)
	strb	r6, [r1], r2
	subs	r4, r4, #1
	bne	L_loop_reco_no_ac

#else

	add	r3, r3, #32		// recoDCint = (dcValue + ITR_DEQUANT_ROUND)

	ldr	r4, [r0], #16		// load 1. row
	mov	r3, r3, asr #6		// recoDCint >>= ITR_DEQUANT_BITS
	ldr	r5, [r0], #16		// load 2. row
	mov	r3, r3, lsl #16		// clear 16 MSBs
	ldr	r6, [r0], #16		// load 3. row
	orr	r3, r3, r3, lsr #16	// duplicate half-word

	// process 1. row
	uxtab16	r7, r3, r4, ror #8	// 1.
	uxtab16	r4, r3, r4		// 1.
	usat16	r7, #8, r7		// 1.
	usat16	r4, #8, r4		// 1.

	// process 2. row
	uxtab16	r12, r3, r5, ror #8	// 2.
	uxtab16	r5, r3, r5		// 2.
	usat16	r12, #8, r12		// 2.
	usat16	r5, #8, r5		// 2.

	orr	r4, r4, r7, lsl #8	// 1.
	str	r4, [r1], r2		// 1.

	ldr	r7, [r0], #16		// load 4. row

	// process 3. row
	uxtab16	r4, r3, r6, ror #8	// 3.
	uxtab16	r6, r3, r6		// 3.
	usat16	r4, #8, r4		// 3.
	usat16	r6, #8, r6		// 3.

	orr	r5, r5, r12, lsl #8	// 2.
	str	r5, [r1], r2		// 2.

	// process 4. row
	uxtab16	r12, r3, r7, ror #8	// 4.
	uxtab16	r7, r3, r7		// 4.
	usat16	r12, #8, r12		// 4.
	usat16	r7, #8, r7		// 4.

	orr	r6, r6, r4, lsl #8	// 3.
	str	r6, [r1], r2		// 3.

	orr	r7, r7, r12, lsl #8	// 4.
	str	r7, [r1], r2		// 4.

#endif

	ldmfd	sp!, {r4-r7}		// pull 4 regs from stack
	bx	lr			// return


	ENDP


	ALIGNW
LABELDEF(deq_tab_ptr)
	DEFW	L_deq_tab


	DATASEC

LABELDEF(deq_tab)
	DEFB	10
	DEFB	13
	DEFB	13
	DEFB	16
	DEFB	10
	DEFB	13
	DEFB	13
	DEFB	16

	DEFB	11
	DEFB	14
	DEFB	14
	DEFB	18
	DEFB	11
	DEFB	14
	DEFB	14
	DEFB	18

	DEFB	13
	DEFB	16
	DEFB	16
	DEFB	20
	DEFB	13
	DEFB	16
	DEFB	16
	DEFB	20

	DEFB	14
	DEFB	18
	DEFB	18
	DEFB	23
	DEFB	14
	DEFB	18
	DEFB	18
	DEFB	23

	DEFB	16
	DEFB	20
	DEFB	20
	DEFB	25
	DEFB	16
	DEFB	20
	DEFB	20
	DEFB	25

	DEFB	18
	DEFB	23
	DEFB	23
	DEFB	29
	DEFB	18
	DEFB	23
	DEFB	23
	DEFB	29


	ENDFILE
