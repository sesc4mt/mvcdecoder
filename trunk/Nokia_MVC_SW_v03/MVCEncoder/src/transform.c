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
 * transform.c
 *
 * Contains:
 *    Transform and quantization functions.
 *
 */

#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "globals.h"
#include "transform.h"


#define QUANT_INTRA_ADD    (TRA_QUANT_SCALE/3)
#define QUANT_INTER_ADD    (TRA_QUANT_SCALE/6)


static const int16 quantCoef[6][16] = {
  {13107, 8066,13107, 8066, 8066, 5243, 8066, 5243,13107, 8066,13107, 8066, 8066, 5243, 8066, 5243},
  {11916, 7490,11916, 7490, 7490, 4660, 7490, 4660,11916, 7490,11916, 7490, 7490, 4660, 7490, 4660},
  {10082, 6554,10082, 6554, 6554, 4194, 6554, 4194,10082, 6554,10082, 6554, 6554, 4194, 6554, 4194},
  { 9362, 5825, 9362, 5825, 5825, 3647, 5825, 3647, 9362, 5825, 9362, 5825, 5825, 3647, 5825, 3647},
  { 8192, 5243, 8192, 5243, 5243, 3355, 5243, 3355, 8192, 5243, 8192, 5243, 5243, 3355, 5243, 3355},
  { 7282, 4559, 7282, 4559, 4559, 2893, 4559, 2893, 7282, 4559, 7282, 4559, 4559, 2893, 4559, 2893}
};


extern const int8 qpPerTab[52];
extern const int8 qpRemTab[52];


/* array used to find expencive coefficients */
static const int8 COEFF_COST[16] = {
  3,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0
};



/*
 *
 * traDiffDCT4x4:
 *
 * Parameters:
 *      orig            Original values
 *      pred            Prediction values
 *      coef            DCT coefficients
 *
 * Function:
 *      Compute approximate 4x4 forward DCT.
 *
 * Returns:
 *      -
 */
