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
 * motest.c
 *
 * Contains:
 *    Motion estimation with selection of all modes.
 *    Acceleration will be performed at 2 diffferent levels. The lower level
 *    is to speedup the block matching. The upper level is to exploit the 
 *    correlation among different modes and neighboring blocks.
 *
 */

#include <limits.h>
#include <string.h>
#include "globals.h"
#include "debug.h"
#include "vlcutility.h"
#include "transform.h"
#include "motcomp.h"
#include "meutility.h"
#include "macroblock.h"
#include "stream.h"
#ifdef ENABLE_SEARCH_WINDOW
#include "searchwin.h"
#endif

#ifdef MOTION_ANALYSIS
extern motVec_s *dbgMotVecModes[10];
#endif

//#define DBG_STATISTICS

#define CENTER_PRED_MV              0
#define CENTER_LARGER_BLOCK_MV      1

#ifdef DBG_STATISTICS
int boundaryCount0 = 0;
int boundaryCount1 = 0;
int boundaryCount2 = 0;
int boundaryCount3 = 0;
int boundaryCount4 = 0;
int totalCount = 0;
int betterMatch = 0;
int skippedCount = 0;
int unskippedCount = 0;
#endif

#define SAD_NOT_AVAILABLE     0
#define SAD_AVAILABLE         1
#define MAX_SUB_MB_RECT_SIZE  576


/*
*
* mesMultiStepSearch:
*
* Parameters:
*      blk                 Buffer pointers and parameters related to the block
*      pMeProf             Parameters for controlling ME
*      bestVec             Best vector so far, will be updated at return
*      bestSad             Minimum SAD so far, will be updated at return
*      neighborSads        SAD of neighboring positions
*
* Function:
*      Perform integer motion vector. Support sparse search. N-step search
*      is the special case. 
*
* Returns:
*      Return values are in bestVec and bestSad.
*
*/
static int mesMultiStepSearch(mbPart_s    *mbPart, 
                              meProfile_s *pMeProf, 
                              motVec_s    *bestVec,
                              int32       *bestSad,
                              int32       *neighborSads)
{
  int startX, stopX, startY, stopY;
  int subsamplingStep, offset, returnStat;
  lowComplexProf3_s *plc3 = &(pMeProf->lc3);
  
  subsamplingStep = pMeProf->subsampling;
  
  // sparse search based on the step size, subsamplingStep must be 2's power
  // subsamplingStep was in quater pixel precision, we shift by 1/2 step
  offset = (subsamplingStep >> 3) * 4;
  
  startX = mbPart->p0[0];  startY = mbPart->p0[1];
  stopX  = mbPart->p1[0];  stopY  = mbPart->p1[1];
  
  startX += offset;
  stopX  -= offset;
  
  startY += offset;
  stopY  -= offset;
  
  
  if ( (plc3->low_complex_prof3) && (plc3->spec_search_pos)    ) {
    // do_16x8 must be 1 for 16x16 mode, and might become 0 when
    // handling 16x8 or 8x16 mode
    if (plc3->do_16x8)
      matchBlockLong_MultiStep(mbPart, startX, stopX, startY, stopY, subsamplingStep, bestVec, bestSad);
  }
  else
    matchBlockLong(mbPart, startX, stopX, startY, stopY, subsamplingStep, bestVec, bestSad, plc3->low_complex_prof3);
  
  // refinement step-wise search to get the finer step size
  returnStat = SAD_NOT_AVAILABLE;
  if (mbPart->profile == PROF_CODING_SPEED)
  {
    // we do one step refinement and record the SADs at neighboring positions
    if (subsamplingStep > 4)
    {
      neighborSads[0] = *bestSad;
      // neighborSads[0] has been used above
      if (matchBlockLocal4(mbPart, 4, bestVec, bestSad, neighborSads + 1))
        // the best location has changed
        returnStat = SAD_AVAILABLE;
    }
  }
  else
  {
    while (subsamplingStep > 4)
    {
      // perform refinement search
      subsamplingStep >>= 1;          // should always be 4 now
      matchBlockDiamond(mbPart, subsamplingStep, bestVec, bestSad, 0);
    }
    returnStat = SAD_NOT_AVAILABLE;
  }
  
  return returnStat;
}


/*
 *
 * mesGradientSearch:
 *
 * Parameters:
 *      blk                 Buffer pointers and parameters related to the block
 *      pMeProf             Parameters for controlling ME
 *      bestVec             Best vector so far, will be updated at return
 *      bestSad             Minimum SAD so far, will be updated at return
 *
 * Function:
 *      Perform gradient search for integer motion vector. This is used as
 *      the refinement search stage if the best motion vector is located
 *      at the boundary of the search window.
 *
 * Returns:
 *      Return values are in bestVec and bestSad.
 *
 */
void mesGradientSearch(mbPart_s    *mbPart, 
                       meProfile_s *pMeProf, 
                       motVec_s    *bestVec,
                       int32       *bestSad)
{
  int i, loopCount;
  int p0[2], p1[2];

  
  p0[0] = mbPart->p0[0];
  p1[0] = mbPart->p1[0];
  p0[1] = mbPart->p0[1];
  p1[1] = mbPart->p1[1];
  
  loopCount = 0;
  while ((bestVec->x == p0[0]) || (bestVec->x == p1[0]) ||
    (bestVec->y == p0[1]) || (bestVec->y == p1[1]))
  {
    int searchDir[2], vec[2], tmp;
    motVec_s prevBestVec;
    
    vec[0] = bestVec->x;
    vec[1] = bestVec->y;
    
    for (i = 0; i < 2; i ++) {
      searchDir[i] = 0;
      if (vec[i] == p1[i])      // upper boundary
        searchDir[i] = 1;
      else if (vec[i] == p0[i])    // lower boundary
        searchDir[i] = -1;
    }
    
    if ((searchDir[0] != 0) && (searchDir[1] != 0)) {
      // this is the corner
      p0[0] = bestVec->x - searchDir[0] * 4;
      p1[0] = bestVec->x + searchDir[0] * 12;
      p0[1] = bestVec->y - searchDir[1] * 4;
      p1[1] = bestVec->y + searchDir[1] * 12;
    }
    else
    {
      // this is at least 1 pixel away from the corner
      if (searchDir[0] != 0) {
        p0[0] = bestVec->x + searchDir[0] * 4;
        p1[0] = bestVec->x + searchDir[0] * 20;
        p0[1] = bestVec->y - 8;  
        p1[1] = bestVec->y + 8; 
      }
      else
      {
        p0[0] = bestVec->x - 8;  
        p1[0] = bestVec->x + 8;  
        p0[1] = bestVec->y + searchDir[1] * 4;
        p1[1] = bestVec->y + searchDir[1] * 20;
      }
    }
    for (i = 0; i < 2; i ++) {
      if (p0[i] > p1[i]) {
        tmp   = p0[i];
        p0[i] = p1[i]; 
        p1[i] = tmp;
      }
      if (p0[i] < pMeProf->vecLmt0[i])
        p0[i] = pMeProf->vecLmt0[i];
      if (p1[i] >  pMeProf->vecLmt1[i])
        p1[i] = pMeProf->vecLmt1[i];
    }
    
    prevBestVec = *bestVec;
    
    matchBlockLong(mbPart, p0[0], p1[0], p0[1], p1[1], 4, bestVec, bestSad, pMeProf->lc3.low_complex_prof3);
    
    // bestVec could be a new value
    loopCount ++;
    if (((prevBestVec.x == bestVec->x) && (prevBestVec.y == bestVec->y)) ||
      (loopCount == 3))
    {
#ifdef DBG_STATISTICS
      if (loopCount == 3)
        boundaryCount3 ++;
#endif
      break;
    }
  }
}


static int32 mySad2(mbPart_s *mbPart, int vecX, int vecY)
{
  int32 currSad;
  int lambda;
  

  /* Take into account number fo bits spent for motion vector */
  lambda = mbPart->lambdaCoarse;
  currSad = (int32)lambda * (mbPart->vlcMvBitsX[vecX] + mbPart->vlcMvBitsY[vecY]);
  
  if (mbPart->mode == MOT_16x16)
  {
    if ((vecY | vecX) == 0)
      currSad -= lambda * ZERO_VEC_SAD;
  }
  
  /* Accumulate sad until no pels left or sad is worse than best so far */
  currSad = findSAD2(mbPart->orig, mbPart->ref, mbPart->refWidth, 
    mbPart->width, mbPart->height, vecX, vecY, currSad, INT_MAX);
  
  return currSad;
}


#define NO_HALF_PRED        -128
#define NOT_REAL_SAD        -4096

