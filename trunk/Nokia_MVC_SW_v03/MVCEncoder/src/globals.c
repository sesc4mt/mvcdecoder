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

Any dispute relating to these Terms or the Code shall be submitted to binding arbitration in Westchester County, New York within eighteen (18) months of the date the facts giving rise to the suit were known, or should have been known, by the complainant, except that Nokia may seek injunctive or other relief if you have violated or threatened to violate any intellectual property rights. All matters relating to arbitration shall be governed by the Federal Arbitration Act (9 U.S.C. �1 et. seq.). Arbitration shall be conducted by a single arbitrator under the then prevailing Wireless Arbitration Rules of the American Arbitration Association (�AAA�). Each party must submit any claim which would constitute a compulsory counterclaim in litigation or such claim shall be barred. No award of exemplary, special, consequential or punitive damages shall be permitted. The losing party, as determined by the arbitrator, shall pay the arbitration fees. The arbitrator's award shall be binding and may be entered as a judgment and enforceable in any court of competent jurisdiction. Arbitration shall be conducted on an individual, not class-wide basis, and no arbitration shall be joined with an arbitration involving any other person or entity.

7.3 Severability

If any provision contained in these Terms is determined to be invalid or unenforceable, in whole or in part, the remaining provisions and any partially enforceable provision will, nevertheless, be binding and enforceable, and the parties agree to substitute for the invalid provision a valid provision which most closely approximates the intent and economic effect of the invalid provision.

7.4 Export Control

You shall follow all export control laws and regulations relating to the Code. You agree not to export or re-export, as the case may be, the Code to any country without obtaining licenses and permits that may be required under any applicable legislation or regulations.  You shall not license the Code or provide services, nor export or re-export any information, or any process, product or service that is produced under these Terms to any country specified as a prohibited destination in applicable national, state and local, regulations and ordi�nances, including the Regulations of the U.S. Department of Commerce and/or the U.S. State Department, without first obtaining government approval.
*/

/*
 *
 * globals.c
 *
 * Contains:
 *    Data and functions common to all modules
 *
 */

#include <string.h>
#include "globals.h"


/*
 * convert from H.263 QP to H.26L quant given by: quant = pow(2,QP/6)
 */
const int8 QP2QUANT[52] = {
               1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1,
   1, 1, 1, 1, 2, 2, 2, 2,
   3, 3, 3, 4, 4, 4, 5, 6,
   6, 7, 8, 9,10,11,13,14,
  16,17,20,23,25,29,32,36,
  40,45,51,57,64,72,81,91
};

/*
 * Chroma QP = qpChroma[Luma QP]
 */
const int8 qpChroma[52] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,
   12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,
   28,29,29,30,31,32,32,33,34,34,35,35,36,36,37,37,
   37,38,38,38,39,39,39,39
}; 


const int8 blkRasterOrder[16] = 
{
  0, 1, 4, 5, 2, 3, 6, 7, 8, 9, 12, 13, 10, 11, 14, 15,
};


const costMeasure_s initCostMeasure = {
  MAX_COST, MAX_COST, 0, 0, MAX_COST, MAX_COST, MAX_COST
};


/*
 *
 * staClear:
 *
 * Parameters:
 *      stat                  Statistics object
 *
 * Function:
 *      Zero out statistics
 *
 * Returns:
 *      -
 */
void staClear(statSlice_s *stat)
{
  memset(stat, 0, sizeof(statSlice_s));
}

void staNonSliceClear(statNonSliceNal_s *pstat)
{
  memset(pstat, 0, sizeof(statNonSliceNal_s));
}

/*
 *
 * staAccumulate:
 *
 * Parameters:
 *      stat1                 Statistics destination object
 *      stat2                 Statistics object
 *
 * Function:
 *      Add statistics from stat2 to stat1
 *
 * Returns:
 *      -
 */
void staAccumulate(statSlice_s *stat1, statSlice_s *stat2)
{
  int i;

  stat1->nFrames += stat2->nFrames;

  /*
   * Accumulate bits
   */
  stat1->bitsNAL          += stat2->bitsNAL;
  stat1->bitsHdr          += stat2->bitsHdr;
  stat1->bitsSkipLen      += stat2->bitsSkipLen;
  stat1->bitsMBtype       += stat2->bitsMBtype;
  stat1->bitsPred         += stat2->bitsPred;
  stat1->bitsVec          += stat2->bitsVec;
  stat1->bitsCBP          += stat2->bitsCBP;
  stat1->bitsCoefLumaDC   += stat2->bitsCoefLumaDC;
  stat1->bitsCoefLuma     += stat2->bitsCoefLuma;
  stat1->bitsCoefChromaDC += stat2->bitsCoefChromaDC;
  stat1->bitsCoefChroma   += stat2->bitsCoefChroma;
  stat1->bitsArithmeticStream += stat2->bitsArithmeticStream;

  /*
   * Accumulate modes
   */
  stat1->intraModeCtr1 += stat2->intraModeCtr1;
  for (i = 0; i < MAX_MODES; i++)
    stat1->intraModeCtr2[i] += stat2->intraModeCtr2[i];
  for (i = 0; i < MAX_MODES; i++)
    stat1->interModeCtr[i] += stat2->interModeCtr[i];

  /*
   * Accumulate psnr
   */
  stat1->psnrY += stat2->psnrY;
  stat1->psnrU += stat2->psnrU;
  stat1->psnrV += stat2->psnrV;
}


