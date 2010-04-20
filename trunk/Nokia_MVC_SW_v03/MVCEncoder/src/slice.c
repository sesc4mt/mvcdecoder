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
 * slice.c
 *
 * Contains:
 *    Slice layer functions
 *
 */

#include <math.h>
#include <string.h>
#include <limits.h>
#include "nccglob.h"
#include "globals.h"
#include "debug.h"
#include "bitbuffer.h"
#include "vlcutility.h"
#include "macroblock.h"
#include "slice.h"
#include "refframe.h"
#include "stream.h"
#include "ratecontrol.h"


/*
 * sliceSendRefListReordering
 *
 * Parameters:
 *      dpbBuf                    Decoded picture buffer
 *      bitbuf                    Bitbuffer
 *      viewId                    View Id of the current view
 *      interViewPred             Flag to signal prediction between views
 *
 * Function:
 *      Sends reference picture list reordering bits to the bitbuffer if required.
 *
 * Returns:
 *      Number of bits used.
 *
 */
static int sliceSendRefListReordering(dpbBuf_s    *dpbBuf, 
                                      bitbuffer_s *bitbuf,
                  									  int viewId,
                                      int interViewPred)
{
  int i, bits, numCmds;
  int refPicListReorderingFlagL0;


  // let's check whether it is necessary to send re-order command
  numCmds = dpbGetReorderCommands(dpbBuf);

  /* encode the reordering commands */
  refPicListReorderingFlagL0 = (numCmds != 0);

  /* Reorder pictures, if at the second view and there are enough reference pictures */
  if((viewId == 0 || dpbBuf->numRefFrms < 4) && (NUM_VIEWS > 1) || !(interViewPred) || !(dpbBuf->reorderRefPicList)) {
    bits = u_n(bitbuf, refPicListReorderingFlagL0, 1);
    
    if (refPicListReorderingFlagL0) {
      for (i = 0; i < numCmds; i++) {
        bits += ue_v(bitbuf, dpbBuf->reorderCmds[i].idc);
        
        if (dpbBuf->reorderCmds[i].idc == 0 || dpbBuf->reorderCmds[i].idc == 1)
          bits += ue_v(bitbuf, dpbBuf->reorderCmds[i].absDiffPicNumMinus1);
        else if (dpbBuf->reorderCmds[i].idc == 2)
          bits += ue_v(bitbuf, dpbBuf->reorderCmds[i].longTermPicNum);
      }
      
      // end of the re-order command list
      bits += ue_v(bitbuf, 3);
    }
  }
  else
  {
    /* Reorder the pictures */
    numCmds = 2;
    refPicListReorderingFlagL0 = (numCmds != 0);
    
    bits = u_n(bitbuf, refPicListReorderingFlagL0, 1);
    
    if (refPicListReorderingFlagL0) {

      /* These are hardcoded for now, first send [0,0] and then [5,0] */
      bits += ue_v(bitbuf, 0);
      bits += ue_v(bitbuf, 0);
      
      bits += ue_v(bitbuf, 5);
      bits += ue_v(bitbuf, 0);
      
      // end of the re-order command list
      bits += ue_v(bitbuf, 3);
    }
  }

  return bits;
}


/*
 * encRefPicMarking
 *
 * Parameters:
 *      slice                       Current slice
 *      mmcolist                    MMCO list
 *      idrLongTermRefFlag          Flag to signal IDR as long term reference
 *      bitbuf                      Bitbuffer
 *
 * Function:
 *      Sends reference picture list reordering bits to the bitbuffer if required.
 *
 * Returns:
 *      Number of bits used.
 *
 */
