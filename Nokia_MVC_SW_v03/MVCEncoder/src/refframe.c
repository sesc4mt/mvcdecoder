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
 * refframe.c
 *
 * Contains:
 *
 *    Reference frame operations.
 *
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "nccglob.h"
#include "debug.h"
#include "refframe.h"

#define ONEFOURTH1  20
#define ONEFOURTH2  -5
#define ONEFOURTH3  1


void refFrmUpsampleLumaH(u_int8  *yBuf, u_int8 *reco, int picWidth,
                         int picHeight, int xExt, int yExt);

void refFrmUpsampleLumaV(u_int8  *yBuf, int picWidth, int picHeight,
                         int xExt, int yExt);

void refFrmPartialSum8x8(u_int8  *yBufIn, u_int16 *seaYBufIn,
                         int picWidth, int picHeight, int xExt, int yExt);


#ifdef USE_CLIPBUF
const u_int8 clip8Buf[768] = 
{
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
   32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 
   48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
   64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 
   80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 
   96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111,
  112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,
  128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
  144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
  160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,
  176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,
  192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,
  208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,
  224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
  240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
};
#endif


/*
 *
 * allocMemRef:
 *
 * Parameters:
 *      blkSize               Block size
 *      unitSize              unit size
 *
 * Function:
 *      Allocate blkSize*unitSize bytes of memory
 *
 * Returns:
 *      Pointer to allocated memory
 *
 */
static void *allocMemRef(int blkSize, size_t unitSize)
{
  void *mem;

  if ((mem = nccMalloc(blkSize*unitSize)) == NULL) {
#ifdef DEBUG_PRINT
    printf("Cannot allocate memory for reference frame\n");
#endif
    nccExit(1);
  }

  return mem;
}


/*
 *
 * refFrmOpen:
 *
 * Parameters:
 *      pRefFrm        Pointer to reference frame object
 *      pEncPar        Pointer to encoding parameter object
 *
 * Function:
 *      Initialize the reference frame object, and allocate memory for frame 
 *      buffers. Each component has separate buffer, with extended area for 
 *      the extended bounfaries. Y buffer is different from u/v buffer in 
 *      that Y samples will be upsampled by 2 in both directions.
 *
 * Returns:
 *      -
 *
 */
void refFrmOpen(refFrmBuf_s *pRefFrm, encParams_s *pEncPar)
{
  int extWidth, extHeight, extBufSize;
  
  pRefFrm->picWidth  = (int16) pEncPar->picWidth;
  pRefFrm->picHeight = (int16) pEncPar->picHeight;

  // xExt & yExt are specified for original y, 
  // so for y in reference buffer, the actual extension is twice as much, 
  // but the extension for u/v is only half of xExt and yExt.
  // extension of 16 is not necessary, not it is nice to align the buffer
  pRefFrm->xExt = 16;
  pRefFrm->yExt = 16;

  // leave some margin so that it is easier to take care 
  // boundary coundition in motion search
  pRefFrm->searchArea.x0 = (int16)(-pRefFrm->xExt + 2);
  pRefFrm->searchArea.y0 = (int16)(-pRefFrm->yExt + 2);

  pRefFrm->searchArea.x1 = (int16)(pRefFrm->picWidth  + pRefFrm->xExt - 2);
  pRefFrm->searchArea.y1 = (int16)(pRefFrm->picHeight + pRefFrm->yExt - 2);

  extWidth  = pRefFrm->picWidth  + pRefFrm->xExt * 2;
  extHeight = pRefFrm->picHeight + pRefFrm->yExt * 2;

  pRefFrm->yBufWidth  = (int16) (extWidth * 2);
  pRefFrm->yBufHeight = (int16) (extHeight * 2);

  pRefFrm->cBufWidth = (int16) (extWidth >> 1);

  extBufSize = extWidth * extHeight;

#ifdef ENABLE_SEARCH_WINDOW
  if (!pEncPar->useSearchWin)
    pRefFrm->yBuf = (u_int8 *) allocMemRef(4 * extBufSize, sizeof(u_int8));
  else
    pRefFrm->yBuf = (u_int8 *) allocMemRef(pRefFrm->picWidth * pRefFrm->picHeight, sizeof(u_int8));
#else
  pRefFrm->yBuf = (u_int8 *) allocMemRef(4 * extBufSize, sizeof(u_int8));
#endif
  pRefFrm->uBuf = (u_int8 *) allocMemRef(extBufSize/4, sizeof(u_int8));
  pRefFrm->vBuf = (u_int8 *) allocMemRef(extBufSize/4, sizeof(u_int8));

  // always use SEA
  // take away partial sum for prof3
  if (!pEncPar->low_complex_prof3)
    pRefFrm->seaYBuf = (u_int16 *)allocMemRef(extBufSize, sizeof(u_int16));

  // the pointers pointing the first actual samples
  // y is upsampled by 2 in both horizontal and vertical directions
  pRefFrm->y = pRefFrm->yBuf + 
    pRefFrm->yBufWidth * pRefFrm->yExt * 2 + pRefFrm->xExt * 2;

  pRefFrm->u = pRefFrm->uBuf + 
    pRefFrm->cBufWidth * (pRefFrm->yExt/2) + pRefFrm->xExt/2;

  pRefFrm->v = pRefFrm->vBuf + 
    pRefFrm->cBufWidth * (pRefFrm->yExt/2) + pRefFrm->xExt/2;
  
  // take away partial sum
  if (!pEncPar->low_complex_prof3)
    pRefFrm->partSums = 
      pRefFrm->seaYBuf + extWidth * pRefFrm->yExt + pRefFrm->xExt;

  pRefFrm->forOutput = 0;
  pRefFrm->forRef = 0;
  pRefFrm->frameNum = -1;
  pRefFrm->isShortTerm = -1;
  pRefFrm->picNum = 0;

  // the channel distortion array is based on MBs
  if (pEncPar->irType == PDT_IR || pEncPar->irType == PDT_IR_LC)
    pRefFrm->channelDistortion = (int32*)nccMalloc(sizeof(int32)*pRefFrm->picWidth/MBK_SIZE * pRefFrm->picHeight/MBK_SIZE);
  else
    pRefFrm->channelDistortion = NULL;

  pRefFrm->viewId = 0;		// Initialize to zero for all frames
}


