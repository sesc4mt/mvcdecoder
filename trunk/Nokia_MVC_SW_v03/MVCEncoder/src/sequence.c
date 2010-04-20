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
 * sequence.c
 *
 * Contains:
 *    Functions for sequence layer.
 *
 */

#include <math.h>
#include <string.h>
#include "globals.h"
#include "debug.h"
#include "nccglob.h"
#include "vlcutility.h"
#include "frame.h"
#include "sequence.h"
#include "avcencoder.h"
#include "parameterset.h"
#include "dpb.h"
#include "air.h"
#include "ratecontrol.h"
#include "rtp.h"

#ifdef ENABLE_SEARCH_WINDOW
// internal search window 
#include "searchwin.h"
#endif


/* 
 * Definitions of SEI types
 */
#define SEI_TYPE_SCENE_INFO       9

#define MIN_CHROMA_QP_INDEX     -12
#define MAX_CHROMA_QP_INDEX     12
#define MIN_ALPHA_BETA_OFFSET   -6
#define MAX_ALPHA_BETA_OFFSET   6

#if  PRINT_DETAILED_SEQ_STATISTICS
static void printIntraStat(statSlice_s *intraStat, FILE *fp);
static void printInterStat(statSlice_s *interStat, FILE *fp);
#endif

const int   level_idc[16]  = {10,    11,   11,   12,   13,    20,    21,    22,    30,    31,     32,     40,     41,     42,     50,     51};
const int32 maxMBPS[16]    = {1485,  1485, 3000, 6000, 11880, 11880, 19800, 20250, 40500, 108000, 216000, 245760, 245760, 491520, 589824, 983040};
const int32 maxFS[16]      = {99,    99,   396,  396,  396,   396,   792,   1620,  1620,  3600,   5120,   8192,   8192,   8192,   22080,  36864};
const int32 maxBR[16]      = {64,    128,  192,  384,  768,   2000,  4000,  4000,  10000, 14000,  20000,  20000,  50000,  50000,  135000, 240000};
const int32 maxCPB[16]     = {175,   350,  500,  1000, 2000,  2000,  4000,  4000,  10000, 14000,  20000,  25000,  62500,  62500,  135000, 240000}; 
 
static void getStat(avceStatistics_s *retStat, statSlice_s *stat);


/*
 * seqLoad
 *
 * Parameters:
 *      seq                   Sequence parameters
 *
 * Function:
 *      Initializes sequence constants
 *      
 * Returns:
 *      -
 */
void avceLoad()
{
  frmLoad();
}


/*
 * seqOpen
 *
 * Parameters:
 *      param                 Parameters for sequence
 *
 * Function:
 *      Initializes sequence by opening files and allocating memory for
 *      framebuffers and other buffers
 *      
 * Returns:
 *      Pointer to encoder instance or NULL if error.
 */
