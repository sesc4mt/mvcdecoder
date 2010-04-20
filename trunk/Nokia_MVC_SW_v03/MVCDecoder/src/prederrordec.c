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
#include "invtransform.h"
#include "prederrordec.h"


#ifndef AVC_RECO_BLOCK_ASM

static const int dequantCoef[6][8] = {
  {10, 13, 13, 16, 10, 13, 13, 16},
  {11, 14, 14, 18, 11, 14, 14, 18},
  {13, 16, 16, 20, 13, 16, 16, 20},
  {14, 18, 18, 23, 14, 18, 18, 23},
  {16, 20, 20, 25, 16, 20, 20, 25},
  {18, 23, 23, 29, 18, 23, 23, 29}
};

#endif


static const int16 dequantCoefDC[52] = {
  10<<0, 11<<0, 13<<0, 14<<0, 16<<0, 18<<0,
  10<<1, 11<<1, 13<<1, 14<<1, 16<<1, 18<<1,
  10<<2, 11<<2, 13<<2, 14<<2, 16<<2, 18<<2,
  10<<3, 11<<3, 13<<3, 14<<3, 16<<3, 18<<3,
  10<<4, 11<<4, 13<<4, 14<<4, 16<<4, 18<<4,
  10<<5, 11<<5, 13<<5, 14<<5, 16<<5, 18<<5,
  10<<6, 11<<6, 13<<6, 14<<6, 16<<6, 18<<6,
  10<<7, 11<<7, 13<<7, 14<<7, 16<<7, 18<<7,
  10<<8, 11<<8, 13<<8, 14<<8
};


static const int zeroValues[16] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


