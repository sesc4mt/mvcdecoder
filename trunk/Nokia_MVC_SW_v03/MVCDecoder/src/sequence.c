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
 * sequence.c
 *
 * Contains:
 *    Functions for sequence layer.
 *
 */

#include <string.h>
#include "nccglob.h"
#include "globals.h"
#include "bitbuffer.h"
#include "vld.h"
#include "framebuffer.h"
#include "avcdecoder.h"
#include "parameterset.h"
#include "loopfilter.h"
#include "dpb.h"
#include "sequence.h"
#include "conversion.h"
#include <time.h>

#ifdef ERROR_CONCEALMENT
#include "sei.h"
#include "errorconcealment.h"
#endif


#define SEQ_OK                      0
#define SEQ_ERROR                  -1
#define SEQ_ERR_MEM                -2
#define SEQ_ERR_GAPS_IN_FRAME_NUM  -3
#define SEQ_ERR_DPB_CORRUPTED      -4


/*
 * Definitions of NAL types
 */
#define NAL_TYPE_UNSPECIFIED      0
#define NAL_TYPE_CODED_SLICE      1
#define NAL_TYPE_CODED_SLICE_P_A  2
#define NAL_TYPE_CODED_SLICE_P_B  3
#define NAL_TYPE_CODED_SLICE_P_C  4
#define NAL_TYPE_CODED_SLICE_IDR  5
#define NAL_TYPE_SEI              6
#define NAL_TYPE_SPS              7
#define NAL_TYPE_PPS              8
#define NAL_TYPE_AU_DELIMITER     9
#define NAL_TYPE_END_SEQ          10
#define NAL_TYPE_END_STREAM       11
#define NAL_TYPE_FILLER_DATA      12
#define NAL_TYPE_PREFIX			      14
#define NAL_TYPE_SUBSET_SPS		    15
#define NAL_NON_BASE_VIEW_SLICE   20

/* 
 * Definitions of SEI types
 */
#define SEI_TYPE_SCENE_INFO       9


#ifdef CHECK_MV_RANGE
int maxVerticalMvRange;
#endif


int openOutputFiles(sequence_s *seq);
void closeOutputFiles(sequence_s *seq);
void writeYUVOut(sequence_s *seq, frmBuf_s *recoBuf, int viewId);
int decodeMVCPrefix(sequence_s *seq, int nalType);


/* Return fixed length code */
static int u_n(bitbuffer_s *bitbuf, int len, unsigned int *val)
{
  *val = vldGetFLC(bitbuf, len);

  if (bibGetStatus(bitbuf) < 0)
    return PS_ERROR;

  return PS_OK;
}


/*
 * setLower4Bits:
 *
 * Parameters:
 *      value               the destination to store the 4 bits
 *      bits                the 4 bits to be copied
 *
 * Function:
 *      Assign the value to the lowest 4 bits
 *
 *  Return:
 *      -
 */
#define setLower4Bits(value, bits) (value) = ((value) & ~0xF) | ((bits))


/*
 *
 * avcdOpen:
 *
 * Parameters:
 *      -
 *
 * Function:
 *      Open AVC decoder.
 *      
 * Returns:
 *      Pointer to initialized avcdDecoder_t object
 */
avcdDecoder_t *avcdOpen()
{
  sequence_s *seq;

  /*
   * Allocate sequence object
   */
  if ((seq = (sequence_s *)nccMalloc(sizeof(sequence_s))) == NULL)
    return NULL;

  memset(seq, 0, sizeof(sequence_s));

  seq->isFirstSliceOfSeq       = 1;
  seq->unusedShortTermFrameNum = -1;

  seq->decResult = AVCD_OK;

  /*
   * Open slices
   */
  if ((seq->currSlice = sliceOpen()) == NULL)
    return NULL;

  if ((seq->nextSlice = sliceOpen()) == NULL)
    return NULL;

  /*
   * Open dpb
   */
  if ((seq->dpb = dpbOpen()) == NULL)
    return NULL;

  /*
   * Open bitbuffer
   */
  if ((seq->bitbuf = bibOpen()) == NULL)
    return NULL;

#ifdef ERROR_CONCEALMENT
  /* 
   * Open scene info SEI
   */
  if ((seq->currSceneInfo = seiSceneOpen()) == NULL)
    return NULL;
  if ((seq->prevSceneInfo = seiSceneOpen()) == NULL)
    return NULL;
  seq->hasSceneInfo = 0;
  seq->sceneInfoDecoded = 0;
#endif

#ifdef DEBUG_PRINT
  seq->filterTime = 0.0;
  seq->intraTime = 0.0;
  seq->interTime = 0.0;
  seq->vldTime = 0.0;
  seq->codingTime = 0.0;
  seq->frameTime = 0.0;
  seq->interlaceTime = 0.0;
#endif
  seq->outputFrameIdx = 0;
  
  return seq;
}


/*
 *
 * avcdClose:
 *
 * Parameters:
 *      seq                   Sequence object
 *
 * Function:
 *      Close sequence.
 *      
 * Returns:
 *      -
 */
void avcdClose(avcdDecoder_t *dec)
{
  sequence_s *seq = (sequence_s *)dec;

  /* Close current frame */
  frmClose(seq->recoBuf, seq->mbData);

  /* Close decoded picture buffer */
  dpbClose(seq->dpb);

  /* Close bitbuffer */
  bibClose(seq->bitbuf);

  /* Close parameter sets */
  psCloseParametersSets(seq->spsList, seq->ppsList);

  /* Close slices */
  sliceClose(seq->currSlice);
  sliceClose(seq->nextSlice);

#ifdef ERROR_CONCEALMENT
  /* Close error concealment */
  ercClose(seq->errConcealment);

  /* Close SEIs */
  seiSceneClose(seq->currSceneInfo);
  seiSceneClose(seq->prevSceneInfo);
#endif

  /* Close display buffer */
  closeDisplayBuffer(seq->displayBuffer);

  if (seq->writeYUV)
    closeOutputFiles(seq);

  nccFree(seq);
}


/*
 *
 * slidingWindowDecRefPicMarking:
 *
 * Parameters:
 *      seq                   Sequence object
 *
 * Function:
 *      Sliding window decoded reference picture marking. Reference pictures
 *      in dpb are marked based on first in first out principle.
 *      
 * Returns:
 *      SEQ_OK for no error, negative value for error
 */
static int slidingWindowDecRefPicMarking(sequence_s *seq)
{
  dpb_s *dpb;
  int numRefPics;


  dpb = seq->dpb;

  numRefPics = dpb->numShortTermPics[seq->currSlice->viewId] + dpb->numLongTermPics[seq->currSlice->viewId];

  /* If dpb contains maximum number of reference pitures allowed, short */
  /*  term reference picture with lowest picture number is removed.     */
  if (numRefPics == dpb->maxNumRefFrames) {
    if (dpb->numShortTermPics[seq->currSlice->viewId] == 0) {
      printf("numShortTerm must be greater than zero\n");
      return SEQ_ERR_DPB_CORRUPTED;
    }

    dpbMarkLowestShortTermPicAsNonRef(dpb, seq->currSlice->viewId);
  }

  return SEQ_OK;
}


/*
 *
 * adaptiveDecRefPicMarking:
 *
 * Parameters:
 *      seq                   Sequence object
 *
 * Function:
 *      Adaptive decoded reference picture marking. Reference pictures in dpb
 *      are marked based on memory management command operations that were
 *      decoded in slice header earlier.
 *      
 * Returns:
 *      SEQ_OK for no error, SEQ_ERR_DPB_CORRUPTED for error in DPB
 */
static int adaptiveDecRefPicMarking(sequence_s *seq)
{
  dpb_s *dpb;
  sliceMMCO_s *mmcoCmdList;
  int32 currPicNum, picNumX;
  int i;


  dpb = seq->dpb;
  currPicNum = seq->currSlice->frame_num;
  mmcoCmdList = seq->currSlice->mmcoCmdList;

  i = 0;
  do {
    switch (mmcoCmdList[i].memory_management_control_operation) {
      case 1:
        picNumX = currPicNum - (mmcoCmdList[i].difference_of_pic_nums_minus1 + 1);
        if (dpbMarkShortTermPicAsNonRef(dpb, picNumX, seq->currSlice->viewId) < 0)
          return SEQ_ERR_DPB_CORRUPTED;
        break;
      case 2:
        if (dpbMarkLongTermPicAsNonRef(dpb, mmcoCmdList[i].long_term_pic_num, seq->currSlice->viewId) < 0)
          return SEQ_ERR_DPB_CORRUPTED;
        break;
      case 3:
        picNumX = currPicNum - (mmcoCmdList[i].difference_of_pic_nums_minus1 + 1);
        if (dpbMarkShortTermPicAsLongTerm(dpb, picNumX, mmcoCmdList[i].long_term_frame_idx, seq->currSlice->viewId) < 0)
          return SEQ_ERR_DPB_CORRUPTED;
        break;
      case 4:
        dpbSetMaxLongTermFrameIdx(dpb, mmcoCmdList[i].max_long_term_frame_idx_plus1, seq->currSlice->viewId);
        break;
      case 5:
        dpbMarkAllPicsAsNonRef(dpb);
        dpb->maxLongTermFrameIdx[seq->currSlice->viewId] = -1;
        break;
      case 6:
        /* To avoid duplicate of longTermFrmIdx */
        dpbVerifyLongTermFrmIdx(dpb, mmcoCmdList[i].long_term_frame_idx, seq->currSlice->viewId);

        seq->recoBuf->refType        = FRM_LONG_TERM_PIC;
        seq->recoBuf->longTermFrmIdx = mmcoCmdList[i].long_term_frame_idx;
        break;
    }
    i++;
  } while (mmcoCmdList[i].memory_management_control_operation != 0 && i < MAX_NUM_OF_MMCO_OPS);

  return SEQ_OK;
}