/*
 *
 * refFrmClose:
 *
 * Parameters:
 *      pRefFrm                 Pointer to reference frame object to be released
 *      low_complex_prof3       Low complexity prof 3
 *      useSearchWin            Use internal search window
 *
 * Function:
 *      Deallocate reference frame buffer memory.
 *
 * Returns:
 *      -
 *
 */
void refFrmClose(refFrmBuf_s *pRefFrm, int low_complex_prof3
#ifdef ENABLE_SEARCH_WINDOW
                 , int useSearchWin
#endif
                 )
{
  nccFree(pRefFrm->yBuf);
  nccFree(pRefFrm->uBuf);
  nccFree(pRefFrm->vBuf);

  // take away partial sum

  if (!low_complex_prof3)
    nccFree(pRefFrm->seaYBuf);

  if (pRefFrm->channelDistortion)
    nccFree(pRefFrm->channelDistortion);
}


/*
 *
 * refFrmUpsampleLumaH
 *
 * Parameters:
 *      reco                 y component of reconstructed frame
 *      yBuf                 Luma reference pixels
 *      picWidth             Picture width in pixels
 *      picHeight            Picture height in pixels
 *      xExt                 Reference frame x-extension in pixels
 *      yExt                 Reference frame y-extension in pixels
 *
 * Function:
 *      Horizontal upsampling of luma.
 *
 *
 * Returns:
 *      -
 */