avceEncoder_t *avceOpen(avceOpenParams_s *param, void **nalBuffer, int *nalBufSize)
{
  sequence_s  *seq;
  encParams_s *pEncPar;
  int bitBufInitialSize;
  int numMbsPerFrame;
  int counter;
  int i,indx;
  int j;
  int useMVC;


  if ((seq = nccMalloc(sizeof(sequence_s))) == NULL)
    return NULL;
  
  if (NUM_VIEWS > 1) {
    useMVC = 1;
  }
  else
    useMVC = 0;
  
  /* Use one SPS and PPS for each view */
  seq->numSPS = NUM_VIEWS;
  seq->numPPS = NUM_VIEWS;
  
  /* allocate memory for SPS and PPS sets */
  if ((seq->sps = nccMalloc(sizeof(seq_parameter_set_s) * seq->numSPS)) == NULL)
    return NULL;
  if ((seq->pps = nccMalloc(sizeof(pic_parameter_set_s) * seq->numPPS)) == NULL)
    return NULL;
  
  /*
   * Initialize sequence variables
   */
  seq->lastIdrTr    = 0;
  seq->nextIdrPicId = 0;
  seq->encPar = *param;
  
  /* initialize the encoding parameter structure */
  pEncPar = & seq->encPar;
  
  numMbsPerFrame = (pEncPar->picWidth/16) * (pEncPar->picHeight/16);
  
  /* If level is 3.1 or higher, we can't use 4x4 motion blocks because */
  /* we might exceed level limit (max. number of motion vector for two */
  /* consecutive macroblocks is 16 for level 3.1 and higher).          */
  if (pEncPar->level >= 31)
    pEncPar->modeFlags = pEncPar->modeFlags & 0x3f;
  
  pEncPar->filterMode  = clip(0, 2, pEncPar->filterMode);
  
  pEncPar->chromaQpIdx = 
    clip(MIN_CHROMA_QP_INDEX, MAX_CHROMA_QP_INDEX, pEncPar->chromaQpIdx);
  
  pEncPar->alphaOffset = 2 *
    clip(MIN_ALPHA_BETA_OFFSET, MAX_ALPHA_BETA_OFFSET, pEncPar->alphaOffset);
  
  pEncPar->betaOffset  = 2 *
    clip(MIN_ALPHA_BETA_OFFSET, MAX_ALPHA_BETA_OFFSET, pEncPar->betaOffset);
  
  pEncPar->maxNumRefFrms = clip(0, FRM_MAX_REF_FRAMES, pEncPar->maxNumRefFrms);
  
  pEncPar->numReorderFrames = min(pEncPar->numReorderFrames, pEncPar->maxNumRefFrms);
  
  pEncPar->range = clip(4, 64, pEncPar->range);
  
  pEncPar->log2_max_frame_num_minus4 = 
    clip(0, 12, pEncPar->log2_max_frame_num_minus4);
  
  pEncPar->nRandomIntraRefresh =
    clip(0, numMbsPerFrame, pEncPar->nRandomIntraRefresh);
  
  pEncPar->numNonref = param->numNonref;
  
  if(pEncPar->rtp_flag == 1)
    initializeRTP(&seq->rtpPacket,(int) 90000 / (pEncPar->origFpsTimes1000/pEncPar->offsetForRefFrame/1000));
  else
    seq->rtpPacket.use_rtp = 0;
  
  if(pEncPar->maxBytesPerSlice < pEncPar->nBytesPerSlice)
    pEncPar->maxBytesPerSlice = pEncPar->nBytesPerSlice;
  
  // Forced Intra Refresh
  seq->forcedIRNo = FORCE_INTRA_FREQUENCY;
  seq->forcedIR = (int*) nccMalloc(sizeof(int)*numMbsPerFrame);
  seq->AIR_intraMap = (int*) nccMalloc(sizeof(int)*numMbsPerFrame);

  // Simple AIR
  seq->nAIR = pEncPar->nAIR;
  
  counter = seq->forcedIRNo;
  for (i = 0; i < numMbsPerFrame; i++) {
    seq->forcedIR[i] = counter--;
    if (counter < 0)
      counter = seq->forcedIRNo;
  }
  
  /* LOW_COMPLEX_PROF3 */
  if (pEncPar->profile == PROF_CODING_LC3) {
    pEncPar->profile = PROF_CODING_SPEED;
    pEncPar->low_complex_prof3 = 1;
    pEncPar->low_complex_prof4 = 0;
    pEncPar->spec_search_pos = ( pEncPar->range == LC3_RANGE ) ;
  }
  if (pEncPar->profile == PROF_CODING_LC4 ) {
    pEncPar->profile = PROF_CODING_SPEED;
    pEncPar->low_complex_prof3 = 1;
    pEncPar->low_complex_prof4 = 1; //prof 4 = prof3 + more modifications
    pEncPar->spec_search_pos = ( pEncPar->range == LC3_RANGE ) ;
  }
  
#ifdef ENABLE_SEARCH_WINDOW
  // internal search window
  pEncPar->useSearchWin = ( (pEncPar->srx > 0) && (pEncPar->sry > 0) );
#endif
  
  /*
   * Initialize frame buffer and reference frame buffers
   */
  frmOpen(& seq->recoFrm, pEncPar->picWidth, pEncPar->picHeight, pEncPar->plr);
  frmEncBufOpen(& seq->mbData, pEncPar->picWidth, pEncPar->picHeight, pEncPar->nRandomIntraRefresh);
  
  seq->sliceGroupCycle = 0;
  
  /* Initialize the SPS sets */
  for(j = 0; j < seq->numSPS; j++) {
    seq->sps[j].level_idc   = 0;
    
    // Check if the input level parameter makes sense or not
    if(pEncPar->level != 0) {
      int j=0;
      for(i = 0; i< 16; i++) {      
        if(level_idc[i] == (int)pEncPar->level)
          j=1;
      }
      if(j==0)
        pEncPar->level=0;
    }
    
    // Find the level according to the encoding parameters
    for (i = 0; i < 16; i++) {
      if (numMbsPerFrame <= maxFS[i] &&
        numMbsPerFrame*pEncPar->origFpsTimes1000 <= pEncPar->offsetForRefFrame*maxMBPS[i]*1000 &&
        pEncPar->brcBitRate <= 1000*maxBR[i]) {
        seq->sps[j].level_idc = level_idc[i];
        break;
      }
    }
    
    // Adjust Level if we use Constant QP
    if (pEncPar->brcBitRate == 0) {
      if (seq->sps[j].level_idc == 9)
        seq->sps[j].level_idc = 10;
      else if (seq->sps[j].level_idc == 13)
        seq->sps[j].level_idc = 20;
    }
    
    // If appropriate level is not found
    if(seq->sps[j].level_idc == 0) {
      printf("Input Parameters do not conform to any Level!\n");

      seq->sps[j].level_idc = 51;
      indx = 15;
    }
    else
    {
      if (seq->sps[j].level_idc > pEncPar->level && pEncPar->level != 0)
        printf("Level Information is adjusted\n");
      else if (seq->sps[j].level_idc < pEncPar->level && pEncPar->level != 0 && seq->sps[j].level_idc != 9)
        seq->sps[j].level_idc = pEncPar->level;
      
      for(i=0;i<16;i++) {
        if((int)seq->sps[j].level_idc == level_idc[i])
          indx=i;
      }
      
      if (pEncPar->brcBufSize*8 > 1000*maxCPB[indx]) {
        printf("Buffer Size is too large and it is adjusted for the given level\n");
        
        pEncPar->brcBufSize = (maxCPB[indx]*1000)>>3;
      }
    }
  }	
  
  seq->encPar.level = seq->sps[0].level_idc;
  
  if (seq->encPar.brcBufSize == 0)
  {
    seq->encPar.brcBufSize = (maxCPB[indx]*1000)>>3;
  }
  
  if (seq->encPar.brcBitRate > 0 && pEncPar->brcBufSize*8*10/seq->encPar.brcBitRate < 2  )
  {
    printf("Buffer Size is too low. Increasing to 0.2 seconds..!\n");
    seq->encPar.brcBufSize = (int)(seq->encPar.brcBitRate*2/80);    
  }	  
  
  rc_init_seq(&seq->bRC, & seq->encPar);  
  
  if(seq->encPar.brcBitRate!= 0) {		
    if(seq->encPar.useSEIMessages) {

      /* Currently, only base view has VUI */
      fillHRDParameters(&seq->bRC, &seq->sps[0].vui_parameters.vcl_hrd_parameters);
      fillBufferingPeriodSEI(&seq->bRC);
    }
  }
  
  /* initialize dpb buffer */
  dpbInitialize(& seq->dpbBuf, pEncPar);
  
  /*
   * Open bitbuffer. Decide bitbuffer initial size
   */
  
  /* Initial bit buffer size is frame_width*frame_heigth/4 rounded up to nearest kilobyte */
  bitBufInitialSize = 3*(pEncPar->picWidth * pEncPar->picHeight/8);
  
  bibOpen(& seq->bitbuf, bitBufInitialSize);
  
  /*
   * Clear statistics
   */
  staClear(& seq->intraStat);
  staClear(& seq->interStat);
  staNonSliceClear(&seq->nonSliceStat);
  
#if MOTION_FIELD_DRAWING
  if (pEncPar->makeMotField) 
    frmOpen(& seq->recoBufMotField, pEncPar->picWidth, pEncPar->picHeight);
#endif
  
  /*
   * Initialize the Parameter Set. 
   */
  
  // do additional check on parameters for slice definition
  psValidateSliceParams(pEncPar);

  /* Fill out the SPS and PPS sets */
  for(i=0; i<seq->numSPS; i++)
    psFillSPSSetStructures( & seq->sps[i], pEncPar, i);
  for(i=0; i<seq->numPPS; i++)
    psFillPPSSetStructures( seq->sps[0], & seq->pps[i], pEncPar, i);
  
  for(j = 0; j < seq->numSPS; j++) {
    
    /* If this is baseline/extended profile and level is <= 3.0, */
    /* we must enable sub-macroblock rect size checking         */
    if ((seq->sps[j].profile_idc == PS_BASELINE_PROFILE_IDC ||
      seq->sps[j].profile_idc != PS_EXTENDED_PROFILE_IDC) &&
      seq->sps[j].level_idc <= 30)
      seq->slice.meProfile.subMbRectSizeFlag = 1;
    else
      seq->slice.meProfile.subMbRectSizeFlag = 0;
    
    /* Set maximum vertical motion vector range according to level limitation */
    if (seq->sps[j].level_idc <= 10)
      seq->slice.meProfile.maxVerticalMvRange = 64;
    else if (seq->sps[j].level_idc <= 20)
      seq->slice.meProfile.maxVerticalMvRange = 128;
    else if (seq->sps[j].level_idc <= 30)
      seq->slice.meProfile.maxVerticalMvRange = 256;
    else
      seq->slice.meProfile.maxVerticalMvRange = 512;
  }
  
  /* Send the sequence parameter set to the bitbuffer */
  seq->nonSliceStat.bitsSPS += psSendSeqParameterSet
    (& seq->bitbuf, & seq->sps[0], & seq->nonSliceStat.bitsNAL, &seq->rtpPacket);
  
  if (useMVC)
  {
    /* For all other views than base view, send subset SPS */
    for (i=1; i<seq->numSPS; i++) {

      /* Add Subset SPS bits to SPS bits */
      seq->nonSliceStat.bitsSPS += psSendSubsetSeqParameterSet
        ( & seq->sps[i], & seq->bitbuf, & seq->nonSliceStat.bitsNAL, &seq->rtpPacket);
    }
  }
  
  /* Send all the PPS sets to the bitbuffer */
  for(i=0; i<seq->numPPS; i++) {
    seq->nonSliceStat.bitsPPS += psSendPicParameterSet
      (& seq->bitbuf, & seq->pps[i], & seq->nonSliceStat.bitsNAL, &seq->rtpPacket);
  }
  
  if(param->useSEIMessages)
    seq->nonSliceStat.bitsSEI += sendBufferingPeriodSEIMessage(&seq->bitbuf,&seq->bRC.bufperiodSEI,&seq->sps[0].vui_parameters.vcl_hrd_parameters, &seq->nonSliceStat.bitsNAL);  
  
  seq->slice.mbksPerLine  = (int16) (seq->encPar.picWidth/MBK_SIZE);
  seq->slice.mbksPerCol   = (int16) (seq->encPar.picHeight/MBK_SIZE);
  seq->slice.picSizeInMbs = (int16) (seq->slice.mbksPerLine * seq->slice.mbksPerCol);
  seq->slice.mbStateArr   = seq->mbData.mbStateArr;
  seq->slice.bitbuf       = & seq->bitbuf;
  seq->slice.recoBuf      = & seq->recoFrm;
  
  mbkInit(& seq->slice.mb, seq->encPar.plr);
  
#ifdef ENABLE_SEARCH_WINDOW
  // internal search window init
  if (pEncPar->useSearchWin)
    searchWinInit( & seq->slice.meProfile.sWin , pEncPar->picWidth, pEncPar->picHeight,
    pEncPar->srx, pEncPar->sry);
  else
    seq->slice.meProfile.sWin.useSearchWin = 0;
#endif
  
  *nalBufSize = bibGetBuffer(&seq->bitbuf, nalBuffer);

  /* Reset bit buffer to empty state. This does not delete contents of bit buffer */
  bibInit(&seq->bitbuf);
  
  return seq;
}