static int encRefPicMarking(slice_s     *slice, 
                            MMCO_s      *mmcoList, 
                            int         idrLongTermRefFlag,
                            bitbuffer_s *bitbuf)
{
  int bits = 0;
  int noOutputOfPriorPicsFlag, adaptiveRefMarkingModeFlag;


  noOutputOfPriorPicsFlag = 0;

  /* Decoded reference picture marking process will be delayed after all the slices are decoded */
  if (slice->isIDR) {
    bits += u_n(bitbuf, noOutputOfPriorPicsFlag, 1);
    bits += u_n(bitbuf, idrLongTermRefFlag, 1);
  }
  else { /* non-IDR */
    adaptiveRefMarkingModeFlag = 0;
    if (mmcoList->mmco != 0)
      adaptiveRefMarkingModeFlag = 1;

    bits += u_n(bitbuf, adaptiveRefMarkingModeFlag, 1);

    if (adaptiveRefMarkingModeFlag) {
      do {
        bits += ue_v(bitbuf, mmcoList->mmco);
        if (mmcoList->mmco == 1 || mmcoList->mmco == 3)
          bits += ue_v(bitbuf, mmcoList->diffPicNumMinus1);
        if (mmcoList->mmco == 2)
          bits += ue_v(bitbuf, mmcoList->longTermPicNum);
        if (mmcoList->mmco == 3 || mmcoList->mmco == 6)
          bits += ue_v(bitbuf, mmcoList->longTermFrmIdx);
        if (mmcoList->mmco == 4)
          bits += ue_v(bitbuf, mmcoList->maxLongTermFrmIdxPlus1);

        if (mmcoList->mmco != 0) {
          mmcoList = mmcoList->next;
        }
        else
          mmcoList = 0;
      } while (mmcoList != 0);
    }
  }

  return bits;
}


/*
 * startSlice
 *
 * Parameters:
 *      slice                 Slice coding structure
 *      sps                   Sequence parameter set
 *      pps                   Picture parameter set
 *      bitsNal               Pointer to counter accumulating NAL bits
 *
 * Function:
 *      Send slice header information.
 *
 * Returns:
 *      Length of the slice header in bits.
 *
 */
