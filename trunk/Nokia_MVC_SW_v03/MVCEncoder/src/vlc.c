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
 * vlc.c
 *
 * Contains:
 *    Functions for variable length coding
 *
 */

#include "vlcutility.h"
#include "vlc.h"


static const vlcCode_s numCoefsTrailTabChroma[4][5] = 
{
  {{1,2},{7,6},{4,6},{3,6},{2,6}},
  {{0,0},{1,1},{6,6},{3,7},{3,8}},
  {{0,0},{0,0},{1,3},{2,7},{2,8}},
  {{0,0},{0,0},{0,0},{5,6},{0,7}},
};


static const vlcCode_s totZerosTab[15][16] = {
  {{1,1},{3,3},{2,3},{3,4},{2,4},{3,5},{2,5},{3,6},{2,6},{3,7},{2,7},{3,8},{2,8},{3,9},{2,9},{1, 9}},
  {{7,3},{6,3},{5,3},{4,3},{3,3},{5,4},{4,4},{3,4},{2,4},{3,5},{2,5},{3,6},{2,6},{1,6},{0,6}},
  {{5,4},{7,3},{6,3},{5,3},{4,4},{3,4},{4,3},{3,3},{2,4},{3,5},{2,5},{1,6},{1,5},{0,6}},
  {{3,5},{7,3},{5,4},{4,4},{6,3},{5,3},{4,3},{3,4},{3,3},{2,4},{2,5},{1,5},{0,5}},
  {{5,4},{4,4},{3,4},{7,3},{6,3},{5,3},{4,3},{3,3},{2,4},{1,5},{1,4},{0,5}},
  {{1,6},{1,5},{7,3},{6,3},{5,3},{4,3},{3,3},{2,3},{1,4},{1,3},{0,6}},
  {{1,6},{1,5},{5,3},{4,3},{3,3},{3,2},{2,3},{1,4},{1,3},{0,6}},
  {{1,6},{1,4},{1,5},{3,3},{3,2},{2,2},{2,3},{1,3},{0,6}},
  {{1,6},{0,6},{1,4},{3,2},{2,2},{1,3},{1,2},{1,5}},
  {{1,5},{0,5},{1,3},{3,2},{2,2},{1,2},{1,4}},
  {{0,4},{1,4},{1,3},{2,3},{1,1},{3,3}},
  {{0,4},{1,4},{1,2},{1,1},{1,3}},
  {{0,3},{1,3},{1,1},{1,2}},
  {{0,2},{1,2},{1,1}},
  {{0,1},{1,1}},
};

static const vlcCode_s totZerosTabChroma[3][4] = 
{
  {{1, 1}, {1, 2}, {1, 3}, {0, 3},},
  {{1, 1}, {1, 2}, {0, 2}, {0, 0},},
  {{1, 1}, {0, 1}, {0, 0}, {0, 0},}
};

static const vlcCode_s runTab[6][7] = 
{
  {{1,1}, {0,1}},
  {{1,1}, {1,2}, {0,2}},
  {{3,2}, {2,2}, {1,2}, {0,2}},
  {{3,2}, {2,2}, {1,2}, {1,3}, {0,3}},
  {{3,2}, {2,2}, {3,3}, {2,3}, {1,3}, {0,3}},
  {{3,2}, {0,3}, {1,3}, {3,3}, {2,3}, {5,3}, {4,3}},
};


static const vlcCode_s runTabLong[15] = 
{
  {7,3}, {6,3}, {5,3}, {4,3}, {3,3}, {2,3}, {1,3}, {1,4}, 
  {1,5}, {1,6}, {1,7}, {1,8}, {1,9}, {1,10}, {1,11},
};


static const unsigned int incVlc[7] = {
  0,3,6,12,24,48,32768          /* maximum vlc = 6 */
};


static const int8 vlcNumTab[8] = {
  0, 0, 1, 1, 2, 2, 2, 2
};