/*
 *
 * decRefPicMarking:
 *
 * Parameters:
 *      seq                   Sequence object
 *
 * Function:
 *      Decoded reference picture marking. Reference pictures in dpb are marked
 *      differently depending on whether current picture is IDR picture or not
 *      and whether it is reference picture or non-reference picture.
 *      If current picture is non-IDR reference picture, reference pictures are
 *      marked with either sliding window marking process or adaptive marking
 *      process depending on the adaptiveRefPicMarkingModeFlag flag.
 *      
 * Returns:
 *      -
 */
static int decRefPicMarking(sequence_s *seq)
{
  slice_s *slice;
  frmBuf_s *recoBuf;


  slice = seq->currSlice;
  recoBuf = seq->recoBuf;

  recoBuf->refType  = FRM_SHORT_TERM_PIC;
  recoBuf->frameNum = slice->frame_num;
  recoBuf->hasMMCO5 = slice->picHasMMCO5;
  recoBuf->isIDR    = slice->isIDR;

  if (slice->isIDR) {
    recoBuf->idrPicID = slice->idr_pic_id;

    /* All reference frames are marked as non-reference frames */
    dpbMarkAllPicsAsNonRef(seq->dpb);

    /* Set reference type for current picture */
    if (!slice->long_term_reference_flag) {
      seq->dpb->maxLongTermFrameIdx[slice->viewId] = -1;
    }
    else {
      recoBuf->refType         = FRM_LONG_TERM_PIC;
      recoBuf->longTermFrmIdx  = 0;
      seq->dpb->maxLongTermFrameIdx[slice->viewId] = 0;
    }
  }
  else if (slice->nalRefIdc != 0) {
    if (!slice->adaptive_ref_pic_marking_mode_flag)
      return slidingWindowDecRefPicMarking(seq);
    else
      return adaptiveDecRefPicMarking(seq);
  }
  else
    recoBuf->refType  = FRM_NON_REF_PIC;

  return SEQ_OK;
} 


/*
 *
 * buildSliceGroups:
 *
 * Parameters:
 *      seq                   Sequence object
 *      slice                 Slice object
 *      sps                   Sequence parameter set
 *      pps                   Picture parameter set
 *
 * Function:
 *      Build slice group map. Syntax elements for slice groups are
 *      in active picture parameter set.
 *      
 * Returns:
 *      -
 *
 */
static void buildSliceGroups(sequence_s* seq, slice_s *slice,
                             seq_parameter_set_s *sps, pic_parameter_set_s *pps)
{
  int xTopLeft, yTopLeft;
  int xBottomRight, yBottomRight;
  int x, y;
  int leftBound, topBound;
  int rightBound, bottomBound;
  int xDir, yDir;
  int mapUnitsInSliceGroup0;
  int mapUnitVacant;
  int sizeOfUpperLeftGroup;
  int iGroup, picSizeInMapUnits;
  int picWidthInMbs, picHeightInMapUnits;
  int i, j, k;
  int *sliceMap;


  sliceMap = seq->mbData->sliceMap;

  picWidthInMbs = sps->pic_width_in_mbs_minus1+1;
  picHeightInMapUnits = sps->pic_height_in_map_units_minus1+1;

  picSizeInMapUnits = picWidthInMbs * picHeightInMapUnits;

  if (pps->num_slice_groups_minus1 == 0) {
    /* Only one slice group */
    for (i = 0; i < picSizeInMapUnits; i++)
      sliceMap[i] = 0;
  }
  else {
    /* There are more than one slice groups in this picture */

    switch (pps->slice_group_map_type) {

    case PS_SLICE_GROUP_MAP_TYPE_INTERLEAVED:
      i = 0;
      do {
        for (iGroup = 0; iGroup <= (int)pps->num_slice_groups_minus1 && i < picSizeInMapUnits;
          i += pps->run_length_minus1[iGroup++] + 1)
        {
          for (j = 0; j <= (int)pps->run_length_minus1[iGroup] && i+j < picSizeInMapUnits; j++)
            sliceMap[i+j] = iGroup;   /* Only the group number */
        }
      } while (i < picSizeInMapUnits);
      break;

    case PS_SLICE_GROUP_MAP_TYPE_DISPERSED:
      for ( i = 0; i < picSizeInMapUnits; i++ )
        sliceMap[i] = ( ( i % picWidthInMbs ) + 
        ( ( ( i / picWidthInMbs ) * ( pps->num_slice_groups_minus1 + 1 ) ) / 2 ) )
        % ( pps->num_slice_groups_minus1 + 1 );
      break;

    case PS_SLICE_GROUP_MAP_TYPE_FOREGROUND:
      for (i = 0; i < picSizeInMapUnits; i++)
        setLower4Bits(sliceMap[i], pps->num_slice_groups_minus1);
      for (iGroup = pps->num_slice_groups_minus1 - 1; iGroup >= 0; iGroup--) {
        yTopLeft = pps->top_left[iGroup] / picWidthInMbs;
        xTopLeft = pps->top_left[iGroup] % picWidthInMbs;
        yBottomRight = pps->bottom_right[iGroup] / picWidthInMbs;
        xBottomRight = pps->bottom_right[iGroup] % picWidthInMbs;
        for (y = yTopLeft; y <= yBottomRight; y++)
          for (x = xTopLeft; x <= xBottomRight; x++)
            sliceMap[y * picWidthInMbs + x] = iGroup;
      }
      break;

    case PS_SLICE_GROUP_MAP_TYPE_CHANGING_3:
      /* mapUnitsInSliceGroup0 */
      mapUnitsInSliceGroup0 =	min((int)(slice->slice_group_change_cycle * (pps->slice_group_change_rate_minus1+1)), picSizeInMapUnits);

      for (i = 0; i < picSizeInMapUnits; i++)
        sliceMap[i] = 1; // mapUnitToSliceGroupMap[ i ] = 1;

      x = (picWidthInMbs - pps->slice_group_change_direction_flag) / 2;
      y = (picHeightInMapUnits - pps->slice_group_change_direction_flag ) / 2;
      // ( leftBound, topBound ) = ( x, y )
      leftBound = x; 
      topBound = y;
      // ( rightBound, bottomBound ) = ( x, y )
      rightBound = x; 
      bottomBound = y;
      // ( xDir, yDir ) = ( slice_group_change_direction_flag - 1, slice_group_change_direction_flag )
      xDir = pps->slice_group_change_direction_flag - 1;
      yDir = pps->slice_group_change_direction_flag;
      for (i = 0; i < mapUnitsInSliceGroup0; i += mapUnitVacant) {
        mapUnitVacant = ( (sliceMap[y * picWidthInMbs + x] & 0xF) == 1);
        if (mapUnitVacant)
          setLower4Bits(sliceMap[y * picWidthInMbs + x], 0);
        if (xDir == -1 && x == leftBound) {
          leftBound = max(leftBound - 1, 0);
          x = leftBound;
          //( xDir, yDir ) = ( 0, 2 * slice_group_change_direction_flag - 1 )
          xDir = 0;
          yDir = 2 * pps->slice_group_change_direction_flag - 1;
        } 
        else if (xDir == 1 && x == rightBound) {
          rightBound = min(rightBound + 1, picWidthInMbs - 1);
          x = rightBound;
          //( xDir, yDir ) = ( 0, 1 - 2 * slice_group_change_direction_flag )
          xDir = 0;
          yDir = 1 - 2 * pps->slice_group_change_direction_flag;
        } 
        else if (yDir == -1 && y == topBound) {
          topBound = max(topBound - 1, 0);
          y = topBound;
          //( xDir, yDir ) = ( 1 - 2 * slice_group_change_direction_flag, 0 )
          xDir = 1 - 2 * pps->slice_group_change_direction_flag;
          yDir = 0;
        } 
        else if (yDir == 1 && y == bottomBound) {
          bottomBound = min(bottomBound + 1, picHeightInMapUnits - 1);
          y = bottomBound;
          //( xDir, yDir ) = ( 2 * slice_group_change_direction_flag - 1, 0 )
          xDir = 2 * pps->slice_group_change_direction_flag - 1;
          yDir = 0;
        } 
        else {
          //( x, y ) = ( x + xDir, y + yDir )
          x = x + xDir;
          y = y + yDir;
        }
      }
      break;

    case PS_SLICE_GROUP_MAP_TYPE_CHANGING_4:
      /* mapUnitsInSliceGroup0 */
      mapUnitsInSliceGroup0 =	min((int)(slice->slice_group_change_cycle * (pps->slice_group_change_rate_minus1+1)), picSizeInMapUnits);

      sizeOfUpperLeftGroup = ( pps->slice_group_change_direction_flag ? 
			                        ( picSizeInMapUnits - mapUnitsInSliceGroup0 ) : mapUnitsInSliceGroup0 );

      for( i = 0; i < picSizeInMapUnits; i++ )
        if( i < sizeOfUpperLeftGroup )
          sliceMap[ i ] = pps->slice_group_change_direction_flag;
        else
          sliceMap[ i ] = 1 - pps->slice_group_change_direction_flag;
      break;

    case PS_SLICE_GROUP_MAP_TYPE_CHANGING_5:
      /* mapUnitsInSliceGroup0 */
      mapUnitsInSliceGroup0 =	min((int)(slice->slice_group_change_cycle * (pps->slice_group_change_rate_minus1+1)), picSizeInMapUnits);

      sizeOfUpperLeftGroup = ( pps->slice_group_change_direction_flag ? 
			                        ( picSizeInMapUnits - mapUnitsInSliceGroup0 ) : mapUnitsInSliceGroup0 );

      k = 0;
      for( j = 0; j < picWidthInMbs; j++ )
        for( i = 0; i < picHeightInMapUnits; i++ )
          if( k++ < sizeOfUpperLeftGroup )
            sliceMap[ i * picWidthInMbs + j ] = pps->slice_group_change_direction_flag;
          else
            sliceMap[ i * picWidthInMbs + j ] = 1 - pps->slice_group_change_direction_flag;
      break;

    case PS_SLICE_GROUP_MAP_TYPE_EXPLICIT:
      for (i = 0; i < picSizeInMapUnits; i++)
        sliceMap[i] = pps->slice_group_id[i];
      break;

    default:
      break;
    }
  }
}