static int startSlice(slice_s             *slice, 
                      encParams_s         *encPar,
                      int                 firstMbAddr,
                      dpbBuf_s            *dpbBuf,
                      seq_parameter_set_s *sps, 
                      pic_parameter_set_s *pps,
                      int                 *bitsNal)
{
  int i, bits;
  int deltaQp, value;
  int expectedPicOrderCnt;
  int picOrderCntCycleCnt;
  int expectedDeltaPerPicOrderCntCycle;
  int frameNumInPicOrderCntCycle;
  int absFrameNum;
  int temp;
  int len1;
  bitbuffer_s *bitbuf;


  bitbuf = slice->bitbuf;
  bits = 0;
  picOrderCntCycleCnt = 0;
  frameNumInPicOrderCntCycle = 0;

  /* Do not take the bits prior to the starting code into account */
  /* Nor the naltype byte */
  /* 1 zero byte is always present */
  if ( NUM_VIEWS == 1 ) {
    if(encPar->rtp_flag == 0)
      *bitsNal += vlcuSendNalUnitStartCodePrefix(slice->bitbuf, 1);
    if (slice->isIDR == 1) 
      *bitsNal += vlcuSendNalHead(slice->bitbuf, slice->nalRefIdc, CODED_SLICE_IDR_NAL_TYPE);
    else 
      *bitsNal += vlcuSendNalHead(slice->bitbuf, slice->nalRefIdc, CODED_SLICE_NAL_TYPE);
  }
  else
  {
    /* Number of views is > 1, i.e. use MVC */
    if(encPar->rtp_flag == 0)
      *bitsNal += vlcuSendNalUnitStartCodePrefix(slice->bitbuf, 1);
    
    if (slice->isIDR == 1) 
    {
      /* First send the prefix NAL, then NAL */
      *bitsNal += vlcuSendNalHeadMVC(slice->bitbuf, slice->nalRefIdc, PREFIX_NAL_TYPE, 1, slice->viewId);

      if(encPar->rtp_flag == 0)
        *bitsNal += vlcuSendNalUnitStartCodePrefix(slice->bitbuf, 1);

      /* Switch nal_unit_type depending on whether we have a base view or not */
      if (slice->viewId == 0)
        *bitsNal += vlcuSendNalHead(slice->bitbuf, slice->nalRefIdc, CODED_SLICE_IDR_NAL_TYPE); /* Base view */
      else
        *bitsNal += vlcuSendNalHeadMVC(slice->bitbuf, slice->nalRefIdc, NON_BASE_VIEW_SLICE,1,slice->viewId);    /* Non-base view */
    }
    else 
    {
      /* First send the prefix NAL, then NAL */
      *bitsNal += vlcuSendNalHeadMVC(slice->bitbuf, slice->nalRefIdc, PREFIX_NAL_TYPE, 0, slice->viewId);
      
      if(encPar->rtp_flag == 0)
        *bitsNal += vlcuSendNalUnitStartCodePrefix(slice->bitbuf, 1);

      /* Switch nal_unit_type depending on whether we have a base view or not */
      if (slice->viewId == 0)
        *bitsNal += vlcuSendNalHead(slice->bitbuf, slice->nalRefIdc, CODED_SLICE_NAL_TYPE); /* Base view */
      else
        *bitsNal += vlcuSendNalHeadMVC(slice->bitbuf, slice->nalRefIdc, NON_BASE_VIEW_SLICE,0,slice->viewId);    /* Non-base view */
    }
  }
  
  /* first_mb_in_slice */
  bits += ue_v(bitbuf, firstMbAddr);
  
  /* slice_type */
  bits += ue_v(bitbuf, slice->sliceType);
  
  /* pps id, for us == view id */
  bits += ue_v(bitbuf, slice->viewId);
  
  /* frame_num */
  bits += u_n(bitbuf, dpbBuf->frameNum, encPar->log2_max_frame_num_minus4+4);
  
  /* idr pic id */
  if (slice->isIDR) {
    bits += ue_v(bitbuf, slice->idrPicId);
  }
  
  /* POC: Picture order count */
  if (sps->pic_order_cnt_type == 0) {
    unsigned int mask;
    
    /* pic_order_cnt_lsb */
    mask = (1 << (sps->log2_max_pic_order_cnt_lsb_minus4 + 4)) - 1;
    value = (slice->poc & mask);
    bits += u_n(bitbuf, value, sps->log2_max_pic_order_cnt_lsb_minus4+4);
  }
  else if (sps->pic_order_cnt_type == 1 && !sps->delta_pic_order_always_zero_flag) {
    
    /* Reset prevFrameNumOffset if needed */
    if (slice->isIDR || dpbBuf->prevPicHasMMCO5) { /* Todo: prevPicHasMMCO5 has not been tested. */
      dpbBuf->prevFrameNumOffset = 0;
    }
    
    /* frameNumOffset is derived as follows: */
    if (slice->isIDR)
      dpbBuf->frameNumOffset = 0;
    else if (dpbBuf->prevRefFrameNum > dpbBuf->frameNum)
      dpbBuf->frameNumOffset = dpbBuf->prevFrameNumOffset + dpbBuf->maxFrameNum;
    else
      dpbBuf->frameNumOffset = dpbBuf->prevFrameNumOffset;
    
    /* absFrameNum is derived as follows: */
    if (sps->num_ref_frames_in_pic_order_cnt_cycle != 0)
      absFrameNum = dpbBuf->frameNumOffset + dpbBuf->frameNum;
    else
      absFrameNum = 0;
    if (slice->nalRefIdc == 0 && absFrameNum > 0)
      absFrameNum = absFrameNum - 1;
    
    /* When absFrameNum > 0, picOrderCntCycleCnt and frameNumInPicOrderCntCycle are derived as follows */
    if (absFrameNum > 0) {
      picOrderCntCycleCnt = (absFrameNum - 1) / sps->num_ref_frames_in_pic_order_cnt_cycle;
      frameNumInPicOrderCntCycle = (absFrameNum - 1) % sps->num_ref_frames_in_pic_order_cnt_cycle;
    }
    
    /* expectedDeltaPerPicOrderCntCycle */
    expectedDeltaPerPicOrderCntCycle = 0;
    for (i = 0; i < (int)sps->num_ref_frames_in_pic_order_cnt_cycle; i++)
      expectedDeltaPerPicOrderCntCycle += sps->offset_for_ref_frame[i];
    
    /* expectedPicOrderCnt */
    if (absFrameNum > 0) {
      expectedPicOrderCnt = picOrderCntCycleCnt * expectedDeltaPerPicOrderCntCycle;
      for (i = 0; i <= frameNumInPicOrderCntCycle; i++)
        expectedPicOrderCnt = expectedPicOrderCnt + sps->offset_for_ref_frame[i];
    } else
      expectedPicOrderCnt = 0;
    if (slice->nalRefIdc == 0)
      expectedPicOrderCnt = expectedPicOrderCnt + sps->offset_for_non_ref_pic;
    
    /* delta_pic_order_cnt[ 0 ] */
    value = slice->poc - expectedPicOrderCnt;
    bits += se_v(bitbuf, value);
  }
  
  /* Redundant picture count */
  if (pps->redundant_pic_cnt_present_flag)
    bits += ue_v(bitbuf, slice->redundantPicCnt);
  
  slice->numRefIdxl0 = pps->num_ref_idx_l0_active_minus1 + 1;

  /* reference picture management */
  if (IS_SLICE_P(slice->sliceType)) {
    int numRefIdxActiveOverrideFlag;
    if (slice->viewId == 0 || encPar->viewPrediction) {
      // these should be dynamically determined
      numRefIdxActiveOverrideFlag = 
        ((int) (pps->num_ref_idx_l0_active_minus1 + 1) > dpbBuf->numRefFrms) ? 1 : 0;
    
      bits += u_n(bitbuf, numRefIdxActiveOverrideFlag, 1);
    
      if (numRefIdxActiveOverrideFlag) {
        bits += ue_v(bitbuf, dpbBuf->numRefFrms - 1);
        slice->numRefIdxl0 = dpbBuf->numRefFrms;
      }
    }
    else {    // ViewId == 1 && viewPrediction == 0
      numRefIdxActiveOverrideFlag = 
        ((int) (pps->num_ref_idx_l0_active_minus1 + 1) > dpbBuf->numActiveRef) ? 1 : 0;
    
      bits += u_n(bitbuf, numRefIdxActiveOverrideFlag, 1);
    
      if (numRefIdxActiveOverrideFlag) {
        bits += ue_v(bitbuf, dpbBuf->numActiveRef - 1);
        slice->numRefIdxl0 = dpbBuf->numActiveRef;
      }
    }
  }
  
  /* send reference frame reordering syntax elements */
  if (! IS_SLICE_I(slice->sliceType)) 
    bits += sliceSendRefListReordering(dpbBuf, bitbuf, slice->viewId, encPar->viewPrediction);
  
  /* ref pic marking, including writing MMCO commands if any. */
  if (slice->nalRefIdc) {
    bits += encRefPicMarking(slice, dpbBuf->mmcoList, dpbBuf->ltrIdr, bitbuf);
  }
  
  /* slice_qp_delta */
  deltaQp = slice->qp - pps->pic_init_qp_minus26 - 26;
  bits += se_v(bitbuf, deltaQp);
  
  /* deblocking filter */
  if (pps->deblocking_filter_parameters_present_flag == 1) {
    bits += ue_v(bitbuf, encPar->filterMode); // ue_v(bitbuf, &slice->disableDeblockingFilterIdc);
    if (encPar->filterMode != 1) {
      bits += se_v(bitbuf, encPar->alphaOffset/2);
      bits += se_v(bitbuf, encPar->betaOffset/2);
    }
  }
  
  /* macroblock to slice group map */
  if ((pps->num_slice_groups_minus1 > 0) && (pps->slice_group_map_type >= 3)
    && (pps->slice_group_map_type <= 5))
  {
    int picSizeInMapUnits;
    
    picSizeInMapUnits = slice->mbksPerCol * slice->mbksPerLine;
    
    // find minimal # of bits to store maximal possible sliceGroupChangeCycle
    // slightly different from the original implementation
    temp = picSizeInMapUnits/(pps->slice_group_change_rate_minus1 + 1);
    len1 = 0;
    do
    {
      len1 ++;
      temp >>= 1;
    } while (temp);
    
    /* read slice_group_change_cycle */
    bits += u_n(bitbuf, slice->sliceGroupChangeCycle, len1);
  }
  
  return bits;
}


