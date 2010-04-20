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
 *    ratecontrol.c
 * 
 *    Contains: 
 *
 *    Implenentation of one-pass rate control. 
 *
 */


#ifdef RC_DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif
#include <math.h>
#include <string.h>
#include <limits.h>
#include "globals.h"
#include "avcencoder.h"
#include "sequence.h"
#include "ratecontrol.h"
#include "sei.h"
#include "nccglob.h"

#ifndef USE_SIMPLE_MODEL

FILE *dbg_file;

int scoreLUT[20]={66,66,66,66,66,66,71,74,77,82,
85,87,89,92,94,96,98,100 ,100, 100};


//PI attenuation factors
static float Kp = 0.50f;
static float Ki = 0.10f;
static float Kd = 0.4f;


void RDModelEstimator (rateCtrl_s *pbRC, int img_type);
void lt_RDModelEstimator (rateCtrl_s *pbRC, int img_type);
int getQP_UsingRDModel(int targetBits, int mad, float X1, float X2);
int getAverageMAD(rateCtrl_s *pbRC, int windowSize, int lt);
float getAverageQstep(rateCtrl_s *pbRC, int windowSize, int lt);
int getAverageTextureBits(rateCtrl_s *pbRC, int windowSize, int lt);
int getAverageHeaderBits(rateCtrl_s *pbRC, int windowSize, int lt) ;


int ComputePictureMAD(rateCtrl_s *pbRC);
int Qstep2QP( float Qstep );
float QP2Qstep( int QP );
void createBitEnvelope(rateCtrl_s *pbRC);
int getIFrameQP(rateCtrl_s *pbRC);
int checkFrameSkip(rateCtrl_s *pbRC, int frmBits,float psnrY);
void computePFrameQP(rateCtrl_s *pbRC, int img_type, int nalRefIdc,int srcPicNum,int hdrSize);

static void rc_alloc_mem(rateCtrl_s *bRC)
{

  //Allocate the tables
  bRC->prevFrame_MBsad = (int32*) nccMalloc(sizeof(int32) * bRC->TotalNumberofMB);
  bRC->prevFrame_MBQp = (int*) nccMalloc(sizeof(int) * bRC->TotalNumberofMB);
  bRC->prevFrame_MBtexbits = (int32*) nccMalloc(sizeof(int32) * bRC->TotalNumberofMB);
  bRC->prevFrame_MBheaderbits = (int32*) nccMalloc(sizeof(int32) * bRC->TotalNumberofMB);
  
  bRC->currentFrame_MBsad = (int32*) nccMalloc(sizeof(int32) * bRC->TotalNumberofMB);
  bRC->currentFrame_MBQp = (int*) nccMalloc(sizeof(int) * bRC->TotalNumberofMB);
  bRC->currentFrame_MBtexbits = (int32*) nccMalloc(sizeof(int32) * bRC->TotalNumberofMB);
  bRC->currentFrame_MBheaderbits = (int32*) nccMalloc(sizeof(int32) * bRC->TotalNumberofMB);
  
  bRC->MSEofMB = (int32*) nccMalloc(sizeof(int32) * bRC->TotalNumberofMB);
  
  memset(bRC->prevFrame_MBsad, 0, sizeof(int32)*bRC->TotalNumberofMB);
  memset(bRC->prevFrame_MBQp, 0, sizeof(int)*bRC->TotalNumberofMB);
  memset(bRC->prevFrame_MBtexbits, 0, sizeof(int32)*bRC->TotalNumberofMB);
  memset(bRC->prevFrame_MBheaderbits, 0, sizeof(int32)*bRC->TotalNumberofMB);
  
  memset(bRC->currentFrame_MBsad, 0, sizeof(int32)*bRC->TotalNumberofMB);
  memset(bRC->currentFrame_MBQp, 0, sizeof(int)*bRC->TotalNumberofMB);
  memset(bRC->currentFrame_MBtexbits, 0, sizeof(int32)*bRC->TotalNumberofMB);
  memset(bRC->currentFrame_MBheaderbits, 0, sizeof(int32)*bRC->TotalNumberofMB);
  
  memset(bRC->MSEofMB, 0, sizeof(int32)*bRC->TotalNumberofMB);
}


// Initiate rate control parameters
void rc_init_seq(rateCtrl_s *bRC, encParams_s *pencPar)
{
  int L1,L2,L3,bpp;
  int qp;
  int i;
  
  memset(bRC, 0, sizeof(rateCtrl_s));
  if(pencPar->brcBitRate!=0)
  {    
#ifndef DISABLE_RDO
    bRC->modeDecision = (pencPar->rdo & 0x0F);
#else
    bRC->modeDecision = MODE_DECISION_SIMPLE;
#endif
    bRC->numFrms = pencPar->numFrms;
    bRC->numConsecutiveSkips = 0;
    bRC->numIntraMBs = 0;
    bRC->bit_rate=pencPar->brcBitRate;
    bRC->frame_rate=pencPar->origFpsTimes1000/pencPar->offsetForRefFrame/1000;
    bRC->BufferSize=MIN(bRC->bit_rate*6,pencPar->brcBufSize*8);
    
    if(bRC->numFrms > 0)
    {
      bRC->BufferSize = MIN(bRC->BufferSize,(bRC->numFrms*bRC->bit_rate)/(bRC->frame_rate*3));
      bRC->BufferSize = MAX(bRC->BufferSize,bRC->bit_rate*2/10);
    }      
    

    bRC->realBufferSize = pencPar->brcBufSize*8;
    bRC->prevFrameScut=0;
    
    if(bRC->BufferSize < bRC->bit_rate)
    {
      //Low Delay
      bRC->I_P_RATIO = 5;
      bRC->UPPER_LIMIT_MULTIPLE = 2;
      bRC->LOWER_LIMIT_MULTIPLE = 4;
      bRC->BIT_ADJUST_FREQUENCY = 1;
      bRC->BIT_ADJUST_WINDOW = MAX(30,bRC->BufferSize/(2*bRC->bit_rate));
      bRC->LT_WINDOW_QP_UPDATE_FREQ = 4;
      
    }
    else
    {
      //Larger Delay
      bRC->I_P_RATIO = 8;
      bRC->UPPER_LIMIT_MULTIPLE = 6;
      bRC->LOWER_LIMIT_MULTIPLE = 4;
      bRC->BIT_ADJUST_FREQUENCY = 5;
      bRC->BIT_ADJUST_WINDOW = MAX(50,bRC->BufferSize/(2*bRC->bit_rate));
      if(bRC->BufferSize < bRC->bitsPerFrame*3 || bRC->numFrms < 300 )
        bRC->LT_WINDOW_QP_UPDATE_FREQ = 15;
      else
        bRC->LT_WINDOW_QP_UPDATE_FREQ = 50;      
    }
    
    bRC->useSEI = pencPar->useSEIMessages;
    bRC->numSkippedMBs = 0;
    bRC->numNonref = pencPar->numNonref;
    bRC->frameSkipEnabled = pencPar->frameSkipEnabled;
    bRC->TotalNumberofMB = pencPar->picWidth*pencPar->picHeight/256;
    
    bRC->stat_NumberofSkips = 0;
    bRC->stat_NumberofReencodes = 0;
    bRC->CurrentBufferFullness=0;
    bRC->actualBufferFullness=0;
    bRC->TargetBufferLevel = bRC->BufferSize/2;
    
    bRC->use_lt_RD_Model= 0;
    bRC->use_sh_RD_Model= 0;
    bRC->rdModel_windowSize=0;
    bRC->lt_rdModel_windowSize=0;
    bRC->rdModel_X1=pencPar->brcBitRate*1.0f;
    bRC->rdModel_X2=0.0;
    bRC->lt_rdModel_X1=pencPar->brcBitRate*1.0f;
    bRC->lt_rdModel_X2=0.0f;
    bRC->brcdisableMBLevel = pencPar->brcdisableMBLevel;

    rc_alloc_mem(bRC);
    
    for(i=0;i<bRC->TotalNumberofMB;i++)
    {
      bRC->prevFrame_MBsad[i]=0;
      bRC->prevFrame_MBQp[i]=0;
      bRC->prevFrame_MBtexbits[i]=0;
      bRC->prevFrame_MBheaderbits[i]=0;
      bRC->currentFrame_MBsad[i]=0;
      bRC->currentFrame_MBQp[i]=0;
      bRC->currentFrame_MBtexbits[i]=0;
      bRC->currentFrame_MBheaderbits[i]=0;    
    }
    
    bRC->PPictureIndexinGOP=-1;
    bRC->PictureIndex=0;
    
    bRC->SPPPictureCounter = SPP_PICTURE_FREQ;
    bRC->bitDifference=0;
    
    bRC->bufferStall = 1;
    bRC->playingStartFrame = 0;
    bRC->TotalBits = 0;
    bRC->prevFrameBits = 0;
    bRC->currentFrameBits = 0;
    
    if(pencPar->intraFreq == 0 && pencPar->idrFreq == 0)
      bRC->GOPSize = bRC->numFrms;
    
    else
    {    
      if(pencPar->intraFreq > 0)
        bRC->GOPSize = pencPar->intraFreq;
      else
        bRC->GOPSize = pencPar->idrFreq;
    }
    
    bRC->CurrentPicturePredictedMAD=0;
    for(i=0;i<MAX_RD_WINDOW_SIZE;i++)
    {
      bRC->rdModel_QP[i]    = 0;
      bRC->rdModel_Qstep[i]    = 0;
      bRC->rdModel_PictureMAD[i]  = 0;
      bRC->rdModel_TextureBits[i]  = 0;
      bRC->rdModel_HeaderBits[i]  = 0;
      bRC->BufferFullnessArray[i]  = 0;
    }
    for(i=0;i<MAX_LT_RD_WINDOW_SIZE;i++)
    {
      bRC->lt_rdModel_Qstep[i]      = 0;
      bRC->lt_rdModel_PictureMAD[i]  = 0;
      bRC->lt_rdModel_TextureBits[i]  = 0;
      bRC->lt_rdModel_HeaderBits[i]  = 0;  
      bRC->framePSNR[i]              = 0.0f;
    }
    bRC->currentFramePSNR = 0.0f;

    //Calculate the Initial QP from bpp
    bRC->InitialQP=pencPar->qpStart;
    bRC->QP_LW = pencPar->qpStart;
    bRC->frameComputedQP = pencPar->qpStart;
    
    bRC->ignoreIDR = pencPar->ignoreIDRBits;
    
    /*compute the initial QP*/
    bpp = 100*bRC->bit_rate /(bRC->frame_rate * pencPar->picWidth * pencPar->picHeight);
    
    if (pencPar->picWidth <= 200) 
    {
      L1 = 10;
      L2 = 30;
      L3 = 60;
    }
    else if (pencPar->picWidth <= 400)
    {
      L1 = 20;
      L2 = 60;
      L3 = 120;
    }
    else 
    {
      L1 = 30;
      L2 = 60;
      L3 = 150;
    }
    
    if (bRC->InitialQP==0)
    {
      if(bpp<= L1)
        qp = 35;
      else if(bpp<=L2)
        qp = 25;
      else if(bpp<=L3)
        qp  = 20;
      else
        qp =10;
      
      if(bRC->BufferSize < bRC->bit_rate*0.5)
        qp+=3;
    
      bRC->InitialQP = qp;
      bRC->QP_LW = qp;
      bRC->frameComputedQP = qp;
    }
    
#ifdef RC_DEBUG
    if((bRC->rcdebug=fopen("RCA_debug.txt","w"))==NULL)
    {
      printf("Cannot open RCA_debug.txt\n");
      exit(1);
    }
#endif
    
    bRC->bitsPerFrame = (int)(bRC->bit_rate*1.0/bRC->frame_rate) ;
    bRC->centerFrameBits = bRC->bitsPerFrame;
    bRC->averageQPforFrame =  bRC->InitialQP;
    bRC->SPPframeComputedQP = bRC->InitialQP;
    bRC->strictControlFlag = 0;
    bRC->frameReturnedQP = bRC->frameComputedQP;
    
    for(i=0;i<10;i++)
      bRC->IFrameQP[0] = 0;
    
    bRC->IFrameQP[0] = pencPar->qpStart;

  }
  else
  {
    bRC->numIntraMBs = 0;
    bRC->bit_rate=pencPar->brcBitRate;
    bRC->frame_rate=pencPar->origFpsTimes1000/pencPar->offsetForRefFrame/1000;
    bRC->bitsPerFrame = (int)(bRC->bit_rate*1.0/bRC->frame_rate) ;
  }
    
  //Ignore IDR bits for low delay cases
  if (bRC->bit_rate > 0 && bRC->BufferSize*1.0f/bRC->bit_rate < 0.5 && bRC->ignoreIDR == 0)
  {
    bRC->ignoreIDR = 1;
#ifdef DEBUG_PRINT
    printf("Low Delay Rate Control Enabled. Intra/IDR Bits will be ignored\n");
#endif
  }

  if(bRC->ignoreIDR == 2)
    bRC->ignoreIDR = 0;

}


void rc_init_pict(rateCtrl_s *bRC, int img_type, int nalRefIdc,int srcPicNum)
{
  int hdrSize;
  int avg_sh_HeaderBits, avg_sh_TextureBits;
  int finalQp=0;
  int i;
  
  
  if(bRC->bit_rate != 0)
  {
    bRC->numSkippedMBs = 0;
    bRC->img_type = img_type;
    bRC->numIntraMBs = 0;
    bRC->nalRefIdc = nalRefIdc;
    bRC->srcPicNum = srcPicNum;
    bRC->lastQPUpdateID = 0;
    bRC->currentFrameBits = 0;
    if(bRC->GOPSize > 1)
    {
      if(bRC->PictureIndex == 0)
      {
        bRC->bitsPerPFrame =(int) (bRC->bit_rate*10/bRC->frame_rate * (bRC->GOPSize *10 / (bRC->GOPSize - 1 + 5.0) ) )/100;
        bRC->bitsPerPFrame = (int)((bRC->bitsPerPFrame)*(bRC->numNonref+1)*10/(10+7*bRC->numNonref));            
      }
    }
    else
    {
      bRC->upperFrameLimit =  (int)(bRC->bitsPerFrame*12/10);
      bRC->lowerFrameLimit =  (int)(bRC->bitsPerFrame*8/10);
    }
    
    if(img_type==SLICE_P && (bRC->PPictureIndexinGOP > 0) )
      bRC->CurrentPicturePredictedMAD = (int)bRC->rdModel_PictureMAD[0];
    
    if(img_type == SLICE_I)
      hdrSize = 0;
    else
      hdrSize=bRC->rdModel_windowSize;
    hdrSize=MIN(hdrSize,MAX_RD_WINDOW_SIZE);
    avg_sh_HeaderBits = getAverageHeaderBits(bRC,hdrSize,0);
    avg_sh_TextureBits = getAverageTextureBits(bRC,hdrSize,0);
    
    if(bRC->PictureIndex == 0)
      bRC->scut = 0;
    
    //Fill the Picture Timing SEI Message associated with the current picture
    if(bRC->useSEI)  
      fillPictureTimingSEI(bRC);
    
    if(img_type == SLICE_I)
    {
      bRC->PPictureIndexinGOP = -1;
      
      createBitEnvelope(bRC);
      if(bRC->scut == 1 )
      {

        //This is a frame at scut; Reset the short-term window
        finalQp =(int)( ((bRC->QP_LW + bRC->averageQPforFrame)/2) + 2);
        for(i=0;i<MAX_RD_WINDOW_SIZE;i++)
        {
          bRC->rdModel_QP[i]    = 0;
          bRC->rdModel_Qstep[i]    = 0;
          bRC->rdModel_PictureMAD[i]  = 0;
          bRC->rdModel_TextureBits[i]  = 0;
          bRC->rdModel_HeaderBits[i]  = 0;
        }
        bRC->rdModel_windowSize = 0;
        bRC->use_sh_RD_Model= 0;
        
        if(finalQp > bRC->frameComputedQP)
          bRC->frameComputedQP=MIN(bRC->frameComputedQP + 2, finalQp);
        else
          bRC->frameComputedQP=MAX(bRC->frameComputedQP - 2, finalQp);

      }
      else
      {
        
        if(bRC->PictureIndex > 0)
          bRC->frameComputedQP = getIFrameQP(bRC);
      }
    }
    
    if(img_type==SLICE_P)
    {        
      
#ifdef USE_SPP    
      if(bRC->SPPPictureCounter == 0 && (bRC->BufferSize - bRC->CurrentBufferFullness) < 5*bRC->bitsPerFrame)
        bRC->SPPPictureCounter = 1;
#endif
      
      createBitEnvelope(bRC);         
      computePFrameQP(bRC, img_type, nalRefIdc,srcPicNum,hdrSize);
      
    }
    
    bRC->frameComputedQP=(int)(MAX(bRC->frameComputedQP, 1 ));
    bRC->frameComputedQP=(int)(MIN(bRC->frameComputedQP, 51 ));
    
    return;
  }
  else
  {
    bRC->numIntraMBs = 0;
    return;
  }
}


