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
 *    Functions for handling macroblock layer
 *
 */

#include <stdio.h>
#include "nccglob.h"
#include "globals.h"
#include "bitbuffer.h"
#include "macroblock.h"
#include "intrapred.h"
#include "motcomp.h"
#include "prederrordec.h"
#include "loopfilter.h"
#include "framebuffer.h"
#include "vld.h"
#include "time.h"


/*
 * Static functions
 */
static int getMacroblock(macroblock_s *mb, int numRefFrames,
                         int8 *ipTab, int8 **numCoefUpPred, int diffVecs[][2],
                         int picType, int chromaQpIdx, bitbuffer_s *bitbuf);

static int getMbAvailability(macroblock_s *mb, mbAttributes_s *mbData,
                             int picWidth, int constrainedIntra);



/*
 *
 * getMacroblock:
 *
 * Parameters:
 *      mb                    Macroblock parameters
 *      multRef               1 -> multiple reference frames used
 *      ipTab                 Macroblock intra pred. modes
 *      numCoefUpPred         Block coefficient counts of upper MBs
 *      diffVecs              Macroblock delta motion vectors
 *      picType               Picture type (intra/inter)
 *      chromaQpIdx           Chroma QP index relative to luma QP
 *      bitbuf                Bitbuffer handle
 *
 * Function:
 *      Get macroblock parameters from bitbuffer
 *      
 * Returns:
 *      MBK_OK for no error, MBK_ERROR for error
 *
 */