/*
 * seqClose:
 *
 * Parameters:
 *      seq                   Encoder sequence to be closed
 *
 * Function:
 *      Deinitializes sequence by closing files and deallocating memory
 *      
 * Returns:
 *      -
 */
void avceClose(avceEncoder_t *pSeq)
{
  sequence_s *seq;
  int i;


  seq = (sequence_s *) pSeq;

  vlcuSendEndOfSeq(&seq->bitbuf);

  frmClose(& seq->recoFrm);
  frmEncBufClose(& seq->mbData);
  rc_free_mem(&seq->bRC);

  dpbRelease(& seq->dpbBuf, seq->encPar.low_complex_prof3
#ifdef ENABLE_SEARCH_WINDOW
    , seq->encPar.useSearchWin
#endif
    );
  mbkRelease(& seq->slice.mb);

  bibClose(& seq->bitbuf);

  /* Accumulate & output statistics of intra and inter frames */
#if PRINT_DETAILED_SEQ_STATISTICS
  printIntraStat(&seq->intraStat, stdout);
  deb0f(stdout, "\n");
  printInterStat(&seq->interStat, stdout);
#endif

#if MOTION_FIELD_DRAWING
  if (seq->encPar.makeMotField)
    frmClose(& seq->recoBufMotField);
#endif

  for(i=0; i<seq->numPPS; i++)
	  psClosePictureParameterSet(& seq->pps[i]);

  for(i=0; i<seq->numSPS; i++)
	  psCloseSequenceParameterSet(& seq->sps[i]);

#ifdef ENABLE_SEARCH_WINDOW
  // clean up internal search window
  if (seq->slice.meProfile.sWin.useSearchWin)
    searchWinFinish( & seq->slice.meProfile.sWin );
#endif
  nccFree(seq->forcedIR);
  nccFree(seq->AIR_intraMap);

  nccFree(seq);
}


#if  PRINT_DETAILED_SEQ_STATISTICS
/*
 * printIntraStat
 *
 * Parameters:
 *      intraStat             Intra statistics
 *      fp                    Destination stream
 *
 * Function:
 *      Print intra statistics
 *
 * Returns:
 *      -
 */
static void printIntraStat(statSlice_s *intraStat, FILE *fp)
{
  int i;


  deb0f(fp, "INTRA\n-----\n");
  deb1f(fp, "Intra 4x4:            %i\n", intraStat->intraModeCtr1);
  for (i = 0; i < 4; i++)
    deb2f(fp, "Intra 16x16 mode %2i:  %i\n", i, intraStat->intraModeCtr2[i]);

  deb0f(fp, "\n");
  deb1f(fp, "Hdr:           %i\n", intraStat->bitsHdr);
  deb1f(fp, "Modeinfo:      %i\n", intraStat->bitsPred);
  deb1f(fp, "CBP:           %i\n", intraStat->bitsCBP);
  deb1f(fp, "Coef Y:        %i\n", (intraStat->bitsCoefLumaDC+intraStat->bitsCoefLuma));
  deb1f(fp, "Coef C:        %i\n", (intraStat->bitsCoefChromaDC+intraStat->bitsCoefChroma));
}


/*
 * printInterStat
 *
 * Parameters:
 *      intraStat             Inter statistics
 *      fp                    Destination stream
 *
 * Function:
 *      Print inter statistics
 *
 * Returns:
 *      -
 */