int rc_update_pict(rateCtrl_s *bRC, int img_type, int32 texbits,int32 headerbits,float psnrY)
{
  int i;
  int tempRDSize,lt_tempRDSize;
  int MADUpdateFlag=0;
  int Qaver;
  int hdrSize;
  int avgHeaderBits = 0,avgTextureBits = 0; 
  int tex;
  float error[MAX_RD_WINDOW_SIZE],lt_error[MAX_LT_RD_WINDOW_SIZE],  std = 0.0, lt_std=0.0, threshold;
  float picqstep;
  int avgMAD;
 

  bRC->prevFrameBits = bRC->currentFrameBits;
  bRC->currentFramePSNR = psnrY;
  
  if(bRC->PictureIndex == 0)
    bRC->IFrameQP[0] = 0;
  
  if(img_type == SLICE_I)
  {
    for(i=9;i>0;i--)
    {
      bRC->IFrameQP[i]   = bRC->IFrameQP[i-1];
      bRC->IFrameBits[i] = bRC->IFrameBits[i-1];
    }
    bRC->IFrameQP[0]   = (int)(bRC->averageQPforFrame+0.5);
    bRC->IFrameBits[0] = texbits + headerbits;
  }

  if(bRC->numIntraMBs > bRC->TotalNumberofMB/2 || (bRC->prevFrameScut == 1 && (bRC->CurrentBufferFullness + texbits+headerbits - bRC->bitsPerFrame > bRC->BufferSize) ))
  //This was a frame at scene cut
    bRC->prevFrameScut = 1;
  else
    bRC->prevFrameScut = 0;

  if(bRC->bit_rate == 0)
  {
    bRC->CurrentBufferFullness = bRC->CurrentBufferFullness + texbits + headerbits - bRC->bitsPerFrame;
    bRC->actualBufferFullness = bRC->CurrentBufferFullness;
    return AVCE_OK;
  }
  
  if(checkFrameSkip(bRC,texbits+headerbits,psnrY) == AVCE_FRAME_SKIPPED)
  {
    if(bRC->frameSkipEnabled == 1 || bRC->frameSkipEnabled == 2)
      return AVCE_FRAME_SKIPPED;
    else if(bRC->frameSkipEnabled == 0)
    {
      bRC->stat_NumberofSkips--;
      bRC->numConsecutiveSkips--;
      bRC->bitDifference = bRC->bitDifference+bRC->bitsPerFrame+(bRC->bitsPerFrame-texbits+headerbits);
      return AVCE_OK;
    }
  } 
  else if(bRC->CurrentBufferFullness + texbits + headerbits - bRC->bitsPerFrame < 0)
  {
    //Filler Data SEI will be sent at a higher layer
  }
  
  bRC->numConsecutiveSkips = 0;  
  if(bRC->numFrms > 0)
    bRC->PictureIndex = MIN(bRC->numFrms,bRC->PictureIndex+1);
  else
    bRC->PictureIndex++;

  bRC->PPictureIndexinGOP++;
  if(!(bRC->ignoreIDR && img_type == SLICE_I))
    bRC->bitDifference += (texbits+headerbits-bRC->bitsPerFrame);
  bRC->TotalBits += (texbits+headerbits);

  /*
   * Regular Rate Control, with RD Model and floating point arithmetic
   */
  if(img_type ==SLICE_P){
    if( ((bRC->PictureIndex % bRC->BIT_ADJUST_FREQUENCY) == 0) && (bRC->PictureIndex > 0))
    {
      if(bRC->numFrms>0)
      {
        //Number of frames to code is known
#ifdef STRICT_FILE_SIZE_CONTROL
        if(bRC->numFrms - bRC->PictureIndex < 30)
          bRC->strictControlFlag = 1;

        bRC->bitsPerPFrame = bRC->bitsPerFrame - (bRC->bitDifference)/(MIN(bRC->BIT_ADJUST_WINDOW,bRC->numFrms - bRC->PictureIndex+1)) ;
        bRC->bitsPerPFrame = (int)((bRC->bitsPerPFrame)*(bRC->numNonref+1)*1.0/(1+0.5*bRC->numNonref));
        
#else            
        bRC->bitsPerPFrame = bRC->bitsPerFrame - (bRC->bitDifference)/(bRC->BIT_ADJUST_WINDOW) ;
        bRC->bitsPerPFrame = (int)(bRC->bitsPerPFrame)*(bRC->numNonref+1)*1.0/(1+0.5*bRC->numNonref);
#endif
      }
      else          
      {
        bRC->bitsPerPFrame = bRC->bitsPerFrame - (bRC->bitDifference)/(bRC->BIT_ADJUST_WINDOW);  
        bRC->bitsPerPFrame = (int)((bRC->bitsPerPFrame)*(bRC->numNonref+1)*1.0/(1+0.5*bRC->numNonref));
      }
      
      if(bRC->bitsPerPFrame < bRC->bitsPerFrame)
        bRC->bitsPerPFrame = (int)(MAX(bRC->bitsPerPFrame,bRC->bitsPerFrame/2.0));        
    }
  }
  else if(img_type == SLICE_I)
  {
    bRC->bitsPerPFrame = bRC->bitsPerFrame - (bRC->bitDifference)/(MAX(15,bRC->GOPSize));  
    bRC->bitsPerPFrame = (int)((bRC->bitsPerPFrame)*(bRC->numNonref+1)*1.0/(1+0.5*bRC->numNonref));
    
    if(bRC->bitsPerPFrame < bRC->bitsPerFrame)
      bRC->bitsPerPFrame = (int)(MAX(bRC->bitsPerPFrame,bRC->bitsPerFrame/2.0));              
  }
  
  if(bRC->PPictureIndexinGOP >= 2)
    bRC->use_sh_RD_Model= 1;
  
  if(bRC->PictureIndex>= 3 ||bRC->PPictureIndexinGOP >= 2)
  {
    bRC->use_lt_RD_Model= 1;
  }
  
#ifdef USE_SPP
  if(bRC->SPPPictureCounter == 0)
    bRC->SPPPictureCounter = SPP_PICTURE_FREQ;
#endif
  
  picqstep=QP2Qstep((int)floor(bRC->averageQPforFrame));
  
  if(bRC->bufferStall)
  {
    //    if(!(img_type == SLICE_I && bRC->ignoreIDR == 1))
    bRC->CurrentBufferFullness += texbits + headerbits ;
    
    if(bRC->CurrentBufferFullness > bRC->TargetBufferLevel)
    {
      bRC->playingStartFrame = bRC->PictureIndex;
      bRC->CurrentBufferFullness -= bRC->bitsPerFrame;
      bRC->bufferStall = 0;    
      
    }
  }
  else
  {
    //    if(!(img_type == SLICE_I && bRC->ignoreIDR == 1))
    bRC->CurrentBufferFullness += texbits + headerbits - bRC->bitsPerFrame ;
  }
  
  bRC->actualBufferFullness = bRC->CurrentBufferFullness;
  bRC->CurrentBufferFullness = MIN(bRC->BufferSize,MAX(bRC->CurrentBufferFullness,0)); //Overflow and Underflow handled elsewhere
  bRC->actualBufferFullness = MIN(bRC->realBufferSize,MAX(bRC->actualBufferFullness,0)); //Overflow and Underflow handled elsewhere
  
  for(i=MAX_LT_RD_WINDOW_SIZE-1;i>0;i--)
    bRC->BufferFullnessArray[i]  = bRC->BufferFullnessArray[i-1];
  
  bRC->BufferFullnessArray[0] = bRC->CurrentBufferFullness;
  
  //Update the Model Parameters
  for(i=0;i<bRC->TotalNumberofMB;i++)
  {
    bRC->prevFrame_MBsad[i]=bRC->currentFrame_MBsad[i];
    bRC->prevFrame_MBQp[i]=bRC->currentFrame_MBQp[i];
    bRC->prevFrame_MBtexbits[i]=bRC->currentFrame_MBtexbits[i];
    bRC->prevFrame_MBheaderbits[i]=bRC->currentFrame_MBheaderbits[i];      
  }
  
  for(i=MAX_LT_RD_WINDOW_SIZE-1;i>0;i--)
    bRC->framePSNR[i] = bRC->framePSNR[i-1];
  
  bRC->framePSNR[i] = psnrY;
  
  if(img_type == SLICE_I)
  {
    if(bRC->scut != 1)
    {  
      //Due to GOP start
      if(bRC->GOPSize > 1)
      {
        bRC->bitsPerPFrame = bRC->bitsPerFrame - (texbits+headerbits - bRC->bitsPerPFrame) / (bRC->GOPSize - 1)  ;
        
        if(bRC->numFrms>0)
          //Number of frames to code is known
          bRC->bitsPerPFrame -= (bRC->bitDifference-texbits-headerbits+bRC->bitsPerFrame)/(bRC->numFrms - bRC->PictureIndex + 1) ;
        else
          bRC->bitsPerPFrame -= (bRC->bitDifference-texbits-headerbits+bRC->bitsPerFrame)/(100) ;
      }
    }
    else
    {      
      //Due to Scene cut
      if(bRC->GOPSize > 1)
      {
        //Compensate the additional I frame over the course of 30 frames
        bRC->bitsPerPFrame = bRC->bitsPerFrame - (texbits+headerbits - bRC->bitsPerPFrame) / (30)  ;
        
        if(bRC->numFrms>0)
          //Number of frames to code is known
          bRC->bitsPerPFrame -= (bRC->bitDifference-texbits-headerbits+bRC->bitsPerFrame)/(bRC->numFrms - bRC->PictureIndex + 1) ;
        else
          bRC->bitsPerPFrame -= (bRC->bitDifference-texbits-headerbits+bRC->bitsPerFrame)/(100) ;      
      }
    }
  }
  else if(img_type == SLICE_P)
  {
#ifdef USE_SPP
    bRC->SPPPictureCounter--;
#endif
    //Update the Bit, MAD and RD Arrays
    for(i=MAX_RD_WINDOW_SIZE-1;i>0;i--)
    {
      bRC->rdModel_QP[i]      = bRC->rdModel_QP[i-1];
      if(texbits > 0 && headerbits > 0)
      {
        bRC->rdModel_TextureBits[i]  = bRC->rdModel_TextureBits[i-1];
        bRC->rdModel_HeaderBits[i]  = bRC->rdModel_HeaderBits[i-1];
        bRC->rdModel_PictureMAD[i]  = bRC->rdModel_PictureMAD[i-1];
        bRC->rdModel_Qstep[i]      = bRC->rdModel_Qstep[i-1];
      }
    }
    
    for(i=MAX_LT_RD_WINDOW_SIZE-1;i>0;i--)
    {
      if(texbits > 0 && headerbits > 0)
      {
        bRC->lt_rdModel_TextureBits[i]  = bRC->lt_rdModel_TextureBits[i-1];
        bRC->lt_rdModel_HeaderBits[i]  = bRC->lt_rdModel_HeaderBits[i-1];
        bRC->lt_rdModel_PictureMAD[i]  = bRC->lt_rdModel_PictureMAD[i-1];
        bRC->lt_rdModel_Qstep[i]      = bRC->lt_rdModel_Qstep[i-1];
        
      }
      
    }
    if(texbits > 0 || headerbits > 0)
    {
      
      if(headerbits > 0)
      {
        bRC->rdModel_HeaderBits[0]  = headerbits;
        bRC->lt_rdModel_HeaderBits[0]  = headerbits;
      }
      if(texbits > 0)
      {
        bRC->rdModel_TextureBits[0]  = texbits;
        bRC->lt_rdModel_TextureBits[0]  = texbits;
      }
      if(ComputePictureMAD(bRC) > 0)
      {
        bRC->rdModel_PictureMAD[0]  = ComputePictureMAD(bRC);
        bRC->lt_rdModel_PictureMAD[0]  = bRC->rdModel_PictureMAD[0];
      }
      
      bRC->rdModel_Qstep[0]      = picqstep;
      bRC->lt_rdModel_Qstep[0]      = picqstep;
      
      bRC->rdModel_QP[0]      = bRC->averageQPforFrame;
    }
    MADUpdateFlag=1;
  }
  
  if(img_type == SLICE_P)
  {
    //Compute the size of windows
    if(bRC->rdModel_PictureMAD[0] == 0 && bRC->rdModel_PictureMAD[1] == 0)
      tempRDSize = bRC->rdModel_windowSize;
    else
      tempRDSize = (bRC->rdModel_PictureMAD[0]>bRC->rdModel_PictureMAD[1])?(int)(bRC->rdModel_PictureMAD[1]*MAX_RD_WINDOW_SIZE/bRC->rdModel_PictureMAD[0])
      :(int)(bRC->rdModel_PictureMAD[0]*MAX_RD_WINDOW_SIZE/bRC->rdModel_PictureMAD[1]);

    tempRDSize=MAX(tempRDSize, 1);
    tempRDSize=MIN(tempRDSize,bRC->rdModel_windowSize+1);
    tempRDSize=MIN(tempRDSize,MAX_RD_WINDOW_SIZE);
    
    if(bRC->lt_rdModel_PictureMAD[0] == 0 && bRC->lt_rdModel_PictureMAD[1] == 0)
      lt_tempRDSize = bRC->lt_rdModel_windowSize;
    else
      lt_tempRDSize = (bRC->lt_rdModel_PictureMAD[0]>bRC->lt_rdModel_PictureMAD[1])?(int)(bRC->lt_rdModel_PictureMAD[1]*MAX_LT_RD_WINDOW_SIZE/bRC->lt_rdModel_PictureMAD[0])
      :(int)(bRC->lt_rdModel_PictureMAD[0]*MAX_LT_RD_WINDOW_SIZE/bRC->lt_rdModel_PictureMAD[1]);
    lt_tempRDSize=MAX(lt_tempRDSize, 1);
    lt_tempRDSize=MIN(lt_tempRDSize,bRC->lt_rdModel_windowSize+1);
    lt_tempRDSize=MIN(lt_tempRDSize,MAX_LT_RD_WINDOW_SIZE);
    
    bRC->rdModel_windowSize=tempRDSize;
    bRC->lt_rdModel_windowSize=lt_tempRDSize;
    
    //Update the RD Model
    for (i = 0; i < MAX_RD_WINDOW_SIZE; i++) 
      bRC->rdModel_Rejected[i] = 0;
    
    // initial RD model estimator
    RDModelEstimator (bRC,img_type);
    
    // remove outlier 
    for (i = 0; i < (int) tempRDSize; i++) 
    {
      error[i] = 1.0f*bRC->rdModel_X1 /( bRC->rdModel_Qstep[i]) + 1.0f*bRC->rdModel_X2 /( bRC->rdModel_Qstep[i] * bRC->rdModel_Qstep[i]) - bRC->rdModel_TextureBits[i]*1.0f/bRC->rdModel_PictureMAD[i];
      std += error[i] * error[i]; 
    }
    threshold = (float)((tempRDSize == 2) ? 0 : sqrt (std / tempRDSize));
    
    for (i = 0; i < (int) tempRDSize; i++)
    {
      if (fabs(error[i]) > threshold)
        bRC->rdModel_Rejected[i] = 1;
    }
    // always include the last data point
    bRC->rdModel_Rejected[0] = 0;
    
    // second RD model estimator
    RDModelEstimator (bRC, img_type);
    
    //************** Update the long term RD Model *******************
    //Update the RD Model
    for (i = 0; i < MAX_LT_RD_WINDOW_SIZE; i++) 
      bRC->lt_rdModel_Rejected[i] = 0;
    
    // initial RD model estimator
    lt_RDModelEstimator (bRC,img_type);
    
    // remove outlier 
    for (i = 0; i < (int) lt_tempRDSize; i++) 
    {
      lt_error[i] = bRC->lt_rdModel_X1 /( bRC->lt_rdModel_Qstep[i]) + bRC->lt_rdModel_X2 /( bRC->lt_rdModel_Qstep[i] * bRC->lt_rdModel_Qstep[i]) - bRC->lt_rdModel_TextureBits[i]*1.0f/bRC->lt_rdModel_PictureMAD[i];
      lt_std += lt_error[i] * lt_error[i]; 
    }
    threshold = (lt_tempRDSize == 2) ? 0 :(float) sqrt (lt_std / lt_tempRDSize);
    
    for (i = 0; i < (int) lt_tempRDSize; i++)
    {
      if (fabs(lt_error[i]) > threshold)
        bRC->lt_rdModel_Rejected[i] = 1;
    }
    // always include the last data point
    bRC->lt_rdModel_Rejected[0] = 0;
    
    // second RD model estimator
    lt_RDModelEstimator (bRC, img_type);
  }
  
  hdrSize=bRC->lt_rdModel_windowSize;
  hdrSize=MIN(hdrSize,MAX_LT_RD_WINDOW_SIZE);
  
  if(bRC->use_lt_RD_Model== 1 && img_type == SLICE_P)
  {    
    avgHeaderBits = getAverageHeaderBits(bRC,hdrSize,1);
    avgTextureBits = getAverageTextureBits(bRC,hdrSize,1);
    avgMAD = getAverageMAD(bRC,hdrSize,1);
    tex = bRC->bitsPerPFrame*avgTextureBits/(avgTextureBits+avgHeaderBits);
    if(avgTextureBits > 0 )
    {      
      Qaver =  (int)(getQP_UsingRDModel(tex, avgMAD, bRC->lt_rdModel_X1, bRC->lt_rdModel_X2));
    }
    else
      Qaver = (int) bRC->averageQPforFrame-1;    
    
  }
  else
    Qaver = (int) bRC->averageQPforFrame;
  
  if(bRC->GOPSize == 0)
  {
    //No GOPs
    if(bRC->PictureIndex%bRC->LT_WINDOW_QP_UPDATE_FREQ == 0 || bRC->PictureIndex<15 || bRC->PPictureIndexinGOP == 0)
    {
      if(bRC->PictureIndex > 3)
      {
        if( avgHeaderBits<bRC->bitsPerPFrame )
        {
          if(Qaver > bRC->QP_LW)
            bRC->QP_LW = MIN(Qaver, bRC->QP_LW+2);
          else 
            bRC->QP_LW = MAX(Qaver, bRC->QP_LW-2);
        }
        else
          bRC->QP_LW++;
      }
      else if(img_type == SLICE_P)
        bRC->QP_LW = Qaver;
      
    }
  }
  else if(bRC->PictureIndex%bRC->GOPSize == 0 || bRC->PictureIndex%bRC->LT_WINDOW_QP_UPDATE_FREQ==0 || bRC->PictureIndex<15 || bRC->PPictureIndexinGOP == 0 || bRC->use_lt_RD_Model == 0)
  {
    if(bRC->PictureIndex > 3)
    {
      if( avgHeaderBits<bRC->bitsPerPFrame )
      {
        if(Qaver > bRC->QP_LW)
          bRC->QP_LW = MIN(Qaver, bRC->QP_LW+2);
        else 
          bRC->QP_LW = MAX(Qaver, bRC->QP_LW-2);
      }
      else
        bRC->QP_LW++;
    }
    
    else if(img_type == SLICE_P)
      bRC->QP_LW = Qaver;
  }
  
  bRC->QP_LW = MIN(50,MAX(1,bRC->QP_LW));

  return AVCE_OK;    
}