static int getMacroblock(macroblock_s *mb, int numRefFrames,
                         int8 *ipTab, int8 **numCoefUpPred, int diffVecs[][2],
                         int picType, int chromaQpIdx, bitbuffer_s *bitbuf)
{
  int numVecs;
  int delta_qp;
  int8 *numCoefPtrY, *numCoefPtrU, *numCoefPtrV;
  int retCode;


  numCoefPtrY = &numCoefUpPred[0][mb->blkX];
  numCoefPtrU = &numCoefUpPred[1][mb->blkX>>1];
  numCoefPtrV = &numCoefUpPred[2][mb->blkX>>1];

  /*
   * Get Macroblock type
   */

  /* Check if we have to fetch run indicator */
  if ((! IS_SLICE_I(picType)) && mb->numSkipped < 0) {

    mb->numSkipped = vldGetRunIndicator(bitbuf);

    if (bibGetStatus(bitbuf) < 0)
      return MBK_ERROR;
  }

  if ((! IS_SLICE_I(picType)) && mb->numSkipped > 0) {
    /* If skipped MBs, set MB to COPY */
    mb->type = MB_TYPE_INTER_SKIPPED;
    mb->interMode = MOT_COPY;
    mb->refNum[0] = 0;
    mb->cbpY = mb->cbpChromaDC = mb->cbpC = 0;
    mb->numSkipped -= 1;

    vldGetZeroLumaCoeffs(numCoefPtrY, mb->numCoefLeftPred);
    vldGetZeroChromaCoeffs(numCoefPtrU, numCoefPtrV, mb->numCoefLeftPredC);

    return MBK_OK;
  }
  else {

    if (vldGetMBtype(bitbuf, mb, picType) < 0) {
      printf("Error: illegal MB type\n");
      return MBK_ERROR;
    }

    mb->numSkipped -= 1;
  }

  if (MBK_IS_INTRA_PCM(mb->type)) {
    vldGetAllCoeffs(numCoefPtrY, numCoefPtrU, numCoefPtrV,
                    mb->numCoefLeftPred, mb->numCoefLeftPredC);
    return MBK_OK;
  }

  /*
   * 4x4 intra prediction modes 
   */
  if (MBK_IS_INTRA_4x4(mb->type)) {

    if (vldGetIntraPred(bitbuf, ipTab) < 0) {
      printf("Error: illegal intra pred\n");
      return MBK_ERROR;
    }
  }

  /*
   * 8x8 chroma intra prediction mode
   */
  if (MBK_IS_INTRA(mb->type)) {

    mb->intraModeChroma = vldGetChromaIntraPred(bitbuf);

    if (mb->intraModeChroma < 0) {
      printf("Error: illegal chroma intra pred\n");
      return MBK_ERROR;
    }
  }

  /*
   * Reference frame number and motion vectors
   */
  if (MBK_IS_INTER(mb->type)) {

    numVecs = mcpGetNumMotVecs(mb->interMode, mb->subMbModes);
    mb->numMotVecs = numVecs;

    retCode = vldGetMotVecs(bitbuf, mb->interMode, numRefFrames,
                            mb->refNum, diffVecs, numVecs);

    if (retCode < 0) {
      printf("Error: illegal motion vectors\n");
      return MBK_ERROR;
    }
  }

  /*
   * Coded block pattern
   */
  if (!MBK_IS_INTRA_16x16(mb->type)) {

    retCode = vldGetCBP(bitbuf, mb->type, &mb->cbpY, &mb->cbpChromaDC, &mb->cbpC);

    if (retCode < 0) {
      printf("Error: illegal CBP\n");
      return MBK_ERROR;
    }
  }


  /* Delta QP */
  if (MBK_IS_INTRA_16x16(mb->type) || 
      (mb->cbpY | mb->cbpChromaDC | mb->cbpC) != 0)
  {
    retCode = vldGetDeltaqp(bitbuf, &delta_qp);

    if (retCode < 0 || delta_qp < -(MAX_QP-MIN_QP+1)/2 || delta_qp >= (MAX_QP-MIN_QP+1)/2) {
      printf("Error: illegal delta qp\n");
      return MBK_ERROR;
    }

    if (delta_qp != 0) {
      int qp = mb->qp + delta_qp;
      if (qp < MIN_QP)
        qp += (MAX_QP-MIN_QP+1);
      if (qp > MAX_QP)
        qp -= (MAX_QP-MIN_QP+1);
      mb->qp = qp;
      mb->qpC = qpChroma[clip(MIN_QP, MAX_QP, mb->qp + chromaQpIdx)];
    }
  }


  /*
   * Get transform coefficients
   */

  /*
   * Luma DC coefficients (if 16x16 intra)
   */
  if (MBK_IS_INTRA_16x16(mb->type)) {

    retCode = vldGetLumaDCcoeffs(bitbuf, mb->dcCoefY, numCoefPtrY,
                             mb->numCoefLeftPred, mb->mbAvailBits);
    if (retCode < 0) {
      printf("Error: illegal luma DC coefficient\n");
      return MBK_ERROR;
    }
  }

  /*
   * Luma AC coefficients
   */
  if (mb->cbpY != 0) {

    retCode = vldGetLumaCoeffs(bitbuf, mb->type, &mb->cbpY,
                               mb->coefY, numCoefPtrY, mb->numCoefLeftPred,
                               mb->mbAvailBits);
    if (retCode < 0) {
      printf("Error: illegal luma AC coefficient\n");
      return MBK_ERROR;
    } 
  }
  else
    vldGetZeroLumaCoeffs(numCoefPtrY, mb->numCoefLeftPred);

  /*
   * Chroma DC coefficients
   */
  if (mb->cbpChromaDC != 0) {

    retCode = vldGetChromaDCcoeffs(bitbuf, mb->dcCoefC, &mb->cbpChromaDC);

    if (retCode < 0) {
      printf("Error: illegal chroma DC coefficient\n");
      return MBK_ERROR;
    }
  }

  /*
   * Chroma AC coefficients
   */
  if (mb->cbpC != 0) {

    retCode = vldGetChromaCoeffs(bitbuf, mb->coefC, &mb->cbpC, numCoefPtrU, numCoefPtrV,
                             mb->numCoefLeftPredC[0], mb->numCoefLeftPredC[1], mb->mbAvailBits);
    if (retCode < 0) {
      printf("Error: illegal chroma AC coefficient\n");
      return MBK_ERROR;
    }
  }
  else {
    vldGetZeroChromaCoeffs(numCoefPtrU, numCoefPtrV, mb->numCoefLeftPredC);
  }

  return MBK_OK;
}