/*
 *
 * isPicBoundary:
 *
 * Parameters:
 *      seq                   Sequence object
 *
 * Function:
 *      Check if current slice and next slice belong to different pictures.
 *      
 * Returns:
 *      1: slices belong to different pictures (picture boundary detected)
 *      0: slices belong to the same picture
 *
 */
static int isPicBoundary(sequence_s *seq)
{
  slice_s *currSlice, *nextSlice;
  seq_parameter_set_s *prevSps, *currSps;

  currSlice = seq->currSlice;
  nextSlice = seq->nextSlice;

  /* frame_num differs in value. */
  if (currSlice->frame_num != nextSlice->frame_num)
    return 1;

  /* nal_ref_idc differs in value with one of the nal_ref_idc values being equal to 0. */
  if ((currSlice->nalRefIdc != nextSlice->nalRefIdc) &&
      (currSlice->nalRefIdc == 0 || nextSlice->nalRefIdc == 0))
    return 1;

  /* nal_unit_type is equal to 5 for one coded slice NAL unit and */
  /* is not equal to 5 in the other coded slice NAL unit */
  if ((currSlice->nalType == NAL_TYPE_CODED_SLICE_IDR || nextSlice->nalType == NAL_TYPE_CODED_SLICE_IDR) &&
      (currSlice->nalType != nextSlice->nalType))
    return 1;

  /* nal_unit_type is equal to 5 for both and idr_pic_id differs in value. */
  if (currSlice->nalType == NAL_TYPE_CODED_SLICE_IDR &&
      nextSlice->nalType == NAL_TYPE_CODED_SLICE_IDR &&
      (currSlice->idr_pic_id != nextSlice->idr_pic_id))
    return 1;

  prevSps = seq->spsList[seq->ppsList[currSlice->pic_parameter_set_id]->seq_parameter_set_id];
  currSps = seq->spsList[seq->ppsList[nextSlice->pic_parameter_set_id]->seq_parameter_set_id];

  /* pic_order_cnt_type is equal to 0 for both and */
  /* either pic_order_cnt_lsb differs in value, or delta_pic_order_cnt_bottom differs in value. */
  if ((prevSps->pic_order_cnt_type == 0 && currSps->pic_order_cnt_type == 0) &&
    ((currSlice->pic_order_cnt_lsb != nextSlice->pic_order_cnt_lsb) ||
    (currSlice->delta_pic_order_cnt_bottom != nextSlice->delta_pic_order_cnt_bottom)))
    return 1;

  /* pic_order_cnt_type is equal to 1 for both and */
  /* either delta_pic_order_cnt[ 0 ] differs in value, or delta_pic_order_cnt[ 1 ] differs in value. */
  if ((prevSps->pic_order_cnt_type == 1 && currSps->pic_order_cnt_type == 1) &&
      ((currSlice->delta_pic_order_cnt_0 != nextSlice->delta_pic_order_cnt_0) ||
       (currSlice->delta_pic_order_cnt_1 != nextSlice->delta_pic_order_cnt_1)))
    return 1;

  /* View id differs in value. */
  if (currSlice->viewId != nextSlice->viewId)
    return 1;

#ifdef DEBUG_PRINT
  printf("Slice is pic boundary returns 0\n");
#endif

  return 0;
}


/*
 *
 * decodePictureOrderCount:
 *
 * Parameters:
 *      seq                   Sequence object
 *      slice                 Slice object
 *      sps                   Sequence parameter set
 *
 * Function:
 *      Decode picture order count using syntax elements in slice object.
 *      
 * Returns:
 *      poc
 *
 */
static int decodePictureOrderCount(sequence_s* seq, slice_s *slice,
                                   seq_parameter_set_s *sps)
{
  int i;
  int32 maxPocLsb;
  int32 expectedPicOrderCnt, picOrderCntCycleCnt = 0;
  int32 expectedDeltaPerPicOrderCntCycle, frameNumInPicOrderCntCycle = 0, absFrameNum;
  int32 tempPicOrderCnt;
  int32 poc = 0;

  /* POC */
  if (sps->pic_order_cnt_type == 0) {
    /* Reset prevPocMsb, prevPocLsb if needed */
    if (slice->isIDR) {
      seq->prevPocMsb = seq->prevPocLsb = 0;
    }
    else if (seq->prevPicHasMMCO5) {
      seq->prevPocMsb = 0;
      seq->prevPocLsb = seq->prevRefPicPoc;
    }

    /* PicOrderCntMsb is derived: */
    maxPocLsb = (u_int32)1 << (sps->log2_max_pic_order_cnt_lsb_minus4 + 4);
    if ( (int32)slice->pic_order_cnt_lsb < seq->prevPocLsb &&  (seq->prevPocLsb - (int32)slice->pic_order_cnt_lsb ) >= (maxPocLsb / 2) )
      seq->pocMsb = seq->prevPocMsb + maxPocLsb;
    else if ( (int32)slice->pic_order_cnt_lsb > seq->prevPocLsb && ((int32)slice->pic_order_cnt_lsb - seq->prevPocLsb) > (maxPocLsb / 2) )
      seq->pocMsb = seq->prevPocMsb - maxPocLsb;
    else
      seq->pocMsb = seq->prevPocMsb;
    /* poc */
    poc = seq->pocMsb + slice->pic_order_cnt_lsb;
  }

  else if (sps->pic_order_cnt_type == 1) {
    /* Reset prevFrameNumOffset if needed */
    if (!slice->isIDR && seq->prevPicHasMMCO5)  /* Todo: prevPicHasMMCO5 has not been tested. */
      seq->prevFrameNumOffset = 0;

    /* frameNumOffset is derived as follows: */
    if (slice->isIDR)
      seq->frameNumOffset = 0;
    else if (seq->prevFrameNum > (int32)slice->frame_num)
      seq->frameNumOffset = seq->prevFrameNumOffset + slice->maxFrameNum;
    else
      seq->frameNumOffset = seq->prevFrameNumOffset;

    /* absFrameNum is derived as follows: */
    if (sps->num_ref_frames_in_pic_order_cnt_cycle != 0)
      absFrameNum = seq->frameNumOffset + slice->frame_num;
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
    }
    else
      expectedPicOrderCnt = 0;
    if (slice->nalRefIdc == 0)
      expectedPicOrderCnt = expectedPicOrderCnt + sps->offset_for_non_ref_pic;

    /* poc */
    poc = expectedPicOrderCnt + slice->delta_pic_order_cnt_0;
  }

  else if (sps->pic_order_cnt_type == 2) {
    /* prevFrameNumOffset is derived as follows */
    if (!slice->isIDR && seq->prevPicHasMMCO5)
      seq->prevFrameNumOffset = 0;

    /* FrameNumOffset is derived as follows. */
    if (slice->isIDR)
      seq->frameNumOffset = 0;
    else if (seq->prevFrameNum > (int32)slice->frame_num)
      seq->frameNumOffset = seq->prevFrameNumOffset + slice->maxFrameNum;
    else
      seq->frameNumOffset = seq->prevFrameNumOffset;

    /* tempPicOrderCnt is derived as follows */
    if (slice->isIDR)
      tempPicOrderCnt = 0;
    else if (slice->nalRefIdc == 0)
      tempPicOrderCnt = 2 * (seq->frameNumOffset + slice->frame_num) - 1;
    else
      tempPicOrderCnt = 2 * (seq->frameNumOffset + slice->frame_num);

    /* poc */
    poc = tempPicOrderCnt;
  }

  return poc;
}


/*
 *
 * getOutputPic:
 *
 * Parameters:
 *      seq                   Sequence object
 *
 * Function:
 *      Get one output picture. Pictures are output from output queue and
 *      if queue is empty pictures are ouput from dpb. Ouput from dpb can only
 *      happen if sequence is finished (i.e there are not more bits to decode).
 *
 * Returns:
 *      1: output picture is available
 *      0: output picture is not available
 */
