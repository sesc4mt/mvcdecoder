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
 * bitbuffer.c
 *
 * Contains:
 *    Functions for reading from bitbuffer
 *
 */

#include <string.h>
#include <stdio.h>
#include "nccglob.h"
#include "globals.h"
#include "bitbuffer.h"


/*
 * Static functions
 */
static int removeStartCodeEmulationBytes(bitbuffer_s *bitbuf);


/*
 *
 * bibOpen:
 *
 * Parameters:
 *
 * Function:
 *      Open bitbuffer
 *
 * Returns:
 *      Pointer to bitbuffer object or NULL for allocation failure.
 *
 */
bitbuffer_s *bibOpen()
{
  bitbuffer_s *bitbuf;

  bitbuf = (bitbuffer_s *)nccMalloc(sizeof(bitbuffer_s));

  if (bitbuf != NULL)
    memset(bitbuf, 0, sizeof(bitbuffer_s));

  return bitbuf;
}


/*
 *
 * bibInit:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      streamBytes           Pointer to data
 *      length                Data length in bytes
 *
 * Function:
 *      Initialize bitbuffer
 *
 * Returns:
 *      BIB_ok for ok, BIB_ERROR for error
 *
 */
int bibInit(bitbuffer_s *bitbuf, u_int8 *streamBytes, int length)
{
  bitbuf->data           = streamBytes;
  bitbuf->dataLen        = length;
  bitbuf->bytePos        = 0;
  bitbuf->bitpos         = 0;
  bitbuf->errorStatus    = BIB_OK;

#if ENCAPSULATED_NAL_PAYLOAD
  if (removeStartCodeEmulationBytes(bitbuf) < 0)
    return BIB_ERROR;
#endif

  return BIB_OK;
}


/*
 *
 * bibClose:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Close bitbuffer
 *
 * Returns:
 *      -
 *
 */
void bibClose(bitbuffer_s *bitbuf)
{
  nccFree(bitbuf);
}


/*
 *
 * removeStartCodeEmulationBytes:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Remove start code emulation bytes from the bitbuffer
 *
 * Returns:
 *      -
 *
 */
static int removeStartCodeEmulationBytes(bitbuffer_s *bitbuf)
{
  int i;
  int j;
  int numZero;
  u_int32 lastBytes;
  u_int8 *inputData = bitbuf->data;
  int inputLen = bitbuf->dataLen;


  /*
   * Skip the start code if it exists
   */
  numZero = 0;
  i = 0;
  while (i < inputLen) {
    if (inputData[i] == 0)
      numZero++;
    else if (numZero > 1 && inputData[i] == 1) {
      /* Start code found */
      i++;
      break;
    }
    else {
      /* No start code found */
      i = 0;
      break;
    }
    i++;
  }

  /*
   * Convert EBSP to RBSP. Note that the nal head byte is kept within the buffer
   */
  lastBytes = 0xffffffff;
  j = 0;
  while (i < inputLen) {
    lastBytes = (lastBytes << 8) | inputData[i];
    if ((lastBytes & 0xffffff) != 0x000003) {
      inputData[j] = inputData[i];
      j++;
    }
    i++;
  }

  bitbuf->dataLen = j;

  return BIB_OK;
}


/*
 *
 * bibGetBitFunc:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Get next bit from bitbuffer.
 *
 * Returns:
 *      Next bit in bitbuffer or BIB_ERR_NO_BITS if no bits left.
 *
 */
int bibGetBitFunc(bitbuffer_s *bitbuf)
{
  /* If there are no bits left in buffer return an error */
  if (bitbuf->bitpos + 8*(bitbuf->dataLen - bitbuf->bytePos) < 1) {
    printf("Error: unexpected end of bitbuffer\n");
    bitbuf->errorStatus = BIB_ERR_NO_BITS;
    return 0;
  }

  /* Fill bitbuf->currentBits with bits */
  while (bitbuf->bitpos <= 24 && bitbuf->bytePos < bitbuf->dataLen) {
    bitbuf->currentBits = (bitbuf->currentBits << 8) | bitbuf->data[bitbuf->bytePos++];
    bitbuf->bitpos += 8;
  }

  /* Return bit */
  bitbuf->bitpos--;
  return (bitbuf->currentBits >> bitbuf->bitpos) & 1;
}


/*
 *
 * bibGetBitsFunc:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      n                     Number of bits requested
 *
 * Function:
 *      Get next n bits from bitbuffer.
 *
 *      NOTE: maximum of 24 bits can be fetched
 *
 * Returns:
 *      Next n bits from bitbuffer
 *
 */
int32 bibGetBitsFunc(bitbuffer_s *bitbuf, int n)
{
  /* Fill bitbuf->currentBits with bits */
  while (n > bitbuf->bitpos) {
    bitbuf->currentBits <<= 8;
    if (bitbuf->bytePos < bitbuf->dataLen)
      bitbuf->currentBits |= bitbuf->data[bitbuf->bytePos];
    bitbuf->bytePos++;
    bitbuf->bitpos += 8;
  }

  /* If there are not enought bits there was an error */
  if (n > bitbuf->bitpos + 8*(bitbuf->dataLen - bitbuf->bytePos)) {
    printf("Error: unexpected end of bitbuffer\n");
    bitbuf->errorStatus = BIB_ERR_NO_BITS;
  }

  /* Return bits */
  bitbuf->bitpos -= n;
  return (bitbuf->currentBits >> (bitbuf->bitpos)) & ~(((u_int32)-1)<<n);
}


