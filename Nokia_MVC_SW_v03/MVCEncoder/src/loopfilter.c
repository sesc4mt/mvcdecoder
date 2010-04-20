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
 * loopfilter.c
 *
 * Contains:
 *    Functions for loopfilter.
 *
 */

#include <stdlib.h>
#include "globals.h"
#include "nrctypes.h"
#include "loopfilter.h"


typedef struct abIdx_s_ {
  int alphaIdx;
  int betaIdx;
  int alphaIdxC;
  int betaIdxC;
} abIdx_s;


static const u_int8 alphaTab[12+52+12] = {
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,

    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    4,  4,  5,  6,  7,  8,  9, 10,
   12, 13, 15, 17, 20, 22, 25, 28,
   32, 36, 40, 45, 50, 56, 63, 71,
   80, 90,101,113,127,144,162,182,
  203,226,255,255,

  255,255,255,255,255,255,255,255,
  255,255,255,255
};

static const u_int8 betaTab[12+52+12] = {
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0,

   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   2, 2, 2, 3, 3, 3, 3, 4,
   4, 4, 6, 6, 7, 7, 8, 8,
   9, 9,10,10,11,11,12,12,
  13,13,14,14,15,15,16,16,
  17,17,18,18,

  18,18,18,18,18,18,18,18,
  18,18,18,18
};

static const u_int8 clipTab[12+52+12][4] = {
  { 0, 0, 0, 0}, { 0, 0, 0, 0}, { 0, 0, 0, 0}, { 0, 0, 0, 0},
  { 0, 0, 0, 0}, { 0, 0, 0, 0}, { 0, 0, 0, 0}, { 0, 0, 0, 0},
  { 0, 0, 0, 0}, { 0, 0, 0, 0}, { 0, 0, 0, 0}, { 0, 0, 0, 0},

  { 0, 0, 0, 0}, { 0, 0, 0, 0}, { 0, 0, 0, 0}, { 0, 0, 0, 0},
  { 0, 0, 0, 0}, { 0, 0, 0, 0}, { 0, 0, 0, 0}, { 0, 0, 0, 0},
  { 0, 0, 0, 0}, { 0, 0, 0, 0}, { 0, 0, 0, 0}, { 0, 0, 0, 0},
  { 0, 0, 0, 0}, { 0, 0, 0, 0}, { 0, 0, 0, 0}, { 0, 0, 0, 0},
  { 0, 0, 0, 0}, { 0, 0, 1, 1}, { 0, 0, 1, 1}, { 0, 0, 1, 1},
  { 0, 0, 1, 1}, { 0, 1, 1, 1}, { 0, 1, 1, 1}, { 1, 1, 1, 1},
  { 1, 1, 1, 1}, { 1, 1, 1, 1}, { 1, 1, 1, 1}, { 1, 1, 2, 2},
  { 1, 1, 2, 2}, { 1, 1, 2, 2}, { 1, 1, 2, 2}, { 1, 2, 3, 3},
  { 1, 2, 3, 3}, { 2, 2, 3, 3}, { 2, 2, 4, 4}, { 2, 3, 4, 4},
  { 2, 3, 4, 4}, { 3, 3, 5, 5}, { 3, 4, 6, 6}, { 3, 4, 6, 6},
  { 4, 5, 7, 7}, { 4, 5, 8, 8}, { 4, 6, 9, 9}, { 5, 7,10,10},
  { 6, 8,11,11}, { 6, 8,13,13}, { 7,10,14,14}, { 8,11,16,16},
  { 9,12,18,18}, {10,13,20,20}, {11,15,23,23}, {13,17,25,25},

  {13,17,25,25}, {13,17,25,25}, {13,17,25,25}, {13,17,25,25},
  {13,17,25,25}, {13,17,25,25}, {13,17,25,25}, {13,17,25,25},
  {13,17,25,25}, {13,17,25,25}, {13,17,25,25}, {13,17,25,25},
};



