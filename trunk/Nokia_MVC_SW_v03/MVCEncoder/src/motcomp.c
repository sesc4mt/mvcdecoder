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
 * motcomp.c
 *
 * Contains:
 *    Functions for Motion compensation and prediction.
 *
 */


#include <limits.h>
#include "globals.h"
#include "nrctypes.h"
#include "vlcutility.h"
#include "macroblock.h"
#include <stdio.h>


const int8 modeBlkIndices[5][4] = 
{
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 8, 0, 0},
  {0, 2, 0, 0},
  {0, 2, 8, 10},
};


// the first element is always reserved
const int8 modeNumBlocks[8] =
{
  16, 16, 8, 8, 4, 2, 2, 1
};


const int8 modePartWidth[8] =
{
  4, 4, 4, 2, 2, 2, 1, 1
};

const int8 modePartHeight[8] =
{
  4, 4, 2, 4, 2, 1, 2, 1
};

#define NA      -2


#define MEDIAN(med, a0, a1, a2)   {             \
    if ((a0) > (a1)) {                          \
		  if (a1 > (a2))        (med) = (a1);       \
		  else if ((a0) > (a2))	(med) = (a2);       \
		  else        			    (med) = (a0);       \
	  } else if ((a0) > (a2))	(med) = (a0);       \
	  else if ((a1) > (a2))		(med) = (a2);       \
	  else            		    (med) = (a1);       \
  }


static const int8 trIdx[8] = {0, 0, 0, 1, 1, 1, 2, 2};


/*
 *
 * mcpFindPredMv:
 *
 * Parameters:
 *      pMb               Macroblock information
 *      refNum            Reference frame index for this partition
 *      mode              Indicate size of partition
 *      blkAddr           Addr of 1st block of partition in 4x4 block array
 *
 * Function:
 *      Calculate the MV predictor. 
 *
 * Returns:
 *      -
 *
 */
motVec_s mcpFindPredMv(macroblock_s *pMb,
                       int          refNum,
                       int          mode,
                       int          blkAddr)
{
  motVec_s vecA;
  motVec_s vecB;
  motVec_s vecC;
  motVec_s vecX;
  int refLeft, refUp, refUpRight;
  int numEqualRefs;
  blkState_s *blkLeft, *blkUp, *blkUpRight;

  /*
   * Fetch vectors and reference frame numbers of blocks A, B and C
   */
  blkLeft    = pMb->blkLeft[blkAddr];
  blkUp      = pMb->blkUp[blkAddr];
  blkUpRight = pMb->blkUpRight[trIdx[mode]][blkAddr];

  refLeft    = blkLeft->ref == refNum;
  vecA       = blkLeft->mv;
  refUp      = blkUp->ref == refNum;
  vecB       = blkUp->mv;
  refUpRight = blkUpRight->ref == refNum;
  vecC       = blkUpRight->mv;

  numEqualRefs = refLeft + refUp + refUpRight;

  // put the most common case in the front
  if ((mode > MOT_8x16) && (numEqualRefs > 1))
  {
    // performa median filtering
    MEDIAN(vecX.x, vecA.x, vecB.x, vecC.x);
    MEDIAN(vecX.y, vecA.y, vecB.y, vecC.y);
  }
  else
  {
    // directional prediction
    if (mode == MOT_16x8)
    {
      if (blkAddr == 0)
      {
        if (refUp)
          return vecB;
      }
      else 
      {
        if (refLeft)
          return vecA;
      }
    }
    else if (mode == MOT_8x16)
    {
      if (blkAddr == 0)
      {
        if (refLeft)
          return vecA;
      }
      else
      {
        // this could be real upRight, or upRight replaced by upLeft
        if (refUpRight)
          return vecC;
      }
    }

    /*
    * If only one of the neighboring block has the same reference
    * frame number as the  current block, predict from that block.
    */

    // this is of little probabability, make it faster
    if (numEqualRefs == 1)
    {
      if (refLeft)
        vecX = vecA;
      else if (refUp)
        vecX = vecB;
      else
        vecX = vecC;
    }
    else if ((blkUp->ref == REF_NA) && (blkUpRight->ref == REF_NA) && (blkLeft->ref >= 0))
    {
      // if only vecA is available, vecA is set as the predictor
      vecX = vecA;
    }
    else
    {
      // performa median filtering
      MEDIAN(vecX.x, vecA.x, vecB.x, vecC.x);
      MEDIAN(vecX.y, vecA.y, vecB.y, vecC.y);
    }
  }

  return vecX;
}