/*
 *
 * mbkSetInitialQP:
 *
 * Parameters:
 *      mb                    Macroblock object
 *      qp                    Quantization parameter
 *      chromaQpIdx           Chroma QP index relative to luma QP
 *
 * Function:
 *      Set macroblock qp.
 *      
 * Returns:
 *      -
 *
 */
void mbkSliceStart(macroblock_s *mb, int qp, int chromaQpIdx, frmBuf_s *refPicList0[], int numRefFrames)
{
  int i;

  mb->qp  = qp;
  mb->qpC = qpChroma[clip(MIN_QP, MAX_QP, qp + chromaQpIdx)];

  mb->numSkipped = -1;

  mb->refIdxToPicIDmappingL0[0] = (int8) -1;
  for (i = 0; i < numRefFrames; i++)
    mb->refIdxToPicIDmappingL0[i+1] = (int8) refPicList0[i]->picID;
}


/*
 *
 * recoPcmMb:
 *
 * Parameters:
 *      reco                  Reconstruction frame
 *      pixX                  MB horizontal position
 *      pixY                  MB vertical position
 *      width                 Picture width
 *      bitbuf                Bitbuffer handle
 *
 * Function:
 *      Get PCM macroblock.
 *      
 * Returns:
 *      MBK_OK for ok, MBK_ERROR for error
 *
 */
static int recoPcmMb(frmBuf_s *reco, int pixX, int pixY, int width,
                     bitbuffer_s *bitbuf)
{
  int x, y;
  u_int8 *recoPtr;
  int byteRet;

  if (bibGetNumRemainingBits(bitbuf) < 8*(3*MBK_SIZE*MBK_SIZE/2))
    return MBK_ERROR;

  /* Get y */
  recoPtr = reco->y + pixY*width + pixX;
  for (y = 0; y < MBK_SIZE; y++) {
    for (x = 0; x < MBK_SIZE; x++) {
      bibGetByte(bitbuf, &byteRet);
      recoPtr[y*width+x] = (u_int8)byteRet;
    }
  }

  pixX >>= 1;
  pixY >>= 1;
  width >>= 1;

  /* Get u */
  recoPtr = reco->u + pixY*width + pixX;
  for (y = 0; y < MBK_SIZE/2; y++) {
    for (x = 0; x < MBK_SIZE/2; x++) {
      bibGetByte(bitbuf, &byteRet);
      recoPtr[y*width+x] = (u_int8)byteRet;
    }
  }

  /* Get v */
  recoPtr = reco->v + pixY*width + pixX;
  for (y = 0; y < MBK_SIZE/2; y++) {
    for (x = 0; x < MBK_SIZE/2; x++) {
      bibGetByte(bitbuf, &byteRet);
      recoPtr[y*width+x] = (u_int8)byteRet;
    }
  }

  return MBK_OK;
}


/*
 *
 * getMbAvailability:
 *
 * Parameters:
 *      mb                    Macroblock object
 *      mbData                Buffers for for macroblock attributes
 *      picWidth              Picture width
 *      constrainedIntra      Constrained intra prediction flag
 *
 * Function:
 *      Get neighboring macroblock availability info
 *      
 * Returns:
 *      Macroblock availability bits:
 *        bit 0 : left macroblock
 *        bit 1 : upper macroblock
 *        bit 2 : upper-right macroblock
 *        bit 3 : upper-left macroblock
 *        bit 4 : left macroblock (intra)
 *        bit 5 : upper macroblock (intra)
 *        bit 6 : upper-right macroblock (intra)
 *        bit 7 : upper-left macroblock (intra)
 */
