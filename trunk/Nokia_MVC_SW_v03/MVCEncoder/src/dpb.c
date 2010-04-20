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
 * dbp.c
 *
 * Contains:
 *
 *    Decoded picture buffer. The buffer also manages the reference frame 
 *    pointers.
 *
 */


#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include "nccglob.h"
#include "debug.h"
#include "refframe.h"
#include "dpb.h"
#include "frame.h"


/*
 * dpbInitialize:
 *
 * Parameters:
 *      dpbBuf                Decoded picture buffer object
 *      pEncPar               Encoding parameter
 *
 * Function:
 *      Initialize the decoded picture buffer. This buffer also manages the 
 *      reference frame pointers.
 *
 * Returns:
 *      -
 */
void dpbInitialize(dpbBuf_s    *dpbBuf, 
                   encParams_s *pEncPar)
{
  int i;

  dpbBuf->frameNum      = 0;
  dpbBuf->prevRefFrameNum = 0;
  dpbBuf->maxFrameNum   = 1 << (pEncPar->log2_max_frame_num_minus4 + 4);

  dpbBuf->maxNumRefFrms = pEncPar->maxNumRefFrms;
  dpbBuf->maxNumRefFrmsMVC = dpbBuf->maxNumRefFrms * NUM_VIEWS;

  dpbBuf->numRefFrms    = 0;
  dpbBuf->actualNumRefFrms = 0;
  dpbBuf->numShorts = 0;
  dpbBuf->numLongs  = 0;
  dpbBuf->idxOldest = 0;
  dpbBuf->prevPicHasMMCO5 = 0;
  dpbBuf->frameNumOffset = 0;
  dpbBuf->prevFrameNumOffset = 0;
  dpbBuf->ltrIdr = 0;

  // only support P frame, so # of frame buffers needed is equal 
  // to the maximal # of reference frames
  if (dpbBuf->maxNumRefFrms > 0)
  {
    dpbBuf->refFrmArr  = (refFrmBuf_s *) 
      nccMalloc(dpbBuf->maxNumRefFrmsMVC * sizeof(refFrmBuf_s));

    dpbBuf->refPicList0 = (refFrmBuf_s **) 
      nccMalloc(dpbBuf->maxNumRefFrmsMVC * sizeof(refFrmBuf_s *));

    dpbBuf->refPicListNormalOrder = (refFrmBuf_s **) 
      nccMalloc(dpbBuf->maxNumRefFrmsMVC * sizeof(refFrmBuf_s *));

    dpbBuf->reorderCmds = (reorderCommand_s *) 
      nccMalloc((dpbBuf->maxNumRefFrmsMVC) * sizeof(reorderCommand_s));

    if (dpbBuf->refFrmArr != 0) 
    {
      for (i = 0; i < dpbBuf->maxNumRefFrmsMVC; i++)
        refFrmOpen(& dpbBuf->refFrmArr[i], pEncPar);
    }
  }

  // mmcoList always has at least one entry
  dpbBuf->mmcoList = (MMCO_s *) nccMalloc(sizeof(MMCO_s));
  dpbBuf->mmcoList->mmco = 0;
  dpbBuf->mmcoList->next = 0;

  dpbBuf->numRefSameView = 0;
}


/*
 * freeMMCOList
 *
 * Parameters:
 *      mmcoList            mmcoList object
 *
 * Function:
 *      free the memory of a MMCO list
 *
 * Returns:
 *      -
 */
static void freeMMCOList(MMCO_s *mmcoList)
{
  MMCO_s *next = mmcoList;
  while (next) {
    next = mmcoList->next;
    nccFree(mmcoList);
    mmcoList = next;
  }
}


/*
 * dpbRelease:
 *
 * Parameters:
 *      dpbBuf                Decoded picture buffer object
 *      low_complex_prof3     Low complexity prof 3
 *      useSearchWin          Use internal search window
 *
 * Function:
 *      Release all the internal buffers within dbpBuf.
 *
 * Returns:
 *      -
 */
