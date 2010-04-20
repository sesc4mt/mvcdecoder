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

#include <string.h>
#include <stdio.h>
#include "nccglob.h"
#include "globals.h"
#include "bitbuffer.h"
#include "vld.h"
#include "macroblock.h"
#include "loopfilter.h"
#include "parameterset.h"
#include "framebuffer.h"
#include "dpb.h"
#include "slice.h"

#ifdef ERROR_CONCEALMENT
#include "errorconcealment.h"
#endif


#define MIN_ALPHA_BETA_OFFSET   -6
#define MAX_ALPHA_BETA_OFFSET   6


/*
 * AVC syntax functions as specified in specification
 */

/*
 * Static functions
 */
static int getRefPicListReorderingCmds(slice_s *slice, unsigned int numRefFrames,
                                       unsigned int *ref_pic_list_reordering_flag_lx,
                                       sliceRefPicListReorderCmd_s *reorderCmdListX,
                                       bitbuffer_s *bitbuf);

static int getDecRefPicMarkingCmds(slice_s *slice, unsigned int numRefFrames,
                                   bitbuffer_s *bitbuf);

static int refPicListReordering(slice_s *slice, 
                                seq_parameter_set_s *sps,	
                                dpb_s *dpb,
                                frmBuf_s *refPicList[], int numRefPicActive,
                                sliceRefPicListReorderCmd_s reorderCmdList[]);

int readSliceMVCExtension(slice_s *slice, bitbuffer_s *bitbuf );


/*
 * AVC syntax functions as specified in specification
 */

/* Return fixed length code */
static int u_n(bitbuffer_s *bitbuf, int len, unsigned int *val)
{
  *val = vldGetFLC(bitbuf, len);

  if (bibGetStatus(bitbuf) < 0)
    return SLICE_ERROR;

  return SLICE_OK;
}


/* Return unsigned UVLC code */
static int ue_v(bitbuffer_s *bitbuf, unsigned int *val, unsigned int maxVal)
{
  *val = vldGetUVLC(bitbuf);

  if (bibGetStatus(bitbuf) < 0)
    return SLICE_ERROR;

  if (*val > maxVal)
    return SLICE_ERR_ILLEGAL_VALUE;

  return SLICE_OK;
}


/* Return signed UVLC code */
static int se_v(bitbuffer_s *bitbuf, int *val, int minVal, int maxVal)
{
  *val = vldGetSignedUVLC(bitbuf);

  if (bibGetStatus(bitbuf) < 0)
    return SLICE_ERROR;

  if (*val < minVal || *val > maxVal)
    return SLICE_ERR_ILLEGAL_VALUE;

  return SLICE_OK;
}


/* Return long signed UVLC code */
static int se_v_long(bitbuffer_s *bitbuf, int32 *val)
{
  *val = vldGetSignedUVLClong(bitbuf);

  if (bibGetStatus(bitbuf) < 0)
    return SLICE_ERROR;

  return SLICE_OK;
}


/*
 *
 * sliceOpen:
 *
 * Parameters:
 *
 * Function:
 *      Allocate and initialize a slice.
 *
 * Returns:
 *      Pointer to slice
 *
 */
slice_s *sliceOpen()
{
  slice_s *slice;

  slice = (slice_s *)nccMalloc(sizeof(slice_s));

  if (slice != NULL)
    memset(slice, 0, sizeof(slice_s));

  return slice;
}


/*
 *
 * sliceClose:
 *
 * Parameters:
 *      slice                 Slice object
 *
 * Function:
 *      Deallocate slice
 *
 * Returns:
 *      Nothing
 *
 */
void sliceClose(slice_s *slice)
{
  nccFree(slice);
}


/*
 *
 * getSliceHeader:
 *
 * Parameters:
 *      slice                 Slice object
 *      spsList               Sequence Parameter Set list
 *      ppsList               Picture Parameter Set list
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Parses slice header syntax.
 *      
 * Returns:
 *      SLICE_OK for no error and negative value for error.
 *
 */
