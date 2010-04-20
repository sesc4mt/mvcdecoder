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
 * stream.c
 *
 * Contains:
 *    The functions that encode the data into bitstream.
 *
 */

#include "vlcutility.h"
#include "macroblock.h"
#include "stream.h"
#include "vlc.h"

static const vlcCode_s numCoefsTrailTabChroma[4][5] = 
{
  {{1,2},{7,6},{4,6},{3,6},{2,6}},
  {{0,0},{1,1},{6,6},{3,7},{3,8}},
  {{0,0},{0,0},{1,3},{2,7},{2,8}},
  {{0,0},{0,0},{0,0},{5,6},{0,7}},
};


/*
 * streamGetMbTypeIntra
 *
 * Parameters:
 *      intraType             Type of the intra macroblock
 *      intra16x16Mode        16x16 intra prediction mode
 *      cbpY                  Coded Block Pattern for luma
 *      cbpChromaDC           Coded Block Pattern for chroma DC
 *      cbpC                  Coded Block Pattern for chroma AC
 *
 * Function:
 *      Get intra-macroblock mb_type.
 *
 * Returns:
 *      mb_type.
 */
int streamGetMbTypeIntra(int intraType,
                         int intra16x16Mode,
                         unsigned int cbpY,
                         unsigned int cbpChromaDC,
                         unsigned int cbpC)
{
  int mbType;

  mbType = 0;
  if (intraType == MBK_INTRA_TYPE2)
  {
    int ac, nc;

    // In intra type 2, MB type includes information about coded blocks
    ac = (cbpY == 0) ? 0 : 12;
    nc = vlcuGetChromaNC(cbpChromaDC, cbpC);
    mbType += 1 + ac + nc * 4 + intra16x16Mode;
  }

  return mbType;
}


/*
 * streamGetMbTypeInter
 *
 * Parameters:
 *      interMode             Inter motion mode, more details below ...
 *      refIndices            Reference frame indices
 *
 * Function:
 *      Get inter-macroblock mb_type.
 *
 * Returns:
 *      mb_type.
 */
int streamGetMbTypeInter(int    interMode,
                         u_int8 refIndices[4])
{
  if (interMode == MOT_8x8) {
    // mbType == 3, P_8x8,     multiple reference frames
    // mbType == 4, P_8x8ref0, single reference frame, no ref_idx to follow
    return ((refIndices[0] | refIndices[1] | 
      refIndices[2] | refIndices[3]) != 0) ? 3 : 4;
  }
  else {
    // interMode == 0 not allowed
    // interMode == 1, mbType = 0, P_L0_16x16
    // interMode == 2, mbType = 1, P_L0_16x8
    // interMode == 3, mbType = 2, P_L0_8x16
    return interMode - 1;
  }
}


/*
 * streamCountIntraSyntaxBits:
 *
 * Parameters:
 *      mb                    Macroblock object
 *      picType               Picture type (intra/inter)
 *
 * Function:
 *      Count additional intra-MB syntax bits, used only in helping make mode 
 *      decision when rate distortion optimization is enabled.
 *      
 * Returns:
 *      number of bits in the header.
 */