void dpbRelease(dpbBuf_s *dpbBuf, int low_complex_prof3
#ifdef ENABLE_SEARCH_WINDOW
                , int useSearchWin
#endif
                )
{
  int i;

  // release the reference frame buffers
  if (dpbBuf->refFrmArr != 0)
  {
    for (i = 0; i < dpbBuf->maxNumRefFrmsMVC; i++)
      refFrmClose(& dpbBuf->refFrmArr[i], low_complex_prof3
#ifdef ENABLE_SEARCH_WINDOW
                  , useSearchWin
#endif
      );

    nccFree(dpbBuf->refFrmArr);
    dpbBuf->refFrmArr = 0;
  }

  // release other buffers within dpbBuf object
  if (dpbBuf->refPicList0 != 0)
  {
    nccFree(dpbBuf->refPicList0);
    dpbBuf->refPicList0 = 0;
  }
  if (dpbBuf->refPicListNormalOrder != 0)
  {
    nccFree(dpbBuf->refPicListNormalOrder);
    dpbBuf->refPicListNormalOrder = 0;
  }
  if (dpbBuf->reorderCmds != 0)
  {
    nccFree(dpbBuf->reorderCmds);
    dpbBuf->reorderCmds = 0;
  }

  if (dpbBuf->mmcoList != 0) {
    freeMMCOList(dpbBuf->mmcoList);
    dpbBuf->mmcoList = 0;
  }
}


/*
 * dpbCreateMmcoEntry:
 *
 * Parameters:
 *      mmcoEntry             new mmco entry
 *      operation             mmco operation index, 0 to 6,
 *      parameter             mmco operation parameter
 *
 * Function:
 *      Create a new MMCO entry. Buffer will be allocated if the buffer is 
 *      not available.
 *
 * Returns:
 *      -
 */
static void dpbCreateMmcoEntry(MMCO_s **mmcoEntry, 
                               int operation,
                               int parameter)
{
  if (*mmcoEntry == 0)
  {
    // create a new entry
    *mmcoEntry = (MMCO_s *) nccMalloc(sizeof(MMCO_s));
    if (*mmcoEntry)
      (*mmcoEntry)->next = 0;
  }

  // in case the allocation failed
  if (*mmcoEntry != 0)
  {
    (*mmcoEntry)->mmco = operation;

    // only support mmco 6 for the time being
    if (operation == 6)
      (*mmcoEntry)->longTermFrmIdx = parameter;
  }
}


/*
 * dbpBeforeEncodeFrame:
 *
 * Parameters:
 *      dpbBuf                Decoded picture buffer object
 *      nalRefIdc             Indicate if the frame will be used as ref frame
 *      idrFlag               IDR frame flag
 *      ltrCandidate          This frame will be set as a long term ref frame
 *      viewId                View id of the current view
 *
 * Function:
 *      Perform frameNum update and prepare MMCO list before the frame is 
 *      encoded.
 *
 * Returns:
 *      -
 */
void dbpBeforeEncodeFrame(dpbBuf_s *dpbBuf,
                          int nalRefIdc, 
                          int idrFlag,
                          int ltrCandidate,
                          int viewId)
{
  if (idrFlag)
  {
    dpbBuf->frameNum = 0;
    dpbBuf->prevRefFrameNum = 0;
  }
  else
  {
    /* Only change frame numbering if at the first view */
    if(viewId == 0)
      dpbBuf->frameNum = (dpbBuf->prevRefFrameNum + 1) % dpbBuf->maxFrameNum;
    else if (!nalRefIdc)
      dpbBuf->frameNum = (dpbBuf->prevRefFrameNum + 1) % dpbBuf->maxFrameNum;
    else
      dpbBuf->frameNum = dpbBuf->prevRefFrameNum % dpbBuf->maxFrameNum;
    
    if (nalRefIdc)
      dpbBuf->prevRefFrameNum = dpbBuf->frameNum;
  }

  dpbBuf->prevPicHasMMCO5    = dpbBuf->picHasMMCO5;
  dpbBuf->prevFrameNumOffset = dpbBuf->frameNumOffset;

  dpbBuf->mmcoList->mmco = 0;
  dpbBuf->ltrIdr = 0;

  if (ltrCandidate)
  {
    if (idrFlag)
      // handled differently
      dpbBuf->ltrIdr = 1;
    else
    {
      // this is so far the only MMCO operation we support
      // handled as MMCO operation
      dpbCreateMmcoEntry(& dpbBuf->mmcoList, 6, 0);
      dpbCreateMmcoEntry(& dpbBuf->mmcoList->next, 0, 0);     // terminating condition
    }
  }
}