#if X86MMX
void traDiffDCT4x4(u_int8 orig[BLK_SIZE][MBK_SIZE],
                   u_int8 pred[BLK_SIZE][MBK_SIZE],
                   int coef[BLK_SIZE][BLK_SIZE])
{
  __asm {
    mov     eax,[orig]
    mov     ecx,[pred]
    mov     edx,[coef]

    pxor    mm7,mm7

    movd    mm0,[eax]
    movd    mm4,[ecx]
    punpcklbw mm0,mm7
    punpcklbw mm4,mm7
    psubw   mm0,mm4

    movd    mm1,[eax+MBK_SIZE]
    movd    mm4,[ecx+MBK_SIZE]
    punpcklbw mm1,mm7
    punpcklbw mm4,mm7
    psubw   mm1,mm4

    movd    mm2,[eax+2*MBK_SIZE]
    movd    mm4,[ecx+2*MBK_SIZE]
    punpcklbw mm2,mm7
    punpcklbw mm4,mm7
    psubw   mm2,mm4

    movd    mm3,[eax+3*MBK_SIZE]
    movd    mm4,[ecx+3*MBK_SIZE]
    punpcklbw mm3,mm7
    punpcklbw mm4,mm7
    psubw   mm3,mm4

    ;Vertical transform
    movq    mm4,mm0
    movq    mm5,mm1
    paddw   mm0,mm3     ;e
    paddw   mm1,mm2     ;f
    psubw   mm4,mm3     ;e2
    psubw   mm5,mm2     ;f2
    movq    mm2,mm0
    paddw   mm0,mm1     ;dest0
    psubw   mm2,mm1     ;dest2
    movq    mm6,mm4
    paddw   mm4,mm4     ;2*e2
    paddw   mm4,mm5     ;dest1
    psubw   mm6,mm5
    psubw   mm6,mm5     ;dest3

    ;Transpose
    movq    mm3,mm0
    movq    mm5,mm2
    punpcklwd mm3,mm4   ;b1,a1,b0,a0
    punpcklwd mm5,mm6   ;d1,c1,d0,c0
    movq    mm7,mm3
    punpckldq mm3,mm5   ;d0,c0,b0,a0
    punpckhdq mm7,mm5   ;d1,c1,b1,a1

    punpckhwd mm0,mm4
    punpckhwd mm2,mm6
    movq    mm4,mm0
    punpckldq mm0,mm2   ;d2,c2,b2,a2
    punpckhdq mm4,mm2   ;d3,c3,b3,a3

    ;Horizontal hadamard
    movq    mm1,mm3
    movq    mm2,mm7
    paddw   mm3,mm4     ;e
    paddw   mm7,mm0     ;f
    psubw   mm1,mm4     ;e2
    psubw   mm2,mm0     ;f2
    movq    mm6,mm3
    paddw   mm3,mm7     ;dest0
    psubw   mm6,mm7     ;dest2
    movq    mm4,mm1
    paddw   mm1,mm1     ;2*e2
    paddw   mm1,mm2     ;dest1
    psubw   mm4,mm2
    psubw   mm4,mm2     ;dest3

#if 1
    PSHUFW(0,3,0x90)
    psrad   mm0,16
    movd    [edx],mm0
    psrlq   mm0,32
    movd    [edx+2*(BLK_SIZE*4)],mm0
    psrad   mm3,16
    movd    [edx+1*(BLK_SIZE*4)],mm3
    psrlq   mm3,32
    movd    [edx+3*(BLK_SIZE*4)],mm3

    PSHUFW(0,1,0x90)
    psrad   mm0,16
    movd    [edx+4],mm0
    psrlq   mm0,32
    movd    [edx+2*(BLK_SIZE*4)+4],mm0
    psrad   mm1,16
    movd    [edx+1*(BLK_SIZE*4)+4],mm1
    psrlq   mm1,32
    movd    [edx+3*(BLK_SIZE*4)+4],mm1

    PSHUFW(0,6,0x90)
    psrad   mm0,16
    movd    [edx+8],mm0
    psrlq   mm0,32
    movd    [edx+2*(BLK_SIZE*4)+8],mm0
    psrad   mm6,16
    movd    [edx+1*(BLK_SIZE*4)+8],mm6
    psrlq   mm6,32
    movd    [edx+3*(BLK_SIZE*4)+8],mm6

    PSHUFW(0,4,0x90)
    psrad   mm0,16
    movd    [edx+12],mm0
    psrlq   mm0,32
    movd    [edx+2*(BLK_SIZE*4)+12],mm0
    psrad   mm4,16
    movd    [edx+1*(BLK_SIZE*4)+12],mm4
    psrlq   mm4,32
    movd    [edx+3*(BLK_SIZE*4)+12],mm4
#else

    /* This is faster than above only if coef array is 8-byte aligned */

    movq    mm2,mm3
    punpckldq mm3,mm1
    punpckhdq mm2,mm1

    PSHUFW(0,3,0x90)
    psrad   mm0,16
    movq    [edx],mm0
    psrad   mm3,16
    movq    [edx+1*(BLK_SIZE*4)],mm3

    PSHUFW(0,2,0x90)
    psrad   mm0,16
    movq    [edx+2*(BLK_SIZE*4)],mm0
    psrad   mm2,16
    movq    [edx+3*(BLK_SIZE*4)],mm2

    movq    mm2,mm6
    punpckldq mm6,mm4
    punpckhdq mm2,mm4

    PSHUFW(0,6,0x90)
    psrad   mm0,16
    movq    [edx+8],mm0
    psrad   mm6,16
    movq    [edx+1*(BLK_SIZE*4)+8],mm6

    PSHUFW(0,2,0x90)
    psrad   mm0,16
    movq    [edx+2*(BLK_SIZE*4)+8],mm0
    psrad   mm2,16
    movq    [edx+3*(BLK_SIZE*4)+8],mm2
#endif

    emms
  }
}
#else
void traDiffDCT4x4(u_int8 orig[BLK_SIZE][MBK_SIZE],
                   u_int8 pred[BLK_SIZE][MBK_SIZE],
                   int coef[BLK_SIZE][BLK_SIZE])
{
  int tmp[4][4];
  int a, b, c, d;
  int e;
  int f;
  int i;

  /*
   *  A = 13a + 13b + 13c + 13d
   *  B = 17a +  7b -  7c - 17d
   *  C = 13a - 13b - 13c + 13d
   *  D = 7a  - 17b + 17c -  7d
   *
   *  e = a + d
   *  f = b + c
   *  A = 13(e + f)
   *  C = 13(e - f)
   *  e = a - d
   *  f = b - c
   *  B = 17e +  7f
   *  D =  7e - 17f
   */

  /* Horizontal transform */
  for (i = 0; i < 4; i++) {
    a = orig[i][0] - pred[i][0];
    b = orig[i][1] - pred[i][1];
    c = orig[i][2] - pred[i][2];
    d = orig[i][3] - pred[i][3];
    e = a + d;
    f = b + c;
    tmp[i][0] = e + f;
    tmp[i][2] = e - f;
    e = a - d;
    f = b - c;
    tmp[i][1] = 2*e +   f;
    tmp[i][3] =   e - 2*f;

  }

  /* Vertical transform */
  for (i = 0; i < 4; i++) {
    e = tmp[0][i] + tmp[3][i];
    f = tmp[1][i] + tmp[2][i];
    coef[0][i] = e + f;
    coef[2][i] = e - f;
    e = tmp[0][i] - tmp[3][i];
    f = tmp[1][i] - tmp[2][i];
    coef[1][i] = 2*e +   f;
    coef[3][i] =   e - 2*f;
  }
}
#endif