#if 1
void refFrmUpsampleLumaH(u_int8 *reco, u_int8  *yBuf, int picWidth,
                         int picHeight, int xExt, int yExt)
{
  int i, j, tmp;
  u_int8  *yBufLine;
  int extBufWidth;

  // pRefFrm->yBufWidth/height has extended boundary 
  extBufWidth  = 2*(picWidth + 2*xExt);

  yBufLine = yBuf + 2*yExt*extBufWidth;

  // upsample by 2 and filter horizontally
  for (i = 0; i < picHeight; i ++)
  {
    int a, b, c, d, e, f;

    a = *reco++;              // left pixel

    // left extension, these pixels are indentical
    for (j = xExt-2; j > 0; j--)
    {
      // left boundary
      *yBufLine++ = (u_int8) a;
      *yBufLine++ = (u_int8) a;
    }

    // Horizontal filtering to generate odd locations

    // Interpolate 6 values per iteration. We'll use variable
    // a,b,c,d,e and f in rotating manner to avoid unnecessary mem loads
    b = c = d = e = a;
    for (j = (2 + picWidth - 3) - 6; j >= 0; j -= 6)
    {
      f = *reco++;
      *yBufLine++ = (u_int8) c;
      tmp = (a + 5*(-b + 4*(c + d) - e) + f + 16) >> 5;
#ifdef USE_CLIPBUF
      *yBufLine++ = clip8Buf[tmp+256];
#else
      *yBufLine++ = (u_int8) clip(0, 255, tmp);
#endif

      a = *reco++;
      *yBufLine++ = (u_int8) d;
      tmp = (b + 5*(-c + 4*(d + e) - f) + a + 16) >> 5;
#ifdef USE_CLIPBUF
      *yBufLine++ = clip8Buf[tmp+256];
#else
      *yBufLine++ = (u_int8) clip(0, 255, tmp);
#endif

      b = *reco++;
      *yBufLine++ = (u_int8) e;
      tmp = (c + 5*(-d + 4*(e + f) - a) + b + 16) >> 5;
#ifdef USE_CLIPBUF
      *yBufLine++ = clip8Buf[tmp+256];
#else
      *yBufLine++ = (u_int8) clip(0, 255, tmp);
#endif

      c = *reco++;
      *yBufLine++ = (u_int8) f;
      tmp = (d + 5*(-e + 4*(f + a) - b) + c + 16) >> 5;
#ifdef USE_CLIPBUF
      *yBufLine++ = clip8Buf[tmp+256];
#else
      *yBufLine++ = (u_int8) clip(0, 255, tmp);
#endif

      d = *reco++;
      *yBufLine++ = (u_int8) a;
      tmp = (e + 5*(-f + 4*(a + b) - c) + d + 16) >> 5;
#ifdef USE_CLIPBUF
      *yBufLine++ = clip8Buf[tmp+256];
#else
      *yBufLine++ = (u_int8) clip(0, 255, tmp);
#endif

      e = *reco++;
      *yBufLine++ = (u_int8) b;
      tmp = (f + 5*(-a + 4*(b + c) - d) + e + 16) >> 5;
#ifdef USE_CLIPBUF
      *yBufLine++ = clip8Buf[tmp+256];
#else
      *yBufLine++ = (u_int8) clip(0, 255, tmp);
#endif
    }

    // Interpolate remaining (2 + picWidth - 3)%6 values
    for (j = j + 6; j > 0; j--) {
      f = *reco++;
      *yBufLine++ = (u_int8) c;
      tmp = (a + 5*(-b + 4*(c + d) - e) + f + 16) >> 5;
#ifdef USE_CLIPBUF
      *yBufLine++ = clip8Buf[tmp+256];
#else
      *yBufLine++ = (u_int8) clip(0, 255, tmp);
#endif
      a = b;
      b = c;
      c = d;
      d = e;
      e = f;
    }

    // Interpolate 4 last values that are interpolated
    // across the picture border
    f = e;
    for (j = 4; j > 0; j--) {
      *yBufLine++ = (u_int8) c;
      tmp = (a + 5*(-b + 4*(c + d) - e) + f + 16) >> 5;
#ifdef USE_CLIPBUF
      *yBufLine++ = clip8Buf[tmp+256];
#else
      *yBufLine++ = (u_int8) clip(0, 255, tmp);
#endif
      a = b;
      b = c;
      c = d;
      d = e;
    }

    // right extension, these pixels are indentical
    for (j = xExt-1; j > 0; j--)
    {
      // right boundary
      *yBufLine++ = (u_int8) e;
      *yBufLine++ = (u_int8) e;
    }

    yBufLine += extBufWidth;
  }

  // perform vertical boundary extension
  // the first line in the active area
  yBufLine = yBuf + 2 * yExt * extBufWidth;
  for (i = 0; i < (yExt * 2); i ++)
  {
    memcpy(yBuf + i * extBufWidth, yBufLine, extBufWidth * sizeof(u_int8));
  }

  // the last line in the active area
  yBufLine += (picHeight * 2 - 2) * extBufWidth;
  for (i = 2 * (yExt + picHeight); i < (2 * (2 * yExt + picHeight)); i ++)
  {
    memcpy(yBuf + i * extBufWidth, yBufLine,  extBufWidth * sizeof(u_int8));
  }
}
#else
// this is a SIMD version of the horizontal filtering function
void refFrmUpsampleLumaH(u_int8 *reco, u_int8  *yBuf, int picWidth,
                         int picHeight, int xExt, int yExt)
{
  int i, j;
  int32 tmp;
  u_int8  *yBufLine;
  int extBufWidth;

  // pRefFrm->yBufWidth/height has extended boundary 
  extBufWidth  = 2*(picWidth + 2*xExt);

  yBufLine  = yBuf + 2*yExt*extBufWidth;

  // upsample by 2 and filter horizontally
  for (i = 0; i < picHeight; i ++)
  {
    int32 a, b, c, d, e, f;

    a = *reco++;              // left pixel

    // left extension, these pixels are indentical
    for (j = xExt-2; j > 0; j--)
    {
      // left boundary
      *yBufLine++ = (u_int8) a;
      *yBufLine++ = (u_int8) a;
    }

    // Horizontal filtering to generate odd locations

    // Interpolate 6 values per iteration. We'll use variable
    // a,b,c,d,e and f in rotating manner to avoid unnecessary mem loads
    // this is doing filtering in SIMD style, two 16 bits values in one int32
    a = (a << 16) | a;
    b = c = d = a;
    for (j = (2 + picWidth - 3) - 6; j >= 0; j -= 6)
    {
      e = *reco++;
      f = *reco++;
      f = (e << 16) | f;
      e = (d << 16) | e;
      tmp = a + 5*(-b + 4*(c + d) - e) + f + 0x20102010;
      *yBufLine++ = (u_int8) b;
      *yBufLine++ = clip8Buf[tmp>>(16+5)];
      *yBufLine++ = (u_int8) c;
      *yBufLine++ = clip8Buf[(tmp >> 5) & 0x000007ff];

      a = *reco++;
      b = *reco++;
      b = (a << 16) | b;
      a = (f << 16) | a;
      tmp = c + 5*(-d + 4*(e + f) - a) + b + 0x20102010;
      *yBufLine++ = (u_int8) d;
      *yBufLine++ = clip8Buf[tmp>>(16+5)];
      *yBufLine++ = (u_int8) e;
      *yBufLine++ = clip8Buf[(tmp >> 5) & 0x000007ff];

      c = *reco++;
      d = *reco++;
      d = (c << 16) | d;
      c = (b << 16) | c;
      tmp = e + 5*(-f + 4*(a + b) - c) + d + 0x20102010;
      *yBufLine++ = (u_int8) f;
      *yBufLine++ = clip8Buf[tmp>>(16+5)];
      *yBufLine++ = (u_int8) a;
      *yBufLine++ = clip8Buf[(tmp >> 5) & 0x000007ff];
    }

    // Interpolate remaining (2 + picWidth - 3)%6 values
    for (j = j + 6; j > 0; j--) {
      e = *reco++;
      tmp = f + 5*(-a + 4*(b + c) - d) + e + 0x20102010;
      *yBufLine++ = (u_int8) b;
      *yBufLine++ = clip8Buf[(tmp >> 5) & 0x000007ff];
      f = a;
      a = b;
      b = c;
      c = d;
      d = e;
    }

    // Interpolate 4 last values that are interpolated
    // across the picture border
    e = d;
    for (j = 4; j > 0; j--) {
      tmp = f + 5*(-a + 4*(b + c) - d) + e + 0x20102010;
      *yBufLine++ = (u_int8) b;
      *yBufLine++ = clip8Buf[(tmp >> 5) & 0x000007ff];
      f = a;
      a = b;
      b = c;
      c = d;
    }

    // right extension, these pixels are indentical
    for (j = xExt-1; j > 0; j--)
    {
      // right boundary
      *yBufLine++ = (u_int8) e;
      *yBufLine++ = (u_int8) e;
    }

    yBufLine += extBufWidth;
  }

  // perform vertical boundary extension
  // the first line in the active area
  yBufLine = yBuf + 2 * yExt * extBufWidth;
  for (i = 0; i < (yExt * 2); i ++)
  {
    memcpy(yBuf + i * extBufWidth, yBufLine, extBufWidth * sizeof(u_int8));
  }

  // the last line in the active area
  yBufLine += (picHeight * 2 - 2) * extBufWidth;
  for (i = 2 * (yExt + picHeight); i < (2 * (2 * yExt + picHeight)); i ++)
  {
    memcpy(yBuf + i * extBufWidth, yBufLine,  extBufWidth * sizeof(u_int8));
  }
}
#endif