static int getOutputPic(sequence_s *seq, avcdYUVbuffer_s *outBuf, char *outputInt)
{
  frmBuf_s *srcBuf;
  char writeOutYUV = seq->writeYUV;
#ifdef DEBUG_PRINT
  double tempTime, tempTime2;
#endif


  /* If no slices have been decoded, there are no pictures available */
  if (seq->isFirstSliceOfSeq)
    return 0;

  /* Check if there are pictures in output queue */
  if (seq->numQueuedOutputPics > 0) {

    /* Take next picture from queue. */
    srcBuf = seq->outputQueue[seq->outputQueuePos];

    seq->numQueuedOutputPics--;
    if (seq->numQueuedOutputPics == 0)
      seq->outputQueuePos = 0;
    else
      seq->outputQueuePos++;
  }
  else {

    /*
     * There are no queued pictures, but we can still output a picture if DPB
     * has picture(s) and at least one of the following conditions is true:
     * - we have decoded all NAL units of the sequence
     * - num_reorder_frames in VUI parameters is zero
     * - POC type is 2
     * - there exists IDR or MMCO5 picture after next output picture in
     *   decoding order in DPB
     */

    int dpbHasIDRorMMCO5;

    srcBuf = dpbGetNextOutputPic(seq->dpb, &dpbHasIDRorMMCO5, seq->currSlice->viewId);
    if (!(srcBuf &&
          (seq->isSeqFinished ||
           srcBuf->numReorderFrames == 0 ||
           srcBuf->pocType == 2 ||
           dpbHasIDRorMMCO5)))
    {
      return 0;   /* Cannot output picture */
    }
  }

  outBuf->y                   = srcBuf->y;
  outBuf->u                   = srcBuf->u;
  outBuf->v                   = srcBuf->v;

  outBuf->constraintSet0flag  = srcBuf->constraintSet0flag;
  outBuf->constraintSet1flag  = srcBuf->constraintSet1flag;
  outBuf->constraintSet2flag  = srcBuf->constraintSet2flag;
  outBuf->profile             = srcBuf->profile;
  outBuf->level               = srcBuf->level;
  outBuf->width               = srcBuf->width;
  outBuf->height              = srcBuf->height;
  outBuf->cropBottomOff       = srcBuf->cropBottomOff;
  outBuf->cropLeftOff         = srcBuf->cropLeftOff;
  outBuf->cropRightOff        = srcBuf->cropRightOff;
  outBuf->cropTopOff          = srcBuf->cropTopOff;
  outBuf->aspectRatioNum      = srcBuf->aspectRatioNum;
  outBuf->aspectRatioDenom    = srcBuf->aspectRatioDenom;
  outBuf->overscanInfo        = srcBuf->overscanInfo;
  outBuf->videoFormat         = srcBuf->videoFormat;
  outBuf->videoFullRangeFlag  = srcBuf->videoFullRangeFlag;
  outBuf->matrixCoefficients  = srcBuf->matrixCoefficients;
  outBuf->chromaSampleLocType = srcBuf->chromaSampleLocType;
  outBuf->numReorderFrames    = srcBuf->numReorderFrames;
  outBuf->frameRate           = srcBuf->frameRate;
  outBuf->imgPadding          = srcBuf->imgPadding;
  outBuf->frameQp             = srcBuf->qp;

  if (IS_SLICE_I(srcBuf->picType))
    outBuf->picType      = AVCD_PICTURE_TYPE_I;
  else
    outBuf->picType      = AVCD_PICTURE_TYPE_P;

  if (srcBuf->refType == FRM_LONG_TERM_PIC) {
    outBuf->longTermReference = 1;
    outBuf->longTermFrmIdx    = srcBuf->longTermFrmIdx;
  }
  else {
    outBuf->longTermReference = 0;
  }

  outBuf->frameNum           = srcBuf->frameNum;
  outBuf->maxFrameNum        = srcBuf->maxFrameNum;
  outBuf->poc                = srcBuf->poc;
  outBuf->isIDR              = srcBuf->isIDR;
  outBuf->idrCnt             = srcBuf->idrPicID;
  outBuf->pictureStructure   = srcBuf->pictureStructure;
  outBuf->lossy              = srcBuf->lossy;
  outBuf->numDecodedBits     = 0;

#if defined(ERROR_CONCEALMENT) && defined(BACKCHANNEL_INFO)
  outBuf->mbLossMap          = srcBuf->mbLossMap;
#endif

  outBuf->numPrevPicsLost    = srcBuf->numPrevPicsLost;
  outBuf->timingInfo         = srcBuf->timingInfo;

  /* Make conversion from YUV to RGB and store converted to display buffer */
  if(srcBuf->viewId == 0)
  {
#ifdef DEBUG_PRINT
    tempTime = (double)clock()/CLOCKS_PER_SEC;
#endif

    StoreYUV(srcBuf, seq->displayBuffer);

#ifdef DEBUG_PRINT
    tempTime2 = ((double)clock()/CLOCKS_PER_SEC) - tempTime;
    seq->interlaceTime += tempTime2;
#endif
    
    /* Write out separate YUV files for left and right eye view, if required */
    if (writeOutYUV)
      writeYUVOut(seq, srcBuf, 0);

  }
  else {

    /* Write out separate YUV files for left and right eye view, if required */
    if (writeOutYUV)
      writeYUVOut(seq, srcBuf, 1);

#ifdef DEBUG_PRINT
    printf("View id %d, view output\n", srcBuf->viewId);
    tempTime = (double)clock()/CLOCKS_PER_SEC;
#endif

    interleaveParallax(seq, (unsigned char*) (outputInt), srcBuf);

#ifdef DEBUG_PRINT
    tempTime2 = ((double)clock()/CLOCKS_PER_SEC) - tempTime;
    seq->interlaceTime += tempTime2;
#endif
    
    seq->outputFrameIdx++;

#ifdef DEBUG_PRINT
    printf("Number of output frames %d\n",seq->outputFrameIdx);
#endif
    
    srcBuf->forOutput = 0;
    
    /* Picture ready to be drawn */
    return(1);
  }
  
  srcBuf->forOutput = 0;

  return 0;
}


/*
 *
 * finishCurrentPic:
 *
 * Parameters:
 *      seq                   Sequence object
 *
 * Function:
 *      Finish decoding of current picture. Call loopfilter for the picture
 *      and try to store picture in dpb. Function also updates variables
 *      for previous decoded frame and previous decoded reference frame.
 *
 * Returns:
 *       0 : no frames were output
 *      >0 : the number of frames output
 *      <0 : error
 */
static int finishCurrentPic(sequence_s *seq)
{
  slice_s *slice;
  frmBuf_s *currPic;
  int numOutput;
  int retVal;
#ifdef DEBUG_PRINT
  double tempTime;
#endif


  slice   = seq->currSlice;
  currPic = seq->recoBuf;
  
#ifdef DEBUG_PRINT
  tempTime = (double)clock()/CLOCKS_PER_SEC;
#endif
  
  if (!currPic->nonExisting) {
    filFilterFrame(currPic, seq->mbData, currPic->width,
      currPic->height, currPic->chromaQpIndexOffset);
    
#if defined(ERROR_CONCEALMENT) && defined(BACKCHANNEL_INFO)
    {
      int i;
      for (i = 0; i < (currPic->width>>MBK_SIZE_LOG2)*(currPic->height>>MBK_SIZE_LOG2); i++)
        currPic->mbLossMap[i] = (unsigned char)(seq->errConcealment->decodedMbs[0][i] & 1);
    }
#endif
  }
  
#ifdef DEBUG_PRINT
  seq->filterTime += ((double)clock()/CLOCKS_PER_SEC) - tempTime;
#endif  
  
  if ((retVal = decRefPicMarking(seq)) < 0)
    return retVal;
  
  /* After the decoding of the current picture and the processing of the     */
  /* memory management control operations a picture including                */
  /* a memory_management_control_operation equal to 5 shall be inferred      */
  /* to have had frame_num equal to 0 for all subsequent use in the decoding */
  /* process.                                                                */
  if (slice->picHasMMCO5)
    currPic->frameNum = slice->frame_num = 0;
  
  if (slice->nalRefIdc != 0) {
    seq->prevRefPicPoc   = currPic->poc;
  }
  
  /* This action is not defined in the H.264/AVC standard, but reference SW does it */
  if (currPic->hasMMCO5)
    currPic->poc = 0;
  
  /* Try to store current picture to dpb */
  numOutput = dpbStorePicture(seq->dpb, currPic, seq->outputQueue);
  /* If numOutput != 0, picture was not stored */
  
  if (numOutput != 0) {
    
    /* numOutput != 0 implies that pictures were output from dpb */
    seq->outputQueuePos      = 0;
    seq->numQueuedOutputPics = numOutput;
    
    /* Picture was not stored so we have to store it later */
    seq->isDpbStorePending   = 1;
  }
  else
    seq->isDpbStorePending = 0;
  
  seq->prevFrameNum       = slice->frame_num;
  seq->prevFrameNumOffset = seq->frameNumOffset;
  seq->prevPicHasMMCO5 = slice->picHasMMCO5;
  
  /* prevRefFrameNum, prevPocLsb and prevPocMsb for latest reference picture */
  if (slice->nalRefIdc != 0) {
    seq->prevRefFrameNum = slice->frame_num;
    seq->prevPocLsb      = slice->pic_order_cnt_lsb;
    seq->prevPocMsb      = seq->pocMsb;
  }
  
  seq->isCurrPicFinished = 1;
  
  return numOutput;
}


#ifdef ERROR_CONCEALMENT
/*
 *
 * concealAndFinishCurrentPic:
 *
 * Parameters:
 *      seq                   Sequence object
 *
 * Function:
 *      Conceal current picture and finish decoding it.
 *
 * Returns:
 *       0 : no frames were output
 *      >0 : the number of frames output
 *      <0 : error
 */
static int concealAndFinishCurrentPic(sequence_s *seq)
{
  pic_parameter_set_s *pps;
  int numOutput;

#ifdef REDUNDANT_PIC_CONCEALMENT
  if (seq->redundantPicConcealmentCnt > 0) {

    /* Combine the latest redundant picture with the primary picture. */
    ercCombinePictures(seq->errConcealment_PP, seq->errConcealment_RP,
                       seq->recoBuf_PP, seq->recoBuf_RP,
                       seq->mbData_PP, seq->mbData_RP,
                       seq->redundantPicConcealmentCnt);

    /* Make primary picture "active picture" */
    seq->recoBuf        = seq->recoBuf_PP;
    seq->mbData         = seq->mbData_PP;
    seq->errConcealment = seq->errConcealment_PP;

    seq->redundantPicConcealmentCnt = 0;
  }
#endif

  pps = seq->ppsList[seq->currSlice->pic_parameter_set_id];

  ercCheckAndConceal(seq->errConcealment, seq->recoBuf, seq->mbData, seq->dpb, pps);

  /* Finish decoding of current picture */
  numOutput = finishCurrentPic(seq);

  return numOutput;
}
#endif


/*
 *
 * generateNonExistingFrames:
 *
 * Parameters:
 *      seq                   Sequence object
 *
 * Function:
 *      Generate non-existing frame for each unused frame number between
 *      two closest existing frames in decoding order. Generated frames
 *      are stored to dpb in finishCurrentPic function.
 *
 * Returns:
 *       0 : no frames were output
 *      >0 : the number of frames output
 *      <0 : error
 */
static int generateNonExistingFrames(sequence_s *seq)
{
  slice_s *slice;
  frmBuf_s *currPic;
  int32 nextFrameNum;
  int numOutput;

  slice   = seq->currSlice;
  currPic = seq->recoBuf;

  slice->picHasMMCO5                        = 0;
  slice->isIDR                              = 0;
  slice->adaptive_ref_pic_marking_mode_flag = 0;
  slice->nalType                            = NAL_TYPE_CODED_SLICE;
  slice->nalRefIdc                          = 1;

  currPic->forOutput   = 0;
  currPic->nonExisting = 1;

  do {
    slice->frame_num = seq->unusedShortTermFrameNum;

    dpbUpdatePicNums(seq->dpb, slice->frame_num, slice->maxFrameNum, slice->viewId);

    numOutput = finishCurrentPic(seq);

    nextFrameNum = (seq->unusedShortTermFrameNum + 1) % seq->nextSlice->maxFrameNum;

    if (nextFrameNum == (int)seq->nextSlice->frame_num)
      seq->unusedShortTermFrameNum = -1;
    else
      seq->unusedShortTermFrameNum = nextFrameNum;

  } while (numOutput == 0 && seq->unusedShortTermFrameNum >= 0);

  return numOutput;
}