//compute a  quantization parameter for each frame
int rc_getFrameQP(rateCtrl_s *bRC, int img_type)
{
  
  /*frame layer rate control*/
  if(img_type==SLICE_I && bRC->PictureIndex == 0)
  {
    bRC->averageQPforFrame =  bRC->InitialQP;
    
    bRC->frameReturnedQP = (int)bRC->InitialQP;
    return bRC->frameReturnedQP;
  }
  else if(img_type == SLICE_I)
    return bRC->frameReturnedQP = bRC->frameComputedQP;
  else if((img_type==SLICE_P)&&(bRC->PPictureIndexinGOP==0))
  {
#ifdef USE_SPP
    if(bRC->SPPPictureCounter == 0)
      return bRC->frameReturnedQP = bRC->SPPframeComputedQP;
    else
#endif
      if(bRC->BufferSize < bRC->bit_rate)
      {
       bRC->frameComputedQP = bRC->frameReturnedQP = clip(MIN_QP, MAX_QP, (int)(bRC->averageQPforFrame)+2);
       return bRC->frameComputedQP;
      }
      else
      {
        if(bRC->use_lt_RD_Model == 0 && bRC->use_sh_RD_Model == 0)
        {
          bRC->frameComputedQP = bRC->frameReturnedQP = clip(MIN_QP, MAX_QP,(bRC->averageQPforFrame));
          return bRC->frameComputedQP;
        }

          
        else
          return bRC->frameReturnedQP=bRC->frameComputedQP;
      }
      
  }  
  else
    
#ifdef USE_SPP
    if(bRC->SPPPictureCounter == 0)
      return bRC->frameReturnedQP = bRC->SPPframeComputedQP;
    else
#endif
      return bRC->frameReturnedQP = bRC->frameComputedQP;
}


int ComputePictureMAD(rateCtrl_s *bRC)
{
  int32 TotalMAD=0;
  int i; 
  

  for(i=0;i<bRC->TotalNumberofMB;i++)
    TotalMAD += (bRC->MSEofMB[i]);
  
  return TotalMAD/(bRC->TotalNumberofMB);
}


int Qstep2QP( float Qstep )
{
  int q_per = 0, q_rem = 0;
  

  if( Qstep < QP2Qstep(0))
    return 0;
  else if (Qstep > QP2Qstep(51) )
    return 51;
  
  while( Qstep > QP2Qstep(5) )
  {
    Qstep /= 2;
    q_per += 1;
  }
  
  if (Qstep <= (0.625+0.6875)/2) 
  {
    Qstep = 0.625;
    q_rem = 0;
  }
  else if (Qstep <= (0.6875+0.8125)/2)
  {
    Qstep = 0.6875;
    q_rem = 1;
  }
  else if (Qstep <= (0.8125+0.875)/2)
  {
    Qstep = 0.8125;
    q_rem = 2;
  }
  else if (Qstep <= (0.875+1.0)/2)
  {
    Qstep = 0.875;
    q_rem = 3;
  }
  else if (Qstep <= (1.0+1.125)/2)
  {
    Qstep = 1.0;  
    q_rem = 4;
  }
  else 
  {
    Qstep = 1.125;
    q_rem = 5;
  }
  
  return (q_per * 6 + q_rem);
}


float QP2Qstep( int QP )
{
  int i; 
  float Qstep;
  static const float QP2QSTEP[6] = { 0.625, 0.6875, 0.8125, 0.875, 1.0, 1.125 };
  

  Qstep = QP2QSTEP[QP % 6];
  for( i=0; i<(QP/6); i++)
    Qstep *= 2;
  
  return Qstep;
}


void RDModelEstimator (rateCtrl_s *bRC, int img_type)
{
  int n_windowSize = bRC->rdModel_windowSize;
  int n_realSize = n_windowSize;
  int i;
  float oneSampleQ=0.0;
  float a00 = 0.0f, a01 = 0.0f, a10 = 0.0f, a11 = 0.0f, b0 = 0.0f, b1 = 0.0f;
  float MatrixValue;
  Boolean estimateX2 = 0;
  

  if(img_type == SLICE_I)
    return;
  
  for (i = 0; i < n_windowSize; i++) {// find the number of samples which are not rejected
    if (bRC->rdModel_Rejected[i])
      n_realSize--;
  }
  
  // default RD model estimation results
  bRC->rdModel_X1 = bRC->rdModel_X2= 0.0f;
  
  for (i = 0; i < n_windowSize; i++)  {
    if (!bRC->rdModel_Rejected[i])
      oneSampleQ = bRC->rdModel_Qstep[i];
  }
  
  for (i = 0; i < n_windowSize; i++)  {// if all non-rejected Q are the same, take 1st order model
    if ((bRC->rdModel_Qstep[i] != oneSampleQ) && !bRC->rdModel_Rejected[i])
      estimateX2 = 1;
    if (!bRC->rdModel_Rejected[i])
      bRC->rdModel_X1 += (bRC->rdModel_Qstep[i] * bRC->rdModel_TextureBits[i]*1.0f/bRC->rdModel_PictureMAD[i]) / n_realSize;
    
  }
  
  // take 2nd order model to estimate X1 and X2
  if ((n_realSize >= 1) && estimateX2) 
  {
    for (i = 0; i < n_windowSize; i++) 
    {
      if (!bRC->rdModel_Rejected[i])
      {
        a00 = a00 + 1.0f;
        a01 += 1.0f / bRC->rdModel_Qstep[i];
        a10 = a01;
        a11 += 1.0f / (bRC->rdModel_Qstep[i] * bRC->rdModel_Qstep[i]);
        b0 += (bRC->rdModel_Qstep[i] * bRC->rdModel_TextureBits[i]*1.0f/bRC->rdModel_PictureMAD[i]);
        b1 += bRC->rdModel_TextureBits[i]*1.0f/bRC->rdModel_PictureMAD[i];        
      }
    }
    
    // solve the equation of AX = B
    MatrixValue=a00*a11-a01*a10;
    if(fabs(MatrixValue)>0.000001f)
    {
      bRC->rdModel_X1 = (b0*a11-b1*a01)/MatrixValue;
      bRC->rdModel_X2 = (b1*a00-b0*a10)/MatrixValue;
    } 
    else
    {
      bRC->rdModel_X1 = b0/a00;
      bRC->rdModel_X2 = 0.0f;
    }
  }  
}


void lt_RDModelEstimator(rateCtrl_s *bRC, int img_type)
{
  int n_windowSize = bRC->lt_rdModel_windowSize;
  int n_realSize = n_windowSize;
  int i;
  float oneSampleQ=0.0;
  float a00 = 0.0f, a01 = 0.0f, a10 = 0.0f, a11 = 0.0f, b0 = 0.0f, b1 = 0.0f;
  float MatrixValue;
  Boolean estimateX2 = 0;
  

  if(img_type == SLICE_I)
    return;
  
  for (i = 0; i < n_windowSize; i++) {// find the number of samples which are not rejected
    if (bRC->lt_rdModel_Rejected[i])
      n_realSize--;
  }
  
  // default RD model estimation results
  bRC->lt_rdModel_X1 = bRC->lt_rdModel_X2= 0.0f;
  
  for (i = 0; i < n_windowSize; i++)  {
    if (!bRC->lt_rdModel_Rejected[i])
      oneSampleQ = bRC->lt_rdModel_Qstep[i];
  }
  for (i = 0; i < n_windowSize; i++)  {// if all non-rejected Q are the same, take 1st order model
    if ((bRC->lt_rdModel_Qstep[i] != oneSampleQ) && !bRC->lt_rdModel_Rejected[i])
      estimateX2 = 1;
    if (!bRC->lt_rdModel_Rejected[i])
      bRC->lt_rdModel_X1 += (bRC->lt_rdModel_Qstep[i] * bRC->lt_rdModel_TextureBits[i]*1.0f/bRC->lt_rdModel_PictureMAD[i]) / n_realSize;
    
  }
  
  // take 2nd order model to estimate X1 and X2
  if ((n_realSize >= 1) && estimateX2) 
  {
    for (i = 0; i < n_windowSize; i++) 
    {
      if (!bRC->lt_rdModel_Rejected[i])
      {
        a00 = a00 + 1.0f;
        a01 += 1.0f / bRC->lt_rdModel_Qstep[i];
        a10 = a01;
        a11 += 1.0f / (bRC->lt_rdModel_Qstep[i] * bRC->lt_rdModel_Qstep[i]);
        b0 += (bRC->lt_rdModel_Qstep[i] * bRC->lt_rdModel_TextureBits[i]*1.0f/bRC->lt_rdModel_PictureMAD[i]);
        b1 += bRC->lt_rdModel_TextureBits[i]*1.0f/bRC->lt_rdModel_PictureMAD[i];
        
      }
    }
    
    // solve the equation of AX = B
    MatrixValue=a00*a11-a01*a10;
    if(fabs(MatrixValue)>0.000001f)
    {
      bRC->lt_rdModel_X1 = (b0*a11-b1*a01)/MatrixValue;
      bRC->lt_rdModel_X2 = (b1*a00-b0*a10)/MatrixValue;
    } 
    else
    {
      bRC->lt_rdModel_X1 = b0/a00;
      bRC->lt_rdModel_X2 = 0.0f;
    }
  }  
}


int getQP_UsingRDModel(int targetBits, int mad, float X1, float X2)
{
  float deltaTemp;
  float Qstep;
  int q;

  
  deltaTemp = mad * X1 * mad * X1  + 4 * X2* mad * targetBits;
  if ((X2 == 0.0) || (deltaTemp < 0) || ((sqrt (deltaTemp) - X1 * mad) <= 0.0)) // fall back 1st order mode
    Qstep = (float) (X1 * mad / (float) targetBits);
  else // 2nd order mode
    Qstep = (float) ((2 * X2 * mad) / (sqrt (deltaTemp) - X1 * mad));
  q=Qstep2QP(Qstep);
  return q;    
}


int getAverageHeaderBits(rateCtrl_s *bRC, int windowSize, int lt) 
{
  int i;
  int headerbits=0;
  int  *parr = bRC->rdModel_HeaderBits;
  
  
  if(lt == 1)
    parr = bRC->lt_rdModel_HeaderBits;
  
  for(i=0;i<windowSize;i++)
    headerbits+=parr[i];
  if(windowSize>0)
    headerbits=headerbits/windowSize;
  else
    headerbits=0;
  return headerbits;
}


int getAverageTextureBits(rateCtrl_s *bRC, int windowSize,int lt) 
{
  int i;
  int texbits=0;
  int *parr = bRC->rdModel_TextureBits;
  
  
  if(lt == 1)
    parr = bRC->lt_rdModel_TextureBits;
  
  for(i=0;i<windowSize;i++)
    texbits+=parr[i];
  if(windowSize>0)
    texbits=texbits/windowSize;
  else
    texbits=0;
  return texbits;
}


int getAverageMAD(rateCtrl_s *bRC, int windowSize,int lt) 
{
  int i;
  int mad=0;
  int *parr = bRC->rdModel_PictureMAD;
  int *prejected = bRC->rdModel_Rejected;
  int n_realSize = windowSize;
  
  
  if(lt == 1)
  {
    prejected = bRC->lt_rdModel_Rejected;
    parr = bRC->lt_rdModel_PictureMAD;
  }
  
  for (i = 0; i < windowSize; i++) {// find the number of samples which are not rejected
    if (prejected[i])
      n_realSize--;
  }
  
  for(i=0;i<windowSize;i++)
  {
    if (!prejected[i])
      mad+=parr[i];
  }
  
  if(n_realSize>0)
    mad=mad/n_realSize;
  else
    mad=0;
  return mad;
}


