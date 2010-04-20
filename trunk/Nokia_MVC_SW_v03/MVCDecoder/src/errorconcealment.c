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
 * errorconcealment.c
 *
 * Contains:
 *    Error concealment related procedures.
 *
 */

#include <string.h>
#include "nccglob.h"
#include "globals.h"
#include "framebuffer.h"
#include "motcomp.h"
#include "parameterset.h"
#include "dpb.h"
#include "slice.h"
#include "errorconcealment.h"


#ifdef ERROR_CONCEALMENT


#define mabs(a) ( (a) < 0 ? -(a) : (a) )

#define MVPERMB_THR 8

#define DIR_ZERO 0
#define DIR_TOP  1
#define DIR_BOTTOM 2
#define DIR_LEFT 3
#define DIR_RIGHT 4
#define DIR_UPPERLEFT 5
#define DIR_UPPERRIGHT 6
#define DIR_BOTTOMLEFT 7
#define DIR_BOTTOMRIGHT 8
#define NUM_OF_CANDIDATES 9

#define MASK_TOP    1
#define MASK_BOTTOM 2
#define MASK_LEFT   4
#define MASK_RIGHT  8


/*
 *
 * fillMotionVectors:
 *
 * Parameters:
 *      mbIdxX                MB horizontal location
 *      mbIdxY                MB vertical location
 *      picWidth              Picture width in pixel
 *      picHeight             Picture height in pixel
 *      refTab                Reference index buffer
 *      motVecs               Motion vector buffer
 *      mbTypeTable           Macroblock mode table
 *      from                  Where are the candidate MVs from?
 *
 * Function:
 *      Fill the MVs of a lost MB.
 *      
 * Returns:
 *      0:                    If all MVs in the MB is set to be zero MV
 *      1:                    Otherwise
 */

