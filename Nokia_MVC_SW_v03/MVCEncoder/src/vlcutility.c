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
 * vlcutility.c
 *
 * Contains:
 *    Low-level variable length coding functions.
 *
 */

#include "vlcutility.h"

/*
 * Table for number of bits for the smallest codes
 */
const int8 uvlcBitsUnsigned[] = {
   1, 3, 3, 5, 5, 5, 5, 7,
   7, 7, 7, 7, 7, 7, 7, 9,
   9, 9, 9, 9, 9, 9, 9, 9,
   9, 9, 9, 9, 9, 9, 9, 11,
   11,11,11,11,11,11,11,11,
   11,11,11,11,11,11,11,11,
   11,11,11,11,11,11,11,11,
   11,11,11,11,11,11,11,13,
};


/*
 * Number of bits for motion vectors. Range goes from -511 to 511
 */
const int8 uvlcBitsSigned[511 + 1 + 511] = {
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
  15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
  15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
  15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
  13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
  13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
  11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,
   9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 5, 5, 3,
   1,
   3, 5, 5, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9,
  11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,
  13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
  13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
  15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
  15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
  15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
  15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
  19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19
};


const int8 numOfRefPar[7] = {
  1, 2, 2, 4, 4, 4, 4
};


/*
 * vlcuZigZagScan4x4
 *
 * Parameters:
 *      src                   Source block
 *      dst                   Zig zag scanned values
 *
 * Function:
 *      Perform zig zag scanning for a block of values.
 *      
 * Returns:
 *      -
 *
 */
void vlcuZigZagScan4x4(int src[BLK_SIZE][BLK_SIZE], int *dst)
{
  dst[0] =src[0][0], dst[1] =src[0][1], dst[2] =src[1][0], dst[3] =src[2][0];
  dst[4] =src[1][1], dst[5] =src[0][2], dst[6] =src[0][3], dst[7] =src[1][2];
  dst[8] =src[2][1], dst[9] =src[3][0], dst[10]=src[3][1], dst[11]=src[2][2];
  dst[12]=src[1][3], dst[13]=src[2][3], dst[14]=src[3][2], dst[15]=src[3][3];
}


/*
 * vlcuUVLCSize:
 *
 * Parameters:
 *      codeNum               Code number to be sent
 *
 * Function:
 *      Calculate the length of the Unified VLC representation of an integer.
 *
 * Returns:
 *      Length of the codeword.
 */
int vlcuUVLCSize(unsigned int codeNum)
{
  int tmp;
  int len;
  int i;


  tmp = (codeNum + 1) >> 1;

  /* Find len/2 = i */
  for (i = 0; tmp != 0 && i < 16; i++)
    tmp >>= 1;

  /* Compute length. Length is always odd number */
  len  = 2*i + 1;

  return len;
}


/*
 * vlcuSendUVLC:
 *
 * Parameters:
 *      bitbuf                Bitbuffer to be used
 *      codeNum               Code number to be sent
 *
 * Function:
 *      Sends Unified VLC.
 *      Code number is first converted to info and length. Info is the info part
 *      of the codeword and length is the length of the final codeword
 *      (not info part). Relationship between code number, info and length is
 *
 *        codeNum = 2^(len/2) + info - 1
 *
 * Returns:
 *      Length of the codeword.
 */
int vlcuSendUVLC(bitbuffer_s *bitbuf, unsigned int codeNum)
{
  int tmp;
  int info;
  int len;
  int i;


  tmp = (codeNum+1)>>1;

  /* Find len/2 = i */
  for (i = 0; tmp != 0 && i < 16; i++)
    tmp >>= 1;

  /* Compute length. Length is always odd number */
  len  = 2*i + 1;

  /* info = codeNum + 1 - 2^(len/2) */
  info = codeNum + 1 - (1<<i);

  bibPutBits(bitbuf, info | (1 << (len >> 1)), len);

  return len;
}


/*
 * vlcuSendFLC:
 *
 * Parameters:
 *      bitbuf                Bitbuffer to be used
 *      code                  Code to send
 *      len                   Number of bits to send
 *
 * Function:
 *      Send Fixed LEngth Code.
 *
 * Returns:
 *      Length of the codeword that was sent.
 *
 */
int vlcuSendFLC(bitbuffer_s *bitbuf, u_int32 codeNum, int len)
{
  return bibPutBits(bitbuf, codeNum, len);
}