/*
 * dpbGetReorderCommands:
 *
 * Parameters:
 *      dpbBuf                Decoded picture buffer object
 *
 * Function:
 *      Get the re-ordering command based on the comparison between the 
 *      pointers normal order and re-order pointers.
 *
 * Returns:
 *      -
 */
int dpbGetReorderCommands(dpbBuf_s *dpbBuf)
{
  int numCmds;
  refFrmBuf_s **normal, **reorder;

  // find the last frame that is reordered
  normal  = dpbBuf->refPicListNormalOrder;
  reorder = dpbBuf->refPicList0;

  numCmds = dpbBuf->numRefFrms - 1;

  while (numCmds >= 0)
  {
    if ((normal[numCmds] != reorder[numCmds]))
      break;

    numCmds --;
  }

  numCmds ++;
  if (numCmds > 0)
  {
    int i, diff;
    int picNumL0Pred, maxPicNum;

    picNumL0Pred = dpbBuf->frameNum;
    maxPicNum    = dpbBuf->maxFrameNum;

    for (i = 0; i < numCmds; i ++) {
      diff = reorder[i]->picNum - picNumL0Pred;
      if (diff < 0)  
      {
        dpbBuf->reorderCmds[i].idc = 0;
        dpbBuf->reorderCmds[i].absDiffPicNumMinus1 = - diff - 1;
        if (reorder[i]->picNum < 0)
          picNumL0Pred = reorder[i]->picNum + maxPicNum;
        else
          picNumL0Pred = reorder[i]->picNum;
      }
      else 
      {
        dpbBuf->reorderCmds[i].idc = 1;
        dpbBuf->reorderCmds[i].absDiffPicNumMinus1 = diff - 1;
        if (reorder[i]->picNum >= maxPicNum)
          picNumL0Pred = reorder[i]->picNum - maxPicNum;
        else
          picNumL0Pred = reorder[i]->picNum;
      }
    }
  }

  return numCmds;
}


/*
 * dpbRefListNormalOrder
 *
 * Parameters:
 *      dpbBuf                Decoded/reference picture buffer
 *      currViewId            Current view's view id
 *      interViewPred         Inter view prediction is used
 *      isIntra               Is current slice intra
 *
 * Function:
 *      Generate the pointers to the reference frames in the normal order
 *      according to the reference picture numbers.
 *      The normal order for the reference frame pointers:
 *        Short-term ref frame pointers in descending order of picture number,
 *        Followed by long-term reference frame pointers in ascending order.
 *
 * Returns:
 *      -
 *
 */