static int fillMotionVectors(int mbIdxX, int mbIdxY, int picWidth, int picHeight,
                             int8 *refTab, motVec_s *motVecs, int8 *mbTypeTable, int from)
{
  int blks   = picWidth/BLK_SIZE;
  int blkX   = mbIdxX*BLK_PER_MB;
  int blkY   = mbIdxY*BLK_PER_MB;
  motVec_s vec;
  int blkIdx;
  motVec_s *vecPtr;
  motVec_s *adjVecPtr;
  int8 *refPtr;
  int8 *adjRefPtr;
  int zeroMvFlag;
  int blkAddr;
  int widthMBs = picWidth/MBK_SIZE;
  int heightMBs = picHeight/MBK_SIZE;

  blkAddr = blkY*blks+blkX;

  adjVecPtr = vecPtr = &motVecs[blkAddr];
  adjRefPtr = refPtr = &refTab[blkAddr];
  mbTypeTable = &mbTypeTable[mbIdxY*widthMBs+mbIdxX];

  vec.x = 0;
  vec.y = 0;
  zeroMvFlag = 1;

  switch (from) {
  case DIR_TOP: // Top
    adjVecPtr -= (blks);
    adjRefPtr -= (blks);

    /* If upper MB is not available */
    if (( mbIdxY == 0) || MBK_IS_INTRA(mbTypeTable[-widthMBs]))
    {
      zeroMvFlag = 1;
    }
    /* Otherwise, skip mode vec is predicted */
    else {
      zeroMvFlag = 0;
    }
    break;

  case DIR_BOTTOM: // Bottom
    adjVecPtr += (4*blks);
    adjRefPtr += (4*blks);

    /* If bottom MB is not available */
    if (( mbIdxY == (heightMBs - 1)) || MBK_IS_INTRA(mbTypeTable[widthMBs]))
    {
      zeroMvFlag = 1;
    }
    /* Otherwise, skip mode vec is predicted */
    else {
      zeroMvFlag = 0;
    }
    break;
  case DIR_LEFT: // Left
    adjVecPtr -= 1;
    adjRefPtr -= 1;

    /* If left MB is not available */
    if (( mbIdxX == 0 ) || MBK_IS_INTRA(mbTypeTable[-1]))
    {
      zeroMvFlag = 1;
    }
    /* Otherwise, skip mode vec is predicted */
    else {
      zeroMvFlag = 0;
    }
    break;

  case DIR_RIGHT: // right
    adjVecPtr += 4;
    adjRefPtr += 4;

    /* If right MB is not available */
    if (( mbIdxX == (widthMBs - 1) ) || MBK_IS_INTRA(mbTypeTable[1]))
    {
      zeroMvFlag = 1;
    }
    /* Otherwise, skip mode vec is predicted */
    else {
      zeroMvFlag = 0;
    }
    break;

  case DIR_UPPERLEFT:
    adjVecPtr -= (1*blks+1);
    adjRefPtr -= (1*blks+1);
    /* if the upper left MB is not available */
    if ( mbIdxY == 0 || // the first line
         mbIdxX == 0 || // the first column
         MBK_IS_INTRA(mbTypeTable[-widthMBs-1]) // Intra coded
       )
    {
      zeroMvFlag = 1;
    }
    else
      zeroMvFlag = 0;
    break;

  case DIR_UPPERRIGHT:
    adjVecPtr -= (1*blks-4);
    adjRefPtr -= (1*blks-4);
    /* if the upper right MB is not available */
    if ( mbIdxY == 0 || // the first line
         mbIdxX == widthMBs-1 || // the last column
         MBK_IS_INTRA(mbTypeTable[-widthMBs+1]) // intra coded
       )
    {
      zeroMvFlag = 1;
    }
    else
      zeroMvFlag = 0;
    break;

  case DIR_BOTTOMLEFT:
    adjVecPtr += (4*blks-1);
    adjRefPtr += (4*blks-1);
    if (mbIdxY == heightMBs-1 || // the last line
        mbIdxX == 0 || // the first column
        MBK_IS_INTRA(mbTypeTable[widthMBs-1]) // intra coded
       )
    {
      zeroMvFlag = 1;
    }
    else
      zeroMvFlag = 0;
    break;
      
  case DIR_BOTTOMRIGHT:
    adjVecPtr += (4*blks+4);
    adjRefPtr += (4*blks+4);
    if (mbIdxY == heightMBs-1 || // the last line
        mbIdxX == widthMBs-1 || // the last column
        MBK_IS_INTRA(mbTypeTable[widthMBs+1]) // intra coded
       )
    {
      zeroMvFlag = 1;
    }
    else
      zeroMvFlag = 0;
    break;

  case DIR_ZERO:
  default:
    zeroMvFlag = 1;
    break;
  }


  if (zeroMvFlag) {
    for (blkIdx = 0; blkIdx < BLK_PER_MB; blkIdx++) {
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
  }
  else { // non zero MVs
    if (from == DIR_TOP || from == DIR_BOTTOM) {
      for (blkIdx = 0; blkIdx < BLK_PER_MB; blkIdx++) {
        vecPtr[0] = adjVecPtr[0];
        vecPtr[1] = adjVecPtr[1];
        vecPtr[2] = adjVecPtr[2];
        vecPtr[3] = adjVecPtr[3];

        refPtr[0] = adjRefPtr[0];
        refPtr[1] = adjRefPtr[1];
        refPtr[2] = adjRefPtr[2];
        refPtr[3] = adjRefPtr[3];

        vecPtr += blks;
        refPtr += blks;
      }
    }
    else if (from == DIR_LEFT || from == DIR_RIGHT) {
      for (blkIdx = 0; blkIdx < BLK_PER_MB; blkIdx++) {
        vecPtr[  0   ] = adjVecPtr[  0   ];
        vecPtr[  blks] = adjVecPtr[  blks];
        vecPtr[2*blks] = adjVecPtr[2*blks];
        vecPtr[3*blks] = adjVecPtr[3*blks];

        refPtr[  0   ] = adjRefPtr[  0   ];
        refPtr[  blks] = adjRefPtr[  blks];
        refPtr[2*blks] = adjRefPtr[2*blks];
        refPtr[3*blks] = adjRefPtr[3*blks];

        vecPtr += 1;
        refPtr += 1;
      }
    }
    else if (from == DIR_UPPERLEFT || from == DIR_UPPERRIGHT || from == DIR_BOTTOMLEFT || from == DIR_BOTTOMRIGHT) {
      for (blkIdx = 0; blkIdx < BLK_PER_MB; blkIdx++) {
        vecPtr[0] = adjVecPtr[0];
        vecPtr[1] = adjVecPtr[0];
        vecPtr[2] = adjVecPtr[0];
        vecPtr[3] = adjVecPtr[0];

        refPtr[0] = adjRefPtr[0];
        refPtr[1] = adjRefPtr[0];
        refPtr[2] = adjRefPtr[0];
        refPtr[3] = adjRefPtr[0];

        vecPtr += blks;
        refPtr += blks;
      }
    }
  }

  return zeroMvFlag;
}


/*
 *
 * getMismatch:
 *
 * Parameters:
 *      pEc                   EC object  
 *      currPic               The picture to be concealed
 *      mbIdxX                MB horizontal location
 *      mbIdxY                MB vertical location
 *      mbData                Table of MB attributes
 *      refPicList            Reference picture list
 *
 * Function:
 *      Calculate the mismatch
 *      
 * Returns:
 *      Mismatch
 */
static u_int32 selectDir(errorConcealment_s* pEc, int isUpOrDown, int mbIdxX, int mbIdxY)
{

  if (isUpOrDown == 0) // if going downwards
  // check if correctly received neighbours exist
  {
    // when the top mb is available
    if ( mbIdxY > 0 && pEc->decodedMbs[mbIdxY-1][mbIdxX] == 1 ) {
      return DIR_TOP;
    }

    // when the left mb is available
    if ( mbIdxX > 0 && pEc->decodedMbs[mbIdxY][mbIdxX-1] == 1 ) {
      return DIR_LEFT;
    }

    // when the right mb is available
    if ( mbIdxX < (pEc->widthMbs-1) && pEc->decodedMbs[mbIdxY][mbIdxX+1] == 1 ) {  
      return DIR_RIGHT;
    }

    // when the bottom mb is available
    if ( mbIdxY < (pEc->heightMbs-1) && pEc->decodedMbs[mbIdxY+1][mbIdxX] == 1 ) {
      return DIR_BOTTOM;
    }

    // when the top mb is available
    if ( mbIdxY > 0 && pEc->decodedMbs[mbIdxY-1][mbIdxX] == 2 ) {
      return DIR_TOP;
    }

    // when the left mb is available
    if ( mbIdxX > 0 && pEc->decodedMbs[mbIdxY][mbIdxX-1] == 2 ) {
      return DIR_LEFT;
    }

    // when the right mb is available
    if ( mbIdxX < (pEc->widthMbs-1) && pEc->decodedMbs[mbIdxY][mbIdxX+1] == 2 ) {  
      return DIR_RIGHT;
    }

    // when the bottom mb is available
    if ( mbIdxY < (pEc->heightMbs-1) && pEc->decodedMbs[mbIdxY+1][mbIdxX] == 2 ) {
      return DIR_BOTTOM;
    }
  }


  else // going upwards
  {
    // when the bottom mb is available
    if ( mbIdxY < (pEc->heightMbs-1) && pEc->decodedMbs[mbIdxY+1][mbIdxX] == 1 ) {
      return DIR_BOTTOM;
    }

    // when the right mb is available
    if ( mbIdxX < (pEc->widthMbs-1) && pEc->decodedMbs[mbIdxY][mbIdxX+1] == 1 ) {  
      return DIR_RIGHT;
    }

    // when the left mb is available
    if ( mbIdxX > 0 && pEc->decodedMbs[mbIdxY][mbIdxX-1] == 1 ) {
      return DIR_LEFT;
    }

    // when the top mb is available
    if ( mbIdxY > 0 && pEc->decodedMbs[mbIdxY-1][mbIdxX] == 1 ) {
      return DIR_TOP;
    }

    // when the bottom mb is available
    if ( mbIdxY < (pEc->heightMbs-1) && pEc->decodedMbs[mbIdxY+1][mbIdxX] == 2 ) {
      return DIR_BOTTOM;
    }

    // when the right mb is available
    if ( mbIdxX < (pEc->widthMbs-1) && pEc->decodedMbs[mbIdxY][mbIdxX+1] == 2 ) {  
      return DIR_RIGHT;
    }

    // when the left mb is available
    if ( mbIdxX > 0 && pEc->decodedMbs[mbIdxY][mbIdxX-1] == 2 ) {
      return DIR_LEFT;
    }

    // when the top mb is available
    if ( mbIdxY > 0 && pEc->decodedMbs[mbIdxY-1][mbIdxX] == 2 ) {
      return DIR_TOP;
    }
  }

  return DIR_ZERO;
}


/*
 *
 * initDir:
 *
 * Parameters:
 *      pEc                   EC object  
 *      refTab                Reference index buffer
 *
 * Function:
 *      Init the rank array (pEc->rank) before starting the concealment of current picture
 *
 * Returns:
 *      -
 */
static void initDir(errorConcealment_s* pEc)
{
  int start;
  int i, j;

  if (pEc->decodedMbs[0][0] != 0) {
    pEc->dirDown = 1;
    pEc->posDown = 1;
  }
  else {
    pEc->dirDown = 0;
  }

  if (pEc->decodedMbs[pEc->heightMbs-1][pEc->widthMbs-1] != 0) {
    pEc->dirUp = 1;
    pEc->posUp = pEc->widthMbs*pEc->heightMbs - 1;
  }
  else {
    pEc->dirUp = 0;
  }

  if (pEc->dirDown == 0 && pEc->dirUp == 0) {
    start = -1;
    for (j = 0; j < pEc->heightMbs && start < 0; j++) {
      for (i = 0; i < pEc->widthMbs; i++) {
        if (pEc->decodedMbs[j][i] != 0) {
          start = j*pEc->widthMbs+i;
          break;
        }
      }
    }

    if (start != -1) {
      pEc->dirDown = 1;
      pEc->posDown = start+1;
      pEc->dirUp = 1;
      pEc->posUp = start-1;
    }
  }

  if (pEc->dirDown == 0 && pEc->dirUp == 0) {
    pEc->dirDown = 1;
    pEc->posDown = 0;
  }

  if (pEc->dirDown != 0)
    pEc->dir = 0;   // going down
  else
    pEc->dir = 1;   // going up
}


static int selectDownwards(errorConcealment_s* pEc)
{
  int i;
  int found = -1;

  if (pEc->dirDown == 0)
    return found;

  for (i=pEc->posDown; i<pEc->widthMbs*pEc->heightMbs; i++) {
    if (pEc->decodedMbs[0][i] == 0) {
      found = i;
      pEc->posDown = i+1;
      break;
    }
  }

  if (found == -1) 
    pEc->dirDown = 0;

  return found;
}


static int selectUpwards(errorConcealment_s* pEc)
{
  int i;
  int found = -1;

  if (pEc->dirUp == 0)
    return found;

  for (i=pEc->posUp; i>=0; i--) {
    if (pEc->decodedMbs[0][i] == 0) {
      found = i;
      pEc->posUp = i-1;
      break;
    }
  }

  if (found == -1) 
    pEc->dirUp = 0;

  return found;
}


/*
 *
 * selectOneMB:
 *
 * Parameters:
 *      pEc                   EC object  
 *
 * Function:
 *      Select the MB to be concealed, which has the highest rank.
 *
 * Returns:
 *      The index of the selected MB
 *      -1, if no MB is selected
 */
static int selectOneMB(errorConcealment_s* pEc, int *isUpOrDown)
{
  int found = -1;

  if (pEc->dir == 0) { // going downwards
    found = selectDownwards(pEc);
    *isUpOrDown = 0;
    if (found == -1) {
      found = selectUpwards(pEc);
      *isUpOrDown = 1;
    }
    if (pEc->dirUp) // change the dir
      pEc->dir = 1;
  }
  else if (pEc->dir == 1) {               // going upwards
    found = selectUpwards(pEc);
    *isUpOrDown = 1;
    if (found == -1) {
      found = selectDownwards(pEc);
      *isUpOrDown = 0;
    }
    if (pEc->dirDown)
      pEc->dir = 0;
  }

  return found;
}


/*
 *
 * blkIntraConceal:
 *
 * Parameters:
 *      pEc                   EC object
 *      predY                 Return pointer for predicted luma pixels
 *      predC                 Return pointer for predicted chroma pixels
 *      currPic               The picture to be concealed
 *      idxX                  The position of the MB to be intra concealed
 *      idxY                  The position of the MB to be intra concealed
 *
 * Function:
 *      Do Intra concealment for an MB.
 *
 * Returns:
 *      -
 */
static void blkIntraConceal(errorConcealment_s *pEc, u_int8 predY[MBK_SIZE][MBK_SIZE],
                            u_int8 predC[MBK_SIZE/2][MBK_SIZE], 
                            frmBuf_s *currPic, int idxX, int idxY)
{
  int pxlX, pxlY, x, y, weight, i, comp;
  int picWidth = pEc->widthMbs * MBK_SIZE;
  int picWidthC = picWidth >> 1;
  u_int32 tmp;
  int neighbourExist = 0;
  u_int8 *pred, *currY, *currU, *currV, *currC, *src1, *src2;
  u_int8 srcTop[MBK_SIZE];
  u_int8 srcBottom[MBK_SIZE];
  u_int8 srcLeft[MBK_SIZE];
  u_int8 srcRight[MBK_SIZE];
  int tmpPix, step;
  int gradX, gradY;

  static const int8 weightTab[16] =
  {0, 0, 0, 0, 0, 16, 31, 16, 0, 1, 16, 1, 0, 16, 31, 16};
  static const int8 gradXtab[16] =
  {0, 0, 0, 0, 0, -1, -1, -1, 0, 1,  1, 1, 0,  0,  0,  0};
  static const int8 gradYtab[16] =
  {0, 0, 0, 0, 0,  1, -1,  0, 0, 1, -1, 0, 0,  1, -1,  0};

  pxlX = idxX * MBK_SIZE;
  pxlY = idxY * MBK_SIZE;

  currY = currPic->y + pxlY * picWidth + pxlX;
  currU = currPic->u + (pxlY>>1) * picWidthC + (pxlX>>1);
  currV = currPic->v + (pxlY>>1) * picWidthC + (pxlX>>1);

  // check if correctly received neighbours exist

  // when the top mb is available
  if ( idxY > 0 && pEc->decodedMbs[idxY-1][idxX] == 1 )
    neighbourExist |= MASK_TOP;

  // when the bottom mb is available
  if ( idxY < (pEc->heightMbs-1) && pEc->decodedMbs[idxY+1][idxX] == 1 )
    neighbourExist |= MASK_BOTTOM;

  // when the left mb is available
  if ( idxX > 0 && pEc->decodedMbs[idxY][idxX-1] == 1 )
    neighbourExist |= MASK_LEFT;

  // when the right mb is available
  if ( idxX < (pEc->widthMbs-1) && pEc->decodedMbs[idxY][idxX+1] == 1 )
    neighbourExist |= MASK_RIGHT;


  if (neighbourExist == 0) {

    // Correctly received neighbours does no exist, check if concealed neighbours exist

    // when the top mb is available
    if ( idxY > 0 && pEc->decodedMbs[idxY-1][idxX] == 2 )
      neighbourExist |= MASK_TOP;

    // when the bottom mb is available
    if ( idxY < (pEc->heightMbs-1) && pEc->decodedMbs[idxY+1][idxX] == 2 )
      neighbourExist |= MASK_BOTTOM;

    // when the left mb is available
    if ( idxX > 0 && pEc->decodedMbs[idxY][idxX-1] == 2 )
      neighbourExist |= MASK_LEFT;

    // when the right mb is available
    if ( idxX < (pEc->widthMbs-1) && pEc->decodedMbs[idxY][idxX+1] == 2 )
      neighbourExist |= MASK_RIGHT;
  }


  if (neighbourExist & MASK_TOP) {
    for (i = 0; i < MBK_SIZE; i++)
      srcTop[i] = currY[-picWidth + i];
  }
  if (neighbourExist & MASK_BOTTOM) {
    for (i = 0; i < MBK_SIZE; i++)
      srcBottom[i] = currY[MBK_SIZE*picWidth + i];
  }
  if (neighbourExist & MASK_LEFT) {
    for (i = 0; i < MBK_SIZE; i++)
      srcLeft[i] = currY[i*picWidth-1];
  }
  if (neighbourExist & MASK_RIGHT) {
    for (i = 0; i < MBK_SIZE; i++)
      srcRight[i] = currY[i*picWidth + MBK_SIZE];
  }


  if (neighbourExist & (MASK_TOP|MASK_BOTTOM)) {
    /*
     * Top and/or bottom macroblocks is available. Perform vertical linear
     * interpolation.
     */

    if (neighbourExist & MASK_TOP) {
      src1 = srcTop;
      src2 = (neighbourExist & MASK_BOTTOM) ? srcBottom : srcTop;
    }
    else
      src1 = src2 = srcBottom;

    pred = &predY[0][0];
    for (x = 0; x < MBK_SIZE; x++) {
      tmpPix = src1[x] * 16;
      step = src2[x] - src1[x];
      for (y = 0; y < MBK_SIZE; y++) {
        *pred = (u_int8)((tmpPix + 8) >> 4);
        pred += MBK_SIZE;
        tmpPix += step;
      }
      pred = pred - MBK_SIZE*MBK_SIZE + 1;
    }

    if (neighbourExist & (MASK_LEFT|MASK_RIGHT)) {
      /*
       * Left and/or right macroblocks is available. Perform horizontal linear
       * interpolation and combine results with vertical interpolation results.
       */

      if (neighbourExist & MASK_LEFT) {
        src1 = srcLeft;
        src2 = (neighbourExist & MASK_RIGHT) ? srcRight : srcLeft;
      }
      else
        src1 = src2 = srcRight;

      weight = weightTab[neighbourExist]; // weight at top left corner
      gradX  = gradXtab[neighbourExist];  // change in weight in horizontal direction
      gradY  = gradYtab[neighbourExist];  // change in weight in vertical direction

      pred = &predY[0][0];
      for (y = 0; y < MBK_SIZE; y++) {
        tmpPix = src1[y] * 16;
        step = src2[y] - src1[y];
        for (x = 0; x < MBK_SIZE; x++) {
          tmp = (u_int32)weight*tmpPix + (u_int32)(32-weight)*16*(*pred);
          *pred++ = (u_int8)((tmp + 256) >> 9);
          tmpPix += step;
          weight += gradX;
        }
        weight = weight - MBK_SIZE*gradX + gradY;
      }

    }
  }
  else {
    /*
     * Left and/or right macroblocks is available. Perform horizontal linear
     * interpolation. Top and bottom macroblocks are not available.
     */

    if (neighbourExist & MASK_LEFT) {
      src1 = srcLeft;
      src2 = (neighbourExist & MASK_RIGHT) ? srcRight : srcLeft;
    }
    else
      src1 = src2 = srcRight;

    /* Horizontal linear interpolation */
    pred = &predY[0][0];
    for (y = 0; y < MBK_SIZE; y++) {
      tmpPix = src1[y] * 16;
      step = src2[y] - src1[y];
      for (x = 0; x < MBK_SIZE; x++) {
        *pred++ = (u_int8)((tmpPix + 8) >> 4);
        tmpPix += step;
      }
    }
  }


  currC = currU;

  for (comp = 0; comp < 2; comp++) {

    if (neighbourExist & 0x1) {
      for (i = 0; i < MBK_SIZE/2; i++)
        srcTop[i] = currC[-picWidthC + i];
    }
    if (neighbourExist & 0x2) {
      for (i = 0; i < MBK_SIZE/2; i++)
        srcBottom[i] = currC[(MBK_SIZE/2)*picWidthC + i];
    }
    if (neighbourExist & 0x4) {
      for (i = 0; i < MBK_SIZE/2; i++)
        srcLeft[i] = currC[i*picWidthC-1];
    }
    if (neighbourExist & 0x8) {
      for (i = 0; i < MBK_SIZE/2; i++)
        srcRight[i] = currC[i*picWidthC + MBK_SIZE/2];
    }


    if (neighbourExist & (MASK_TOP|MASK_BOTTOM)) {
      /*
      * Top and/or bottom macroblocks is available. Perform vertical linear
      * interpolation.
      */

      if (neighbourExist & MASK_TOP) {
        src1 = srcTop;
        src2 = (neighbourExist & MASK_BOTTOM) ? srcBottom : srcTop;
      }
      else
        src1 = src2 = srcBottom;

      pred = &predC[0][comp*(MBK_SIZE/2)];
      for (x = 0; x < MBK_SIZE/2; x++) {
        tmpPix = src1[x] * 8;
        step = src2[x] - src1[x];
        for (y = 0; y < MBK_SIZE/2; y++) {
          *pred = (u_int8)((tmpPix + 4) >> 3);
          pred += MBK_SIZE;
          tmpPix += step;
        }
        pred = pred - (MBK_SIZE/2)*MBK_SIZE + 1;
      }

      if (neighbourExist & (MASK_LEFT|MASK_RIGHT)) {
        /*
        * Left and/or right macroblocks is available. Perform horizontal linear
        * interpolation and combine results with vertical interpolation results.
        */

        if (neighbourExist & MASK_LEFT) {
          src1 = srcLeft;
          src2 = (neighbourExist & MASK_RIGHT) ? srcRight : srcLeft;
        }
        else
          src1 = src2 = srcRight;

        weight = weightTab[neighbourExist];  // weight at top left corner
        gradX  = 2*gradXtab[neighbourExist]; // change in weight in horizontal direction
        gradY  = 2*gradYtab[neighbourExist]; // change in weight in vertical direction

        pred = &predC[0][comp*(MBK_SIZE/2)];
        for (y = 0; y < MBK_SIZE/2; y++) {
          tmpPix = src1[y] * 8;
          step = src2[y] - src1[y];
          for (x = 0; x < MBK_SIZE/2; x++) {
            tmp = (u_int32)weight*tmpPix + (u_int32)(32-weight)*8*(*pred);
            *pred++ = (u_int8)((tmp + 128) >> 8);
            tmpPix += step;
            weight += gradX;
          }
          pred += MBK_SIZE/2;
          weight = weight - (MBK_SIZE/2)*gradX + gradY;
        }

      }
    }
    else {
      /*
      * Left and/or right macroblocks is available. Perform horizontal linear
      * interpolation. Top and bottom macroblocks are not available.
      */

      if (neighbourExist & MASK_LEFT) {
        src1 = srcLeft;
        src2 = (neighbourExist & MASK_RIGHT) ? srcRight : srcLeft;
      }
      else
        src1 = src2 = srcRight;

      /* Horizontal linear interpolation */
      pred = &predC[0][comp*(MBK_SIZE/2)];
      for (y = 0; y < MBK_SIZE/2; y++) {
        tmpPix = src1[y] * 8;
        step = src2[y] - src1[y];
        for (x = 0; x < MBK_SIZE/2; x++) {
          *pred++ = (u_int8)((tmpPix + 4) >> 3);
          tmpPix += step;
        }
        pred += MBK_SIZE/2;
      }
    }

    currC = currV;
  }

}


/*
 *
 * useIntra:
 *
 * Parameters:
 *      pEc                   EC object  
 *      mbTypeTable           Macroblock type table
 *      idxX                  The position of the MB to be concealed
 *      idxY                  The position of the MB to be concealed
 *
 * Function:
 *      Make the decision to do Intra concealment or Inter concealment
 *
 * Returns:
 *      1                      Do Intra concealment
 *      0                      Do Inter concealment
 */
static int useIntra(errorConcealment_s* pEc, int8 *mbTypeTable, int idxX, int idxY)
{
  int flag = 0;
  int mbX, mbY;

  if (mbTypeTable == NULL)
    return 1;

  // top
  mbX = idxX;
  mbY = idxY - 1;
  if (mbY >= 0) {
    if (MBK_IS_INTRA(mbTypeTable[mbY*pEc->widthMbs+mbX]) && pEc->decodedMbs[mbY][mbX] == 1)
      flag++;
  }

  // bottom
  mbX = idxX;
  mbY = idxY + 1;
  if (mbY < pEc->heightMbs) {
    if (MBK_IS_INTRA(mbTypeTable[mbY*pEc->widthMbs+mbX]) && pEc->decodedMbs[mbY][mbX] == 1)
      flag++;
  }

  // left
  mbX = idxX - 1;
  mbY = idxY;
  if (mbX >= 0) {
    if (MBK_IS_INTRA(mbTypeTable[mbY*pEc->widthMbs+mbX]) && pEc->decodedMbs[mbY][mbX] == 1)
      flag++;
  }

  // right
  mbX = idxX + 1;
  mbY = idxY;
  if (mbX < pEc->widthMbs) {
    if (MBK_IS_INTRA(mbTypeTable[mbY*pEc->widthMbs+mbX]) && pEc->decodedMbs[mbY][mbX] == 1)
      flag++;
  }

  if (flag >= 4)
    return 1;
  else
    return 0;
}


/*
 *
 * bySceneCutDetection:
 *
 * Parameters:
 *      pEc                   EC object  
 *      currPic               The picture to be concealed
 *
 * Function:
 *      Check if the picture is scene cut picture by partly received picture.
 *
 * Returns:
 *      0:      Not scene cut picture, or failed in the algorithm
 *      1:      Scene cut picture
 */
#define DEBUG_SCENE_CUT_DETECTION 0
static int bySceneCutDetection(errorConcealment_s *pEc, frmBuf_s *currPic, dpb_s *dpb)
{
  frmBuf_s *prevPic;
  int      numMBs;
  int      numSelectedMbs;
  int      countMbs;
  int      i;
  int      j;
  int      k;
  int      x;
  int      y;
  int      xDir;
  int      yDir;
  int      mbOffset;
  int      pixelOffset;
  int32    diff;
  int      leftBound;
  int      rightBound;
  int      topBound;
  int      bottomBound;
  int      visit;
  int      diffTh = 44/2;

#if DEBUG_SCENE_CUT_DETECTION
  int      debugNum[11][9];
  FILE     *fp;
  static int count = 0;
  unsigned char *curr, *prev;      
#endif

#if DEBUG_SCENE_CUT_DETECTION
  for (y = 0; y < 9; y++) {
    for (x = 0; x < 11; x++)
      debugNum[x][y] = -1;
  }
  curr = malloc(176*144);
  prev = malloc(176*144);

  if (curr == NULL|| prev == NULL) {
    printf("Error!");
    exit(0);
  }
  memset(curr, 0, 176*144);
  memset(prev, 0, 176*144);
#endif

  /* Find the latest decoded ref pic */
  if (dpb->fullness[0] > 0)
  {
    prevPic = dpb->buffers[0][0];	// Get this from the first view
  }
  else
    prevPic = NULL;

  /* No stored pictures, we assume the current pictures to be a scene cut picture */
  if (prevPic == NULL)
    return 1;

  /* 20% Mbs will be used for scene cut detection */
  numMBs = pEc->widthMbs * pEc->heightMbs;
  numSelectedMbs = numMBs / 5;

  /* As per box-out order to select the MBs to do the scene cut detection */
  // init position
  x = pEc->widthMbs / 2;
  y = pEc->heightMbs / 2;
  // init dir
  xDir = 0;
  yDir = -1;
  // init bound
  leftBound = x;
  rightBound = x;
  topBound = y;
  bottomBound = y;

  visit = 0;
  k = 0;
  countMbs = 0;
  diff = 0;

  do {
    /* calculate the diff */
    if (!visit && pEc->decodedMbs[y][x] == 1 && pEc->prevDecodedMbs[y][x] == 1) {
#if DEBUG_SCENE_CUT_DETECTION
      debugNum[x][y] = k;
#endif
      countMbs++;
      mbOffset = (y * pEc->widthMbs << 8) + (x << 4); //  y * MBK_SIZE * pEc->widthMbs * MBK_SIZE + x * MBK_SIZE;
      for (j = 0; j < MBK_SIZE; j+=2) {
        for (i = 0; i < MBK_SIZE; i++) {
          pixelOffset = mbOffset + j * pEc->widthMbs * MBK_SIZE + i;
          diff += abs(currPic->y[pixelOffset] - prevPic->y[pixelOffset]);
#if DEBUG_SCENE_CUT_DETECTION
          prev[pixelOffset] = prevPic->y[pixelOffset];
          curr[pixelOffset] = currPic->y[pixelOffset];
#endif
        }
      }
    }

    if (!visit)
      k++;

    if ( xDir == -1 &&  x == leftBound ) {
      if (leftBound == 0)
        visit = 1;
      else {
        visit = 0;
        leftBound = leftBound - 1;
        x = leftBound;
      }
      xDir = 0;
      yDir = -1;
    } 
    else if ( xDir == 1 && x == rightBound ) {
      if (rightBound == pEc->widthMbs - 1)
        visit = 1;
      else {
        visit = 0;
        rightBound = rightBound + 1;
        x = rightBound;
      }
      xDir = 0;
      yDir = 1;
    } 
    else if ( yDir == -1 && y == topBound ) {
      if (topBound == 0)
        visit = 1;
      else {
        visit = 0;
        topBound = topBound - 1;
        y = topBound;
      }
      xDir = 1;
      yDir = 0;
    } 
    else if( yDir == 1 && y == bottomBound ) {
      if (bottomBound == pEc->heightMbs - 1)
        visit = 1;
      else {
        visit = 0;
        bottomBound = bottomBound + 1;
        y = bottomBound;
      }
      xDir = -1;
      yDir = 0;
    } 
    else {
      x = x + xDir;
      y = y + yDir;
    }
  } while (k < numMBs && countMbs < numSelectedMbs);

#if DEBUG_SCENE_CUT_DETECTION
  fp = fopen("dddd.txt", "wt");
  for (y = 0; y < 9; y++) {
    for (x = 0; x < 11; x++)
      fprintf(fp, "%d\t", debugNum[x][y]);
    fprintf(fp, "\n");
  }
  fclose(fp);

  count++;
  fp = fopen("prev.yuv", "wb");
  fwrite(prev, 1, 176*144, fp);
  memset(prev, 128, 176*144/2);
  fwrite(prev, 1, 176*144/2, fp);
  fclose(fp);

  fp = fopen("curr.yuv", "wb");
  fwrite(curr, 1, 176*144, fp);
  memset(curr, 128, 176*144/2);
  fwrite(curr, 1, 176*144/2, fp);
  fclose(fp);

  free(curr);
  free(prev);
#endif

  /* If there are not enough MBs or the diff is small enough, not a scene cut! */
  if (countMbs < numSelectedMbs || diff < (diffTh * numSelectedMbs << 8) ) { // * MBK_SIZE * MBK_SIZE
#if DEBUG_SCENE_CUT_DETECTION
    printf("Inter concealing at pic layer (%d).\n", diff / (numSelectedMbs * MBK_SIZE * MBK_SIZE));
#endif
    return 0;
  }
  else {
#if DEBUG_SCENE_CUT_DETECTION
    printf("INTRA concealing at pic layer (%d).\n", diff / (numSelectedMbs * MBK_SIZE * MBK_SIZE));
#endif
    return 1;
  }
}


/*
 *
 * concealCurrPic:
 *
 * Parameters:
 *      pEc                   EC object  
 *      currPic               The picture to be concealed
 *      mbData                Table of MB attributes
 *      dpb                   Decoded picture buffer
 *      pps                   Picture parameter set
 *
 * Function:
 *      Conceal the lost area in current picture MB by MB. Note that whole picture losses are 
 *      not handled.
 *
 * Returns:
 *      -
 */
static void concealCurrPic(errorConcealment_s* pEc, frmBuf_s *currPic,
                           mbAttributes_s *mbData, dpb_s *dpb,
                           pic_parameter_set_s *pps)
{
  int idxX, idxY, idxMB;
  int x, y;
  int width, height;
  u_int8 *currPtr;
  int isUpOrDown;
  int intra;
  u_int8 predY[MBK_SIZE][MBK_SIZE];
  u_int8 predC[MBK_SIZE/2][MBK_SIZE];
  int fromBest;
  frmBuf_s *refPicList0[DPB_MAX_SIZE+1];
  int numRefFrames, numExistingRefFrames;

  static const int modes4x4[4] = {3, 3, 3, 3};

  width = pEc->widthMbs * MBK_SIZE;
  height = pEc->heightMbs * MBK_SIZE;

  /* Choose number of reference frames and build reference picture list */
  /* Use the parameters in the PPS to build the ref list */
  /* Alternatively, we can use the received slices in the same frame if available - a little more complex */
  numRefFrames = pps->num_ref_idx_l0_active_minus1 + 1;
  
  numExistingRefFrames = sliceInitRefPicList(dpb, refPicList0, 0, currPic->frameNum);		/* Use the base view (viewId = 0) for now */
  sliceFixRefPicList(dpb, refPicList0, numExistingRefFrames, width, height,0);

  initDir(pEc);

  /* Make a decision to do intra concealment on picture layer */
  /* The first picture of the sequence */
  if (pEc->isFirstPicOfSeq)
    intra = 1;
  /* Having scene info SEI */
  else if (pEc->hasSceneInfo) {
    intra = currPic->sceneCut;
  }
  /* Using scene cut detection */
  else {
    intra = bySceneCutDetection(pEc, currPic, dpb);
  }

  while ((idxMB = selectOneMB(pEc, &isUpOrDown)) >= 0) {
    idxY = (int)(((int32)idxMB * pEc->inverseOfWidthMbs) >> pEc->numFractBits);
    idxX = idxMB - idxY*pEc->widthMbs;

    /* Current MB is not decoded (pEc->decodedMbs[idxY][idxX] == 0), conceal it */
    /* do Intra concealment or Inter concealment? */
    if ( intra || useIntra(pEc, mbData->mbTypeTable, idxX, idxY) ) {
      mbData->mbTypeTable[idxMB] = MB_TYPE_INTRA_16x16;
      mcpClearMBmotion(idxX, idxY, width, mbData->refIdxTable, -1, mbData->motVecTable);
      blkIntraConceal(pEc, predY, predC, currPic, idxX, idxY);
    }
    else {
      mbData->mbTypeTable[idxMB] = MB_TYPE_INTER_8x8;
      fromBest = selectDir(pEc, isUpOrDown, idxX, idxY);
      fillMotionVectors(idxX, idxY, width, height, mbData->refIdxTable,
                        mbData->motVecTable, mbData->mbTypeTable, fromBest);
      mcpGetPred(predY, predC, idxX, idxY, refPicList0, width, 
                 height, mbData->motVecTable, mbData->refIdxTable, modes4x4);
    }

    mbData->qpTable[idxMB] = MAX_QP;
    mbData->cbpTable[idxMB] = 0;
    mbData->alphaOffset[idxMB] = 0;
    mbData->betaOffset[idxMB] = 0;
    mbData->filterModeTab[idxMB] = 0;

    /* Y */
    currPtr = currPic->y + idxY*MBK_SIZE*width + idxX*MBK_SIZE;
    for (y = 0; y < MBK_SIZE; y++) {
      for (x = 0; x < MBK_SIZE; x++) {
        currPtr[y*width+x] = predY[y][x];
      }
    }
    /* U */
    currPtr = currPic->u + idxY *MBK_SIZE/2 * width/2 + idxX*MBK_SIZE/2;
    for (y = 0; y < MBK_SIZE/2; y++) {
      for (x = 0; x < MBK_SIZE/2; x++) {
        currPtr[y*width/2+x] = predC[y][0+x];
      }
    }
    /* V */
    currPtr = currPic->v + idxY *MBK_SIZE/2 * width/2 + idxX*MBK_SIZE/2;
    for (y = 0; y < MBK_SIZE/2; y++) {
      for (x = 0; x < MBK_SIZE/2; x++) {
        currPtr[y*width/2+x] = predC[y][MBK_SIZE/2 +x];
      }
    }

    pEc->decodedMbs[idxY][idxX] = 2;
  }
}


/*
 *
 * ercConcealMbs:
 *
 * Parameters:
 *      seq                   Sequence object
 *      currPic               The picture to be concealed
 *      mbData                Table of MB attributes
 *      dpb                   Decoded picture buffer
 *      pps                   Picture parameter set
 *
 * Function:
 *      Call concealCurrPic
 *      Interface of the error concealment
 *
 * Returns:
 *      -
 */
void ercConcealMbs(errorConcealment_s *pEc, frmBuf_s *currPic,
                   mbAttributes_s *mbData, dpb_s *dpb,
                   pic_parameter_set_s *pps)
{
  /* Conceal the lost MBs */

  /* TCON */
  concealCurrPic(pEc, currPic, mbData, dpb, pps);
}


/*
 *
 * ercConcealWholePic:
 *
 * Parameters:
 *      seq                   Sequence object
 *      currPic               The picture to be concealed
 *      mbData                Table of MB attributes
 *      dpb                   Decoded picture buffer
 *      pps                   Picture parameter set
 *
 * Function:
 *      Although the wholly lost pictures will not be outputted currently,
 *      we copy the content of the last decoded picture to the buffer as 
 *      a concealment. This is due to the wholly lost pictures will still 
 *      serve as ref pictures for the subsequent pictures.
 *
 * Returns:
 *      -
 */
void ercConcealWholePic(frmBuf_s *currPic, mbAttributes_s *mbData, dpb_s *dpb)
{
  /* Todo: Conceal the wholly lost pictures */
  int i, j;
  int mbsPerRow = currPic->width/MBK_SIZE;
  int mbsPerCol = currPic->height/MBK_SIZE;
  frmBuf_s *tmpFrm = dpb->buffers[0][0];	/* Use base view */

  if (dpb->fullness[0] == 0)	/* Use base view */
    return;

  currPic->poc = tmpFrm->poc + 1;
  
  memcpy(currPic->y, tmpFrm->y, currPic->width * currPic->height);
  memcpy(currPic->u, tmpFrm->u, currPic->width * currPic->height / 4);
  memcpy(currPic->v, tmpFrm->v, currPic->width * currPic->height / 4);

  /* Switch off loopfilter for this picture */
  for (j = 0; j < mbsPerCol; j++)
    for (i = 0; i < mbsPerRow; i++)
      mbData->filterModeTab[j*mbsPerRow+i] = 1;
}


/*
 *
 * ercInit:
 *
 * Parameters:
 *      wMbs                  The picture width in MBs
 *      hMbs                  The picture height in MBs
 *
 * Function:
 *      Initialization for the error concealment.
 *
 * Returns:
 *      The Error Concealment object.
 */
errorConcealment_s* ercOpen(int wMbs, int hMbs)
{
  int i;
  errorConcealment_s* pEc;

  if ((pEc = (errorConcealment_s*)nccMalloc(sizeof(errorConcealment_s))) == NULL)
    return NULL;

  memset(pEc, 0, sizeof(errorConcealment_s));

  if ((pEc->decodedMbs = (int **)nccMalloc(sizeof(int*)*hMbs)) == NULL)
    return NULL;

  if ((pEc->decodedMbs[0] = (int*)nccMalloc(sizeof(int)*wMbs*hMbs)) == NULL)
    return NULL;

  for (i = 1; i < hMbs; i++)
    pEc->decodedMbs[i] = pEc->decodedMbs[0] + i*wMbs;

  if ((pEc->prevDecodedMbs = (int **)nccMalloc(sizeof(int*)*hMbs)) == NULL)
    return NULL;

  if ((pEc->prevDecodedMbs[0] = (int*)nccMalloc(sizeof(int)*wMbs*hMbs)) == NULL)
    return NULL;

  for (i = 1; i < hMbs; i++)
    pEc->prevDecodedMbs[i] = pEc->prevDecodedMbs[0] + i*wMbs;

  pEc->widthMbs = wMbs;
  pEc->heightMbs = hMbs;
  pEc->numMbs = wMbs*hMbs;

  pEc->hasSceneInfo = 0;

  for (i = 15; i > 0; i--) {
    if ((wMbs>>i) & 1)
      break;
  }
  pEc->numFractBits = 14+i;
  pEc->inverseOfWidthMbs = (int)((((int32)1<<pEc->numFractBits)) / wMbs + 1);

  ercClear(pEc);

  return pEc;
}


/*
 *
 * ercClose:
 *
 * Parameters:
 *      pEc                   The EC object
 *
 * Function:
 *      Close the object of error concealment.
 *
 * Returns:
 *      -
 */
void ercClose(errorConcealment_s* pEc)
{
  if (pEc == NULL)
    return;

  nccFree(pEc->decodedMbs[0]);
  nccFree(pEc->decodedMbs);

  nccFree(pEc->prevDecodedMbs[0]);
  nccFree(pEc->prevDecodedMbs);

  nccFree(pEc);
}


/*
 *
 * ercClear:
 *
 * Parameters:
 *      pEc                   The EC object
 *
 * Function:
 *      Reset the indicators for all the MBs.
 *
 * Returns:
 *      -
 */
void ercClear(errorConcealment_s* pEc)
{
  int i, j;
  int *decodedMbs, *prevDecodedMbs;
  int widthMbs, heightMbs;

  widthMbs = pEc->widthMbs;
  heightMbs = pEc->heightMbs;

  for (j = 0; j < heightMbs; j++) {
    decodedMbs = pEc->decodedMbs[j];
    prevDecodedMbs = pEc->prevDecodedMbs[j];
    for (i = 0; i < widthMbs; i++) {
      prevDecodedMbs[i] = decodedMbs[i];
      decodedMbs[i] = 0;
    }
  }

  pEc->numDecodedMbs = 0;
}


/*
 *
 * ercDecodeMb:
 *
 * Parameters:
 *      pEc                   The EC object
 *      mbX                   The column of the decoded MBs
 *      mbY                   The row of the decoded MBs
 *
 * Function:
 *      Set the indicator for the decoded MB.
 *
 * Returns:
 *      -
 */
void ercDecodeMb(errorConcealment_s *pEc, int mbX, int mbY)
{
  if (pEc->decodedMbs[mbY][mbX] == 0) {
    pEc->decodedMbs[mbY][mbX] = 1;
    pEc->numDecodedMbs++;
  }
}


/*
 *
 * ercCheckAndConceal:
 *
 * Parameters:
 *      pEc                   The EC object
 *      currPic               The picture to be concealed
 *      mbData                Table of MB attributes
 *      dpb                   Decoded picture buffer
 *      pps                   Picture parameter set
 *
 * Function:
 *      Check whether all the MBs in current picture are decoded correctly.
 *      If not, conceal the lost area.
 *
 * Returns:
 *      -
 *      
 */
void ercCheckAndConceal(errorConcealment_s *pEc, frmBuf_s *currPic,
                        mbAttributes_s *mbData, dpb_s *dpb,
                        pic_parameter_set_s *pps)
{
  /* Check if all MBs of the current picture were decoded */
  if (pEc->numDecodedMbs < pEc->numMbs) {

    currPic->lossy = 1;

    /* Invoke error concealment */
    ercConcealMbs(pEc, currPic, mbData, dpb, pps);
  }
}


#ifdef REDUNDANT_PIC_CONCEALMENT
/*
 *
 * ercCombinePictures:
 *
 * Parameters:
 *      erc                   The EC object
 *      erc2                  The EC object for redundant picture
 *      reco                  Decoded picture
 *      reco2                 Decoded redundant picture
 *      mbData                Table of MB attributes
 *      mbData2               Table of MB attributes for redundant picture
 *
 * Function:
 *      For all macroblock in the picture:
 *        - if MB is not decoded in primary picture and is decoded in
 *          redundant picture, copy MB data (including contex data) from
 *          redundant picture to primary picture
 *
 * Returns:
 *      -
 *      
 */
void ercCombinePictures(errorConcealment_s *erc, errorConcealment_s *erc2,
                        frmBuf_s *reco, frmBuf_s *reco2,
                        mbAttributes_s *mbData, mbAttributes_s *mbData2,
                        int picCnt)
{
  int i, j, k, l;
  int mbAddr, blkAddr, pixAddr;
  int blksPerLine;

  mbAddr = 0;
  blksPerLine = reco->width / BLK_SIZE;

  for (j = 0; j < erc->heightMbs; j++) {
    for (i = 0; i < erc->widthMbs; i++, mbAddr++) {

      /* Should MB be copied from redundant picture? */
      if (erc->decodedMbs[j][i] == 0 && erc2->decodedMbs[j][i] != 0) {

        /*
         * Copy contex data
         */

        mbData->alphaOffset[mbAddr]   = mbData2->alphaOffset[mbAddr];
        mbData->betaOffset[mbAddr]    = mbData2->betaOffset[mbAddr];
        mbData->cbpTable[mbAddr]      = mbData2->cbpTable[mbAddr];
        mbData->filterModeTab[mbAddr] = mbData2->filterModeTab[mbAddr];
        mbData->mbTypeTable[mbAddr]   = mbData2->mbTypeTable[mbAddr];
        mbData->qpTable[mbAddr]       = mbData2->qpTable[mbAddr];
        /* Add picCnt to differentitate MBs of redundant pictures */
        mbData->sliceMap[mbAddr]      = mbData2->sliceMap[mbAddr] + (picCnt << 20);

        blkAddr = j * BLK_PER_MB * blksPerLine + i * BLK_PER_MB;

        for (l = 0; l < BLK_PER_MB; l++, blkAddr += (blksPerLine - BLK_PER_MB)) {
          for (k = 0; k < BLK_PER_MB; k++, blkAddr++) {
            mbData->motVecTable[blkAddr]   = mbData2->motVecTable[blkAddr];
            mbData->refIdxTable[blkAddr]   = mbData2->refIdxTable[blkAddr];
            mbData->refPicIDtable[blkAddr] = mbData2->refPicIDtable[blkAddr];
          }
        }

        /*
         * Copy pixel data
         */

        pixAddr = j * MBK_SIZE * reco->width + i * MBK_SIZE;

        for (l = 0; l < MBK_SIZE; l++, pixAddr += (reco->width - MBK_SIZE)) {
          for (k = 0; k < MBK_SIZE; k++, pixAddr++) {
            reco->y[pixAddr] = reco2->y[pixAddr];
          }
        }

        pixAddr = j * (MBK_SIZE/2) * (reco->width/2) + i * (MBK_SIZE/2);

        for (l = 0; l < MBK_SIZE/2; l++, pixAddr += (reco->width/2 - MBK_SIZE/2)) {
          for (k = 0; k < MBK_SIZE/2; k++, pixAddr++) {
            reco->u[pixAddr] = reco2->u[pixAddr];
            reco->v[pixAddr] = reco2->v[pixAddr];
          }
        }

        erc->decodedMbs[j][i] = 1;
      }
    }
  }
}

#endif  /* REDUNDANT_PIC_CONCEALMENT */


#endif  /* ERROR_CONCEALMENT */