/*
 *
 * traHada4x4:
 *
 * Parameters:
 *      src                   Source values, and also store the results
 *
 * Function:
 *      Compute Hadamard Transform.
 *
 * Returns:
 *      -
 */
void traHada4x4(int src[4][4])
{
  int tmp[4][4];
  int e;
  int f;
  int i;

  /* Horizontal transform */
  for (i = 0; i < 4; i++) {
    e = src[i][0] + src[i][3];
    f = src[i][1] + src[i][2];
    tmp[i][0] = e + f;
    tmp[i][2] = e - f;
    e = src[i][0] - src[i][3];
    f = src[i][1] - src[i][2];
    tmp[i][1] = e + f;
    tmp[i][3] = e - f;
  }

  /* Vertical transform */
  for (i = 0; i < 4; i++) {
    e = tmp[0][i] + tmp[3][i];
    f = tmp[1][i] + tmp[2][i];
    src[0][i] = (e + f)>>1;
    src[2][i] = (e - f)>>1;
    e = tmp[0][i] - tmp[3][i];
    f = tmp[1][i] - tmp[2][i];
    src[1][i] = (e + f)>>1;
    src[3][i] = (e - f)>>1;
  }
}


/*
 *
 * traDCT2x2:
 *
 * Parameters:
 *      src                   Source values, and also store the results
 *
 * Function:
 *      Compute 2x2 forward DCT.
 *
 * Returns:
 *      -
 */
void traDCT2x2(int src[2][2])
{
  int DC0 = src[0][0];
  int DC1 = src[0][1];
  int DC2 = src[1][0];
  int DC3 = src[1][1];
  int A, B;

  /*
   *  DC0 DC1  =>  DDC(0,0) DDC(1,0)
   *  DC2 DC3      DDC(0,1) DDC(1,1)
   *
   *  DDC(0,0) = (DC0+DC1+DC2+DC3)
   *  DDC(1,0) = (DC0-DC1+DC2-DC3)
   *  DDC(0,1) = (DC0+DC1-DC2-DC3)
   *  DDC(1,1) = (DC0-DC1-DC2+DC3)
   */

  A = DC0 + DC2;
  B = DC1 + DC3;
  src[0][0] = (A + B);
  src[0][1] = (A - B);
  A = DC0 - DC2;
  B = DC1 - DC3;
  src[1][0] = (A + B);
  src[1][1] = (A - B);
}


/*
 *
 * traHadamard4x4:
 *
 * Parameters:
 *      src                   Source values, and also store the results
 *
 * Function:
 *      Compute Hadamard Transform and sum of absolute coefficients
 *
 * Returns:
 *      Sum of absolute coefficiets
 *
 */
