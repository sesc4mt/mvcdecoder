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
 * dpb.c
 *
 * Contains:
 *    Functions for Decoded Picture Buffer handling.
 *
 */

#include <string.h>
#include <stdio.h>
#include "nccglob.h"
#include "globals.h"
#include "framebuffer.h"
#include "dpb.h"


/*
 *
 * dpbOpen:
 *
 * Parameters:
 *
 * Function:
 *      Allocate DPB.
 *
 * Returns:
 *      Pointer to dpb or NULL
 *
 */
dpb_s *dpbOpen()
{
  dpb_s *dpb;

  dpb = (dpb_s *)nccMalloc(sizeof(dpb_s));

  if (dpb != NULL)
    memset(dpb, 0, sizeof(dpb_s));

  return dpb;
}


/*
 *
 * dpbClose:
 *
 * Parameters:
 *      dpb                   DPB object
 *
 * Function:
 *      Deinitialize DPB.
 *
 * Returns:
 *      -
 *
 */
void dpbClose(dpb_s *dpb)
{
  int i, j;


  for (i = 0; i < DPB_MAX_SIZE; i++)
    for (j = 0; j < NUM_VIEWS; j++)
      frmCloseRef(dpb->buffers[i][j]);

  nccFree(dpb);
}


/*
 *
 * dpbSetSize:
 *
 * Parameters:
 *      dpb                   DPB object
 *      dpbSize               New DPB size
 *
 * Function:
 *      Set DPB size in frames.
 *
 * Returns:
 *      -
 *
 */
void dpbSetSize(dpb_s *dpb, int dpbSize)
{
  int i, j;
  
  /* If new DPB size is smaller than old, close any unneeded frame buffers */
  for (j = 0; j < NUM_VIEWS; j++)
  {
    for (i = dpbSize; i < dpb->size[j]; i++) {
      frmCloseRef(dpb->buffers[i][j]);
      dpb->buffers[i][j] = NULL;
    }
    
    dpb->size[j] = min(dpbSize, DPB_MAX_SIZE);
  }
  
  for (j = 0; j < NUM_VIEWS; j++)
  {
    for (i = 0; i < dpb->size[j]; i++) {
      if(dpb->buffers[i][j] != NULL)
      {
        dpb->buffers[i][j]->picID = (dpb->size[j])*j+i+1;
      }
    }
  }
}


/*
 *
 * dpbGetNextOutputPic:
 *
 * Parameters:
 *      dpb                   DPB object
 *      dpbHasIDRorMMCO5      Set upon return if IDR picture or picture with
 *                            MMCO5 command is found in DPB
 *      viewId                ViewId of the current view
 *
 * Function:
 *      Find next frame to output (frame with the lowest POC).
 *      Search is started from the last active frame in dpb and is
 *      stopped if all frames have been checked or IDR picture or
 *      picture with MMCO5 is found.
 *
 * Returns:
 *      Framebuffer with the lowest POC or 0 if DPB is empty
 *
 */
frmBuf_s *dpbGetNextOutputPic(dpb_s *dpb, 
							  int *dpbHasIDRorMMCO5,
							  int viewId)
{
  frmBuf_s * tmpFrm;
  int i;


  tmpFrm = 0;

  /* Find first output pic in decoding order */
  for (i = dpb->fullness[viewId]-1; i >= 0; i--) {
    if (dpb->buffers[i][viewId]->forOutput) {
      tmpFrm = dpb->buffers[i][viewId];
      break;
    }
  }

  *dpbHasIDRorMMCO5 = 0;

  if (i >= 0 && (dpb->buffers[i][viewId]->isIDR || dpb->buffers[i][viewId]->hasMMCO5))
    i--;

  /* Find picture with lowest poc. Stop search if IDR or MMCO5 is found */
  for (; i >= 0; i--) {
    if (dpb->buffers[i][viewId]->isIDR || dpb->buffers[i][viewId]->hasMMCO5) {
      *dpbHasIDRorMMCO5 = 1;
      break;
    }

    if (dpb->buffers[i][viewId]->forOutput && dpb->buffers[i][viewId]->poc < tmpFrm->poc)
      tmpFrm = dpb->buffers[i][viewId];
  }

  if(tmpFrm)	
  {
#ifdef DEBUG_PRINT
	  printf("GetOutputPic, view%d, picNum %d, viewId %d\n", viewId, (int)(tmpFrm->frameNum), (int)(tmpFrm->viewId));
#endif
  }
  return tmpFrm;
}


