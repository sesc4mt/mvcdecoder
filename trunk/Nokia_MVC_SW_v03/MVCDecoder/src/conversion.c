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
 * conversion.c
 *
 * Contains:
 *    Functions for YUV to RGB conversion and interleaving
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "framebuffer.h"
#include "conversion.h"
#include "sequence.h"

#define clipTo255(a) (a<0?0:a>255?255:a)


static const int redInterlacing[15]={0,255,0,255,255,0,255,255,0,255,0,0,255,0,0};
static const int greenInterlacing[15]={0,255,255,0,255,0,0,255,0,0,255,0,255,255,0};
static const int blueInterlacing[15]={0,0,255,0,0,255,0,255,255,0,255,255,0,255,0};


void StoreYUV(frmBuf_s *recoBuf, dispBuf_s *displayBuf)
{
	u_int8 *yBuf, *uBuf, *vBuf;
	u_int8 *storeYBuf, *storeUBuf, *storeVBuf;
	int width, height;
	int numPels;
	int uvSize;


	yBuf = recoBuf->y;
	uBuf = recoBuf->u;
	vBuf = recoBuf->v;

  storeYBuf = displayBuf->y;
	storeUBuf = displayBuf->u;
	storeVBuf = displayBuf->v;

	width = recoBuf->width;
	height = recoBuf->height;
	numPels = width * height;
	uvSize = numPels >>2;

  memcpy(storeYBuf, yBuf, numPels);
  memcpy(storeUBuf, uBuf, uvSize);
  memcpy(storeVBuf, vBuf, uvSize);
}


#ifdef AVC_ARM_ASSEMBLY

/* Assembly version */
void interleaveParallax_asm(u_int8 *ylBuf, u_int8 *yrBuf, u_int8 *ulBuf, u_int8 *urBuf, 
			    u_int8 *vlBuf, u_int8 *vrBuf,
                            u_int16 *rowEven, u_int16 *rowOdd,
                            int width, int height);

void interleaveParallax(sequence_s *seq, unsigned char *outputRGB, frmBuf_s *recoBuf)
{
    interleaveParallax_asm(recoBuf->y, seq->displayBuffer->y, recoBuf->u, seq->displayBuffer->u, recoBuf->v, seq->displayBuffer->v,(u_int16 *) outputRGB, (u_int16 *)  &outputRGB[4*seq->displayBuffer->width],seq->displayBuffer->width, seq->displayBuffer->height);
}

#else

/* Non-assembly version */
void interleaveParallax(sequence_s *seq, unsigned char *outputRGB, frmBuf_s *recoBuf)
{
	u_int16 *rowEven,*rowOdd, *rowEven2;
	int i,j;
	u_int8 *yrBuf, *ylBuf, *urBuf, *ulBuf, *vrBuf, *vlBuf;
	int width, height;
	int uvRowIndex;
	int ul, ur, vl, vr, yl, yr;
	int rl,rr, gl, gr, bl, br;
	int red, green, blue;
	int yl2,yr2;


	/* Left eye view Y, u and v */
	yrBuf = seq->displayBuffer->y;
	urBuf = seq->displayBuffer->u;
	vrBuf = seq->displayBuffer->v;

	/* Right eye view Y, u and v */
	ylBuf = recoBuf->y;
	ulBuf = recoBuf->u;
	vlBuf = recoBuf->v;

	width = seq->displayBuffer->width;
	height = seq->displayBuffer->height;

  uvRowIndex=0;
  
  rowEven = (u_int16 *) &(outputRGB[0]);
  rowOdd = (u_int16 *) &(outputRGB[width*4]);
  rowEven2 = (u_int16 *) &(outputRGB[width*8]);
  
  for(i=0; i<height; i+=2)
  {
    
    for(j=0; j<width; j+=2)
    {
      ul = ulBuf[uvRowIndex]; 
      ur = urBuf[uvRowIndex]; 
      vl = vlBuf[uvRowIndex]; 
      vr = vrBuf[uvRowIndex++]; 
      
      rl = 357*vl-45568;
      rr = 357*vr-45568;
      gr = 34688-88*ur-182*vr;
      gl = 34688-88*ul-182*vl;
      bl = 452*ul-57728;
      br = 452*ur-57728;
      
      yr2 = (yrBuf[width])<<8;
      yl2 = (ylBuf[width])<<8;
      yr = (*yrBuf++)<<8;
      yl = (*ylBuf++)<<8;
      
      red = yl+rl; if(red<0)red=0;if(red>65280)red=65280;
      green = yr+gr; if(green<0)green=0;if(green>65280)green=65280;
      blue = yl+bl; if(blue<0)blue=0;if(blue>65280)blue=65280;
      (*rowEven++) = (unsigned short) ((blue>>11) | ((green & 0xfc00) >> 5) | ((red & 0xf800)));
      
      red = yl2+rl; if(red<0)red=0;if(red>65280)red=65280;
      green = yr2+gr; if(green<0)green=0;if(green>65280)green=65280;
      blue = yl2+bl; if(blue<0)blue=0;if(blue>65280)blue=65280;
      (*rowEven2++) = (unsigned short) ((blue>>11) | ((green & 0xfc00) >> 5) | ((red & 0xf800)));
      
      red = yr+rr; if(red<0)red=0;if(red>65280)red=65280;
      green = yl+gl; if(green<0)green=0;if(green>65280)green=65280;
      blue = yr+br; if(blue<0)blue=0;if(blue>65280)blue=65280;
      (*rowEven++) = (unsigned short) ((blue>>11) | ((green & 0xfc00) >> 5) | ((red & 0xf800)));
      
      red = yr2+rr; if(red<0)red=0;if(red>65280)red=65280;
      green = yl2+gl; if(green<0)green=0;if(green>65280)green=65280;
      blue = yr2+br; if(blue<0)blue=0;if(blue>65280)blue=65280;
      (*rowEven2++) = (unsigned short) ((blue>>11) | ((green & 0xfc00) >> 5) | ((red & 0xf800)));
      
      yr2 = (yrBuf[width])<<8;
      yl2 = (ylBuf[width])<<8;
      yr = (*yrBuf++)<<8;
      yl = (*ylBuf++)<<8;
      
      red = yl+rl; if(red<0)red=0;if(red>65280)red=65280;
      green = yr+gr; if(green<0)green=0;if(green>65280)green=65280;
      blue = yl+bl; if(blue<0)blue=0;if(blue>65280)blue=65280;
      (*rowEven++) = (unsigned short) ((blue>>11) | ((green & 0xfc00) >> 5) | ((red & 0xf800)));
      
      red = yl2+rl; if(red<0)red=0;if(red>65280)red=65280;
      green = yr2+gr; if(green<0)green=0;if(green>65280)green=65280;
      blue = yl2+bl; if(blue<0)blue=0;if(blue>65280)blue=65280;
      (*rowEven2++) = (unsigned short) ((blue>>11) | ((green & 0xfc00) >> 5) | ((red & 0xf800)));
      
      red = yr+rr; if(red<0)red=0;if(red>65280)red=65280;
      green = yl+gl; if(green<0)green=0;if(green>65280)green=65280;
      blue = yr+br; if(blue<0)blue=0;if(blue>65280)blue=65280;
      (*rowEven++) = (unsigned short) ((blue>>11) | ((green & 0xfc00) >> 5) | ((red & 0xf800)));
      
      red = yr2+rr; if(red<0)red=0;if(red>65280)red=65280;
      green = yl2+gl; if(green<0)green=0;if(green>65280)green=65280;
      blue = yr2+br; if(blue<0)blue=0;if(blue>65280)blue=65280;
      (*rowEven2++) = (unsigned short) ((blue>>11) | ((green & 0xfc00) >> 5) | ((red & 0xf800)));
    }
    
    /* Copy even row to odd row */
    memcpy(rowOdd, (rowEven-width*2), width*4);
    memcpy((rowOdd+width*2*2), (rowEven2-width*2), width*4);
    rowEven += width*2*3;
    rowOdd += width*8;
    rowEven2 += width*2*3;
    
    ylBuf+=width;
    yrBuf+=width;
  }
}