#if X86MMX
int32 traHadamard4x4(int16 src[4][4])
{
  __asm {
    mov     eax,[src]

    movq    mm0,[eax]
    movq    mm1,[eax+8]
    movq    mm2,[eax+16]
    movq    mm3,[eax+24]

    ;Vertical hadamard
    movq    mm4,mm0
    movq    mm5,mm1
    paddw   mm0,mm3     ;e
    paddw   mm1,mm2     ;f
    psubw   mm4,mm3     ;e2
    psubw   mm5,mm2     ;f2
    movq    mm2,mm0
    paddw   mm0,mm1     ;dest0
    psubw   mm2,mm1     ;dest2
    movq    mm6,mm4
    paddw   mm4,mm5     ;dest1
    psubw   mm6,mm5     ;dest3

    ;Transpose
    movq    mm3,mm0
    movq    mm5,mm2
    punpcklwd mm3,mm4   ;b1,a1,b0,a0
    punpcklwd mm5,mm6   ;d1,c1,d0,c0
    movq    mm7,mm3
    punpckldq mm3,mm5   ;d0,c0,b0,a0
    punpckhdq mm7,mm5   ;d1,c1,b1,a1

    punpckhwd mm0,mm4
    punpckhwd mm2,mm6
    movq    mm4,mm0
    punpckldq mm0,mm2   ;d2,c2,b2,a2
    punpckhdq mm4,mm2   ;d3,c3,b3,a3

    ;Horizontal hadamard
    movq    mm1,mm3
    movq    mm2,mm7
    paddsw  mm3,mm4     ;e
    paddsw  mm7,mm0     ;f
    psubsw  mm1,mm4     ;e2
    psubsw  mm2,mm0     ;f2
    movq    mm6,mm3
    paddsw  mm3,mm7     ;dest0
    psubsw  mm6,mm7     ;dest2
    movq    mm4,mm1
    paddsw  mm1,mm2     ;dest1
    psubsw  mm4,mm2     ;dest3

    ;1. row sad
    movq    mm0,mm3
    psraw   mm3,15
    pxor    mm0,mm3
    psubw   mm0,mm3

    ;2. row sad
    movq    mm2,mm1
    psraw   mm1,15
    pxor    mm2,mm1
    psubw   mm2,mm1
    paddusw mm0,mm2

    ;3. row sad
    movq    mm2,mm6
    psraw   mm6,15
    pxor    mm2,mm6
    psubw   mm2,mm6
    paddusw mm0,mm2

    ;2. row sad
    movq    mm2,mm4
    psraw   mm4,15
    pxor    mm2,mm4
    psubw   mm2,mm4
    paddusw mm0,mm2

    ;Sum 4 words of mm0
    PSHUFW(1,0,0x90)
    psrld   mm0,16
    psrld   mm1,16
    paddd   mm0,mm1
    PSHUFW(1,0,0x0e)
    paddd   mm0,mm1
    movd    eax,mm0

    emms
  }
}
#else
int32 traHadamard4x4(int16 src[4][4])
{
  int tmp[4][4];
  int e;
  int f;
  int i;
  int32 sad;

  /*
   *  A = a + b + c + d
   *  B = a + b - c - d
   *  C = a - b - c + d
   *  D = a - b + c - d
   *
   *  e = a + d
   *  f = b + c
   *  A = e + f
   *  C = e - f
   *  e = a - d
   *  f = b - c
   *  B = e + f
   *  D = e - f
   */

  /* Horizontal transform */
  for (i = 0; i < 4; i++) {
    e = src[i][0] + src[i][3];
    f = src[i][1] + src[i][2];
    tmp[i][0] = e + f;
    tmp[i][2] = e - f;
    e = src[i][0] - src[i][3];
    f = src[i][1] - src[i][2];
    tmp[i][1] = e + f;
    tmp[i][3] = e - f;
  }

  /* Vertical transform and SATD */
  for (sad = 0, i = 0; i < 4; i++) {
    e = tmp[0][i] + tmp[3][i];
    f = tmp[1][i] + tmp[2][i];
    sad += abs(e + f);
    sad += abs(e - f);
    e = tmp[0][i] - tmp[3][i];
    f = tmp[1][i] - tmp[2][i];
    sad += abs(e + f);
    sad += abs(e - f);
  }

  return sad;
}
#endif


/*
 *
 * traDiffSATD4x4:
 *
 * Parameters:
 *      orig            Original values
 *      pred            Prediction values
 *
 * Function:
 *      Compute difference between orig and pred, compute hadamard
 *      transform on difference matrix and compute sum of absolute
 *      transformed differences.
 *
 * Returns:
 *      Sum of absolute transformed differences
 *
 */