/*
 * sliceGenerateMbMap
 *
 * Parameters:
 *      slice                 Slice coding structure
 *      pps                   Picture parameter set
 *
 * Function:
 *      Generate the slice group maps from the parameters stored in picture
 *      parameter set.
 *
 * Returns:
 *      -
 *
 */
void sliceGenerateMbMap(slice_s             *slice, 
                        pic_parameter_set_s *pps)
{
  int i, j, k;
  int x, y;
  int iGroup;
  int picSizeInMapUnits, picWidthInMbs, picHeightInMapUnits;
  int mapUnitsInSliceGroup0;
  int sizeOfUpperLeftGroup;
  mbState_s *pMbStateArr;


  pMbStateArr = slice->mbStateArr;
  for (i = 0; i < slice->picSizeInMbs; i ++) {
    // mbType is used to indicate whether an MB has been encoded
    pMbStateArr[i].mbType   = -1;
    pMbStateArr[i].sliceMap = 0;
  }

  /* macroblock to slice group map */
  if (pps->num_slice_groups_minus1 > 0) {
    picSizeInMapUnits   = slice->mbksPerCol * slice->mbksPerLine;
    picWidthInMbs       = slice->mbksPerLine;
    picHeightInMapUnits = slice->mbksPerCol;

    // mapUnitsInSliceGroup0 only used in slice_group_map_type 3, 4, 5
    mapUnitsInSliceGroup0 = slice->sliceGroupChangeCycle * 
      (pps->slice_group_change_rate_minus1 + 1);
    mapUnitsInSliceGroup0 =	min(mapUnitsInSliceGroup0, picSizeInMapUnits);

    switch (pps->slice_group_map_type) {
      /* type 0, 1 can be moved to the function activating parameter set. */
    case SLICE_MAP_INTERLEAVED:
      // the parameters should not violate the frame constraints
      i = 0;
      do {
        for (iGroup = 0; iGroup <= (int)pps->num_slice_groups_minus1 && i < picSizeInMapUnits;
          i += pps->run_length_minus1[iGroup++] + 1)
        {
          for (j = 0; j <= (int)pps->run_length_minus1[iGroup] && i+j < picSizeInMapUnits; j++)
            pMbStateArr[i+j].sliceMap |= iGroup;   /* Only the group number */
        }
      } while (i < picSizeInMapUnits);
      break;

    case SLICE_MAP_DISPERSED:
      {
        int numGroups, offset;

        numGroups = pps->num_slice_groups_minus1 + 1;
        for (i = 0; i < picSizeInMapUnits; i ++)
        {
          // offset makes an even row start with group 0, 
          // an odd row start with group "numGroups/2"
          offset = ((i/picWidthInMbs) * numGroups)/2;
          pMbStateArr[i].sliceMap = 
            (int16) (((i % picWidthInMbs) + offset) % numGroups);
        }
      }
      break;

    case SLICE_MAP_FOREGROUND:
      // background, with the largest ground ID
      for (i = 0; i < picSizeInMapUnits; i++)
        pMbStateArr[i].sliceMap = (int16) pps->num_slice_groups_minus1;

      // foreground, rectangles can overlap
      // overlapping area will be in the group with the smallest ID
      for (iGroup = pps->num_slice_groups_minus1 - 1; iGroup >= 0; iGroup--) {
        int xTopLeft, yTopLeft, xBottomRight, yBottomRight;

        yTopLeft = pps->top_left[iGroup] / picWidthInMbs;
        xTopLeft = pps->top_left[iGroup] % picWidthInMbs;
        yBottomRight = pps->bottom_right[iGroup] / picWidthInMbs;
        xBottomRight = pps->bottom_right[iGroup] % picWidthInMbs;

        for (y = yTopLeft; y <= yBottomRight; y++)
          for (x = xTopLeft; x <= xBottomRight; x++)
            pMbStateArr[y * picWidthInMbs + x].sliceMap = (int16) iGroup;
      }
      break;

    case SLICE_MAP_BOX_OUT:
      {
        int leftBound, topBound, rightBound, bottomBound;
        int xDir, yDir;
        int mapUnitVacant;

        for (i = 0; i < picSizeInMapUnits; i++)
          pMbStateArr[i].sliceMap = 1;

        x = (picWidthInMbs - pps->slice_group_change_direction_flag)/2;
        y = (picHeightInMapUnits - pps->slice_group_change_direction_flag)/2;

        leftBound = x; 
        topBound = y;

        rightBound = x; 
        bottomBound = y;

        xDir = pps->slice_group_change_direction_flag - 1;
        yDir = pps->slice_group_change_direction_flag;

        for (i = 0; i < mapUnitsInSliceGroup0; i += mapUnitVacant) {
          mapUnitVacant = (pMbStateArr[y * picWidthInMbs + x].sliceMap == 1);
          if (mapUnitVacant)
            pMbStateArr[y * picWidthInMbs + x].sliceMap = 0;

          if (xDir == -1 && x == leftBound) {
            // reach left bound, shift one step left, then move vertically
            leftBound = max(leftBound - 1, 0);
            x = leftBound;
            xDir = 0;

            // move up if direction_flag is 0, otherwise move down
            yDir = 2 * pps->slice_group_change_direction_flag - 1;
          } 
          else if (xDir == 1 && x == rightBound) {
            // reach right bound, shift one step right, then move vertically
            rightBound = min(rightBound + 1, picWidthInMbs - 1);
            x = rightBound;
            xDir = 0;

            // move down if direction_flag is 0, otherwise move up
            yDir = 1 - 2 * pps->slice_group_change_direction_flag;
          }
          else if (yDir == -1 && y == topBound) {
            // reach top bound, shift one step up, then move horizontally
            topBound = max(topBound - 1, 0);
            y = topBound;

            // move to right if direction_flag is 0, otherwise move to left
            xDir = 1 - 2 * pps->slice_group_change_direction_flag;
            yDir = 0;
          } 
          else if (yDir == 1 && y == bottomBound) {
            // reach bottom bound, shift one step down, then move horizontally
            bottomBound = min(bottomBound + 1, picHeightInMapUnits - 1);
            y = bottomBound;

            // move to left if direction_flag is 0, otherwise move to right
            xDir = 2 * pps->slice_group_change_direction_flag - 1;
            yDir = 0;
          } 
          else {
            // just move according to pre-determined direction
            x = x + xDir;
            y = y + yDir;
          }
        }
      }
      break;

    case SLICE_MAP_RASTER:
    case SLICE_MAP_WIPE:
      sizeOfUpperLeftGroup = pps->slice_group_change_direction_flag ? 
        (picSizeInMapUnits - mapUnitsInSliceGroup0) : mapUnitsInSliceGroup0;
      iGroup = pps->slice_group_change_direction_flag;

      if (pps->slice_group_map_type == SLICE_MAP_RASTER)
      {
        for (i = 0; i < picSizeInMapUnits; i ++)
        {
          if (i >= sizeOfUpperLeftGroup)
            // change to another slice group
            iGroup = 1 - pps->slice_group_change_direction_flag;
          pMbStateArr[i].sliceMap = (int16) iGroup;
        }
      }
      else
      {
        k = 0;
        for (j = 0; j < picWidthInMbs; j ++)
          for (i = 0; i < picHeightInMapUnits; i ++)
          {
            if( k ++ >= sizeOfUpperLeftGroup )
              // change to another slice group
              iGroup = 1 - pps->slice_group_change_direction_flag;
            pMbStateArr[i * picWidthInMbs + j].sliceMap = (int16) iGroup;
          }
      }
      break;

    case SLICE_MAP_BITMAP:
      for (i = 0; i < picSizeInMapUnits; i++)
        pMbStateArr[i].sliceMap = pps->slice_group_id[i];
      break;
    default:
      break;
    }
  }
}


