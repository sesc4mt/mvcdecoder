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
	.cpu arm1136j-s
	.fpu softvfp
	.file	"conversion.c"
	.section	.rodata
	.align	2
	.type	blueInterlacing, %object
	.size	blueInterlacing, 60
blueInterlacing:
	.word	0
	.word	0
	.word	255
	.word	0
	.word	0
	.word	255
	.word	0
	.word	255
	.word	255
	.word	0
	.word	255
	.word	255
	.word	0
	.word	255
	.word	0
	.align	2
	.type	greenInterlacing, %object
	.size	greenInterlacing, 60
greenInterlacing:
	.word	0
	.word	255
	.word	255
	.word	0
	.word	255
	.word	0
	.word	0
	.word	255
	.word	0
	.word	0
	.word	255
	.word	0
	.word	255
	.word	255
	.word	0
	.align	2
	.type	redInterlacing, %object
	.size	redInterlacing, 60
redInterlacing:
	.word	0
	.word	255
	.word	0
	.word	255
	.word	255
	.word	0
	.word	255
	.word	255
	.word	0
	.word	255
	.word	0
	.word	0
	.word	255
	.word	0
	.word	0
	.global	__aeabi_i2d
	.global	__aeabi_d2uiz
	.text
	.align	2
	.global	PerformYUV2RGBConversion
	.type	PerformYUV2RGBConversion, %function