void createBitEnvelope(rateCtrl_s *bRC)
{

  //Creates the upper and lower limits using PI Buffer Regulator
  float Et = (bRC->TargetBufferLevel - bRC->CurrentBufferFullness)*1.0f / bRC->TargetBufferLevel; //Proportional
  float Etau=0;
  float PIError;
  int i;

  
  bRC->upperFrameLimit = (int)(bRC->bitsPerPFrame*bRC->UPPER_LIMIT_MULTIPLE);
  bRC->lowerFrameLimit = (int)(bRC->bitsPerPFrame/bRC->LOWER_LIMIT_MULTIPLE);
  
  if(bRC->BufferSize > bRC->bit_rate)
  {
    if(bRC->img_type == SLICE_I)
    {
      
      bRC->upperFrameLimit = (bRC->bitsPerFrame*bRC->I_P_RATIO);
      bRC->lowerFrameLimit = (bRC->upperFrameLimit/2);
      return;
    }
    
    if(!bRC->bufferStall )
    {
      for(i=0;i<MIN(30,(bRC->PictureIndex-bRC->playingStartFrame));i++)
      {
        if(bRC->BufferFullnessArray[i]>0)
          Etau+=(bRC->TargetBufferLevel - bRC->BufferFullnessArray[i])*1.0f / bRC->TargetBufferLevel;
      }
      //Then create upper and lower limits otherwise do not touch
      PIError = Kp*(Et+Etau*Ki);  
      if(PIError<0)
      {
        bRC->upperFrameLimit = (int)((1+MAX(-0.5f,PIError)) * bRC->bitsPerPFrame*bRC->UPPER_LIMIT_MULTIPLE);
        //bRC->upperFrameLimit = MIN(bRC->BufferSize - bRC->CurrentBufferFullness , bRC->upperFrameLimit);
        bRC->upperFrameLimit = MIN(bRC->realBufferSize - bRC->CurrentBufferFullness , bRC->upperFrameLimit);
      }
      else
      {
        if(bRC->nalRefIdc == 1)
        {
          bRC->lowerFrameLimit = (int)((1+MIN(5,PIError*8)) * bRC->bitsPerPFrame/bRC->LOWER_LIMIT_MULTIPLE);
          bRC->lowerFrameLimit = MAX( (2*bRC->bitsPerPFrame - bRC->CurrentBufferFullness) , bRC->lowerFrameLimit);
        }
        else
          bRC->lowerFrameLimit = bRC->bitsPerPFrame - bRC->CurrentBufferFullness;
      }
      //Check if we are approaching to a start of GOP
      if( bRC->GOPSize - (bRC->PictureIndex%bRC->GOPSize) <= 5 )
      {
        //Check the Buffer size, change the envelope accordingly
        if( (bRC->BufferSize - bRC->CurrentBufferFullness) < bRC->bitsPerFrame * 5)
        {
          bRC->upperFrameLimit = (int)(1.1 * (bRC->CurrentBufferFullness - (bRC->BufferSize - bRC->bitsPerFrame*5))/(1.0*(bRC->GOPSize - (bRC->PictureIndex%bRC->GOPSize))));
        }
      }
    }
    else
    {
      
      bRC->upperFrameLimit = (int)(bRC->bitsPerPFrame*bRC->UPPER_LIMIT_MULTIPLE);
      bRC->lowerFrameLimit = (int)(bRC->bitsPerPFrame/bRC->LOWER_LIMIT_MULTIPLE);
      
      if(bRC->nalRefIdc == 0)
        bRC->lowerFrameLimit = bRC->bitsPerPFrame - bRC->CurrentBufferFullness;
    }
    
    /*if(bRC->upperFrameLimit < bRC->bitsPerFrame/LOWER_LIMIT_MULTIPLE)
    bRC->upperFrameLimit = (int)(bRC->bitsPerFrame/LOWER_LIMIT_MULTIPLE);
    if(bRC->lowerFrameLimit > bRC->bitsPerFrame*UPPER_LIMIT_MULTIPLE)
    bRC->upperFrameLimit = (int)(bRC->bitsPerFrame*UPPER_LIMIT_MULTIPLE);*/
    
    if(bRC->lowerFrameLimit < bRC->bitsPerFrame/bRC->LOWER_LIMIT_MULTIPLE)
      bRC->lowerFrameLimit = (int)(bRC->bitsPerFrame/bRC->LOWER_LIMIT_MULTIPLE);
    if(bRC->upperFrameLimit > bRC->bitsPerFrame*bRC->UPPER_LIMIT_MULTIPLE)
      bRC->upperFrameLimit = (int)(bRC->bitsPerFrame*bRC->UPPER_LIMIT_MULTIPLE);

    /*if(bRC->strictControlFlag == 1)
    {
      bRC->upperFrameLimit = bRC->bitsPerPFrame*1.2;
      bRC->lowerFrameLimit = bRC->bitsPerPFrame*0.8;
    } 
    */
  }
  else
  {    
    if(bRC->img_type == SLICE_I)
    {
      
      bRC->upperFrameLimit = (int)MAX(bRC->bitsPerFrame,MIN(bRC->BufferSize*0.95f-bRC->CurrentBufferFullness+bRC->bitsPerFrame, bRC->bitsPerFrame*bRC->I_P_RATIO));
      bRC->lowerFrameLimit = bRC->upperFrameLimit - bRC->bitsPerFrame;
      return;
    }
    
    bRC->centerFrameBits = bRC->bitsPerPFrame;
    
    if(bRC->CurrentBufferFullness < 0)
    {
      bRC->upperFrameLimit = (int)(bRC->bitsPerFrame*bRC->UPPER_LIMIT_MULTIPLE);
      bRC->lowerFrameLimit = (int)(bRC->bitsPerFrame*3)>>1;
      bRC->centerFrameBits = bRC->lowerFrameLimit;
      
    }
    else
    {     
      if(bRC->CurrentBufferFullness >= bRC->BufferSize/2)
      {       
        bRC->upperFrameLimit = (int)(bRC->bitsPerPFrame * (bRC->UPPER_LIMIT_MULTIPLE - ((bRC->UPPER_LIMIT_MULTIPLE - 1)*(bRC->CurrentBufferFullness - bRC->BufferSize/2)*100/bRC->BufferSize))/100);
        bRC->centerFrameBits = MIN(bRC->upperFrameLimit,bRC->bitsPerPFrame);
        bRC->lowerFrameLimit = (int)(bRC->centerFrameBits / bRC->LOWER_LIMIT_MULTIPLE);
      }
      else
      {
        bRC->lowerFrameLimit = (int)(bRC->bitsPerFrame * ((200-200/bRC->LOWER_LIMIT_MULTIPLE)*bRC->CurrentBufferFullness)/bRC->BufferSize)/100; 
        bRC->centerFrameBits = MIN(bRC->upperFrameLimit,bRC->bitsPerPFrame);
        bRC->upperFrameLimit = (int)(bRC->centerFrameBits * bRC->UPPER_LIMIT_MULTIPLE);
      }  
    }
    
    if(bRC->CurrentBufferFullness + bRC->upperFrameLimit - bRC->bitsPerFrame > bRC->BufferSize - bRC->bitsPerFrame/5)
    {
      bRC->upperFrameLimit = -bRC->bitsPerFrame/5 + bRC->BufferSize - bRC->CurrentBufferFullness + bRC->bitsPerFrame;
      bRC->lowerFrameLimit = MAX(bRC->bitsPerFrame/4, bRC->upperFrameLimit - bRC->bitsPerFrame);
      bRC->centerFrameBits = (bRC->upperFrameLimit + bRC->lowerFrameLimit)/2;
    }
    
    if(bRC->CurrentBufferFullness + bRC->lowerFrameLimit - bRC->bitsPerFrame < bRC->bitsPerFrame/5)
    {
      bRC->lowerFrameLimit = bRC->bitsPerFrame/5 + bRC->bitsPerFrame  - bRC->CurrentBufferFullness;
      bRC->upperFrameLimit = bRC->lowerFrameLimit + bRC->bitsPerFrame;
      bRC->centerFrameBits = (bRC->upperFrameLimit + bRC->lowerFrameLimit)/2;
    }
    
    if(bRC->lowerFrameLimit < bRC->bitsPerFrame/bRC->LOWER_LIMIT_MULTIPLE)
    {
      bRC->lowerFrameLimit = (int)(bRC->bitsPerFrame/bRC->LOWER_LIMIT_MULTIPLE);
      bRC->upperFrameLimit = bRC->lowerFrameLimit + bRC->bitsPerFrame/2;
      bRC->centerFrameBits = bRC->lowerFrameLimit + bRC->bitsPerFrame/4;
    }
    
    if(bRC->upperFrameLimit > bRC->bitsPerFrame*bRC->UPPER_LIMIT_MULTIPLE)
    {
      bRC->upperFrameLimit = (int)(bRC->bitsPerFrame*bRC->UPPER_LIMIT_MULTIPLE);
      bRC->lowerFrameLimit = bRC->upperFrameLimit - bRC->bitsPerFrame/2;
      bRC->centerFrameBits = bRC->upperFrameLimit - bRC->bitsPerFrame/4;
    }
  }
}  


//Fills the necessary HRD parameter syntaxes that should be put in the bitstream
void fillHRDParameters(rateCtrl_s *bRC, hrd_parameters_s *hrd)
{
  int i;

  
  hrd->cpb_cnt_minus1 = 0;
  //Calculate the bit_rate_scale and bit_rate_value
  for(i=1 ; ( ((bRC->bit_rate>>i) & (0x00000001)) != 0x00000001) ;i++);
  //i holds the number of zeros
  hrd->bit_rate_scale = MAX(0,i-6);
  hrd->bit_rate_value_minus1[0] = (int)(bRC->bit_rate >> i) - 1;
  
  //Calculate the bit_rate_scale and bit_rate_value
  for(i=1 ; ( ((bRC->BufferSize>>i) & (0x00000001)) != 0x00000001) ;i++);
  hrd->cpb_size_scale = MAX(0,i-4);
  hrd->cpb_size_value_minus1[0] = (int)(bRC->bit_rate >> (i-1)  ) - 1;
  
  hrd->cbr_flag[0] = 0; 
  hrd->initial_cpb_removal_delay_length_minus1 = 19; 
  hrd->cpb_removal_delay_length_minus1 = 19;
  hrd->dpb_output_delay_length_minus1 = 19;
  hrd->time_offset_length = 0;
}


void fillBufferingPeriodSEI(rateCtrl_s *bRC)
{
  buffering_period_SEI_s  *bufperiodSEI = &bRC->bufperiodSEI;
  bufperiodSEI->initial_cpb_removal_delay = (unsigned int)(bRC->TargetBufferLevel* (90000*1.0/ bRC->bit_rate)) ;
  bufperiodSEI->initial_cpb_removal_delay_offset =   
    bufperiodSEI->seq_parameter_set_id = 0;
}


void fillPictureTimingSEI(rateCtrl_s *bRC)
{
  picture_timing_SEI_s *pic_timing_SEI = &bRC->picture_timing_SEI;
  if(bRC->PictureIndex == 0)
  {
    pic_timing_SEI->cpb_removal_delay = 0;
    pic_timing_SEI->dpb_output_delay = 0;
  }
  else
  {
    pic_timing_SEI->cpb_removal_delay = bRC->PictureIndex;
    pic_timing_SEI->dpb_output_delay = bRC->PictureIndex;
  }
}


#ifdef RC_DEBUG
void rc_printDebug(rateCtrl_s *bRC,statSlice_s *frmStat)
{
  
  fprintf(bRC->rcdebug,"%6d\t%6d\t%6d\t  %6d\t %6d\t %6d\t %6d\t %6d\t %6d\t %.2f\t %6d\t %6d\t %6d\t%6d\t%6d\n",
    bRC->srcPicNum,
    bRC->PictureIndex,
    staGetTotalBits(frmStat),
    bRC->TargetBufferLevel,
    bRC->CurrentBufferFullness,
    bRC->frameReturnedQP,
    bRC->averageQPforFrame,
    bRC->QP_LW ,
    bRC->QP_SW,
    frmStat->psnrY,
    bRC->upperFrameLimit,
    bRC->lowerFrameLimit,
    bRC->nalRefIdc,
    bRC->bitsPerPFrame,
    bRC->rdModel_PictureMAD[0]
    );

}
#endif


void rc_update_bitrate(rateCtrl_s *bRC, int bitrate)
{
  int i;


  if( abs(bitrate - bRC->bit_rate)*1.0f/bRC->bit_rate > 0.1)
  {
    bRC->use_lt_RD_Model= 0;
    bRC->use_sh_RD_Model= 0;
    
    for(i=0;i<MAX_RD_WINDOW_SIZE;i++)
    {
      bRC->rdModel_QP[i]    = 0;
      bRC->rdModel_Qstep[i]    = 0;
      bRC->rdModel_PictureMAD[i]  = 0;
      bRC->rdModel_TextureBits[i]  = 0;
      bRC->rdModel_HeaderBits[i]  = 0;
    }
    bRC->rdModel_windowSize = 0; 
    for(i=0;i<MAX_LT_RD_WINDOW_SIZE;i++)
    {
      bRC->lt_rdModel_Qstep[i]      = 0;
      bRC->lt_rdModel_PictureMAD[i]  = 0;
      bRC->lt_rdModel_TextureBits[i]  = 0;
      bRC->lt_rdModel_HeaderBits[i]  = 0;  
    }
    bRC->lt_rdModel_windowSize = 0;
  }
  
  if(bitrate!=0)
  {
    bRC->bitsPerPFrame = (int)(bRC->bitsPerPFrame * (bitrate*1.0f/bRC->bit_rate));
    bRC->bitsPerFrame = (int)(bRC->bitsPerFrame * (bitrate*1.0f/bRC->bit_rate));
    bRC->BufferSize = (int)(bRC->BufferSize * (bitrate*1.0f / bRC->bit_rate));
    
    if(bRC->CurrentBufferFullness > bRC->BufferSize)
      //Assume the extra portion of the underlying data transfers to the Transport Buffer
      bRC->CurrentBufferFullness = bRC->BufferSize;
    
  }
  
  bRC->bit_rate = bitrate;
  bRC->TargetBufferLevel = bRC->BufferSize/2;
}


void rc_updateMB(rateCtrl_s *bRC, int texbits,int headerbits,int mb_minMSE, int mb_type, int mb_interMode,int mbNum)
{
  int totalMB=0,i=0;
  int tx_th = 5;


  bRC->MSEofMB[mbNum] = mb_minMSE>>6; //Convert SAD to MAD (with increased accuracy)
  bRC->currentFrameBits += (headerbits + texbits);
  bRC->currentFrame_MBheaderbits[mbNum] = headerbits;
  bRC->currentFrame_MBtexbits[mbNum] = texbits;
  
  if(mb_type == MBK_INTER && mb_interMode == MOT_COPY)
    bRC->numSkippedMBs++;
  
  if(mbNum == bRC->TotalNumberofMB-1)
  {
    
    bRC->averageQPforFrame = 0;
    
    for(i=0;i<bRC->TotalNumberofMB;i++)
    {
      if(bRC->currentFrame_MBtexbits[i]>tx_th)
      {
        bRC->averageQPforFrame+=bRC->currentFrame_MBQp[i];
        totalMB++;
      }
    }
    if(totalMB < bRC->TotalNumberofMB/4)
    {
      bRC->averageQPforFrame = 0;
      for(i=0;i<bRC->TotalNumberofMB;i++)
        bRC->averageQPforFrame+=bRC->currentFrame_MBQp[i];
      totalMB = bRC->TotalNumberofMB;
    }
    
    bRC->averageQPforFrame=bRC->averageQPforFrame/totalMB;
  }
  
}


