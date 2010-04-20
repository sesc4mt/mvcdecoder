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
 * vld.c
 *
 * Contains:
 *    Variable length decoding
 *
 */

#include "nccglob.h"
#include "globals.h"
#include "bitbuffer.h"
#include "vld.h"

#define VLD_MAX_CW_LEN              33
#define VLD_MAX_LONG_CW_LEN         65

#define VLD_MAX_UVLC_CODE_NUM       65535         /* 2^16-1 */
#define VLD_MAX_LONG_UVLC_CODE_NUM  4294967295ul  /* 2^32-1 */

#define VLD_NUM_MB_CODES_INTRA      (1+4*3*2+1)   /* 1 4x4, 24 16x16, 1 PCM */
#define VLD_NUM_MB_CODES_INTER      (5+1+4*3*2+1) /* 5 inter, 1 4x4, 24 16x16, 1 PCM */

#define VLD_MAX_SUB_MB_MODE         3

#define VLD_MAX_IPR_CHROMA_MODE     3

#define VLD_MAX_CBP_CODE            47
#define VLD_MAX_DELTA_QP_CODE       52


/*
 * Static tables for VLD decoder
 */

/* gives CBP value from codeword number, both for intra and inter */
static const int8 code2cbp[VLD_MAX_CBP_CODE+1][2] = {  
  {47, 0},{31,16},{15, 1},{ 0, 2},{23, 4},{27, 8},{29,32},{30, 3},{ 7, 5},{11,10},{13,12},{14,15}, 
  {39,47},{43, 7},{45,11},{46,13},{16,14},{ 3, 6},{ 5, 9},{10,31},{12,35},{19,37},{21,42},{26,44},
  {28,33},{35,34},{37,36},{42,40},{44,39},{ 1,43},{ 2,45},{ 4,46},{ 8,17},{17,18},{18,20},{20,24},
  {24,19},{ 6,21},{ 9,26},{22,28},{25,23},{32,27},{33,29},{34,30},{36,22},{40,25},{38,38},{41,41}    
};

static const int numRefIndices[5] = {
  0, 1, 2, 2, 4
};

/* Look-up table for determining the number of leading zero bits in a 7-bit bumber */
static const int8 numLeadZerosTab[128] = {
  7,6,5,5,4,4,4,4,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};


/*
 * Structure of the code is XXYYYYZZ, where XX is the length of the code
 * minus (number of leading zero bits plus 1), YYYY is totalCoef-1 and
 * ZZ is numTrailingOnes. Code xx000010 means that there are no coefficients.
 * 0 is illegal.
 */
static const u_int8 numCoefTrailTab[3][16][8] = {
  {
    {  2,  2,  2,  2,  2,  2,  2,  2}, {  1,  1,  1,  1,  1,  1,  1,  1},
    {  6,  6,  6,  6,  6,  6,  6,  6}, {133,133,128,128, 75, 75, 75, 75},
    {147,147,138,138, 79, 79, 79, 79}, {151,151,142,142,137,137,132,132},
    {155,155,146,146,141,141,136,136}, {159,159,150,150,145,145,140,140},
    {163,163,154,154,149,149,144,144}, {220,226,221,216,231,222,217,212},
    {239,234,229,228,235,230,225,224}, {247,242,237,236,243,238,233,232},
    {255,250,249,244,251,246,245,240}, {188,188,190,190,189,189,184,184},
    { 49, 49, 49, 49, 49, 49, 49, 49}, {  0,  0,  0,  0,  0,  0,  0,  0}
  },
  {
    { 65, 65, 65, 65, 66, 66, 66, 66}, {143,143,139,139, 70, 70, 70, 70},
    {215,202,201,192,147,147,133,133}, {155,155,142,142,141,141,132,132},
    {159,159,146,146,145,145,136,136}, {144,144,150,150,149,149,140,140},
    {163,163,154,154,153,153,148,148}, {235,226,225,220,231,222,221,216},
    {232,234,233,228,239,230,229,224}, {247,242,241,240,243,238,237,236},
    {249,248,250,245,182,182,180,180}, {191,191,190,190,189,189,188,188},
    { 59, 59, 59, 59, 59, 59, 59, 59}, {  0,  0,  0,  0,  0,  0,  0,  0},
    {  0,  0,  0,  0,  0,  0,  0,  0}, {  0,  0,  0,  0,  0,  0,  0,  0}
  },
  {
    {219,215,211,207,203,198,193,194}, {209,210,205,206,201,223,202,197},
    {200,218,217,196,227,214,213,192}, {216,212,226,208,231,222,221,204},
    {239,234,229,224,235,230,225,220}, {236,242,237,232,243,238,233,228},
    {249,244,247,246,245,240,177,177}, {189,189,184,184,187,187,186,186},
    {127,127,127,127,126,126,126,126}, { 60, 60, 60, 60, 60, 60, 60, 60},
    {  0,  0,  0,  0,  0,  0,  0,  0}, {  0,  0,  0,  0,  0,  0,  0,  0},
    {  0,  0,  0,  0,  0,  0,  0,  0}, {  0,  0,  0,  0,  0,  0,  0,  0},
    {  0,  0,  0,  0,  0,  0,  0,  0}, {  0,  0,  0,  0,  0,  0,  0,  0}
  }
};


/*
 * The structure of the code is XXXYYYXX where XXX is the length of the code
 * minus 1, YYY is total number of non-zero coefficients and XX is
 * the number of trailing ones.
 */
static const u_int8 numCoefTrailTabChroma[8][4] = {
  {  5,  5,  5,  5},
  { 32, 32, 32, 32},
  { 74, 74, 74, 74},
  {168,175,169,164},
  {176,176,172,172},
  {206,206,205,205},
  {242,242,241,241},
  {211,211,211,211}
};


/* Offsets for 15 Huffman tables in totalZerosTab */
static const int totalZerosTabOffset[15] = {
  0, 40, 72, 104, 136, 168,
  184, 200, 216, 232, 248, 264, 280,
  288, 296
};

/*
 * The meaning of the code in the table is the following:
 *  If (code > 0xc0) then (code - 0xc0) is an offset to the next position 
 *  in the Huffman tree
 *  Otherwise, code structure is XXXXYYYY where XXXX is the length of the code
 *  and YYYY is the number of zero coefficients.
 */