/*
 *
 * dpbStorePicture:
 *
 * Parameters:
 *      dpb                   DPB object
 *      currPic               Current picture
 *      outputQueue           Output queue
 *
 * Function:
 *      - Remove unused frames (non-reference, non-output frames) from the DPB.
 *      - If there is room in the DPB, put picture to DPB.
 *      - If there is no room in DPB, put pictures to output queue
 *        until frame is available.
 *
 * Returns:
 *      The number of pictures in output queue or negative value for error.
 *
 */
int dpbStorePicture(dpb_s *dpb, frmBuf_s *currPic, frmBuf_s *outputQueue[])
{
  frmBuf_s *tmpRemList[DPB_MAX_SIZE];
  frmBuf_s *tmpFrm;
  int numFrm, numRemFrm;
  int i;
  int freeBufferFound;
  int numOutput;
  int dpbHasIDRorMMCO5;
  int viewId;
  
  
  // Current view Id
  viewId = currPic->viewId;
  
  /*
  * If the current picture is a reference picture and DPB is already full of
  * reference pictures, we cannot insert current picture to DPB. Therefore,
  * we force one reference picture out of DPB to make space for current
  * picture. This situation can only happen with corrupted bitstreams.
  */
  if (currPic->refType != FRM_NON_REF_PIC &&
    (dpb->numShortTermPics[viewId]+dpb->numLongTermPics[viewId]) == dpb->size[viewId])
  {
    if (dpb->numLongTermPics[viewId] == dpb->size[viewId])
      dpb->buffers[dpb->fullness[viewId]-1][viewId]->refType = FRM_NON_REF_PIC;
    else
      dpbMarkLowestShortTermPicAsNonRef(dpb, viewId);
  }
  
  /*
  * Remove unused frames from dpb
  */
  
  numFrm = 0;
  numRemFrm = 0;
  for (i = 0; i < dpb->fullness[viewId]; i++) {
    if (dpb->buffers[i][viewId]->refType != FRM_NON_REF_PIC || dpb->buffers[i][viewId]->forOutput) {
      dpb->buffers[numFrm][viewId] = dpb->buffers[i][viewId];
      numFrm++;
    }
    else {
      /* Put unsused pics to temporary list */
      tmpRemList[numRemFrm] = dpb->buffers[i][viewId];
      numRemFrm++;
    }
  }
  
  /* Copy unused pics after active pics */
  for (i = 0; i < numRemFrm; i++)
    dpb->buffers[numFrm+i][viewId] = tmpRemList[i];
  
  dpb->fullness[viewId] = numFrm;
  
  /*
  * Try to store current pic to dpb. If there is no room in dpb, we have to
  * output some pictures to make room.
  */
  
  /* Case 1: if current pic is unused, it won't be stored in dpb */
  if (currPic->refType == FRM_NON_REF_PIC && !currPic->forOutput) {
    return 0;
  }
  
  /* Case 2: if there is space left in dpb, store current pic */
  if (dpb->fullness[viewId] < dpb->size[viewId]) {
    
    tmpFrm = dpb->buffers[dpb->fullness[viewId]][viewId];   /* Unused frame */
    
    tmpFrm = frmMakeRefFrame(currPic, tmpFrm, dpb->fullness[viewId], viewId);
    if (tmpFrm == NULL)
      return DPB_ERR_MEM_ALLOC;
    
    /* Move frames one position toward end of the list */
    for (i = dpb->fullness[viewId]; i > 0; i--)
      dpb->buffers[i][viewId] = dpb->buffers[i-1][viewId];
    
    /* Always insert new frame to the beginning of the list */
    dpb->buffers[0][viewId] = tmpFrm;
    dpb->fullness[viewId]++;
    
    if (currPic->refType == FRM_SHORT_TERM_PIC)
    {
      dpb->numShortTermPics[viewId]++;
    }
    else if (currPic->refType == FRM_LONG_TERM_PIC)
      dpb->numLongTermPics[viewId]++;
    
    /* Current picture is marked unused */
    currPic->forOutput = 0;
    currPic->refType   = FRM_NON_REF_PIC;
    
    /* No pictures in output queue */
    return 0;
  }
  
  /* Case 3: output pictures with bumping process until there is space in dpb or
  *  current pic is non-reference and has lowest poc */
  freeBufferFound = 0;
  numOutput       = 0;
  while (!freeBufferFound) {
    
    /* Next picture to output is a picture having smallest POC in DPB */
    tmpFrm = dpbGetNextOutputPic(dpb, &dpbHasIDRorMMCO5, currPic->viewId);
    
    /* Current picture is output if it is non-reference picture having */
    /* smaller POC than any of the pictures in DPB                     */
    if (currPic->refType == FRM_NON_REF_PIC &&
      (tmpFrm == 0 || (!dpbHasIDRorMMCO5 && currPic->poc < tmpFrm->poc)))
    {
      /* Output current picture  */
      currPic->forOutput = 0;
      outputQueue[numOutput] = currPic;
      numOutput++;
      freeBufferFound = 1;
    }
    else {
      /* Output picture that we got from DPB */
      if (tmpFrm != 0) {
        tmpFrm->forOutput = 0;
        outputQueue[numOutput] = tmpFrm;
        numOutput++;
        if (tmpFrm->refType == FRM_NON_REF_PIC)
          freeBufferFound = 1;
      }
      else
        /* Can only happen with erroneus bitstreams */
        freeBufferFound = 1;
    }
  }
  
  return numOutput;
}


