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

Any dispute relating to these Terms or the Code shall be submitted to binding arbitration in Westchester County, New York within eighteen (18) months of the date the facts giving rise to the suit were known, or should have been known, by the complainant, except that Nokia may seek injunctive or other relief if you have violated or threatened to violate any intellectual property rights. All matters relating to arbitration shall be governed by the Federal Arbitration Act (9 U.S.C. �1 et. seq.). Arbitration shall be conducted by a single arbitrator under the then prevailing Wireless Arbitration Rules of the American Arbitration Association (�AAA�). Each party must submit any claim which would constitute a compulsory counterclaim in litigation or such claim shall be barred. No award of exemplary, special, consequential or punitive damages shall be permitted. The losing party, as determined by the arbitrator, shall pay the arbitration fees. The arbitrator's award shall be binding and may be entered as a judgment and enforceable in any court of competent jurisdiction. Arbitration shall be conducted on an individual, not class-wide basis, and no arbitration shall be joined with an arbitration involving any other person or entity.

7.3 Severability

If any provision contained in these Terms is determined to be invalid or unenforceable, in whole or in part, the remaining provisions and any partially enforceable provision will, nevertheless, be binding and enforceable, and the parties agree to substitute for the invalid provision a valid provision which most closely approximates the intent and economic effect of the invalid provision.

7.4 Export Control

You shall follow all export control laws and regulations relating to the Code. You agree not to export or re-export, as the case may be, the Code to any country without obtaining licenses and permits that may be required under any applicable legislation or regulations.  You shall not license the Code or provide services, nor export or re-export any information, or any process, product or service that is produced under these Terms to any country specified as a prohibited destination in applicable national, state and local, regulations and ordi�nances, including the Regulations of the U.S. Department of Commerce and/or the U.S. State Department, without first obtaining government approval.
*/


/*
 *    ratecontrol.h
 * 
 *    Contains: 
 *
 *    Implenentation of one-pass rate control. 
 *
 */

#ifndef _RATECONTROL_H_
#define _RATECONTROL_H_
#include <stdio.h>

#include "encparams.h"
#include "avcencoder.h"
#include "parameterset.h"
#include "sei.h"

//#define USE_SIMPLE_MODEL

//#define RC_DEBUG                      // Debug file is used
#define MAX_RD_WINDOW_SIZE 20           // Short term RD model window size
#define MAX_LT_RD_WINDOW_SIZE 100       // Long term RD model window size
//#define USE_SPP                       // Use High-Quality P Pictures (SPP) periodically
#define SPP_PICTURE_FREQ  15            // The freq to use SPP pictures, Should be higher if GOP is used. 
#define SPP_QP_CHANGE    4              // QP Change in High Quality P Pictures

#define STRICT_FILE_SIZE_CONTROL        
                                      
//#define ENABLE_REENCODE               // For realtime operation disable this

#define MIN(a,b)  (((a)<(b)) ? (a) : (b))
#define MAX(a,b)  (((a)<(b)) ? (b) : (a))
  
