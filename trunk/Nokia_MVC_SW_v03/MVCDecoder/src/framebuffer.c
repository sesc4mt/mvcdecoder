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
 * framebuffer.c
 *
 * Contains:
 *    Functions for handling reference frame buffer.
 *
 */

#include <string.h>
#include <stdio.h>
#include "nccglob.h"
#include "globals.h"
#include "framebuffer.h"
#include "sequence.h"


/*
 * Static functions
 */
static void *allocMem(int blkSize, size_t unitSize);
static frmBuf_s *initRefFrame(frmBuf_s *recoBuf, frmBuf_s *refBuf, int dpbFullness, int viewId);


/*
 *
 * allocMem:
 *
 * Parameters:
 *      blkSize               Block size
 *      unitSize              unit size
 *
 * Function:
 *      Allocate blkSize*unitSize bytes of memory
 *
 * Returns:
 *      Pointer to allocated memory or NULL
 *
 */
static void *allocMem(int blkSize, size_t unitSize)
{
  void *mem;

  if ((mem = nccMalloc(blkSize*unitSize)) == NULL) {
    printf("Cannot allocate memory for frame\n");
  }

  return mem;
}


/*
 *
 * frmOpen:
 *
 * Parameters:
 *      mbData                Macroblock state buffer
 *      width                 Width of the frame
 *      height                Height of the frame
 *
 * Function:
 *      Allocate memory for frame buffer and macroblock state buffer.
 *
 * Returns:
 *      Pointer to allocated frame buffer or NULL
 *
 */
frmBuf_s *frmOpen(mbAttributes_s **mbData, int width, int height)
{
  int numPels = width*height;
  int numBlksPerLine = width/BLK_SIZE;
  int numBlocks = numBlksPerLine*height/BLK_SIZE;
  int numMacroblocks = width/MBK_SIZE*height/MBK_SIZE;
  frmBuf_s *recoBuf;
  mbAttributes_s *mbDataTmp;

  if ((recoBuf = (frmBuf_s *)nccMalloc(sizeof(frmBuf_s))) == NULL)
    return NULL;

  memset(recoBuf, 0, sizeof(frmBuf_s));

  if ((recoBuf->y = (u_int8 *)allocMem(numPels, sizeof(u_int8))) == NULL)
    return NULL;
  if ((recoBuf->u = (u_int8 *)allocMem(numPels/4, sizeof(u_int8))) == NULL)
    return NULL;
  if ((recoBuf->v = (u_int8 *)allocMem(numPels/4, sizeof(u_int8))) == NULL)
    return NULL;

#if defined(ERROR_CONCEALMENT) && defined(BACKCHANNEL_INFO)
  if ((recoBuf->mbLossMap = (u_int8 *)allocMem(numMacroblocks, sizeof(unsigned char))) == NULL)
    return NULL;
#endif

  recoBuf->width = width;
  recoBuf->height = height;

  if ((mbDataTmp = (mbAttributes_s *)nccMalloc(sizeof(mbAttributes_s))) == NULL)
    return NULL;

  memset(mbDataTmp, 0, sizeof(mbAttributes_s));

  if ((mbDataTmp->sliceMap = (int *)allocMem(numMacroblocks, sizeof(int))) == NULL)
    return NULL;
  if ((mbDataTmp->mbTypeTable = (int8 *)allocMem(numMacroblocks, sizeof(int8))) == NULL)
    return NULL;
  if ((mbDataTmp->qpTable = (int8 *)allocMem(numMacroblocks, sizeof(int8))) == NULL)
    return NULL;
  if ((mbDataTmp->refIdxTable = (int8 *)allocMem(numBlocks, sizeof(int8))) == NULL)
    return NULL;
  if ((mbDataTmp->cbpTable = (int *)allocMem(numMacroblocks, sizeof(int))) == NULL)
    return NULL;
  if ((mbDataTmp->motVecTable = (motVec_s *)allocMem(numBlocks, sizeof(motVec_s))) == NULL)
    return NULL;
  if ((mbDataTmp->ipModesUpPred = (int8 *)allocMem(numBlksPerLine, sizeof(int8))) == NULL)
    return NULL;

  if ((mbDataTmp->numCoefUpPred[0] = (int8 *)allocMem(numBlksPerLine, sizeof(int8))) == NULL)
    return NULL;
  if ((mbDataTmp->numCoefUpPred[1] = (int8 *)allocMem(numBlksPerLine/2, sizeof(int8))) == NULL)
    return NULL;
  if ((mbDataTmp->numCoefUpPred[2] = (int8 *)allocMem(numBlksPerLine/2, sizeof(int8))) == NULL)
    return NULL;

  if ((mbDataTmp->filterModeTab = (int8 *)allocMem(numMacroblocks, sizeof(int8))) == NULL)
    return NULL;
  if ((mbDataTmp->alphaOffset = (int8 *)allocMem(numMacroblocks, sizeof(int8))) == NULL)
    return NULL;
  if ((mbDataTmp->betaOffset = (int8 *)allocMem(numMacroblocks, sizeof(int8))) == NULL)
    return NULL;

  if ((mbDataTmp->refPicIDtable = (int8 *)allocMem(numBlocks, sizeof(int8))) == NULL)
    return NULL;

  *mbData = mbDataTmp;

  return recoBuf;
}


