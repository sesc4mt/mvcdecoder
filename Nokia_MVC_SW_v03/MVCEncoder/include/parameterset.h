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
 * parameterset.h
 *
 * Contains:
 *    Interface for parameter set.
 *
 */

#ifndef _PARAMETERSET_H_
#define _PARAMETERSET_H_

#include "bitbuffer.h"
#include "globals.h"
#include "encparams.h"
#include "rtp.h"

#define PS_BASELINE_PROFILE_IDC   66
#define PS_MAIN_PROFILE_IDC       77
#define PS_EXTENDED_PROFILE_IDC   88
#define PS_MVC_BASEVIEW           66
#define PS_MVC_HIGH               118

#define PS_EXTENDED_SAR           255

#define PS_MAX_CPB_CNT            32

/* supported by baseline profile and extended profile */
#define PS_MAX_NUM_SLICE_GROUPS   8

#define PS_MAX_NUM_REF_FRAMES_IN_PIC_ORDER_CNT_CYCLE  256

/*
 * Hypothetical reference decoder parameters
 */
typedef struct _hrd_parameters_s
{
  unsigned    cpb_cnt_minus1;                                   // ue(v)
  unsigned    bit_rate_scale;                                   // u(4)
  unsigned    cpb_size_scale;                                   // u(4)
  unsigned  bit_rate_value_minus1[PS_MAX_CPB_CNT];                   // ue(v)
  unsigned  cpb_size_value_minus1[PS_MAX_CPB_CNT];                   // ue(v)
  unsigned  cbr_flag[PS_MAX_CPB_CNT];                         // u(1)
  unsigned    initial_cpb_removal_delay_length_minus1;          // u(5)
  unsigned    cpb_removal_delay_length_minus1;                  // u(5)
  unsigned    dpb_output_delay_length_minus1;                   // u(5)
  unsigned    time_offset_length;                               // u(5)
} hrd_parameters_s;

/*
 * Video usability information
 */
typedef struct _vui_parameters_s
{
  Boolean             aspect_ratio_info_present_flag;                   // u(1)
    unsigned          aspect_ratio_idc;                                 // u(8)
      unsigned        sar_width;                                        // u(16)
      unsigned        sar_height;                                       // u(16)
  Boolean             overscan_info_present_flag;                       // u(1)
    Boolean           overscan_appropriate_flag;                        // u(1)
  Boolean             video_signal_type_present_flag;                   // u(1)
    unsigned          video_format;                                     // u(3)
    Boolean           video_full_range_flag;                            // u(1)
    Boolean           colour_description_present_flag;                  // u(1)
      unsigned        colour_primaries;                                 // u(8)
      unsigned        transfer_characteristics;                         // u(8)
      unsigned        matrix_coefficients;                              // u(8)
  Boolean             chroma_loc_info_present_flag;                     // u(1)
    unsigned          chroma_sample_loc_type_top_field;                 // ue(v)
    unsigned          chroma_sample_loc_type_bottom_field;              // ue(v)
  Boolean             timing_info_present_flag;                         // u(1)
    u_int32           num_units_in_tick;                                // u(32)
    u_int32           time_scale;                                       // u(32)
    Boolean           fixed_frame_rate_flag;                            // u(1)
  Boolean             nal_hrd_parameters_present_flag;                  // u(1)
    hrd_parameters_s  nal_hrd_parameters;                               // hrd_paramters_s
  Boolean             vcl_hrd_parameters_present_flag;                  // u(1)
    hrd_parameters_s  vcl_hrd_parameters;                               // hrd_paramters_s
  // if ((nal_hrd_parameters_present_flag || (vcl_hrd_parameters_present_flag))
    Boolean           low_delay_hrd_flag;                               // u(1)
  Boolean             pic_struct_present_flag;                          // u(1)
  Boolean             bitstream_restriction_flag;                       // u(1)
    Boolean           motion_vectors_over_pic_boundaries_flag;          // u(1)
    unsigned          max_bytes_per_pic_denom;                          // ue(v)
    unsigned          max_bits_per_mb_denom;                            // ue(v)
    unsigned          log2_max_mv_length_horizontal;                    // ue(v)
    unsigned          log2_max_mv_length_vertical;                      // ue(v)
    unsigned          num_reorder_frames;                               // ue(v)
    unsigned          max_dec_frame_buffering;                          // ue(v)
} vui_parameters_s;

/*
 * Picture parameter set
 */
typedef struct _pic_parameter_set_s
{
  Boolean       Valid;                  // indicates the parameter set is valid

  unsigned      pic_parameter_set_id;                          // ue(v)
  unsigned      seq_parameter_set_id;                          // ue(v)
  Boolean       entropy_coding_mode_flag;                      // u(1)
  Boolean       pic_order_present_flag;                        // u(1)
  unsigned      num_slice_groups_minus1;                       // ue(v)
    unsigned    slice_group_map_type;                          // ue(v)
      // if( slice_group_map_type = = 0 )
      unsigned  run_length_minus1[PS_MAX_NUM_SLICE_GROUPS];    // ue(v)
      // else if( slice_group_map_type = = 2 )
      unsigned  top_left[PS_MAX_NUM_SLICE_GROUPS];             // ue(v)
      unsigned  bottom_right[PS_MAX_NUM_SLICE_GROUPS];         // ue(v)
      // else if( slice_group_map_type = = 3 || 4 || 5
      Boolean   slice_group_change_direction_flag;             // u(1)
      unsigned  slice_group_change_rate_minus1;                // ue(v)
      // else if( slice_group_map_type = = 6 )
      unsigned  pic_size_in_map_units_minus1;                  // ue(v)
      int8      *slice_group_id;                               // complete MBAmap u(v)
  unsigned      num_ref_idx_l0_active_minus1;                  // ue(v)
  unsigned      num_ref_idx_l1_active_minus1;                  // ue(v)
  Boolean       weighted_pred_flag;                            // u(1)
  Boolean       weighted_bipred_idc;                           // u(2)
  int           pic_init_qp_minus26;                           // se(v)
  int           pic_init_qs_minus26;                           // se(v)
  int           chroma_qp_index_offset;                        // se(v)
  Boolean       deblocking_filter_parameters_present_flag;     // u(1)
  Boolean       constrained_intra_pred_flag;                   // u(1)
  Boolean       redundant_pic_cnt_present_flag;                // u(1)
} pic_parameter_set_s;