static void loopLuma(u_int8 *destCol, int dir, abIdx_s *abIdxCurr,
                     abIdx_s *abIdx, int edgeDir, int *strTab, int n);

static void loopLumaIntraMbEdge(u_int8 *dest, int dir, int alphaIdx,
                                int betaIdx, int edgeDir);

static void loopChroma(u_int8 *destUcol, int dir, abIdx_s *abIdxCurr,
                       abIdx_s *abIdx, int edgeDir, int *strTab,
                       u_int8 *destVcol, int n);

static void loopChromaIntraMbEdge(u_int8 *dest, int dir, int alphaIdx,
                                  int betaIdx, int edgeDir, u_int8 *dest2);


/*
 *
 * loopLuma:
 *
 * Parameters:
 *      destCol               Pointer to first edge to be filtered
 *      dir                   Filter direction (horiz/vert)
 *      abIdxCurr             Initial alpha and beta indices
 *      abIdx                 Rest of the alpha and beta indices
 *      edgeDir               Edge direction (horiz/vert)
 *      strTab                Strength values
 *      n                     Number of columns/rows to be filtered
 *
 * Function:
 *      Filter MB block edges.
 *
 * Returns:
 *      -
 *
 */
static void loopLuma(u_int8 *destCol, int dir, abIdx_s *abIdxCurr,
                     abIdx_s *abIdx, int edgeDir, int *strTab, int n)
{
  int blk, i;
  int alphaIdx, betaIdx, alpha, beta, str;
  int delta;
  int diff, c0, c;
  int orig[2*BLK_SIZE];
  u_int8 *dest;

  for (; n > 0; n--, destCol+=BLK_SIZE*dir) {

    alphaIdx = abIdxCurr->alphaIdx;
    betaIdx = abIdxCurr->betaIdx;

    alpha = alphaTab[12+alphaIdx];
    beta = betaTab[12+betaIdx];

    abIdxCurr = abIdx;

    dest = destCol;

    for (blk = 0; blk < BLK_PER_MB; blk++) {

      str = *strTab++;

      if (str == 0) {
        dest += BLK_SIZE*edgeDir;
      }
      else {
        c0 = clipTab[12+alphaIdx][str-1];

        for (i = 0; i < BLK_SIZE; i++, dest+=edgeDir) {

          orig[2] = dest[-2*dir];
          orig[3] = dest[  -dir];
          orig[4] = dest[     0];
          orig[5] = dest[   dir];

          /* The step across the block boundaries */
          delta = abs(orig[3]-orig[4]);
          
          /* Find right activity parameter dr and left activity parameter dl */
          if (delta < alpha && abs(orig[4]-orig[5]) < beta &&
                               abs(orig[3]-orig[2]) < beta)
          {
            c = c0;

            orig[1] = dest[-3*dir];
            orig[6] = dest[ 2*dir];

            if (abs(orig[3]-orig[1]) < beta) {
              diff = ((2*orig[1] + orig[3] + orig[4] + 1) >> 2) - orig[2];
              diff = clip(-c0, c0, diff);
              dest[-2*dir] = (u_int8)(orig[2]+diff);
              c++;
            }
            if (abs(orig[4]-orig[6]) < beta) {
              diff = ((2*orig[6] + orig[3] + orig[4] + 1) >> 2) - orig[5];
              diff = clip(-c0, c0, diff);
              dest[dir] = (u_int8)(orig[5]+diff);
              c++;
            }

            diff = (4*(orig[4] - orig[3]) + orig[2] - orig[5] + 4) >> 3;
            diff = clip(-c, c, diff);
            dest[-dir] = (u_int8)clip(0, 255, orig[3]+diff);
            dest[   0] = (u_int8)clip(0, 255, orig[4]-diff);
          }
        }
      }
    }
  }
}


/*
 *
 * loopLumaIntraMbEdge:
 *
 * Parameters:
 *      dest                  Pixels to be filtered
 *      dir                   Filter direction (horiz/vert)
 *      edgeDir               Edge direction (horiz/vert)
 *      alphaIdx              Filter alpha index
 *      betaIdx               Filter beta index
 *
 * Function:
 *      Filter intra MB edge.
 *
 * Returns:
 *      -
 *
 */
