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
 * macroblock.h
 *
 * Contains:
 *    Interface for functions handling macroblock layer
 *
 */

#ifndef _MACROBLOCK_H_
#define _MACROBLOCK_H_

#include "nrctypes.h"
#include "globals.h"
#include "bitbuffer.h"
#include "refframe.h"
#include "macroblock.h"
#include "encparams.h"
#include "ratecontrol.h"


/*
 * Structures
 */
typedef struct _macroblock_s
{
  // position of the macroblock
  int isLastMb;
  int idxX, idxY;
  
  // index to first block of MB in raster order not in coding order
  int blkAddr;
  int mbAddr;           // index to this macroblock in raster order

  // availability flags of the neighboring MBs, and intra MBs
  int mbAvailMap[4];
  int mbAvailMapIntra[4];

  // pointers to the current and neighboring macroblocks
  mbState_s *mbThis;
  mbState_s *mbLeft;
  mbState_s *mbUp;
  mbState_s *mbUpLeft;
  mbState_s *mbUpRight;

  // availablility of the up-right and up-left neighboring blocks for i4x4
  u_int8 i4x4CornersAvail[4][4];

  int8   ipTab[16];     // i4x4Mode transformed, ready to be stored in stream

  // parameters used in prediction mode decision

  // minSad should be equal to "minActualSad + lambda * syntaxBits", 
  // syntaxBits is not the same as headerBits, which has more information
  // except for inter16x16, and MV = 0. A fixed bias is added for this mode
  int32 minSad;           // minimal SAD, rate constrained, intra/inter
  int32 minActualSad;     // non-rate constrained SAD, corresponding to minSad
  int32 actualIntraSad;   // actual intra SAD, non-rate constrained,
  int32 actualIntra16x16Sad;// actual intra16x16 SAD, non-rate constrained,
  int32 actualIntra4x4Sad;// actual intra4x4 SAD, non-rate constrained,
  int32 actualInterSad;   // actual inter SAD, non-rate constrained,
  int intraSyntaxBits;  // bits included in intra rate-constrained decision, 
  int interSyntaxBits;  // bits included in inter rate-constrained decision, 
  int minMSE;

  int type;

  // macroblock type, and prediction mode information
  int intraType;
  int intra16x16enabled;
  int intra16x16mode;
  int intraModeChroma;

  int interMode;
  u_int8 interSubMbModes[4];

  int interModeFlags;

  // coding parameters
  int numSkipped;

  int prevQp, qp, qpC, deltaQp;
  int lambda;
#ifndef DISABLE_RDO
  int32 rdoLambda, rdoLambdaIntra;    // all are derived from qp
#endif

  // These are returned from ME, and may be encoded in the bitstream
  int      numVecs;
  int16    diffVecs[16][2];     // differential motion vectors
  u_int8   refIndices[4];       // ref frame indices for up to 4 MB partitions

  motVec_s skipPredMv;          // predictor for 16x16 MB skipping
  int      skipPredMvValid;

  // these are for motion vector prediction
  blkState_s surround[10];
  blkState_s current[4][4];

  blkState_s *blkLeft[16];
  blkState_s *blkUp[16];
  blkState_s *blkUpRight[3][16];

  // 16 MV-ref pairs for one macroblock, for each mode
  // index 0 is reserved for MOT_COPY
  blkState_s modeMvRef[MOT_8x8 + 1][16];
  motVec_s   skipMVs[4][16];         // store additional MVs for tree-pruning

  // MV of 16x16 block is used as search center for smaller blocks
  int16 searchCtr[2];

  // for test encoding
  bitbuffer_s mbBs;

  // for test purpose
  int headerBits;
#ifdef DEBUG_DUMP
  int ssdY, ssdCb, ssdCr;
#endif

  // corresponding positions in reco buffer for current MB
  u_int8  *recoY;
  u_int8  *recoU;
  u_int8  *recoV;

  u_int8 origY[MBK_SIZE][MBK_SIZE];
  u_int8 origC[MBK_SIZE/2][2*(MBK_SIZE/2)];

  // partial sum of the luma of a macroblock
  int partSums4x4[4][4];
  int partSums[4][4];       // effective 2x2, make it 4x4, easier to address

  // stores possible intra16x16 predictors
  u_int8 predBlk2[IPR_NUM_MODES2][MBK_SIZE][MBK_SIZE];
  u_int8 predY[MBK_SIZE][MBK_SIZE];

  // stores possible intra chroma predictors
  u_int8 predIntraC[IPR_CHROMA_NUM_MODES][MBK_SIZE/2][2 * (MBK_SIZE/2)];
  u_int8 predC[MBK_SIZE/2][2 * (MBK_SIZE/2)];

  unsigned int cbpY, cbpC, cbpChromaDC;
  unsigned int rastercbpY;             // cbpY in raster order

  int lumaNonzeroDC;         // nonzero coeffs in luma DC block, I16x16 only

  // perform coefficient elimination
  int coeffElim;
  int coeffElimTh8x8;         // threshold for 8x8 luma block
  int coeffElimThLuma;        // threshold for 16x16 luma block
  int coeffElimThChroma;      // threshold for 8x8 chroma block

#ifndef DISABLE_RDO
  // these are only used in RDO
  unsigned int intra16x16CbpY, intra4x4CbpY;
#endif

  int dcCoefY[BLK_PER_MB][BLK_PER_MB];
  int dcCoefC[2][BLK_PER_MB/2][BLK_PER_MB/2];

  int coefY[BLK_PER_MB * BLK_PER_MB][BLK_SIZE][BLK_SIZE];
  int coefC[2][BLK_PER_MB/2][BLK_PER_MB/2][BLK_SIZE][BLK_SIZE];

#ifdef ENABLE_SEARCH_WINDOW
  // internal search window
  searchWin_s *pSWin;
#endif
  int plr;          // packet loss rate
  u_int8 irType;

  // SAD values for 4x4 blocks
  int16    blkSADs[FRM_MAX_REF_FRAMES][8][16];
  
  int currentView;	
} macroblock_s;

