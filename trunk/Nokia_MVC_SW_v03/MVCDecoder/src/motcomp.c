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
 *    Motion compensation and prediction
 *
 */

#ifdef CHECK_MV_RANGE
#include <stdio.h>
#endif

#include "globals.h"
#include "motcomp.h"
#include "framebuffer.h"

#if defined(USE_CLIPBUF)
#include "clipbuf.h"
#endif


#define ONEFOURTH1  20
#define ONEFOURTH2  -5
#define ONEFOURTH3  1


static const int numModeMotVecs[MOT_NUM_MODES+1] = {
  0, 1, 2, 2, 4, 8, 8, 16
};

static const int numModeMotVecs8x8[4] = {
  1, 2, 2, 4
};

static const int blockShapes[][2] = {
  {4, 4},
  {4, 2},
  {2, 4},
  {2, 2},
  {2, 2}
};

static const int blockShapes8x8[][2] = {
  {2, 2},
  {2, 1},
  {1, 2},
  {1, 1}
};


#ifdef CHECK_MV_RANGE
extern int maxVerticalMvRange;
#endif



/*
 * findPredMotVec
 *
 * Parameters:
 *      refTab                Table containing reference frame number
 *                            for the whole frame
 *      motVecs               Motion vectors for the whole frame
 *      blksPerLine           The number of 4x4 blocks per line
 *      mbAvailBits           Availability of neighboring macroblocks
 *      blkIdxX               Horizontal 4x4 block index within macroblock
 *      blkIdxY               Vertical 4x4 block index within macroblock
 *      shapeX                Width of the partition in 4x4 blocks
 *      shapeY                Height of the partition in 4x4 blocks
 *
 * Function:
 *      Find the prediction vector for the current (sub-)macroblock partition.
 *
 * Returns:
 *      Prediction vector
 *
 */
static motVec_s findPredMotVec(int8 *refTab, motVec_s *vecs, int blksPerLine,
                               int mbAvailBits, int blkIdxX, int blkIdxY,
                               int shapeX, int shapeY)
{
  static const motVec_s zeroVec = {0,0};
  motVec_s const *vecA;
  motVec_s const *vecB;
  motVec_s const *vecC;
  motVec_s vecX;
  int refNum, refLeft, refUp, refUpRight;
  int blkIdxXright;

  /*
   *       |       |
   *     D | B     | C
   *   ----+-------+----
   *     A |       |
   *       |   X   |
   *       |       |
   *
   *   X is current partition. Motion vectors from named
   *   positions are used for prediction
   */

  /*
   * Fetch vectors and reference frame numbers of blocks A, B and C
   */

  if (blkIdxX != 0 || (mbAvailBits & 1)) {
    vecA    = &vecs[-1];
    refLeft = refTab[-1];
  }
  else {
    /* A is outside the picture  =>  A is zero  and ref is -1 */
    vecA    = &zeroVec;
    refLeft = -1;
  }

  if (blkIdxY != 0 || (mbAvailBits & 2)) {
    vecB  = &vecs[-blksPerLine];
    refUp = refTab[-blksPerLine];
  }
  else {
    /* B is outside the picture  =>  B is zero and ref is -2 */
    vecB  = &zeroVec;
    refUp = -2;
  }

  blkIdxXright = blkIdxX + shapeX - 1;
  if ((blkIdxXright != BLK_PER_MB/2 && (blkIdxXright&blkIdxY) != 0) ||
      (blkIdxY == 0 && (blkIdxXright < BLK_PER_MB-1 ? !(mbAvailBits & 2) : !(mbAvailBits & 4))))
  {
    /* C is outside the picture or is not available  =>  C = D */
    if ((blkIdxY != 0 && (blkIdxX != 0 || (mbAvailBits & 1))) ||
        (blkIdxY == 0 && (blkIdxX != 0 ? (mbAvailBits & 2) : (mbAvailBits & 8))))
    {
      vecC       = &vecs[-blksPerLine-1];
      refUpRight = refTab[-blksPerLine-1];
    }
    else {
      /* D is also outside the picture  =>  C is not available */
      /* If both B abd C are not available then C = B = A  */
      if (refUp == -2) {
        vecC = vecB = vecA;
        refUpRight = refUp = refLeft;
      }
      /* if only C is not available then C is zero */
      else {
        vecC       = &zeroVec;
        refUpRight = -1;
      }
    }
  }
  else {
    /* C is inside the picture and is available */
    vecC       = &vecs[-blksPerLine+shapeX];
    refUpRight = refTab[-blksPerLine+shapeX];
  }

  refNum = refTab[0];

  /*
   * Directional prediction for 8x16 and 16x8 partitions
   */
  if (shapeX + shapeY == 6) {
    if (shapeX == 2) {  /* Is it 8x16? */
      if (blkIdxX == 0 && refLeft == refNum)
        return *vecA;
      else if (blkIdxX != 0 && refUpRight == refNum)
        return *vecC;
    }
    else {              /* It is 16x8 */
      if (blkIdxY == 0 && refUp == refNum)
        return *vecB;
      else if (blkIdxY != 0 && refLeft == refNum)
        return *vecA;
    }
  }

  /*
   * If only one of the neighboring partitions has the same reference
   * frame number as the  current partition, predict from that partition.
   */
  if (refLeft == refNum) {
    if (refUp != refNum && refUpRight != refNum)
      return *vecA;
  }
  else {
    if (refUp == refNum) {
      if (refUpRight != refNum)
        return *vecB;
    }
    else if (refUpRight == refNum)
      return *vecC;
  }

  /*
   * If everything else fails, do median prediction.
   */

  /* Median of x co-ordinates */
  if (vecB->x < vecA->x) {
    if      (vecA->x < vecC->x) vecX.x = vecA->x; // vecB->x < vecA->x < vecC->x
    else if (vecC->x < vecB->x) vecX.x = vecB->x; // vecC->x < vecB->x < vecA->x
    else                        vecX.x = vecC->x; // vecB->x < vecC->x < vecA->x
  }
  else {  // vecA->x < vecB->x
    if      (vecC->x < vecA->x) vecX.x = vecA->x; // vecC->x < vecA->x < vecB->x
    else if (vecB->x < vecC->x) vecX.x = vecB->x; // vecA->x < vecB->x < vecC->x
    else                        vecX.x = vecC->x; // vecA->x < vecC->x < vecB->x
  }

  /* Median of y co-ordinates */
  if (vecB->y < vecA->y) {
    if      (vecA->y < vecC->y) vecX.y = vecA->y; // vecB->y < vecA->y < vecC->y
    else if (vecC->y < vecB->y) vecX.y = vecB->y; // vecC->y < vecB->y < vecA->y
    else                        vecX.y = vecC->y; // vecB->y < vecC->y < vecA->y
  }
  else {  // vecA->y < vecB->y
    if      (vecC->y < vecA->y) vecX.y = vecA->y; // vecC->y < vecA->y < vecB->y
    else if (vecB->y < vecC->y) vecX.y = vecB->y; // vecA->y < vecB->y < vecC->y
    else                        vecX.y = vecC->y; // vecA->y < vecC->y < vecB->y
  }

  return vecX;
}


/*
 *
 * mcpGetNumMotVecs:
 *
 * Parameters:
 *      mode                  MB partition type (16x16, 8x16, 16x8, 8x8)
 *      subMbTypes            Sub-MB partition types (8x8, 4x8, 8x4, 4x4)
 *
 * Function:
 *      Get the number of motion vectors that need to be decoded for given
 *      MB type and Sub-MB partition types.
 *      
 * Returns:
 *      Number of motion vectors.
 *
 */
int mcpGetNumMotVecs(int interMode, int subMbTypes[4])
{
  int numVecs;

  if (interMode < MOT_8x8)
    numVecs = numModeMotVecs[interMode];
  else {
    numVecs  = numModeMotVecs8x8[subMbTypes[0]];
    numVecs += numModeMotVecs8x8[subMbTypes[1]];
    numVecs += numModeMotVecs8x8[subMbTypes[2]];
    numVecs += numModeMotVecs8x8[subMbTypes[3]];
  }

  return numVecs;
}


