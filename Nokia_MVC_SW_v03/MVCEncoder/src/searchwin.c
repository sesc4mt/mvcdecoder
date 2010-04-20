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
 * searchwin.c
 *
 * Contains:
 *    Functions for using internal search window
 *
 */

#ifdef ENABLE_SEARCH_WINDOW

#include <string.h>
#include "nccglob.h"
#include "globals.h"
#include "searchwin.h"


static const int coef6tap[6] = {1, -5, 20, 20, -5, 1};


/*
 * searchWinInit:
 *
 * Parameters:
 *      pSWin               Pointers to internal search window structure
 *      picWidth            Picture width
 *      picHeight           Picture height
 *      srx                 Hori. MV restriction e.g. srx=16, MVX: -14.00 to +14.00
 *      sry                 Vert. MV restriction
 *
 * Function:
 *      Initialize the data structure for using internal search window
 *
 * Returns:
 *      -
 */
void searchWinInit(searchWin_s *pSWin, int picWidth, int picHeight, int srx, int sry)
{
  pSWin->useSearchWin = 1;

  pSWin->srx = srx;
  pSWin->sry = sry;

  pSWin->searchWinWidth = (MBK_SIZE + 2 * pSWin->srx) * 2;    // in byte, upsampled
  pSWin->searchWinHeight = (MBK_SIZE + 2 * pSWin->sry) * 2;

  pSWin->searchWindow =
    (u_int8 *) nccMalloc((pSWin->searchWinHeight * pSWin->searchWinWidth + (picWidth - MBK_SIZE) * 2) * sizeof(u_int8));
  
  if (pSWin->searchWindow == NULL) {
    nccExit(1);
  }

  pSWin->auxBuf =
    (int16 *) nccMalloc( pSWin->searchWinWidth/2 * sizeof(int16) );

  if (pSWin->auxBuf == NULL) {
    nccExit(1);
  }

  pSWin->picWidth = picWidth;
  pSWin->picHeight = picHeight;

  return;
}


/*
 * searchWinFinish:
 *
 * Parameters:
 *      pSWin               Pointers to internal search window structure
 *
 * Function:
 *      Clean up the data structure for using internal search window
 *
 * Returns:
 *      -
 */
void searchWinFinish(searchWin_s *pSWin)
{
  nccFree(pSWin->searchWindow);
  nccFree(pSWin->auxBuf);
}


/*
 * loadSearchWindow:
 *
 * Parameters:
 *      pSWin               Pointers to internal search window structure
 *
 * Function:
 *      Load the pixel data from reconstructed frame buffer to internal search window. 
 *
 * Returns:
 *      -
 */