/*
 *
 * frmOpenRef:
 *
 * Parameters:
 *      width                 Width of the frame
 *      height                Height of the frame
 *
 * Function:
 *      Allocate memory for reference frame buffer
 *
 * Returns:
 *      Pointer to Reference frame or NULL
 *
 */
frmBuf_s *frmOpenRef(int width, int height)
{
  int numPels = width*height;
  frmBuf_s *ref;

  if ((ref = (frmBuf_s *)nccMalloc(sizeof(frmBuf_s))) == NULL)
    return NULL;

  memset(ref, 0, sizeof(frmBuf_s));

  if ((ref->y = (u_int8 *)allocMem(numPels, sizeof(u_int8))) == NULL)
    return NULL;
  if ((ref->u = (u_int8 *)allocMem(numPels/4, sizeof(u_int8))) == NULL)
    return NULL;
  if ((ref->v = (u_int8 *)allocMem(numPels/4, sizeof(u_int8))) == NULL)
    return NULL;

#if defined(ERROR_CONCEALMENT) && defined(BACKCHANNEL_INFO)
  if ((ref->mbLossMap = (u_int8 *)allocMem(numPels/(MBK_SIZE*MBK_SIZE), sizeof(unsigned char))) == NULL)
    return NULL;
#endif

  ref->width      = width;
  ref->height     = height;
  ref->imgPadding = 0;

  ref->forOutput = 0;
  ref->refType = FRM_NON_REF_PIC;
  ref->viewId = 0;

  return ref;
}


/*
 *
 * frmClose:
 *
 * Parameters:
 *      frame                 Frame
 *      mbData                MB state buffers
 *
 * Function:
 *      Deallocate frame buffer and state array memory.
 *
 * Returns:
 *      Nothing
 *
 */
void frmClose(frmBuf_s *recoBuf, mbAttributes_s *mbData)
{
  if (!recoBuf)
    return;

  nccFree(recoBuf->y);
  nccFree(recoBuf->u);
  nccFree(recoBuf->v);
#if defined(ERROR_CONCEALMENT) && defined(BACKCHANNEL_INFO)
  nccFree(recoBuf->mbLossMap);
#endif

  nccFree(mbData->sliceMap);
  nccFree(mbData->mbTypeTable);
  nccFree(mbData->qpTable);
  nccFree(mbData->refIdxTable);
  nccFree(mbData->cbpTable);
  nccFree(mbData->motVecTable);
  nccFree(mbData->ipModesUpPred);
  nccFree(mbData->numCoefUpPred[0]);
  nccFree(mbData->numCoefUpPred[1]);
  nccFree(mbData->numCoefUpPred[2]);
  nccFree(mbData->filterModeTab);
  nccFree(mbData->alphaOffset);
  nccFree(mbData->betaOffset);
  nccFree(mbData->refPicIDtable);

  nccFree(recoBuf);
  nccFree(mbData);
}


/*
 *
 * frmCloseRef:
 *
 * Parameters:
 *      ref                   Reference frame
 *
 * Function:
 *      Deallocate reference frame buffer memory.
 *
 * Returns:
 *      Nothing
 *
 */
void frmCloseRef(frmBuf_s *ref)
{
  if (!ref)
    return;

  nccFree(ref->y);
  nccFree(ref->u);
  nccFree(ref->v);

#if defined(ERROR_CONCEALMENT) && defined(BACKCHANNEL_INFO)
  nccFree(ref->mbLossMap);
#endif

  nccFree(ref);
}


/*
 *
 * initRefFrame:
 *
 * Parameters:
 *      recoBuf               Reconstruction frame
 *      frameBuf              Frame buffer to initialize
 *      viewId                ViewId of the current view
 *
 * Function:
 *      Initialize reference frame buffer refBuf using reconstructed buffer
 *      recoBuf. If width and height of the reference buffer do not those
 *      of the reconstructed buffer, reference buffer is reallocated.
 *
 * Returns:
 *      Pointer to reference frame
 *
 */
