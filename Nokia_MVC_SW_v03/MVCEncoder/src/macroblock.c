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
 * macroblock.c
 *
 * Contains:
 *    Functions for macroblock layer.
 *
 */

#include <limits.h>
#include "globals.h"
#include "debug.h"
#include "bitbuffer.h"
#include "macroblock.h"
#include "intrapred.h"
#include "motest.h"
#include "motcomp.h"
#include "prederrorcod.h"
#include "prederrordec.h"
#include "stream.h"
#include "vlcutility.h"
#include "modedecision.h"
#include <math.h>
#include "ratecontrol.h"

//#define DBG_STATISTICS

static int32 qp2RdoLambda[52];


/*
 * Prototypes for static functions
 */
static void getOrigMB(macroblock_s *mb, frmBuf_s *orig, int width);


/*
 * mbkLoad
 *
 * Parameters:
 *      -
 *
 * Function:
 *      Initialize macroblock constants
 *      
 * Returns:
 *      -
 */
void mbkLoad()
{
  int qp;

  for (qp = 0; qp < 52; qp ++)
    // scaled by 1024
    qp2RdoLambda[qp] = (int32) (0.85 * 256 * pow (2, (qp - 12)/3.0) + 0.5);
  //qp2RdoLambda[qp] = (lambda * lambda * 85)/100;
}


/*
 * getOrigMB:
 *
 * Parameters:
 *      mb                    Macroblock object
 *      orig                  Pointer to original frame
 *      width                 Frame width
 *
 * Function:
 *      Copies original blocks from original frame
 *      
 * Returns:
 *      -
 */
static void getOrigMB(macroblock_s *mb, frmBuf_s *orig, int width)
{
  int i, j, k;
  int widthC = width>>1;
  int pixX, pixY;
  u_int8 *yPtr;
  int partSum;

  /*
   * Get luma blocks
   */
  pixX = mb->idxX * MBK_SIZE;
  pixY = mb->idxY * MBK_SIZE;
  yPtr = orig->y + pixY * width + pixX;

  // get MB pixels and calculate partial sums
  for (j = 0; j < MBK_SIZE; j += 4) {
    for (i = 0; i < MBK_SIZE; i += 4) {
      for (partSum = 0, k = 0; k < 4; k ++)
      {
        mb->origY[j+k][i+0] = yPtr[k * width + i + 0];
        partSum += mb->origY[j+k][i+0] ;
        mb->origY[j+k][i+1] = yPtr[k * width + i + 1];
        partSum += mb->origY[j+k][i+1];
        mb->origY[j+k][i+2] = yPtr[k * width + i + 2];
        partSum += mb->origY[j+k][i+2];
        mb->origY[j+k][i+3] = yPtr[k * width + i + 3];
        partSum += mb->origY[j+k][i+3];
      }
      mb->partSums4x4[j >> 2][i >> 2] = partSum;
    }
    yPtr += 4*width;
  }

  // 8x8 partial sums
  for (i = 0; i < 4; i += 2)
    for (j = 0; j < 4; j += 2)
    {
      mb->partSums[i][j] = 
        mb->partSums4x4[i][j]     + mb->partSums4x4[i][j + 1] +
        mb->partSums4x4[i + 1][j] + mb->partSums4x4[i + 1][j + 1];
    }

  /*
   * Get chroma blocks
   */
  pixX >>= 1;
  pixY >>= 1;

  for (j = 0; j < MBK_SIZE/2; j++) {
    for (i = 0; i < MBK_SIZE/2; i++) {
      mb->origC[j][           i] = orig->u[(pixY+j) * widthC + pixX+i];
      mb->origC[j][MBK_SIZE/2+i] = orig->v[(pixY+j) * widthC + pixX+i];
    }
  }
}


/*
 * mbkSetupNeighbors:
 *
 * Parameters:
 *      pMb                   Information related to motion estimation
 *
 * Function:
 *      Set up the pointers to the neighbors for all the blocks in all modes.
 *      Because we use the local buffers, most of the relationships are fixed.
 *      Relationships that could change will be modified in other function.
 *
 *      Each macroblock need to access up to 10 motion vectors from 4
 *      neighboring macroblocks. Those vectors will be stored in array 
 *      "surround" in ME profile. They are stored in the following order:
 *        0 - 3, 4 right-most vectors of left macroblock
 *        4 - 7, 4 bottom vectors of top macroblock
 *        8,     vector at lower-left corner of up-right macroblock
 *        9,     vector at lower-right corner of up-left macroblock
 *      Vectors of the current macroblock will be stored in array "current"
 *      in ME profile, in raster order, instead of coding order.
 *
 * Returns:
 *      -
 */
