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
 * modedecision.c
 *
 * Contains:
 *    Select the best modes for the optimal coding performance. Different
 *    algorithms are used depending on the user input. 
 *
 */


#include <limits.h>
#include "globals.h"
#include "debug.h"
#include "bitbuffer.h"
#include "macroblock.h"
#include "motest.h"
#include "motcomp.h"
#include "prederrorcod.h"
#include "prederrordec.h"
#include "vlcutility.h"
#include "stream.h"
#include "meutility.h"
#include "transform.h"
#include "intrapred.h"
#include "modedecision.h"


/*
 * mdBestIntraLuma16x16Plain
 *
 * Parameters:
 *      pMb                   Macroblock information
 *      orig                  Original pixels
 *      predBlk               Storage all 16x16 mode predictions
 *      modeAvail             Which modes are available
 *      bestMbSad             Best MB SAD so far
 *
 * Function:
 *      Build 16x16 predictions and choose the best mode for the macroblock.
 *      The decision is made based on SAD after Hadamard transform.
 *
 * Returns:
 *      SAD for the best 16x16 intra prediction mode.
 *      Best intra16x16 mode is also set in this function.
 */
static int32
mdBestIntraLuma16x16Plain(macroblock_s *pMb, 
                          u_int8 orig[MBK_SIZE][MBK_SIZE],
                          u_int8 predBlk[IPR_NUM_MODES2][MBK_SIZE][MBK_SIZE],
                          int    modeAvail[IPR_NUM_MODES2],
                          int    hadamard,
                          int32  bestMbSad)
{
  int mode;
  int32 currentCost;
  int bestMode;
  int32 bestCost;
  int exitFlag;
  int i, j;
  int16 dcCoeffs[4][4];


  bestMode = -1;
  bestCost = MAX_COST;

  for (mode = 0; mode < IPR_NUM_MODES2; mode ++) {

    if (modeAvail[mode]) {

      currentCost = 0;
      exitFlag = 0;

      for (j = 0; (j < MBK_SIZE) && (! exitFlag); j += 4) {
        for (i = 0; (i < MBK_SIZE) && (! exitFlag); i += 4) {
          if (hadamard) {
            int dc;
            currentCost += traDiffSATD4x4RetDc(
              (u_int8 (*)[MBK_SIZE]) &orig[j][i],
              (u_int8 (*)[MBK_SIZE]) &predBlk[mode][j][i],
              &dc);
            dcCoeffs[j >> 2][i >> 2] = (int16)dc;
          }
          else
            currentCost += traDiffSAD4x4(
            (u_int8 (*)[MBK_SIZE]) &orig[j][i],
            (u_int8 (*)[MBK_SIZE]) &predBlk[mode][j][i]);

          // perform early termination
          exitFlag = ((currentCost >> 1) >= bestMbSad);
        }
      }

      if (! exitFlag)
      {

        // compare with best mode, only if early termination has not happened
        if (hadamard) {
          currentCost += traHadamard4x4(dcCoeffs) >> 2;
          currentCost >>= 1;
        }

        if (currentCost < bestCost ) {
          bestCost  = currentCost;
          bestMode = mode;
        }
      }
    }

  }
  pMb->intra16x16mode = bestMode;

  return bestCost;
}


// LOW_COMPLEX_PROF3
static int32
mdBestIntraLuma16x16Plain_fast(macroblock_s *pMb, 
                          u_int8 orig[MBK_SIZE][MBK_SIZE],
                          u_int8 predBlk[IPR_NUM_MODES2][MBK_SIZE][MBK_SIZE],
                          int    modeAvail[IPR_NUM_MODES2],
                          int    hadamard,
                          int32  bestMbSad)
{
  int mode;
  int32 currentCost;
  int bestMode;
  int32 bestCost;
  int exitFlag;
  int i, j;
  int16 dcCoeffs[4][4];

  int32 currentCost_thre = MAX_COST;

  bestMode = -1;
  bestCost = MAX_COST;

  for (mode = 0; mode < (IPR_NUM_MODES2-1); mode ++) {
    if (modeAvail[mode]) {

      currentCost = 0;
      exitFlag = 0;

      for (j = 0; (j < MBK_SIZE) && (! exitFlag); j += 4) {
        for (i = 0; (i < MBK_SIZE) && (! exitFlag); i += 4) {
          if (hadamard) {
            int dc;
            currentCost += traDiffSATD4x4RetDc(
              (u_int8 (*)[MBK_SIZE]) &orig[j][i],
              (u_int8 (*)[MBK_SIZE]) &predBlk[mode][j][i],
              &dc);
            dcCoeffs[j >> 2][i >> 2] = (int16)dc;
          }
          else
            currentCost += traDiffSAD4x4(
            (u_int8 (*)[MBK_SIZE]) &orig[j][i],
            (u_int8 (*)[MBK_SIZE]) &predBlk[mode][j][i]);

          // perform early termination
          exitFlag = (  ((currentCost >> 1) >= bestMbSad) ||
                          (currentCost>currentCost_thre)  );

        }
      }

      if (! exitFlag)
      {
        if (currentCost < currentCost_thre )
          currentCost_thre=currentCost;

        // compare with best mode, only if early termination has not happened
        if (hadamard) {
          currentCost += traHadamard4x4(dcCoeffs) >> 2;
          currentCost >>= 1;
        }

        if (currentCost < bestCost ) {
          bestCost  = currentCost;
          bestMode = mode;
        }
      }
    }
  }
  pMb->intra16x16mode = bestMode;

  return bestCost;
}