int sliceGetHeader(slice_s *slice, seq_parameter_set_s *spsList[],
                   pic_parameter_set_s *ppsList[], bitbuffer_s *bitbuf)
{
  seq_parameter_set_s *sps;
  pic_parameter_set_s *pps;
  unsigned int picSizeInMapUnits;
  unsigned int temp, temp2;
  int sliceQp, len1;
  int retCode;


#ifdef DEBUG_PRINT
  slice->intraTime = 0.0;
  slice->vldTime = 0.0;
  slice->interTime = 0.0;
  slice->codingTime = 0.0;
#endif

  slice->picHasMMCO5 = 0;

  /* first_mb_in_slice */
  if ((retCode = ue_v(bitbuf, &slice->first_mb_in_slice, 65535)) < 0)
    return retCode;

  /* slice_type */
  if ((retCode = ue_v(bitbuf, &slice->slice_type, SLICE_MAX)) < 0)
    return retCode;

  /* pps id */
  if ((retCode = ue_v(bitbuf, &slice->pic_parameter_set_id, PS_MAX_NUM_OF_PPS-1)) < 0)
    return retCode;

  pps = ppsList[slice->pic_parameter_set_id];
  if (pps == NULL) {

#ifdef DEBUG_PRINT
    printf("Error: referring to non-existing PPS.\n");
#endif
    return SLICE_ERR_NON_EXISTING_PPS;
  }

  sps = spsList[pps->seq_parameter_set_id];
  if (sps == NULL) {

#ifdef DEBUG_PRINT
    printf("Error: referring to non-existing SPS.\n");
#endif
    return SLICE_ERR_NON_EXISTING_SPS;
  }

  picSizeInMapUnits = (sps->pic_width_in_mbs_minus1+1) * (sps->pic_height_in_map_units_minus1+1);

  if (slice->first_mb_in_slice >= picSizeInMapUnits)
    return SLICE_ERR_ILLEGAL_VALUE;

  /* frame_num */ 
  slice->maxFrameNum = (u_int32)1 << (sps->log2_max_frame_num_minus4+4);

  if ((retCode = u_n(bitbuf, (int)sps->log2_max_frame_num_minus4+4, &slice->frame_num)) < 0)
    return retCode;

  /* IDR pic ID */
  if (slice->isIDR) {
    if ((retCode = ue_v(bitbuf, &slice->idr_pic_id, 65535)) < 0)
      return retCode;
  }

  /* POC parameters */
  if (sps->pic_order_cnt_type == 0) {
    /* read pocLsb and deltaPOCLsb */
    if ((retCode = u_n(bitbuf, (int)sps->log2_max_pic_order_cnt_lsb_minus4+4, &slice->pic_order_cnt_lsb)) < 0)
      return retCode;

    slice->delta_pic_order_cnt_bottom = 0;
    if (pps->pic_order_present_flag) { /*  && !field_pic_flag */
      if ((retCode = se_v_long(bitbuf, &slice->delta_pic_order_cnt_bottom)) < 0)
        return retCode;
    }
  }
  else if (sps->pic_order_cnt_type == 1) {
    slice->delta_pic_order_cnt_0 = 0;
    slice->delta_pic_order_cnt_1 = 0;
    /* read delta_pic_order_cnt[ 0 ] and delta_pic_order_cnt[ 1 ]*/
    if (!sps->delta_pic_order_always_zero_flag) {
      /* delta_pic_order_cnt[ 0 ] */
      if ((retCode = se_v_long(bitbuf, &slice->delta_pic_order_cnt_0)) < 0)
        return retCode;
      if (pps->pic_order_present_flag) { /*  && !field_pic_flag */
        if ((retCode = se_v_long(bitbuf, &slice->delta_pic_order_cnt_1)) < 0)
          return retCode;
      }
    }
  }

  /* redundant pic cnt*/
  if (pps->redundant_pic_cnt_present_flag) {
    if ((retCode = ue_v(bitbuf, &slice->redundant_pic_cnt, 127)) < 0)
      return retCode;
  }
  else
    slice->redundant_pic_cnt = 0;

  /* reference picture management */
  if (!IS_SLICE_I(slice->slice_type)) {
    if ((retCode = u_n(bitbuf, 1, &slice->num_ref_idx_active_override_flag)) < 0)
      return retCode;
    if (slice->num_ref_idx_active_override_flag) {
      if ((retCode = ue_v(bitbuf, &slice->num_ref_idx_l0_active_minus1, DPB_MAX_SIZE-1)) < 0)
        return retCode;
    }
    else {
      slice->num_ref_idx_l0_active_minus1 = pps->num_ref_idx_l0_active_minus1;
    }
  }

  if (!IS_SLICE_I(slice->slice_type)) {
    /* reordering the ref picture list */
    retCode = getRefPicListReorderingCmds(slice, sps->num_ref_frames,
                                          &slice->ref_pic_list_reordering_flag_l0,
                                          slice->reorderCmdList0,
                                          bitbuf);
    if (retCode < 0)
      return retCode;

  }

  /* get the MMCO commands, but not do the operations until all the slices in current picture are decoded */
  if (slice->nalRefIdc) {
    retCode = getDecRefPicMarkingCmds(slice, sps->num_ref_frames, bitbuf);
    if (retCode < 0)
      return retCode;
  }

  /* Slice quant */
  if ((retCode = se_v(bitbuf, &slice->slice_qp_delta, -MAX_QP, MAX_QP)) < 0)
    return retCode;

  sliceQp = pps->pic_init_qp_minus26 + 26 + slice->slice_qp_delta;
  if (sliceQp < MIN_QP || sliceQp > MAX_QP) {

#ifdef DEBUG_PRINT
    printf("Error: illegal slice quant.\n");
#endif
    return SLICE_ERR_ILLEGAL_VALUE;
  }
  slice->qp = sliceQp;

  /* deblocking filter */
  slice->disable_deblocking_filter_idc = 0;
  slice->slice_alpha_c0_offset_div2    = 0;
  slice->slice_beta_offset_div2        = 0;

  if (pps->deblocking_filter_parameters_present_flag == 1) {

    if ((retCode = ue_v(bitbuf, &slice->disable_deblocking_filter_idc, 2)) < 0)
      return retCode;

    if (slice->disable_deblocking_filter_idc != 1) {
      if ((retCode = se_v(bitbuf, &slice->slice_alpha_c0_offset_div2, MIN_ALPHA_BETA_OFFSET, MAX_ALPHA_BETA_OFFSET)) < 0)
        return retCode;
      if ((retCode = se_v(bitbuf, &slice->slice_beta_offset_div2, MIN_ALPHA_BETA_OFFSET, MAX_ALPHA_BETA_OFFSET)) < 0)
        return retCode;
    }
  }

  /* read slice_group_change_cycle */
  if (pps->num_slice_groups_minus1 > 0 && pps->slice_group_map_type >= 3 &&
                                          pps->slice_group_map_type <= 5)
  {
    /* PicSizeInMapUnits / SliceGroupChangeRate */
    temp = picSizeInMapUnits / (pps->slice_group_change_rate_minus1+1);

    /* Calculate Log2 */
    temp2 = (temp + 1) >> 1;
    for (len1 = 0; len1 < 16 && temp2 != 0; len1++)
      temp2 >>= 1;

    /* Calculate Ceil */
    if ( (((unsigned)1) << len1) < (temp + 1) )
      len1++;

    if ((retCode = u_n(bitbuf, len1, &slice->slice_group_change_cycle)) < 0)
      return retCode;

    /* Ceil( PicSizeInMapUnits/SliceGroupChangeRate ) */
    if (temp * (pps->slice_group_change_rate_minus1+1) != picSizeInMapUnits)
      temp++;

    /* The value of slice_group_change_cycle shall be in the range of  */
    /* 0 to Ceil( PicSizeInMapUnits/SliceGroupChangeRate ), inclusive. */
    if (slice->slice_group_change_cycle > temp)
      return SLICE_ERR_ILLEGAL_VALUE;
  }

  return SLICE_OK;
}