static void mbkSetupNeighbors(macroblock_s *mb)
{
  int i, blkX, blkY;
  blkState_s *s;
  blkState_s *c;

  s = mb->surround;
  c = & mb->current[0][0];

  // all the mode has the same left and top neighbor relationship
  for (i = 0; i < 16; i ++)
  {
    blkX = i % 4;
    blkY = i / 4;

    mb->blkLeft[i] = (blkX == 0) ? & s[blkY]     : & c[i - 1];
    mb->blkUp[i]   = (blkY == 0) ? & s[blkX + 4] : & c[i - 4];
  }

  // 16x16 and 16 x 8 can share the same up-right pointer arrays
  mb->blkUpRight[0][0]  = & s[8];  mb->blkUpRight[0][8]  = & s[1];
  
  // 8 x 16 and 8 x 8, and 8 x 4 can share the same up-right pointer arrays
  mb->blkUpRight[1][0]  = & s[6];  mb->blkUpRight[1][2]  = & s[8];     
  mb->blkUpRight[1][4]  = & s[0];  mb->blkUpRight[1][6]  = & c[1];     
  mb->blkUpRight[1][8]  = & c[6];  mb->blkUpRight[1][10] = & c[5];     
  mb->blkUpRight[1][12] = & s[2];  mb->blkUpRight[1][14] = & c[9];     

  // 4 x 8 and 4x4 can share the same pointer arrays
  for (i = 0; i < 16; i ++)
  {
    blkX = i % 4;
    blkY = i / 4;

    // assign the up-right neighboring block
    if (blkY == 0)
      mb->blkUpRight[2][i] = & s[blkX + 5];
    else if ((blkX & 1) != 0 && (blkY & 1) != 0)
      mb->blkUpRight[2][i] = & c[i - 5];
    else
      mb->blkUpRight[2][i] = & c[i - 3];
  }

  // exception
  mb->blkUpRight[2][11] = & c [6];

  mb->coeffElim = USE_COEF_ELIM;
  mb->coeffElimThLuma   = COEF_ELIM_TH_MB;      // threshold for 16x16 luma
  mb->coeffElimTh8x8    = COEF_ELIM_TH_BLK8x8;  // threshold for 8x8 luma
  mb->coeffElimThChroma = COEF_ELIM_TH_CHROMA;  // threshold for 8x8 chroma
}


/*
 * mbkInit:
 *
 * Parameters:
 *      mb                    Macroblock object
 *
 * Function:
 *      Set structure for intra mode and motion vector prediction.
 *      
 * Returns:
 *      -
 */
void mbkInit(macroblock_s *mb, int plr)
{
  mb->i4x4CornersAvail[1][1] = 0 | 1;           // 0, up-right, 1, up-left
  mb->i4x4CornersAvail[1][2] = 2 | 1;           // 1, up-right, 1, up-left
  mb->i4x4CornersAvail[1][3] = 0 | 1;           // 0, up-right, 1, up-left
  mb->i4x4CornersAvail[2][1] = 2 | 1;           // 1, up-right, 1, up-left
  mb->i4x4CornersAvail[2][2] = 2 | 1;           // 1, up-right, 1, up-left
  mb->i4x4CornersAvail[2][3] = 0 | 1;           // 0, up-right, 1, up-left
  mb->i4x4CornersAvail[3][1] = 0 | 1;           // 0, up-right, 1, up-left
  mb->i4x4CornersAvail[3][2] = 2 | 1;           // 1, up-right, 1, up-left
  mb->i4x4CornersAvail[3][3] = 0 | 1;           // 0, up-right, 1, up-left
  mbkSetupNeighbors(mb);

  // need a temporary buffer for doing test encoding, to count the bits
  bibOpen(& mb->mbBs, 256);
  mb->plr = plr;
}



/*
 * mbkRelease:
 *
 * Parameters:
 *      mb                    Macroblock object
 *
 * Function:
 *      Release any dynamic structures in macroblock.
 *      
 * Returns:
 *      -
 */
void mbkRelease(macroblock_s *mb)
{
  bibClose(& mb->mbBs);
}


/*
 * mbkStartEnc:
 *
 * Parameters:
 *      mb                    Macroblock object
 *      mbStateArr            Array of objects that store MB coding information
 *      orig                  Frame buffer of original frame
 *      reco                  Frame buffer of reconstructed frame
 *      encPar                Encoding parameters
 *      qp                    Quantization parameter
 *      tuneFactor            Factor for tuning rdoLambda based on user input
 *
 * Function:
 *      Setup macroblock object for encoding the current macroblock.
 *      
 * Returns:
 *      -
 */
void mbkStartEnc(macroblock_s *mb, 
                 mbState_s    *mbStateArr,
                 frmBuf_s     *orig, 
                 frmBuf_s     *reco,
                 encParams_s  *encPar, 
                 int          qp, 
                 int          tuneFactor)
{
  int pixX, pixY;
  int mbsPerLine;

  mbsPerLine = encPar->picWidth/MBK_SIZE;

  mb->blkAddr = (mb->idxY * BLK_PER_MB) * (encPar->picWidth/BLK_SIZE) + 
    mb->idxX * BLK_PER_MB;

  mb->mbThis    = mbStateArr + mb->mbAddr;
  mb->mbLeft    = mb->mbThis - 1;
  mb->mbUp      = mb->mbThis - mbsPerLine;
  mb->mbUpLeft  = mb->mbUp - 1;
  mb->mbUpRight = mb->mbUp + 1;

  pixX = mb->idxX * MBK_SIZE;
  pixY = mb->idxY * MBK_SIZE;

  // setup the pointers to the reconstructed frame buffer
  mb->recoY = reco->y + pixY * encPar->picWidth + pixX;
  mb->recoU = reco->u + (pixY >> 1) * (encPar->picWidth >> 1) + (pixX >> 1);
  mb->recoV = reco->v + (pixY >> 1) * (encPar->picWidth >> 1) + (pixX >> 1);

  // DT: check. The following two lines and 
  mb->qp  = qp;
  mb->qpC = qpChroma[clip(MIN_QP, MAX_QP, qp + encPar->chromaQpIdx)];

  mb->lambda = QP2QUANT[mb->qp];

#ifndef DISABLE_RDO
  // play with rdoLambda for inter and intra, if intra RDO is not enabled, smaller lambda is preferred!!!
  mb->rdoLambda = mb->rdoLambdaIntra = 
    (qp2RdoLambda[mb->qp] * tuneFactor + ((int32)1 << 15)) >> 16;

  if (mb->rdoLambda == 0)
    mb->rdoLambda = mb->rdoLambdaIntra = 1;
#endif

  getOrigMB(mb, orig, encPar->picWidth);
}