/*
 * mdIntraPredLuma16x16:
 *
 * Parameters:
 *      pMb                   Macroblock coding object
 *      picWidth              Horizontal size of the frame
 *      picType               Type of the frame (intra/inter)
 *      bestMbSad             Best MB sad so far
 *      modeDecision          How mode decision should be performed
 *      intra16x16Cost          Cost for the intra4x4 prediction
 *      low_complex_prof3     low complexity profile 3
 *
 * Function:
 *      Build 16x16 predictions and choose the best mode.
 *
 * Returns:
 *      -
 */
void mdIntraPredLuma16x16(macroblock_s  *pMb, 
                          int           picWidth,
                          int           picType,
                          int32         bestMbSad,
                          int           modeDecision,
                          costMeasure_s *intra16x16Cost,
                          int           low_complex_prof3)
{
  int modeAvail[IPR_NUM_MODES2];


  if (low_complex_prof3)
    iprGetPredLuma16x16_fast
      (pMb->predBlk2, modeAvail, pMb->recoY, picWidth, pMb->mbAvailMapIntra);
  else
    iprGetPredLuma16x16
      (pMb->predBlk2, modeAvail, pMb->recoY, picWidth, pMb->mbAvailMapIntra);

  // calculate the MSE of intra16x16 and intra4x4
#ifndef DISABLE_RDO
  if ((modeDecision & 0x0F) == MODE_DECISION_RDO)
  {
    int mode, bestMode, startMode, stopMode;
    costMeasure_s current;
    statSlice_s testStat;      // dummy

    pMb->type      = MBK_INTRA;
    pMb->intraType = MBK_INTRA_TYPE2;

    if ((modeDecision & RDO_INTRA_LUMA_16x16) == 0) {
      // always try to find the best 16x16 prediction
      if (low_complex_prof3)
        intra16x16Cost->sad = mdBestIntraLuma16x16Plain_fast(pMb, 
          pMb->origY, pMb->predBlk2, modeAvail, 1, MAX_COST);
      else
        intra16x16Cost->sad = mdBestIntraLuma16x16Plain(pMb, 
          pMb->origY, pMb->predBlk2, modeAvail, 1, MAX_COST);

      // only check the best mode just found, to evaluate the RD
      startMode = pMb->intra16x16mode;
      stopMode  = pMb->intra16x16mode;
    }
    else
    {
      startMode = 0;
      stopMode = IPR_NUM_MODES2 - 1;
    }

    // consider the best intra16x16 mode in the context of the entire MB
    // more accurate, but overhead of encoding chroma repeatedly
    bestMode = IPR_MODE2_DC;
    for (mode = startMode; mode <= stopMode; mode ++) {
      if (modeAvail[mode]) {
        pMb->intra16x16mode = mode;

        pecCodeLumaMB(pMb, pMb->predBlk2[mode], 1, picType);
        pedRecoLumaMB(pMb, pMb->predBlk2[mode], 1, picWidth);

        pMb->intra16x16CbpY = pMb->cbpY;

        current.mse = 
          CalculateSsd(& pMb->origY[0][0], 16, pMb->recoY, picWidth, 16, 16);

        // perform test encoding to get the actual rate
        bibInit(& pMb->mbBs);

        // suppose the macroblock type is intra-16x16
        current.bits = streamSendLumaCoeffs(& pMb->mbBs,
          pMb, & testStat);

        current.cost = current.mse + pMb->rdoLambda * current.bits;
        current.sad = 0;
        current.edgeMse = 0;

        if (current.cost < intra16x16Cost->cost)
        {
          bestMode = mode;
          *intra16x16Cost = current;
        }
      }
    }

    pMb->intra16x16mode = bestMode;
  }
  else
#endif
  {
    int mbType;

    // early termination will be applied
    if (low_complex_prof3)
      intra16x16Cost->sad = mdBestIntraLuma16x16Plain_fast(pMb, 
        pMb->origY, pMb->predBlk2, modeAvail, (modeDecision & 0xf) != MODE_DECISION_SIMPLE, bestMbSad);
    else
      intra16x16Cost->sad = mdBestIntraLuma16x16Plain(pMb, 
        pMb->origY, pMb->predBlk2, modeAvail, (modeDecision & 0xf) != MODE_DECISION_SIMPLE, bestMbSad);

    // at least these many bits will be used for mbType, all CBPs are set to 0
    mbType = ((IS_SLICE_P(picType)) ? 5 : 0) + streamGetMbTypeIntra
      (MBK_INTRA_TYPE2, pMb->intra16x16mode, 0, 0, 0);

    pMb->actualIntra16x16Sad = intra16x16Cost->sad;
    intra16x16Cost->sad += (int32)pMb->lambda * uvlcBitsUnsigned[mbType];
    intra16x16Cost->cost = intra16x16Cost->sad;
  }
}


/*
 * encoRecoBlock
 *
 * Parameters:
 *      origBlk               Original pixels
 *      predBlk               Prediction block
 *      coeff                 Quantized coefficients
 *      reco                  Which modes are available
 *      recoWidth             Horizontal size reconstructed buffer
 *      picType               Type of the frame (intra/inter)
 *      qp                    Macroblock qp
 *
 * Function:
 *      Perform forward and backward transform/quantization on a 4x4 block.
 *      The reconstructed pixels are put in buffer "reco".
 *
 * Returns:
 *      SAD for the best 16x16 intra prediction mode.
 *      Best intra16x16 mode is also set in this function.
 */