/*
 *
 * bibGetByte:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      byteRet               Return pointer for byte
 *
 * Function:
 *      Get next byte aligned byte from bitbuffer.
 *
 * Returns:
 *      1 for End Of Stream, 0 otherwise
 *
 */
int bibGetByte(bitbuffer_s *bitbuf, int *byteRet)
{
  if (bitbuf->bitpos + 8*(bitbuf->dataLen - bitbuf->bytePos) < 8)
    return 1;

  if (bitbuf->bitpos >= 8) {
    bitbuf->bitpos = bitbuf->bitpos & ~7;
    *byteRet = (bitbuf->currentBits >> (bitbuf->bitpos - 8)) & 0xff;
    bitbuf->bitpos -= 8;
  }
  else {
    bitbuf->bitpos = 0;
    *byteRet = bitbuf->data[bitbuf->bytePos++];
  }

  return 0;
}


/*
 *
 * bibByteAlign:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Set bitbuffer pointer to next byte aligned position.
 *
 * Returns:
 *      Number of bits skipped as a result of aligning.
 *
 */
int bibByteAlign(bitbuffer_s *bitbuf)
{
  int bitpos = bitbuf->bitpos;

  bitbuf->bitpos = bitbuf->bitpos & ~7;

  return (bitpos - bitbuf->bitpos);
}


/*
 * bibSkipTrailingBits:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Skip the trailing bits at the end of a NAL unit
 *
 * Returns:
 *      The number of bits being skipped or <0 for error.
 */
int bibSkipTrailingBits(bitbuffer_s *bitbuf)
{
  int ret;
  int len = 0;
  int bit = 0;

  bit = bibGetBitFunc(bitbuf);
  len++;

  ret = bibGetStatus(bitbuf);
  if (ret < 0)
    return ret;

  /* First we expect to receive 1 bit */
  if (bit != 1) {
    printf("Error: Unexpected trailing bit (0).\n");
    bibRaiseError(bitbuf, BIB_INCORRECT_TRAILING_BIT);
    return BIB_INCORRECT_TRAILING_BIT;
  }

  /* Remaining bits in current byte should be zero */
  while ( bitbuf->bitpos % 8 != 0 ) {  
    bibGetBit(bitbuf, &bit);
    len++;
    if (bit != 0) {
      printf("Error: Unexpected trailing bit (1).\n");
      bibRaiseError(bitbuf, BIB_INCORRECT_TRAILING_BIT);
      return BIB_INCORRECT_TRAILING_BIT;
    }
  }

  ret = bibGetStatus(bitbuf);
  if (ret < 0)
    return ret;

  return len;
}


/*
 * bibMoreRbspData:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Check if there is more RBSP data in the bitbuffer.
 *
 * Returns:
 *      0: no more rbsp data
 *      1: more rbsp data
 */
int bibMoreRbspData(bitbuffer_s *bitbuf)
{
  int numBitsLeft;
  u_int32 lastBits;

  numBitsLeft = bitbuf->bitpos + 8*(bitbuf->dataLen - bitbuf->bytePos);

  if (numBitsLeft >= 9)
    /* If there are at least 9 bits left, it is certain to have more rbsp data */
    return 1;

  if (numBitsLeft <= 0)
    /* Something may be wrong. Normally, there should be at least one bit left */
    return 0;

  if (bitbuf->bytePos < bitbuf->dataLen) {
    /* Insert last byte to currentBits */
    bitbuf->currentBits = (bitbuf->currentBits << 8) | bitbuf->data[bitbuf->bytePos++];
    bitbuf->bitpos += 8;
  }

  /* Copy the last bits into "lastBits", then compare it with 0x1..00 */
  lastBits = bitbuf->currentBits & ~(((u_int32)-1)<<bitbuf->bitpos);

  if (lastBits == ((u_int32)1 << (bitbuf->bitpos-1)))
    return 0;
  else
    return 1;
}


/*
 * bibGetNumOfRemainingBits:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Return number of bits in bitbuffer.
 *
 * Returns:
 *      Number of bits
 */
int32 bibGetNumRemainingBits(bitbuffer_s *bitbuf)
{
  return bitbuf->bitpos + 8*(bitbuf->dataLen - bitbuf->bytePos);
}


/*
 * bibGetStatus:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Return bitbuffer error status
 *
 * Returns:
 *      status
 */
int bibGetStatus(bitbuffer_s *bitbuf)
{
  if (bitbuf->errorStatus < 0)
    return bitbuf->errorStatus;

  if (bitbuf->bitpos + 8*(bitbuf->dataLen - bitbuf->bytePos) < 0)
    bitbuf->errorStatus = BIB_ERR_NO_BITS;

  return bitbuf->errorStatus;
}