/*
 * getMbAvailability:
 *
 * Parameters:
 *      mb                  Macroblock object
 *      picWidth            Picture width
 *      constrainedIntra    Constrained intra prediction flag
 *
 * Function:
 *      Get neighboring macroblock availability info
 *      
 * Returns:
 *      -
 */
static void getMbAvailability(macroblock_s *mb, 
                              int          picWidth, 
                              int          constrainedIntra)
{
  int i, mbsPerLine;
  int currSliceIdx;

  mbsPerLine = picWidth/MBK_SIZE;
  
  currSliceIdx = mb->mbThis->sliceMap;

  // let's set them to unavailable at first
  for (i = 0; i < 4; i ++)
  {
    mb->mbAvailMap[i] = 0;
    mb->mbAvailMapIntra[i] = 0;
  }

  // Check availability of left macroblock
  if (mb->idxX > 0 && mb->mbLeft->sliceMap == currSliceIdx) {
    mb->mbAvailMap[0] = 1;
    mb->mbAvailMapIntra[0] = (! constrainedIntra) || 
      (mb->mbLeft->mbType <= MB_TYPE_INTRA_16x16);
  }

  /*
   * Check availability of upper macroblock
   */
  if (mb->idxY > 0)
  {
    if (mb->mbUp->sliceMap == currSliceIdx) {
      mb->mbAvailMap[1] = 1;
      mb->mbAvailMapIntra[1] = 
        (! constrainedIntra) || (mb->mbUp->mbType <= MB_TYPE_INTRA_16x16);
    }

    /*
     * Check availability of upper-right macroblock
     */
    if (mb->idxX + 1 < mbsPerLine && mb->mbUpRight->sliceMap == currSliceIdx) {
      mb->mbAvailMap[2] = 1;
      mb->mbAvailMapIntra[2] = 
        (! constrainedIntra) || (mb->mbUpRight->mbType <= MB_TYPE_INTRA_16x16);
    }

    /*
    * Check availability of upper-left macroblock
    */
    if (mb->idxX > 0 && mb->mbUpLeft->sliceMap == currSliceIdx) {
      mb->mbAvailMap[3] = 1;
      mb->mbAvailMapIntra[3] = 
        (! constrainedIntra) || (mb->mbUpLeft->mbType <= MB_TYPE_INTRA_16x16);
    }
  }
  
  // --------------------------------------------------------------------------
  // additional intra MB parameter setup

  // availability of the MB above the current macroblock
  // should always be aligned at 32-bit boundary

  // IPR_MODE_DC is chosen to tell the block is available
  mb->i4x4CornersAvail[1][0] = mb->i4x4CornersAvail[2][0] = 
    mb->i4x4CornersAvail[3][0] = (u_int8)((mb->mbAvailMapIntra[0]) ? 3 : 2);

  // fill the changing slots in upRightMode and upLeftMode
  mb->i4x4CornersAvail[0][0] = (u_int8)
    (((mb->mbAvailMapIntra[1] != 0) << 1) + (mb->mbAvailMapIntra[3] != 0));

  mb->i4x4CornersAvail[0][1] = mb->i4x4CornersAvail[0][2] = (u_int8)
    ((mb->mbAvailMapIntra[1]) ? 3 : 0);

  mb->i4x4CornersAvail[0][3] = (u_int8)
    (((mb->mbAvailMapIntra[2] != 0) << 1) + (mb->mbAvailMapIntra[1] != 0));
}


/*
 *
 * mbkLoadNeighbors:
 *
 * Parameters:
 *      pMb                 Macroblock information
 *
 * Function:
 *      Load all the related neighboring motion vectors in local storage
 *      "surround". Change the pointer directions if some macroblock
 *      becomes available or unavailable.
 *      We do it once for a macroblock, so do not need to worry about the 
 *      relationship in the motion estimation.
 *
 * Returns:
 *      -
 *
 */
