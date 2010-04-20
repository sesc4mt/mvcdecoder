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
 * meutility.c
 *
 * Contains:
 *    Common data and low level functions for motion estimation.
 *
 */

#include <limits.h>
#include "vlcutility.h"
#include "transform.h"
#include "meutility.h"

#define MAX_DIFF        255

#define ABS_DIFF(a, b)  ((absDiff+MAX_DIFF)[(int)(a) - (int)(b)])

//#define DBG_STATISTICS

static const u_int8 absDiff[2*MAX_DIFF+1] = {
  255,254,253,252,251,250,249,248,247,246,245,244,243,242,241,240,
  239,238,237,236,235,234,233,232,231,230,229,228,227,226,225,224,
  223,222,221,220,219,218,217,216,215,214,213,212,211,210,209,208,
  207,206,205,204,203,202,201,200,199,198,197,196,195,194,193,192,
  191,190,189,188,187,186,185,184,183,182,181,180,179,178,177,176,
  175,174,173,172,171,170,169,168,167,166,165,164,163,162,161,160,
  159,158,157,156,155,154,153,152,151,150,149,148,147,146,145,144,
  143,142,141,140,139,138,137,136,135,134,133,132,131,130,129,128,
  127,126,125,124,123,122,121,120,119,118,117,116,115,114,113,112,
  111,110,109,108,107,106,105,104,103,102,101,100, 99, 98, 97, 96,
   95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80,
   79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64,
   63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48,
   47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32,
   31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,
   15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0,
    1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
   17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
   33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
   49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
   65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
   81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96,
   97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111,112,
  113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,
  129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,
  145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,
  161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,
  177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,
  193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,
  209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,
  225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,
  241,242,243,244,245,246,247,248,249,250,251,252,253,254,255
};



int32 findSad2_16x(u_int8 *orig, u_int8* ref, int w, int blkHeight, int32 sad, int32 bestSad)
{
#ifdef X86MMX
  _asm {// SSE SAD

    mov     esi, [ref]
    mov     edi, [orig]
    mov     ecx, [blkHeight]
    mov     eax, [sad]
    mov     ebx, [w]
    add     ebx, ebx
    pcmpeqw mm7, mm7              ;0xffffffffffffffff
    psrlw   mm7, 8                ;0x00ff00ff00ff00ff
findSad2_16x_loop:
    movq    mm0, [esi]
    pand    mm0, mm7
    movq    mm2, [esi+8]				
    pand    mm2, mm7
    packuswb mm0, mm2
    //8 pixel SAD
    movq    mm1, [edi]
    PSADBW(0,1)                   ;psadbw  mm0, mm1

    movq    mm4, [esi+16]
    pand    mm4, mm7
    movq    mm6, [esi+24]				
    pand    mm6, mm7
    packuswb mm4, mm6
    //8 pixel SAD
    movq    mm3, [edi+8]
    PSADBW(4,3)                   ;psadbw  mm4, mm3

    paddw   mm0, mm4              ;Combine two 8 pixels SADs
    movd    edx, mm0
    add     eax, edx
    mov     edx, [bestSad]
    cmp     eax, edx
    jge     findSad2_16x_finish

    add     edi, MBK_SIZE
    add     esi, ebx

    sub     ecx, 1
    jnz     findSad2_16x_loop
    
findSad2_16x_finish:
    mov     [sad], eax
    emms
  } 
#else
  int j;

  j = 0;
  do {
    sad += ABS_DIFF(orig[j*MBK_SIZE+0], ref[j*2*w+0]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+1], ref[j*2*w+2]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+2], ref[j*2*w+4]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+3], ref[j*2*w+6]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+4], ref[j*2*w+8]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+5], ref[j*2*w+10]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+6], ref[j*2*w+12]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+7], ref[j*2*w+14]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+8], ref[j*2*w+16]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+9], ref[j*2*w+18]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+10], ref[j*2*w+20]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+11], ref[j*2*w+22]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+12], ref[j*2*w+24]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+13], ref[j*2*w+26]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+14], ref[j*2*w+28]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+15], ref[j*2*w+30]);
    j++;
  } while (sad < bestSad && j < blkHeight);
#endif

  return sad;
}


int32 findSad2_8x(u_int8 *orig, u_int8* ref, int w, int blkHeight, int32 sad, int32 bestSad)
{
#ifdef X86MMX
  _asm {// SSE SAD

    mov     esi, [ref]
    mov     edi, [orig]
    mov     ecx, [blkHeight]
    mov     eax, [sad]
    mov     ebx, [w]
    add     ebx, ebx
    pcmpeqw mm7, mm7              ;0xffffffffffffffff
    psrlw   mm7, 8                ;0x00ff00ff00ff00ff
findSad2_8x_loop:
    movq    mm0, [esi]
    pand    mm0, mm7
    movq    mm2, [esi+8]				
    pand    mm2, mm7
    packuswb mm0, mm2
    //8 pixel SAD
    movq    mm1, [edi]
    PSADBW(0,1)                   ;psadbw  mm0, mm1

    movq    mm4, [esi+ebx]
    pand    mm4, mm7
    movq    mm6, [esi+ebx+8]				
    pand    mm6, mm7
    packuswb mm4, mm6
    //8 pixel SAD
    movq    mm3, [edi+MBK_SIZE]
    PSADBW(4,3)                   ;psadbw  mm4, mm3

    paddw   mm0, mm4              ;Combine two 8 pixels SADs
    movd    edx, mm0
    add     eax, edx
    mov     edx, [bestSad]
    cmp     eax, edx
    jge     findSad2_8x_finish

    add     edi, 2*MBK_SIZE
    lea     esi, [esi+2*ebx]

    sub     ecx, 2
    jnz     findSad2_8x_loop
    
findSad2_8x_finish:
    mov     [sad], eax
    emms
  } 
#else
  int j;

  j = 0;
  do {
    sad += ABS_DIFF(orig[j*MBK_SIZE+0], ref[j*2*w+0]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+1], ref[j*2*w+2]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+2], ref[j*2*w+4]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+3], ref[j*2*w+6]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+4], ref[j*2*w+8]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+5], ref[j*2*w+10]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+6], ref[j*2*w+12]);
    sad += ABS_DIFF(orig[j*MBK_SIZE+7], ref[j*2*w+14]);
    j++;
  } while (sad < bestSad && j < blkHeight);
#endif

  return sad;
}