/*
 * Sequence parameter set
 */
typedef struct _seq_parameter_set_s
{
  Boolean   Valid;                  // indicates the parameter set is valid

  Boolean mvcParametersPresent;

  unsigned  profile_idc;                                      // u(8)
  Boolean   constraint_set0_flag;                             // u(1)   !!
  Boolean   constraint_set1_flag;                             // u(1)   !!
  Boolean   constraint_set2_flag;                             // u(1)   !!
  Boolean   constraint_set3_flag;                             // u(1)   !!
  Boolean   constraint_set4_flag;                             // u(1)   !!
  Boolean   reserved_zero_3bits;                              // u(3)   !!
  unsigned  level_idc;                                        // u(8)
  unsigned  seq_parameter_set_id;                             // ue(v)

  unsigned chroma_format_idc;								// ue(v)
  unsigned bitdepth_luma_minus8;							// ue(v)
  unsigned bitdepth_chroma_minus8;							// ue(v)
  Boolean qpprime_y_zero_transform_bypass_flag;				// u(1)
  Boolean seq_scaling_matrix_present_flag;					// u(1)

  unsigned  log2_max_frame_num_minus4;                        // ue(v)
  unsigned  pic_order_cnt_type;
    // if( pic_order_cnt_type == 0 ) 
    unsigned log2_max_pic_order_cnt_lsb_minus4;               // ue(v)
    // else if( pic_order_cnt_type == 1 )
    Boolean delta_pic_order_always_zero_flag;                 // u(1)
    int     offset_for_non_ref_pic;                           // se(v)
    int     offset_for_top_to_bottom_field;                   // se(v)
    unsigned  num_ref_frames_in_pic_order_cnt_cycle;          // ue(v)
      // for( i = 0; i < num_ref_frames_in_pic_order_cnt_cycle; i++ )
      int   offset_for_ref_frame[PS_MAX_NUM_REF_FRAMES_IN_PIC_ORDER_CNT_CYCLE];   // se(v)
  unsigned  num_ref_frames;                                   // ue(v)
  Boolean   gaps_in_frame_num_value_allowed_flag;             // u(1)
  unsigned  pic_width_in_mbs_minus1;                          // ue(v)
  unsigned  pic_height_in_map_units_minus1;                   // ue(v)
  Boolean   frame_mbs_only_flag;                              // u(1)
    // if( !frame_mbs_only_flag ) 
    Boolean mb_adaptive_frame_field_flag;                     // u(1)
  Boolean   direct_8x8_inference_flag;                        // u(1)
  Boolean       frame_cropping_flag;                           // u(1)
    unsigned    frame_crop_left_offset;                        // ue(v)
    unsigned    frame_crop_right_offset;                       // ue(v)
    unsigned    frame_crop_top_offset;                         // ue(v)
    unsigned    frame_crop_bottom_offset;                      // ue(v)
  Boolean   vui_parameters_present_flag;                      // u(1)
    vui_parameters_s vui_parameters;                          // vui_seq_parameters_s

  unsigned num_views_minus1;
    unsigned *view_id;
    unsigned *num_anchor_refs_l0;
	  unsigned **anchor_refs_l0;
    unsigned *num_anchor_refs_l1;
	  unsigned **anchor_refs_l1;
    unsigned *num_non_anchor_refs_l0;
	  unsigned **non_anchor_refs_l0;
    unsigned *num_non_anchor_refs_l1;
	  unsigned **non_anchor_refs_l1;
  unsigned num_level_values_signalled_minus1;
    unsigned *level_idc_mvc;
	unsigned *num_applicable_ops_minus1;
	  unsigned **applicable_op_temporal_id;
	  unsigned **applicable_op_num_target_views_minus1;
	    unsigned ***applicable_op_target_view_id;
	  unsigned **applicable_op_num_views_minus1;
} seq_parameter_set_s;

/*
 * Function prototypes
 */
void psValidateSliceParams(encParams_s *param);

int psSendSeqParameterSet(bitbuffer_s *bitbuf, 
                          seq_parameter_set_s *sps, 
                          int *bitsNal,
                          rtpPacket_s* rtpPacket);

int psSendPicParameterSet(bitbuffer_s *bitbuf, 
                          pic_parameter_set_s *pps, 
                          int *bitsNal,
                          rtpPacket_s* rtpPacket);

void psCloseSequenceParameterSet(seq_parameter_set_s *sps);

void psClosePictureParameterSet(pic_parameter_set_s *pps);

int psSendSubsetSeqParameterSet(seq_parameter_set_s *sps,
                                bitbuffer_s *bitbuf,
                                int *bitsNal,
                                rtpPacket_s* rtpPacket);

int psSendSeqParameterSetMVCExtension(seq_parameter_set_s *sps,
                                      bitbuffer_s *bitbuf);

void psFillSPSSetStructures(seq_parameter_set_s *sps,
                            encParams_s         *param,
                            int spsIndex);

void psFillPPSSetStructures(seq_parameter_set_s sps,
                            pic_parameter_set_s *pps,
                            encParams_s         *param,
                            int ppsIndex);

#endif