static void mbkLoadNeighbors(macroblock_s *pMb)
{
  int i;
  blkState_s *s;

  blkState_s blkStateNA = {{0, 0}, REF_NA, IPR_MODE_NA, 0};
  motVec_s zeroVec = {0, 0};

  s = pMb->surround;

  // point to the start of the current macroblock
  if (pMb->mbAvailMap[0])
  {
    for (i = 0; i < 4; i ++)
    {
      s[i] = pMb->mbLeft->blkInfo[i][3];
      if (! pMb->mbAvailMapIntra[0])      // inter and constrainIntra
        s[i].i4x4Mode = IPR_MODE_NA;
    }
  }
  else
    for (i = 0; i < 4; i ++)
      s[i] = blkStateNA;

  if (pMb->mbAvailMap[1])
  {
    for (i = 0; i < 4; i ++)
    {
      s[i + 4] = pMb->mbUp->blkInfo[3][i];
      if (! pMb->mbAvailMapIntra[1])      // inter and constrainIntra
        s[i + 4].i4x4Mode = IPR_MODE_NA;
    }
  }
  else
    for (i = 0; i < 4; i ++)
      s[i + 4] = blkStateNA;

  // up-right and up-left corners
  s[8] = (pMb->mbAvailMap[2]) ? pMb->mbUpRight->blkInfo[3][0] : blkStateNA;
  s[9] = (pMb->mbAvailMap[3]) ? pMb->mbUpLeft->blkInfo[3][3]  : blkStateNA;

  // we need have to re-direct some pointers if the mbAvailMap has changed
  if (pMb->mbAvailMap[1])
  {
    pMb->blkUpRight[1][0] = & s[6];
    pMb->blkUpRight[2][0] = & s[5];
  }
  else
  {
    pMb->blkUpRight[1][0] = & s[9];
    pMb->blkUpRight[2][0] = & s[9];
  }

  if (pMb->mbAvailMap[2])
  {
    // some pointers may have been re-directed
    pMb->blkUpRight[0][0] = & s[8];
    pMb->blkUpRight[1][2] = & s[8];
    pMb->blkUpRight[2][3] = & s[8];
  }
  else
  {
    // redirect the pointers to use vecD as vecC
    pMb->blkUpRight[0][0] = & s[9];
    pMb->blkUpRight[1][2] = & s[5];
    pMb->blkUpRight[2][3] = & s[6];
  }

  // calculate the MV predictor for skipped MB
  if (! pMb->mbAvailMap[0] || ! pMb->mbAvailMap[1] ||
    ((s[0].ref | s[0].mv.x | s[0].mv.y) == 0) ||
    ((s[4].ref | s[4].mv.x | s[4].mv.y) == 0))
  {
    pMb->skipPredMv = zeroVec;
  }
  else
    pMb->skipPredMv = mcpFindPredMv(pMb, 0, MOT_16x16, 0);
}


#ifdef DBG_STATISTICS
int intra16x16Count = 0;
int intra4x4Count = 0;
int inter = 0;
#endif

/*
 * mbkRasterCbpY:
 *
 * Parameters:
 *      cbpY                  Macroblock object
 *
 * Function:
 *      Convert cbpY from coding order to raster order. 
 *      
 * Returns:
 *      cbpY in raster order.
 */
static unsigned int mbkRasterCbpY(unsigned int cbpY)
{
  unsigned int rasterCbp;

  rasterCbp  = cbpY & 0xC3C3;       // those are not changed
  rasterCbp |= (cbpY & 0x000C) << 2;
  rasterCbp |= (cbpY & 0x0030) >> 2;
  rasterCbp |= (cbpY & 0x0C00) << 2;
  rasterCbp |= (cbpY & 0x3000) >> 2;

  return rasterCbp;
}


/*
 * mbkProcessData:
 *
 * Parameters:
 *      mb                    Macroblock object
 *      picType               Picture type (intra/inter)
 *      encPar                Encoding parameters (motion range, etc.)
 *
 * Function:
 *      Perform forward and backward transform/quatization. 
 *      
 * Returns:
 *      -
 */
void mbkProcessData(macroblock_s *mb, 
                    int          picType, 
                    encParams_s  *encPar)
{
  void *predPtr;


  /*
   * Transform, quantization & reconstruction
   */
  if (mb->type == MBK_INTER && mb->interMode == MOT_COPY)
  {
    // only need to get predicted MB to the reconstructed frame buffer
    // Setup the cbp, and let pedRecoLumaMB do the copying operations
    mb->cbpY = 0;
    mb->rastercbpY  = 0;
    mb->cbpChromaDC = 0;
    mb->cbpC = 0;
    mb->minMSE = 0;

    pedRecoLumaMB(mb, mb->predY, 0, encPar->picWidth);
    pedRecoChromaMB(mb, mb->predC, encPar->picWidth >> 1);

    return;
  }

  /* If 4x4 intra mode, luma prediction error is already transformed */
  if (! (mb->type == MBK_INTRA && mb->intraType == MBK_INTRA_TYPE1)) {
    int skip;

    if (mb->type == MBK_INTRA)
    {
      // mb->type == MBK_INTRA, must be intra16x16
      predPtr = mb->predBlk2[mb->intra16x16mode];
      skip = 1;
    }
    else
    {
      predPtr = mb->predY;
      skip = 0;
    }

    mb->minMSE =  CalculateSad
     (& mb->origY[0][0],     16, predPtr, 16, 16, 16);  

    pecCodeLumaMB(mb, predPtr, skip, picType);
    pedRecoLumaMB(mb, predPtr, skip, encPar->picWidth);
  }

  predPtr = (mb->type == MBK_INTRA) ? 
    mb->predIntraC[mb->intraModeChroma] : mb->predC;

  pecCodeChromaMB(mb, predPtr, picType);
  pedRecoChromaMB(mb, predPtr, encPar->picWidth >> 1);

  mb->rastercbpY = mbkRasterCbpY(mb->cbpY);
}


