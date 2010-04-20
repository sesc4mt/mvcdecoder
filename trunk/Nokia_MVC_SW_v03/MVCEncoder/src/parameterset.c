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
 * parameterset.c
 *
 * Contains:
 *    
 *
 */

#include <limits.h>
#include "nccglob.h"
#include "globals.h"
#include "debug.h"
#include "vlcutility.h"
#include "parameterset.h"


/*
 * psSendHrdParameters:
 *
 * Parameters:
 *      bitbuf                the bitbuffer object
 *      hrd                   the pointer for returning HRD parameters
 *
 * Function:
 *      encode the HRD Parameters
 *
 * Returns:
 *      the number of bits being used
 */
static int psSendHrdParameters(bitbuffer_s *bitbuf, 
                               hrd_parameters_s *hrd)
{
  unsigned int i;
  int bits;


  bits = 0;
  bits += ue_v(bitbuf, hrd->cpb_cnt_minus1);
  bits += u_n(bitbuf, hrd->bit_rate_scale, 4);
  bits += u_n(bitbuf, hrd->cpb_size_scale, 4);
  for (i = 0; i <= hrd->cpb_cnt_minus1; i++) {
    bits += ue_v(bitbuf, hrd->bit_rate_value_minus1[i]);
    bits += ue_v(bitbuf, hrd->cpb_size_value_minus1[i]);
    bits += u_n(bitbuf, hrd->cbr_flag[i], 1);
  }
  bits += u_n(bitbuf, hrd->initial_cpb_removal_delay_length_minus1, 5);
  bits += u_n(bitbuf, hrd->cpb_removal_delay_length_minus1, 5);
  bits += u_n(bitbuf, hrd->dpb_output_delay_length_minus1, 5);
  bits += u_n(bitbuf, hrd->time_offset_length, 5);

  return bits;
}


/*
 * psSendVUI:
 *
 * Parameters:
 *      bitbuf                the bitbuffer object
 *      vui                   the pointer for returning VUI parameters
 *
 * Function:
 *      encode the VUI Parameters
 *
 * Returns:
 *      the number of bits being used
 */
static int psSendVUI(bitbuffer_s *bitbuf, 
                     vui_parameters_s *vui)
{
  int bits;

  
  bits = 0;

  bits += u_n(bitbuf, vui->aspect_ratio_info_present_flag, 1);
  if (vui->aspect_ratio_info_present_flag) {
    bits += u_n(bitbuf, vui->aspect_ratio_idc, 8);
    if (vui->aspect_ratio_idc == PS_EXTENDED_SAR) {
      bits += u_n(bitbuf, vui->sar_width, 16);
      bits += u_n(bitbuf, vui->sar_height, 16);
    }
  }
  bits += u_n(bitbuf, vui->overscan_info_present_flag, 1);
  
  if (vui->overscan_info_present_flag) {
    bits += u_n(bitbuf, vui->overscan_appropriate_flag, 1);
  }
  bits += u_n(bitbuf, vui->video_signal_type_present_flag, 1);
  
  if (vui->video_signal_type_present_flag) {
    bits += u_n(bitbuf, vui->video_format, 3);
    bits += u_n(bitbuf, vui->video_full_range_flag, 1);
    bits += u_n(bitbuf, vui->colour_description_present_flag, 1);
    if (vui->colour_description_present_flag) {
      bits += u_n(bitbuf, vui->colour_primaries, 8);
      bits += u_n(bitbuf, vui->transfer_characteristics, 8);
      bits += u_n(bitbuf, vui->matrix_coefficients, 8);
    }
  }
  bits += u_n(bitbuf, vui->chroma_loc_info_present_flag, 1);
  
  if (vui->chroma_loc_info_present_flag) {
    bits += ue_v(bitbuf, vui->chroma_sample_loc_type_top_field);
    bits += ue_v(bitbuf, vui->chroma_sample_loc_type_bottom_field);
  }
  bits += u_n(bitbuf, vui->timing_info_present_flag, 1);
  
  if (vui->timing_info_present_flag) {
    bits += u_n(bitbuf, vui->num_units_in_tick, 32);
    bits += u_n(bitbuf, vui->time_scale, 32);
    bits += u_n(bitbuf, vui->fixed_frame_rate_flag, 1);
  }
  bits += u_n(bitbuf, vui->nal_hrd_parameters_present_flag, 1);
  
  if (vui->nal_hrd_parameters_present_flag) {
    //bits += psSendHrdParameters(bitbuf, &vui->nal_hrd_parameters);
	  bits += psSendHrdParameters(bitbuf, &vui->vcl_hrd_parameters);
  }
  bits += u_n(bitbuf, vui->vcl_hrd_parameters_present_flag,1);
  
  if (vui->vcl_hrd_parameters_present_flag) {
    bits += psSendHrdParameters(bitbuf, &vui->vcl_hrd_parameters);
  }
  
  if (vui->nal_hrd_parameters_present_flag || vui->vcl_hrd_parameters_present_flag) {
    bits += u_n(bitbuf, vui->low_delay_hrd_flag, 1);
  }
  bits += u_n(bitbuf, vui->pic_struct_present_flag, 1);
  bits += u_n(bitbuf, vui->bitstream_restriction_flag, 1);
  
  if (vui->bitstream_restriction_flag) {
    bits += u_n(bitbuf, vui->motion_vectors_over_pic_boundaries_flag, 1);
    bits += ue_v(bitbuf, vui->max_bytes_per_pic_denom);
    bits += ue_v(bitbuf, vui->max_bits_per_mb_denom);
    bits += ue_v(bitbuf, vui->log2_max_mv_length_horizontal);
    bits += ue_v(bitbuf, vui->log2_max_mv_length_vertical);
    bits += ue_v(bitbuf, vui->num_reorder_frames);
    bits += ue_v(bitbuf, vui->max_dec_frame_buffering);
  }
  
  return bits;
}