int32 findSAD2(u_int8 *orig, u_int8 *ref, int w, int blkWidth,
               int blkHeight,  int vecX, int vecY, int32 sad, int32 bestSad)
{
#ifndef X86MMX
  int j;
#endif

  ref = & ref[(vecY >> 1) * w + (vecX >> 1)];

  switch (blkWidth) {

  case 4:
#ifdef X86MMX
  _asm {// SSE SAD

    mov     esi, [ref]
    mov     edi, [orig]
    mov     ecx, [blkHeight]
    mov     eax, [sad]
    mov     ebx, [w]
    add     ebx, ebx
    pcmpeqw mm7, mm7              ;0xffffffffffffffff
    psrlw   mm7, 8                ;0x00ff00ff00ff00ff
findSad2_4x_loop:
    movq    mm0, [esi]
    pand    mm0, mm7
    movq    mm2, [esi+ebx]
    pand    mm2, mm7
    packuswb mm0, mm2
    //8 pixel SAD
    movq    mm1, [edi]
    movq    mm2, [edi+MBK_SIZE]
    punpckldq mm1, mm2
    PSADBW(0,1)                   ;psadbw  mm0, mm1

    movd    edx, mm0
    add     eax, edx
    mov     edx, [bestSad]
    cmp     eax, edx
    jge     findSad2_4x_finish

    add     edi, 2*MBK_SIZE
    lea     esi, [esi+2*ebx]

    sub     ecx, 2
    jnz     findSad2_4x_loop
    
findSad2_4x_finish:
    mov     [sad], eax
    emms
  } 
#else
    j = 0;
    do {
      sad += ABS_DIFF(orig[j*MBK_SIZE+0], ref[j*2*w+0]);
      sad += ABS_DIFF(orig[j*MBK_SIZE+1], ref[j*2*w+2]);
      sad += ABS_DIFF(orig[j*MBK_SIZE+2], ref[j*2*w+4]);
      sad += ABS_DIFF(orig[j*MBK_SIZE+3], ref[j*2*w+6]);
      j++;
    } while (sad < bestSad && j < blkHeight);
#endif

    break;

  case 8:
    sad = findSad2_8x(orig, ref, w, blkHeight, sad, bestSad);
    break;

  default:  // Block size == 16
    sad = findSad2_16x(orig, ref, w, blkHeight, sad, bestSad);
    break;
  }

#ifdef X86MMX
  _asm {
    emms
  } 
#endif

  return sad;
}


#define findSAD2_4x(orig, ref, w, blkHeight, sad, bestSad, j)  {    \
    (j) = 0;                                                        \
    do {                                                            \
      (sad) += ABS_DIFF((orig)[j*MBK_SIZE+0], (ref)[j*2*(w)+0]);    \
      (sad) += ABS_DIFF((orig)[j*MBK_SIZE+1], (ref)[j*2*(w)+2]);    \
      (sad) += ABS_DIFF((orig)[j*MBK_SIZE+2], (ref)[j*2*(w)+4]);    \
      (sad) += ABS_DIFF((orig)[j*MBK_SIZE+3], (ref)[j*2*(w)+6]);    \
      j ++;                                                         \
    } while ((sad) < (bestSad) && j < (blkHeight));                 \
  }


static void halfPixelDiff(u_int8 *orig, u_int8 *ref, int w, 
                          int16 blk[BLK_SIZE][BLK_SIZE])
{
  blk[0][0] = (int16) (orig[0* MBK_SIZE + 0] - ref[0 * w + 0]);
  blk[0][1] = (int16) (orig[0* MBK_SIZE + 1] - ref[0 * w + 2]);
  blk[0][2] = (int16) (orig[0* MBK_SIZE + 2] - ref[0 * w + 4]);
  blk[0][3] = (int16) (orig[0* MBK_SIZE + 3] - ref[0 * w + 6]);
  blk[1][0] = (int16) (orig[1* MBK_SIZE + 0] - ref[2 * w + 0]);
  blk[1][1] = (int16) (orig[1* MBK_SIZE + 1] - ref[2 * w + 2]);
  blk[1][2] = (int16) (orig[1* MBK_SIZE + 2] - ref[2 * w + 4]);
  blk[1][3] = (int16) (orig[1* MBK_SIZE + 3] - ref[2 * w + 6]);
  blk[2][0] = (int16) (orig[2* MBK_SIZE + 0] - ref[4 * w + 0]);
  blk[2][1] = (int16) (orig[2* MBK_SIZE + 1] - ref[4 * w + 2]);
  blk[2][2] = (int16) (orig[2* MBK_SIZE + 2] - ref[4 * w + 4]);
  blk[2][3] = (int16) (orig[2* MBK_SIZE + 3] - ref[4 * w + 6]);
  blk[3][0] = (int16) (orig[3* MBK_SIZE + 0] - ref[6 * w + 0]);
  blk[3][1] = (int16) (orig[3* MBK_SIZE + 1] - ref[6 * w + 2]);
  blk[3][2] = (int16) (orig[3* MBK_SIZE + 2] - ref[6 * w + 4]);
  blk[3][3] = (int16) (orig[3* MBK_SIZE + 3] - ref[6 * w + 6]);
}


#ifdef X86MMX
int quarterPixelDiffSAD4x4(u_int8 orig[BLK_SIZE][MBK_SIZE],
                           u_int8 *ref, u_int8 *ref2, int w)
{
  __asm {
    mov     eax,[orig]
    mov     ecx,[ref]
    mov     edx,[ref2]
    mov     ebx,[w]

    pxor    mm7,mm7
    pcmpeqw mm6,mm6              ;0xffffffffffffffff
    psrlw   mm6,8                ;0x00ff00ff00ff00ff

    add     ebx,ebx              ;2*w

    movq    mm0,[ecx]
    movq    mm1,[ecx+ebx]
    pand    mm0,mm6
    pand    mm1,mm6
    packuswb mm0,mm1
    movq    mm1,[edx]
    movq    mm2,[edx+ebx]
    pand    mm1,mm6
    pand    mm2,mm6
    packuswb mm1,mm2
    PAVGB(0,1)                   ;pavgb   mm0,mm1
    movd    mm1,[eax]
    movd    mm2,[eax+MBK_SIZE]
    punpckldq mm1,mm2
    PSADBW(0,1)                  ;psadbw  mm0,mm1

    add     ecx,ebx
    add     edx,ebx
    add     ecx,ebx
    add     edx,ebx

    movq    mm1,[ecx]
    movq    mm2,[ecx+ebx]
    pand    mm1,mm6
    pand    mm2,mm6
    packuswb mm1,mm2
    movq    mm2,[edx]
    movq    mm3,[edx+ebx]
    pand    mm2,mm6
    pand    mm3,mm6
    packuswb mm2,mm3
    PAVGB(1,2)                   ;pavgb   mm1,mm2
    movd    mm2,[eax+2*MBK_SIZE]
    movd    mm3,[eax+3*MBK_SIZE]
    punpckldq mm2,mm3
    PSADBW(1,2)                  ;psadbw  mm1,mm2

    paddd   mm0,mm1
    movd    eax,mm0

    emms
  }
}
#else
int quarterPixelDiffSAD4x4(u_int8 orig[BLK_SIZE][MBK_SIZE],
                           u_int8 *ref, u_int8 *ref2, int w)
{
  int sad;

  sad  = abs(orig[0][0] - ((ref[0 * w + 0]+ref2[0 * w + 0]+1)>>1));
  sad += abs(orig[0][1] - ((ref[0 * w + 2]+ref2[0 * w + 2]+1)>>1));
  sad += abs(orig[0][2] - ((ref[0 * w + 4]+ref2[0 * w + 4]+1)>>1));
  sad += abs(orig[0][3] - ((ref[0 * w + 6]+ref2[0 * w + 6]+1)>>1));
  sad += abs(orig[1][0] - ((ref[2 * w + 0]+ref2[2 * w + 0]+1)>>1));
  sad += abs(orig[1][1] - ((ref[2 * w + 2]+ref2[2 * w + 2]+1)>>1));
  sad += abs(orig[1][2] - ((ref[2 * w + 4]+ref2[2 * w + 4]+1)>>1));
  sad += abs(orig[1][3] - ((ref[2 * w + 6]+ref2[2 * w + 6]+1)>>1));
  sad += abs(orig[2][0] - ((ref[4 * w + 0]+ref2[4 * w + 0]+1)>>1));
  sad += abs(orig[2][1] - ((ref[4 * w + 2]+ref2[4 * w + 2]+1)>>1));
  sad += abs(orig[2][2] - ((ref[4 * w + 4]+ref2[4 * w + 4]+1)>>1));
  sad += abs(orig[2][3] - ((ref[4 * w + 6]+ref2[4 * w + 6]+1)>>1));
  sad += abs(orig[3][0] - ((ref[6 * w + 0]+ref2[6 * w + 0]+1)>>1));
  sad += abs(orig[3][1] - ((ref[6 * w + 2]+ref2[6 * w + 2]+1)>>1));
  sad += abs(orig[3][2] - ((ref[6 * w + 4]+ref2[6 * w + 4]+1)>>1));
  sad += abs(orig[3][3] - ((ref[6 * w + 6]+ref2[6 * w + 6]+1)>>1));

  return sad;
}
#endif


