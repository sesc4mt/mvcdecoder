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

#include <string.h>
#include <stdio.h>
#include "nccglob.h"
#include "globals.h"
#include "vld.h"
#include "parameterset.h"
#include "avcdecoder.h"

#define MIN_CHROMA_QP_INDEX           -12
#define MAX_CHROMA_QP_INDEX            12
#define NUM_LEVELS                     16     /* The number of AVC levels */
#define MAX_PIC_SIZE_IN_MBS            36864
#define MAX_PIC_WIDTH_IN_MBS           543    /* Sqrt( MAX_PIC_SIZE_IN_MBS * 8 ) */
#define MAX_PIC_HEIGHT_IN_MBS          543    /* Sqrt( MAX_PIC_SIZE_IN_MBS * 8 ) */


/* These fields are defined in Annex A of the standard */
typedef struct _level_s {
  int8 levelNumber;
  int8 constraintSet3flag;
  int32 maxMBPS;
  int32 maxFS;
  int32 maxDPB;
  int32 maxBR;
  int32 maxCPB;
  int16 maxVmvR;
  int8 minCR;
  int8 maxMvsPer2Mb;
} level_s;


/* Parameters for all levels */
static const level_s levelArray[NUM_LEVELS] = {
  {10, 0,   1485,    99,   152064,     64,    175,  64, 2, 32},
  {11, 1,   1485,    99,   152064,    128,    350,  64, 2, 32}, /* level 1b */
  {11, 0,   3000,   396,   345600,    192,    500, 128, 2, 32},
  {12, 0,   6000,   396,   912384,    384,   1000, 128, 2, 32},
  {13, 0,  11880,   396,   912384,    768,   2000, 128, 2, 32},
  {20, 0,  11880,   396,   912384,   2000,   2000, 128, 2, 32},
  {21, 0,  19800,   792,  1824768,   4000,   4000, 256, 2, 32},
  {22, 0,  20250,  1620,  3110400,   4000,   4000, 256, 2, 32},
  {30, 0,  40500,  1620,  3110400,  10000,  10000, 256, 2, 32},
  {31, 0, 108000,  3600,  6912000,  14000,  14000, 512, 4, 16},
  {32, 0, 216000,  5120,  7864320,  20000,  20000, 512, 4, 16},
  {40, 0, 245760,  8192, 12582912,  20000,  25000, 512, 4, 16},
  {41, 0, 245760,  8192, 12582912,  50000,  62500, 512, 2, 16},
  {42, 0, 491520,  8192, 12582912,  50000,  62500, 512, 2, 16},
  {50, 0, 589824, 22080, 42393600, 135000, 135000, 512, 2, 16},
  {51, 0, 983040, 36864, 70778880, 240000, 240000, 512, 2, 16}
};


struct aspectRatio_s {
  int width;
  int height;
};


static const struct aspectRatio_s aspectRatioArr[13] = {
  {  1,  1},
  { 12, 11},
  { 10, 11},
  { 16, 11},
  { 40, 33},
  { 24, 11},
  { 20, 11},
  { 32, 11},
  { 80, 33},
  { 18, 11},
  { 15, 11},
  { 64, 33},
  {160, 99}
};


/*
 * AVC syntax functions as specified in specification
 */

/* Return fixed length code */
static int u_n(bitbuffer_s *bitbuf, int len, unsigned int *val)
{
  *val = vldGetFLC(bitbuf, len);

  if (bibGetStatus(bitbuf) < 0)
    return PS_ERROR;

  return PS_OK;
}


/* Return unsigned UVLC code */
static int ue_v(bitbuffer_s *bitbuf, unsigned int *val, unsigned int maxVal)
{
  *val = vldGetUVLC(bitbuf);

  if (bibGetStatus(bitbuf) < 0)
    return PS_ERROR;

  if (*val > maxVal)
    return PS_ERR_ILLEGAL_VALUE;

  return PS_OK;
}


/* Return long unsigned UVLC code */
static int ue_v_long(bitbuffer_s *bitbuf, u_int32 *val, u_int32 maxVal)
{
  *val = vldGetUVLClong(bitbuf);

  if (bibGetStatus(bitbuf) < 0)
    return PS_ERROR;

  if (*val > maxVal)
    return PS_ERR_ILLEGAL_VALUE;

  return PS_OK;
}


/* Return signed UVLC code */
static int se_v(bitbuffer_s *bitbuf, int *val, int minVal, int maxVal)
{
  *val = vldGetSignedUVLC(bitbuf);

  if (bibGetStatus(bitbuf) < 0)
    return PS_ERROR;

  if (*val < minVal || *val > maxVal)
    return PS_ERR_ILLEGAL_VALUE;

  return PS_OK;
}


/* Return long signed UVLC code */
static int se_v_long(bitbuffer_s *bitbuf, int32 *val)
{
  *val = vldGetSignedUVLClong(bitbuf);

  if (bibGetStatus(bitbuf) < 0)
    return PS_ERROR;

  return PS_OK;
}


/*
 *
 * psClosePPS:
 *
 * Parameters:
 *      pps                   the picture parameter set to be freed
 *
 * Function:
 *      free the picture parameter set
 *
 * Returns:
 *      -
 */
void psClosePPS( pic_parameter_set_s *pps )
{
  if (pps == 0)
    return;

  if (pps->slice_group_id)
    nccFree(pps->slice_group_id);

  nccFree(pps);
}


/*
 *
 * psCloseSPS:
 *
 * Parameters:
 *      sps                   the sequence parameter set to be freed
 *
 * Fucntion:
 *      free the sequence parameter set
 *
 * Returns:
 *      -
 */
void psCloseSPS( seq_parameter_set_s *sps )
{
  if (sps == 0)
    return;

  nccFree(sps);
}


/*
 *
 * psCloseParametersSets:
 *
 * Parameters:
 *      spsList               The sequence parameter set list
 *      ppsList               The picture parameter set list
 *
 * Fucntion:
 *      Free all parameter sets
 *
 * Returns:
 *      -
 */
void psCloseParametersSets(seq_parameter_set_s **spsList,
                           pic_parameter_set_s **ppsList)
{
  int i;

  for (i = 0; i < PS_MAX_NUM_OF_SPS; i++) {
    psCloseSPS(spsList[i]);
    spsList[i] = 0;
  }

  for (i = 0; i < PS_MAX_NUM_OF_PPS; i++) {
    psClosePPS(ppsList[i]);
    ppsList[i] = 0;
  }
}


