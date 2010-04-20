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

#include <stdio.h>
#include "globals.h"
#include "prederrordec.h"
#include "intrapred.h"


/*
 * Prototypes for static functions
 */
static void intraPred4x4(u_int8 predBlk[BLK_SIZE][MBK_SIZE], int mode,
                         u_int8 *reco, int picWidth, int blkAvailBits);


/*
 *
 * intraPred4x4
 *
 * Parameters:
 *      predBlk               Return pointer for predicted pixels
 *      mode                  Prediction for the block
 *      reco                  Reconstruction pixels
 *      picWidth              Horizontal size of the frame
 *      blkAvailBits          Availability of neighboring blocks
 *
 * Function:
 *      Compute prediction for one 4x4 block using given mode
 *
 * Returns:
 *      -
 *
 */
static void intraPred4x4(u_int8 predBlk[BLK_SIZE][MBK_SIZE], int mode,
                         u_int8 *reco, int picWidth, int blkAvailBits)
{
  int i;
  int X,A,B,C,D,E,F,G,H,I,J,K,L;
  int dc;
#ifdef AVC_ARM_ASSEMBLY
  u_int32 tmp;
#else
  int j;
#endif


  /*
   * Copy reconstruction pixels used for prediction
   */
  if (blkAvailBits & 0x1000) /* up-left */
    X = reco[0];
  else
    X = 128;

  if (blkAvailBits & 0x0010) { /* up */
    A = reco[1];
    B = reco[2];
    C = reco[3];
    D = reco[4];
    if (blkAvailBits & 0x0100) { /* up-right */
      E = reco[5];
      F = reco[6];
      G = reco[7];
      H = reco[8];
    }
    else
      E = F = G = H = D;
  }
  else
    A = B = C = D = E = F = G = H = 128;

  if (blkAvailBits & 0x0001) { /* left */
    I = reco[1*picWidth];
    J = reco[2*picWidth];
    K = reco[3*picWidth];
    L = reco[4*picWidth];
  }
  else
    I = J = K = L = 128;


  switch (mode) {

  case IPR_MODE_DC:

    /* DC PREDICTION */
    if ((blkAvailBits & 0x0010) && (blkAvailBits & 0x0001)) /* up & left */
      dc = (A+B+C+D+I+J+K+L+4)>>3;
    else if (blkAvailBits & 0x0010) /* up */
      dc = (A+B+C+D+2)>>2;
    else if (blkAvailBits & 0x0001) /* left */
      dc = (I+J+K+L+2)>>2;
    else
      dc = 128;

#ifdef AVC_ARM_ASSEMBLY
    tmp =  (u_int32)dc | ((u_int32)dc<<8);
    tmp =  tmp | (tmp<<16);
    *((u_int32 *)predBlk[0]) = tmp;
    *((u_int32 *)predBlk[1]) = tmp;
    *((u_int32 *)predBlk[2]) = tmp;
    *((u_int32 *)predBlk[3]) = tmp;
#else
    for (j = 0; j < BLK_SIZE; j++) {
      predBlk[j][0] = (u_int8) dc;
      predBlk[j][1] = (u_int8) dc;
      predBlk[j][2] = (u_int8) dc;
      predBlk[j][3] = (u_int8) dc;
    }
#endif
      
    break;

  case IPR_MODE_VERT:

    /* VERTICAL PREDICTION */
#ifdef AVC_ARM_ASSEMBLY
    tmp = (u_int32)A | ((u_int32)B<<8) | ((u_int32)C<<16) | ((u_int32)D<<24);
    *((u_int32 *)predBlk[0]) = tmp;
    *((u_int32 *)predBlk[1]) = tmp;
    *((u_int32 *)predBlk[2]) = tmp;
    *((u_int32 *)predBlk[3]) = tmp;
#else  
    for (j = 0; j < BLK_SIZE; j++) {
      predBlk[j][0] = (u_int8) A;
      predBlk[j][1] = (u_int8) B;
      predBlk[j][2] = (u_int8) C;
      predBlk[j][3] = (u_int8) D;
    }
#endif

    break;

  case IPR_MODE_HOR:

    /* HORIZONTAL PREDICTION */
    for (i = 0; i < BLK_SIZE; i++) {
      predBlk[0][i] = (u_int8) I;
      predBlk[1][i] = (u_int8) J;
      predBlk[2][i] = (u_int8) K;
      predBlk[3][i] = (u_int8) L;
    }

    break;

  case IPR_MODE_DIAG_DOWN_RIGHT:

    /* DIAGONAL PREDICTION */
    predBlk[3][0] = (u_int8) ((L+2*K+J+2)>>2);
    predBlk[2][0] = 
    predBlk[3][1] = (u_int8) ((K+2*J+I+2)>>2);
    predBlk[1][0] = 
    predBlk[2][1] = 
    predBlk[3][2] = (u_int8) ((J+2*I+X+2)>>2);
    predBlk[0][0] = 
    predBlk[1][1] = 
    predBlk[2][2] = 
    predBlk[3][3] = (u_int8) ((I+2*X+A+2)>>2);
    predBlk[0][1] = 
    predBlk[1][2] = 
    predBlk[2][3] = (u_int8) ((X+2*A+B+2)>>2);
    predBlk[0][2] = 
    predBlk[1][3] = (u_int8) ((A+2*B+C+2)>>2);
    predBlk[0][3] = (u_int8) ((B+2*C+D+2)>>2);

    break;

  case IPR_MODE_DIAG_DOWN_LEFT:
    predBlk[0][0] = (u_int8) ((A+2*B+C+2)>>2);
    predBlk[0][1] = 
    predBlk[1][0] = (u_int8) ((B+2*C+D+2)>>2);
    predBlk[0][2] =
    predBlk[1][1] =
    predBlk[2][0] = (u_int8) ((C+2*D+E+2)>>2);
    predBlk[0][3] = 
    predBlk[1][2] = 
    predBlk[2][1] = 
    predBlk[3][0] = (u_int8) ((D+2*E+F+2)>>2);
    predBlk[1][3] = 
    predBlk[2][2] = 
    predBlk[3][1] = (u_int8) ((E+2*F+G+2)>>2);
    predBlk[2][3] = 
    predBlk[3][2] = (u_int8) ((F+2*G+H+2)>>2);
    predBlk[3][3] = (u_int8) ((G+3*H+2)>>2);

    break;

  case IPR_MODE_VERT_RIGHT:/* diagonal prediction -22.5 deg to horizontal plane */
    predBlk[0][0] = 
    predBlk[2][1] = (u_int8) ((X+A+1)>>1);
    predBlk[0][1] = 
    predBlk[2][2] = (u_int8) ((A+B+1)>>1);
    predBlk[0][2] = 
    predBlk[2][3] = (u_int8) ((B+C+1)>>1);
    predBlk[0][3] = (u_int8) ((C+D+1)>>1);
    predBlk[1][0] = 
    predBlk[3][1] = (u_int8) ((I+2*X+A+2)>>2);
    predBlk[1][1] = 
    predBlk[3][2] = (u_int8) ((X+2*A+B+2)>>2);
    predBlk[1][2] = 
    predBlk[3][3] = (u_int8) ((A+2*B+C+2)>>2);
    predBlk[1][3] = (u_int8) ((B+2*C+D+2)>>2);
    predBlk[2][0] = (u_int8) ((X+2*I+J+2)>>2);
    predBlk[3][0] = (u_int8) ((I+2*J+K+2)>>2);

    break;

  case IPR_MODE_VERT_LEFT:/* diagonal prediction -22.5 deg to horizontal plane */
    predBlk[0][0] = (u_int8) ((A+B+1)>>1);
    predBlk[0][1] = 
    predBlk[2][0] = (u_int8) ((B+C+1)>>1);
    predBlk[0][2] = 
    predBlk[2][1] = (u_int8) ((C+D+1)>>1);
    predBlk[0][3] = 
    predBlk[2][2] = (u_int8) ((D+E+1)>>1);
    predBlk[2][3] = (u_int8) ((E+F+1)>>1);
    predBlk[1][0] = (u_int8) ((A+2*B+C+2)>>2);
    predBlk[1][1] = 
    predBlk[3][0] = (u_int8) ((B+2*C+D+2)>>2);
    predBlk[1][2] = 
    predBlk[3][1] = (u_int8) ((C+2*D+E+2)>>2);
    predBlk[1][3] = 
    predBlk[3][2] = (u_int8) ((D+2*E+F+2)>>2);
    predBlk[3][3] = (u_int8) ((E+2*F+G+2)>>2);

    break;

  case IPR_MODE_HOR_UP:/* diagonal prediction -22.5 deg to horizontal plane */
    predBlk[0][0] = (u_int8) ((I+J+1)>>1);
    predBlk[0][1] = (u_int8) ((I+2*J+K+2)>>2);
    predBlk[0][2] = 
    predBlk[1][0] = (u_int8) ((J+K+1)>>1);
    predBlk[0][3] = 
    predBlk[1][1] = (u_int8) ((J+2*K+L+2)>>2);
    predBlk[1][2] = 
    predBlk[2][0] = (u_int8) ((K+L+1)>>1);
    predBlk[1][3] = 
    predBlk[2][1] = (u_int8) ((K+2*L+L+2)>>2);
    predBlk[2][3] = 
    predBlk[3][1] = 
    predBlk[2][2] = 
    predBlk[3][0] = 
    predBlk[3][2] = 
    predBlk[3][3] = (u_int8) L;

    break;

  case IPR_MODE_HOR_DOWN:/* diagonal prediction -22.5 deg to horizontal plane */
    predBlk[0][0] = 
    predBlk[1][2] = (u_int8) ((X+I+1)>>1);
    predBlk[0][1] = 
    predBlk[1][3] = (u_int8) ((I+2*X+A+2)>>2);
    predBlk[0][2] = (u_int8) ((X+2*A+B+2)>>2);
    predBlk[0][3] = (u_int8) ((A+2*B+C+2)>>2);
    predBlk[1][0] = 
    predBlk[2][2] = (u_int8) ((I+J+1)>>1);
    predBlk[1][1] = 
    predBlk[2][3] = (u_int8) ((X+2*I+J+2)>>2);
    predBlk[2][0] = 
    predBlk[3][2] = (u_int8) ((J+K+1)>>1);
    predBlk[2][1] = 
    predBlk[3][3] = (u_int8) ((I+2*J+K+2)>>2);
    predBlk[3][0] = (u_int8) ((K+L+1)>>1);
    predBlk[3][1] = (u_int8) ((J+2*K+L+2)>>2);
    break;

  default:
    printf("Illegal 4x4 intra mode\n");
    break;
  }
}