static const int8 numCoefsTrailTab[3][4][17] = {
  {
    { 1, 5, 7, 7, 7, 7,15,11, 8,15,11,15,11,15,11, 7,4}, 
    { 0, 1, 4, 6, 6, 6, 6,14,10,14,10,14,10, 1,14,10,6}, 
    { 0, 0, 1, 5, 5, 5, 5, 5,13, 9,13, 9,13, 9,13, 9,5}, 
    { 0, 0, 0, 3, 3, 4, 4, 4, 4, 4,12,12, 8,12, 8,12,8}
  },
  {
    { 3,11, 7, 7, 7, 4, 7,15,11,15,11, 8,15,11, 7, 9,7}, 
    { 0, 2, 7,10, 6, 6, 6, 6,14,10,14,10,14,10,11, 8,6}, 
    { 0, 0, 3, 9, 5, 5, 5, 5,13, 9,13, 9,13, 9, 6,10,5}, 
    { 0, 0, 0, 5, 4, 6, 8, 4, 4, 4,12, 8,12,12, 8, 1,4}
  },
  {
    {15,15,11, 8,15,11, 9, 8,15,11,15,11, 8,13, 9, 5,1}, 
    { 0,14,15,12,10, 8,14,10,14,14,10,14,10, 7,12, 8,4},
    { 0, 0,13,14,11, 9,13, 9,13,10,13, 9,13, 9,11, 7,3},
    { 0, 0, 0,12,11,10, 9, 8,13,12,12,12, 8,12,10, 6,2}
  }
};


static const int8 numCoefsTrailLenTab[3][4][17] = {
  {
    { 1, 6, 8, 9,10,11,13,13,13,14,14,15,15,16,16,16,16},
    { 0, 2, 6, 8, 9,10,11,13,13,14,14,15,15,15,16,16,16},
    { 0, 0, 3, 7, 8, 9,10,11,13,13,14,14,15,15,16,16,16},
    { 0, 0, 0, 5, 6, 7, 8, 9,10,11,13,14,14,15,15,16,16}
  },
  {
    { 2, 6, 6, 7, 8, 8, 9,11,11,12,12,12,13,13,13,14,14},
    { 0, 2, 5, 6, 6, 7, 8, 9,11,11,12,12,13,13,14,14,14},
    { 0, 0, 3, 6, 6, 7, 8, 9,11,11,12,12,13,13,13,14,14},
    { 0, 0, 0, 4, 4, 5, 6, 6, 7, 9,11,11,12,13,13,13,14}
  },
  {
    { 4, 6, 6, 6, 7, 7, 7, 7, 8, 8, 9, 9, 9,10,10,10,10},
    { 0, 4, 5, 5, 5, 5, 6, 6, 7, 8, 8, 9, 9, 9,10,10,10},
    { 0, 0, 4, 5, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9,10,10,10},
    { 0, 0, 0, 4, 4, 4, 4, 4, 5, 6, 7, 8, 8, 9,10,10,10}
  }
};


/*
 * Codes for Coded Block Patterns for intra and inter
 */
const int8 cbpCode[48][2] = {
  { 3, 0},{29, 2},{30, 3},{17, 7},{31, 4},{18, 8},{37,17},{ 8,13},{32, 5},{38,18},{19, 9},{ 9,14},
  {20,10},{10,15},{11,16},{ 2,11},{16, 1},{33,32},{34,33},{21,36},{35,34},{22,37},{39,44},{ 4,40},
  {36,35},{40,45},{23,38},{ 5,41},{24,39},{ 6,42},{ 7,43},{ 1,19},{41, 6},{42,24},{43,25},{25,20},
  {44,26},{26,21},{46,46},{12,28},{45,27},{47,47},{27,22},{13,29},{28,23},{14,30},{15,31},{ 0,12},
}; 


/*
 * vlcSendMbSkipFlag:
 *
 * Parameters:
 *      bitbuf                Bitbuffer handle
 *      mb                    Macroblock object
 *      stat                  Statistics
 *
 * Function:
 *      Send the MB skipping count. 
 *      
 * Returns:
 *      1, MB skipped, 0, MB not skipped.
 */
int vlcSendMbSkipFlag(bitbuffer_s  *bitbuf, 
                      macroblock_s *mb, 
                      int          skipFlag)
{
  int bitsSkipLen;
  int sendSkipCount;

  sendSkipCount = 1;
  if (skipFlag) 
  {
    mb->numSkipped += 1;
    if (! mb->isLastMb)
      sendSkipCount = 0;
  }

  bitsSkipLen = 0;
  if (sendSkipCount)
  {
    bitsSkipLen    = vlcuSendUVLC(bitbuf, mb->numSkipped);
    mb->headerBits = bitsSkipLen;
    mb->numSkipped = 0;
  }

  return bitsSkipLen;
}


