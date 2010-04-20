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


	CODE32
	CODESEC


/*
 *
 * loopLuma:
 *
 * Parameters:
 *      destCol               Pointer to first edge to be filtered
 *      dir                   Filter direction (horiz/vert)
 *      abIdxCurr             Initial alpha and beta indices
 *      abIdx                 Rest of the alpha and beta indices
 *      edgeDir               Edge direction (horiz/vert)
 *      strBits               Strength values
 *      n                     Number of columns/rows to be filtered
 *
 * Function:
 *      Filter MB block edges.
 *
 * Returns:
 *      -
 *
 */

/*
 * static void loopLuma(u_int8 *destCol, int dir, abIdx_s *abIdxCurr,
 *                      abIdx_s *abIdx, int edgeDir, u_int32 strBits, int n)
 * {
 */

	ALIGNW
#if defined(COMPILER_ADS) && !defined(__SYMBIAN32__)
	GLOBLAB	loopLuma
loopLuma PROC
#elif defined(COMPILER_GCC) || defined(__SYMBIAN32__)
	GLOBLAB	loopLuma
loopLuma:
#elif defined(COMPILER_CCS)
	GLOBLAB	_loopLuma
_loopLuma
#endif


// Local variables in stack
#define DEST_COL          0
#define ALPHA             4
#define BETA              8
#define CLIP_TAB_PTR      12
#define CURR_CLIP_TAB_PTR 16
#define BLK               20
#define LOC_SIZE          24	// Size of a stack frame

// Number of registers saved in stack
#define NUM_SAVED_REGS    9

// Offset to first function argument in stack
#define ARG_BASE          LOC_SIZE+4*NUM_SAVED_REGS