void dpbRefListNormalOrder(dpbBuf_s *dpbBuf, int currViewId, int interViewPred, int isIntra)
{
  int i, j;
  int numRef;
  refFrmBuf_s *refTmp;
  refFrmBuf_s **refList0;
  int idxOldestMVC = 0;
  int numRefWithSameViewId = 0;


  refList0 = dpbBuf->refPicListNormalOrder;

  /* Set the number of active reference pics to zero */
  dpbBuf->numActiveRef = 0;
  dpbBuf->numRefSameView = 0;
  
  // get pointers to all the frames labeled as short term ref frames
  numRef = 0;
  
  if(currViewId == 0) {
    for (i = 0; i < dpbBuf->maxNumRefFrmsMVC; i++) {
      refTmp = & dpbBuf->refFrmArr[i];
      
      /* Store frames from only this view */
      if (refTmp->forRef && refTmp->isShortTerm && (refTmp->viewId == currViewId)) {
        dpbBuf->numActiveRef++;
        refList0[numRef++] = refTmp;
        
        // Assign the picture numbers that are easier to use
        refTmp->picNum = refTmp->frameNum;
        if (refTmp->picNum > dpbBuf->frameNum)
          refTmp->picNum -= dpbBuf->maxFrameNum;
      }
    }
    
    dpbBuf->numShorts = numRef;
    
    /* Store the index of the oldest reference */
    idxOldestMVC = numRef - 1;
    
    // order the pointers in descending order of picNum for short term refs
    for (i = 0; i < dpbBuf->numShorts - 1; i ++) {
      for (j = i + 1; j < dpbBuf->numShorts; j ++) {
        if (refList0[i]->picNum < refList0[j]->picNum) {
          // exchange refList0[i] and refList0[j]
          refTmp = refList0[i];
          refList0[i] = refList0[j];
          refList0[j] = refTmp;
        }
      }
    }
  }
  else	/* View id > 0, i.e. not the base view */
  {
    for (i = 0; i < dpbBuf->maxNumRefFrmsMVC; i++) {
      refTmp = & dpbBuf->refFrmArr[i];
      
      /* First, store frames from only this view */
      if (refTmp->forRef && refTmp->isShortTerm && (refTmp->viewId == currViewId))
      {
        dpbBuf->numActiveRef++;
        refList0[numRef ++] = refTmp;
        
        // Assign the picture numbers that are easier to use
        refTmp->picNum = refTmp->frameNum;
        if (refTmp->picNum > dpbBuf->frameNum)
          refTmp->picNum -= dpbBuf->maxFrameNum;
      }
      
      /* Store only maxNumRefFrms amount of frames */
      if(numRef >= dpbBuf->maxNumRefFrms)
        break;
    }
    
    dpbBuf->numRefSameView = numRefWithSameViewId = numRef;
    
    /* Store the index of the oldest reference */
    idxOldestMVC = numRef - 1;
    
    // Order the frames with the same ViewId
    for (i = 0; i < numRef - 1; i ++) {
      for (j = i + 1; j < numRef; j ++) {
        if (refList0[i]->picNum < refList0[j]->picNum) {
          // exchange refList0[i] and refList0[j]
          refTmp = refList0[i];
          refList0[i] = refList0[j];
          refList0[j] = refTmp;
        }
      }
    }

    /* Next add the frame(s) which have different viewId as current view and the same POC */
    for (i = 0; i < dpbBuf->maxNumRefFrmsMVC; i++) 
    {
      refTmp = & dpbBuf->refFrmArr[i];
      
      // Store only the previous view's frames
      if (refTmp->forRef && refTmp->isShortTerm && (refTmp->viewId < currViewId))
      {
        
        /* Only add frames with the same frame number */
        if (refTmp->frameNum == dpbBuf->frameNum)
        {
          refList0[numRef ++] = refTmp;
          dpbBuf->numActiveRef++;
          
          // Assign the picture numbers that are easier to use
          refTmp->picNum = refTmp->frameNum;
          if (refTmp->picNum > dpbBuf->frameNum)
            refTmp->picNum -= dpbBuf->maxFrameNum;
        }
      }
    }
    
    dpbBuf->numShorts = numRef;
    
    // order the frames with different viewId than current one
    for (i = numRefWithSameViewId; i < dpbBuf->numShorts - 1; i ++) {
      for (j = i + 1; j < dpbBuf->numShorts; j ++) {
        if (refList0[i]->picNum < refList0[j]->picNum) {
          // exchange refList0[i] and refList0[j]
          refTmp = refList0[i];
          refList0[i] = refList0[j];
          refList0[j] = refTmp;
        }
      }
    }
  }
  
#ifdef DEBUG_PRINT
  for (i = 0; i < dpbBuf->numShorts; i ++) {
    printf(" %d %d, ", refList0[i]->frameNum, refList0[i]->viewId);
  }
  printf("\n");
#endif
  
  // By default, do not reorder refpiclist
  dpbBuf->reorderRefPicList = 0;

  /* Reorder the reference frames */
  /* The following code reorders the last picture in the refpiclist 
   * so that the last picture is from the base view (view id 0), and not from this view 
   */
  if(currViewId == 1 && interViewPred && !isIntra)
  {
    /* Only reorder, if we have enough frames from the same view */
    if(numRefWithSameViewId >= dpbBuf->maxNumRefFrms)	
    {
      /* The picture at index "dpbBuf->maxNumRefFrms - 1", is from this view, and the picture 
       * at index "dpbBuf->maxNumRefFrms" is the picture from the base view with the same 
       * frame number 
       */

      if(refList0[dpbBuf->maxNumRefFrms]) {

        refTmp = refList0[dpbBuf->maxNumRefFrms - 1];
        refList0[dpbBuf->maxNumRefFrms - 1] = refList0[dpbBuf->maxNumRefFrms];
        refList0[dpbBuf->maxNumRefFrms] = refTmp;
      
        // Update the idxOldestMVC value also
        idxOldestMVC = numRefWithSameViewId;
        dpbBuf->reorderRefPicList = 1;
		  }
    }
  }
  else if (currViewId == 1 && !interViewPred) {
    // Remove all inter-view references, adjust numActiveRef
    if (dpbBuf->numActiveRef > dpbBuf->numRefSameView)
      dpbBuf->numActiveRef = dpbBuf->numRefSameView;
  }

  /* The numActiveRef tells how many reference frames are in the refpiclist that can be used for prediction */
  if(dpbBuf->numActiveRef > dpbBuf->maxNumRefFrms)
    dpbBuf->numActiveRef = dpbBuf->maxNumRefFrms;
  
  if (idxOldestMVC >= 0)
  {
    dpbBuf->idxOldest = refList0[idxOldestMVC] - dpbBuf->refFrmArr;
  }
  else
    dpbBuf->idxOldest = 0;
  
  // get pointers to all the frames labeled as long term ref frames
  for (i = 0; i < dpbBuf->maxNumRefFrmsMVC; i++) {
    refTmp = & dpbBuf->refFrmArr[i];
    if (refTmp->forRef && (! refTmp->isShortTerm))
    {
      refList0[numRef ++] = refTmp;
      dpbBuf->numLongs ++;
    }
  }
  dpbBuf->numLongs = numRef - dpbBuf->numShorts;
  
  // order the pointers in ascending order of picNum for long term refs
  for (i = dpbBuf->numShorts; i < numRef - 1; i ++) {
    for (j = i + 1; j < numRef; j ++) {
      if (refList0[i]->picNum > refList0[j]->picNum) {
        /* exchange refList0[i] and refList0[j] */
        refTmp = refList0[i];
        refList0[i] = refList0[j];
        refList0[j] = refTmp;
      }
    }
  }
  
  // set the remaining entries in the pointer array to NULL
  for (i = numRef; i < dpbBuf->maxNumRefFrmsMVC; i++)
    refList0[i] = 0;
  
  // copy the pointers from the normal order
  for (i = 0; i < dpbBuf->maxNumRefFrmsMVC; i ++)
  {
    dpbBuf->refPicList0[i] = refList0[i];
  }
  
#ifdef DEBUG_PRINT
  printf("numShorts %d, IdxOldest %d \n", dpbBuf->numShorts, dpbBuf->idxOldest);
  
  for (i = 0; i < dpbBuf->numShorts; i ++) {
    printf(" %d %d, ", refList0[i]->frameNum, refList0[i]->viewId);
  }
  printf("\n");
#endif
}