/* 
 * psSendSeqParameterSet
 *
 * Parameters:
 *    bitbuf            the bitbuffer object
 *    sps               the SPS object
 *    bitsNal           Pointer to counter accumulating NAL bits
 *
 * Function:
 *    Encode sequence parameter set
 *
 * Returns:
 *    the number of bits being used for encoding the SPS. Please note that the stream header
 *    and the NAL header is not taken into account.
 */
int psSendSeqParameterSet(bitbuffer_s *bitbuf, 
                          seq_parameter_set_s *sps, 
                          int *bitsNal,
                          rtpPacket_s* rtpPacket)

{
  int bits = 0;
  unsigned i;
  int currBytePos = bitbuf->bytePos;


  if(rtpPacket->use_rtp == 0)
    *bitsNal += vlcuSendNalUnitStartCodePrefix(bitbuf, 1);
  else
  {
    generateRTPHeader(bitbuf,rtpPacket); // Use the same timestamp,    
  }
   
  *bitsNal += vlcuSendNalHead(bitbuf, 1, SPS_NAL_TYPE);

  bits += u_n(bitbuf, sps->profile_idc, 8);
  bits += u_n(bitbuf, sps->constraint_set0_flag, 1);
  bits += u_n(bitbuf, sps->constraint_set1_flag, 1);
  bits += u_n(bitbuf, sps->constraint_set2_flag, 1);
  bits += u_n(bitbuf, sps->constraint_set3_flag, 1);
  bits += u_n(bitbuf, sps->constraint_set4_flag, 1);
  bits += u_n(bitbuf, sps->reserved_zero_3bits, 3);

  bits += u_n(bitbuf, sps->level_idc, 8);
  bits += ue_v(bitbuf, sps->seq_parameter_set_id);

  if ( sps->profile_idc == 100 || sps->profile_idc == 110 || sps->profile_idc == 122 || 
       sps->profile_idc == 244 || sps->profile_idc == 44 || sps->profile_idc == 83 || 
       sps->profile_idc == 86 || sps->profile_idc == 118 ) {
    bits += ue_v(bitbuf, sps->chroma_format_idc);
    bits += ue_v(bitbuf, sps->bitdepth_luma_minus8);
    bits += ue_v(bitbuf, sps->bitdepth_chroma_minus8);
    bits += u_n(bitbuf, sps->qpprime_y_zero_transform_bypass_flag, 1);
    bits += u_n(bitbuf, sps->seq_scaling_matrix_present_flag, 1);
  }

  bits += ue_v(bitbuf, sps->log2_max_frame_num_minus4);
  bits += ue_v(bitbuf, sps->pic_order_cnt_type);

  if (sps->pic_order_cnt_type == 0)
    bits += ue_v(bitbuf, sps->log2_max_pic_order_cnt_lsb_minus4);
  else if (sps->pic_order_cnt_type == 1)
  {
    bits += u_n(bitbuf, sps->delta_pic_order_always_zero_flag, 1);
    bits += se_v(bitbuf, sps->offset_for_non_ref_pic);
    bits += se_v(bitbuf, sps->offset_for_top_to_bottom_field);
    bits += ue_v(bitbuf, sps->num_ref_frames_in_pic_order_cnt_cycle);
    for (i=0; i<sps->num_ref_frames_in_pic_order_cnt_cycle; i++)
      bits += se_v(bitbuf, sps->offset_for_ref_frame[i]);
  }
  
  bits += ue_v(bitbuf, sps->num_ref_frames);
  bits += u_n(bitbuf,sps->gaps_in_frame_num_value_allowed_flag, 1);
  bits += ue_v(bitbuf, sps->pic_width_in_mbs_minus1);
  bits += ue_v(bitbuf, sps->pic_height_in_map_units_minus1);
  bits += u_n(bitbuf, sps->frame_mbs_only_flag, 1);
  
  if (sps->frame_mbs_only_flag==0)
    bits += u_n(bitbuf, sps->mb_adaptive_frame_field_flag, 1);
  bits += u_n(bitbuf, sps->direct_8x8_inference_flag, 1);
  bits += u_n( bitbuf, sps->frame_cropping_flag, 1 );
  
  if (sps->frame_cropping_flag)
  {
    bits += ue_v( bitbuf, sps->frame_crop_left_offset );
    bits += ue_v( bitbuf, sps->frame_crop_right_offset );
    bits += ue_v( bitbuf, sps->frame_crop_top_offset );
    bits += ue_v( bitbuf, sps->frame_crop_bottom_offset );
  }

  sps->vui_parameters_present_flag = 0;

  bits += u_n(bitbuf, sps->vui_parameters_present_flag, 1);
  if (sps->vui_parameters_present_flag)
    bits += psSendVUI(bitbuf, &sps->vui_parameters);

  bits += bibTrailingBits(bitbuf);

  if(rtpPacket->use_rtp == 1)
  {
    //Modify the size
    modifyRTPSize(bitbuf,bits/8 + 1,currBytePos);
  }

  return bits;
}