static const u_int8 totalZerosTab[304] = {
  0xC8, 0xD0, 0x32, 0x31, 0x10, 0x10, 0x10, 0x10,  /* totalCoef==1 */
  0xD8, 0xE0, 0x68, 0x67, 0x56, 0x56, 0x55, 0x55,  /* prefix 000 */
  0x44, 0x44, 0x44, 0x44, 0x43, 0x43, 0x43, 0x43,  /* prefix 001 */
  0x00, 0x9f, 0x9e, 0x9d, 0x8c, 0x8c, 0x8b, 0x8b,  /* prefix 000000 */
  0x7a, 0x7a, 0x7a, 0x7a, 0x79, 0x79, 0x79, 0x79,  /* prefix 000001 */
  0xC8, 0xD0, 0xD8, 0x34, 0x33, 0x32, 0x31, 0x30,  /* totalCoef==2 */
  0x6e, 0x6d, 0x6c, 0x6b, 0x5a, 0x5a, 0x59, 0x59,  /* prefix 000 */
  0x48, 0x48, 0x48, 0x48, 0x47, 0x47, 0x47, 0x47,  /* prefix 001 */
  0x46, 0x46, 0x46, 0x46, 0x45, 0x45, 0x45, 0x45,  /* prefix 010 */
  0xC8, 0xD0, 0xD8, 0x37, 0x36, 0x33, 0x32, 0x31,  /* totalCoef==3 */
  0x6d, 0x6b, 0x5c, 0x5c, 0x5a, 0x5a, 0x59, 0x59,  /* prefix 000 */
  0x48, 0x48, 0x48, 0x48, 0x45, 0x45, 0x45, 0x45,  /* prefix 001 */
  0x44, 0x44, 0x44, 0x44, 0x40, 0x40, 0x40, 0x40,  /* prefix 010 */
  0xC8, 0xD0, 0xD8, 0x38, 0x36, 0x35, 0x34, 0x31,  /* totalCoef==4 */
  0x5c, 0x5c, 0x5b, 0x5b, 0x5a, 0x5a, 0x50, 0x50,  /* prefix 000 */
  0x49, 0x49, 0x49, 0x49, 0x47, 0x47, 0x47, 0x47,  /* prefix 001 */
  0x43, 0x43, 0x43, 0x43, 0x42, 0x42, 0x42, 0x42,  /* prefix 010 */
  0xC8, 0xD0, 0xD8, 0x37, 0x36, 0x35, 0x34, 0x33,  /* totalCoef==5 */
  0x5b, 0x5b, 0x59, 0x59, 0x4a, 0x4a, 0x4a, 0x4a,  /* prefix 000 */
  0x48, 0x48, 0x48, 0x48, 0x42, 0x42, 0x42, 0x42,  /* prefix 001 */
  0x41, 0x41, 0x41, 0x41, 0x40, 0x40, 0x40, 0x40,  /* prefix 010 */
  0xC8, 0x39, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32,  /* totalCoef==6 */
  0x6a, 0x60, 0x51, 0x51, 0x48, 0x48, 0x48, 0x48,  /* prefix 000 */
  0xC8, 0x38, 0x36, 0x34, 0x33, 0x32, 0x25, 0x25,  /* totalCoef==7 */
  0x69, 0x60, 0x51, 0x51, 0x47, 0x47, 0x47, 0x47,  /* prefix 000 */
  0xC8, 0x37, 0x36, 0x33, 0x25, 0x25, 0x24, 0x24,  /* totalCoef==8 */
  0x68, 0x60, 0x52, 0x52, 0x41, 0x41, 0x41, 0x41,  /* prefix 000 */
  0xC8, 0x35, 0x26, 0x26, 0x24, 0x24, 0x23, 0x23,  /* totalCoef==9 */
  0x61, 0x60, 0x57, 0x57, 0x42, 0x42, 0x42, 0x42,  /* prefix 000 */
  0xC8, 0x32, 0x25, 0x25, 0x24, 0x24, 0x23, 0x23,  /* totalCoef==10 */
  0x51, 0x51, 0x50, 0x50, 0x46, 0x46, 0x46, 0x46,  /* prefix 000 */
  0xC8, 0x32, 0x33, 0x35, 0x14, 0x14, 0x14, 0x14,  /* totalCoef==11 */
  0x40, 0x40, 0x40, 0x40, 0x41, 0x41, 0x41, 0x41,  /* prefix 000 */
  0xC8, 0x34, 0x22, 0x22, 0x13, 0x13, 0x13, 0x13,  /* totalCoef==12 */
  0x40, 0x40, 0x40, 0x40, 0x41, 0x41, 0x41, 0x41,  /* prefix 000 */
  0x30, 0x31, 0x23, 0x23, 0x12, 0x12, 0x12, 0x12,  /* totalCoef==13 */
  0x20, 0x20, 0x21, 0x21, 0x12, 0x12, 0x12, 0x12,  /* totalCoef==14 */
  0x10, 0x10, 0x10, 0x10, 0x11, 0x11, 0x11, 0x11,  /* totalCoef==15 */
};


/*
 * The structure of the code is XXXXYYYY where XXXX is the length of the code
 * and YYYY is the number of zero coefficients.
 */
static const u_int8 totalZerosTabChroma[3][8] = {
  {0x33, 0x32, 0x21, 0x21, 0x10, 0x10, 0x10, 0x10},
  {0x22, 0x22, 0x21, 0x21, 0x10, 0x10, 0x10, 0x10},
  {0x11, 0x11, 0x11, 0x11, 0x10, 0x10, 0x10, 0x10}
};


/*
 * The structure of the code is XXXXYYYY where XXXX is the length of the code
 * and YYYY is run length.
 */
static const u_int8 runBeforeTab[7][8] = {
  {0x11, 0x11, 0x11, 0x11, 0x10, 0x10, 0x10, 0x10},
  {0x22, 0x22, 0x21, 0x21, 0x10, 0x10, 0x10, 0x10},
  {0x23, 0x23, 0x22, 0x22, 0x21, 0x21, 0x20, 0x20},
  {0x34, 0x33, 0x22, 0x22, 0x21, 0x21, 0x20, 0x20},
  {0x35, 0x34, 0x33, 0x32, 0x21, 0x21, 0x20, 0x20},
  {0x31, 0x32, 0x34, 0x33, 0x36, 0x35, 0x20, 0x20},
  {0x00, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30},
};

#ifndef AVC_ARM_ASSEMBLY

/* Fast look-up for uvlc codes with max length of 7 bits */
static const int8 uvlcLookup[128] = {
  7, 6, 5, 5, 4, 4, 4, 4,                                          // 0000xxx
  7*16+7, 7*16+8, 7*16+9,7*16+10,7*16+11,7*16+12,7*16+13,7*16+14,  // 0001xxx
  5*16+3, 5*16+3, 5*16+3, 5*16+3, 5*16+4, 5*16+4, 5*16+4, 5*16+4,  // 001xxxx
  5*16+5, 5*16+5, 5*16+5, 5*16+5, 5*16+6, 5*16+6, 5*16+6, 5*16+6,
  3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1,  // 010xxxx
  3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1, 3*16+1,
  3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2,  // 011xxxx
  3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2, 3*16+2,
  1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0,  // 1xxxxxx
  1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0,
  1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0,
  1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0,
  1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0,
  1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0,
  1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0,
  1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0, 1*16+0,
};