/* pedRecoBlock, pedRecoBlockNoAC and pedRecoBlockNoCoef have */
/* equivalent assembly functions.                             */
#ifndef AVC_RECO_BLOCK_ASM

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

  /* Compute qp/6 */
  int qp_per = (43 * qp) >> 8;

  /* Compute qp%6 */
  int qp_rem = qp - 6*qp_per;

  itrIDCTdequant4x4(coef, tmpBlk, dequantCoef[qp_rem], qp_per,
                    isDc, dcValue);

  for (j = 0; j < BLK_SIZE; j++, reco += recoWidth) {
    for (i = 0; i < BLK_SIZE; i++) {
      /* Add prediction error to prediction and round to nearest */
      tmp = pred[j][i] + ((tmpBlk[j][i] + ITR_DEQUANT_ROUND) >> ITR_DEQUANT_BITS);
      /* Clipping */
      reco[i] = (u_int8)(clip(0,255,tmp));
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
  int tmp;

  recoDCint = (dcValue + ITR_DEQUANT_ROUND) >> ITR_DEQUANT_BITS;

  for (j = 0; j < BLK_SIZE; j++, reco += recoWidth) {
    for (i = 0; i < BLK_SIZE; i++) {
      /* Add prediction error to prediction */
      tmp = pred[j][i] + recoDCint;
      /* Clipping */
      reco[i] = (u_int8)(clip(0,255,tmp));
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
  int j;

  for (j = 0; j < BLK_SIZE; j++) {
    reco[0] = pred[j][0];
    reco[1] = pred[j][1];
    reco[2] = pred[j][2];
    reco[3] = pred[j][3];
    reco += recoWidth;
  }
}

#endif      /* End of #ifndef AVC_ARM_ASSEMBLY */


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
void pedRecoLumaMB(u_int8 pred[MBK_SIZE][MBK_SIZE],
                   int dcCoef[BLK_PER_MB][BLK_PER_MB], int hasDC,
                   int coef[BLK_PER_MB][BLK_PER_MB][BLK_SIZE][BLK_SIZE],
                   u_int8 *reco, int recoWidth, int qp, int cbp)
{
  int dcCoefTmp[BLK_PER_MB][BLK_PER_MB];
  const int *dcCoefPtr;
  int blkIdxX, blkIdxY;
  int dcValue;
  u_int8 *predPtr;


  /*
   * Inverse transform and quantize luma DC (if 16x16 intra mode)
   */

  if (hasDC) {
    /* 4x4 DC Inv. Hadamard */
    itrIHadaDequant4x4(dcCoef, dcCoefTmp, dequantCoefDC[qp]);
    dcCoefPtr = &dcCoefTmp[0][0];
  }
  else
    dcCoefPtr = zeroValues;


  /*
   * Luma block reconstruction
   */

  dcValue = 0;
  predPtr = pred[0];

  for (blkIdxY = 0; blkIdxY < BLK_PER_MB; blkIdxY++) {
    for (blkIdxX = 0; blkIdxX < BLK_PER_MB; blkIdxX++) {

      dcValue = *dcCoefPtr++;

      if ((cbp & 1) == 0) {
        if (dcValue == 0) {
#ifndef AVC_RECO_BLOCK_ASM
          pedRecoBlockNoCoef((u_int8 (*)[MBK_SIZE])&predPtr[blkIdxX*BLK_SIZE],
                             &reco[blkIdxX*BLK_SIZE], recoWidth);
#else
            u_int8 *src, *dest;
            src  = &predPtr[blkIdxX*BLK_SIZE];
            dest = &reco[blkIdxX*BLK_SIZE];
            *((u_int32 *)dest)               = *((u_int32 *) src);
            *((u_int32 *)&dest[  recoWidth]) = *((u_int32 *)&src[  MBK_SIZE]);
            *((u_int32 *)&dest[2*recoWidth]) = *((u_int32 *)&src[2*MBK_SIZE]);
            *((u_int32 *)&dest[3*recoWidth]) = *((u_int32 *)&src[3*MBK_SIZE]);
#endif
        }
        else {
          pedRecoBlockNoAC((u_int8 (*)[MBK_SIZE])&predPtr[blkIdxX*BLK_SIZE],
                           &reco[blkIdxX*BLK_SIZE], recoWidth, dcValue);
        }
      }
      else {
        pedRecoBlock((u_int8 (*)[MBK_SIZE])&predPtr[blkIdxX*BLK_SIZE],
                     coef[blkIdxY][blkIdxX], &reco[blkIdxX*BLK_SIZE],
                     recoWidth, hasDC, dcValue, qp);
      }

      cbp >>= 1;
    }

    reco += BLK_SIZE*recoWidth;
    predPtr += BLK_SIZE*MBK_SIZE;
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
void pedRecoChromaMB(u_int8 pred[MBK_SIZE/2][MBK_SIZE],
                     int dcCoef[2][BLK_PER_MB/2][BLK_PER_MB/2],
                     int coef[2][BLK_PER_MB/2][BLK_PER_MB/2][BLK_SIZE][BLK_SIZE],
                     u_int8 *recoU, u_int8 *recoV, int recoWidth, int qp,
                     int cbpDC, int cbp)
{
  int dcCoefTmp[BLK_PER_MB/2][BLK_PER_MB/2];
  const int *dcCoefPtr;
  int comp;
  int blkIdxX, blkIdxY;
  int dcValue;
  u_int8 *reco;
  u_int8 *predPtr;

  /* 
   * Chroma MB reconstruction
   */

  for (comp = 0; comp < 2; comp++) {

    if (cbpDC & (1<<comp)) {
      /* 2x2 DC inverse transform and dequant */
      itrIDCTdequant2x2(dcCoef[comp], dcCoefTmp, dequantCoefDC[qp]);
      dcCoefPtr = &dcCoefTmp[0][0];
    }
    else
      /* DC coefficients are zero */
      dcCoefPtr = zeroValues;

    reco = comp == 0 ? recoU : recoV;
    predPtr = &pred[0][comp*(MBK_SIZE/2)];

    /*
     * AC reconstruction
     */

    for (blkIdxY = 0; blkIdxY < BLK_PER_MB/2; blkIdxY++) {
      for (blkIdxX = 0; blkIdxX < BLK_PER_MB/2; blkIdxX++) {

        dcValue = *dcCoefPtr++;

        if ((cbp & 1) == 0) {
          if (dcValue == 0) {
#ifndef AVC_RECO_BLOCK_ASM
            pedRecoBlockNoCoef((u_int8 (*)[MBK_SIZE])&predPtr[blkIdxX*BLK_SIZE],
                               &reco[blkIdxX*BLK_SIZE], recoWidth);
#else
            u_int8 *src, *dest;
            src  = &predPtr[blkIdxX*BLK_SIZE];
            dest = &reco[blkIdxX*BLK_SIZE];
            *((u_int32 *)dest)               = *((u_int32 *) src);
            *((u_int32 *)&dest[  recoWidth]) = *((u_int32 *)&src[  MBK_SIZE]);
            *((u_int32 *)&dest[2*recoWidth]) = *((u_int32 *)&src[2*MBK_SIZE]);
            *((u_int32 *)&dest[3*recoWidth]) = *((u_int32 *)&src[3*MBK_SIZE]);
#endif
          }
          else {
            pedRecoBlockNoAC((u_int8 (*)[MBK_SIZE])&predPtr[blkIdxX*BLK_SIZE],
                             &reco[blkIdxX*BLK_SIZE], recoWidth, dcValue);
          }
        }
        else {
          pedRecoBlock((u_int8 (*)[MBK_SIZE])&predPtr[blkIdxX*BLK_SIZE],
                       coef[comp][blkIdxY][blkIdxX], &reco[blkIdxX*BLK_SIZE],
                       recoWidth, 1, dcValue, qp);
        }

        cbp >>= 1;
      }

      reco += BLK_SIZE*recoWidth;
      predPtr += BLK_SIZE*MBK_SIZE;
    }
  }
}
