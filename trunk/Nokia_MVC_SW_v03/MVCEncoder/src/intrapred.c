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
 * intrapred.c
 *
 * Contains:
 *    Functions for handling intra prediction 
 *
 */

#include <limits.h>
#include "globals.h"
#include "nrctypes.h"
#include "debug.h"
#include "intrapred.h"

//#define DBG_STATISTICS

#ifdef USE_CLIPTAB
extern const u_int8 clip8Buf[768];
#endif


#ifdef DBG_STATISTICS
int countBlks16 = 0;
int countHada16 = 0;
int countHada4 = 0;
int intraModeHist4[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0, };
int intraModeHist16[5] = {0, 0, 0, 0, 0};
#endif


/*
 *
 * iprPredLuma16x16:
 *
 * Parameters:
 *      predBlk               Storage for predicted pixels
 *      modeAvail             Will contains flags indicating available
 *                            modes for current macroblock
 *      reco                  Reconstruction pixels
 *      picWidth              Horizontal size of the frame
 *      mbAvailMap            Indicate which of the 4 neighbors are available
 *
 * Function:
 *      Make 16x16 intra prediction for given macroblock.
 *
 * Returns:
 *      DC of the boundary pixels
 *
 */
int iprGetPredLuma16x16(u_int8 predBlk[IPR_NUM_MODES2][MBK_SIZE][MBK_SIZE],
                        int    *modeAvail, 
                        u_int8 *reco, 
                        int    picWidth,
                        int    mbAvailMap[4])
{
  u_int32 dc;
  int H, V;
  int a, b, c;
  int aTemp;
  int i, j;


  modeAvail[IPR_MODE2_VERT] = mbAvailMap[1];
  modeAvail[IPR_MODE2_HOR]  = mbAvailMap[0];
  modeAvail[IPR_MODE2_DC] = 1;
  modeAvail[IPR_MODE2_PLANE] = mbAvailMap[0] & mbAvailMap[1] & mbAvailMap[3];

  dc = 0;

  /* HORIZONTAL PREDICTION */
  if (modeAvail[IPR_MODE2_HOR]) {
    for (j = 0; j < MBK_SIZE; j++)
    {
#ifdef COPY_4_BYTES_AS_32_BITS
      u_int32 neighBor;

      neighBor = reco[j * picWidth - 1];
      dc += neighBor;
      neighBor = neighBor | (neighBor << 8);
      neighBor = neighBor | (neighBor << 16);

      * ((u_int32 *) & predBlk[IPR_MODE2_HOR][j][0])  = neighBor;
      * ((u_int32 *) & predBlk[IPR_MODE2_HOR][j][4])  = neighBor;
      * ((u_int32 *) & predBlk[IPR_MODE2_HOR][j][8])  = neighBor;
      * ((u_int32 *) & predBlk[IPR_MODE2_HOR][j][12]) = neighBor;
#else
      u_int8 neighBor = reco[j * picWidth - 1];
      dc += neighBor;

      for (i = 0; i < MBK_SIZE; i++)
        predBlk[IPR_MODE2_HOR][j][i] = neighBor;
#endif
    }
  }

  /* VERTICAL PREDICTION */
  if (modeAvail[IPR_MODE2_VERT]) {
#ifdef COPY_4_BYTES_AS_32_BITS
    for (i = 0; i < MBK_SIZE; i += 4)
    {
      u_int32 neighBor;

      neighBor = * (u_int32 *) & reco[-picWidth + i];

      dc += neighBor & 0xFF;
      dc += (neighBor >> 8)  & 0xFF;
      dc += (neighBor >> 16) & 0xFF;
      dc += (neighBor >> 24) & 0xFF;

      for (j = 0; j < MBK_SIZE; j ++)
        *((u_int32 *) & predBlk[IPR_MODE2_VERT][j][i]) = neighBor;
    }
#else
    for (i = 0; i < MBK_SIZE; i ++)
    {
      u_int8 neighBor = reco[-picWidth + i];
      dc += neighBor;

      for (j = 0; j < MBK_SIZE; j++)
        predBlk[IPR_MODE2_VERT][j][i] = neighBor;
    }
#endif
  }

  /* DC PREDICTION */
  if (modeAvail[IPR_MODE2_HOR] && modeAvail[IPR_MODE2_VERT])
    dc = (dc + 16) >> 5;
  else if (modeAvail[IPR_MODE2_HOR] || modeAvail[IPR_MODE2_VERT])
    dc = (dc + 8) >> 4;
  else
    dc = 128;

#ifdef COPY_4_BYTES_AS_32_BITS
  dc = dc | (dc << 8);
  dc = dc | (dc << 16);

  for (j = 0; j < MBK_SIZE; j++) {
    *((u_int32 *) & predBlk[IPR_MODE2_DC][j][0])  = dc;
    *((u_int32 *) & predBlk[IPR_MODE2_DC][j][4])  = dc;
    *((u_int32 *) & predBlk[IPR_MODE2_DC][j][8])  = dc;
    *((u_int32 *) & predBlk[IPR_MODE2_DC][j][12]) = dc;
  }
#else
  for (j = 0; j < MBK_SIZE; j++) {
    for (i = 0; i < MBK_SIZE; i ++)
      predBlk[IPR_MODE2_DC][j][i]  = (u_int8)dc;
  }
#endif

  /* PLANE PREDICTION */
  if (modeAvail[IPR_MODE2_PLANE])
  {
    u_int8 *reco0, *reco1;

    reco0 = & reco[   -picWidth + 7];
    reco1 = & reco[7 * picWidth - 1];

    for (H = 0, V = 0, i = 1; i <= 8; i++) {
      H += i * ((int) reco0[i] -            (int) reco0[-i]);
      V += i * ((int) reco1[i * picWidth] - (int) reco1[(-i) * picWidth]);
    }

    a = 16 * ((int) reco[15 * picWidth - 1] + (int) reco[-1 * picWidth + 15]);

    b = (5 * H + 32) >> 6;
    c = (5 * V + 32) >> 6;

    // pre-compute constant, complete equation (a + b(i-7) + c(j-7) + 16) >> 5
    a += 16 - 7 * (b + c);

    for (j = 0; j < MBK_SIZE; j++) {
      aTemp = a;
      for (i = 0; i < MBK_SIZE; i++) {
#ifdef USE_CLIPTAB
        predBlk[IPR_MODE2_PLANE][j][i] = clip8Buf[(aTemp >> 5) + 256];
#else
        predBlk[IPR_MODE2_PLANE][j][i] = (u_int8) max(0, min(255, (aTemp >> 5)));
#endif
        aTemp += b;
      }
      a += c;
    }
  }

  return ((int)dc&0xff);
}