// estimate the half pixel location from 5 SADs
static int mesPredictHalfPixel(mbPart_s *mbPart, 
                               int32 *neighborSads,
                               int32 *halfPixelSads,
                               motVec_s *bestVec,
                               int32 *bestSad,
                               int *direction)
{
  int i, idx, x, y;
  int32 centerSad;
  int whoIsLarger[2], center[2];
  

  // estimate at x direction
  for (i = 0; i < 9; i ++)
    halfPixelSads[i] = NOT_REAL_SAD;
  
  halfPixelSads[4] = *bestSad;
  center[0] = bestVec->x;
  center[1] = bestVec->y;
  centerSad = *bestSad;
  
  // characterize the data and perform 1-D estimation
  for (i = 0; i < 2; i ++) {
    direction[i] = NO_HALF_PRED;
    
    if (neighborSads[1 + i] >= neighborSads[3 + i])
    {
      whoIsLarger[i] = 1;
    }
    else
    {
      whoIsLarger[i] = -1;
    }
    
    if (i == 0)    // x direction
    {
      x = whoIsLarger[0];
      y = 0;
      idx = 3 + 1 + x;
      x *= 2;
    }
    else          // y direction
    {
      x = 0;
      y = whoIsLarger[1];
      idx = (1 + y) * 3 + 1;
      y *= 2;
    }
    
    halfPixelSads[idx] = mySad2(mbPart, center[0] + x, center[1] + y);
    
    direction[i] = 0;
    if (halfPixelSads[idx] < *bestSad)
    {
      *bestSad = halfPixelSads[idx];
      bestVec->x = (int16) (center[0] + x);
      bestVec->y = (int16) (center[1] + y);
      direction[i] = whoIsLarger[i];
    }
  }
  
  // let's find out how confident we are
  if ((direction[1] != NO_HALF_PRED) && (direction[1] != NO_HALF_PRED)) {
    if ((direction[0] != 0) && (direction[1] != 0)) {
      // predict a diagonal half-pixel point, very un-reliable
      int candidate;
      int x0, y0;
      
      // diagonal search, 
      x0 = direction[0];
      y0 = direction[1];
      
      idx = (1 + y0) * 3 + 1 + x0;
      x0 *= 2;
      y0 *= 2;
      halfPixelSads[idx] = mySad2(mbPart, center[0] + x0, center[1] + y0);
      
      candidate = 0;
      if (halfPixelSads[idx] < *bestSad)
      {
        *bestSad = halfPixelSads[idx];
        bestVec->x = (int16) (center[0] + x0);
        bestVec->y = (int16) (center[1] + y0);
        candidate = 1;
      }
    }
  }
  
  return (direction[0] != NO_HALF_PRED) && (direction[1] != NO_HALF_PRED);
}


#ifdef DBG_STATISTICS
static int totalVecCount = 0;
static int nonFastHalfPixel = 0;
static int normErrCount[7] = { 0, 0, 0, 0, 0, 0, 0};
static int diagErrCounts[4][7] = { {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}, {0,0,0,0,0,0,0}};
static int badErrCount = 0;
static int normHitCount[7] = { 0, 0, 0, 0, 0, 0, 0};
static int diagHitCount = 0;
static int nonCounts[5][5] = 
{
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
};
#endif


/*
 * mesFindMotionBlock_fast:
 *
 * Parameters:
 *      blk                 Buffer pointers and parameters related to the block
 *      pMeProf             Parameters for controlling ME
 *      retSad              The minimum SAD of the block, for the best MV
 *
 * Function:
 *      Find the best motion vector for 1 block, of any possible size
 *
 *      Function is used only in low complexity mode 3
 * Returns:
 *      Best motion vector
 */
static motVec_s mesFindMotionBlock_fast(mbPart_s *mbPart,
                                        meProfile_s   *pMeProf,
                                        int32         *retSad)
{
  motVec_s bestVec, myBestVec;
  int32 bestSad, sad0;
  int32 neighborSads[5], fastHalfPixel;
  lowComplexProf3_s *plc3 = mbPart->plc3;
  int do_qpel = 0;
  int32 old_bestSad, change_bestSad;

  
  // y has been upsampled
  bestVec.x = 0;
  bestVec.y = 0;
  
  // SAD for zero vector
  sad0 = findSadPT(mbPart, 0, 0, INT_MAX);
  bestSad = sad0;
  
  // SAD for predicted vector
  if ((mbPart->estVec4[0] | mbPart->estVec4[1]) != 0) {
    int estMvX, estMvY;
    int tmpSad;
    
    estMvX = mbPart->estVec4[0];
    estMvY = mbPart->estVec4[1];
    
    // Although it could be checked again if it is in the search range,
    // but having a check up-front can speedup the speed, 
    // in sparse search, this could be an additional check point
    tmpSad = findSadPT(mbPart, estMvX, estMvY, bestSad);
    
    if (tmpSad < bestSad) {
      bestSad = tmpSad;
      bestVec.x = (int16) estMvX;
      bestVec.y = (int16) estMvY;
      
#ifdef DBG_STATISTICS
      boundaryCount4 ++;
#endif
    }
  }
  
  // Integer pel search
  fastHalfPixel = mesMultiStepSearch
    (mbPart, pMeProf, & bestVec, & bestSad, neighborSads);
  
  myBestVec = bestVec;
  
  // is bestVec (0, 0), but (0, 0) not in the search range?
  // this refinement search at the center seems to give better performance 
  // at low bit rate, but not high bit rate, 
  if ((bestVec.x == 0) && (bestVec.y == 0) &&
    ((mbPart->p0[0] >= 8) || (mbPart->p1[0] <= -8)) &&
    ((mbPart->p0[1] >= 8) || (mbPart->p1[1] <= -8))) {
    // I do not like your search ranges, (0, 0) not in the range, but better!
    mbPart->p0[0] = -8;
    mbPart->p1[0] =  8;
    mbPart->p0[1] = -8;
    mbPart->p1[1] =  8;
    
    // Integer pel search
    mesMultiStepSearch(mbPart, pMeProf, & bestVec, & bestSad, neighborSads);
    
#ifdef DBG_STATISTICS
    boundaryCount0 ++;
#endif
  }
  
#ifdef DBG_STATISTICS
  totalCount ++;
#endif
  
  mesGradientSearch(mbPart, pMeProf, & bestVec, & bestSad);
  
  old_bestSad=bestSad;
  
  if ((mbPart->profile == PROF_CODING_SPEED) &&
    (myBestVec.x == bestVec.x && myBestVec.y == bestVec.y && fastHalfPixel)) {
    // we do fast search only when there are 5 SADs available, and 
    // minimal SAD sits in the middle, seems to be still very probable
    motVec_s oldBestVec;
    int direction[2];
    int32 mySad, oldSad;
    int32 halfPixelSads[3][3];
    
    // 1/2 and 1/4 pixel search
    oldBestVec = bestVec;
    oldSad = bestSad;
    mySad  = bestSad;
    
    fastHalfPixel = mesPredictHalfPixel
      (mbPart, neighborSads, (int32 *) halfPixelSads, & bestVec, & bestSad, direction);
    
  }
  
  if (! fastHalfPixel)
    matchBlockDiamond(mbPart, 2, & bestVec, & bestSad, 0);
  
  change_bestSad=old_bestSad-bestSad;
  
  do_qpel += (change_bestSad>plc3->thre_change[plc3->mode]);
  
  if (plc3->mode == MOT_16x16) {
    do_qpel += 1;
  } 
  else {    
    do_qpel += plc3->do_qpel_mode_2_3;
  }
  
  old_bestSad = bestSad;
  
  if (do_qpel >= 2)       // do quarter pel when **both** heuristics are satisfied
  {
    
    if (mbPart->profile == PROF_CODING_SPEED)
      matchBlockDiamond(mbPart, 1, & bestVec, & bestSad, 0);
    else
    {
      bestSad = INT_MAX; 
      matchBlockDiamond(mbPart, 1, & bestVec, & bestSad, 1);
    }
    
    
  }
  
  change_bestSad = old_bestSad-bestSad;
  
  if (  (  plc3->qp > TH_QP2 ) && ( (plc3->mode == MOT_16x8) || (plc3->mode == MOT_8x16) )   ) {
    if  (plc3->cnt != plc3->old_cnt) {
      
      // diff mb
      plc3->old_cnt = plc3->cnt;
      
      if ( change_bestSad < TH_QPEL )
        plc3->do_qpel_mode_2_3 = 0;
    }
  }
  
  *retSad = bestSad;
  
  return bestVec;
}