/*
 *
 * iprPredLuma4x4blocks
 *
 * Parameters:
 *      coef                  Transform coefficints for 4x4 blocks
 *      reco                  Reconstruction pixels
 *      picWidth              Horizontal size of the frame
 *      picHeight             Vertical size of the frame
 *      ipModes               Intra prediction modes for the frame
 *      mbAvailBits           Macroblock availability flags
 *      mbIdxX                Horz. location of the MB in the frame
 *      mbIdxY                Vert. location of the MB in the frame
 *      cbp                   Coded Block Pattern
 *      qp                    Quantization parameter
 *
 * Function:
 *      Make 4x4 luma intra prediction for all blocks in the macroblock.
 *
 * Returns:
 *      -
 *
 */
void iprPredLuma4x4blocks(int coef[BLK_PER_MB][BLK_PER_MB][BLK_SIZE][BLK_SIZE],
                          u_int8 *reco, int picWidth, int8 *ipModes,
                          int mbAvailBits, int mbIdxX, int mbIdxY, int cbp, int qp)
{
  u_int8 predY[BLK_SIZE][MBK_SIZE];
  int blkIdxX, blkIdxY;
  int blkAvailUp, blkAvailLeft, blkAvailUpRight, blkAvailUpLeft;
  u_int8 *recoPtr;
  int blkAvailBits;
  int blkNum;
  double intraTime;


  recoPtr = &reco[mbIdxY*MBK_SIZE*picWidth+mbIdxX*MBK_SIZE];

  /*
   * Check block availability (1 bit per block, 4 directions)
   */
  blkAvailUp = (mbAvailBits & 2) ? 0xFFFF : 0xFFF0;

  blkAvailLeft = (mbAvailBits & 1) ? 0xFFFF : 0xEEEE;

  blkAvailUpRight = 0x5750;
  if (mbAvailBits & 2) blkAvailUpRight |= 0x0007;
  if (mbAvailBits & 4) blkAvailUpRight |= 0x0008;

  blkAvailUpLeft = 0xEEE0;
  if (mbAvailBits & 2) blkAvailUpLeft |= 0x000E;
  if (mbAvailBits & 1) blkAvailUpLeft |= 0x1110;
  if (mbAvailBits & 8) blkAvailUpLeft |= 0x0001;

  intraTime = 0.0; 

  /*
   * Build 4x4 intra prediction
   */
  for (blkIdxY = 0; blkIdxY < BLK_PER_MB; blkIdxY++) {

    /* Gather availability bits for 4 blocks in raster scan order */
    blkAvailBits = ( blkAvailLeft    & 0x000f       ) |
                   ((blkAvailUp      & 0x000f) <<  4) |
                   ((blkAvailUpRight & 0x000f) <<  8) |
                   ((blkAvailUpLeft  & 0x000f) << 12);

    /* Next 4 blocks */
    blkAvailLeft    >>= 4;
    blkAvailUp      >>= 4;
    blkAvailUpRight >>= 4;
    blkAvailUpLeft  >>= 4;

    for (blkIdxX = 0; blkIdxX < BLK_PER_MB; blkIdxX++) {

      blkNum = blkIdxY*BLK_PER_MB+blkIdxX;

      /* Make all possible 4x4 predictions for current block */
      intraPred4x4(predY, ipModes[blkIdxX],
                   &recoPtr[blkIdxX*BLK_SIZE-picWidth-1],
                   picWidth, blkAvailBits);

      if ((cbp>>blkNum) & 1) {
        pedRecoBlock(predY, coef[blkIdxY][blkIdxX],
                     &recoPtr[blkIdxX*BLK_SIZE], picWidth, 0, 0, qp);
      }
      else {
#ifndef AVC_RECO_BLOCK_ASM
        pedRecoBlockNoCoef(predY, &recoPtr[blkIdxX*BLK_SIZE], picWidth);
#else
        u_int8 *src, *dest;
        src  = predY[0];
        dest = &recoPtr[blkIdxX*BLK_SIZE];
        *((u_int32 *) dest)             = *((u_int32 *) src);
        *((u_int32 *)&dest[  picWidth]) = *((u_int32 *)&src[  MBK_SIZE]);
        *((u_int32 *)&dest[2*picWidth]) = *((u_int32 *)&src[2*MBK_SIZE]);
        *((u_int32 *)&dest[3*picWidth]) = *((u_int32 *)&src[3*MBK_SIZE]);
#endif
      }

      blkAvailBits >>= 1;
    }

    recoPtr   += BLK_SIZE*picWidth;
    ipModes += BLK_PER_MB;
  }
}