//// LOW_COMPLEX_PROF3
int iprGetPredLuma16x16_fast(u_int8 predBlk[IPR_NUM_MODES2][MBK_SIZE][MBK_SIZE],
                        int    *modeAvail, 
                        u_int8 *reco, 
                        int    picWidth,
                        int    mbAvailMap[4])
{
  u_int32 dc;

  int i, j;

  modeAvail[IPR_MODE2_VERT] = mbAvailMap[1];
  modeAvail[IPR_MODE2_HOR]  = mbAvailMap[0];
  modeAvail[IPR_MODE2_DC] = 1;
  modeAvail[IPR_MODE2_PLANE] = mbAvailMap[0] & mbAvailMap[1] & mbAvailMap[3];

  dc = 0;

  /* HORIZONTAL PREDICTION */
  if (modeAvail[IPR_MODE2_HOR]) {
    for (j = 0; j < MBK_SIZE; j++)
    {
#ifdef COPY_4_BYTES_AS_32_BITS
      u_int32 neighBor;

      neighBor = reco[j * picWidth - 1];
      dc += neighBor;
      neighBor = neighBor | (neighBor << 8);
      neighBor = neighBor | (neighBor << 16);

      * ((u_int32 *) & predBlk[IPR_MODE2_HOR][j][0])  = neighBor;
      * ((u_int32 *) & predBlk[IPR_MODE2_HOR][j][4])  = neighBor;
      * ((u_int32 *) & predBlk[IPR_MODE2_HOR][j][8])  = neighBor;
      * ((u_int32 *) & predBlk[IPR_MODE2_HOR][j][12]) = neighBor;
#else
      u_int8 neighBor = reco[j * picWidth - 1];
      dc += neighBor;

      for (i = 0; i < MBK_SIZE; i++)
        predBlk[IPR_MODE2_HOR][j][i] = neighBor;
#endif
    }
  }

  /* VERTICAL PREDICTION */
  if (modeAvail[IPR_MODE2_VERT]) {
#ifdef COPY_4_BYTES_AS_32_BITS
    for (i = 0; i < MBK_SIZE; i += 4)
    {
      u_int32 neighBor;

      neighBor = * (u_int32 *) & reco[-picWidth + i];

      dc += neighBor & 0xFF;
      dc += (neighBor >> 8)  & 0xFF;
      dc += (neighBor >> 16) & 0xFF;
      dc += (neighBor >> 24) & 0xFF;

      for (j = 0; j < MBK_SIZE; j ++)
        *((u_int32 *) & predBlk[IPR_MODE2_VERT][j][i]) = neighBor;
    }
#else
    for (i = 0; i < MBK_SIZE; i ++)
    {
      u_int8 neighBor = reco[-picWidth + i];
      dc += neighBor;

      for (j = 0; j < MBK_SIZE; j++)
        predBlk[IPR_MODE2_VERT][j][i] = neighBor;
    }
#endif
  }

  /* DC PREDICTION */
  if (modeAvail[IPR_MODE2_HOR] && modeAvail[IPR_MODE2_VERT])
    dc = (dc + 16) >> 5;
  else if (modeAvail[IPR_MODE2_HOR] || modeAvail[IPR_MODE2_VERT])
    dc = (dc + 8) >> 4;
  else
    dc = 128;

#ifdef COPY_4_BYTES_AS_32_BITS
  dc = dc | (dc << 8);
  dc = dc | (dc << 16);

  for (j = 0; j < MBK_SIZE; j++) {
    *((u_int32 *) & predBlk[IPR_MODE2_DC][j][0])  = dc;
    *((u_int32 *) & predBlk[IPR_MODE2_DC][j][4])  = dc;
    *((u_int32 *) & predBlk[IPR_MODE2_DC][j][8])  = dc;
    *((u_int32 *) & predBlk[IPR_MODE2_DC][j][12]) = dc;
  }
#else
  for (j = 0; j < MBK_SIZE; j++) {
    for (i = 0; i < MBK_SIZE; i ++)
      predBlk[IPR_MODE2_DC][j][i]  = (u_int8)dc;
  }
#endif

  return ((int)dc&0xff);
}