static void printInterStat(statSlice_s *interStat, FILE *fp)
{
  int i;

  interStat->nFrames = max(1, interStat->nFrames);

  deb0f(fp, "\nINTER\n-----\n");
  for (i = 0; i < 8; i++)
    deb2f(fp, "Inter mode %i:         %i\n", i, interStat->interModeCtr[i]);
  deb1f(fp, "Intra 4x4:            %i\n", interStat->intraModeCtr1);
  for (i = 0; i < 4; i++)
    deb2f(fp, "Intra 16x16 mode %2i:  %i\n", i, interStat->intraModeCtr2[i]);

  deb0f(fp, "\n");
  deb1f(fp, "Hdr:           %i\n", interStat->bitsHdr/interStat->nFrames);
  deb1f(fp, "CBP:           %i\n", interStat->bitsCBP/interStat->nFrames);
  deb1f(fp, "Coef Y:        %i  ", (interStat->bitsCoefLumaDC+interStat->bitsCoefLuma+interStat->bitsVec)/interStat->nFrames);
  deb1f(fp, "(Vecs: %i)\n", interStat->bitsVec/interStat->nFrames);
  deb1f(fp, "Coef C:        %i\n", (interStat->bitsCoefChromaDC+interStat->bitsCoefChroma)/interStat->nFrames);
  fp = 0;  /* Avoid warnings */
}
#endif  /* #if PRINT_DETAILED_SEQ_STATISTICS */


/*
 * avceGetIntraStat, avceGetInterStat, avceGetSeqStat
 *
 * Parameters:
 *      seq                   Encoder instance
 *
 * Function:
 *      Get statistics for intra/inter/all frames
 *      
 * Returns:
 *      Statistics
 */
void avceGetIntraStat(avceEncoder_t *seq, avceStatistics_s *stat)
{
  getStat(stat, & ((sequence_s *) seq)->intraStat);
}


void avceGetInterStat(avceEncoder_t *seq, avceStatistics_s *stat)
{
  getStat(stat, & ((sequence_s *) seq)->interStat);
}


void avceGetSeqStat(avceEncoder_t *seq, avceStatistics_s *stat)
{
  statSlice_s seqStat;


  staClear(&seqStat);
  staAccumulate(&seqStat, & ((sequence_s *) seq)->intraStat);
  staAccumulate(&seqStat, & ((sequence_s *) seq)->interStat);

  // statistics of encoded frames
  getStat(stat, &seqStat);

  // statistics of NAL, Sequence PS, Picture PS,
  stat->bits += ((sequence_s *) seq)->nonSliceStat.bitsNAL;
  stat->bits += ((sequence_s *) seq)->nonSliceStat.bitsPPS;
  stat->bits += ((sequence_s *) seq)->nonSliceStat.bitsSEI;
  stat->bits += ((sequence_s *) seq)->nonSliceStat.bitsSPS;
}


void avceGetFrmStat(avceEncoder_t *seq, avceStatistics_s *stat)
{
  stat->bits = staGetTotalBits(& ((sequence_s *) seq)->frmStat);
  stat->psnrY = ((sequence_s *) seq)->frmStat.psnrY;
  stat->psnrU = ((sequence_s *) seq)->frmStat.psnrU;
  stat->psnrV = ((sequence_s *) seq)->frmStat.psnrV;
  stat->bufFullness = ((sequence_s *) seq)->bRC.actualBufferFullness/8;
  stat->numIntraMbs = ((sequence_s *) seq)->bRC.numIntraMBs;
}


int avceGetBitsNAL(avceEncoder_t *seq)
{
  return ((sequence_s *) seq)->nonSliceStat.bitsNAL;
}


int avceGetBitsSPS(avceEncoder_t *seq)
{
  return ((sequence_s *) seq)->nonSliceStat.bitsSPS;
}


int avceGetBitsPPS(avceEncoder_t *seq)
{
  return ((sequence_s *) seq)->nonSliceStat.bitsPPS;
}


static void getStat(avceStatistics_s *retStat, statSlice_s *stat)
{
  retStat->psnrY = stat->psnrY;
  retStat->psnrU = stat->psnrU;
  retStat->psnrV = stat->psnrV;
  retStat->bits = staGetTotalBits(stat);
  retStat->nFrames = stat->nFrames;
}


/*
 * calcFrmError
 *
 * Parameters:
 *      orig                  Original pixels
 *      reco                  Reconstructed pixels
 *      width                 Width of the frame
 *      height                Height of the frame
 *
 * Function:
 *      Calculates PSNR error between two framebuffers.
 *
 * Returns:
 *      -
 */
static double calcFrmError(u_int8 *orig, u_int8 *reco, int width, int height)
{
  double sqSum;
  int32 sqSumLine;
#ifndef X86MMX
  int diff;
  int i, j, j2;
#endif

#ifdef X86MMX

  __asm {

    fldz
    fstp    QWORD PTR [sqSum]      ;sqSum = 0.0

    mov     eax,[orig]
    mov     ecx,[reco]
    mov     edx,[width]
    mov     ebx,[height]

calcFrmError_loop0:

    mov     esi,edx

    pxor    mm6,mm6
    pcmpeqd mm7, mm7              ;0xffffffffffffffff
    psrld   mm7, 16               ;0x0000ffff0000ffff

    pxor    mm5,mm5               ;sqSumLine = 0

calcFrmError_loop1:

    movd    mm0,[eax]
    movd    mm1,[ecx]
    punpcklbw mm0,mm6
    punpcklbw mm1,mm6
    psubw   mm0,mm1
    pmaddwd mm0,mm0

    movd    mm1,[eax+4]
    movd    mm2,[ecx+4]
    punpcklbw mm1,mm6
    punpcklbw mm2,mm6
    psubw   mm1,mm2
    pmaddwd mm1,mm1

    add     eax,8                 ;next 8 pixels
    add     ecx,8

    paddd   mm5,mm0
    paddd   mm5,mm1

    sub     esi,1
    jnz     calcFrmError_loop1

    PSHUFW(0,5,0x0e)              ;sum up upper and lower 32-bit halves
    paddd   mm0,mm5               ;-''-
    movd    [sqSumLine],mm0

    emms

    fild    DWORD PTR [sqSumLine]
    fadd    QWORD PTR [sqSum]     ;sqSum += sqSumLine;
    fstp    QWORD PTR [sqSum]

    sub     ebx,8                 ;next 8 lines
    jnz     calcFrmError_loop0

  }

#else

  for (sqSum = 0.0, j = 0; j < height; j += 8) {
    for (sqSumLine = 0, j2 = j; j2 < j+8; j2++) {
      for (i = 0; i < width; i += 4) {
        diff = (int)orig[j2*width+i+0] - (int)reco[j2*width+i+0];
        sqSumLine += (int32)diff*diff;
        diff = (int)orig[j2*width+i+1] - (int)reco[j2*width+i+1];
        sqSumLine += (int32)diff*diff;
        diff = (int)orig[j2*width+i+2] - (int)reco[j2*width+i+2];
        sqSumLine += (int32)diff*diff;
        diff = (int)orig[j2*width+i+3] - (int)reco[j2*width+i+3];
        sqSumLine += (int32)diff*diff;
      }
    }
    sqSum += sqSumLine;
  }

#endif

  if (sqSum == 0)
    sqSum = 1;
  
  return (10.0*log10(width*height*65025.0/sqSum));
}