/*
 *
 * iprPredLuma16x16
 *
 * Parameters:
 *      predBlk               Return pointer for predicted pixels
 *      mode                  16x16 mode to be computed
 *      reco                  Reconstruction pixels
 *      picWidth              Horizontal size of the frame
 *      mbAvailBits           Contains availability flags for neighboring MBs
 *
 * Function:
 *      Predict luma pixels using one of 16x16 intra modes.
 *
 * Returns:
 *      -
 *
 */
int iprPredLuma16x16(u_int8 predBlk[MBK_SIZE][MBK_SIZE], int mode,
                     u_int8 *reco, int picWidth, int mbAvailBits)
{
  int dc;
  int H, V;
  int a, b, c;
  int i, j;
  int tmp, tmp2;
  u_int8 *recoPtr, *recoPtr2;
#ifdef AVC_ARM_ASSEMBLY
  u_int32 fourPix0, fourPix1, fourPix2, fourPix3;
#endif


  switch (mode) {

  case IPR_MODE2_DC:

    /* DC PREDICTION */
    if ((mbAvailBits & 1) && (mbAvailBits & 2)) {
      recoPtr = &reco[picWidth];
      for (dc = 0, i = 0; i < MBK_SIZE; i++) {
        dc += reco[1+i] + (*recoPtr);
        recoPtr += picWidth;
      }
      dc = (dc+16)>>5;
    }
    else if (mbAvailBits & 1) {
      recoPtr = &reco[picWidth];
      for (dc = 0, i = 0; i < MBK_SIZE; i++) {
        dc += (*recoPtr);
        recoPtr += picWidth;
      }
      dc = (dc+8)>>4;
    }
    else if (mbAvailBits & 2) {
      for (dc = 0, i = 0; i < MBK_SIZE; i++)
        dc += reco[1+i];
      dc = (dc+8)>>4;
    }
    else
      dc = 128;

#ifdef AVC_ARM_ASSEMBLY
    fourPix0 = (u_int32)dc | ((u_int32)dc<<8);
    fourPix0 = fourPix0 | (fourPix0<<16);
    for (j = 0; j < MBK_SIZE; j++) {
      *((u_int32 *)&predBlk[j][0]) = fourPix0;
      *((u_int32 *)&predBlk[j][4]) = fourPix0;
      *((u_int32 *)&predBlk[j][8]) = fourPix0;
      *((u_int32 *)&predBlk[j][12]) = fourPix0;
    }
#else
    for (j = 0; j < MBK_SIZE; j++) {
      for (i = 0; i < MBK_SIZE; i+=4) {
        predBlk[j][i+0] = (u_int8) dc;
        predBlk[j][i+1] = (u_int8) dc;
        predBlk[j][i+2] = (u_int8) dc;
        predBlk[j][i+3] = (u_int8) dc;
      }
    }
#endif

    break;

  case IPR_MODE2_VERT:

    /* VERTICAL PREDICTION */
    if (!(mbAvailBits & 2)) return -1;

#ifdef AVC_ARM_ASSEMBLY
    fourPix0 = *((u_int32 *)&reco[1]);
    fourPix1 = *((u_int32 *)&reco[5]);
    fourPix2 = *((u_int32 *)&reco[9]);
    fourPix3 = *((u_int32 *)&reco[13]);
    for (j = 0; j < MBK_SIZE; j++) {
      *((u_int32 *)&predBlk[j][0]) = fourPix0;
      *((u_int32 *)&predBlk[j][4]) = fourPix1;
      *((u_int32 *)&predBlk[j][8]) = fourPix2;
      *((u_int32 *)&predBlk[j][12]) = fourPix3;
    }
#else
    for (i = 0; i < MBK_SIZE; i++) {
      tmp = reco[1+i];
      for (j = 0; j < MBK_SIZE; j+=4) {
        predBlk[j+0][i] = (u_int8) tmp;
        predBlk[j+1][i] = (u_int8) tmp;
        predBlk[j+2][i] = (u_int8) tmp;
        predBlk[j+3][i] = (u_int8) tmp;
      }
    }
#endif

    break;

  case IPR_MODE2_HOR:

    /* HORIZONTAL PREDICTION */
    if (!(mbAvailBits & 1)) return -1;

    recoPtr = &reco[picWidth];
    for (j = 0; j < MBK_SIZE; j++) {
#ifdef AVC_ARM_ASSEMBLY
      fourPix0 = *recoPtr;
      recoPtr += picWidth;
      fourPix0 = fourPix0 | (fourPix0<<8);
      fourPix0 = fourPix0 | (fourPix0<<16);
      *((u_int32 *)&predBlk[j][0]) = fourPix0;
      *((u_int32 *)&predBlk[j][4]) = fourPix0;
      *((u_int32 *)&predBlk[j][8]) = fourPix0;
      *((u_int32 *)&predBlk[j][12]) = fourPix0;
#else
      tmp = *recoPtr;
      recoPtr += picWidth;
      for (i = 0; i < MBK_SIZE; i+=4) {
        predBlk[j][i+0] = (u_int8) tmp;
        predBlk[j][i+1] = (u_int8) tmp;
        predBlk[j][i+2] = (u_int8) tmp;
        predBlk[j][i+3] = (u_int8) tmp;
      }
#endif
    }

    break;

  case IPR_MODE2_PLANE:

    /* PLANE PREDICTION */
    if (!(mbAvailBits & 1) || !(mbAvailBits & 2) || !(mbAvailBits & 8)) return -1;

    recoPtr  = &reco[9*picWidth];
    recoPtr2 = &reco[7*picWidth];
    for (H = 0, V = 0, i = 1; i <= 8; i++) {
      H += (i * (reco[8+i] - reco[8-i]));
      V += (i * ((*recoPtr) - (*recoPtr2)));
      recoPtr  += picWidth;
      recoPtr2 -= picWidth;
    }
    a = 16*(reco[16*picWidth] + reco[16]);
    b = (int)((5*((int32)H)+32)>>6);
    c = (int)((5*((int32)V)+32)>>6);

    tmp = a + b*(0-7) + c*(0-7) + 16;

    /* Check if clipping if needed */
    tmp2 = tmp | (tmp + (MBK_SIZE-1)*b) | (tmp + (MBK_SIZE-1)*c) | (tmp + (MBK_SIZE-1)*b + (MBK_SIZE-1)*c);
    if ((unsigned int)tmp2 <= 255) {
      /* No clipping needed */
      for (j = 0; j < MBK_SIZE; j++, tmp+=c) {
        tmp2 = tmp;
        for (i = 0; i < MBK_SIZE; i+=4) {
          predBlk[j][i  ] = (u_int8) (tmp2>>5);
          tmp2 += b;
          predBlk[j][i+1] = (u_int8) (tmp2>>5);
          tmp2 += b;
          predBlk[j][i+2] = (u_int8) (tmp2>>5);
          tmp2 += b;
          predBlk[j][i+3] = (u_int8) (tmp2>>5);
          tmp2 += b;
        }
      }
    }
    else {
      /* Clipping is needed */
      for (j = 0; j < MBK_SIZE; j++, tmp+=c) {
        tmp2 = tmp;
        for (i = 0; i < MBK_SIZE; i++, tmp2+=b) {
          predBlk[j][i] = (u_int8) clip(0,255,tmp2>>5);
        }
      }
    }

    break;
  }

  return 1;
}