static frmBuf_s *initRefFrame(frmBuf_s *recoBuf, frmBuf_s *refBuf, int dpbFullness, int viewId)
{
  u_int8 *y, *u, *v;
  int picID;
#if defined(ERROR_CONCEALMENT) && defined(BACKCHANNEL_INFO)
  unsigned char *mbLossMap;
#endif

  /* utilize viewId in picID assignment */
  if(viewId == 0)
    picID = refBuf ? refBuf->picID : dpbFullness + 1;
  else		// viewId == 1
    picID = refBuf ? refBuf->picID : 6 + dpbFullness + 1;

  /* If pic size is different, reopen with new size */
  if (!refBuf || refBuf->width != recoBuf->width || refBuf->height != recoBuf->height) {
    frmCloseRef(refBuf);
    if ((refBuf = frmOpenRef(recoBuf->width, recoBuf->height)) == NULL)
      return NULL;
  }

  /* Save data pointers */
  y = refBuf->y;
  u = refBuf->u;
  v = refBuf->v;
#if defined(ERROR_CONCEALMENT) && defined(BACKCHANNEL_INFO)
  mbLossMap = refBuf->mbLossMap;
#endif

  /* Copy variables */
  *refBuf = *recoBuf;

  /* Restore data pointers */
  refBuf->y = y;
  refBuf->u = u;
  refBuf->v = v;
#if defined(ERROR_CONCEALMENT) && defined(BACKCHANNEL_INFO)
  refBuf->mbLossMap = mbLossMap;
#endif

  refBuf->picID = picID;

  return refBuf;
}


/*
 *
 * frmMakeRefFrame:
 *
 * Parameters:
 *      recoBuf               Reconstructed frame
 *      refBuf                Reference frame
 *      viewId                ViewId of the current view
 *
 * Function:
 *      Generate reference frame refBuf using reconstructed frame recoBuf.
 *      Function does not copy pixel data, but it simply swaps pointers.
 *
 * Returns:
 *      Pointer to reference frame
 *
 */
frmBuf_s *frmMakeRefFrame(frmBuf_s *recoBuf, frmBuf_s *refBuf, int dpbFullness, int viewId)
{
  u_int8 *p;
#if defined(ERROR_CONCEALMENT) && defined(BACKCHANNEL_INFO)
  unsigned char *pu;
#endif

  refBuf = initRefFrame(recoBuf, refBuf, dpbFullness, viewId);
  if (refBuf == NULL)
    return NULL;

  /* Swap luma pointers */
  p = refBuf->y;
  refBuf->y = recoBuf->y;
  recoBuf->y = p;

  /* Swap chroma U pointers */
  p = refBuf->u;
  refBuf->u = recoBuf->u;
  recoBuf->u = p;

  /* Swap chroma V pointers */
  p = refBuf->v;
  refBuf->v = recoBuf->v;
  recoBuf->v = p;

#if defined(ERROR_CONCEALMENT) && defined(BACKCHANNEL_INFO)
  /* Swap MB loss map pointers */
  pu = refBuf->mbLossMap;
  refBuf->mbLossMap = recoBuf->mbLossMap;
  recoBuf->mbLossMap = pu;
#endif

  return refBuf;
}


dispBuf_s *initDisplayBuffer(int width, int height)
{
  int numPels = width*height;
  int numPelsUV = (width >> 1)*(height >> 1);
  dispBuf_s *displayBuf;

  if ((displayBuf = (dispBuf_s *)nccMalloc(sizeof(dispBuf_s))) == NULL)
    return NULL;

  memset(displayBuf, 0, sizeof(dispBuf_s));

  if ((displayBuf->y = (u_int8 *)allocMem(numPels, sizeof(u_int8))) == NULL)
    return NULL;
  if ((displayBuf->u = (u_int8 *)allocMem(numPelsUV, sizeof(u_int8))) == NULL)
    return NULL;
  if ((displayBuf->v = (u_int8 *)allocMem(numPelsUV, sizeof(u_int8))) == NULL)
    return NULL;

  displayBuf->width = width;
  displayBuf->height = height;

  return displayBuf;
}


void closeDisplayBuffer(dispBuf_s *dsp)
{
  if (!dsp)
    return;

  nccFree(dsp->y);
  nccFree(dsp->u);
  nccFree(dsp->v);

  nccFree(dsp);
}