// Function arguments
#define EDGE_DIR          ARG_BASE+0
#define STR_BITS          ARG_BASE+4
#define NUM_ROWS_COLS     ARG_BASE+8


	// r0 = destCol
	// r1 = dir
	// r2 = abIdxCurr
	// r3 = abIdx
	// [sp]   = edgeDir
	// [sp+4] = strTab
	// [sp+8] = n

	stmfd	sp!, {r4-r11}		// save 8 regs
	str	lr, [sp, #-4]!		// push lr to stack = 4 bytes
	sub	sp, sp, #LOC_SIZE	// alloc space for local data

	str	r0, [sp, #DEST_COL]

	ldr	r6, L_alphaTabPtr	// alphaTab
	ldr	r7, L_betaTabPtr	// betaTab
	ldr	r8, L_clipTabPtr	// clipTab

	// Fetch alpha, beta and a pointer to clipBuf for other than the first filtered
	// block row or column

	ldr	r9, [r3, #0]		// abIdx->alphaIdx
	ldr	r10, [r3, #4]		// abIdx->betaIdx

	ldrb	r11, [r6, r9]		// alpha for rest of the block rows or columns
	ldrb	r12, [r7, r10]		// beta for rest of the block rows or columns
	add	r14, r8, r9, lsl #2	// clipTabPtr for rest of the block rows or columns
	str	r14, [sp, #CLIP_TAB_PTR]
	str	r11, [sp, #ALPHA]
	str	r12, [sp, #BETA]

	// Fetch alpha, beta and a pointer to clipBuf for the first filtered
	// block row or column

	ldr	r9, [r2, #0]		// abIdxCurr->alphaIdx
	ldr	r10, [r2, #4]		// abIdxCurr->betaIdx

	ldrb	r2, [r6, r9]		// alpha for the first block row or column
	ldrb	r3, [r7, r10]		// beta for the first block row or column
	add	r14, r8, r9, lsl #2	// clipTabPtr for the first block row or column

	ldr	r8, [sp, #STR_BITS]

	b	L_filt_row_col_skip


	// for (; n > 0; n--, destCol+=BLK_SIZE*dir) {

LABELDEF(filt_row_col_loop)

	ldr	r14, [sp, #CLIP_TAB_PTR]
	ldr	r2, [sp, #ALPHA]
	ldr	r3, [sp, #BETA]

LABELDEF(filt_row_col_skip)

	str	r14, [sp, #CURR_CLIP_TAB_PTR]

	ldr	r10, [sp, #EDGE_DIR]
	mov	r7, #4			// block loop counter

	//    for (blk = BLK_PER_MB; blk > 0; blk--) {

LABELDEF(filt_blks_loop)

	ands	r5, r8, #3		// str = strBits & 3
	addeq	r0, r0, r10, lsl #2	// if (str == 0) dest += BLK_SIZE*edgeDir
	beq	L_filt_next_block	// if str is 0 we do not need to filter this edge

	str	r8, [sp, #STR_BITS]	// store current strBits
	ldr	r8, [sp, #CURR_CLIP_TAB_PTR]
	sub	r5, r5, #1		// str - 1
	str	r7, [sp, #BLK]		// store current loop counter
	ldrb	r4, [r8, r5]		// c0
	mov	r5, #4			// loop counter

	//        for (i = BLK_SIZE; i > 0; i--, dest+=edgeDir) {

LABELDEF(filt_loop)
	// r0 = dest
	// r1 = dir
	// r2 = alpha
	// r3 = beta
	// r4 = c0
	// r5 = loop counter and

	ldrb	r7, [r0, -r1]		// orig3
	ldrb	r8, [r0]		// orig4
	ldrb	r6, [r0, -r1, lsl #1]	// orig2
	ldrb	r9, [r0, r1]		// orig5

	// r6 = orig2
	// r7 = orig3
	// r8 = orig4
	// r9 = orig5

	subs	r10, r7, r8		// delta = orig3 - orig4
	submi	r10, r8, r7		// delta = |delta|
	subs	r11, r6, r7		// orig2 - orig3
	submi	r11, r7, r6		// |orig2 - orig3|
	subs	r12, r8, r9		// orig4 - orig5
	submi	r12, r9, r8		// |orig4 - orig5|
	cmp	r10, r2			// if (delta >= alpha) 		OR
	cmplt	r11, r3			// if (|orig2 - orig3| >= beta) OR
	cmplt	r12, r3			// if (|orig4 - orig5| >= beta)
	bge	L_next_line		// then no filtering


LABELDEF(weak_filter)
	// r6 = orig2
	// r7 = orig3
	// r8 = orig4
	// r9 = orig5

	add	r10, r1, r1, lsl #1	// dir*3
	ldrb	r10, [r0, -r10]		// orig1
	ldrb	r11, [r0, r1, lsl #1]	// orig6
	mov	r14, r4			// c = c0
LABELDEF(check_left_filt)
	subs	r12, r7, r10		// orig3 - orig1
	submi	r12, r10, r7		// |orig3 - orig1|
	cmp	r12, r3			// if |orig3 - orig1| >= beta
	bge	L_check_right_filt	// then skip left pix filter
LABELDEF(filt_left_pix)
	add	r12, r7, r10, lsl #1	// diff  = orig[3] + 2*orig[1]
	add	r12, r12, r8		// diff += orig4
	add	r12, r12, #1		// diff += 1
	rsb	r12, r6, r12, asr #2	// diff = -orig[2] + (diff >> 2)
	cmn	r12, r4			// if diff < -c0
	rsblt	r12, r4, #0		// then diff = -c0
	cmp	r12, r4			// if diff > c0
	movgt	r12, r4			// then diff = c0
	add	r12, r6, r12		// orig2 + diff
	strb	r12, [r0, -r1, lsl #1]
	add	r14, r14, #1		// c++
LABELDEF(check_right_filt)
	subs	r12, r8, r11		// orig4 - orig6
	submi	r12, r11, r8		// |orig4 - orig6|
	cmp	r12, r3			// if |orig4 - orig6| >= beta
	bge	L_filt_middle_pix	// then skip right pix filter
LABELDEF(filt_right_pix)
	add	r12, r7, r11, lsl #1	// diff  = orig3 + 2*orig[6]
	add	r12, r12, r8		// diff += orig4
	add	r12, r12, #1		// diff += 1
	rsb	r12, r9, r12, asr #2	// diff  = -orig5 + (diff >> 2)
	cmn	r12, r4			// if diff < -c0
	rsblt	r12, r4, #0		// then diff = -c0
	cmp	r12, r4			// if diff > c0
	movgt	r12, r4			// then diff = c0
	add	r12, r9, r12		// orig5 + diff
	strb	r12, [r0, r1]
	add	r14, r14, #1		// c++

LABELDEF(filt_middle_pix)
	sub	r10, r8, r7		// diff = orig4 - orig3
	add	r10, r6, r10, lsl #2	// diff = orig2 + ((orig4 - orig3) << 2)
	sub	r10, r10, r9		// - orig5
	add	r10, r10, #4		// + 4
	mov	r6, #255
	mov	r10, r10, asr #3	// >> 3
	cmn	r10, r14		// if diff < -c
	rsblt	r10, r14, #0		// then diff = -c
	cmp	r10, r14		// if diff > -c
	movgt	r10, r14		// then diff = c
	add	r11, r7, r10		// left_edge_pix = orig3 + diff
	cmp	r11, r6
	bichi	r11, r6, r11, asr #31	// clip left_edge_pix to the range of [0,255]
	strb	r11, [r0, -r1]
	sub	r11, r8, r10		// right_edge_pix = orig4 - diff
	cmp	r11, r6
	bichi	r11, r6, r11, asr #31	// clip right_edge_pix to the range of [0,255]
	strb	r11, [r0]

LABELDEF(next_line)
	ldr	r10, [sp, #EDGE_DIR]	// edgeDir
	subs	r5, r5, #1		// decrement loop counter
	add	r0, r0, r10		// go to next line
	bne	L_filt_loop		// continue until loop counter wraps around

	ldr	r8, [sp, #STR_BITS]	// get current strBits
	ldr	r7, [sp, #BLK]		// get current block counter

LABELDEF(filt_next_block)
	movs	r8, r8, lsr #2
	subnes	r7, r7, #1
	bne	L_filt_blks_loop

	ldr	r0, [sp, #DEST_COL]
	ldr	r5, [sp, #NUM_ROWS_COLS]
	cmp	r8, #0			// strBits == 0 ?
	add	r0, r0, r1, lsl #2	// destCol+=BLK_SIZE*dir
	subnes	r5, r5, #1		// n--
	str	r0, [sp, #DEST_COL]
	str	r5, [sp, #NUM_ROWS_COLS]
	bne	L_filt_row_col_loop	// strBits != 0 && n != 0


	add	sp, sp, #LOC_SIZE	// deallocate local data
	ldr	lr, [sp], #4		// pull lr from stack
	ldmfd	sp!, {r4-r11}		// pull 8 regs from stack
	bx	lr			// return


	ENDP


/*
 *
 * loopLumaIntraMbEdge:
 *
 * Parameters:
 *      dest                  Pixels to be filtered
 *      dir                   Filter direction (horiz/vert)
 *      alphaIdx              Filter alpha index
 *      betaIdx               Filter beta index
 *      edgeDir               Edge direction (horiz/vert)
 *
 * Function:
 *      Filter intra MB edge.
 *
 * Returns:
 *      -
 *
 */

/*
 * void loopLumaIntraMbEdge(u_int8 *dest, int dir, int alphaIdx,
 *                          int betaIdx, int edgeDir)
 * {
 */

	ALIGNW
#if defined(COMPILER_ADS) && !defined(__SYMBIAN32__)
	GLOBLAB	loopLumaIntraMbEdge
loopLumaIntraMbEdge PROC
#elif defined(COMPILER_GCC) || defined(__SYMBIAN32__)
	GLOBLAB	loopLumaIntraMbEdge
loopLumaIntraMbEdge:
#elif defined(COMPILER_CCS)
	GLOBLAB	_loopLumaIntraMbEdge
_loopLumaIntraMbEdge
#endif
	// r0 = dest
	// r1 = dir
	// r2 = alphaIdx
	// r3 = betaIdx
	// [sp]   = edgeDir

	stmfd	sp!, {r4-r11}		// push 8 regs to stack = 32 bytes
	str	lr, [sp, #-4]!		// push lr to stack = 4 bytes
	// 9 regs pushed to stack = 36 bytes

	// [sp+36] = edgeDir

	ldr	r6, L_alphaTabPtr	// alphaTab
	ldr	r7, L_betaTabPtr	// betaTab
	ldr	r4, [sp, #36]		// edgeDir
	mov	r5, #16			// loop counter
	ldrb	r2, [r6, r2]		// alpha
	ldrb	r3, [r7, r3]		// beta


LABELDEF(filt_intra_loop)
	// r0 = dest
	// r1 = dir
	// r2 = alpha
	// r3 = beta
	// r4 = edgeDir
	// r5 = loop counter
	// [sp+40] = edgeDir

	ldrb	r7, [r0, -r1]		// orig3
	ldrb	r8, [r0]		// orig4
	ldrb	r6, [r0, -r1, lsl #1]	// orig2
	ldrb	r9, [r0, r1]		// orig5

	// r6 = orig2
	// r7 = orig3
	// r8 = orig4
	// r9 = orig5

	subs	r10, r7, r8		// delta = orig3 - orig4
	submi	r10, r8, r7		// delta = |delta|
	subs	r11, r6, r7		// orig2 - orig3
	submi	r11, r7, r6		// |orig2 - orig3|
	subs	r12, r8, r9		// orig4 - orig5
	submi	r12, r9, r8		// |orig4 - orig5|
	cmp	r10, r2			// if (delta >= alpha) 		OR
	cmplt	r11, r3			// if (|orig2 - orig3| >= beta) OR
	cmplt	r12, r3			// if (|orig4 - orig5| >= beta)
	bge	L_next_line_intra		// then no filtering

	sub	r11, r10, #2		// delta - 2
	cmp	r11, r2, asr #2		// delta - 2 < (alpha >> 2)
	blt	L_filt_intra_left	// if true, we will do long filter all the way

LABELDEF(short_filt)
	// do only short filter for both left and right sides
	add	r14, r7, r6, lsl #1	// orig3 + 2*orig2
	add	r14, r14, r9		// + orig5
	add	r14, r14, #2		// + 2
	add	r6, r6, r9, lsl #1	// orig2 + 2*orig5
	add	r6, r6, r8		// + orig4
	add	r6, r6, #2		// + 2
	mov	r14, r14, asr #2	// >> 2
	mov	r6, r6, asr #2		// >> 2
	strb	r14, [r0, -r1]
	strb	r6, [r0]
	b	L_next_line_intra

LABELDEF(filt_intra_left)
	add	r10, r1, r1, lsl #1	// 3*dir
	ldrb	r10, [r0, -r10]		// orig1
	ldrb	r11, [r0, r1, lsl #1]	// orig6
	subs	r12, r7, r10		// orig3 - orig1
	submi	r12, r10, r7		// |orig3 - orig1|
	cmp	r12, r3			// if |orig3 - orig1| < beta
	blt	L_long_filt_left	// then do longer filter
LABELDEF(short_filt_left)
	add	r14, r7, r6, lsl #1	// orig3 + 2*orig2
	add	r14, r14, r9		// + orig5
	add	r14, r14, #2		// + 2
	mov	r14, r14, asr #2	// >> 2
	strb	r14, [r0, -r1]
	b	L_filt_intra_right
LABELDEF(long_filt_left)
	// r10 = orig1
	// r11 = orig6
	add	r12, r6, r7		// tmpSum = orig2 + orig3
	add	r12, r12, r8		// + orig4
	add	r12, r12, #2		// + 2
	add	r14, r10, r12, lsl #1	// orig1 + 2*tmpSum
	add	r14, r14, r9		// + orig5
	add	r12, r10, r12		// orig1 + tmpSum
	mov	r14, r14, asr #3	// >> 3
	strb	r14, [r0, -r1]
	mov	r14, r12, asr #2	// >> 2
	strb	r14, [r0, -r1, lsl #1]
	ldrb	r14, [r0, -r1, lsl #2]	// orig0
	add	r12, r12, r10, lsl #1	// orig1 + tmpSum + 2*orig1
	add	r12, r12, #2		// + 2
	add	r12, r12, r14, lsl #1	// + 2*orig0
	add	r14, r1, r1, lsl #1	// 3*dir
	mov	r12, r12, asr #3	// >> 3
	strb	r12, [r0, -r14]

LABELDEF(filt_intra_right)
	// r11 = orig6
	subs	r12, r8, r11		// orig4 - orig6
	submi	r12, r11, r8		// |orig4 - orig6|
	cmp	r12, r3			// if |orig4 - orig6| < beta
	blt	L_long_filt_right	// then do longer filter
LABELDEF(short_filt_right)
	add	r14, r6, r9, lsl #1	// orig2 + 2*orig5
	add	r14, r14, r8		// + orig4
	add	r14, r14, #2		// + 2
	mov	r14, r14, asr #2	// >> 2
	strb	r14, [r0]
	b	L_next_line_intra
LABELDEF(long_filt_right)
	add	r12, r7, r8		// tmpSum = orig3 + orig4
	add	r12, r12, r9		// + orig5
	add	r12, r12, #2		// + 2
	add	r10, r1, r1, lsl #1	// 3*dir
	add	r14, r6, r12, lsl #1	// orig2 + 2*tmpSum
	add	r14, r14, r11		// + orig6
	add	r12, r12, r11		// tmpSum + orig6
	mov	r14, r14, asr #3	// >> 3
	strb	r14, [r0]
	mov	r14, r12, asr #2	// >> 2
	strb	r14, [r0, r1]
	ldrb	r14, [r0, r10]		// orig7
	add	r12, r12, r11, lsl #1	// tmpSum + orig6 + 2*orig6
	add	r12, r12, #2		// + 2
	add	r12, r12, r14, lsl #1	// + 2*orig7
	mov	r12, r12, asr #3	// >> 3
	strb	r12, [r0, r1, lsl #1]

LABELDEF(next_line_intra)
	subs	r5, r5, #1		// decrement loop counter
	add	r0, r0, r4		// go to next line
	bne	L_filt_intra_loop	// continue until loop counter wraps around

	ldr	lr, [sp], #4		// pull lr from stack
	ldmfd	sp!, {r4-r11}		// pull 8 regs from stack
	bx	lr			// return


	ENDP


/*
 *
 * loopChroma:
 *
 * Parameters:
 *      destUcol              Pointer to first edge to be filtered (U)
 *      dir                   Filter direction (horiz/vert)
 *      abIdxCurr             Initial alpha and beta indices
 *      abIdx                 Rest of the alpha and beta indices
 *      edgeDir               Edge direction (horiz/vert)
 *      strBits               Strength values
 *      destVcol              Pointer to first edge to be filtered (V)
 *      n                     Number of columns/rows to be filtered
 *
 * Function:
 *      Filter MB block edges.
 *
 * Returns:
 *      -
 *
 */

/*
 * static void loopChroma(u_int8 *destUcol, int dir, abIdx_s *abIdxCurr,
 *                        abIdx_s *abIdx, int edgeDir, u_int32 strBits,
 *                        u_int8 *destVcol, int n)
 * {
 */

	ALIGNW
#if defined(COMPILER_ADS) && !defined(__SYMBIAN32__)
	GLOBLAB	loopChroma
loopChroma PROC
#elif defined(COMPILER_GCC) || defined(__SYMBIAN32__)
	GLOBLAB	loopChroma
loopChroma:
#elif defined(COMPILER_CCS)
	GLOBLAB	_loopChroma
_loopChroma
#endif

// Local variables in stack
#define DEST_U_COL        0
#define ALPHA             4
#define BETA              8
#define CLIP_TAB_PTR      12
#define CURR_CLIP_TAB_PTR 16
#define BLK               20
#define DEST_U            24
#define DEST_V            28
#define LOC_SIZE          32	// Size of a stack frame

// Number of registers saved in stack
#define NUM_SAVED_REGS    9

// Offset to first function argument in stack
#define ARG_BASE          LOC_SIZE+4*NUM_SAVED_REGS

// Function arguments
#define EDGE_DIR          ARG_BASE+0
#define STR_BITS          ARG_BASE+4
#define DEST_V_COL        ARG_BASE+8
#define NUM_ROWS_COLS     ARG_BASE+12


	// r0 = destUcol
	// r1 = dir
	// r2 = abIdxCurr
	// r3 = abIdx
	// [sp]    = edgeDir
	// [sp+4]  = strTab
	// [sp+8]  = destVcol
	// [sp+12] = n

	stmfd	sp!, {r4-r11}		// push 8 regs to stack
	str	lr, [sp, #-4]!		// push lr to stack
	sub	sp, sp, #LOC_SIZE	// alloc space for local data

	str	r0, [sp, #DEST_U_COL]

	ldr	r6, L_alphaTabPtr	// alphaTab
	ldr	r7, L_betaTabPtr	// betaTab
	ldr	r8, L_clipTabPtr	// clipTab

	// Fetch alpha, beta and a pointer to clipBuf for other than the first filtered
	// block row or column

	ldr	r9, [r3, #8]		// abIdx->alphaIdx
	ldr	r10, [r3, #12]		// abIdx->betaIdx
	ldrb	r11, [r6, r9]		// alpha for rest of the block rows or columns
	ldrb	r12, [r7, r10]		// beta for rest of the block rows or columns
	add	r14, r8, r9, lsl #2	// clipTabPtr for rest of the block rows or columns
	str	r14, [sp, #CLIP_TAB_PTR]
	str	r11, [sp, #ALPHA]
	str	r12, [sp, #BETA]

	// Fetch alpha, beta and a pointer to clipBuf for the first filtered
	// block row or column

	ldr	r9, [r2, #8]		// abIdxCurr->alphaIdx
	ldr	r10, [r2, #12]		// abIdxCurr->betaIdx
	ldrb	r2, [r6, r9]		// alpha for the first block row or column
	ldrb	r3, [r7, r10]		// beta for the first block row or column
	add	r14, r8, r9, lsl #2	// clipTabPtr for the first block row or column

	ldr	r11, [sp, #EDGE_DIR]

	ldr	r8, [sp, #STR_BITS]

	b	L_c_filt_row_col_skip


	//  for (; n > 0; n--, strTab+=BLK_PER_MB, destUcol+=2*BLK_SIZE/2*dir,
	//                                         destVcol+=2*BLK_SIZE/2*dir)

LABELDEF(c_filt_row_col_loop)

	ldr	r14, [sp, #CLIP_TAB_PTR]
	ldr	r2, [sp, #ALPHA]
	ldr	r3, [sp, #BETA]

LABELDEF(c_filt_row_col_skip)

	str	r14, [sp, #CURR_CLIP_TAB_PTR]

	mov	r7, #4			// block loop counter
	ldr	r0, [sp, #DEST_U_COL]
	ldr	r6, [sp, #DEST_V_COL]

	//    for (blk = BLK_PER_MB; blk > 0; blk--, destU+=(BLK_SIZE/2)*edgeDir,
	//                                           destV+=(BLK_SIZE/2)*edgeDir)

LABELDEF(c_filt_blks_loop)

	ands	r5, r8, #3		// str = strBits & 3
	beq	L_c_filt_next_block	// if str is 0 we do not need to filter this edge

	str	r8, [sp, #STR_BITS]	// store current strTab pointer
	ldr	r8, [sp, #CURR_CLIP_TAB_PTR]
	sub	r5, r5, #1		// str - 1
	str	r7, [sp, #BLK]		// store current loop counter
	ldrb	r4, [r8, r5]		// c0

	mov	r5, #0			// loop counter
	// loop cuonter is in two highest bits of r5
	// loop counter will have binary values 00 01 10 11 and 00.
	// when loop counter goes from 01 to 10 V-flag is set and we change
	// from U component to V component (with conditional load).
	// when loop counter goes from 11 to 00 C-flag is set and we exit the loop

	str	r0, [sp, #DEST_U]
	str	r6, [sp, #DEST_V]

	add	r4, r4, #1		// c = c0 + 1

	//        for (i = BLK_SIZE; i > 0; i--, dest+=edgeDir) {

LABELDEF(c_filt_loop)
	// r0 = dest
	// r1 = dir
	// r2 = alpha
	// r3 = beta
	// r4 = c
	// r5 = loop counter
	// r11 = edgeDir

	ldrb	r7, [r0, -r1]		// orig3
	ldrb	r8, [r0]		// orig4
	ldrb	r6, [r0, -r1, lsl #1]	// orig2
	ldrb	r9, [r0, r1]		// orig5

	// r6 = orig2
	// r7 = orig3
	// r8 = orig4
	// r9 = orig5

	subs	r10, r7, r8		// delta = orig3 - orig4
	submi	r10, r8, r7		// delta = |delta|
	subs	r12, r6, r7		// orig2 - orig3
	submi	r12, r7, r6		// |orig2 - orig3|
	subs	r14, r8, r9		// orig4 - orig5
	submi	r14, r9, r8		// |orig4 - orig5|
	cmp	r10, r2			// if (delta >= alpha)		OR
	cmplt	r12, r3			// if (|orig2 - orig3| >= beta)	OR
	cmplt	r14, r3			// if (|orig4 - orig5| >= beta)
	bge	L_c_next_line		// then no filtering

LABELDEF(c_weak_filter)
	// r6 = orig2
	// r7 = orig3
	// r8 = orig4
	// r9 = orig5

	sub	r10, r8, r7		// diff = orig4 - orig3
	sub	r6, r6, r9		// orig2 - orig5
	add	r10, r6, r10, lsl #2	// diff = orig2 - orig5 + ((orig4 - orig3) << 2)
	add	r10, r10, #4		// + 4
	mov	r6, #255
	mov	r10, r10, asr #3	// >> 3
	cmn	r10, r4			// if diff < -c
	rsblt	r10, r4, #0		// then diff = -c
	cmp	r10, r4			// if diff > -c
	movgt	r10, r4			// then diff = c
	add	r9, r7, r10		// left_edge_pix = orig3 + diff
	cmp	r9, r6
	bichi	r9, r6, r9, asr #31	// clip left_edge_pix to the range of [0,255]
	strb	r9, [r0, -r1]
	sub	r9, r8, r10		// right_edge_pix = orig4 - diff
	cmp	r9, r6
	bichi	r9, r6, r9, asr #31	// clip right_edge_pix to the range of [0,255]
	strb	r9, [r0]

LABELDEF(c_next_line)
	adds	r5, r5, #0x40000000	// increment loop counter
	add	r0, r0, r11		// go to next line
	ldrvs	r0, [sp, #DEST_V]	// load V frame pointer if V-flag set
	bcc	L_c_filt_loop		// continue until loop counter wraps (C-flag set)

	ldr	r8, [sp, #STR_BITS]	// get current strTab pointer
	ldr	r7, [sp, #BLK]		// get current block counter

	ldr	r0, [sp, #DEST_U]
	ldr	r6, [sp, #DEST_V]

LABELDEF(c_filt_next_block)
	movs	r8, r8, lsr #2		// strBits >>= 2
	subnes	r7, r7, #1
	add	r0, r0, r11, lsl #1	// destU+=(BLK_SIZE/2)*edgeDir
	add	r6, r6, r11, lsl #1	// destV+=(BLK_SIZE/2)*edgeDir
	bne	L_c_filt_blks_loop

	movs	r8, r8, lsr #4*2	// strBits >>= BLK_PER_MB*2

	ldr	r0, [sp, #DEST_U_COL]
	ldr	r6, [sp, #DEST_V_COL]
	ldr	r5, [sp, #NUM_ROWS_COLS]
	add	r0, r0, r1, lsl #2	// destUcol+=2*BLK_SIZE/2*dir
	add	r6, r6, r1, lsl #2	// destUcol+=2*BLK_SIZE/2*dir
	subnes	r5, r5, #1		// n--
	str	r0, [sp, #DEST_U_COL]
	str	r6, [sp, #DEST_V_COL]
	str	r5, [sp, #NUM_ROWS_COLS]
	bne	L_c_filt_row_col_loop	// strBits != 0 && n != 0

	add	sp, sp, #LOC_SIZE	// dealloc space for local data
	ldr	lr, [sp], #4		// pull lr from stack
	ldmfd	sp!, {r4-r11}		// pull 8 regs from stack
	bx	lr			// return


	ENDP


/*
 *
 * loopChromaIntraMbEdge:
 *
 * Parameters:
 *      dest                  Pixels to be filtered (U)
 *      dir                   Filter direction (horiz/vert)
 *      alphaIdx              Filter alpha index
 *      betaIdx               Filter beta index
 *      edgeDir               Edge direction (horiz/vert)
 *      dest2                 Pixels to be filtered (V)
 *
 * Function:
 *      Filter intra MB edge.
 *
 * Returns:
 *      -
 *
 */

/*
 * static void loopChromaIntraMbEdge(u_int8 *dest, int dir, int alphaIdx,
 *                                   int betaIdx, int edgeDir, u_int8 *dest2)
 * {
 */

	ALIGNW
#if defined(COMPILER_ADS) && !defined(__SYMBIAN32__)
	GLOBLAB	loopChromaIntraMbEdge
loopChromaIntraMbEdge PROC
#elif defined(COMPILER_GCC) || defined(__SYMBIAN32__)
	GLOBLAB	loopChromaIntraMbEdge
loopChromaIntraMbEdge:
#elif defined(COMPILER_CCS)
	GLOBLAB	_loopChromaIntraMbEdge
_loopChromaIntraMbEdge
#endif
	// r0 = dest
	// r1 = dir
	// r2 = alphaIdx
	// r3 = betaIdx
	// [sp]   = edgeDir
	// [sp+4] = dest2

	stmfd	sp!, {r4-r11}		// push 8 regs to stack = 32 bytes
	// 8 regs pushed to stack = 32 bytes

	// [sp+32] = edgeDir
	// [sp+36] = dest2

	ldr	r11, [sp, #32]		// edgeDir
	ldr	r6, L_alphaTabPtr	// alphaTab
	ldr	r7, L_betaTabPtr	// betaTab
	mov	r5, #0
	ldrb	r2, [r6, r2]		// alpha
	ldrb	r3, [r7, r3]		// beta

	// loop cuonter is in two highest bits of r5.
	// loop counter will have binary values 00 01 10 11 and 00.
	// when loop counter goes from 01 to 10 V-flag is set and we change
	// from U component to V component (with conditional load).
	// when loop counter goes from 11 to 00 C-flag is set and we exit the loop

LABELDEF(c_filt_intra_loop)
	// r0 = dest
	// r1 = dir
	// r2 = alpha
	// r3 = beta
	// r5 = loop counter
	// [sp+32] = edgeDir
	// [sp+36] = dest2

	ldrb	r7, [r0, -r1]		// orig3
	ldrb	r8, [r0]		// orig4
	ldrb	r6, [r0, -r1, lsl #1]	// orig2
	ldrb	r9, [r0, r1]		// orig5

	// r6 = orig2
	// r7 = orig3
	// r8 = orig4
	// r9 = orig5

	subs	r10, r7, r8		// delta = orig3 - orig4
	submi	r10, r8, r7		// delta = |delta|
	subs	r12, r6, r7		// orig2 - orig3
	submi	r12, r7, r6		// |orig2 - orig3|
	subs	r4, r8, r9		// orig4 - orig5
	submi	r4, r9, r8		// |orig4 - orig5|
	cmp	r10, r2			// if (delta >= alpha)		OR
	cmplt	r12, r3			// if (|orig2 - orig3| >= beta)	OR
	cmplt	r4, r3			// if (|orig4 - orig5| >= beta)
	bge	L_c_next_line_intra	// then no filtering

	add	r10, r7, r6, lsl #1	// 1) orig3 + 2*orig2
	add	r6, r6, r9, lsl #1	// 2) orig2 + 2*orig5
	add	r10, r10, r9		// 1) + orig5
	add	r6, r6, r8		// 2) + orig4
	add	r10, r10, #2		// 1) + 2
	add	r6, r6, #2		// 2) + 2
	mov	r10, r10, asr #2	// 1) >> 2
	mov	r6, r6, asr #2		// 2) >> 2
	strb	r10, [r0, -r1]		// 1)
	strb	r6, [r0]		// 2)

LABELDEF(c_next_line_intra)
	adds	r5, r5, #0x10000000	// increment loop counter
	add	r0, r0, r11		// go to next line
	ldrvs	r0, [sp, #36]		// load V frame pointer if V-flag set
	bcc	L_c_filt_intra_loop	// continue until loop counter wraps (C-flag set)

	ldmfd	sp!, {r4-r11}		// pull 8 regs from stack
	bx	lr			// return


	ENDP



	ALIGNW
LABELDEF(alphaTabPtr)
	DEFW	L_alphaTab
LABELDEF(betaTabPtr)
	DEFW	L_betaTab
LABELDEF(clipTabPtr)
	DEFW	L_clipTab



	DATASEC


	DEFB	  0,  0,  0,  0,  0,  0,  0,  0
	DEFB	  0,  0,  0,  0
LABELDEF(alphaTab)
	DEFB	  0,  0,  0,  0,  0,  0,  0,  0
	DEFB	  0,  0,  0,  0,  0,  0,  0,  0
	DEFB	  4,  4,  5,  6,  7,  8,  9, 10
	DEFB	 12, 13, 15, 17, 20, 22, 25, 28
	DEFB	 32, 36, 40, 45, 50, 56, 63, 71
	DEFB	 80, 90,101,113,127,144,162,182
	DEFB	203,226,255,255

	DEFB	255,255,255,255,255,255,255,255
	DEFB	255,255,255,255



	DEFB	 0, 0, 0, 0, 0, 0, 0, 0
	DEFB	 0, 0, 0, 0
LABELDEF(betaTab)
	DEFB	 0, 0, 0, 0, 0, 0, 0, 0
	DEFB	 0, 0, 0, 0, 0, 0, 0, 0
	DEFB	 2, 2, 2, 3, 3, 3, 3, 4
	DEFB	 4, 4, 6, 6, 7, 7, 8, 8
	DEFB	 9, 9,10,10,11,11,12,12
	DEFB	13,13,14,14,15,15,16,16
	DEFB	17,17,18,18

	DEFB	18,18,18,18,18,18,18,18
	DEFB	18,18,18,18



	DEFB	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	DEFB	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	DEFB	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
LABELDEF(clipTab)
	DEFB	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	DEFB	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	DEFB	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	DEFB	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	DEFB	 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1
	DEFB	 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1
	DEFB	 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2
	DEFB	 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 2, 3, 3
	DEFB	 1, 2, 3, 3, 2, 2, 3, 3, 2, 2, 4, 4, 2, 3, 4, 4
	DEFB	 2, 3, 4, 4, 3, 3, 5, 5, 3, 4, 6, 6, 3, 4, 6, 6
	DEFB	 4, 5, 7, 7, 4, 5, 8, 8, 4, 6, 9, 9, 5, 7,10,10
	DEFB	 6, 8,11,11, 6, 8,13,13, 7,10,14,14, 8,11,16,16
	DEFB	 9,12,18,18,10,13,20,20,11,15,23,23,13,17,25,25

	DEFB	13,17,25,25,13,17,25,25,13,17,25,25,13,17,25,25
	DEFB	13,17,25,25,13,17,25,25,13,17,25,25,13,17,25,25
	DEFB	13,17,25,25,13,17,25,25,13,17,25,25,13,17,25,25



	ENDFILE
