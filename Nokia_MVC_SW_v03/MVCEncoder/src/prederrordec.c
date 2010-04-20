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
 * prederrordec.c
 *
 * Contains:
 *    Functions for prediction error decoding.
 *
 */

#include "globals.h"
#include "nrctypes.h"
#include "invtransform.h"
#include "prederrordec.h"


/*
 *
 * pedRecoBlock:
 *
 * Parameters:
 *      pred                  Predicted pixels for a block
 *      coef                  Transformed&quantized coefficients for a block
 *      reco                  Reconstructed pixels
 *      recoWidth             Width of reco. buffer in pixels
 *      isDc                  Does block have separate DC coefficient
 *      dcValue               DC coefficient
 *      qp                    Quantization parameter
 *
 * Function:
 *      Dequantize and inverse transform coefficients and add result
 *      with prediction.
 *
 * Returns:
 *      -
 */
void pedRecoBlock(u_int8 pred[BLK_SIZE][MBK_SIZE],
                  int coef[BLK_SIZE][BLK_SIZE],
                  u_int8 *reco, int recoWidth,
                  int isDc, int dcValue, int qp)
{
  int tmpBlk[BLK_SIZE][BLK_SIZE];
  int i, j;
  int tmp;


  itrInvQuant4x4(& coef[0][0], & tmpBlk[0][0], qp);

  if (isDc)
    tmpBlk[0][0] = dcValue;  /* Insert DC coef if requested */
  
  itrIDCT4x4(tmpBlk);

  for (j = 0; j < BLK_SIZE; j++, reco += recoWidth) {
    for (i = 0; i < BLK_SIZE; i++) {
      /* Add prediction error to prediction and round to nearest */
      tmp = (tmpBlk[j][i] + ITR_DEQUANT_ROUND) >> ITR_DEQUANT_BITS;
      /* Clipping */
      reco[i] = (u_int8) clip(0, 255, tmp + (int)pred[j][i]);
    }
  }
}


/*
 *
 * pedRecoBlockNoAC:
 *
 * Parameters:
 *      pred                  Predicted pixels
 *      reco                  Reconstructed pixels
 *      recoWidth             Width of reco. buffer in pixels
 *      dcValue               DC coefficient
 *
 * Function:
 *      All AC coefficients are zero - reconstruct using DC only.
 *
 * Returns:
 *      -
 */
void pedRecoBlockNoAC(u_int8 pred[BLK_SIZE][MBK_SIZE],
                      u_int8 *reco, int recoWidth,
                      int dcValue)
{
  int i, j;
  int recoDCint;

  
  recoDCint = (dcValue + ITR_DEQUANT_ROUND) >> ITR_DEQUANT_BITS;

  for (j = 0; j < BLK_SIZE; j++, reco += recoWidth) {
    for (i = 0; i < BLK_SIZE; i++) {
      /* Add prediction error to prediction and Clipping */
      reco[i] = (u_int8) clip(0, 255, (int)pred[j][i] + recoDCint);
    }
  }
}


/*
 *
 * pedRecoBlockNoCoef:
 *
 * Parameters:
 *      pred                  Predicted pixels
 *      reco                  Reconstructed pixels
 *      recoWidth             Width of reco. buffer in pixels
 *
 * Function:
 *      All coefficients are zero - just copy prediction.
 *
 * Returns:
 *      -
 */
void pedRecoBlockNoCoef(u_int8 pred[BLK_SIZE][MBK_SIZE],
                        u_int8 *reco, int recoWidth)
{
#ifdef COPY_4_BYTES_AS_32_BITS
  // copy 4 bytes at a time
  * (int32 *) & reco[recoWidth * 0] = * (int32 *) & pred[0][0];
  * (int32 *) & reco[recoWidth * 1] = * (int32 *) & pred[1][0];
  * (int32 *) & reco[recoWidth * 2] = * (int32 *) & pred[2][0];
  * (int32 *) & reco[recoWidth * 3] = * (int32 *) & pred[3][0];
#else
  int i;
  for (i = 0; i < 4; i++)
  {
    reco[i * recoWidth + 0] = pred[i][0];
    reco[i * recoWidth + 1] = pred[i][1];
    reco[i * recoWidth + 2] = pred[i][2];
    reco[i * recoWidth + 3] = pred[i][3];
  }
#endif
}


/*
 *
 * pedRecoLumaMB:
 *
 * Parameters:
 *      pred                  Predicted pixels for an MB
 *      dcCoef                Transformed&quantized DC coefficients for an MB
 *      hasDc                 Do blocks have separate DC coefficients
 *      coef                  Transformed&quantized coefficients for an MB
 *      reco                  Reconstructed pixels
 *      recoWidth             Width of reco. buffer in pixels
 *      qp                    Quantization parameter
 *      cbp                   Coded Block Pattern
 *
 * Function:
 *      Reconstruct macroblock from prediction and transformed coefficients
 *
 * Returns:
 *      -
 */
