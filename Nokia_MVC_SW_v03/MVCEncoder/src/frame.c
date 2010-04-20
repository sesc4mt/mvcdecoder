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
 * frame.c
 *
 * Contains:
 *    Picture layer functions
 *
 */

#include <math.h>
#include <assert.h>
#include <string.h>
#include "nccglob.h"
#include "globals.h"
#include "debug.h"
#include "frame.h"
#include "loopfilter.h"
#include "slice.h"


/*
 * Prototypes for static functions
 */
static void *allocMem(int blkSize, size_t unitSize);


/*
 * frmLoad:
 *
 * Parameters:
 *
 * Function:
 *      Initialize frame constants
 *
 * Returns:
 *      -
 */
void frmLoad()
{
  mbkLoad();
}


/*
 * allocMem:
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
 */
static void *allocMem(int blkSize, size_t unitSize)
{
  void *mem;

  if ((mem = nccMalloc(blkSize*unitSize)) == NULL) {
#ifdef DEBUG_PRINT
    printf("Cannot allocate memory for frame\n");
#endif
    nccExit(1);
  }

  return mem;
}


#ifdef MOTION_ANALYSIS
// global for debug purpose only
motVec_s *dbgMotVecModes[10];
int *dbgMbSizes;
static FILE *dbgVectorFile;
#endif


/*
 * frmOpen:
 *
 * Parameters:
 *      frame                 Frame
 *      width                 Width of the frame
 *      height                Height of the frame
 *
 * Function:
 *      Allocate memory for frame buffers
 *
 * Returns:
 *      -
 */
void frmOpen(frmBuf_s *frame, 
             int width, 
             int height,
             int plr)
{
  int numPels = width*height;

  frame->width  = (int16) width;
  frame->height = (int16) height;

  frame->y = (u_int8 *)allocMem(numPels, sizeof(u_int8));
  frame->u = (u_int8 *)allocMem(numPels/4, sizeof(u_int8));
  frame->v = (u_int8 *)allocMem(numPels/4, sizeof(u_int8));
  if (plr != 0)
    frame->channelDistortion = (int32*) nccMalloc(sizeof(int32) * numPels/MBK_SIZE/MBK_SIZE);
  else
    frame->channelDistortion = NULL;
}


/*
 * frmEncBufOpen:
 *
 * Parameters:
 *      mbData                Buffers for for macroblock attributes
 *      width                 Width of the frame
 *      height                Height of the frame
 *
 * Function:
 *      Allocate buffers for storing the macroblock attributes.
 *
 * Returns:
 *      -
 */
void frmEncBufOpen(mbAttributes_s *mbData, 
                   int width, 
                   int height,
                   int nRandomIntraRefresh)
{
  int numMacroblocks = width/MBK_SIZE*height/MBK_SIZE;

  // buffers for MB/block level encoding information
  mbData->blksPerLine = width/BLK_SIZE;

  mbData->mbStateArr = (mbState_s *)allocMem(numMacroblocks, sizeof(mbState_s));

  mbData->mapRIR = NULL;
  if (nRandomIntraRefresh > 0)
    mbData->mapRIR = (int *) allocMem(nRandomIntraRefresh, sizeof(int));

#ifdef MOTION_ANALYSIS
  {
    int i;
    int numBlocks = width/BLK_SIZE*height/BLK_SIZE;

    dbgMbSizes = (int *)allocMem(numMacroblocks, sizeof(int));
    for (i = 1; i <= MOT_NUM_MODES; i ++)
    {
      dbgMotVecModes[i] = 
        (motVec_s *)allocMem(numBlocks, sizeof(motVec_s));
    }

    dbgVectorFile = fopen("vecDump.txt", "wt");
  }
#endif
}


/*
 * frmClose:
 *
 * Parameters:
 *      frame                 Frame
 *
 * Function:
 *      Deallocate frame buffers memory.
 *
 * Returns:
 *      -
 *
 */
void frmClose(frmBuf_s *frame)
{
  nccFree(frame->y);
  nccFree(frame->u);
  nccFree(frame->v);
  nccFree(frame->channelDistortion);
}