/*
* mesFindMotionBlock_fast_fast:
*
* Parameters:
*      blk                 Buffer pointers and parameters related to the block
*      pMeProf             Parameters for controlling ME
*      retSad              The minimum SAD of the block, for the best MV
*
* Function:
*      Find the best motion vector for 1 block, of any possible size
*
*      Function is used only in low complexity mode 3
* Returns:
*      Best motion vector
*/
static motVec_s mesFindMotionBlock_fast_fast(mbPart_s *mbPart,
                                             meProfile_s   *pMeProf,
                                             int32         *retSad)
{
  motVec_s bestVec, myBestVec,diffVec; //myBestVec holds the integer best
  int32 bestSad, sad0;
  int32 neighborSads[5], fastHalfPixel;
  int16 search_indx;
  lowComplexProf3_s *plc3 = mbPart->plc3;
  int do_qpel = 0;
  int32 old_bestSad, change_bestSad;

  
  // y has been upsampled
  bestVec.x = 0;
  bestVec.y = 0;
  
  // SAD for zero vector
  sad0 = findSadPT(mbPart, 0, 0, INT_MAX);
  bestSad = sad0;
  
  // SAD for predicted vector
  if ((mbPart->estVec4[0] | mbPart->estVec4[1]) != 0) {
    int estMvX, estMvY;
    int tmpSad;
    
    estMvX = mbPart->estVec4[0];
    estMvY = mbPart->estVec4[1];
    
    // Although it could be checked again if it is in the search range,
    // but having a check up-front can speedup the speed, 
    // in sparse search, this could be an additional check point
    tmpSad = findSadPT(mbPart, estMvX, estMvY, bestSad);
    
    if (tmpSad < bestSad) {
      bestSad = tmpSad;
      bestVec.x = (int16) estMvX;
      bestVec.y = (int16) estMvY;
      
#ifdef DBG_STATISTICS
      boundaryCount4 ++;
#endif
    }
  }
  
  // Integer pel search
  fastHalfPixel = mesMultiStepSearch
    (mbPart, pMeProf, & bestVec, & bestSad, neighborSads);
  
  myBestVec = bestVec;
  
  // is bestVec (0, 0), but (0, 0) not in the search range?
  // this refinement search at the center seems to give better performance 
  // at low bit rate, but not high bit rate, 
  if ((bestVec.x == 0) && (bestVec.y == 0) &&
    ((mbPart->p0[0] >= 8) || (mbPart->p1[0] <= -8)) &&
    ((mbPart->p0[1] >= 8) || (mbPart->p1[1] <= -8))) {
    // I do not like your search ranges, (0, 0) not in the range, but better!
    mbPart->p0[0] = -8;
    mbPart->p1[0] =  8;
    mbPart->p0[1] = -8;
    mbPart->p1[1] =  8;
    
    // Integer pel search
    mesMultiStepSearch(mbPart, pMeProf, & bestVec, & bestSad, neighborSads);
    
#ifdef DBG_STATISTICS
    boundaryCount0 ++;
#endif
  }
  
#ifdef DBG_STATISTICS
  totalCount ++;
#endif
  
  mesGradientSearch(mbPart, pMeProf, & bestVec, & bestSad);
  
  old_bestSad=bestSad;
  
  
  matchBlockDiamond(mbPart, 2, & bestVec, & bestSad, 0);
  
  change_bestSad=old_bestSad-bestSad;
  
  do_qpel += (change_bestSad>plc3->thre_change[plc3->mode]);
  
  diffVec.x = (int16)( myBestVec.x - bestVec.x) ;
  diffVec.y = (int16)( myBestVec.y - bestVec.y) ;
  
  if (plc3->mode == MOT_16x16) {
    do_qpel += 1;
  } 
  else {    
    do_qpel += plc3->do_qpel_mode_2_3;
  }
  
  old_bestSad = bestSad;
  if(plc3->useProf4 == 1) {
    if(diffVec.x == 0 && diffVec.y == 0) {   
      if (do_qpel >= 2){       // do quarter pel when **both** heuristics are satisfied
        matchBlockDiamond(mbPart, 1, & bestVec, & bestSad, 0);
        plc3->numQPEL+=6;
      }
    }
    else
    {
      search_indx = (int16)(((diffVec.x <0 ) << 3) + ((diffVec.x == 0)<<2) + ((diffVec.y <0 ) << 1) + ((diffVec.y == 0)));
      plc3->numQPEL+=3;
      if (do_qpel >= 2)       // do quarter pel when **both** heuristics are satisfied
        matchBlockDiamond_fast(mbPart, 1, & bestVec, & bestSad, 0,search_indx);
    }
  }
  else
  {
    if (do_qpel >= 2)       // do quarter pel when **both** heuristics are satisfied
    {
      // do quarter pel when **both** heuristics are satisfied
      matchBlockDiamond(mbPart, 1, & bestVec, & bestSad, 0);    
      plc3->numQPEL+=6;    
      
    }
  }
  
  change_bestSad = old_bestSad-bestSad;
  
  if (  (  plc3->qp > TH_QP2 ) && ( (plc3->mode == MOT_16x8) || (plc3->mode == MOT_8x16) )   ) {
    if  (plc3->cnt != plc3->old_cnt) {
      
      // diff mb
      plc3->old_cnt = plc3->cnt;
      
      if ( change_bestSad < TH_QPEL )
        plc3->do_qpel_mode_2_3 = 0;
    }
  }
  
  *retSad = bestSad;
  
  return bestVec;
}


/*
 * mesFindMotionBlock:
 *
 * Parameters:
 *      blk                 Buffer pointers and parameters related to the block
 *      pMeProf             Parameters for controlling ME
 *      retSad              The minimum SAD of the block, for the best MV
 *
 * Function:
 *      Find the best motion vector for 1 block, of any possible size
 *
 * Returns:
 *      Best motion vector
 */
static motVec_s mesFindMotionBlock(mbPart_s    *mbPart, 
                                   meProfile_s *pMeProf, 
                                   int32       *retSad)
{
  motVec_s bestVec, myBestVec;
  int32 bestSad, sad0;
  int32 neighborSads[5], fastHalfPixel;
  

  // y has been upsampled
  bestVec.x = 0;
  bestVec.y = 0;
  
  // SAD for zero vector
  sad0 = findSadPT(mbPart, 0, 0, INT_MAX);
  bestSad = sad0;
  
  // SAD for predicted vector
  if ((mbPart->estVec4[0] | mbPart->estVec4[1]) != 0) {
    int estMvX, estMvY;
    int32 tmpSad;
    
    estMvX = mbPart->estVec4[0];
    estMvY = mbPart->estVec4[1];
    
    // Although it could be checked again if it is in the search range,
    // but having a check up-front can speedup the speed, 
    // in sparse search, this could be an additional check point
    tmpSad = findSadPT(mbPart, estMvX, estMvY, bestSad);
    
    if (tmpSad < bestSad)
    {
      bestSad = tmpSad;
      bestVec.x = (int16) estMvX;
      bestVec.y = (int16) estMvY;
      
#ifdef DBG_STATISTICS
      boundaryCount4 ++;
#endif
    }
  }
  
  // Integer pel search
  fastHalfPixel = mesMultiStepSearch
    (mbPart, pMeProf, & bestVec, & bestSad, neighborSads);
  
  myBestVec = bestVec;
  
  // is bestVec (0, 0), but (0, 0) not in the search range?
  // this refinement search at the center seems to give better performance 
  // at low bit rate, but not high bit rate, 
  if ((bestVec.x == 0) && (bestVec.y == 0) &&
    ((mbPart->p0[0] >= 8) || (mbPart->p1[0] <= -8)) &&
    ((mbPart->p0[1] >= 8) || (mbPart->p1[1] <= -8)))
  {
    meProfile_s origProf;
    
    origProf = *pMeProf;
    
    // I do not like your search ranges, (0, 0) not in the range, but better!
    mbPart->p0[0] = -8;
    mbPart->p1[0] =  8;
    mbPart->p0[1] = -8;
    mbPart->p1[1] =  8;
    
    // Integer pel search
    mesMultiStepSearch(mbPart, pMeProf, & bestVec, & bestSad, neighborSads);
    
#ifdef DBG_STATISTICS
    boundaryCount0 ++;
#endif
  }
  
#ifdef DBG_STATISTICS
  totalCount ++;
#endif
  
  mesGradientSearch(mbPart, pMeProf, & bestVec, & bestSad);
  
  if ((mbPart->profile == PROF_CODING_SPEED) &&
    (myBestVec.x == bestVec.x && myBestVec.y == bestVec.y && fastHalfPixel)) {
    // we do fast search only when there are 5 SADs available, and 
    // minimal SAD sits in the middle, seems to be still very probable
    motVec_s oldBestVec;
    int direction[2];
    int32 mySad, oldSad;
    int32 halfPixelSads[3][3];
    
    // 1/2 and 1/4 pixel search
    oldBestVec = bestVec;
    oldSad = bestSad;
    mySad  = bestSad;
    
    fastHalfPixel = mesPredictHalfPixel
      (mbPart, neighborSads, (int32 *) halfPixelSads, & bestVec, & bestSad, direction);
  }
  
  if (! fastHalfPixel)
    matchBlockDiamond(mbPart, 2, & bestVec, & bestSad, 0);
  
  if (mbPart->profile == PROF_CODING_SPEED)
    matchBlockDiamond(mbPart, 1, & bestVec, & bestSad, 0);
  else
  {
    bestSad = INT_MAX; 
    matchBlockDiamond(mbPart, 1, & bestVec, & bestSad, 1);
  }
  
  *retSad = bestSad;
  
  return bestVec;
}


/*
 * mesDetermineSearchRegion:
 *
 * Parameters:
 *
 * Function:
 *      Determine in which range the search should be performed. 
 *      The search center changes from MB to MB, but the size of the search 
 *      area will always be (2*range + 1) * (2*range + 1).
 *
 * Returns:
 *      -
 */