/*
 *
 * iprGetPredLuma4x4:
 *
 * Parameters:
 *      predBlk               Storage for predicted pixels
 *      modeAvail             Will contains flags indicating available
 *                            modes for current block
 *      reco                  Points to macroblock in the reconstructed buffer 
 *      picWidth              Horizontal size of the frame
 *      leftMode              Prediction mode of the block to the left
 *      upMode                Prediction mode of the upper block
 *      cornersAvail          bit 1, up-right blk is available, bit 0, up-left is available
 *
 * Function:
 *      Make 4x4 intra prediction for given block.
 *
 * Returns:
 *      -
 *
 */
void iprGetPredLuma4x4(u_int8 predBlk[][BLK_SIZE][MBK_SIZE], 
                       int    *modeAvail,
                       u_int8 *reco, 
                       int    picWidth, 
                       int    leftMode, 
                       int    upMode, 
                       int    cornersAvail)
{
  int X,A,B,C,D,E,F,G,H,I,J,K,L;
  int dc;
  int i;
#ifdef COPY_4_BYTES_AS_32_BITS
  int intTerm;
#else
  int j;
#endif

  /*
   * Copy reconstruction pixels used for prediction
   */
  if (cornersAvail & 0x01)
    X = reco[-picWidth - 1];

  if (upMode != IPR_MODE_NA) {
    A = reco[-picWidth + 0];
    B = reco[-picWidth + 1];
    C = reco[-picWidth + 2];
    D = reco[-picWidth + 3];
    if (cornersAvail & 0x02) {
      E = reco[-picWidth + 4];
      F = reco[-picWidth + 5];
      G = reco[-picWidth + 6];
      H = reco[-picWidth + 7];
    }
    else
      E = F = G = H = D;
  }

  if (leftMode != IPR_MODE_NA) {
    I = reco[0 * picWidth - 1];
    J = reco[1 * picWidth - 1];
    K = reco[2 * picWidth - 1];
    L = reco[3 * picWidth - 1];
  }

  /* DC PREDICTION */
  if (upMode != IPR_MODE_NA && leftMode != IPR_MODE_NA)
    dc = (A+B+C+D+I+J+K+L+4)>>3;
  else if (upMode != IPR_MODE_NA)
    dc = (A+B+C+D+2)>>2;
  else if (leftMode != IPR_MODE_NA)
    dc = (I+J+K+L+2)>>2;
  else
    dc = 128;

#ifdef COPY_4_BYTES_AS_32_BITS
  intTerm = (dc << 24) + (dc << 16) + (dc << 8) + dc;
  *(int *) & predBlk[IPR_MODE_DC][0][0] = intTerm;
  *(int *) & predBlk[IPR_MODE_DC][1][0] = intTerm;
  *(int *) & predBlk[IPR_MODE_DC][2][0] = intTerm;
  *(int *) & predBlk[IPR_MODE_DC][3][0] = intTerm;
#else
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      predBlk[IPR_MODE_DC][i][j] = (u_int8) dc;
  }