typedef struct {
#ifndef USE_SIMPLE_MODEL

  //RD_Model Related Parameters
  int  rdModel_QP[MAX_LT_RD_WINDOW_SIZE+1];
  float  rdModel_Qstep[MAX_RD_WINDOW_SIZE+1];  
  int rdModel_TextureBits[MAX_RD_WINDOW_SIZE+1];
  int rdModel_HeaderBits[MAX_RD_WINDOW_SIZE+1];
  int rdModel_PictureMAD[MAX_RD_WINDOW_SIZE+1]; 
  int rdModel_Rejected[MAX_RD_WINDOW_SIZE+1];
  float rdModel_X1;
  float rdModel_X2;
  int rdModel_windowSize;  

  //Long Term Model
  float  lt_rdModel_Qstep[MAX_LT_RD_WINDOW_SIZE+1];
  int lt_rdModel_TextureBits[MAX_LT_RD_WINDOW_SIZE+1];
  int lt_rdModel_HeaderBits[MAX_LT_RD_WINDOW_SIZE+1];
  int lt_rdModel_PictureMAD[MAX_LT_RD_WINDOW_SIZE+1]; 
  int lt_rdModel_Rejected[MAX_LT_RD_WINDOW_SIZE+1];
  float lt_rdModel_X1;
  float lt_rdModel_X2;
  int lt_rdModel_windowSize;

  int BufferFullnessArray[MAX_LT_RD_WINDOW_SIZE];

  float framePSNR[MAX_LT_RD_WINDOW_SIZE+1];
  float currentFramePSNR;


  int use_lt_RD_Model;
  int use_sh_RD_Model;
#else
  
  int sadHistory[MAX_RD_WINDOW_SIZE+1];
  int qpHistory[MAX_RD_WINDOW_SIZE+1];
  int bitHistory[MAX_RD_WINDOW_SIZE+1];
  float qstepHistory[MAX_RD_WINDOW_SIZE+1];

#endif
  
  int frameSkipEnabled;
  int modeDecision;

  int32 CurrentPicturePredictedMAD;
  int32 upperFrameLimit;
  int32 lowerFrameLimit;
  int32 centerFrameBits;

  int32 TotalFrameBits;
  int SPPPictureCounter;    
  int SPPframeComputedQP;
  int averageQPforFrame;
  int32 TotalBits;
  int stat_NumberofSkips;
  int stat_NumberofUnderflows;
  int stat_NumberofReencodes;
  int TotalNumberofMB;
  int QP_LW;
  int QP_SW;

  int img_type;
  int numConsecutiveSkips;
  int numConsecutiveUnderflows;

  int frameComputedQP;
  int frameReturnedQP;
  int32 PictureIndex;
  int32 PPictureIndexinGOP;
  int GOPSize; 
  int32 BufferSize;
  int32 realBufferSize;
  int32 CurrentBufferFullness; 
  int32 actualBufferFullness;
  int32 TargetBufferLevel; 
  int32 bit_rate; 
  int32 frame_rate;
  int32 bitsPerFrame;
  int32 bitsPerPFrame;
  int32 bitDifference;   
  int bufferStall;    
  int playingStartFrame;
  int32 numFrms;
  int InitialQP; 
  int scut;     
  int useSEI;  
  int numIntraMBs;
  int numNonref;
  int modelQP;

  int32 prevFrameBits;
  int32 currentFrameBits;

  int ignoreIDR; // A special case for video telephony. If enabled, the output bitrate will be slightly off the target 
                 // No buffer regulation is done for IDR pictures  

  FILE* rcdebug;

  picture_timing_SEI_s picture_timing_SEI; 
  buffering_period_SEI_s bufperiodSEI;

  int BIT_ADJUST_FREQUENCY;
  int BIT_ADJUST_WINDOW;
  int LT_WINDOW_QP_UPDATE_FREQ;
  int nalRefIdc;
  int32 srcPicNum;

  int numSkippedMBs ;  

  int UPPER_LIMIT_MULTIPLE;   
  int LOWER_LIMIT_MULTIPLE;     

  
  int32* prevFrame_MBsad;
  int* prevFrame_MBQp;
  int32* prevFrame_MBtexbits;
  int32* prevFrame_MBheaderbits;
  int32* currentFrame_MBsad;
  int* currentFrame_MBQp;
  int32* currentFrame_MBtexbits;
  int32* currentFrame_MBheaderbits;
  int32* MSEofMB;

  int lastQPUpdateID;

  int IFrameQP[10];
  int32 IFrameBits[10];

  int brcdisableMBLevel;
  int I_P_RATIO;
  int prevFrameScut;
  
  int strictControlFlag;
} rateCtrl_s;


#ifndef USE_SIMPLE_MODEL
int    rc_update_pict(rateCtrl_s *pbRC, int img_type, int32 texbits,int32 headerbits,float psnrY);
#else
int    rc_update_pict(rateCtrl_s *pbRC, int img_type, int32 texbits,int32 headerbits);
#endif

void   rc_init_seq(rateCtrl_s *pbRC, encParams_s *pencPar);
void   rc_init_pict(rateCtrl_s *pbRC, int img_type, int nalRefIdc,int srcPicNum);

int    rc_getFrameQP(rateCtrl_s *pbRC, int img_type);
void   rc_update_bitrate(rateCtrl_s *pbRC, int bitrate);
int    rc_getMBQP(rateCtrl_s *bRC, int sliceType,int mbNum);
void   rc_updateMB(rateCtrl_s *bRC, int texbits,int headerbits,int sad, int mb_type, int mb_interMode,int mbNum);
void fillHRDParameters(rateCtrl_s *pbRC, hrd_parameters_s *hrd);
void fillBufferingPeriodSEI(rateCtrl_s *pbRC);
void fillPictureTimingSEI(rateCtrl_s *pbRC);
void fillFillerPayloadSEI(rateCtrl_s *pbRC,int payloadSize);
void rc_free_mem(rateCtrl_s *pbRC);
void rc_printDebug(rateCtrl_s *pbRC,statSlice_s *frmStat);

#endif