/* 
 * psSendPicParameterSet
 *
 * Parameters:
 *    bitbuf            the bitbuffer object
 *    pps               the PPS object
 *    bitsNal           Pointer to counter accumulating NAL bits
 *
 * Function:
 *    Encode the picture parameter set
 *
 * Returns:
 *    the number of bits being used for encoding the PPS. Please note that the stream header
 *    and the NAL header is not taken into account.
 */
int psSendPicParameterSet(bitbuffer_s *bitbuf, 
                          pic_parameter_set_s *pps, 
                          int *bitsNal,
                          rtpPacket_s* rtpPacket)
{
  int bits = 0, tmp;
  unsigned i, len;
  int currBytePos = bitbuf->bytePos;


  if(rtpPacket->use_rtp == 0)
    *bitsNal += vlcuSendNalUnitStartCodePrefix(bitbuf, 1);
  else
  {
    
    generateRTPHeader(bitbuf,rtpPacket); //Use the same timestamp, 
  }
  
  *bitsNal += vlcuSendNalHead(bitbuf, 1, PPS_NAL_TYPE);

  bits += ue_v( bitbuf, pps->pic_parameter_set_id);
  bits += ue_v( bitbuf, pps->seq_parameter_set_id);
  bits += u_n( bitbuf, pps->entropy_coding_mode_flag, 1 );
  bits += u_n( bitbuf, pps->pic_order_present_flag, 1 );
  bits += ue_v( bitbuf, pps->num_slice_groups_minus1 );

  if(pps->num_slice_groups_minus1 > 0 )
  {
    bits += ue_v( bitbuf, pps->slice_group_map_type);
    if (pps->slice_group_map_type == 0)
      for (i=0; i<=pps->num_slice_groups_minus1; i++)
        bits += ue_v( bitbuf, pps->run_length_minus1[i] );
    else if (pps->slice_group_map_type==2)
      for (i=0; i<pps->num_slice_groups_minus1; i++)
      {
        bits += ue_v( bitbuf, pps->top_left[i]);
        bits += ue_v( bitbuf, pps->bottom_right[i]);
      }
    else if (pps->slice_group_map_type == 3 ||
             pps->slice_group_map_type == 4 ||
             pps->slice_group_map_type == 5) 
    {
      bits += u_n( bitbuf, pps->slice_group_change_direction_flag, 1);
      bits += ue_v( bitbuf, pps->slice_group_change_rate_minus1);
    } 
    else if (pps->slice_group_map_type == 6)
    {
      bits += ue_v( bitbuf, pps->pic_size_in_map_units_minus1 );

      // Calculate len = Ceil( Log2( num_slice_groups_minus1 + 1 ) )
      tmp = pps->num_slice_groups_minus1 + 1;
      tmp = tmp >> 1;
      for( len = 0; len < 16 && tmp != 0; len++ )
        tmp >>= 1;
      if ( (((unsigned)1)<<len) < (pps->num_slice_groups_minus1 + 1) )
        len++;
      
      for( i = 0; i <= pps->pic_size_in_map_units_minus1; i++ )
        bits += u_n( bitbuf, (int) pps->slice_group_id[i], len ); // DT: check
    }
  }

  bits += ue_v( bitbuf, pps->num_ref_idx_l0_active_minus1 );
  bits += ue_v( bitbuf, pps->num_ref_idx_l1_active_minus1 );
  bits += u_n( bitbuf, pps->weighted_pred_flag, 1);
  bits += u_n( bitbuf, pps->weighted_bipred_idc, 2);
  bits += se_v( bitbuf, pps->pic_init_qp_minus26 );
  bits += se_v( bitbuf, pps->pic_init_qs_minus26 );
  bits += se_v( bitbuf, pps->chroma_qp_index_offset );
  bits += u_n( bitbuf, pps->deblocking_filter_parameters_present_flag, 1 );
  bits += u_n( bitbuf, pps->constrained_intra_pred_flag, 1 );
  bits += u_n( bitbuf, pps->redundant_pic_cnt_present_flag, 1 );

  bits += bibTrailingBits(bitbuf);

  if(rtpPacket->use_rtp == 1)
  {
    //Modify the size
    modifyRTPSize(bitbuf,bits/8+ 1,currBytePos);
  }

  return bits;
}


/*
 * psValidateSliceParams:
 *
 * Parameters:
 *      param                 Encoding parameters
 *      
 * Function:
 *      Validate the slice related members in encParams_s structure.
 *
 * Returns:
 *      -
 */