#endif


/*
 * Static function prototypes
 */

static int getCoefLevelVLC0(bitbuffer_s *bitbuf);

static int getCoefLevelVLCN(bitbuffer_s *bitbuf, int tabNum);

static int get4x4coefs(bitbuffer_s *bitbuf, int coef[4][4],
                       int blkIdxX, int blkIdxY, int8 *numCoefUpPred,
                       int8 *numCoefLeftPred, int mbAvailbits, int dcSkip);

static int get2x2coefsCDC(bitbuffer_s *bitbuf, int coef[4], int *numCoef);



/*
 * Functions begin here
 */

#ifndef AVC_ARM_ASSEMBLY

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
unsigned int vldGetUVLC(bitbuffer_s *bitbuf)
{
  int prefixLen;
  u_int32 bits;
  u_int32 c;

  bibShowMax8bits(bitbuf, 7, &bits);

  c = uvlcLookup[bits];

  if (bits >= 8) {
    bibSkipBits(bitbuf, c >> 4);
    return (unsigned int) (c & 15);
  }

  bibSkipBits(bitbuf, c);
  prefixLen = c - 1;

  do {
    prefixLen += 1;
    if (prefixLen > VLD_MAX_CW_LEN/2) {
      bibRaiseError(bitbuf, BIB_ERR_BIT_ERROR);
      return 0;
    }
    bibGetBit(bitbuf, &bits);
  } while (bits == 0);


  bibGetMax16bits(bitbuf, prefixLen, &c);

  c = c + (1<<prefixLen)-1;

  if (c > VLD_MAX_UVLC_CODE_NUM) {
    /* We encoutered overlong codeword or we encoutered too big code */
    bibRaiseError(bitbuf, BIB_ERR_BIT_ERROR);
    return 0;
  }

  return (unsigned int) c;
}

#endif


/*
 *
 * vldGetUVLClong:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      code                  Return pointer for code
 *
 * Function:
 *      Decode long UVLC codeword.
 *
 * Returns:
 *      Codenumber in the range [0, 2^32-1]
 *
 */
u_int32 vldGetUVLClong(bitbuffer_s *bitbuf)
{
  u_int32 c, cLo;
  int prefixLen, len0;
  int bits;

  prefixLen = -1;

  do {
    bibGetBit(bitbuf, &bits);
    prefixLen += 1;

    /* Is codeword too long? */
    if (prefixLen > VLD_MAX_LONG_CW_LEN/2) {
      bibRaiseError(bitbuf, BIB_ERR_BIT_ERROR);
      return 0;
    }

  } while (bits == 0);

  len0 = min(24, prefixLen);
  bibGetBits(bitbuf, len0, &c);

  if (prefixLen > 24) {
    /* We have to read bits in two pieces because bibGetBits can only fetch */
    /* max. 24 bits */
    bibGetMax16bits(bitbuf, prefixLen-24, &cLo);
    c = (c << (prefixLen-24)) | cLo;  /* Combine two pieces */

    if (prefixLen == VLD_MAX_LONG_CW_LEN/2) {
      /* Is codeword too big? */
      if (c != 0) {
        bibRaiseError(bitbuf, BIB_ERR_BIT_ERROR);
        return 0;
      }
      else
        return (u_int32)VLD_MAX_LONG_UVLC_CODE_NUM;  /* Otherwise, return maximum 32-bit code number */
    }
  }

  return (c + (1<<prefixLen)-1);
}


/*
 *
 * vldGetSignedUVLC:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Decode an UVLC codeword and produce signed integer.
 *
 * Returns:
 *      Code in the range [-32768,32767].
 *
 */
int vldGetSignedUVLC(bitbuffer_s *bitbuf)
{
  unsigned int codeNum;
  int code;

  codeNum = vldGetUVLC(bitbuf);

  /* Decode magnitude */
  code = (int)(((int32)codeNum+1)>>1);

  /* Decode sign */
  if ((codeNum & 1) == 0)
    code = -code;

  return code;
}


/*
 *
 * vldGetSignedUVLClong:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Decode an UVLC codeword and produce signed 32-bit integer
 *
 * Returns:
 *      Code in the range [-2^31, 2^31-1]
 *
 */
int32 vldGetSignedUVLClong(bitbuffer_s *bitbuf)
{
  u_int32 codeNum;
  int32 code;

  codeNum = vldGetUVLClong(bitbuf);

  /* Decode magnitude */
  code = (int32)((codeNum >> 1) + (codeNum & 1));

  /* Decode sign */
  if ((codeNum & 1) == 0)
    code = -code;

  return code;
}


/*
 *
 * vldGetFLC:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      len                   Length of the code
 *
 * Function:
 *      Get Fixed Length Code (max length 16 bits).
 *
 * Returns:
 *      Code
 *
 */
unsigned int vldGetFLC(bitbuffer_s *bitbuf, int len)
{
  u_int32 code;

  bibGetMax16bits(bitbuf, len, &code);

  return (unsigned int)code;
}


/*
 *
 * setChromaCbp:
 *
 * Parameters:
 *      nc                    If 0, all CBP are zero
 *      cbpDC                 Coded Bit Pattern for chroma DC
 *      cbp                   Coded Bit Pattern for chroma AC
 *
 * Function:
 *      Set chroma DC and AC CBP values
 *      nc = 0:   No coefficients
 *      nc = 1:   Only nonzero DC coefficients
 *      nc = 2:   Nonzero AC and DC coefficients
 *
 * Returns:
 *      -
 */
void setChromaCbp(int nc, int *cbpDC, int *cbp)
{
  if (nc == 0)
    *cbpDC = *cbp = 0;
  else if (nc == 1)
    *cbpDC = 3, *cbp = 0;
  else
    *cbpDC = 3, *cbp = (1<<2*BLK_PER_MB/2*BLK_PER_MB/2)-1;
}


/*
 *
 * getLumaBlkCbp:
 *
 * Parameters:
 *      cbpY                  CBP for 8x8 blocks
 *
 * Function:
 *      Convert Codec Block Pattern of 8x8 blocks to Codec Block Pattern for
 *      4x4 blocks. If 8x8 block has nonzero coefficients then all 4x4 blocks
 *      within that 8x8 block are marked nonzero.
 *
 * Returns:
 *      CBP for 4x4 blocks
 *
 */
int getLumaBlkCbp(int cbpY)
{
  int cbp;

  cbp  = (cbpY & (1<<0)) == 0 ? 0 : 0x0033;
  cbp |= (cbpY & (1<<1)) == 0 ? 0 : 0x00cc;
  cbp |= (cbpY & (1<<2)) == 0 ? 0 : 0x3300;
  cbp |= (cbpY & (1<<3)) == 0 ? 0 : 0xcc00;

  return cbp;
}