/*
 *
 * getHrdParameters:
 *
 * Parameters:
 *      bitbuf                The bitbuffer object
 *      hrd                   the pointer for returning HRD parameters
 *
 * Function:
 *      decode the HRD Parameters
 *
 * Returns:
 *      PS_OK:                Hrd parameters decoded succesfully
 *      <0:                   Fail
 */
static int getHrdParameters(bitbuffer_s *bitbuf, hrd_parameters_s *hrd)
{
  unsigned int i;
  int retCode;

  if ((retCode = ue_v(bitbuf, &hrd->cpb_cnt_minus1, 31)) < 0)
    return retCode;

  if ((retCode = u_n(bitbuf, 4, &hrd->bit_rate_scale)) < 0)
    return retCode;

  if ((retCode = u_n(bitbuf, 4, &hrd->cpb_size_scale)) < 0)
    return retCode;

  for (i = 0; i <= hrd->cpb_cnt_minus1; i++) {
    /* bit_rate_value_minus1 must be in range of 0 to 2^32-2 */
    if ((retCode = ue_v_long(bitbuf, &hrd->bit_rate_value_minus1[i], (u_int32)4294967294)) < 0)
      return retCode;

    /* cpb_size_value_minus1 must be in range of 0 to 2^32-2 */
    if ((retCode = ue_v_long(bitbuf, &hrd->cpb_size_value_minus1[i], (u_int32)4294967294)) < 0)
      return retCode;

    if ((retCode = u_n(bitbuf, 1, &hrd->cbr_flag[i])) < 0)
      return retCode;
  }

  if ((retCode = u_n(bitbuf, 5, &hrd->initial_cpb_removal_delay_length_minus1)) < 0)
    return retCode;

  if ((retCode = u_n(bitbuf, 5, &hrd->cpb_removal_delay_length_minus1)) < 0)
    return retCode;

  if ((retCode = u_n(bitbuf, 5, &hrd->dpb_output_delay_length_minus1)) < 0)
    return retCode;

  if ((retCode = u_n(bitbuf, 5, &hrd->time_offset_length)) < 0)
    return retCode;

  return PS_OK;
}


/*
 * getLevel:
 *
 * Parameters:
 *      levelNumber
 *      constraintSet3flag
 *
 * Function:
 *      Return parameters for level based on level number.
 *
 *  Return:
 *      Pointer to level or 0 if level does not exist
 */
static const level_s *getLevel(int levelNumber, int constraintSet3flag)
{
  int i;

  for (i = 0; i < NUM_LEVELS; i++) {
    if (levelArray[i].levelNumber == levelNumber &&
        levelArray[i].constraintSet3flag == constraintSet3flag)
      return &levelArray[i];
  }

  printf("Unknown level: %i.\n", levelNumber);
  return 0;
}


/*
 *
 * setVUIdefaults:
 *
 * Parameters:
 *      vui                   Pointer to VUI parameters
 *
 * Function:
 *      Set VUI parameters to their default values when default value is non-zero.
 *
 * Returns:
 *      -
 */
static void setVUIdefaults(seq_parameter_set_s *sps)
{
  vui_parameters_s *vui;
  const level_s *level;
  int MaxDpbSize;

  vui = &sps->vui_parameters;

  vui->video_format                            = 5;
  vui->colour_primaries                        = 2;
  vui->transfer_characteristics                = 2;
  vui->matrix_coefficients                     = 2;
  vui->motion_vectors_over_pic_boundaries_flag = 1;
  vui->max_bytes_per_pic_denom                 = 2;
  vui->max_bits_per_mb_denom                   = 1;
  vui->log2_max_mv_length_horizontal           = 16;
  vui->log2_max_mv_length_vertical             = 16;

  level = getLevel(sps->level_idc, sps->constraint_set3_flag);
  MaxDpbSize = level->maxDPB /
    ((sps->pic_width_in_mbs_minus1+1) * (sps->pic_height_in_map_units_minus1+1) * 384);
  MaxDpbSize = clip(1, 16, MaxDpbSize);

  vui->max_dec_frame_buffering = MaxDpbSize;
  vui->num_reorder_frames      = vui->max_dec_frame_buffering;
}


/*
 *
 * getVUI:
 *
 * Parameters:
 *      bitbuf                The bitbuffer object
 *      vui                   the pointer for returning VUI parameters
 *
 * Function:
 *      decode the VUI Parameters
 *
 * Returns:
 *      PS_OK:                VUI parameters decoded succesfully
 *      <0:                   Fail
 */