#if X86MMX
int32 traDiffSATD4x4(u_int8 orig[BLK_SIZE][MBK_SIZE],
                     u_int8 pred[BLK_SIZE][MBK_SIZE])
{
  __asm {
    mov     eax,[orig]
    mov     ecx,[pred]

    pxor    mm7,mm7

    movd    mm0,[eax]
    movd    mm4,[ecx]
    punpcklbw mm0,mm7
    punpcklbw mm4,mm7
    psubw   mm0,mm4

    movd    mm1,[eax+MBK_SIZE]
    movd    mm4,[ecx+MBK_SIZE]
    punpcklbw mm1,mm7
    punpcklbw mm4,mm7
    psubw   mm1,mm4

    movd    mm2,[eax+2*MBK_SIZE]
    movd    mm4,[ecx+2*MBK_SIZE]
    punpcklbw mm2,mm7
    punpcklbw mm4,mm7
    psubw   mm2,mm4

    movd    mm3,[eax+3*MBK_SIZE]
    movd    mm4,[ecx+3*MBK_SIZE]
    punpcklbw mm3,mm7
    punpcklbw mm4,mm7
    psubw   mm3,mm4

    ;Vertical hadamard
    movq    mm4,mm0
    movq    mm5,mm1
    paddw   mm0,mm3     ;e
    paddw   mm1,mm2     ;f
    psubw   mm4,mm3     ;e2
    psubw   mm5,mm2     ;f2
    movq    mm2,mm0
    paddw   mm0,mm1     ;dest0
    psubw   mm2,mm1     ;dest2
    movq    mm6,mm4
    paddw   mm4,mm5     ;dest1
    psubw   mm6,mm5     ;dest3

    ;Transpose
    movq    mm3,mm0
    movq    mm5,mm2
    punpcklwd mm3,mm4   ;b1,a1,b0,a0
    punpcklwd mm5,mm6   ;d1,c1,d0,c0
    movq    mm7,mm3
    punpckldq mm3,mm5   ;d0,c0,b0,a0
    punpckhdq mm7,mm5   ;d1,c1,b1,a1

    punpckhwd mm0,mm4
    punpckhwd mm2,mm6
    movq    mm4,mm0
    punpckldq mm0,mm2   ;d2,c2,b2,a2
    punpckhdq mm4,mm2   ;d3,c3,b3,a3

    ;Horizontal hadamard
    movq    mm1,mm3
    movq    mm2,mm7
    paddsw  mm3,mm4     ;e
    paddsw  mm7,mm0     ;f
    psubsw  mm1,mm4     ;e2
    psubsw  mm2,mm0     ;f2
    movq    mm6,mm3
    paddsw  mm3,mm7     ;dest0
    psubsw  mm6,mm7     ;dest2
    movq    mm4,mm1
    paddsw  mm1,mm2     ;dest1
    psubsw  mm4,mm2     ;dest3

    ;1. row sad
    movq    mm0,mm3
    psraw   mm3,15
    pxor    mm0,mm3
    psubw   mm0,mm3

    ;2. row sad
    movq    mm2,mm1
    psraw   mm1,15
    pxor    mm2,mm1
    psubw   mm2,mm1
    paddusw mm0,mm2

    ;3. row sad
    movq    mm2,mm6
    psraw   mm6,15
    pxor    mm2,mm6
    psubw   mm2,mm6
    paddusw mm0,mm2

    ;2. row sad
    movq    mm2,mm4
    psraw   mm4,15
    pxor    mm2,mm4
    psubw   mm2,mm4
    paddusw mm0,mm2

    ;Sum 4 words of mm0
    PSHUFW(1,0,0x0e)
    paddw   mm0,mm1
    PSHUFW(1,0,0x01)
    paddw   mm0,mm1
    movd    eax,mm0

    emms

    and     eax,0xffff
  }
}
#else
int32 traDiffSATD4x4(u_int8 orig[BLK_SIZE][MBK_SIZE],
                     u_int8 pred[BLK_SIZE][MBK_SIZE])
{
  int tmp[4][4];
  int a, b, c, d;
  int e;
  int f;
  int i;
  int32 sad;

  /*
   *  A = a + b + c + d
   *  B = a + b - c - d
   *  C = a - b - c + d
   *  D = a - b + c - d
   *
   *  e = a + d
   *  f = b + c
   *  A = e + f
   *  C = e - f
   *  e = a - d
   *  f = b - c
   *  B = e + f
   *  D = e - f
   */

  /* Difference and horizontal transform */
  for (i = 0; i < 4; i++) {
    a = orig[i][0] - pred[i][0];
    b = orig[i][1] - pred[i][1];
    c = orig[i][2] - pred[i][2];
    d = orig[i][3] - pred[i][3];
    e = a + d;
    f = b + c;
    tmp[i][0] = e + f;
    tmp[i][2] = e - f;
    e = a - d;
    f = b - c;
    tmp[i][1] = e + f;
    tmp[i][3] = e - f;
  }

  /* Vertical transform and SATD */
  for (sad = 0, i = 0; i < 4; i++) {
    e = tmp[0][i] + tmp[3][i];
    f = tmp[1][i] + tmp[2][i];
    sad += abs(e + f);
    sad += abs(e - f);
    e = tmp[0][i] - tmp[3][i];
    f = tmp[1][i] - tmp[2][i];
    sad += abs(e + f);
    sad += abs(e - f);
  }

  return sad;
}
#endif