/*
 * mcpFindDiffMvs:
 *
 * Parameters:
 *      pMb                 Macroblock information
 *      refIdxRange         Information related to motion estimation
 *
 * Function:
 *      Calculate the differential motion vectors and referenace frame indices
 *      for all MB partitions. We use the index tables to find the position of
 *      the first 4x4 block within the partition.
 *
 * Returns:
 *      -
 */
int mcpFindDiffMvs(macroblock_s *pMb,
                   int          refIdxRange)
{
  int i, mpIdx, mpBlkAddr, blkAddr;
  int mpBlkCount;
  int mvBits, interMode, subMbMode, blkMode;
  int numVecs, lastNumVecs;
  motVec_s predVec;
  blkState_s *mrPair, *blkInfo;


  mvBits  = 0;
  numVecs = 0;

  interMode  = pMb->interMode;
  subMbMode  = 0;
  mpBlkCount = 1;
  blkInfo    = & pMb->current[0][0];

  for (mpIdx = 0; mpIdx < numOfRefPar[interMode - 1]; mpIdx ++)
  {
    mpBlkAddr = modeBlkIndices[interMode][mpIdx];
    blkAddr   = mpBlkAddr;

    pMb->refIndices[mpIdx] = (u_int8) blkInfo[mpBlkAddr].ref;
    mvBits += vlcGetRefIndexBits(refIdxRange, pMb->refIndices[mpIdx]);

    if (interMode == MOT_8x8)
    {
      // make index this way to use the same tables
      subMbMode  = pMb->interSubMbModes[mpIdx];
      mpBlkCount = numOfRefPar[subMbMode];
    }
    blkMode = interMode + subMbMode;

    lastNumVecs = numVecs;
    numVecs += mpBlkCount;
    for (i = lastNumVecs; i < numVecs; i ++)
    {
      if (interMode == MOT_8x8)
        blkAddr = mpBlkAddr + (modeBlkIndices[subMbMode + 1][i - lastNumVecs] >> 1);

      mrPair = & blkInfo[blkAddr];
      predVec = mcpFindPredMv(pMb, mrPair->ref, blkMode, blkAddr);

      pMb->diffVecs[i][0] = (int16)(mrPair->mv.x - predVec.x);
      pMb->diffVecs[i][1] = (int16)(mrPair->mv.y - predVec.y);

      mvBits += vlcGetMvBits(pMb->diffVecs[i][0], pMb->diffVecs[i][1]);
    }
  }

  if (interMode == MOT_8x8)
  {
    if ((pMb->refIndices[0] | pMb->refIndices[1] | pMb->refIndices[2] | 
      pMb->refIndices[3]) == 0)
    {
      if (refIdxRange > 1)
        mvBits -= 4;
    }
  }

  // else, no reference frame indices are sent at all
  pMb->numVecs = numVecs;

  return mvBits;
}


const int8 mcpModePartWidth[5]  = {4, 4, 4, 2, 1};
const int8 mcpModePartHeight[5] = {4, 4, 2, 4, 1};


/*
 * mcpGetQuarterPixels:
 *
 * Parameters:
 *      ref                 ref frame buffer, luma, adjusted for partition
 *      w                   ref frame buffer width
 *      vecX                Motion vector, x component, in 1/4 pixel
 *      vecY                Motion vector, y component, in 1/4 pixel
 *      mbPartW             MB partition width
 *      mbPartH             MB partition height
 *      pred                Predict pixel buffer, adjusted for partition
 *
 * Function:
 *      Get luma pixels from the reference frame buffer. Perform quarter
 *      pixel interpolation if necessary.
 *
 * Returns:
 *      -
 */