/*
 *
 * refFrmUpsampleLumaV
 *
 * Parameters:
 *      yBuf                 Luma reference pixels
 *      picWidth             Picture width in pixels
 *      picHeight            Picture height in pixels
 *      xExt                 Reference frame x-extension in pixels
 *      yExt                 Reference frame y-extension in pixels
 *
 * Function:
 *
 *      Vertical upsampling and filtering of luma.
 *
 * Returns:
 *      -
 */
#ifdef USE_CLIPBUF
void refFrmUpsampleLumaV(u_int8  *yBuf, int picWidth, int picHeight,
                         int xExt, int yExt)
{
  int extBufWidth;
  u_int8 *lnPtr, *tmpLnPtr;
  int i, j, i2;
  int32 a, b, c, d, e, f;
  int32 tmp;

  // yBuf has extended boundary
  extBufWidth  = 2*(picWidth + 2*xExt);

  // first line affected by vertical filtering
  lnPtr = yBuf + (2*yExt - 3) * extBufWidth;

  // interpolate 4 lines at a time
  for (i = picHeight + 4; i > 0; i -= 4)
  {
    tmpLnPtr = lnPtr + 2*xExt - 5*extBufWidth;

#if 1
    for (j = picWidth; j > 0; j--) {
      a = *tmpLnPtr, tmpLnPtr += 2*extBufWidth;
      b = *tmpLnPtr, tmpLnPtr += 2*extBufWidth;
      c = *tmpLnPtr, tmpLnPtr += 2*extBufWidth;
      d = *tmpLnPtr, tmpLnPtr += 2*extBufWidth;
      e = *tmpLnPtr, tmpLnPtr += 2*extBufWidth;
      f = *tmpLnPtr, tmpLnPtr += 2*extBufWidth;
      // 0x2010 is combination of rounding constant (16) and clip table offset (256)<<5
      *((int16 *)(tmpLnPtr-7*extBufWidth)) =
        (int16) (a + 5*(-b + 4*(c + d) - e) + f + 0x2010);

      a = *tmpLnPtr, tmpLnPtr += 2*extBufWidth;
      *((int16 *)(tmpLnPtr-7*extBufWidth)) =
        (int16) (b + 5*(-c + 4*(d + e) - f) + a + 0x2010);

      b = *tmpLnPtr, tmpLnPtr += 2*extBufWidth;
      *((int16 *)(tmpLnPtr-7*extBufWidth)) =
        (int16) (c + 5*(-d + 4*(e + f) - a) + b + 0x2010);

      c = *tmpLnPtr;
      *((int16 *)(tmpLnPtr-5*extBufWidth)) =
        (int16) (d + 5*(-e + 4*(f + a) - b) + c + 0x2010);

      tmpLnPtr += -16*extBufWidth + 2;
    }
#else
    // this is a SIMD version of vertical filtering.
    // works on little endian CPUs only
    for (j = picWidth; j > 0; j -= 2) {
      a = *((int32 *)tmpLnPtr) & 0x00ff00ff, tmpLnPtr += 2*extBufWidth;
      b = *((int32 *)tmpLnPtr) & 0x00ff00ff, tmpLnPtr += 2*extBufWidth;
      c = *((int32 *)tmpLnPtr) & 0x00ff00ff, tmpLnPtr += 2*extBufWidth;
      d = *((int32 *)tmpLnPtr) & 0x00ff00ff, tmpLnPtr += 2*extBufWidth;
      e = *((int32 *)tmpLnPtr) & 0x00ff00ff, tmpLnPtr += 2*extBufWidth;
      f = *((int32 *)tmpLnPtr) & 0x00ff00ff, tmpLnPtr += 2*extBufWidth;
      // 0x2010 is combination of rounding constant (16) and clip table offset (256<<5)
      *((int32 *)(tmpLnPtr-7*extBufWidth)) =
        (a + 5*(-b + 4*(c + d) - e) + f + 0x20102010);

      a = *((int32 *)tmpLnPtr) & 0x00ff00ff, tmpLnPtr += 2*extBufWidth;
      *((int32 *)(tmpLnPtr-7*extBufWidth)) =
        (b + 5*(-c + 4*(d + e) - f) + a + 0x20102010);

      b = *((int32 *)tmpLnPtr) & 0x00ff00ff, tmpLnPtr += 2*extBufWidth;
      *((int32 *)(tmpLnPtr-7*extBufWidth)) =
        (c + 5*(-d + 4*(e + f) - a) + b + 0x20102010);

      c = *((int32 *)tmpLnPtr) & 0x00ff00ff;
      *((int32 *)(tmpLnPtr-5*extBufWidth)) =
        (d + 5*(-e + 4*(f + a) - b) + c + 0x20102010);

      tmpLnPtr += -16*extBufWidth + 4;
    }
#endif

    // horizontal filtering of 4 lines 
    for (i2 = 4; i2 > 0; i2--) {

      a = *((int16 *) (lnPtr + 2*xExt));  // left pixel

      // left extension, these pixels are indentical
      tmp = clip8Buf[a>>5];
      for (j = xExt-2; j > 0; j--)
      {
        // left boundary
        *lnPtr++ = (u_int8) tmp;
        *lnPtr++ = (u_int8) tmp;
      }

      // Horizontal filtering to generate odd locations

      // Interpolate 6 values per iteration. We'll use variable
      // a,b,c,d,e and f in rotating manner to avoid unnecessary mem loads.
      // rounding constant and clip table offset were added during vertical filtering
      b = c = d = e = a;
      for (j = (2 + picWidth - 3) - 6; j >= 0; j -= 6)
      {
        f = *((int16 *) (lnPtr + 6));
        *lnPtr++ = clip8Buf[c>>5];
        tmp = (a + 5*(-b + 4*(c + d) - e) + f) >> 10;
        *lnPtr++ = clip8Buf[tmp];

        a = *((int16 *) (lnPtr + 6));
        *lnPtr++ = clip8Buf[d>>5];
        tmp = (b + 5*(-c + 4*(d + e) - f) + a) >> 10;
        *lnPtr++ = clip8Buf[tmp];

        b = *((int16 *) (lnPtr + 6));
        *lnPtr++ = clip8Buf[e>>5];
        tmp = (c + 5*(-d + 4*(e + f) - a) + b) >> 10;
        *lnPtr++ = clip8Buf[tmp];

        c = *((int16 *) (lnPtr + 6));
        *lnPtr++ = clip8Buf[f>>5];
        tmp = (d + 5*(-e + 4*(f + a) - b) + c) >> 10;
        *lnPtr++ = clip8Buf[tmp];

        d = *((int16 *) (lnPtr + 6));
        *lnPtr++ = clip8Buf[a>>5];
        tmp = (e + 5*(-f + 4*(a + b) - c) + d) >> 10;
        *lnPtr++ = clip8Buf[tmp];

        e = *((int16 *) (lnPtr + 6));
        *lnPtr++ = clip8Buf[b>>5];
        tmp = (f + 5*(-a + 4*(b + c) - d) + e) >> 10;
        *lnPtr++ = clip8Buf[tmp];
      }

      // Interpolate remaining (2 + picWidth - 3)%6 values
      for (j = j + 6; j > 0; j--) {
        f = *((int16 *) (lnPtr + 6));
        *lnPtr++ = clip8Buf[c>>5];
        tmp = (a + 5*(-b + 4*(c + d) - e) + f) >> 10;
        *lnPtr++ = clip8Buf[tmp];
        a = b;
        b = c;
        c = d;
        d = e;
        e = f;
      }

      // Interpolate 4 last values that are interpolated
      // across the picture border
      f = e;
      for (j = 4; j > 0; j--) {
        *lnPtr++ = clip8Buf[c>>5];
        tmp = (a + 5*(-b + 4*(c + d) - e) + f) >> 10;
        *lnPtr++ = clip8Buf[tmp];
        a = b;
        b = c;
        c = d;
        d = e;
      }

      // right extension, these pixels are indentical
      tmp = clip8Buf[e>>5];
      for (j = xExt-1; j > 0; j--)
      {
        // right boundary
        *lnPtr++ = (u_int8) tmp;
        *lnPtr++ = (u_int8) tmp;
      }

      lnPtr += extBufWidth;
    }

  }
}
#else
void refFrmUpsampleLumaV(u_int8  *yBuf, int picWidth, int picHeight,
                         int xExt, int yExt)
{
  int extBufWidth;
  u_int8 *lnPtr, *tmpLnPtr;
  int i, j, i2;
  int32 a, b, c, d, e, f;
  int32 tmp;

  // yBuf has extended boundary
  extBufWidth  = 2*(picWidth + 2*xExt);

  // first line affected by vertical filtering
  lnPtr = yBuf + (2*yExt - 3) * extBufWidth;

  // interpolate 4 lines at a time
  for (i = picHeight + 4; i > 0; i -= 4)
  {
    tmpLnPtr = lnPtr + 2*xExt - 5*extBufWidth;

    for (j = picWidth; j > 0; j--) {
      a = *tmpLnPtr, tmpLnPtr += 2*extBufWidth;
      b = *tmpLnPtr, tmpLnPtr += 2*extBufWidth;
      c = *tmpLnPtr, tmpLnPtr += 2*extBufWidth;
      d = *tmpLnPtr, tmpLnPtr += 2*extBufWidth;
      e = *tmpLnPtr, tmpLnPtr += 2*extBufWidth;
      f = *tmpLnPtr, tmpLnPtr += 2*extBufWidth;

      *((int16 *)(tmpLnPtr-7*extBufWidth)) =
        (int16) (a + 5*(-b + 4*(c + d) - e) + f);

      a = *tmpLnPtr, tmpLnPtr += 2*extBufWidth;
      *((int16 *)(tmpLnPtr-7*extBufWidth)) =
        (int16) (b + 5*(-c + 4*(d + e) - f) + a);

      b = *tmpLnPtr, tmpLnPtr += 2*extBufWidth;
      *((int16 *)(tmpLnPtr-7*extBufWidth)) =
        (int16) (c + 5*(-d + 4*(e + f) - a) + b);

      c = *tmpLnPtr;
      *((int16 *)(tmpLnPtr-5*extBufWidth)) =
        (int16) (d + 5*(-e + 4*(f + a) - b) + c);

      tmpLnPtr += -16*extBufWidth + 2;
    }

    // horizontal filtering of 4 lines 
    for (i2 = 4; i2 > 0; i2--) {

      a = *((int16 *) (lnPtr + 2*xExt));  // left pixel

      // left extension, these pixels are indentical
      tmp = clip(0, 255, (a+16)>>5);
      for (j = xExt-2; j > 0; j--)
      {
        // left boundary
        *lnPtr++ = (u_int8) tmp;
        *lnPtr++ = (u_int8) tmp;
      }

      // Horizontal filtering to generate odd locations

      // Interpolate 6 values per iteration. We'll use variable
      // a,b,c,d,e and f in rotating manner to avoid unnecessary mem loads.
      // rounding constant and clip table offset were added during vertical filtering
      b = c = d = e = a;
      for (j = (2 + picWidth - 3) - 6; j >= 0; j -= 6)
      {
        f = *((int16 *) (lnPtr + 6));
        *lnPtr++ = (u_int8) clip(0, 255, (c+16)>>5);
        tmp = (a + 5*(-b + 4*(c + d) - e) + f + 512) >> 10;
        *lnPtr++ = (u_int8) clip(0, 255, tmp);

        a = *((int16 *) (lnPtr + 6));
        *lnPtr++ = (u_int8) clip(0, 255, (d+16)>>5);
        tmp = (b + 5*(-c + 4*(d + e) - f) + a + 512) >> 10;
        *lnPtr++ = (u_int8) clip(0, 255, tmp);

        b = *((int16 *) (lnPtr + 6));
        *lnPtr++ = (u_int8) clip(0, 255, (e+16)>>5);
        tmp = (c + 5*(-d + 4*(e + f) - a) + b + 512) >> 10;
        *lnPtr++ = (u_int8) clip(0, 255, tmp);

        c = *((int16 *) (lnPtr + 6));
        *lnPtr++ = (u_int8) clip(0, 255, (f+16)>>5);
        tmp = (d + 5*(-e + 4*(f + a) - b) + c + 512) >> 10;
        *lnPtr++ = (u_int8) clip(0, 255, tmp);

        d = *((int16 *) (lnPtr + 6));
        *lnPtr++ = (u_int8) clip(0, 255, (a+16)>>5);
        tmp = (e + 5*(-f + 4*(a + b) - c) + d + 512) >> 10;
        *lnPtr++ = (u_int8) clip(0, 255, tmp);

        e = *((int16 *) (lnPtr + 6));
        *lnPtr++ = (u_int8) clip(0, 255, (b+16)>>5);
        tmp = (f + 5*(-a + 4*(b + c) - d) + e + 512) >> 10;
        *lnPtr++ = (u_int8) clip(0, 255, tmp);
      }

      // Interpolate remaining (2 + picWidth - 3)%6 values
      for (j = j + 6; j > 0; j--) {
        f = *((int16 *) (lnPtr + 6));
        *lnPtr++ = (u_int8) clip(0, 255, (c+16)>>5);
        tmp = (a + 5*(-b + 4*(c + d) - e) + f + 512) >> 10;
        *lnPtr++ = (u_int8) clip(0, 255, tmp);
        a = b;
        b = c;
        c = d;
        d = e;
        e = f;
      }

      // Interpolate 4 last values that are interpolated
      // across the picture border
      f = e;
      for (j = 4; j > 0; j--) {
        *lnPtr++ = (u_int8) clip(0, 255, (c+16)>>5);
        tmp = (a + 5*(-b + 4*(c + d) - e) + f + 512) >> 10;
        *lnPtr++ = (u_int8) clip(0, 255, tmp);
        a = b;
        b = c;
        c = d;
        d = e;
      }

      // right extension, these pixels are indentical
      tmp = (u_int8) clip(0, 255, (e+16)>>5);
      for (j = xExt-1; j > 0; j--)
      {
        // right boundary
        *lnPtr++ = (u_int8) tmp;
        *lnPtr++ = (u_int8) tmp;
      }

      lnPtr += extBufWidth;
    }

  }
}
#endif