int encoRecoBlock(u_int8 origBlk[][MBK_SIZE], 
                  u_int8 predBlk[][MBK_SIZE], 
                  int    coeff[BLK_SIZE][BLK_SIZE],
                  u_int8 *reco,
                  int    recoWidth, 
                  int    picType,
                  int    qp)
{
  int nonZero;

  /* Code block */
  nonZero = pecCodeBlock(origBlk, predBlk, coeff, 0, qp, picType);

  /* If there were non-zero coefficients, decode block */
  if (nonZero > 0) {
    // this function is never used in intra16x16 mode, so there is no DC
    pedRecoBlock(predBlk, coeff, reco, recoWidth, 0 /* no DC */, 0, qp);
  }
  /* Otherwise, just copy prediction */
  else
  {
#ifdef COPY_4_BYTES_AS_32_BITS
    * (u_int32 *) & reco[recoWidth * 0] = *(u_int32 *) & predBlk[0][0];
    * (u_int32 *) & reco[recoWidth * 1] = *(u_int32 *) & predBlk[1][0];
    * (u_int32 *) & reco[recoWidth * 2] = *(u_int32 *) & predBlk[2][0];
    * (u_int32 *) & reco[recoWidth * 3] = *(u_int32 *) & predBlk[3][0];
#else
    int i;
    for (i = 0; i < BLK_SIZE; i++) {
      reco[recoWidth * i + 0] = predBlk[i][0];
      reco[recoWidth * i + 1] = predBlk[i][1];
      reco[recoWidth * i + 2] = predBlk[i][2];
      reco[recoWidth * i + 3] = predBlk[i][3];
    }
#endif
  }

  return nonZero;
}


/*
 * mdIntraPredLuma4x4:
 *
 * Parameters:
 *      pMb                   Macroblock coding object
 *      picWidth              Horizontal size of the frame
 *      picType               Type of the frame (intra/inter)
 *      bestMbSad             Best MB sad so far
 *      modeDecision          How mode decision should be performed
 *      intra4x4Cost          Cost for the intra4x4 prediction
 *      low_complex_prof3     low complexity prof 3
 *
 * Function:
 *      Build 4x4 predictions and choose the best mode for each block.
 *
 * Returns:
 *      SAD for the best 4x4 intra prediction modes, if RDO is not enabled,
 *      otherwise, RDO cost of encoding luma is returned.
 *      pMb->cbpY is also modified in the function.
 */