/*
 *
 * traDiffSATD4x4RetDc:
 *
 * Parameters:
 *      orig            Original values
 *      pred            Prediction values
 *      dc              Return pointer for DC value
 *
 * Function:
 *      Compute difference between orig and pred, compute hadamard
 *      transform on difference matrix and compute sum of absolute
 *      transformed differences. Write DC coefficient to location
 *      pointed by dc.
 *
 * Returns:
 *      Sum of absolute transformed differences
 *
 */
#if X86MMX
int32 traDiffSATD4x4RetDc(u_int8 orig[BLK_SIZE][MBK_SIZE],
                          u_int8 pred[BLK_SIZE][MBK_SIZE], int *dc)
{
  __asm {
    mov     eax,[orig]
    mov     ecx,[pred]
    mov     edx,[dc]

    pxor    mm7,mm7

    movd    mm0,[eax]
    movd    mm4,[ecx]
    punpcklbw mm0,mm7
    punpcklbw mm4,mm7
    psubw   mm0,mm4

    movd    mm1,[eax+MBK_SIZE]
    movd    mm4,[ecx+MBK_SIZE]
    punpcklbw mm1,mm7
    punpcklbw mm4,mm7
    psubw   mm1,mm4

    movd    mm2,[eax+2*MBK_SIZE]
    movd    mm4,[ecx+2*MBK_SIZE]
    punpcklbw mm2,mm7
    punpcklbw mm4,mm7
    psubw   mm2,mm4

    movd    mm3,[eax+3*MBK_SIZE]
    movd    mm4,[ecx+3*MBK_SIZE]
    punpcklbw mm3,mm7
    punpcklbw mm4,mm7
    psubw   mm3,mm4

    ;Vertical hadamard
    movq    mm4,mm0
    movq    mm5,mm1
    paddw   mm0,mm3     ;e
    paddw   mm1,mm2     ;f
    psubw   mm4,mm3     ;e2
    psubw   mm5,mm2     ;f2
    movq    mm2,mm0
    paddw   mm0,mm1     ;dest0
    psubw   mm2,mm1     ;dest2
    movq    mm6,mm4
    paddw   mm4,mm5     ;dest1
    psubw   mm6,mm5     ;dest3

    ;Transpose
    movq    mm3,mm0
    movq    mm5,mm2
    punpcklwd mm3,mm4   ;b1,a1,b0,a0
    punpcklwd mm5,mm6   ;d1,c1,d0,c0
    movq    mm7,mm3
    punpckldq mm3,mm5   ;d0,c0,b0,a0
    punpckhdq mm7,mm5   ;d1,c1,b1,a1

    punpckhwd mm0,mm4
    punpckhwd mm2,mm6
    movq    mm4,mm0
    punpckldq mm0,mm2   ;d2,c2,b2,a2
    punpckhdq mm4,mm2   ;d3,c3,b3,a3

    ;Horizontal hadamard
    movq    mm1,mm3
    movq    mm2,mm7
    paddsw  mm3,mm4     ;e
    paddsw  mm7,mm0     ;f
    psubsw  mm1,mm4     ;e2
    psubsw  mm2,mm0     ;f2
    movq    mm6,mm3
    paddsw  mm3,mm7     ;dest0
    psubsw  mm6,mm7     ;dest2
    movq    mm4,mm1
    paddsw  mm1,mm2     ;dest1
    psubsw  mm4,mm2     ;dest3

    punpcklwd mm0,mm3
    psrad   mm0,16
    movd    [edx],mm0   ;save dc value

    psrlq   mm3,16      ;exclude dc from sum
    psllq   mm3,16

    ;1. row sad
    movq    mm0,mm3
    psraw   mm3,15
    pxor    mm0,mm3
    psubw   mm0,mm3

    ;2. row sad
    movq    mm2,mm1
    psraw   mm1,15
    pxor    mm2,mm1
    psubw   mm2,mm1
    paddusw mm0,mm2

    ;3. row sad
    movq    mm2,mm6
    psraw   mm6,15
    pxor    mm2,mm6
    psubw   mm2,mm6
    paddusw mm0,mm2

    ;2. row sad
    movq    mm2,mm4
    psraw   mm4,15
    pxor    mm2,mm4
    psubw   mm2,mm4
    paddusw mm0,mm2

    ;Sum 4 words of mm0
    PSHUFW(1,0,0x0e)
    paddw   mm0,mm1
    PSHUFW(1,0,0x01)
    paddw   mm0,mm1
    movd    eax,mm0

    emms

    and     eax,0xffff
  }
}
#else
int32 traDiffSATD4x4RetDc(u_int8 orig[BLK_SIZE][MBK_SIZE],
                          u_int8 pred[BLK_SIZE][MBK_SIZE], int *dc)
{
  int tmp[4][4];
  int a, b, c, d;
  int e;
  int f;
  int i;
  int32 sad;

  /*
   *  A = a + b + c + d
   *  B = a + b - c - d
   *  C = a - b - c + d
   *  D = a - b + c - d
   *
   *  e = a + d
   *  f = b + c
   *  A = e + f
   *  C = e - f
   *  e = a - d
   *  f = b - c
   *  B = e + f
   *  D = e - f
   */

  /* Difference and horizontal transform */
  for (i = 0; i < 4; i++) {
    a = orig[i][0] - pred[i][0];
    b = orig[i][1] - pred[i][1];
    c = orig[i][2] - pred[i][2];
    d = orig[i][3] - pred[i][3];
    e = a + d;
    f = b + c;
    tmp[i][0] = e + f;
    tmp[i][2] = e - f;
    e = a - d;
    f = b - c;
    tmp[i][1] = e + f;
    tmp[i][3] = e - f;
  }

  /* Vertical transform and SATD */
  for (sad = 0, i = 0; i < 4; i++) {
    e = tmp[0][i] + tmp[3][i];
    f = tmp[1][i] + tmp[2][i];
    if (i == 0)
      *dc = e + f;
    else
      sad += abs(e + f);

    sad += abs(e - f);
    e = tmp[0][i] - tmp[3][i];
    f = tmp[1][i] - tmp[2][i];
    sad += abs(e + f);
    sad += abs(e - f);
  }

  return sad;
}
#endif