/*
 * vlcuSendNalUnitStartCodePrefix:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      zero_byte             indicate there will be zero byte before the 
 *                            start_code_prefix_one_3bytes
 *
 * Function:
 *      Write the start code in a byte stream NAL unit
 *
 * Returns:
 *      Number of bits being written
 */
int vlcuSendNalUnitStartCodePrefix(bitbuffer_s *bitbuf, int zeroByte)
{
  int bits = 0;


  // write 1 zero byte if requested
  if (zeroByte != 0)
  {
    bibPutByte( bitbuf, 0 );
    bits += 8;
  }

  // write the start_code_prefix_one_3bytes 0x00 0x00 0x01
  bibPutByte( bitbuf, 0 );
  bibPutByte( bitbuf, 0 );
  bibPutByte( bitbuf, 1 );
  bits += 24;

  return bits;
}


/*
 * vlcuSendNalHead:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      nal_ref_idc           nal_ref_idc
 *      nal_type              Nal type
 *
 * Function:
 *      Write the start code in a byte stream NAL unit
 *
 * Returns:
 *      Number of bits being written
 */
int vlcuSendNalHead(bitbuffer_s *bitbuf, int nal_ref_idc, int nal_type)
{
  int nalHeaderByte = 0;
  int bits = 8;


  nalHeaderByte |= 0 << 7;              // forbidden bit (1 bit)
  nalHeaderByte |= nal_ref_idc << 5;    // nal_ref_idc   (2 bits)
  nalHeaderByte |= nal_type;            // nal_ref_idc   (5 bits)

  bibPutByte(bitbuf, nalHeaderByte);

  return bits;
}


/*
 * vlcuSendEndOfSeq
 *
 * Parameters:
 *      bitbuf                Bitbuffer to be used
 *
 * Function:
 *      Send End Of Sequence codeword.
 *
 * Returns:
 *      Number of bits sent.
 */
int vlcuSendEndOfSeq(bitbuffer_s *bitbuf)
{
  return (bibByteAlign(bitbuf));
}


/*
 * vlcuGetLuma8x8cbp
 *
 * Parameters:
 *      cbpY                  Coded Block Pattern for 16 4x4 blocks.
 *                            Order of the 4x4 cbp bits:
 *                              0  1  4  5
 *                              2  3  6  7
 *                              8  9 12 13
 *                             10 11 14 15
 *
 * Function:
 *      Create Coded Block Pattern for 8x8 blocks. Each 8x8 block consists of
 *      four neighboring 4x4 blocks.
 *
 * Returns:
 *      Coded Block Pattern for 8x8 blocks.
 */
int vlcuGetLuma8x8cbp(unsigned int cbpY)
{
  int cbp;

  cbp  = (cbpY & 0x000F) == 0 ? 0 : (1<<0);
  cbp |= (cbpY & 0x00F0) == 0 ? 0 : (1<<1);
  cbp |= (cbpY & 0x0F00) == 0 ? 0 : (1<<2);
  cbp |= (cbpY & 0xF000) == 0 ? 0 : (1<<3);

  return cbp;
}


/*
 * vlcuSendCoefLevelVLC0:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      coef                  Coefficient
 *
 * Function:
 *      Send CAVLC coefficient level using VLC0 code format
 *
 * Returns:
 *      Number of bits send
 */
int vlcuSendCoefLevelVLC0(bitbuffer_s *bitbuf, int coef)
{
  int len;
  int bits;
  int absLev;


  absLev = abs(coef);

  if (absLev <= 7) {
    bits = 1;
    len = 2*absLev - (coef > 0 ? 1 : 0);
  }
  else if (absLev <= 15) {
    bits = 16 | ((absLev-8)<<1) | (coef < 0 ? 1 : 0);
    len = 19;
  }
  else {
    bits = (1<<12) | ((absLev-16)<<1) | (coef < 0 ? 1 : 0);
    len = 28;
  }

  bibPutBits(bitbuf, bits, len);
  return len;
}


/*
 * vlcuSendCoefLevelVLCN:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      tabNum                VLC table number to be used
 *      coef                  Coefficient
 *
 * Function:
 *      Send CAVLC coefficient level using VLC1-6 code format
 *
 * Returns:
 *      Number of bits sent
 */