static int getMbAvailability(macroblock_s *mb, mbAttributes_s *mbData,
                             int picWidth, int constrainedIntra)
{
  int mbsPerLine;
  int mbAddr;
  int currSliceIdx;
  int *sliceMap;
  int8 *mbTypeTable;
  int mbAvailBits;

  mbsPerLine = picWidth/MBK_SIZE;
  mbAddr = mb->idxY*mbsPerLine+mb->idxX;

  sliceMap = & mbData->sliceMap[mbAddr];
  currSliceIdx = sliceMap[0];

  mbAvailBits = 0;

  /* Check availability of left macroblock */
  if (mb->idxX > 0 && sliceMap[-1] == currSliceIdx)
    mbAvailBits |= 0x11;

  /* Check availability of upper, upper-left and upper-right macroblocks */
  if (mb->idxY > 0) {

    sliceMap -= mbsPerLine;

    /* Check availability of upper macroblock */
    if (sliceMap[0] == currSliceIdx)
      mbAvailBits |= 0x22;

    /* Check availability of upper-right macroblock */
    if (mb->idxX+1 < mbsPerLine && sliceMap[1] == currSliceIdx)
      mbAvailBits |= 0x44;

    /* Check availability of upper-left macroblock */
    if (mb->idxX > 0 && sliceMap[-1] == currSliceIdx)
      mbAvailBits |= 0x88;
  }


  /*
   * Check availability of intra MB if constrained intra is enabled
   */
  if (constrainedIntra) {

     mbTypeTable = & mbData->mbTypeTable[mbAddr];

    /* Check availability of left intra macroblock */
    if ((mbAvailBits & 0x10) && !MBK_IS_INTRA(mbTypeTable[-1]))
      mbAvailBits &= ~0x10;

    /* Check availability of upper, upper-left and upper-right intra macroblocks */
    if (mbAvailBits & (0x20|0x40|0x80)) {

      mbTypeTable -= mbsPerLine;

      /* Check availability of upper intra macroblock */
      if ((mbAvailBits & 0x20) && !MBK_IS_INTRA(mbTypeTable[0]))
        mbAvailBits &= ~0x20;

      /* Check availability of upper-right intra macroblock */
      if ((mbAvailBits & 0x40) && !MBK_IS_INTRA(mbTypeTable[1]))
        mbAvailBits &= ~0x40;

      /* Check availability of upper-left intra macroblock */
      if ((mbAvailBits & 0x80) && !MBK_IS_INTRA(mbTypeTable[-1]))
        mbAvailBits &= ~0x80;
    }
  }

  return mbAvailBits;
}


#ifdef CHECK_SUB_MB_RECT_SIZE

/*
 * checkSubMbRectSize:
 *
 * Parameters:
 *      vecs                Motion vectors for the frame
 *      picWidth            Picture width
 *      blkX                Sub-macroblock X index within frame
 *      blkY                Sub-macroblock Y index within frame
 *
 * Function:
 *      Check whether motion vectors for the current sub-macroblock
 *      conform to the AVC/H.264 standard's  rect size restriction.
 *
 * Returns:
 *      1 for vectors ok, 0 for vectors not ok.
 */
static int checkSubMbRectSize(motVec_s *vecs, int picWidth, int blkX, int blkY)
{
  int blksPerRow;
  int minX, maxX, minY, maxY;
  int vecDiffX, vecDiffY;
  int rectSize;
  int i, j;

  blksPerRow = picWidth/BLK_SIZE;
  vecs += blksPerRow*blkY + blkX;

  minX = minY = 32767;
  maxX = maxY = -32768;

  for (j = 0; j < BLK_PER_MB/2; j++) {
    for (i = 0; i < BLK_PER_MB/2; i++) {
      minX = min(minX, vecs[j*blksPerRow+i].x + i*BLK_SIZE*4);
      maxX = max(maxX, vecs[j*blksPerRow+i].x + i*BLK_SIZE*4);
      minY = min(minY, vecs[j*blksPerRow+i].y + j*BLK_SIZE*4);
      maxY = max(maxY, vecs[j*blksPerRow+i].y + j*BLK_SIZE*4);
    }
  }

  vecDiffX = (maxX>>2) - (minX>>2);
  vecDiffY = (maxY>>2) - (minY>>2);
  rectSize = (vecDiffX + BLK_SIZE + 6) * (vecDiffY + BLK_SIZE + 6);

  if (rectSize <= 576)
    return 1;
  else
    return 0;
}