int simpleSad4x4(int16 src[4][4])
{
  int sad;

  sad  = abs(src[0][0]) + abs(src[0][1]) + abs(src[0][2]) + abs(src[0][3]);
  sad += abs(src[1][0]) + abs(src[1][1]) + abs(src[1][2]) + abs(src[1][3]);
  sad += abs(src[2][0]) + abs(src[2][1]) + abs(src[2][2]) + abs(src[2][3]);
  sad += abs(src[3][0]) + abs(src[3][1]) + abs(src[3][2]) + abs(src[3][3]);

  return sad;
}


/*
 *
 * traDiffSAD4x4:
 *
 * Parameters:
 *      orig            Original values
 *      pred            Prediction values
 *
 * Function:
 *      Compute difference between orig and pred and compute sum of absolute
 *      differences.
 *
 * Returns:
 *      Sum of absolute differences
 *
 */
int traDiffSAD4x4(u_int8 orig[BLK_SIZE][MBK_SIZE],
                  u_int8 pred[BLK_SIZE][MBK_SIZE])
{
  int sad;
  int i;

  for (sad = 0, i = 0; i < BLK_SIZE; i++) {
    sad += abs(orig[i][0] - pred[i][0]);
    sad += abs(orig[i][1] - pred[i][1]);
    sad += abs(orig[i][2] - pred[i][2]);
    sad += abs(orig[i][3] - pred[i][3]);
  }

  return sad;
}


