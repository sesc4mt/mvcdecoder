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

#define PRELOAD 0

	CODE32
	CODESEC

	ALIGNW

#if defined(COMPILER_ADS) && !defined(__SYMBIAN32__)
	GLOBLAB	interleaveParallax_asm
interleaveParallax_asm PROC
#elif defined(COMPILER_GCC) || defined(__SYMBIAN32__)
	GLOBLAB	interleaveParallax_asm
	.type	interleaveParallax_asm, %function
interleaveParallax_asm:
#elif defined(COMPILER_CCS)
	GLOBLAB	_interleaveParallax_asm
_interleaveParallax_asm
#endif


// Variables in stack

#define	SP_m45568		0
#define	SP_p357_m88		4
#define	SP_p34688		8
#define	SP_m182_p452		12
#define	SP_m57728		16
#define SP_COUNTER_J		24
#define SP_UV_ROW_INDEX		28
#define SP_COUNTER_I		32
#define SP_UV_WIDTH		36

#define SP_YL_BUF		40
#define SP_YR_BUF		44
#define SP_UL_BUF		48
#define SP_UR_BUF		52
#define SP_VL_BUF		56
#define SP_VR_BUF		60
#define SP_ROW_EVEN		64
#define SP_ROW_ODD		68
#define SP_WIDTH		72
#define SP_HEIGHT		76