/*
 * mbkSend:
 *
 * Parameters:
 *      stream                Generic stream buffer, bitbuffer/arith encoder
 *      mb                    Macroblock object
 *      nRefFrames            Number of reference frames in use
 *      picType               Picture type (intra/inter)
 *      stat                  Statistics
 *
 * Function:
 *      Code macroblock using VLC. 
 *      
 * Returns:
 *      Number of bits spent on encoding luma component.
 */
int mbkSend(void         *stream, 
            macroblock_s *mb, 
            int          nRefFrames, 
            int          picType,
            statSlice_s  *stat)
{
  int lumaBits;


  if (mb->type == MBK_INTER && mb->interMode == MOT_16x16 &&
    (mb->cbpY | mb->cbpChromaDC | mb->cbpC) == 0)
  {
    if ((mb->current[0][0].ref == 0) &&
      (mb->current[0][0].mv.x == mb->skipPredMv.x) &&
      (mb->current[0][0].mv.y == mb->skipPredMv.y))
      mb->interMode = MOT_COPY;
  }

  // set the bits related to mbType, and MVs
  if (IS_SLICE_P(picType))
  {
    int i, j, skipFlag;

    skipFlag = (mb->type == MBK_INTER) && (mb->interMode == MOT_COPY);
    stat->bitsSkipLen += streamSendMbSkipFlag(stream,
      mb, skipFlag);

    if (skipFlag)
    {
      for (j = 0; j < 4; j ++)
        for (i = 0; i < 4; i ++)
          mb->current[j][i].numLumaCoefs = 0;

#ifdef COPY_4_BYTES_AS_32_BITS
      * ((u_int32 *) & mb->mbThis->numChromaCoefs[0][0][0]) = 0;
      * ((u_int32 *) & mb->mbThis->numChromaCoefs[1][0][0]) = 0;
#else
      mb->mbThis->numChromaCoefs[0][0][0] = mb->mbThis->numChromaCoefs[0][0][1] =
      mb->mbThis->numChromaCoefs[1][0][0] = mb->mbThis->numChromaCoefs[1][0][1] =
      mb->mbThis->numChromaCoefs[0][1][0] = mb->mbThis->numChromaCoefs[0][1][1] =
      mb->mbThis->numChromaCoefs[1][1][0] = mb->mbThis->numChromaCoefs[1][1][1] = 0;
#endif

      mb->qp = mb->prevQp;
      mb->deltaQp = 0;

      return 0;
    }
  }

  streamSendMbHeader(stream,
    mb, nRefFrames, picType, stat);

  // Send transform coefficients
  lumaBits = streamSendLumaCoeffs(stream,
    mb, stat);

  streamSendChromaCoeffs(stream,
    mb, stat);

  return lumaBits;
}


/*
 * mbkBeforeSlice:
 *
 * Parameters:
 *      mb                    Macroblock object
 *      sliceQp               Slice qp
 *
 * Function:
 *      Macroblock initialization before the slice is encoded. 
 *      
 * Returns:
 *      -
 */
void mbkBeforeSlice(macroblock_s *mb,
                    int          sliceQp)
{
  mb->numSkipped  = 0;
  mb->prevQp      = sliceQp;
}


/*
 * mbkFinishEnc:
 *
 * Parameters:
 *      mb                    Macroblock object
 *      stat                  Statistics
 *
 * Function:
 *      Save state information after the macroblock is encoded. 
 *      
 * Returns:
 *      -
 */
void mbkFinishEnc(macroblock_s *mb,
                  statSlice_s  *stat)
{
  int i, j;

#ifdef DEBUG_DUMP
  {
    int picWidth;

    picWidth = mbData->blksPerLine * BLK_SIZE;

    mb->ssdY  = CalculateSsd
      (& mb->origY[0][0], 16, mb->recoY, picWidth, 16, 16);

    mb->ssdCb = CalculateSsd
      (& mb->origC[0][0], 16, mb->recoU, picWidth >> 1, 8, 8);

    mb->ssdCr = CalculateSsd
      (& mb->origC[0][8], 16, mb->recoV, picWidth >> 1, 8, 8);
  }
#endif

  /* Store CBP, qp, mbType for loopfilter */

  // change cbpY order, so we do not have to modify loop filter implementation
  mb->mbThis->cbp = (int32)mb->rastercbpY | ((int32)mb->cbpC << 16) |
    ((int32)(mb->lumaNonzeroDC != 0) << 24) | ((int32)mb->cbpChromaDC << 25);

  mb->mbThis->qp  = (int8) mb->qp;
  mb->mbThis->intraModeChroma = (int8) mb->intraModeChroma;
  
  if (mb->type == MBK_INTRA)
  {
    mb->mbThis->mbType = (int8)((mb->intraType == MBK_INTRA_TYPE1) 
      ? MB_TYPE_INTRA_4x4 : MB_TYPE_INTRA_16x16);
  }
  else
    // mb->interMode = 2, MOT_COPY (skipped MOT_16x16)
    mb->mbThis->mbType = (int8)(mb->interMode + 2);

  // Copy motion vectors of the best model to motion vector buffer
  for (j = 0; j < BLK_PER_MB;  j ++)
    for (i = 0; i < BLK_PER_MB;  i ++)
      mb->mbThis->blkInfo[j][i] = mb->current[j][i];

  /*
   * Update MB mode statistics
   */
  if (mb->type == MBK_INTRA) {
    if (mb->intraType == MBK_INTRA_TYPE1)
      stat->intraModeCtr1 += 1;
    else
      stat->intraModeCtr2[mb->intra16x16mode] += 1;
  }
  else
    stat->interModeCtr[mb->interMode] += 1;         // temporary
}