/*
 *
 * initializeCurrentPicture:
 *
 * Parameters:
 *      seq                   Sequence object
 *      sps                   Active sequence parameter set
 *      pps                   Active picture parameter set
 *      width                 Picture width
 *      height                Picture height
 *
 * Function:
 *      Current frame and dpb are initialized according to active
 *      parameter sets.
 *
 * Returns:
 *      SEQ_OK for no error, negative value for error
 */
static int initializeCurrentPicture(sequence_s *seq, seq_parameter_set_s *sps,
                                    pic_parameter_set_s *pps,
                                    int width, int height)

{
  frmBuf_s *currPic;
  slice_s *slice;
  int i;

#ifdef CHECK_MV_RANGE
  if (sps->level_idc <= 10)
    maxVerticalMvRange = 64;
  else if (sps->level_idc <= 20)
    maxVerticalMvRange = 128;
  else if (sps->level_idc <= 30)
    maxVerticalMvRange = 256;
  else
    maxVerticalMvRange = 512;
#endif

  currPic = seq->recoBuf;
  slice   = seq->currSlice;

  /*
   * (Re)initialize frame buffer for current picture if picture size has changed
   */
  if (!currPic || width != currPic->width || height != currPic->height) {

    frmClose(currPic, seq->mbData);
    if ((currPic = frmOpen(&seq->mbData, width, height)) == NULL)
      return SEQ_ERR_MEM;

    seq->recoBuf = currPic;

#ifdef ERROR_CONCEALMENT
    /* (Re)initialize the error concealment procedure if picture size has changed */
    ercClose(seq->errConcealment);
    if ((seq->errConcealment = ercOpen(width/MBK_SIZE, height/MBK_SIZE)) == NULL)
      return SEQ_ERR_MEM;
#endif

#ifdef REDUNDANT_PIC_CONCEALMENT
    if (seq->redundantPicConcealmentCnt > 0) {
      /* redundant picture state */
      seq->recoBuf_RP = currPic;
      seq->mbData_RP  = seq->mbData;
      seq->errConcealment_RP = seq->errConcealment;
    }
    else {
      /* primary picture state */
      seq->recoBuf_PP = currPic;
      seq->mbData_PP  = seq->mbData;
      seq->errConcealment_PP = seq->errConcealment;
    }
#endif
  }

  for (i = 0; i < MAX_SLICE_GROUP_NUM; i++)
    seq->sliceNums[i] = 0;

  /* Build slice group map */
  buildSliceGroups(seq, slice, sps, pps);

  /* Parameter from SPS */
  currPic->constraintSet0flag = sps->constraint_set0_flag;
  currPic->constraintSet1flag = sps->constraint_set1_flag;
  currPic->constraintSet2flag = sps->constraint_set2_flag;
  currPic->profile            = sps->profile_idc;
  currPic->level              = sps->level_idc;
  currPic->maxFrameNum        = slice->maxFrameNum; /* Derived from sps->log2_max_frame_num_minus4 */
  currPic->pocType            = sps->pic_order_cnt_type;

  /* Parameter from PPS */
  currPic->qp = pps->pic_init_qp_minus26 + 26;

  /* By default picture will be output */
  currPic->forOutput   = 1;
  currPic->nonExisting = 0;
  currPic->picType     = slice->slice_type;
  currPic->isIDR       = slice->isIDR;
  currPic->viewId = slice->viewId;

  psGetAspectRatio(sps, &currPic->aspectRatioNum, &currPic->aspectRatioDenom);
  currPic->overscanInfo        = sps->vui_parameters.overscan_appropriate_flag;
  currPic->videoFormat         = sps->vui_parameters.video_format;
  currPic->videoFullRangeFlag  = sps->vui_parameters.video_full_range_flag;
  currPic->matrixCoefficients  = sps->vui_parameters.matrix_coefficients;
  currPic->chromaSampleLocType = sps->vui_parameters.chroma_sample_loc_type_top_field;
  currPic->numReorderFrames    = sps->vui_parameters.num_reorder_frames;

  if (sps->frame_cropping_flag) {
    currPic->cropLeftOff   = sps->frame_crop_left_offset;
    currPic->cropRightOff  = sps->frame_crop_right_offset;
    currPic->cropTopOff    = sps->frame_crop_top_offset;
    currPic->cropBottomOff = sps->frame_crop_bottom_offset;
  }
  else {
    currPic->cropLeftOff   = 0;
    currPic->cropRightOff  = 0;
    currPic->cropTopOff    = 0;
    currPic->cropBottomOff = 0;
  }

  if (sps->vui_parameters_present_flag &&
      sps->vui_parameters.timing_info_present_flag &&
      sps->vui_parameters.num_units_in_tick != 0)
    currPic->frameRate = (float)(0.5 * (float)sps->vui_parameters.time_scale/(float)sps->vui_parameters.num_units_in_tick);
  else
    currPic->frameRate = 0.0;

  /* Get poc for current picture */
  currPic->poc = decodePictureOrderCount(seq, slice, sps);

  /* Set chroma qp index offset */
  currPic->chromaQpIndexOffset = pps->chroma_qp_index_offset;

  currPic->pictureStructure = 0;

#ifdef ERROR_CONCEALMENT
  /* By default, this is not a scene cut picture */
  currPic->sceneCut = 0;
#endif

  currPic->lossy = 0;
  currPic->numPrevPicsLost = seq->numPrevPicsLost;

  currPic->timingInfo = seq->timingInfo;

  seq->isCurrPicFinished = 0;
  seq->redundantPicCnt = slice->redundant_pic_cnt;

  return SEQ_OK;
}


#ifdef ERROR_CONCEALMENT

/*
 *
 * setSceneCutFlag:
 *
 * Parameters:
 *      seq                   Sequence object
 *
 * Function:
 *      Tell if current picture is a scene cut picture or not.
 *
 * Returns:
 *      -
 */
static void setSceneCutFlag(sequence_s *seq)
{
  seq->errConcealment->hasSceneInfo = seq->hasSceneInfo;

  /* Scene info messages are available, and there is newly decoded scene info SEI */
  if (seq->hasSceneInfo && seq->sceneInfoDecoded) {

    seq->sceneInfoDecoded = 0;
    if (seq->prevSceneInfo->sceneId != seq->currSceneInfo->sceneId ||
        seq->prevSceneInfo->sceneTransitionType != seq->currSceneInfo->sceneTransitionType )
      seq->recoBuf->sceneCut = 1;
  }
}

#endif


/*
 *
 * decodeSliceData:
 *
 * Parameters:
 *      seq                   Sequence object
 *
 * Function:
 *      Decode slice data of the current slice. Before decoding slice data,
 *      current frame and dpb are initialized according to active
 *      parameter sets.
 *
 * Returns:
 *      SEQ_OK for no error, negative value for error
 */
static int decodeSliceData(sequence_s *seq)
{
  slice_s *slice;
  pic_parameter_set_s *pps;
  seq_parameter_set_s *sps;
  int width, height;
  int sliceGroupNum, sliceID;
  int retCode;

  /* New slice becomes current slice */
  slice = seq->nextSlice;
  seq->nextSlice = seq->currSlice;
  seq->currSlice = slice;

  /* Get current parameter sets */
  pps = seq->ppsList[slice->pic_parameter_set_id];
  sps = seq->spsList[pps->seq_parameter_set_id];

  /* Get picture size */
  width  = (sps->pic_width_in_mbs_minus1+1)*16;
  height = (sps->pic_height_in_map_units_minus1+1)*16;
  
  /* If this is the first slice of a picture, initialize picture */
  if (seq->isFirstSliceOfSeq || seq->isPicBoundary) {
    
    retCode = initializeCurrentPicture(seq, sps, pps, width, height);
    
    if(seq->isFirstSliceOfSeq)
    {
      seq->displayBuffer = initDisplayBuffer(width, height);
      
      if (seq->writeYUV)
        openOutputFiles(seq);
    }
    
    if (retCode < 0)
      return retCode;
    
    if (slice->isIDR || seq->isFirstSliceOfSeq) {
      
      /* Set dpb according to level */
      dpbSetSize(seq->dpb, sps->vui_parameters.max_dec_frame_buffering);

      seq->recoBuf->picID = 0;
      
      seq->dpb->maxNumRefFrames = sps->num_ref_frames;
    }
    
#ifdef ERROR_CONCEALMENT
    /* Reset error concealment */
    ercClear(seq->errConcealment);
    
    /* Set the scene cut flag if scene info SEIs are available */
    setSceneCutFlag(seq);
    if (seq->isFirstSliceOfSeq)
      seq->errConcealment->isFirstPicOfSeq = 1;
    else
      seq->errConcealment->isFirstPicOfSeq = 0;
#endif
  }
  else {
    if (IS_SLICE_P(slice->slice_type))
      /* If there is a P-slice in the picture, mark picture as P-picture */
      seq->recoBuf->picType = slice->slice_type;
  }
  
  /* Compute picture numbers for all reference frames */
  if (!slice->isIDR)
    dpbUpdatePicNums(seq->dpb, slice->frame_num, slice->maxFrameNum, slice->viewId);
  
  /* Get slice group number if there are more than 1 slice groups */
  if (pps->num_slice_groups_minus1 == 0)
    sliceGroupNum = 0;
  else
    sliceGroupNum = seq->mbData->sliceMap[slice->first_mb_in_slice] & 0xF;
  
  /* Increment slice number for current slice group (slice numbers start from 1) */
  seq->sliceNums[sliceGroupNum]++;
  
  /* sliceID for current slice */
  sliceID       = seq->sliceNums[sliceGroupNum]*16 | sliceGroupNum;
  
  /*
   * Go decode slice data
   */
  retCode = sliceDecodeMacroblocks(slice, seq->recoBuf, seq->dpb,
#ifdef ERROR_CONCEALMENT
                                   seq->errConcealment,
#endif
                                   sps, pps, seq->mbData, sliceID, seq->bitbuf);

#ifdef DEBUG_PRINT
  seq->intraTime += slice->intraTime;
  seq->vldTime += slice->vldTime;
  seq->interTime += slice->interTime;
  seq->codingTime += slice->codingTime;

  printf("Times (cumulative) %3.2f %3.2f %3.2f %3.2f %3.2f secs\n", seq->intraTime, seq->interTime, seq->vldTime, seq->codingTime, seq->filterTime);
  printf("Interlacing (cumulative) %3.3f seconds\n", seq->interlaceTime);
#endif

  /* Update sequence variables */
  seq->isFirstSliceOfSeq        = 0;
  seq->isPicBoundary            = 0;

#ifdef ERROR_CONCEALMENT
  if (seq->errConcealment->numDecodedMbs >= seq->errConcealment->numMbs) {
#ifdef REDUNDANT_PIC_CONCEALMENT
    concealAndFinishCurrentPic(seq);
#else
    finishCurrentPic(seq);
#endif
  }
#endif

  if (retCode < 0)
    return SEQ_ERROR;
  else
    return SEQ_OK;
}