/*
 * calcRecoError
 *
 * Parameters:
 *      f                     Reconstructed frame buffer
 *      orig                  Original frame buffer
 *      stat                  Statistics
 *
 * Function:
 *      Calculates frame reconstruction error for Y, U and V components.
 *
 * Returns:
 *      -
 */
static void calcRecoError(frmBuf_s *reco, frmBuf_s *orig, statSlice_s *stat)
{
  stat->psnrY += calcFrmError(orig->y, reco->y, reco->width,   reco->height);
  stat->psnrU += calcFrmError(orig->u, reco->u, reco->width/2, reco->height/2);
  stat->psnrV += calcFrmError(orig->v, reco->v, reco->width/2, reco->height/2);
}


/*
 * seqEncode:
 *
 * Parameters:
 *      seq                   Encoder instance
 *      origPic               YUV buffers for original frame
 *      recoPic               YUV buffers for reconstruction frame
 *      intraFlag             1 -> Intra, 0 -> Inter
 *      qp                    Quantization parameter
 *      srcPicNum             Source picture index
 *      nalBuffer             Return pointer for nal bits buffer
 *      nalBufSize            Return pointer for nal buffer size
 *      viewId                Current view's id
 *
 * Function:
 *      Encode sequence using parameters in seq structure.
 *      
 * Returns:
 *      AVCE_ERROR          for error
 *      AVCE_OK             for ok
 *      AVCE_FRAME_SKIPPED  for frame got skipped
 */