static int getVUI(bitbuffer_s *bitbuf, vui_parameters_s *vui)
{
  unsigned tempWordHi, tempWordLo;
  int retCode;

  if ((retCode = u_n(bitbuf, 1, &vui->aspect_ratio_info_present_flag)) < 0)
    return retCode;

  if (vui->aspect_ratio_info_present_flag) {
    if ((retCode = u_n(bitbuf, 8, &vui->aspect_ratio_idc)) < 0)
      return retCode;
    if (vui->aspect_ratio_idc == PS_EXTENDED_SAR) {
      if ((retCode = u_n(bitbuf, 16, &vui->sar_width)) < 0)
        return retCode;
      if ((retCode = u_n(bitbuf, 16, &vui->sar_height)) < 0)
        return retCode;
    }
  }

  if ((retCode = u_n(bitbuf, 1, &vui->overscan_info_present_flag)) < 0)
    return retCode;

  if (vui->overscan_info_present_flag) {
    if ((retCode = u_n(bitbuf, 1, &vui->overscan_appropriate_flag)) < 0)
      return retCode;
  }

  if ((retCode = u_n(bitbuf, 1, &vui->video_signal_type_present_flag)) < 0)
    return retCode;

  if (vui->video_signal_type_present_flag) {
    if ((retCode = u_n(bitbuf, 3, &vui->video_format)) < 0)
      return retCode;
    if ((retCode = u_n(bitbuf, 1, &vui->video_full_range_flag)) < 0)
      return retCode;
    if ((retCode = u_n(bitbuf, 1, &vui->colour_description_present_flag)) < 0)
      return retCode;
    if (vui->colour_description_present_flag) {
      if ((retCode = u_n(bitbuf, 8, &vui->colour_primaries)) < 0)
        return retCode;
      if ((retCode = u_n(bitbuf, 8, &vui->transfer_characteristics)) < 0)
        return retCode;
      if ((retCode = u_n(bitbuf, 8, &vui->matrix_coefficients)) < 0)
        return retCode;
    }
  }

  if ((retCode = u_n(bitbuf, 1, &vui->chroma_loc_info_present_flag)) < 0)
    return retCode;

  if (vui->chroma_loc_info_present_flag) {
    if ((retCode = ue_v(bitbuf, &vui->chroma_sample_loc_type_top_field, 5)) < 0)
      return retCode;
    if ((retCode = ue_v(bitbuf, &vui->chroma_sample_loc_type_bottom_field, 5)) < 0)
      return retCode;
  }

  if ((retCode = u_n(bitbuf, 1, &vui->timing_info_present_flag)) < 0)
    return retCode;

  if (vui->timing_info_present_flag) {
    if ((retCode = u_n(bitbuf, 16, &tempWordHi)) < 0)
      return retCode;
    if ((retCode = u_n(bitbuf, 16, &tempWordLo)) < 0)
      return retCode;
    vui->num_units_in_tick = (((u_int32)tempWordHi) << 16) | ((u_int32)tempWordLo);

    if ((retCode = u_n(bitbuf, 16, &tempWordHi)) < 0)
      return retCode;
    if ((retCode = u_n(bitbuf, 16, &tempWordLo)) < 0)
      return retCode;
    vui->time_scale = (((u_int32)tempWordHi) << 16) | ((u_int32)tempWordLo);

    if ((retCode = u_n(bitbuf, 1, &vui->fixed_frame_rate_flag)) < 0)
      return retCode;
  }

  if ((retCode = u_n(bitbuf, 1, &vui->nal_hrd_parameters_present_flag)) < 0)
    return retCode;

  if (vui->nal_hrd_parameters_present_flag) {
    if ((retCode = getHrdParameters(bitbuf, &vui->nal_hrd_parameters)) < 0)
      return retCode;
  }

  if ((retCode = u_n(bitbuf, 1, &vui->vcl_hrd_parameters_present_flag)) < 0)
    return retCode;

  if (vui->vcl_hrd_parameters_present_flag) {
    if ((retCode = getHrdParameters(bitbuf, &vui->vcl_hrd_parameters)) < 0)
      return retCode;
  }

  if (vui->nal_hrd_parameters_present_flag || vui->vcl_hrd_parameters_present_flag) {
    if ((retCode = u_n(bitbuf, 1, &vui->low_delay_hrd_flag)) < 0)
      return retCode;
  }

  if ((retCode = u_n(bitbuf, 1, &vui->pic_struct_present_flag)) < 0)
    return retCode;

  if ((retCode = u_n(bitbuf, 1, &vui->bitstream_restriction_flag)) < 0)
    return retCode;

  if (vui->bitstream_restriction_flag) {
    if ((retCode = u_n(bitbuf, 1, &vui->motion_vectors_over_pic_boundaries_flag)) < 0)
      return retCode;
    if ((retCode = ue_v(bitbuf, &vui->max_bytes_per_pic_denom, 16)) < 0)
      return retCode;
    if ((retCode = ue_v(bitbuf, &vui->max_bits_per_mb_denom, 16)) < 0)
      return retCode;
    if ((retCode = ue_v(bitbuf, &vui->log2_max_mv_length_horizontal, 16)) < 0)
      return retCode;
    if ((retCode = ue_v(bitbuf, &vui->log2_max_mv_length_vertical, 16)) < 0)
      return retCode;
    if ((retCode = ue_v(bitbuf, &vui->num_reorder_frames, 16)) < 0)
      return retCode;
    if ((retCode = ue_v(bitbuf, &vui->max_dec_frame_buffering, 16)) < 0)
    {
      printf("VUI: ERROR max frame buff %d\n",vui->max_dec_frame_buffering);
        return retCode;
     }
  }

  printf("VUI: max frame buff %d\n",vui->max_dec_frame_buffering);

  return PS_OK;
}

/*
 *
 * psDecodeSPS:
 *      
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      spsList               The list for SPS's, the newly decoded SPS will be stored into the list
 *
 * Function:
 *      Decode the SPS, and store it into the SPS list
 *
 * Returns:
 *      PS_OK:                SPS decoded succesfully
 *      <0:                   Fail
 */