/*
 * getRefPicListReorderingCmds:
 *
 * Parameters:
 *     slice                             Slice object
 *     numRefFrames                      Number of reference frames in used
 *     ref_pic_list_reordering_flag_lx   Return reordering enabled flag
 *     reorderCmdListX                   Reordering command list
 *     bitbuf                            Bitbuffer object
 *
 * Function:
 *     Parse and store the ref pic reordering commands
 *
 * Return:
 *     Return code
 */
static int getRefPicListReorderingCmds(slice_s *slice, unsigned int numRefFrames,
                                       unsigned int *ref_pic_list_reordering_flag_lx,
                                       sliceRefPicListReorderCmd_s *reorderCmdListX,
                                       bitbuffer_s *bitbuf)
{
  int i;
  unsigned int reordering_of_pic_nums_idc;
  int retCode;

  if ((retCode = u_n(bitbuf, 1, ref_pic_list_reordering_flag_lx)) < 0)
    return retCode;

  if (*ref_pic_list_reordering_flag_lx) {

    i = 0;
    do {
      /* Get command */
      if ((retCode = ue_v(bitbuf, &reordering_of_pic_nums_idc, 5)) < 0)
        return retCode;

      reorderCmdListX[i].reordering_of_pic_nums_idc = reordering_of_pic_nums_idc;

      /* Get command parameters */
      if (reordering_of_pic_nums_idc == 0 || reordering_of_pic_nums_idc == 1) {
        unsigned int maxDiff = slice->maxFrameNum-1;
        if ((retCode = ue_v(bitbuf, &reorderCmdListX[i].abs_diff_pic_num_minus1, maxDiff)) < 0)
          return retCode;
      }
      else if (reordering_of_pic_nums_idc == 2) {
        /* longTermPicNum be in the range of 0 to num_ref_frames, inclusive. */
        if ((retCode = ue_v(bitbuf, &reorderCmdListX[i].long_term_pic_num, numRefFrames)) < 0)
          return retCode;
      }
      else if (reordering_of_pic_nums_idc == 4 || reordering_of_pic_nums_idc == 5) {
        unsigned int maxDiff = MAX_NUM_VIEWS;		
        if ((retCode = ue_v(bitbuf, &reorderCmdListX[i].abs_diff_view_idx_minus1, maxDiff)) < 0)
          return retCode;
      }

      i++;
    } while (reordering_of_pic_nums_idc != 3 && i < MAX_NUM_OF_REORDER_CMDS);
  }

  return SLICE_OK;
}