int32 mdIntraPredLuma4x4(macroblock_s   *pMb, 
                         int            picWidth, 
                         int            picType, 
                         int32          bestMbSad, 
                         int            modeDecision,
                         costMeasure_s *intra4x4Cost)
{
  u_int8 predBlk[IPR_NUM_MODES1][BLK_SIZE][MBK_SIZE];
  int modeAvail1[IPR_NUM_MODES1];
  int blk8x8, blkIdx;
  int blkCount;
  int mode;
  int bestMode;
  int nonZero, exitFlag;
  int32 searchLimit;
  int mostProbableMode;
  int mbModeBits;
  int *mbAvailMap;
  int actualBlkSad=0;
  costMeasure_s bestBlkCost, blkCost;


  pMb->cbpY = 0;
  mbAvailMap = pMb->mbAvailMapIntra;

  intra4x4Cost->mse  = 0;
  intra4x4Cost->sad  = 0;
  pMb->actualIntra4x4Sad = 0;
#ifndef DISABLE_RDO
  if (modeDecision == MODE_DECISION_RDO)
  {
    intra4x4Cost->cost = 0;
    searchLimit = MAX_COST;
  }
  else
#endif
  {
    // used for mbType, 5 bits in P-frame, 1 bit in I-frame
    intra4x4Cost->cost = pMb->lambda * (IS_SLICE_P(picType) ? 5 : 1);
    searchLimit = bestMbSad;
  }

  mbModeBits = 0;
  blkCount = 0;

  exitFlag = 0;
  if (intra4x4Cost->cost + 16 * pMb->lambda >= searchLimit)
  {
    exitFlag = 1;
    intra4x4Cost->cost += 16 * pMb->lambda;
  }


  for (blk8x8 = 0; (blk8x8 < 16) && (! exitFlag); blk8x8 += 4)
  {
    int numNonZeroBlks, nonZeroBlkFlag;
    int blk8x8ModeBits, blk8x8CoeffBits;

    numNonZeroBlks = 0;
    blk8x8CoeffBits = 0;
    blk8x8ModeBits = 0;

    for (blkIdx = blk8x8; (blkIdx < (blk8x8 + 4)) && (! exitFlag); blkIdx ++)
    {
      int upMode, leftMode, blkAddr;
      u_int8 *origBlk;
      u_int8 *recoY;
      int blk4x4BestModeBits;
      int blk4x4BestNumCoeffs;
      int blkX, blkY;

      blkX = blkRasterOrder[blkIdx] & 3;
      blkY = blkRasterOrder[blkIdx] >> 2;
      blkAddr = blkY * 4 + blkX;

      /* Get ipr modes of the two of the neighbouring blocks */
      leftMode = pMb->blkLeft[blkAddr]->i4x4Mode;
      upMode   = pMb->blkUp[blkAddr]->i4x4Mode;

      recoY = & pMb->recoY[blkY * BLK_SIZE * picWidth + blkX*BLK_SIZE];

      /* Make all possible 4x4 predictions for current block */

      iprGetPredLuma4x4(predBlk, modeAvail1, recoY, 
        picWidth, leftMode, upMode, pMb->i4x4CornersAvail[blkY][blkX]);


      // at least one is IPR_MODE_NA
      if ((upMode + leftMode) >=  IPR_MODE_NA)
        mostProbableMode = IPR_MODE_DC;
      else
        mostProbableMode = min(upMode, leftMode);

      bestMode = 0;
      blk4x4BestModeBits = 0;
      blk4x4BestNumCoeffs = 0;

      origBlk = & pMb->origY[blkY * BLK_SIZE][blkX * BLK_SIZE];

      nonZeroBlkFlag = 0;
      bestBlkCost = initCostMeasure;
      blkCost     = initCostMeasure;

      /* Choose the best mode for the current block */
      
      for (mode = 0; mode < IPR_NUM_MODES1; mode++) {
        
        if (modeAvail1[mode]) {
          int numCoefs;

          blkCost.sad = pMb->lambda * (mode == mostProbableMode ? 1 : 4);

          if (modeDecision == MODE_DECISION_HADAMARD)
            blkCost.sad += traDiffSATD4x4(
            (u_int8 (*)[MBK_SIZE]) origBlk,
            (u_int8 (*)[MBK_SIZE]) predBlk[mode]) >> 1;
          else
            blkCost.sad += traDiffSAD4x4(
            (u_int8 (*)[MBK_SIZE]) origBlk,
            (u_int8 (*)[MBK_SIZE]) predBlk[mode]);

          nonZero  = 1;
          numCoefs = 0;

          /* Compute total SAD for the current mode by adding the start */
          /* 'handicap' and the computed SAD                            */
#ifndef DISABLE_RDO
          if (modeDecision == MODE_DECISION_RDO)
          {
            nonZero = encoRecoBlock((u_int8 (*)[MBK_SIZE]) origBlk, predBlk[mode], 
              pMb->coefY[blkIdx], recoY, picWidth, picType, pMb->qp);

            /* If there were non-zero coefficients, decode block */
            // perform entropy encoding
            bibInit(& pMb->mbBs);

            blkCost.bits = streamSend4x4Blk(& pMb->mbBs,
              pMb, 1, COMP_LUMA, blkX, blkY, pMb->coefY[blkIdx], BLK_CAT_Y, & numCoefs);

            blkCost.bits += (mode == mostProbableMode) ? 1 : 4;
            blkCost.mse   = CalculateSsd
              (origBlk, MBK_SIZE, recoY, picWidth, BLK_SIZE, BLK_SIZE);

            // calculate the MSE
            blkCost.cost = blkCost.mse + pMb->rdoLambda * blkCost.bits;
          }
          else
#endif
            blkCost.cost = blkCost.sad;

          if (blkCost.cost < bestBlkCost.cost) {
            bestBlkCost   = blkCost;
            bestMode      = mode;
            blk4x4BestNumCoeffs = numCoefs;
            actualBlkSad = blkCost.sad - pMb->lambda * (mode == mostProbableMode ? 1 : 4); 
            blk4x4BestModeBits  = (mode == mostProbableMode) ? 1 : 4;

            nonZeroBlkFlag = nonZero;
          }

#ifdef DBG_STATISTICS
          countHada4 ++;
#endif
        }
      }

      // store number of coeffs of the best mode, for future prediction
      pMb->current[blkY][blkX].i4x4Mode = (int8) bestMode;
      pMb->current[blkY][blkX].numLumaCoefs = 
        (int8) blk4x4BestNumCoeffs;

      // this is the information related i4x4Mode to be stored in stream
      pMb->ipTab[blkIdx] = (int8) ((bestMode == mostProbableMode) ?
        -1 : ((bestMode < mostProbableMode) ? bestMode : bestMode - 1));

      numNonZeroBlks  += nonZeroBlkFlag;
      blk8x8CoeffBits += bestBlkCost.bits - blk4x4BestModeBits;
      blk8x8ModeBits  += blk4x4BestModeBits;
      blkCount ++;

#ifdef DBG_STATISTICS
      intraModeHist4[bestMode] ++;
#endif

      intra4x4Cost->cost += bestBlkCost.cost;
      intra4x4Cost->sad  += bestBlkCost.sad;
      intra4x4Cost->mse  += bestBlkCost.mse;
      pMb->actualIntra4x4Sad+=actualBlkSad;

      // a little bit look ahead to have earlier termination
      if ((intra4x4Cost->cost + pMb->lambda * (16 - blkCount)) >= searchLimit)
      {
        // at least this amount
        intra4x4Cost->cost += pMb->lambda * (16 - blkCount);
        exitFlag = 1;
        continue;
      }

      nonZero = encoRecoBlock((u_int8 (*)[MBK_SIZE]) origBlk, predBlk[bestMode], 
        pMb->coefY[blkIdx], recoY, picWidth, picType, pMb->qp);

      /* If there were non-zero coefficients, decode block */
      if (nonZero > 0)
        /* Update luma CBP */
        pMb->cbpY |= (unsigned int)1 << blkIdx;
    }

    mbModeBits += blk8x8ModeBits;
    if (numNonZeroBlks)
      intra4x4Cost->bits += blk8x8CoeffBits;
    else
      intra4x4Cost->bits += 2;      // do not want to be too biased
  }

  intra4x4Cost->bits += mbModeBits;

  // we re-calculate the sad here
#ifndef DISABLE_RDO
  if (modeDecision == MODE_DECISION_RDO) {
    pMb->intra4x4CbpY = pMb->cbpY;
    intra4x4Cost->cost = intra4x4Cost->mse + intra4x4Cost->bits * pMb->rdoLambda;
  }
  else
#endif
  {
    // sad is used as cost above
    intra4x4Cost->sad  = intra4x4Cost->cost;
  }

  return intra4x4Cost->cost;
}