static void loopLumaIntraMbEdge(u_int8 *dest, int dir, int alphaIdx,
                                int betaIdx, int edgeDir)
{
  int i;
  int alpha, beta;
  int delta;
  int orig[2*BLK_SIZE];
  int tmpSum;

  alpha = alphaTab[12+alphaIdx];
  beta = betaTab[12+betaIdx];

  for (i = 0; i < MBK_SIZE; i++, dest+=edgeDir) {

    orig[2] = dest[-2*dir];
    orig[3] = dest[  -dir];
    orig[4] = dest[     0];
    orig[5] = dest[   dir];

    /* The step across the block boundaries */
    delta = abs(orig[3]-orig[4]);
    
    /* Find right activity parameter dr and left activity parameter dl */
    if (delta < alpha && abs(orig[4]-orig[5]) < beta &&
                         abs(orig[3]-orig[2]) < beta)
    {
      if (delta >= ((alpha>>2) + 2)) {
        dest[  -dir] = (u_int8)((orig[3] + orig[5] + 2*orig[2] + 2) >> 2);
        dest[     0] = (u_int8)((orig[2] + orig[4] + 2*orig[5] + 2) >> 2);
      }
      else {
        orig[1] = dest[-3*dir];
        orig[6] = dest[ 2*dir];

        if (abs(orig[3]-orig[1]) < beta) {
          tmpSum = orig[2] + orig[3] + orig[4] + 2;
          dest[  -dir] = (u_int8)((orig[1] + 2*tmpSum + orig[5]) >> 3);
          dest[-2*dir] = (u_int8)((orig[1] + tmpSum) >> 2);
          dest[-3*dir] = (u_int8)((2*dest[-4*dir] + 3*orig[1] + tmpSum + 2) >> 3);
        }
        else
          dest[  -dir] = (u_int8)((orig[3] + orig[5] + 2*orig[2] + 2) >> 2);

        if (abs(orig[4]-orig[6]) < beta) {
          tmpSum = orig[3] + orig[4] + orig[5] + 2;
          dest[     0] = (u_int8)((orig[2] + 2*tmpSum + orig[6]) >> 3);
          dest[   dir] = (u_int8)((tmpSum + orig[6]) >> 2);
          dest[ 2*dir] = (u_int8)((2*dest[ 3*dir] + 3*orig[6] + tmpSum + 2) >> 3);
        }
        else
          dest[     0] = (u_int8)((orig[2] + orig[4] + 2*orig[5] + 2) >> 2);
      }
    }
  }
}


/*
 *
 * loopChroma:
 *
 * Parameters:
 *      destUcol              Pointer to first edge to be filtered (U)
 *      dir                   Filter direction (horiz/vert)
 *      abIdxCurr             Initial alpha and beta indices
 *      abIdx                 Rest of the alpha and beta indices
 *      edgeDir               Edge direction (horiz/vert)
 *      strTab                Strength values
 *      destVcol              Pointer to first edge to be filtered (V)
 *      n                     Number of columns/rows to be filtered
 *
 * Function:
 *      Filter MB block edges.
 *
 * Returns:
 *      -
 *
 */