/*
 * markAsUnusedForRef:
 *
 * Parameters:
 *      dpbBuf                the DPB object
 *      picNumX               the picNum of the ref picture
 *      isShort               to indicate if ref picture is short or long term
 *
 * Function:
 *      mark a ref picture as "unused for ref"
 *
 * Returns:
 *      -
 */
static void markAsUnusedForRef(dpbBuf_s *dpbBuf, 
                               int picNumX, 
                               int isShort)
{
  int i;


  for (i = 0; i < dpbBuf->maxNumRefFrmsMVC; i++) {
    refFrmBuf_s *pRefFrm;

    pRefFrm = & dpbBuf->refFrmArr[i];
    if (pRefFrm->forRef && pRefFrm->isShortTerm == isShort && 
      pRefFrm->picNum == picNumX) 
    {
      pRefFrm->forRef = 0;
      pRefFrm->isShortTerm = -1;
    }
  }
}


/*
 * markAsUnusedForRef4:
 *
 * Parameters:
 *      dpbBuf                the DPB object
 *      longTermFrmIdx        the given idx threshold
 *
 * Function:
 *      mark all the ref picture as "unused for ref", which long term frame 
 *      idx is greater than the given idx
 *
 * Returns:
 *      -
 */
static void markAsUnusedForRef4(dpbBuf_s *dpbBuf, 
                                int longTermFrmIdx)
{
  int i;
  refFrmBuf_s *pRefFrm;


  for (i = 0; i < dpbBuf->maxNumRefFrmsMVC; i++) {
    pRefFrm = & dpbBuf->refFrmArr[i];

    if (pRefFrm->forRef && pRefFrm->isShortTerm == 0 && 
      pRefFrm->picNum >= longTermFrmIdx) 
    {
      pRefFrm->forRef = 0;
      pRefFrm->isShortTerm = -1;
    }
  }
}