#endif
  
  modeAvail[IPR_MODE_DC] = 1;
  modeAvail[IPR_MODE_VERT] = modeAvail[IPR_MODE_DIAG_DOWN_LEFT] = 
    modeAvail[IPR_MODE_VERT_LEFT] = (upMode != IPR_MODE_NA);

  modeAvail[IPR_MODE_DIAG_DOWN_RIGHT] = modeAvail[IPR_MODE_VERT_RIGHT] = 
    modeAvail[IPR_MODE_HOR_DOWN] = ((leftMode + upMode) < IPR_MODE_NA) && (cornersAvail & 1);

  if (upMode != IPR_MODE_NA) {

    /* VERTICAL PREDICTION */
#ifdef COPY_4_BYTES_AS_32_BITS

#ifdef LITTLE_ENDIAN_MVC
    intTerm = (D << 24) + (C << 16) + (B << 8) + A;
#else
    intTerm = (A << 24) + (B << 16) + (C << 8) + D;
#endif
  
    // predBlk is (u_int8 *) 16x16, addressed in integers, jump by 4 elements
    *(int *) & predBlk[IPR_MODE_VERT][0][0] = intTerm;
    *(int *) & predBlk[IPR_MODE_VERT][1][0] = intTerm;
    *(int *) & predBlk[IPR_MODE_VERT][2][0] = intTerm;
    *(int *) & predBlk[IPR_MODE_VERT][3][0] = intTerm;
#else
    for (j = 0; j < 4; j++) {
      predBlk[IPR_MODE_VERT][j][0] = (u_int8) A;
      predBlk[IPR_MODE_VERT][j][1] = (u_int8) B;
      predBlk[IPR_MODE_VERT][j][2] = (u_int8) C;
      predBlk[IPR_MODE_VERT][j][3] = (u_int8) D;
    }
#endif

    /* DIAGONAL DOWN/LEFT PREDICTION */
    predBlk[IPR_MODE_DIAG_DOWN_LEFT][0][0] = (u_int8) ((A+2*B+C+2) >> 2);
    predBlk[IPR_MODE_DIAG_DOWN_LEFT][0][1] = 
    predBlk[IPR_MODE_DIAG_DOWN_LEFT][1][0] = (u_int8) ((B+2*C+D+2) >> 2);
    predBlk[IPR_MODE_DIAG_DOWN_LEFT][0][2] =
    predBlk[IPR_MODE_DIAG_DOWN_LEFT][1][1] =
    predBlk[IPR_MODE_DIAG_DOWN_LEFT][2][0] = (u_int8) ((C+2*D+E+2) >> 2);
    predBlk[IPR_MODE_DIAG_DOWN_LEFT][0][3] = 
    predBlk[IPR_MODE_DIAG_DOWN_LEFT][1][2] = 
    predBlk[IPR_MODE_DIAG_DOWN_LEFT][2][1] = 
    predBlk[IPR_MODE_DIAG_DOWN_LEFT][3][0] = (u_int8) ((D+2*E+F+2) >> 2);
    predBlk[IPR_MODE_DIAG_DOWN_LEFT][1][3] = 
    predBlk[IPR_MODE_DIAG_DOWN_LEFT][2][2] = 
    predBlk[IPR_MODE_DIAG_DOWN_LEFT][3][1] = (u_int8) ((E+2*F+G+2) >> 2);
    predBlk[IPR_MODE_DIAG_DOWN_LEFT][2][3] = 
    predBlk[IPR_MODE_DIAG_DOWN_LEFT][3][2] = (u_int8) ((F+2*G+H+2) >> 2);
    predBlk[IPR_MODE_DIAG_DOWN_LEFT][3][3] = (u_int8) ((G+3*H+2) >> 2);

    /* VERTICAL-LEFT PREDICTION */
    predBlk[IPR_MODE_VERT_LEFT][0][0] = (u_int8) ((A+B+1) >> 1);
    predBlk[IPR_MODE_VERT_LEFT][0][1] = 
    predBlk[IPR_MODE_VERT_LEFT][2][0] = (u_int8) ((B+C+1) >> 1);
    predBlk[IPR_MODE_VERT_LEFT][0][2] = 
    predBlk[IPR_MODE_VERT_LEFT][2][1] = (u_int8) ((C+D+1) >> 1);
    predBlk[IPR_MODE_VERT_LEFT][0][3] = 
    predBlk[IPR_MODE_VERT_LEFT][2][2] = (u_int8) ((D+E+1) >> 1);
    predBlk[IPR_MODE_VERT_LEFT][2][3] = (u_int8) ((E+F+1) >> 1);
    predBlk[IPR_MODE_VERT_LEFT][1][0] = (u_int8) ((A+2*B+C+2) >> 2);
    predBlk[IPR_MODE_VERT_LEFT][1][1] = 
    predBlk[IPR_MODE_VERT_LEFT][3][0] = (u_int8) ((B+2*C+D+2) >> 2);
    predBlk[IPR_MODE_VERT_LEFT][1][2] = 
    predBlk[IPR_MODE_VERT_LEFT][3][1] = (u_int8) ((C+2*D+E+2) >> 2);
    predBlk[IPR_MODE_VERT_LEFT][1][3] = 
    predBlk[IPR_MODE_VERT_LEFT][3][2] = (u_int8) ((D+2*E+F+2) >> 2);
    predBlk[IPR_MODE_VERT_LEFT][3][3] = (u_int8) ((E+2*F+G+2) >> 2);
  }

  modeAvail[IPR_MODE_HOR] = modeAvail[IPR_MODE_HOR_UP] = 
    (leftMode != IPR_MODE_NA);

  if (leftMode != IPR_MODE_NA) {
    /* HORIZONTAL PREDICTION */
    for (i = 0; i < 4; i++) {
      predBlk[IPR_MODE_HOR][0][i] = (u_int8) I;
      predBlk[IPR_MODE_HOR][1][i] = (u_int8) J;
      predBlk[IPR_MODE_HOR][2][i] = (u_int8) K;
      predBlk[IPR_MODE_HOR][3][i] = (u_int8) L;
    }

    /* HORIZONTAL-UP PREDICTION */
    predBlk[IPR_MODE_HOR_UP][0][0] = (u_int8) ((I+J+1) >> 1);
    predBlk[IPR_MODE_HOR_UP][0][1] = (u_int8) ((I+2*J+K+2) >> 2);
    predBlk[IPR_MODE_HOR_UP][0][2] = 
    predBlk[IPR_MODE_HOR_UP][1][0] = (u_int8) ((J+K+1) >> 1);
    predBlk[IPR_MODE_HOR_UP][0][3] = 
    predBlk[IPR_MODE_HOR_UP][1][1] = (u_int8) ((J+2*K+L+2) >> 2);
    predBlk[IPR_MODE_HOR_UP][1][2] = 
    predBlk[IPR_MODE_HOR_UP][2][0] = (u_int8) ((K+L+1) >> 1);
    predBlk[IPR_MODE_HOR_UP][1][3] = 
    predBlk[IPR_MODE_HOR_UP][2][1] = (u_int8) ((K+2*L+L+2) >> 2);
    predBlk[IPR_MODE_HOR_UP][2][2] = 
    predBlk[IPR_MODE_HOR_UP][2][3] =
    predBlk[IPR_MODE_HOR_UP][3][0] =
    predBlk[IPR_MODE_HOR_UP][3][1] =
    predBlk[IPR_MODE_HOR_UP][3][2] =
    predBlk[IPR_MODE_HOR_UP][3][3] = (u_int8) L;
  }

  if (modeAvail[IPR_MODE_DIAG_DOWN_RIGHT]) {

    /* DIAGONAL DOWN/RIGHT PREDICTION */
    predBlk[IPR_MODE_DIAG_DOWN_RIGHT][3][0] = (u_int8) ((L+2*K+J+2) >> 2);
    predBlk[IPR_MODE_DIAG_DOWN_RIGHT][2][0] =
    predBlk[IPR_MODE_DIAG_DOWN_RIGHT][3][1] = (u_int8) ((K+2*J+I+2) >> 2);
    predBlk[IPR_MODE_DIAG_DOWN_RIGHT][1][0] =
    predBlk[IPR_MODE_DIAG_DOWN_RIGHT][2][1] =
    predBlk[IPR_MODE_DIAG_DOWN_RIGHT][3][2] = (u_int8) ((J+2*I+X+2) >> 2);
    predBlk[IPR_MODE_DIAG_DOWN_RIGHT][0][0] =
    predBlk[IPR_MODE_DIAG_DOWN_RIGHT][1][1] =
    predBlk[IPR_MODE_DIAG_DOWN_RIGHT][2][2] =
    predBlk[IPR_MODE_DIAG_DOWN_RIGHT][3][3] = (u_int8) ((I+2*X+A+2) >> 2);
    predBlk[IPR_MODE_DIAG_DOWN_RIGHT][0][1] =
    predBlk[IPR_MODE_DIAG_DOWN_RIGHT][1][2] =
    predBlk[IPR_MODE_DIAG_DOWN_RIGHT][2][3] = (u_int8) ((X+2*A+B+2) >> 2);
    predBlk[IPR_MODE_DIAG_DOWN_RIGHT][0][2] =
    predBlk[IPR_MODE_DIAG_DOWN_RIGHT][1][3] = (u_int8) ((A+2*B+C+2) >> 2);
    predBlk[IPR_MODE_DIAG_DOWN_RIGHT][0][3] = (u_int8) ((B+2*C+D+2) >> 2);
    
    /* VERTICAL-RIGHT PREDICTION */
    predBlk[IPR_MODE_VERT_RIGHT][0][0] = 
    predBlk[IPR_MODE_VERT_RIGHT][2][1] = (u_int8) ((X+A+1) >> 1);
    predBlk[IPR_MODE_VERT_RIGHT][0][1] = 
    predBlk[IPR_MODE_VERT_RIGHT][2][2] = (u_int8) ((A+B+1) >> 1);
    predBlk[IPR_MODE_VERT_RIGHT][0][2] = 
    predBlk[IPR_MODE_VERT_RIGHT][2][3] = (u_int8) ((B+C+1) >> 1);
    predBlk[IPR_MODE_VERT_RIGHT][0][3] = (u_int8) ((C+D+1) >> 1);
    predBlk[IPR_MODE_VERT_RIGHT][1][0] = 
    predBlk[IPR_MODE_VERT_RIGHT][3][1] = (u_int8) ((I+2*X+A+2) >> 2);
    predBlk[IPR_MODE_VERT_RIGHT][1][1] = 
    predBlk[IPR_MODE_VERT_RIGHT][3][2] = (u_int8) ((X+2*A+B+2) >> 2);
    predBlk[IPR_MODE_VERT_RIGHT][1][2] = 
    predBlk[IPR_MODE_VERT_RIGHT][3][3] = (u_int8) ((A+2*B+C+2) >> 2);
    predBlk[IPR_MODE_VERT_RIGHT][1][3] = (u_int8) ((B+2*C+D+2) >> 2);
    predBlk[IPR_MODE_VERT_RIGHT][2][0] = (u_int8) ((X+2*I+J+2) >> 2);
    predBlk[IPR_MODE_VERT_RIGHT][3][0] = (u_int8) ((I+2*J+K+2) >> 2);

    /* HORIZONTAL-DOWN PREDICTION */
    predBlk[IPR_MODE_HOR_DOWN][0][0] = 
    predBlk[IPR_MODE_HOR_DOWN][1][2] = (u_int8) ((X+I+1) >> 1);
    predBlk[IPR_MODE_HOR_DOWN][0][1] = 
    predBlk[IPR_MODE_HOR_DOWN][1][3] = (u_int8) ((I+2*X+A+2) >> 2);
    predBlk[IPR_MODE_HOR_DOWN][0][2] = (u_int8) ((X+2*A+B+2) >> 2);
    predBlk[IPR_MODE_HOR_DOWN][0][3] = (u_int8) ((A+2*B+C+2) >> 2);
    predBlk[IPR_MODE_HOR_DOWN][1][0] = 
    predBlk[IPR_MODE_HOR_DOWN][2][2] = (u_int8) ((I+J+1) >> 1);
    predBlk[IPR_MODE_HOR_DOWN][1][1] = 
    predBlk[IPR_MODE_HOR_DOWN][2][3] = (u_int8) ((X+2*I+J+2) >> 2);
    predBlk[IPR_MODE_HOR_DOWN][2][0] = 
    predBlk[IPR_MODE_HOR_DOWN][3][2] = (u_int8) ((J+K+1) >> 1);
    predBlk[IPR_MODE_HOR_DOWN][2][1] = 
    predBlk[IPR_MODE_HOR_DOWN][3][3] = (u_int8) ((I+2*J+K+2) >> 2);
    predBlk[IPR_MODE_HOR_DOWN][3][0] = (u_int8) ((K+L+1) >> 1);
    predBlk[IPR_MODE_HOR_DOWN][3][1] = (u_int8) ((J+2*K+L+2) >> 2);
  }
}