static void loopChroma(u_int8 *destUcol, int dir, abIdx_s *abIdxCurr,
                       abIdx_s *abIdx, int edgeDir, int *strTab,
                       u_int8 *destVcol, int n)
{
  int blk, i;
  int alphaIdx, betaIdx, alpha, beta, str;
  int delta;
  int diff, c;
  int orig[2*BLK_SIZE];
  u_int8 *destU, *destV;
  u_int8 *dest;

  for (; n > 0; n--, strTab+=BLK_PER_MB, destUcol+=2*BLK_SIZE/2*dir,
                                         destVcol+=2*BLK_SIZE/2*dir)
  {

    alphaIdx = abIdxCurr->alphaIdxC;
    betaIdx = abIdxCurr->betaIdxC;

    alpha = alphaTab[12+alphaIdx];
    beta = betaTab[12+betaIdx];

    abIdxCurr = abIdx;

    destU = destUcol;
    destV = destVcol;

    for (blk = 0; blk < BLK_PER_MB; blk++, destU+=(BLK_SIZE/2)*edgeDir,
                                           destV+=(BLK_SIZE/2)*edgeDir)
    {

      str = *strTab++;

      if (str > 0) {

        c = clipTab[12+alphaIdx][str-1] + 1;

        dest = destU;

        for (i = 0; i < BLK_SIZE; i++, dest+=edgeDir) {

          if (i == 2) dest = destV;

          orig[2] = dest[-2*dir];
          orig[3] = dest[  -dir];
          orig[4] = dest[     0];
          orig[5] = dest[   dir];

          /* The step across the block boundaries */
          delta = abs(orig[3]-orig[4]);
          
          /* Find right activity parameter dr and left activity parameter dl */
          if (delta < alpha && abs(orig[4]-orig[5]) < beta &&
                               abs(orig[3]-orig[2]) < beta)
          {
            diff = (4*(orig[4] - orig[3]) + orig[2] - orig[5] + 4) >> 3;
            diff = clip(-c, c, diff);
            dest[-dir] = (u_int8)clip(0, 255, orig[3]+diff);
            dest[   0] = (u_int8)clip(0, 255, orig[4]-diff);
          }
        }
      }
    }
  }
}


/*
 *
 * loopChromaIntraMbEdge:
 *
 * Parameters:
 *      dest                  Pixels to be filtered (U)
 *      dir                   Filter direction (horiz/vert)
 *      alphaIdx              Filter alpha index
 *      betaIdx               Filter beta index
 *      edgeDir               Edge direction (horiz/vert)
 *      dest2                 Pixels to be filtered (V)
 *
 * Function:
 *      Filter intra MB edge.
 *
 * Returns:
 *      -
 *
 */
static void loopChromaIntraMbEdge(u_int8 *dest, int dir, int alphaIdx,
                                  int betaIdx, int edgeDir, u_int8 *dest2)
{
  int i;
  int alpha, beta;
  int delta;
  int orig[2*BLK_SIZE];

  alpha = alphaTab[12+alphaIdx];
  beta = betaTab[12+betaIdx];

  for (i = 0; i < 2*(MBK_SIZE/2); i++, dest+=edgeDir) {

    // Change V chroma component at half way
    if (i == MBK_SIZE/2) dest = dest2;

    orig[2] = dest[-2*dir];
    orig[3] = dest[  -dir];
    orig[4] = dest[     0];
    orig[5] = dest[   dir];

    /* The step across the block boundaries */
    delta = abs(orig[3]-orig[4]);
    
    /* Find right activity parameter dr and left activity parameter dl */
    if (delta < alpha && abs(orig[4]-orig[5]) < beta &&
                         abs(orig[3]-orig[2]) < beta)
    {
      dest[  -dir] = (u_int8)((orig[3] + orig[5] + 2*orig[2] + 2) >> 2);
      dest[     0] = (u_int8)((orig[2] + orig[4] + 2*orig[5] + 2) >> 2);
    }
  }
}


/*
 *
 * filFilterMB:
 *
 * Parameters:
 *      recoBuf               Frame buffer for reconstruction 
 *      mbData                Table of MB attributes
 *      picWidth              Frame width in pixels
 *      chromaQpIdx           Chroma QP index relative to luma QP
 *      alphaOffs             Filter alpha offset
 *      betaOffs              Filter beta offset
 *      mbX                   Macroblocks horizontal position
 *      mbY                   Macroblocks vertical position
 *
 * Function:
 *      Apply loopfilter on macroblock.
 *
 * Returns:
 *      -
 *
 */