/*
 * getDecRefPicMarkingCmds:
 *
 * Parameters:
 *     slice               Slice object
 *     bitbuf              Bitbuffer object
 *     numRefFrames        Number of reference frames in used
 *
 * Function:
 *     Parse and store the MMCO commands
 *
 * Return:
 *     The number of bits being parsed
 */
static int getDecRefPicMarkingCmds(slice_s *slice, unsigned int numRefFrames,
                                   bitbuffer_s *bitbuf)
{
  int i;
  unsigned int mmco;
  int retCode;

  /* MMCO commands can exist only in slice header of a reference picture */
  if (slice->nalRefIdc != 0) {
    if (slice->idrFlag) {
      if ((retCode = u_n(bitbuf, 1, &slice->no_output_of_prior_pics_flag)) < 0)
        return retCode;
      if ((retCode = u_n(bitbuf, 1, &slice->long_term_reference_flag)) < 0)
        return retCode;
    }
    else {
      if ((retCode = u_n(bitbuf, 1, &slice->adaptive_ref_pic_marking_mode_flag)) < 0)
        return retCode;

      if (slice->adaptive_ref_pic_marking_mode_flag) {

        i = 0;
        do {
          /* Get MMCO command */
          if ((retCode = ue_v(bitbuf, &mmco, 6)) < 0)
            return retCode;

          slice->mmcoCmdList[i].memory_management_control_operation = mmco;

          /* Get command parameter (if any) */
          if (mmco == 1 || mmco == 3) {
            if ((retCode = ue_v(bitbuf, &slice->mmcoCmdList[i].difference_of_pic_nums_minus1, 65535)) < 0)
              return retCode;
          }
          if (mmco == 2) {
            if ((retCode = ue_v(bitbuf, &slice->mmcoCmdList[i].long_term_pic_num, numRefFrames)) < 0)
              return retCode;
          }
          if (mmco == 3 || mmco == 6) {
            if ((retCode = ue_v(bitbuf, &slice->mmcoCmdList[i].long_term_frame_idx, numRefFrames)) < 0)
              return retCode;
          }
          if (mmco == 4) {
            if ((retCode = ue_v(bitbuf, &slice->mmcoCmdList[i].max_long_term_frame_idx_plus1, numRefFrames)) < 0)
              return retCode;
          }
          if (mmco == 5) {
            slice->picHasMMCO5 = 1;
          }

          i++;
        } while (mmco != 0 && i < MAX_NUM_OF_MMCO_OPS);
      }
    }
  }
  else
    slice->adaptive_ref_pic_marking_mode_flag = 0;

  return NCC_OK;
}


/*
 * sliceInitRefPicList:
 *
 * Parameters:
 *     dpb                  DPB buffer
 *     refPicList           Reference picture list (output)
 *     frameNum             Current frame number
 *
 * Fucntion:
 *     Initialize reference picture list.
 *
 * Return:
 *     Number of reference frames in the list
 */