/*
 *
 * mcpClearMBmotion:
 *
 * Parameters:
 *      mbIdxX                MB horizontal location
 *      mbIdxY                MB vertical location
 *      picWidth              Frame buffer width in pixels
 *      refTab                Reference index buffer
 *      refNum                Reference frame index
 *      motVecs               Motion vector buffer
 *
 * Function:
 *      Set MB reference frame indices to refNum.
 *      
 * Returns:
 *      -
 */
void mcpClearMBmotion(int mbIdxX, int mbIdxY, int picWidth, int8 *refTab,
                      int refNum, motVec_s *motVecs)
{
  int blksPerLine = picWidth/BLK_SIZE;
  int blkIdxX, blkIdxY;
  motVec_s *vecPtr;
  int8 *refPtr;

  vecPtr = &motVecs[mbIdxY*BLK_PER_MB*blksPerLine+mbIdxX*BLK_PER_MB];
  refPtr = &refTab[mbIdxY*BLK_PER_MB*blksPerLine+mbIdxX*BLK_PER_MB];

  for (blkIdxY = 0; blkIdxY < BLK_PER_MB; blkIdxY++) {
    for (blkIdxX = 0; blkIdxX < BLK_PER_MB; blkIdxX++) {
      vecPtr[blkIdxX].x = 0;
      vecPtr[blkIdxX].y = 0;
      refPtr[blkIdxX] = (int8)refNum;
    }
    vecPtr += blksPerLine;
    refPtr += blksPerLine;
  }
}


/*
 *
 * mcpPutVectors:
 *
 * Parameters:
 *      mbIdxX                MB horizontal location
 *      mbIdxY                MB vertical location
 *      ref                   Reference frame buffer list
 *      mbType                MB partition type (16x16, 8x16, 16x8, 8x8)
 *      subMbTypes            Sub-macroblock partition types (8x8, 4x8, 8x4, 4x4)
 *      mbRefIndices          Reference frame indices for MB partitions
 *      picWidth              Frame buffer width in pixels
 *      refTab                Reference index buffer
 *      hasRef                Indicates whether multiple reference framea are used
 *      motVecs               Motion vector buffer
 *      mbAvailBIts           Availability of neighboring macroblocks
 *      diffVecs              Decoded delta vectors
 *      numVecs               The number of motion vectors in current macrobock
 *
 * Function:
 *      Put decoded motion vectors to the motion vector buffer
 *      
 * Returns:
 *      -
 */
void mcpPutVectors(int mbIdxX, int mbIdxY, int mbType, int *subMbTypes,
                   int *mbRefIndices, int picWidth, int8 *refTab,
                   int numRefFrames, motVec_s *motVecs, int mbAvailBits,
                   int diffVecs[BLK_PER_MB*BLK_PER_MB][2], int numVecs)
{
  int blksPerLine;
  int shapeX, shapeY;
  int blkIdxX, blkIdxY;
  motVec_s predVec;
  int y;
  int *subMbTypePtr;
  int blk8X, blk8Y;
  int blkAddr;
  int8 *refIdxPtr;
  motVec_s *vecPtr;
  int *diffVecPtr;
  int refIdx, refIdx2;
  int16 mvX, mvY;

  blksPerLine = picWidth/BLK_SIZE;
  blkAddr = mbIdxY*BLK_PER_MB*blksPerLine + mbIdxX*BLK_PER_MB;
  refTab = &refTab[blkAddr];
  motVecs = &motVecs[blkAddr];

  /*
   * Put ref. indices to the ref. index buffer.
   */
  refIdxPtr = refTab;

  if (numRefFrames > 1 && mbType <= MOT_8x8) {

    /*
     * Put reference indices for 16x16, 16x8, 8x16 or 8x8 blocks
     */
    shapeX = blockShapes[mbType-1][0];
    shapeY = blockShapes[mbType-1][1];

    for (blkIdxY = 0; blkIdxY < BLK_PER_MB; blkIdxY+=shapeY) {

      refIdx  = *mbRefIndices++;
      refIdx2 = (shapeX == 2) ? *mbRefIndices++ : refIdx;

      y = 0;
      do {
        refIdxPtr[0] = (int8) refIdx;
        refIdxPtr[1] = (int8) refIdx;
        refIdxPtr[2] = (int8) refIdx2;
        refIdxPtr[3] = (int8) refIdx2;
        refIdxPtr += blksPerLine;
      } while (++y < shapeY);
    }
  }
  else {

    /*
     * All reference indices are zero
     */
    for (blkIdxY = 0; blkIdxY < BLK_PER_MB; blkIdxY++) {
      refIdxPtr[0] = 0;
      refIdxPtr[1] = 0;
      refIdxPtr[2] = 0;
      refIdxPtr[3] = 0;
      refIdxPtr += blksPerLine;
    }
  }


  /*
   * Put motion vectors to the motion vector buffer.
   */
  diffVecPtr = diffVecs[0];

  if (numVecs <= 4) {

    /*
     * Put motion vectors for 16x16, 16x8, 8x16 and 8x8 macroblock partitions
     */
    shapeX = blockShapes[mbType-1][0];  /* Width of partition in 4x4 blocks */
    shapeY = blockShapes[mbType-1][1];  /* Height of partition in 4x4 blocks */

    for (blkIdxY = 0; blkIdxY < BLK_PER_MB; blkIdxY+=shapeY) {
      for (blkIdxX = 0; blkIdxX < BLK_PER_MB; blkIdxX+=shapeX) {

        blkAddr = blkIdxY*blksPerLine+blkIdxX;
        vecPtr = &motVecs[blkAddr];

        /* Get predicted vector */
        predVec = findPredMotVec(refTab+blkAddr, vecPtr, blksPerLine,
                                 mbAvailBits, blkIdxX, blkIdxY, shapeX, shapeY);

        mvX = (int16) (predVec.x + (*diffVecPtr++));
        mvY = (int16) (predVec.y + (*diffVecPtr++));

#ifdef CHECK_MV_RANGE
        if (mvX < -2048*4 || mvX > (2048*4-1)) {
          printf("Horizontal MV component range violation %f (%i,%i) (%i,%i)\n", 0.25*mvX, mbIdxX*BLK_PER_MB+blkIdxX, mbIdxY*BLK_PER_MB+blkIdxY, shapeX, shapeY);
        }
        if (mvY < -maxVerticalMvRange*4 || mvY > (maxVerticalMvRange*4-1)) {
          printf("Vertical MV component range violation %f (%i,%i) (%i,%i)\n", 0.25*mvY, mbIdxX*BLK_PER_MB+blkIdxX, mbIdxY*BLK_PER_MB+blkIdxY, shapeX, shapeY);
        }
#endif

        y = 0;
        do {
          vecPtr[0].x = mvX;
          vecPtr[0].y = mvY;
          vecPtr[1].x = mvX;
          vecPtr[1].y = mvY;
          if (shapeX == 4) {
            /* for 16x8 and 16x16 blocks */
            vecPtr[2].x = mvX;
            vecPtr[2].y = mvY;
            vecPtr[3].x = mvX;
            vecPtr[3].y = mvY;
          }
          vecPtr += blksPerLine;
        } while (++y < shapeY);

      }
    }
  }
  else {

    /*
     * Put motion vectors for 8x8 sub-macroblock partitions. Each sub-macroblock
     * can have either 8x8, 8x4, 4x8 or 4x4 partitions.
     */
    subMbTypePtr = subMbTypes;

    /* Scan all 8x8 sub-macroblocks */
    for (blk8Y = 0; blk8Y < BLK_PER_MB; blk8Y+=BLK_PER_MB/2) {
      for (blk8X = 0; blk8X < BLK_PER_MB; blk8X+=BLK_PER_MB/2) {

        int subMbType = *subMbTypePtr++;

        /* Get sub-macroblock partition shape for current sub-macroblock */
        shapeX = blockShapes8x8[subMbType][0];
        shapeY = blockShapes8x8[subMbType][1];

        /* Scan all sub-macroblock partitions (8x8, 8x4, 4x8 or 4x4) in current sub-macroblock */
        blkIdxY = blk8Y;
        do {
          blkIdxX = blk8X;
          do {

            blkAddr = blkIdxY*blksPerLine+blkIdxX;
            vecPtr = &motVecs[blkAddr];

            /* Get predicted vector */
            predVec = findPredMotVec(refTab+blkAddr, vecPtr, blksPerLine,
                                     mbAvailBits, blkIdxX, blkIdxY,
                                     shapeX, shapeY);

            mvX = (int16) (predVec.x + (*diffVecPtr++));
            mvY = (int16) (predVec.y + (*diffVecPtr++));

#ifdef CHECK_MV_RANGE
            if (mvX < -2048*4 || mvX > (2048*4-1)) {
              printf("Horizontal MV component range violation %f (%i,%i) (%i,%i)\n", 0.25*mvX, mbIdxX*BLK_PER_MB+blkIdxX, mbIdxY*BLK_PER_MB+blkIdxY, shapeX, shapeY);
            }
            if (mvY < -maxVerticalMvRange*4 || mvY > (maxVerticalMvRange*4-1)) {
              printf("Vertical MV component range violation %f (%i,%i) (%i,%i)\n", 0.25*mvY, mbIdxX*BLK_PER_MB+blkIdxX, mbIdxY*BLK_PER_MB+blkIdxY, shapeX, shapeY);
            }
#endif

            /* Put vectors for current motion block */

            /* 4x4 block */
            vecPtr[0].x = mvX;
            vecPtr[0].y = mvY;
            if (shapeY == 1) {
              if (shapeX == 2) {
                /* 8x4 block */
                vecPtr[1].x = mvX;
                vecPtr[1].y = mvY;
              }
            }
            else {
              /* 4x8 block */
              vecPtr[blksPerLine].x = mvX;
              vecPtr[blksPerLine].y = mvY;
              if (shapeX == 2) {
                /* 8x8 block */
                vecPtr[1].x = (int16) mvX;
                vecPtr[1].y = (int16) mvY;
                vecPtr[blksPerLine+1].x = mvX;
                vecPtr[blksPerLine+1].y = mvY;
              }
            }

          } while ((blkIdxX += shapeX) < blk8X+BLK_PER_MB/2);
        } while ((blkIdxY += shapeY) < blk8Y+BLK_PER_MB/2);

      }
    }
  }
}