/*
 * markAsLongTermRef:
 *
 * Parameters:
 *      dpbBuf                the DPB object
 *      picNumX               which short-term picture to be marked as a long-term ref pic
 *      longTermFrmIdx        the given long-term ref pic index
 *
 * Function:
 *      mark a short-term ref pic as a long-term ref pic
 *
 * Returns:
 *      -
 */
static void markAsLongTermRef(dpbBuf_s *dpbBuf, int picNumX, int longTermFrmIdx)
{
  int i;
  refFrmBuf_s *pRefFrm;


  for (i = 0; i < dpbBuf->maxNumRefFrmsMVC; i++) {
    pRefFrm = & dpbBuf->refFrmArr[i];

    if (pRefFrm->forRef == 1 && pRefFrm->isShortTerm == 1 && 
      pRefFrm->picNum == picNumX) 
    {
      pRefFrm->isShortTerm = 0;
      pRefFrm->picNum = longTermFrmIdx;
      return;
    }
  }
}


/*
 * dpbPicMarkingProcess:
 *
 * Parameters:
 *      dpbBuf                Decoded picture buffer object
 *      idrFlag               to indicate if current picture is an IDR picture or not
 *
 * Function:
 *      the reference picture marking process
 *
 * Returns:
 *      if success, the pointer to the empty frame buffer is returned
 *      otherwise, 0
 */
static refFrmBuf_s *dpbPicMarkingProcess(dpbBuf_s *dpbBuf, 
                                         int      idrFlag)
{
  int i;
  int picNumX;
  int isShort, longTermFrmIdx;
  int thisIsShort = 1, thisLongTermFrmIdx = 0;
  refFrmBuf_s *pRefFrm, *pEmptySlot;
  MMCO_s *mmcoList;


  /* Do reference picture marking process, subclause 8.2.5 */
  if (idrFlag) 
  {
    // IDR should not have any MMCO operations
    dpbBuf->numRefFrms = 0;

    for (i = 0; i < dpbBuf->maxNumRefFrmsMVC; i++) {
      dpbBuf->refFrmArr[i].isShortTerm = -1;
      dpbBuf->refFrmArr[i].forRef = 0;
    }
    if (dpbBuf->ltrIdr) 
    {
      thisIsShort = 0;
      thisLongTermFrmIdx = 0;
    }
  }
  else 
  {
    mmcoList = dpbBuf->mmcoList;

    // no MMCO operations
    if (mmcoList->mmco == 0)
    {
      /* 1. sliding window decoded reference picture marking process, -subclause 8.2.5.3 */
      if (dpbBuf->numRefFrms == dpbBuf->maxNumRefFrmsMVC)
      {
        // we know where the oldest short-term ref is 
        if (dpbBuf->numShorts > 0)
        {
          dpbBuf->refFrmArr[dpbBuf->idxOldest].forRef = 0;
          dpbBuf->refFrmArr[dpbBuf->idxOldest].isShortTerm = -1;
        }
      }
    }
    else {
      /* 2. MMCO -subclause 8.2.5.4 */
      while ( mmcoList ) {
        switch (mmcoList->mmco) {
        case 0:
          // mmco == 0 tells there is no more mmco operations
          break;
        case 1:
          picNumX = dpbBuf->frameNum - mmcoList->diffPicNumMinus1 - 1;
          isShort = 1;
          markAsUnusedForRef(dpbBuf, picNumX, isShort);
          break;
        case 2:
          picNumX = mmcoList->longTermPicNum;
          isShort = 0;
          markAsUnusedForRef(dpbBuf, picNumX, isShort);
          break;
        case 3:
          picNumX = dpbBuf->frameNum - mmcoList->diffPicNumMinus1 - 1;
          longTermFrmIdx = mmcoList->longTermFrmIdx;
          isShort = 0;
          markAsUnusedForRef(dpbBuf, longTermFrmIdx, isShort);
          markAsLongTermRef(dpbBuf, picNumX, longTermFrmIdx);
          break;
        case 4:
          markAsUnusedForRef4(dpbBuf, mmcoList->maxLongTermFrmIdxPlus1);
          break;
        case 5:
          for (i = 0; i < dpbBuf->maxNumRefFrmsMVC; i++) {
            if (dpbBuf->refFrmArr[i].forRef == 1) {
              dpbBuf->refFrmArr[i].isShortTerm = -1;
              dpbBuf->refFrmArr[i].forRef = 0;
            }
          }
          break;
        case 6:
          // to check if the same longTermFrmIdx has been used
          for (i = 0; i < dpbBuf->maxNumRefFrmsMVC; i++)
          {
            pRefFrm = & dpbBuf->refFrmArr[i];
            if (pRefFrm->forRef && (pRefFrm->isShortTerm == 0) && 
              pRefFrm->frameNum == mmcoList->longTermFrmIdx) 
            {
              dpbBuf->refFrmArr[i].isShortTerm = -1;
              dpbBuf->refFrmArr[i].forRef = 0;
              dpbBuf->numRefFrms--;
              break;
            }
          }

          thisIsShort = 0;
          thisLongTermFrmIdx = mmcoList->longTermFrmIdx;
          break;
        default:
          break;
        }

        mmcoList = mmcoList->next;
      }
    }
  }

  /* find the empty frame slot, set its status and return it */
  pEmptySlot = 0;
  for (i = 0; i < dpbBuf->maxNumRefFrmsMVC; i++) {
    pRefFrm = & dpbBuf->refFrmArr[i];

    if (pRefFrm->forOutput == 0 && pRefFrm->forRef == 0) {
      pRefFrm->forRef = 1;
      pRefFrm->isShortTerm = thisIsShort;
      if (thisIsShort) 
        pRefFrm->frameNum = dpbBuf->frameNum;
      else
        pRefFrm->frameNum = thisLongTermFrmIdx;

      pEmptySlot = pRefFrm;
      break;
    }
  }

  if (dpbBuf->numRefFrms < dpbBuf->maxNumRefFrmsMVC)
    dpbBuf->numRefFrms ++;

  return pEmptySlot;
}