int rc_getMBQP(rateCtrl_s *bRC, int sliceType,int mbNum)
{
  int i=0;
  int validQPs[51];
  int originalQP;
  int currentFrameGeneratedBits=0;
  int prevFrameGeneratedBits = 0,prevFrameBits;
  int upperlimit= bRC->upperFrameLimit;
  int lowerlimit= bRC->lowerFrameLimit;
  int currPredFrame;
  int QP_buffer;  
  int firstChangeChance = bRC->TotalNumberofMB/5;
  int lastMBIndex = 4*bRC->TotalNumberofMB/5;
  int qpUpdateThreshold; 
  int changeScore=0;
  int maxQP = MIN(50,bRC->frameReturnedQP+6);
  int minQP = MAX(2,bRC->frameReturnedQP-6);

  
  if(bRC->bit_rate == 0 || bRC->brcdisableMBLevel==1)
    return -1;
  
  //if((sliceType == SLICE_I && bRC->PictureIndex == 0) || ( (sliceType == SLICE_I && bRC->ignoreIDR)) )
  if((sliceType == SLICE_I && bRC->ignoreIDR)) 
    return bRC->frameReturnedQP;
  
  qpUpdateThreshold = bRC->TotalNumberofMB / 20;
  if(bRC->bit_rate < bRC->BufferSize*3)
  {
    if(mbNum > bRC->TotalNumberofMB*0.4)
      qpUpdateThreshold=qpUpdateThreshold/2;
    if(mbNum > bRC->TotalNumberofMB*0.7)
      qpUpdateThreshold=qpUpdateThreshold/2;
    if(mbNum > bRC->TotalNumberofMB*0.9)
      qpUpdateThreshold = 1;
  }
  
  if(mbNum == 0)
    originalQP = bRC->frameReturnedQP;
  else
    originalQP = bRC->currentFrame_MBQp[mbNum - 1];
  
  QP_buffer = originalQP;
  
  for(i=0;i<51;i++)
    validQPs[i]=0;
  
  for(i=MAX(minQP,originalQP-3);i<MIN(maxQP,originalQP+3);i++)
    validQPs[i]=1;
  
  
  if(mbNum - bRC->lastQPUpdateID >= qpUpdateThreshold || mbNum>=lastMBIndex )
  {  
    int ratio=0; 
    //predict the current frame bits
    if(bRC->PPictureIndexinGOP>0)
    {
      prevFrameBits = bRC->prevFrameBits;
      
      for(i=bRC->lastQPUpdateID;i<mbNum;i++)
      {
        prevFrameGeneratedBits += bRC->prevFrame_MBheaderbits[i]+bRC->prevFrame_MBtexbits[i];
        currentFrameGeneratedBits += bRC->currentFrame_MBheaderbits[i]+bRC->currentFrame_MBtexbits[i];
      }
      
      if(prevFrameBits == 0)
      {
        //Previous frame was ALL-SKIP
        currPredFrame = currentFrameGeneratedBits*(bRC->TotalNumberofMB -  bRC->lastQPUpdateID)/(mbNum - bRC->lastQPUpdateID);
        for(i=0;i<bRC->lastQPUpdateID;i++)
          currPredFrame+=bRC->currentFrame_MBheaderbits[i]+bRC->currentFrame_MBtexbits[i];
      }
      else
      {          
        if(prevFrameGeneratedBits == 0 || currentFrameGeneratedBits == 0)
        {
          for(i=0;i<bRC->lastQPUpdateID;i++)
          {
            prevFrameGeneratedBits += bRC->prevFrame_MBheaderbits[i]+bRC->prevFrame_MBtexbits[i];
            currentFrameGeneratedBits += bRC->currentFrame_MBheaderbits[i]+bRC->currentFrame_MBtexbits[i];
          }
          if(prevFrameGeneratedBits == 0)
            ratio=400;
          else
            ratio = MIN(400,MAX(25,currentFrameGeneratedBits*100/prevFrameGeneratedBits));  
        }
        else
        {
          ratio = MIN(400,MAX(25,currentFrameGeneratedBits*100/prevFrameGeneratedBits));
          for(i=0;i<bRC->lastQPUpdateID;i++)
          {
            prevFrameGeneratedBits += bRC->prevFrame_MBheaderbits[i]+bRC->prevFrame_MBtexbits[i];
            currentFrameGeneratedBits += bRC->currentFrame_MBheaderbits[i]+bRC->currentFrame_MBtexbits[i];
          }
        }
      }
      
      if(currentFrameGeneratedBits > 0)
      {          
        if(prevFrameGeneratedBits != 0 &&  currentFrameGeneratedBits != 0)
          currPredFrame = (int)(currentFrameGeneratedBits + (ratio*(prevFrameBits - prevFrameGeneratedBits))/100) ;
        else
          currPredFrame  = prevFrameBits;
      }
      else
      {
        prevFrameGeneratedBits = 0;
        for(i=0;i<bRC->TotalNumberofMB;i++)
          prevFrameGeneratedBits += bRC->prevFrame_MBheaderbits[i]+bRC->prevFrame_MBtexbits[i];
        currPredFrame = prevFrameGeneratedBits;
      }  
    }
    else 
    {
      for(i=bRC->lastQPUpdateID;i<mbNum;i++)
        currentFrameGeneratedBits += bRC->currentFrame_MBheaderbits[i]+bRC->currentFrame_MBtexbits[i];
      
      currPredFrame = currentFrameGeneratedBits*(bRC->TotalNumberofMB -  bRC->lastQPUpdateID)/(mbNum - bRC->lastQPUpdateID);
      
      for(i=0;i<bRC->lastQPUpdateID;i++)
        currPredFrame+=bRC->currentFrame_MBheaderbits[i]+bRC->currentFrame_MBtexbits[i];
    }      
    
    if(currPredFrame > upperlimit)
    {changeScore = (int)(scoreLUT[mbNum*20/bRC->TotalNumberofMB]*currPredFrame/upperlimit);QP_buffer += 2;}      
    else if(currPredFrame < lowerlimit)
    {
      QP_buffer -= 2;
      if(currPredFrame == 0)
        changeScore = 500;
      else
      {
        if(bRC->CurrentBufferFullness + currPredFrame - bRC->bitsPerFrame < 0)
          changeScore = (int)(scoreLUT[mbNum*20/bRC->TotalNumberofMB]*lowerlimit/currPredFrame);
        else
          changeScore = (int)(scoreLUT[mbNum*20/bRC->TotalNumberofMB]*lowerlimit/currPredFrame);
      }
    }
    
    QP_buffer = MIN(50,MAX(2,QP_buffer));
    //printf("%d %d %d\n",currPredFrame,upperlimit,lowerlimit);
    if(mbNum>firstChangeChance && changeScore>100)
    {
      
      if(currPredFrame > bRC->centerFrameBits)
      {        
        if(validQPs[QP_buffer] == 1)
        {
          
          bRC->lastQPUpdateID = mbNum;
          return MIN(50,MAX(2,QP_buffer));
        }
        else
        {
          int bestQP=originalQP,best_dist=51,dist;
          for(i=0;i<51;i++)
          {
            dist=51;
            
            if(validQPs[i]==1)
              dist=abs(i-QP_buffer);
            if(dist<best_dist)
            {
              bestQP=i;
              best_dist = dist;
            }
          }
          bRC->lastQPUpdateID = mbNum;
          return bestQP;            
        }        
      }
      else if(currPredFrame < bRC->centerFrameBits)
      {      
        
        if(validQPs[(int)QP_buffer] == 1)
        {
          bRC->lastQPUpdateID = mbNum;
          return MIN(50,MAX(2,QP_buffer));
        }
        else
        {
          int bestQP=originalQP,best_dist=51;
          bRC->lastQPUpdateID = mbNum;
          for(i=0;i<51;i++)
          {
            int dist=51;
            if(validQPs[i]==1)
              dist=abs(i-(int)QP_buffer);
            if(dist<best_dist)
            {
              bestQP=i;
              best_dist = dist;
            }
          }
          bRC->lastQPUpdateID = mbNum;
          return bestQP;
        }        
      }
      
    }
   }
   return originalQP;
}


int getIFrameQP(rateCtrl_s *bRC)
{
  //Calculate the QP for the I Frame depending on Buffer Fullness, and Previous Coding History
  int i,bufferAvail,totalSamples=0,lastFrameQP,minBits=INT_MAX,maxBits=0,maxQP=0,minQP=0;
  float a=0.0f,b=0.0f,c=0.0f,d=0.0f,m,y;
  int finalQp;
  

  if(bRC->ignoreIDR == 1)
    return (int)(bRC->averageQPforFrame+1.5);
  
  bufferAvail = bRC->BufferSize - bRC->CurrentBufferFullness + bRC->bitsPerFrame;
  
  if(bufferAvail > bRC->I_P_RATIO * bRC->bitsPerFrame && bRC->numConsecutiveSkips == 0)
  {
    if(bRC->PictureIndex>0)
    {
      finalQp = (int)(bRC->averageQPforFrame+2);
      if(finalQp > bRC->frameComputedQP)
        bRC->frameComputedQP=MIN(bRC->frameComputedQP + 2, finalQp);
      else
        bRC->frameComputedQP=MAX(bRC->frameComputedQP - 2, finalQp);      
    }
    return bRC->frameComputedQP;
  }
  
  for(i=0;i<10;i++)
  {    
    if(bRC->IFrameBits[i]>maxBits)
    {
      maxBits = bRC->IFrameBits[i];
      maxQP = bRC->IFrameQP[i];
    }
    if(bRC->IFrameBits[i]<minBits)
    {
      minBits = bRC->IFrameBits[i];
      minQP = bRC->IFrameQP[i];
    }
    
    //Use all the buffer you have
    if(!(bRC->IFrameQP[i] == 0 || bRC->IFrameBits[i] == 0))
    {
      totalSamples++;
      a+=bRC->IFrameQP[i]*bRC->IFrameBits[i];
      b+=bRC->IFrameQP[i];
      c+=bRC->IFrameBits[i];
      d+=bRC->IFrameQP[i]*bRC->IFrameQP[i];
    }
  }
  m = (totalSamples*a-b*c)/(totalSamples*d - b*b);
  y = (c - m*b)/totalSamples;
  lastFrameQP = bRC->IFrameQP[0];
  
  if(m>=0)
  {
    //Remove the last Sample
    for(i=0;i<totalSamples-1;i++)
    {
      bRC->IFrameQP[i]=bRC->IFrameQP[i+1];
      bRC->IFrameBits[i]=bRC->IFrameBits[i+1];
    }
    bRC->IFrameQP[totalSamples - 1]=0;
    bRC->IFrameBits[totalSamples - 1]=0;
    
    totalSamples = 0;
    for(i=0;i<10;i++)
    {    
      if(bRC->IFrameBits[i]>maxBits)
        maxBits = bRC->IFrameBits[i];
      if(bRC->IFrameBits[i]<minBits)
        minBits = bRC->IFrameBits[i];
      
      //Use all the buffer you have
      if(!(bRC->IFrameQP[i] == 0 || bRC->IFrameBits[i] == 0))
      {
        totalSamples++;
        a+=bRC->IFrameQP[i]*bRC->IFrameBits[i];
        b+=bRC->IFrameQP[i];
        c+=bRC->IFrameBits[i];
        d+=bRC->IFrameQP[i]*bRC->IFrameQP[i];
      }
    }
    m = (totalSamples*a-b*c)/(totalSamples*d - b*b);
    y = (c - m*b)/totalSamples;
  }
  
  if(bRC->numConsecutiveSkips > 0)
    return lastFrameQP+1;
  
  if (m == 0)
    return lastFrameQP;
  
  
  if(totalSamples < 2)
  {
    if(bufferAvail > 1.2*bRC->IFrameBits[0])
      return bRC->IFrameQP[0]-1;
    else if(bufferAvail < 0.8*bRC->IFrameBits[0])
      return bRC->IFrameQP[0]+1;
    else
      return bRC->IFrameQP[0];
    
  }    
  
  //Interpolation is reliable
  else if(bufferAvail<maxBits && bufferAvail>minBits)
  {
    int calcQP = (int)MIN(51,MAX(0,(bufferAvail - y)/m));
    if(calcQP > bRC->IFrameQP[0])
      return MIN(calcQP, bRC->IFrameQP[0] + 2);
    else
      return MAX(calcQP, bRC->IFrameQP[0] - 2);
  }
  //Interpolation is unreliable
  else
  {
    if(bufferAvail>maxBits)
      return maxQP;
    else
      return minQP;
  }
  
}


static float getAveragePSNR(rateCtrl_s *bRC,int windowSize) 
{
  float totalPSNR=0.0f;
  int i,totalFrm=0;
  
  
  for(i=0;i<windowSize;i++)
  {
    if(bRC->framePSNR[i]>0)
    {
      totalPSNR+=bRC->framePSNR[i];
      totalFrm++;
    }
  }
  return totalPSNR/windowSize;
}


int checkFrameSkip(rateCtrl_s *bRC, int frmBits,float psnrY)
{
  if(bRC->img_type == SLICE_I && bRC->ignoreIDR == 1)
    return AVCE_OK;
  
  //Only regular frame Skipping is used
  if(bRC->frameSkipEnabled == 1)  
  {
    if(bRC->CurrentBufferFullness + frmBits - bRC->bitsPerFrame > bRC->realBufferSize && !(bRC->numConsecutiveSkips > 2 && bRC->CurrentBufferFullness == 0))
    {     
      
      //Buffer overflow  
      if(bRC->numFrms > 0)
        bRC->PictureIndex = MIN(bRC->numFrms,bRC->PictureIndex+1);
      else
        bRC->PictureIndex++;

      bRC->CurrentBufferFullness-=bRC->bitsPerFrame;
      bRC->CurrentBufferFullness = MAX(0,bRC->CurrentBufferFullness);
      bRC->actualBufferFullness = bRC->CurrentBufferFullness;
      bRC->bitDifference = MAX(0,bRC->bitDifference-bRC->bitsPerFrame);
      bRC->stat_NumberofSkips++;
      bRC->numConsecutiveSkips++;
      return AVCE_FRAME_SKIPPED;
    }
    else if(bRC->CurrentBufferFullness + frmBits - bRC->bitsPerFrame > bRC->BufferSize && !(bRC->numConsecutiveSkips > 2 && bRC->CurrentBufferFullness == 0))
    {
      //Does not Overflow the Buffer limit by the Level, but only overflows hypothetical buffer RCA uses
      bRC->actualBufferFullness = bRC->CurrentBufferFullness + frmBits - bRC->bitsPerFrame;
      bRC->CurrentBufferFullness = bRC->BufferSize;      
      return AVCE_OK;
    }
    else
      return AVCE_OK;
  }

  else if(bRC->frameSkipEnabled == 2)  
  {
    //Advanced Frame Skipping algorithm
    if(bRC->CurrentBufferFullness + frmBits - bRC->bitsPerFrame > bRC->BufferSize && !(bRC->numConsecutiveSkips > 2 && bRC->CurrentBufferFullness == 0))
    {
       //Buffer overflow  
      if(bRC->numFrms > 0)
        bRC->PictureIndex = MIN(bRC->numFrms,bRC->PictureIndex+1);
      else
        bRC->PictureIndex++;

      bRC->CurrentBufferFullness-=bRC->bitsPerFrame;
      bRC->CurrentBufferFullness = MAX(0,bRC->CurrentBufferFullness);
      bRC->bitDifference-=bRC->bitsPerFrame;
      bRC->stat_NumberofSkips++;
      bRC->numConsecutiveSkips++;
      return AVCE_FRAME_SKIPPED;
    }
    else if(bRC->img_type == SLICE_I)
    {
      if(
        bRC->currentFramePSNR< getAveragePSNR(bRC,MIN(100,bRC->PictureIndex)) - 2 &&
        bRC->numConsecutiveSkips < 2    &&
        bRC->CurrentBufferFullness > bRC->BufferSize*0.1
        )
      {
        //Advanced Skip
        if(bRC->numFrms > 0)
          bRC->PictureIndex = MIN(bRC->numFrms,bRC->PictureIndex+1);
        else
          bRC->PictureIndex++;

        bRC->CurrentBufferFullness-=bRC->bitsPerFrame;
        bRC->CurrentBufferFullness = MAX(0,bRC->CurrentBufferFullness);
        bRC->bitDifference-=bRC->bitsPerFrame;
        bRC->stat_NumberofSkips++;
        bRC->numConsecutiveSkips++;
        return AVCE_FRAME_SKIPPED;
      }
    }
    else if(bRC->img_type == SLICE_P)
    {
      if(
        bRC->currentFramePSNR< getAveragePSNR(bRC,MIN(10,bRC->PictureIndex)) - 2 &&
        bRC->numConsecutiveSkips < 1  
        && psnrY > 0 //avoid warning
        )
      {
        
        if(bRC->numFrms > 0)
          bRC->PictureIndex = MIN(bRC->numFrms,bRC->PictureIndex+1);
        else
          bRC->PictureIndex++;
        
        bRC->CurrentBufferFullness-=bRC->bitsPerFrame;
        bRC->CurrentBufferFullness = MAX(0,bRC->CurrentBufferFullness);
        bRC->bitDifference-=bRC->bitsPerFrame;
        bRC->stat_NumberofSkips++;
        bRC->numConsecutiveSkips++;
        return AVCE_FRAME_SKIPPED;
      }
      
    }
    
    else
      return AVCE_OK;
  }

  return AVCE_OK;
}


void rc_free_mem(rateCtrl_s *bRC)
{
  nccFree(bRC->prevFrame_MBsad);
  nccFree(bRC->prevFrame_MBQp);
  nccFree(bRC->prevFrame_MBtexbits);
  nccFree(bRC->prevFrame_MBheaderbits);
  
  nccFree(bRC->currentFrame_MBsad);
  nccFree(bRC->currentFrame_MBQp);
  nccFree(bRC->currentFrame_MBtexbits);
  nccFree(bRC->currentFrame_MBheaderbits);
  
  nccFree(bRC->MSEofMB);
}