/*
 *
 * mcpPutSkipModeVectors:
 *
 * Parameters:
 *      mbIdxX                MB horizontal location
 *      mbIdxY                MB vertical location
 *      picWidth              Frame buffer width in pixels
 *      refTab                Reference index buffer
 *      motVecs               Motion vector buffer
 *      mbAvailBits           Availability of neighboring macroblocks
 *
 * Function:
 *      Put skip mode motion vectors to the motion vector buffer
 *      
 * Returns:
 *      1 if macroblock MV is zero, 0 otherwise
 */
int mcpPutSkipModeVectors(int mbIdxX, int mbIdxY, int picWidth, int8 *refTab,
                          motVec_s *motVecs, int mbAvailBits)
{
  int blks   = picWidth/BLK_SIZE;
  int blkX   = mbIdxX*BLK_PER_MB;
  int blkY   = mbIdxY*BLK_PER_MB;
  motVec_s vec;
  int blkIdxY;
  motVec_s *vecPtr;
  int8 *refPtr;
  int zeroMvFlag;
  int blkAddr;

  blkAddr = blkY*blks+blkX;

  vecPtr = &motVecs[blkAddr];
  refPtr = &refTab[blkAddr];

  /* If upper or left MB is not available or has zero motion, skip mode vec is zero */
  if (!(mbAvailBits & 1) || !(mbAvailBits & 2) ||
      (refPtr[-1] == 0 && vecPtr[-1].x == 0 && vecPtr[-1].y == 0) ||
      (refPtr[-blks] == 0 && vecPtr[-blks].x == 0 && vecPtr[-blks].y == 0))
  {
    vec.x = 0;
    vec.y = 0;
    zeroMvFlag = 1;
  }
  /* Otherwise, skip mode vec is predicted */
  else {
    refPtr[0] = 0;
    vec = findPredMotVec(refPtr, vecPtr, blks, mbAvailBits, 0, 0, 4, 4);
    zeroMvFlag = 0;

#ifdef CHECK_MV_RANGE
    if (vec.x < -2048*4 || vec.x > (2048*4-1)) {
      printf("Horizontal MV component range violation %f\n", 0.25*vec.x);
    }
    if (vec.y < -maxVerticalMvRange*4 || vec.y > (maxVerticalMvRange*4-1)) {
      printf("Vertical MV component range violation %f\n", 0.25*vec.y);
    }
#endif
  }

  for (blkIdxY = 0; blkIdxY < BLK_PER_MB; blkIdxY++) {
    vecPtr[0] = vec;
    vecPtr[1] = vec;
    vecPtr[2] = vec;
    vecPtr[3] = vec;
    refPtr[0] = 0;
    refPtr[1] = 0;
    refPtr[2] = 0;
    refPtr[3] = 0;

    vecPtr += blks;
    refPtr += blks;
  }

  return zeroMvFlag;
}


#ifndef AVC_MOTION_COMP_ASM

/*
 * mcpCopyMacroblock:
 *
 * Parameters:
 *      reco                  Reconstruction frame
 *      ref                   Reference frame
 *      pixX                  Horizontal pixel position
 *      pixY                  Vertical pixel position
 *      picWidth              Frame width in pixels
 *
 * Function:
 *      Copy macroblock data to reconstruction frame from
 *      co-located macroblock ín reference frame.
 *      
 * Returns:
 *      -
 */
void mcpCopyMacroblock(frmBuf_s *reco, frmBuf_s *ref,
                       int pixX, int pixY, int picWidth)
{
  u_int8 *recoPtr;
  u_int8 *refPtr;
  int c, i, j;
  int refWidth = picWidth;

  recoPtr = &reco->y[pixY*picWidth+pixX];
  refPtr = &ref->y[pixY*refWidth+pixX];

  for (j = 0; j < MBK_SIZE; j++, recoPtr+=picWidth, refPtr+=refWidth) {
    for (i = 0; i < MBK_SIZE; i+=4) {
      recoPtr[i+0] = refPtr[i+0];
      recoPtr[i+1] = refPtr[i+1];
      recoPtr[i+2] = refPtr[i+2];
      recoPtr[i+3] = refPtr[i+3];
    }
  }

  picWidth >>= 1;
  refWidth >>= 1;
  pixX >>= 1;
  pixY >>= 1;

  recoPtr = &reco->u[pixY*picWidth+pixX];
  refPtr = &ref->u[pixY*refWidth+pixX];

  for (c = 0; c < 2; c++) {
    for (j = 0; j < MBK_SIZE/2; j++, recoPtr+=picWidth, refPtr+=refWidth) {
      for (i = 0; i < MBK_SIZE/2; i+=4) {
        recoPtr[i+0] = refPtr[i+0];
        recoPtr[i+1] = refPtr[i+1];
        recoPtr[i+2] = refPtr[i+2];
        recoPtr[i+3] = refPtr[i+3];
      }
    }
    recoPtr = &reco->v[pixY*picWidth+pixX];
    refPtr = &ref->v[pixY*refWidth+pixX];
  }

}

#endif


/*
 * mcpFillMacroblock:
 *
 * Parameters:
 *      reco                  Reconstruction frame
 *      pixX                  Horizontal pixel position
 *      pixY                  Vertical pixel position
 *      picWidth              Frame width in pixels
 *
 * Function:
 *      Initialize all macroblock pixels with value 128
 *      
 * Returns:
 *      -
 */