int streamCountIntraSyntaxBits(macroblock_s *mb, 
                               int          picType)
{
  int mbType, bitsHdr;


  bitsHdr = 0;

  if (IS_SLICE_P(picType)) 
    bitsHdr = vlcuUVLCSize(mb->numSkipped);

  /* Send Macroblock type */
  mbType = ((IS_SLICE_P(picType)) ? 5 : 0) + streamGetMbTypeIntra
    (mb->intraType, mb->intra16x16mode, mb->cbpY, mb->cbpChromaDC, mb->cbpC);
  bitsHdr += uvlcBitsUnsigned[mbType];

  // bits on intra4x4 modes were counted in the intra4x4 prediction
  // bits on 8x8 chroma intra mode were counted in chroma8x8 prediction

  // Send coded block pattern
  if (mb->intraType != MBK_INTRA_TYPE2)
  {
    int cbp;

    cbp  = vlcuGetLuma8x8cbp(mb->cbpY);
    cbp |= vlcuGetChromaNC(mb->cbpChromaDC, mb->cbpC) << 4;
    bitsHdr += vlcuUVLCSize(cbpCode[cbp][0]);

    // for MBK_INTRA_TYPE2, cbp is included in mbtype
  }

  // Send delta QP
  if ((mb->intraType == MBK_INTRA_TYPE2) || 
    (mb->cbpY | mb->cbpChromaDC | mb->cbpC) != 0)
  {
    int deltaQp;

    CALCULATE_DELTA_QP(deltaQp, mb->qp, mb->prevQp);
    bitsHdr += uvlcBitsSigned[511 + deltaQp];
  }

  return bitsHdr;
}


/*
 * streamSend4x4Blk
 *
 * Parameters:
 *      stream                bitbuffer for CAVLC
 *      mb                    Macroblock object
 *      nonzeroBlkFlag        0, it's known all the coefficients are zero
 *      comp                  Color component index
 *      blkX                  Horizontal block index within MB
 *      blkY                  Vertical block index within MB
 *      coef                  4x4 coefficients
 *      blkCategory           Block category, 1 of 5 types
 *      numCoefs              Number of nonzero coefficients encoded
 *
 * Function:
 *      Send coefficients of 4x4 block. 
 *      nonzeroBlkFlag can be used to save some process time, as it is usually 
 *      known whether this block has any non-zero coefficients at all before 
 *      this function is called.
 *
 * Returns:
 *      Number of bits for coefficients.
 */
int streamSend4x4Blk(void         *stream, 
                     macroblock_s *mb,
                     int          nonzeroBlkFlag,
                     int          comp,
                     int          blkX,
                     int          blkY,
                     int          coef[4][4], 
                     int          blkCategory,
                     int          *numCoefs)
{
  int i;
  int tmpCoef[4*4];
  int len;
  int dcSkip;
  vlcCoefBlkStat_s blkStat;


  dcSkip = (blkCategory == BLK_CAT_Y_I16x16_AC) || (blkCategory == BLK_CAT_C_AC);

  vlcuZigZagScan4x4(coef, tmpCoef);

  blkStat.totalCoef = 0;
  blkStat.numTrailingZeros = (int8)(16 - dcSkip);
  if (nonzeroBlkFlag)
  {
    i = 15;
    while (i >= dcSkip && tmpCoef[i] == 0) i --;
    blkStat.numTrailingZeros = (int8) (15 - i);

    nonzeroBlkFlag = (16 - dcSkip) > blkStat.numTrailingZeros;
  }
  
  {
    if (nonzeroBlkFlag)
    {
      vlcCollectCoefBlkStat(tmpCoef, 15, dcSkip, & blkStat);
      len = vlcSendCoeffToken(stream, mb, comp, blkX, blkY, 
        blkStat.numTrailingOnes, blkStat.totalCoef);
      len += vlcEncodeCoefBlk(stream, & blkStat, 16, dcSkip, 0);
    }
    else
      len = vlcSendCoeffToken(stream, mb, comp, blkX, blkY, 0, 0);
  }

  *numCoefs = blkStat.totalCoef;

  return len;
}


/*
 * streamSend2x2ChromaDC
 *
 * Parameters:
 *      stream                bitbuffer for CAVLC
 *      tmpCoef               2x2 coefficients
 *
 * Function:
 *      Send coefficients of 2x2 block, 
 *      A 2x2 block is formed with transformed coefficients of the 4 DC 
 *      coefficients from 4 4x4 blocks. 
 *
 * Returns:
 *      Number of bits for coefficients.
 */