/*
 * frmEncBufClose:
 *
 * Parameters:
 *      mbData                Buffers for for macroblock attributes
 *
 * Function:
 *      Deallocate buffers used for storing the macroblock attributes.
 *
 * Returns:
 *      -
 */
void frmEncBufClose(mbAttributes_s *mbData)
{
  nccFree(mbData->mbStateArr);

  if (mbData->mapRIR != NULL)
    nccFree(mbData->mapRIR);

#ifdef MOTION_ANALYSIS
  {
    int i;

    // for debug purpose, record all the possible motion vectors
    for (i = 1; i <= MOT_NUM_MODES; i ++)
    {
      nccFree(dbgMotVecModes[i]);
    }

    if (dbgVectorFile)
      fclose(dbgVectorFile);
  }
#endif
}


#if MOTION_FIELD_DRAWING
/*
 * frmDrawMotField
 *
 * Parameters:
 *      mbData                Buffers for macroblock attributes
 *      buf                   Frame buffer used for drawing
 *
 * Function:
 *      Draw motion field and motion blocks.
 *
 * Returns:
 *      -
 */
void frmDrawMotField(mbAttributes_s *mbData,
                     frmBuf_s       *buf)
{
  static const int shape[10][2] = {
    {4, 4}, {4, 4}, {4, 4}, {4, 4}, {4, 2}, {2, 4}, {2, 2}, {2, 1}, {1, 2}, {1, 1}
  };

  int width, height;
  int mbPerLine;
  int mbX, mbY;
  int shapeX, shapeY;
  int blkW, blkH;
  int bx, by;
  int blkX, blkY;
  int pixX, pixY;
  int i, j;
  int vecX, vecY;
  int x1, y1;
  int x, y;
  int addX, addY;
  int len;
  mbState_s *pMbState;        // encoding state of the current MB

  width  = buf->width;
  height = buf->height;
  mbPerLine = width/MBK_SIZE;

  /*
   * Draw block edges
   */
  for (mbY = 0; mbY < height/MBK_SIZE; mbY++) {
    for (mbX = 0; mbX < mbPerLine; mbX++) {
      pMbState = & mbData->mbStateArr[mbY*mbPerLine+mbX];

      shapeX = shape[pMbState->mbType][0];
      shapeY = shape[pMbState->mbType][1];
      blkW = shapeX*BLK_SIZE;
      blkH = shapeY*BLK_SIZE;

      for (by = 0; by < BLK_PER_MB; by += shapeY) {
        for (bx = 0; bx < BLK_PER_MB; bx += shapeX) {

          blkX = mbX*BLK_PER_MB+bx;
          blkY = mbY*BLK_PER_MB+by;
          pixX = blkX*BLK_SIZE;
          pixY = blkY*BLK_SIZE;

          for (i = 0; i < blkW; i++)
            buf->y[(pixY+blkH-1)*width+pixX+i] = (u_int8)0;
          for (j = 0; j < blkH-1; j++)
            buf->y[(pixY+j)*width+pixX+blkW-1] = (u_int8)0;

        }
      }

    }
  }

  /*
   * Draw vectors
   */
  for (mbY = 0; mbY < height/MBK_SIZE; mbY++) {
    for (mbX = 0; mbX < mbPerLine; mbX++) {
      pMbState = & mbData->mbStateArr[mbY*mbPerLine+mbX];

      if (pMbState->mbType <= MB_TYPE_INTRA_16x16) {

        /*
         * INTRA
         */
        x1 = mbX*MBK_SIZE + MBK_SIZE/2 - 1;
        y1 = mbY*MBK_SIZE + MBK_SIZE/2 - 1;
        buf->y[y1*width+x1]     = (u_int8)255;
        buf->y[(y1+1)*width+x1] = (u_int8)255;
        buf->y[(y1-2)*width+x1] = (u_int8)255;
      }
      else {

        /*
         * INTER
         */
        shapeX = shape[pMbState->mbType][0];
        shapeY = shape[pMbState->mbType][1];
        blkW = shapeX*BLK_SIZE;
        blkH = shapeY*BLK_SIZE;

        for (by = 0; by < BLK_PER_MB; by += shapeY) {
          for (bx = 0; bx < BLK_PER_MB; bx += shapeX) {

            blkX = mbX*BLK_PER_MB+bx;
            blkY = mbY*BLK_PER_MB+by;
            pixX = blkX*BLK_SIZE;
            pixY = blkY*BLK_SIZE;
            
            vecX = mbData->motVecTable[blkY*mbPerLine*BLK_PER_MB+blkX].x;
            vecY = mbData->motVecTable[blkY*mbPerLine*BLK_PER_MB+blkX].y;
            
            if (pMbState->mbType - 1 != 0 && (vecX != 0 || vecY != 0)) {
              x1 = (pixX + blkW/2 - 1)*4*65536;
              y1 = (pixY + blkH/2 - 1)*4*65536;
              if (abs(vecX) >= abs(vecY))
                len = abs(vecX),
                addX = SIGN(vecX)*65536, addY = vecY*65536/len;
              else
                len = abs(vecY),
                addY = SIGN(vecY)*65536, addX = vecX*65536/len;
              for (i = 0; i <= len; i+=4) {
                x = (x1+2*65536)/4/65536;
                y = (y1+2*65536)/4/65536;
                if (x > 0 && x < width && y > 0 && y < height)
                  buf->y[y*width+x] = (u_int8)255;
                //                buf->y[y*width+x] = (u_int8)255;
                x1 += addX*4;
                y1 += addY*4;
              }
            }
          }
        }
      }
    }
  }
}