/*
 *
 * iprGetPredChroma:
 *
 * Parameters:
 *      predBlk               Storage for predicted pixels
 *      modeAvail             Will contains flags indicating available
 *                            modes for current macroblock
 *      recoU                 Reconstructed U pixels in the macroblock
 *      recoV                 Reconstructed V pixels in the macroblock
 *      width                 Horizontal size of the frame
 *      mbAvailMap            Availability of neighboring macroblocks
 *
 * Function:
 *      Make 8x8 chroma intra prediction for given macroblock.
 *
 * Returns:
 *      -
 *
 */
void iprGetPredChroma(u_int8 pred[IPR_CHROMA_NUM_MODES][MBK_SIZE/2][2*(MBK_SIZE/2)],
                      int    *modeAvail, 
                      u_int8 *recoU, 
                      u_int8 *recoV, 
                      int    width,
                      int    mbAvailMap[4])
{
  int comp;
  u_int8 *recoPic;
  int S0, S1, S2, S3;
  int A, B, C, D;
  int H, V, a, b, c;
  int aTemp;
  int i, j;

  /*
   * DC prediction
   */
  for (comp = 0; comp < MBK_SIZE; comp+=MBK_SIZE/2) {

    recoPic = comp == 0 ? recoU : recoV;

    S0 = S1 = S2 = S3 = 0;

    if (mbAvailMap[0]) {
      for (i = 0; i < 4; i++) {
        S2 += recoPic[      i * width - 1];
        S3 += recoPic[(4 + i) * width - 1];
      }
    }
    if (mbAvailMap[1]) {
      for (i = 0; i < 4; i++) {
        S0 += recoPic[-width + i];
        S1 += recoPic[-width + 4 + i];
      }
    }

    if (mbAvailMap[0] && mbAvailMap[1]) {
      A = (S0 + S2 + 4)>>3;
      B = (S1 + 2)>>2;
      C = (S3 + 2)>>2;
      D = (S1 + S3 + 4)>>3;
    }
    else if (mbAvailMap[0]) {
      A = B = (S2 + 2)>>2;
      C = D = (S3 + 2)>>2;
    }
    else if (mbAvailMap[1]) {
      A = C = (S0 + 2)>>2;
      B = D = (S1 + 2)>>2;
    }
    else
      A = B = C = D = 128;

    for (j = 0; j < BLK_SIZE; j++) {
      for (i = 0; i < BLK_SIZE; i++) {
        pred[IPR_CHROMA_MODE_DC][j  ][comp+i  ] = (u_int8) A;
        pred[IPR_CHROMA_MODE_DC][j  ][comp+4+i] = (u_int8) B;
        pred[IPR_CHROMA_MODE_DC][4+j][comp+i  ] = (u_int8) C;
        pred[IPR_CHROMA_MODE_DC][4+j][comp+4+i] = (u_int8) D;
      }
    }
  }

  modeAvail[IPR_CHROMA_MODE_DC] = 1;

  /*
   * Vertical prediction
   */
  if (mbAvailMap[1]) {
    for (comp = 0; comp < MBK_SIZE; comp+=MBK_SIZE/2) {

      recoPic = comp == 0 ? recoU : recoV;

      for (i = 0; i < MBK_SIZE/2; i++)
        for (j = 0; j < MBK_SIZE/2; j++)
          pred[IPR_CHROMA_MODE_VERT][j][comp+i] = recoPic[-width + i];
    }

    modeAvail[IPR_CHROMA_MODE_VERT] = 1;
  }
  else
    modeAvail[IPR_CHROMA_MODE_VERT] = 0;

  /*
   * Horizontal prediction
   */
  if (mbAvailMap[0]) {
    for (comp = 0; comp < MBK_SIZE; comp+=MBK_SIZE/2) {

      recoPic = comp == 0 ? recoU : recoV;

      for (j = 0; j < MBK_SIZE/2; j++)
        for (i = 0; i < MBK_SIZE/2; i++)
          pred[IPR_CHROMA_MODE_HOR][j][comp+i] = recoPic[j * width - 1];
    }

    modeAvail[IPR_CHROMA_MODE_HOR] = 1;
  }
  else
    modeAvail[IPR_CHROMA_MODE_HOR] = 0;

  /*
   * Plane Prediction
   */
  if (mbAvailMap[0] && mbAvailMap[1] && mbAvailMap[3]) {

    for (comp = 0; comp < MBK_SIZE; comp+=MBK_SIZE/2) {

      recoPic = comp == 0 ? recoU : recoV;
      
      for (H = V = 0, i = 1; i <= 4; i++) {
        H += i * (recoPic[-width + 3 + i] - recoPic[-width + 3 - i]);
        V += i * (recoPic[(3 + i) * width - 1] - recoPic[(3 - i) * width - 1]);
      }
      
      a = 16 * (recoPic[7 * width - 1] + recoPic[-width + 7]);
      b = (17 * H + 16) >> 5;
      c = (17 * V + 16) >> 5;
      
      // pre-compute constant, complete equation (a + b(i-7) + c(j-7) + 16) >> 5
      a += 16 - 3 * (b + c);
      for (j = 0; j < MBK_SIZE/2; j++) {
        aTemp = a;
        for (i = 0; i < MBK_SIZE/2; i++)
        {
          pred[IPR_CHROMA_MODE_PLANE][j][comp+i] = 
#ifdef USE_CLIPTAB
            clip8Buf[(aTemp >> 5) + 256];
#else
            (u_int8) max(0, min(255, (aTemp >> 5)));
#endif
          aTemp += b;
        }
        a += c;
      }
    }
    modeAvail[IPR_CHROMA_MODE_PLANE] = 1;
  }
  else
    modeAvail[IPR_CHROMA_MODE_PLANE] = 0;
}