void psValidateSliceParams(encParams_s *param)
{
  int i;
  int widthMb, heightMb, totalMbs;


  widthMb  = param->picWidth/16;
  heightMb = param->picHeight/16;
  totalMbs = widthMb * heightMb;

  param->sgmType  = clip(0, 6, param->sgmType);
  param->sgmCount = clip(1, 8, param->sgmCount);
  if (param->sgmCount > 1) {
    if (param->sgmType == SLICE_MAP_INTERLEAVED) {
      int totalMbsThisType;

      // numSgmParams has run-length, # of parameters should match sgmCount
      param->sgmCount = min(param->sgmCount, param->numSgmParams);
      for (totalMbsThisType = 0, i = 0; i < param->sgmCount; i ++) {
        param->sgmParams[i] = clip(1, totalMbs, param->sgmParams[i]);
        totalMbsThisType += param->sgmParams[i];
      }
      if (totalMbsThisType >= totalMbs)
        param->sgmCount = 1;
    }
    else if (param->sgmType == SLICE_MAP_FOREGROUND)
    {
      param->sgmCount = min(param->sgmCount, param->numSgmParams/2 + 1);

      // the last slice is the background
      for (i = 0; i < param->sgmCount - 1; i ++) {
        int mbX0, mbY0, mbX1, mbY1;

        if ((param->sgmParams[2 * i] >= totalMbs) ||
          (param->sgmParams[2 * i + 1] >= totalMbs))
          break;

        // the rectangles should be correctly defined
        mbX0 = param->sgmParams[2 * i] % widthMb;
        mbY0 = param->sgmParams[2 * i] / widthMb;
        mbX1 = param->sgmParams[2 * i + 1] % widthMb;
        mbY1 = param->sgmParams[2 * i + 1] / widthMb;

        if ((mbX0 > mbX1) || (mbY0 > mbY1))
          break;
      }

      param->sgmCount = ((i > 0) ? i : 0) + 1;
    }
    else if ((param->sgmType >= SLICE_MAP_BOX_OUT) && 
      (param->sgmType <= SLICE_MAP_WIPE))
    {
      if (param->numSgmParams < 2)
      {
        param->sgmParams[0] = 0;     // slice_group_change_direction_flag
        param->sgmParams[1] = 4;     // slice_group_change_rate_minus1
      }
      else
      {
        param->sgmParams[0] = clip(0, 1, param->sgmParams[0]);
        param->sgmParams[1] = clip(1, totalMbs, param->sgmParams[1]);
      }
    }
  }
}


/*
 * psCloseSequenceParameterSet:
 *      free the sequence parameter set
 *
 * Parameters:
 *      sps                   the sequence parameter set to be freed
 *
 * Returns:
 *      -
 */
void psCloseSequenceParameterSet(seq_parameter_set_s *sps)
{
  int i, j;
  int numViews = sps->num_views_minus1 + 1;
  int numLevels = sps->num_level_values_signalled_minus1 + 1;
  int numOps;

  
  if(sps->mvcParametersPresent) {

    for (i=0; i<numViews-1; i++) {
      nccFree(sps->anchor_refs_l0[i]);
      nccFree(sps->anchor_refs_l1[i]);
      nccFree(sps->non_anchor_refs_l0[i]);
      nccFree(sps->non_anchor_refs_l1[i]);
    }

    nccFree(sps->view_id);
    nccFree(sps->num_anchor_refs_l0);
    nccFree(sps->num_anchor_refs_l1);
    nccFree(sps->num_non_anchor_refs_l0);
    nccFree(sps->num_non_anchor_refs_l1);
    nccFree(sps->anchor_refs_l0);
    nccFree(sps->anchor_refs_l1);
    nccFree(sps->non_anchor_refs_l0);
    nccFree(sps->non_anchor_refs_l1);
  
    for( i=0; i<numLevels; i++ ) {
      nccFree(sps->applicable_op_temporal_id[i]);
      nccFree(sps->applicable_op_num_target_views_minus1[i]);
      nccFree(sps->applicable_op_num_views_minus1[i]);
      
      numOps = sps->num_applicable_ops_minus1[i];

      for( j=0; j<=numOps; j++ ) {
        nccFree(sps->applicable_op_target_view_id[i][j]);
      }
      
      nccFree(sps->applicable_op_target_view_id[i]);
    }
    
    nccFree(sps->num_applicable_ops_minus1);
    nccFree(sps->level_idc_mvc);
    nccFree(sps->applicable_op_temporal_id);
    nccFree(sps->applicable_op_num_target_views_minus1);
    nccFree(sps->applicable_op_target_view_id);
    nccFree(sps->applicable_op_num_views_minus1);
  }
}


/*
 * psClosePictureParameterSet:
 *      free the picture parameter set
 *
 * Parameters:
 *      pps                   the picture parameter set to be freed
 *
 * Returns:
 *      -
 */
void psClosePictureParameterSet(pic_parameter_set_s *pps)
{
  if (pps->num_slice_groups_minus1 > 0 && pps->slice_group_map_type == 6)
    nccFree(pps->slice_group_id);
}


/* 
 * psSendSubsetSeqParameterSet
 *
 * Parameters:
 *    sps               the SPS object
 *    bitbuf            the bitbuffer object
 *    bitsNal           Pointer to counter accumulating NAL bits
 *
 * Function:
 *    Encode the subset sequence parameter set
 *
 * Returns:
 *    the number of bits being used for encoding the Subset SPS. Please note that the stream header
 *    and the NAL header is not taken into account.
 */