/*
 * sliceEncode
 *
 * Parameters:
 *      slice                 SLice object
 *      sliceIdxInGroup       Index of this slice within a slice group       
 *      sps                   Sequence parameter set
 *      pps                   Picture parameter set
 *      pBrc                  pointer to bit rate control engine,
 *
 * Function:
 *      Encode one slice
 *
 * Returns:
 *      0   This is not the last slice in the current frame
 *      1   This is the last slice in the current slice group of the current frame
 */
int sliceEncode(slice_s             *slice, 
                int                 sliceIdxInGroup, 
                dpbBuf_s            *dpbBuf,
                encParams_s         *encPar,
                int                 tuneFactor,
                int                 *mapRIR,
                seq_parameter_set_s *sps, 
                pic_parameter_set_s *pps,
                int                 forcedIRNo,
                int                 *forcedIR,
                rateCtrl_s          *pbRC,
                int                 *AIR_intraMap)

{
  int numBits;
  int sliceDataStartBits;
  int sliceStartBits, targetSliceSize, maxSliceSize;
  int maxMbsPerSlice;
  int mbNum, numIntraMbs;
  macroblock_s *mb;
  meProfile_s  *pMeProf;
  refFrmBuf_s  **refFrmBufs;    /* Interface for MB layer. */
  mbState_s    *mbStateArr;
  void         *stream;
  int numRefFrms;
  int nextSliceAddr;
  int maxMbBits = 0, mbBits = 0;
  int temp_header= 0;
  int temp_texture = 0;
  int currentViewId;
  int numCodingRef;
  int numSkippedTemp;

  /* Bit buffer state */
  bitbuffer_s bitbufTemp;

  /* store the member state of frmStat */
  statSlice_s frmStatTemp;


  mbStateArr = slice->mbStateArr;

  mb         = & slice->mb;
  pMeProf    = & slice->meProfile;

  sliceStartBits = bibGetNumBits(slice->bitbuf);
  sliceDataStartBits = sliceStartBits;    // just to avoid compiler complaint

  currentViewId = slice->viewId;

  dpbRefListNormalOrder(dpbBuf, currentViewId, encPar->viewPrediction, (IS_SLICE_I(slice->sliceType)));

  // Reference picture list (Interface for MB layer)
  refFrmBufs = dpbBuf->refPicList0;
  
  //Intra Refresh Type
  mb->irType = (u_int8) encPar->irType;

  // setup the motion estimation profile
  if (IS_SLICE_P(slice->sliceType)) {

    numRefFrms = dpbBuf->numActiveRef;
    mesPrepareProfile(pMeProf, refFrmBufs[0], encPar, numRefFrms);

#ifdef ENABLE_SEARCH_WINDOW
    if (slice->meProfile.sWin.useSearchWin)
      slice->meProfile.sWin.refFrm = refFrmBufs[0]->y;
#endif
  }

  // if nBytesPerSlice is 0, no fixed length slices, set the size to max
  targetSliceSize = (encPar->nBytesPerSlice == 0) ? INT_MAX : 8 * 
    (encPar->nBytesPerSlice - 4);
  
  maxSliceSize = (encPar->maxBytesPerSlice == 0) ? INT_MAX : 8 * 
    (encPar->maxBytesPerSlice - 4);

  // If nMbsPerSlice is 0, set number of mbs per slice to max
  maxMbsPerSlice = (encPar->nMbsPerSlice == 0) ? INT_MAX : encPar->nMbsPerSlice;

  // Initialize macroblock before the slice is encoded
  mbkBeforeSlice(mb, slice->qp);

  stream = slice->bitbuf;

  // in the first run, the best frame order will be found
  numIntraMbs = 0;

  // perform the reordering of the reference frame pointers
  numRefFrms = dpbBuf->numActiveRef;

  slice->frmStat->bitsHdr += startSlice(slice, encPar, slice->firstMbAddr, 
    dpbBuf, sps, pps, & slice->frmStat->bitsNAL);

  sliceDataStartBits = bibGetNumBits(slice->bitbuf);
 
  // Scan through all macroblocks in slice
  nextSliceAddr = slice->firstMbAddr;

  mbNum = 0;

  do {
    mbState_s *pMbState;
    
    // setup the address of the current macroblock
    mb->mbAddr = nextSliceAddr;
    mb->idxX   = nextSliceAddr % slice->mbksPerLine;
    mb->idxY   = nextSliceAddr / slice->mbksPerLine;

    // look for the next MB in the same slice group
    do {
      nextSliceAddr ++;
    } while (nextSliceAddr < slice->picSizeInMbs && 
      (mbStateArr[nextSliceAddr].sliceMap & 0xF) != slice->groupId);

    mb->currentView = currentViewId;

    // if next MB is available, nextSliceAddr should be within the frame
    mb->isLastMb = (nextSliceAddr == slice->picSizeInMbs) || (mbNum+1 == maxMbsPerSlice);

    // Perform bit-rate control
    numBits = bibGetNumBits(slice->bitbuf);

    if(pbRC->bit_rate != 0)
    {
        temp_header =   
          slice->frmStat->bitsNAL +
          slice->frmStat->bitsHdr +
          slice->frmStat->bitsSkipLen +
          slice->frmStat->bitsMBtype +
          slice->frmStat->bitsPred +
          slice->frmStat->bitsVec +
          slice->frmStat->bitsCBP;

        temp_texture = 
          slice->frmStat->bitsCoefLumaDC +
          slice->frmStat->bitsCoefLuma +
          slice->frmStat->bitsCoefChromaDC +
          slice->frmStat->bitsCoefChroma +
          slice->frmStat->bitsArithmeticStream ;  
    }

    // this is to collect the statistics
    mbkStartEnc(mb, slice->mbStateArr, slice->origBuf, slice->recoBuf, 
      encPar, slice->qp, tuneFactor);

    // mbAddr is calculated in mbkStartEnc
    pMbState = & mbStateArr[mb->mbAddr];

    // differentiate slices within the same slice group
    pMbState->sliceMap |= sliceIdxInGroup << 4;

    // Put loopfilter mode
    pMbState->filterMode  = (int8) encPar->filterMode;
    pMbState->alphaOffset = (int8) encPar->alphaOffset;
    pMbState->betaOffset  = (int8) encPar->betaOffset;

    mbkModeSelection(pbRC,mb, pMeProf, refFrmBufs, numRefFrms, 
    slice->sliceType, encPar, mapRIR, slice->recoBuf->channelDistortion, forcedIRNo, forcedIR, mb->idxY*encPar->picWidth/MBK_SIZE+mb->idxX,AIR_intraMap);

    slice->qp = (short) mb->qp;

    // otherwise (temporary), intra-4x4 was fully processed, using nominal qp
    mbkProcessData(mb, slice->sliceType, encPar);

    if (maxSliceSize < INT_MAX)
    {
      numSkippedTemp = mb->numSkipped;
      /* Bit buffer state */
      bibSaveState(slice->bitbuf, &bitbufTemp);
      /* save the temporary state of frmStat for slice overflow forbidden implementation */
      staSaveState(slice->frmStat, &frmStatTemp);
    }

    // VLC coding of macroblock

    /* numCodingRef is needed for the MB header */
    numCodingRef = slice->numRefIdxl0;

    mbkSend(stream,
      mb, numCodingRef, slice->sliceType, slice->frmStat);
    
    if ((bibGetNumBits(slice->bitbuf) - sliceStartBits >= maxSliceSize) && (mb->mbAddr != slice->firstMbAddr))
    {
      mb->isLastMb = 1;
      mb->numSkipped = numSkippedTemp;
      /* update the frmStat to previous state as the last encoded MB belong to next slice */
      staRestoreState(slice->frmStat, &frmStatTemp);
      /* Bit buffer state */
      bibRestoreState(slice->bitbuf, &bitbufTemp);
      /* reset MB state */
      slice->mbStateArr[mb->mbAddr].mbType = -1;
      slice->mbStateArr[mb->mbAddr].sliceMap &= 0xf;

      break;
    }

    mbBits = bibGetNumBits(slice->bitbuf) - numBits ;
    
    numBits += mbBits;
    
    if(mbBits > maxMbBits)
      maxMbBits = mbBits;
    
    if (((numBits - sliceStartBits + 32) >= maxSliceSize) ||
      ((numBits - sliceStartBits + maxMbBits) >= targetSliceSize)
      )
      mb->isLastMb = 1;

    // some bookkeeping at the end of encoding
    mbkFinishEnc(mb, slice->frmStat);

    if (mb->type == MBK_INTRA)
      numIntraMbs ++;

    if (mb->type == MBK_INTRA)
      pbRC->numIntraMBs++;

    if(pbRC->bit_rate != 0)
    {
      temp_header =   
        slice->frmStat->bitsNAL +
        slice->frmStat->bitsHdr +
        slice->frmStat->bitsSkipLen +
        slice->frmStat->bitsMBtype +
        slice->frmStat->bitsPred +
        slice->frmStat->bitsVec +
        slice->frmStat->bitsCBP - temp_header;

      temp_texture = 
        slice->frmStat->bitsCoefLumaDC +
        slice->frmStat->bitsCoefLuma +
        slice->frmStat->bitsCoefChromaDC +
        slice->frmStat->bitsCoefChroma +
        slice->frmStat->bitsArithmeticStream - temp_texture;  
      
        rc_updateMB(pbRC,temp_texture,temp_header,mb->minMSE,mb->type,mb->interMode,mb->idxY*encPar->picWidth / MBK_SIZE+mb->idxX);
    }

    mbNum++;
  } while (!mb->isLastMb);

  // Check if skip flag needs to be sent at the end of slice
  if (IS_SLICE_P(slice->sliceType) && mb->numSkipped > 0)
    streamSendMbSkipFlag(stream, mb, 0);

  // end the slice by sending the trailing bits
  slice->frmStat->bitsHdr += bibTrailingBits(slice->bitbuf);

  if(bibGetNumBits(slice->bitbuf) - sliceStartBits > maxSliceSize)
    return AVCE_FRAME_SKIP_SLICE_OVERFLOW;
  else
    return numIntraMbs;
}