/*
 * Function prototypes
 */
void mbkLoad();

void mbkInit(macroblock_s *mb, int plr);

void mbkRelease(macroblock_s *mb);

void mbkBeforeSlice(macroblock_s *mb,
                    int sliceQp);

void mbkStartEnc(macroblock_s *mb, 
                 mbState_s *mbStateArr,
                 frmBuf_s *orig, 
                 frmBuf_s *reco,
                 encParams_s *encPar, 
                 int qp, 
                 int tuneFactor);

void mbkProcessData(macroblock_s *mb, 
                    int picType, 
                    encParams_s *encPar);

int mbkSend(void         *stream, 
            macroblock_s *mb, 
            int          nRefFrames, 
            int          picType, 
            statSlice_s  *stat);

void mbkFinishEnc(macroblock_s *mb,
                  statSlice_s  *stat);

void mesPrepareProfile(meProfile_s *pMeProf, 
                       refFrmBuf_s *pRefFrm,
                       encParams_s *encPar,
                       int nRefFrames);

int mesFindMotionFullSearch(macroblock_s *pMb, 
                            meProfile_s  *pMeProf,
                            refFrmBuf_s  **refBufList, 
                            int          nRefFrames);

void mesUpdateSearchWin(macroblock_s *pMb);

void mbkModeSelection(rateCtrl_s *pbRC,
                      macroblock_s   *mb, 
                      meProfile_s    *pMeProf,
                      refFrmBuf_s    **refBufList,
                      int            nRefFrames, 
                      int            picType,
                      encParams_s    *encPar,
                      int            *mapRIR,
                      int32          *channelDistortion,
                      int            forcedIRNo,
                      int            *forcedIR,
                      int            mbNum,
                      int            *AIR_intraMap);

#endif  // _MACROBLOCK_H_