int psSendSubsetSeqParameterSet(seq_parameter_set_s *sps,
                								bitbuffer_s *bitbuf,
                                int *bitsNal,
                                rtpPacket_s* rtpPacket)
{
  int bits = 0;
  unsigned i;
  int currBytePos = bitbuf->bytePos;


  if(rtpPacket->use_rtp == 0)
    *bitsNal += vlcuSendNalUnitStartCodePrefix(bitbuf, 1);
  else
  {
    generateRTPHeader(bitbuf,rtpPacket); // Use the same timestamp,    
  }
   
  *bitsNal += vlcuSendNalHead(bitbuf, 1, SUBSET_SPS_TYPE);
  
  /* The SPS part */
  bits += u_n(bitbuf, sps->profile_idc, 8);	
  bits += u_n(bitbuf, sps->constraint_set0_flag, 1);
  bits += u_n(bitbuf, sps->constraint_set1_flag, 1);
  bits += u_n(bitbuf, sps->constraint_set2_flag, 1);
  bits += u_n(bitbuf, sps->constraint_set3_flag, 1);
  bits += u_n(bitbuf, sps->constraint_set4_flag, 1);
  bits += u_n(bitbuf, sps->reserved_zero_3bits, 3);
  bits += u_n(bitbuf, sps->level_idc, 8);

  bits += ue_v(bitbuf, sps->seq_parameter_set_id);

  bits += ue_v(bitbuf, sps->chroma_format_idc);
  bits += ue_v(bitbuf, sps->bitdepth_luma_minus8);
  bits += ue_v(bitbuf, sps->bitdepth_chroma_minus8);
  bits += u_n(bitbuf, sps->qpprime_y_zero_transform_bypass_flag, 1);
  bits += u_n(bitbuf, sps->seq_scaling_matrix_present_flag, 1);

  bits += ue_v(bitbuf, sps->log2_max_frame_num_minus4);
  bits += ue_v(bitbuf, sps->pic_order_cnt_type);

  if (sps->pic_order_cnt_type == 0)
    bits += ue_v(bitbuf, sps->log2_max_pic_order_cnt_lsb_minus4);
  else if (sps->pic_order_cnt_type == 1)
  {
    bits += u_n(bitbuf, sps->delta_pic_order_always_zero_flag, 1);
    bits += se_v(bitbuf, sps->offset_for_non_ref_pic);
    bits += se_v(bitbuf, sps->offset_for_top_to_bottom_field);
    bits += ue_v(bitbuf, sps->num_ref_frames_in_pic_order_cnt_cycle);
    for (i=0; i<sps->num_ref_frames_in_pic_order_cnt_cycle; i++)
      bits += se_v(bitbuf, sps->offset_for_ref_frame[i]);
  }

  bits += ue_v(bitbuf, sps->num_ref_frames);
  bits += u_n(bitbuf,sps->gaps_in_frame_num_value_allowed_flag, 1);
  bits += ue_v(bitbuf, sps->pic_width_in_mbs_minus1);
  bits += ue_v(bitbuf, sps->pic_height_in_map_units_minus1);
  bits += u_n(bitbuf, sps->frame_mbs_only_flag, 1);
  
  if (sps->frame_mbs_only_flag==0)
    bits += u_n(bitbuf, sps->mb_adaptive_frame_field_flag, 1);
  bits += u_n(bitbuf, sps->direct_8x8_inference_flag, 1);
  bits += u_n( bitbuf, sps->frame_cropping_flag, 1 );
  
  if (sps->frame_cropping_flag)
  {
    bits += ue_v( bitbuf, sps->frame_crop_left_offset );
    bits += ue_v( bitbuf, sps->frame_crop_right_offset );
    bits += ue_v( bitbuf, sps->frame_crop_top_offset );
    bits += ue_v( bitbuf, sps->frame_crop_bottom_offset );
  }

  sps->vui_parameters_present_flag = 0;

  bits += u_n(bitbuf, sps->vui_parameters_present_flag, 1);
  if (sps->vui_parameters_present_flag)
    bits += psSendVUI(bitbuf, &sps->vui_parameters);

  /* The Subset SPS part */
  /* Send bit equal to one */
  bits += u_n(bitbuf, 1, 1);

  bits += psSendSeqParameterSetMVCExtension(sps, bitbuf);

  /* No MVC VUI (at the moment) */
  bits += u_n(bitbuf, 0, 1);

  /* No additional extension2 data */
  bits += u_n(bitbuf, 0, 1);

  bits += bibTrailingBits(bitbuf);

  if(rtpPacket->use_rtp == 1)
  {
    //Modify the size
    modifyRTPSize(bitbuf,bits/8+ 1,currBytePos);
  }

  return bits;
}


/* 
 * psSendSeqParameterSetMVCExtension
 *
 * Parameters:
 *    sps               the SPS object
 *    bitbuf            the bitbuffer object
 *
 * Function:
 *    Encode the subset sequence parameter set MVC extension
 *
 * Returns:
 *    the number of bits being used for encoding the Subset SPS. Please note that the stream header
 *    and the NAL header is not taken into account.
 */
int psSendSeqParameterSetMVCExtension(seq_parameter_set_s *sps,
                                      bitbuffer_s *bitbuf)
{
  int bits = 0;
  unsigned i, j, k;


  bits += ue_v(bitbuf, sps->num_views_minus1);
  
  for( i=0; i<=sps->num_views_minus1; i++) {
    bits += ue_v(bitbuf, sps->view_id[i]);
  }
  
  for( i=0; i<sps->num_views_minus1; i++) {
    bits += ue_v(bitbuf, sps->num_anchor_refs_l0[i]);

    for( j=0; j<sps->num_anchor_refs_l0[i]; j++) {
      bits += ue_v(bitbuf, sps->anchor_refs_l0[i][j]);
    }
    
    bits += ue_v(bitbuf, sps->num_anchor_refs_l1[i]);
    
    for( j=0; j<sps->num_anchor_refs_l1[i]; j++) {
      bits += ue_v(bitbuf, sps->anchor_refs_l1[i][j]);
    }
  }
  
  for( i=0; i<sps->num_views_minus1; i++) {
    bits += ue_v(bitbuf, sps->num_non_anchor_refs_l0[i]);
    
    for( j=0; j<sps->num_non_anchor_refs_l0[i]; j++) {
      bits += ue_v(bitbuf, sps->non_anchor_refs_l0[i][j]);
    }
    
    bits += ue_v(bitbuf, sps->num_non_anchor_refs_l1[i]);
    
    for( j=0; j<sps->num_non_anchor_refs_l1[i]; j++) {
      bits += ue_v(bitbuf, sps->non_anchor_refs_l1[i][j]);
    }
  }
  
  bits += ue_v(bitbuf, sps->num_level_values_signalled_minus1);
  
  for( i=0; i<=sps->num_level_values_signalled_minus1; i++) {
    
    bits += u_n(bitbuf, sps->level_idc_mvc[i], 8);
    bits += ue_v(bitbuf, sps->num_applicable_ops_minus1[i]);
    
    for( j=0; j<=sps->num_applicable_ops_minus1[i]; j++) {
      bits += u_n(bitbuf, sps->applicable_op_temporal_id[i][j], 3);
      bits += ue_v(bitbuf, sps->applicable_op_num_target_views_minus1[i][j]);
      
      for( k=0; k<=sps->applicable_op_num_target_views_minus1[i][j]; k++) {
        bits += ue_v(bitbuf, sps->applicable_op_target_view_id[i][j][k]);
      }
      
      bits += ue_v(bitbuf, sps->applicable_op_num_views_minus1[i][j]);
    }
  }
  
  return bits;
}