/*
 *
 * vldGetRunIndicator:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Get the amount of copy macroblocks.
 *
 * Returns:
 *      The number of copy MBs
 *
 */
unsigned int vldGetRunIndicator(bitbuffer_s *bitbuf)
{
  return vldGetUVLC(bitbuf);
}


/*
 *
 * vldGetMBtype:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      hdr                   Return pointer for MB params
 *      picType               Type of current picture (intra/inter)
 *
 * Function:
 *      Get macroblock type. If MB is 16x16 intra then form cbp. Subblock
 *      mode are also fetched if main mode is 8x8 inter.
 *
 * Returns:
 *      VLD_OK for no error and VLD_ERROR for error.
 *
 */
int vldGetMBtype(bitbuffer_s *bitbuf, macroblock_s *mb, int picType)
{
  unsigned int code;
  int nc;
  int i;

  /* Get macroblock mode */
  code = vldGetUVLC(bitbuf);

  if (IS_SLICE_I(picType)) {
    /* INTRA macroblock in INTRA slice */
    if (code >= VLD_NUM_MB_CODES_INTRA)
      return VLD_ERROR;
  }
  else {
    if (code >= VLD_NUM_MB_CODES_INTER)
      return VLD_ERROR;

    if (code >= 5) {
      /* INTRA macroblock in INTER slice */
      code -= 5;
    }
    else {
      /* INTER macroblock in INTER slice */
      mb->interMode = code+1;
      mb->type = MB_TYPE_INTER_SKIPPED + mb->interMode;
      mb->type = min(mb->type, MB_TYPE_INTER_8x8);

      if (mb->interMode >= 4) {

        /*
         * Get sub-macroblock mode modes
         */

        for (i = 0; i < 4; i++) {
          code = vldGetUVLC(bitbuf);

          if (code > VLD_MAX_SUB_MB_MODE)
            return VLD_ERROR;

          mb->subMbModes[i] = code;
        }

      }

      return VLD_OK;
    }
  }

  /*
   * This is INTRA macroblock, find out INTRA type
   */

  if (code == 0) {
    mb->type = MB_TYPE_INTRA_4x4;
  }
  else if (code != VLD_NUM_MB_CODES_INTRA-1) {
    /* 16x16 INTRA - compose cbp value */
    mb->type = MB_TYPE_INTRA_16x16;
    code -= 1;
    mb->intraMode = code & 3;
    code >>= 2;
    if (code < 3) {
      nc = code;
      mb->cbpY = 0;
    }
    else {
      nc = code-3;
      mb->cbpY = 0xffff;
    }
    setChromaCbp(nc, &mb->cbpChromaDC, &mb->cbpC);
  }
  else {
    mb->type = MB_TYPE_INTRA_PCM;
    mb->cbpY = 0xffff;
    mb->cbpC = 0xff;
    mb->cbpChromaDC = 0x3;
  }


  return VLD_OK;
}


/*
 *
 * vldGetIntraPred:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      ipTab                 Return pointer for intra pred. modes
 *
 * Function:
 *      Get 4x4 intra prediction modes. First a one bit flag is read. If flag
 *      is 1, mode is predicted from neighborin blocks. If flag is 0,
 *      additional 3 bit mode code is read. Process is repeated for 16 blocks.
 *
 * Returns:
 *      VLD_OK for no error and VLD_ERROR for error.
 *
 */
int vldGetIntraPred(bitbuffer_s *bitbuf, int8 *ipTab)
{
  int i, j, k, l;
  int bit;
  int modeCode;

  for (j = 0; j < BLK_PER_MB; j+=2) {
    for (i = 0; i < BLK_PER_MB; i+=2) {
      for (k = 0; k < 2; k++) {
        for (l = 0; l < 2; l++) {
          bibGetBit(bitbuf, &bit);    /* Read flag */
          if (bit == 1)               /* If 1, predict from neighbors */
            ipTab[(j+k)*4+i+l] = -1;
          else {                      /* If 0, read mode code */
            bibGetMax8bits(bitbuf, 3, &modeCode);
            ipTab[(j+k)*4+i+l] = (int8)modeCode;
          }
        }
      }
    }
  }

  return VLD_OK;
}


/*
 *
 * vldGetChromaIntraPred:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Get chroma intra prediction mode.
 *
 * Returns:
 *      Prediction mode.
 *
 */
int vldGetChromaIntraPred(bitbuffer_s *bitbuf)
{
  unsigned int mode;

  mode = vldGetUVLC(bitbuf);

  if (mode > VLD_MAX_IPR_CHROMA_MODE)
    return VLD_ERROR;

  return (int)mode;
}


/*
 *
 * vldGetMotVecs:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      interMode             Motion mode (16x16, 8x16, ...)
 *      hasRef                Flag for multiple ref. frames
 *      refNum                Return pointer for ref. indices
 *      predVecs              Return pointer for delta vectors
 *      numVecs               Number of vectors to read
 *
 * Function:
 *      Get reference indices and delta motion vectors for MB
 *
 * Returns:
 *      VLD_OK for no error and VLD_ERROR for error
 *
 */
int vldGetMotVecs(bitbuffer_s *bitbuf, int interMode, int numRefFrames,
                  int *refNum, int predVecs[][2], int numVecs)
{
  int i, j;
  int code;
  int refIdx;

  if (numRefFrames > 1 && interMode < 5) {
    if (numRefFrames == 2) {
      for (i = 0; i < numRefIndices[interMode]; i++) {
        bibGetBit(bitbuf, &refIdx);
        refNum[i] = 1 - refIdx;
      }
    }
    else {
      for (i = 0; i < numRefIndices[interMode]; i++) {
        if ((refNum[i] = (int)vldGetUVLC(bitbuf)) >= numRefFrames)
          return VLD_ERROR;
      }
    }
  }
  else
    refNum[0] = 0;

  for(j = 0; j < numVecs; j++) {
    for(i = 0; i < 2; i++) {
      code = vldGetUVLC(bitbuf);
      predVecs[j][i] = (code+1)>>1;
      if ((code & 1) == 0)
        predVecs[j][i] = -predVecs[j][i];
    }
  }

  return VLD_OK;
}


/*
 *
 * vldGetCBP:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      mbType                Macroblock type (intra/inter)
 *      cbpY                  Return pointer for luma CBP
 *      cbpChromaDC           Return pointer for chroma DC CBP
 *      cbpC                  Return pointer for chroma CBP
 *
 * Function:
 *      Get Coded Block Patterns for both luma and chroma
 *
 * Returns:
 *      VLD_OK for no error and VLD_ERROR for error
 *
 */