#endif


/*
 *
 * frmEncode
 *
 * Parameters:
 *      slice                 Slice coding object
 *      dpbBuf                Buffer for decoded frames, used as reference frames
 *      encPar                Encoding parameters (motion range, etc.)
 *      mbData                Buffers for macroblock attributes
 *      sps                   Sequence parameter set
 *      pps                   Picture parameter set
 *      pBrc                  pointer to bit rate control engine,
 *
 * Function:
 *      Encode a frame, as 1 or multiple slices.
 *
 * Returns:
 *      -
 *
 */
int frmEncode(slice_s             *slice, 
              dpbBuf_s            *dpbBuf, 
              encParams_s         *encPar, 
              mbAttributes_s      *mbData,
              seq_parameter_set_s *sps, 
              pic_parameter_set_s *pps,
              int                 forcedIRNo,
              int                 *forcedIR,
              rateCtrl_s          *pbRC,
              rtpPacket_s         *rtpPacket,
              int                 *AIR_intraMap)


{
  int i;
  int firstMbAddr;
  int frmMarker, numFrmBits;
  int *mapRIR;
  int numIntraMbs;
  int tuneFactor;
  int sliceIdxInGroup[MAX_SLICE_GROUP_NUM];
  bitbuffer_s *origBitbuf;
  bitbuffer_s redundantBitbuf;
  int redundantPicCnt;
  int origQp;

  if (encPar->redundantPicFlag) {
    // Initialize redundant picture
    origBitbuf = slice->bitbuf;         // Save primary picture buffer
    bibOpen(&redundantBitbuf, 1024);    // Temporary buffer for redundant picture
    slice->bitbuf = &redundantBitbuf;
    origQp = slice->qp;                 // Save primary picture qp
    slice->qp = (int16)clip(MIN_QP, MAX_QP, origQp + encPar->redundantPicQpOffset);
    redundantPicCnt = 1;                // One redundant picture
  }
  else
    redundantPicCnt = 0; // No redundant pictures

  // Any redundant pictures are encoded first and primary picture last
  while (redundantPicCnt >= 0) {

    if (encPar->redundantPicFlag) {
      slice->redundantPicCnt = (int16)redundantPicCnt;
      if (redundantPicCnt == 0) {
        // Restore primary picture parameters
        slice->bitbuf = origBitbuf;  
        slice->qp = (int16)origQp;
      }
    }

    // this is to tune the rdoLambda
    if (slice->nalRefIdc == 0)
      tuneFactor = encPar->tuneNonref;
    else
      tuneFactor = (slice->sliceType == SLICE_I) ? encPar->tuneIntra : encPar->tuneInter;

    // Random Intra REfresh
    mapRIR = NULL;
    if(encPar->nRandomIntraRefresh != 0)
    { 
      mapRIR = mbData->mapRIR;
      for(i = 0; i < encPar->nRandomIntraRefresh; i ++)
        mapRIR[i] = rand() % slice->picSizeInMbs;
    }

    // Generate slice group map, and mark all macroblocks as un-encoded
    sliceGenerateMbMap(slice, pps);

  #if PRINT_IMG_TYPE
    deb0p("Pic sync: type %i, format %i, qp %i, num %i\n",
          (IS_INTRA(slice->sliceType)) ? 2 : (dbpBuf->numRefFrms == 1 ? 0 : 1),
          picFormat, slice->qp, picNum%256);
  #endif

    /*
    * Scan through all slices in picture
    */
    frmMarker = bibGetNumBits(slice->bitbuf);

  #ifdef MOTION_ANALYSIS
    memset(dbgMbSizes, 0, slice->mbksPerLine * sizeof(int));     // DBG
  #endif

    numIntraMbs = 0;
    firstMbAddr = 0;

    for (i = 0; i < MAX_SLICE_GROUP_NUM; i++)
      sliceIdxInGroup[i] = -1;

    // LOW_COMPLEX_PROF3
    // per slice/frame init
    {
      int ii;
      lowComplexProf3_s *plc3 = &(slice->meProfile.lc3);
  #ifdef ENABLE_SEARCH_WINDOW
      searchWin_s *pSWin = &(slice->meProfile.sWin);
  #endif

      plc3->old_cnt = plc3->old_cnt2 = plc3->cnt = -1; 

      for (ii = MOT_COPY;ii <= MOT_8x8; ii++)
        plc3->thre_change[ii] = -1;     // disable

      plc3->thre_change[MOT_16x16] = TH_HPEL_GAIN;

  #ifdef ENABLE_SEARCH_WINDOW
      pSWin->mbksPerLine = slice->mbksPerLine;

      slice->mb.pSWin = &(slice->meProfile.sWin);
  #endif
      plc3->numQPEL=0;
      plc3->numMEs = 0;

      if(encPar->low_complex_prof4 == 1)
      {
        //Initialize frame parameters
        plc3->useProf4=1;
        plc3->skipThreMultiple = 6;
        plc3->sadThreMultiple_1 = 8;
        plc3->sadThreMultiple_2 = 4;
        plc3->exitToIntraTh = 4200;       
        
      }
      else
        plc3->useProf4=0;
    }

    // End of LOW_COMPLEX_PROF3
    do
    {
      if (slice->mbStateArr[firstMbAddr].mbType == -1)
      {
        int temp, numBitsSlice=0,currBytePos = slice->bitbuf->bytePos;
        
        // find one MB not encoded, encode slice that contains this MB
        slice->groupId     = (int16) (slice->mbStateArr[firstMbAddr].sliceMap & 0x0F);
        slice->firstMbAddr = (int16) firstMbAddr;
        slice->firstMbX    = (int16) (firstMbAddr % slice->mbksPerLine);
        slice->firstMbY    = (int16) (firstMbAddr / slice->mbksPerLine);
        
        if(encPar->rtp_flag == 1)
          generateRTPHeader(slice->bitbuf,rtpPacket);
        
        temp = bibGetNumBits(slice->bitbuf);
        
        // this is for identifying different slices within a group
        sliceIdxInGroup[slice->groupId] ++;
        numIntraMbs += sliceEncode(slice, sliceIdxInGroup[slice->groupId], 
          dpbBuf, encPar, tuneFactor, mapRIR, sps, pps, forcedIRNo, forcedIR, pbRC,AIR_intraMap);
        
        
        numBitsSlice = bibGetNumBits(slice->bitbuf)-temp;
                
        if(encPar->rtp_flag == 1)
        {
          //Modify the size
          modifyRTPSize(slice->bitbuf,
            (numBitsSlice)/8,
            currBytePos);
        }
        
      }

      firstMbAddr ++;
    } while (firstMbAddr < slice->picSizeInMbs);

    // per slice/frame finish

    redundantPicCnt--;
  }

  // Append redundant picture after primary picture
  if (encPar->redundantPicFlag) {
    u_int8 *ptr;
    int len, i;

    len = bibGetBuffer(&redundantBitbuf, (void **)&ptr);
    for (i = 0; i < len; i++)
      bibPutByte(slice->bitbuf, ptr[i]);
  }

  // how many bits generated for this frame
  numFrmBits = bibGetNumBits(slice->bitbuf);
  

#ifdef MOTION_ANALYSIS

  // dump the motion vectors for all the modes
  if ((IS_SLICE_P(slice->sliceType)) && (dbgVectorFile != 0))
  {
    int i, j, k, l, m, n, blkIdx, blksPerLine;
    int mbIdx;

    blksPerLine = encPar->picWidth/BLK_SIZE;

    // print x component
    mbIdx = 0;

    for (i = 0; i < encPar->picHeight/BLK_SIZE; i += 4)
      for (j = 0; j < encPar->picWidth/BLK_SIZE; j += 4)
      {
        int mbType;
        mbState_s *pMbState;

        fprintf(dbgVectorFile, "MB: %d", mbIdx);

        pMbState = & slice->mbData->mbStateArr[mbIdx];
        mbType = pMbState->mbType;

        // for the time being, each sub-MB has the same type
        if (mbType >= MB_TYPE_INTER_SKIPPED)
        {
          if (mbType == MB_TYPE_INTER_SKIPPED)
            mbType = MB_TYPE_INTER_16x16;

          mbType -= 2;          // it was incremented by 2
          if (mbType == MOT_8x8)
          {
            mbType += pMbState->subMbType[0];
          }
        }

        switch (mbType)
        {
        case 0:
          fprintf(dbgVectorFile, "intra\n");
          break;
        case 1:
          fprintf(dbgVectorFile, "\tP16x16\t\t\t\t\t\t\t%d\tP16x16\n", dbgMbSizes[mbIdx]);
          break;
        case 2:
          fprintf(dbgVectorFile, "\t\tP16x 8\t\t\t\t\t\t%d\t\tP16x 8\n", dbgMbSizes[mbIdx]);
          break;
        case 3:
          fprintf(dbgVectorFile, "\t\t\tP 8x16\t\t\t\t\t%d\t\t\tP 8x16\n", dbgMbSizes[mbIdx]);
          break;
        case 4:
          fprintf(dbgVectorFile, "\t\t\t\tP 8x 8\t\t\t\t%d\t\t\t\tP 8x 8\n", dbgMbSizes[mbIdx]);
          break;
        case 5:
          fprintf(dbgVectorFile, "\t\t\t\t\tP 8x 4\t\t\t%d\t\t\t\t\tP 8x 4\n", dbgMbSizes[mbIdx]);
          break;
        case 6:
          fprintf(dbgVectorFile, "\t\t\t\t\t\tP 4x 8\t\t%d\t\t\t\t\t\tP 4x 8\n", dbgMbSizes[mbIdx]);
          break;
        case 7:
          fprintf(dbgVectorFile, "\t\t\t\t\t\t\tP 4x 4\t%d\t\t\t\t\t\t\tP 4x 4\n", dbgMbSizes[mbIdx]);
          break;
        }
        mbIdx ++;

        for (k = 0; k < 4; k += 2)
          for (l = 0; l < 4; l += 2)
            for (m = 0; m < 2; m ++)
              for (n = 0; n < 2; n ++)
              {
                blkIdx = (i + k + m) * blksPerLine + j + l + n;

                fprintf(dbgVectorFile, "\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t", 
                  dbgMotVecModes[1][blkIdx].x, dbgMotVecModes[2][blkIdx].x, 
                  dbgMotVecModes[3][blkIdx].x, dbgMotVecModes[4][blkIdx].x, 
                  dbgMotVecModes[5][blkIdx].x, dbgMotVecModes[6][blkIdx].x, 
                  dbgMotVecModes[7][blkIdx].x);
                fprintf(dbgVectorFile, "\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
                  dbgMotVecModes[1][blkIdx].y, dbgMotVecModes[2][blkIdx].y, 
                  dbgMotVecModes[3][blkIdx].y, dbgMotVecModes[4][blkIdx].y, 
                  dbgMotVecModes[5][blkIdx].y, dbgMotVecModes[6][blkIdx].y, 
                  dbgMotVecModes[7][blkIdx].y);
              }
      }
  }
#endif

  /*
   * Invoke loopfilter for current frame
   */
  filFilterFrame(slice->recoBuf, mbData, encPar->chromaQpIdx);

  return numIntraMbs;
}