/*
 *
 * dpbUpdatePicNums:
 *
 * Parameters:
 *      dpb                   DPB object
 *      frameNum              Current picture frame number
 *      maxFrameNum           Maximum frame number
 *      viewId                ViewId of the current view
 *
 * Function:
 *      Compute picture numbers for all pictures in DPB.
 *
 * Returns:
 *      -
 *
 */
void dpbUpdatePicNums(dpb_s *dpb, int32 frameNum, int32 maxFrameNum, int viewId)
{
  int i;
  int j;
  
  
  for(j=0; j<NUM_VIEWS; j++)
  {
    viewId = j;
    for (i = 0; i < dpb->fullness[viewId]; i++) {
      if (dpb->buffers[i][viewId]->refType == FRM_SHORT_TERM_PIC) {
        /* Short term pictures */
        if (dpb->buffers[i][viewId]->frameNum > frameNum)
          dpb->buffers[i][viewId]->picNum = dpb->buffers[i][viewId]->frameNum - maxFrameNum;
        else
          dpb->buffers[i][viewId]->picNum = dpb->buffers[i][viewId]->frameNum;
      }
      else if (dpb->buffers[i][viewId]->refType == FRM_LONG_TERM_PIC)
        /* Long term pictures */
        dpb->buffers[i][viewId]->longTermPicNum = dpb->buffers[i][viewId]->longTermFrmIdx;
    }
  }

#ifdef DEBUG_PRINT
  viewId=0;
  printf("RefList, view%d:", viewId);
  for (i = 0; i < dpb->fullness[viewId]; i++) {
    printf(" %d %d, ",(int)(dpb->buffers[i][viewId]->picNum),(int)(dpb->buffers[i][viewId]->viewId));
  }
  printf("\n");
  viewId=1;
  printf("RefList, view%d:", viewId);
  for (i = 0; i < dpb->fullness[viewId]; i++) {
    printf(" %d %d, ",(int)(dpb->buffers[i][viewId]->picNum),(int)(dpb->buffers[i][viewId]->viewId));
  }
  printf("\n");
#endif  
  
}


