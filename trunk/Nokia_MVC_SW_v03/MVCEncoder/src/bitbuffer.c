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


#include <assert.h>
#include <stdio.h>
#include "debug.h"
#include "nrctypes.h"
#include "globals.h"
#include "bitbuffer.h"
#include "nccglob.h"


/* Maximum number of zeros in RBSP */
#define STR_MAX_ZEROS             2

/*
 *
 * bibOpen:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Open and initialize bitbuffer writing
 *      The bits are written to a byte. When the byte is full, the byte is 
 *      stored in array.
 *
 * Returns:
 *      -
 *
 */
void bibOpen(bitbuffer_s *bitbuf, int initialSize)
{
  bitbuf->bufSize = initialSize;

  bitbuf->bufAddr = (u_int8 *) nccMalloc(bitbuf->bufSize);

  if (bitbuf->bufAddr == NULL) {
#ifdef DEBUG_PRINT
    printf("Cannot allocate memory for bitbuffer");
#endif
    nccExit(1);
  }

  bibInit(bitbuf);
}


/*
 *
 * bibInit:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Set the bit buffer in empty state.
 *
 * Returns:
 *      -
 *
 */
void bibInit(bitbuffer_s *bitbuf)
{
  bitbuf->bytePos = 0;
  bitbuf->currentBits = 0;
  bitbuf->bitpos = 32;
  bitbuf->numZeros = 0;
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
  // release the buffer
  nccFree(bitbuf->bufAddr);
  bitbuf->bufAddr = 0;
}


/*
 *
 * bibPutByte:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      byte                  Byte to store
 *
 * Function:
 *      Put one byte to the bitbuffer. If buffer is full, allocate 
 *      bigger buffer.
 *
 *      NOTE: does not insert start code emulation prevention bytes
 *
 * Returns:
 *      -
 */
void bibPutByte(bitbuffer_s *bitbuf, int byte)
{
  /* Check if we have enough memory and get more if not */
  if (bitbuf->bytePos == bitbuf->bufSize) {
    /* Increase buffer size by 20% and round up to nearest kilobyte */
    bitbuf->bufSize = (12*(bitbuf->bufSize)/10 + 1023) & ~1023;
    bitbuf->bufAddr = nccRealloc(bitbuf->bufAddr, bitbuf->bufSize);
    if (bitbuf->bufAddr == NULL) {
#ifdef DEBUG_PRINT
      printf("Cannot allocate memory for bitbuffer");
#endif
      nccExit(1);
    }
  }

  /* Store byte into the bit buffer */
  bitbuf->bufAddr[bitbuf->bytePos++] = (u_int8)byte;
}


/*
 *
 * bibPutBits:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      bits                  Bits to store
 *      len                   Number of bits to store
 *
 * Function:
 *      Put number of bits to bitbuffer. Also take care of start code
 *      emulation prevention.
 *
 * Returns:
 *      Number of bits stored
 */
int bibPutBits(bitbuffer_s *bitbuf, u_int32 bits, int len)
{
  /* To avoid the side affect of higher bits in the input byte */
  if (len != 32)
    bits &= ~((u_int32)-1 << len);

  if (bitbuf->bitpos > len)
  {
    // make this path fast
    bitbuf->bitpos -= len;
    bitbuf->currentBits |= bits << bitbuf->bitpos;
  }
  else
  {
    int i, remLen;
    int currentByte;

    // fill the remaing bits in the buffer
    remLen = len - bitbuf->bitpos;
    bitbuf->currentBits |= bits >> remLen;

    // send 4 bytes
    for (i = 0; i < 4; i ++)
    {
      currentByte = bitbuf->currentBits >> 24;
      bitbuf->currentBits <<= 8;

      if (bitbuf->numZeros == STR_MAX_ZEROS  && (currentByte & 0xfc) == 0)
      {
        bibPutByte(bitbuf, 0x03);
        bitbuf->numZeros = 0;
      }

      if (currentByte == 0)
        bitbuf->numZeros ++;
      else
        bitbuf->numZeros = 0;

      bibPutByte(bitbuf, currentByte);
    }

    // put the remaining bits in the buffer
    bitbuf->bitpos = 32 - remLen;
    bitbuf->currentBits = 0;
    if (remLen)
      bitbuf->currentBits = bits << bitbuf->bitpos;
  }

  return len;
}


/*
 * bibByteAlign:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Align bitbuffer writing at byte boundary.
 *
 * Returns:
 *      The number of skipped bits
 */
int bibByteAlign(bitbuffer_s *bitbuf)
{
  int bitsSkipped;

  while (bitbuf->bitpos < 32)
  {
    bibPutByte(bitbuf, bitbuf->currentBits >> 24);
    bitbuf->currentBits <<= 8;
    bitbuf->bitpos += 8;
  }

  bitsSkipped = bitbuf->bitpos - 32;
  bitbuf->bitpos = 32;

  // set numZeros to 0, because this function is called at the end of NAL
  bitbuf->numZeros = 0;

  return bitsSkipped;
}


/*
 * bibIsByteAlign:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Check if the bitbuf is byte aligned.
 *
 * Returns:
 *      1: if byte aligned
 *      0: otherwise
 */
int bibIsByteAlign(bitbuffer_s *bitbuf)
{
  if (bitbuf->bitpos % 8 == 0)
    return 1;
  else
    return 0;
}


/*
 *
 * bibGetNumBits:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Get bit buffer position in bits
 *
 * Returns:
 *      bit buffer position.
 *
 */
int bibGetNumBits(bitbuffer_s *bitbuf)
{
  return (bitbuf->bytePos * 8 + 32 - bitbuf->bitpos);
}


/*
 *
 * bibTrailingBits:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *
 * Function:
 *      Put bitbuffer trailing bits
 *
 * Returns:
 *      Number of bits stored
 *
 */
int bibTrailingBits(bitbuffer_s *bitbuf)
{
  int bits = 0;

  bits+=bibPutBits(bitbuf, 1, 1);         // rbsp_stop_one_bit  
  bits+=bibByteAlign(bitbuf);

  return bits;
}


/*
 *
 * bibGetBuffer:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      bufferPtr             Return pointer for bit buffer
 *
 * Function:
 *      Get bit buffer pointer and size
 *
 * Returns:
 *      Number of bytes in bit buffer
 *
 */
int bibGetBuffer(bitbuffer_s *bitbuf, void **bufferPtr)
{
  *bufferPtr = bitbuf->bufAddr;

  return bitbuf->bytePos;
}


/*
 *
 * ebibSaveState:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      save                  Destination buffer for saved state
 *
 * Function:
 *      Save bitbuffer state.
 *
 * Returns:
 *
 */
void bibSaveState(bitbuffer_s *bitbuf, bitbuffer_s *save)
{
  *save = *bitbuf;
}


/*
 *
 * ebibRestoreState:
 *
 * Parameters:
 *      bitbuf                Bitbuffer object
 *      saved                 Saved state
 *
 * Function:
 *      Restore bitbuffer state.
 *
 * Returns:
 *
 */
void bibRestoreState(bitbuffer_s *bitbuf, bitbuffer_s *saved)
{
  bitbuf->bitpos      = saved->bitpos;
  bitbuf->bytePos     = saved->bytePos;
  bitbuf->currentBits = saved->currentBits;
  bitbuf->numZeros    = saved->numZeros;
}