void mbkModeSelection(rateCtrl_s        *pbRC,
                         macroblock_s   *mb, 
                         meProfile_s    *pMeProf,
                         refFrmBuf_s    **refBufList,
                         int            nRefFrames, 
                         int            picType,
                         encParams_s    *encPar,
                         int            *mapRIR,
                         int32          *channelDistortion,
                         int            forcedIRNo,
                         int            *forcedIR,
                         int            mbNum,
                         int            *AIR_intraMap)

{
  
  int i, j;
  costMeasure_s intraCost, interCost, intra16x16Cost, intra4x4Cost;
  double thr;
  int picWidth;
  int mbkPerLine;
  int chromaIntraSad;
  int constrainedIntra;
  int chromaModeAvail[IPR_CHROMA_NUM_MODES];
  int fIntra;
  int8 i4x4Modes[4][4];
  u_int8 colMbY[MBK_SIZE][MBK_SIZE];
  u_int8 colMbC[MBK_SIZE/2][2 * (MBK_SIZE/2)];
  int ssd0 = 0;
  int scale;
  int qp;

#ifndef DISABLE_RDO
  encPar->rdo |= 
    RDO_INTRA_LUMA_4x4 | 
    RDO_INTRA_CHROMA |
//    RDO_INTRA_LUMA_16x16 |
    RDO_INTER;
#endif

#ifndef DISABLE_RDO
  if((encPar->rdo & 0x0F) == MODE_DECISION_RDO)
    scale = 1;
  else
#endif
    scale = 3;

  if(encPar->irType != PDT_IR)
    scale = 0;
  
  picWidth = encPar->picWidth;
  mbkPerLine = picWidth / MBK_SIZE;

  fIntra = 0;
  
  if(encPar->nRandomIntraRefresh != 0 ) {
    for (i = 0; i < encPar->nRandomIntraRefresh; i ++) {
      if (mapRIR[i] == mb->mbAddr)
        fIntra = 1 ;//Force Intra
    }
  }

  // An MB is forced to be Intra Refreshed with fixed frequecy
  if ((encPar->irType == PDT_IR_LC || encPar->irType == PDT_IR) && forcedIRNo > 0) {
    if (forcedIR[mbNum] == 0) 
      fIntra=1;    
    forcedIR[mbNum]--;
  }

  if (encPar->irType == PDT_IR_LC )
  {
    if(AIR_intraMap[mbNum] == 1)
      fIntra=1;      
   }
    
  constrainedIntra = encPar->constIpred && (IS_SLICE_P(picType));
  getMbAvailability(mb, picWidth, constrainedIntra);

  // If inter picture, find best inter mode
  interCost = initCostMeasure;

  // set the initial condition of the macroblock, and calculate skipPredMv
  mbkLoadNeighbors(mb);

  qp = rc_getMBQP(pbRC,picType,mb->idxY*mbkPerLine+mb->idxX);
  
  if(qp != -1)
    mb->qp = qp;
  
  mb->qpC = qpChroma[clip(MIN_QP, MAX_QP, mb->qp + encPar->chromaQpIdx)];
  
  if (IS_SLICE_P(picType) && !(fIntra==1)) {      // picType == IMG_INTER
    int interSad;

    // Do Motion Search and find the best mode based on SAD
    interSad = mesFindMotionFullSearch(mb, pMeProf, refBufList, nRefFrames);

    if(encPar->irType == PDT_IR || encPar->irType == PDT_IR_LC)
    {
      // get the colocated MB
      mcpGetColocatedMb(mb, refBufList, colMbY, colMbC);

#ifndef DISABLE_RDO
      if((encPar->rdo & 0x0F) == MODE_DECISION_RDO)
      {
        scale = 1;
        // calculate the MSE between current and previous MB, it will be used as a metric of channel distortion
        ssd0  = CalculateSsd
          (& mb->origY[0][0],     16, &colMbY[0][0],     16, 16, 16);         
      }
      else
#endif
      {
        // calculate the SAD between current and previous MB, it will be used as a metric of channel distortion
        ssd0  = CalculateSad
          (& mb->origY[0][0],     16, &colMbY[0][0],     16, 16, 16);     
      }
    }

    //If RDO is disabled, the best inter-mode is selected by the above function
#ifndef DISABLE_RDO
    mdInterModeDecision(mb, refBufList, nRefFrames, picWidth, picType, 
      encPar->rdo, ssd0, & interCost);
#else
    mdInterModeDecision(mb, refBufList, nRefFrames, picWidth, picType, 
      0, ssd0, & interCost);
#endif

    interCost.sad = interSad;
    mb->actualInterSad = interSad;           // DBG

    // prefer inter by 4 lambda
    interCost.sad -= mb->lambda * 4;

#ifndef DISABLE_RDO
    if ((encPar->rdo & 0x0F) != MODE_DECISION_RDO) {
#endif
     interCost.cost = interCost.sad;
#ifndef DISABLE_RDO
    }
#endif
  }
  
  // Update search window if we skipped motion estimation
  // If forced intra MB in P slice we still need to update search window
  if (IS_SLICE_P(picType) && fIntra == 1) {
#ifdef ENABLE_SEARCH_WINDOW
    mesUpdateSearchWin(mb);
#endif
    interCost.sad = INT_MAX;
    interCost.cost = INT_MAX;
    if(encPar->irType == PDT_IR || encPar->irType == PDT_IR_LC)
    {
      // get the colocated MB   
      mcpGetColocatedMb(mb, refBufList, mb->predY, mb->predC);
      
      // calculate the SAD between current and previous MB, it will be used as a metric of channel distortion
      ssd0  = CalculateSad
        (& mb->origY[0][0],     16, &mb->predY[0][0],     16, 16, 16);      
      
    }
  }

  if(IS_SLICE_I(picType) || pMeProf->goodEarlyMatch == 0 || fIntra == 1)
  {
  // --------------------------------------------------------------------------
  // Find the best 16x16 intra prediction
  
  intra16x16Cost = initCostMeasure;

  if (mb->qp >= MIN_QP + 12)
    mb->intra16x16enabled = 1;
  else
    mb->intra16x16enabled = 0;

  if (mb->intra16x16enabled) {
    //   : skip whole 16x16 check when inter cost small
    if ( ((pMeProf->lc3.low_complex_prof3) && (interCost.sad>TH_IPR_16x16) )
            || (! pMeProf->lc3.low_complex_prof3) 
            || (encPar->irType == PDT_IR) || (fIntra == 1)) {

#ifndef DISABLE_RDO
       if(encPar->irType == PDT_IR || fIntra == 1)
      mdIntraPredLuma16x16(mb, picWidth, picType, 
           MAX_COST, encPar->rdo, & intra16x16Cost, encPar->low_complex_prof3);
       else
         mdIntraPredLuma16x16(mb, picWidth, picType, 
           interCost.sad, encPar->rdo, & intra16x16Cost, encPar->low_complex_prof3);
#else
       if(encPar->irType == PDT_IR || fIntra == 1)
      mdIntraPredLuma16x16(mb, picWidth, picType, 
         MAX_COST, 0, & intra16x16Cost, encPar->low_complex_prof3);
       else
          mdIntraPredLuma16x16(mb, picWidth, picType, 
            interCost.sad, 0, & intra16x16Cost, encPar->low_complex_prof3);
#endif

    }
  }

  // Find the best 4x4 intra prediction

  /* Compute error threshold for doing 4x4 intra search */
  if (!IS_SLICE_I(picType) 
#ifndef DISABLE_RDO
    && (encPar->rdo & 0x0F) != MODE_DECISION_RDO
#endif
    )
    thr = -0.000933 * (mb->qp-12) * (mb->qp-12) - 0.004673 * (mb->qp-12) + 2.133227;
  else
    thr = MAX_COST;

  // --------------------------------------------------------------------------
  // Get intra 4x4 predictions and choose best of 4x4 mode and 16x16 mode.
  // Only if inter error is small enough, 4x4 intra is not checked.
  intra4x4Cost = initCostMeasure;

  if (IS_SLICE_I(picType) || !mb->intra16x16enabled || thr*interCost.sad > intra16x16Cost.sad  )  {
  //if (IS_SLICE_I(picType) || !mb->intra16x16enabled || thr*interCost.sad > intra16x16Cost.sad || encPar->irType == PDT_IR || fIntra == 1)  {

    //  : intra pred
    if (( (pMeProf->lc3.low_complex_prof3) && (intra16x16Cost.sad>TH_IPR_4x4) ) 
        || (! pMeProf->lc3.low_complex_prof3) 
        || (encPar->irType == PDT_IR) || (fIntra == 1))
    {

#ifndef DISABLE_RDO
      if(encPar->irType == PDT_IR || fIntra == 1)
         mdIntraPredLuma4x4(mb, picWidth, picType, MAX_COST, 
        encPar->rdo & 0x0F, & intra4x4Cost);
      else
         mdIntraPredLuma4x4(mb, picWidth, picType, interCost.sad, 
        encPar->rdo & 0x0F, & intra4x4Cost);
             
#else
      if(encPar->irType == PDT_IR || fIntra == 1)
       mdIntraPredLuma4x4(mb, picWidth, picType, MAX_COST, 
        0, & intra4x4Cost);
      else
         mdIntraPredLuma4x4(mb, picWidth, picType, interCost.sad, 
         0, & intra4x4Cost);

#endif

      // save i4x4 modes here, buffer "current" will be used for other purpose
      for (j = 0; j < 4; j ++)
        for (i = 0; i < 4; i ++)
          i4x4Modes[j][i] = mb->current[j][i].i4x4Mode;
    }
  }
 
#ifndef DISABLE_RDO
  mdIntraModeDecision(mb, refBufList, picWidth, picType, encPar->rdo, ssd0,
    & intra16x16Cost, & intra4x4Cost, & intraCost);
#else
  mdIntraModeDecision(mb, refBufList, picWidth, picType, 0, ssd0,
    & intra16x16Cost, & intra4x4Cost, & intraCost);
#endif

  
  // --------------------------------------------------------------------------
  // Choose the better one between intra and inter

  //printf("%d %d\n",mdGetCost(mb, &intraCost, scale),mdGetCost(mb, &interCost, scale));
  if (IS_SLICE_I(picType) || (mdGetCost(mb, &intraCost, scale) < mdGetCost(mb, &interCost, scale)) || fIntra == 1) {
  
    int mbType, i, numNonPredicted;

    mb->type = MBK_INTRA;
    
    
    // calculate the actual SAD by excluding the syntax bits
    mbType = ((IS_SLICE_P(picType)) ? 5 : 0) + streamGetMbTypeIntra
      (mb->intraType, mb->intra16x16mode, 0, 0, 0);

    mb->intraSyntaxBits = uvlcBitsUnsigned[mbType]; 

    // bits on sending 4x4 intra prediction modes
    if (mb->intraType == MBK_INTRA_TYPE1)
    {
      numNonPredicted = 0;
      for (i = 0; i < 16; i ++)
        if (mb->ipTab[i] >= 0)
          numNonPredicted ++;
      mb->intraSyntaxBits += 16 + numNonPredicted * 3;
    }

    mb->minSad = intraCost.sad;
    mb->minActualSad = mb->actualIntraSad;
//    mb->minMSE = intraCost.mse;
  }
  else {
    
    mb->type   = MBK_INTER;
    mb->minSad = interCost.sad;
    mb->minActualSad = mb->actualInterSad;
//    mb->minMSE = interCost.mse;
  }
  }
  else
  {

    mb->type   = MBK_INTER;
    mb->minSad = interCost.sad;
    mb->minActualSad = mb->actualInterSad;
//    mb->minMSE = interCost.mse;
  }

  if(pbRC->bit_rate > 0) {
    
    if (
      (mb->type == MBK_INTER) &&
      (mb->modeMvRef[MOT_16x16][0].ref == 0) &&
      (mb->modeMvRef[MOT_16x16][0].mv.x == mb->skipPredMv.x) &&
      (mb->modeMvRef[MOT_16x16][0].mv.y == mb->skipPredMv.y) && 
      mbNum>0)
      
      
      pbRC->currentFrame_MBQp[mbNum]=pbRC->currentFrame_MBQp[mbNum-1];      
    else
      pbRC->currentFrame_MBQp[mbNum]=mb->qp;   
    
  }
        
  // get the data ready for encoding
  if (mb->type == MBK_INTRA)
  {
    if (mb->intraType == MBK_INTRA_TYPE2)
      for (j = 0; j < BLK_PER_MB;  j ++)
        for (i = 0; i < BLK_PER_MB;  i ++)
          i4x4Modes[j][i] = IPR_MODE_DC;

    for (j = 0; j < BLK_PER_MB;  j ++) {
      for (i = 0; i < BLK_PER_MB;  i ++) {
        mb->current[j][i].mv.x = 0;
        mb->current[j][i].mv.y = 0;
        mb->current[j][i].ref  = -1;    // available but intra
        mb->current[j][i].i4x4Mode = i4x4Modes[j][i];
      }
    }
   
    // perform chroma prediction
#ifndef DISABLE_RDO
    if ((encPar->rdo & 0x0F) != MODE_DECISION_RDO)
#endif
    {
      iprGetPredChroma(mb->predIntraC, chromaModeAvail, mb->recoU, mb->recoV, 
        picWidth >> 1, mb->mbAvailMapIntra);

#ifndef DISABLE_RDO
      chromaIntraSad = mdIntraPredChroma(mb, chromaModeAvail, ((encPar->rdo & 0xf) != MODE_DECISION_SIMPLE));
#else
      chromaIntraSad = mdIntraPredChroma(mb, chromaModeAvail, 1);
#endif
    }
  }
  else
  {
    int8 interI4x4Mode;


   // get the inter pixel predictors
    mcpGetPred(mb, refBufList);
    
    // set the i4x4Mode according to constrainedIntra
    interI4x4Mode = (int8)((constrainedIntra) ? IPR_MODE_NA : IPR_MODE_DC);
    for (j = 0; j < BLK_PER_MB;  j ++)
      for (i = 0; i < BLK_PER_MB;  i ++)
        mb->current[j][i].i4x4Mode = interI4x4Mode;
  }

  // if Intra coded, forced Intra Refresh is postponed. 
  if (forcedIRNo > 0 && mb->type == MBK_INTRA) {
    if (forcedIR[mbNum] < 2*FORCE_INTRA_FREQUENCY)
      forcedIR[mbNum] += forcedIRNo+1;
  }

  // update the channel distortion 
  if (channelDistortion) {
    if (mb->type == MBK_INTRA)
      channelDistortion[mb->idxY*mbkPerLine+mb->idxX] = intraCost.cDistortion;
    else
      channelDistortion[mb->idxY*mbkPerLine+mb->idxX] = interCost.cDistortion;
  }
}