void filFilterMB(frmBuf_s *recoBuf, mbAttributes_s *mbData, 
                 int chromaQpIdx, int mbX, int mbY)
{
  int mbsPerLine, mbAddr;
  int mbAvailableLeft, mbAvailableUp;
  int bx, by;
  int edgeStrH[BLK_PER_MB][BLK_PER_MB];
  int edgeStrV[BLK_PER_MB][BLK_PER_MB];
  unsigned int cbp;
  u_int8 *recoY, *recoU, *recoV;
  int qp, qpC;
  int edge_qp, edge_qpC;
  int filterMode;
  int alphaOffs;
  int betaOffs;
  int picWidth, picWidthC;
  mbState_s *pMbState, *pMbStateLeft, *pMbStateTop;
  blkState_s (*pBlkState)[BLK_PER_MB];
  blkState_s (*pBlkStateLeft)[BLK_PER_MB];
  blkState_s *pBlkStateTop;
  int strongFilterH, strongFilterV;
  abIdx_s abIdx, abIdxMbEdge;
  abIdx_s *currAbIdx;

  picWidth = recoBuf->width;
  mbsPerLine = picWidth/MBK_SIZE;
  mbAddr = mbY*mbsPerLine+mbX;

  pMbState     = mbData->mbStateArr + mbAddr;
  pMbStateLeft = pMbState - 1;
  pMbStateTop  = pMbState - mbsPerLine;

  filterMode = pMbState->filterMode;
  alphaOffs  = pMbState->alphaOffset;
  betaOffs   = pMbState->betaOffset;
  qp         = pMbState->qp;

  qpC = qpChroma[clip(MIN_QP, MAX_QP, qp + chromaQpIdx)];

  if (filterMode == 1)  /* filterMode 1: loopfilter disabled */
    return;

  /* filterMode 0: filter all edges, filterMode 2: don't filter slice edges */
  mbAvailableLeft = mbX > 0 && (filterMode == 0 || pMbState->sliceMap == pMbStateLeft->sliceMap);
  mbAvailableUp   = mbY > 0 && (filterMode == 0 || pMbState->sliceMap == pMbStateTop->sliceMap);

  /*
   * Initialize horizontal and vertical boundary strength values
   */

  /* If INTRA MB, stregths are 4 and 3 */
  if (pMbState->mbType <= MB_TYPE_INTRA_16x16) {
    for (by = 0; by < BLK_PER_MB; by++) {
      edgeStrH[1][by] = edgeStrV[1][by] = 3;
      edgeStrH[2][by] = edgeStrV[2][by] = 3;
      edgeStrH[3][by] = edgeStrV[3][by] = 3;
    }
    strongFilterH = strongFilterV = 1;
  }
  else {

    pBlkState = pMbState->blkInfo;

    /* Init. horizontal boundary strengths at the MB edge */
    if (mbAvailableLeft) {
      if (pMbStateLeft->mbType <= MB_TYPE_INTRA_16x16) {
        strongFilterH = 1;
      }
      else {
        /* To see if at least 1 of 2 blocks at left MB edge are non-zero */
        cbp = (pMbStateLeft->cbp >> 3) | pMbState->cbp;
        pBlkStateLeft = (blkState_s (*)[BLK_PER_MB]) &pMbStateLeft->blkInfo[0][BLK_PER_MB-1];
        for (by = 0; by < BLK_PER_MB; by++, cbp>>=4) {
          if (cbp & 1)
            edgeStrH[0][by] = 2;
          else
            edgeStrH[0][by] =
              (pBlkStateLeft[by][0].ref != pBlkState[by][0].ref) ||
              ((abs(pBlkStateLeft[by][0].mv.x - pBlkState[by][0].mv.x) |
                abs(pBlkStateLeft[by][0].mv.y - pBlkState[by][0].mv.y)) >= 4) ? 1 : 0;
        }
        strongFilterH = 0;
      }
    }

    /* Init. vertical boundary strengths at the MB edge */
    if (mbAvailableUp) {
      if (pMbStateTop->mbType <= MB_TYPE_INTRA_16x16) {
        strongFilterV = 1;
      }
      else {
        /* To see if at least 1 of 2 blocks at top MB edge are non-zero */
        cbp = (pMbStateTop->cbp >> 12) | pMbState->cbp;
        pBlkStateTop = pMbStateTop->blkInfo[BLK_PER_MB-1];
        for (bx = 0; bx < BLK_PER_MB; bx++, cbp>>=1) {
          if (cbp & 1)
            edgeStrV[0][bx] = 2;
          else
            edgeStrV[0][bx] =
              (pBlkStateTop[bx].ref != pBlkState[0][bx].ref) ||
              ((abs(pBlkStateTop[bx].mv.x - pBlkState[0][bx].mv.x) |
                abs(pBlkStateTop[bx].mv.y - pBlkState[0][bx].mv.y)) >= 4) ? 1 : 0;
        }
        strongFilterV = 0;
      }
    }

    /* Init. horizontal block boundary strengths */

    /* To see if at least 1 of 2 blocks at inner block V edge are non-zero */
    cbp = (pMbState->cbp >> 1) | pMbState->cbp;
    for (by = 0; by < BLK_PER_MB; by++, cbp>>=1) {
      for (bx = 1; bx < BLK_PER_MB; bx++, cbp>>=1) {
        if (cbp & 1)
          edgeStrH[bx][by] = 2;
        else
          edgeStrH[bx][by] =
            (pBlkState[by][bx-1].ref != pBlkState[by][bx].ref) ||
            ((abs(pBlkState[by][bx-1].mv.x - pBlkState[by][bx].mv.x) |
              abs(pBlkState[by][bx-1].mv.y - pBlkState[by][bx].mv.y)) >= 4) ? 1 : 0;
      }
    }

    /* Init. vertical block boundary strengths */

    /* To see if at least 1 of 2 blocks at inner block V edge are non-zero */
    cbp = (pMbState->cbp >> 4) | pMbState->cbp;
    for (by = 1; by < BLK_PER_MB; by++) {
      for (bx = 0; bx < BLK_PER_MB; bx++, cbp>>=1) {
        if (cbp & 1)
          edgeStrV[by][bx] = 2;
        else
          edgeStrV[by][bx] = 
            (pBlkState[by-1][bx].ref != pBlkState[by][bx].ref) ||
            ((abs(pBlkState[by-1][bx].mv.x - pBlkState[by][bx].mv.x) |
              abs(pBlkState[by-1][bx].mv.y - pBlkState[by][bx].mv.y)) >= 4) ? 1 : 0;
      }
    }
 
  } /* End else (MB == INTRA) */


  picWidthC = picWidth>>1;    /* picWidth/2 */

  recoY = recoBuf->y + mbY*MBK_SIZE    *picWidth  + mbX*MBK_SIZE;
  recoU = recoBuf->u + mbY*(MBK_SIZE/2)*picWidthC + mbX*(MBK_SIZE/2);
  recoV = recoBuf->v + mbY*(MBK_SIZE/2)*picWidthC + mbX*(MBK_SIZE/2);

  abIdx.alphaIdx = qp + alphaOffs;
  abIdx.betaIdx  = qp + betaOffs;
  abIdx.alphaIdxC = qpC + alphaOffs;
  abIdx.betaIdxC  = qpC + betaOffs;


  /*
   * Initialize qp, alpha index and beta index for horizontal MB edge
   * and filter the MB edge
   */
  if (mbAvailableLeft) {
    if (qp != pMbStateLeft->qp) {
      edge_qp  = (qp + pMbStateLeft->qp + 1) >> 1;
      edge_qpC = (qpC + qpChroma[clip(MIN_QP, MAX_QP, pMbStateLeft->qp+chromaQpIdx)] + 1) >> 1;

      abIdxMbEdge.alphaIdx = edge_qp + alphaOffs;
      abIdxMbEdge.betaIdx  = edge_qp + betaOffs;
      abIdxMbEdge.alphaIdxC = edge_qpC + alphaOffs;
      abIdxMbEdge.betaIdxC  = edge_qpC + betaOffs;

      currAbIdx = &abIdxMbEdge;
    }
    else
      currAbIdx = &abIdx;

    if (strongFilterH) {
      loopLumaIntraMbEdge(recoY, 1, currAbIdx->alphaIdx, currAbIdx->betaIdx, picWidth);
      loopChromaIntraMbEdge(recoU, 1, currAbIdx->alphaIdxC, currAbIdx->betaIdxC, picWidthC, recoV);
      currAbIdx = &abIdx;
      bx = 1;
    }
    else
      bx = 0;
  }
  else {
    currAbIdx = &abIdx;
    bx = 1;
  }

  /* Filter block edges */
  loopLuma(recoY + bx*BLK_SIZE, 1, currAbIdx,
           &abIdx, picWidth, &edgeStrH[bx][0], BLK_PER_MB-bx);

  loopChroma(recoU + bx*(2*BLK_SIZE/2), 1, currAbIdx, &abIdx, picWidthC,
             &edgeStrH[2*bx][0], recoV + bx*(2*BLK_SIZE/2), (BLK_PER_MB-bx)>>1);


  /*
   * Initialize qp, alpha index and beta index for vertical MB edge
   * and filter intra MB edge
   */
  if (mbAvailableUp) {
    if (qp != pMbStateTop->qp) {
      edge_qp = (qp + pMbStateTop->qp + 1) >> 1;
      edge_qpC = (qpC + qpChroma[clip(MIN_QP, MAX_QP, pMbStateTop->qp+chromaQpIdx)] + 1) >> 1;

      abIdxMbEdge.alphaIdx = edge_qp + alphaOffs;
      abIdxMbEdge.betaIdx  = edge_qp + betaOffs;
      abIdxMbEdge.alphaIdxC = edge_qpC + alphaOffs;
      abIdxMbEdge.betaIdxC  = edge_qpC + betaOffs;

      currAbIdx = &abIdxMbEdge;
    }
    else
      currAbIdx = &abIdx;

    /* Filter intra MB edge in vertical direction */
    if (strongFilterV) {
      loopLumaIntraMbEdge(recoY, picWidth, currAbIdx->alphaIdx, currAbIdx->betaIdx, 1);
      loopChromaIntraMbEdge(recoU, picWidthC, currAbIdx->alphaIdxC, currAbIdx->betaIdxC, 1, recoV);
      currAbIdx = &abIdx;
      by = 1;
    }
    else
      by = 0;
  }
  else {
    currAbIdx = &abIdx;
    by = 1;
  }

  /* Filter block edges */
  loopLuma(recoY + by*BLK_SIZE*picWidth, picWidth, currAbIdx,
           &abIdx, 1, &edgeStrV[by][0], BLK_PER_MB-by);

  loopChroma(recoU + by*(2*BLK_SIZE/2)*picWidthC, picWidthC, currAbIdx,
             &abIdx, 1, &edgeStrV[2*by][0], recoV + by*(2*BLK_SIZE/2)*picWidthC,
             (BLK_PER_MB-by)>>1);
}


/*
 *
 * filFilterMB:
 *
 * Parameters:
 *      recoBuf               Frame buffer for reconstruction 
 *      mbData                Tables of MB attributes
 *      chromaQpIdx           Chroma QP index relative to luma QP
 *      alphaOffs             Filter alpha offset
 *      betaOffs              Filter beta offset
 *
 * Function:
 *      Apply loopfilter on frame buffer.
 *
 * Returns:
 *      -
 *
 */
void filFilterFrame(frmBuf_s *recoBuf, mbAttributes_s *mbData, 
                    int chromaQpIdx)
{
  int i, j;

  for (j = 0; j < recoBuf->height/MBK_SIZE; j++) {
    for (i = 0; i < recoBuf->width/MBK_SIZE; i++) {
      filFilterMB(recoBuf, mbData, chromaQpIdx, i, j);
    }
  }
}