PerformYUV2RGBConversion:
	@ args = 0, pretend = 0, frame = 96
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #100
	ldrb	r3, [r1, #50]	@ zero_extendqisi2
	ldr	r2, [r0, #0]
	cmp	r3, #0
	str	r2, [sp, #76]
	ldmib	r0, {r2, r3}	@ phole ldm
	str	r3, [sp, #68]
	str	r2, [sp, #72]
	ldreq	r3, [r1, #0]
	ldreq	r2, [r1, #8]
	ldrne	r2, [r1, #20]
	ldrne	r3, [r1, #12]
	ldreq	r1, [r1, #4]
	ldrne	r1, [r1, #16]
	streq	r2, [sp, #56]
	str	r1, [sp, #60]
	add	r0, r0, #32
	ldmia	r0, {r0, r1}	@ phole ldm
	strne	r2, [sp, #56]
	mov	r2, #0
	streq	r3, [sp, #64]
	strne	r3, [sp, #64]
	mov	r3, r0, asr #1
	cmp	r2, r1
	str	r1, [sp, #48]
	str	r0, [sp, #52]
	str	r2, [sp, #92]
	str	r3, [sp, #84]
	bge	.L13
	str	r2, [sp, #4]
.L11:
	ldr	r1, [sp, #92]
	mov	r2, #0
	str	r2, [sp, #88]
	mov	r3, r1, asr #1
	ldr	r1, [sp, #84]
	cmp	r2, r1
	mul	r3, r1, r3
	bge	.L15
	ldr	r2, [sp, #68]
	ldr	r1, [sp, #72]
	ldr	r8, [sp, #4]
	add	r2, r3, r2
	add	r3, r3, r1
	str	r2, [sp, #8]
	str	r3, [sp, #12]
.L10:
	ldr	r3, [sp, #88]
	ldr	r2, [sp, #8]
	ldr	r1, [sp, #76]
	ldrb	r9, [r2, r3]	@ zero_extendqisi2
	ldrb	r5, [r8, r1]	@ zero_extendqisi2
	ldr	r2, [sp, #12]
	sub	r9, r9, #128
	add	r1, r8, #1
	add	r4, r9, r9, asl #1
	rsb	r5, r5, r5, asl #8
	rsb	sl, r4, r4, asl #3
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	add	sl, sl, sl, asl #4
	add	r0, r5, sl
	ldr	r2, [sp, #76]
	add	r0, r0, #128
	sub	r6, r3, #128
	mov	r0, r0, asr #8
	str	r1, [sp, #80]
	ldrb	fp, [r2, r1]	@ zero_extendqisi2
	bl	__aeabi_i2d
	add	r7, r6, r6, asl #2
	add	r9, r9, r4, asl #2
	add	r7, r6, r7, asl #1
	rsb	r9, r9, r9, asl #3
	mov	r7, r7, asl #3
	mov	r9, r9, asl #1
	rsb	fp, fp, fp, asl #8
	add	sl, fp, sl
	add	sl, sl, #128
	mov	sl, sl, asr #8
	strd	r0, [sp, #40]
	rsb	r0, r7, r5
	rsb	r0, r9, r0
	add	r0, r0, #128
	rsb	r7, r7, fp
	mov	r0, r0, asr #8
	bl	__aeabi_i2d
	rsb	r3, r6, r6, asl #3
	rsb	r7, r9, r7
	add	r3, r6, r3, asl #4
	add	r7, r7, #128
	mov	r3, r3, asl #2
	add	r5, r5, r3
	add	r5, r5, #128
	str	r3, [sp, #28]
	mov	r5, r5, asr #8
	mov	r7, r7, asr #8
	strd	r0, [sp, #32]
	ldr	r1, [sp, #88]
	mov	r0, r5
	add	r1, r1, #1
	str	r1, [sp, #88]
	bl	__aeabi_i2d
	mov	r5, r1
	mov	r4, r0
	ldrd	r0, [sp, #40]
	bl	__aeabi_d2uiz
	ldr	r2, [sp, #64]
	strb	r0, [r8, r2]
	ldrd	r0, [sp, #32]
	bl	__aeabi_d2uiz
	ldr	r3, [sp, #60]
	strb	r0, [r8, r3]
	mov	r1, r5
	mov	r0, r4
	bl	__aeabi_d2uiz
	ldr	r1, [sp, #56]
	strb	r0, [r8, r1]
	mov	r0, sl
	bl	__aeabi_i2d
	add	r8, r8, #2
	strd	r0, [sp, #16]
	mov	r0, r7
	bl	__aeabi_i2d
	ldr	r2, [sp, #28]
	add	sl, fp, r2
	mov	r7, r1
	mov	r6, r0
	add	r0, sl, #128
	mov	r0, r0, asr #8
	bl	__aeabi_i2d
	mov	r5, r1
	mov	r4, r0
	ldrd	r0, [sp, #16]
	bl	__aeabi_d2uiz
	ldr	r3, [sp, #64]
	ldr	r1, [sp, #80]
	strb	r0, [r3, r1]
	mov	r1, r7
	mov	r0, r6
	bl	__aeabi_d2uiz
	ldr	r2, [sp, #60]
	ldr	r3, [sp, #80]
	strb	r0, [r2, r3]
	mov	r1, r5
	mov	r0, r4
	bl	__aeabi_d2uiz
	ldr	r1, [sp, #88]
	ldr	r2, [sp, #84]
	ldr	r3, [sp, #56]
	cmp	r1, r2
	ldr	r1, [sp, #80]
	strb	r0, [r3, r1]
	blt	.L10
.L15:
	ldr	r2, [sp, #92]
	ldr	r3, [sp, #48]
	add	r2, r2, #1
	ldr	r1, [sp, #4]
	str	r2, [sp, #92]
	cmp	r2, r3
	ldr	r2, [sp, #52]
	add	r1, r1, r2
	str	r1, [sp, #4]
	blt	.L11
.L13:
	add	sp, sp, #100
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
	.size	PerformYUV2RGBConversion, .-PerformYUV2RGBConversion
	.align	2
	.global	StoreYUV
	.type	StoreYUV, %function
StoreYUV:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, lr}
	ldrb	r3, [r1, #50]	@ zero_extendqisi2
	ldr	r2, [r0, #36]
	ldr	lr, [r0, #0]
	cmp	r3, #0
	ldr	r3, [r0, #32]
	ldreq	ip, [r1, #0]
	ldrne	ip, [r1, #12]
	mul	r4, r2, r3
	ldreq	r5, [r1, #4]
	ldrne	r5, [r1, #16]
	ldr	r7, [r0, #4]
	ldreq	r6, [r1, #8]
	ldrne	r6, [r1, #20]
	ldr	r8, [r0, #8]
	mov	r1, lr
	mov	r0, ip
	mov	r2, r4
	mov	r4, r4, asr #2
	bl	memcpy
	mov	r1, r7
	mov	r2, r4
	mov	r0, r5
	bl	memcpy
	mov	r0, r6
	mov	r1, r8
	mov	r2, r4
	ldmfd	sp!, {r4, r5, r6, r7, r8, lr}
	b	memcpy
	.size	StoreYUV, .-StoreYUV
	.align	2
	.global	interlaceSlanted
	.type	interlaceSlanted, %function
interlaceSlanted:
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #52
	ldr	r3, [r0, #1400]
	mov	r1, #0
	str	r1, [sp, #44]
	ldr	r2, [r3, #44]
	ldr	ip, [r3, #40]
	cmp	r1, r2
	mov	r9, r1
	str	r2, [sp, #36]
	ldmia	r3, {r1, r2}	@ phole ldm
	str	ip, [sp, #40]
	ldr	ip, [r3, #8]
	str	r1, [sp, #32]
	str	r2, [sp, #28]
	str	ip, [sp, #24]
	add	r1, r3, #12
	ldmia	r1, {r1, r2, ip}	@ phole ldm
	mov	r5, r0
	ldr	fp, [r3, #36]
	str	r1, [sp, #20]
	str	r2, [sp, #16]
	str	ip, [sp, #12]
	ldr	r8, [r3, #24]
	ldr	r7, [r3, #28]
	ldr	r6, [r3, #32]
	bge	.L55
.L59:
	add	r1, sp, #40
	ldmia	r1, {r1, r4}	@ phole ldm
	cmp	r1, #0
	mul	r4, r1, r4
	ble	.L57
	mov	sl, r1
.L52:
	ldr	r2, [r5, #1416]
	ldr	r0, [r5, #1420]
	ldr	r3, [sp, #28]
	ldrb	r2, [r2, r4]	@ zero_extendqisi2
	ldr	ip, [r5, #1424]
	str	r2, [sp, #4]
	ldr	r2, [sp, #32]
	ldrb	r1, [ip, r4]	@ zero_extendqisi2
	ldrb	lr, [r2, r4]	@ zero_extendqisi2
	ldrb	r2, [r0, r4]	@ zero_extendqisi2
	ldrb	r0, [r3, r4]	@ zero_extendqisi2
	ldr	r3, [sp, #24]
	add	r2, r2, r0
	ldrb	ip, [r3, r4]	@ zero_extendqisi2
	ldr	r3, [sp, #4]
	sub	r2, r2, #255
	add	lr, r3, lr
	sub	r3, lr, #255
	add	r1, r1, ip
	cmp	r3, #255
	sub	r1, r1, #255
	movgt	r3, #255
	bgt	.L29
	cmp	r3, #0
	uxtbge	r3, r3
	movlt	r3, #0
.L29:
	cmp	r2, #255
	movgt	r2, #255
	bgt	.L33
	cmp	r2, #0
	uxtbge	r2, r2
	movlt	r2, #0
.L33:
	cmp	r1, #255
	movgt	r1, #255
	bgt	.L37
	cmp	r1, #0
	uxtbge	r1, r1
	movlt	r1, #0
.L37:
	strb	r3, [r8, r4]
	strb	r2, [r7, r4]
	strb	r1, [r6, r4]
	ldr	r2, [r5, #1428]
	ldr	r0, [r5, #1432]
	ldr	r3, [sp, #16]
	ldrb	r2, [r2, r4]	@ zero_extendqisi2
	ldr	r1, [sp, #20]
	ldr	ip, [r5, #1436]
	str	r2, [sp, #4]
	ldrb	r2, [r0, r4]	@ zero_extendqisi2
	ldrb	r0, [r3, r4]	@ zero_extendqisi2
	ldr	r3, [sp, #12]
	ldrb	lr, [r1, r4]	@ zero_extendqisi2
	ldrb	r1, [ip, r4]	@ zero_extendqisi2
	ldrb	ip, [r3, r4]	@ zero_extendqisi2
	ldr	r3, [sp, #4]
	add	r2, r2, r0
	add	lr, r3, lr
	sub	r3, lr, #255
	add	r1, r1, ip
	cmp	r3, #255
	sub	r2, r2, #255
	sub	r1, r1, #255
	movgt	r3, #255
	bgt	.L41
	cmp	r3, #0
	uxtbge	r3, r3
	movlt	r3, #0
.L41:
	cmp	r2, #255
	movgt	ip, #255
	bgt	.L45
	cmp	r2, #0
	uxtbge	ip, r2
	movlt	ip, #0
.L45:
	cmp	r1, #255
	movgt	r0, #255
	bgt	.L49
	cmp	r1, #0
	uxtbge	r0, r1
	movlt	r0, #0
.L49:
	ldrb	r2, [r8, r4]	@ zero_extendqisi2
	add	r1, fp, r9
	subs	sl, sl, #1
	add	r2, r2, r3
	strb	r2, [r8, r4]
	ldrb	r3, [r7, r4]	@ zero_extendqisi2
	add	r3, r3, ip
	strb	r3, [r7, r4]
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	add	r2, r2, r0
	strb	r2, [r6, r4]
	ldrb	r3, [r8, r4]	@ zero_extendqisi2
	strb	r3, [fp, r9]
	ldrb	r2, [r7, r4]	@ zero_extendqisi2
	add	r9, r9, #3
	strb	r2, [r1, #1]
	ldrb	r3, [r6, r4]	@ zero_extendqisi2
	add	r4, r4, #1
	strb	r3, [r1, #2]
	bne	.L52
.L57:
	ldr	ip, [sp, #44]
	ldr	r1, [sp, #36]
	add	ip, ip, #1
	str	ip, [sp, #44]
	cmp	ip, r1
	blt	.L59
.L55:
	add	sp, sp, #52
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
	.size	interlaceSlanted, .-interlaceSlanted
	.align	2
	.global	interlaceSlantedFast
	.type	interlaceSlantedFast, %function
interlaceSlantedFast:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #36
	ldr	r3, [r0, #1400]
	mov	r4, r1
	mov	lr, #0
	ldr	r5, [r3, #20]
	add	r1, r3, #40
	ldmia	r1, {r1, r2}	@ phole ldm
	str	r5, [sp, #12]
	ldr	r5, [r0, #1436]
	mul	fp, r2, r1
	str	r5, [sp, #8]
	ldmia	r3, {r2, r5}	@ phole ldm
	str	r2, [sp, #28]
	str	r5, [sp, #24]
	add	r2, r3, #8
	ldmia	r2, {r2, r5}	@ phole ldm
	ldr	sl, [r0, #1416]
	ldr	r8, [r0, #1420]
	ldr	r7, [r0, #1424]
	ldr	r6, [r0, #1428]
	ldr	r0, [r0, #1432]
	cmp	lr, fp
	mov	ip, lr
	str	r2, [sp, #20]
	str	r5, [sp, #16]
	ldr	r9, [r3, #16]
	str	r0, [sp, #4]
	bge	.L66
.L68:
	ldr	r3, [sp, #28]
	ldr	r5, [sp, #16]
	ldrb	r2, [sl, ip]	@ zero_extendqisi2
	ldrb	r0, [r3, ip]	@ zero_extendqisi2
	ldrb	r1, [r5, ip]	@ zero_extendqisi2
	ldrb	r3, [r6, ip]	@ zero_extendqisi2
	and	r2, r2, r0
	and	r3, r3, r1
	add	r2, r2, r3
	strb	r2, [lr, r4]
	ldr	r0, [sp, #24]
	ldr	r5, [sp, #4]
	ldrb	r1, [r8, ip]	@ zero_extendqisi2
	ldrb	r2, [r0, ip]	@ zero_extendqisi2
	ldrb	r3, [r5, ip]	@ zero_extendqisi2
	ldrb	r0, [r9, ip]	@ zero_extendqisi2
	and	r1, r1, r2
	add	lr, lr, #1
	and	r3, r3, r0
	add	r1, r1, r3
	strb	r1, [lr, r4]
	ldr	r5, [sp, #8]
	ldr	r0, [sp, #20]
	ldrb	r2, [r7, ip]	@ zero_extendqisi2
	ldrb	r3, [r5, ip]	@ zero_extendqisi2
	ldr	r5, [sp, #12]
	ldrb	r1, [r0, ip]	@ zero_extendqisi2
	add	lr, lr, #1
	ldrb	r0, [r5, ip]	@ zero_extendqisi2
	and	r2, r2, r1
	add	ip, ip, #1
	and	r3, r3, r0
	add	r2, r2, r3
	strb	r2, [lr, r4]
	cmp	ip, fp
	add	lr, lr, #1
	blt	.L68
.L66:
	add	sp, sp, #36
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
	.size	interlaceSlantedFast, .-interlaceSlantedFast
	.align	2
	.global	interlaceSlantedFastPlusRGB
	.type	interlaceSlantedFastPlusRGB, %function
interlaceSlantedFastPlusRGB:
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	mov	fp, r1
	ldr	r3, [r0, #1400]
	sub	sp, sp, #68
	mov	r8, #0
	ldr	r1, [r3, #40]
	ldr	r0, [r3, #44]
	ldr	r2, [r3, #0]
	ldr	r4, [r3, #12]
	ldr	sl, [r3, #4]
	ldr	ip, [r3, #16]
	ldr	lr, [r3, #8]
	ldr	r3, [r3, #20]
	str	r0, [sp, #20]
	cmp	r8, r0
	mov	r0, r1, asr #1
	str	r8, [sp, #60]
	str	r1, [sp, #24]
	str	r2, [sp, #48]
	str	r4, [sp, #44]
	str	sl, [sp, #40]
	str	ip, [sp, #36]
	str	lr, [sp, #32]
	str	r3, [sp, #28]
	str	r0, [sp, #52]
	bge	.L103
	str	r8, [sp, #4]
	str	r8, [sp, #0]
.L101:
	ldr	r1, [sp, #60]
	ldr	sl, [sp, #52]
	ldr	r4, [sp, #24]
	mov	r3, r1, asr #1
	mov	r2, #0
	mul	sl, r3, sl
	cmp	r2, r4
	str	r2, [sp, #56]
	str	sl, [sp, #16]
	bge	.L105
.L113:
	ldr	lr, [sp, #56]
	ldr	ip, [sp, #4]
	ldr	r3, .L114
	add	r1, ip, lr
	ldr	r2, [sp, #0]
	ldr	sl, [sp, #48]
	add	r0, r2, lr
	smull	r4, r2, r3, r1
	ldr	lr, [sp, #44]
	add	r2, r2, r1
	mov	r3, r1, asr #31
	rsb	r7, r3, r2, asr #3
	ldrb	r5, [sl, r0]	@ zero_extendqisi2
	add	r2, sl, r0
	ldr	r4, [sp, #56]
	ldr	sl, [sp, #44]
	rsb	r3, r7, r7, asl #3
	sub	r7, r1, r3, asl #1
	add	ip, lr, r0
	ldr	r1, [sp, #16]
	ldrb	lr, [ip, #1]	@ zero_extendqisi2
	add	r3, r1, r4, asr #1
	ldr	ip, [sp, #32]
	ldrb	r1, [r2, #1]	@ zero_extendqisi2
	ldrb	r2, [sl, r0]	@ zero_extendqisi2
	ldr	sl, [sp, #40]
	ldrb	r6, [ip, r3]	@ zero_extendqisi2
	ldr	r4, [sp, #36]
	ldrb	ip, [sl, r3]	@ zero_extendqisi2
	ldr	sl, [sp, #28]
	ldrb	r0, [r4, r3]	@ zero_extendqisi2
	sub	r6, r6, #128
	ldrb	r4, [sl, r3]	@ zero_extendqisi2
	ldr	sl, .L114+4
	rsb	r1, r1, r1, asl #8
	sub	r4, r4, #128
	ldr	r3, [sl, r7, asl #2]
	str	r1, [sp, #8]
	cmp	r3, #0
	addne	r3, r4, r4, asl #1
	addeq	r3, r6, r6, asl #1
	rsbne	r3, r3, r3, asl #3
	rsbeq	r3, r3, r3, asl #3
	rsb	r1, r2, r2, asl #8
	rsb	r5, r5, r5, asl #8
	addne	r3, r3, r3, asl #4
	addeq	r3, r3, r3, asl #4
	rsb	lr, lr, lr, asl #8
	str	lr, [sp, #12]
	addne	r3, r3, r1
	addeq	r3, r3, r5
	ldr	lr, .L114+8
	add	r3, r3, #128
	sub	r0, r0, #128
	mov	r9, r3, asr #8
	ldr	r3, [lr, r7, asl #2]
	sub	ip, ip, #128
	cmp	r3, #0
	addne	r3, r0, r0, asl #2
	addne	r2, r4, r4, asl #1
	addeq	r3, ip, ip, asl #2
	addeq	r2, r6, r6, asl #1
	addne	r3, r0, r3, asl #1
	addne	r2, r4, r2, asl #2
	addeq	r3, ip, r3, asl #1
	addeq	r2, r6, r2, asl #2
	subne	r3, r1, r3, asl #3
	subeq	r3, r5, r3, asl #3
	rsb	r2, r2, r2, asl #3
	sub	r3, r3, r2, asl #1
	ldr	lr, .L114+12
	mov	r2, r7
	add	r3, r3, #128
	add	r7, r7, #1
	mov	sl, r3, asr #8
	ldr	r3, [lr, r2, asl #2]
	cmp	r3, #0
	rsbne	r3, r0, r0, asl #3
	rsbeq	r3, ip, ip, asl #3
	addne	r3, r0, r3, asl #4
	addeq	r3, ip, r3, asl #4
	addne	r3, r1, r3, asl #2
	addeq	r3, r5, r3, asl #2
	ldr	r1, .L114+4
	add	r3, r3, #128
	mov	lr, r3, asr #8
	ldr	r3, [r1, r7, asl #2]
	cmp	r3, #0
	addne	r3, r4, r4, asl #1
	addeq	r3, r6, r6, asl #1
	rsbne	r3, r3, r3, asl #3
	rsbeq	r3, r3, r3, asl #3
	ldrne	r2, [sp, #12]
	ldreq	r1, [sp, #8]
	addne	r3, r3, r3, asl #4
	addeq	r3, r3, r3, asl #4
	addne	r3, r3, r2
	addeq	r3, r3, r1
	ldr	r2, .L114+8
	add	r3, r3, #128
	mov	r1, r3, asr #8
	ldr	r3, [r2, r7, asl #2]
	cmp	r3, #0
	addne	r2, r4, r4, asl #1
	addne	r3, r0, r0, asl #2
	addne	r2, r4, r2, asl #2
	addeq	r3, ip, ip, asl #2
	ldrne	r4, [sp, #12]
	ldreq	r4, [sp, #8]
	addeq	r2, r6, r6, asl #1
	addne	r3, r0, r3, asl #1
	addeq	r3, ip, r3, asl #1
	addeq	r2, r6, r2, asl #2
	sub	r3, r4, r3, asl #3
	rsb	r2, r2, r2, asl #3
	sub	r3, r3, r2, asl #1
	ldr	r2, .L114+12
	add	r3, r3, #128
	mov	r4, r3, asr #8
	ldr	r3, [r2, r7, asl #2]
	add	r2, r8, fp
	cmp	r3, #0
	rsbne	r3, r0, r0, asl #3
	rsbeq	r3, ip, ip, asl #3
	addne	r3, r0, r3, asl #4
	ldreq	r0, [sp, #8]
	ldrne	ip, [sp, #12]
	addeq	r3, ip, r3, asl #4
	addne	r3, ip, r3, asl #2
	addeq	r3, r0, r3, asl #2
	add	r3, r3, #128
	cmp	r9, #0
	mov	r0, r3, asr #8
	add	r8, r8, #1
	movge	r3, r9
	movlt	r3, #0
	strb	r3, [r2, #0]
	cmp	sl, #0
	add	r2, r8, fp
	movge	r3, sl
	movlt	r3, #0
	add	r8, r8, #1
	strb	r3, [r2, #0]
	cmp	lr, #0
	add	r2, r8, fp
	movge	r3, lr
	movlt	r3, #0
	add	r8, r8, #1
	strb	r3, [r2, #0]
	cmp	r1, #0
	add	r2, r8, fp
	movge	r3, r1
	movlt	r3, #0
	add	r8, r8, #1
	strb	r3, [r2, #0]
	cmp	r4, #0
	add	r2, r8, fp
	movge	r3, r4
	movlt	r3, #0
	strb	r3, [r2, #0]
	ldr	r1, [sp, #56]
	add	r8, r8, #1
	cmp	r0, #0
	add	r2, r8, fp
	ldr	r3, [sp, #24]
	movlt	r0, #0
	add	r1, r1, #2
	str	r1, [sp, #56]
	add	r8, r8, #1
	cmp	r1, r3
	strb	r0, [r2, #0]
	blt	.L113
.L105:
	ldr	r4, [sp, #60]
	ldr	ip, [sp, #0]
	ldr	r0, [sp, #4]
	add	sl, sp, #20
	ldmia	sl, {sl, lr}	@ phole ldm
	add	r4, r4, #1
	add	ip, ip, lr
	add	r0, r0, #5
	cmp	r4, sl
	str	r4, [sp, #60]
	str	ip, [sp, #0]
	str	r0, [sp, #4]
	blt	.L101
.L103:
	add	sp, sp, #68
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
.L115:
	.align	2
.L114:
	.word	-1840700269
	.word	redInterlacing
	.word	greenInterlacing
	.word	blueInterlacing
	.size	interlaceSlantedFastPlusRGB, .-interlaceSlantedFastPlusRGB
	.align	2
	.global	interlaceParalaxFast
	.type	interlaceParalaxFast, %function
interlaceParalaxFast:
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #76
	ldr	r3, [r0, #1400]
	str	r1, [sp, #68]
	mov	fp, #0
	ldr	r1, [r3, #40]
	ldr	r0, [r3, #44]
	ldr	r2, [r3, #0]
	ldr	r4, [r3, #12]
	ldr	r7, [r3, #4]
	ldr	r8, [r3, #16]
	ldr	r9, [r3, #8]
	ldr	r3, [r3, #20]
	str	r0, [sp, #24]
	cmp	fp, r0
	mov	r0, r1, asr #1
	str	fp, [sp, #64]
	str	r1, [sp, #28]
	str	r2, [sp, #52]
	str	r4, [sp, #48]
	str	r7, [sp, #44]
	str	r8, [sp, #40]
	str	r9, [sp, #36]
	str	r3, [sp, #32]
	str	r0, [sp, #56]
	bge	.L138
	str	fp, [sp, #4]
.L136:
	ldr	r1, [sp, #64]
	ldr	r4, [sp, #56]
	ldr	r3, [sp, #28]
	mov	ip, r1, asr #1
	mov	r2, #0
	mul	r4, ip, r4
	cmp	r2, r3
	str	r2, [sp, #60]
	str	r4, [sp, #20]
	bge	.L140
.L142:
	ldr	r8, [sp, #60]
	ldr	r7, [sp, #20]
	ldr	r9, [sp, #4]
	ldr	r0, [sp, #32]
	ldr	r1, [sp, #48]
	add	ip, r7, r8, asr #1
	add	r4, sp, #36
	ldmia	r4, {r4, r7}	@ phole ldm
	add	r3, r9, r8
	ldr	r8, [sp, #44]
	ldrb	lr, [r0, ip]	@ zero_extendqisi2
	ldr	r9, [sp, #52]
	add	r2, r1, r3
	ldrb	r0, [r7, ip]	@ zero_extendqisi2
	ldrb	r1, [r4, ip]	@ zero_extendqisi2
	ldrb	r6, [r2, #1]	@ zero_extendqisi2
	ldrb	ip, [r8, ip]	@ zero_extendqisi2
	add	r2, r9, r3
	ldr	r8, [sp, #48]
	sub	lr, lr, #128
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	ldrb	r5, [r9, r3]	@ zero_extendqisi2
	ldrb	r4, [r8, r3]	@ zero_extendqisi2
	add	r7, lr, lr, asl #1
	sub	r0, r0, #128
	sub	ip, ip, #128
	sub	r1, r1, #128
	str	r2, [sp, #16]
	rsb	r2, r7, r7, asl #3
	rsb	r9, r0, r0, asl #3
	add	r3, r1, r1, asl #1
	add	r8, ip, ip, asl #2
	str	r9, [sp, #8]
	rsb	r4, r4, r4, asl #8
	rsb	r9, ip, ip, asl #3
	rsb	r5, r5, r5, asl #8
	add	r2, r2, r2, asl #4
	add	r8, ip, r8, asl #1
	add	r1, r1, r3, asl #2
	add	r2, r2, r4
	add	lr, lr, r7, asl #2
	sub	r5, r5, r8, asl #3
	ldr	r7, [sp, #8]
	ldr	r8, [sp, #16]
	add	ip, ip, r9, asl #4
	add	r2, r2, #128
	ldr	r9, [sp, #68]
	add	sl, r0, r0, asl #2
	rsb	r1, r1, r1, asl #3
	movs	r2, r2, asr #8
	sub	r5, r5, r1, asl #1
	add	r1, fp, r9
	rsb	r8, r8, r8, asl #8
	movmi	r2, #0
	add	sl, r0, sl, asl #1
	add	r0, r0, r7, asl #4
	str	r8, [sp, #12]
	add	r5, r5, #128
	strb	r2, [r1, #0]
	add	r4, r4, r0, asl #2
	ldr	r0, [sp, #68]
	mov	r5, r5, asr #8
	add	fp, fp, #1
	add	r2, fp, r0
	cmp	r5, #0
	movlt	r5, #0
	strb	r5, [r2, #0]
	add	r4, r4, #128
	ldr	r1, [sp, #68]
	rsb	r3, r3, r3, asl #3
	mov	r4, r4, asr #8
	add	fp, fp, #1
	cmp	r4, #0
	add	r2, fp, r1
	add	r3, r3, r3, asl #4
	movlt	r4, #0
	add	r3, r3, r8
	strb	r4, [r2, #0]
	rsb	r6, r6, r6, asl #8
	add	r3, r3, #128
	ldr	r4, [sp, #68]
	mov	r3, r3, asr #8
	add	fp, fp, #1
	sub	r6, r6, sl, asl #3
	cmp	r3, #0
	add	r2, fp, r4
	rsb	lr, lr, lr, asl #3
	movlt	r3, #0
	sub	r6, r6, lr, asl #1
	strb	r3, [r2, #0]
	add	r6, r6, #128
	ldr	r7, [sp, #68]
	mov	r6, r6, asr #8
	add	fp, fp, #1
	add	r3, fp, r7
	cmp	r6, #0
	movlt	r6, #0
	strb	r6, [r3, #0]
	add	ip, r8, ip, asl #2
	ldr	r9, [sp, #60]
	add	ip, ip, #128
	ldr	r8, [sp, #68]
	mov	ip, ip, asr #8
	add	fp, fp, #1
	add	r9, r9, #2
	cmp	ip, #0
	add	r3, fp, r8
	str	r9, [sp, #60]
	ldr	r0, [sp, #28]
	movlt	ip, #0
	add	fp, fp, #1
	cmp	r9, r0
	strb	ip, [r3, #0]
	blt	.L142
.L140:
	ldr	r1, [sp, #64]
	ldr	r3, [sp, #4]
	add	r2, sp, #24
	ldmia	r2, {r2, r4}	@ phole ldm
	add	r1, r1, #1
	add	r3, r3, r4
	cmp	r1, r2
	str	r1, [sp, #64]
	str	r3, [sp, #4]
	blt	.L136
.L138:
	add	sp, sp, #76
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
	.size	interlaceParalaxFast, .-interlaceParalaxFast
	.align	2
	.global	interlaceParalaxFastScale
	.type	interlaceParalaxFastScale, %function
interlaceParalaxFastScale:
	@ args = 0, pretend = 0, frame = 104
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #108
	ldr	r3, [r0, #1400]
	mov	r2, #0
	str	r1, [sp, #100]
	ldr	r5, [r3, #40]
	ldr	r4, [r3, #44]
	ldr	r6, [r3, #0]
	ldr	ip, [r3, #12]
	ldr	lr, [r3, #4]
	ldr	r0, [r3, #16]
	ldr	r1, [r3, #8]
	ldr	r3, [r3, #20]
	str	r2, [sp, #92]
	str	r2, [sp, #96]
	cmp	r2, r4
	mov	r2, r5, asr #1
	str	r4, [sp, #52]
	str	r5, [sp, #56]
	str	r6, [sp, #80]
	str	ip, [sp, #76]
	str	lr, [sp, #72]
	str	r0, [sp, #68]
	str	r1, [sp, #64]
	str	r3, [sp, #60]
	str	r2, [sp, #84]
	bge	.L177
.L183:
	ldr	r4, [sp, #56]
	ldr	r3, [sp, #92]
	ldr	r5, [sp, #92]
	ldr	ip, [sp, #84]
	mul	r3, r4, r3
	add	r2, r5, r5, asl #1
	mov	r1, r5, asr #1
	ldr	lr, [sp, #100]
	mov	r2, r2, asl #2
	mul	ip, r1, ip
	mov	r6, #0
	add	r3, r3, r3, asl #1
	add	r2, r2, #6
	mov	fp, lr
	cmp	r6, r4
	str	r6, [sp, #88]
	str	ip, [sp, #48]
	add	r7, lr, r3, asl #2
	mla	fp, r4, r2, fp
	bge	.L179
.L182:
	ldr	ip, [sp, #96]
	ldr	r6, [sp, #80]
	ldr	r2, [sp, #48]
	ldr	r1, [sp, #60]
	ldrb	r6, [r6, ip]	@ zero_extendqisi2
	add	r3, sp, #64
	ldmia	r3, {r3, r4, r5, lr}	@ phole ldm
	ldrb	r0, [r1, r2]	@ zero_extendqisi2
	ldrb	r1, [r2, r3]	@ zero_extendqisi2
	ldrb	r3, [r4, r2]	@ zero_extendqisi2
	ldrb	r2, [r5, r2]	@ zero_extendqisi2
	str	r6, [sp, #24]
	ldrb	lr, [ip, lr]	@ zero_extendqisi2
	ldr	r6, [sp, #80]
	add	ip, ip, #1
	str	lr, [sp, #20]
	ldr	lr, [sp, #76]
	str	ip, [sp, #96]
	ldrb	r8, [r6, ip]	@ zero_extendqisi2
	ldrb	r9, [ip, lr]	@ zero_extendqisi2
	rsb	r6, r2, r2, asl #3
	add	ip, r2, r2, asl #2
	add	lr, r3, r3, asl #2
	add	ip, r2, ip, asl #1
	add	r2, r2, r6, asl #4
	ldr	r6, [sp, #24]
	add	lr, r3, lr, asl #1
	add	r5, r0, r0, asl #1
	mov	r6, r6, asl #8
	str	r6, [sp, #40]
	ldr	r6, [sp, #20]
	add	r4, r1, r1, asl #1
	mov	r9, r9, asl #8
	mov	r6, r6, asl #8
	mov	lr, lr, asl #3
	str	r6, [sp, #44]
	str	r9, [sp, #36]
	add	r0, r0, r5, asl #2
	rsb	r9, lr, r9
	rsb	r5, r5, r5, asl #3
	rsb	lr, lr, r6
	str	lr, [sp, #8]
	add	r1, r1, r4, asl #2
	ldr	lr, [sp, #44]
	rsb	sl, r3, r3, asl #3
	add	r5, r5, r5, asl #4
	add	r3, r3, sl, asl #4
	rsb	r1, r1, r1, asl #3
	add	sl, r5, lr
	ldr	lr, [sp, #40]
	mov	r8, r8, asl #8
	mov	ip, ip, asl #3
	mov	r1, r1, asl #1
	rsb	r6, ip, r8
	rsb	r0, r0, r0, asl #3
	rsb	ip, ip, lr
	rsb	r6, r1, r6
	rsb	ip, r1, ip
	ldr	r1, [sp, #8]
	mov	r0, r0, asl #1
	rsb	r9, r0, r9
	rsb	lr, r0, r1
	ldr	r0, [sp, #40]
	mov	r2, r2, asl #2
	str	r9, [sp, #16]
	add	r9, r2, r8
	add	r2, r2, r0
	ldr	r0, [sp, #36]
	mov	r3, r3, asl #2
	add	r1, r3, r0
	ldr	r0, [sp, #44]
	rsb	r4, r4, r4, asl #3
	add	r3, r3, r0
	ldr	r0, [sp, #36]
	add	r4, r4, r4, asl #4
	add	r5, r5, r0
	str	r5, [sp, #4]
	ldr	r5, [sp, #16]
	add	r8, r4, r8
	add	r0, r5, #34560
	ldr	r5, [sp, #40]
	sub	r3, r3, #57600
	add	r4, r4, r5
	sub	r4, r4, #45568
	str	r4, [sp, #12]
	ldr	r4, [sp, #4]
	sub	r3, r3, #128
	sub	r5, r4, #45568
	ldr	r4, [sp, #48]
	mov	r3, r3, asr #8
	add	r4, r4, #1
	str	r3, [sp, #32]
	str	r4, [sp, #48]
	ldr	r3, [sp, #12]
	ldr	r4, [sp, #96]
	sub	sl, sl, #45568
	add	r0, r0, #128
	mov	sl, sl, asr #8
	add	r4, r4, #1
	mov	r0, r0, asr #8
	str	r0, [sp, #28]
	str	r4, [sp, #96]
	cmp	sl, #0
	mov	r4, r3, asr #8
	mov	r0, r7
	mov	r3, fp
	add	ip, ip, #34560
	movle	sl, #0
	add	ip, ip, #128
	strb	sl, [r3, #0]
	strb	sl, [r0, #0]
	ldr	r3, [sp, #32]
	mov	ip, ip, asr #8
	cmp	ip, #0
	add	fp, fp, #1
	add	r7, r7, #1
	movle	ip, #0
	mov	sl, fp
	cmp	r3, #0
	mov	r0, r7
	strb	ip, [sl, #0]
	add	fp, fp, #1
	strb	ip, [r0, #0]
	add	r7, r7, #1
	ldrgt	ip, [sp, #32]
	mov	r0, r7
	mov	sl, fp
	add	lr, lr, #34560
	movgt	r3, ip
	movle	r3, #0
	add	fp, fp, #1
	add	r7, r7, #1
	add	lr, lr, #128
	strb	r3, [sl, #0]
	cmp	r4, #0
	strb	r3, [r0, #0]
	sub	r2, r2, #57600
	mov	r0, fp
	mov	r3, r7
	mov	lr, lr, asr #8
	movle	r4, #0
	add	fp, fp, #1
	add	r7, r7, #1
	sub	r2, r2, #128
	strb	r4, [r0, #0]
	cmp	lr, #0
	strb	r4, [r3, #0]
	mov	r0, fp
	mov	r3, r7
	mov	r2, r2, asr #8
	movle	lr, #0
	add	fp, fp, #1
	add	r7, r7, #1
	strb	lr, [r0, #0]
	cmp	r2, #0
	strb	lr, [r3, #0]
	mov	r0, fp
	mov	r3, r7
	add	r6, r6, #34560
	mov	r5, r5, asr #8
	movle	r2, #0
	add	fp, fp, #1
	add	r7, r7, #1
	add	r6, r6, #128
	strb	r2, [r0, #0]
	cmp	r5, #0
	strb	r2, [r3, #0]
	sub	r1, r1, #57600
	mov	r2, fp
	mov	r3, r7
	mov	r6, r6, asr #8
	movle	r5, #0
	add	fp, fp, #1
	add	r7, r7, #1
	sub	r1, r1, #128
	strb	r5, [r2, #0]
	cmp	r6, #0
	strb	r5, [r3, #0]
	mov	r2, fp
	mov	r3, r7
	mov	r1, r1, asr #8
	movle	r6, #0
	add	fp, fp, #1
	add	r7, r7, #1
	strb	r6, [r2, #0]
	cmp	r1, #0
	strb	r6, [r3, #0]
	mov	r2, fp
	mov	r3, r7
	movle	r1, #0
	sub	r8, r8, #45568
	strb	r1, [r2, #0]
	strb	r1, [r3, #0]
	mov	r8, r8, asr #8
	ldr	lr, [sp, #28]
	add	fp, fp, #1
	add	r7, r7, #1
	mov	r3, r7
	mov	r2, fp
	cmp	r8, #0
	add	fp, fp, #1
	add	r7, r7, #1
	movle	r8, #0
	mov	r0, r7
	cmp	lr, #0
	mov	ip, fp
	sub	r9, r9, #57600
	strb	r8, [r2, #0]
	sub	r9, r9, #128
	strb	r8, [r3, #0]
	movgt	r3, lr
	movle	r3, #0
	strb	r3, [ip, #0]
	strb	r3, [r0, #0]
	mov	r9, r9, asr #8
	ldr	r0, [sp, #88]
	add	fp, fp, #1
	add	r7, r7, #1
	ldr	r3, [sp, #56]
	mov	r2, fp
	mov	r1, r7
	cmp	r9, #0
	movle	r9, #0
	add	r0, r0, #2
	str	r0, [sp, #88]
	add	fp, fp, #1
	strb	r9, [r2, #0]
	add	r7, r7, #1
	cmp	r0, r3
	strb	r9, [r1, #0]
	blt	.L182
.L179:
	ldr	r4, [sp, #92]
	ldr	r5, [sp, #52]
	add	r4, r4, #1
	str	r4, [sp, #92]
	cmp	r4, r5
	blt	.L183
.L177:
	add	sp, sp, #108
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
	.size	interlaceParalaxFastScale, .-interlaceParalaxFastScale
	.align	2
	.global	interlaceParalaxFastScalePlusOld
	.type	interlaceParalaxFastScalePlusOld, %function
interlaceParalaxFastScalePlusOld:
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #60
	ldr	r3, [r0, #1400]
	mov	r7, r1
	mov	fp, #0
	add	r0, r3, #40
	ldmia	r0, {r0, ip}	@ phole ldm
	str	r0, [sp, #12]
	str	ip, [sp, #8]
	ldr	ip, [sp, #12]
	mov	r0, r0, asl #1
	add	r1, r0, ip
	str	r0, [sp, #4]
	ldr	ip, [r2, #8]
	ldr	r0, [sp, #8]
	add	r1, r7, r1, asl #1
	cmp	fp, r0
	str	ip, [sp, #16]
	ldr	r0, [r3, #0]
	str	r1, [sp, #52]
	ldr	ip, [sp, #12]
	ldmib	r3, {r1, r3}	@ phole ldm
	mov	ip, ip, asr #1
	str	r3, [sp, #20]
	ldr	r3, [r2, #0]
	ldr	r2, [r2, #4]
	str	fp, [sp, #48]
	str	r0, [sp, #36]
	str	r1, [sp, #28]
	str	r3, [sp, #32]
	str	r2, [sp, #24]
	str	ip, [sp, #40]
	bge	.L218
.L224:
	ldr	r0, [sp, #48]
	ldr	r2, [sp, #12]
	ldr	r9, [sp, #40]
	mov	r1, #0
	mov	r3, r0, asr #1
	cmp	r1, r2
	str	r1, [sp, #44]
	mul	r9, r3, r9
	bge	.L220
.L223:
	add	r3, sp, #16
	ldmia	r3, {r3, ip}	@ phole ldm
	ldrb	r2, [r9, ip]	@ zero_extendqisi2
	ldrb	r1, [r3, r9]	@ zero_extendqisi2
	add	r3, sp, #24
	ldmia	r3, {r3, ip}	@ phole ldm
	ldrb	lr, [ip, r9]	@ zero_extendqisi2
	add	ip, r2, r2, asl #1
	ldrb	r0, [r3, r9]	@ zero_extendqisi2
	add	r3, r1, r1, asl #1
	add	r2, r2, ip, asl #2
	ldr	ip, [sp, #32]
	add	r1, r1, r3, asl #2
	rsb	r3, r3, r3, asl #3
	ldrb	r6, [fp, ip]	@ zero_extendqisi2
	add	r3, r3, r3, asl #4
	sub	sl, r3, #45568
	rsb	r2, r2, r2, asl #3
	ldr	r3, [sp, #36]
	rsb	r1, r1, r1, asl #3
	rsb	ip, r0, r0, asl #3
	add	r4, lr, lr, asl #2
	mov	r2, r2, asl #1
	mov	r1, r1, asl #1
	add	r5, r0, r0, asl #2
	add	ip, r0, ip, asl #4
	mov	r8, r6, asl #8
	rsb	r2, r2, #0
	ldrb	r6, [r3, fp]	@ zero_extendqisi2
	rsb	r1, r1, #0
	add	lr, lr, r4, asl #1
	add	r0, r0, r5, asl #1
	add	r3, r8, sl
	sub	r1, r1, r0, asl #3
	sub	r2, r2, lr, asl #3
	mov	ip, ip, asl #2
	add	lr, r2, #34560
	add	r4, r1, #34560
	sub	ip, ip, #57600
	movs	r3, r3, asr #8
	mov	r0, r7
	add	r9, r9, #1
	mov	r1, r6, asl #8
	add	fp, fp, #1
	add	lr, lr, #128
	add	r4, r4, #128
	sub	ip, ip, #128
	add	r7, r7, #1
	movmi	r2, #0
	bmi	.L192
	cmp	r3, #255
	movlt	r2, r3
	movge	r2, #255
.L192:
	add	r3, r1, lr
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r0, r7
	movmi	r2, #0
	add	r7, r7, #1
	bmi	.L194
	cmp	r3, #255
	movlt	r2, r3
	movge	r2, #255
.L194:
	add	r3, r8, ip
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r0, r7
	movmi	r2, #0
	add	r7, r7, #1
	bmi	.L196
	cmp	r3, #255
	movlt	r2, r3
	movge	r2, #255
.L196:
	add	r3, r1, sl
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r0, r7
	movmi	r2, #0
	add	r7, r7, #1
	bmi	.L198
	cmp	r3, #255
	movlt	r2, r3
	movge	r2, #255
.L198:
	add	r3, r8, r4
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r0, r7
	movmi	r2, #0
	add	r7, r7, #1
	bmi	.L200
	cmp	r3, #255
	movlt	r2, r3
	movge	r2, #255
.L200:
	add	r3, r1, ip
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r2, r7
	movmi	r3, #0
	add	r7, r7, #1
	bmi	.L202
	cmp	r3, #255
	movge	r3, #255
.L202:
	strb	r3, [r2, #0]
	add	r0, sp, #32
	ldmia	r0, {r0, r2}	@ phole ldm
	ldrb	r3, [fp, r0]	@ zero_extendqisi2
	ldrb	r1, [r2, fp]	@ zero_extendqisi2
	mov	r0, r7
	add	fp, fp, #1
	mov	r8, r3, asl #8
	add	r2, r8, sl
	mov	r1, r1, asl #8
	movs	r2, r2, asr #8
	add	r7, r7, #1
	movmi	r2, #0
	bmi	.L204
	cmp	r2, #255
	movge	r2, #255
.L204:
	add	r3, r1, lr
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r0, r7
	movmi	r2, #0
	add	r7, r7, #1
	bmi	.L206
	cmp	r3, #255
	movlt	r2, r3
	movge	r2, #255
.L206:
	add	r3, r8, ip
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r0, r7
	movmi	r2, #0
	add	r7, r7, #1
	bmi	.L208
	cmp	r3, #255
	movlt	r2, r3
	movge	r2, #255
.L208:
	add	r3, r1, sl
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r0, r7
	movmi	r2, #0
	add	r7, r7, #1
	bmi	.L210
	cmp	r3, #255
	movlt	r2, r3
	movge	r2, #255
.L210:
	add	r3, r8, r4
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r0, r7
	movmi	r2, #0
	add	r7, r7, #1
	bmi	.L212
	cmp	r3, #255
	movlt	r2, r3
	movge	r2, #255
.L212:
	add	r3, r1, ip
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r2, r7
	movmi	r3, #0
	add	r7, r7, #1
	bmi	.L214
	cmp	r3, #255
	movge	r3, #255
.L214:
	ldr	ip, [sp, #44]
	ldr	r0, [sp, #12]
	add	ip, ip, #2
	str	ip, [sp, #44]
	cmp	ip, r0
	strb	r3, [r2, #0]
	blt	.L223
.L220:
	ldr	r1, [sp, #4]
	ldr	r2, [sp, #12]
	ldr	r3, [sp, #48]
	add	r5, r1, r2
	add	r3, r3, #1
	mov	r4, r5, asl #1
	rsb	r1, r4, r7
	ldr	r0, [sp, #52]
	mov	r2, r4
	str	r3, [sp, #48]
	bl	memcpy
	ldr	r1, [sp, #52]
	ldr	ip, [sp, #48]
	ldr	r0, [sp, #8]
	add	r1, r1, r5, asl #2
	cmp	ip, r0
	add	r7, r7, r4
	str	r1, [sp, #52]
	blt	.L224
.L218:
	add	sp, sp, #60
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
	.size	interlaceParalaxFastScalePlusOld, .-interlaceParalaxFastScalePlusOld
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"h: %d, w: %d\n\000"
	.align	2
.LC1:
	.ascii	"Values: \000"
	.align	2
.LC2:
	.ascii	"%d %d \000"
	.text
	.align	2
	.global	interlaceParalaxFastScalePlusYUV
	.type	interlaceParalaxFastScalePlusYUV, %function
interlaceParalaxFastScalePlusYUV:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, sl, lr}
	mov	r3, r2
	ldr	r2, [r0, #1400]
	mov	r6, r1
	sub	sp, sp, #4
	add	r4, r2, #40
	ldmia	r4, {r4, r5}	@ phole ldm
	mov	r1, r5
	mov	r2, r4
	mul	r5, r4, r5
	ldr	r0, .L248
	mov	r4, #0
	ldmia	r3, {r7, r8, sl}	@ phole ldm
	bl	printf
	cmp	r5, r4
	mov	r1, r4
	ble	.L239
.L246:
	ldrb	r3, [r7, r4]	@ zero_extendqisi2
	add	r4, r4, #1
	cmp	r5, r4
	strb	r3, [r6, r1]
	add	r1, r1, #1
	bgt	.L246
.L239:
	mov	r5, r5, asr #2
	cmp	r5, #0
	mov	r4, #0
	ble	.L241
.L247:
	ldrb	r3, [sl, r4]	@ zero_extendqisi2
	strb	r3, [r1, r6]
	ldrb	r2, [r8, r4]	@ zero_extendqisi2
	add	r1, r1, #1
	add	r4, r4, #1
	strb	r2, [r1, r6]
	cmp	r5, r4
	add	r1, r1, #1
	bgt	.L247
.L241:
	ldr	r0, .L248+4
	bl	printf
	mov	r4, #0
.L237:
	ldrb	r1, [r8, r4]	@ zero_extendqisi2
	ldrb	r2, [sl, r4]	@ zero_extendqisi2
	ldr	r0, .L248+8
	add	r4, r4, #1
	bl	printf
	cmp	r4, #9
	ble	.L237
	mov	r4, #10
	mov	r0, r4
	add	sp, sp, #4
	ldmfd	sp!, {r4, r5, r6, r7, r8, sl, lr}
	b	putchar
.L249:
	.align	2
.L248:
	.word	.LC0
	.word	.LC1
	.word	.LC2
	.size	interlaceParalaxFastScalePlusYUV, .-interlaceParalaxFastScalePlusYUV
	.align	2
	.global	interlaceParalaxFastScalePlus
	.type	interlaceParalaxFastScalePlus, %function
interlaceParalaxFastScalePlus:
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #76
	mov	r3, #0
	str	r3, [sp, #68]
	ldr	r3, [r0, #1400]
	mov	r4, #0
	mov	sl, r1
	add	r5, r3, #40
	ldmia	r5, {r5, r6}	@ phole ldm
	str	r5, [sp, #24]
	mov	ip, r5, asl #1
	add	r1, ip, r5
	cmp	r4, r6
	str	r6, [sp, #20]
	ldr	r6, [sp, #24]
	add	r1, sl, r1, asl #1
	ldr	r0, [r2, #8]
	ldr	r5, [r2, #0]
	str	r4, [sp, #60]
	str	r1, [sp, #64]
	ldmia	r3, {r1, r4}	@ phole ldm
	ldr	r2, [r2, #4]
	ldr	r3, [r3, #8]
	mov	r6, r6, asr #1
	str	ip, [sp, #12]
	str	r0, [sp, #28]
	str	r1, [sp, #48]
	str	r4, [sp, #40]
	str	r3, [sp, #32]
	str	r5, [sp, #44]
	str	r2, [sp, #36]
	str	r6, [sp, #52]
	bge	.L284
.L290:
	ldr	ip, [sp, #60]
	ldr	r1, [sp, #24]
	ldr	fp, [sp, #52]
	mov	r0, #0
	mov	r3, ip, asr #1
	cmp	r0, r1
	str	r0, [sp, #56]
	mul	fp, r3, fp
	bge	.L286
.L289:
	add	r2, sp, #28
	ldmia	r2, {r2, r3, r4}	@ phole ldm
	ldrb	r1, [r2, fp]	@ zero_extendqisi2
	ldrb	r2, [fp, r3]	@ zero_extendqisi2
	ldr	r5, [sp, #40]
	ldrb	ip, [r4, fp]	@ zero_extendqisi2
	add	r3, r1, r1, asl #1
	add	lr, r2, r2, asl #1
	ldrb	r0, [r5, fp]	@ zero_extendqisi2
	add	r2, r2, lr, asl #2
	ldr	r6, [sp, #68]
	ldr	r4, [sp, #44]
	add	r1, r1, r3, asl #2
	rsb	r2, r2, r2, asl #3
	rsb	r3, r3, r3, asl #3
	ldrb	r8, [r6, r4]	@ zero_extendqisi2
	add	r3, r3, r3, asl #4
	mov	r2, r2, asl #1
	rsb	r5, r0, r0, asl #3
	add	r6, r0, r0, asl #2
	sub	r3, r3, #45568
	rsb	r2, r2, #0
	str	r3, [sp, #16]
	str	r2, [sp, #4]
	ldr	r3, [sp, #68]
	ldr	r2, [sp, #48]
	add	r5, r0, r5, asl #4
	add	r0, r0, r6, asl #1
	ldr	r6, [sp, #16]
	mov	r9, r8, asl #8
	rsb	r1, r1, r1, asl #3
	ldrb	r8, [r2, r3]	@ zero_extendqisi2
	rsb	r4, ip, ip, asl #3
	add	r3, r9, r6
	ldr	r6, [sp, #4]
	mov	r1, r1, asl #1
	add	r7, ip, ip, asl #2
	add	r4, ip, r4, asl #4
	rsb	r1, r1, #0
	sub	r2, r6, r0, asl #3
	add	ip, ip, r7, asl #1
	ldr	r0, [sp, #68]
	rsb	lr, lr, lr, asl #3
	sub	r1, r1, ip, asl #3
	mov	r4, r4, asl #2
	mov	r5, r5, asl #2
	add	ip, r2, #34560
	add	r6, r1, #34560
	add	r0, r0, #1
	add	lr, lr, lr, asl #4
	sub	r4, r4, #57600
	sub	r5, r5, #57600
	movs	r3, r3, asr #8
	str	r0, [sp, #68]
	add	fp, fp, #1
	mov	r0, sl
	mov	r1, r8, asl #8
	sub	lr, lr, #45568
	add	ip, ip, #128
	add	r6, r6, #128
	sub	r4, r4, #128
	sub	r5, r5, #128
	add	sl, sl, #1
	movmi	r2, #0
	bmi	.L258
	cmp	r3, #255
	movlt	r2, r3
	movge	r2, #255
.L258:
	add	r3, r1, ip
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r0, sl
	movmi	r2, #0
	add	sl, sl, #1
	bmi	.L260
	cmp	r3, #255
	movlt	r2, r3
	movge	r2, #255
.L260:
	add	r3, r9, r4
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r0, sl
	movmi	r2, #0
	add	sl, sl, #1
	bmi	.L262
	cmp	r3, #255
	movlt	r2, r3
	movge	r2, #255
.L262:
	add	r3, r1, lr
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r0, sl
	movmi	r2, #0
	add	sl, sl, #1
	bmi	.L264
	cmp	r3, #255
	movlt	r2, r3
	movge	r2, #255
.L264:
	add	r3, r9, r6
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r0, sl
	movmi	r2, #0
	add	sl, sl, #1
	bmi	.L266
	cmp	r3, #255
	movlt	r2, r3
	movge	r2, #255
.L266:
	add	r3, r1, r5
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r2, sl
	movmi	r3, #0
	add	sl, sl, #1
	bmi	.L268
	cmp	r3, #255
	movge	r3, #255
.L268:
	strb	r3, [r2, #0]
	ldr	r1, [sp, #68]
	ldr	r2, [sp, #44]
	ldr	r0, [sp, #48]
	ldrb	r3, [r1, r2]	@ zero_extendqisi2
	ldr	r2, [sp, #68]
	ldrb	r1, [r0, r1]	@ zero_extendqisi2
	add	r2, r2, #1
	mov	r9, r3, asl #8
	ldr	r3, [sp, #16]
	str	r2, [sp, #68]
	add	r2, r9, r3
	mov	r0, sl
	movs	r2, r2, asr #8
	mov	r1, r1, asl #8
	add	sl, sl, #1
	movmi	r2, #0
	bmi	.L270
	cmp	r2, #255
	movge	r2, #255
.L270:
	add	r3, r1, ip
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r0, sl
	movmi	r2, #0
	add	sl, sl, #1
	bmi	.L272
	cmp	r3, #255
	movlt	r2, r3
	movge	r2, #255
.L272:
	add	r3, r9, r4
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r0, sl
	movmi	r2, #0
	add	sl, sl, #1
	bmi	.L274
	cmp	r3, #255
	movlt	r2, r3
	movge	r2, #255
.L274:
	add	r3, r1, lr
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r0, sl
	movmi	r2, #0
	add	sl, sl, #1
	bmi	.L276
	cmp	r3, #255
	movlt	r2, r3
	movge	r2, #255
.L276:
	add	r3, r9, r6
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r0, sl
	movmi	r2, #0
	add	sl, sl, #1
	bmi	.L278
	cmp	r3, #255
	movlt	r2, r3
	movge	r2, #255
.L278:
	add	r3, r1, r5
	strb	r2, [r0, #0]
	movs	r3, r3, asr #8
	mov	r2, sl
	movmi	r3, #0
	add	sl, sl, #1
	bmi	.L280
	cmp	r3, #255
	movge	r3, #255
.L280:
	ldr	r4, [sp, #56]
	ldr	r5, [sp, #24]
	add	r4, r4, #2
	str	r4, [sp, #56]
	cmp	r4, r5
	strb	r3, [r2, #0]
	blt	.L289
.L286:
	ldr	r6, [sp, #12]
	ldr	ip, [sp, #24]
	ldr	r0, [sp, #60]
	add	r5, r6, ip
	add	r0, r0, #1
	mov	r4, r5, asl #1
	rsb	r1, r4, sl
	str	r0, [sp, #60]
	mov	r2, r4
	ldr	r0, [sp, #64]
	bl	memcpy
	add	r1, sp, #60
	ldmia	r1, {r1, r3}	@ phole ldm
	ldr	r2, [sp, #20]
	add	r3, r3, r5, asl #2
	cmp	r1, r2
	add	sl, sl, r4
	str	r3, [sp, #64]
	blt	.L290
.L284:
	add	sp, sp, #76
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
	.size	interlaceParalaxFastScalePlus, .-interlaceParalaxFastScalePlus
	.align	2
	.global	interlaceParalaxFastScalePlusXv
	.type	interlaceParalaxFastScalePlusXv, %function
interlaceParalaxFastScalePlusXv:
	@ args = 0, pretend = 0, frame = 88
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #92
	ldr	r3, [r0, #1400]
	str	r1, [sp, #84]
	ldr	r5, [r2, #8]
	add	r1, r3, #40
	ldmia	r1, {r1, r4}	@ phole ldm
	ldr	lr, [r2, #0]
	ldr	r2, [r2, #4]
	mov	r0, #0
	mov	r6, r1, asl #2
	mov	r9, r1, asl #3
	str	r0, [sp, #72]
	str	r1, [sp, #36]
	cmp	r0, r4
	str	r2, [sp, #48]
	mov	r0, r1, asr #1
	ldr	r2, [sp, #84]
	ldr	r1, [sp, #84]
	ldmia	r3, {fp, ip}	@ phole ldm
	ldr	r3, [r3, #8]
	add	r1, r6, r1
	add	r2, r9, r2
	str	r4, [sp, #32]
	str	r5, [sp, #40]
	str	r6, [sp, #12]
	str	r9, [sp, #8]
	str	fp, [sp, #60]
	str	ip, [sp, #52]
	str	r3, [sp, #44]
	str	lr, [sp, #56]
	str	r0, [sp, #64]
	str	r1, [sp, #80]
	str	r2, [sp, #76]
	bge	.L349
	ldr	r3, [sp, #36]
	ldr	r4, [sp, #36]
	mov	r3, r3, asl #1
	mov	r4, r4, asl #4
	str	r3, [sp, #16]
	str	r4, [sp, #4]
.L347:
	ldr	r5, [sp, #72]
	ldr	fp, [sp, #64]
	ldr	r9, [sp, #36]
	mov	r3, r5, asr #1
	mov	r6, #0
	mul	fp, r3, fp
	cmp	r6, r9
	str	r6, [sp, #68]
	str	fp, [sp, #28]
	bge	.L351
.L353:
	ldr	lr, [sp, #28]
	ldr	ip, [sp, #40]
	ldr	r0, [sp, #44]
	ldr	r5, [sp, #56]
	ldrb	r2, [ip, lr]	@ zero_extendqisi2
	ldrb	r3, [lr, r0]	@ zero_extendqisi2
	ldr	r6, [sp, #36]
	add	r1, sp, #48
	ldmia	r1, {r1, r4}	@ phole ldm
	add	r0, r2, r2, asl #1
	ldrb	r5, [r5, r6]	@ zero_extendqisi2
	ldr	r6, [sp, #56]
	ldrb	ip, [r1, lr]	@ zero_extendqisi2
	add	r2, r2, r0, asl #2
	ldrb	r1, [r4, lr]	@ zero_extendqisi2
	add	lr, r3, r3, asl #1
	str	r5, [sp, #20]
	ldr	r9, [sp, #60]
	ldrb	r8, [r6], #1	@ zero_extendqisi2
	add	r3, r3, lr, asl #2
	ldr	fp, [sp, #36]
	rsb	r2, r2, r2, asl #3
	rsb	r4, ip, ip, asl #3
	add	r7, ip, ip, asl #2
	rsb	r3, r3, r3, asl #3
	mov	r2, r2, asl #1
	str	r6, [sp, #56]
	rsb	r2, r2, #0
	ldrb	sl, [r9, fp]	@ zero_extendqisi2
	mov	fp, r9
	rsb	r5, r1, r1, asl #3
	add	r6, r1, r1, asl #2
	add	r4, ip, r4, asl #4
	mov	r3, r3, asl #1
	add	ip, ip, r7, asl #1
	ldrb	r9, [fp], #1	@ zero_extendqisi2
	sub	r2, r2, ip, asl #3
	rsb	r0, r0, r0, asl #3
	rsb	r3, r3, #0
	add	r5, r1, r5, asl #4
	add	r2, r2, #34560
	add	r1, r1, r6, asl #1
	sub	r3, r3, r1, asl #3
	str	r2, [sp, #24]
	add	r0, r0, r0, asl #4
	add	r7, r3, #34560
	ldr	ip, [sp, #28]
	str	fp, [sp, #60]
	rsb	lr, lr, lr, asl #3
	sub	fp, r0, #45568
	ldr	r3, [sp, #20]
	ldr	r0, [sp, #24]
	mov	r4, r4, asl #2
	mov	r5, r5, asl #2
	mov	r8, r8, asl #8
	add	r0, r0, #128
	add	lr, lr, lr, asl #4
	sub	r4, r4, #57600
	sub	r5, r5, #57600
	adds	r2, r8, fp
	add	ip, ip, #1
	str	r0, [sp, #24]
	str	ip, [sp, #28]
	sub	lr, lr, #45568
	add	r7, r7, #128
	sub	r4, r4, #128
	sub	r5, r5, #128
	mov	r1, sl, asl #8
	mov	r6, r3, asl #8
	mov	r0, r9, asl #8
	movmi	r2, #0
	bmi	.L299
	cmp	r2, #65280
	movge	r2, #65280
.L299:
	adds	r3, r0, r7
	movmi	r3, #0
	bmi	.L301
	cmp	r3, #65280
	movge	r3, #65280
.L301:
	adds	ip, r8, r4
	movmi	ip, #0
	bmi	.L303
	cmp	ip, #65280
	movge	ip, #65280
.L303:
	and	r3, r3, #64512
	ldr	r9, [sp, #84]
	mov	r3, r3, asr #5
	and	r2, r2, #63488
	orr	r3, r3, ip, asr #11
	orr	r3, r3, r2
	adds	r2, r6, fp
	strh	r3, [r9], #2	@ movhi 
	movmi	r2, #0
	str	r9, [sp, #84]
	bmi	.L305
	cmp	r2, #65280
	movge	r2, #65280
.L305:
	adds	r3, r1, r7
	movmi	r3, #0
	bmi	.L307
	cmp	r3, #65280
	movge	r3, #65280
.L307:
	adds	ip, r6, r4
	movmi	ip, #0
	bmi	.L309
	cmp	ip, #65280
	movge	ip, #65280
.L309:
	and	r3, r3, #64512
	and	r2, r2, #63488
	mov	r3, r3, asr #5
	orr	r3, r3, ip, asr #11
	ldr	ip, [sp, #76]
	orr	r3, r3, r2
	adds	r2, r0, lr
	strh	r3, [ip], #2	@ movhi 
	movmi	r2, #0
	str	ip, [sp, #76]
	bmi	.L311
	cmp	r2, #65280
	movge	r2, #65280
.L311:
	ldr	r9, [sp, #24]
	adds	r3, r8, r9
	movmi	r3, #0
	bmi	.L313
	cmp	r3, #65280
	movge	r3, #65280
.L313:
	adds	ip, r0, r5
	movmi	ip, #0
	bmi	.L315
	cmp	ip, #65280
	movge	ip, #65280
.L315:
	and	r3, r3, #64512
	and	r2, r2, #63488
	mov	r3, r3, asr #5
	orr	r3, r3, ip, asr #11
	ldr	ip, [sp, #84]
	orr	r3, r3, r2
	adds	r2, r1, lr
	strh	r3, [ip], #2	@ movhi 
	movmi	r2, #0
	str	ip, [sp, #84]
	bmi	.L317
	cmp	r2, #65280
	movge	r2, #65280
.L317:
	ldr	r0, [sp, #24]
	adds	r3, r6, r0
	movmi	r3, #0
	bmi	.L319
	cmp	r3, #65280
	movge	r3, #65280
.L319:
	adds	ip, r1, r5
	movmi	ip, #0
	bmi	.L321
	cmp	ip, #65280
	movge	ip, #65280
.L321:
	and	r3, r3, #64512
	ldr	r1, [sp, #76]
	mov	r3, r3, asr #5
	and	r2, r2, #63488
	orr	r3, r3, ip, asr #11
	orr	r3, r3, r2
	strh	r3, [r1], #2	@ movhi 
	ldr	r3, [sp, #56]
	ldr	r6, [sp, #36]
	mov	r9, r3
	str	r1, [sp, #76]
	ldr	ip, [sp, #60]
	ldrb	r2, [r3, r6]	@ zero_extendqisi2
	ldrb	r3, [r9], #1	@ zero_extendqisi2
	str	r9, [sp, #56]
	ldrb	r1, [ip, r6]	@ zero_extendqisi2
	ldrb	r0, [ip], #1	@ zero_extendqisi2
	mov	r8, r3, asl #8
	mov	r6, r2, asl #8
	adds	r2, r8, fp
	str	ip, [sp, #60]
	mov	r1, r1, asl #8
	mov	r0, r0, asl #8
	movmi	r2, #0
	bmi	.L323
	cmp	r2, #65280
	movge	r2, #65280
.L323:
	adds	r3, r0, r7
	movmi	r3, #0
	bmi	.L325
	cmp	r3, #65280
	movge	r3, #65280
.L325:
	adds	ip, r8, r4
	movmi	ip, #0
	bmi	.L327
	cmp	ip, #65280
	movge	ip, #65280
.L327:
	and	r3, r3, #64512
	ldr	r9, [sp, #84]
	mov	r3, r3, asr #5
	and	r2, r2, #63488
	orr	r3, r3, ip, asr #11
	orr	r3, r3, r2
	adds	r2, r6, fp
	strh	r3, [r9], #2	@ movhi 
	movmi	r2, #0
	str	r9, [sp, #84]
	bmi	.L329
	cmp	r2, #65280
	movge	r2, #65280
.L329:
	adds	r3, r1, r7
	movmi	r3, #0
	bmi	.L331
	cmp	r3, #65280
	movge	r3, #65280
.L331:
	adds	ip, r6, r4
	movmi	ip, #0
	bmi	.L333
	cmp	ip, #65280
	movge	ip, #65280
.L333:
	and	r3, r3, #64512
	ldr	fp, [sp, #76]
	mov	r3, r3, asr #5
	and	r2, r2, #63488
	orr	r3, r3, ip, asr #11
	orr	r3, r3, r2
	adds	r2, r0, lr
	strh	r3, [fp], #2	@ movhi 
	movmi	r2, #0
	str	fp, [sp, #76]
	bmi	.L335
	cmp	r2, #65280
	movge	r2, #65280
.L335:
	ldr	ip, [sp, #24]
	adds	r3, r8, ip
	movmi	r3, #0
	bmi	.L337
	cmp	r3, #65280
	movge	r3, #65280
.L337:
	adds	ip, r0, r5
	movmi	ip, #0
	bmi	.L339
	cmp	ip, #65280
	movge	ip, #65280
.L339:
	and	r3, r3, #64512
	and	r2, r2, #63488
	mov	r3, r3, asr #5
	orr	r3, r3, ip, asr #11
	orr	r3, r3, r2
	adds	r2, r1, lr
	ldr	lr, [sp, #84]
	movmi	r2, #0
	strh	r3, [lr], #2	@ movhi 
	str	lr, [sp, #84]
	bmi	.L341
	cmp	r2, #65280
	movge	r2, #65280
.L341:
	ldr	r0, [sp, #24]
	adds	r3, r6, r0
	movmi	r3, #0
	bmi	.L343
	cmp	r3, #65280
	movge	r3, #65280
.L343:
	adds	ip, r1, r5
	movmi	ip, #0
	bmi	.L345
	cmp	ip, #65280
	movge	ip, #65280
.L345:
	and	r3, r3, #64512
	and	r2, r2, #63488
	mov	r3, r3, asr #5
	ldr	r1, [sp, #68]
	ldr	r4, [sp, #76]
	orr	r3, r3, ip, asr #11
	orr	r3, r3, r2
	ldr	r2, [sp, #36]
	add	r1, r1, #2
	strh	r3, [r4], #2	@ movhi 
	str	r1, [sp, #68]
	cmp	r1, r2
	str	r4, [sp, #76]
	blt	.L353
.L351:
	ldr	r6, [sp, #12]
	ldr	r5, [sp, #84]
	mov	r2, r6
	rsb	r1, r6, r5
	ldr	r0, [sp, #80]
	bl	memcpy
	ldr	r9, [sp, #8]
	ldr	fp, [sp, #80]
	ldr	ip, [sp, #76]
	add	r0, r9, fp
	rsb	r1, r6, ip
	ldr	r2, [sp, #12]
	bl	memcpy
	ldr	r0, [sp, #36]
	ldr	lr, [sp, #16]
	ldr	r1, [sp, #72]
	add	r3, lr, r0
	ldr	r4, [sp, #76]
	mov	r3, r3, asl #2
	add	r5, r5, r3
	add	r6, sp, #56
	ldmia	r6, {r6, r9}	@ phole ldm
	ldr	r2, [sp, #32]
	str	r5, [sp, #84]
	ldr	r5, [sp, #4]
	add	r1, r1, #2
	add	r4, r4, r3
	add	fp, fp, r5
	add	r6, r6, r0
	add	r9, r9, r0
	cmp	r1, r2
	str	r1, [sp, #72]
	str	r4, [sp, #76]
	str	fp, [sp, #80]
	str	r6, [sp, #56]
	str	r9, [sp, #60]
	blt	.L347
.L349:
	add	sp, sp, #92
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
	.size	interlaceParalaxFastScalePlusXv, .-interlaceParalaxFastScalePlusXv
	.ident	"GCC: (GNU) 3.4.4 (release) (CodeSourcery ARM 2005q3-2)"