#define SP_SAVED_SP		80



	mov	r12, sp
	stmfd	sp!, {r4-r11}		// save regs
	str	lr, [sp, #-4]!		// save return address

	ldmia	r12, {r4-r9}		// load params from stack
	mov	r12, sp			// save non-aligned stack pointer
	sub	sp, sp, #4		// align stack pointer at 8 bytes
	mvn	r11, #7			// ...
	and	sp, sp, r11		// ...
	stmfd	sp!, {r0-r9}		// save all params to aligned stack area
	sub	sp, #40			// make space for local vars

	str	r12, [sp, #SP_SAVED_SP]	// save non-aligned stack pointer

	ldr	r12, L_rgb_coefs_ptr
	ldmia	r12, {r0-r4}
	stmia	sp, {r0-r4}

	mov	r0, #0
	str	r0, [sp, #SP_COUNTER_I]

	ldr	r0, [sp, #SP_WIDTH]
	mov	r0, r0, lsr #1
	str	r0, [sp, #SP_UV_WIDTH]

LABELDEF(row_loop)

	ldr	r0, [sp, #SP_COUNTER_I]
	ldr	r1, [sp, #SP_UV_WIDTH]
	ldr	r2, [sp, #SP_WIDTH]
	mov	r0, r0, lsr #1
	smulbb	r0, r1, r0
	str	r2, [sp, #SP_COUNTER_J]
	str	r0, [sp, #SP_UV_ROW_INDEX]

LABELDEF(pel_loop)

#define COUNTER_J	r0
#define UV_ROW_INDEX	r1
#define COUNTER_J_MINUS_2   r6
#define UV_ROW_INDEX_PLUS_1 r7
#define UL_BUF		r8
#define UR_BUF		r9
#define VL_BUF		r10
#define VR_BUF		r11
#define UL		r8
#define UR		r9
#define VL		r10
#define VR		r11

	// ldr	COUNTER_J, [sp, #SP_COUNTER_J]
	// ldr	UV_ROW_INDEX, [sp, #SP_UV_ROW_INDEX]
	ldrd	COUNTER_J, [sp, #SP_COUNTER_J]
	// ldr	VL_BUF, [sp, #SP_VL_BUF]
	// ldr	VR_BUF, [sp, #SP_VR_BUF]
	ldrd	VL_BUF, [sp, #SP_VL_BUF]
	// ldr	UL_BUF, [sp, #SP_UL_BUF]
	// ldr	UR_BUF, [sp, #SP_UR_BUF]
	ldrd	UL_BUF, [sp, #SP_UL_BUF]

#define m45568		r2
#define p357_m88	r3
#define p34688		r4
#define m182_p452	r5
#define m57728		r14

	ldmia	sp, {m45568, p357_m88, p34688, m182_p452, m57728}

	subs	COUNTER_J_MINUS_2, COUNTER_J, #2	// j-2
	add	UV_ROW_INDEX_PLUS_1, UV_ROW_INDEX, #1	// uvRowIndex+1

	// str	COUNTER_J_MINUS_2, [sp, #SP_COUNTER_J]
	// str	UV_ROW_INDEX_PLUS_1, [sp, #SP_UV_ROW_INDEX]
	strd	COUNTER_J_MINUS_2, [sp, #SP_COUNTER_J]

	ldrb	VL, [VL_BUF, UV_ROW_INDEX]	// vl = vlBuf[uvRowIndex]
	ldrb	VR, [VR_BUF, UV_ROW_INDEX]	// vr = vrBuf[uvRowIndex]
	ldrb	UL, [UL_BUF, UV_ROW_INDEX]	// ul = ulBuf[uvRowIndex]
	ldrb	UR, [UR_BUF, UV_ROW_INDEX]	// vl = vlBuf[uvRowIndex]

#define YL_BUF		r6
#define YR_BUF		r7

	// ldr	YL_BUF, [sp, #SP_YL_BUF]
	// ldr	YR_BUF, [sp, #SP_YR_BUF]
	ldrd	YL_BUF, [sp, #SP_YL_BUF]

#define RL		r0
#define RR		r1
#define GL		r2
#define GR		r3
#define BL		r4
#define BR		r5


	smlabb	RL, p357_m88, VL, m45568	// rl = 357*vl-45568
	smlabb	RR, p357_m88, VR, m45568	// rr = 357*vr-45568
	smlatb	GL, p357_m88, UL, p34688	// gl = 34688-88*ul
	smlatb	GR, p357_m88, UR, p34688	// gr = 34688-88*ur
	smlabb	GL, m182_p452, VL, GL		// gl += -182*vl
	smlabb	GR, m182_p452, VR, GR		// gr += -182*vr

#define YL		R10
#define YR		R11

	ldrb	YL, [YL_BUF], #1		// yl = (*ylBuf++)
	ldrb	YR, [YR_BUF], #1		// yr = (*yrBuf++)
#if PRELOAD
	pld	[YL_BUF, #23]			// preload
#endif
	smlatb	BL, m182_p452, UL, m57728	// bl = 452*ul-57728
	smlatb	BR, m182_p452, UR, m57728	// br = 452*ur-57728

#define ROW_EVEN	r14

	ldr	ROW_EVEN, [sp, #SP_ROW_EVEN]

#define REDL		r8
#define GREENL		r9
#define BLUEL		r12
#define REDR		r8
#define GREENR		r9
#define BLUER		r12

	add	REDL,   RL, YL, lsl #8		// redL = (yl<<8)+rl
	add	GREENL, GR, YR, lsl #8		// greenL = (yr<<8)+gr
	add	BLUEL,  BL, YL, lsl #8		// blueL = (yl<<8)+bl
	usat	REDL,   #5, REDL,   asr #11	// redL = max(0, min((1<<5)-1, (redL >> 11)))
	usat	GREENL, #6, GREENL, asr #10	// greenL = max(0, min((1<<6)-1, (greenL >> 10)))
	usat	BLUEL,  #5, BLUEL,  asr #11	// blueL = max(0, min((1<<5)-1, (blueL >> 11)))
	orr	GREENL, GREENL, REDL, lsl #6	// greenL |= redL << 6
	add	REDR,   RR, YR, lsl #8		// redR = (yr<<8)+rr
	orr	BLUEL, BLUEL, GREENL, lsl #5	// blueL |= greenL << 5
	strh	BLUEL, [ROW_EVEN], #2
	add	GREENR, GL, YL, lsl #8		// greenR = (yl<<8)+gl
	add	BLUER,  BR, YR, lsl #8		// blueR = (yr<<8)+br
	usat	REDR,   #5, REDR,   asr #11	// redR = max(0, min(2^5-1, (redR >> 11)))
	usat	GREENR, #6, GREENR, asr #10	// greenR = max(0, min(2^6-1, (greenR >> 10)))
	usat	BLUER,  #5, BLUER,  asr #11	// blueR = max(0, min(2^5-1, (blueR >> 11)))
	orr	GREENR, GREENR, REDR, lsl #6	// greenR |= redR << 6
	ldrb	YL, [YL_BUF], #1		// yl = (*ylBuf++)
	ldrb	YR, [YR_BUF], #1		// yr = (*yrBuf++)
#if PRELOAD
	pld	[YR_BUF, #18]			// preload
#endif
	orr	BLUER, BLUER, GREENR, lsl #5	// blueR |= greenR << 5
	strh	BLUER, [ROW_EVEN], #2

	add	REDL,   RL, YL, lsl #8		// redL = (yl<<8)+rl
	add	GREENL, GR, YR, lsl #8		// greenL = (yr<<8)+gr
	add	BLUEL,  BL, YL, lsl #8		// blueL = (yl<<8)+bl
	usat	REDL,   #5, REDL,   asr #11	// redL = max(0, min(2^5-1, (redL >> 11)))
	usat	GREENL, #6, GREENL, asr #10	// greenL = max(0, min(2^6-1, (greenL >> 10)))
	usat	BLUEL,  #5, BLUEL,  asr #11	// blueL = max(0, min(2^5-1, (blueL >> 11)))
	orr	GREENL, GREENL, REDL, lsl #6	// greenL |= redL << 6
	add	REDR,   RR, YR, lsl #8		// (yr<<8)+rr
	orr	BLUEL, BLUEL, GREENL, lsl #5	// blueL |= greenL << 5
	strh	BLUEL, [ROW_EVEN], #2
	add	GREENR, GL, YL, lsl #8		// (yl<<8)+gl
	add	BLUER,  BR, YR, lsl #8		// (yr<<8)+br
	usat	REDR,   #5, REDR,   asr #11	// redR = max(0, min(2^5-1, (redR >> 11)))
	usat	GREENR, #6, GREENR, asr #10	// greenR = max(0, min(2^6-1, (greenR >> 10)))
	usat	BLUER,  #5, BLUER,  asr #11	// blueR = max(0, min(2^5-1, (blueR >> 11)))
	orr	GREENR, GREENR, REDR, lsl #6	// greenR |= redR << 6
	// str	YL_BUF, [sp, #SP_YL_BUF]
	// str	YR_BUF, [sp, #SP_YR_BUF]
	strd	YL_BUF, [sp, #SP_YL_BUF]
	orr	BLUER, BLUER, GREENR, lsl #5	// blueR |= greenR << 5
	strh	BLUER, [ROW_EVEN], #2

	str	ROW_EVEN, [sp, #SP_ROW_EVEN]

	bne	L_pel_loop


	// duplicate even row to odd row

	ldr	r2, [sp, #SP_WIDTH]
	ldr	r0, [sp, #SP_ROW_EVEN]
	ldr	r1, [sp, #SP_ROW_ODD]

	add	r3, r0, r2, lsl #2		// rowEven += width*2
	add	r4, r1, r2, lsl #3		// rowOdd += width*2*2

	str	r3, [sp, #SP_ROW_EVEN]
	str	r4, [sp, #SP_ROW_ODD]
	sub	r0, r0, r2, lsl #2
	mov	r2, r2, lsl #2

	// copy 32 bytes at a time
LABELDEF(copy_even_to_odd)
	ldmia	r0!, {r4-r11}
	subs	r2, r2, #32
	stmia	r1!, {r4-r11}
	bgt	L_copy_even_to_odd

	beq	L_all_copied

	add	r2, r2, #32

	// copy 4 bytes at a time
LABELDEF(copy_even_to_odd_2)
	ldr	r4, [r0], #4
	subs	r2, r2, #4
	str	r4, [r1], #4
	bne	L_copy_even_to_odd_2

LABELDEF(all_copied)

	ldr	r0, [sp, #SP_COUNTER_I]
	ldr	r1, [sp, #SP_HEIGHT]
	add	r0, r0, #1
	cmp	r0, r1
	str	r0, [sp, #SP_COUNTER_I]
	blt	L_row_loop


	ldr	sp, [sp, #SP_SAVED_SP]

	ldr	lr, [sp], #4		// pull lr from stack
	ldmfd	sp!, {r4-r11}		// pull 8 regs from stack
	bx	lr			// return


#if defined(COMPILER_GCC) || defined(__SYMBIAN32__)
	.size	interleaveParallax_asm, .-interleaveParallax_asm
#endif

	ENDP


	ALIGNW
LABELDEF(rgb_coefs_ptr)
	DEFW	L_rgb_coefs


	DATASEC


	ALIGNW
LABELDEF(rgb_coefs)
	DEFW	-45568
	DEFH	357
	DEFH	-88
	DEFW	34688
	DEFH	-182
	DEFH	452
	DEFW	-57728


	ENDFILE