static void mesDetermineSearchRegion(meProfile_s  *pMeProf,
                                     motVec_s     *predVec,
                                     macroblock_s *pMb,
                                     mbPart_s     *mbPart)
{
  int i;
  int ctr[2], sizes[2], blkStart[2];
  int blkAddr;
#ifdef ENABLE_SEARCH_WINDOW
  searchWin_s *sWin = &pMeProf->sWin;
  int sWinLimits[2];
#endif
  

  blkAddr = mbPart->y0 * 4 + mbPart->x0;
  
  blkStart[0] = (pMb->idxX * BLK_PER_MB + mbPart->x0) * BLK_SIZE;
  blkStart[1] = (pMb->idxY * BLK_PER_MB + mbPart->y0) * BLK_SIZE;
  
  sizes[0] = mbPart->width;
  sizes[1] = mbPart->height;
  ctr[0]   = predVec->x;
  ctr[1]   = predVec->y;
  
#ifdef ENABLE_SEARCH_WINDOW
  if (sWin->useSearchWin) {
    sWinLimits[0] = sWin->srx - 2;
    sWinLimits[1] = sWin->sry - 2;
  }
#endif
  
  // i = 0 -> x, i = 1 -> y
  for (i = 0; i < 2; i ++) {
    int range;
    
    // lower and upper limits, convert to quarter pixel precision
    pMeProf->vecLmt0[i] = (int16) (4 * (pMeProf->area0[i] - blkStart[i]));
    pMeProf->vecLmt1[i] = (int16) (4 * (pMeProf->area1[i] - blkStart[i] - sizes[i]));
    
    if (i == 1) {
      /* Make sure we don't violate MV vertical range limitation */
      if (pMeProf->vecLmt0[i] < (-pMeProf->maxVerticalMvRange) * 4)
        pMeProf->vecLmt0[i] = (int16) ((-pMeProf->maxVerticalMvRange) * 4);
      if (pMeProf->vecLmt1[i] > (pMeProf->maxVerticalMvRange - 1) * 4)
        pMeProf->vecLmt1[i] = (int16) ((pMeProf->maxVerticalMvRange - 1) * 4);
    }
    
#ifdef ENABLE_SEARCH_WINDOW
    if (sWin->useSearchWin) {
      /* Stay within search window */
      int blkOffset = blkStart[i] & 15;
      if (pMeProf->vecLmt0[i] < -(sWinLimits[0] - blkOffset) * 4)
        pMeProf->vecLmt0[i] = -(sWinLimits[0] - blkOffset) * 4;
      if (pMeProf->vecLmt1[i] > (sWinLimits[0] + (16 - blkOffset - sizes[i])) * 4)
        pMeProf->vecLmt1[i] = (sWinLimits[0] + (16 - blkOffset - sizes[i])) * 4;
    }
#endif
    
    mbPart->estVec4[i] = (int16) ((ctr[i] + 2) & (~3));
    if (mbPart->estVec4[i] < pMeProf->vecLmt0[i])
      mbPart->estVec4[i] = (int16) (pMeProf->vecLmt0[i]);
    if (mbPart->estVec4[i] > pMeProf->vecLmt1[i])
      mbPart->estVec4[i] = (int16) (pMeProf->vecLmt1[i]);
    
    if (pMeProf->searchCtrFlag != CENTER_PRED_MV)
    {
      ctr[i] = (pMb->searchCtr[i] + ctr[i]) >> 1;
    }
    
    // Set nominal range of the motion, and the hard limits on the motion
    ctr[i] = (ctr[i] + 2) & (~3);
    
    range = ((pMeProf->vecLmt1[i] - pMeProf->vecLmt0[i]) >> 1) & ~3;
    if (range > mbPart->range)
      range = mbPart->range;
    
    // the search area will always be (2*range + 1) * (2*range + 1)
    mbPart->p0[i] = (int16) (ctr[i] - range);
    
    if (mbPart->p0[i] < pMeProf->vecLmt0[i])
      mbPart->p0[i] = pMeProf->vecLmt0[i];
    if ((mbPart->p0[i] + range * 2) > pMeProf->vecLmt1[i])
      mbPart->p0[i] = (int16) (pMeProf->vecLmt1[i] - 2 * range);
    
    mbPart->p1[i] = (int16) (mbPart->p0[i] + 2 * range);
    
    mbPart->vecLmt0[i] = pMeProf->vecLmt0[i];
    mbPart->vecLmt1[i] = pMeProf->vecLmt1[i];
  }
}


/*
 * mesBlockLazyMatch:
 *
 * Parameters:
 *      sadsPtr               Pointer to buffer storing SAD values
 *      mode                  Block mode
 *      bestLazyMode          Mode with the best match
 *
 * Function:
 *      Find the best match found so far. 
 *
 * Returns:
 *      Minimal SAD for the MB or sub-MB being predicted.
 */
int mesBlockLazyMatch(int16 *sadsPtr,
                      int   mode,
                      int   *bestLazyMode)
{
  int m;
  int32 bestSad, partSad;
  

  *bestLazyMode = MOT_16x16;
  bestSad = 0;
  
  // we address blkSADs as 1-D array here 
  switch (mode)
  {
  case MOT_4x4:
    bestSad = sadsPtr[0];
    for (m = MOT_16x8; m <= MOT_4x8; m ++)
    {
      sadsPtr += 16;
      partSad = sadsPtr[0];
      if (sadsPtr[0] < bestSad)
      {
        bestSad   = partSad;
        *bestLazyMode = m;
      }
    }
    break;
    
  case MOT_4x8:
    bestSad = (int32)sadsPtr[0] + sadsPtr[4];
    for (m = MOT_16x8; m <= MOT_8x8; m ++)
    {
      sadsPtr += 16;
      partSad = (int32)sadsPtr[0] + sadsPtr[4];
      if (partSad < bestSad)
      {
        bestSad   = partSad;
        *bestLazyMode = m;
      }
    }
    break;
    
  case MOT_8x4:
    bestSad = (int32)sadsPtr[0] + sadsPtr[1];
    for (m = MOT_16x8; m <= MOT_8x8; m ++)
    {
      sadsPtr += 16;
      partSad = (int32)sadsPtr[0] + sadsPtr[1];
      if (partSad < bestSad)
      {
        bestSad   = partSad;
        *bestLazyMode = m;
      }
    }
    break;
    
  case MOT_8x8:
    bestSad = (int32)sadsPtr[0] + sadsPtr[1] + sadsPtr[4] + sadsPtr[5];
    for (m = MOT_16x8; m <= MOT_8x16; m ++)
    {
      sadsPtr += 16;
      partSad = (int32)sadsPtr[0] + sadsPtr[1] + sadsPtr[4] + sadsPtr[5];
      if (partSad < bestSad)
      {
        bestSad   = partSad;
        *bestLazyMode = m;
      }
    }
    break;
    
  case MOT_8x16:
    bestSad  = (int32)sadsPtr[0] + sadsPtr[1] + sadsPtr[4]  + sadsPtr[5];
    bestSad += sadsPtr[8] + sadsPtr[9] + sadsPtr[12] + sadsPtr[13];
    break;
    
  case MOT_16x8:
    bestSad  = (int32)sadsPtr[0] + sadsPtr[1] + sadsPtr[2] + sadsPtr[3];
    bestSad += sadsPtr[4] + sadsPtr[5] + sadsPtr[6] + sadsPtr[7];
    break;
  }
  
  return bestSad;
}


/*
 * mesPrepareProfile:
 *
 * Parameters:
 *      pMeProf             Parameters for controlling ME
 *      pRefFrm             Reference frame buffer to provide frame information
 *      encPar              Encoding parameters (motion range, etc.)
 *      nRefFrames          Number of reference frames
 *
 * Function:
 *      Prepare the structure for controlling the ME. 
 *
 * Returns:
 *      -
 */
void mesPrepareProfile(meProfile_s *pMeProf, 
                       refFrmBuf_s *pRefFrm,
                       encParams_s *encPar,
                       int         nRefFrames)
{
  int i, j;
  

  // at least 1 reference frame
  pMeProf->area0[0] = pRefFrm->searchArea.x0;
  pMeProf->area1[0] = pRefFrm->searchArea.x1;
  pMeProf->area0[1] = pRefFrm->searchArea.y0;
  pMeProf->area1[1] = pRefFrm->searchArea.y1;
  
  // Hadamard transform is not used in MODE_DECISION_SIMPLE mode
#ifndef DISABLE_RDO
  pMeProf->hadamard = ! ((encPar->rdo & 0x0F) == MODE_DECISION_SIMPLE);
  pMeProf->profile  = 
    (encPar->profile << 4) | ((encPar->rdo & 0x0F) == MODE_DECISION_RDO);
#else
  pMeProf->hadamard = 1;
  pMeProf->profile  = encPar->profile << 4;
#endif
  
  pMeProf->interModeFlags = encPar->modeFlags;    // from MOT_16x16 to MOT_4x4
  
  pMeProf->goodEarlyMatch = 0;
  // for reference frame 0, MOT_16x16
  for (i = 0; i < 2; i ++)
    for (j = 0; j < 2; j ++)
      pMeProf->range[i][j] = (int16) (encPar->range * 4);
    
  // half range for other modes
  if (encPar->rangeMod & 1)
    for (j = 0; j < 2; j ++)
      pMeProf->range[1][j] >>= 1;
      
  // half range for other reference frames
  if (encPar->rangeMod & 2)
    for (i = 0; i < 2; i ++)
      pMeProf->range[i][1] >>= 1;
      
  for (i = 0; i < 2; i ++)
    for (j = 0; j < 2; j ++)
      if (pMeProf->range[i][j] < 16)        // scaled up by 4
        pMeProf->range[i][j] = 16;
    
  if ((pMeProf->profile >> 4) == PROF_CODING_SPEED)
  {
    pMeProf->searchCtrFlag = 0;
    pMeProf->pruneTreeFlag = 1;                   // 0 or 1
    pMeProf->pruneThUnit   = 5;
    pMeProf->subsampling   = 8;                     // 4, 8, 16
  }
  else
  {
    pMeProf->searchCtrFlag  = 0;
  
#ifndef DISABLE_RDO
    if ((encPar->rdo & 0x0F) == MODE_DECISION_RDO)
      pMeProf->pruneTreeFlag = 0;                 // 0 or 1
    else
#endif
      pMeProf->pruneTreeFlag = 1;                 // 0 or 1
    pMeProf->pruneThUnit    = 1;
  
    pMeProf->subsampling = 4;                     // 4, 8, 16
  }

  // can not support this feature if there are multiple reference frames
  if (nRefFrames > 1)
    pMeProf->pruneTreeFlag  = 0;                  // 0 or 1
}