void loadSearchWindow(searchWin_s *pSWin)
{
  int i, j;
  u_int8 *dst;
  u_int8 *src;
  int startX, stopX;
  int startY, stopY;
  u_int8 c;

  /* Pointer to Up-left corner of the current search window */
  dst = pSWin->searchWindow + (2 * pSWin->locX);

  /* Horizontal start position of loaded area */
  if (pSWin->locX == 0)
    startX = 0;
  else
    startX = pSWin->srx;

  /* Horizontal end position of loaded area */
  stopX = MBK_SIZE + pSWin->srx;
  if (pSWin->locX + stopX > pSWin->picWidth)
    stopX = pSWin->picWidth - pSWin->locX;

  /* Vertical start position of loaded area */
  if (pSWin->locY < pSWin->sry)
    startY = -pSWin->locY;
  else
    startY = -pSWin->sry;

  /* Vertical end position of loaded area */
  stopY = MBK_SIZE + pSWin->sry;
  if (pSWin->locY + stopY > pSWin->picHeight)
    stopY = pSWin->picHeight - pSWin->locY;

  /* Pointer to beginning of loaded area */
  dst += 2 * (startX + pSWin->srx);
  dst += 2 * (startY + pSWin->sry) * pSWin->searchWinWidth;

  /*
   * Copy pixels
   */

  for (i = startY; i < stopY; i++) {
    for (j = startX; j < stopX; j++) {
      *dst = pSWin->refFrm[(pSWin->locY + i) * pSWin->picWidth + (pSWin->locX + j)];
      dst += 2;
    }
    dst -= 2 * (stopX - startX);
    dst += 2 * pSWin->searchWinWidth;

  }

  /*
   * Extend to the left
   */

  if (pSWin->locX == 0) {

    dst = pSWin->searchWindow + 2 * (pSWin->sry + startY) * pSWin->searchWinWidth;

    for (i = startY; i < stopY; i++) {
      
      c = dst[2 * pSWin->srx];

      for (j = 0; j < pSWin->srx; j++) {
        *dst = c;
        dst += 2;
      }
      dst -= 2 * pSWin->srx;
      dst += 2 * pSWin->searchWinWidth;
      
    }

  }

  /*
   * Extend to the right
   */

  if (pSWin->locX + MBK_SIZE + pSWin->srx > pSWin->picWidth) {

    dst  = pSWin->searchWindow + 2 * (pSWin->sry + startY) * pSWin->searchWinWidth;
    dst += 2 * (pSWin->srx + pSWin->picWidth);

    for (i = startY; i < stopY; i++) {
      
      c = dst[-2];

      for (j = 0; j < pSWin->srx; j++) {
        *dst = c;
        dst += 2;
      }
      dst -= 2 * pSWin->srx;
      dst += 2 * pSWin->searchWinWidth;
      
    }

  }


  /* Adjust startX and stopX for vertical extension */

  if (pSWin->locX == 0)
    startX = -pSWin->srx;
  else
    startX = pSWin->srx;

  stopX = MBK_SIZE + pSWin->srx;


  /*
   * Top extension
   */

  if (pSWin->locY - pSWin->sry < 0) {
    dst = pSWin->searchWindow + 2 * (pSWin->srx + pSWin->locX + startX);
    src = dst + 2 * (pSWin->sry - pSWin->locY) * pSWin->searchWinWidth;

    for (i = (pSWin->locY - pSWin->sry); i < 0; i++) {

      for (j = startX; j < stopX; j++) {
        *dst = *src;
        src += 2;
        dst += 2;
      }
      src -= 2 * (stopX - startX);
      dst -= 2 * (stopX - startX);
      dst += 2 * pSWin->searchWinWidth;
      
    }
  }

  /*
   * Bottom extension
   */

  if (pSWin->locY + MBK_SIZE + pSWin->sry > pSWin->picHeight) {

    dst = pSWin->searchWindow + 2 * (pSWin->srx + pSWin->locX + startX);
    dst += 2 * (pSWin->sry + stopY) * pSWin->searchWinWidth;
    src = dst - 2 * pSWin->searchWinWidth;

    for (i = stopY; i < (MBK_SIZE + pSWin->sry); i++) {

      for (j = startX; j < stopX; j++) {
        *dst = *src;
        src += 2;
        dst += 2;
      }
      src -= 2 * (stopX - startX);
      dst -= 2 * (stopX - startX);
      dst += 2 * pSWin->searchWinWidth;
      
    }
  }

}


/*
 * refFrmUpsampleLumaH_SearchWin:
 *
 * Parameters:
 *      pSWin               Pointers to internal search window structure
 *
 * Function:
 *      Interpolate half pel horizontally.  This is modified from refFrmUpsampleLumaH.
 *
 * Returns:
 *      -
 */