int vldGetCBP(bitbuffer_s *bitbuf, int mbType,
              int *cbpY, int *cbpChromaDC, int *cbpC)
{
  unsigned int code;
  int cbp;

  code = vldGetUVLC(bitbuf);

  if (code > VLD_MAX_CBP_CODE)
    return VLD_ERROR;

  if (MBK_IS_INTRA(mbType))
    cbp = code2cbp[code][0];
  else
    cbp = code2cbp[code][1];

  *cbpY = getLumaBlkCbp(cbp%16);
  setChromaCbp(cbp>>4, cbpChromaDC, cbpC);

  return VLD_OK;
}


/*
 *
 * vldGetDeltaqp:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      delta_qp              Return pointer for delta QP
 *
 * Function:
 *      Get macroblock delta QP
 *
 * Returns:
 *      VLD_OK for no error and VLD_ERROR for error
 *
 */
int vldGetDeltaqp(bitbuffer_s *bitbuf, int *delta_qp)
{
  unsigned int code;

  code = vldGetUVLC(bitbuf);

  if (code > VLD_MAX_DELTA_QP_CODE)
    return VLD_ERROR;

  *delta_qp = (code+1)>>1;

  if ((code & 1) == 0)
    *delta_qp = -(*delta_qp);

  return VLD_OK;
}


/*
 *
 * getCoefLevelVLC0:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Get CAVLC coefficient level for VLC0 code format
 *
 * Returns:
 *      Coefficient level
 *
 */
static int getCoefLevelVLC0(bitbuffer_s *bitbuf)
{
  int numLeadingZeroBits;
  u_int32 bits;
  int len;
  int coef;

  bibShowMax16bits(bitbuf, 16, &bits);

  if (bits > 0x0003) {
    if (bits > 0x00ff)
      numLeadingZeroBits = numLeadZerosTab[(int)(bits>>(16-7))];
    else
      numLeadingZeroBits = 7 + numLeadZerosTab[(int)(bits>>(16-7-7))];

    coef = (numLeadingZeroBits >> 1) + 1;
    if (numLeadingZeroBits & 1)
      coef = -coef;

    len = numLeadingZeroBits + 1;
    bibSkipBits(bitbuf, len);
  }
  else if (bits > 0x0001) {
    bibGetBits(bitbuf, 19, &bits);
    coef = 8 + (((int)bits & 15) >> 1);
    if (bits & 1)
      coef = -coef;
  }
  else {
    bibShowBits(bitbuf, 18, &bits);
    if (bits > 0) {
      numLeadingZeroBits = 18 - 7 + numLeadZerosTab[(int)bits];
      bibSkipBits(bitbuf, numLeadingZeroBits + 1);
      bibGetMax16bits(bitbuf, numLeadingZeroBits - 3, &bits);
      coef = 16 + ((int)bits >> 1);
      if (numLeadingZeroBits >= 16)
        coef += (1 << (numLeadingZeroBits - 4)) - 2048;
      if (bits & 1)
        coef = -coef;
    }
    else {
      bibRaiseError(bitbuf, BIB_ERR_BIT_ERROR);
      coef = 0;
    }
  }

  return coef;
}

/*
 *
 * getCoefLevelVLCN:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      tabNum                VLC table number to be used
 *
 * Function:
 *      Get CAVLC coefficient level for VLC1-6 code format
 *
 * Returns:
 *      Coefficient level
 *
 */
static int getCoefLevelVLCN(bitbuffer_s *bitbuf, int tabNum)
{
  int numLeadingZeroBits;
  u_int32 bits;
  int len;
  int coef;

  bibShowBits(bitbuf, 21, &bits);

  if (bits > 0x00003f) {
    if (bits > 0x001fff)
      numLeadingZeroBits = numLeadZerosTab[(int)(bits>>(21-7))];
    else
      numLeadingZeroBits = 7 + numLeadZerosTab[(int)(bits>>(21-7-7))];

    len = numLeadingZeroBits + 1 + tabNum;
    bits = (bits >> (21 - len)) & ((1 << tabNum) - 1);
    coef = (int)((numLeadingZeroBits << (tabNum - 1)) + (bits >> 1) +  1);
    if (bits & 1)
      coef = -coef;

    bibSkipBits(bitbuf, len);
  }
  else if (bits > 0x000007) {
    numLeadingZeroBits = 21 - 7 + numLeadZerosTab[(int)bits];
    bibSkipBits(bitbuf, numLeadingZeroBits + 1);
    bibGetMax16bits(bitbuf, numLeadingZeroBits - 3, &bits);
    coef = (15 << (tabNum - 1)) + ((int)bits >> 1) + 1;
    if (numLeadingZeroBits >= 16)
      coef += (1 << (numLeadingZeroBits - 4)) - 2048;
    if (bits & 1)
      coef = -coef;
  }
  else {
    bibRaiseError(bitbuf, BIB_ERR_BIT_ERROR);
    coef = 0;
  }

  return coef;
}


/*
 *
 * get4x4coefs:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      coef                  Return pointer for 4x4 coefficients
 *      blkIdxX               Horizontal block pos. within MB
 *      blkIdxY               Vertical block pos. within MB
 *      numCoefUpPred         Block coefficients counts of upper block
 *      numCoefLeftPred       Block coefficients counts of left block
 *      mbAvailBits           Macroblock availability flags
 *      dcSkip                if 1, there's no DC coefficient
 *
 * Function:
 *      Decode coefficients for 4x4 block.
 *
 * Returns:
 *      VLD_OK for no error, VLD_ERROR for error
 *
 */