/*
 *
 * dpbMarkAllPicsAsNonRef:
 *
 * Parameters:
 *      dpb                   DPB object
 *      viewId                ViewId of the current view
 *
 * Function:
 *      Mark all picrures as non-reference pictures.
 *
 * Returns:
 *      -
 *
 */
void dpbMarkAllPicsAsNonRef(dpb_s *dpb)
{
  int i, j;

  /* Mark all pictures as not used for reference */
  for (j = 0; j < NUM_VIEWS; j++) {
    for (i = 0; i < dpb->fullness[j]; i++)
      dpb->buffers[i][j]->refType = FRM_NON_REF_PIC;

    dpb->numShortTermPics[j] = 0;
    dpb->numLongTermPics[j]  = 0;
  }
}


/*
 *
 * dpbMarkLowestShortTermPicAsNonRef:
 *
 * Parameters:
 *      dpb                   DPB object
 *      viewId                ViewId of the current view
 *
 * Function:
 *      Mark short-term picture having lowest picture number as
 *      non-reference pictures.
 *
 * Returns:
 *      -
 *
 */
void dpbMarkLowestShortTermPicAsNonRef(dpb_s *dpb, int viewId)
{
  int picIdx;
  int i;

  /* Find short term pic with lowest picNum */
  picIdx = -1;
  for (i = dpb->fullness[viewId]-1; i >= 0; i--) {
    if (dpb->buffers[i][viewId]->refType == FRM_SHORT_TERM_PIC &&
        (picIdx < 0 || dpb->buffers[i][viewId]->picNum < dpb->buffers[picIdx][viewId]->picNum))
      picIdx = i;
  }

  /* Mark short term pic with lowest picNum as not reference picture */
  if (picIdx >= 0) {
    dpb->buffers[picIdx][viewId]->refType = FRM_NON_REF_PIC;
    dpb->numShortTermPics[viewId]--;
  }
}


/*
 *
 * dpbMarkShortTermPicAsNonRef:
 *
 * Parameters:
 *      dpb                   DPB object
 *      picNum                Picture number
 *      viewId                ViewId of the current view
 *
 * Function:
 *      Mark short-term picture having picture number picNum as
 *      non-reference picture.
 *
 * Returns:
 *      DPB_OK or DPB_ERR_PICTURE_NOT_FOUND
 *
 */
int dpbMarkShortTermPicAsNonRef(dpb_s *dpb, int32 picNum, int viewId)
{
  int i;


  for (i = 0; i < dpb->fullness[viewId]; i++) {
    if (dpb->buffers[i][viewId]->refType == FRM_SHORT_TERM_PIC &&
        dpb->buffers[i][viewId]->picNum == picNum)
    {
      dpb->buffers[i][viewId]->refType = FRM_NON_REF_PIC;
      dpb->numShortTermPics[viewId]--;
      return DPB_OK;
    }
  }

  return DPB_ERR_PICTURE_NOT_FOUND;
}


/*
 *
 * dpbMarkLongTermPicAsNonRef:
 *
 * Parameters:
 *      dpb                   DPB object
 *      longTermPicNum        Long-term picture number
 *      viewId                ViewId of the current view
 *
 * Function:
 *      Mark long-term picture having long-term picture number longTermPicNum
 *      as non-reference picture.
 *
 * Returns:
 *      DPB_OK or DPB_ERR_PICTURE_NOT_FOUND
 *
 */
int dpbMarkLongTermPicAsNonRef(dpb_s *dpb, int longTermPicNum, int viewId)
{
  int i;


  for (i = 0; i < dpb->fullness[viewId]; i++) {
    if (dpb->buffers[i][viewId]->refType == FRM_LONG_TERM_PIC &&
        dpb->buffers[i][viewId]->longTermPicNum == longTermPicNum)
    {
      dpb->buffers[i][viewId]->refType = FRM_NON_REF_PIC;
      dpb->numLongTermPics[viewId]--;
      return DPB_OK;
    }
  }

  return DPB_ERR_PICTURE_NOT_FOUND;
}