void mcpFillMacroblock(frmBuf_s *reco, int pixX, int pixY, int picWidth)
{
  int i, j, c;
  u_int8 *recoPtr;

  recoPtr = &reco->y[pixY*picWidth+pixX];

  for (j = 0; j < MBK_SIZE; j++, recoPtr+=picWidth)
    for (i = 0; i < MBK_SIZE; i++)
      recoPtr[i] = 128;

  picWidth >>= 1;
  pixX >>= 1;
  pixY >>= 1;

  recoPtr = &reco->u[pixY*picWidth+pixX];

  for (c = 0; c < 2; c++) {
    for (j = 0; j < MBK_SIZE/2; j++, recoPtr+=picWidth)
      for (i = 0; i < MBK_SIZE/2; i++)
        recoPtr[i] = 128;
    recoPtr = &reco->v[pixY*picWidth+pixX];
  }
}


/*
 *
 * mcpGetPred:
 *
 * Parameters:
 *      predY                 Return pointer for predicted luma pixels
 *      predC                 Return pointer for predicted chroma pixels
 *      mbIdxX                MB horizontal location
 *      mbIdxY                MB vertical location
 *      ref                   Reference frame buffer list
 *      picWidth              Frame buffer width in pixels
 *      picHeight             Frame buffer height in pixels
 *      motVecs               Motion vector buffer
 *      refTab                Reference index buffer
 *      subMbModes            8x8 sub-macroblocks modes
 *
 * Function:
 *      Get motion compensated prediction for both luma and chroma MBs
 *
 *      NOTE: this version does not use image padding. If pixels outside the
 *      picture need to be fetched, a function getRefAre is called.
 *      
 * Returns:
 *      -
 */
void mcpGetPred(u_int8 predY[MBK_SIZE][MBK_SIZE],
                u_int8 predC[MBK_SIZE/2][MBK_SIZE],
                int mbIdxX, int mbIdxY, frmBuf_s **ref, int picWidth,
                int picHeight, motVec_s *motVecs, int8 *refTab,
				const int *subMbModes)
{
  int blkIdxX, blkIdxY;
  int blkX, blkY;
  int blksPerLine;
  int blkAddr;
  int blkSkip;
  u_int8 *predPtr, *predPtrC;

  blksPerLine = picWidth/BLK_SIZE;

  blkX = mbIdxX*BLK_PER_MB;
  blkY = mbIdxY*BLK_PER_MB;

  predPtr = predY[0];
  predPtrC = predC[0];

  blkAddr = blkY*blksPerLine + blkX;
  refTab += blkAddr;
  motVecs += blkAddr;

  blkSkip = (BLK_PER_MB/2)*blksPerLine - BLK_PER_MB;

  for (blkIdxY = 0; blkIdxY < BLK_PER_MB; blkIdxY+=BLK_PER_MB/2) {
    for (blkIdxX = 0; blkIdxX < BLK_PER_MB; blkIdxX+=BLK_PER_MB/2) {

      int refIdx = *refTab;
      int mode = *subMbModes++;

      if (mode == 0) {
        mcpGetPred8x8((u_int8 (*)[MBK_SIZE]) predPtr,
                      (u_int8 (*)[MBK_SIZE]) predPtrC,
                      blkX+blkIdxX, blkY+blkIdxY, ref[refIdx],
                      picWidth, picHeight, motVecs);
      }
      else {
        mcpGetPred4x4((u_int8 (*)[MBK_SIZE]) predPtr,
                      (u_int8 (*)[MBK_SIZE]) predPtrC,
                      blkX+blkIdxX, blkY+blkIdxY, ref[refIdx],
                      picWidth, picHeight, motVecs);
      }

      predPtr += MBK_SIZE/2;
      predPtrC += MBK_SIZE/2/2;
      refTab += BLK_PER_MB/2;
      motVecs += BLK_PER_MB/2;
    }
    predPtr += (MBK_SIZE/2)*MBK_SIZE - MBK_SIZE;
    predPtrC += (MBK_SIZE/2/2)*MBK_SIZE - MBK_SIZE/2;
    refTab = refTab + blkSkip;
    motVecs = motVecs + blkSkip;
  }
}


#ifndef AVC_MOTION_COMP_ASM


/* Fetch luma reference pixels. If pixel lies outside the picture, */
/* nearest boundary pixel is fetched */
static void getRefArea(u_int8 *frm, u_int8 *buf, int picWidth, int picHeight, int x, int y, int w, int h)
{
  int i, y2;
  u_int8 *linePtr;

  y2 = y + h;

  if (x < 0) {
    x = max(1-w, x);
    do {
      linePtr = frm + clip(0, picHeight-1, y) * picWidth;
      i = x;
      do {
        *buf++ = *linePtr;
        i++;
      } while (i < 0);
      do {
        *buf++ = *linePtr++;
        i++;
      } while (i < x+w);
      y++;
    } while (y < y2);
  }
  else if (x+w <= picWidth) {
    do {
      linePtr = frm + clip(0, picHeight-1, y) * picWidth + x;
      i = 0;
      do {
        *buf++ = *linePtr++;
        i++;
      } while (i < w);
      y++;
    } while (y < y2);
  }
  else {
    x = min(picWidth-1, x);
    do {
      linePtr = frm + clip(0, picHeight-1, y) * picWidth + x;
      i = x;
      do {
        *buf++ = *linePtr++;
        i++;
      } while (i < picWidth);
      linePtr--;
      do {
        *buf++ = *linePtr;
        i++;
      } while (i < x+w);
      y++;
    } while (y < y2);
  }
}


/* Fetch 3x3 chroma reference pixels. If pixel lies outside the picture, */
/* nearest boundary pixel is fetched */
static void getRefAreaC(u_int8 *frm, u_int8 *buf, int picWidth, int picHeight, int x, int y)
{
  int y2, inc;
  u_int8 *linePtr;

  y2 = y + 3;

  if (x < 0) {
    inc = x < -1 ? 0 : 1;
    do {
      linePtr = frm + clip(0, picHeight-1, y) * picWidth;
      *buf++ = *linePtr;
      *buf++ = *linePtr;
      linePtr += inc;
      *buf++ = *linePtr;
      y++;
    } while (y < y2);
  }
  else if (x+2 < picWidth) {
    do {
      linePtr = frm + clip(0, picHeight-1, y) * picWidth + x;
      *buf++ = *linePtr++;
      *buf++ = *linePtr++;
      *buf++ = *linePtr++;
      y++;
    } while (y < y2);
  }
  else {
    inc = x+2 <= picWidth ? 1 : 0;
    frm = frm + picWidth - 1 - inc;
    do {
      linePtr = frm + clip(0, picHeight-1, y) * picWidth;
      *buf++ = *linePtr;
      linePtr += inc;
      *buf++ = *linePtr;
      *buf++ = *linePtr;
      y++;
    } while (y < y2);
  }

}


/*
 *
 * mcpGetPred8x8:
 *
 * Parameters:
 *      predY                 Return pointer for predicted luma pixels
 *      predC                 Return pointer for predicted chroma pixels
 *      blkX                  Sub-macroblock horizontal location (in 4x4 blocks)
 *      blkY                  Sub-macroblock vertical location (in 4x4 blocks)
 *      ref                   Reference frame buffer
 *      picWidth              Frame buffer width in pixels
 *      picHeight             Frame buffer height in pixels
 *      motVec                Motion vector
 *
 * Function:
 *      Get motion compensated prediction for 8x8 block.
 *
 * Returns:
 *      -
 */