/*
 *
 * refFrmPartialSum8x8:
 *
 * Parameters:
 *      yBufIn               Luma pixels
 *      seaYBufIn            SEA buffer
 *      picWidth             Picture width in pixels
 *      picHeight            Picture height in pixels
 *      xExt                 Reference frame x-extension in pixels
 *      yExt                 Reference frame y-extension in pixels
 *
 * Function:
 *      Calculate 8x8 partial sum.
 *
 * Returns:
 *      -
 */
void refFrmPartialSum8x8(u_int8  *yBufIn, u_int16 *seaYBufIn,
                         int picWidth, int picHeight, int xExt, int yExt)
{
  u_int8 *yBuf;
  u_int16 *seaYBuf;
  int bufWidth;
  int i, j;
  u_int32 sum;
  u_int32 borderPixel;
  u_int32 tmp;

  bufWidth = picWidth + 2*xExt;

  yBuf = yBufIn;
  seaYBuf = seaYBufIn + yExt*bufWidth;

  // calculate partial sums horizontally
  for (i = 0; i < picHeight; i++)
  {
    borderPixel = *yBuf++;

    // left border pixels
    sum = borderPixel * 8;
    for (j = xExt-8+2; j > 0; j--)
      *seaYBuf++ = (u_int16) sum;

    // sum over picture border
    for (j = 8; j > 0; j--) {
      sum -= borderPixel;
      sum += *yBuf++;
      *seaYBuf++ = (u_int16) sum;
    }

    // middle picture
    for (j = picWidth-8+1-3; j > 0; j--) {
      sum -= yBuf[-8];
      sum += *yBuf++;
      *seaYBuf++ = (u_int16) sum;
    }

    borderPixel = *yBuf;
    yBuf -= 8;

    // sum over picture border
    for (j = 7; j > 0; j--) {
      sum -= *yBuf++;
      sum += borderPixel;
      *seaYBuf++ = (u_int16) sum;
    }

    // right border pixels
    sum = borderPixel * 8;
    for (j = xExt-8+2; j > 0; j--)
      *seaYBuf++ = (u_int16) sum;

    *seaYBuf++ = (u_int16) sum;

    yBuf += 2;
    seaYBuf += 6;
  }

  // sum up 1-D partial sums vertically to get 2-D partial sum
#if 0
  for (j = 0; j < bufWidth - 7; j ++)
  {
    seaYBuf = seaYBufIn + j;

    borderPixel = seaYBuf[yExt * bufWidth];

    // top border pixels only
    sum = borderPixel * 8;
    for (i = yExt-8+2; i > 0; i--, seaYBuf+=bufWidth)
      *seaYBuf = (u_int16) sum;

    // sum over picture border
    for (i = 6; i > 0; i--, seaYBuf+=bufWidth) {
      sum -= borderPixel;
      sum += seaYBuf[7*bufWidth];
      *seaYBuf = (u_int16) sum;
    }

    sum -= borderPixel;

    // middle picture
    for (i = picHeight-8+1-1; i > 0; i--, seaYBuf+=bufWidth) {
      sum += seaYBuf[7*bufWidth];
      tmp  = seaYBuf[0];
      seaYBuf[0] = (u_int16) sum;
      sum -= tmp;
    }

    borderPixel = seaYBuf[7*bufWidth];

    // sum over picture border
    for (i = 7; i > 0; i--, seaYBuf+=bufWidth) {
      sum += borderPixel;
      tmp  = seaYBuf[0];
      seaYBuf[0] = (u_int16) sum;
      sum -= tmp;
    }

    // bottom border pixels
    sum = borderPixel * 8;
    for (i = yExt-8+2; i > 0; i--, seaYBuf+=bufWidth)
      *seaYBuf = (u_int16) sum;
  }
#else
  // this is a SIMD version, i.e. it generates two 16 bits sums in one 32 bit variable
  for (j = 0; j < bufWidth - 6; j += 2)
  {
    seaYBuf = seaYBufIn + j;

    borderPixel = *((u_int32 *)(seaYBuf + yExt * bufWidth));

    // top border pixels only
    sum = borderPixel * 8;
    for (i = yExt-8+2; i > 0; i--, seaYBuf+=bufWidth)
      *((u_int32 *)seaYBuf) = sum;

    // sum over picture border
    for (i = 6; i > 0; i--, seaYBuf+=bufWidth) {
      sum -= borderPixel;
      sum += *((u_int32 *)(seaYBuf + 7*bufWidth));
      *((u_int32 *)seaYBuf) = sum;
    }

    sum -= borderPixel;

    // middle picture
    for (i = picHeight-8+1-1; i > 0; i--, seaYBuf+=bufWidth) {
      sum += *((u_int32 *)(seaYBuf + 7*bufWidth));
      tmp  = *((u_int32 *)seaYBuf);
      *((u_int32 *)seaYBuf) = sum;
      sum -= tmp;
    }

    borderPixel = *((u_int32 *)(seaYBuf + 7*bufWidth));

    // sum over picture border
    for (i = 7; i > 0; i--, seaYBuf+=bufWidth) {
      sum += borderPixel;
      tmp  = *((u_int32 *)seaYBuf);
      *((u_int32 *)seaYBuf) = sum;
      sum -= tmp;
    }

    // bottom border pixels
    sum = borderPixel * 8;
    for (i = yExt-8+2; i > 0; i--, seaYBuf+=bufWidth)
      *((u_int32 *)seaYBuf) = sum;
  }
#endif
} 