/*
 * checkAllSubMbRectSizes:
 *
 * Parameters:
 *      vecs                Motion vectors for the frame
 *      picWidth            Picture width
 *      blkX                Sub-macroblock X index within frame
 *      blkY                Sub-macroblock Y index within frame
 *
 * Function:
 *      Check whether motion vectors for the current macroblock
 *      conform to the AVC/H.264 standard's rect size restriction.
 *
 * Returns:
 *      1 for vectors ok, 0 for vectors not ok.
 */
static int checkAllSubMbRectSizes(motVec_s *vecs, int picWidth, int blkX, int blkY)
{
  int i, j;

  for (j = 0; j < BLK_PER_MB; j+=BLK_PER_MB/2) {
    for (i = 0; i < BLK_PER_MB; i+=BLK_PER_MB/2) {
      if (!checkSubMbRectSize(vecs, picWidth, blkX+i, blkY+j))
        return 0;
    }
  }

  return 1;
}

#endif


/*
 *
 * mbkDecode:
 *
 * Parameters:
 *      mb                    Macroblock parameters
 *      reco                  Pointer to reconstruction frame
 *      ref                   Reference frame list
 *      numRefFrames          Number of reference frames active
 *      mbData                Buffer for macroblock attributes
 *      picWidth              Picture width
 *      picHeight             Picture height
 *      picType               Picture type (intra/inter)
 *      bitbuf                Bitbuffer handle
 *
 * Function:
 *      Decodes one macroblock
 *      
 * Returns:
 *      -
 *
 */
