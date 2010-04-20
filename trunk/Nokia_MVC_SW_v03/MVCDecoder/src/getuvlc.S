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


#define BIB_ERR_BIT_ERROR          -4
#define BIB_INCORRECT_TRAILING_BIT -3
#define BIB_ERR_NO_BITS            -2
#define BIB_ERROR                  -1
#define BIB_OK                      0


/*
typedef struct _bitbuffer_s 
{
  u_int8 *data;
  int dataLen;
  int bytePos;
  int bitpos;
  int32 currentBits;
  int errorStatus;
} bitbuffer_s;
*/

#define bitbuffer_s_data        0
#define bitbuffer_s_dataLen     4
#define bitbuffer_s_bytePos     8
#define bitbuffer_s_bitpos      12
#define bitbuffer_s_currentBits 16
#define bitbuffer_s_errorStatus 20



#define VLD_MAX_CW_LEN              33
#define VLD_MAX_LONG_CW_LEN         65

#define VLD_MAX_UVLC_CODE_NUM       65535         /* 2^16-1 */
#define VLD_MAX_LONG_UVLC_CODE_NUM  4294967295    /* 2^32-1 */



/*
 *
 * vldGetUVLC:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Decode an UVLC codeword, UVLC codeword is of the form:
 *      code          codeword
 *      0                1
 *      1               010
 *      2               011
 *      3              00100
 *      4              00101
 *      5              00110
 *      6              00111
 *      7             0001000
 *      8             0001001
 *      ...             ...
 *
 * Returns:
 *      Codenumber in the range [0, 65535]
 *
 */

/*
 * unsigned int vldGetUVLC(bitbuffer_s *bitbuf)
 */

	ALIGNW
#if defined(COMPILER_ADS)
	GLOBLAB	vldGetUVLC
vldGetUVLC PROC
#elif defined(COMPILER_GCC)
	GLOBLAB	vldGetUVLC
vldGetUVLC:
#elif defined(COMPILER_CCS)
	GLOBLAB	_vldGetUVLC