static int streamSend2x2ChromaDC(void         *stream, 
                                 int          tmpCoef[4])
{
  int i, len;
  const vlcCode_s *pVlc;
  vlcCoefBlkStat_s blkStat;


  // Count trailing zero coefficients
  i = 3;
  while (i >= 0 && tmpCoef[i] == 0) i --;

  blkStat.numTrailingZeros = (int8) (3 - i);
  blkStat.totalCoef = 0;

  {
    // Send totalCoef & numTrailingOnes
    vlcCollectCoefBlkStat(tmpCoef, 3, 0, & blkStat);
    pVlc = & numCoefsTrailTabChroma[blkStat.numTrailingOnes][blkStat.totalCoef];
    len = bibPutBits(stream, pVlc->code, pVlc->len);
  }

  if (blkStat.numTrailingZeros < 4)
  {
      len += vlcEncodeCoefBlk(stream, & blkStat, 4, 0, 1);
  }
 
  return len;
}


/*
 * streamSendMbSkipFlag:
 *
 * Parameters:
 *      stream                bitbuffer for CAVLC
 *      mb                    Macroblock object
 *      skipFlag              0, MB is not skipped, 1, MB is skipped
 *
 * Function:
 *      Process the flag to indicate whether the MB is skipped or not. 
 *      
 * Returns:
 *      Number of bits generated.
 */
int streamSendMbSkipFlag(void         *stream, 
                         macroblock_s *mb, 
                         int          skipFlag)
{
    return vlcSendMbSkipFlag(stream, mb, skipFlag);
}


/*
 * streamSendMbType:
 *
 * Parameters:
 *      stream                bitbuffer for CAVLC
 *      mb                    Macroblock object
 *      picType               Picture type (intra/inter)
 *      cbpY                  Coded Block Pattern for luma
 *      cbpChromaDC           Coded Block Pattern for chroma DC
 *      cbpC                  Coded Block Pattern for chroma AC
 *
 * Function:
 *      Send mb_type in CAVLC
 *      
 * Returns:
 *      Number of bits generated.
 */
static int streamSendMbType(void         *stream, 
                            macroblock_s *mb, 
                            int          picType,
                            unsigned int cbpY, 
                            unsigned int cbpChromaDC, 
                            unsigned int cbpC)
{
  int mbType;
  int i, bitsMBtype;


  if (mb->type == MBK_INTRA)
  {
    mbType = streamGetMbTypeIntra
      (mb->intraType, mb->intra16x16mode, cbpY, cbpChromaDC, cbpC);

    mbType += (IS_SLICE_P(picType)) ? 5 : 0;
  }
  else
    mbType = streamGetMbTypeInter(mb->interMode, mb->refIndices);

    bitsMBtype = vlcuSendUVLC(stream, mbType);

  if (mb->type == MBK_INTER && mb->interMode == MOT_8x8)
  {
      // need to send sub_mb_type
      for (i = 0; i < 4; i++)
        bitsMBtype += vlcuSendUVLC(stream, mb->interSubMbModes[i]);
  }

  return bitsMBtype;
}


/*
 * streamSendCbp:
 *
 * Parameters:
 *      stream                bitbuffer for CAVLC
 *      mb                    Macroblock object
 *
 * Function:
 *      Code coded block pattern in CAVLC
 *      
 * Returns:
 *      -
 */
static int streamSendCbp(void         *stream,
                         macroblock_s *mb)
{
  int cbpY, cbpC;

  
  cbpY = vlcuGetLuma8x8cbp(mb->cbpY);
  cbpC = vlcuGetChromaNC(mb->cbpChromaDC, mb->cbpC);

    return vlcSendCbp(stream, mb->type, (cbpC << 4) | cbpY);
}


/*
 * streamSendMbHeader:
 *
 * Parameters:
 *      stream                bitbuffer for CAVLC
 *      mb                    Macroblock object
 *      nRefFrames            Number of reference frames in use
 *      picType               Picture type (intra/inter)
 *      stat                  Statistics
 *
 * Function:
 *      Code macroblock header using in CAVLC
 *      
 * Returns:
 *      -
 */