int sliceInitRefPicList(dpb_s *dpb, frmBuf_s *refPicList[], int currViewId, int frameNum)
{
  int numRef, numShort;
  frmBuf_s *refTmp;
  int i, j, k;

  /*
   * Select the reference pictures from the DPB
   */
  j = 0;

  /* Put short term pictures first in the list */
  for (i = 0; i < dpb->fullness[currViewId]; i++) {
    if (dpb->buffers[i][currViewId]->refType == FRM_SHORT_TERM_PIC) {
      refPicList[j++] = dpb->buffers[i][currViewId];
    }
  }

  numShort = j;

  /* Sort short term pictures in the order of descending picNum */
  for (i = 0; i < numShort; i++) {
    for (k = i+1; k < numShort; k++) {
      if (refPicList[i]->picNum < refPicList[k]->picNum) {
        /* exchange refPicList[i] and refPicList[k] */
        refTmp = refPicList[i];
        refPicList[i] = refPicList[k];
        refPicList[k] = refTmp;
      }
    }
  }

  /* For a non-base view, add base view reference */
  if (currViewId > 0) {
    for (i = 0; i < dpb->fullness[0]; i++) {
      if (dpb->buffers[i][0]->refType == FRM_SHORT_TERM_PIC && dpb->buffers[i][0]->picNum == frameNum) {
        refPicList[j++] = dpb->buffers[i][0];
      }
    }
  }

  /* Update numShort value */
  numShort = j;

  /* Put long term pictures after the short term pictures */
  for (i = 0; i < dpb->fullness[currViewId]; i++) {
    if (dpb->buffers[i][currViewId]->refType == FRM_LONG_TERM_PIC) 
      refPicList[j++] = dpb->buffers[i][currViewId];
  }
  numRef = j;

  /*
   * Initialisation process for reference picture lists
   */
  /* Sort long term pictures in the order of ascending longTermPicNum */
  for (i = numShort; i < numRef; i++) {
    for (j = i+1; j < numRef; j++) {
      if (refPicList[i]->longTermPicNum > refPicList[j]->longTermPicNum) {
        /* exchange refPicList[i] and refPicList[j] */
        refTmp = refPicList[i];
        refPicList[i] = refPicList[j];
        refPicList[j] = refTmp;
      }
    }
  }

#ifdef DEBUG_PRINT
  printf("Slice: RefPicList: ");
  for (i = 0; i < numShort; i++) {
    printf(" %d %d, ", (int)(refPicList[i]->picNum), (int)(refPicList[i]->viewId)); 
  }
  printf("\n");
#endif

  return numRef;
}


/*
 * sliceFixRefPicList:
 *
 * Parameters:
 *     dpb                  DPB buffer
 *     refPicList           Reference picture list (output)
 *     numExistingRefFrames Number of reference frames in refPicList
 *     width , height       Width and height of the picture
 *     viewId               ViewId of the current view
 *
 * Fucntion:
 *     If numExistingRefFrames < numRefPicActive, try to fill up the
 *     reference frame list
 *
 * Return:
 *     0 for no pictures exist in reference frame list
 *     1 for pictures exist in reference frame list
 */
int sliceFixRefPicList(dpb_s *dpb, frmBuf_s *refPicList[],
                       int numExistingRefFrames,
                       int width, int height,
          					   int viewId)
{
  int i;

  if (numExistingRefFrames == 0) {
    /* Try to find any picture in DPB, even non-reference frame */
    for (i = 0; i < dpb->size[viewId]; i++) {
      if (dpb->buffers[i][viewId] != NULL && dpb->buffers[i][viewId]->width == width && dpb->buffers[i][viewId]->height == height)
        break;
    }

    if (i < dpb->size[viewId]) {
      refPicList[0] = dpb->buffers[i][viewId];
      numExistingRefFrames = 1;
    }
    else
      return 0;
  }

  /* Duplicate last extry of the reference frame list so that list becomes full */
  for (i = numExistingRefFrames; i < DPB_MAX_SIZE; i++)
    refPicList[i] = refPicList[numExistingRefFrames-1];

  return 1;
}


/*
 * refPicListReordering:
 *
 * Parameters:
 *     slice                Current slice object
 *     sps                  Current SPS parameter set
 *     dpb                  DPB buffer
 *     refPicList           Reference picture list (modified by this function)
 *     numRefPicActive      Number of active reference frames
 *     reorderCmdList       Reordering command list
 *
 * Fucntion:
 *     Reorder the reference picture list for current slice
 *
 * Return:
 *     SLICE_OK for no error and negative value for error
 */