_vldGetUVLC
#endif


	ldr	r1, [r0, #bitbuffer_s_bitpos]
	ldr	r2, [r0, #bitbuffer_s_currentBits]
	subs	r1, r1, #7			// bitpos -= 7
	bge	L_enought_bits
	str	r4, [sp, #-4]!			// save r4
	ldr	r4, [r0, #bitbuffer_s_dataLen]
	ldr	r3, [r0, #bitbuffer_s_bytePos]
	ldr	r12, [r0, #bitbuffer_s_data]
	sub	r4, r4, #1
	cmp	r3, r4				// if (bytePos <= dataLen-1)
	ldrleb	r4, [r12, r3]			//   data[bytePos]
	mov	r2, r2, lsl #16			// currentBits <<= 16
	add	r3, r3, #1			// bytePos++
	add	r1, r1, #16			// bitpos += 16
	orrle	r2, r2, r4, lsl #8		//   currentBits |= (data[bytePos] << 8)
	ldrltb	r4, [r12, r3]			//   data[bytePos]
	add	r3, r3, #1			// bytePos++
	str	r3, [r0, #bitbuffer_s_bytePos]
	orrlt	r2, r2, r4			//   currentBits |= data[bytePos]
	str	r2, [r0, #bitbuffer_s_currentBits]
	ldr	r4, [sp], #4			// restore r4

LABELDEF(enought_bits)

	ldr	r3, L_uvlcLookupPtr
//	ldr	r3, [r0, #bitbuffer_s_data]

	mov	r12, #127			// ~(((u_int32)-1)<<7)
	and	r2, r12, r2, lsr r1		// bits = (currentBits >> bitpos) & ~(((u_int32)-1)<<7)

	ldrb	r3, [r3, r2]			// c = uvlcLookup[bits]

	add	r1, r1, #7			// bitpos += 7  (cancels earlier substraction)

// bx lr
	cmp	r2, #8				// if (bits >= 8) {
	subge	r1, r1, r3, lsr #4		//   bibSkipBits(bitbuf, c >> 4)
	strge	r1, [r0, #bitbuffer_s_bitpos]
	andge	r0, r3, #15			//   return (unsigned int) (c & 15)
	bxge	lr				// }


	// Handle long codewords (over 7 bits)


	stmfd	sp!, {r4-r6}			// save 3 regs

#if ARM_ARCH_VERSION <= ARM_ARCH_V5
	mov	r5, r3				// prefixLen = c
#endif

	ldr	r2, [r0, #bitbuffer_s_currentBits]
	ldr	r3, [r0, #bitbuffer_s_bytePos]
	ldr	r4, [r0, #bitbuffer_s_dataLen]
	ldr	r12, [r0, #bitbuffer_s_data]

	cmp	r1, #24
	bgt	L_enought_bits2

	// Fill currentBits with bytes to speed up scanning of one bit
LABELDEF(not_enought_bits)
	cmp	r3, r4				// if (bytePos < dataLen)
	mov	r2, r2, lsl #8			// currentBits <<= 8
	ldrltb	r6, [r12, r3]			//   data[bytePos]
	add	r3, r3, #1			// bytePos++
	add	r1, r1, #8			// bitpos += 8
	orrlt	r2, r2, r6			//   currentBits |= data[bytePos]
	cmp	r1, #24
	ble	L_not_enought_bits

LABELDEF(enought_bits2)

/*
  do {
    prefixLen += 1;
    if (prefixLen > VLD_MAX_CW_LEN/2) {
      bibRaiseError(bitbuf, BIB_ERR_BIT_ERROR);
      return 0;
    }
    bibGetBit(bitbuf, &bits);
  } while (bits == 0);
*/

	rsb	r6, r1, #32			// 32 - bitpos
	mov	r6, r2, lsl r6			// align valid bits at msb
#if ARM_ARCH_VERSION <= ARM_ARCH_V5
	mov	r6, r6, lsl r5			// -"-
	orr	r6, r6, #1			// prevent infinite loop
LABELDEF(find_one_bit)
	adds	r6, r6, r6			// is next bit "1"?
	addcc	r5, r5, #1			// if not, increment prefixLen
	bcc	L_find_one_bit			// and check next bit ...
#else
	clz	r5, r6				// prefixLen = number of leading zero bits
#endif

	cmp	r5, #VLD_MAX_CW_LEN/2
	bgt	L_uvlc_error

	sub	r1, r1, r5			// bitpos -= prefixLen
	add	r5, r5, #1			// prefixLen++  (increment to include "1" bit)

// bibGetBits(bitbuf, prefixLen, &c)

	subs	r1, r1, r5			// bitpos -= prefixLen
	bge	L_enought_bits3
	cmp	r3, r4				// if (bytePos < dataLen)
	mov	r2, r2, lsl #8			// currentBits <<= 8
	ldrltb	r6, [r12, r3]			//   data[bytePos]
	add	r3, r3, #1			// bytePos++
	add	r1, r1, #8			// bitpos += 8
	orrlt	r2, r2, r6			//   currentBits |= data[bytePos]

LABELDEF(enought_bits3)

	str	r1, [r0, #bitbuffer_s_bitpos]
	str	r2, [r0, #bitbuffer_s_currentBits]
	str	r3, [r0, #bitbuffer_s_bytePos]

	mvn	r12, #0				// -1
	mov	r2, r2, lsr r1			// currentBits >> bitpos
	bic	r2, r2, r12, lsl r5		// c = (currentBits >> bitpos) & ~(((u_int32)-1)<<prefixLen)

	sub	r2, r2, #1			// c = c - 1

	cmp	r2, r12, lsr #16		// if (c > VLD_MAX_UVLC_CODE_NUM)
	bgt	L_uvlc_error

	mov	r0, r2				// return (unsigned int) c

	ldmfd	sp!, {r4-r6}			// restore 3 regs
	bx	lr

LABELDEF(uvlc_error)

	ldr	r1, L_BIB_ERR_BIT_ERROR_value
	str	r1, [r0, #bitbuffer_s_errorStatus]
	mov	r0, #0
	ldmfd	sp!, {r4-r6}			// restore 3 regs
	bx	lr



	ALIGNW

LABELDEF(uvlcLookupPtr)
	DEFW	L_uvlcLookup

LABELDEF(BIB_ERR_BIT_ERROR_value)
	DEFW	BIB_ERR_BIT_ERROR


	ENDP



	DATASEC


/* Fast look-up for uvlc codes with max length of 7 bits */

/* static const int8 uvlcLookup[128] */
LABELDEF(uvlcLookup)
	DEFB	7, 6, 5, 5, 4, 4, 4, 4                                          // 0000xxx
	DEFB	7*16+7, 7*16+8, 7*16+9,7*16+10,7*16+11,7*16+12,7*16+13,7*16+14  // 0001xxx
	DEFB	5*16+3, 5*16+3, 5*16+3, 5*16+3, 5*16+4, 5*16+4, 5*16+4, 5*16+4  // 001xxxx
	DEFB	5*16+5, 5*16+5, 5*16+5, 5*16+5, 5*16+6, 5*16+6, 5*16+6, 5*16+6
	DEFB	3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1  // 010xxxx
	DEFB	3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1
	DEFB	3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2  // 011xxxx
	DEFB	3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2
	DEFB	1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0  // 1xxxxxx
	DEFB	1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0
	DEFB	1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0
	DEFB	1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0
	DEFB	1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0
	DEFB	1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0
	DEFB	1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0
	DEFB	1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0



	ENDFILE