/*
 * psFillSPSSetStructures:
 *
 * Parameters:
 *      sps                   Sequence parameter set
 *      param                 Encoding parameters
 *      spsIndex              Index (and id) of the current SPS set
 *      
 * Function:
 *      Generates sequence parameter set structures (and subset SPS sets).
 *      Many values are current hard-coded to defaults.
 *
 * Returns:
 *      -
 */
void psFillSPSSetStructures(seq_parameter_set_s *sps,
                            encParams_s         *param,
							              int spsIndex)
{
  int i;
  unsigned int j, k;
  vui_parameters_s    *vui;
  int numViews = NUM_VIEWS;		/* NUM_VIEWS is 2 for now */
  int numLevels;


  /* First SPS is for the base view, no MVC parameters there */
  if(spsIndex == 0)
    sps->mvcParametersPresent = 0;
  else
    sps->mvcParametersPresent = 1;
  
  sps->level_idc   = param->level;
  if(sps->level_idc == 11 && param->brcBitRate >= 64000)
    sps->constraint_set3_flag = 1;
  else
    sps->constraint_set3_flag = 0;
  
  sps->constraint_set0_flag = 0;
  sps->constraint_set1_flag = 0;
  sps->constraint_set2_flag = 0;
  sps->constraint_set4_flag = 0;    
  
  /* For the base view, use profile_idc 100, for others use 118 */
  if(spsIndex == 0) {
    sps->profile_idc          = PS_MVC_BASEVIEW;
    sps->constraint_set1_flag = 1;
  }
  else
    sps->profile_idc          = PS_MVC_HIGH;
  
  sps->reserved_zero_3bits  = 0;
  
  /* Parameter set id */
  sps->seq_parameter_set_id = spsIndex;
  
  /* These are required for the MVC profiles */
  sps->chroma_format_idc = 1;
  sps->bitdepth_luma_minus8 = 0;
  sps->bitdepth_chroma_minus8 = 0;
  sps->qpprime_y_zero_transform_bypass_flag = 0;
  sps->seq_scaling_matrix_present_flag = 0;
  
  /* POC stuff: */
  sps->log2_max_frame_num_minus4 = param->log2_max_frame_num_minus4;
  
  if (param->numReorderFrames != 0)
    sps->pic_order_cnt_type = 0;
  else
    sps->pic_order_cnt_type = 2;
  
  if (sps->pic_order_cnt_type == 0) {
    sps->log2_max_pic_order_cnt_lsb_minus4 = 
      param->log2_max_pic_order_cnt_lsb_minus4;
  }
  else if (sps->pic_order_cnt_type == 1) {
    /* The parameters are hard coded */
    sps->delta_pic_order_always_zero_flag = 1;
    sps->offset_for_non_ref_pic = 0;
    sps->offset_for_top_to_bottom_field = 0;
    sps->num_ref_frames_in_pic_order_cnt_cycle = 1;
    sps->offset_for_ref_frame[0] = param->offsetForRefFrame;
  }
  /* End of POC stuff */
  
  sps->num_ref_frames = param->maxNumRefFrms;
  sps->gaps_in_frame_num_value_allowed_flag = 0;
  sps->frame_mbs_only_flag = 1;
  
  /* Picture size */
  sps->pic_width_in_mbs_minus1 = (param->picWidth/16) -1;
  sps->pic_height_in_map_units_minus1 = 
    ((param->picHeight/16)/ (2 - sps->frame_mbs_only_flag)) - 1;
  
  /* We don't use interlace, put 0 here */
  sps->mb_adaptive_frame_field_flag = 0;
  /* Has no meaning for Baseline, must be 1 for some Main Profile levels */
  sps->direct_8x8_inference_flag = 1;  
  
  sps->frame_cropping_flag = 0;
  if ((param->cropOffsets[0] > 0) || (param->cropOffsets[1] > 0) || 
    (param->cropOffsets[2] > 0) || (param->cropOffsets[3] > 0))
  {
    sps->frame_cropping_flag = 1;
    sps->frame_crop_left_offset = param->cropOffsets[0] >> 1;
    sps->frame_crop_right_offset = param->cropOffsets[1] >> 1;
    sps->frame_crop_top_offset = param->cropOffsets[2] >> 1;
    sps->frame_crop_bottom_offset = param->cropOffsets[3] >> 1;
  }
  
  /* Only the first SPS, base view, contains VUI parameters */
  if(spsIndex == 0) {

    sps->vui_parameters_present_flag = 1;
    
    // *************************************************************************
    // VUI parameters: Set the default values here
    // *************************************************************************
    vui = &sps->vui_parameters;
    
    vui->aspect_ratio_info_present_flag = 0;
    vui->overscan_info_present_flag = 0;
    vui->video_signal_type_present_flag = 0;
    vui->chroma_loc_info_present_flag = 0;
    vui->timing_info_present_flag = 0;
    
    if(param->useSEIMessages)
      vui->nal_hrd_parameters_present_flag = 1;
    else
      vui->nal_hrd_parameters_present_flag = 0;
    
    if(param->useSEIMessages)
      vui->vcl_hrd_parameters_present_flag = 1;
    else
      vui->vcl_hrd_parameters_present_flag = 0;
    
    vui->pic_struct_present_flag = 0;
    
    /* Write bitstream restriction parameters (mainly to restrict DPB size) */
    vui->bitstream_restriction_flag = 1;
    vui->motion_vectors_over_pic_boundaries_flag = 1;
    vui->max_bytes_per_pic_denom = 0;
    vui->max_bits_per_mb_denom = 0;
    vui->log2_max_mv_length_horizontal = 12; /* max. mv horizontal component is [-4096, 4095] */
    vui->log2_max_mv_length_vertical   = 12; /* max. mv vertical component is [-4096, 4095] */
    vui->num_reorder_frames = param->numReorderFrames;
    vui->max_dec_frame_buffering = param->maxNumRefFrms;  /* Set DPB size */
  }
  else
    sps->vui_parameters_present_flag = 0;
  
  /* MVC related attributes */
  if(sps->mvcParametersPresent) {
    
    sps->num_views_minus1 = numViews-1;
    sps->view_id = (unsigned *)
      nccMalloc((numViews) * sizeof(unsigned));
    
    for( i=0; i<numViews; i++ ) {
      sps->view_id[i] = i;	 
    }
  
    sps->num_anchor_refs_l0 = (unsigned *)
      nccMalloc((numViews) * sizeof(unsigned));
    sps->num_anchor_refs_l1 = (unsigned *)
      nccMalloc((numViews) * sizeof(unsigned));
    sps->num_non_anchor_refs_l0 = (unsigned *)
      nccMalloc((numViews) * sizeof(unsigned));
    sps->num_non_anchor_refs_l1 = (unsigned *)
      nccMalloc((numViews) * sizeof(unsigned));
    sps->anchor_refs_l0 = (unsigned **)
      nccMalloc((numViews-1) * sizeof(unsigned *));
    sps->anchor_refs_l1 = (unsigned **)
      nccMalloc((numViews-1) * sizeof(unsigned *));
    sps->non_anchor_refs_l0 = (unsigned **)
      nccMalloc((numViews-1) * sizeof(unsigned *));
    sps->non_anchor_refs_l1 = (unsigned **)
      nccMalloc((numViews-1) * sizeof(unsigned *));
    
    for( i=0; i<numViews-1; i++ ) {
      sps->anchor_refs_l0[i] = (unsigned *)
        nccMalloc((numViews-1) * sizeof(unsigned));
      sps->anchor_refs_l1[i] = (unsigned *)
        nccMalloc((numViews-1) * sizeof(unsigned));
      sps->non_anchor_refs_l0[i] = (unsigned *)
        nccMalloc((numViews-1) * sizeof(unsigned));
      sps->non_anchor_refs_l1[i] = (unsigned *)
        nccMalloc((numViews-1) * sizeof(unsigned));
      
      sps->num_anchor_refs_l0[i] = 1;
      sps->num_anchor_refs_l1[i] = 0;
      sps->num_non_anchor_refs_l0[i] = 1;
      sps->num_non_anchor_refs_l1[i] = 0;
      
      /* All references are to the base view currently, i.e. set all refs to zero */
      for(j=0; j<sps->num_anchor_refs_l0[i]; j++) {
        sps->anchor_refs_l0[i][j] = 0;
      }
      for(j=0; j<sps->num_anchor_refs_l1[i]; j++) {
        sps->anchor_refs_l1[i][j] = 0;
      }
      for(j=0; j<sps->num_non_anchor_refs_l0[i]; j++) {
        sps->non_anchor_refs_l0[i][j] = 0;
      }
      for( j=0; j<sps->num_non_anchor_refs_l1[i]; j++ ) {
        sps->non_anchor_refs_l1[i][j] = 0;
      }
    }
    
    /* Signal only one level */
    sps->num_level_values_signalled_minus1 = 0;	
    numLevels = sps->num_level_values_signalled_minus1 + 1;
    
    sps->num_applicable_ops_minus1 = (unsigned *)
      nccMalloc((numLevels) * sizeof(unsigned));
    
    sps->level_idc_mvc = (unsigned *)
      nccMalloc((numLevels) * sizeof(unsigned));
    
    sps->applicable_op_temporal_id = (unsigned **)
      nccMalloc((numLevels) * sizeof(unsigned *));
    
    sps->applicable_op_num_target_views_minus1 = (unsigned **)
      nccMalloc((numLevels) * sizeof(unsigned *));
    
    sps->applicable_op_target_view_id = (unsigned ***)
      nccMalloc((numLevels) * sizeof(unsigned **));
    
    sps->applicable_op_num_views_minus1 = (unsigned **)
      nccMalloc((numLevels) * sizeof(unsigned *));
    
    for( i=0; i<numLevels; i++ ) {
      sps->num_applicable_ops_minus1[i] = 0;
      sps->level_idc_mvc[i] = i+1;		/* Set as 1 for now (we have only one level signaled) */
      
      sps->applicable_op_temporal_id[i] = (unsigned *)
        nccMalloc((sps->num_applicable_ops_minus1[i]+1) * sizeof(unsigned));
      sps->applicable_op_num_target_views_minus1[i] = (unsigned *)
        nccMalloc((sps->num_applicable_ops_minus1[i]+1) * sizeof(unsigned));
      
      sps->applicable_op_target_view_id[i] = (unsigned **)
        nccMalloc((sps->num_applicable_ops_minus1[i]+1) * sizeof(unsigned *));
      
      sps->applicable_op_num_views_minus1[i] = (unsigned *)
        nccMalloc((sps->num_applicable_ops_minus1[i]+1) * sizeof(unsigned));
      
      for( j=0; j<=sps->num_applicable_ops_minus1[i]; j++ ) {
        sps->applicable_op_temporal_id[i][j] = 0;
        sps->applicable_op_num_target_views_minus1[i][j] = 1;		// Two target views
        
        sps->applicable_op_target_view_id[i][j] = (unsigned *)
          nccMalloc((sps->applicable_op_num_target_views_minus1[i][j] + 1) * sizeof(unsigned));
        
        for( k=0; k<=sps->applicable_op_num_target_views_minus1[i][j]; k++ )
        {
          sps->applicable_op_target_view_id[i][j][k] = k;		// Set as 0, 1 for now
        }
        
        sps->applicable_op_num_views_minus1[i][j] = 0;
      }
    }
  }
}