/*
 *
 * refFrmUpsampleLuma
 *
 * Parameters:
 *      pRefFrm         Reference frame object
 *      reco            y component of reconstructed frame
 *      low_complex_prof3   Low complexity profile 3
 *      useSearchWin    Use internal search window
 *      reconstFrm      Previous reconstructed frame, use by internal search window
 *
 * Function:
 *      Make a new luma reference frame buffer from luma reconstruction frame
 *      buffer by upsampling with factor of 2 horizontally and vertically.
 *
 * Returns:
 *      -
 */
void refFrmUpsampleLuma(refFrmBuf_s *pRefFrm, u_int8 *reco, int low_complex_prof3
#ifdef ENABLE_SEARCH_WINDOW
                        , int useSearchWin
#endif
                        )
{
  // constraints on boundary extension, could be enforced at the top level

  // the following functions do not if work extension smaller than 4 pixels
  assert((pRefFrm->xExt >= 4) && (pRefFrm->yExt >= 4));

  // make line buffer aligned at at leeat 4-byte boundary
  assert(((pRefFrm->xExt & 3) == 0) && ((pRefFrm->yExt & 3) == 0));



  // calculate partial sum for Successive Elimination Algorithm Implementation

  // take away partial
  if (!low_complex_prof3)
    refFrmPartialSum8x8(reco, pRefFrm->seaYBuf,
                      pRefFrm->picWidth, pRefFrm->picHeight,
                      pRefFrm->xExt, pRefFrm->yExt);


  // here upsample frame!!!  reco is prev output frame, pRefFrm->yBuf use later

#ifdef ENABLE_SEARCH_WINDOW
  if (!useSearchWin)
#endif
  {
  refFrmUpsampleLumaH(reco, pRefFrm->yBuf, pRefFrm->picWidth,
                      pRefFrm->picHeight, pRefFrm->xExt, pRefFrm->yExt);

  refFrmUpsampleLumaV(pRefFrm->yBuf, pRefFrm->picWidth, pRefFrm->picHeight,
                      pRefFrm->xExt, pRefFrm->yExt);
  }

//  DumpRefY(pRefFrm);
}