int avceEncodeOneFrame(avceEncoder_t *pSeq, avceYUVbuffer_s *origPic,
                       avceYUVbuffer_s *recoPic, int intraFlag, 
                       int idrFlag, int scutFlag, int nalRefIdc, int ltrCandidate,
                       int srcPicNum, int qp, void **nalBuffer, int *nalBufSize, int viewId) 
{
  frmBuf_s origBuf;
  statSlice_s *seqStat;
  statSlice_s *frmStat;
  int numIntraMbs, numMbsPerFrm;
  slice_s *slice;
  int i;
  int textureBits,headerBits;
#ifdef ENABLE_REENCODE
  int maxreencode=5;
#endif
  sequence_s *seq;


  seq = (sequence_s *) pSeq;
  frmStat = & seq->frmStat;
  slice   = & seq->slice;

  slice->viewId = viewId;

  origBuf.width  = (int16) (seq->encPar.picWidth);
  origBuf.height = (int16) (seq->encPar.picHeight);
  origBuf.y = origPic->y;
  origBuf.u = origPic->u;
  origBuf.v = origPic->v;
  numMbsPerFrm = (seq->encPar.picWidth/16) * (seq->encPar.picHeight/16);

  seq->bRC.scut = scutFlag;
  if(seq->encPar.brcBitRate!=0)
     seq->bRC.scut = scutFlag;

  if (idrFlag)
  {
    seq->lastIdrTr  = srcPicNum;
    slice->idrPicId = seq->nextIdrPicId;
    seq->nextIdrPicId = (int16)((seq->nextIdrPicId + 1) & 0x0F);
  }

  /* Select slice type and number of reference frames for inter frames */
  if (intraFlag) {
    slice->sliceType = SLICE_I;
    seqStat = &seq->intraStat;
  }
  else {
    slice->sliceType = SLICE_P;
    seqStat = &seq->interStat;
  }
  
  rc_init_pict(& seq->bRC,slice->sliceType,nalRefIdc,srcPicNum);
  
  if(seq->bRC.useSEI)
    seq->nonSliceStat.bitsSEI += sendPictureTimingSEIMessage(&seq->bitbuf,&seq->bRC.picture_timing_SEI,&seq->sps[0].vui_parameters.vcl_hrd_parameters, &seq->nonSliceStat.bitsNAL);

  dbpBeforeEncodeFrame(& seq->dpbBuf, nalRefIdc, idrFlag, ltrCandidate, slice->viewId);

  // Set a different sliceGroupCycle, for slice group types 3 to 5 
  // sliceGroupCycle is an syntax element in slice header
  // Just an example of changing sliceGroupCycle from one frame to the next
  if (seq->pps[viewId].slice_group_map_type >= 3 && seq->pps[viewId].slice_group_map_type <= 5) {
    int sliceGroupCycleLimit;

    // calculate maximum sliceGroupCycle allowed, with ceiling operation
    sliceGroupCycleLimit = (seq->slice.picSizeInMbs + seq->pps[viewId].slice_group_change_rate_minus1)/
      (seq->pps[viewId].slice_group_change_rate_minus1 + 1);

    // larger than that does not make sense, and may not be represented properly
    if (seq->sliceGroupCycle >= sliceGroupCycleLimit)
      seq->sliceGroupCycle = 0;
    else
      seq->sliceGroupCycle ++;

    slice->sliceGroupChangeCycle = seq->sliceGroupCycle;
  }

  slice->origBuf   = & origBuf;
  slice->isIDR     = (int16) idrFlag;
  slice->poc       = (int16) (srcPicNum - seq->lastIdrTr);
  slice->qp        = (int16) qp;
  slice->nalRefIdc = (int16) nalRefIdc;
  slice->frmStat   = frmStat;    /* Have been cleared */

  // set up low complexity prof 3
  slice->meProfile.lc3.low_complex_prof3 = seq->encPar.low_complex_prof3;
  slice->meProfile.lc3.spec_search_pos = seq->encPar.spec_search_pos;

#ifdef ENABLE_SEARCH_WINDOW
  // set up internal search window
  slice->meProfile.sWin.picHeight = seq->recoFrm.height;
  slice->meProfile.sWin.picWidth = seq->recoFrm.width;
#endif

  /* Clear frame statistics */
  staClear(frmStat);

  if (slice->recoBuf->channelDistortion)
  memset(slice->recoBuf->channelDistortion, 0, sizeof(int)*numMbsPerFrm);

  memset(seq->AIR_intraMap,0 , sizeof(int)*numMbsPerFrm);

   if(seq->encPar.irType == PDT_IR_LC && seq->encPar.nAIR > 0 && idrFlag == 0 && intraFlag == 0)
    // Compute The Intra MAP
    compute_AIRMAP(seq->AIR_intraMap,seq->dpbBuf.refFrmArr[0].channelDistortion,seq->nAIR,numMbsPerFrm);

  if(seq->bRC.bit_rate > 0)
  {
    slice->qp = (int16)rc_getFrameQP(& seq->bRC,slice->sliceType);

    /* Encode frame */
    numIntraMbs = frmEncode(slice, & seq->dpbBuf, 
      &seq->encPar, &seq->mbData, &seq->sps[viewId], &seq->pps[viewId], seq->forcedIRNo, seq->forcedIR, &seq->bRC,&seq->rtpPacket,seq->AIR_intraMap);

    textureBits=
      frmStat->bitsCoefLumaDC +
      frmStat->bitsCoefLuma +
      frmStat->bitsCoefChromaDC +
      frmStat->bitsCoefChroma +
      frmStat->bitsArithmeticStream;  

    headerBits=
      frmStat->bitsNAL +
      frmStat->bitsHdr +
      frmStat->bitsSkipLen +
      frmStat->bitsMBtype +
      frmStat->bitsPred +
      frmStat->bitsVec +
      frmStat->bitsCBP;

#ifdef ENABLE_REENCODE
    if(seq->bRC.PictureIndex == 0) {
      if(seq->bRC.ignoreIDR==0 && 1.5*(seq->bRC.CurrentBufferFullness + textureBits + headerBits - seq->bRC.bitsPerFrame) > seq->bRC.BufferSize) {
        while( 1.5*(seq->bRC.CurrentBufferFullness + textureBits + headerBits - seq->bRC.bitsPerFrame) > seq->bRC.BufferSize) {

          //Buffer Overflow and I picture
          bibInit(&seq->bitbuf);
          if(seq->bRC.useSEI)
            sendPictureTimingSEIMessage(&seq->bitbuf,&seq->bRC.picture_timing_SEI,&seq->sps.vui_parameters.vcl_hrd_parameters, &seq->nonSliceStat.bitsNAL);
          
          staClear(frmStat);
          seq->bRC.numIntraMBs = 0;
          
          seq->bRC.stat_NumberofReencodes++;
#ifdef DEBUG_PRINT
          printf("REENCODE\n");
#endif
          slice->qp = seq->bRC.frameComputedQP+2;
          seq->bRC.frameComputedQP = slice->qp;
          seq->bRC.frameReturnedQP = slice->qp;
          
          numIntraMbs = frmEncode(slice, & seq->dpbBuf, 
            &seq->encPar, &seq->mbData, &seq->sps, &seq->pps, seq->forcedIRNo, seq->forcedIR, &seq->bRC, &seq->rtpPacket,seq->AIR_intraMap);
          
          textureBits=
            frmStat->bitsCoefLumaDC +
            frmStat->bitsCoefLuma +
            frmStat->bitsCoefChromaDC +
            frmStat->bitsCoefChroma +
            frmStat->bitsArithmeticStream;  
          
          headerBits=
            frmStat->bitsNAL +
            frmStat->bitsHdr +
            frmStat->bitsSkipLen +
            frmStat->bitsMBtype +
            frmStat->bitsPred +
            frmStat->bitsVec +
            frmStat->bitsCBP;
        }
      }
      else if(textureBits + headerBits < seq->bRC.bitsPerFrame*seq->bRC.I_P_RATIO) {
        maxreencode=5;
        while( textureBits + headerBits < seq->bRC.bitsPerFrame*seq->bRC.I_P_RATIO && maxreencode>0) {
          maxreencode--;
          bibInit(&seq->bitbuf);
          
          if(seq->bRC.useSEI)
            sendPictureTimingSEIMessage(&seq->bitbuf,&seq->bRC.picture_timing_SEI,&seq->sps.vui_parameters.vcl_hrd_parameters, &seq->nonSliceStat.bitsNAL);
          
          staClear(frmStat);
          seq->bRC.numIntraMBs = 0;
          
          seq->bRC.stat_NumberofReencodes++;
#ifdef DEBUG_PRINT
          printf("REENCODE\n");
#endif
          seq->bRC.frameComputedQP -=2;
          seq->bRC.frameReturnedQP = seq->bRC.frameComputedQP;
          slice->qp = seq->bRC.frameComputedQP;
          
          numIntraMbs = frmEncode(slice, & seq->dpbBuf, 
            &seq->encPar, &seq->mbData, &seq->sps, &seq->pps, seq->forcedIRNo, seq->forcedIR, &seq->bRC, &seq->rtpPacket,seq->AIR_intraMap);
          
          textureBits=
            frmStat->bitsCoefLumaDC +
            frmStat->bitsCoefLuma +
            frmStat->bitsCoefChromaDC +
            frmStat->bitsCoefChroma +
            frmStat->bitsArithmeticStream;  
          
          headerBits=
            frmStat->bitsNAL +
            frmStat->bitsHdr +
            frmStat->bitsSkipLen +
            frmStat->bitsMBtype +
            frmStat->bitsPred +
            frmStat->bitsVec +
            frmStat->bitsCBP;			
        }
      }
    }
    else if(slice->sliceType == SLICE_I) {
      maxreencode=5;
      if(seq->bRC.CurrentBufferFullness + textureBits + headerBits - seq->bRC.bitsPerFrame) {
        while((seq->bRC.CurrentBufferFullness + textureBits + headerBits - seq->bRC.bitsPerFrame > seq->bRC.BufferSize && maxreencode>0)) {
          maxreencode--;
          //Buffer Overflow and I picture
          bibInit(&seq->bitbuf);
          
          if(seq->bRC.useSEI)
            sendPictureTimingSEIMessage(&seq->bitbuf,&seq->bRC.picture_timing_SEI,&seq->sps.vui_parameters.vcl_hrd_parameters, &seq->nonSliceStat.bitsNAL);
          
          staClear(frmStat);
          seq->bRC.numIntraMBs = 0;
          
          seq->bRC.stat_NumberofReencodes++;
#ifdef DEBUG_PRINT
          printf("REENCODE\n");
#endif
          slice->qp = (int16)MIN(seq->bRC.frameComputedQP+2,51);
          seq->bRC.frameComputedQP = slice->qp;
          seq->bRC.frameReturnedQP = slice->qp;
          numIntraMbs = frmEncode(slice, & seq->dpbBuf, 
            &seq->encPar, &seq->mbData, &seq->sps, &seq->pps, seq->forcedIRNo, seq->forcedIR, &seq->bRC,&seq->rtpPacket,seq->AIR_intraMap);
          
          textureBits=
            frmStat->bitsCoefLumaDC +
            frmStat->bitsCoefLuma +
            frmStat->bitsCoefChromaDC +
            frmStat->bitsCoefChroma +
            frmStat->bitsArithmeticStream;  
          
          headerBits=
            frmStat->bitsNAL +
            frmStat->bitsHdr +
            frmStat->bitsSkipLen +
            frmStat->bitsMBtype +
            frmStat->bitsPred +
            frmStat->bitsVec +
            frmStat->bitsCBP;
        }
      }
    }
    else
    {
      maxreencode=5;
      while((seq->bRC.CurrentBufferFullness + textureBits + headerBits - seq->bRC.bitsPerFrame > seq->bRC.BufferSize && slice->sliceType == SLICE_P && maxreencode>0)) {
        maxreencode--;      
        bibInit(&seq->bitbuf);
        
        if(seq->bRC.useSEI)
          sendPictureTimingSEIMessage(&seq->bitbuf,&seq->bRC.picture_timing_SEI,&seq->sps.vui_parameters.vcl_hrd_parameters, &seq->nonSliceStat.bitsNAL);

        staClear(frmStat);
        seq->bRC.numIntraMBs = 0;
        
        seq->bRC.stat_NumberofReencodes++;
#ifdef DEBUG_PRINT
        printf("REENCODE\n");
#endif
        slice->qp = (int16)(MIN(seq->bRC.frameComputedQP+2,51));
        seq->bRC.frameComputedQP = slice->qp;
        seq->bRC.frameReturnedQP = slice->qp;
        numIntraMbs = frmEncode(slice, & seq->dpbBuf, 
          &seq->encPar, &seq->mbData, &seq->sps, &seq->pps, seq->forcedIRNo, seq->forcedIR, &seq->bRC,&seq->rtpPacket,seq->AIR_intraMap);
        
        textureBits=
          frmStat->bitsCoefLumaDC +
          frmStat->bitsCoefLuma +
          frmStat->bitsCoefChromaDC +
          frmStat->bitsCoefChroma +
          frmStat->bitsArithmeticStream;  
        
        headerBits=
          frmStat->bitsNAL +
          frmStat->bitsHdr +
          frmStat->bitsSkipLen +
          frmStat->bitsMBtype +
          frmStat->bitsPred +
          frmStat->bitsVec +
          frmStat->bitsCBP;
        
      }
    }
 
    if((seq->bRC.SPPPictureCounter!=0) && ( seq->bRC.TotalFrameBits>seq->bRC.upperFrameLimit*1.2 || seq->bRC.TotalFrameBits<seq->bRC.lowerFrameLimit*0.8 ) && (fabs(seq->bRC.averageQPforFrame - seq->bRC.frameComputedQP*1.0) > 4)) {
      if(!(seq->bRC.TotalFrameBits<seq->bRC.lowerFrameLimit*0.8 && !(seq->bRC.bufferStall == 0 || seq->bRC.CurrentBufferFullness*1.0/seq->bRC.BufferSize > 0.1))) {
        //do not reencode low-complexity frames unless critical buffer situation  
        bibInit(&seq->bitbuf);
        
        if(seq->bRC.useSEI)
          sendPictureTimingSEIMessage(&seq->bitbuf,&seq->bRC.picture_timing_SEI,&seq->sps.vui_parameters.vcl_hrd_parameters, &seq->nonSliceStat.bitsNAL);
        
        staClear(frmStat);
        seq->bRC.numIntraMBs = 0;
        
        seq->bRC.stat_NumberofReencodes++;
#ifdef DEBUG_PRINT
        printf("REENCODE\n");
#endif
        slice->qp = (int16)(seq->bRC.averageQPforFrame+0.5);
        seq->bRC.frameComputedQP = (int)(seq->bRC.averageQPforFrame+0.5);
        numIntraMbs = frmEncode(slice, & seq->dpbBuf, 
          &seq->encPar, &seq->mbData, &seq->sps, &seq->pps, seq->forcedIRNo, seq->forcedIR, &seq->bRC,&seq->rtpPacket);
      }
    }

#else

    if(seq->encPar.frameSkipEnabled >= 1) {
      
      if( seq->bRC.PictureIndex == 0 && seq->bRC.bit_rate > 0 && seq->bRC.ignoreIDR == 0) {
        slice->qp = (short) seq->bRC.InitialQP;   
        while((rc_update_pict(&seq->bRC,slice->sliceType, textureBits, headerBits,(float)frmStat->psnrY) == AVCE_FRAME_SKIPPED)) {
          //Buffer Overflow and I picture
          bibInit(&seq->bitbuf);
          
          if(seq->bRC.useSEI)
            sendPictureTimingSEIMessage(&seq->bitbuf,&seq->bRC.picture_timing_SEI,&seq->sps[0].vui_parameters.vcl_hrd_parameters, &seq->nonSliceStat.bitsNAL);
          
          staClear(frmStat);
          seq->bRC.numIntraMBs = 0;
          seq->bRC.PictureIndex--;    
          seq->bRC.stat_NumberofReencodes++;

          printf("REENCODE1: %d\n",seq->bRC.numConsecutiveSkips);
          
          slice->qp= (short) (seq->bRC.InitialQP+seq->bRC.stat_NumberofReencodes);
          seq->bRC.frameComputedQP = slice->qp;
          seq->bRC.frameReturnedQP = slice->qp;

          numIntraMbs = frmEncode(slice, & seq->dpbBuf, 
            &seq->encPar, &seq->mbData, &seq->sps[viewId], &seq->pps[viewId], seq->forcedIRNo, seq->forcedIR, &seq->bRC,&seq->rtpPacket,seq->AIR_intraMap);
          
          textureBits=
            frmStat->bitsCoefLumaDC +
            frmStat->bitsCoefLuma +
            frmStat->bitsCoefChromaDC +
            frmStat->bitsCoefChroma +
            frmStat->bitsArithmeticStream;  
          
          headerBits=
            frmStat->bitsNAL +
            frmStat->bitsHdr +
            frmStat->bitsSkipLen +
            frmStat->bitsMBtype +
            frmStat->bitsPred +
            frmStat->bitsVec +
            frmStat->bitsCBP;
        }
        seq->bRC.PictureIndex--;
      }
    }
#endif
  }
  else
    numIntraMbs = frmEncode(slice, & seq->dpbBuf, 
    &seq->encPar, &seq->mbData, &seq->sps[viewId], &seq->pps[viewId], seq->forcedIRNo, seq->forcedIR, &seq->bRC,&seq->rtpPacket,seq->AIR_intraMap);

  if (slice->sliceType == SLICE_P)
  {
    numMbsPerFrm = (seq->encPar.picWidth/16) * (seq->encPar.picHeight/16);
    
    if (((seq->encPar.scIntra == 1) && (numIntraMbs == numMbsPerFrm)) ||
      ((seq->encPar.scIntra == 2) && (numIntraMbs >= (numMbsPerFrm * 95)/100)))
    {
      bibInit(&seq->bitbuf);
      
      if(seq->bRC.useSEI)
          sendPictureTimingSEIMessage(&seq->bitbuf,&seq->bRC.picture_timing_SEI,&seq->sps[0].vui_parameters.vcl_hrd_parameters, &seq->nonSliceStat.bitsNAL);
      
      slice->sliceType = SLICE_I;
      
      // we re-encode this frame as intra frame
      // Clear frame statistics
      staClear(frmStat);
      
      if(seq->bRC.bit_rate > 0) {
        slice->qp = (int16)rc_getFrameQP(& seq->bRC,slice->sliceType);
        
        frmEncode(slice, & seq->dpbBuf, &seq->encPar, &seq->mbData, &seq->sps[viewId], 
          &seq->pps[viewId], seq->forcedIRNo, seq->forcedIR, &seq->bRC,&seq->rtpPacket,seq->AIR_intraMap);
      }
      else
        frmEncode(slice, & seq->dpbBuf, &seq->encPar, &seq->mbData, &seq->sps[viewId], 
        &seq->pps[viewId], seq->forcedIRNo, seq->forcedIR, &seq->bRC,&seq->rtpPacket,seq->AIR_intraMap);
    }
  }

  calcRecoError(& seq->recoFrm, & origBuf, frmStat);

#if MOTION_FIELD_DRAWING
  if (IS_SLICE_P(slice->sliceType) && seq->encPar.makeMotField) {
    /* Draw motion field to the reconstructed picture */
    frmDrawMotField(& seq->mbData, & seq->recoBufMotField);

    recoPic->y = seq->recoBufMotField.y;
    recoPic->u = seq->recoBufMotField.u;
    recoPic->v = seq->recoBufMotField.v;
  }
  else
#endif
  {
    /* Return reconstructed frame buffer to the caller */
    recoPic->y = seq->recoFrm.y;
    recoPic->u = seq->recoFrm.u;
    recoPic->v = seq->recoFrm.v;
  }

  /* Update statistics */
  frmStat->nFrames = 1;

  textureBits=
    frmStat->bitsCoefLumaDC +
    frmStat->bitsCoefLuma +
    frmStat->bitsCoefChromaDC +
    frmStat->bitsCoefChroma +
    frmStat->bitsArithmeticStream;  

  headerBits=
    frmStat->bitsNAL +
    frmStat->bitsHdr +
    frmStat->bitsSkipLen +
    frmStat->bitsMBtype +
    frmStat->bitsPred +
    frmStat->bitsVec +
    frmStat->bitsCBP;

  i = rc_update_pict(&seq->bRC,slice->sliceType, textureBits, headerBits,(float)frmStat->psnrY);
  
  if( i != AVCE_FRAME_SKIPPED && numIntraMbs == AVCE_FRAME_SKIP_SLICE_OVERFLOW)
    i = AVCE_FRAME_SKIPPED;

  if (i != AVCE_FRAME_SKIPPED)
  {
    staAccumulate(seqStat, frmStat);

    /* update dpb */
    dpbUpdate(& seq->dpbBuf, & seq->recoFrm, nalRefIdc, idrFlag, seq->encPar.low_complex_prof3
#ifdef ENABLE_SEARCH_WINDOW
      , slice->meProfile.sWin.useSearchWin
#endif
      , viewId);

#if 1

    /* Printf frame by frame statistics */
    deb5f(stderr, "%3i  snr: Y %2.2f  U: %2.2f  V: %2.2f  bits: %7i\n",
      srcPicNum, frmStat.psnrY, frmStat.psnrU, frmStat.psnrV,
      staGetTotalBits(&frmStat));
#endif

#ifdef RC_DEBUG
    if(seq->encPar.brcBitRate!= 0)
      rc_printDebug(&seq->bRC,frmStat);
#endif	

    /* Get NAL bit buffer pointer and bit buffer length in bytes */
    *nalBufSize = bibGetBuffer(&seq->bitbuf, nalBuffer);

    /* Reset bit buffer to empty state. This does not delete contents of bit buffer */
    bibInit(&seq->bitbuf);
  }
  else
  {
    // Frame skipped
    bibInit(&seq->bitbuf);
    staClear(frmStat);
    seq->dpbBuf.prevRefFrameNum--;
    seq->dpbBuf.frameNum--;
  }

  if(i==AVCE_FRAME_SKIPPED)
    return AVCE_FRAME_SKIPPED;
  else		
    return AVCE_OK;
}