void computePFrameQP(rateCtrl_s *bRC, int img_type, int nalRefIdc,int srcPicNum,int hdrSize)
{
  float gamma;
  int QP_SW;
  int tex,finalQp=0;
  int avg_sh_mad = getAverageMAD(bRC,hdrSize,0);
   
  
  if(bRC->use_lt_RD_Model == 1)
  {
    if(bRC->use_sh_RD_Model == 1)
    {
      tex = bRC->bitsPerPFrame*bRC->rdModel_TextureBits[0]/(bRC->rdModel_TextureBits[0]+bRC->rdModel_HeaderBits[0]);
      if(tex>0 && avg_sh_mad > 0)
        QP_SW  = getQP_UsingRDModel(tex , avg_sh_mad , bRC->rdModel_X1, bRC->rdModel_X2);
      else
        QP_SW  = (int)(bRC->averageQPforFrame - 2);
      
      if(QP_SW > bRC->QP_SW)
        bRC->QP_SW = MIN(bRC->QP_SW+2, QP_SW);
      else
        bRC->QP_SW = MAX(bRC->QP_SW-2, QP_SW);
      srcPicNum,img_type;
    }
    else
      bRC->QP_SW = bRC->QP_LW;      
    
    gamma =  (MIN(bRC->BufferSize,(bRC->CurrentBufferFullness+bRC->numConsecutiveSkips*bRC->bitsPerFrame))*1.0f/bRC->BufferSize);
    
    if(gamma < 0.9f && gamma > 0.1f)
    {
      if(gamma > 0.65f)
      {
        if(bRC->QP_LW > bRC->QP_SW)
          finalQp = (int)(bRC->QP_LW);
        else
          finalQp = (int)((gamma-0.5f)*2.0f * bRC->QP_SW + (1-(gamma-0.5f)*2.0f) * bRC->QP_LW );
      }
      else if(gamma < 0.35f)
      {
        if(bRC->QP_LW < bRC->QP_SW)
          finalQp = (int)(bRC->QP_LW);
        else
          
          finalQp = (int)((1-gamma) * bRC->QP_SW + gamma * bRC->QP_LW);
      }
      else
        finalQp = (int)(bRC->QP_LW+ 0.5);        
    } 
    else if(gamma<=0.1)
      finalQp = MIN(bRC->QP_LW,bRC->QP_SW);
    else if(gamma>=0.9)
      finalQp = MAX(bRC->QP_LW,bRC->QP_SW);    
    
  }
  else
  {        
    if(bRC->PictureIndex == 1)
      finalQp = (int)bRC->averageQPforFrame + 2;
    else
      finalQp = (int)(bRC->averageQPforFrame);
    bRC->QP_SW = finalQp;                
  }
  
  if(finalQp > bRC->frameComputedQP && bRC->averageQPforFrame > bRC->frameComputedQP)
    bRC->frameComputedQP=MIN(bRC->frameComputedQP + 2, finalQp);
  else if(finalQp > bRC->frameComputedQP && bRC->averageQPforFrame <= bRC->frameComputedQP)
    bRC->frameComputedQP=(int)(MIN(bRC->averageQPforFrame + 2, finalQp));
  else if(finalQp <= bRC->frameComputedQP && bRC->averageQPforFrame <= bRC->frameComputedQP)
    bRC->frameComputedQP=MAX(bRC->frameComputedQP - 2, finalQp);
  else if(finalQp <= bRC->frameComputedQP && bRC->averageQPforFrame > bRC->frameComputedQP)
    bRC->frameComputedQP=(int)(MAX(bRC->averageQPforFrame , finalQp));
  
  if(bRC->frameSkipEnabled != 0 && bRC->numConsecutiveSkips>0 && bRC->PPictureIndexinGOP<3)
    bRC->frameComputedQP=MIN(50,bRC->frameComputedQP+2*bRC->numConsecutiveSkips);
  
  else if(bRC->frameSkipEnabled != 0)
    bRC->frameComputedQP=MIN(50,bRC->frameComputedQP+bRC->numConsecutiveSkips);
  
  bRC->frameComputedQP = MIN(50,bRC->frameComputedQP);
  
  if(nalRefIdc == 0)
  {
    if(bRC->CurrentBufferFullness > bRC->bitsPerFrame*2)
      bRC->frameComputedQP+=2;
    else if(bRC->CurrentBufferFullness > bRC->bitsPerFrame)
      bRC->frameComputedQP++;
  }
  
#ifdef USE_SPP
  if(bRC->SPPPictureCounter == 0)
    bRC->SPPframeComputedQP=bRC->frameComputedQP-SPP_QP_CHANGE;      
#endif
}

#else

static const int scoreLUT[20] = {
  66,66,66,66,66,66,71,74,77,82,85,87,89,92,94,96,98,100 ,100, 100
};


static int32 ComputePictureMAD(rateCtrl_s *pbRC);
static int Qstep2QP( float Qstep );
static float QP2Qstep( int QP );
static void createBitEnvelope(rateCtrl_s *pbRC);
static int getIFrameQP(rateCtrl_s *pbRC);
static int checkFrameSkip(rateCtrl_s *pbRC, int32 frmBits);
static void computePFrameQP(rateCtrl_s *pbRC, int img_type, int nalRefIdc,int srcPicNum);
static void clearRCHistory(rateCtrl_s *bRC);

static void rc_alloc_mem(rateCtrl_s *bRC)
{

  //Allocate the tables
  bRC->prevFrame_MBsad = (int32*) nccMalloc(sizeof(int32) * bRC->TotalNumberofMB);
  bRC->prevFrame_MBQp = (int*) nccMalloc(sizeof(int) * bRC->TotalNumberofMB);
  bRC->prevFrame_MBtexbits = (int32*) nccMalloc(sizeof(int32) * bRC->TotalNumberofMB);
  bRC->prevFrame_MBheaderbits = (int32*) nccMalloc(sizeof(int32) * bRC->TotalNumberofMB);
  
  bRC->currentFrame_MBsad = (int32*) nccMalloc(sizeof(int32) * bRC->TotalNumberofMB);
  bRC->currentFrame_MBQp = (int*) nccMalloc(sizeof(int) * bRC->TotalNumberofMB);
  bRC->currentFrame_MBtexbits = (int32*) nccMalloc(sizeof(int32) * bRC->TotalNumberofMB);
  bRC->currentFrame_MBheaderbits = (int32*) nccMalloc(sizeof(int32) * bRC->TotalNumberofMB);
  
  bRC->MSEofMB = (int32*) nccMalloc(sizeof(int32) * bRC->TotalNumberofMB);
  
  memset(bRC->prevFrame_MBsad, 0, sizeof(int32)*bRC->TotalNumberofMB);
  memset(bRC->prevFrame_MBQp, 0, sizeof(int)*bRC->TotalNumberofMB);
  memset(bRC->prevFrame_MBtexbits, 0, sizeof(int32)*bRC->TotalNumberofMB);
  memset(bRC->prevFrame_MBheaderbits, 0, sizeof(int32)*bRC->TotalNumberofMB);
  
  memset(bRC->currentFrame_MBsad, 0, sizeof(int32)*bRC->TotalNumberofMB);
  memset(bRC->currentFrame_MBQp, 0, sizeof(int)*bRC->TotalNumberofMB);
  memset(bRC->currentFrame_MBtexbits, 0, sizeof(int32)*bRC->TotalNumberofMB);
  memset(bRC->currentFrame_MBheaderbits, 0, sizeof(int32)*bRC->TotalNumberofMB);
  
  memset(bRC->MSEofMB, 0, sizeof(int32)*bRC->TotalNumberofMB);
}


// Initiate rate control parameters
void rc_init_seq(rateCtrl_s *bRC, encParams_s *pencPar)
{
  int L1,L2,L3,bpp;
  int qp;
  int i;
  

  memset(bRC, 0, sizeof(rateCtrl_s));
  if(pencPar->brcBitRate!=0)
  {    

    bRC->modeDecision = MODE_DECISION_SIMPLE;

    bRC->numConsecutiveSkips = 0;
    bRC->numIntraMBs = 0;
    bRC->bit_rate=pencPar->brcBitRate;
    bRC->frame_rate=pencPar->origFpsTimes1000/pencPar->offsetForRefFrame/1000;
    bRC->BufferSize=MIN(bRC->bit_rate*6,pencPar->brcBufSize*8);
    bRC->prevFrameScut=0;
    
    if(bRC->BufferSize < bRC->bit_rate)
    {
      //Low Delay
      bRC->I_P_RATIO = 5;
      bRC->UPPER_LIMIT_MULTIPLE = 2;
      bRC->LOWER_LIMIT_MULTIPLE = 4;
      bRC->BIT_ADJUST_FREQUENCY = 1;
      bRC->BIT_ADJUST_WINDOW = MAX(30,bRC->BufferSize/(2*bRC->bit_rate));
      bRC->LT_WINDOW_QP_UPDATE_FREQ = 4;
      
    }
    else
    {
      //Larger Delay
      bRC->I_P_RATIO = 8;
      bRC->UPPER_LIMIT_MULTIPLE = 4;
      bRC->LOWER_LIMIT_MULTIPLE = 4;
      bRC->BIT_ADJUST_FREQUENCY = 5;
      bRC->BIT_ADJUST_WINDOW = MAX(50,bRC->BufferSize/(2*bRC->bit_rate));
      if(bRC->BufferSize < bRC->bitsPerFrame*3)
        bRC->LT_WINDOW_QP_UPDATE_FREQ = 25;
      else
        bRC->LT_WINDOW_QP_UPDATE_FREQ = 50;      
    }
    
    bRC->useSEI = pencPar->useSEIMessages;
    bRC->numSkippedMBs = 0;
    bRC->numNonref = pencPar->numNonref;
    bRC->frameSkipEnabled = pencPar->frameSkipEnabled;
    bRC->TotalNumberofMB = pencPar->picWidth*pencPar->picHeight/256;
    bRC->numFrms = pencPar->numFrms;
    bRC->stat_NumberofSkips = 0;
    bRC->stat_NumberofUnderflows = 0;
    bRC->stat_NumberofReencodes = 0;
    bRC->CurrentBufferFullness=0;
    bRC->TargetBufferLevel = bRC->BufferSize/2;

    rc_alloc_mem(bRC);
    
    for(i=0;i<bRC->TotalNumberofMB;i++)
    {
      bRC->prevFrame_MBsad[i]=0;
      bRC->prevFrame_MBQp[i]=0;
      bRC->prevFrame_MBtexbits[i]=0;
      bRC->prevFrame_MBheaderbits[i]=0;
      bRC->currentFrame_MBsad[i]=0;
      bRC->currentFrame_MBQp[i]=0;
      bRC->currentFrame_MBtexbits[i]=0;
      bRC->currentFrame_MBheaderbits[i]=0;    
    }
    
    bRC->PPictureIndexinGOP=-1;
    bRC->PictureIndex=0;
    
    bRC->SPPPictureCounter = SPP_PICTURE_FREQ;
    bRC->bitDifference=0;
    
    bRC->bufferStall = 1;
    bRC->playingStartFrame = 0;
    bRC->TotalBits = 0;
    bRC->prevFrameBits = 0;
    bRC->currentFrameBits = 0;
    
    if(pencPar->intraFreq == 0 && pencPar->idrFreq == 0)
      bRC->GOPSize = bRC->numFrms;
    else
    {    
      if(pencPar->intraFreq > 0)
        bRC->GOPSize = pencPar->intraFreq;
      else
        bRC->GOPSize = pencPar->idrFreq;
    }
    
    for(i=0;i<MAX_RD_WINDOW_SIZE;i++)
    {
      bRC->sadHistory[i] = 0;
      bRC->qpHistory[i]  = 0;
      bRC->bitHistory[i] = 0;
      bRC->qstepHistory[i]  = 0.0f;
    }

    //Calculate the Initial QP from bpp
    bRC->InitialQP=pencPar->qpStart;
    bRC->QP_LW = pencPar->qpStart;
    bRC->frameComputedQP = pencPar->qpStart;
    
    bRC->ignoreIDR = pencPar->ignoreIDRBits;
    
    /*compute the initial QP*/
    bpp = 100*bRC->bit_rate /(bRC->frame_rate * pencPar->picWidth * pencPar->picHeight);
    
    if (pencPar->picWidth <= 200) 
    {
      L1 = 10;
      L2 = 30;
      L3 = 60;
    }
    else if (pencPar->picWidth <= 400)
    {
      L1 = 20;
      L2 = 60;
      L3 = 120;
    }
    else 
    {
      L1 = 30;
      L2 = 60;
      L3 = 150;
    }
    
    if (bRC->InitialQP==0)
    {
      if(bpp<= L1)
        qp = 35;
      else if(bpp<=L2)
        qp = 25;
      else if(bpp<=L3)
        qp  = 20;
      else
        qp =10;
      
      if(bRC->BufferSize < (bRC->bit_rate>>1))
        qp+=3;
      
      bRC->InitialQP = qp;
      bRC->QP_LW = qp;
      bRC->frameComputedQP = qp;
    }
    
    bRC->bitsPerFrame = (bRC->bit_rate*100/bRC->frame_rate)/100 ;
    bRC->centerFrameBits = bRC->bitsPerFrame;
    bRC->averageQPforFrame =  bRC->InitialQP;
    bRC->SPPframeComputedQP = bRC->InitialQP;
    
    bRC->frameReturnedQP = bRC->frameComputedQP;
    
    for(i=0;i<10;i++)
      bRC->IFrameQP[0] = 0;
    
    bRC->IFrameQP[0] = pencPar->qpStart;
    
  }
  else
  {
    bRC->numIntraMBs = 0;
    bRC->bit_rate=pencPar->brcBitRate;
    bRC->frame_rate=pencPar->origFpsTimes1000/pencPar->offsetForRefFrame/1000;
    bRC->bitsPerFrame = (bRC->bit_rate*100/bRC->frame_rate)/100;
  }
    
  //Ignore IDR bits for low delay cases
  if(bRC->bit_rate > 0 && bRC->BufferSize*100/bRC->bit_rate < 50 && bRC->ignoreIDR == 0)
  {
    bRC->ignoreIDR=1;      
  }

  if(bRC->ignoreIDR==2)
    bRC->ignoreIDR=0;
}


void rc_init_pict(rateCtrl_s *bRC, int img_type, int nalRefIdc,int srcPicNum)
{
  
  if(bRC->bit_rate != 0)
  {
    bRC->numSkippedMBs = 0;
    bRC->img_type = img_type;
    bRC->numIntraMBs = 0;
    bRC->nalRefIdc = nalRefIdc;
    bRC->srcPicNum = srcPicNum;
    bRC->lastQPUpdateID = 0;
    bRC->currentFrameBits = 0;
    if(bRC->GOPSize > 1)
    {
      if(bRC->PictureIndex == 0)
      {
        bRC->bitsPerPFrame = (bRC->bit_rate*10/bRC->frame_rate * (bRC->GOPSize *10 / (bRC->GOPSize - 1 + 5) ) )/100;
        bRC->bitsPerPFrame = ((bRC->bitsPerPFrame)*(bRC->numNonref+1)*10/(10+7*bRC->numNonref));            
      }
    }
    else
    {
      bRC->upperFrameLimit =  (int32)(bRC->bitsPerFrame*12/10);
      bRC->lowerFrameLimit =  (int32)(bRC->bitsPerFrame*8/10);
    }
  
    bRC->CurrentPicturePredictedMAD = bRC->sadHistory[0];

    if(bRC->PictureIndex == 0)
      bRC->scut = 0;
    
    //Fill the Picture Timing SEI Message associated with the current picture
    if(bRC->useSEI)  
      fillPictureTimingSEI(bRC);
    
    if(img_type == SLICE_I)
    {
      bRC->PPictureIndexinGOP = -1;
      
      createBitEnvelope(bRC);
      if(bRC->scut == 1)
      {

        if(bRC->averageQPforFrame > bRC->frameComputedQP)
          bRC->frameComputedQP=MIN(bRC->frameComputedQP + 2, bRC->averageQPforFrame);
        else
          bRC->frameComputedQP=MAX(bRC->frameComputedQP - 2, bRC->averageQPforFrame);

      }
      else
      {
        if(bRC->PictureIndex > 0)
          bRC->frameComputedQP = getIFrameQP(bRC);
      }
      
    }
    
    if(img_type==SLICE_P)
    {        
      
      createBitEnvelope(bRC);         
      computePFrameQP(bRC, img_type, nalRefIdc,srcPicNum);
      
    }
    
    bRC->frameComputedQP=(int)(MAX(bRC->frameComputedQP, 1 ));
    bRC->frameComputedQP=(int)(MIN(bRC->frameComputedQP, 51 ));
    
    return;
  }
  else
  {
    bRC->numIntraMBs = 0;
    return;
  }
}