void mcpGetQuarterPixels(u_int8 *ref, 
                         int    w, 
                         int    vecX, 
                         int    vecY,
                         int    mbPartW, 
                         int    mbPartH,
                         u_int8 pred[][16])
{
  int i, j;
  u_int8 *ref2;

  if (((vecX | vecY) & 1) == 0) {
    // integer or half-pixel locations, already interpolated
    for (j = 0; j < mbPartH; j ++) {
      for (i = 0; i < mbPartW; i += BLK_SIZE) {
        pred[j][i + 0] = ref[i * 2 + 0];
        pred[j][i + 1] = ref[i * 2 + 2];
        pred[j][i + 2] = ref[i * 2 + 4];
        pred[j][i + 3] = ref[i * 2 + 6];
      }
      ref += (2 * w);
    }
  }
  else 
  {
    // Quarter-pel locations
    ref2 = ref + (vecY&1)*w + (vecX&1);

    if (((vecX ^ vecY) & 3) == 0) {
      ref++;
      ref2--;
    }

    for (j = 0; j < mbPartH; j ++) {
      for (i = 0; i < mbPartW; i += BLK_SIZE) {
        pred[j][i + 0] = (u_int8)((ref[i * 2 + 0] + ref2[i * 2 + 0] + 1) >> 1);
        pred[j][i + 1] = (u_int8)((ref[i * 2 + 2] + ref2[i * 2 + 2] + 1) >> 1);
        pred[j][i + 2] = (u_int8)((ref[i * 2 + 4] + ref2[i * 2 + 4] + 1) >> 1);
        pred[j][i + 3] = (u_int8)((ref[i * 2 + 6] + ref2[i * 2 + 6] + 1) >> 1);
      }
      ref  += (2 * w);
      ref2 += (2 * w);
    }
  }
}


/*
 * mcpGetPred
 *
 * Parameters:
 *      pMb                 Macroblock information
 *      refBufList          Reference frames
 *
 * Function:
 *      Compute luminance and chrominance prediction for the current
 *      macroblock using motion vector found.
 *
 * Returns:
 *      -
 */
void mcpGetPred(macroblock_s *pMb,
                refFrmBuf_s  **refBufList)
{
  int blkIdxX, blkIdxY;
  int shapeX, shapeY, mbPartW, mbPartH, mbPartChromaW, mbPartChromaH;
  int i0, j0;
  int c, i, j;
  int dx, dy;
  int yBufWidth, cBufWidth;
  u_int8 *refPtr, *predPtr, *predPtrC;
  refFrmBuf_s *pRefFrm;
#ifdef ENABLE_SEARCH_WINDOW
  // for internal search window
  searchWin_s *pSWin = pMb->pSWin;
#endif

  yBufWidth = refBufList[0]->yBufWidth;
  cBufWidth = refBufList[0]->cBufWidth;

  shapeX = mcpModePartWidth[pMb->interMode];
  shapeY = mcpModePartHeight[pMb->interMode];
  mbPartW = shapeX * BLK_SIZE;
  mbPartH = shapeY * BLK_SIZE;
  mbPartChromaW = mbPartW >> 1;
  mbPartChromaH = mbPartH >> 1;

  for (blkIdxY = 0; blkIdxY < BLK_PER_MB; blkIdxY += shapeY) {
    for (blkIdxX = 0; blkIdxX < BLK_PER_MB; blkIdxX += shapeX) {
      blkState_s *pBlkState;

      // Absolute motion vector coordinates of the macroblock
      pBlkState = & pMb->current[blkIdxY][blkIdxX];
      predPtr   = & pMb->predY[blkIdxY*BLK_SIZE][blkIdxX*BLK_SIZE];

      i0 = (pMb->idxX * BLK_PER_MB + blkIdxX) * BLK_SIZE * 4 + 
        pBlkState->mv.x;
      j0 = (pMb->idxY * BLK_PER_MB + blkIdxY) * BLK_SIZE * 4 + 
        pBlkState->mv.y;

      pRefFrm = refBufList[pBlkState->ref];

#ifdef ENABLE_SEARCH_WINDOW
      if (pSWin->useSearchWin) {
        // motion compensation from internal search window

        int     x, y;

        x = (i0 >> 1) + (pSWin->srx * 2);
        y = (j0 >> 1) + (pSWin->sry - pSWin->locY) * 2;   // w.r.t. the upsampled frame buf

        refPtr = pSWin->searchWindow +  y * pSWin->searchWinWidth + x ;

        mcpGetQuarterPixels(refPtr, pSWin->searchWinWidth, i0, j0, mbPartW, mbPartH,         
          (u_int8 (*)[MBK_SIZE]) predPtr);
      }
      else
#endif
      {
        refPtr  = & pRefFrm->y[(j0 >> 1) * yBufWidth + (i0 >> 1)];

        mcpGetQuarterPixels(refPtr, yBufWidth, i0, j0, mbPartW, mbPartH, 
          (u_int8 (*)[MBK_SIZE]) predPtr);
      }

      dx = i0 & 7;
      dy = j0 & 7;
      i0 = i0 >> 3;
      j0 = j0 >> 3;

      /* Chroma vectors have 1/8 pel precision, Bilinear interpolation */
      refPtr = pRefFrm->u;
      for (c = 0; c < 16; c += 8) {  // 2 chroma components
        int h0, h1;
        u_int8 *upPoint;

        predPtrC = & pMb->predC[blkIdxY*(BLK_SIZE/2)][blkIdxX * (BLK_SIZE/2)] + c;
        refPtr = & refPtr[j0 * cBufWidth + i0];

        for (j = 0; j < mbPartChromaH; j ++) {
          upPoint = refPtr;
          h0 = 8 * upPoint[0] - (upPoint[0] - upPoint[cBufWidth]) * dy;
          upPoint ++;
          for (i = 0; i < mbPartChromaW; i += 2) {
            h1 = 8 * upPoint[i    ] - (upPoint[i    ] - upPoint[cBufWidth + i    ]) * dy;
            predPtrC[j * 16 + i    ] = (u_int8) ((8*h0 - (h0 - h1)*dx + 32) >> 6);
            h0 = 8 * upPoint[i + 1] - (upPoint[i + 1] - upPoint[cBufWidth + i + 1]) * dy;
            predPtrC[j * 16 + i + 1] = (u_int8) ((8*h1 - (h1 - h0)*dx + 32) >> 6);
          }
          refPtr += cBufWidth;
        }

        refPtr = pRefFrm->v;
      }
    }
  }
}