int psDecodeSPS( bitbuffer_s *bitbuf, seq_parameter_set_s **spsList )
{
  seq_parameter_set_s *sps;
  unsigned int i, j;
  int retCode;
  unsigned  profile_idc;                                      // u(8)
  Boolean   constraint_set0_flag;                             // u(1)
  Boolean   constraint_set1_flag;                             // u(1)
  Boolean   constraint_set2_flag;                             // u(1)
  Boolean   constraint_set3_flag;                             // u(1)
  Boolean   reserved_zero_4bits;                              // u(4)
  unsigned  level_idc;                                        // u(8)
  unsigned  seq_parameter_set_id;                             // ue(v)
  unsigned tempValue;
  unsigned chroma_format_idc;


#ifdef DEBUG_PRINT
  printf("Start SPS decoding\n");
#endif

  /*
   * Parse sequence parameter set syntax until sps id
   */
  if ((retCode = u_n(bitbuf, 8, &profile_idc)) < 0)
    return retCode;

  /* If constraint_set0_flag == 1, stream is Baseline Profile compliant */
  if ((retCode = u_n(bitbuf, 1, &constraint_set0_flag)) < 0)
    return retCode;

  /* If constraint_set1_flag == 1, stream is Main Profile compliant */
  if ((retCode = u_n(bitbuf, 1, &constraint_set1_flag)) < 0)
    return retCode;

  /* If constraint_set2_flag == 1, stream is Extended Profile compliant */
  if ((retCode = u_n(bitbuf, 1, &constraint_set2_flag)) < 0)
    return retCode;

  if ((retCode = u_n(bitbuf, 1, &constraint_set3_flag)) < 0)
    return retCode;

  /* We support only baseline compliant and streams */
  if ((profile_idc != PS_BASELINE_PROFILE_IDC && constraint_set0_flag == 0) && 
      (!(profile_idc == PS_MVC_BASEVIEW || profile_idc == PS_MVC_HIGH || profile_idc == PS_MAIN_PROFILE_IDC)))
  {
    // Note that B-pictures are not supported!!!
    return PS_ERR_UNSUPPORTED_PROFILE;
  }

  /* We don't care what is in these bits */
  if ((retCode = u_n(bitbuf, 4, &reserved_zero_4bits)) < 0)
    return retCode;

  /* Fetch level */
  if ((retCode = u_n(bitbuf, 8, &level_idc)) < 0)
    return retCode;

  /* Find level in the list of legal levels */
  for (i = 0; i < NUM_LEVELS; i++) {
    if ((int)level_idc == levelArray[i].levelNumber)
      break;
  }

  /* If level was not found in the list, return with error */
  if (i == NUM_LEVELS)
    return PS_ERR_ILLEGAL_VALUE;

  /* Get sequence parameter set id */
  if ((retCode = ue_v(bitbuf, &seq_parameter_set_id, PS_MAX_NUM_OF_SPS-1)) < 0)
    return retCode;

  if ( profile_idc == PS_MVC_BASEVIEW || profile_idc == PS_MVC_HIGH )
  {
    if ((retCode = ue_v(bitbuf, &chroma_format_idc, 3)) < 0)
      return retCode;
    if (chroma_format_idc == 3) {   
      if ((retCode = u_n(bitbuf, 1, &tempValue)) < 0)
        return retCode;
    }

    if ((retCode = ue_v(bitbuf, &tempValue, 6)) < 0)
      return retCode;
    if ((retCode = ue_v(bitbuf, &tempValue, 6)) < 0)
      return retCode;
    if ((retCode = u_n(bitbuf, 1, &tempValue)) < 0)
      return retCode;
    if ((retCode = u_n(bitbuf, 1, &tempValue)) < 0)
      return retCode;
    if (tempValue == 1) {   /* seq_scaling_matrix_present */

      if (chroma_format_idc == 3)
        j = 12;
      else
        j = 8;

      for (i=0; i<j; i++) {
        if ((retCode = u_n(bitbuf, 1, &tempValue)) < 0)
          return retCode;
      }
    }
  }

  /*
   * Allocate memory for SPS
   */

  /* Pointer to sequence parameter set structure */
  sps = spsList[seq_parameter_set_id];

  /* allocate mem for SPS, if it has not been allocated already */
  if (!sps) {
    sps = (seq_parameter_set_s *) nccMalloc(sizeof(seq_parameter_set_s));
    if (sps == 0) {
      printf("Error while allocating memory for SPS.\n");
      return PS_ERR_MEM_ALLOC;
    }
    spsList[seq_parameter_set_id] = sps;
  }

  memset( sps, 0, sizeof(seq_parameter_set_s));

  /* Copy temporary variables to sequence parameter set structure */
  sps->profile_idc          = profile_idc;
  sps->constraint_set0_flag = constraint_set0_flag;
  sps->constraint_set1_flag = constraint_set1_flag;
  sps->constraint_set2_flag = constraint_set2_flag;
  sps->constraint_set3_flag = constraint_set3_flag;
  sps->reserved_zero_4bits  = reserved_zero_4bits;
  sps->level_idc            = level_idc;
  sps->seq_parameter_set_id = seq_parameter_set_id;

  /*
   * Parse rest of the sequence parameter set syntax
   */

  /* This defines how many bits there are in frame_num syntax element */
  if ((retCode = ue_v(bitbuf, &sps->log2_max_frame_num_minus4, 12)) < 0)
    return retCode;

  /* Fetch POC type */
  if ((retCode = ue_v(bitbuf, &sps->pic_order_cnt_type, 2)) < 0)
    return retCode;

  if (sps->pic_order_cnt_type == 0) {
    if ((retCode = ue_v(bitbuf, &sps->log2_max_pic_order_cnt_lsb_minus4, 12)) < 0)
      return retCode;
  }
  else if (sps->pic_order_cnt_type == 1) {
    if ((retCode = u_n(bitbuf, 1, &sps->delta_pic_order_always_zero_flag)) < 0)
      return retCode;

    if ((retCode = se_v_long(bitbuf, &sps->offset_for_non_ref_pic)) < 0)
      return retCode;

    if ((retCode = se_v_long(bitbuf, &sps->offset_for_top_to_bottom_field)) < 0)
      return retCode;

    if ((retCode = ue_v(bitbuf, &sps->num_ref_frames_in_pic_order_cnt_cycle, 255)) < 0)
      return retCode;

    for (i = 0; i < sps->num_ref_frames_in_pic_order_cnt_cycle; i++) {
      if ((retCode = se_v_long(bitbuf, &sps->offset_for_ref_frame[i])) < 0)
        return retCode;
    }
  }

  if ((retCode = ue_v(bitbuf, &sps->num_ref_frames, 16)) < 0)
    return retCode;

  if ((retCode = u_n(bitbuf, 1, &sps->gaps_in_frame_num_value_allowed_flag)) < 0)
    return retCode;

  if ((retCode = ue_v(bitbuf, &sps->pic_width_in_mbs_minus1, MAX_PIC_WIDTH_IN_MBS-1)) < 0)
    return retCode;

  if ((retCode = ue_v(bitbuf, &sps->pic_height_in_map_units_minus1, MAX_PIC_WIDTH_IN_MBS-1)) < 0)
    return retCode;

  if ((retCode = u_n(bitbuf, 1, &sps->frame_mbs_only_flag)) < 0)
    return retCode;

  if (!sps->frame_mbs_only_flag) {
    u_n(bitbuf, 1, &sps->mb_adaptive_frame_field_flag);
    return PS_ERR_UNSUPPORTED_FEATURE;
  }

  if ((retCode = u_n(bitbuf, 1, &sps->direct_8x8_inference_flag)) < 0)
    return retCode;

  if ((retCode = u_n(bitbuf, 1, &sps->frame_cropping_flag)) < 0)
    return retCode;

  /* Fetch cropping window */
  if (sps->frame_cropping_flag) {
    if ((retCode = ue_v(bitbuf, &sps->frame_crop_left_offset, 8*(sps->pic_width_in_mbs_minus1+1)-1)) < 0)
      return retCode;

    if ((retCode = ue_v(bitbuf, &sps->frame_crop_right_offset, 8*(sps->pic_width_in_mbs_minus1+1)-sps->frame_crop_left_offset-1)) < 0)
      return retCode;

    if ((retCode = ue_v(bitbuf, &sps->frame_crop_top_offset, 8*(sps->pic_height_in_map_units_minus1+1)-1)) < 0)
      return retCode;

    if ((retCode = ue_v(bitbuf, &sps->frame_crop_bottom_offset, 8*(sps->pic_height_in_map_units_minus1+1)-sps->frame_crop_top_offset-1)) < 0)
      return retCode;
  }

  if ((retCode = u_n(bitbuf, 1, &sps->vui_parameters_present_flag)) < 0)
    return retCode;

  setVUIdefaults(sps);

  if (sps->vui_parameters_present_flag) {
    if ((retCode = getVUI(bitbuf, &sps->vui_parameters)) < 0)
      return retCode;

#ifdef DEBUG_PRINT
    printf("SPS: VUI->Max_Frames %d\n",sps->vui_parameters.max_dec_frame_buffering);
#endif
  }

  if (bibSkipTrailingBits(bitbuf) < 0)
    return PS_ERROR;

  return PS_OK;
}