int PrecomputeRefPointers(macroblock_s *pMb,
                          refFrmBuf_s  **refBufList, 
                          int          nRefFrames,   
                          u_int8       *refBlkPtrs[][16],
                          u_int16      *refPartSum[])
{
  int i, j;
  int refWidth;
  

  // pre-compute all the reference block pointers,  
  refWidth = refBufList[0]->yBufWidth;
  for (i = 0; i < nRefFrames; i ++) {
    u_int8 *refMbPtr;
    refFrmBuf_s *pRefFrm;
    
    pRefFrm = refBufList[i];
    refMbPtr = pRefFrm->y + (pMb->idxY * MBK_SIZE << 1) * refWidth + 
      (pMb->idxX * MBK_SIZE << 1);
    
    // refPartSum is not used that often, so only compute the MB pointer
    refPartSum[i] = pRefFrm->partSums + 
      (pMb->idxY * MBK_SIZE) * (refWidth >> 1) + (pMb->idxX * MBK_SIZE);
    
    for (j = 0; j < BLK_PER_MB * BLK_PER_MB; j ++) {
      int k;
      
      k = j % 4;
      
      refBlkPtrs[i][j] = refMbPtr + (k * BLK_SIZE << 1);
      if (k == 3)
        refMbPtr += refWidth * (BLK_SIZE << 1);
    }
  }
  
  return refWidth;
}


/*
 * mesBasicMode:
 *
 * Parameters:
 *      pMb                 Macroblock information
 *      pMeProf             Parameters for controlling ME
 *      mbPart              Define a region within macroblock
 *      refBlkPtrs          Pointers to blocks in the reference MB
 *      refPartSum          Partial sum of blocks in reference MB
 *      mode                Prediction mode, define prediction block size
 *      blkMvBits           Number of MV bits of this block
 *
 * Function:
 *      Search the best vectors for one of basic modes: 16x16, 16x8, 8x16, 
 *      8x8, 8x4, 4x8, 4x4. 
 *
 * Returns:
 *      Minimal SAD for the MB or sub-MB being predicted.
 */
static int mesBasicMode(macroblock_s *pMb, 
                        meProfile_s  *pMeProf,
                        mbPart_s     *mbPart, 
                        u_int8       **refBlkPtrs, 
                        u_int16      *refPartSum,
                        int          mode,
                        int          *blkMvBits)
{
  int bestLazyMode;
  int16 *blkSadsBuf;
  motVec_s predVec, bestVec;
  blkState_s *current;
  int32 mbPartSad;
  int mpBlkAddr;
  

  mpBlkAddr  = mbPart->y0 * BLK_PER_MB + mbPart->x0;
  current    = & pMb->current[mbPart->y0][mbPart->x0];
  
  blkSadsBuf = & pMb->blkSADs[current->ref][mode][0];
  predVec    = mcpFindPredMv(pMb, current->ref, mode, mpBlkAddr);
  
  mbPart->vlcMvBitsX = uvlcBitsSigned - predVec.x + 511;
  mbPart->vlcMvBitsY = uvlcBitsSigned - predVec.y + 511;
  
  // should we perform search at all?
  bestLazyMode = mode;
  mbPartSad    = 0;
  
  // perform this only for the last reference frame
  if (pMeProf->pruneTreeFlag && (mode > MOT_16x16)) {
    mbPartSad = mesBlockLazyMatch(
      & pMb->blkSADs[0][MOT_16x16][mpBlkAddr], mode, & bestLazyMode);
    
    if (mbPartSad >= ((int32)modeNumBlocks[mode] * pMeProf->pruneTreeTh))
      bestLazyMode = mode;               // set it to the original mode
    //else bestLazyMode should be set to be < mode
  }
  
  if (bestLazyMode == mode) {
    mesDetermineSearchRegion(pMeProf, & predVec, pMb, mbPart);
    
    mbPart->orig = & pMb->origY[mbPart->y0 * BLK_SIZE][mbPart->x0 * BLK_SIZE];
    
    // Motion block position in reference frame
    // y has been upsampled
    mbPart->ref  = refBlkPtrs[mpBlkAddr];
    
    if (mode <= MOT_8x8) {
      // SEA is only performed when size is 8x8 or up
      mbPart->partSum = (int *) pMb->partSums + mpBlkAddr;
      mbPart->refPartSum = refPartSum + 
#ifdef ENABLE_SEARCH_WINDOW
        (mbPart->y0 * BLK_SIZE) * ( /*mbPart->refWidth*/  mbPart->refPsWidth >> 1) +
#else
        (mbPart->y0 * BLK_SIZE) * (mbPart->refWidth >> 1) + 
#endif
        (mbPart->x0 * BLK_SIZE);
    }
    
    if(pMeProf->lc3.useProf4 == 1)
      bestVec = mesFindMotionBlock_fast_fast(mbPart, pMeProf, & mbPartSad );
    else if (pMeProf->lc3.low_complex_prof3)    
      bestVec = mesFindMotionBlock_fast(mbPart, pMeProf, & mbPartSad );
    else
      bestVec = mesFindMotionBlock(mbPart, pMeProf, & mbPartSad);
    
    // we will calculate the sad after Hadamard anyway
    if (pMeProf->hadamard)
      mbPartSad = findSATD4Blk(mbPart->orig, mbPart->ref, mbPart->refWidth, 
      mbPart->width, mbPart->height, bestVec.x, bestVec.y, & blkSadsBuf[mpBlkAddr]);
    else
      mbPartSad = findSAD4Blk(mbPart->orig, mbPart->ref, mbPart->refWidth, 
      mbPart->width, mbPart->height, bestVec.x, bestVec.y, & blkSadsBuf[mpBlkAddr]);
    
    /* Favor 16x16 blocks that have zero motion */
    if (mbPart->mode == MOT_16x16)
    {
      if ((bestVec.x | bestVec.y) == 0)
        mbPartSad -= mbPart->lambda * ZERO_VEC_SAD;
    }
  }
  else
  {
    // no additional search, but need to calculate SAD
    
    // get MV from skipMotVecs as the best vector, only need 1 MV as area
    // sharing the same vector in skipMotVecs always larger than size of 
    // current partition, ME is from large to small partitions.
    // do not need to copy blkSADs and skipMotVecs to the current mode, 
    // as blkSADs of the current mode has been set to a large value, 
    // current mode will never be picked as a replacement.
    if (bestLazyMode < MOT_8x8)
      bestVec = pMb->modeMvRef[bestLazyMode][mpBlkAddr].mv;
    else
      bestVec = pMb->skipMVs[bestLazyMode - MOT_8x8][mpBlkAddr];
  }
  
  // only need to copy this one position, others will be filled later
  current[0].mv = bestVec;
  
  // add the motion vector to the overall SAD
  *blkMvBits = mbPart->vlcMvBitsX[bestVec.x] + mbPart->vlcMvBitsY[bestVec.y];
  mbPartSad += (int32)mbPart->lambda * (*blkMvBits);
  
  return mbPartSad;
}


int encoRecoBlock(u_int8 origBlk[][MBK_SIZE], 
                  u_int8 predBlk[][MBK_SIZE], 
                  int    coeff[BLK_SIZE][BLK_SIZE],
                  u_int8 *reco, 
                  int    recoWidth, 
                  int    picType,
                  int    qp);


#ifndef DISABLE_RDO

/*
 * mesMbPartCost:
 *
 * Parameters:
 *      pMb                 Macroblock information
 *      refBlkPtrs          Pointers to blocks in the reference MB
 *      refWidth            Reference buffer width
 *      mpX0                Addr of 1st 4x4 block, X
 *      mpY0                Addr of 1st 4x4 block, Y
 *      mbPartW             Width of the MB partition, in 4x4 blocks
 *      mbPartH             Height of the MB partition, in 4x4 blocks
 *      pMse                For getting the MSE
 *
 * Function:
 *      Evaluate the cost of encoding the MB partition. 
 *
 * Returns:
 *      Number of bits spent on encoding the MB partition.
 */