int rc_update_pict(rateCtrl_s *bRC, int img_type, int32 texbits,int32 headerbits)
{
  int i;


  bRC->prevFrameBits = bRC->currentFrameBits;
  
  if(bRC->PictureIndex == 0)
    bRC->IFrameQP[0] = 0;
  
  if(img_type == SLICE_I)
  {
    for(i=9;i>0;i--)
    {
      bRC->IFrameQP[i]   = bRC->IFrameQP[i-1];
      bRC->IFrameBits[i] = bRC->IFrameBits[i-1];
    }
    bRC->IFrameQP[0]   = (int)(bRC->averageQPforFrame+0.5);
    bRC->IFrameBits[0] = texbits + headerbits;
  }
  if(bRC->numIntraMBs > bRC->TotalNumberofMB*4/5 || (bRC->prevFrameScut == 1 && (bRC->CurrentBufferFullness + texbits+headerbits - bRC->bitsPerFrame > bRC->BufferSize) ))
  //This was a frame at scene cut
    bRC->prevFrameScut = 1;
  else
    bRC->prevFrameScut = 0;
  
  if(bRC->bit_rate == 0)
  {
    bRC->CurrentBufferFullness = bRC->CurrentBufferFullness + texbits + headerbits - bRC->bitsPerFrame;
    return AVCE_OK;
  }
  
  if(bRC->frameSkipEnabled == 1 || bRC->frameSkipEnabled == 2)
  {
    if(checkFrameSkip(bRC,(int32)(texbits+headerbits)) == AVCE_FRAME_SKIPPED)
      return AVCE_FRAME_SKIPPED;
    
    if(bRC->CurrentBufferFullness + texbits + headerbits - bRC->bitsPerFrame < 0)
    {    
      //Filler Data SEI will be sent at a higher layer
      bRC->stat_NumberofUnderflows++;
      bRC->numConsecutiveUnderflows++;      
    }
    else
      bRC->numConsecutiveUnderflows = 0;   
  }
  
  bRC->numConsecutiveSkips = 0;  
  bRC->PictureIndex++;
  bRC->PPictureIndexinGOP++;
  if(!(bRC->ignoreIDR && img_type == SLICE_I))
    bRC->bitDifference += (texbits+headerbits-bRC->bitsPerFrame);
  bRC->TotalBits += (texbits+headerbits);
  
  /*
   * Simple Rate Control, without any floating point arithmetic
   */
  if(bRC->bufferStall)
  {
    //    if(!(img_type == SLICE_I && bRC->ignoreIDR == 1))
    bRC->CurrentBufferFullness += texbits + headerbits ;
    
    if(bRC->CurrentBufferFullness > bRC->TargetBufferLevel)
    {
      bRC->playingStartFrame = bRC->PictureIndex;
      bRC->CurrentBufferFullness -= bRC->bitsPerFrame;
      bRC->bufferStall = 0;    
      
    }
  }
  else
  {
    //    if(!(img_type == SLICE_I && bRC->ignoreIDR == 1))
    bRC->CurrentBufferFullness += texbits + headerbits - bRC->bitsPerFrame ;
  }
  
  bRC->CurrentBufferFullness = MIN(bRC->BufferSize,MAX(bRC->CurrentBufferFullness,0)); //Overflow and Underflow handled elsewhere
  
  if(img_type ==SLICE_P)
  {
    //Update the Model Parameters
    for(i=0;i<bRC->TotalNumberofMB;i++)
    {
      bRC->prevFrame_MBsad[i]=bRC->currentFrame_MBsad[i];
      bRC->prevFrame_MBQp[i]=bRC->currentFrame_MBQp[i];
      bRC->prevFrame_MBtexbits[i]=bRC->currentFrame_MBtexbits[i];
      bRC->prevFrame_MBheaderbits[i]=bRC->currentFrame_MBheaderbits[i];      
    }
    
    //Update the model
    if(texbits>0 && headerbits > 0)
    {
      for(i=MAX_RD_WINDOW_SIZE-1;i>0;i--)
      {
        bRC->sadHistory[i]  = bRC->sadHistory[i-1];
        bRC->qpHistory[i]   = bRC->qpHistory[i-1];
        bRC->qstepHistory[i]= bRC->qstepHistory[i-1];
        bRC->bitHistory[i]  = bRC->bitHistory[i-1];              
      }
      bRC->qpHistory[0]     = bRC->averageQPforFrame;
      bRC->qstepHistory[i]  = 1.0f/QP2Qstep(bRC->averageQPforFrame);
      bRC->bitHistory[0]    = texbits+headerbits;
      bRC->sadHistory[0]    = ComputePictureMAD(bRC);
    }
  }
  return AVCE_OK;    
}


int rc_getFrameQP(rateCtrl_s *bRC, int img_type)
{
  if((img_type==SLICE_P)&&(bRC->PPictureIndexinGOP==0))
  {
    bRC->frameComputedQP = bRC->frameReturnedQP = clip(MIN_QP, MAX_QP, (int)(bRC->averageQPforFrame)+2);
    return bRC->frameComputedQP;
  }
  else
    return bRC->frameReturnedQP=bRC->frameComputedQP;
}


static int32 ComputePictureMAD(rateCtrl_s *bRC)
{
  float TotalMAD;
  int i;


  TotalMAD = 0.0;
  
  for(i=0;i<bRC->TotalNumberofMB;i++)
    TotalMAD +=bRC->MSEofMB[i];
  
  //TotalMAD /=(bRC->TotalNumberofMB*256);
  return TotalMAD;
}


static void createBitEnvelope(rateCtrl_s *bRC)
{    
  if(bRC->img_type == SLICE_I)
  {
    
    bRC->upperFrameLimit = (int32)MAX(bRC->bitsPerFrame,MIN(bRC->BufferSize*0.95f-bRC->CurrentBufferFullness+bRC->bitsPerFrame, bRC->bitsPerFrame*bRC->I_P_RATIO));
    bRC->lowerFrameLimit = bRC->upperFrameLimit - bRC->bitsPerFrame;
    return;
  }
  
  bRC->centerFrameBits = bRC->bitsPerPFrame;
  
  if(bRC->CurrentBufferFullness < 0)
  {
    bRC->upperFrameLimit = (int32)(bRC->bitsPerFrame*bRC->UPPER_LIMIT_MULTIPLE);
    bRC->lowerFrameLimit = (int32)(bRC->bitsPerFrame*3)>>1;
    bRC->centerFrameBits = bRC->lowerFrameLimit;
    
  }
  else
  {     
    if(bRC->CurrentBufferFullness >= bRC->BufferSize/2)
    {       
      bRC->upperFrameLimit = (int32)(bRC->bitsPerPFrame * (bRC->UPPER_LIMIT_MULTIPLE - ((bRC->UPPER_LIMIT_MULTIPLE - 1)*(bRC->CurrentBufferFullness - bRC->BufferSize/2)*100/bRC->BufferSize))/100);
      bRC->centerFrameBits = MIN(bRC->upperFrameLimit,bRC->bitsPerPFrame);
      bRC->lowerFrameLimit = (int32)(bRC->centerFrameBits / bRC->LOWER_LIMIT_MULTIPLE);
    }
    else
    {
      bRC->lowerFrameLimit = (int32)(bRC->bitsPerFrame * ((200-200/bRC->LOWER_LIMIT_MULTIPLE)*bRC->CurrentBufferFullness)/bRC->BufferSize)/100; 
      bRC->centerFrameBits = MIN(bRC->upperFrameLimit,bRC->bitsPerPFrame);
      bRC->upperFrameLimit = (int32)(bRC->centerFrameBits * bRC->UPPER_LIMIT_MULTIPLE);
    }  
  }
  
  if(bRC->CurrentBufferFullness + bRC->upperFrameLimit - bRC->bitsPerFrame > bRC->BufferSize - bRC->bitsPerFrame/5)
  {
    bRC->upperFrameLimit = -bRC->bitsPerFrame/5 + bRC->BufferSize - bRC->CurrentBufferFullness + bRC->bitsPerFrame;
    bRC->lowerFrameLimit = MAX(bRC->bitsPerFrame/4, bRC->upperFrameLimit - bRC->bitsPerFrame);
    bRC->centerFrameBits = (bRC->upperFrameLimit + bRC->lowerFrameLimit)/2;
  }
  
  if(bRC->CurrentBufferFullness + bRC->lowerFrameLimit - bRC->bitsPerFrame < bRC->bitsPerFrame/5)
  {
    bRC->lowerFrameLimit = bRC->bitsPerFrame/5 + bRC->bitsPerFrame  - bRC->CurrentBufferFullness;
    bRC->upperFrameLimit = bRC->lowerFrameLimit + bRC->bitsPerFrame;
    bRC->centerFrameBits = (bRC->upperFrameLimit + bRC->lowerFrameLimit)/2;
  }
  
  if(bRC->lowerFrameLimit < bRC->bitsPerFrame/bRC->LOWER_LIMIT_MULTIPLE)
  {
    bRC->lowerFrameLimit = (int32)(bRC->bitsPerFrame/bRC->LOWER_LIMIT_MULTIPLE);
    bRC->upperFrameLimit = bRC->lowerFrameLimit + bRC->bitsPerFrame/2;
    bRC->centerFrameBits = bRC->lowerFrameLimit + bRC->bitsPerFrame/4;
  }
  
  if(bRC->upperFrameLimit > bRC->bitsPerFrame*bRC->UPPER_LIMIT_MULTIPLE)
  {
    bRC->upperFrameLimit = (int32)(bRC->bitsPerFrame*bRC->UPPER_LIMIT_MULTIPLE);
    bRC->lowerFrameLimit = bRC->upperFrameLimit - bRC->bitsPerFrame/2;
    bRC->centerFrameBits = bRC->upperFrameLimit - bRC->bitsPerFrame/4;
  }
}  


//Fills the necessary HRD parameter syntaxes that should be put in the bitstream
void fillHRDParameters(rateCtrl_s *bRC, hrd_parameters_s *hrd)
{
  int i;

  
  hrd->cpb_cnt_minus1 = 0;
  //Calculate the bit_rate_scale and bit_rate_value
  for(i=1 ; ( ((bRC->bit_rate>>i) & (0x00000001)) != 0x00000001) ;i++);
  //i holds the number of zeros
  hrd->bit_rate_scale = MAX(0,i-6);
  hrd->bit_rate_value_minus1[0] = (int)(bRC->bit_rate >> i) - 1;
  
  //Calculate the bit_rate_scale and bit_rate_value
  for(i=1 ; ( ((bRC->BufferSize>>i) & (0x00000001)) != 0x00000001) ;i++);
  hrd->cpb_size_scale = MAX(0,i-4);
  hrd->cpb_size_value_minus1[0] = (int)(bRC->bit_rate >> (i-1)  ) - 1;
  
  hrd->cbr_flag[0] = 0; 
  hrd->initial_cpb_removal_delay_length_minus1 = 19; 
  hrd->cpb_removal_delay_length_minus1 = 19;
  hrd->dpb_output_delay_length_minus1 = 19;
  hrd->time_offset_length = 0;
}


void fillBufferingPeriodSEI(rateCtrl_s *bRC)
{
  buffering_period_SEI_s  *bufperiodSEI = &bRC->bufperiodSEI;
  bufperiodSEI->initial_cpb_removal_delay = (unsigned int)(bRC->TargetBufferLevel* (90000*1.0/ bRC->bit_rate)) ;
  bufperiodSEI->initial_cpb_removal_delay_offset =   
    bufperiodSEI->seq_parameter_set_id = 0;
}


void fillPictureTimingSEI(rateCtrl_s *bRC)
{
  picture_timing_SEI_s *pic_timing_SEI = &bRC->picture_timing_SEI;
  if(bRC->PictureIndex == 0)
  {
    pic_timing_SEI->cpb_removal_delay = 0;
    pic_timing_SEI->dpb_output_delay = 0;
  }
  else
  {
    pic_timing_SEI->cpb_removal_delay = bRC->PictureIndex;
    pic_timing_SEI->dpb_output_delay = bRC->PictureIndex;
  }
}


void   rc_update_bitrate(rateCtrl_s *bRC, int bitrate)
{
  if(bitrate!=0)
  {
    bRC->bitsPerPFrame = (int)(bRC->bitsPerPFrame * (bitrate*1.0f/bRC->bit_rate));
    bRC->bitsPerFrame = (int)(bRC->bitsPerFrame * (bitrate*1.0f/bRC->bit_rate));
    bRC->BufferSize = (int)(bRC->BufferSize * (bitrate*1.0f / bRC->bit_rate));
    
    if(bRC->CurrentBufferFullness > bRC->BufferSize)
      //Assume the extra portion of the underlying data transfers to the Transport Buffer
      bRC->CurrentBufferFullness = bRC->BufferSize;
    
  }  
  bRC->bit_rate = bitrate; 
}


void rc_updateMB(rateCtrl_s *bRC, int texbits,int headerbits,int mb_minMSE, int mb_type, int mb_interMode,int mbNum)
{
  int totalMB=0,i=0;
  int tx_th = 5;


  //bRC->MSEofMB[mbNum] = mb->minSad;
  bRC->MSEofMB[mbNum] = mb_minMSE>>7;
  
  bRC->currentFrameBits += (headerbits + texbits);
  bRC->currentFrame_MBheaderbits[mbNum] = headerbits;
  bRC->currentFrame_MBtexbits[mbNum] = texbits;
  
  if(mb_type == MBK_INTER && mb_interMode == MOT_COPY)
    bRC->numSkippedMBs++;
  
  if(mbNum == bRC->TotalNumberofMB-1)
  {
    
    bRC->averageQPforFrame = 0;
    
    for(i=0;i<bRC->TotalNumberofMB;i++)
    {
      if(bRC->currentFrame_MBtexbits[i]>tx_th)
      {
        bRC->averageQPforFrame+=bRC->currentFrame_MBQp[i];
        totalMB++;
      }
    }
    if(totalMB < bRC->TotalNumberofMB/4)
    {
      bRC->averageQPforFrame = 0;
      for(i=0;i<bRC->TotalNumberofMB;i++)
        bRC->averageQPforFrame+=bRC->currentFrame_MBQp[i];
      totalMB = bRC->TotalNumberofMB;
    }
    
    bRC->averageQPforFrame=bRC->averageQPforFrame/totalMB;
  }
  
}