/*
 *
 * psDecodePPS:
 *      
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      ppsList               The list for PPS's, the newly decoded PPS will be stored into the list
 *
 * Function:
 *      Decode the PPS, and store it into the PPS list
 *
 * Returns:
 *      PS_OK:                PPS decoded succesfully
 *      <0:                   Fail
 */
int psDecodePPS( bitbuffer_s *bitbuf, pic_parameter_set_s **ppsList )
{
  unsigned int i, tmp;
  int len;
  pic_parameter_set_s *pps;
  unsigned pic_parameter_set_id;
  int retCode;
  unsigned pic_size_in_map_units_minus1;


  /* Parse pps id */
  if ((retCode = ue_v(bitbuf, &pic_parameter_set_id, PS_MAX_NUM_OF_PPS-1)) < 0)
    return retCode;

  /*
   * Allocate memory for pps if not already allocated
   */
  pps = ppsList[pic_parameter_set_id];

  if (!pps) {
    pps = (pic_parameter_set_s *) nccMalloc(sizeof(pic_parameter_set_s));
    if (pps == 0) {
      printf("Error while allocating memory for PPS.\n");
      return PS_ERR_MEM_ALLOC;
    }
    ppsList[pic_parameter_set_id] = pps;
  }

  memset( pps, 0, sizeof(pic_parameter_set_s));

  /*
   * Parse rest of the picture parameter set syntax
   */
  if ((retCode = ue_v( bitbuf, &pps->seq_parameter_set_id, PS_MAX_NUM_OF_SPS-1)) < 0)
    return retCode;

  /* Fetch entropy coding mode. Mode is 0 for CAVLC and 1 for CABAC */
  if ((retCode = u_n( bitbuf, 1, &pps->entropy_coding_mode_flag)) < 0)
    return retCode;

  /* If this flag is 1, POC related syntax elements are present in slice header */
  if ((retCode = u_n( bitbuf, 1, &pps->pic_order_present_flag)) < 0)
    return retCode;

  /* Fetch the number of slice groups minus 1 */
  if ((retCode = ue_v( bitbuf, &pps->num_slice_groups_minus1, PS_MAX_NUM_SLICE_GROUPS-1)) < 0)
    return retCode;

  if(pps->num_slice_groups_minus1 > 0 ) {

    if ((retCode = ue_v( bitbuf, &pps->slice_group_map_type, 6)) < 0)
      return retCode;

    switch (pps->slice_group_map_type) {

      case PS_SLICE_GROUP_MAP_TYPE_INTERLEAVED:
        for (i = 0; i <= pps->num_slice_groups_minus1; i++) {
          if ((retCode = ue_v( bitbuf, &pps->run_length_minus1[i], MAX_PIC_SIZE_IN_MBS-1 )) < 0)
            return retCode;
        }
        break;

      case PS_SLICE_GROUP_MAP_TYPE_DISPERSED:
        break;

      case PS_SLICE_GROUP_MAP_TYPE_FOREGROUND:
        for (i = 0; i < pps->num_slice_groups_minus1; i++) {
          /* Fetch MB address of the top-left corner */
          if ((retCode = ue_v( bitbuf, &pps->top_left[i], MAX_PIC_SIZE_IN_MBS-1)) < 0)
            return retCode;
          /* Fetch MB address of the bottom-right corner (top-left address must */
          /* be smaller than or equal to bottom-right address)                  */
          if ((retCode = ue_v( bitbuf, &pps->bottom_right[i], MAX_PIC_SIZE_IN_MBS-1)) < 0)
            return retCode;

          if (pps->top_left[i] > pps->bottom_right[i])
            return PS_ERR_ILLEGAL_VALUE;
        }
        break;

      case PS_SLICE_GROUP_MAP_TYPE_CHANGING_3:
      case PS_SLICE_GROUP_MAP_TYPE_CHANGING_4:
      case PS_SLICE_GROUP_MAP_TYPE_CHANGING_5:
        if ((retCode = u_n( bitbuf, 1, &pps->slice_group_change_direction_flag)) < 0)
          return retCode;
        if ((retCode = ue_v( bitbuf, &pps->slice_group_change_rate_minus1, MAX_PIC_SIZE_IN_MBS-1)) < 0)
          return retCode;
        break;

      case PS_SLICE_GROUP_MAP_TYPE_EXPLICIT:

        if ((retCode = ue_v( bitbuf, &pic_size_in_map_units_minus1, MAX_PIC_SIZE_IN_MBS-1 )) < 0)
          return retCode;

        /* Allocate array for slice group ids if not already allocated */
        if (pic_size_in_map_units_minus1 != pps->pic_size_in_map_units_minus1) {
          nccFree(pps->slice_group_id);
          pps->slice_group_id = (unsigned int *)nccMalloc( (pic_size_in_map_units_minus1+1) * sizeof(int));
          pps->pic_size_in_map_units_minus1 = pic_size_in_map_units_minus1;
        }

        // Calculate len = ceil( Log2( num_slice_groups_minus1 + 1 ) )
        tmp = pps->num_slice_groups_minus1 + 1;
        tmp = tmp >> 1;
        for( len = 0; len < 16 && tmp != 0; len++ )
          tmp >>= 1;
        if ( (((unsigned)1)<<len) < (pps->num_slice_groups_minus1 + 1) )
          len++;

        for( i = 0; i <= pps->pic_size_in_map_units_minus1; i++ ) {
          if ((retCode = u_n( bitbuf, len, &pps->slice_group_id[i])) < 0)
            return retCode;
        }

        break;

      default:
        /* Cannnot happen */
        break;
    }
  }

  if ((retCode = ue_v( bitbuf, &pps->num_ref_idx_l0_active_minus1, 31 )) < 0)
    return retCode;

  if ((retCode = ue_v( bitbuf, &pps->num_ref_idx_l1_active_minus1, 31 )) < 0)
    return retCode;

  if ((retCode = u_n( bitbuf, 1, &pps->weighted_pred_flag)) < 0)
    return retCode;

  if ((retCode = u_n( bitbuf, 2, &pps->weighted_bipred_idc)) < 0)
    return retCode;

  if (pps->weighted_bipred_idc > 2)
    return PS_ERR_ILLEGAL_VALUE;

  if ((retCode = se_v( bitbuf, &pps->pic_init_qp_minus26, -26, 25 )) < 0)
    return retCode;

  if ((retCode = se_v( bitbuf, &pps->pic_init_qs_minus26, -26, 25  )) < 0)
    return retCode;

  if ((retCode = se_v( bitbuf, &pps->chroma_qp_index_offset, -12, 12 )) < 0)
    return retCode;

  pps->chroma_qp_index_offset =
    clip(MIN_CHROMA_QP_INDEX, MAX_CHROMA_QP_INDEX, pps->chroma_qp_index_offset);

  if ((retCode = u_n( bitbuf, 1, &pps->deblocking_filter_parameters_present_flag )) < 0)
    return retCode;

  if ((retCode = u_n( bitbuf, 1, &pps->constrained_intra_pred_flag )) < 0)
    return retCode;

  if ((retCode = u_n( bitbuf, 1, &pps->redundant_pic_cnt_present_flag )) < 0)
    return retCode;

  if (bibSkipTrailingBits(bitbuf) < 0)
    return PS_ERROR;

  return PS_OK;
}