/*
 *
 * mdIntraPredChroma:
 *
 * Parameters:
 *      pMb                   macroblock information
 *      orig                  Original pixels
 *      pred                  Return pointer for predicted pixels
 *
 * Function:
 *      Build 8x8 chroma predictions and choose the best mode for the
 *      macroblock.
 *
 * Returns:
 *      SAD of the best chroma intra mode
 *
 */
int32 mdIntraPredChroma(macroblock_s *pMb, 
                        int chromaModeAvail[IPR_CHROMA_NUM_MODES],
                        int hadamard)
{
  int bestMode;
  int32 bestCost;
  int mode;
  int32 currentCost;
  int c;
  int i, j;
  int dcCoeffs[2][2];


  /*
   * Build 8x8 intra prediction
   */
  bestMode = -1;
  bestCost  = INT_MAX;

  for (mode = 0; mode < IPR_CHROMA_NUM_MODES; mode++) {
    if (chromaModeAvail[mode]) {
      currentCost = 0;
      for (c = 0; c < MBK_SIZE; c += MBK_SIZE/2) {
        for (j = 0; j < BLK_PER_MB/2; j ++) {
          for (i = 0; i < BLK_PER_MB/2; i ++) {
            if (hadamard)
              currentCost += traDiffSATD4x4RetDc(
              (u_int8 (*)[MBK_SIZE]) &pMb->origC[j*BLK_SIZE][c + i*BLK_SIZE],
              (u_int8 (*)[MBK_SIZE]) &pMb->predIntraC[mode][j*BLK_SIZE][c + i*BLK_SIZE],
              & dcCoeffs[j][i]);
            else
              currentCost += traDiffSAD4x4(
              (u_int8 (*)[MBK_SIZE]) &pMb->origC[j*BLK_SIZE][c + i*BLK_SIZE],
              (u_int8 (*)[MBK_SIZE]) &pMb->predIntraC[mode][j*BLK_SIZE][c + i*BLK_SIZE]);
          }
        }

        if (hadamard) {
          traDCT2x2(dcCoeffs);

          // DC (>> 2), 2x2 Hadamard (<< 1) to match 4x4 Hadamard, end up (>> 1)
          currentCost += (abs(dcCoeffs[0][0]) + abs(dcCoeffs[0][1]) +
            abs(dcCoeffs[1][0]) + abs(dcCoeffs[1][1])) >> 1;
        }
      }

      if (hadamard)
        currentCost = currentCost >> 1;

      currentCost = currentCost + (int32)uvlcBitsUnsigned[mode] * pMb->lambda;
      if (currentCost < bestCost ) {
        bestCost = currentCost;
        bestMode = mode;
      }
    }
  }

  pMb->intraModeChroma = bestMode;

  return bestCost;
}

extern int8 mcpModePartWidth[5];
extern int8 mcpModePartHeight[5];

static void getChannelDistortion(macroblock_s *pMb,
                                 refFrmBuf_s  **refBufList,
                                 int32        ssd0,
                                 int          *distortion)
{
  int blkIdxX, blkIdxY;
  int shapeX, shapeY, mbPartW, mbPartH;
  int i0, j0;
  int i1, j1;
  int i2, j2;
  int k0, l0;
  int picWidth;
  int picHeight;
  int mbIdxRef;
  int mbkPerLine;
  int mbAddr;
  int32 *pDistortion;


  distortion[0] = 0;

  picWidth = refBufList[0]->picWidth;
  picHeight = refBufList[0]->picHeight;
  mbkPerLine = picWidth / MBK_SIZE;
  mbAddr = pMb->idxY * picWidth / MBK_SIZE + pMb->idxX ;

  shapeX = mcpModePartWidth[pMb->interMode];
  shapeY = mcpModePartHeight[pMb->interMode];
  mbPartW = shapeX * BLK_SIZE;
  mbPartH = shapeY * BLK_SIZE;

  // 1:    (1-p) * Dc(n-1, j)
  for (blkIdxY = 0; blkIdxY < BLK_PER_MB; blkIdxY += shapeY) {
    for (blkIdxX = 0; blkIdxX < BLK_PER_MB; blkIdxX += shapeX) {
      blkState_s *pBlkState;

      // the starting position of current block in pixel: k0, l0
      k0 = (pMb->idxX * BLK_PER_MB + blkIdxX) * BLK_SIZE;
      l0 = (pMb->idxY * BLK_PER_MB + blkIdxY) * BLK_SIZE;

      // Absolute motion vector coordinates of the macroblock
      pBlkState = & pMb->current[blkIdxY][blkIdxX];
      pDistortion = refBufList[pBlkState->ref]->channelDistortion;

      i0 = k0 * 4 + pBlkState->mv.x;
      j0 = l0 * 4 + pBlkState->mv.y;

      // the starting position of the ref block in pixel: i0, j0
      i0 = i0 / 4;
      j0 = j0 / 4;
      if (i0 < 0) i0 = 0;
      if (j0 < 0) j0 = 0;
      if (i0 >= picWidth) i0 = picWidth - 1;
      if (j0 >= picHeight) j0 = picHeight - 1;

      // calculate the distortion here:
      for (j1 = j0; j1 < j0 + mbPartH; j1++) {
        for (i1 = i0; i1 < i0 + mbPartW; i1++) {
          i2 = i1;
          j2 = j1;

          if (i2 >= picWidth) i2 = picWidth - 1;
          if (j2 >= picHeight) j2 = picHeight - 1;

          mbIdxRef  = (j2 / MBK_SIZE) * mbkPerLine + i2 / MBK_SIZE;
          distortion[0] += pDistortion[mbIdxRef];  //  / 256.0
        }
      }

    }
  }
  distortion[0] = distortion[0] >> 8; //  / 256
  distortion[0] = distortion[0] * (100-pMb->plr);

  // 2:    p * Dc(n-1, i)
  distortion[0] += refBufList[0]->channelDistortion[mbAddr] * pMb->plr;

  // 3:    p * ssd
  distortion[0] += ssd0 * pMb->plr;
  distortion[0] = distortion[0] / 100;
}