/*
 *
 * refFrmExtendChroma:
 *
 * Parameters:
 *      frame                 Frame object
 *      pRefFrm               Reference frame buffer
 *
 * Function:
 *      Make a new chroma reference frame buffer from chroma reconstruction
 *      frame buffer. Chroma reference frame buffers are not stored in
 *      upsampled form. Therefore, we can make reference frame just by copying
 *      pointers.
 *
 * Returns:
 *      -
 */
void refFrmExtendChroma(refFrmBuf_s *pRefFrm, u_int8 *recoU, u_int8 *recoV)
{
  int c, i, j;
  int xExt, yExt;                         // extension for chroma
  int picWidth, picHeight, extBufWidth;   // sizes for chroma
  u_int8 *srcLine, *dstLine;

  // boundary extension is performed
  picWidth    = pRefFrm->picWidth >> 1;
  picHeight   = pRefFrm->picHeight >> 1;
  extBufWidth = pRefFrm->cBufWidth;

  xExt = pRefFrm->xExt >> 1;
  yExt = pRefFrm->yExt >> 1;

  srcLine = recoU;
  dstLine = pRefFrm->uBuf + xExt;
  for (c = 0; c < 2; c ++)
  {
    for (i = -yExt; i < picHeight + yExt; i ++)
    {
      memcpy(dstLine, srcLine, picWidth);

      // horizontal extension
      for (j = 0; j < xExt; j ++)
      {
        dstLine[-1 - j]       = srcLine[0];
        dstLine[picWidth + j] = srcLine[picWidth - 1];
      }

      // so the first line is extended up and the last line is extended down
      if ((i >= 0) && (i < picHeight - 1))
        srcLine += picWidth;

      dstLine += extBufWidth;
    }

    // process v
    srcLine = recoV;
    dstLine = pRefFrm->vBuf + xExt;
  }
}
void refFrmStoreChannelDistortion(refFrmBuf_s *pRefFrm, int32 *channelDistortion)
{
  int numMbs;

  numMbs = pRefFrm->picWidth/MBK_SIZE * pRefFrm->picHeight/MBK_SIZE;
  if (pRefFrm->channelDistortion && channelDistortion) {
    memcpy(pRefFrm->channelDistortion, channelDistortion, numMbs*sizeof(int));
  }
}