static int get4x4coefs(bitbuffer_s *bitbuf, int coef[4][4],
                       int blkIdxX, int blkIdxY, int8 *numCoefUpPred,
                       int8 *numCoefLeftPred, int mbAvailBits, int dcSkip)
{
  int numCoefPred;
  int tabNum;
  u_int32 bits;
  int code;
  int numTrailingOnes;
  int numLeadingZeroBits;
  int totalCoef;
  int numBits;
  u_int32 flc;
  int tmpLevel[16];
  int level;
  int numBigCoef;
  u_int32 signs;
  int i;
  const u_int8 *totalZerosPtr;
  int offset;
  int totalZeros;
  int zerosLeft;
  int run;
  int coefPos;
  int coefNum;

  static const int vlcNumTab[8] = {
    0, 0, 1, 1, 2, 2, 2, 2
  };

  static const unsigned int incVlc[7] = {
    0,3,6,12,24,48,32768          /* maximum vlc = 6 */
  };

  static const int zigZagPos[16] = {
    0, 1, 4, 8, 5, 2, 3, 6, 9, 12, 13, 10, 7, 11, 14, 15
  };

  /*
   * Decode number of coefficients and number of trailing ones
   */

  /* Predict number of coefficients from neighboring blocks */
  if (blkIdxX || (mbAvailBits & 1)) {
    numCoefPred = numCoefLeftPred[0];
    if (blkIdxY || (mbAvailBits & 2))
      numCoefPred = (numCoefPred + numCoefUpPred[0] + 1) >> 1;
  }
  else
    numCoefPred = (blkIdxY || (mbAvailBits & 2)) ? numCoefUpPred[0] : 0;

  /* Select variable length code or fixed length decoding */
  if (numCoefPred < 8) {

    /* Use variable length code  */

    /* Select table number based on the prediction */
    tabNum = vlcNumTab[numCoefPred];

    bibShowBits(bitbuf, 18, &bits);

    /* Compute number of leading zeros using look-up table */
    if (bits >= 0x00400)
      numLeadingZeroBits = numLeadZerosTab[(int)(bits>>(18-7))];
    else
      numLeadingZeroBits = 7 + numLeadZerosTab[(int)(bits>>(18-7-7))];

    /* Shift excess bits away */
    bits >>= 18-4-numLeadingZeroBits;

    /* numTrailingOnes, totalCoef and length of the codeword are codec in one code */
    code = numCoefTrailTab[tabNum][numLeadingZeroBits][(int)bits&7];

    /* Total number of bits in codeword is sum of the number of leading zero bits,     */
    /* 1 one bit and the number of bits in postfix. We know the number of leading zero */
    /* bits. Postfix length is extracted from 2 highest bits of code.                  */
    numBits = numLeadingZeroBits + 1 + (code >> 6);

    bibSkipBits(bitbuf, numBits);

    if ((code & 0x3f) == 2) {
      /* All coefficients are zero */
      numCoefUpPred[0] = numCoefLeftPred[0] = 0;
      return VLD_OK;
    }
    else {
      /* 2 lowest bits contains number of trailing ones */
      numTrailingOnes = code & 3;
      /* 4 middle bits contain total number of coefficients minus 1 */
      totalCoef = ((code >> 2) & 15) + 1;
    }
  }
  else {

    /* Use fixed length code  */

    bibGetMax8bits(bitbuf, 6, &flc);

    if (flc != 3) {
      /* 2 lowest bits contains number of trailing ones */
      numTrailingOnes = (int)flc & 0x03;
      /* high bits contain total number of coefficients minus 1 */
      totalCoef = ((int)flc >> 2) + 1;
      if (totalCoef < numTrailingOnes)
        return VLD_ERROR;
    }
    else {
      /* All coefficients are zero */
      numCoefUpPred[0] = numCoefLeftPred[0] = 0;
      return VLD_OK;
    }
  }

  numCoefUpPred[0] = numCoefLeftPred[0] = (int8) totalCoef;


  /*
   * Decode signs for trailing ones and store trailing ones in tmpLevel.
   */

  numBigCoef = totalCoef - numTrailingOnes; 

  if (numTrailingOnes != 0) {

    /* Get signs for trailing ones. There can be maximum of 3 of them */
    bibGetMax8bits(bitbuf, numTrailingOnes, &signs);

    tmpLevel[numBigCoef] = 1 - 2*(signs&1);
    if (numTrailingOnes >= 2) {
      tmpLevel[numBigCoef+1] = 1 - (signs&2);
      if (numTrailingOnes > 2)
        tmpLevel[numBigCoef+2] = 1 - ((signs&4)>>1);
    }
  }

  if (numBigCoef != 0) {

    /*
     * Decode first "big" level
     */

    if (totalCoef > 10 && numTrailingOnes < 3)
      level = getCoefLevelVLCN(bitbuf, 1);
    else
      level = getCoefLevelVLC0(bitbuf);

    if (numTrailingOnes < 3)
      level += (level > 0) ? 1 : -1;

    tmpLevel[numBigCoef-1] = level;

    tabNum = (labs((int32)level) > 3) ? 2 : 1;

    /*
     * Decode rest of the "big" levels
     */

    for (i = numBigCoef - 2; i >= 0; i--) {

      level = getCoefLevelVLCN(bitbuf, tabNum);

      tmpLevel[i] = level;

      /* update VLC table number */
      if (labs((int32)level) > (int32)incVlc[tabNum])
        tabNum++;
    }

  }

  /*
   * Get total number of zero coefficients
   */

  if (totalCoef < 16-dcSkip) {

    bibShowMax16bits(bitbuf, 9, &bits);

    totalZerosPtr = &totalZerosTab[totalZerosTabOffset[totalCoef-1]];
    code = totalZerosPtr[(int)bits>>6];

    if (code > 0xc0) {
      offset = code - 0xc0;
      code = totalZerosPtr[offset+(((int)bits>>3)&7)];
      if (code > 0xc0) {
        offset = code - 0xc0;
        code = totalZerosPtr[offset+((int)bits&7)];
      }
    }

    totalZeros = code & 15;

    numBits = code >> 4;
    bibSkipBits(bitbuf, numBits);
  }
  else
    totalZeros = 0;

  if (dcSkip + totalCoef + totalZeros > 16)
    return VLD_ERROR;

  /* All coefficients are initially zero */
  for (i = 0; i < 4; i++) {
    coef[i][0] = 0;
    coef[i][1] = 0;
    coef[i][2] = 0;
    coef[i][3] = 0;
  }

  /*
   * Get run of zeros before each coefficient and store coeffs. in tmpCoef
   */

  zerosLeft = totalZeros;
  coefPos = dcSkip + totalCoef + totalZeros - 1;
  coefNum = totalCoef - 1;

  while (zerosLeft > 0 && coefNum > 0) {

    coef[0][zigZagPos[coefPos]] = tmpLevel[coefNum];

    // select VLC for runbefore
    tabNum = zerosLeft <= 7 ? zerosLeft-1 : 6;

    bibShowMax8bits(bitbuf, 3, &bits);

    if (tabNum == 6 && bits == 0) {
      bibShowMax16bits(bitbuf, 11, &bits);
      if (bits == 0)
        return VLD_ERROR;
      numLeadingZeroBits = numLeadZerosTab[(int)bits>>1];
      run = 7 + numLeadingZeroBits;
      if (run > zerosLeft)
        return VLD_ERROR;
      numBits = 4 + numLeadingZeroBits;
    }
    else {
      code = runBeforeTab[tabNum][(int)bits];
      run = code & 15;
      numBits = code >> 4;
    }

    bibSkipBits(bitbuf, numBits);

    zerosLeft -= run;
    coefPos -= run + 1;
    coefNum--;
  }

  do {
    coef[0][zigZagPos[coefPos]] = tmpLevel[coefNum];
    coefPos--;
    coefNum--;
  } while (coefNum >= 0);

  return VLD_OK;
}