/*
 * psFillPPSSetStructures:
 *
 * Parameters:
 *      pps                   Picture parameter set
 *      param                 Encoding parameters
 *      ppsIndex              Index (and id) of the current PPS set
 *      
 * Function:
 *      Generates picture parameter set structures.
 *      Many values are current hard-coded to defaults.
 *
 * Returns:
 *      -
 */
void psFillPPSSetStructures(seq_parameter_set_s sps,
              							pic_parameter_set_s *pps,
                            encParams_s         *param,
							              int ppsIndex)
{
  int i;


  /* Each PPS point to a separate SPS (with the same index, i.e. PPS0->SPS0, ...) */
  pps->seq_parameter_set_id = ppsIndex;
  pps->pic_parameter_set_id = ppsIndex;
  pps->entropy_coding_mode_flag = 0;

  pps->pic_order_present_flag = 0;    /* Always be zero, because no bottom field POC is needed */

  pps->num_slice_groups_minus1 = param->sgmCount - 1;
  pps->slice_group_map_type    = param->sgmType;

  if (pps->num_slice_groups_minus1 > 0) {
    if (pps->slice_group_map_type == SLICE_MAP_INTERLEAVED) {
      // interleaved, run-length
      for (i = 0; i < param->sgmCount; i ++)
        pps->run_length_minus1[i] = param->sgmParams[i] - 1;
    }
    // dispersed, no parameter needed
    else if (pps->slice_group_map_type == SLICE_MAP_FOREGROUND) {
      for (i = 0; i < param->sgmCount; i ++) {
        pps->top_left[i]     = param->sgmParams[2 * i];
        pps->bottom_right[i] = param->sgmParams[2 * i + 1];
      }
    }
    else if ((pps->slice_group_map_type >= SLICE_MAP_BOX_OUT) && 
      (pps->slice_group_map_type <= SLICE_MAP_WIPE)) {
      pps->slice_group_change_direction_flag = param->sgmParams[0];
      pps->slice_group_change_rate_minus1    = param->sgmParams[1] - 1;
    }
    else if (pps->slice_group_map_type == SLICE_MAP_BITMAP) {
      pps->pic_size_in_map_units_minus1 = (sps.pic_width_in_mbs_minus1 + 1) *
        (sps.pic_height_in_map_units_minus1 + 1) - 1;

      pps->slice_group_id = (int8 *)
        nccMalloc((pps->pic_size_in_map_units_minus1 + 1) * sizeof(int8));

      for (i = 0; i < (int) pps->pic_size_in_map_units_minus1; i++)
        pps->slice_group_id[i] = (int8) (i % (pps->num_slice_groups_minus1 + 1));
    }
  }

  pps->num_ref_idx_l0_active_minus1 = max(0, param->maxNumRefFrms - 1);
  pps->num_ref_idx_l1_active_minus1 = 0;
  
  pps->weighted_pred_flag = 0;
  pps->weighted_bipred_idc = 0;

  pps->pic_init_qp_minus26 = param->qpInter - 26;
  pps->pic_init_qs_minus26 = 0;

  pps->chroma_qp_index_offset = param->chromaQpIdx;

  if (param->filterMode == 0 && param->alphaOffset == 0 && param->betaOffset == 0)
    pps->deblocking_filter_parameters_present_flag = 0;
  else
    pps->deblocking_filter_parameters_present_flag = 1;

  pps->constrained_intra_pred_flag = param->constIpred;
  
  if (param->redundantPicFlag)
    pps->redundant_pic_cnt_present_flag = 1;
  else
    pps->redundant_pic_cnt_present_flag = 0;
}