/*
 *
 * psGetAspectRatio:
 *      
 * Parameters:
 *      sps                   Sequence parameter set
 *      width                 Horizontal size of the sample aspect ratio
 *      height                Vertical size of the sample aspect ratio
 *
 * Function:
 *      Return sample aspect ratio in width and height
 *
 * Returns:
 *      -
 */
void psGetAspectRatio(seq_parameter_set_s *sps, int *width, int *height)
{
  vui_parameters_s *vui;

  vui = &sps->vui_parameters;

  *width  = 0;
  *height = 0;

  if (sps->vui_parameters_present_flag &&
      vui->aspect_ratio_info_present_flag &&
      vui->aspect_ratio_idc != 0 &&
      (vui->aspect_ratio_idc <= 13 || vui->aspect_ratio_idc == 255))
  {
    if (vui->aspect_ratio_idc == 255) {
      /* Extended_SAR */
      if (vui->sar_width != 0 && vui->sar_height != 0) {
        *width  = vui->sar_width;
        *height = vui->sar_height;
      }
    }
    else {
      *width  = aspectRatioArr[vui->aspect_ratio_idc-1].width;
      *height = aspectRatioArr[vui->aspect_ratio_idc-1].height;
    }
  }
}


int psDecodeSubsetSPS( bitbuffer_s *bitbuf, seq_parameter_set_s **spsList )
{
  seq_parameter_set_s *sps;
  unsigned int i;
  int retCode;
  unsigned  profile_idc;                                      // u(8)
  Boolean   constraint_set0_flag;                             // u(1)
  Boolean   constraint_set1_flag;                             // u(1)
  Boolean   constraint_set2_flag;                             // u(1)
  Boolean   constraint_set3_flag;                             // u(1)
  Boolean   reserved_zero_4bits;                              // u(4)
  unsigned  level_idc;                                        // u(8)
  unsigned  seq_parameter_set_id;                             // ue(v)
  unsigned tempBit;
  unsigned tempValue;


#ifdef DEBUG_PRINT
  printf("Start Subset SPS\n");
#endif

  /*
   * Parse sequence parameter set syntax until sps id
   */
  if ((retCode = u_n(bitbuf, 8, &profile_idc)) < 0)
    return retCode;

  /* If constraint_set0_flag == 1, stream is Baseline Profile compliant */
  if ((retCode = u_n(bitbuf, 1, &constraint_set0_flag)) < 0)
    return retCode;

  /* If constraint_set1_flag == 1, stream is Main Profile compliant */
  if ((retCode = u_n(bitbuf, 1, &constraint_set1_flag)) < 0)
    return retCode;

  /* If constraint_set2_flag == 1, stream is Extended Profile compliant */
  if ((retCode = u_n(bitbuf, 1, &constraint_set2_flag)) < 0)
    return retCode;

  if ((retCode = u_n(bitbuf, 1, &constraint_set3_flag)) < 0)
    return retCode;

  /* We don't care what is in these bits */
  if ((retCode = u_n(bitbuf, 4, &reserved_zero_4bits)) < 0)
    return retCode;

  /* Fetch level */
  if ((retCode = u_n(bitbuf, 8, &level_idc)) < 0)
    return retCode;

  /* Find level in the list of legal levels */
  for (i = 0; i < NUM_LEVELS; i++) {
    if ((int)level_idc == levelArray[i].levelNumber)
      break;
  }

  /* If level was not found in the list, return with error */
  if (i == NUM_LEVELS)
    return PS_ERR_ILLEGAL_VALUE;

  /* Get sequence parameter set id */
  if ((retCode = ue_v(bitbuf, &seq_parameter_set_id, PS_MAX_NUM_OF_SPS-1)) < 0)
    return retCode;

  if ( profile_idc == PS_MVC_BASEVIEW || profile_idc == PS_MVC_HIGH )
  {
    if ((retCode = ue_v(bitbuf, &tempValue, 3)) < 0)
      return retCode;
    if ((retCode = ue_v(bitbuf, &tempValue, 6)) < 0)
      return retCode;
    if ((retCode = ue_v(bitbuf, &tempValue, 6)) < 0)
      return retCode;
    if ((retCode = u_n(bitbuf, 1, &tempValue)) < 0)
      return retCode;
    if ((retCode = u_n(bitbuf, 1, &tempValue)) < 0)
      return retCode;
  }

  /*
   * Allocate memory for SPS
   */

  /* Pointer to sequence parameter set structure */
  sps = spsList[seq_parameter_set_id];

#ifdef DEBUG_PRINT
  printf("SubSet SPS id %d\n",seq_parameter_set_id);
#endif

  /* allocate mem for SPS, if it has not been allocated already */
  if (!sps) {
    sps = (seq_parameter_set_s *) nccMalloc(sizeof(seq_parameter_set_s));
    if (sps == 0) {
      printf("Error while allocating memory for SPS.\n");
      return PS_ERR_MEM_ALLOC;
    }
    spsList[seq_parameter_set_id] = sps;
  }

  memset( sps, 0, sizeof(seq_parameter_set_s));

  /* Copy temporary variables to sequence parameter set structure */
  sps->profile_idc          = profile_idc;
  sps->constraint_set0_flag = constraint_set0_flag;
  sps->constraint_set1_flag = constraint_set1_flag;
  sps->constraint_set2_flag = constraint_set2_flag;
  sps->constraint_set3_flag = constraint_set3_flag;
  sps->reserved_zero_4bits  = reserved_zero_4bits;
  sps->level_idc            = level_idc;
  sps->seq_parameter_set_id = seq_parameter_set_id;


  /*
   * Parse rest of the sequence parameter set syntax
   */

  /* This defines how many bits there are in frame_num syntax element */
  if ((retCode = ue_v(bitbuf, &sps->log2_max_frame_num_minus4, 12)) < 0)
    return retCode;

  /* Fetch POC type */
  if ((retCode = ue_v(bitbuf, &sps->pic_order_cnt_type, 2)) < 0)
    return retCode;

  if (sps->pic_order_cnt_type == 0) {
    if ((retCode = ue_v(bitbuf, &sps->log2_max_pic_order_cnt_lsb_minus4, 12)) < 0)
      return retCode;
  }
  else if (sps->pic_order_cnt_type == 1) {
    if ((retCode = u_n(bitbuf, 1, &sps->delta_pic_order_always_zero_flag)) < 0)
      return retCode;

    if ((retCode = se_v_long(bitbuf, &sps->offset_for_non_ref_pic)) < 0)
      return retCode;

    if ((retCode = se_v_long(bitbuf, &sps->offset_for_top_to_bottom_field)) < 0)
      return retCode;

    if ((retCode = ue_v(bitbuf, &sps->num_ref_frames_in_pic_order_cnt_cycle, 255)) < 0)
      return retCode;

    for (i = 0; i < sps->num_ref_frames_in_pic_order_cnt_cycle; i++) {
      if ((retCode = se_v_long(bitbuf, &sps->offset_for_ref_frame[i])) < 0)
        return retCode;
    }
  }

  if ((retCode = ue_v(bitbuf, &sps->num_ref_frames, 16)) < 0)
    return retCode;

  if ((retCode = u_n(bitbuf, 1, &sps->gaps_in_frame_num_value_allowed_flag)) < 0)
    return retCode;

  if ((retCode = ue_v(bitbuf, &sps->pic_width_in_mbs_minus1, MAX_PIC_WIDTH_IN_MBS-1)) < 0)
    return retCode;

  if ((retCode = ue_v(bitbuf, &sps->pic_height_in_map_units_minus1, MAX_PIC_WIDTH_IN_MBS-1)) < 0)
    return retCode;

  if ((retCode = u_n(bitbuf, 1, &sps->frame_mbs_only_flag)) < 0)
    return retCode;

  if (!sps->frame_mbs_only_flag) {
    u_n(bitbuf, 1, &sps->mb_adaptive_frame_field_flag);
    return PS_ERR_UNSUPPORTED_FEATURE;
  }

  if ((retCode = u_n(bitbuf, 1, &sps->direct_8x8_inference_flag)) < 0)
    return retCode;

  if ((retCode = u_n(bitbuf, 1, &sps->frame_cropping_flag)) < 0)
    return retCode;

  /* Fetch cropping window */
  if (sps->frame_cropping_flag) {
    if ((retCode = ue_v(bitbuf, &sps->frame_crop_left_offset, 8*(sps->pic_width_in_mbs_minus1+1)-1)) < 0)
      return retCode;

    if ((retCode = ue_v(bitbuf, &sps->frame_crop_right_offset, 8*(sps->pic_width_in_mbs_minus1+1)-sps->frame_crop_left_offset-1)) < 0)
      return retCode;

    if ((retCode = ue_v(bitbuf, &sps->frame_crop_top_offset, 8*(sps->pic_height_in_map_units_minus1+1)-1)) < 0)
      return retCode;

    if ((retCode = ue_v(bitbuf, &sps->frame_crop_bottom_offset, 8*(sps->pic_height_in_map_units_minus1+1)-sps->frame_crop_top_offset-1)) < 0)
      return retCode;
  }

  if ((retCode = u_n(bitbuf, 1, &sps->vui_parameters_present_flag)) < 0)
    return retCode;

  setVUIdefaults(sps);

  if (sps->vui_parameters_present_flag) {
    if ((retCode = getVUI(bitbuf, &sps->vui_parameters)) < 0)
      return retCode;
  }
  
  if (sps->profile_idc == PS_MVC_HIGH) {
    
    /* Read bit equal to one */
    if ((retCode = u_n(bitbuf, 1, &tempBit)) < 0)
      return retCode;
    if (tempBit == 0)
      return -1;	// Return error
    
    /* Read SPS MVC extension */
    if (readSPSMVCExtension(bitbuf, sps) < 0)
      return -1;
    
    /* MVC VUI */
    if ((retCode = u_n(bitbuf, 1, &tempBit)) < 0)
      return retCode;
    
    /* Add reading of the MVC VUI later */
  }
  
  /* Additional extension flag */
  if ((retCode = u_n(bitbuf, 1, &tempBit)) < 0)
    return retCode;

  /* Add reading of the extension later */
  
  if (bibSkipTrailingBits(bitbuf) < 0)
    return PS_ERROR;
  
  return PS_OK;
}