static int refPicListReordering(slice_s *slice, 
                								seq_parameter_set_s *sps,
								                dpb_s *dpb,
                                frmBuf_s *refPicList[], int numRefPicActive,
                                sliceRefPicListReorderCmd_s reorderCmdList[])
{
  int i;
  int reordering_of_pic_nums_idc, longTermPicNum;
  int32 absDiffPicNum;
  int refIdx;
  int32 currPicNum, picNumPred, picNumNoWrap;
  int32 maxPicNum, picNum;
  int cmdNum;
  int cIdx, nIdx;
  int viewId;
  int absDiffViewIdx;
  int picViewIdxLXPred, picViewIdxLX;
  int maxViewIdx;
  int targetViewId;


  viewId = slice->viewId;

  /*
   * 3. Reordering process for reference picture list
   */
  maxPicNum = slice->maxFrameNum;   /* for frame coding only */
  currPicNum = slice->frame_num;
  picNumPred = currPicNum;
  refIdx = 0;
  cmdNum = 0;

  picViewIdxLXPred = 0;
  if(slice->anchorPicFlag)
    maxViewIdx = sps->num_anchor_refs_l0[viewId];
  else
    maxViewIdx = sps->num_non_anchor_refs_l0[viewId];

  do {
    reordering_of_pic_nums_idc = reorderCmdList[cmdNum].reordering_of_pic_nums_idc;

    if (reordering_of_pic_nums_idc == 0 || reordering_of_pic_nums_idc == 1) {

      /*
       * reorder short-term ref pic  -subclause 8.2.4.3.1
       */
      absDiffPicNum = reorderCmdList[cmdNum].abs_diff_pic_num_minus1 + 1;

      /* Derive picNumNoWrap */
      if (reordering_of_pic_nums_idc == 0) {
        if (picNumPred - absDiffPicNum < 0)
          picNumNoWrap = picNumPred - absDiffPicNum + maxPicNum;
        else
          picNumNoWrap = picNumPred - absDiffPicNum;
      }
      else { /* reordering_of_pic_nums_idc == 1 */
        if (picNumPred + absDiffPicNum >= maxPicNum) 
          picNumNoWrap = picNumPred + absDiffPicNum - maxPicNum;
        else
          picNumNoWrap = picNumPred + absDiffPicNum;
      }

      /* Derive picNum */
      if (picNumNoWrap > currPicNum)
        picNum = picNumNoWrap - maxPicNum;
      else
        picNum = picNumNoWrap;

      /* Find short term picture with picture number picNum */
      for (i = 0; i < dpb->fullness[viewId]; i++) {
        if (!dpb->buffers[i][viewId]->nonExisting &&
            dpb->buffers[i][viewId]->refType == FRM_SHORT_TERM_PIC &&
            dpb->buffers[i][viewId]->picNum == picNum)
          break;
      }

      /* If picNum was not found */
      if (i == dpb->fullness[viewId]) {

#ifdef DEBUG_PRINT
        printf("The short term ref pic(%d) is not found!\n", (int)picNum);
#endif
        return SLICE_ERR_ILLEGAL_VALUE;
      }

      /* Shift remaining pictures later in the list */
      for (cIdx = numRefPicActive; cIdx > refIdx; cIdx--)
        refPicList[cIdx] = refPicList[cIdx - 1];

      /* Place picture with number picNum into the index position refIdx */
      refPicList[refIdx++] = dpb->buffers[i][viewId];

      /* Remove duplicate of the inserted picture */
      nIdx = refIdx;
      for (cIdx = refIdx; cIdx <= numRefPicActive; cIdx++)
        if (refPicList[cIdx]->refType == FRM_LONG_TERM_PIC || refPicList[cIdx]->picNum != picNum)
          refPicList[nIdx++] = refPicList[cIdx];

      picNumPred = picNumNoWrap;
    }

    else if (reordering_of_pic_nums_idc == 2) {

      /*
       * reorder long-term ref pic  -subclause 8.2.4.3.2
       */

      /* Get long-term picture number */
      longTermPicNum = reorderCmdList[cmdNum].long_term_pic_num;

      /* Find long-term picture with picture number longTermPicNum */
      for (i = 0; i < dpb->fullness[viewId]; i++)
        if (dpb->buffers[i][viewId]->refType == FRM_LONG_TERM_PIC &&
            dpb->buffers[i][viewId]->longTermPicNum == longTermPicNum)
          break;

      if (i == dpb->fullness[viewId]) {
#ifdef DEBUG_PRINT
        printf("The long term ref pic(%d) is not found!\n", longTermPicNum);
#endif
        return SLICE_ERR_ILLEGAL_VALUE;
      }

      /* Shift remaining pictures later in the list */
      for (cIdx = numRefPicActive; cIdx > refIdx; cIdx--)
        refPicList[cIdx] = refPicList[cIdx - 1];

      /* Place picture with number longTermPicNum into the index position refIdx */
      refPicList[refIdx++] = dpb->buffers[i][viewId];

      /* Remove duplicate of the inserted picture */
      nIdx = refIdx;
      for (cIdx = refIdx; cIdx <= numRefPicActive; cIdx++)
        if (refPicList[cIdx]->refType == FRM_SHORT_TERM_PIC ||
            refPicList[cIdx]->longTermPicNum != longTermPicNum)
        {
          refPicList[nIdx++] = refPicList[cIdx];
        }
    }
    else if (reordering_of_pic_nums_idc == 4 || reordering_of_pic_nums_idc == 5) 
	{

		absDiffViewIdx = reorderCmdList[cmdNum].abs_diff_view_idx_minus1 + 1;

		/* Derive picNumNoWrap */
      if (reordering_of_pic_nums_idc == 4) 
	  {
        if (picViewIdxLXPred - absDiffViewIdx < 0)
          picViewIdxLX = picViewIdxLXPred - absDiffViewIdx + maxViewIdx;
        else
          picViewIdxLX = picViewIdxLXPred - absDiffViewIdx;
      }
      else 
	  { /* reordering_of_pic_nums_idc == 5 */
        if (picViewIdxLXPred + absDiffViewIdx >= maxViewIdx) 
          picViewIdxLX = picViewIdxLXPred + absDiffViewIdx - maxViewIdx;
        else
          picViewIdxLX = picViewIdxLXPred + absDiffViewIdx;
      }

	  /* Get the target view id */
      if(slice->anchorPicFlag)
	    targetViewId = sps->anchor_refs_l0[viewId][picViewIdxLX];
	  else
	    targetViewId = sps->non_anchor_refs_l0[viewId][picViewIdxLX];

      /* Find short term picture from target view */
      for (i = 0; i < dpb->fullness[targetViewId]; i++) {
        if (!dpb->buffers[i][targetViewId]->nonExisting &&
            dpb->buffers[i][targetViewId]->refType == FRM_SHORT_TERM_PIC &&
            dpb->buffers[i][targetViewId]->picNum == currPicNum)
          break;
      }

      /* If reference picture from target view was not found */
      if (i == dpb->fullness[targetViewId]) {
        printf("The ref from target view (view id %d) was not found!\n", (int)targetViewId);
        return SLICE_ERR_ILLEGAL_VALUE;
      }

      /* Shift remaining pictures later in the list */
      for (cIdx = numRefPicActive; cIdx > refIdx; cIdx--)
        refPicList[cIdx] = refPicList[cIdx - 1];

	  /* Add the inter-view prediction reference to the list */
      refPicList[refIdx++] = dpb->buffers[i][targetViewId];

      /* Remove duplicate of the inserted picture */
      nIdx = refIdx;
      for (cIdx = refIdx; cIdx <= numRefPicActive; cIdx++)
	  {
        if (refPicList[cIdx]->refType == FRM_LONG_TERM_PIC || refPicList[cIdx]->viewId != targetViewId || refPicList[cIdx]->picNum != currPicNum)
          refPicList[nIdx++] = refPicList[cIdx];
	  }

      picViewIdxLXPred = picViewIdxLX;
    }

    cmdNum++;

  } while (reordering_of_pic_nums_idc != 3 && cmdNum < MAX_NUM_OF_REORDER_CMDS);


  refPicList[numRefPicActive] = 0;

#ifdef DEBUG_PRINT

  for (i=0; i<numRefPicActive; i++) {
    printf("%d %d, ", (int)(refPicList[i]->picNum), (int)(refPicList[i]->viewId));
  }
  printf("\n");
#endif

  return SLICE_OK;
}