#ifdef ERROR_CONCEALMENT

/*
 *
 * concealFrames:
 *
 * Parameters:
 *      seq                   Sequence object
 *
 * Function:
 *      Try to recover an entirely lost picture. Compared to partly
 *      corrupted picture, additional tasks have to be done to set
 *      proper flags for the lost pictures.
 *
 * Returns:
 *       0 : no frames were output
 *      >0 : the number of frames output
 *      <0 : error
 *
 */
static int concealFrames(sequence_s *seq)
{
  slice_s *slice;
  frmBuf_s *currPic;
  int nextFrameNum;
  int numOutput;
  pic_parameter_set_s *pps;

  ercClear(seq->errConcealment);

  slice   = seq->currSlice;
  currPic = seq->recoBuf;

  slice->picHasMMCO5                        = 0;
  slice->isIDR                              = 0;
  slice->adaptive_ref_pic_marking_mode_flag = 0;
  slice->nalType                            = NAL_TYPE_CODED_SLICE;
  slice->nalRefIdc                          = 1;

  /* 
   * Set the currPic->forOutput to 0 for the time being. The wholly lost pictures will not 
   * be outputted by the video decoder.
   */
  pps = seq->ppsList[slice->pic_parameter_set_id];

  do {
    slice->frame_num = seq->unusedShortTermFrameNum;

    printf("Concealing frame num: %d\n", slice->frame_num);

#ifdef OUTPUT_LOST_PICS
    currPic->forOutput   = 1;
#else
    currPic->forOutput   = 0;
#endif
    currPic->nonExisting = 1;

    dpbUpdatePicNums(seq->dpb, slice->frame_num, slice->maxFrameNum, slice->viewId);

    ercConcealWholePic(seq->recoBuf, seq->mbData, seq->dpb);

    numOutput = finishCurrentPic(seq);

    nextFrameNum = (seq->unusedShortTermFrameNum + 1) % seq->nextSlice->maxFrameNum;

    if (nextFrameNum == (int)seq->nextSlice->frame_num)
      seq->unusedShortTermFrameNum = -1;
    else
      seq->unusedShortTermFrameNum = nextFrameNum;

    seq->numPrevPicsLost++;

  } while (numOutput == 0 && seq->unusedShortTermFrameNum >= 0);

  return numOutput;
}

#endif


/*
 *
 * decodeSlice:
 *
 * Parameters:
 *      seq                   Sequence object
 *      nalType               Type of nal unit
 *      nalRefIdc             Nal unit reference indicator
 *
 * Function:
 *      Start decoding slice. Decode slice header and also
 *      decode slice data if picture boundary is not detected. If 
 *      picture boundary is detected, current picture is finished and an
 *      attempt is made to store it in the dpb. Possible gap
 *      in frame numbers is detected and handled (by generating
 *      non-existing frames).
 *
 * Returns:
 *      SEQ_OK for ok, negative value for error
 */
static int decodeSlice(sequence_s *seq, int nalType, int nalRefIdc)
{
  slice_s *slice;
  int32 nextFrameNum;
  int numOutput;
  int retCode;


  slice = seq->nextSlice;
  slice->nalType   = nalType;
  slice->nalRefIdc = nalRefIdc;
  slice->isIDR     = (nalType == NAL_TYPE_CODED_SLICE_IDR);

  retCode = sliceGetHeader(slice, seq->spsList, seq->ppsList,
                           seq->bitbuf);

  if (retCode < 0)
    return SEQ_ERROR;

  /* Check if next slice belongs to next picture */
  if (seq->isFirstSliceOfSeq)
    seq->isPicBoundary = 0;
  else
    seq->isPicBoundary = isPicBoundary(seq);

  if (!seq->isPicBoundary) {
    /* There is no picture boundary. Decode new slice if redundant */
    /* picture count is same as in previous slice                  */
    if (seq->isFirstSliceOfSeq || slice->redundant_pic_cnt == seq->redundantPicCnt)
      return decodeSliceData(seq);
    else {
#ifdef REDUNDANT_PIC_CONCEALMENT
      /* If we see a new redundant picture while current picture  */
      /* is not finished, we know that current picture has losses */
      /* and we will use redundant picture for concealment.       */
      if (slice->redundant_pic_cnt != seq->redundantPicCnt &&
          !seq->isCurrPicFinished)
      {
        if (seq->redundantPicConcealmentCnt > 0)
          /* There are more than one redudant pictures in current access */
          /* unit, combine the latest decoded redundant picture with the */
          /* primary picture before proceeding to decode the new         */
          /* redundant picture.                                          */
          ercCombinePictures(seq->errConcealment_PP, seq->errConcealment_RP,
                             seq->recoBuf_PP, seq->recoBuf_RP,
                             seq->mbData_PP, seq->mbData_RP,
                             seq->redundantPicConcealmentCnt);

        /* Make redundant picture "active" */
        seq->recoBuf        = seq->recoBuf_RP;
        seq->mbData         = seq->mbData_RP;
        seq->errConcealment = seq->errConcealment_RP;

        seq->redundantPicConcealmentCnt++;
        seq->isPicBoundary = 1; /* Start new picture */

        /* Decode data of the first slice of the redundant picture */
        return decodeSliceData(seq);
      }
      else
#endif
        return SEQ_OK;
    }
  }
  else {
    /* Picture boundary reached or all MBs of current picture were decoded. */

    if (!seq->isCurrPicFinished) {
      /* Finish decoding of current picture */
#ifdef ERROR_CONCEALMENT
      numOutput = concealAndFinishCurrentPic(seq);
#else
      numOutput = finishCurrentPic(seq);
#endif
      /* numOutput is the number of pictures in output queue */

      /* If numOutput < 0, error occured */
      if (numOutput < 0)
        return numOutput;
    }
    else
      numOutput = 0;

    seq->numPrevPicsLost = 0;

    /* Compute expected next frame number */
    nextFrameNum = (seq->prevRefFrameNum + 1) % slice->maxFrameNum;

    /* Check if there is a gap in frame numbers */
    if (!slice->isIDR &&
        (int)slice->frame_num != seq->prevRefFrameNum &&
        (int)slice->frame_num != nextFrameNum)
    {
#ifdef ERROR_CONCEALMENT
      /* Check if gaps in frame numbers are allowed */
      if (!seq->spsList[seq->ppsList[slice->pic_parameter_set_id]->seq_parameter_set_id]->gaps_in_frame_num_value_allowed_flag)
      {
        /* Start concealing the lost pictures */
#ifdef DEBUG_PRINT
        printf("Lost before frame num: %d\n", slice->frame_num);
#endif

        seq->unusedShortTermFrameNum = nextFrameNum;
        seq->conceal                 = 1;

        /* If dpb was not full we can recover lost frames */
        if (numOutput == 0) 
          numOutput = concealFrames(seq);
      }
      else
#endif
      {
        /* Start filling in gaps in frame numbers */

        seq->unusedShortTermFrameNum = nextFrameNum;
#ifdef ERROR_CONCEALMENT
        seq->conceal                 = 0;
#endif
        /* If dpb was not full (i.e. we did not have to output any pictures), */
        /* we can generate non-existing frames.                               */
        if (numOutput == 0) 
          numOutput = generateNonExistingFrames(seq);
      }
    }

    if (numOutput == 0)
      /* If there are no pictures in output queue we can decode next slice */
      return decodeSliceData(seq);
    else {
      /* Don't decode slice since it belongs to next picture */
      return SEQ_OK;
    }
  }
}


#ifdef ERROR_CONCEALMENT

/*
 *
 * decodeSei:
 *
 * Parameters:
 *      seq                   Sequence object
 *
 * Function:
 *      Decode SEI message
 *
 * Returns:
 *      SEQ_OK for ok, negative value for error
 */
static int decodeSei(sequence_s *seq)
{
  int payloadType;
  int payloadSize;
  int byte;
  int retCode;
  bitbuffer_s *bitbuf;
  sceneInfo_s *scene;

  bitbuf = seq->bitbuf;

  while (bibMoreRbspData(bitbuf)) {
    payloadType = 0;
    bibGetByte(bitbuf, &byte);
    while (byte == 0xff) {
      payloadType += byte;
      bibGetByte(bitbuf, &byte);
    }
    payloadType += byte;

    payloadSize = 0;
    bibGetByte(bitbuf, &byte);
    while (byte == 0xff) {
      payloadSize += byte;
      bibGetByte(bitbuf, &byte);
    }
    payloadSize += byte;

    switch (payloadType) {
    case SEI_TYPE_SCENE_INFO:

      seq->hasSceneInfo = 1;
      scene = seq->currSceneInfo;
      seq->currSceneInfo = seq->prevSceneInfo;
      seq->prevSceneInfo = scene;

      if ((retCode = seiSceneInfo(seq->currSceneInfo, bitbuf)) < 0) 
        return retCode;
      seq->sceneInfoDecoded = 1;
      break;

    default:
      printf("The decoder does not support the SEI message in type of %d\n", payloadType);
      bitbuf->bytePos += payloadSize;   // skip the content of the SEI payload.
      break;
    }
  }

  return SEQ_OK;
}