#ifndef DISABLE_RDO

static void mdInterModeCost(macroblock_s   *pMb, 
                            refFrmBuf_s    **refBufList,
                            int            nRefFrames, 
                            int            picType, 
                            int            picWidth,
                            int32          rdoLambda,
                            int32          ssd0,
                            costMeasure_s  *codResults) 
{
  int recordNumSkipped;
  int recordQp;
  int recordPrevQp;
  int channelDistortion;
  statSlice_s testStat;      // dummy


  pecCodeLumaMB(pMb, pMb->predY, 0, picType);
  pedRecoLumaMB(pMb, pMb->predY, 0, picWidth);

  codResults->mse = CalculateSsd
    (& pMb->origY[0][0],     16, pMb->recoY, picWidth, 16, 16);

  pecCodeChromaMB(pMb, pMb->predC, picType);
  pedRecoChromaMB(pMb, pMb->predC, picWidth >> 1);

  codResults->mse += CalculateSsd
    (& pMb->origC[0][0],     16, pMb->recoU, picWidth >> 1, 8, 8);
  codResults->mse += CalculateSsd
    (& pMb->origC[0][0] + 8, 16, pMb->recoV, picWidth >> 1, 8, 8);

  // perform test encoding to get the actual rate

  bibInit(& pMb->mbBs);
  pMb->type = MBK_INTER;

  // do not want to change numSkipped and prevQp
  recordNumSkipped = pMb->numSkipped;
  recordQp         = pMb->qp;
  recordPrevQp     = pMb->prevQp;

  codResults->lumaCoeffBits = mbkSend(& pMb->mbBs,
    pMb, nRefFrames, picType, & testStat);

  pMb->numSkipped = recordNumSkipped;
  pMb->qp         = recordQp;
  pMb->prevQp     = recordPrevQp;

  if (pMb->interMode == MOT_COPY)
    pMb->interMode = MOT_16x16;

  codResults->bits = bibGetNumBits(& pMb->mbBs);
  codResults->cost = codResults->mse + rdoLambda * codResults->bits;

  // channel distortion estimation
  channelDistortion = 0;
  if (pMb->plr > 0)
    getChannelDistortion(pMb, refBufList, ssd0, &channelDistortion);

  codResults->cDistortion = channelDistortion;
}

#endif


int32 mdGetCost(macroblock_s *pMb, costMeasure_s *cost, int scaleFactor)
{
  if (pMb->plr == 0 || pMb->irType != PDT_IR)
    return cost->cost;
  else {
    if ( cost->cost == MAX_COST)
      return MAX_COST;
    else
      return ((int32)cost->cost + ((int32)cost->cDistortion * scaleFactor));
  }
}

static int interMbSyntaxBits(macroblock_s *pMb)
{
  int i, mbType, bitsMBtype;

  // estimate the bits on mbType
  mbType = streamGetMbTypeInter(pMb->interMode, pMb->refIndices);

  bitsMBtype = uvlcBitsUnsigned[mbType];
  if (pMb->interMode == MOT_8x8)
  {
    // need to send sub_mb_type
    for (i = 0; i < 4; i++)
      bitsMBtype += uvlcBitsUnsigned[pMb->interSubMbModes[i]];
  }

  return bitsMBtype;
}