/*
 *
 * get2x2coefsCDC:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      coef                  Return pointer for 2x2 coefficients
 *      numCoef               Return pointer number of nonzero cefficients
 *
 * Function:
 *      Decode coefficients for 2x2 DC block.
 *
 * Returns:
 *      VLD_OK for no error, VLD_ERROR for error
 *
 */
static int get2x2coefsCDC(bitbuffer_s *bitbuf, int coef[4], int *numCoef)
{
  int tabNum;
  u_int32 bits;
  int code;
  int numTrailingOnes;
  int numLeadingZeroBits;
  int totalCoef;
  int numBits;
  int tmpLevel[4];
  int level;
  int numBigCoef;
  u_int32 signs;
  int i;
  int totalZeros;
  int zerosLeft;
  int run;
  int coefPos;
  int coefNum;

  static const unsigned int incVlc[7] = {
    0,3,6,12,24,48,32768          /* maximum vlc = 6 */
  };


  /*
   * Decode number of coefficients and number of trailing ones
   */

  bibShowMax16bits(bitbuf, 10, &bits);

  /* Compute number of leading zeros using look-up table */
  numLeadingZeroBits = numLeadZerosTab[(int)bits>>(10-7)];

  /* Shift excess bits away */
  bits >>= 10-3-numLeadingZeroBits;

  /* Fetch numTrailingOnes and totalCoef */
  code = numCoefTrailTabChroma[numLeadingZeroBits][(int)bits&3];

  numTrailingOnes = code & 3;
  totalCoef = (code >> 2) & 7;

  numBits = (code >> 5) + 1;

  bibSkipBits(bitbuf, numBits);

  *numCoef = totalCoef;

  if (totalCoef == 0)
    return VLD_OK;


  /*
   * Decode signs for trailing ones
   */
  numBigCoef = totalCoef - numTrailingOnes; 

  if (numTrailingOnes != 0) {

    /* Get signs for trailing ones. There can be maximum of 3 of them */
    bibGetMax8bits(bitbuf, numTrailingOnes, &signs);

    tmpLevel[numBigCoef] = 1 - 2*(signs&1);
    if (numTrailingOnes >= 2) {
      tmpLevel[numBigCoef+1] = 1 - (signs&2);
      if (numTrailingOnes > 2)
        tmpLevel[numBigCoef+2] = 1 - ((signs&4)>>1);
    }
  }

  if (numBigCoef != 0) {

    /*
     * Decode first level
     */
    level = getCoefLevelVLC0(bitbuf);

    if (numTrailingOnes < 3)
      level += (level > 0) ? 1 : -1;

    tmpLevel[numBigCoef-1] = level;

    tabNum = (labs((int32)level) > 3) ? 2 : 1;

    /*
     * Decode rest of the levels
     */
    for (i = numBigCoef - 2; i >= 0; i--) {

      level = getCoefLevelVLCN(bitbuf, tabNum);

      tmpLevel[i] = level;

      /* update VLC table number */
      if (labs((int32)level) > (int32)incVlc[tabNum])
        tabNum++;
    }
  }

  /*
   * Get total zeros
   */
  if (totalCoef < 4) {
    bibShowMax8bits(bitbuf, 3, &bits);
    code = totalZerosTabChroma[totalCoef-1][(int)bits];
    totalZeros = code & 15;
    numBits = code >> 4;
    bibSkipBits(bitbuf, numBits);
  }
  else
    totalZeros = 0;

  /* All coefficients are initially zero */
  coef[0] = 0;
  coef[1] = 0;
  coef[2] = 0;
  coef[3] = 0;

  /*
   * Get run before each coefficient
   */
  zerosLeft = totalZeros;
  coefPos = totalCoef + totalZeros - 1;
  coefNum = totalCoef - 1;

  while (zerosLeft > 0 && coefNum > 0) {

    coef[coefPos] = tmpLevel[coefNum];

    bibShowMax8bits(bitbuf, 3, &bits);

    code = runBeforeTab[zerosLeft-1][(int)bits];
    run = code & 15;
    numBits = code >> 4;

    bibSkipBits(bitbuf, numBits);

    zerosLeft -= run;
    coefPos -= run + 1;
    coefNum--;
  }

  do {
    coef[coefPos] = tmpLevel[coefNum];
    coefPos--;
    coefNum--;
  } while (coefNum >= 0);

  return VLD_OK;
}


/*
 *
 * vldGetLumaDCcoeffs:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      coef                  Return pointer for 4x4 coefficients
 *      numCoefUpPred         Block coefficients counts of upper block
 *      numCoefLeftPred       Block coefficient counts of blocks to the left
 *      mbAvailBits           Macroblock availability flags
 *
 * Function:
 *      Decode coefficients for 4x4 luma DC block.
 *
 * Returns:
 *      VLD_OK for no error, negative value for error
 *
 */
int vldGetLumaDCcoeffs(bitbuffer_s *bitbuf, int coef[4][4],
                       int8 *numCoefUpPred, int8 *numCoefLeftPred,
                       int mbAvailBits)
{
  int j;
  int8 numCoef   = *numCoefUpPred;
  int8 numCoefLP = *numCoefLeftPred;
  int retCode;

  retCode = get4x4coefs(bitbuf, coef, 0, 0, &numCoef, &numCoefLP, mbAvailBits, 0);

  if (retCode < 0)
    return retCode;

  if (numCoef == 0) {
    for (j = 0; j < 4; j++) {
      coef[j][0] = 0;
      coef[j][1] = 0;
      coef[j][2] = 0;
      coef[j][3] = 0;
    }
  }

  return VLD_OK;
}


/*
 *
 * vldGetLumaCoeffs:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      mbType                Macroblock type (intraXxX/interXxX)
 *      cbpY                  Return pointer coded block pattern
 *      coef                  Return pointer for 16x4x4 coefficients
 *      numCoefUpPred         Block coefficients counts of upper block
 *      numCoefLeftPred       Block coefficient counts of blocks to the left
 *      mbAvailBits           Macroblock availability flags
 *
 * Function:
 *      Decode coefficients for 16 4x4 luma blocks.
 *
 * Returns:
 *      VLD_OK for no error, negative value for error
 *
 */