int mesMbPartCost(macroblock_s *pMb, 
                  u_int8       *refBlkPtrs[16], 
                  int          refWidth,
                  int          mpX0, 
                  int          mpY0, 
                  int          mbPartW, 
                  int          mbPartH,
                  int          *pMse)
{
  int i, j, bits, mse, numCoefs, numNonZeroBlks, nonZero;
  u_int8 predBlk[4][16], reco[16];
  int coeff[4][4];

  
  bits = 0;
  mse  = 0;
  numNonZeroBlks = 0;
  
  for (j = mpY0; j < mpY0 + mbPartH; j ++) {
    for (i = mpX0; i < mpX0 + mbPartW; i ++) {
      u_int8 *origBlk, *refBlk;
      blkState_s *blkInfo;
      
      if (mbPartH + mbPartW == 4)         // MOT_8x8
        blkInfo = & pMb->current[j][i];
      else
        blkInfo = & pMb->current[mpY0][mpX0];
      
      origBlk = & pMb->origY[j * BLK_SIZE][i * BLK_SIZE];
      
      // get the quarter-pixel interpolated luminance predictor
      refBlk = refBlkPtrs[j * 4 + i] + (blkInfo->mv.y >> 1) * refWidth + (blkInfo->mv.x >> 1);
      
      mcpGetQuarterPixels(refBlk, refWidth, blkInfo->mv.x, blkInfo->mv.y, 4, 4, predBlk);
      
      nonZero = encoRecoBlock((u_int8 (*)[MBK_SIZE]) origBlk, predBlk, coeff, reco, 4, SLICE_P, pMb->qp);
      
      if (nonZero)
        numNonZeroBlks ++;
      
      mse += CalculateSsd(origBlk, MBK_SIZE, reco, 4, BLK_SIZE, BLK_SIZE);
      
      bibInit(& pMb->mbBs);
      
      bits += streamSend4x4Blk(& pMb->mbBs,
        pMb, 1, COMP_LUMA, i, j, 
        coeff, BLK_CAT_Y, & numCoefs);
      
      blkInfo->numLumaCoefs = (int8) numCoefs;
    }
  }
  
  if (numNonZeroBlks == 0)
    bits = mbPartH * mbPartW;
  
  *pMse = mse;
  
  return bits;
}

#endif


/*
 * checkSubMbRectSize:
 *
 * Parameters:
 *      current             State of blocks of current MB
 *      subMbMode           Sub-macroblock mode (8x8, 4x8, 4x4)
 *      mpX0                Sub-macroblock X index within MB
 *      mpY0                Sub-macroblock Y index within MB
 *
 * Function:
 *      Check whether motion vectors for the current sub-macroblock
 *      conform to the AVC/H.264 standard's rect size restriction.
 *
 * Returns:
 *      1 for vectors ok, 0 for vectors not ok.
 */
static int checkSubMbRectSize(blkState_s current[4][4], int subMbMode,
                              int mpX0, int mpY0)
{
  blkState_s (*curr)[BLK_PER_MB];
  int minX, maxX, minY, maxY;
  int vecDiffX, vecDiffY;
  int rectSize;
  int i, j;
  

  curr = (blkState_s (*)[BLK_PER_MB])&current[mpY0][mpX0];
  
  switch (subMbMode) {
  case P_L0_8x4:
    vecDiffX = abs((curr[0][0].mv.x>>2) - (curr[1][0].mv.x>>2));
    vecDiffY = abs((curr[0][0].mv.y>>2) - ((curr[1][0].mv.y>>2) + BLK_SIZE));
    rectSize = (vecDiffX + 2*BLK_SIZE + 6) * (vecDiffY + BLK_SIZE + 6);
    break;
  case P_L0_4x8:
    vecDiffX = abs((curr[0][0].mv.x>>2) - ((curr[0][1].mv.x>>2) + BLK_SIZE));
    vecDiffY = abs((curr[0][0].mv.y>>2) - (curr[0][1].mv.y>>2));
    rectSize = (vecDiffX + BLK_SIZE + 6) * (vecDiffY + 2*BLK_SIZE + 6);
    break;
  case P_L0_4x4:
    minX = minY = 32767;
    maxX = maxY = -32768;
    for (j = 0; j < BLK_PER_MB/2; j++) {
      for (i = 0; i < BLK_PER_MB/2; i++) {
        minX = min(minX, curr[j][i].mv.x + i*BLK_SIZE*4);
        maxX = max(maxX, curr[j][i].mv.x + i*BLK_SIZE*4);
        minY = min(minY, curr[j][i].mv.y + j*BLK_SIZE*4);
        maxY = max(maxY, curr[j][i].mv.y + j*BLK_SIZE*4);
      }
    }
    vecDiffX = (maxX>>2) - (minX>>2);
    vecDiffY = (maxY>>2) - (minY>>2);
    rectSize = (vecDiffX + BLK_SIZE + 6) * (vecDiffY + BLK_SIZE + 6);
    break;
  default:
    return 1;
  }
  
  if (rectSize <= MAX_SUB_MB_RECT_SIZE)
    return 1;  /* Rect size ok */
  else
    return 0;  /* Rect size too large */
}


#ifdef ENABLE_SEARCH_WINDOW

/*
 * mesUpdateSearchWin:
 *
 * Parameters:
 *      pMb                 Macroblock information
 *
 * Function:
 *      Interpolate search window data and transfer new data to search window
 *
 * Returns:
 *      -
 */
void mesUpdateSearchWin(macroblock_s *pMb)
{
  searchWin_s *pSWin;

  pSWin = pMb->pSWin;

  // search window start position
  pSWin->locX = pMb->idxX * MBK_SIZE;
  pSWin->locY = pMb->idxY * MBK_SIZE;

  // Load search window for this MB
  loadSearchWindow(pSWin);

  // interpolate half pel horizontally
  refFrmUpsampleLumaH_SearchWin(pSWin);

  // interpolate half pel vertically
  refFrmUpsampleLumaV_SearchWin(pSWin);

}

#endif


/*
 * mesFindMotionFullSearch:
 *
 * Parameters:
 *      pMb                 Macroblock information
 *      pMeProf             Parameters for controlling ME
 *      refBufList          Reference frame buffer array
 *      nRefFrames          Number of reference frames in the array
 *
 * Function:
 *      Perform complexity scalable motion estimation based on the motion 
 *      estimation profile. 
 *      Here are how the blocks of different sizes are defined:
 *        MB:               Macroblock, no definition is needed
 *        MB partition:     One can have independent reference frame
 *        Sub-MB:           8x8 MB partition
 *        Sub-MB partition: parition within a sub-MB, sometime use MB parition
 *        Block:            4x4 block, the smallest possible parition
 *
 *      The motion vectors of all the modes are returned in "pMb->modeMvRef". 
 *      The actual decision is made in another function.
 *      The best mode based on SAD after Hadamard has been found already in 
 *      this function. However, if RDO is enabled, the actual rate and 
 *      distortion will be calculated, the best mode could change. This is 
 *      performed in another function.
 *
 * Returns:
 *      SAD of the best match. 
 */