void refFrmUpsampleLumaH_SearchWin(searchWin_s *pSWin)
{
  int i, j, k;
  int tmp;
  int width;
  int height;
  u_int8 *ptr, *searchWinPtr;

  /* Pointer to current search window data */
  searchWinPtr = pSWin->searchWindow + (2 * pSWin->locX);

  if (pSWin->locX > 0) {
    width = 2 + 3 + MBK_SIZE;
    ptr = searchWinPtr + pSWin->searchWinWidth - (width * 2);
  }
  else {
    width = MBK_SIZE + (2 * pSWin->srx);
    ptr = searchWinPtr;
  }

  height = MBK_SIZE + (2 * pSWin->sry);

  for (i = 0; i < height; i++) {
    for (j = 2; j < width-3; j++) {

      tmp = 0;
      for (k = 0; k < 6; k++)
        tmp += coef6tap[k] * (int)ptr[2*i*pSWin->searchWinWidth + 2*(j-2+k)];

      tmp = clip(0, 32*255, tmp);
      ptr[2*i*pSWin->searchWinWidth + 2*j + 1] = (u_int8) ((tmp + 16) >> 5);
    }
  }
}


/*
 * refFrmUpsampleLumaV_SearchWin:
 *
 * Parameters:
 *      pSWin               Pointers to internal search window structure
 *
 * Function:
 *      Interpolate half pel vertically.  This is modified from refFrmUpsampleLumaV.
 *
 * Returns:
 *      -
 */
void refFrmUpsampleLumaV_SearchWin(searchWin_s *pSWin)
{
  int i, j, k;
  int32 tmp;
  int16 *auxBuf = pSWin->auxBuf;
  u_int8 *ptr = pSWin->searchWindow + (2 * pSWin->locX);
  int width = MBK_SIZE + (2 * pSWin->srx);
  int height = MBK_SIZE + (2 * pSWin->sry);

  if (pSWin->locX > 0) {
    width = 2 + 3 + MBK_SIZE;
    ptr += pSWin->searchWinWidth - (width * 2);
  }

  for (i = 2; i < height-3; i++) {

    for (j = 0; j < width; j++) {

      tmp = 0;
      for (k = 0; k < 6; k++)
        tmp += coef6tap[k] * (int)ptr[2*(i-2+k)*pSWin->searchWinWidth + 2*j];

      auxBuf[j] = (int16) tmp;

      tmp = clip(0, 255*32, tmp);
      ptr[(2*i+1)*pSWin->searchWinWidth + 2*j] = (u_int8) ((tmp + 16) >> 5);
    }

    for (j = 2; j < width-3; j++) {

      tmp = 0;
      for (k = 0; k < 6; k++)
        tmp += (int32)coef6tap[k] * auxBuf[j-2+k];

      tmp = clip(0, (int32)255*1024, tmp);
      ptr[(2*i+1)*pSWin->searchWinWidth + 2*j+1] = (u_int8) ((tmp + 512) >> 10);
    }
  }

}


int PrecomputeRefPointers_SearchWin(macroblock_s *pMb,
                                    int          nRefFrames,   
                                    u_int8       *refBlkPtrs[][16])
{
  int i, j;
  int refWidth;
  u_int8 **refBlkPtrsPtr;
  
  refWidth = pMb->pSWin->searchWinWidth;
  
  for (i = 0; i < nRefFrames; i ++)
  {
    u_int8 *refMbPtr;

    refMbPtr = pMb->pSWin->searchWindow +
      pMb->pSWin->sry * 2 * refWidth + (pMb->pSWin->srx + pMb->pSWin->locX) * 2;

    refBlkPtrsPtr = refBlkPtrs[i];

    for (j = 0; j < BLK_PER_MB; j++)
    {
      *refBlkPtrsPtr++ = refMbPtr + (0 * 2 * BLK_SIZE);
      *refBlkPtrsPtr++ = refMbPtr + (1 * 2 * BLK_SIZE);
      *refBlkPtrsPtr++ = refMbPtr + (2 * 2 * BLK_SIZE);
      *refBlkPtrsPtr++ = refMbPtr + (3 * 2 * BLK_SIZE);
      refMbPtr += (2 * BLK_SIZE) * refWidth;
    }
  }
  
  return refWidth;
}

#endif