/*
 * vlcSendMotVecs
 *
 * Parameters:
 *      bitbuf                Bitbuffer
 *      interMode             Mode for inter MB (16x16, 8x16, 16x8 or 8x8)
 *      numRefFrames          Number of reference frames scanned
 *      diffVecs              Differential motion vectors
 *      numVecs               Number of motion vectors
 *      refIndices            Reference frame indices
 *
 * Function:
 *      Send motion vectors.
 *
 * Returns:
 *      Number of bits for prediction modes.
 */
int vlcSendMotVecs(bitbuffer_s *bitbuf, 
                   int interMode, 
                   int numRefFrames,
                   int16 diffVecs[16][2], 
                   int numVecs, 
                   u_int8 refIndices[4])
{
  int i, j;
  int bits = 0;

  /* Send reference frame indices if there are more than one reference frames */
  /* and all indices are not zero for inter mode >= 4                        */
  if (numRefFrames > 1 && !(interMode == MOT_8x8 &&
      ((refIndices[0] | refIndices[1] | refIndices[2] | refIndices[3]) == 0))) {
    /* If there are only two ref. frames we just send one bit flag for each index */
    if (numRefFrames == 2) {
      for (i = 0; i < numOfRefPar[interMode - 1]; i ++) {
        bibPutBits(bitbuf, 1 - refIndices[i], 1);
      }

      bits += numOfRefPar[interMode-1];
    }
    
    /* Otherwise we send UVLC code for each index */
    else {
      for (i = 0; i < numOfRefPar[interMode-1]; i++)
        bits += vlcuSendUVLC(bitbuf, refIndices[i]);
    }
  }

  for(j = 0; j < numVecs; j++) {
    for(i = 0; i < 2; i++) {
      bits += vlcuSendUVLC(bitbuf, vlcuMapSigned(diffVecs[j][i]));
    }
  }

  return bits;
}


/*
 * vlcuSendIntraPred
 *
 * Parameters:
 *      bitbuf                Bitbuffer
 *      ipTab                 Intra predicition modes
 *
 * Function:
 *      Send 4x4 intra prediction modes.
 *
 * Returns:
 *      Number of bits for prediction modes.
 */
int vlcSendIntraPred(bitbuffer_s *bitbuf, int8 *ipTab)
{
  int i;
  int numNonPredicted;


  numNonPredicted = 0;
  for (i = 0; i < 16; i ++)
  {
    if (ipTab[i] < 0)
      bibPutBits(bitbuf, 1, 1);
    else
    {
      numNonPredicted ++;
      bibPutBits(bitbuf, ipTab[i], 4);
    }
  }

  return (16 + numNonPredicted * 3);
}


/*
 * vlcSendCbp
 *
 * Parameters:
 *      bitbuf                Bitbuffer
 *      type                  Type of the macroblock
 *      cbp                   Combined coded Block Pattern for luma and chroma
 *
 * Function:
 *      Send Coded Block Pattern.
 *
 * Returns:
 *      Number of bits for Coded Block Pattern.
 */
int vlcSendCbp(bitbuffer_s *bitbuf, 
               int mbType,
               int cbp)
{
  int code;


  if (mbType == MBK_INTRA)
    code = cbpCode[cbp][0];
  else
    code = cbpCode[cbp][1];

  return vlcuSendUVLC(bitbuf, code);
}


/*
 * vlcGetNumCoefsPredLuma:
 *
 * Parameters:
 *      mb                    Macroblock object
 *      blkX                  Horizontal block index within MB
 *      blkY                  Vertical block index within MB
 * 
 * Function:
 *      Get predictor for encoding number of coefficients in a luma block. 
 *      In getting the neighboring block information, pre-configured pointers
 *      blkLeft and blkUp are used. In processing luma information, the
 *      buffer "current" is used.
 *      
 * Returns:
 *      Predictor.
 */
static int vlcGetNumCoefsPredLuma(macroblock_s *mb,
                                  int          blkX, 
                                  int          blkY)
{
  int leftAvail, numCoefPred;

  leftAvail = 0;
  numCoefPred  = 0;
  
  if ((blkX > 0) || mb->mbAvailMap[0])
  {
    numCoefPred += mb->blkLeft[blkY * 4 + blkX]->numLumaCoefs;
    leftAvail = 1;
  }

  if ((blkY > 0) || mb->mbAvailMap[1])
  {
    numCoefPred += mb->blkUp[blkY * 4 + blkX]->numLumaCoefs;
    if (leftAvail)
      numCoefPred = (numCoefPred + 1) >> 1;
  }

  return numCoefPred;
}