void streamSendMbHeader(void         *stream, 
                        macroblock_s *mb, 
                        int          nRefFrames, 
                        int          picType,
                        statSlice_s  *stat)
{
  int bitsHdr, bitsMBtype, bitsPred, bitsVec;

  
  bitsHdr  = 0;
  bitsPred = 0;
  bitsVec  = 0;

  /* Send Macroblock type */
  bitsMBtype = streamSendMbType(stream,
    mb, picType, mb->cbpY, mb->cbpChromaDC, mb->cbpC);

  /* Send 4x4 intra prediction modes */
  if (mb->type == MBK_INTRA)
  {
    if (mb->intraType == MBK_INTRA_TYPE1)
    {
        bitsPred += vlcSendIntraPred(stream, mb->ipTab);
    }

    /* Send 8x8 chroma intra prediction mode */
    bitsPred += vlcuSendUVLC(stream, mb->intraModeChroma);
  }
  else
  {
    /* Send reference frame number and motion vectors */
    bitsVec = vlcSendMotVecs(stream, mb->interMode, nRefFrames, 
                             mb->diffVecs, mb->numVecs,  mb->refIndices);
  }

  /* Send coded block pattern */
  if (!(mb->type == MBK_INTRA && mb->intraType == MBK_INTRA_TYPE2))
     stat->bitsCBP += streamSendCbp(stream,
     mb);

  /* Send delta QP */
  if ((mb->type == MBK_INTRA && mb->intraType == MBK_INTRA_TYPE2) || 
    (mb->cbpY | mb->cbpChromaDC | mb->cbpC) != 0)
  {
    CALCULATE_DELTA_QP(mb->deltaQp, mb->qp, mb->prevQp);
    
      stat->bitsHdr += vlcuSendUVLC(stream, vlcuMapSigned(mb->deltaQp));

    mb->prevQp = mb->qp;
  }
  else
  {
    mb->deltaQp = 0;
    mb->qp = mb->prevQp;
  }

  stat->bitsMBtype += bitsMBtype;
  stat->bitsPred   += bitsPred;
  stat->bitsVec    += bitsVec;

  // mb->headerBits should be initialized in vlcSendSkipCount
  mb->headerBits += bitsMBtype + bitsPred + bitsVec;
}


/*
 * streamSendLumaCoeffs:
 *
 * Parameters:
 *      stream                bitbuffer for CAVLC
 *      mb                    Macroblock object
 *      stat                  Statistics
 * 
 * Function:
 *      Code all luma coefficients within a macroblock in CAVLC
 *      
 * Returns:
 *      Number of bits used.
 */
int streamSendLumaCoeffs(void         *stream, 
                         macroblock_s *mb, 
                         statSlice_s  *stat)
{
  int i, j;
  int bits, totalBits;
  unsigned int cbpY;


  totalBits = 0;

  if (mb->type == MBK_INTRA && mb->intraType == MBK_INTRA_TYPE2) 
  {
    int numCoefs;

    // send DC coefficients
    bits = streamSend4x4Blk(stream,
      mb, 1, COMP_LUMA, 0, 0, mb->dcCoefY, BLK_CAT_Y_I16x16_DC, & numCoefs);

    /* Luma DC coefficients are sent for 16x16 intra */
    totalBits += bits;
    stat->bitsCoefLumaDC += bits;
  }

  // most blocks are zero anyway, clear all of them up-front 
  // instead of clearing them selectively
  for (j = 0; j < 4; j ++)
    for (i = 0; i < 4; i ++)
      mb->current[j][i].numLumaCoefs = 0;

  cbpY = mb->cbpY;
  if (cbpY != 0) 
  {
    int blk8x8, blkIdx;
    int blkCategory;

    bits   = 0;
    blkCategory = BLK_CAT_Y;

    if (mb->type == MBK_INTRA && mb->intraType == MBK_INTRA_TYPE2) {
      /* In 16x16 INTRA, if there is even one nonzero block in MB, */
      /* all blocks will be sent (even if it means sending EOBs)   */
      cbpY = 0xFFFF;
      blkCategory = BLK_CAT_Y_I16x16_AC;
    }

    for (blk8x8 = 0; blk8x8 < 16; blk8x8 += 4)
    {
      if ((cbpY & 0x000F) == 0)
        cbpY >>= 4;
      else
      {
        for (blkIdx = blk8x8; blkIdx < (blk8x8 + 4); blkIdx ++)
        {
          int numCoefs;
          int blkX, blkY;

          blkX = blkRasterOrder[blkIdx] & 3;
          blkY = blkRasterOrder[blkIdx] >> 2;

          bits += streamSend4x4Blk(stream,
            mb, cbpY & 1, COMP_LUMA, blkX, blkY, mb->coefY[blkIdx], blkCategory, & numCoefs);

          mb->current[blkY][blkX].numLumaCoefs = (int8) numCoefs;

          cbpY >>= 1;
        }
      }
    }

    totalBits += bits;
    stat->bitsCoefLuma += bits;
  }

  return totalBits;
}