#endif


/*
 *
 * avcdDecodeOneNal:
 *
 * Parameters:
 *      dec                     Sequence object
 *      nalUnitBits             Bits for NAL unit to be decoded
 *      nalUnitLen              Number of bytes in NAL unit
 *      outBuf                  Possibly outputted frame
 *      timingInfo              Time stamps
 *
 * Function:
 *      Return output picture immediately if available. Otherwise finish any
 *      pending tasks from previous call such as storing of current frame to
 *      dpb, generation of non-existing frames (to fill in gaps in frame
 *      numbers) and decoding of current slice data. If any of the tasks
 *      did not cause this function to return, start decoding NAL unit.
 *
 * Returns:
 *      AVCD_OK:                     Nal unit decoded and frame available
 *      AVCD_OK_FRAME_NOT_AVAILABLE: Nal unit decoded, frame not available
 *      AVCD_OK_STREAM_NOT_DECODED:  Nal unit not decoded, frame available
 *      AVCD_ERROR:                  Error occured
 *
 */
int avcdDecodeOneNal(avcdDecoder_t *dec, void *nalUnitBits, int nalUnitLen,
                     avcdYUVbuffer_s *outBuf, avcdTimingInfo_s *timingInfo, 
                     char *outputInt, char writeOutYUV)
{
  sequence_s *seq = (sequence_s *)dec;
  int nalHeaderByte;
  int nalType;
  int nalRefIdc;
  int ret;
#ifdef DEBUG_PRINT
  double tempTime;
#endif
  int i;
  int spsFound = 0;


  /*
   * The following conditions are tested to see what is the current decoder state
   * and to act upon that state:
   *
   * - Check if picture can be output from output queue without further decoding.
   * - Check if dpb store is pending (i.e current picture was not be
   *   stored to dpb during previous call because dpb was full).
   * - Check any non-existing frames should be generated (i.e there were gaps in
   *   frame number). If non-existing frame(s) were generated, check output
   *   queue again.
   * - Check for end of stream. If end of stream was reached then current picture
   *   is finished if not yet finished. Check again whether picture can be output
   *   from either output queue or dpb (check is internal to getOutputPic(...)).
   * - Check if slice decode is pending (i.e only header of the latest slice was
   *   decoded during previous call and we now need to decode slice data) and if
   *   so, decode slice data.
   * - Check any lost frames being recovered (i.e there were ref frames lost)
   *   If lost frames were rescued, check output queue again.
   */

  seq->writeYUV = writeOutYUV;

  /* We can return immediately if there are queued output pics */
  if (seq->numQueuedOutputPics > 0) {
    getOutputPic(seq, outBuf, outputInt);
    return AVCD_OK_STREAM_NOT_DECODED;
  }

  /* Is current picture waiting to be moved to DPB? */
  if (seq->isDpbStorePending) {
    
#ifdef DEBUG_PRINT
    printf("Store is pending!!!!\n");
#endif
    
    if (dpbStorePicture(seq->dpb, seq->recoBuf, seq->outputQueue) != 0) {
#ifdef DEBUG_PRINT
      printf("Error: dpb store failed\n");
#endif
      return AVCD_ERROR;
    }
    seq->isDpbStorePending = 0;
  }

  /* Are there non-existing frames to be generated? */
  /* Or are there any lost frames to be rescued?    */
  if (seq->unusedShortTermFrameNum >= 0) {
#ifdef ERROR_CONCEALMENT
    if (seq->conceal) {
      ret = concealFrames(seq);
      if (ret < 0)
        return AVCD_ERROR;
      else if (ret != 0) {
        getOutputPic(seq, outBuf, outputInt);
        return AVCD_OK_STREAM_NOT_DECODED;
      }
    }
    else
#endif
    {
      printf("Before genrate non-existing frames\n");
      ret = generateNonExistingFrames(seq);
      if (ret < 0)
        return AVCD_ERROR;
      else if (ret != 0) {
        getOutputPic(seq, outBuf, outputInt);
        return AVCD_OK_STREAM_NOT_DECODED;
      }
    }
  }

  /* Check for end of stream */
  if (nalUnitBits == 0 || nalUnitLen == 0) {
    if (!seq->isSeqFinished && !seq->isCurrPicFinished && seq->recoBuf != NULL) {
#ifdef ERROR_CONCEALMENT
      if (concealAndFinishCurrentPic(seq) < 0)
#else
        if (finishCurrentPic(seq) < 0)
#endif
        return AVCD_ERROR;
    }
    seq->isSeqFinished = 1;
    
    /* At the end of the sequence, output both views */
    for(i=0; i<NUM_VIEWS; i++)
    {
      seq->currSlice->viewId = i;
      
      if(i == NUM_VIEWS-1)
      {
        /* Return at last view */
        if (getOutputPic(seq, outBuf, outputInt))
          return AVCD_OK;
        else
          return AVCD_OK_FRAME_NOT_AVAILABLE;
      }
      else
      {
        getOutputPic(seq, outBuf, outputInt);
      }
    }
  }
  
  /* Decode slice data if slice decode is pending */
  if (seq->isPicBoundary) {
    decodeSliceData(seq);
    
    /* Check for output */
    if (getOutputPic(seq, outBuf, outputInt))
      return AVCD_OK;
    else
      return AVCD_OK_FRAME_NOT_AVAILABLE;
  }
  
  
  /*
   * Decode new NAL unit
   */
  seq->timingInfo = *timingInfo;
  
  /* Initialize bitbuffer and get first byte containing NAL type and NAL ref idc */
  if (bibInit(seq->bitbuf, (u_int8 *)nalUnitBits, nalUnitLen) < 0)
    return AVCD_ERROR;
  
  if (bibGetByte(seq->bitbuf, &nalHeaderByte))
    return AVCD_ERROR;
  
  /* Decode NAL unit type and reference indicator */
  nalType   = nalHeaderByte & 0x1F;
  nalRefIdc = (nalHeaderByte & 0x60) >> 5;
  
  /* Finish current picture if new access unit starts */
  if (!seq->isCurrPicFinished && seq->recoBuf != NULL &&
    nalType >= 6 && nalType <= 13) /* These indicate change of access unit */
  {
#ifdef ERROR_CONCEALMENT
    if (concealAndFinishCurrentPic(seq) < 0)
#else
    if (finishCurrentPic(seq) < 0)
#endif
    return AVCD_ERROR;
  }
  
#ifdef DEBUG_PRINT
  tempTime = (double)clock()/CLOCKS_PER_SEC;
#endif
  
  /* Decode NAL unit data */
  switch (nalType)
  {
  case NAL_TYPE_CODED_SLICE:      // 1 and 20
#ifdef DEBUG_PRINT
    printf("NAL SLICE \n");
#endif
    decodeSlice(seq, nalType, nalRefIdc);
    break;
  case NAL_TYPE_CODED_SLICE_P_A:  // 2
  case NAL_TYPE_CODED_SLICE_P_B:  // 3
  case NAL_TYPE_CODED_SLICE_P_C:  // 4
    break;
  case NAL_TYPE_CODED_SLICE_IDR:  // 5
#ifdef DEBUG_PRINT
    printf("NAL SLICE IDR \n");
#endif
    decodeSlice(seq, nalType, nalRefIdc);
    break;
  case NAL_TYPE_SEI:              // 6
#ifdef ERROR_CONCEALMENT
    decodeSei(seq);
#else
#ifdef DEBUG_PRINT
    printf("SEI NAL unit (6) skipped.\n");
#endif
#endif
    break;
  case NAL_TYPE_SPS:              // 7
#ifdef DEBUG_PRINT
    printf("NAL SPS \n");
#endif
    if (psDecodeSPS(seq->bitbuf, seq->spsList) < 0)
      return AVCD_ERROR;
    else
      spsFound = 1;
    break;
  case NAL_TYPE_PPS:              // 8
#ifdef DEBUG_PRINT
    printf("NAL PPS \n");
#endif
    if (psDecodePPS(seq->bitbuf, seq->ppsList) < 0)
      return AVCD_ERROR;
    break;
  case NAL_TYPE_AU_DELIMITER:     // 9
    break;
  case NAL_TYPE_END_SEQ:          // 10
    break;
  case NAL_TYPE_END_STREAM:       // 11
    break;
  case NAL_TYPE_FILLER_DATA:      // 12
    break;
  case NAL_TYPE_PREFIX:           // 14
    //    printf("Prefix NAL unit (14) \n");
#ifdef DEBUG_PRINT
    printf("Prefix NAL(14) \n");
#endif
    decodeMVCPrefix(seq, nalType);
    break;
  case NAL_TYPE_SUBSET_SPS:   // 15
#ifdef DEBUG_PRINT
    printf("Subset SPS (15) \n");
#endif
    if (psDecodeSubsetSPS(seq->bitbuf, seq->spsList) < 0)
      return AVCD_ERROR;
    break;
  case NAL_NON_BASE_VIEW_SLICE:     // 20
    //    printf("Prefix NAL unit (14) \n");
#ifdef DEBUG_PRINT
    printf("Non-base view NAL(20) \n");
#endif
    decodeMVCPrefix(seq, nalType);
    decodeSlice(seq, nalType, nalRefIdc);
    break;
  default:
    /* Unspecied NAL types 0 and 24-31 */
    if (nalType == 0 || (nalType >= 24 && nalType <= 31)) {
#ifdef DEBUG_PRINT
      printf("Unspecified NAL type: (%i)\n", nalType);
#endif
    ;
    }
    /* Reserved NAL types 13-23 */
    else {
#ifdef DEBUG_PRINT
      printf("Reserved NAL type (%i)\n", nalType);
#endif
    ;
    }
    break;
  }
  
#ifdef DEBUG_PRINT
  seq->frameTime += ((double)clock()/CLOCKS_PER_SEC) - tempTime;
  printf("Frame time (cumulative) %3.3f seconds\n", seq->frameTime);
#endif
  
  /*
   * Check the output queue once again
   */
  if (getOutputPic(seq, outBuf, outputInt)) {
    if (seq->isPicBoundary)
      /* We have output picture, but current slice has not been decoded */ 
      return AVCD_OK_STREAM_NOT_DECODED;
    else
      return AVCD_OK;
  }
  else {
    if (seq->isPicBoundary) {
      /* If queue is empty, there should be no slice data left for current slice */

#ifdef DEBUG_PRINT
      printf("Something wrong here...\n");
#endif
    }
    if (spsFound)
      return AVCD_OK_RESOLUTION_AVAILABLE;  // Signal that the video resolution is found
    else
      return AVCD_OK_FRAME_NOT_AVAILABLE;
  }
}