int vlcuSendCoefLevelVLCN(bitbuffer_s *bitbuf, int tabNum, int coef)
{
  int len;
  int bits;
  int absLev;


  absLev = abs(coef);

  if (absLev <= (15<<(tabNum-1))) {
    bits = (1<<tabNum) |
           (((absLev-1) & ((1<<(tabNum-1))-1))<<1) |
           (coef < 0 ? 1 : 0);
    len = ((absLev-1) >> (tabNum-1)) + 1 + tabNum;
  }
  else {
    bits = (1<<12) + ((absLev-(15<<(tabNum-1))-1)<<1) + (coef < 0 ? 1 : 0);
    len = 28;
  }

  bibPutBits(bitbuf, bits, len);
  return len;
}


/*
 * vlcuSendNalHeadMVC:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      nal_ref_idc           nal_ref_idc
 *      nal_type              Nal type
 *      view_id               View id of the current view
 *
 * Function:
 *      Write the start code in a byte stream NAL unit
 *
 * Returns:
 *      Number of bits being written
 */
int vlcuSendNalHeadMVC(bitbuffer_s *bitbuf, int nal_ref_idc, int nal_type, int idr_flag, int view_id)
{
  int nalHeaderByte = 0;
  int bits = 8;
  int priority_id = 1;
  int temporal_id = 0;
  int anchor_flag;
  int inter_view_flag;	


  nalHeaderByte |= 0 << 7;              // forbidden bit (1 bit)
  nalHeaderByte |= nal_ref_idc << 5;    // nal_ref_idc   (2 bits)
  nalHeaderByte |= nal_type;            // nal_ref_idc   (5 bits)

  bibPutByte(bitbuf, nalHeaderByte);

  if( idr_flag == 1 )
    anchor_flag = 1;
  else
    anchor_flag = 0;

  inter_view_flag = 1;

  /* For now, only the base view is used for inter view prediction */
  if(view_id > 0)
	  inter_view_flag = 0;
  else
    inter_view_flag = 1;  /* Base view */	

  if( nal_type == PREFIX_NAL_TYPE || nal_type == NON_BASE_VIEW_SLICE )
  {
    bits += vlcuSendNalHeadMVCExtension(bitbuf, idr_flag, priority_id, view_id, temporal_id, anchor_flag, inter_view_flag);
  }

  /* Put trailing bits if this is a prefix NAL, otherwise not (NAL type == 20, slice header comes after this) */
  if( nal_type == PREFIX_NAL_TYPE )
    bits += bibTrailingBits(bitbuf);

  return bits;
}


/*
 * vlcuSendNalHeadMVCExtension:
 *
 * Parameters:
 *      bitbuf					Bitbuffer object
 *      temporalLevel           Temporal level
 *      viewLevel				View level
 *		  anchorPicFlag			Anchor picture flag
 *		  viewId					View Id
 *		  idrFlag					IDR flag
 *
 * Function:
 *      Write the MVC NAL header extension to the bitbuffer
 *
 * Returns:
 *      Number of bits being written
 */
int vlcuSendNalHeadMVCExtension(bitbuffer_s *bitbuf, int idrFlag, int priorityId, int viewId, 
								                int temporalId, int anchorPicFlag, int interViewFlag)
{
  int nalHeaderByte = 0;

  /* Start with the zero bit */
  nalHeaderByte = 0;						// First bit a zero bit
  nalHeaderByte |= ((!idrFlag) << 6);			// non IDR flag (1 bit)
  nalHeaderByte |= (priorityId & 0x3f);	  // Priority Id (6 bits)
  bibPutByte(bitbuf, nalHeaderByte);

  nalHeaderByte = 0;
  nalHeaderByte |= (viewId >> 2) & 0xFF;	// view Id (8 (highest) bits)
  bibPutByte(bitbuf, nalHeaderByte);

  nalHeaderByte = 0;
  nalHeaderByte |= (viewId & 0x03) << 6;	// view Id (2 (lowest) bits)

  nalHeaderByte |= temporalId << 4;			// temporal Id   (3 bits)
  nalHeaderByte |= (anchorPicFlag & 0x01)<<2;	// anchor picture flag  (1 bit)
  nalHeaderByte |= (interViewFlag & 0x01)<<1;	// inter view flag  (1 bit)
  nalHeaderByte |= 0x01;					// reserved one bit  (1 bit)
  bibPutByte(bitbuf, nalHeaderByte);

  return 24;		// Three bytes == 24 bits
}