/*
 *
 * iprPredChroma
 *
 * Parameters:
 *      pred                  Storage for predicted pixels
 *      recoU                 Reconstruction pixels for U frame
 *      recoV                 Reconstruction pixels for V frame
 *      width                 Horizontal size of the frame
 *      mbAvailBits           Macroblock availability flags
 *      mode                  Chrominance intra mode
 *
 * Function:
 *      Make 8x8 chroma intra prediction for given macroblock.
 *
 * Returns:
 *      -
 *
 */
int iprPredChroma(u_int8 pred[MBK_SIZE/2][MBK_SIZE],
                  u_int8 *recoU, u_int8 *recoV,
                  int width, int mbAvailBits, int mode)
{
  int comp;
  u_int8 *recoPic;
  int S0, S1, S2, S3;
  int A, B, C, D;
  int H, V, a, b, c;
  int i, j;
  int tmp, tmp2;
#ifdef AVC_ARM_ASSEMBLY
  u_int32 fourPix0, fourPix1, fourPix2, fourPix3;
#endif


  switch (mode) {

  case IPR_CHROMA_MODE_DC:

    /*
     * DC prediction
     */
    for (comp = 0; comp < MBK_SIZE; comp+=MBK_SIZE/2) {
      
      recoPic = comp == 0 ? recoU : recoV;
      
      S0 = S1 = S2 = S3 = 0;
      
      if (mbAvailBits & 1) {
        for (i = 0; i < 4; i++) {
          S2 += recoPic[(1+i)*width];
          S3 += recoPic[(5+i)*width];
        }
      }
      if (mbAvailBits & 2) {
        for (i = 0; i < 4; i++) {
          S0 += recoPic[1+i];
          S1 += recoPic[5+i];
        }
      }

      if ((mbAvailBits & 1) && (mbAvailBits & 2)) {
        A = (S0 + S2 + 4)>>3;
        B = (S1 + 2)>>2;
        C = (S3 + 2)>>2;
        D = (S1 + S3 + 4)>>3;
      }
      else if (mbAvailBits & 1) {
        A = B = (S2 + 2)>>2;
        C = D = (S3 + 2)>>2;
      }
      else if (mbAvailBits & 2) {
        A = C = (S0 + 2)>>2;
        B = D = (S1 + 2)>>2;
      }
      else
        A = B = C = D = 128;

#ifdef AVC_ARM_ASSEMBLY
      fourPix0 = (u_int32)A | ((u_int32)A<<8);
      fourPix0 = fourPix0 | (fourPix0<<16); 
      fourPix1 = (u_int32)B | ((u_int32)B<<8);
      fourPix1 = fourPix1 | (fourPix1<<16); 
      fourPix2 = (u_int32)C | ((u_int32)C<<8);
      fourPix2 = fourPix2 | (fourPix2<<16); 
      fourPix3 = (u_int32)D | ((u_int32)D<<8);
      fourPix3 = fourPix3 | (fourPix3<<16); 
      for (j = 0; j < BLK_SIZE; j++) {
        *((u_int32 *)&pred[j  ][comp  ]) = fourPix0;
        *((u_int32 *)&pred[j  ][comp+4]) = fourPix1;
        *((u_int32 *)&pred[4+j][comp  ]) = fourPix2;
        *((u_int32 *)&pred[4+j][comp+4]) = fourPix3;
      }
#else
      for (j = 0; j < BLK_SIZE; j++) {
        for (i = 0; i < BLK_SIZE; i++) {
          pred[j  ][comp+i  ] = (u_int8) A;
          pred[j  ][comp+4+i] = (u_int8) B;
          pred[4+j][comp+i  ] = (u_int8) C;
          pred[4+j][comp+4+i] = (u_int8) D;
        }
      }
#endif
    }

    break;

  case IPR_CHROMA_MODE_VERT:

    /*
     * Vertical prediction
     */
    if (!(mbAvailBits & 2)) return -1;

    for (comp = 0; comp < MBK_SIZE; comp+=MBK_SIZE/2) {

      recoPic = comp == 0 ? recoU : recoV;

#ifdef AVC_ARM_ASSEMBLY
      fourPix0 = *((u_int32 *)&recoPic[1]);
      fourPix1 = *((u_int32 *)&recoPic[5]);
      for (j = 0; j < MBK_SIZE/2; j++) {
        *((u_int32 *)&pred[j][comp  ]) = fourPix0;
        *((u_int32 *)&pred[j][comp+4]) = fourPix1;
      }
#else
      for (i = 0; i < MBK_SIZE/2; i++) {
        tmp = recoPic[1+i];
        for (j = 0; j < MBK_SIZE/2; j+=4) {
          pred[j+0][comp+i] = (u_int8) tmp;
          pred[j+1][comp+i] = (u_int8) tmp;
          pred[j+2][comp+i] = (u_int8) tmp;
          pred[j+3][comp+i] = (u_int8) tmp;
        }
      }
#endif
    }

    break;

  case IPR_CHROMA_MODE_HOR:

    /*
     * Horizontal prediction
     */
    if (!(mbAvailBits & 1)) return -1;

    for (comp = 0; comp < MBK_SIZE; comp+=MBK_SIZE/2) {

      recoPic = comp == 0 ? recoU : recoV;

      for (j = 0; j < MBK_SIZE/2; j++) {
#ifdef AVC_ARM_ASSEMBLY
        fourPix0 = recoPic[(1+j)*width];
        fourPix0 = fourPix0 | (fourPix0<<8);
        fourPix0 = fourPix0 | (fourPix0<<16);
        *((u_int32 *)&pred[j][comp  ]) = fourPix0;
        *((u_int32 *)&pred[j][comp+4]) = fourPix0;
#else
        tmp = recoPic[(1+j)*width];
        for (i = 0; i < MBK_SIZE/2; i+=4) {
          pred[j][comp+i+0] = (u_int8) tmp;
          pred[j][comp+i+1] = (u_int8) tmp;
          pred[j][comp+i+2] = (u_int8) tmp;
          pred[j][comp+i+3] = (u_int8) tmp;
        }
#endif
      }
    }

    break;

  case IPR_CHROMA_MODE_PLANE:

    /*
     * Plane Prediction
     */
    if (!(mbAvailBits & 1) || !(mbAvailBits & 2) || !(mbAvailBits & 8)) return -1;

    for (comp = 0; comp < MBK_SIZE; comp+=MBK_SIZE/2) {

      recoPic = comp == 0 ? recoU : recoV;

      for (H = V = 0, i = 1; i <= 4; i++) {
        H += i*(recoPic[4+i] - recoPic[4-i]);
        V += i*(recoPic[(4+i)*width] - recoPic[(4-i)*width]);
      }

      a = 16*(recoPic[8*width] + recoPic[8]);
      b = (int)((17*((int32)H)+16)>>5);
      c = (int)((17*((int32)V)+16)>>5);

      tmp = a + b*(0-3) + c*(0-3) + 16;

      /* Check if clipping if needed */
      tmp2 = tmp | (tmp + (MBK_SIZE/2-1)*b) | (tmp + (MBK_SIZE/2-1)*c) | (tmp + (MBK_SIZE/2-1)*b + (MBK_SIZE/2-1)*c);
      if ((unsigned int)tmp2 <= 255) {
        /* No clipping needed */
        for (j = 0; j < MBK_SIZE/2; j++, tmp+=c) {
          tmp2 = tmp;
          for (i = 0; i < MBK_SIZE/2; i+=4) {
            pred[j][comp+i  ] = (u_int8) (tmp2>>5);
            tmp2 += b;
            pred[j][comp+i+1] = (u_int8) (tmp2>>5);
            tmp2 += b;
            pred[j][comp+i+2] = (u_int8) (tmp2>>5);
            tmp2 += b;
            pred[j][comp+i+3] = (u_int8) (tmp2>>5);
            tmp2 += b;
          }
        }
      }
      else {
        /* Clipping is needed */
        for (j = 0; j < MBK_SIZE/2; j++, tmp+=c) {
          tmp2 = tmp;
          for (i = 0; i < MBK_SIZE/2; i++, tmp2+=b) {
            pred[j][comp+i] = (u_int8) clip(0,255,tmp2>>5);
          }
        }
      }
        
    }

    break;
  }

  return 1;
}