/*
 * streamSendChromaCoeffs:
 *
 * Parameters:
 *      stream                bitbuffer for CAVLC
 *      mb                    Macroblock object
 *      stat                  Statistics
 * 
 * Function:
 *      Code all chroma coefficients within a macroblock in CAVLC
 *      
 * Returns:
 *      Number of bits used.
 */
int streamSendChromaCoeffs(void         *stream, 
                           macroblock_s *mb, 
                           statSlice_s  *stat)
{
  int dcBits, acBits, cbpC;

  
  dcBits = 0;
  acBits = 0;

  if ((mb->cbpChromaDC | mb->cbpC) != 0)
  {
    // although mb->cbpC == 1 && mb->cbpChromaDC == 0 is possible,
    // and it seems to be it is not necessary to send dc at all,
    // but this is not supported by syntax
    dcBits  = streamSend2x2ChromaDC(stream,
      & mb->dcCoefC[0][0][0]);

    dcBits += streamSend2x2ChromaDC(stream,
      & mb->dcCoefC[1][0][0]);
  }

#ifdef COPY_4_BYTES_AS_32_BITS
  * ((u_int32 *) & mb->mbThis->numChromaCoefs[0][0][0]) = 0;
  * ((u_int32 *) & mb->mbThis->numChromaCoefs[1][0][0]) = 0;
#else
  mb->mbThis->numChromaCoefs[0][0][0] = mb->mbThis->numChromaCoefs[0][0][1] = 
  mb->mbThis->numChromaCoefs[1][0][0] = mb->mbThis->numChromaCoefs[1][0][1] = 
  mb->mbThis->numChromaCoefs[0][1][0] = mb->mbThis->numChromaCoefs[0][1][1] =
  mb->mbThis->numChromaCoefs[1][1][0] = mb->mbThis->numChromaCoefs[1][1][1] = 0;
#endif

  cbpC = mb->cbpC;

  if (cbpC != 0)
  {
    int comp;
    int i, j;
    int numCoefs;

    for (comp = 0; comp < 2; comp++) {
      for (j = 0; j < 2; j++) {
        for (i = 0; i < 2; i++) {
          acBits += streamSend4x4Blk(stream,
            mb, cbpC & 1, comp + 1, i, j, mb->coefC[comp][j][i], BLK_CAT_C_AC, & numCoefs);

          // store numCoefs in the buffer for future numCoefs prediction
          mb->mbThis->numChromaCoefs[comp][j][i] = (int8) numCoefs;

          cbpC >>= 1;
        }
      }
    }
  }

  stat->bitsCoefChromaDC += dcBits;
  stat->bitsCoefChroma   += acBits;

  return (dcBits + acBits);
}