#endif


void interleaveParallaxSingleXv(sequence_s *seq, unsigned char *outputRGB, frmBuf_s *recoBuf)
{
	int index;
	int numPels;
	u_int16 *rowEven,*rowOdd;
	int i,j;
	int uvWidth, uvHeight;
	u_int8 *yrBuf, *ylBuf, *urBuf, *ulBuf, *vrBuf, *vlBuf;
	int width, height;
	int uvRowIndex;
	int uvSize;
	int ul, ur, vl, vr, yl, yr;
	int rl,rr, gl, gr, bl, br;
	int indexEven, indexOdd;
  int red, green, blue;
  
  /* Right eye view Y, u and v */
  yrBuf = seq->displayBuffer->y;
  urBuf = seq->displayBuffer->u;
  vrBuf = seq->displayBuffer->v;
  
  /* Left eye view Y, u and v */
  ylBuf = recoBuf->y;
  ulBuf = recoBuf->u;
  vlBuf = recoBuf->v;
  
  width = seq->displayBuffer->width;
  height = seq->displayBuffer->height;
  numPels = width * height;
  uvSize = numPels >>2;
  
  numPels = seq->displayBuffer->width * seq->displayBuffer->height;
  
  uvWidth = width >> 1;
  uvHeight = height >> 1;
  
  index=0;
  indexOdd=indexEven=0;
  
  rowEven = (u_int16 *) &(outputRGB[0]);
  rowOdd = (u_int16 *) &(outputRGB[width*4]);
  
  for(i=0; i<height; i++)
  {
    uvRowIndex = (i >> 1)*uvWidth;
    
    for(j=0; j<width; j+=2)
    {
      ul = ulBuf[uvRowIndex]; 
      ur = urBuf[uvRowIndex]; 
      vl = vlBuf[uvRowIndex]; 
      vr = vrBuf[uvRowIndex++]; 
      
      rl = 357*vl-45568;
      rr = 357*vr-45568;
      gr = 34688-88*ur-182*vr;
      gl = 34688-88*ul-182*vl;
      bl = 452*ul-57728;
      br = 452*ur-57728;
      
      yr = (*yrBuf++)<<8;
      yl = (*ylBuf++)<<8;
      
      red = yl+rl; if(red<0)red=0;if(red>65280)red=65280;
      green = yr+gr; if(green<0)green=0;if(green>65280)green=65280;
      blue = yl+bl; if(blue<0)blue=0;if(blue>65280)blue=65280;
      (*rowEven++) = (unsigned short) ((blue>>11) | ((green & 0xfc00) >> 5) | ((red & 0xf800)));
      
      yr = (*yrBuf++)<<8;
      yl = (*ylBuf++)<<8;
      
      red = yr+rr; if(red<0)red=0;if(red>65280)red=65280;
      green = yl+gl; if(green<0)green=0;if(green>65280)green=65280;
      blue = yr+br; if(blue<0)blue=0;if(blue>65280)blue=65280;
      (*rowEven++) = (unsigned short)((blue>>11) | ((green & 0xfc00) >> 5) | ((red & 0xf800)));
      
    }
  }
}