/*
 *
 * sliceDecodeMacroblocks:
 *
 * Parameters:
 *      slice                 Slice object
 *      recoBuf               Current frame buffer
 *      dpb                   Decoded picture buffer
 *      pEc                   Error concealment
 *      sps                   Sequence PS
 *      pps                   Picture PS
 *      mdData                Macroblock buffer
 *      sliceID               Slice ID (=sliceNum*16+sliceGroupNum)
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Decode one slice
 *
 * Returns:
 *      SLICE_OK:             Success
 *      <0:                   Fail
 */
int sliceDecodeMacroblocks(slice_s *slice, frmBuf_s *recoBuf, dpb_s *dpb,
#ifdef ERROR_CONCEALMENT
                           errorConcealment_s *pEc,
#endif
                  			   seq_parameter_set_s *sps,	
                           pic_parameter_set_s *pps,
                           mbAttributes_s *mbData, int sliceID,
                           bitbuffer_s *bitbuf)
{
  frmBuf_s *refPicList0[DPB_MAX_SIZE+1];
  macroblock_s mb;
  int numRefFrames;
  int numExistingRefFrames;
  int refFramesExist;
  int mbIdxY;
  int mbIdxX;
  int mbksPerLine;
  int mbksPerCol;
  int picSizeInMbs;
  int currMbAddr;
  int sliceGroupNum;
  void *stream;
  int retCode;


  /* Choose number of reference frames and build reference picture list */
  numRefFrames   = 0;
  refFramesExist = 0;

  if (!IS_SLICE_I(slice->slice_type)) {

    numRefFrames = slice->num_ref_idx_l0_active_minus1 + 1;

    numExistingRefFrames = sliceInitRefPicList(dpb, refPicList0, slice->viewId, slice->frame_num);

    if (numExistingRefFrames < numRefFrames) {
      refFramesExist = sliceFixRefPicList(dpb, refPicList0, numExistingRefFrames,
                                          recoBuf->width, recoBuf->height, slice->viewId);
    }
    else
      refFramesExist = 1;

    if (slice->ref_pic_list_reordering_flag_l0 && numExistingRefFrames > 0) {
      retCode = refPicListReordering(slice, sps, dpb, refPicList0, numRefFrames, slice->reorderCmdList0);
      if (retCode < 0)
        return retCode;
    }
  }

  mbksPerLine = recoBuf->width/MBK_SIZE;
  mbksPerCol  = recoBuf->height/MBK_SIZE;
  picSizeInMbs = mbksPerLine*mbksPerCol;

  currMbAddr = slice->first_mb_in_slice;
  sliceGroupNum = sliceID & 0xF;

  mbIdxY = currMbAddr / mbksPerLine;
  mbIdxX = currMbAddr - mbIdxY*mbksPerLine;

  mbkSliceStart(&mb, slice->qp, pps->chroma_qp_index_offset, refPicList0, numRefFrames);

  stream = bitbuf;

  /* Loop until all macroblocks in current slice have been decoded */
  do {

    /* Store slice ID for current macroblock */
    mbData->sliceMap[currMbAddr] = sliceID;

    /* Store loopfilter mode */
    mbData->filterModeTab[currMbAddr] = (int8) slice->disable_deblocking_filter_idc;
    mbData->alphaOffset[currMbAddr]   = (int8) (slice->slice_alpha_c0_offset_div2*2);
    mbData->betaOffset[currMbAddr]    = (int8) (slice->slice_beta_offset_div2*2);

    retCode = mbkDecode(&mb, recoBuf, refPicList0, refFramesExist, numRefFrames,
                        mbData, recoBuf->width, recoBuf->height,
                        slice->slice_type, pps->constrained_intra_pred_flag,
                        pps->chroma_qp_index_offset,
                        mbIdxX, mbIdxY, stream);

#ifdef DEBUG_PRINT
    slice->intraTime += mb.intraTime;
    slice->vldTime += mb.vldTime;
    slice->interTime += mb.interTime;
    slice->codingTime += mb.codingTime;
#endif

    if (retCode < 0)
      return SLICE_ERROR;

#ifdef ERROR_CONCEALMENT
    ercDecodeMb(pEc, mbIdxX, mbIdxY);
#endif

    {
      /* If end of slice data has been reached and there are no */
      /* skipped macroblocks left, stop decoding slice.         */
      if (!bibMoreRbspData(bitbuf) && mb.numSkipped <= 0)
        break;
    }

    /* Find next mb address in the current slice group */
    do {
      /* Next mb address */
      currMbAddr++;

      /* If end of frame was reached, stop search */
      if (currMbAddr == picSizeInMbs)
        break;

      /* Update mb location */
      mbIdxX++;
      if (mbIdxX == mbksPerLine) {
        mbIdxX = 0;
        mbIdxY++;
      }
    } while ((mbData->sliceMap[currMbAddr] & 0xF) != sliceGroupNum);

    /* If end of frame was reached, stop decoding slice */
  } while (currMbAddr < picSizeInMbs);


  return SLICE_OK;
}