/*
 * vlcGetNumCoefsPredChroma:
 *
 * Parameters:
 *      mb                    Macroblock object
 *      comp                  0, Cb, 1, Cr
 *      blkX                  Horizontal block index within MB
 *      blkY                  Vertical block index within MB
 *
 * Function:
 *      Get predictor for encoding number of coefficients in a chroma block. 
 *      
 * Returns:
 *      Predictor.
 */
static int vlcGetNumCoefsPredChroma(macroblock_s *mb,
                                    int          comp, 
                                    int          blkX, 
                                    int          blkY)
{
  int leftAvail, numCoefPred;

  leftAvail   = 0;
  numCoefPred = 0;
  
  if ((blkX > 0) || mb->mbAvailMap[0])
  {
    if (blkX > 0)
      numCoefPred += mb->mbThis->numChromaCoefs[comp][blkY][blkX - 1];
    else
      numCoefPred += mb->mbLeft->numChromaCoefs[comp][blkY][1];
    leftAvail = 1;
  }

  if ((blkY > 0) || mb->mbAvailMap[1])
  {
    if (blkY > 0)
      numCoefPred += mb->mbThis->numChromaCoefs[comp][blkY - 1][blkX];
    else
      numCoefPred += mb->mbUp->numChromaCoefs[comp][1][blkX];

    if (leftAvail)
      numCoefPred = (numCoefPred + 1) >> 1;
  }

  return numCoefPred;
}


/*
 * vlcCollectCoefBlkStat
 *
 * Parameters:
 *      coef                  Coefficient buffer
 *      lastCoefIdx           Index of the last coeff in block, either 15 or 3
 *      dcSkip                Whether the first coefficient should be skipped
 *      blkStat               Block statistics
 *
 * Function:
 *      Encode a block based on statistics collected in streamCollectCoefBlkStat.
 *
 * Returns:
 *      Number of bits generated.
 */
void vlcCollectCoefBlkStat(int              *coef, 
                           int              lastCoefIdx,
                           int              dcSkip,
                           vlcCoefBlkStat_s *blkStat)
{
  int i, prev, run;


  /* Trailing zeros are counted outside */

  /*
   * Find trailing ones and runs
   */
  blkStat->numTrailingOnes = 0;
  blkStat->signs = 0;
  i = lastCoefIdx - blkStat->numTrailingZeros;  // first non-zero coefficient

  while (i >= dcSkip && blkStat->numTrailingOnes < 3 && abs(coef[i]) == 1) {

    blkStat->signs <<= 1;
    if (coef[i] < 0) 
      blkStat->signs |= 1;

    i --;
    prev = i;
    while (i >= dcSkip && coef[i] == 0) 
      i--;

    run = prev - i;

    blkStat->runs[blkStat->numTrailingOnes] = (int8) run;
    blkStat->numTrailingOnes++;
  }

  blkStat->totalCoef = blkStat->numTrailingOnes;

  /*
   * Find levels and runs
   */
  while (i >= dcSkip) {
    blkStat->levels[blkStat->totalCoef] = coef[i];

    i--;
    prev = i;
    while (i >= dcSkip && coef[i] == 0) i--;
    run = prev - i;

    blkStat->runs[blkStat->totalCoef] = (int8) run;
    blkStat->totalCoef ++;
  }

  // total number of zeros excluding the trailing zeros
  blkStat->totalZeros = (int8) 
    (lastCoefIdx + 1 - dcSkip - blkStat->numTrailingZeros - blkStat->totalCoef);
}


/*
 * vlcSendCoeffToken
 *
 * Parameters:
 *      bitbuf                Bitbuffer
 *      numCoefsPred          Number of coefficients predictor
 *      numTrailingOnes       Number of trailing ones in the 4x4 block
 *      totalCoef             Number of non-zero coefficients
 *
 * Function:
 *      Encode a coefficient token which consists of number of trailing ones
 *      and total number of coefficients, under the context of numCoefsPred. 
 *      numCoefsPred is calculated from the numbers of non-zero coeffcients 
 *      of the neighboring blocks. 
 *
 * Returns:
 *      Number of bits generated.
 */