void mdInterModeDecision(macroblock_s   *pMb,
                         refFrmBuf_s    **refBufList,
                         int            nRefFrames, 
                         int            picWidth,
                         int            picType, 
                         int            modeDecision,
                         int32          ssd0,
                         costMeasure_s  *interCost)
{
  int i, j;
  blkState_s *mvRefPairs;

#ifndef DISABLE_RDO
  if ((modeDecision & 0x0F) == MODE_DECISION_RDO)
  {
    int mode, bestMode, oldBestMode, mode16x16Disabled;
    costMeasure_s modeResults;


    interCost->cost = MAX_COST;
    bestMode = MOT_16x16;
    oldBestMode = pMb->interMode;
    
    // need skipping RDO only if current best MOT_16x16 can not be skipped
    mode = MOT_16x16;
    mode16x16Disabled = 0;

    if (pMb->skipPredMvValid) {
      mode = MOT_COPY;

      for (i = 0; i < 16; i ++) {
        pMb->modeMvRef[MOT_COPY][i].ref = 0;
        pMb->modeMvRef[MOT_COPY][i].mv = pMb->skipPredMv;
      }

      if ((pMb->modeMvRef[MOT_16x16][0].ref == 0) &&
        (pMb->modeMvRef[MOT_16x16][0].mv.x == pMb->skipPredMv.x) &&
        (pMb->modeMvRef[MOT_16x16][0].mv.y == pMb->skipPredMv.y))
      {
        // this is handled as a skip case
        mode16x16Disabled = 1;
      }
    }

    for ( ; mode <= MOT_8x8; mode ++) {
      if (mode != MOT_COPY) {
        if (((mode < MOT_8x8) && (pMb->interModeFlags & (1 << (mode - 1))) == 0) ||
          ((mode == MOT_8x8) && (pMb->interModeFlags >> 3) == 0))
          continue;
      }

      if (mode == MOT_16x16 && mode16x16Disabled)
        continue;

      // the MV and refIdx for this mode is found in motion estimation
      mvRefPairs = pMb->modeMvRef[mode];

      // Copy motion vectors and reference index to get the prediction
      for (j = 0; j < BLK_PER_MB;  j ++) 
        for (i = 0; i < BLK_PER_MB;  i ++) 
          pMb->current[j][i] = mvRefPairs[j * 4 + i];

      // get the cost of this particular inter-mode
      pMb->type = MBK_INTER;

      pMb->interMode = mode;
      if (mode == MOT_COPY)
        pMb->interMode = MOT_16x16;

      pMb->interSyntaxBits = mcpFindDiffMvs(pMb, nRefFrames - 1);

      // get the luma and chroma predictors
      mcpGetPred(pMb, refBufList);

      mdInterModeCost
        (pMb, refBufList, nRefFrames, picType, picWidth, pMb->rdoLambda, ssd0, & modeResults);

      // adjust for the skipping cost
      if (mode == MOT_COPY) {
        int skipCountCost;

        // this cost is included in a non-skipped MB
        skipCountCost = pMb->rdoLambda * (vlcuUVLCSize(pMb->numSkipped + 2) - 1);

        if (modeResults.bits) {
          int skipCost;

          // let's see if it is worthwhile to skip this MB
          skipCost = CalculateSsd
            (& pMb->origY[0][0], 16, & pMb->predY[0][0], 16, 16, 16);

          skipCost += CalculateSsd
            (& pMb->origC[0][0], 16, & pMb->predC[0][0], 16, 8, 8);
          skipCost += CalculateSsd
            (& pMb->origC[0][8], 16, & pMb->predC[0][8], 16, 8, 8);

          if (pMb->plr == 0) {
            if ((skipCost + skipCountCost < modeResults.cost) &&
              (modeResults.lumaCoeffBits == 0)) {
              // let's skip this
              modeResults.bits = 0;
              modeResults.mse  = skipCost;
              modeResults.cost = modeResults.mse;
            }
          }
          else {
            if ((skipCost + modeResults.cDistortion + skipCountCost < mdGetCost(pMb, &modeResults, 1)) &&
              (modeResults.lumaCoeffBits == 0)) {
              // let's skip this
              modeResults.bits = 0;
              modeResults.mse  = skipCost;
              modeResults.cost = modeResults.mse;
            }
          }
        }

        if (modeResults.bits == 0)
          modeResults.cost += skipCountCost;
      }

      if (mdGetCost(pMb, &modeResults, 1) < mdGetCost(pMb, interCost, 1)) // modeResults.cost < interCost->cost
      {
        bestMode = mode;
        *interCost = modeResults;
      }
    }

    pMb->interMode = bestMode;
  }
  else
#endif
  {
    int channelDistortion;

    channelDistortion = 0;
    if (pMb->plr > 0)
      getChannelDistortion(pMb, refBufList, ssd0, &channelDistortion);

    interCost->cDistortion = (int) channelDistortion;
  }

  // we got the best mode already if not rdo
  mvRefPairs = pMb->modeMvRef[pMb->interMode];

  for (j = 0; j < BLK_PER_MB;  j ++) 
    for (i = 0; i < BLK_PER_MB;  i ++) 
      pMb->current[j][i] = mvRefPairs[j * 4 + i];

  // do we have MOT_COPY as the best mode
  if ((pMb->interMode == MOT_COPY) && (interCost->bits != 0))
    pMb->interMode = MOT_16x16;

  pMb->type = MBK_INTER;

  // differential motion vectors, must be called before interMbSyntaxBits
  pMb->interSyntaxBits = 0;
  if (pMb->interMode != MOT_COPY)
  {
    pMb->interSyntaxBits  = mcpFindDiffMvs(pMb, nRefFrames - 1);
    pMb->interSyntaxBits += interMbSyntaxBits(pMb);
  }

  pMb->actualInterSad  = interCost->sad - (int32)pMb->interSyntaxBits * pMb->lambda;

  // possible to separate an MB/sub-MB unnecessarily, because of greedy search.
  // for example, best mode is 16x8, but 2 parts have the same motion vectors. 
  if (pMb->interMode > MOT_16x16)
  {
    if (MergeTree(mvRefPairs, & pMb->interMode))
    {
      // find the differential motion vectors again
      // mcpFindDiffMvs must be called before interMbSyntaxBits
      pMb->interSyntaxBits = mcpFindDiffMvs(pMb, nRefFrames - 1);
      pMb->interSyntaxBits += interMbSyntaxBits(pMb);

      interCost->sad = pMb->actualInterSad + pMb->interSyntaxBits * pMb->lambda;
    }
  }
}