int mesFindMotionFullSearch(macroblock_s *pMb,
                            meProfile_s  *pMeProf,
                            refFrmBuf_s  **refBufList, 
                            int          nRefFrames)
{
  int mode, r, i, j;
  int mpX0, mpX1, mpY0, mpY1;
  int shapeX, shapeY;
  int lambda;
  int blkMvBits;
  int32 mbSad, minMbSad;
  int32 mbPartSad, minMbPartSad;
  int mbPartBits;
  u_int8   *refBlkPtrs[FRM_MAX_REF_FRAMES][16];  // maximally 5 frames
  u_int16  *refPartSum[FRM_MAX_REF_FRAMES];
  mbPart_s mbPart;              // one partition of MB or sub-MB
  int16 *blkSadPtr;
  int totalSad=0,totalSkipSad=0;
  lowComplexProf3_s *plc3;
#ifdef ENABLE_SEARCH_WINDOW
  searchWin_s *pSWin;
#endif
  

  pMeProf->pruneTreeTh = pMeProf->pruneThUnit * (pMb->qp - 12 - MIN_QP);
  pMeProf->goodEarlyMatch = 0;
  // Is skipPredMv valid? Is it pointing within the extended search area?
  if (((pMeProf->area0[0] - pMb->idxX * MBK_SIZE) * 4 <= pMb->skipPredMv.x) &&
    ((pMeProf->area0[1] - pMb->idxY * MBK_SIZE) * 4 <= pMb->skipPredMv.y) &&
    ((pMeProf->area1[0] - (pMb->idxX + 1) * MBK_SIZE) * 4 >= pMb->skipPredMv.x) && 
    ((pMeProf->area1[1] - (pMb->idxY + 1) * MBK_SIZE) * 4 >= pMb->skipPredMv.y))
  {
    pMb->skipPredMvValid = 1;
  }
  else
  {
    pMb->skipPredMvValid = 0;
  }
  
  // need to initialize, 16x8, 8x16, 8x8, 8x4, 4x8
  blkSadPtr = & pMb->blkSADs[0][MOT_16x8][0];
  for (i = 0; i < 5 * 16; i++)
    *blkSadPtr++ = 10000;
  
  /* LOW_COMPLEX_PROF3 */
  plc3 = mbPart.plc3 = &(pMeProf->lc3);
#ifdef ENABLE_SEARCH_WINDOW
  pSWin = &(pMeProf->sWin);
#endif
  
  /* low complexity mode 3 per mb init */
  
  plc3->cnt++;
  plc3->do_qpel_mode_2_3 = plc3->do_qpel_mode_4 = 1;
  plc3->qp = (int16)pMb->qp;
  plc3->do_16x8 = 1;
  
  if(plc3->useProf4)
  {
    
    if(pMb->qp>30)
      plc3->lc4_pruneTreeTh = (int16)(pMeProf->pruneThUnit * (pMb->qp - 21)*2);
    else
      plc3->lc4_pruneTreeTh = (int16)(pMeProf->pruneThUnit * (pMb->qp - 12 - MIN_QP));  
    
    plc3->lc4_pruneTreeTh = (int16)(MAX(plc3->lc4_pruneTreeTh,50));
  }
  
#ifdef ENABLE_SEARCH_WINDOW
  mbPart.refPsWidth = mbPart.refWidth = 
#else
    mbPart.refWidth = 
#endif
    PrecomputeRefPointers(pMb, refBufList, nRefFrames, refBlkPtrs, refPartSum);
  
#ifdef ENABLE_SEARCH_WINDOW
  if (pSWin->useSearchWin) {

    // Update search window for this MB
    mesUpdateSearchWin(pMb);

    mbPart.refPsWidth = refBufList[0]->yBufWidth;

    // set up refBlkPtrs
    mbPart.refWidth = PrecomputeRefPointers_SearchWin(pMb, nRefFrames, refBlkPtrs);     
  }
#endif
  
  lambda = pMb->lambda;
  mbPart.lambda       = lambda;
  mbPart.lambdaCoarse = lambda;
  
  mbPart.profile  = pMeProf->profile >> 4;
  
  minMbSad = LONG_MAX;
  
  pMb->interModeFlags = pMeProf->interModeFlags;
  
  if(plc3->useProf4 == 1)
  {
    int earlySkip=1, earlySkipMot=1;
    int sad=0,totalSad=0,totalMotSad=0;
    
    mbPart.ref  = refBlkPtrs[0][0];
    mbPart.orig = & pMb->origY[0][0];
    
    for(i=0;i<2;i++) {
      for(j=0;j<2;j++) {        
        
        plc3->skipSad[i][j] = (int16) findSAD2(mbPart.orig+j*8+i*128,mbPart.ref+j*16+i*16*mbPart.refWidth, mbPart.refWidth, 
          8, 8, pMb->skipPredMv.x, pMb->skipPredMv.y, 0,INT_MAX);
        
        plc3->zeroMotSad[i][j] = plc3->skipSad[i][j];
        
        totalSad+=plc3->skipSad[i][j];
        
        if(plc3->skipSad[i][j] > (plc3->skipThreMultiple*plc3->lc4_pruneTreeTh)>>1)
          earlySkip = 0;                
      }
    }
    if(pMb->skipPredMv.x == 0 && pMb->skipPredMv.y == 0)
    {
      earlySkipMot = earlySkip;
      totalMotSad=totalSad;
    }    
    else
    {
      //If SKIP MV is not 0,0 check zero MV
      for(i=0;i<2;i++) {
        for(j=0;j<2;j++) {        
          
          plc3->zeroMotSad[i][j] = (int16)findSAD2(mbPart.orig+j*8+i*128,mbPart.ref+j*16+i*16*mbPart.refWidth, mbPart.refWidth, 
            8, 8, 0, 0, 0,INT_MAX);
          
          totalMotSad+=plc3->zeroMotSad[i][j];
          
          if(plc3->zeroMotSad[i][j] > (plc3->skipThreMultiple*plc3->lc4_pruneTreeTh)>>1)
            earlySkipMot = 0;
        }
      }
    }
    
    if(!pMb->skipPredMvValid && earlySkip == 1)
      earlySkip = 0;
    
    if(earlySkip == 1 && earlySkipMot == 1)
    {
      if(totalSad < totalMotSad+pMb->lambda*(*(uvlcBitsSigned - pMb->skipPredMv.x + 511)+*(uvlcBitsSigned - pMb->skipPredMv.y + 511)))
        earlySkipMot = 0;
      else
        earlySkip = 0;
    }
    
    totalSkipSad = MIN(totalSad,totalMotSad+pMb->lambda*(*(uvlcBitsSigned - pMb->skipPredMv.x + 511)+*(uvlcBitsSigned - pMb->skipPredMv.y + 511)));
    
    pMeProf->goodEarlyMatch = (int8)( (earlySkip | earlySkipMot));
    
    if(earlySkip == 1) {      
      pMb->interMode = MOT_COPY;
      for (i = 0; i < 16; i ++) {
        pMb->modeMvRef[MOT_COPY][i].ref = 0;
        pMb->modeMvRef[MOT_COPY][i].mv = pMb->skipPredMv;
      }
      
      pMb->current[0][0].mv.x=pMb->skipPredMv.x;
      pMb->current[0][0].mv.y=pMb->skipPredMv.y;
      pMb->current[0][0].ref=0;
      pMeProf->goodEarlyMatch = 1;
      return sad;     
    }
    
    else if(earlySkipMot == 1) {      
      pMb->interMode = MOT_16x16;
      for (i = 0; i < 16; i ++) {
        pMb->modeMvRef[MOT_16x16][i].ref = 0;
        pMb->modeMvRef[MOT_16x16][i].mv.x =0;
        pMb->modeMvRef[MOT_16x16][i].mv.y =0;
      }
      
      pMb->current[0][0].mv.x=0;
      pMb->current[0][0].mv.y=0;
      pMb->current[0][0].ref=0;
      pMeProf->goodEarlyMatch = 1;
      return sad;     
    }    
  }   
  for (mode = MOT_16x16; mode <= MOT_8x8; mode ++) {
    int part_idx=-1;
    /* LOW_COMPLEX_PROF3 */
    lowComplexProf3_s *plc3 = mbPart.plc3;
    
    plc3->mode = (int16)mode;
    
    // do not check MOT_8x8 only if modes above (include) MOT_8x8 are disabled
    if (((mode < MOT_8x8) && (pMb->interModeFlags & (1 << (mode - 1))) == 0) ||
      ((mode == MOT_8x8) && (pMb->interModeFlags >> 3) == 0))
      continue;
    
    if (mode == MOT_16x16)
      pMeProf->searchCtrFlag = CENTER_PRED_MV;
    else
      pMeProf->searchCtrFlag = CENTER_LARGER_BLOCK_MV;
    
    mbPart.mode = mode;
    shapeX = modePartWidth[mode];           // Width of mot. block in blocks
    shapeY = modePartHeight[mode];          // Height of mot. block in blocks
    mbPart.width  = shapeX * BLK_SIZE;      // Width of mot. block
    mbPart.height = shapeY * BLK_SIZE;      // Height of mot. block
    
    // bits spent on coding mbType
    mbSad = (int32)lambda * uvlcBitsUnsigned[mode - 1];
    for (mpY0 = 0; mpY0 < 4; mpY0 = mpY1) {
      mpY1 = mpY0 + shapeY;
      for (mpX0 = 0; mpX0 < 4; mpX0 = mpX1) {
        // best mode for this MB partition
        int bestMpMode;
        part_idx++;
        
        mpX1 = mpX0 + shapeX;
        
        bestMpMode = mode;
        minMbPartSad = LONG_MAX;
        mbPartSad = 0;            // just to avoid complaint
        
        // look for the best reference frame for this MB-parititon
        for (r = 0; r < nRefFrames; r ++) {
          blkState_s *bestMvRefPair;
          int refIdxBits;
          
  		    // Only use frames from the same view or previous view.
	  	    if(refBufList[r]->viewId > pMb->currentView)
		  	    continue;

          // set the search range
          mbPart.range = pMeProf->range[mode != MOT_16x16][r != 0];
          
          // we may need to have only 1 vector for the partition
          bestMvRefPair = & pMb->current[mpY0][mpX0];
          bestMvRefPair->ref = (int8) r;
          
          mbPartBits = 0;
          refIdxBits = vlcGetRefIndexBits(nRefFrames - 1, r);
          
          if (mode < MOT_8x8) {
            mbPart.x0 = mpX0;   mbPart.x1 = mpX1;
            mbPart.y0 = mpY0;   mbPart.y1 = mpY1;
            
            // the best vector will be filled in bestMvRefPair->mv
            if(plc3->useProf4 != 1) {
              mbPartSad = (int32)lambda * refIdxBits + mesBasicMode
                (pMb, pMeProf, & mbPart, refBlkPtrs[r], refPartSum[r], mode, & blkMvBits);         
              plc3->numMEs++;
            }
            else 
            {
              if(plc3->performME[mode-1][part_idx]) {
                mbPartSad = (int32)lambda * refIdxBits + mesBasicMode
                  (pMb, pMeProf, & mbPart, refBlkPtrs[r], refPartSum[r], mode, & blkMvBits);
                plc3->numMEs++;
              }
              else
              {
                // Fill the best vector
                bestMvRefPair->mv.x = pMb->modeMvRef[MOT_16x16][0].mv.x;
                bestMvRefPair->mv.y = pMb->modeMvRef[MOT_16x16][0].mv.y;
              }
              
            }  
            if(plc3->useProf4 == 1 && mode == MOT_16x16 ) {
              int idx=3,score=0;
              //              int mvsad = pMb->lambda*(*(uvlcBitsSigned - bestMvRefPair->mv.x + 511)+*(uvlcBitsSigned - bestMvRefPair->mv.y+ 511));
              for(i=0;i<2;i++) {
                for(j=0;j<2;j++) {        
                  
                  //This could be filled above in mesBasicMode, depending on the final implementation. Check with Antti
                  plc3->sad16x16[i][j] = (int16) findSAD2(mbPart.orig+j*8+i*128,mbPart.ref+j*16+i*16*mbPart.refWidth, mbPart.refWidth, 
                    8, 8, bestMvRefPair->mv.x, bestMvRefPair->mv.y, blkMvBits,INT_MAX);
                  totalSad+=plc3->sad16x16[i][j];                               
                  if(plc3->sad16x16[i][j] > (plc3->sadThreMultiple_1*plc3->lc4_pruneTreeTh)>>1) 
                    score+=(1<<idx);
                  idx--;
                  
                  
                }
              }
              //Check again: Kemal
              plc3->performME[MOT_16x16-1][0] = 1;
              plc3->performME[MOT_16x16-1][1] = 1;
              plc3->performME[MOT_16x8-1][0] = (int16) ( (plc3->sad16x16[0][0] + plc3->sad16x16[0][1]) < (plc3->sadThreMultiple_2*plc3->lc4_pruneTreeTh) ? 0:1 );
              plc3->performME[MOT_16x8-1][1] = (int16) ( (plc3->sad16x16[1][0] + plc3->sad16x16[1][1]) < (plc3->sadThreMultiple_2*plc3->lc4_pruneTreeTh) ? 0:1 );
              plc3->performME[MOT_8x16-1][0] = (int16) ( (plc3->sad16x16[0][0] + plc3->sad16x16[1][0]) < (plc3->sadThreMultiple_2*plc3->lc4_pruneTreeTh) ? 0:1 );
              plc3->performME[MOT_8x16-1][1] = (int16) ( (plc3->sad16x16[0][1] + plc3->sad16x16[1][1]) < (plc3->sadThreMultiple_2*plc3->lc4_pruneTreeTh) ? 0:1 );
              
              /*
              score:   -------
              | x | x | 
              -------
              | x | x | 
              -------
              
                0 ->Stop here
                12,3 ->16x8 ONLY
                10,5 ->8x16 ONLY
              */
              
              //We always check the INTRA mode. (Dont set the pMeProf->earlyExit as 1)
              if(score == 0 )
                pMb->interModeFlags = 1;                           
              else if(score == 12 || score == 3)
                pMb->interModeFlags = 3;              
              else if(score == 10 || score == 5)
                pMb->interModeFlags = 5;
              
              // If cost too high, exit to INTRA
              if(totalSad > plc3->exitToIntraTh) 
                pMb->interModeFlags = 1;        
              
            }        
            if ((r == 0) && (mode == MOT_16x16))
            {
              pMb->searchCtr[0] = bestMvRefPair->mv.x;
              pMb->searchCtr[1] = bestMvRefPair->mv.y;
            }
            
#ifndef DISABLE_RDO
            // use a different cost function, if RDO is enabled
            if (((pMeProf->profile & 0x0F) == MODE_DECISION_RDO) &&
              (nRefFrames > 1))
            {
              int mse;
              
              mbPartBits = refIdxBits + blkMvBits + 
                mesMbPartCost(pMb, refBlkPtrs[r], 
                mbPart.refWidth, mpX0, mpY0, mpX1 - mpX0, mpY1 - mpY0, & mse);
              
              mbPartSad = mse + pMb->rdoLambda * mbPartBits;
            }
#endif
            
            if (mbPartSad < minMbPartSad)
            {
              // This reference frame gives smaller SAD for this MB partition
              minMbPartSad = mbPartSad;
              for (j = mpY0; j < mpY1; j ++)
                for (i = mpX0; i < mpX1; i ++)
                  pMb->modeMvRef[bestMpMode][j * 4 + i] = *bestMvRefPair;
            }
          }
          else
          {
            int subMbMode;
            
            // more modes under MOT_8x8, entire sub-MB must have same reference
            for (subMbMode = P_L0_8x8; subMbMode <= P_L0_4x4; subMbMode ++) {
              int blkW, blkH;
              
              if ((pMb->interModeFlags & (1 << (subMbMode + MOT_8x8 - 1))) == 0)
                continue;
              
              mbPartBits = refIdxBits + uvlcBitsUnsigned[subMbMode];
              mbPartSad  = (int32)lambda * mbPartBits;
              
              // Sub-MB partition width in 4x4 blocks
              blkW = modePartWidth[subMbMode + MOT_8x8];
              
              // Sub-MB partition height in 4x4 blocks
              blkH = modePartHeight[subMbMode + MOT_8x8];
              mbPart.width  = blkW * BLK_SIZE;   // Width of mot. block
              mbPart.height = blkH * BLK_SIZE;   // Height of mot. block
              
              for (j = mpY0; j < mpY0 + 2; j += blkH) {
                mbPart.y0 = j;  mbPart.y1 = j + blkH;
                for (i = mpX0; i < mpX0 + 2; i += blkW) {
                  mbPart.x0 = i;  mbPart.x1 = i + blkW;
                  
                  bestMvRefPair = & pMb->current[j][i];
                  bestMvRefPair->ref = (int8) r;
                  
                  mbPartSad += mesBasicMode(pMb, pMeProf, & mbPart, refBlkPtrs[r], 
                    refPartSum[r], subMbMode + MOT_8x8, & blkMvBits);
                  
                  mbPartBits += blkMvBits;
                  
                  // fill the vector for the remaining 4x4 blocks
                  if (subMbMode == P_L0_4x8)
                    bestMvRefPair[4] = bestMvRefPair[0];
                  else if (subMbMode <= P_L0_8x4) {
                    bestMvRefPair[1] = bestMvRefPair[0];
                    if (subMbMode == P_L0_8x8) {
                      bestMvRefPair[4] = bestMvRefPair[0];
                      bestMvRefPair[5] = bestMvRefPair[0];
                    }
                  }
                }
              }
              
              if (pMeProf->pruneTreeFlag) {
                // save the motion vectors for sub-MB modes
                for (j = mpY0; j < mpY1; j ++)
                  for (i = mpX0; i < mpX1; i ++)
                    pMb->skipMVs[subMbMode][j * 4 + i] = pMb->current[j][i].mv;
              }
              
#ifndef DISABLE_RDO
              // use a different cost function, if RDO is enabled
              if ((pMeProf->profile & 0x0F) == MODE_DECISION_RDO) {
                int mse;
                
                mbPartBits += mesMbPartCost(pMb, refBlkPtrs[r], 
                  mbPart.refWidth, mpX0, mpY0, 2, 2, & mse);
                
                mbPartSad = mse + pMb->rdoLambda * mbPartBits;
              }
#endif
              
              // picks the best mode and best reference at the same time
              if (mbPartSad < minMbPartSad) {
                if (subMbMode == P_L0_8x8 || !pMeProf->subMbRectSizeFlag ||
                  checkSubMbRectSize(pMb->current, subMbMode, mpX0, mpY0)) {
                  minMbPartSad = mbPartSad;
                  
                  // save the best mode
                  pMb->interSubMbModes[mpY0 + (mpX0 >> 1)] = (u_int8) subMbMode;
                  
                  // both the motion vector and reference index are saved here
                  for (j = mpY0; j < mpY1; j ++)
                    for (i = mpX0; i < mpX1; i ++)
                      pMb->modeMvRef[MOT_8x8][j * 4 + i] = pMb->current[j][i];
                }
              }
            } // MOT_8x8, sub-MB mode search
          } // mode < MOT_8x8, or == MOT_8x8
        } // reference frame
        
        // store best MVs in frame vector buffer for future prediction
        for (j = mpY0; j < mpY1; j ++)
          for (i = mpX0; i < mpX1; i ++)
            pMb->current[j][i] = pMb->modeMvRef[bestMpMode][j * 4 + i];
          
          mbSad += minMbPartSad;
      } // MB partition X
    } // MB partition Y
    
    // if 4 sub-MB all refer to reference frame 0, cost can be reduced
    if ((nRefFrames > 1) && (mode == MOT_8x8))
    {
      if ((pMb->current[0][0].ref == 0) && (pMb->current[0][2].ref == 0) && 
        (pMb->current[2][0].ref == 0) && (pMb->current[2][2].ref == 0))
      {
        // 1 bit has been used unnecessarily for signaling reference indices
        mbSad -= lambda * 4;
      }
    }
    
    // find the best mode
    if (mbSad < minMbSad)
    {
      minMbSad = mbSad;
      pMb->interMode = mode;
    }
    
    if (
      (plc3->useProf4 == 0) &&
      (pMeProf->pruneTreeFlag) && (mode == MOT_16x16) &&
      (minMbSad < (16 * (int32)pMeProf->pruneTreeTh)))
    {
      pMb->interModeFlags = 1 << (MOT_16x16 - 1);
      break;
    }
  } // mode
  
  return minMbSad;
}