void mcpGetPred8x8(u_int8 predPtr[MBK_SIZE][MBK_SIZE],
                   u_int8 predC[MBK_SIZE/2][MBK_SIZE],
                   int blkX, int blkY, frmBuf_s *ref, int picWidth,
                   int picHeight, motVec_s *motVec)
{
  int refWidth;
  int i, j;
  u_int8 *refPtr;
  int xPos, yPos, xInt, yInt, xFrac, yFrac;
  int coef0, coef1, coef2, coef3;
  int c;
  int tmp;
  int32 tmp2;
  int picWidthC;
  int picHeightC;
  u_int8 refArea[(2*BLK_SIZE+2+3)*(2*BLK_SIZE+2+3)];
  int block[2*BLK_SIZE+2+3][2*BLK_SIZE];
  int lineIdx, colIdx;
  u_int8 *refC[2];

#ifdef USE_CLIPBUF
  const u_int8 *clipBufPtr = clip8Buf + 256;
#endif

  picWidthC = picWidth/2;
  picHeightC = picHeight/2;

  /* Absolute coordinates of the prediction block */
  xPos = blkX*BLK_SIZE*4 + motVec->x;
  yPos = blkY*BLK_SIZE*4 + motVec->y;
  
  /*
   * Get luma prediction
   */
  xInt = xPos >> 2;
  yInt = yPos >> 2;
  xFrac = xPos & 3;
  yFrac = yPos & 3;
  
  refPtr = ref->y;

  /* Full-pel precision */
  if (xFrac == 0 && yFrac == 0) {
    if (xInt >= 0 && xInt <= picWidth-2*BLK_SIZE &&
        yInt >= 0 && yInt <= picHeight-2*BLK_SIZE)
    {
      refPtr += yInt*picWidth + xInt;
      refWidth = picWidth;
    }
    else {
      getRefArea(refPtr, refArea, picWidth, picHeight, xInt, yInt, 2*BLK_SIZE, 2*BLK_SIZE);
      refPtr = refArea;
      refWidth = 2*BLK_SIZE;
    }
    for (j = 0; j < 2*BLK_SIZE;  j++) {
      predPtr[j][0] = refPtr[j*refWidth + 0];
      predPtr[j][1] = refPtr[j*refWidth + 1];
      predPtr[j][2] = refPtr[j*refWidth + 2];
      predPtr[j][3] = refPtr[j*refWidth + 3];
      predPtr[j][4] = refPtr[j*refWidth + 4];
      predPtr[j][5] = refPtr[j*refWidth + 5];
      predPtr[j][6] = refPtr[j*refWidth + 6];
      predPtr[j][7] = refPtr[j*refWidth + 7];
    }
  }
  /* Horizontal fullpel precision, vertical subpel precision */
  else if (xFrac == 0) {
    if (xInt >= 0 && xInt <= picWidth-2*BLK_SIZE &&
      yInt >  1 && yInt <  picHeight-2*BLK_SIZE-2)
    {
      refPtr += yInt*picWidth + xInt;
      refWidth = picWidth;
    }
    else {
      getRefArea(refPtr, refArea, picWidth, picHeight, xInt, yInt-2, 2*BLK_SIZE, 2*BLK_SIZE+2+3);
      refPtr = refArea + 2*(2*BLK_SIZE);
      refWidth = 2*BLK_SIZE;
    }
    /* Vertical interpolation */
    for (j = 0; j < 2*BLK_SIZE;  j++) {
      for (i = 0; i < 2*BLK_SIZE;  i++) {
        tmp = (
          ONEFOURTH1*(refPtr[ j   *refWidth + i] +
                      refPtr[(j+1)*refWidth + i]) +
          ONEFOURTH2*(refPtr[(j-1)*refWidth + i] +
                      refPtr[(j+2)*refWidth + i]) +
          ONEFOURTH3*(refPtr[(j-2)*refWidth + i] +
                      refPtr[(j+3)*refWidth + i]) + 16
          ) >> 5;
#ifdef USE_CLIPBUF
        predPtr[j][i] = clipBufPtr[tmp];
#else
        predPtr[j][i] = (u_int8) clip(0,255,tmp);
#endif
      }
    }
    /* Linear interp. */
    if ((yFrac&1) != 0) {
      lineIdx = yFrac >> 1;
      for (j = 0; j < 2*BLK_SIZE;  j++) {
        for (i = 0; i < 2*BLK_SIZE;  i++) {
          predPtr[j][i] = (u_int8) ((predPtr[j][i] + refPtr[(j+lineIdx)*refWidth+i] + 1) >> 1);
        }
      }
    }
  }
  /* Horizontal subpel precision, vertical fullpel precision */
  else if (yFrac == 0) {
    if (xInt >  1 && xInt <  picWidth-2*BLK_SIZE-2 &&
      yInt >= 0 && yInt <= picHeight-2*BLK_SIZE)
    {
      refPtr += yInt*picWidth + xInt;
      refWidth = picWidth;
    }
    else {
      getRefArea(refPtr, refArea, picWidth, picHeight, xInt-2, yInt, 2*BLK_SIZE+2+3, 2*BLK_SIZE);
      refPtr = refArea + 2;
      refWidth = 2*BLK_SIZE+2+3;
    }
    /* Horizontal interpolation */
    for (j = 0; j < 2*BLK_SIZE;  j++) {
      for (i = 0; i < 2*BLK_SIZE;  i++) {
        tmp = (
          ONEFOURTH1*(refPtr[j*refWidth + i  ] +
                      refPtr[j*refWidth + i+1]) +
          ONEFOURTH2*(refPtr[j*refWidth + i-1] +
                      refPtr[j*refWidth + i+2]) +
          ONEFOURTH3*(refPtr[j*refWidth + i-2] +
                      refPtr[j*refWidth + i+3]) + 16
          ) >> 5;
#ifdef USE_CLIPBUF
        predPtr[j][i] = clipBufPtr[tmp];
#else
        predPtr[j][i] = (u_int8) clip(0,255,tmp);
#endif
      }
    }
    /* Linear interp. */
    if ((xFrac&1) != 0) {
      colIdx = xFrac >> 1;
      for (j = 0; j < 2*BLK_SIZE;  j++) {
        for (i = 0; i < 2*BLK_SIZE;  i++) {
          predPtr[j][i] = (u_int8) ((predPtr[j][i] + refPtr[j*refWidth+i+colIdx] + 1) >> 1);
        }
      }
    }
  }
  /* The rest of the sub-pel positions require 13x13 reference pixel are */
  else {
    if (xInt > 1 && xInt <  picWidth-2*BLK_SIZE-2 &&
      yInt > 1 && yInt <  picHeight-2*BLK_SIZE-2)
    {
      refPtr += yInt*picWidth + xInt;
      refWidth = picWidth;
    }
    else {
      getRefArea(refPtr, refArea, picWidth, picHeight, xInt-2, yInt-2, 2*BLK_SIZE+2+3, 2*BLK_SIZE+2+3);
      refPtr = refArea + 2*(2*BLK_SIZE+2+3) + 2;
      refWidth = 2*BLK_SIZE+2+3;
    }
    
    /* Horizontal 1/2-pel precision, vertical sub-pel precision */
    if (xFrac == 2) {
      /* horizontal interpolation */
      for (j = -2; j < 2*BLK_SIZE+3;  j++) {
        for (i = 0; i < 2*BLK_SIZE;  i++) {
          tmp = (
            ONEFOURTH1*(refPtr[j*refWidth + i  ] +
                        refPtr[j*refWidth + i+1]) +
            ONEFOURTH2*(refPtr[j*refWidth + i-1] +
                        refPtr[j*refWidth + i+2]) +
            ONEFOURTH3*(refPtr[j*refWidth + i-2] +
                        refPtr[j*refWidth + i+3]));
          block[2+j][i] = tmp;
        }
      }
      /* Vertical interpolation */
      for (j = 0; j < 2*BLK_SIZE;  j++) {
        for (i = 0; i < 2*BLK_SIZE;  i++) {
          tmp2 = (
            ONEFOURTH1*((int32)(block[2+j  ][i] + block[2+j+1][i])) +
            ONEFOURTH2*((int32)(block[2+j-1][i] + block[2+j+2][i])) +
            ONEFOURTH3*((int32)(block[2+j-2][i] + block[2+j+3][i])) + 512
            ) >> 10;
#ifdef USE_CLIPBUF
          predPtr[j][i] = clipBufPtr[tmp2];
#else
          predPtr[j][i] = (u_int8) clip(0,255,tmp2);
#endif
        }
      }
      /* Linear interp. */
      if ((yFrac&1) != 0) {
        lineIdx = 2 + (yFrac >> 1);
        for (j = 0; j < 2*BLK_SIZE;  j++) {
          for (i = 0; i < 2*BLK_SIZE;  i++) {
            tmp = (block[lineIdx+j][i] + 16) >> 5;
#ifdef USE_CLIPBUF
            predPtr[j][i] = (u_int8) ((predPtr[j][i] + clipBufPtr[tmp] + 1) >> 1);
#else
            predPtr[j][i] = (u_int8) ((predPtr[j][i] + clip(0,255,tmp) + 1) >> 1);
#endif
          }
        }
      }
    }
    /* Vertical 1/2-pel precision, horizontal 1/4-pel precision */
    else if (yFrac == 2) {
      /* Vertical interpolation */
      for (i = -2; i < 2*BLK_SIZE+3; i++) {
        for (j = 0; j < 2*BLK_SIZE; j++) {
          tmp = (
            ONEFOURTH1*(refPtr[ j   *refWidth + i] +
                        refPtr[(j+1)*refWidth + i]) +
            ONEFOURTH2*(refPtr[(j-1)*refWidth + i] +
                        refPtr[(j+2)*refWidth + i]) +
            ONEFOURTH3*(refPtr[(j-2)*refWidth + i] +
                        refPtr[(j+3)*refWidth + i]));
          block[2+i][j] = tmp;
        }
      }
      /* Horizontal interpolation */
      for (i = 0; i < 2*BLK_SIZE;  i++) {
        for (j = 0; j < 2*BLK_SIZE;  j++) {
          tmp2 = (
            ONEFOURTH1*((int32)(block[2+i  ][j] + block[2+i+1][j])) +
            ONEFOURTH2*((int32)(block[2+i-1][j] + block[2+i+2][j])) +
            ONEFOURTH3*((int32)(block[2+i-2][j] + block[2+i+3][j])) + 512
            ) >> 10;
#ifdef USE_CLIPBUF
          predPtr[j][i] = clipBufPtr[tmp2];
#else
          predPtr[j][i] = (u_int8) clip(0,255,tmp2);
#endif
        }
      }
      /* Linear interp. */
      colIdx = 2 + (xFrac >> 1);
      for (i = 0; i < 2*BLK_SIZE;  i++) {
        for (j = 0; j < 2*BLK_SIZE;  j++) {
          tmp = (block[colIdx+i][j] + 16) >> 5;
#ifdef USE_CLIPBUF
          predPtr[j][i] = (u_int8) ((predPtr[j][i] + clipBufPtr[tmp] + 1) >> 1);
#else
          predPtr[j][i] = (u_int8) ((predPtr[j][i] + clip(0,255,tmp) + 1) >> 1);
#endif
        }
      }
    }
    /* Horizontal&vertical 1/4-pel precision -> diagonal interpolation */
    else {
      /* Vertical interpolation */
      colIdx = xFrac >> 1;
      for (j = 0; j < 2*BLK_SIZE; j++) {
        for (i = 0; i < 2*BLK_SIZE; i++) {
          tmp = (
            ONEFOURTH1*(refPtr[ j   *refWidth + i+colIdx] +
                        refPtr[(j+1)*refWidth + i+colIdx]) +
            ONEFOURTH2*(refPtr[(j-1)*refWidth + i+colIdx] +
                        refPtr[(j+2)*refWidth + i+colIdx]) +
            ONEFOURTH3*(refPtr[(j-2)*refWidth + i+colIdx] +
                        refPtr[(j+3)*refWidth + i+colIdx]) + 16
            ) >> 5;
#ifdef USE_CLIPBUF
          predPtr[j][i] = clipBufPtr[tmp];
#else
          predPtr[j][i] = (u_int8) clip(0,255,tmp);
#endif
        }
      }
      /* Horizontal interpolation */
      lineIdx = yFrac >> 1;
      for (j = 0; j < 2*BLK_SIZE; j++) {
        for (i = 0; i < 2*BLK_SIZE; i++) {
          tmp = (
            ONEFOURTH1*(refPtr[(j+lineIdx)*refWidth + i  ] +
                        refPtr[(j+lineIdx)*refWidth + i+1]) +
            ONEFOURTH2*(refPtr[(j+lineIdx)*refWidth + i-1] +
                        refPtr[(j+lineIdx)*refWidth + i+2]) +
            ONEFOURTH3*(refPtr[(j+lineIdx)*refWidth + i-2] +
                        refPtr[(j+lineIdx)*refWidth + i+3]) + 16
            ) >> 5;
#ifdef USE_CLIPBUF
          predPtr[j][i] = (u_int8) ((predPtr[j][i] + clipBufPtr[tmp] + 1) >> 1);
#else
          predPtr[j][i] = (u_int8) ((predPtr[j][i] + clip(0,255,tmp) + 1) >> 1);
#endif
        }
      }
    }
  }


  /*
   * Get chroma prediction
   */
  
  /* Bilinear interpolation coefficients */
  coef0 = (8-(xPos&7)) * (8-(yPos&7));
  coef1 = (xPos&7)     * (8-(yPos&7));
  coef2 = (8-(xPos&7)) * (yPos&7);
  coef3 = (xPos&7)     * (yPos&7);
  
  /* Chroma vectors have 1/8 chroma pel precision */
  xInt  = xPos>>3;
  yInt  = yPos>>3;
  
  if (xInt >= 0 && xInt < picWidthC-2*BLK_SIZE/2 &&
      yInt >= 0 && yInt < picHeightC-2*BLK_SIZE/2)
  {
    refC[0] = &ref->u[yInt*picWidthC+xInt];
    refC[1] = &ref->v[yInt*picWidthC+xInt];
    refWidth = picWidthC;
  }
  else {
    getRefArea(ref->u, refArea    , picWidthC, picHeightC, xInt, yInt, 5, 5);
    getRefArea(ref->v, refArea+5*5, picWidthC, picHeightC, xInt, yInt, 5, 5);
    refC[0] = refArea;
    refC[1] = refArea+5*5;
    refWidth = 5;
  }
  for (c = 0; c < 2; c++) {  /* 2 chroma components */
    for (j = 0; j < 2*BLK_SIZE/2;  j++) {
      for (i = 0; i < 2*BLK_SIZE/2;  i++) {
        tmp = (coef0 * refC[c][(j  )*refWidth + i  ] +
               coef1 * refC[c][(j  )*refWidth + i+1] +
               coef2 * refC[c][(j+1)*refWidth + i  ] +
               coef3 * refC[c][(j+1)*refWidth + i+1] + 32) >> 6;
        predC[j][c*(MBK_SIZE/2)+i] = (u_int8) tmp;
      }
    }
  }
}


