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

/*
 *
 * globals.h
 *
 * Contains:
 *    Interface for data and functions common to all modules
 *
 */

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "nrctypes.h"

/*
 * General defines
 */

#ifdef __TMS320C55X__
/* If this is defined, int is 16 bits */
#define INT_IS_16_BITS
#endif

/* If this is defined as 1, input bitstream is encapsulated in NAL packets */
/* and contians start code emulation prevention bytes                      */
#define ENCAPSULATED_NAL_PAYLOAD 1

/* Minimum and maximum QP value */
#define MIN_QP 0
#define MAX_QP 51

/* If this is defined, pixel clipping will use loop-up table */
#ifndef __TMS320C55X__
#define USE_CLIPBUF
#endif

#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif

/* This macro clips value val to the range of [min, max] */
#define  clip(min, max, val) (((val)<(min))? (min):(((val)>(max))? (max):(val)))


#define DEBUG_PRINT

/*
 * Defines for assembly functions
 */

//#define AVC_ARM_ASSEMBLY

#ifdef AVC_ARM_ASSEMBLY
#define AVC_RECO_BLOCK_ASM
#define AVC_LOOP_FILTER_ASM
#define AVC_MOTION_COMP_ASM
#endif

#ifdef __TMS320C55X__
#define AVC_RECO_BLOCK_ASM
#endif


/*
 * Defines for error concealment
 */
#ifndef ERROR_CONCEALMENT
#define ERROR_CONCEALMENT
#endif


/*
 * Defines for slice
 */

/* All possible slice types */
#define SLICE_MIN 0
#define SLICE_P   0 // P (P slice)
#define SLICE_B   1 // B (B slice)
#define SLICE_I   2 // I (I slice)
#define SLICE_SP  3 // SP (SP slice)
#define SLICE_SI  4 // SI (SI slice)
#define SLICE_P1  5	// P (P slice)
#define SLICE_B1  6	// B (B slice)
#define SLICE_I1  7	// I (I slice)
#define SLICE_SP1 8	// SP (SP slice)
#define SLICE_SI1 9	// SI (SI slice)
#define SLICE_MAX 9

/* Macros for testing whether slice is I slice, P slice or B slice */
#define IS_SLICE_I(x) ((x) == SLICE_I || (x) == SLICE_I1 || (x) == SLICE_SI || (x) == SLICE_SI1)
#define IS_SLICE_P(x) ((x) == SLICE_P || (x) == SLICE_P1 || (x) == SLICE_SP || (x) == SLICE_SP1)
#define IS_SLICE_B(x) ((x) == SLICE_B || (x) == SLICE_B1)

/*
 * Defines for macroblock
 */
#define MBK_SIZE        16
#define BLK_SIZE        4
#define BLK_PER_MB      (MBK_SIZE/BLK_SIZE)
#define MBK_SIZE_LOG2   4
#define BLK_SIZE_LOG2   2

/* Macroblock type */
#define MBK_INTRA  0
#define MBK_INTER  1

/* define all possible intra/inter modes using just 1 variable */
#define MB_TYPE_INTRA_4x4              0
#define MB_TYPE_INTRA_16x16            1
#define MB_TYPE_INTRA_PCM              2
#define MB_TYPE_INTER_SKIPPED          3
#define MB_TYPE_INTER_16x16            4
#define MB_TYPE_INTER_16x8             5
#define MB_TYPE_INTER_8x16             6
#define MB_TYPE_INTER_8x8              7
#define MB_TYPE_INTER_8x8_8x4_4x8_4x4  8
#define MB_TYPE_B_DIRECT_16x16         9

#define MBK_IS_INTRA(mbType)        ((mbType) <= MB_TYPE_INTRA_PCM)
#define MBK_IS_INTRA_4x4(mbType)    ((mbType) == MB_TYPE_INTRA_4x4)
#define MBK_IS_INTRA_16x16(mbType)  ((mbType) == MB_TYPE_INTRA_16x16)
#define MBK_IS_INTRA_PCM(mbType)    ((mbType) == MB_TYPE_INTRA_PCM)
#define MBK_IS_INTER(mbType)        ((mbType) >= MB_TYPE_INTER_SKIPPED)

/*
 * Global structures
 */
typedef struct _motVec_s {
  int16 x;
  int16 y;
} motVec_s;

typedef struct _macroblock_s
{
  int type;
  int numSkipped;

  int intraMode;
  int intraModeChroma;

  int interMode;
  int subMbModes[4];
  int refNum[4];       /* for up to 4 MB partitions */
  int numMotVecs;

  int qp, qpC;
  int idxX, idxY;
  int blkX, blkY;
  int pixX, pixY;
  int mbAddr, blkAddr, pixAddr;

  int cbpY, cbpC, cbpChromaDC;

  u_int8 predY[MBK_SIZE][MBK_SIZE];
  u_int8 predC[MBK_SIZE/2][MBK_SIZE];

  int dcCoefY[BLK_PER_MB][BLK_PER_MB];
  int dcCoefC[2][BLK_PER_MB/2][BLK_PER_MB/2];

  int coefY[BLK_PER_MB][BLK_PER_MB][BLK_SIZE][BLK_SIZE];
  int coefC[2][BLK_PER_MB/2][BLK_PER_MB/2][BLK_SIZE][BLK_SIZE];

  int mbAvailBits;

  int8 numCoefLeftPred[BLK_PER_MB];
  int8 numCoefLeftPredC[2][BLK_PER_MB/2];

  int8 ipModesLeftPred[BLK_PER_MB];

  int8 refIdxToPicIDmappingL0[17];

#ifdef DEBUG_PRINT
  double intraTime;
  double vldTime;
  double interTime;
  double codingTime;
#endif

} macroblock_s;


/* Chrominance QP mapping table. Has to be static on Symbian. */
/* Chroma QP = qpChroma[Luma QP]                              */
#ifndef __SYMBIAN32__
extern const u_int8 qpChroma[52];
#else
static const u_int8 qpChroma[52] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,
   12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,
   28,29,29,30,31,32,32,33,34,34,35,35,36,36,37,37,
   37,38,38,38,39,39,39,39
}; 
#endif

#endif