#ifdef X86MMX
int32 quarterPixelDiffSATD4x4(u_int8 orig[BLK_SIZE][MBK_SIZE],
                              u_int8 *ref, u_int8 *ref2, int w)
{
  __asm {
    mov     eax,[orig]
    mov     ecx,[ref]
    mov     edx,[ref2]
    mov     ebx,[w]

    pxor    mm7,mm7
    pcmpeqw mm6,mm6              ;0xffffffffffffffff
    psrlw   mm6,8                ;0x00ff00ff00ff00ff

    add     ebx,ebx              ;2*w

    movq    mm4,[ecx]
    movq    mm5,[edx]
    movd    mm0,[eax]
    PAVGB(4,5)                    ;pavgb mm4,mm5
    punpcklbw mm0,mm7
    pand    mm4,mm6
    psubw   mm0,mm4

    movq    mm4,[ecx+ebx]
    movq    mm5,[edx+ebx]
    movd    mm1,[eax+MBK_SIZE]
    PAVGB(4,5)                    ;pavgb mm4,mm5
    punpcklbw mm1,mm7
    pand    mm4,mm6
    psubw   mm1,mm4

    add     ecx,ebx
    add     edx,ebx
    add     ecx,ebx
    add     edx,ebx

    movq    mm4,[ecx]
    movq    mm5,[edx]
    movd    mm2,[eax+2*MBK_SIZE]
    PAVGB(4,5)                    ;pavgb mm4,mm5
    punpcklbw mm2,mm7
    pand    mm4,mm6
    psubw   mm2,mm4

    movq    mm4,[ecx+ebx]
    movq    mm5,[edx+ebx]
    movd    mm3,[eax+3*MBK_SIZE]
    PAVGB(4,5)                    ;pavgb mm4,mm5
    punpcklbw mm3,mm7
    pand    mm4,mm6
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
int32 quarterPixelDiffSATD4x4(u_int8 orig[BLK_SIZE][MBK_SIZE],
                              u_int8 *ref, u_int8 *ref2, int w)
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

  /* Interpolation, difference and horizontal transform */
  for (i = 0; i < 4; i++, ref+=2*w, ref2+=2*w) {
    a = orig[i][0] - ((ref[0] + ref2[0] + 1) >> 1);
    b = orig[i][1] - ((ref[2] + ref2[2] + 1) >> 1);
    c = orig[i][2] - ((ref[4] + ref2[4] + 1) >> 1);
    d = orig[i][3] - ((ref[6] + ref2[6] + 1) >> 1);
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


int32 findSATD4(u_int8 *orig, u_int8 *ref, int w, int blkWidth,
                int blkHeight,  int x, int y, int32 sad, int32 bestSad, int hadamard)
{
  int i, j;

#if X86MMX
  int16 blkData[BLK_SIZE*BLK_SIZE+4];
  /* Aligned pointer for MMX */
  int16 (*blk)[BLK_SIZE] = (int16 (*)[BLK_SIZE]) (((long)blkData + 7) & ~7);
#else
  int16 blk[BLK_SIZE][BLK_SIZE];
#endif


  ref += (y >> 1) * w + (x >> 1);

  if (((x | y) & 1) == 0) {

    /* Half-pel */
    for (j = 0; j < blkHeight; j+=BLK_SIZE) {
      for (i = 0; i < blkWidth; i+=BLK_SIZE) {
        halfPixelDiff(orig + i, ref + 2 * i, w, blk);
        if (hadamard) 
          sad += traHadamard4x4(blk)>>1;
        else
          sad += simpleSad4x4(blk);

        if (sad >= bestSad)
          return sad;
      }
      orig += BLK_SIZE*MBK_SIZE;
      ref  += BLK_SIZE*2*w;
    }
  }
  else {
    /* Quarter-pel */
    u_int8 *ref2;


    ref2 = ref + (y&1)*w + (x&1);

    if (((x ^ y) & 3) == 0) {
      ref++;
      ref2--;
    }

    for (j = 0; j < blkHeight; j+=BLK_SIZE) {
      for (i = 0; i < blkWidth; i+=BLK_SIZE) {
        if (hadamard) 
          sad += quarterPixelDiffSATD4x4((u_int8 (*)[MBK_SIZE]) (orig + i),
                                          ref + 2 * i, ref2 + 2 * i, w) >> 1;
        else
          sad += quarterPixelDiffSAD4x4((u_int8 (*)[MBK_SIZE]) (orig + i),
                                        ref + 2 * i, ref2 + 2 * i, w);
        if (sad >= bestSad)
          return sad;
      }
      orig += BLK_SIZE*MBK_SIZE;
      ref  += BLK_SIZE*2*w;
      ref2 += BLK_SIZE*2*w;
    }
  }

  return sad;
}


/*
 *
 * findSAD4Blk:
 *
 * Parameters:
 *      orig            Pointer to the original pixels
 *      ref             Pointer to the reference pixels
 *      w               Width of the reference buffer
 *      blkWidth        Width of block
 *      blkHeight       Height of block
 *      x               Motion vector, x component
 *      y               Motion vector, y component
 *      blkSadsBuf      Store the SAD of 4x4 block
 *
 * Function:
 *      Calculate the sum of absolute
 *      of differences between the original pixels and reference pixels. 
 *      SAD is calculated in 4x4 blocks. The SADs of each
 *      4x4 block are also return in the buffer. The buffer store the SADs
 *      of 4x4 blocks in raster order. So when "j" moves to the next row,
 *      the sad buffer pointer is incremented by 4.
 *
 * Returns:
 *      Total SAD for the partition.
 *
 */
int32 findSAD4Blk(u_int8 *orig, u_int8 *ref, int w, int blkWidth,
                  int blkHeight, int x, int y, int16 *blkSadsBuf)
{
  int i, j;
  int16 blk[BLK_SIZE][BLK_SIZE];
  int32 blkSad, totalSad;
  int16 *sadPtr;

  totalSad = 0;
  ref += (y >> 1) * w + (x >> 1);

  if (((x | y) & 1) == 0) {

    /* Half-pel */
    for (j = 0; j < blkHeight; j += BLK_SIZE) {
      sadPtr = blkSadsBuf;
      for (i = 0; i < blkWidth; i += BLK_SIZE) {
        halfPixelDiff(orig + i, ref + 2 * i, w, blk);
        blkSad = simpleSad4x4(blk);
        totalSad  += blkSad;
        *sadPtr ++ = (int16) blkSad;
      }

      blkSadsBuf += BLK_PER_MB;
      orig += BLK_SIZE*MBK_SIZE;
      ref  += BLK_SIZE*2*w;
    }
  }
  else {
    /* Quarter-pel */
    u_int8 *ref2;


    ref2 = ref + (y&1)*w + (x&1);

    if (((x ^ y) & 3) == 0) {
      ref++;
      ref2--;
    }

    for (j = 0; j < blkHeight; j += BLK_SIZE) {
      sadPtr = blkSadsBuf;
      for (i = 0; i < blkWidth; i += BLK_SIZE) {
        blkSad = quarterPixelDiffSAD4x4((u_int8 (*)[MBK_SIZE]) (orig + i),
                                        ref + 2 * i, ref2 + 2 * i, w);
        totalSad  += blkSad;
        *sadPtr ++ = (int16) blkSad;
      }

      blkSadsBuf += BLK_PER_MB;
      orig += BLK_SIZE*MBK_SIZE;
      ref  += BLK_SIZE*2*w;
      ref2 += BLK_SIZE*2*w;
    }
  }

  return totalSad;
}


/*
 *
 * findSATD4Blk:
 *
 * Parameters:
 *      orig            Pointer to the original pixels
 *      ref             Pointer to the reference pixels
 *      w               Width of the reference buffer
 *      blkWidth        Width of block
 *      blkHeight       Height of block
 *      x               Motion vector, x component
 *      y               Motion vector, y component
 *      blkSadsBuf      Store the SAD of 4x4 block
 *
 * Function:
 *      Calculate the sum of absolute coefficients from Hadamard transform
 *      of differences between the original pixels and reference pixels. 
 *      SAD with Hadamard is calculated in 4x4 blocks. The SADs of each
 *      4x4 block are also return in the buffer. The buffer store the SADs
 *      of 4x4 blocks in raster order. So when "j" moves to the next row,
 *      the sad buffer pointer is incremented by 4.
 *
 * Returns:
 *      Total SAD for the partition.
 *
 */
int32 findSATD4Blk(u_int8 *orig, u_int8 *ref, int w, int blkWidth,
                   int blkHeight, int x, int y, int16 *blkSadsBuf)
{
  int i, j;
  int32 blkSad, totalSad;
  int16 *sadPtr;

#if X86MMX
  int16 blkData[BLK_SIZE*BLK_SIZE+4];
  /* Aligned pointer for MMX */
  int16 (*blk)[BLK_SIZE] = (int16 (*)[BLK_SIZE]) (((long)blkData + 7) & ~7);
#else
  int16 blk[BLK_SIZE][BLK_SIZE];
#endif

  totalSad = 0;
  ref += (y >> 1) * w + (x >> 1);

  if (((x | y) & 1) == 0) {

    /* Half-pel */
    for (j = 0; j < blkHeight; j += BLK_SIZE) {
      sadPtr = blkSadsBuf;
      for (i = 0; i < blkWidth; i += BLK_SIZE) {
        halfPixelDiff(orig + i, ref + 2 * i, w, blk);
        blkSad = traHadamard4x4(blk)>>1;
        totalSad  += blkSad;
        *sadPtr ++ = (int16) blkSad;
      }

      blkSadsBuf += BLK_PER_MB;
      orig += BLK_SIZE*MBK_SIZE;
      ref  += BLK_SIZE*2*w;
    }
  }
  else {
    /* Quarter-pel */
    u_int8 *ref2;


    ref2 = ref + (y&1)*w + (x&1);

    if (((x ^ y) & 3) == 0) {
      ref++;
      ref2--;
    }

    for (j = 0; j < blkHeight; j += BLK_SIZE) {
      sadPtr = blkSadsBuf;
      for (i = 0; i < blkWidth; i += BLK_SIZE) {
        blkSad = quarterPixelDiffSATD4x4((u_int8 (*)[MBK_SIZE]) (orig + i),
                                         ref + 2 * i, ref2 + 2 * i, w) >> 1;
        totalSad  += blkSad;
        *sadPtr ++ = (int16) blkSad;
      }

      blkSadsBuf += BLK_PER_MB;
      orig += BLK_SIZE*MBK_SIZE;
      ref  += BLK_SIZE*2*w;
      ref2 += BLK_SIZE*2*w;
    }
  }

  return totalSad;
}


int32 findSadPT(mbPart_s *mbPart,
                int vecX, int vecY,
                int32 bestSad)
{
  int32 currSad;
  int lambda;

  lambda = mbPart->lambdaCoarse;

  currSad = (int32)lambda * (mbPart->vlcMvBitsX[vecX] + mbPart->vlcMvBitsY[vecY]);
  
  /* Favor 16x16 blocks that have zero motion */
  if (mbPart->mode == MOT_16x16)
  {
    if ((vecY | vecX) == 0)
      currSad -= lambda * ZERO_VEC_SAD;
  }

  /* Take into account number of bits spent for motion vector */
  if (currSad < bestSad) {
      currSad = findSAD2(mbPart->orig, mbPart->ref, mbPart->refWidth, mbPart->width, 
        mbPart->height, vecX, vecY, currSad, bestSad);
  }

  return currSad;
}


#ifdef DBG_STATISTICS
int matchBlockLongCount = 0;
int matchBlockQuarterCount = 0;
int matchOperationsCounts[9] = 
{
  0, 0, 0, 0, 0, 0, 0, 0, 0,
};
int terminatePoint[32] = 
{
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};
#endif


// LOW_COMPLEX_PROF3

// search pos for multi-step integer search
// all must be multiple of 4 -> integer pos
// {x,y}

// use in 16x16
static int8 step_array_16x16[NUM_POS_16x16_FastMot][2] = {
  {14*4,1*4}, {0*4,6*4},  {0*4,6*4}, {-14*4,0*4}, {0*4,-6*4}, {0*4,-6*4},
  {7*4,2*4},  {4*4,4*4}, {-4*4,4*4},  {-4*4,-4*4},
  {3*4,-1*4}, {2*4,0*4}, {-2*4,2*4}, {2*4,0*4},
  {6*4,-3*4}, {0*4,4*4}, {-7*4,5*4},  {-7*4,-5*4}, {0*4,-4*4}, {7*4,-5*4},
  {-4*4,3*4}, {8*4,0*4}, {0*4,8*4}, {-8*4,0*4},
};

// use in 8x16, 16x8, 8x8
static int8 step_array_16x8[NUM_POS_16x8_FastMot][2] = {

  {2*4,2*4}, {2*4,0*4}, {-2*4,2*4}, {2*4,0*4},     
  {2*4,-4*4}, {0*4,6*4}, {-6*4,0*4}, {0*4,-6*4}, 

};
 
static int8 step_array_small[4][2] = {
  {0,0}, {8,0}, 
  {-8,8}, {8,0}, 
};

#define ABS(x)      ( ( (x) >=0) ? (x): (-x)  )

void matchBlockLong_MultiStep(mbPart_s *mbPart, 
                    int startX, int stopX, int startY, int stopY, 
                    int step, 
                    motVec_s *bestVec,
                    int32 *bestSad)
{
  motVec_s lclBestVec;
  int j, vecX, vecY;
  int32 currSad;
  int32 lclBestSad;
  int32 overhead;
  int refW, blkH;
  int lambda;
  u_int8 *refLine, *refPtr, *orig;
  const int8 *vlcMvBitsX;


  int ii;
  int32 old_sad = 0;
  int small_search_win;
  int num_search_pos;
  int8 *pc;

  // *retSad should have the SAD of the best estimate already
  // could be INT_MAX if such an estimate is not available
  lclBestSad = *bestSad;
  lclBestVec = *bestVec;

  blkH = mbPart->height;
  orig = mbPart->orig;
  refW = mbPart->refWidth;
  lambda = mbPart->lambdaCoarse;
  vlcMvBitsX = mbPart->vlcMvBitsX;

#ifdef DBG_STATISTICS
  matchBlockLongCount ++;
#endif

  switch (mbPart->width)
  {
  case 4:
    /* Scan motion vectors within search area */
    for (vecY = startY; vecY <= stopY; vecY += step) {
      refLine   = & mbPart->ref[(vecY >> 1) * refW];
      overhead = (int32) mbPart->vlcMvBitsY[vecY] * lambda;

      for (vecX = startX; vecX <= stopX; vecX += step) {
        /* Take into account number fo bits spent for motion vector */
        currSad = (int32)lambda * vlcMvBitsX[vecX] + overhead;

#ifdef DBG_STATISTICS
        matchOperationsCounts[0] ++;
#endif

        /* Accumulate sad until no pels left or sad is worse than best so far */
        if (currSad < lclBestSad) {

#ifdef DBG_STATISTICS
          matchOperationsCounts[1] ++;
#endif

          refPtr = refLine + (vecX >> 1);
          findSAD2_4x(orig, refPtr, refW, blkH, currSad, lclBestSad, j);

          if (currSad < lclBestSad) {
            lclBestSad   = currSad;
            lclBestVec.x = (int16)vecX;
            lclBestVec.y = (int16)vecY;
          }
        }
        else
        {
#ifdef DBG_STATISTICS
          matchOperationsCounts[2] ++;
#endif
        }
      }
    }
    break;

  case 8:

    small_search_win=0;

    if (stopX-startX == SMALL_SEARCH_WIN) {
      small_search_win = 1;
    }

    if (small_search_win) {
      num_search_pos = 4; 
      pc = &step_array_small[0][0];
    }
    else {
      if ( ( ABS( (startX - (ME_START_16x8))  ) >TH_FastMot_16x8 ) || ( ABS( (startY - (ME_START_16x8)) ) >TH_FastMot_16x8 )  )
      {
        num_search_pos = NUM_POS_16x8_FastMot;
      }
      else
        num_search_pos = NUM_POS_16x8;

      pc = &step_array_16x8[0][0];
    }
     
    vecX = startX;            
    vecY = startY;

    ///////////

    for (ii = 0; ii < num_search_pos; ii++) {
      vecX += *pc++;
      vecY += *pc++;

      refLine = & mbPart->ref[(vecY >> 1) * refW];
      overhead = (int) mbPart->vlcMvBitsY[vecY] * lambda;

      /* Take into account number fo bits spent for motion vector */

      currSad = lambda * vlcMvBitsX[vecX] + overhead;

#ifdef DBG_STATISTICS
      matchOperationsCounts[3] ++;
#endif
      {
#ifdef DBG_STATISTICS
        matchOperationsCounts[4] ++;
#endif

        refPtr = refLine + (vecX >> 1);
        currSad = findSad2_8x(orig, refPtr, refW, blkH, currSad, lclBestSad);

        if (currSad < lclBestSad) {
          lclBestSad   = currSad;
          lclBestVec.x = (int16)vecX;
          lclBestVec.y = (int16)vecY;
        }
      }

      {
#ifdef DBG_STATISTICS
        matchOperationsCounts[5] ++;
#endif
      }
    }
    break;
    
  default:    // blk->width == 16

    small_search_win = 0;

    if (stopX-startX == SMALL_SEARCH_WIN) {
      small_search_win = 1;
    }

    if (small_search_win) {
      num_search_pos = 4;
      pc = &step_array_small[0][0];
    }

    else {
      if (blkH ==16) {

        pc = &step_array_16x16[0][0];
        
        if ( ( ABS( (startX - (ME_START_16x16))  ) >TH_FastMot ) || ( ABS( (startY - (ME_START_16x16)) ) >TH_FastMot )  ) {
          num_search_pos = NUM_POS_16x16_FastMot;
        } 
        else {
          num_search_pos = NUM_POS_16x16;
        }

      }
      else {  
        if ( ( ABS( (startX - (ME_START_16x8))  ) >TH_FastMot_16x8 ) || ( ABS( (startY - (ME_START_16x8)) ) >TH_FastMot_16x8 )  ) {
          num_search_pos=NUM_POS_16x8_FastMot;
        }
        else
          num_search_pos = NUM_POS_16x8;

        pc = &step_array_16x8[0][0];
      }
    }

    old_sad = lclBestSad;

    vecX = startX;
    vecY = startY;
   
    for (ii = 0; ii < num_search_pos; ii++) {

      vecX += *pc++;
      vecY += *pc++;

      refLine = & mbPart->ref[(vecY >> 1) * refW];
      overhead = (int) mbPart->vlcMvBitsY[vecY] * lambda;

      /* Take into account number fo bits spent for motion vector */

      currSad = lambda * vlcMvBitsX[vecX] + overhead;

  #ifdef DBG_STATISTICS
      matchOperationsCounts[6] ++;
  #endif

      if (mbPart->mode == MOT_16x16)
      {
        if ((vecY | vecX) == 0)
          currSad -= lambda * ZERO_VEC_SAD;
      }

      {
  #ifdef DBG_STATISTICS
        matchOperationsCounts[7] ++;
  #endif
        refPtr = refLine + (vecX >> 1); 

        currSad = findSad2_16x(orig, refPtr, refW, blkH, currSad, lclBestSad);

        if (currSad < lclBestSad) {
          lclBestSad   = currSad;
          lclBestVec.x = (int16)vecX;
          lclBestVec.y = (int16)vecY;
        }
      }
    }
    break;
  

  }

  *bestSad = lclBestSad;
  *bestVec = lclBestVec;

  {
    lowComplexProf3_s *plc3 = mbPart->plc3;

    if ( (plc3->qp < TH_QP1) && ((plc3->mode == MOT_16x8) &&  (plc3->old_cnt2 != plc3->cnt)  ) ) {
      plc3->old_cnt2 = plc3->cnt;
      if ( (old_sad-lclBestSad) < 1 ) 
        plc3->do_16x8 = 0;
    }
  }
}


////// LOW_COMPLEX_PROF3

//////////////////////////////////////////////////////////////

void matchBlockLong(mbPart_s *mbPart, 
                    int startX, int stopX, int startY, int stopY, 
                    int step, 
                    motVec_s *bestVec,
                    int32 *bestSad,
                    int low_complex_prof3)
{
  motVec_s lclBestVec;
  int j, vecX, vecY;
  int32 currSad;
  int32 lclBestSad;
  int32 overhead;
  int refW, blkH;
  int lambda;

  int partialSum = 0;
  int *origPsPtr;
  u_int16 *refPsPtr;

  u_int8 *refLine, *refPtr, *orig;
  u_int16 *refPsLine; 

  const int8 *vlcMvBitsX;

#ifdef ENABLE_SEARCH_WINDOW
  int refW2 = mbPart->refPsWidth;
#endif

  // *retSad should have the SAD of the best estimate already
  // could be INT_MAX if such an estimate is not available
  lclBestSad = *bestSad;
  lclBestVec = *bestVec;

  blkH = mbPart->height;
  orig = mbPart->orig;
  refW = mbPart->refWidth;
  lambda = mbPart->lambdaCoarse;
  vlcMvBitsX = mbPart->vlcMvBitsX;

#ifdef DBG_STATISTICS
  matchBlockLongCount ++;
#endif

  switch (mbPart->width)
  {
  case 4:
    /* Scan motion vectors within search area */
    for (vecY = startY; vecY <= stopY; vecY += step) {
      refLine   = & mbPart->ref[(vecY >> 1) * refW];
      overhead = (int32) mbPart->vlcMvBitsY[vecY] * lambda;

      for (vecX = startX; vecX <= stopX; vecX += step) {
        /* Take into account number fo bits spent for motion vector */
        currSad = (int32)lambda * vlcMvBitsX[vecX] + overhead;

#ifdef DBG_STATISTICS
        matchOperationsCounts[0] ++;
#endif

        /* Accumulate sad until no pels left or sad is worse than best so far */
        if (currSad < lclBestSad) {

#ifdef DBG_STATISTICS
          matchOperationsCounts[1] ++;
#endif

          refPtr = refLine + (vecX >> 1);
          findSAD2_4x(orig, refPtr, refW, blkH, currSad, lclBestSad, j);

          if (currSad < lclBestSad) {
            lclBestSad   = currSad;
            lclBestVec.x = (int16)vecX;
            lclBestVec.y = (int16)vecY;
          }
        }
        else
        {
#ifdef DBG_STATISTICS
          matchOperationsCounts[2] ++;
#endif
        }
      }
    }
    break;

  case 8:
    /* Scan motion vectors within search area */
    for (vecY = startY; vecY <= stopY; vecY += step) {

#ifdef ENABLE_SEARCH_WINDOW
      refPsLine = & mbPart->refPartSum[(vecY >> 2) * (refW2 >> 1)];
#else
      refPsLine = & mbPart->refPartSum[(vecY >> 2) * (refW >> 1)];
#endif
      refLine = & mbPart->ref[(vecY >> 1) * refW];
      overhead = (int32) mbPart->vlcMvBitsY[vecY] * lambda;

      for (vecX = startX; vecX <= stopX; vecX += step) {

        /* Take into account number fo bits spent for motion vector */
        currSad = (int32)lambda * vlcMvBitsX[vecX] + overhead;

#ifdef DBG_STATISTICS
        matchOperationsCounts[3] ++;
#endif
        // calculate the partial results here
        // take away partial sum

        if (!low_complex_prof3) {

          refPsPtr = refPsLine + (vecX >> 2); 
          origPsPtr = mbPart->partSum;

          partialSum = 0;
          if (blkH >= 8)
            partialSum  = abs(refPsPtr[0] - origPsPtr[0]);
          if (blkH == 16)
#ifdef ENABLE_SEARCH_WINDOW
            partialSum += abs(refPsPtr[4 * refW2] - origPsPtr[8]);
#else
            partialSum += abs(refPsPtr[4 * refW] - origPsPtr[8]);
#endif
        }

        /* Accumulate sad until no pels left or sad is worse than best so far */
        // take away partial sum
        if  ( (  (!low_complex_prof3) && (partialSum + currSad < lclBestSad) ) 
                  || (low_complex_prof3)  )

        {
#ifdef DBG_STATISTICS
          matchOperationsCounts[4] ++;
#endif

          refPtr = refLine + (vecX >> 1);
          currSad = findSad2_8x(orig, refPtr, refW, blkH, currSad, lclBestSad);

          if (currSad < lclBestSad) {
            lclBestSad   = currSad;
            lclBestVec.x = (int16)vecX;
            lclBestVec.y = (int16)vecY;
          }
        }        
        else
        {
#ifdef DBG_STATISTICS
          matchOperationsCounts[5] ++;
#endif
        }
      }
    }
    break;
    
  default:    // blk->width == 16
    /* Scan motion vectors within search area */
    for (vecY = startY; vecY <= stopY; vecY += step) {

#ifdef ENABLE_SEARCH_WINDOW
      refPsLine = & mbPart->refPartSum[(vecY >> 2) * (refW2 >> 1)];
#else
      refPsLine = & mbPart->refPartSum[(vecY >> 2) * (refW >> 1)];
#endif
      refLine = & mbPart->ref[(vecY >> 1) * refW];
      overhead = (int32) mbPart->vlcMvBitsY[vecY] * lambda;

      for (vecX = startX; vecX <= stopX; vecX += step) {

        /* Take into account number fo bits spent for motion vector */
        currSad = (int32)lambda * vlcMvBitsX[vecX] + overhead;

#ifdef DBG_STATISTICS
        matchOperationsCounts[6] ++;
#endif

        if (mbPart->mode == MOT_16x16)
        {
          if ((vecY | vecX) == 0)
            currSad -= lambda * ZERO_VEC_SAD;
        }

        // calculate the partial results here                
        // take away partial sum
        if (!low_complex_prof3)
        {
          refPsPtr = refPsLine + (vecX >> 2); 
          origPsPtr = mbPart->partSum;
          partialSum  = abs(refPsPtr[0]  - origPsPtr[0]);
          partialSum += abs(refPsPtr[8]  - origPsPtr[2]);
          if (blkH == 16)
          {
#ifdef ENABLE_SEARCH_WINDOW
            partialSum += abs(refPsPtr[4 * refW2 + 0]  - origPsPtr[8]);
            partialSum += abs(refPsPtr[4 * refW2 + 8]  - origPsPtr[10]);
#else
            partialSum += abs(refPsPtr[4 * refW + 0]  - origPsPtr[8]);
            partialSum += abs(refPsPtr[4 * refW + 8]  - origPsPtr[10]);
#endif
          }
        }

        // take away partial sum

        /* Accumulate sad until no pels left or sad is worse than best so far */
        if ( ( (!low_complex_prof3) && (partialSum + currSad < lclBestSad) )
                || (low_complex_prof3)  )
        {
#ifdef DBG_STATISTICS
          matchOperationsCounts[7] ++;
#endif
          refPtr = refLine + (vecX >> 1); 

          currSad = findSad2_16x(orig, refPtr, refW, blkH, currSad, lclBestSad);

          if (currSad < lclBestSad) {
            lclBestSad   = currSad;
            lclBestVec.x = (int16)vecX;
            lclBestVec.y = (int16)vecY;
          }
        }
      }
    }
    break;
  }

  *bestSad = lclBestSad;
  *bestVec = lclBestVec;
}


// center has been searched already
const motVec_s searchPatt[9] =
{
  {-1,  0}, { 0, -1}, { 1,  0}, { 0,  1},
  {-1, -1}, { 1, -1}, {-1,  1}, { 1,  1},
  {0, 0}
};

const motVec_s searchPatt_fast[11][3] =
{
  { {1,1},  {1,0},  {0,1} },
  { {1,0}, {1,-1},  {1,1} },
  { {1,-1}, {0,-1}, {1,0} },
  { {1,-1}, {1,0},  {1,1} },//3 never used
  { {0,1}, {-1,1},  {1,1} },
  { {-1,1}, {0,1},  {1,1} },//5 never used
  { {0,-1},{-1,-1}, {1,-1}},
  { {-1,-1},{0,-1}, {1,-1}},//7 never used
  { {-1,1}, {-1,0}, {0,1} },
  { {-1,0},{-1,-1}, {-1,1}},
  { {-1,-1}, {-1,0},{0,-1}}
};

int matchBlockLocal4(mbPart_s *mbPart, 
                     int step,
                     motVec_s *bestVec,
                     int32 *bestSad,
                     int32 *neighborSads)
{
  motVec_s centerVec, lclBestVec;
  int i, vecX, vecY;
  int32 currSad;
  int32 lclBestSad;
  int lambda;
  int centerBest;
  motVec_s lclSearchPatt[8];


  lambda = mbPart->lambdaCoarse;

  centerVec   = *bestVec;
  lclBestVec  = *bestVec;
  lclBestSad  = *bestSad;

#ifdef DBG_STATISTICS
  matchBlockQuarterCount ++;
#endif

  for (i = 0; i < 4; i ++)
  {
    lclSearchPatt[i].x = (int16) (searchPatt[i].x * step);
    lclSearchPatt[i].y = (int16) (searchPatt[i].y * step);
  }

  /* Scan motion vectors within search area */
  centerBest = 1;

  for (i = 0; i < 4; i ++)
  {
    vecX = centerVec.x + lclSearchPatt[i].x;
    vecY = centerVec.y + lclSearchPatt[i].y;

    // refinement occurs only inside limits
    if ( (vecX < mbPart->vecLmt0[0]) || (vecY < mbPart->vecLmt0[1]) ||
         (vecX > mbPart->vecLmt1[0]) || (vecY > mbPart->vecLmt1[1]) )
    {
      neighborSads[i] = (int32)1<<24;
      continue;
    }

    /* Take into account number fo bits spent for motion vector */
    currSad = (int32)lambda * 
      (mbPart->vlcMvBitsX[vecX] + mbPart->vlcMvBitsY[vecY]);

    /* Favor 16x16 blocks that have zero motion */
    if (mbPart->mode == MOT_16x16)
    {
      if ((vecY | vecX) == 0)
        currSad -= lambda * ZERO_VEC_SAD;
    }

    /* Accumulate sad until no pels left or sad is worse than best so far */
    currSad = findSAD2(mbPart->orig, mbPart->ref, mbPart->refWidth, 
      mbPart->width, mbPart->height, vecX, vecY, currSad, INT_MAX);

    neighborSads[i] = currSad;
    if (currSad < lclBestSad) {
      centerBest = 0;
      lclBestSad   = currSad;
      lclBestVec.x = (int16)vecX;
      lclBestVec.y = (int16)vecY;
    }
  }

  *bestVec = lclBestVec;
  *bestSad = lclBestSad;

  return centerBest;
}


void matchBlockDiamond(mbPart_s *mbPart, 
                       int step,
                       motVec_s *bestVec,
                       int32 *bestSad, 
                       int hadamard)
{
  motVec_s centerVec, lclBestVec, lastBestVec;
  int i, vecX, vecY;
  int32 currSad;
  int32 lclBestSad;
  int lambda;
  int numPositions;
  motVec_s lclSearchPatt[9];


  lambda = mbPart->lambdaCoarse;

  centerVec   = *bestVec;
  lclBestVec  = *bestVec;
  lclBestSad  = *bestSad;

  lastBestVec = lclBestVec;

#ifdef DBG_STATISTICS
  matchBlockQuarterCount ++;
#endif

  if (mbPart->profile == PROF_CODING_SPEED)
    numPositions = 6;
  else
    numPositions = 9;

  for (i = 0; i < numPositions; i ++)
  {
    lclSearchPatt[i].x = (int16) (searchPatt[i].x * step);
    lclSearchPatt[i].y = (int16) (searchPatt[i].y * step);
  }

  /* Scan motion vectors within search area */
  for (i = 0; i < numPositions; i ++)
  {
    vecX = centerVec.x + lclSearchPatt[i].x;
    vecY = centerVec.y + lclSearchPatt[i].y;

    // refinement occurs only inside limits
    if ( (vecX >= mbPart->vecLmt0[0]) && (vecY >= mbPart->vecLmt0[1]) &&
         (vecX <= mbPart->vecLmt1[0]) && (vecY <= mbPart->vecLmt1[1]) )
    {
      /* Take into account number fo bits spent for motion vector */
      currSad = lambda * 
        (mbPart->vlcMvBitsX[vecX] + mbPart->vlcMvBitsY[vecY]);
      
      /* Favor 16x16 blocks that have zero motion */
      if (mbPart->mode == MOT_16x16)
      {
        if ((vecY | vecX) == 0)
          currSad -= lambda * ZERO_VEC_SAD;
      }
      
      /* Accumulate sad until no pels left or sad is worse than best so far */
      if (currSad < lclBestSad) {
        if (step == 1)
        {
          currSad = findSATD4(mbPart->orig, mbPart->ref, mbPart->refWidth, 
            mbPart->width, mbPart->height, vecX, vecY, currSad, lclBestSad, hadamard);
        }
        else
        {
          currSad = findSAD2(mbPart->orig, mbPart->ref, mbPart->refWidth, 
            mbPart->width, mbPart->height, vecX, vecY, currSad, lclBestSad);
        }
        if (currSad < lclBestSad) {
          lclBestSad   = currSad;
          lclBestVec.x = (int16)vecX;
          lclBestVec.y = (int16)vecY;
        }
      }
    }

    // let's see if the center is changed
    if (mbPart->profile == PROF_CODING_SPEED)
    {
      if (i == 3)
      {
        if ((lastBestVec.x == lclBestVec.x) && (lastBestVec.y == lclBestVec.y))
          break;
        else
        {
          if (lastBestVec.x == lclBestVec.x)
          {
            // either top or bottom, need to search the left or right
            lclSearchPatt[4].x = (int16) (-step);
            lclSearchPatt[4].y = (int16) (lclBestVec.y - centerVec.y);
            lclSearchPatt[5].x = (int16) (step);
            lclSearchPatt[5].y = (int16) (lclBestVec.y - centerVec.y);
          }
          else
          {
            // either left or right, need to search the top or bottom
            lclSearchPatt[4].x = (int16) (lclBestVec.x - centerVec.x);
            lclSearchPatt[4].y = (int16) (-step);
            lclSearchPatt[5].x = (int16) (lclBestVec.x - centerVec.x);
            lclSearchPatt[5].y = (int16) (step);
          }
        } 
      }
    }
  }

  *bestVec = lclBestVec;
  *bestSad = lclBestSad;
}


void matchBlockDiamond_fast(mbPart_s *mbPart, 
                       int step,
                       motVec_s *bestVec,
                       int32 *bestSad, 
                       int hadamard,
                       int search_indx)
{
  motVec_s centerVec, lclBestVec, lastBestVec;
  int i, vecX, vecY;
  int32 currSad;
  int32 lclBestSad;
  int lambda;
  int numPositions;
  motVec_s lclSearchPatt[9];


  lambda = mbPart->lambdaCoarse;

  centerVec   = *bestVec;
  lclBestVec  = *bestVec;
  lclBestSad  = *bestSad;

  lastBestVec = lclBestVec;

#ifdef DBG_STATISTICS
  matchBlockQuarterCount ++;
#endif

  numPositions = 3;

  for (i = 0; i < numPositions; i ++)
  {
    lclSearchPatt[i].x = (int16) (searchPatt_fast[search_indx][i].x * step);
    lclSearchPatt[i].y = (int16) (searchPatt_fast[search_indx][i].y * step);
  }

  /* Scan motion vectors within search area */
  for (i = 0; i < numPositions; i ++)
  {
    vecX = centerVec.x + lclSearchPatt[i].x;
    vecY = centerVec.y + lclSearchPatt[i].y;

    // refinement occurs only inside limits
    if ( (vecX >= mbPart->vecLmt0[0]) && (vecY >= mbPart->vecLmt0[1]) &&
         (vecX <= mbPart->vecLmt1[0]) && (vecY <= mbPart->vecLmt1[1]) )
    {
      /* Take into account number fo bits spent for motion vector */
      currSad = lambda * 
        (mbPart->vlcMvBitsX[vecX] + mbPart->vlcMvBitsY[vecY]);
      
      /* Favor 16x16 blocks that have zero motion */
      if (mbPart->mode == MOT_16x16)
      {
        if ((vecY | vecX) == 0)
          currSad -= lambda * ZERO_VEC_SAD;
      }
      
      /* Accumulate sad until no pels left or sad is worse than best so far */
      if (currSad < lclBestSad) {
        if (step == 1)
        {
          currSad = findSATD4(mbPart->orig, mbPart->ref, mbPart->refWidth, 
            mbPart->width, mbPart->height, vecX, vecY, currSad, lclBestSad, hadamard);
        }
        else
        {
          currSad = findSAD2(mbPart->orig, mbPart->ref, mbPart->refWidth, 
            mbPart->width, mbPart->height, vecX, vecY, currSad, lclBestSad);
        }
        if (currSad < lclBestSad) {
          lclBestSad   = currSad;
          lclBestVec.x = (int16)vecX;
          lclBestVec.y = (int16)vecY;
        }
      }
    }

    /*
    // let's see if the center is changed
      if (mbPart->profile == PROF_CODING_SPEED)
    {
      if (i == 3)
      {
        if ((lastBestVec.x == lclBestVec.x) && (lastBestVec.y == lclBestVec.y))
          break;
        else
        {
          if (lastBestVec.x == lclBestVec.x)
          {
            // either top or bottom, need to search the left or right
            lclSearchPatt[4].x = (int16) (-step);
            lclSearchPatt[4].y = (int16) (lclBestVec.y - centerVec.y);
            lclSearchPatt[5].x = (int16) (step);
            lclSearchPatt[5].y = (int16) (lclBestVec.y - centerVec.y);
          }
          else
          {
            // either left or right, need to search the top or bottom
            lclSearchPatt[4].x = (int16) (lclBestVec.x - centerVec.x);
            lclSearchPatt[4].y = (int16) (-step);
            lclSearchPatt[5].x = (int16) (lclBestVec.x - centerVec.x);
            lclSearchPatt[5].y = (int16) (step);
          }
        } 
      }
    }*/
  }

  *bestVec = lclBestVec;
  *bestSad = lclBestSad;
}


/*
 * MergeTree
 *
 * Parameters:
 *      mrPairs            Stores 1 pair of (ref + mv) for each block in MB, 
 *                         no matter how the MB is partitioned.
 *      interMode          Inter-prediction mode for the MB
 *
 * Function:
 *      Check if all the partitions have the same MV and ref. If it is, change
 *      the mode to MOT_16x16, so it can be skipped if other conditions allow.
 *      Sometimes, an MB or sub-MB can be separated into multiple partitions
 *      but all the partitions have the same motion vector. Sometimes it is
 *      due to the greedy search, and they should be merged. Sometimes 
 *      encoding multiple motion vectors can cost less bits because of some
 *      prediction rules favor this particular separation. 
 *
 * Returns:
 *      -
 */
int MergeTree(blkState_s *mrPairs, 
              int        *interMode)
{
  int i;
  int merged;
  int newInterMode;

  newInterMode = *interMode;

  merged = 1;
  if (*interMode == MOT_8x8)
  {
    for (i = 0; i < 16; i ++)
    {
      if (mrPairs[0].mv.x != mrPairs[i].mv.x || 
        mrPairs[0].mv.y != mrPairs[i].mv.y ||
        mrPairs[0].ref != mrPairs[i].ref)
      {
        merged = 0;
        break;
      }
    }
  }
  else
  {
    if (*interMode == MOT_16x8)
    {
      if (mrPairs[0].mv.x != mrPairs[8].mv.x ||
        mrPairs[0].mv.y != mrPairs[8].mv.y ||
        mrPairs[0].ref != mrPairs[8].ref)
        merged = 0;
    }
    if (*interMode == MOT_8x16)
    {
      if (mrPairs[0].mv.x != mrPairs[2].mv.x ||
        mrPairs[0].mv.y != mrPairs[2].mv.y ||
        mrPairs[0].ref != mrPairs[2].ref)
        merged = 0;
    }
  }

  // merge has happened at the MB level
  if (merged)
    *interMode = MOT_16x16;

  return merged;
}