/*
 * doBumpingOutput:
 *      the bumping process
 *      Not done in the encoder yet. 
 *      The re-ordering of reconstructed is performed by writing a frame 
 *      directly to the desired location in the file.
 */
void doBumpingOutput()
{
}


/*
 * dpbUpdate
 *
 * Parameters:
 *      dpbBuf                Decoded picture buffer object
 *      recoFrame             Reconstructed frame
 *      nalRefIdc             Indicate if this is a reference frame
 *      idrFlag               Indicate if this is an IDR frame
 *      low_complex_prof3     Low complexity profile 3 
 *      useSearchWin          Use internal search window
 *      viewId                The view id of the current view
 *
 * Function:
 *      Perform update operations after the frame is encoded.
 *
 * Returns:
 *      -
 */
void dpbUpdate(dpbBuf_s    *dpbBuf, 
               frmBuf_s    *recoFrame,
               int         nalRefIdc,
               int         idrFlag,
               int         low_complex_prof3
#ifdef ENABLE_SEARCH_WINDOW
               ,int         useSearchWin
#endif
               , int viewId)	
{
  refFrmBuf_s *refBuf;

  /*
   * update reference frame buffer
   */
  if (dpbBuf->maxNumRefFrmsMVC > 0) {
    doBumpingOutput();

    if (nalRefIdc > 0) {
      /* sliding window and /or MMCO operations */
      refBuf = dpbPicMarkingProcess(dpbBuf, idrFlag);

      /* store the reference picture into the DPB */
      if (refBuf)
      {
  		  refBuf->viewId = viewId;

        refFrmUpsampleLuma(refBuf, recoFrame->y, low_complex_prof3
#ifdef ENABLE_SEARCH_WINDOW
          , useSearchWin
#endif
          );

        refFrmExtendChroma(refBuf, recoFrame->u, recoFrame->v); 
        refFrmStoreChannelDistortion(refBuf, recoFrame->channelDistortion);

#ifdef ENABLE_SEARCH_WINDOW
        if (useSearchWin) {
          /* Swap reconstruction buffer and reference buffer */
          u_int8 *tmp  = recoFrame->y;
          recoFrame->y = refBuf->yBuf;
          refBuf->y    = tmp;
          refBuf->yBuf = tmp;
        }
#endif

      }
    }
  }
}