/*
 *
 * dpbVerifyLongTermFrmIdx:
 *
 * Parameters:
 *      dpb                   DPB object
 *      longTermFrmIdx        Long-term frame index
 *      viewId                ViewId of the current view
 *
 * Function:
 *      If there is a long-term picture having long term frame index
 *      longTermFrmIdx, mark that picture as non-reference picture.
 *
 * Returns:
 *      -
 *
 */
void dpbVerifyLongTermFrmIdx(dpb_s *dpb, int longTermFrmIdx, int viewId)
{
  int i;

  /* Check if longTermFrmIdx is already in use */
  for (i = 0; i < dpb->fullness[viewId]; i++) {
    if (dpb->buffers[i][viewId]->refType == FRM_LONG_TERM_PIC &&
        dpb->buffers[i][viewId]->longTermFrmIdx == longTermFrmIdx)
    {
      dpb->buffers[i][viewId]->refType = FRM_NON_REF_PIC;
      dpb->numLongTermPics[viewId]--;
      break;
    }
  }
}


/*
 *
 * dpbMarkShortTermPicAsLongTerm:
 *
 * Parameters:
 *      dpb                   DPB object
 *      picNum                Picture number
 *      longTermFrmIdx        Long-term frame index
 *      viewId                ViewId of the current view
 *
 * Function:
 *      Mark short-term picture having picture number picNum as long-term
 *      picture having long-term frame index longTermFrmIdx.
 *
 * Returns:
 *      DPB_OK or DPB_ERR_PICTURE_NOT_FOUND
 *
 */
int dpbMarkShortTermPicAsLongTerm(dpb_s *dpb, int32 picNum, int longTermFrmIdx, int viewId)
{
  int i;

  /* To avoid duplicate of longTermFrmIdx */
  dpbVerifyLongTermFrmIdx(dpb, longTermFrmIdx, viewId);

  /* Mark pic with picNum as long term and assign longTermFrmIdx to it */
  for (i = 0; i < dpb->fullness[viewId]; i++) {
    if (dpb->buffers[i][viewId]->refType == FRM_SHORT_TERM_PIC &&
        dpb->buffers[i][viewId]->picNum == picNum)
    {
      dpb->buffers[i][viewId]->refType = FRM_LONG_TERM_PIC;
      dpb->buffers[i][viewId]->longTermFrmIdx = longTermFrmIdx;
      dpb->numShortTermPics[viewId]--;
      dpb->numLongTermPics[viewId]++;
      return DPB_OK;
    }
  }

  return DPB_ERR_PICTURE_NOT_FOUND;
}


/*
 *
 * dpbSetMaxLongTermFrameIdx:
 *
 * Parameters:
 *      dpb                     DPB object
 *      maxLongTermFrmIdxPlus1  Maximum long-term frame index plus 1
 *      viewId                  ViewId of the current view
 *
 * Function:
 *      Set maximum long-term frame index. All long-term pictures having
 *      bigger long-term frame index than maxLongTermFrmIdxPlus1-1 are
 *      marked as non-reference pictures.
 *
 * Returns:
 *      -
 *
 */
void dpbSetMaxLongTermFrameIdx(dpb_s *dpb, int maxLongTermFrmIdxPlus1, int viewId)
{
  int i;


  for (i = 0; i < dpb->fullness[viewId]; i++) {
    if (dpb->buffers[i][viewId]->refType == FRM_LONG_TERM_PIC &&
        dpb->buffers[i][viewId]->longTermFrmIdx > maxLongTermFrmIdxPlus1-1)
    {
      dpb->buffers[i][viewId]->refType = FRM_NON_REF_PIC;
      dpb->numLongTermPics[viewId]--;
    }
  }

  dpb->maxLongTermFrameIdx[viewId] = maxLongTermFrmIdxPlus1 - 1;
}