int rc_getMBQP(rateCtrl_s *bRC, int sliceType,int mbNum)
{
  int i=0;
  int validQPs[51];
  int originalQP;
  int32 currentFrameGeneratedBits=0;
  int32 prevFrameGeneratedBits = 0,prevFrameBits;
  int32 upperlimit= bRC->upperFrameLimit;
  int32 lowerlimit= bRC->lowerFrameLimit;
  int32 currPredFrame;
  int QP_buffer;  
  int firstChangeChance = bRC->TotalNumberofMB/5;
  int lastMBIndex = 4*bRC->TotalNumberofMB/5;
  int qpUpdateThreshold; 
  int changeScore=0;
  int maxQP = MIN(50,bRC->frameReturnedQP+6);
  int minQP = MAX(2,bRC->frameReturnedQP-6);
  

  if(bRC->bit_rate == 0 || bRC->brcdisableMBLevel==1)
    return -1;
  
  //if((sliceType == SLICE_I && bRC->PictureIndex == 0) || ( (sliceType == SLICE_I && bRC->ignoreIDR)) )
  if((sliceType == SLICE_I && bRC->ignoreIDR)) 
    return bRC->frameReturnedQP;
  
  
  qpUpdateThreshold = bRC->TotalNumberofMB / 20;
  if(bRC->bit_rate < bRC->BufferSize*3)
  {
    if(mbNum > (int)(bRC->TotalNumberofMB*0.4f))
      qpUpdateThreshold=qpUpdateThreshold/2;
    if(mbNum > (int)(bRC->TotalNumberofMB*0.7f))
      qpUpdateThreshold=qpUpdateThreshold/2;
    if(mbNum > (int)(bRC->TotalNumberofMB*0.9f))
      qpUpdateThreshold = 1;
  }
  
  if(mbNum == 0)
    originalQP = bRC->frameReturnedQP;
  else
    originalQP = bRC->currentFrame_MBQp[mbNum - 1];
  
  QP_buffer = originalQP;
  
  for(i=0;i<51;i++)
    validQPs[i]=0;
  
  for(i=MAX(minQP,originalQP-3);i<MIN(maxQP,originalQP+3);i++)
    validQPs[i]=1;
  
  
  if(mbNum - bRC->lastQPUpdateID >= qpUpdateThreshold || mbNum>=lastMBIndex )
  {  
    int ratio=0; 
    //predict the current frame bits
    if(bRC->PPictureIndexinGOP>0 || bRC->prevFrameScut == 1)
    {
      prevFrameBits = bRC->prevFrameBits;
      
      for(i=bRC->lastQPUpdateID;i<mbNum;i++)
      {
        prevFrameGeneratedBits += bRC->prevFrame_MBheaderbits[i]+bRC->prevFrame_MBtexbits[i];
        currentFrameGeneratedBits += bRC->currentFrame_MBheaderbits[i]+bRC->currentFrame_MBtexbits[i];
      }
      //printf("1: %ld\n",currentFrameGeneratedBits);
      if(prevFrameBits == 0)
      {
        //Previous frame was ALL-SKIP
        currPredFrame = currentFrameGeneratedBits*(bRC->TotalNumberofMB -  bRC->lastQPUpdateID)/(mbNum - bRC->lastQPUpdateID);
        for(i=0;i<bRC->lastQPUpdateID;i++)
          currPredFrame+=(bRC->currentFrame_MBheaderbits[i]+bRC->currentFrame_MBtexbits[i]);
      }
      else
      {          
        if(prevFrameGeneratedBits == 0 || currentFrameGeneratedBits == 0)
        {
          for(i=0;i<bRC->lastQPUpdateID;i++)
          {
            prevFrameGeneratedBits += bRC->prevFrame_MBheaderbits[i]+bRC->prevFrame_MBtexbits[i];
            currentFrameGeneratedBits += bRC->currentFrame_MBheaderbits[i]+bRC->currentFrame_MBtexbits[i];
          }
          //printf("2: %ld %ld\n",prevFrameGeneratedBits,currentFrameGeneratedBits);
          if(prevFrameGeneratedBits == 0)
            ratio=400;
          else
            ratio = MIN(400,MAX(25,currentFrameGeneratedBits*100/prevFrameGeneratedBits));  
        }
        else
        {
          ratio = MIN(400,MAX(25,currentFrameGeneratedBits*100/prevFrameGeneratedBits));
          for(i=0;i<bRC->lastQPUpdateID;i++)
          {
            prevFrameGeneratedBits += bRC->prevFrame_MBheaderbits[i]+bRC->prevFrame_MBtexbits[i];
            currentFrameGeneratedBits += bRC->currentFrame_MBheaderbits[i]+bRC->currentFrame_MBtexbits[i];
          }
        }
      }
      
      if(currentFrameGeneratedBits > 0)
      {          
        if(prevFrameGeneratedBits != 0 &&  currentFrameGeneratedBits != 0)
          currPredFrame = (int)(currentFrameGeneratedBits + (ratio*(prevFrameBits - prevFrameGeneratedBits))/100) ;
        else
          currPredFrame  = prevFrameBits;
      }
      else
      {
        prevFrameGeneratedBits = 0;
        for(i=0;i<bRC->TotalNumberofMB;i++)
          prevFrameGeneratedBits += bRC->prevFrame_MBheaderbits[i]+bRC->prevFrame_MBtexbits[i];
        currPredFrame = prevFrameGeneratedBits;
      }
      //printf("3: %ld %ld %ld\n",prevFrameGeneratedBits,currentFrameGeneratedBits,currPredFrame );  
    }
    else 
    {
      for(i=bRC->lastQPUpdateID;i<mbNum;i++)
        currentFrameGeneratedBits += bRC->currentFrame_MBheaderbits[i]+bRC->currentFrame_MBtexbits[i];
      
      currPredFrame = currentFrameGeneratedBits*(bRC->TotalNumberofMB -  bRC->lastQPUpdateID)/(mbNum - bRC->lastQPUpdateID);
      
      for(i=0;i<bRC->lastQPUpdateID;i++)
        currPredFrame+=bRC->currentFrame_MBheaderbits[i]+bRC->currentFrame_MBtexbits[i];
    }      
    
    if(currPredFrame > upperlimit)
    {changeScore = (int)(scoreLUT[mbNum*20/bRC->TotalNumberofMB]*currPredFrame/upperlimit);QP_buffer += 2;}      
    else if(currPredFrame < lowerlimit)
    {
      QP_buffer -= 2;
      if(currPredFrame == 0)
        changeScore = 500;
      else
      {
        if(bRC->CurrentBufferFullness + currPredFrame - bRC->bitsPerFrame < 0)
          changeScore = (int)(scoreLUT[mbNum*20/bRC->TotalNumberofMB]*lowerlimit/currPredFrame);
        else
          changeScore = (int)(scoreLUT[mbNum*20/bRC->TotalNumberofMB]*lowerlimit/currPredFrame);
      }
    }
        
    QP_buffer = MIN(50,MAX(2,QP_buffer));
    
    if(mbNum>firstChangeChance && changeScore>100)
    {
      
      if(currPredFrame > bRC->centerFrameBits)
      {        
        if(validQPs[QP_buffer] == 1)
        {
          
          bRC->lastQPUpdateID = mbNum;
          return MIN(50,MAX(2,QP_buffer));
        }
        else
        {
          int bestQP=originalQP,best_dist=51,dist;
          for(i=0;i<51;i++)
          {
            dist=51;
            
            if(validQPs[i]==1)
              dist=abs(i-QP_buffer);
            if(dist<best_dist)
            {
              bestQP=i;
              best_dist = dist;
            }
          }
          bRC->lastQPUpdateID = mbNum;
          return bestQP;            
        }        
      }
      else if(currPredFrame < bRC->centerFrameBits)
      {      
        
        if(validQPs[(int)QP_buffer] == 1)
        {
          bRC->lastQPUpdateID = mbNum;
          return MIN(50,MAX(2,QP_buffer));
        }
        else
        {
          int bestQP=originalQP,best_dist=51;
          bRC->lastQPUpdateID = mbNum;
          for(i=0;i<51;i++)
          {
            int dist=51;
            if(validQPs[i]==1)
              dist=abs(i-(int)QP_buffer);
            if(dist<best_dist)
            {
              bestQP=i;
              best_dist = dist;
            }
          }
          bRC->lastQPUpdateID = mbNum;
          return bestQP;
        }        
      }
    }
  }

  return originalQP;
}


static int getIFrameQP(rateCtrl_s *bRC)
{
  //Calculate the QP for the I Frame depending on Buffer Fullness, and Previous Coding History
  int i,bufferAvail,totalSamples=0,lastFrameQP,minBits=INT_MAX,maxBits=0,maxQP=0,minQP=0;
  float a=0.0f,b=0.0f,c=0.0f,d=0.0f,m,y;
  int finalQp;
  
  
  if(bRC->ignoreIDR == 1)
    return (int)(bRC->averageQPforFrame+1.5);
  
  bufferAvail = bRC->BufferSize - bRC->CurrentBufferFullness + bRC->bitsPerFrame;
  
  if(bufferAvail > bRC->I_P_RATIO * bRC->bitsPerFrame && bRC->numConsecutiveSkips == 0)
  {
    if(bRC->PictureIndex>0)
    {
      finalQp = (int)(bRC->averageQPforFrame+2);
      if(finalQp > bRC->frameComputedQP)
        bRC->frameComputedQP=MIN(bRC->frameComputedQP + 2, finalQp);
      else
        bRC->frameComputedQP=MAX(bRC->frameComputedQP - 2, finalQp);      
    }
    return bRC->frameComputedQP;
  }
  
  for(i=0;i<10;i++)
  {    
    if(bRC->IFrameBits[i]>maxBits)
    {
      maxBits = bRC->IFrameBits[i];
      maxQP = bRC->IFrameQP[i];
    }
    if(bRC->IFrameBits[i]<minBits)
    {
      minBits = bRC->IFrameBits[i];
      minQP = bRC->IFrameQP[i];
    }
    
    //Use all the buffer you have
    if(!(bRC->IFrameQP[i] == 0 || bRC->IFrameBits[i] == 0))
    {
      totalSamples++;
      a+=bRC->IFrameQP[i]*bRC->IFrameBits[i];
      b+=bRC->IFrameQP[i];
      c+=bRC->IFrameBits[i];
      d+=bRC->IFrameQP[i]*bRC->IFrameQP[i];
    }
  }
  m = (totalSamples*a-b*c)/(totalSamples*d - b*b);
  y = (c - m*b)/totalSamples;
  lastFrameQP = bRC->IFrameQP[0];
  
  if(m>=0)
  {
    //Remove the last Sample
    for(i=0;i<totalSamples-1;i++)
    {
      bRC->IFrameQP[i]=bRC->IFrameQP[i+1];
      bRC->IFrameBits[i]=bRC->IFrameBits[i+1];
    }
    bRC->IFrameQP[totalSamples - 1]=0;
    bRC->IFrameBits[totalSamples - 1]=0;
    
    totalSamples = 0;
    for(i=0;i<10;i++)
    {    
      if(bRC->IFrameBits[i]>maxBits)
        maxBits = bRC->IFrameBits[i];
      if(bRC->IFrameBits[i]<minBits)
        minBits = bRC->IFrameBits[i];
      
      //Use all the buffer you have
      if(!(bRC->IFrameQP[i] == 0 || bRC->IFrameBits[i] == 0))
      {
        totalSamples++;
        a+=bRC->IFrameQP[i]*bRC->IFrameBits[i];
        b+=bRC->IFrameQP[i];
        c+=bRC->IFrameBits[i];
        d+=bRC->IFrameQP[i]*bRC->IFrameQP[i];
      }
    }
    m = (totalSamples*a-b*c)/(totalSamples*d - b*b);
    y = (c - m*b)/totalSamples;
  }
  
  if(bRC->numConsecutiveSkips > 0)
    return lastFrameQP+1;
  
  if (m == 0)
    return lastFrameQP;
  
  
  if(totalSamples < 2)
  {
    if(bufferAvail > 1.2*bRC->IFrameBits[0])
      return bRC->IFrameQP[0]-1;
    else if(bufferAvail < 0.8*bRC->IFrameBits[0])
      return bRC->IFrameQP[0]+1;
    else
      return bRC->IFrameQP[0];
    
  }    
  
  //Interpolation is reliable
  else if(bufferAvail<maxBits && bufferAvail>minBits)
  {
    int calcQP = (int)MIN(51,MAX(0,(bufferAvail - y)/m));
    if(calcQP > bRC->IFrameQP[0])
      return MIN(calcQP, bRC->IFrameQP[0] + 2);
    else
      return MAX(calcQP, bRC->IFrameQP[0] - 2);
  }
  //Interpolation is unreliable
  else
  {
    if(bufferAvail>maxBits)
      return maxQP;
    else
      return minQP;
  }
}


static int checkFrameSkip(rateCtrl_s *bRC, int32 frmBits)
{
  if(bRC->img_type == SLICE_I && bRC->ignoreIDR == 1)
    return AVCE_OK;
  
  //Only regular frame Skipping is used
  if(bRC->frameSkipEnabled == 1)  
  {
    if(bRC->CurrentBufferFullness + frmBits - bRC->bitsPerFrame > bRC->BufferSize && !(bRC->numConsecutiveSkips > 2 && bRC->CurrentBufferFullness == 0))
    {     
      
      //Buffer overflow  
      bRC->PictureIndex++;
      bRC->CurrentBufferFullness-=bRC->bitsPerFrame;
      bRC->CurrentBufferFullness = MAX(0,bRC->CurrentBufferFullness);
      bRC->bitDifference = MAX(0,bRC->bitDifference-bRC->bitsPerFrame);
      bRC->stat_NumberofSkips++;
      bRC->numConsecutiveSkips++;
      return AVCE_FRAME_SKIPPED;
    }
    
    else
      return AVCE_OK;
  }
  
  return AVCE_OK;
}


void rc_free_mem(rateCtrl_s *bRC)
{
  
} 


static void computePFrameQP(rateCtrl_s *bRC, int img_type, int nalRefIdc,int srcPicNum)
{
  int finalQP=bRC->frameComputedQP;
  float m,t;
  int32 a=0,b=0;
  float c=0.0f, d=0.0f, e=0.0f;
  int i;
  int totalSamples=0;
  int modelQP;
  float modelQstep;
  int32 maxBits=0, minBits=INT_MAX;
  float maxQstep = 0.0f, minQstep = 1.0f;
  

  for(i=0;i<MAX_RD_WINDOW_SIZE;i++)
  {
    if(bRC->bitHistory[i] > 0 && bRC->qstepHistory[i]>0.0f && bRC->sadHistory[i]>0)
    {
      totalSamples++;

      a += bRC->bitHistory[i]*bRC->bitHistory[i];
      b += bRC->bitHistory[i];
      c += bRC->qstepHistory[i]*bRC->qstepHistory[i];
      d += bRC->qstepHistory[i];
      e += (float)bRC->bitHistory[i] * bRC->qstepHistory[i];
      
      if(bRC->bitHistory[i] > maxBits)
      {
        maxBits  = bRC->bitHistory[i];
        maxQstep = bRC->qstepHistory[i]; 
      }
      if(bRC->bitHistory[i] < minBits)
      {
        minBits  = bRC->bitHistory[i];
        minQstep = bRC->qstepHistory[i]; 
      }
    }
  }
  
  if(totalSamples < 3)
  {
    modelQstep = 0; //error
    modelQP = bRC->averageQPforFrame;
  }    
  else
  {
    m = (e - (b*d)/totalSamples) / (a - (b*b)/totalSamples);
    t = (d/totalSamples - b/totalSamples*m);
    
    if(m*bRC->centerFrameBits+t <= 0)
    {
      modelQstep = 0; //error
      modelQP = bRC->averageQPforFrame;
    }
    else
    {
      if(bRC->centerFrameBits > maxBits)
        modelQP = Qstep2QP(1.0f/maxQstep) - 2;      
      else if(bRC->centerFrameBits < minBits)
        modelQP = Qstep2QP(1.0f/minQstep) + 2;      
      else
      {
        modelQstep = 1 / (m*bRC->centerFrameBits+t);
        modelQP = Qstep2QP(modelQstep);
      }
    }
  }
  
  //Clip
  bRC->modelQP = modelQP;
  finalQP = modelQP;
  
  if(finalQP > bRC->frameReturnedQP && bRC->averageQPforFrame > bRC->frameReturnedQP)
    finalQP=MIN(bRC->frameComputedQP + 2, finalQP);
  else if(finalQP > bRC->frameReturnedQP && bRC->averageQPforFrame <= bRC->frameReturnedQP)
    finalQP=(int)(MIN(bRC->averageQPforFrame + 2, finalQP));
  else if(finalQP <= bRC->frameReturnedQP && bRC->averageQPforFrame <= bRC->frameReturnedQP)
    finalQP=MAX(bRC->frameComputedQP - 2, finalQP);
  else if(finalQP <= bRC->frameReturnedQP && bRC->averageQPforFrame > bRC->frameReturnedQP)
    finalQP=(int)(MAX(bRC->averageQPforFrame , finalQP));
  
  bRC->frameComputedQP=MIN(50,finalQP+bRC->numConsecutiveSkips);
  bRC->frameComputedQP=MAX(1,finalQP-bRC->numConsecutiveUnderflows);
  
  if(bRC->prevFrameScut==1 )
  {
    clearRCHistory(bRC);
    bRC->frameComputedQP = MIN(50,bRC->InitialQP+1+bRC->numConsecutiveSkips*2);
  }
}


static int Qstep2QP( float Qstep )
{
  int q_per = 0, q_rem = 0;
  

  if( Qstep < QP2Qstep(0))
    return 0;
  else if (Qstep > QP2Qstep(51) )
    return 51;
  
  while( Qstep > QP2Qstep(5) )
  {
    Qstep /= 2;
    q_per += 1;
  }
  
  if (Qstep <= (0.625+0.6875)/2) 
  {
    Qstep = 0.625f;
    q_rem = 0;
  }
  else if (Qstep <= (0.6875+0.8125)/2)
  {
    Qstep = 0.6875f;
    q_rem = 1;
  }
  else if (Qstep <= (0.8125+0.875)/2)
  {
    Qstep = 0.8125f;
    q_rem = 2;
  }
  else if (Qstep <= (0.875+1.0)/2)
  {
    Qstep = 0.875f;
    q_rem = 3;
  }
  else if (Qstep <= (1.0+1.125)/2)
  {
    Qstep = 1.0f;  
    q_rem = 4;
  }
  else 
  {
    Qstep = 1.125f;
    q_rem = 5;
  }
  
  return (q_per * 6 + q_rem);
}


static float QP2Qstep( int QP )
{
  int i; 
  float Qstep;
  static const float QP2QSTEP[6] = { 0.625f, 0.6875f, 0.8125f, 0.875f, 1.0f, 1.125f };
  
  
  Qstep = QP2QSTEP[QP % 6];
  for( i=0; i<(QP/6); i++)
    Qstep *= 2;
  
  return Qstep;
}


static void clearRCHistory(rateCtrl_s *bRC)
{
  int i;
  for(i=0;i<MAX_RD_WINDOW_SIZE;i++)
  {
    bRC->bitHistory[i] =  0;
    bRC->qstepHistory[i] = 0.0f;
    bRC->sadHistory[i] = 0;
  }
  bRC->numConsecutiveUnderflows = 0;
  
}


#ifdef RC_DEBUG
void rc_printDebug(rateCtrl_s *bRC,statSlice_s *frmStat)
{
  fprintf(bRC->rcdebug,"%6d\t%6d\t%6d\t  %6d\t %6d\t %6d\t %6d\t %6d\t %.2f\t %6d\t %6d\t %6d\t%6d\t%6d\n",
    bRC->srcPicNum,
    bRC->PictureIndex,
    staGetTotalBits(frmStat),
    bRC->TargetBufferLevel,
    bRC->CurrentBufferFullness,
    bRC->frameReturnedQP,
    bRC->averageQPforFrame,
    bRC->QP_LW ,
    bRC->QP_SW,
    frmStat->psnrY,
    bRC->upperFrameLimit,
    bRC->lowerFrameLimit,
    bRC->nalRefIdc,
    bRC->bitsPerPFrame    
    );
}

#endif
#endif