void mdIntraModeDecision(macroblock_s   *pMb,
                         refFrmBuf_s    **refBufList,
                         int            picWidth,
                         int            picType,
                         int            modeDecision,
                         int32          ssd0,
                         costMeasure_s  *intra16x16Cost,
                         costMeasure_s  *intra4x4Cost,
                         costMeasure_s  *intraCost)
{
  int mbAddr;
  
  mbAddr = pMb->idxY * picWidth / MBK_SIZE + pMb->idxX ;
  *intraCost = initCostMeasure;

#ifndef DISABLE_RDO
  if ((modeDecision & 0x0F) == MODE_DECISION_RDO)
  {
    // pick better intra mode between intra16x16 and intra4x4, 
    // and the best chroma intra mode at the same time
    int mode, bestChromaMode, startMode, stopMode, intraType;
    int32 chromaIntraSad;
    costMeasure_s current, chromaCost;
    int chromaModeAvail[IPR_CHROMA_NUM_MODES];

    // Get all possible chroma predictors
    iprGetPredChroma(pMb->predIntraC, chromaModeAvail, pMb->recoU, pMb->recoV, 
      picWidth >> 1, pMb->mbAvailMapIntra);

    if ((modeDecision & RDO_INTRA_CHROMA) == 0)
    {
      chromaIntraSad = mdIntraPredChroma(pMb, chromaModeAvail, 1);
      startMode = pMb->intraModeChroma;
      stopMode  = pMb->intraModeChroma;
    }
    else
    {
      startMode = 0;
      stopMode = IPR_CHROMA_NUM_MODES - 1;
    }

    chromaCost = initCostMeasure;

    bestChromaMode = pMb->intraModeChroma;
    pMb->type = MBK_INTRA;
    intraType = MBK_INTRA_TYPE1;

    for (mode = startMode; mode <= stopMode; mode ++) 
    {
      if (chromaModeAvail[mode]) 
      {
        int otherSyntaxBits;
        statSlice_s testStat;      // dummy

        pecCodeChromaMB(pMb, pMb->predIntraC[mode], picType);
        pedRecoChromaMB(pMb, pMb->predIntraC[mode], picWidth >> 1);

        chromaCost.mse = CalculateSsd
          (& pMb->origC[0][0],     16, pMb->recoU, picWidth >> 1, 8, 8);
        chromaCost.mse += CalculateSsd
          (& pMb->origC[0][0] + 8, 16, pMb->recoV, picWidth >> 1, 8, 8);

        // test encoding
        bibInit(& pMb->mbBs);

        chromaCost.bits  = uvlcBitsUnsigned[mode];
        chromaCost.bits += streamSendChromaCoeffs(& pMb->mbBs,
          pMb, & testStat);

        if (pMb->intra16x16enabled) {
          // --------------------------------------------------------------------
          // evaluate the cost if chroma is encoded with the best intra16x16

          // number of bits used for mbType and cbp
          // intialize some parameters to encode MB in intra4x4
          pMb->intraType = MBK_INTRA_TYPE2;
          pMb->cbpY = pMb->intra16x16CbpY;

          otherSyntaxBits = streamCountIntraSyntaxBits(pMb, picType);

          current.mse  = intra16x16Cost->mse + chromaCost.mse;
          current.bits = otherSyntaxBits + intra16x16Cost->bits + chromaCost.bits;
          current.cost = current.mse + pMb->rdoLambda * current.bits;
          if (refBufList[0] && pMb->plr > 0)
            current.cDistortion = pMb->plr * (refBufList[0]->channelDistortion[mbAddr] + ssd0) / 100;
          else
            current.cDistortion = 0;
		  current.sad = intra16x16Cost->sad; 
          if ( mdGetCost(pMb, &current, 1) < mdGetCost(pMb, intraCost, 1) )
          {
            intraType = MBK_INTRA_TYPE2;
            bestChromaMode = mode;
            *intraCost = current;
          }
        }

        // --------------------------------------------------------------------
        // evaluate the cost if chroma is encoded with the best intra4x4
        // number of bits used for mbType and cbp
        // intialize some parameters to encode MB in intra4x4
        pMb->intraType = MBK_INTRA_TYPE1;
        pMb->cbpY = pMb->intra4x4CbpY;    // calculated in intra4x4 prediction

        otherSyntaxBits = streamCountIntraSyntaxBits(pMb, picType);

        current.mse  = intra4x4Cost->mse + chromaCost.mse;
        current.bits = otherSyntaxBits + intra4x4Cost->bits + chromaCost.bits;
        current.cost = current.mse + pMb->rdoLambda * current.bits;
        // the channel distortion is regarded to be 0.0
        if (refBufList[0] && pMb->plr > 0)
          current.cDistortion = pMb->plr * (refBufList[0]->channelDistortion[mbAddr] + ssd0) / 100;
        else
          current.cDistortion = 0;
		current.sad = intra4x4Cost->sad; 
        if ( mdGetCost(pMb, &current, 1) < mdGetCost(pMb, intraCost, 1) )
        {
          intraType = MBK_INTRA_TYPE1;
          bestChromaMode = mode;
          *intraCost = current;
        }
      }
    }

    pMb->intraType = intraType;
    pMb->intraModeChroma = bestChromaMode;
  }
  else
#endif
  {
    // pick better intra mode between intra16x16 and intra4x4
    if (intra4x4Cost->cost < intra16x16Cost->cost)
    {
      pMb->intraType = MBK_INTRA_TYPE1;
      *intraCost = *intra4x4Cost;
      pMb->actualIntraSad = pMb->actualIntra4x4Sad;
      pMb->minMSE = pMb->actualIntra4x4Sad;
    }
    else {
      pMb->intraType = MBK_INTRA_TYPE2;
      *intraCost = *intra16x16Cost;
    pMb->actualIntraSad = pMb->actualIntra16x16Sad;
      pMb->minMSE = pMb->actualIntra16x16Sad;
    }

    if (refBufList[0] && pMb->plr > 0)
      intraCost->cDistortion = pMb->plr * (refBufList[0]->channelDistortion[mbAddr] + ssd0) / 100;
    else
      intraCost->cDistortion = 0;
    // the chroma mode is decided later when intra/inter decision is made
  }
}