void pedRecoLumaMB(macroblock_s *pMb,
                   u_int8 pred[MBK_SIZE][MBK_SIZE],
                   int hasDC,
                   int recoWidth)
{
  int dcCoefTmp[BLK_PER_MB][BLK_PER_MB];
  int blkIdx;
  int dcValue;
  unsigned int cbp;


  /*
   * Inverse transform and quantize luma DC (if 16x16 intra mode)
   */
  if (hasDC) {

    /* 4x4 DC Inv. DCT */
    itrIHada4x4(pMb->dcCoefY, dcCoefTmp);

    itrInvQuantDC4x4(& dcCoefTmp[0][0], & dcCoefTmp[0][0], pMb->qp);
  }

  /*
   * Luma block reconstruction
   */
  dcValue = 0;

  cbp = pMb->cbpY;

  for (blkIdx = 0; blkIdx < 16; blkIdx ++) {
    int blkX, blkY;
    u_int8 *predBlk;
    u_int8 *recoBlk;

    blkX = blkRasterOrder[blkIdx] & 3;
    blkY = blkRasterOrder[blkIdx] >> 2;

    predBlk = & pred[blkY * BLK_SIZE][blkX * BLK_SIZE];
    recoBlk = & pMb->recoY[blkY * BLK_SIZE * recoWidth + blkX * BLK_SIZE];

    if (hasDC) 
      dcValue = dcCoefTmp[blkY][blkX];

    if ((cbp & 1) == 0) {
      if (dcValue == 0) {
        pedRecoBlockNoCoef((u_int8 (*)[MBK_SIZE])predBlk, recoBlk, recoWidth);
      }
      else {
        pedRecoBlockNoAC((u_int8 (*)[MBK_SIZE])predBlk, recoBlk, recoWidth, dcValue);
      }
    }
    else {
      pedRecoBlock((u_int8 (*)[MBK_SIZE])predBlk, pMb->coefY[blkIdx],
                    recoBlk, recoWidth, hasDC, dcValue, pMb->qp);
    }

    cbp >>= 1;
  }
}


/*
 *
 * pedRecoChromaMB:
 *
 * Parameters:
 *      pred                  Predicted pixels for an MB
 *      dcCoef                Transformed&quantized DC coefficients for an MB
 *      coef                  Transformed&quantized coefficients for an MB
 *      recoU                 Reconstructed U pixels
 *      recoV                 Reconstructed V pixels
 *      recoWidth             Width of reco. buffer in pixels
 *      qp                    Quantization parameter
 *      cbpDC                 Coded Block Pattern for DC coefficient blocks
 *      cbp                   Coded Block Pattern for AC coefficient blocks
 *
 * Function:
 *      Reconstruct chroma blocks from prediction and coefficients.
 *
 * Returns:
 *      -
 */
void pedRecoChromaMB(macroblock_s *pMb,
                     u_int8 predC[MBK_SIZE/2][2*(MBK_SIZE/2)],
                     int recoWidth)
{
  int dcCoefTmp[BLK_PER_MB/2][BLK_PER_MB/2];
  int comp;
  int blkIdxX, blkIdxY;
  u_int8 *reco;
  unsigned int cbp;


  cbp = pMb->cbpC;

  /* 
   * Chroma MB reconstruction
   */
  for (comp = 0; comp < 2; comp++) {

    if ((pMb->cbpChromaDC & (1 << comp)) == 0) {
      dcCoefTmp[0][0] = dcCoefTmp[0][1] =
      dcCoefTmp[1][0] = dcCoefTmp[1][1] = 0;
    }
    else {
      /* 2x2 DC IDCT */
      itrIDCT2x2(pMb->dcCoefC[comp], dcCoefTmp);

      /* 2x2 DC inv. quant */
      itrInvQuantDC2x2(& dcCoefTmp[0][0], & dcCoefTmp[0][0], pMb->qpC);
    }

    reco = comp == 0 ? pMb->recoU : pMb->recoV;

    /* AC reconstruction */
    for (blkIdxY = 0; blkIdxY < BLK_PER_MB/2; blkIdxY++) {
      for (blkIdxX = 0; blkIdxX < BLK_PER_MB/2; blkIdxX++) {
        u_int8 *predBlk;
        u_int8 *recoBlk;

        predBlk = & predC[blkIdxY*BLK_SIZE][comp*(MBK_SIZE/2)+blkIdxX*BLK_SIZE];
        recoBlk = & reco[blkIdxY*BLK_SIZE*recoWidth+blkIdxX*BLK_SIZE];

        if ((cbp & 1) == 0) {
          if (dcCoefTmp[blkIdxY][blkIdxX] == 0) {
            pedRecoBlockNoCoef((u_int8 (*)[MBK_SIZE])predBlk, recoBlk, recoWidth);
          }
          else {
            pedRecoBlockNoAC((u_int8 (*)[MBK_SIZE]) predBlk, recoBlk,
                             recoWidth, dcCoefTmp[blkIdxY][blkIdxX]);
          }
        }
        else {
          pedRecoBlock((u_int8 (*)[MBK_SIZE]) predBlk, 
            pMb->coefC[comp][blkIdxY][blkIdxX],
            recoBlk, recoWidth, 1, dcCoefTmp[blkIdxY][blkIdxX], pMb->qpC);
        }

        cbp >>= 1;
      }
    }
  }
}