/*
 * mcpGetColocatedMb
 *
 * Parameters:
 *      pMb                 Macroblock information
 *      refBufList          Reference frames
 *
 * Function:
 *      Get the colocated MB from the last picture (in display order).
 *
 * Returns:
 *      -
 */
void mcpGetColocatedMb(macroblock_s *pMb,
                       refFrmBuf_s  **refBufList,
                       u_int8 colMbY[MBK_SIZE][MBK_SIZE],
                       u_int8 colMbC[MBK_SIZE/2][2 * (MBK_SIZE/2)])
{
  int i0, j0;
  int c, i, j;
  int yBufWidth, cBufWidth;
  u_int8 *refPtr;
  refFrmBuf_s *pRefFrm;
#ifdef ENABLE_SEARCH_WINDOW
  searchWin_s *pSWin = pMb->pSWin;
#endif


  // Coordinates of the macroblock in half-pel resolution
  i0 = (pMb->idxX * BLK_PER_MB) * BLK_SIZE * 2;
  j0 = (pMb->idxY * BLK_PER_MB) * BLK_SIZE * 2;
  
  pRefFrm = refBufList[0];
  
#ifdef ENABLE_SEARCH_WINDOW
  if (pSWin->useSearchWin) {
    // motion compensation from internal search window

    int     x, y;

    x = i0 + (pSWin->srx * 2);
    y = j0 + (pSWin->sry - pSWin->locY) * 2;   // w.r.t. the upsampled frame buf

    yBufWidth = pSWin->searchWinWidth;
    refPtr = pSWin->searchWindow +  y * yBufWidth + x ;
  }
  else
#endif
  {
    yBufWidth = refBufList[0]->yBufWidth;
    refPtr  = & pRefFrm->y[j0 * yBufWidth + i0];
  }

  for (j = 0; j < 16; j ++) {
    for (i = 0; i < 16; i ++) {
      colMbY[j][i] = refPtr[2 * i];
    }
    refPtr += 2 * yBufWidth;
  }

  /* Chroma macroblock coordinates */
  i0 = i0 >> 2;
  j0 = j0 >> 2;

  cBufWidth = refBufList[0]->cBufWidth;

  refPtr = pRefFrm->u;
  for (c = 0; c < 16; c += 8) {  // 2 chroma components
    refPtr = & refPtr[j0 * cBufWidth + i0];
    for (j = 0; j < 8; j ++) {
      for (i = 0; i < 8; i ++) {
        colMbC[j][i + c] = refPtr[i];
      }
      refPtr += cBufWidth;
    }
    
    refPtr = pRefFrm->v;
  }
}