/*
 * traQuant4x4:
 *
 * Parameters:
 *      src                   Source values
 *      skip                  Indicates whether to skip DC coefficient
 *      qp                    Quantization parameter
 *      mode                  Intra/inter picture
 *      n                     Number of coefficients
 *
 * Function:
 *      Quantize block of coefficients.
 *
 * Returns:
 *      Number of nonzero quantized coefficients
 */
int traQuant4x4(int *src, int skip, int qp, int mode)
{
  int i;
  int32 qAdd;
  int32 threshold;
  int nonZero;
  int qp_per = qpPerTab[qp-MIN_QP];
  int qp_rem = qpRemTab[qp-MIN_QP];
  int q_bits = TRA_QUANT_BITS + qp_per;

  if (IS_SLICE_I(mode))
    qAdd = (((int32)1 << TRA_QUANT_BITS)/3) << qp_per;
  else
    qAdd = (((int32)1 << TRA_QUANT_BITS)/6) << qp_per;
 
  threshold = ((int32)1 << q_bits) - qAdd;
  for (nonZero = 0, i = skip; i < BLK_SIZE * BLK_SIZE; i ++) {
    int32 tmp;

    tmp = (int32)src[i] * quantCoef[qp_rem][i];
    src[i] = 0;

    // perform more processing, only if quantized coefficient might be nonzero
    if ((tmp >= threshold) || (tmp <= -threshold))
    {
      if (tmp < 0)
        tmp = -((-tmp + qAdd) >> q_bits);
      else
        tmp = (tmp + qAdd) >> q_bits;

      if (tmp != 0)
      {
        src[i] = (int)tmp;
        nonZero ++;
      }
    }
  }

  return nonZero;
}


/*
 * traQuant4x4:
 *
 * Parameters:
 *      src                   Source values
 *      dest                  Return pointer for quantized coefficients
 *      qp                    Quantization parameter
 *      mode                  Intra/inter picture
 *      n                     Number of coefficients
 *
 * Function:
 *      Quantize block of DC coefficients.
 *
 * Returns:
 *      Number of nonzero quantized coefficients
 */
int traQuantDC(int *src, int qp, int mode, int n, int comp)
{
  int i;
  int32 qAdd;
  int32 tmp;
  int nonZero;
  int qp_per = qpPerTab[qp-MIN_QP];
  int qp_rem = qpRemTab[qp-MIN_QP];
  int q_bits = TRA_QUANT_BITS+qp_per+1;

  if (IS_SLICE_I(mode) || (comp == 0))
    qAdd = (((int32)2<<TRA_QUANT_BITS)/3)<<qp_per;
  else
    qAdd = (((int32)2<<TRA_QUANT_BITS)/6)<<qp_per;
 
  for (nonZero = 0, i = 0; i < n; i++) {

    tmp = (int32)src[i]*quantCoef[qp_rem][0];

    if (src[i] < 0)
      tmp = -((-tmp + qAdd) >> q_bits);
    else
      tmp = (tmp + qAdd) >> q_bits;

    src[i] = (int)tmp;

    if (tmp != 0)
      nonZero++;
  }

  return nonZero;
}


/*
 * traGetCoefCost:
 *
 * Parameters:
 *      coef                  Source coefficients
 *      nonZero               Number of non-zero coefficients
 *
 * Function:
 *      Compute cost of block of coefficients. Coefficients with magnitude 1
 *      have cost of 3-0 depending on length of run. All other coefficients
 *      have cost of 9.
 *
 * Returns:
 *      Cost of coefficients
 */
int traGetCoefCost(int *coef, 
                   int nonZero)
{
  int cost;
  int prev;
  int i;
  int nonZeroCount;

  /*
   * Compute cost of coefficients based on run&level. Coefficients with
   * |level|==1 and long run have smallest cost.
   */

  nonZeroCount = 0;
  cost = 0;
  prev = 0;
  i = 0;
  do 
  {
    if (coef[i] != 0) {
      if (coef[i] == 1 || coef[i] == -1)
        cost += COEFF_COST[i - prev];  /* run = i-prev */
      else
        cost += 9;      // the threshold should not be larger than 9

      nonZeroCount ++;
      prev = i + 1;
    }

    i ++;
  } while (nonZeroCount < nonZero);

  return cost;
}