/*
 *
 * iprClearMBintraPred
 *
 * Parameters:
 *      modesLeftPred         Modes to the left
 *      modesUpPred           Upper modes
 *
 * Function:
 *      Set intra modes of all blocks within MB to DC prediction
 *
 * Returns:
 *      -
 *
 */
void iprClearMBintraPred(int8 *modesLeftPred, int8 *modesUpPred)
{
  int i;

  for (i = 0; i < BLK_PER_MB; i++) {
    *modesLeftPred++ = IPR_MODE_DC;
    *modesUpPred++   = IPR_MODE_DC;
  }
}


/*
 *
 * iprPutIntraModes
 *
 * Parameters:
 *      mbAvailBits           Macroblock availability flags
 *      ipModes               Encode intra modes/decoded intra modes
 *      modesLeftPred         Modes to the left
 *      modesUpPred           Upper modes
 *
 * Function:
 *      Set intra modes for current MB. Modes are predicted from
 *      the blocks up and left of the current block.
 *
 * Returns:
 *      -
 *
 */
void iprPutIntraModes(int mbAvailBits, int8 *ipModes,
                      int8 *modesLeftPred, int8 *modesUpPred)
{
  int blkIdxX, blkIdxY;
  int mostProbableMode;
  int mode, codedMode;
  int blkAvailBits;
  int8 *upPred;

  /* availability of the blocks to the left */
  blkAvailBits = (mbAvailBits & 1) ? 0xffff : 0xeeee;
  
  /* availability of the upper blocks */
  if (!(mbAvailBits & 2))
    blkAvailBits &= 0xfff0;

  upPred = modesUpPred;

  for (blkIdxY = 0; blkIdxY < BLK_PER_MB; blkIdxY++) {

    /* Get mode of the block to the left */
    mode = *modesLeftPred;

    for (blkIdxX = 0; blkIdxX < BLK_PER_MB; blkIdxX++) {

      if (blkAvailBits & 1)
        /* If left and upper blocks are available, the most probable mode */
        /* is minimum of the two modes */
        mostProbableMode =  min(mode, upPred[blkIdxX]);
      else
        /* If either left or upper block is not available, */
        /* DC mode is the most probable mode */
        mostProbableMode =  IPR_MODE_DC;

      /* Get coded mode of current block */
      codedMode = *ipModes;

      if (codedMode < 0)
        mode = mostProbableMode;
      else
        mode = (codedMode < mostProbableMode ? codedMode : codedMode+1);

      /* Overwrite coded mode with decoded mode. mode is used for prediction */
      /* of the block to the right. */
      *ipModes++ = (int8)mode;

      blkAvailBits >>= 1;
    }

    /* This mode is used for prediction of the macroblock to the right */
    *modesLeftPred++ = (int8)mode;

    upPred = ipModes-BLK_PER_MB;
  }

  /* These mode are used for prediction of the below macroblock */
  *modesUpPred++ = *upPred++;
  *modesUpPred++ = *upPred++;
  *modesUpPred++ = *upPred++;
  *modesUpPred++ = *upPred++;
}