/*
 *
 * mcpGetPred4x4:
 *
 * Parameters:
 *      predY                 Return pointer for predicted luma pixels
 *      predC                 Return pointer for predicted chroma pixels
 *      blkX0                 Sub-macroblock horizontal location
 *      blkY0                 Sub-macroblock vertical location
 *      ref                   Reference frame buffer
 *      picWidth              Frame buffer width in pixels
 *      picHeight             Frame buffer height in pixels
 *      motVecs               Motion vector buffer
 *
 * Function:
 *      Get motion compensated prediction for 4x4 blokcs within 8x8 sub-macroblock.
 *
 * Returns:
 *      -
 */
void mcpGetPred4x4(u_int8 predY[MBK_SIZE][MBK_SIZE],
                   u_int8 predC[MBK_SIZE/2][MBK_SIZE],
                   int blkX0, int blkY0, frmBuf_s *ref, int picWidth,
                   int picHeight, motVec_s *motVecs)
{
  int blksPerLine;
  int blkX, blkY;
  int blkIdxX, blkIdxY;
  int refWidth;
  int i, j;
  u_int8 *refPtr;
  int xPos, yPos, xInt, yInt, xFrac, yFrac;
  int coef0, coef1, coef2, coef3;
  int c;
  int tmp;
  int32 tmp2;
  int picWidthC;
  int picHeightC;
  u_int8 refArea[(BLK_SIZE+2+3)*(BLK_SIZE+2+3)];
  int block[BLK_SIZE+2+3][BLK_SIZE];
  int lineIdx, colIdx;
  u_int8 *refC[2];
  u_int8 (* predPtr)[MBK_SIZE];

#ifdef USE_CLIPBUF
  const u_int8 *clipBufPtr = clip8Buf + 256;
#endif


  picWidthC = picWidth/2;
  picHeightC = picHeight/2;
  blksPerLine = picWidth/BLK_SIZE;

  for (blkIdxY = 0; blkIdxY < BLK_PER_MB/2; blkIdxY++, motVecs+=blksPerLine) {
    for (blkIdxX = 0; blkIdxX < BLK_PER_MB/2; blkIdxX++) {

      blkX = blkX0 + blkIdxX;
      blkY = blkY0 + blkIdxY;

      /* Absolute coordinates of the prediction block */
      xPos = blkX*BLK_SIZE*4 + motVecs[blkIdxX].x;
      yPos = blkY*BLK_SIZE*4 + motVecs[blkIdxX].y;

      /*
       * Get luma prediction
       */
      xInt = xPos >> 2;
      yInt = yPos >> 2;
      xFrac = xPos & 3;
      yFrac = yPos & 3;

      refPtr = ref->y;
      predPtr = (u_int8 (*)[MBK_SIZE])&predY[blkIdxY*BLK_SIZE][blkIdxX*BLK_SIZE];

      /* Full-pel precision */
      if (xFrac == 0 && yFrac == 0) {
        if (xInt >= 0 && xInt <= picWidth-BLK_SIZE &&
            yInt >= 0 && yInt <= picHeight-BLK_SIZE)
        {
          refPtr += yInt*picWidth + xInt;
          refWidth = picWidth;
        }
        else {
          getRefArea(refPtr, refArea, picWidth, picHeight, xInt, yInt, 4, 4);
          refPtr = refArea;
          refWidth = 4;
        }
        for (j = 0; j < BLK_SIZE;  j++) {
          predPtr[j][0] = refPtr[j*refWidth + 0];
          predPtr[j][1] = refPtr[j*refWidth + 1];
          predPtr[j][2] = refPtr[j*refWidth + 2];
          predPtr[j][3] = refPtr[j*refWidth + 3];
        }
      }
      /* Horizontal fullpel precision, vertical subpel precision */
      else if (xFrac == 0) {
        if (xInt >= 0 && xInt <= picWidth-BLK_SIZE &&
            yInt >  1 && yInt <  picHeight-BLK_SIZE-2)
        {
          refPtr += yInt*picWidth + xInt;
          refWidth = picWidth;
        }
        else {
          getRefArea(refPtr, refArea, picWidth, picHeight, xInt, yInt-2, 4, 9);
          refPtr = refArea + 2*4;
          refWidth = 4;
        }
        /* Vertical interpolation */
        for (j = 0; j < BLK_SIZE;  j++) {
          for (i = 0; i < BLK_SIZE;  i++) {
            tmp = (
              ONEFOURTH1*(refPtr[ j   *refWidth + i] +
                          refPtr[(j+1)*refWidth + i]) +
              ONEFOURTH2*(refPtr[(j-1)*refWidth + i] +
                          refPtr[(j+2)*refWidth + i]) +
              ONEFOURTH3*(refPtr[(j-2)*refWidth + i] +
                          refPtr[(j+3)*refWidth + i]) + 16
            ) >> 5;
#ifdef USE_CLIPBUF
            predPtr[j][i] = clipBufPtr[tmp];
#else
            predPtr[j][i] = (u_int8) clip(0,255,tmp);
#endif
          }
        }
        /* Linear interp. */
        if ((yFrac&1) != 0) {
          lineIdx = yFrac >> 1;
          for (j = 0; j < BLK_SIZE;  j++) {
            for (i = 0; i < BLK_SIZE;  i++) {
              predPtr[j][i] = (u_int8) ((predPtr[j][i] + refPtr[(j+lineIdx)*refWidth+i] + 1) >> 1);
            }
          }
        }
      }
      /* Horizontal subpel precision, vertical fullpel precision */
      else if (yFrac == 0) {
        if (xInt >  1 && xInt <  picWidth-BLK_SIZE-2 &&
            yInt >= 0 && yInt <= picHeight-BLK_SIZE)
        {
          refPtr += yInt*picWidth + xInt;
          refWidth = picWidth;
        }
        else {
          getRefArea(refPtr, refArea, picWidth, picHeight, xInt-2, yInt, 9, 4);
          refPtr = refArea + 2;
          refWidth = 9;
        }
        /* Horizontal interpolation */
        for (j = 0; j < BLK_SIZE;  j++) {
          for (i = 0; i < BLK_SIZE;  i++) {
            tmp = (
              ONEFOURTH1*(refPtr[j*refWidth + i  ] +
                          refPtr[j*refWidth + i+1]) +
              ONEFOURTH2*(refPtr[j*refWidth + i-1] +
                          refPtr[j*refWidth + i+2]) +
              ONEFOURTH3*(refPtr[j*refWidth + i-2] +
                          refPtr[j*refWidth + i+3]) + 16
            ) >> 5;
#ifdef USE_CLIPBUF
            predPtr[j][i] = clipBufPtr[tmp];
#else
            predPtr[j][i] = (u_int8) clip(0,255,tmp);
#endif
          }
        }
        /* Linear interp. */
        if ((xFrac&1) != 0) {
          colIdx = xFrac >> 1;
          for (j = 0; j < BLK_SIZE;  j++) {
            for (i = 0; i < BLK_SIZE;  i++) {
              predPtr[j][i] = (u_int8) ((predPtr[j][i] + refPtr[j*refWidth+i+colIdx] + 1) >> 1);
            }
          }
        }
      }
      /* The rest of the sub-pel positions require 9x9 reference pixel are */
      else {
        if (xInt > 1 && xInt <  picWidth-BLK_SIZE-2 &&
            yInt > 1 && yInt <  picHeight-BLK_SIZE-2)
        {
          refPtr += yInt*picWidth + xInt;
          refWidth = picWidth;
        }
        else {
          getRefArea(refPtr, refArea, picWidth, picHeight, xInt-2, yInt-2, 9, 9);
          refPtr = refArea + 2*9 + 2;
          refWidth = 9;
        }

        /* Horizontal 1/2-pel precision, vertical sub-pel precision */
        if (xFrac == 2) {
          /* horizontal interpolation */
          for (j = -2; j < BLK_SIZE+3;  j++) {
            for (i = 0; i < BLK_SIZE;  i++) {
              tmp = (
                ONEFOURTH1*(refPtr[j*refWidth + i  ] +
                            refPtr[j*refWidth + i+1]) +
                ONEFOURTH2*(refPtr[j*refWidth + i-1] +
                            refPtr[j*refWidth + i+2]) +
                ONEFOURTH3*(refPtr[j*refWidth + i-2] +
                            refPtr[j*refWidth + i+3]));
              block[2+j][i] = tmp;
            }
          }
          /* Vertical interpolation */
          for (j = 0; j < BLK_SIZE;  j++) {
            for (i = 0; i < BLK_SIZE;  i++) {
              tmp2 = (
                ONEFOURTH1*((int32)(block[2+j  ][i] + block[2+j+1][i])) +
                ONEFOURTH2*((int32)(block[2+j-1][i] + block[2+j+2][i])) +
                ONEFOURTH3*((int32)(block[2+j-2][i] + block[2+j+3][i])) + 512
              ) >> 10;
#ifdef USE_CLIPBUF
              predPtr[j][i] = clipBufPtr[tmp2];
#else
              predPtr[j][i] = (u_int8) clip(0,255,tmp2);
#endif
            }
          }
          /* Linear interp. */
          if ((yFrac&1) != 0) {
            lineIdx = 2 + (yFrac >> 1);
            for (j = 0; j < BLK_SIZE;  j++) {
              for (i = 0; i < BLK_SIZE;  i++) {
                tmp = (block[lineIdx+j][i] + 16) >> 5;
#ifdef USE_CLIPBUF
                predPtr[j][i] = (u_int8) ((predPtr[j][i] + clipBufPtr[tmp] + 1) >> 1);
#else
                predPtr[j][i] = (u_int8) ((predPtr[j][i] + clip(0,255,tmp) + 1) >> 1);
#endif
              }
            }
          }

        }
        /* Vertical 1/2-pel precision, horizontal 1/4-pel precision */
        else if (yFrac == 2) {
          /* Vertical interpolation */
          for (i = -2; i < BLK_SIZE+3; i++) {
            for (j = 0; j < BLK_SIZE; j++) {
              tmp = (
                ONEFOURTH1*(refPtr[ j   *refWidth + i] +
                            refPtr[(j+1)*refWidth + i]) +
                ONEFOURTH2*(refPtr[(j-1)*refWidth + i] +
                            refPtr[(j+2)*refWidth + i]) +
                ONEFOURTH3*(refPtr[(j-2)*refWidth + i] +
                            refPtr[(j+3)*refWidth + i]));
              block[2+i][j] = tmp;
            }
          }
          /* Horizontal interpolation */
          for (i = 0; i < BLK_SIZE;  i++) {
            for (j = 0; j < BLK_SIZE;  j++) {
              tmp2 = (
                ONEFOURTH1*((int32)(block[2+i  ][j] + block[2+i+1][j])) +
                ONEFOURTH2*((int32)(block[2+i-1][j] + block[2+i+2][j])) +
                ONEFOURTH3*((int32)(block[2+i-2][j] + block[2+i+3][j])) + 512
              ) >> 10;
#ifdef USE_CLIPBUF
              predPtr[j][i] = clipBufPtr[tmp2];
#else
              predPtr[j][i] = (u_int8) clip(0,255,tmp2);
#endif
            }
          }
          /* Linear interp. */
          colIdx = 2 + (xFrac >> 1);
          for (i = 0; i < BLK_SIZE;  i++) {
            for (j = 0; j < BLK_SIZE;  j++) {
              tmp = (block[colIdx+i][j] + 16) >> 5;
#ifdef USE_CLIPBUF
              predPtr[j][i] = (u_int8) ((predPtr[j][i] + clipBufPtr[tmp] + 1) >> 1);
#else
              predPtr[j][i] = (u_int8) ((predPtr[j][i] + clip(0,255,tmp) + 1) >> 1);
#endif
            }
          }

        }
        /* Horizontal&vertical 1/4-pel precision -> diagonal interpolation */
        else {
          /* Vertical interpolation */
          colIdx = xFrac >> 1;
          for (j = 0; j < BLK_SIZE; j++) {
            for (i = 0; i < BLK_SIZE; i++) {
              tmp = (
                ONEFOURTH1*(refPtr[ j   *refWidth + i+colIdx] +
                            refPtr[(j+1)*refWidth + i+colIdx]) +
                ONEFOURTH2*(refPtr[(j-1)*refWidth + i+colIdx] +
                            refPtr[(j+2)*refWidth + i+colIdx]) +
                ONEFOURTH3*(refPtr[(j-2)*refWidth + i+colIdx] +
                            refPtr[(j+3)*refWidth + i+colIdx]) + 16
              ) >> 5;
#ifdef USE_CLIPBUF
              predPtr[j][i] = clipBufPtr[tmp];
#else
              predPtr[j][i] = (u_int8) clip(0,255,tmp);
#endif
            }
          }
          /* Horizontal interpolation */
          lineIdx = yFrac >> 1;
          for (j = 0; j < BLK_SIZE; j++) {
            for (i = 0; i < BLK_SIZE; i++) {
              tmp = (
                ONEFOURTH1*(refPtr[(j+lineIdx)*refWidth + i  ] +
                            refPtr[(j+lineIdx)*refWidth + i+1]) +
                ONEFOURTH2*(refPtr[(j+lineIdx)*refWidth + i-1] +
                            refPtr[(j+lineIdx)*refWidth + i+2]) +
                ONEFOURTH3*(refPtr[(j+lineIdx)*refWidth + i-2] +
                            refPtr[(j+lineIdx)*refWidth + i+3]) + 16
              ) >> 5;
#ifdef USE_CLIPBUF
              predPtr[j][i] = (u_int8) ((predPtr[j][i] + clipBufPtr[tmp] + 1) >> 1);
#else
              predPtr[j][i] = (u_int8) ((predPtr[j][i] + clip(0,255,tmp) + 1) >> 1);
#endif
            }
          }

        }
      }


      /*
       * Get chroma prediction
       */

      /* Bilinear interpolation coefficients */
      coef0 = (8-(xPos&7)) * (8-(yPos&7));
      coef1 = (xPos&7)     * (8-(yPos&7));
      coef2 = (8-(xPos&7)) * (yPos&7);
      coef3 = (xPos&7)     * (yPos&7);

      /* Chroma vectors have 1/8 chroma pel precision */
      xInt  = xPos>>3;
      yInt  = yPos>>3;

      if (xInt >= 0 && xInt < picWidthC-BLK_SIZE/2 &&
          yInt >= 0 && yInt < picHeightC-BLK_SIZE/2)
      {
        refC[0] = &ref->u[yInt*picWidthC+xInt];
        refC[1] = &ref->v[yInt*picWidthC+xInt];
        refWidth = picWidthC;
      }
      else {
        getRefAreaC(ref->u, refArea    , picWidthC, picHeightC, xInt, yInt);
        getRefAreaC(ref->v, refArea+3*3, picWidthC, picHeightC, xInt, yInt);
        refC[0] = refArea;
        refC[1] = refArea+3*3;
        refWidth = 3;
      }
      for (c = 0; c < 2; c++) {  /* 2 chroma components */
        for (j = 0; j < BLK_SIZE/2;  j++) {
          for (i = 0; i < BLK_SIZE/2;  i++) {
            tmp = (coef0 * refC[c][(j  )*refWidth + i  ] +
                   coef1 * refC[c][(j  )*refWidth + i+1] +
                   coef2 * refC[c][(j+1)*refWidth + i  ] +
                   coef3 * refC[c][(j+1)*refWidth + i+1] + 32) >> 6;
            predC[blkIdxY*(BLK_SIZE/2)+j][c*(MBK_SIZE/2)+blkIdxX*(BLK_SIZE/2)+i] = (u_int8) tmp;
          }
        }
      }

    }
  }

}


#endif    /* End of #ifndef AVC_ARM_ASSEMBLY */


/*
 *
 * mcpFillPred:
 *
 * Parameters:
 *      predY                 Return pointer for predicted luma pixels
 *      predC                 Return pointer for predicted chroma pixels
 *
 * Function:
 *      Fill prediction with constant value (128)
 *
 * Returns:
 *      -
 */
void mcpFillPred(u_int8 predY[MBK_SIZE][MBK_SIZE],
                 u_int8 predC[MBK_SIZE/2][MBK_SIZE])
{
  int i, j;

  for (j = 0; j < MBK_SIZE; j++)
    for (i = 0; i < MBK_SIZE; i++)
      predY[j][i] = 128;

  for (j = 0; j < MBK_SIZE/2; j++)
    for (i = 0; i < MBK_SIZE; i++)
      predC[j][i] = 128;
}