/*
 *
 * staGetTotalBits:
 *
 * Parameters:
 *      stat                  Statistics object
 *
 * Function:
 *      Get total number of bits in given statistics
 *
 * Returns:
 *      Number of bits
 *
 */
int staGetTotalBits(statSlice_s *stat)
{
  return (
    stat->bitsNAL +
    stat->bitsHdr +
    stat->bitsSkipLen +
    stat->bitsMBtype +
    stat->bitsPred +
    stat->bitsVec +
    stat->bitsCBP +
    stat->bitsCoefLumaDC +
    stat->bitsCoefLuma +
    stat->bitsCoefChromaDC +
    stat->bitsCoefChroma +
    stat->bitsArithmeticStream
  );
}


/*
 *
 * staGetTotalChromaBits:
 *
 * Parameters:
 *      stat                  Statistics object
 *
 * Function:
 *      Get total number of chroma coef bits in given statistics
 *
 * Returns:
 *      Number of bits
 *
 */
int staGetTotalChromaBits(statSlice_s *stat)
{
  return (
    stat->bitsCoefChromaDC +
    stat->bitsCoefChroma
  );
}


/*
 *
 * staSaveState:
 *
 * Parameters:
 *      stat                  Statistics object
 *      statSave              Destination for saved state
 *
 * Function:
 *      Save statistics state.
 *
 * Returns:
 *
 */
void staSaveState(statSlice_s *stat, statSlice_s *statSave)
{
  *statSave = *stat;
}


/*
 *
 * staRestoreState:
 *
 * Parameters:
 *      stat                  Statistics object
 *      statSaved             Saved state
 *
 * Function:
 *      Restore statistics state.
 *
 * Returns:
 *
 */
void staRestoreState(statSlice_s *stat, statSlice_s *statSaved)
{
  *stat = *statSaved;
}


/*
 *
 * CalculateSsd:
 *
 * Parameters:
 *      orig                  Original pixels
 *      origBufWidth          Width of the original buffer
 *      reco                  Reconstructed pixels
 *      recoBufWidth          Width of the reconstructed pixel buffer
 *      width                 Number of pixels to compare, horizontally
 *      height                Number of pixels to compare, vertically
 *
 * Function:
 *      Calculate the sum of squared differences between the original pixels 
 *      and the reconstructed pixels.
 *      
 * Returns:
 *      Sum of squared difference.
 */
int32 CalculateSsd(u_int8 *orig, 
                   int    origBufWidth, 
                   u_int8 *reco, 
                   int    recoBufWidth,
                   int    width, 
                   int    height)
{
  int i, j;
  int32 ssd;

  ssd = 0;
  for (i = 0; i < height; i ++)
  {
    for (j = 0; j < width; j ++)
    {
      int diff;

      diff = (int) orig[j] - (int) reco[j];
      ssd += (int32)diff * diff;
    }

    orig += origBufWidth;
    reco += recoBufWidth;
  }

  return ssd;
}


/*
 *
 * CalculateEdgeSsd:
 *
 * Parameters:
 *      orig                  Original pixels
 *      origBufWidth          Width of the original buffer
 *      reco                  Reconstructed pixels
 *      recoBufWidth          Width of the reconstructed pixel buffer
 *      width                 Number of pixels to compare, horizontally
 *      height                Number of pixels to compare, vertically
 *
 * Function:
 *      Calculate the sum of squared differences between the original pixels 
 *      and the reconstructed pixels at the right and bottom boundaries.
 *      The bottom-right corner will be included twice.
 *      
 * Returns:
 *      Sum of squared difference.
 */
int32 CalculateEdgeSsd(u_int8 *orig, 
                       int    origBufWidth, 
                       u_int8 *reco, 
                       int    recoBufWidth,
                       int    width, 
                       int    height,
                       int    rightMb,
                       int    bottomMb)
{
  int i, diff;
  int32 ssd;

  ssd = 0;

  if (! rightMb)
  {
    for (i = 0; i < height; i ++)
    {
      diff = (int) orig[i * origBufWidth + width - 1] - (int) reco[i * recoBufWidth + width - 1];
      ssd += (int32)diff * diff;
    }
  }

  if (! bottomMb)
  {
    orig += (height - 1) * origBufWidth;
    reco += (height - 1) * recoBufWidth;

    for (i = 0; i < width; i ++)
    {
      diff = (int) orig[i] - (int) reco[i];
      ssd += (int32)diff * diff;
    }
  }

  return ssd;
}


/*
 *
 * CalculateSAD:
 *
 * Parameters:
 *      orig                  Original pixels
 *      origBufWidth          Width of the original buffer
 *      reco                  Reconstructed pixels
 *      recoBufWidth          Width of the reconstructed pixel buffer
 *      width                 Number of pixels to compare, horizontally
 *      height                Number of pixels to compare, vertically
 *
 * Function:
 *      Calculate the sum of absolute differences between the original pixels 
 *      and the reconstructed pixels.
 *      
 * Returns:
 *      Sum of squared difference.
 */
int32 CalculateSad(u_int8 *orig, 
                   int    origBufWidth, 
                   u_int8 *reco, 
                   int    recoBufWidth,
                   int    width, 
                   int    height)
{
  int i, j;
  int32 sad;

  sad = 0;
  for (i = 0; i < height; i ++) {
    for (j = 0; j < width; j ++) {
      int diff;

      diff = (int) orig[j] - (int) reco[j];
	  if(diff<0)
		  sad=sad-diff;
	  else
		  sad+=diff;
    }

    orig += origBufWidth;
    reco += recoBufWidth;
  }

  return sad;
}