/*
 *
 * findStartCode:
 *
 * Parameters:
 *      ptr                   Pointer to byte stream
 *      len                   Length of byte stream
 *      offset                Search start position
 *      startCodeLen          Return pointer for start code langth
 *
 * Function:
 *      First next start code in byte stream
 *
 * Returns:
 *      Start code position if found or length of byte stream if
 *      start code was not found
 *
 */
static int findStartCode(u_int8 *ptr, int len, int offset, int *startCodeLen)
{
  int numZeros = 0;

  while (offset < len) {
    if (ptr[offset] == 0)
      numZeros++;
    else if (ptr[offset] == 1 && numZeros > 1) {
      *startCodeLen = numZeros + 1;
      return offset - numZeros;
    }
    else
      numZeros = 0;

    offset++;
  }

  return len;
}


/*
 *
 * avcdDecodeOneFrame:
 *
 * Parameters:
 *      dec                     Sequence object
 *      frameBitsPtr            Bits for frame
 *      frameBitsLen            Number of bytes in frame
 *      outBuf                  Possibly outputted frame
 *      timingInfo              Time stamps
 *
 * Function:
 *      Decode frame.
 *
 * Returns:
 *      AVCD_OK:                     Frame decoded and frame available
 *      AVCD_OK_FRAME_NOT_AVAILABLE: Frame decoded, frame not available
 *      AVCD_OK_STREAM_NOT_DECODED:  Frame not decoded, frame available
 *      AVCD_ERROR:                  Error occured
 *
 */
int avcdDecodeOneFrame(avcdDecoder_t *dec, void *frameBitsPtr,
                       int frameBitsLen, avcdYUVbuffer_s *outBuf,
                       avcdTimingInfo_s *timingInfo)
{
  sequence_s *seq = (sequence_s *)dec;
  int isStreamEnd;
  int isFrameEnd;
  void *nalBitsPtr;
  int nalBitsLen;
  int numOutput;


  /* If previous frame was completely decoded, start decoding */
  /* this frame from the beginning.                           */
  if (seq->decResult != AVCD_OK_STREAM_NOT_DECODED)
    seq->streamPos = 0;


  /* Check if end of stream (Empty NAL unit) */
  if (frameBitsPtr == 0 || frameBitsLen == 0) {
    seq->isSeqFinished = 1;
    isStreamEnd = 1;
  }
  else
    isStreamEnd = 0;

  isFrameEnd = 0;


  /*
   * Decode all NAL units of the frame one NAL unit at a time.
   * avcdDecodeOneNal() is called for each NAL unit.
   */

  do {

    if (isStreamEnd) {
      nalBitsPtr = 0;
      nalBitsLen = 0;
    }
    else if (seq->decResult != AVCD_OK_STREAM_NOT_DECODED) {
      int nalStart;
      int nalStart2;
      int startCodeLen;
      int startCodeLen2;

      /* Find first start code */
      nalStart = findStartCode((u_int8 *)frameBitsPtr, frameBitsLen, seq->streamPos, &startCodeLen);
      if (nalStart != seq->streamPos) {
        printf("Error in byte stream\n");
        return AVCD_ERROR;
      }

      /* Find second start code */
      nalStart2 = findStartCode((u_int8 *)frameBitsPtr, frameBitsLen, nalStart+startCodeLen, &startCodeLen2);
      if (nalStart2-nalStart-startCodeLen < 1) {  // 1 is minimum NAL unit length
        printf("Error in byte stream\n");
        return AVCD_ERROR;
      }

      /* Move stream pointer to next NAL unit */
      seq->streamPos = nalStart2;

      nalBitsPtr = (u_int8 *)frameBitsPtr + nalStart;
      nalBitsLen = nalStart2-nalStart;
    }
    else {
      /* Previous NAL unit was not decoded -> give some non-zero input   */
      /* to avcdDecodeOneNal to finish decoding previous NAL unit.       */
      /* There is no need to give exact bit pointer in this case because */
      /* avcdDecodeOneNal has stored pointer for unfinished NAL unit.    */
      nalBitsPtr = frameBitsPtr;
      nalBitsLen = 1;
    }

    /* Decode NAL unit and check result */
    seq->decResult = avcdDecodeOneNal(dec, nalBitsPtr, nalBitsLen, outBuf,
                                      timingInfo, NULL, 0);

    /* If there are no more bits in the stream and we got no frame, we */
    /* know that all frames have been decoded and output.              */
    if (isStreamEnd && seq->decResult == AVCD_OK_FRAME_NOT_AVAILABLE)
      isFrameEnd = 1;

    /* If we have decoded all NAL units of the frame, we can go */
    if (!isStreamEnd && seq->streamPos >= frameBitsLen)
      isFrameEnd = 1;

    /* Decode until we are at the end of frame or ouput picture is available */
  } while (!isFrameEnd && seq->decResult == AVCD_OK_FRAME_NOT_AVAILABLE);


  /*
   * If we are not at the end of stream and there is no frame available
   * for output, we can finish current frame.
   */
  if (!isStreamEnd && seq->decResult == AVCD_OK_FRAME_NOT_AVAILABLE) {

    if (!seq->isCurrPicFinished) {
#ifdef ERROR_CONCEALMENT
      /* Conceal and finish decoding of current picture */
      numOutput = concealAndFinishCurrentPic(seq);
#else
      /* Finish decoding of current picture */
      numOutput = finishCurrentPic(seq);
#endif

      /* numOutput is the number of pictures in output queue */
      /* If numOutput < 0, error occured */
      if (numOutput < 0)
        return AVCD_ERROR;
    }

    /* Check if frame is available for output */
    if (getOutputPic(seq, outBuf, NULL))
      seq->decResult = AVCD_OK;
    else
      seq->decResult = AVCD_OK_FRAME_NOT_AVAILABLE;
  }


  return seq->decResult;
}


int openOutputFiles(sequence_s *seq)
{
  char tmpName[31] = "OutLeft.yuv";
  char tmpName2[31] = "OutRight.yuv";

  if ((seq->outFileLeft = fopen(tmpName, "wb")) == NULL) {
    fprintf(stderr, "Cannot open output file \"%s\"\n", tmpName);
    exit(1);
  }
  if ((seq->outFileRight = fopen(tmpName2, "wb")) == NULL) {
    fprintf(stderr, "Cannot open output file \"%s\"\n", tmpName);
    exit(1);
  }
  
  return 1;
}


void closeOutputFiles(sequence_s *seq)
{
  fclose(seq->outFileLeft);  
  fclose(seq->outFileRight);  
}


void writeYUVOut(sequence_s *seq, frmBuf_s *recoBuf, int viewId)
{
  int width = (seq->spsList[0]->pic_width_in_mbs_minus1+1)*16;
  int height = (seq->spsList[0]->pic_height_in_map_units_minus1+1)*16;


  if (viewId == 0) {
    fwrite(recoBuf->y, sizeof(unsigned char), width*height, seq->outFileLeft);
    fwrite(recoBuf->u, sizeof(unsigned char), (width*height >> 2), seq->outFileLeft);
    fwrite(recoBuf->v, sizeof(unsigned char), (width*height >> 2), seq->outFileLeft);
  }
  else {
    fwrite(recoBuf->y, sizeof(unsigned char), width*height, seq->outFileRight);
    fwrite(recoBuf->u, sizeof(unsigned char), (width*height >> 2), seq->outFileRight);
    fwrite(recoBuf->v, sizeof(unsigned char), (width*height >> 2), seq->outFileRight);
  }
}


int decodeMVCPrefix(sequence_s *seq, int nalType)
{
  slice_s *slice;
  int retCode;
  unsigned int tempByte;
  bitbuffer_s *bitbuf;


  slice = seq->nextSlice;
  bitbuf = seq->bitbuf;

  if ((retCode = u_n(bitbuf, 8, &tempByte)) < 0)
    return retCode;

  /* Check for the reserved zero bit */
  if ((tempByte >> 7) & 0x01)
  {
    /* Return an error, reserved zero bit is one */
    return(-1);
  }

  // Read the non_idr_flag
  slice->idrFlag = !((tempByte >> 6) & 0x01);

  slice->priorityId = tempByte & 0x3f;

  // Get the view id
  if ((retCode = u_n(bitbuf, 8, &tempByte)) < 0)
    return retCode;

  slice->viewId = tempByte << 2;    // 8 highest bits

  if ((retCode = u_n(bitbuf, 8, &tempByte)) < 0)
    return retCode;

  slice->viewId |= ((tempByte >> 6) & 0x03);    // 2 lowest bits
  slice->temporalId = (tempByte >> 3) & 0x03;
  slice->anchorPicFlag = (tempByte >> 2) & 0x01;
  slice->interViewFlag = (tempByte >> 1) & 0x01;

  if( !(tempByte & 0x01) )
    return (-1);

  if (nalType == NAL_TYPE_PREFIX) {
    if (bibSkipTrailingBits(bitbuf) < 0)
      return AVCD_ERROR;
  }

  return AVCD_OK;
}


void avcdGetResolution(avcdDecoder_t *dec, int *width, int *height)
{
  sequence_s *seq = (sequence_s *)dec;

  *width = (seq->spsList[0]->pic_width_in_mbs_minus1+1)*16;
  *height = (seq->spsList[0]->pic_height_in_map_units_minus1+1)*16;
}