int vldGetLumaCoeffs(bitbuffer_s *bitbuf, int mbType,
                     int *cbpY, int coef[4][4][4][4], int8 *numCoefUpPred,
                     int8 *numCoefLeftPred, int mbAvailBits)
{
  int bx, by;
  int blkIdxX, blkIdxY;
  int i, j;
  int cbp, cbpTemp;
  int dcSkip;
  int retCode;

  dcSkip = MBK_IS_INTRA_16x16(mbType) ? 1 : 0;

  cbp = cbpTemp = *cbpY;

  for (by = 0; by < 4; by+=2) {
    for (bx = 0; bx < 4; bx+=2) {

      /* Check if any of the blocks in the current 8x8 block is codec */
      if ((cbpTemp & 33) != 0) {
        for (j = 0; j < 2; j++) {
          for (i = 0; i < 2; i++) {

            blkIdxX = bx + i;
            blkIdxY = by + j;

            retCode = get4x4coefs(bitbuf, coef[blkIdxY][blkIdxX], blkIdxX, blkIdxY,
                                  &numCoefUpPred[blkIdxX], &numCoefLeftPred[blkIdxY],
                                  mbAvailBits, dcSkip);

            if (retCode < 0)
              return retCode;

            if (numCoefUpPred[blkIdxX] == 0)
              cbp &= ~(1<<(blkIdxY*BLK_PER_MB+blkIdxX));
          }

        }
      }
      else {
        numCoefUpPred[bx]   = 0;
        numCoefUpPred[bx+1] = 0;
        numCoefLeftPred[by]   = 0;
        numCoefLeftPred[by+1] = 0;
      }

      cbpTemp >>= 2;
    }
    cbpTemp >>= 4;
  }

  *cbpY = cbp;

  return VLD_OK;
}


/*
 *
 * vldGetChromaDCcoeffs:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      coef                  Return pointer for 2x2x2 coefficients
 *      cbpYDC                Return pointer chroma DC coded block pattern
 *
 * Function:
 *      Decode coefficients for 2 2x2 chroma DC blocks.
 *
 * Returns:
 *      VLD_OK for no error, negative value for error
 *
 */
int vldGetChromaDCcoeffs(bitbuffer_s *bitbuf, int coef[2][2][2], int *cbpDC)
{
  int comp;
  int numCoef;
  int retCode;

  for (comp = 0; comp < 2; comp++) {

    retCode = get2x2coefsCDC(bitbuf, &coef[comp][0][0], &numCoef);

    if (retCode < 0)
      return retCode;
      
    if (numCoef == 0)
      *cbpDC &= ~(1<<comp);
  }

  return VLD_OK;
}


/*
 *
 * vldGetChromaCoeffs:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      coef                  Return pointer for 2x2x2x4x4 coefficients
 *      cbp                   Return pointer chroma coded block pattern
 *      numCoefUpPred         Block coefficients counts of upper block for U frame
 *      numCoefUpPredV        Block coefficients counts of upper block for V frame
 *      numCoefLeftPred       Block coefficient counts of blocks to the left for U frame
 *      numCoefLeftPredV      Block coefficient counts of blocks to the left for V frame
 *      mbAvailBits           Macroblock availability flags
 *
 * Function:
 *      Decode coefficients for 8 4x4 chroma blocks.
 *
 * Returns:
 *      VLD_OK for no error, negative value for error
 *
 */
int vldGetChromaCoeffs(bitbuffer_s *bitbuf, int coef[2][2][2][4][4], int *cbp,
                       int8 *numCoefUpPred, int8 *numCoefUpPredV,
                       int8 *numCoefLeftPred, int8 *numCoefLeftPredV,
                       int mbAvailBits)
{
  int comp;
  int i, j;
  int retCode;

  for (comp = 0; comp < 2; comp++) {

    for (j = 0; j < 2; j++) {
      for (i = 0; i < 2; i++) {

        retCode = get4x4coefs(bitbuf, coef[comp][j][i], i, j, &numCoefUpPred[i],
                              &numCoefLeftPred[j], mbAvailBits, 1);

        if (retCode < 0)
          return retCode;

        if (numCoefUpPred[i] == 0)
          *cbp &= ~(1<<(comp*4+j*2+i));
      }

    }

    /* Switch to V frame */
    numCoefUpPred = numCoefUpPredV;
    numCoefLeftPred = numCoefLeftPredV;
  }

  return VLD_OK;
}


/*
 *
 * vldGetZeroLumaCoeffs:
 *
 * Parameters:
 *      numCoefUpPred         Block coefficient counts of upper block
 *      numCoefLeftPred       Block coefficient counts of blocks to the left
 *
 * Function:
 *      Called when there are no luma coefficients.
 *      Sets luma cefficient counts to zero for current MB.
 *
 * Returns:
 *      -
 */
void vldGetZeroLumaCoeffs(int8 *numCoefUpPred, int8 *numCoefLeftPred)
{
  int i;

  for (i = 0; i < 4; i++) {
    numCoefUpPred[i] = 0;
    numCoefLeftPred[i] = 0;
  }
}


/*
 *
 * vldGetZeroChromaCoeffs:
 *
 * Parameters:
 *      numCoefUpPredU        Block coefficient counts of upper block for U frame
 *      numCoefUpPredV        Block coefficient counts of upper block for V frame
 *      numCoefLeftPred       Block coefficient counts of blocks to the left
 *
 * Function:
 *      Called when there are no chroma coefficients.
 *      Sets chroma cefficient counts to zero for current MB.
 *
 * Returns:
 *      -
 */
void vldGetZeroChromaCoeffs(int8 *numCoefUpPredU, int8 *numCoefUpPredV,
                            int8 numCoefLeftPred[2][2])
{
  int i;

  for (i = 0; i < 2; i++) {
    numCoefUpPredU[i] = 0;
    numCoefUpPredV[i] = 0;
    numCoefLeftPred[0][i] = 0;
    numCoefLeftPred[1][i] = 0;
  }
}


/*
 *
 * vldGetAllCoeffs:
 *
 * Parameters:
 *      numCoefUpPredY        Block coefficient counts for Y frame
 *      numCoefUpPredU        Block coefficient counts for U frame
 *      numCoefUpPredV        Block coefficient counts for V frame
 *      numCoefLeftPredY      Luma block coefficient counts of blocks to the left
 *      numCoefLeftPredC      Chroma block coefficient counts of blocks to the left
 *
 * Function:
 *      Called when all coefficients are non-zero (e.g. PCM mactroblock).
 *      Sets cefficient counts to "all coded".
 *
 * Returns:
 *      -
 */
void vldGetAllCoeffs(int8 *numCoefUpPredY, int8 *numCoefUpPredU,
                     int8 *numCoefUpPredV, int8 *numCoefLeftPredY,
                     int8 numCoefLeftPredC[2][2])
{
  int i;

  for (i = 0; i < 4; i++) {
    numCoefUpPredY[i] = 16;
    numCoefLeftPredY[i] = 16;
  }

  for (i = 0; i < 2; i++) {
    numCoefUpPredU[i] = 16;
    numCoefUpPredV[i] = 16;
    numCoefLeftPredC[0][i] = 16;
    numCoefLeftPredC[1][i] = 16;
  }
}
