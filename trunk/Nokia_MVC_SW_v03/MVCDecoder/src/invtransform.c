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
 * invtransform.c
 *
 * Contains:
 *    Inverse transform and dequantization functions.
 *
 */

#include "globals.h"
#include "invtransform.h"


#ifndef AVC_RECO_BLOCK_ASM

/*
 *
 * itrIDCTdequant4x4:
 *
 * Parameters:
 *      src                   Source values
 *      dest                  Inverse transformed values
 *      dequantPtr            Dequant coefficients
 *      qp_per                qp/6
 *      isDc                  True if DC is separate
 *      dcValue               Possible DC value
 *
 * Function:
 *      Dequantize coefficients and compute approximate 4x4 inverse DCT.
 *
 * Returns:
 *      -
 */
void itrIDCTdequant4x4(int src[4][4], int dest[4][4], const int *dequantPtr,
                       int qp_per, int isDc, int dcValue)
{
  int tmp[4][4];
  int A, B, C, D, E, F;
  int i;
  int deqc;

  /*
   *  a = A + B + C + (D>>1)
   *  b = A + (B>>1) - C - D
   *  c = A - (B>>1) - C + D
   *  d = A - B + C - (D>>1)
   *   =>
   *  E = A + C
   *  F = B +  (D>>1)
   *  a = E + F
   *  d = E - F
   *  E = A - C
   *  F = (B>>1) - D
   *  b = E + F
   *  c = E - F
   */

  A = dcValue;

  for (i = 0; i < 4; i++) {
    deqc = (*dequantPtr++) << qp_per;

    if (!isDc)
      A = src[i][0] * deqc;

    C = src[i][2] * deqc;

    deqc = (*dequantPtr++) << qp_per;

    B = src[i][1] * deqc;
    D = src[i][3] * deqc;

    E = A +  C;
    F = B + (D>>1);
    tmp[i][0] = E + F;
    tmp[i][3] = E - F;
    E =  A     - C;
    F = (B>>1) - D;
    tmp[i][1] = E + F;
    tmp[i][2] = E - F;

    isDc = 0;
  }

  for (i = 0; i < 4; i++) {
    E = tmp[0][i] +  tmp[2][i];
    F = tmp[1][i] + (tmp[3][i]>>1);
    dest[0][i] = E + F;
    dest[3][i] = E - F;
    E =  tmp[0][i]     - tmp[2][i];
    F = (tmp[1][i]>>1) - tmp[3][i];
    dest[1][i] = E + F;
    dest[2][i] = E - F;
  }
}

#endif


/*
 *
 * itrIHadaDequant4x4:
 *
 * Parameters:
 *      src                   Source values
 *      dest                  Inverse transformed values
 *      deqc                  Dequantization coefficient
 *
 * Function:
 *      Compute 4x4 inverse Hadamard transform and dequantize coefficients.
 *
 * Returns:
 *      -
 *
 */
void itrIHadaDequant4x4(int src[4][4], int dest[4][4], int deqc)
{
  int tmp[4][4];
  int E;
  int F;
  int i;

  for (i = 0; i < 4; i++) {
    E = src[i][0] + src[i][2];
    F = src[i][1] + src[i][3];
    tmp[i][0] = E + F;
    tmp[i][3] = E - F;
    E = src[i][0] - src[i][2];
    F = src[i][1] - src[i][3];
    tmp[i][1] = E + F;
    tmp[i][2] = E - F;
  }

  for (i = 0; i < 4; i++) {
    E = tmp[0][i] + tmp[2][i];
    F = tmp[1][i] + tmp[3][i];
    dest[0][i] = ((E + F) * deqc + 2) >> 2;
    dest[3][i] = ((E - F) * deqc + 2) >> 2;
    E = tmp[0][i] - tmp[2][i];
    F = tmp[1][i] - tmp[3][i];
    dest[1][i] = ((E + F) * deqc + 2) >> 2;
    dest[2][i] = ((E - F) * deqc + 2) >> 2;
  }
}


/*
 *
 * itrIDCTdequant2x2:
 *
 * Parameters:
 *      src                   Source values
 *      dest                  Inverse transformed values
 *      deqc                  Dequantization coefficient
 *
 * Function:
 *      Compute 2x2 inverse DCT and dequantize coefficients.
 *
 * Returns:
 *      -
 *
 */
void itrIDCTdequant2x2(int src[2][2], int dest[2][2], int deqc)
{
  int DDC00 = src[0][0];
  int DDC10 = src[0][1];
  int DDC01 = src[1][0];
  int DDC11 = src[1][1];
  int A, B;

  /*
   *  DDC(0,0) DDC(1,0)  =>  DC0 DC1
   *  DDC(0,1) DDC(1,1)      DC2 DC3
   *
   *  DC0 = (DDC00+DDC10+DDC01+DDC11)
   *  DC1 = (DDC00-DDC10+DDC01-DDC11)
   *  DC2 = (DDC00+DDC10-DDC01-DDC11)
   *  DC3 = (DDC00-DDC10-DDC01+DDC11)
   */

  A = DDC00 + DDC01;
  B = DDC10 + DDC11;
  dest[0][0] = ((A + B) * deqc) >> 1;
  dest[0][1] = ((A - B) * deqc) >> 1;
  A = DDC00 - DDC01;
  B = DDC10 - DDC11;
  dest[1][0] = ((A + B) * deqc) >> 1;
  dest[1][1] = ((A - B) * deqc) >> 1;
}