int vlcSendCoeffToken(bitbuffer_s  *bitbuf,
                      macroblock_s *mb,
                      int          comp,
                      int          blkX,
                      int          blkY, 
                      int          numTrailingOnes,
                      int          totalCoef)
{
  int code, len, numCoefsPred;


  if (comp == COMP_LUMA)
    numCoefsPred = vlcGetNumCoefsPredLuma(mb, blkX, blkY);
  else
    numCoefsPred = vlcGetNumCoefsPredChroma(mb, comp - 1, blkX, blkY);

  /* Select variable length code or fixed length coding */
  if (numCoefsPred < 8) {
    int tabNum;

    /* Select table number based on the prediction */
    tabNum = vlcNumTab[numCoefsPred];

    code = numCoefsTrailTab[tabNum][numTrailingOnes][totalCoef];
    len  = numCoefsTrailLenTab[tabNum][numTrailingOnes][totalCoef];
  }
  else {
    code = 3;
    if (totalCoef != 0)
      code = ((totalCoef - 1) << 2) | numTrailingOnes;

    len = 6;
  }

  return bibPutBits(bitbuf, code, len);
}


/*
 * vlcEncodeCoefBlk
 *
 * Parameters:
 *      bitbuf                Bitbuffer
 *      blkStat               Block statistics
 *      blockSize             Size of the block, either 16 or 4
 *      dcSkip                Whether the first coefficient should be skipped
 *      blkType               0, 4x4 block, 1, chroma DC 2x2 block.
 *
 * Function:
 *      Encode a block based on statistics collected in vlcCollectCoefBlkStat.
 *
 * Returns:
 *      Number of bits generated.
 */
int vlcEncodeCoefBlk(bitbuffer_s      *bitbuf, 
                     vlcCoefBlkStat_s *blkStat,
                     int              blockSize,
                     int              dcSkip,
                     int              blkType)
{
  int i;
  int len;
  int level, run;
  int levelTabNum;
  int zerosLeft;
  int coefNum;
  const vlcCode_s *pVlc;
  const vlcCode_s *pNumZerosVlc;


  if (blkType == 0)
    pNumZerosVlc = & totZerosTab[blkStat->totalCoef - 1][blkStat->totalZeros];
  else
    pNumZerosVlc = & totZerosTabChroma[blkStat->totalCoef - 1][blkStat->totalZeros];

  levelTabNum = (blkStat->totalCoef > 10 && blkStat->numTrailingOnes < 3) ? 1 : 0;

  // Send signs for trailing ones

  len = 0;
  if (blkStat->numTrailingOnes != 0)
    len += bibPutBits(bitbuf, blkStat->signs, blkStat->numTrailingOnes);

  // Send the large coefficients
  if (blkStat->totalCoef > blkStat->numTrailingOnes) {

    // Encode first level
    level = blkStat->levels[blkStat->numTrailingOnes];

    if (blkStat->numTrailingOnes < 3)
      level += (level > 0) ? -1 : 1;

    if (levelTabNum == 0)
      len += vlcuSendCoefLevelVLC0(bitbuf, level);
    else
      len += vlcuSendCoefLevelVLCN(bitbuf, levelTabNum, level);

    // update VLC table
    if ((unsigned int)abs(blkStat->levels[blkStat->numTrailingOnes]) > incVlc[levelTabNum])
      levelTabNum ++;

    if (abs(blkStat->levels[blkStat->numTrailingOnes]) > 3)
      levelTabNum = 2;

    // Encode rest of the levels
    for (i = blkStat->numTrailingOnes + 1; i < blkStat->totalCoef; i++) {

      level = blkStat->levels[i];

      if (levelTabNum == 0)
        len += vlcuSendCoefLevelVLC0(bitbuf, level);
      else
        len += vlcuSendCoefLevelVLCN(bitbuf, levelTabNum, level);

      // update VLC table
      if ((unsigned int)abs(level) > incVlc[levelTabNum])
        levelTabNum++;
    }
  }

  // Send the number of zero coefficients
  if (blkStat->totalCoef < blockSize - dcSkip)
    len += bibPutBits(bitbuf, pNumZerosVlc->code, pNumZerosVlc->len);

  // Send runs
  zerosLeft = blkStat->totalZeros;
  coefNum = 0;
  while (coefNum < blkStat->totalCoef - 1 && zerosLeft > 0) {

    run = blkStat->runs[coefNum];

    // select VLC for runbefore
    if (zerosLeft <= 6)
      pVlc = & runTab[zerosLeft-1][run];
    else
      pVlc = & runTabLong[run];

    len += bibPutBits(bitbuf, pVlc->code, pVlc->len);

    zerosLeft -= run;
    coefNum++;
  }

  return len;
}