int mbkDecode(macroblock_s *mb, frmBuf_s *reco, frmBuf_s **ref, int refFramesExist,
              int numRefFrames, mbAttributes_s *mbData, int picWidth, int picHeight,
              int picType, int constIpred, int chromaQpIdx,
              int mbIdxX, int mbIdxY, void *streamBuf)
{
  int8 ipTab[BLK_PER_MB*BLK_PER_MB];
  int diffVecs[BLK_PER_MB*BLK_PER_MB][2];
#if 0
  int cbpC;
#endif
  int blksPerLine = picWidth/BLK_SIZE;
  int hasDc;
  int pixOffset;
  int constrainedIntra;
  int copyMbFlag;
  int pcmMbFlag;
  int retCode;
  static const int modes8x8[4] = {0, 0, 0, 0};
  double tempTime;


#ifdef DEBUG_PRINT
  mb->intraTime = 0.0;
  mb->interTime = 0.0;
  mb->vldTime = 0.0;
  mb->codingTime = 0.0;
#endif

  mb->idxX = mbIdxX;
  mb->idxY = mbIdxY;

  mb->blkX = mbIdxX*BLK_PER_MB;
  mb->blkY = mbIdxY*BLK_PER_MB;

  mb->pixX = mbIdxX*MBK_SIZE;
  mb->pixY = mbIdxY*MBK_SIZE;

  mb->mbAddr  = mb->idxY*(picWidth/MBK_SIZE)+mb->idxX;
  mb->blkAddr = mb->blkY*(picWidth/BLK_SIZE)+mb->blkX;
  mb->pixAddr = mb->pixY*picWidth+mb->pixX;

  copyMbFlag = pcmMbFlag = 0;

  constrainedIntra = constIpred && !(IS_SLICE_I(picType));

  mb->mbAvailBits = getMbAvailability(mb, mbData, picWidth, constrainedIntra);

  /*
   * Read macroblock bits
   */
  tempTime = (double)clock()/CLOCKS_PER_SEC;

  {
    retCode = getMacroblock(mb, numRefFrames, ipTab, mbData->numCoefUpPred, diffVecs,
                            picType, chromaQpIdx, (bitbuffer_s *)streamBuf);

    if (retCode < 0)
      return retCode;

    if (bibGetStatus((bitbuffer_s *)streamBuf) < 0)
      return MBK_ERROR;
  }

#ifdef DEBUG_PRINT
  mb->vldTime += ((double)clock()/CLOCKS_PER_SEC) - tempTime;
#endif

  /* Set PCM glag */
  if (MBK_IS_INTRA_PCM(mb->type))
    pcmMbFlag = 1;

  /*
   * Get intra/inter prediction
   */
  if (MBK_IS_INTRA(mb->type)) {

    mbData->mbTypeTable[mb->mbAddr] = (int8) mb->type;

    mcpClearMBmotion(mb->idxX, mb->idxY, picWidth, mbData->refIdxTable,
                     -1, mbData->motVecTable);

    tempTime = (double)clock()/CLOCKS_PER_SEC;

    if (MBK_IS_INTRA_4x4(mb->type)) {
      iprPutIntraModes(mb->mbAvailBits>>4, ipTab, mb->ipModesLeftPred,
                       &mbData->ipModesUpPred[mb->blkX]);

      iprPredLuma4x4blocks(mb->coefY, reco->y, picWidth, ipTab,
                           mb->mbAvailBits>>4, mb->idxX, mb->idxY, mb->cbpY, mb->qp);
    }
    else {
      iprClearMBintraPred(mb->ipModesLeftPred, &mbData->ipModesUpPred[mb->blkX]);

      if (!pcmMbFlag)
        iprPredLuma16x16(mb->predY, mb->intraMode,
                         &reco->y[mb->pixAddr-picWidth-1],
                         picWidth, mb->mbAvailBits>>4);
    }

    if (pcmMbFlag) {
      {
        if (recoPcmMb(reco, mb->pixX, mb->pixY, picWidth, (bitbuffer_s *)streamBuf) < 0)
          return MBK_ERROR;
      }
    }
    else {
      int offset = (mbIdxY*(MBK_SIZE/2)-1)*(picWidth>>1)+mbIdxX*(MBK_SIZE/2)-1;

      iprPredChroma(mb->predC, &reco->u[offset], &reco->v[offset],
                    picWidth>>1, mb->mbAvailBits>>4, mb->intraModeChroma);
    }

#ifdef DEBUG_PRINT
  mb->intraTime += ((double)clock()/CLOCKS_PER_SEC) - tempTime;
#endif
  }
  else {

    iprClearMBintraPred(mb->ipModesLeftPred, &mbData->ipModesUpPred[mb->blkX]);

    /* If COPY MB, put skip motion vectors */
    if (mb->interMode == MOT_COPY) {
      copyMbFlag = mcpPutSkipModeVectors(mb->idxX, mb->idxY, picWidth,
                                         mbData->refIdxTable,
                                         mbData->motVecTable, mb->mbAvailBits);
      mb->interMode = MOT_16x16;
    }
    else
        mcpPutVectors(mb->idxX, mb->idxY, mb->interMode, mb->subMbModes,
                    mb->refNum, picWidth, mbData->refIdxTable, numRefFrames,
                    mbData->motVecTable, mb->mbAvailBits, diffVecs, mb->numMotVecs);

#ifdef DEBUG_PRINT
    tempTime = (double)clock()/CLOCKS_PER_SEC;
#endif

#ifdef CHECK_SUB_MB_RECT_SIZE
    if (!checkAllSubMbRectSizes(mbData->motVecTable, picWidth, mb->blkX, mb->blkY)) {
      printf("Sub-macroblock rect size violation (%i,%i) !!\n", mb->blkX, mb->blkY);
    }
#endif

    if (copyMbFlag) {
      if (refFramesExist)
        mcpCopyMacroblock(reco, ref[0], mb->pixX, mb->pixY, picWidth);
      else
        mcpFillMacroblock(reco, mb->pixX, mb->pixY, picWidth);
    }
    else {
      if (refFramesExist) {
        if (mb->numMotVecs <= 4) {
          // MB does not contain blocks smaller than 8x8
          mcpGetPred(mb->predY, mb->predC, mb->idxX, mb->idxY, ref, picWidth,
                     picHeight, mbData->motVecTable, mbData->refIdxTable, modes8x8);
        }
        else {
          // MB contains blocks smaller than 8x8
          mcpGetPred(mb->predY, mb->predC, mb->idxX, mb->idxY, ref, picWidth,
                     picHeight, mbData->motVecTable, mbData->refIdxTable, mb->subMbModes);
        }
      }
      else
        mcpFillPred(mb->predY, mb->predC);
    }

    if (mb->numMotVecs > 4) {
      mbData->mbTypeTable[mb->mbAddr] = MB_TYPE_INTER_8x8_8x4_4x8_4x4;
    }
    else {
      mbData->mbTypeTable[mb->mbAddr] = (int8) max(min(mb->type, MB_TYPE_INTER_8x8), MB_TYPE_INTER_16x16);
    }

#ifdef DEBUG_PRINT
  mb->interTime += ((double)clock()/CLOCKS_PER_SEC) - tempTime;
#endif
  }


  /*
   * Decode prediction error & reconstruct MB
   */
#ifdef DEBUG_PRINT
  tempTime = (double)clock()/CLOCKS_PER_SEC;
#endif

  if (!copyMbFlag && !pcmMbFlag) {

    /* If 4x4 intra mode, luma prediction error is already transformed */
    if (!MBK_IS_INTRA_4x4(mb->type)) {

      hasDc = MBK_IS_INTRA_16x16(mb->type) ? 1 : 0;

      pedRecoLumaMB(mb->predY, mb->dcCoefY, hasDc, mb->coefY,
                    &reco->y[mb->pixY*picWidth+mb->pixX], picWidth,
                    mb->qp, mb->cbpY);
    }

    pixOffset = ((mb->pixY*picWidth)>>2)+(mb->pixX>>1);

    pedRecoChromaMB(mb->predC, mb->dcCoefC, mb->coefC, &reco->u[pixOffset],
                    &reco->v[pixOffset], picWidth>>1, mb->qpC,
                    mb->cbpChromaDC, mb->cbpC);
  }

#ifdef DEBUG_PRINT
  mb->codingTime += ((double)clock()/CLOCKS_PER_SEC) - tempTime;
#endif

  /*
   * Store qp and coded block pattern for current macroblock
   */
  if (pcmMbFlag)
    mbData->qpTable[mb->mbAddr] = 0;
  else
    mbData->qpTable[mb->mbAddr] = (int8)mb->qp;

#if 0

  cbpC  = ((mb->cbpChromaDC & 1) ? 0x0f : (mb->cbpC & 0x0f)) |
          ((mb->cbpChromaDC & 2) ? 0xf0 : (mb->cbpC & 0xf0));

  mbData->cbpTable[mb->mbAddr] = mb->cbpY | (cbpC<<16);

#else

  mbData->cbpTable[mb->mbAddr] = mb->cbpY;

#endif
  
  if (!IS_SLICE_I(picType))
  {
	  int i;
    int8 *refIdxTab = mbData->refIdxTable + mb->blkAddr;
    int8 *refIDtab = mbData->refPicIDtable + mb->blkAddr;
    int8 *mapping = mb->refIdxToPicIDmappingL0 + 1;
    int j;
    for (j = 0; j < 4; j+=2) {
      int8 refPicID  = mapping[refIdxTab[0]];
      int8 refPicID2 = mapping[refIdxTab[2]];
	  if(refPicID != refPicID2)
		  i=1;
      refIdxTab += 2*blksPerLine;
      refIDtab[0] = refPicID;
      refIDtab[1] = refPicID;
      refIDtab[2] = refPicID2;
      refIDtab[3] = refPicID2;
      refIDtab += blksPerLine;
      refIDtab[0] = refPicID;
      refIDtab[1] = refPicID;
      refIDtab[2] = refPicID2;
      refIDtab[3] = refPicID2;
      refIDtab += blksPerLine;
    }
  }

  return MBK_OK;
}