/*
 * avceEncodeSceneInfo:
 *
 * Parameters:
 *      seq                   Encoder instance
 *      sceneId               The Scene ID
 *      nalBuffer             Return pointer for nal bits buffer
 *      nalBufSize            Return pointer for nal buffer size
 *
 * Function:
 *      Encode the scene information SEI message.
 *      
 * Returns:
 *      AVCE_ERROR          for error
 *      AVCE_OK             for ok
 */
int avceEncodeSceneInfo(avceEncoder_t *pSeq, int sceneId, void **nalBuffer, int *nalBufSize)
{
  int         byte;
  sequence_s  *seq;
  bitbuffer_s tmpBitbuf;
  bitbuffer_s *bitbuf;
  int         initialSize;
  int         payloadSize;


  seq = (sequence_s *) pSeq;

  bitbuf = &tmpBitbuf;
  initialSize = 500;    // hard coded

  bibOpen(bitbuf, initialSize);

  /* start code prefix */
  vlcuSendNalUnitStartCodePrefix(&seq->bitbuf, 1);

  /* NAL head */
  vlcuSendNalHead(&seq->bitbuf, 0, SEI_NAL_TYPE);

  /* 
   * BEGIN -- scene info payload 
   */
  payloadSize = 0;

  /* scene_info_present_flag (1) */
  byte = 1;
  payloadSize += u_n(bitbuf, byte, 1);

  /* scene id */
  payloadSize += ue_v(bitbuf, sceneId);

  /* scene transition type (0) */
  byte = 0;
  payloadSize += ue_v(bitbuf, byte);

  /* byte align */ 
  if (!bibIsByteAlign(bitbuf))
    payloadSize += bibTrailingBits(bitbuf);

  payloadSize = (payloadSize >> 3);

  /* 
   * write the scene info payload to SEI message
   */

  /* payload type (9) */
  bibPutByte(&seq->bitbuf, SEI_TYPE_SCENE_INFO);

  /* payload size */
  while (payloadSize > 255) {
    byte = 0xFF;
    bibPutByte(&seq->bitbuf, byte);
    payloadSize -= byte;
  }
  bibPutByte(&seq->bitbuf, payloadSize);

  /* copy the payload */
  memcpy(seq->bitbuf.bufAddr + seq->bitbuf.bytePos, bitbuf->bufAddr, bitbuf->bytePos);
  seq->bitbuf.bytePos += bitbuf->bytePos;

  /* 
   * END -- scene info payload 
   */
  bibTrailingBits(bitbuf);

  /* Get NAL bit buffer pointer and bit buffer length in bytes */
  *nalBufSize = bibGetBuffer(&seq->bitbuf, nalBuffer);

  /* Reset bit buffer to empty state. This does not delete contents of bit buffer */
  bibInit(&seq->bitbuf);

#if 1
  printf("Scene %d ....\n", sceneId);
#endif

  bibClose(bitbuf);

  return AVCE_OK;
}


void avceUpdateEncodingParameters(avceEncoder_t *encoder, avceOpenParams_s *param)
{
  sequence_s *seq;
  
  
  seq = (sequence_s *) encoder;
  
  // Update only the bitrate for now
  seq->encPar.brcBitRate = param->brcBitRate;
  rc_update_bitrate(& seq->bRC,seq->encPar.brcBitRate);  
}