int readSPSMVCExtension( bitbuffer_s *bitbuf, seq_parameter_set_s *sps )
{
  unsigned int i, j, k;
  unsigned int numViews, numLevels;
  int retCode;


  /* Read number of views */
  if ((retCode = ue_v(bitbuf, &sps->num_views_minus1, MAX_NUM_VIEWS-1)) < 0)
    return retCode;

  /* If number of views is zero, exit */
  if (sps->num_views_minus1 < 1)
	  return (-1);

  numViews = sps->num_views_minus1 + 1;

  /* Allocate memory */
  sps->view_id = (unsigned *) nccMalloc((numViews) * sizeof(unsigned));
  sps->num_anchor_refs_l0 = (unsigned *) nccMalloc((numViews) * sizeof(unsigned));
  sps->num_anchor_refs_l1 = (unsigned *) nccMalloc((numViews) * sizeof(unsigned));
  sps->num_non_anchor_refs_l0 = (unsigned *) nccMalloc((numViews) * sizeof(unsigned));
  sps->num_non_anchor_refs_l1 = (unsigned *) nccMalloc((numViews) * sizeof(unsigned));
  sps->anchor_refs_l0 = (unsigned **) nccMalloc((numViews-1) * sizeof(unsigned *));
  sps->anchor_refs_l1 = (unsigned **) nccMalloc((numViews-1) * sizeof(unsigned *));
  sps->non_anchor_refs_l0 = (unsigned **) nccMalloc((numViews-1) * sizeof(unsigned *));
  sps->non_anchor_refs_l1 = (unsigned **) nccMalloc((numViews-1) * sizeof(unsigned *));

  for( i=1; i<numViews; i++ ) {
    sps->anchor_refs_l0[i] = (unsigned *) nccMalloc((numViews-1) * sizeof(unsigned));
    sps->anchor_refs_l1[i] = (unsigned *) nccMalloc((numViews-1) * sizeof(unsigned));
    sps->non_anchor_refs_l0[i] = (unsigned *) nccMalloc((numViews-1) * sizeof(unsigned));
    sps->non_anchor_refs_l1[i] = (unsigned *) nccMalloc((numViews-1) * sizeof(unsigned));
  }

  for( i=0; i<numViews; i++) {
    if ((retCode = ue_v(bitbuf, &sps->view_id[i], MAX_NUM_VIEWS-1)) < 0)
      return retCode;
  }

  for( i=1; i<numViews; i++) {
    if ((retCode = ue_v(bitbuf, &sps->num_anchor_refs_l0[i], MAX_NUM_VIEWS-1)) < 0)
      return retCode;
    
#ifdef DEBUG_PRINT
    printf("Num anchor refs l0 %d\n",sps->num_anchor_refs_l0[i]);
#endif
    
    for( j=0; j<sps->num_anchor_refs_l0[i]; j++) {
      if ((retCode = ue_v(bitbuf, &sps->anchor_refs_l0[i][j], MAX_NUM_VIEWS-1)) < 0)
        return retCode;
      
#ifdef DEBUG_PRINT
      printf("Anchor refs l0: %d ",sps->anchor_refs_l0[i][j]);
#endif
    }
    
    if ((retCode = ue_v(bitbuf, &sps->num_anchor_refs_l1[i], MAX_NUM_VIEWS-1)) < 0)
      return retCode;
    
    for( j=0; j<sps->num_anchor_refs_l1[i]; j++) {
      if ((retCode = ue_v(bitbuf, &sps->anchor_refs_l1[i][j], MAX_NUM_VIEWS-1)) < 0)
        return retCode;
    }
  }
  
  
  
  for( i=1; i<numViews; i++) {
    if ((retCode = ue_v(bitbuf, &sps->num_non_anchor_refs_l0[i], MAX_NUM_VIEWS-1)) < 0)
      return retCode;
    
    for( j=0; j<sps->num_non_anchor_refs_l0[i]; j++) {
      if ((retCode = ue_v(bitbuf, &sps->non_anchor_refs_l0[i][j], MAX_NUM_VIEWS-1)) < 0)
        return retCode;
    }
    
    if ((retCode = ue_v(bitbuf, &sps->num_non_anchor_refs_l1[i], MAX_NUM_VIEWS-1)) < 0)
      return retCode;
    
    for( j=0; j<sps->num_non_anchor_refs_l1[i]; j++) {
      if ((retCode = ue_v(bitbuf, &sps->non_anchor_refs_l1[i][j], MAX_NUM_VIEWS-1)) < 0)
        return retCode;
    }
  }
  
  if ((retCode = ue_v(bitbuf, &sps->num_level_values_signalled_minus1, MAX_NUM_LEVELS-1)) < 0)
    return retCode;

#ifdef DEBUG_PRINT
  printf("NumLevels -1: %d \n",sps->num_level_values_signalled_minus1);
#endif
  
  numLevels = sps->num_level_values_signalled_minus1 + 1;
  
  /* Allocate memory */
  sps->num_applicable_ops_minus1 = (unsigned *) nccMalloc((numLevels) * sizeof(unsigned));
  sps->level_idc_mvc = (unsigned *) nccMalloc((numLevels) * sizeof(unsigned));
  sps->applicable_op_temporal_id = (unsigned **) nccMalloc((numLevels) * sizeof(unsigned *));
  sps->applicable_op_num_target_views_minus1 = (unsigned **) nccMalloc((numLevels) * sizeof(unsigned *));
  sps->applicable_op_target_view_id = (unsigned ***) nccMalloc((numLevels) * sizeof(unsigned **));
  sps->applicable_op_num_views_minus1 = (unsigned **) nccMalloc((numLevels) * sizeof(unsigned *));
  
  for( i=0; i<=sps->num_level_values_signalled_minus1; i++) {
    if ((retCode = u_n(bitbuf, 8, &sps->level_idc_mvc[i])) < 0)
      return retCode;

    if ((retCode = ue_v(bitbuf, &sps->num_applicable_ops_minus1[i], MAX_NUM_APPLICABLE_OPS-1)) < 0)
      return retCode;
    
    /* Allocate memory */
    sps->applicable_op_temporal_id[i] = (unsigned *) nccMalloc((sps->num_applicable_ops_minus1[i]+1) * sizeof(unsigned));
    sps->applicable_op_num_target_views_minus1[i] = (unsigned *) nccMalloc((sps->num_applicable_ops_minus1[i]+1) * sizeof(unsigned));
    sps->applicable_op_target_view_id[i] = (unsigned **) nccMalloc((sps->num_applicable_ops_minus1[i]+1) * sizeof(unsigned *));
    sps->applicable_op_num_views_minus1[i] = (unsigned *) nccMalloc((sps->num_applicable_ops_minus1[i]+1) * sizeof(unsigned));
    
    for( j=0; j<=sps->num_applicable_ops_minus1[i]; j++) {
      if ((retCode = u_n(bitbuf, 3, &sps->applicable_op_temporal_id[i][j])) < 0)
        return retCode;

      if ((retCode = ue_v(bitbuf, &sps->applicable_op_num_target_views_minus1[i][j], MAX_NUM_VIEWS-1)) < 0)
        return retCode;
      
      /* Allocate memory */
      sps->applicable_op_target_view_id[i][j] = (unsigned *) nccMalloc((sps->applicable_op_num_target_views_minus1[i][j]) * sizeof(unsigned));
      
      for( k=0; k<=sps->applicable_op_num_target_views_minus1[i][j]; k++) {
        if ((retCode = ue_v(bitbuf, &sps->applicable_op_target_view_id[i][j][k], MAX_NUM_VIEWS-1)) < 0)
          return retCode;

#ifdef DEBUG_PRINT
        printf("applicable_op_target_view_id: %d, %d \n",k,sps->applicable_op_target_view_id[i][j][k]);
#endif
      }
      
      if ((retCode = ue_v(bitbuf, &sps->applicable_op_num_views_minus1[i][j], MAX_NUM_VIEWS-1)) < 0)
        return retCode;
    }
  }
  
  return AVCD_OK;
}

