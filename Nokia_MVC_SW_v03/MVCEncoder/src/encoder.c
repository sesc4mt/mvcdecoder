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
 *   encoder.c
 *
 * Contains:
 *    Encoder main function.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include "avcencoder.h"
#include "globals.h"

long scdSceneCut();

#define MAX_FILENAME_LEN      200
#define SEPARATE_YUV_FILES    0
#define COMBINED_YUV_FILE     1
#define MAX_FRM_NUM           ((1 << 30) - 1)

#define USE_MVC 1

#define  clip(min, max, val) (((val)<(min))? (min):(((val)>(max))? (max):(val)))

/* YUV raw video file structure */
typedef struct _videoFile_s
{
  int format;
  FILE *y;
  FILE *u;
  FILE *v;
} videoFile_s;

/* Parameters from user (command line) */
typedef struct _userParam_s
{
  char origFileName[256];
  char origFileName2[256];

  char outFileName[256];
  char recoFileName[256];
  char cumuFileName[256];
  char scutFileName[256];

  int  seqFormat;
  int  recoFormat;
  int  startFrm;
  int  numFrms;
  int  frmSkip;
  int  intraFreq;
  int  idrFreq;
  int  numNonref;
  int  qpNonref;
  int  qpIntra;
  int  qpInter;
  int  qpInter2;
  int  q2Start;

  int  ltrIdr;             // IDR image will always become long term ref
  int  ltrStart;
  int  ltrFreq;

  char fScenecut;//Scenecut
  char fScenecut_Create;
  char fScenecutSei;
  int  minIdrDistance;
  int  Sumy, Sumuv;
  FILE *scutfile;
  int  viewPrediction;
  int  PTqp;
  double BR, Bsize, bmax, bmin, *Buffer;
  int  fInfo;
  int  fSRC_Create;

#ifdef ENABLE_SEARCH_WINDOW
  int  srx;     // motion vector restriction
  int  sry;
#endif

} userParam_s;

/*
 * Definition for command line parsing
 */

/* Command flag and type definitions */
#define CMD_FLAG                0
#define CMD_INT                 1
#define CMD_STR                 2

/* Structure holds a command from command line */
typedef struct _cmdEntry_s
{
  int  flag;        // flag = 1, if the command appears on the command line
  int  type;        // 0, integer, 1, string, 2, no data to follow
  char id[32];      // should be long enough
  int  defaultData; // valid only if type != CMD_STR
  void *data;

  struct _cmdEntry_s *next;
} cmdEntry_s;

typedef struct _cmdBuf_s
{
  int numCmds;
  cmdEntry_s *head;
  cmdEntry_s *current;
} cmdBuf_s;

/*
 * Static function prototypes
 */
static void usage(void);

static int parseModes(char *modeString);

static void printSeqStat(avceEncoder_t *encoder, int qpIntra,
                         int qpInter, int frameRateTimes1000, int numSkippedFrames, FILE *fp);

static void dumpStatistics(avceEncoder_t *encoder, int frameRateTimes1000, int numSkippedFrames);

static void allocOrigFrame(avceYUVbuffer_s *buf, int width, int height);

static void freeOrigFrame(avceYUVbuffer_s *buf);

static int openVideoFiles(userParam_s *param, videoFile_s *origFile,videoFile_s *origFile2, 
                          videoFile_s *recoFile, FILE **stream);

static void closeFiles(videoFile_s *origFile, videoFile_s *origFile2,	
					   videoFile_s *recoFile,
                       int recoFlag, FILE *stream);

static int readFrame(avceYUVbuffer_s *buf, int width, int height,
                     videoFile_s *inFile, int frameIdx);

static void writeFrame(avceYUVbuffer_s *buf, avceOpenParams_s *seqParam,
                       videoFile_s *outFile, int frameIdx);



//Scut
static void ScutCheck(userParam_s *param) 
{
  int sfn, frame, type; 

  sfn = 0;
  while (fscanf(param->scutfile,"%d:%1d\n",&frame,&type) != EOF) {
    sfn = frame;
  }
  rewind(param->scutfile);

  frame = param->numFrms - 1;
  if (sfn < frame ) {
    param->fScenecut_Create = 1;	
    fclose(param->scutfile);
    if((param->scutfile = fopen(param->scutFileName,"w")) == NULL) {
      param->fScenecut = 0;
      param->fScenecut_Create = 0;
    }	
  }
  else 
    param->fScenecut_Create = 0;		
}


/*
 * usage:
 *
 * Parameters:
 *      -
 *
 * Function:
 *      Print encoder usage information.
 *
 * Returns:
 *      -
 */
static void usage(void)
{
  fprintf(stdout,
    "Encoder arguments:\n"
    "  [-h]                     To get this help screen. \n"
    "   -inyuv <file name>      Input Y,U,V in one file            [default none]\n"
    "   -in2 <file name>        Input left eye view                [default none]\n"
    "   -out <file name>        Output bitstream name              [default none]\n"
    "  [-level <value>]         AVC level times 10                 [default none]\n"
    "                           Found automatically, if not provided             \n"

    "  [-width <value>]         Picture width in pixels            [default 176]\n"
    "  [-height <value>]        Picture height in pixels           [default 144]\n"
    "  [-intraview]             Inter-view prediction off          [default disabled]\n"
    "                           (only intra-view prediction)\n"
    "  [-qcif]                  Set picture size 176x144\n"
    "  [-cif]                   Set picture size 352x288\n"
    "  [-start <value>]         First frame number                 [default 0]\n"
    "  [-skip <value>]          Number of skipped frames           [default 2]\n"
    "                           target frame rate = origfps/(skip+1)\n"
    "  [-frames <value>]        Number of frames to be encoded     [default 2^31-1]\n"
    "  [-origfps <value>]       Original frame rate                [default 30]\n"
    "  [-IpP <value>]           Insert non-reference frames        [default 0]\n"
    "                           between reference frames.\n"
    "                           0,    no non-reference frame.\n"
    "                           <= 8, number of non-ref frames.\n"
    "  [-qNonref <value>]       qp of non-reference frames.        [default q]\n"
    "                           Same as ""q"", if not provided.\n"
    "  [-tuneIntra <value>]     Tune intra frame quality.          [default 256]\n"
    "  [-tuneInter <value>]     Tune inter frame quality.          [default 256]\n"
    "  [-tuneNonref <value>]    Tune non-reference frame quality.  [default 256]\n"
    "                           For the 3 switches above:\n"
    "                           Take effect only when ""-rdo 1"".\n"
    "                           > 1024, smaller frame size.\n"
    "                           < 1024, higher quality.\n"
    "  [-intraFreq <value>]     How often intra frame is inserted  [default 0]\n"
    "                           0, only first frame is intra.\n"
    "  [-idrFreq <value>]       How often IDR frame is inserted    [default 0]\n"
    "                           0, only first frame is IDR.\n"
    "                           If -intraFreq is defined, idrFreq must\n"
    "                           be larger than or equal to intraFreq.\n"
    "                           First frame must be intra and IDR.\n"
    "  [-qintra <value>]        Luma QP for I frame                [default 32]\n"
#ifdef ENABLE_SEARCH_WINDOW
    "  [-srx <value>]           Hori. motion vector restriction    [default disable]\n"
    "  [-sry <value>]           Vert. motion vector restriction    [default disable]\n"
#endif
    "  [-q <value>]             Luma QP for P frames               [default 32]\n"
    "  [-q2Start <value>]       Use q2 after q2Start frames        [default 2^31-1]\n"
    "                           Index to frames actually encoded.\n"
    "                           Not to the source video clip.\n"
    "  [-q2 <value>]            Luma QP for second part of clip.   [default q]\n"
    "                           Same as ""q"", if not provided.\n"
    "  [-cumul <file name>]     Write statistics to file           [default none]\n"
    "  [-reco <file name>]      Output Y,U,V in separate files     [default none]\n"
    "  [-recoyuv <file name>]   Output Y,U,V in one file           [default none]\n"
    "  [-scIntra <value>]       Encode a scene cut image as an     [default 0]\n"
    "                           intra frame. This scene cut\n"
    "                           information is from coding results.\n"
    "                           0, no effect.\n"
    "                           1, convert only all MBs are intra.\n"
    "                           2, more aggressive conversion.\n"
    "  [-ltrIdr]                IDR used as a long term ref frame. [default disabled]\n"
    "  [-ltrStart <value>]      First frame to be used as          [default 0]\n"
    "                           a long term reference frame.\n"
    "  [-ltrFreq <value>]       Use a reconstructed frame as       [default 0]\n"
    "                           a long term reference frame for\n"
    "                           every ""ltrFreq"" frames\n"
    "                           0, no long term reference frame.\n"
    "                           Maximally 1 long term ref frame.\n"
    "  [-rframes <value>]       Number of reference frames.        [default 1]\n"
    "                           0, all frames are coded intra.\n"
    "  [-maxFrameNum <value>]   Specify log2_max_frame_num_minus4  [default 0]\n"
    "  [-modes <mode string>]   Block sizes to be used.            [default 1111111]\n"
    "                           0, corresponding mode is disbaled,\n"
    "                           1, corresponding mode is enabled.\n"
    "                           Order of the modes is:\n"
    "                           16x16 16x8 8x16 8x8 8x4 4x8 4x4\n"
    "  [-range <value>]         Max search range in  ME            [default 16]\n"
    "                           motion estimation.\n"
    "  [-qindex <value>]        Chroma QP index [-12,12]           [default 0]\n"
    "                           Adjustment of chroma QP relative to luma QP\n"
    "  [-constipred]            Enable constrained intra pred,     [default disabed]\n"
    "                           i.e. no intraprediction from inter macroblocks.\n"
    "  [-filtermode <value>]    Loopfilter mode                    [default 0]\n"
    "                           0, enabled\n"
    "                           1, disabled\n"
    "                           2, disabled on slice boundaries\n"
    "  [-alpha <value>]         Loopfilter alpha offset [-6,6]     [default 0]\n"
    "  [-beta <value>]          Loopfilter beta offset [-6,6]      [default 0]\n"
    "  [-mfield]                Show motion field in               [default none]\n"
    "                           recontruction frames.\n"
    "  [-sgmType <value>]       Slice group map (SGM) type [0, 6]  [default 0]\n"
    "  [-sgmCount <value>]      # of slices groups in a frame      [default 1]\n"
    "  [-sgmParams <v0> <...>]  SGM parameters, up to 8 values\n"
    "                           Type 0, run lengths,\n"
    "                           Type 2, (UpperLeft, lowerRight) pairs,\n"
    "                           Type 3 4 5, direction and change rate,\n"
    "  [-mbsperslice <value>]   Number of macroblocks per slice,   [default 0]\n"
    "                           0 means one slice\n"	
    "  [-targetbytesperslice <value>] Desired number of bytes per  [default 0]\n"
    "                           slice, 0 means one slice\n"	
    "  [-maxbytesperslice <value>] Maximum number of bytes per     [default 0]\n"
    "                           slice, 0 means one slice\n"	
    "  [-br <value>]            Bit rate of compressed bitstream   [default 0]\n"
    "                           0, disable BRC, qintra & q are used,\n"
    "                           nonzero, enable BRC at this bit rate,\n" 
    "                           qintra & q are reference values,\n"
    "  [-brcBufSize <value>]    Size of encoder virtual buffer     [default max.]\n"
    "                           verifier in bytes\n"
    "  [-brcQPStart <value>]    First Frame QP used by Rate Control[default 0]\n"
    "                           If not specified encoder estimates \n"
    "                           according to bitrate \n"
    "  [-brcFrameSkipsEnabled <value>] Rate Control algorithm      [default 1]\n"
    "                           skips frames to avoid buffer overflow\n"
    "                           0, Frame Skipping is not allowed\n"
    "                           1, Frame Skipping is allowed\n"
    "                           2, Advanced Frame Skipping algorithm\n"
    "  [-brcIgnoreIDRBits <value>] Rate Control algorithm          [default 0]\n"
    "                           does not take into account intraframe bits\n"
    "                           0: Not Ignored\n"
    "                           1: Only Ignored in low delay\n"
    "                           2: Forced to Ignore\n"
    "  [-brcdisableMBLevel]     Disable MB Level Rate Control      [default enabled]\n"
    "  [-brcuseSEI]             Put timing and buffer related,     [default disabled]\n"
    "                           messages to the bitstream\n"
    "  [-prof <value>]          Encoder quality setting            [default 0]\n"
    "                           0, favor coding efficiency\n"
    "                           1, favor encoding speed\n"
///// LOW_COMPLEX_PROF3
    "                           2, more favor encoding speed\n"
/////
//// LOW_COMPLEX_PROF4
    "                           3, favor speed more\n"
//// 
#ifndef DISABLE_RDO
    "  [-rdo <value>]           Rate distortion optimization       [default 1]\n"
    "                           0, disable RDO\n"
    "                           1, enable RDO\n"
#endif
    "  [-crop <L> <R> <T> <B>]  Output frame croppping.            [default all 0]\n"
    "                           <L>, frame_crop left offset.\n"
    "                           <R>, frame_crop right offset.\n"
    "                           <T>, frame_crop top offset.\n"
    "                           <B>, frame_crop bottom offset.\n"
    "                           Odd values will be changed to even.\n"
    "  [-scut <file name>]      Scenecut file name.\n"
    "                           Automatic generation if file not found.\n"
    "  [-sceneInfo]             Generate the scene info SEI messages.\n"
    "  [-IR_Type <value>]       Enables Intra Refresh             [default disabled].\n"
    "                           0: disabled\n"
    "                           1: AIR based on Distortion Tracking\n"
    "                              (use with -PLR)\n"
    "                           2: 1 with complexity/delay optimizations \n"
    "                              (use with -nAIR, -PLR)\n"
    "                           3: Random Intra Refresh \n"
    "                              (use with -nRIR)\n"
    "  [-PLR <value>]           Packet loss rate                   [default 0].\n"
    "                           Used with IR_Type: 1\n"
    "  [-nAIR <value>]          Number of INTRA-MBs adaptively placed\n"
    "                           Used with IR_Type: 2\n"
    "  [-nRIR <value>]          Number of INTRA-MBs randomly placed\n"
    "                           Used with IR_Type: 3\n"
    "  [-redundantPic <value>]  Encode redundant picture. QP of    [default none]\n"
    "                           redundant picture will be QP of\n"
    "                           primary picture plus <value>.\n"
    "  [-info]                  Printout Info.\n"
    "  [-rtp]                   RTP Packetized Output\n"
    );
}


/*
 * parseModes:
 *
 * Parameters:
 *      modeString            String containing '1' for enabled motion mode
 *                            and '0' bit for disabled motion mode
 *
 * Function:
 *      Convert mode string to integer number
 *
 * Returns:
 *      Integer containing mode bits
 */
static int parseModes(char *modeString)
{
  int modes;
  int i;

  if (strlen(modeString) > 7)
    return -1;

  modes = 0;

  for (i = 0; i < (int)strlen(modeString); i++) {
    if (modeString[i] == '1')
      modes |= (1 << i);
    else if (modeString[i] != '0')
      return -1;
  }

  return modes;
}


/*
 * insertCmd:
 *
 * Parameters:
 *      cmdEntry              Command structure
 *      type                  Command type (integer or string)
 *      defaultData           Default value if the command does not appear
 *      cmdId                 Command string
 *      dataBuf               Command parameter
 *
 * Function:
 *      Put a command in the command buffer structure.
 *
 * Returns:
 *      -
 */
static void insertCmd(cmdBuf_s *cmdBuf,
                      int      type,
                      int      defaultData,
                      char     *cmdId, 
                      void     *dataBuf)
{
  cmdEntry_s *newEntry;

  newEntry = (cmdEntry_s *) malloc(sizeof(cmdEntry_s));
  newEntry->type = type;
  strcpy(newEntry->id, cmdId);
  newEntry->data = dataBuf;

  if (type != CMD_STR)
    * ((int *) newEntry->data) = defaultData;

  cmdBuf->current->next = newEntry;
  cmdBuf->current = newEntry;

  cmdBuf->numCmds ++;
}


/*
 * getCmdBuf:
 *
 * Parameters:
 *      up                    Parameter from user 
 *      sp                    Parameter from user to be passed to AVC decoder
 *
 * Function:
 *      Allocate and initialize the command buffer, which is used in parsing 
 *      the input commands.
 *      The buffer is a link list so that the user does not need to worry 
 *      about how the buffer entries are maintained. Each entry in the list
 *      contains command ID, type, command data buffer, and default value.
 *
 * Returns:
 *      command buffer allocated.
 */
static cmdBuf_s *getCmdBuf(userParam_s      *up,
                           avceOpenParams_s *sp)
{
  int i;
  cmdBuf_s *cmdBuf;

  if ((cmdBuf = malloc(sizeof(cmdBuf_s))) == 0)
    return 0;

  cmdBuf->numCmds = 0;

  // we have an empty slot
  cmdBuf->head    = (cmdEntry_s *) malloc(sizeof(cmdEntry_s));
  strcpy(cmdBuf->head->id, "xxHeadxx");
  cmdBuf->current = cmdBuf->head;
  cmdBuf->current->next = 0;

  // a string should follow the command
  insertCmd(cmdBuf, CMD_STR, 0,       "-cumul",      up->cumuFileName);
  insertCmd(cmdBuf, CMD_STR, 0,       "-out",        up->outFileName);
  insertCmd(cmdBuf, CMD_STR, 0,       "-scut",        up->scutFileName);

  // an integer should follow the command
  insertCmd(cmdBuf, CMD_INT, 0,       "-start",      & up->startFrm);
  insertCmd(cmdBuf, CMD_INT, 2,       "-skip",       & up->frmSkip);
  insertCmd(cmdBuf, CMD_INT, INT_MAX, "-frames",     & up->numFrms);
  insertCmd(cmdBuf, CMD_INT, 0,       "-IpP",        & up->numNonref);
  insertCmd(cmdBuf, CMD_INT, 32,      "-qintra",     & up->qpIntra);
  insertCmd(cmdBuf, CMD_INT, 32,      "-q",          & up->qpInter);
  insertCmd(cmdBuf, CMD_INT, -1,      "-qNonref",    & up->qpNonref);
  insertCmd(cmdBuf, CMD_INT, 0,       "-intraFreq",  & up->intraFreq);
  insertCmd(cmdBuf, CMD_INT, 0,       "-idrFreq",    & up->idrFreq);
  insertCmd(cmdBuf, CMD_INT, INT_MAX, "-q2Start",    & up->q2Start);
  insertCmd(cmdBuf, CMD_INT, -1,      "-q2",         & up->qpInter2);
  insertCmd(cmdBuf, CMD_FLAG, 0,      "-ltrIdr",     & up->ltrIdr);
  insertCmd(cmdBuf, CMD_INT, 0,       "-ltrStart",   & up->ltrStart);
  insertCmd(cmdBuf, CMD_INT, 0,       "-ltrFreq",    & up->ltrFreq);
  insertCmd(cmdBuf, CMD_FLAG, 0,      "-sceneInfo",  & up->fScenecutSei);
  insertCmd(cmdBuf, CMD_INT, 0,       "-idrAdap",    & up->minIdrDistance);

  insertCmd(cmdBuf, CMD_INT, 176,     "-width",      & sp->picWidth);
  insertCmd(cmdBuf, CMD_INT, 144,     "-height",     & sp->picHeight);
  insertCmd(cmdBuf, CMD_FLAG, 1,      "-intraview",  & sp->viewPrediction);
  insertCmd(cmdBuf, CMD_INT, 256,     "-tuneIntra",  & sp->tuneIntra);
  insertCmd(cmdBuf, CMD_INT, 256,     "-tuneInter",  & sp->tuneInter);
  insertCmd(cmdBuf, CMD_INT, 256,     "-tuneNonref", & sp->tuneNonref);
  insertCmd(cmdBuf, CMD_INT, 0,      "-level",      & sp->level);
  insertCmd(cmdBuf, CMD_INT, 16,      "-range",      & sp->range);
  insertCmd(cmdBuf, CMD_INT, 1,       "-rangeMod",   & sp->rangeMod);
  insertCmd(cmdBuf, CMD_INT, 0,       "-prof",       & sp->profile);
#ifndef DISABLE_RDO
  insertCmd(cmdBuf, CMD_INT, 1,       "-rdo",        & sp->rdo);
#endif
  insertCmd(cmdBuf, CMD_INT, 0,       "-filtermode", & sp->filterMode);
  insertCmd(cmdBuf, CMD_INT, 0,       "-br",         & sp->brcBitRate);
  insertCmd(cmdBuf, CMD_INT, 0,       "-brcBufSize", & sp->brcBufSize);
  insertCmd(cmdBuf, CMD_FLAG, 0,      "-brcuseSEI",  & sp->useSEIMessages);
  insertCmd(cmdBuf, CMD_FLAG, 0,      "-brcdisableMBLevel",&sp->brcdisableMBLevel);
//  insertCmd(cmdBuf, CMD_INT, 1,       "-brcFrameSkipsEnabled",  & sp->frameSkipEnabled);
  insertCmd(cmdBuf, CMD_INT, 0,       "-brcFrameSkipsEnabled",  & sp->frameSkipEnabled);
  insertCmd(cmdBuf, CMD_INT, 0,		    "-brcQPStart", & sp->qpStart);
  insertCmd(cmdBuf, CMD_INT, 0,       "-brcIgnoreIDRBits",  & sp->ignoreIDRBits);
  insertCmd(cmdBuf, CMD_INT, 1,       "-sgmCount",   & sp->sgmCount);
  insertCmd(cmdBuf, CMD_INT, 0,       "-sgmType",    & sp->sgmType);
  insertCmd(cmdBuf, CMD_INT, 0,       "-alpha",      & sp->alphaOffset);
  insertCmd(cmdBuf, CMD_INT, 0,       "-beta",       & sp->betaOffset);
  insertCmd(cmdBuf, CMD_INT, 0,       "-qindex",     & sp->chromaQpIdx);
  insertCmd(cmdBuf, CMD_INT, 1,       "-rframes",    & sp->maxNumRefFrms);
  insertCmd(cmdBuf, CMD_INT, 0,       "-mbsperslice", & sp->nMbsPerSlice);  
  insertCmd(cmdBuf, CMD_INT, 0,       "-targetbytesperslice", & sp->nBytesPerSlice);
  insertCmd(cmdBuf, CMD_INT, 0,       "-maxbytesperslice",& sp->maxBytesPerSlice); // Default: nBytesPerSlice
  insertCmd(cmdBuf, CMD_INT, 0,       "-maxFrameNum",& sp->log2_max_frame_num_minus4);
  insertCmd(cmdBuf, CMD_INT, 0,       "-scIntra",    & sp->scIntra);
#ifdef ENABLE_SEARCH_WINDOW
  insertCmd(cmdBuf, CMD_INT, -1,      "-srx",        & up->srx);
  insertCmd(cmdBuf, CMD_INT, -1,      "-sry",        & up->sry);
#endif
  // only set a flag, does not need additional parameter on command line
  insertCmd(cmdBuf, CMD_FLAG, 0,      "-constipred",& sp->constIpred);
  insertCmd(cmdBuf, CMD_FLAG, 0,      "-mfield",    & sp->makeMotField);
  insertCmd(cmdBuf, CMD_INT, 0,       "-PLR",       & sp->plr);
  insertCmd(cmdBuf, CMD_INT, 0,       "-IR_Type",   & sp->irType);
  insertCmd(cmdBuf, CMD_INT, 0,       "-nAIR",      & sp->nAIR); //AIR_Simple - num AIR MB's to be put
  insertCmd(cmdBuf, CMD_INT, 0,       "-nRIR",      & sp->nRandomIntraRefresh);
  insertCmd(cmdBuf, CMD_FLAG, 0,      "-rtp",        & sp->rtp_flag);

  // ternimate the list
  cmdBuf->current->next = 0;
  cmdBuf->current = cmdBuf->head->next;

  /*
  * Set default file and sequence parameters
  */

  // make these strings of zero length, 
  // the length will be used to determine whether string has been changed
  up->origFileName[0]  = 0;
  up->origFileName2[0]  = 0;
  up->outFileName[0]   = 0;
  up->recoFileName[0]  = 0;
  up->cumuFileName[0]  = 0;
  up->scutFileName[0]  = 0;
  up->seqFormat        = SEPARATE_YUV_FILES;
  up->recoFormat       = SEPARATE_YUV_FILES;
  up->fScenecut        = 0;//Scene Cut
  up->fScenecut_Create = 0;
  up->scutfile         = NULL;
  up->fInfo            = 0;

  sp->origFpsTimes1000 = 30000;
  sp->modeFlags        = 0x3f;

  sp->qpInter          = 26;
///// LOW_COMPLEX_PROF3
  sp->low_complex_prof3=0;
//////

  for (i = 0; i < 4; i ++)
    sp->cropOffsets[i] = 0;

  sp->redundantPicFlag = 0;

  return cmdBuf;
}

// the config file can not have more than 256 commands
#define MAX_CFG_COMMANDS      256
#define MAX_CFG_LINE_WIDTH    256


/*
 * readOneCfgLine:
 *
 * Parameters:
 *      input                 Input config file
 *      oneString             Buffer to store the line
 *      maxStringLen          Max string length allowed
 *
 * Function:
 *      Read one line from the config file. 
 *
 * Returns:
 *      Length of the line.
 */
int readOneCfgLine(FILE *input, 
                   char *oneString,
                   int  maxStringLen)
{
  int oneCh;
  int strLen;


  strLen = 0;
  do
  {
    if ((oneCh = fgetc(input)) < 0)
      break;
    
    oneString[strLen ++] = (char) oneCh;
  } while ((oneCh != '\n') && (strLen < maxStringLen - 1));

  oneString[strLen] = 0;    // to terminate the string

  return strLen;
}


/*
 * formatLine:
 *
 * Parameters:
 *      oneString             Config file that contains parameter strings
 *
 * Function:
 *      Format the string to make it easier to parse. 
 *
 * Returns:
 *      Length of the formatted string.
 */
int formatLine(char *oneString)
{
  int stringLen, i;

  
  stringLen = (int) strlen(oneString);

  // find the first # sign, which tells the position where comments start
  i = 0;
  while ((i < stringLen) && (oneString[i] != '#'))
    i ++;

  // truncate the string here
  oneString[i] = 0;
  stringLen = i;

  // remove ending blank
  while ((stringLen > 0) && (oneString[stringLen - 1] <= ' '))
    stringLen --;

  oneString[stringLen] = 0;

  // remove leading blank
  i = 0;
  while ((i < stringLen) && (oneString[i] <= ' '))
    i ++;

  stringLen -= i;
  if (stringLen > 0)
    strcpy(oneString, oneString + i);
  
  return stringLen;
}


/*
 * readConfigFile:
 *
 * Parameters:
 *      cfgFile               Config file that contains parameter strings
 *      argv                  Buffer where the parameter strings are stored
 *      maxCfgCmds            Maximal number of strings that are allowed
 *
 * Function:
 *      Read the parameter strings from a config file to an array. 
 *
 * Returns:
 *      Actual number of parameter strings read from the config file.
 */
int readConfigFile(FILE *cfgFile, 
                   char **argv, 
                   int  maxCfgCmds)
{
  int  argc;
  char oneLine[MAX_CFG_LINE_WIDTH];

  
  argc = 0;
  while (readOneCfgLine(cfgFile, oneLine, MAX_CFG_LINE_WIDTH))
  {
    int lineLen;

    if ((lineLen = formatLine(oneLine)) > 0)
    {
      char token[128];
      char *linePtr;

      linePtr = oneLine;
      while ((sscanf(linePtr, "%s", token) > 0) && (argc < maxCfgCmds))
      {
        argv[argc] = (char *) malloc(128);
        strcpy(argv[argc], token);
        linePtr += strlen(token);
        while ((linePtr[0] <= ' ') && (linePtr < (oneLine + lineLen)))
          linePtr ++;

        argc ++;
      }
    }
  }

  return argc;
}


/*
 * calculateMinPocBits:
 *
 * Parameters:
 *      frmSkip               Number of frames skipped in the input clip
 *      numNonref             Number of non-reference frames inserted
 *
 * Function:
 *      Calculate the minimal number of bits needed to store LSBs of POC
 *      (Picture Order Count). 
 *
 * Returns:
 *      0 error
 *      1 ok
 */
int calculateMinPocBits(int frmSkip, 
                        int numNonref)
{
  int maxPocMbs, minPocBits;

  
  // maxPocMbs should be larger than twice of maximal increase in POC
  maxPocMbs = 2 * ((frmSkip + 1) * (numNonref + 1) + 1);

  minPocBits = 0;
  while (maxPocMbs)
  {
    maxPocMbs >>= 1;
    minPocBits ++;
  }

  return minPocBits;
}


/*
 * parseArg:
 *
 * Parameters:
 *      sp                    Coding parameters, used in this module & encoder
 *
 * Function:
 *      Check the cropping parameters. Perform correction if any parameters 
 *      are illegal.
 *
 * Returns:
 *      0 error
 *      1 ok
 */
void validateCroppingOffsets(avceOpenParams_s *sp)
{
  int i;

  
  for (i = 0; i < 4; i ++)
    sp->cropOffsets[i] = (sp->cropOffsets[i] >> 1) << 1;

  if ((sp->cropOffsets[0] < 0) || (sp->cropOffsets[1] < 0) ||
    (sp->cropOffsets[2] < 0) || (sp->cropOffsets[3] < 0) ||
    ((sp->cropOffsets[0] + sp->cropOffsets[1]) > sp->picWidth) ||
    ((sp->cropOffsets[2] + sp->cropOffsets[3]) > sp->picHeight))
  {
    for (i = 0; i < 4; i ++)
      sp->cropOffsets[i] = 0;
  }
}


// make a the smallest number larger or equal to a, and multiple of b
#define ROUND_UP(a, b)    ((((a) + (b) - 1)/(b)) * (b))


/*
 * parseArg:
 *
 * Parameters:
 *      cmdBuf                Buffer for storing the parsed commands
 *      argc                  Number of the input strings
 *      argv                  Array contains the input strings
 *      param                 User parameters, only used in this module
 *      seqParam              Coding parameters, used in this module & encoder
 *
 * Function:
 *      Parse encoder parameters
 *
 * Returns:
 *      0 error
 *      1 ok
 */
static int parseArg(cmdBuf_s         *cmdBuf,
                    int              argc, 
                    char             **argv, 
                    userParam_s      *param,
                    avceOpenParams_s *seqParam)
{
  int   i;
  float origFps;
  

  /*
  * Read all parameters
  */
  for (i = 1; i < argc; i++) {

    if (strcmp(argv[i], "-in") == 0) {
      if (++i == argc) {
        return 0;
      }
      param->seqFormat = SEPARATE_YUV_FILES;
      strcpy(param->origFileName, argv[i]);
    }
    else if (strcmp(argv[i], "-inyuv") == 0) {
      if (++i == argc) {
        return 0;
      }
      param->seqFormat = COMBINED_YUV_FILE;
      strcpy(param->origFileName, argv[i]);
    }
    else if (strcmp(argv[i], "-in2") == 0) {
      if (++i == argc) {
        return 0;
      }
      param->seqFormat = COMBINED_YUV_FILE;
      strcpy(param->origFileName2, argv[i]);
    }
    else if (strcmp(argv[i], "-intraview") == 0) {
      seqParam->viewPrediction = 0;
    }
    else if (strcmp(argv[i], "-reco") == 0) {
      if (++i == argc) {
        return 0;
      }
      param->recoFormat = SEPARATE_YUV_FILES;
      strcpy(param->recoFileName, argv[i]);
    }
    else if (strcmp(argv[i], "-recoyuv") == 0) {
      if (++i == argc) {
        return 0;
      }
      param->recoFormat = COMBINED_YUV_FILE;
      strcpy(param->recoFileName, argv[i]);
    }
    else if (strcmp(argv[i], "-qcif") == 0) {
      seqParam->picWidth  = 176;
      seqParam->picHeight = 144;
    }
    else if (strcmp(argv[i], "-cif") == 0) {
      seqParam->picWidth  = 352;
      seqParam->picHeight = 288;
    }
    else if (strcmp(argv[i], "-origfps") == 0) {
      i++;
      if (i == argc || (sscanf(argv[i], "%f", &origFps) != 1)) {
        return 0;
      }
      seqParam->origFpsTimes1000 = (int)(1000*origFps);
    }
    else if (strcmp(argv[i], "-modes") == 0) {
      i++;
      if (i == argc || (seqParam->modeFlags = parseModes(argv[i])) < 0) {
        return 0;
      }
    }
    else if (strcmp(argv[i], "-sgmParams") == 0) {
      i ++;

      // read up to 8 parameters, and move to next switch
      seqParam->numSgmParams = 0;
      while (i < argc) {
        if (argv[i][0] == '-')
        {
          // see the next switch
          i --;   // will be incremented later
          break;
        }
        
        if (seqParam->numSgmParams < MAX_SLICE_PARAMS)
        {
          seqParam->sgmParams[seqParam->numSgmParams] = atoi(argv[i]);
          seqParam->numSgmParams ++;
        }
        i ++;
      }
    }
    else if (strcmp(argv[i], "-crop") == 0) {
      int numParams;

      i ++;

      // read up to 8 parameters, and move to next switch
      numParams = 0;
      while (i < argc) {
        if (argv[i][0] == '-')
        {
          // see the next switch
          i --;   // will be incremented later
          break;
        }
        
        if (seqParam->numSgmParams < 4)
        {
          seqParam->cropOffsets[numParams] = atoi(argv[i]);
          numParams ++;
        }
        i ++;
      }
    }
    else if (strcmp(argv[i], "-info") == 0) {       
      param->fInfo = 1;	  
    }
    else if (strcmp(argv[i], "-redundantPic") == 0) {
      if (++i == argc) {
        return 0;
      }
      seqParam->redundantPicFlag     = 1;
      seqParam->redundantPicQpOffset = atoi(argv[i]);
      seqParam->redundantPicQpOffset = clip(-51, 51, seqParam->redundantPicQpOffset);
    }
    else {
      // have a regular check
      cmdBuf->current = cmdBuf->head->next;
      do
      {
        if (strcmp(argv[i], cmdBuf->current->id) == 0) 
        {
          if (cmdBuf->current->type == CMD_FLAG)
            * (int *) cmdBuf->current->data = 1;
          else
          {
            i ++;
            if (i == argc)
              return 0;

            if (cmdBuf->current->type == CMD_STR)
              strcpy((char *) cmdBuf->current->data, argv[i]);
            else
              // must be CMD_INT, read the next token as an integer
              if (sscanf(argv[i], "%d", cmdBuf->current->data) != 1)
                return 0;
          }
          // to signal a command is received
          cmdBuf->current->flag = 1;

          // no further search
          break;
        }
        else
          cmdBuf->current = cmdBuf->current->next;
      } while (cmdBuf->current != 0);

      // ternimate the process if an illegal command is encountered
      if (cmdBuf->current == 0)
      {
        fprintf(stderr, "Command ""%s"" is not defined!\n", argv[i]);
        return 0;
      }
    }
  }

  // seqParam->qpInter is only used in setting pic_init_qp_minus26 in PPS
  seqParam->qpInter = param->qpInter;

  // log2_max_pic_order_cnt_lsb_minus4 depends on numSkipFrms and numNonref
  seqParam->log2_max_pic_order_cnt_lsb_minus4 = 
    calculateMinPocBits(param->frmSkip, param->numNonref) - 4;
  if (seqParam->log2_max_pic_order_cnt_lsb_minus4 < 0)
    seqParam->log2_max_pic_order_cnt_lsb_minus4 = 0;

  if (param->qpInter2 < 0)
    param->qpInter2 = param->qpInter;

  if (param->qpNonref < 0)
    param->qpNonref = param->qpInter;

  if ((param->idrFreq > 0) && (param->idrFreq < param->intraFreq))
    param->idrFreq = param->intraFreq;

  // validate the cropping offsets
  validateCroppingOffsets(seqParam);

  // the constraint is that if numLongs + numShorts > 0, numShorts > 0
  if (seqParam->maxNumRefFrms == 1)
    param->ltrIdr = 0;

  if ((seqParam->picWidth & 0x0F) != 0) {
    fprintf(stderr, "Error: picture width must be mutiple of 16\n");
    return 0;
  }

  if ((seqParam->picHeight & 0x0F) != 0) {
    fprintf(stderr, "Error: picture height must be mutiple of 16\n");
    return 0;
  }

  if (strlen(param->origFileName) == 0) {
    fprintf(stderr, "Source file required\n\n");
    return 0;
  }

  if (strlen(param->outFileName) == 0) {
    fprintf(stderr, "Output bitstream  file required\n\n");
    return 0;
  }

  // if the scut file nam is provided, perform scene cut operations
  if (strlen(param->scutFileName) > 0) {
    param->fScenecut = 1;
    if((param->scutfile = fopen(param->scutFileName, "r")) == NULL ) {
      // if the scunre cut file does not exist, create scene cut file
      param->fScenecut_Create = 1;
      if((param->scutfile = fopen(param->scutFileName, "w")) == NULL) {
        param->fScenecut = 0;
        param->fScenecut_Create = 0;
      }
    }
  }

  // numReorderFrames indicates the maximum number of frames that precede
  // any frame in the sequence in decoding order, but follow it in output order
  if (param->numNonref == 0)
    seqParam->numReorderFrames = 0;
  else
    seqParam->numReorderFrames = 1;

  // plr adjustment
  if (seqParam->plr < 0)
    seqParam->plr = 0;

  if (seqParam->irType == 0) {
    seqParam->plr = 0;
    seqParam->nAIR = 0;    
  }

  return 1;
}


void deleteList(cmdEntry_s *list)
{
  cmdEntry_s *next;


  if (list)
    do
    {
      next = list->next;
      free(list);
      list = next;
    } while (list);
}


/*
 * processCommands:
 * 
 * Parameters:
 *      argc                  Number of the input strings
 *      argv                  Array contains the input strings
 *      param                 User parameters, only used in this module
 *      seqParam              Coding parameters, used in this module & encoder
 *
 * Function:
 *      Process the input commands
 *
 * Returns:
 *      -
 */
static int processCommands(int  argc, 
                           char **argv, 
                           userParam_s *param,
                           avceOpenParams_s *seqParam)
{
  FILE *cfgFile;
  int  i, j;
  int  argcNew;
  int  correctArgs;
  char *argvNew[MAX_CFG_COMMANDS];
  cmdBuf_s *cmdBuf;


  // preprocess the arguments, there could be a config file
  cfgFile = 0;
  argcNew = argc;
  for (i = 1; i < argc; i ++) {
    if (strcmp(argv[i], "-cfg") == 0) {
      if (i == argc - 1)
        return 0;

      if ((cfgFile = fopen(argv[i + 1], "rt")) == 0)
        return 0;

      // copy the commands, except config file switches, to the new buffer
      argcNew = i;
      for (j = 0; j < argcNew; j ++) {
        argvNew[j] = (char *) malloc(strlen(argv[j]) + 1);
        strcpy(argvNew[j], argv[j]);
      }

      // read the config file
      argcNew += readConfigFile(cfgFile, argvNew + argcNew, MAX_CFG_COMMANDS - argcNew);

      // copy the remaining commands from the command line to same buffer
      for (j = i + 2; j < argc; j ++) {
        argvNew[argcNew] = (char *) malloc(strlen(argv[j]) + 1);
        strcpy(argvNew[argcNew ++], argv[j]);
      }

      for (j = argcNew; j < MAX_CFG_COMMANDS; j ++)
        argvNew[j] = 0;

      break;
    }
  }

  // the default values of all other parameters are set in fillCommandArr
  if ((cmdBuf = getCmdBuf(param, seqParam)) != 0) {
    // remove the buffer and close the config 
    if (cfgFile) {
      // buffer was allocated if the cfgFile is open
      correctArgs = parseArg(cmdBuf, argcNew, argvNew, param, seqParam);
      for (i = 0; i < argcNew; i ++)
        free(argvNew[i]);

      fclose(cfgFile);
    }
    else
      correctArgs = parseArg(cmdBuf, argc, argv, param, seqParam);

    deleteList(cmdBuf->head);
    free(cmdBuf);

    if (correctArgs)
      return 1;
  }

  // it comes to here only if somthing is wrong
  usage();
  exit(1);
}


/*
 * printSeqStat:
 * 
 * Parameters:
 *      encoder               Encoder object
 *      qpIntra               Intra quantization parameter
 *      qpInter               Inter quantization parameter
 *      fp                    Destination stream
 *
 * Function:
 *      Print one line of sequence statistics
 *
 * Returns:
 *      -
 */
static void printSeqStat(avceEncoder_t *encoder, int qpIntra,
                         int qpInter, int frameRateTimes1000, int numSkippedFrames, FILE *fp)
{
  avceStatistics_s intraStat;
  avceStatistics_s interStat;
  avceStatistics_s seqStat;
  int nInterFrames;


  avceGetIntraStat(encoder, &intraStat);
  avceGetInterStat(encoder, &interStat);
  avceGetSeqStat(encoder, &seqStat);

  nInterFrames = interStat.nFrames ? interStat.nFrames : 1;

  fprintf(fp, "%3d %2d %2d %2.2f %2.2f %2.2f %5d "
    "%2.2f %2.2f %2.2f %5d "
    "%2.2f %2.2f %2.2f %5d %.3f %.5f\n",
    seqStat.nFrames, qpInter, qpIntra,
    intraStat.psnrY/intraStat.nFrames,
    intraStat.psnrU/intraStat.nFrames,
    intraStat.psnrV/intraStat.nFrames,
    intraStat.bits/intraStat.nFrames,
    interStat.psnrY/nInterFrames,
    interStat.psnrU/nInterFrames,
    interStat.psnrV/nInterFrames,
    interStat.bits/nInterFrames,
    seqStat.psnrY/seqStat.nFrames,
    seqStat.psnrU/seqStat.nFrames,
    seqStat.psnrV/seqStat.nFrames,
    seqStat.bits/seqStat.nFrames,
    1.0*(interStat.bits+intraStat.bits)/(seqStat.nFrames+numSkippedFrames)*frameRateTimes1000/1000/1000,
    (double)clock()/CLOCKS_PER_SEC/seqStat.nFrames);
}


/*
 * dumpStatistics:
 *
 * Parameters:
 *      encoder               Encoder object
 *      frameRateTimes1000    Target frame rate times 1000
 *
 * Function:
 *      Print more detailed sequence statistics
 *
 * Returns:
 *      -
 */
static void dumpStatistics(avceEncoder_t *encoder, int frameRateTimes1000, int numSkippedFrames)
{
  avceStatistics_s intraStat;
  avceStatistics_s interStat;
  avceStatistics_s seqStat;


  /* print a brief report */
  avceGetIntraStat(encoder, &intraStat);
  avceGetInterStat(encoder, &interStat);
  avceGetSeqStat(encoder, &seqStat);

  printf("Total frames being encoded: %d\nI: %d, P: %d\n", seqStat.nFrames, intraStat.nFrames, interStat.nFrames);
  printf("Skipped frames: %d\n", numSkippedFrames);
  printf("Total bits in the stream: %d\n", seqStat.bits);
  printf("Bits in all NAL headers: %d\n", avceGetBitsNAL(encoder));
  printf("Bits in Sequence Parameter Set: %d\n", avceGetBitsSPS(encoder));
  printf("Bits in Picture Parameter Set: %d\n", avceGetBitsPPS(encoder));
  printf("I-frame bits: %d, P-frame bits: %d\n", intraStat.bits, interStat.bits);
  if (interStat.nFrames > 0)
  {
    printf("P-frame bit rate: %d bits/second\n", 
      (int) ((interStat.bits * (float)frameRateTimes1000/1000)/interStat.nFrames + 0.5f));
    printf("Overall bit rate: %d bits/second\n", 
      (int) (((interStat.bits + intraStat.bits) * (float)frameRateTimes1000/1000)/(interStat.nFrames+intraStat.nFrames+numSkippedFrames) + 0.5f));
  }
  printf("Average PSNR: %5.2f\nI: %5.2f, P: %5.2f\n", 
    seqStat.nFrames != 0? seqStat.psnrY / seqStat.nFrames : 9999,
    intraStat.nFrames != 0? intraStat.psnrY / intraStat.nFrames : 9999, 
    interStat.nFrames != 0? interStat.psnrY / interStat.nFrames : 9999);
}


/*
 * allocOrigFrame:
 *
 * Parameters:
 *      buf                   Frame buffer struct
 *      width                 Frame width
 *      height                Frame height
 *
 * Function:
 *      Allocate memory for original frame
 *      
 * Returns:
 *      -
 *
 */
static void allocOrigFrame(avceYUVbuffer_s *buf, int width, int height)
{
  int frmSize = width*height;
  int frmSizeC = width/2*height/2;

  
  if ((buf->y = malloc(frmSize*sizeof(unsigned char))) == NULL) {
    fprintf(stderr, "Cannot allocate orig frame memory\n");
    exit(1);
  }
  if ((buf->u = malloc(frmSizeC*sizeof(unsigned char))) == NULL) {
    fprintf(stderr, "Cannot allocate orig frame memory\n");
    exit(1);
  }
  if ((buf->v = malloc(frmSizeC*sizeof(unsigned char))) == NULL) {
    fprintf(stderr, "Cannot allocate orig frame memory\n");
    exit(1);
  }
}


/*
 * freeOrigFrame:
 *
 * Parameters:
 *      buf                   Frame buffer struct
 *
 * Function:
 *      Free memory of original frame
 *      
 * Returns:
 *      -
 *
 */
static void freeOrigFrame(avceYUVbuffer_s *buf)
{
  free(buf->y);
  free(buf->u);
  free(buf->v);
}


/*
 * openVideoFiles:
 *
 * Parameters:
 *      param                 Parameters
 *      origFile              Source file
 *      recoFile              Reconstruction file
 *      stream                bitsream file
 *
 * Function:
 *      Open raw video files
 *      
 * Returns:
 *      1 if reconstructed frames are written to file(s), 0 otherwise
 *
 */
static int openVideoFiles(userParam_s *param, 
                          videoFile_s *origFile,
                          videoFile_s *origFile2,
                          videoFile_s *recoFile, 
                          FILE        **stream)
{
  char tmpName[MAX_FILENAME_LEN+1];
  int writeReco = 0;
  int secondFilePresent;


  /*
   * Open source sequence file
   */
  if ((strlen(param->origFileName) != 0) && 
    strlen(param->origFileName)+2 > MAX_FILENAME_LEN) {
    fprintf(stderr, "Too long input file name\n");
    exit(1);
  }
  if ((strlen(param->recoFileName) != 0) && 
    strlen(param->recoFileName)+2 > MAX_FILENAME_LEN) {
    fprintf(stderr, "Too long reconstruction file name\n");
    exit(1);
  }

  switch (param->seqFormat) {

  case SEPARATE_YUV_FILES:
    sprintf(tmpName, "%s%s", param->origFileName, ".y");
    if ((origFile->y = fopen(tmpName, "rb")) == NULL) {
      fprintf(stderr, "Input file \"%s\" not found\n", tmpName);
      exit(1);
    }
    sprintf(tmpName, "%s%s", param->origFileName, ".u");
    if ((origFile->u = fopen(tmpName, "rb")) == NULL) {
      fprintf(stderr, "Input file \"%s\" not found\n", tmpName);
      exit(1);
    }
    sprintf(tmpName, "%s%s", param->origFileName, ".v");
    if ((origFile->v = fopen(tmpName, "rb")) == NULL) {
      fprintf(stderr, "Input file \"%s\" not found\n", tmpName);
      exit(1);
    }
    break;

  case COMBINED_YUV_FILE:
    if ((origFile->y = fopen(param->origFileName, "rb")) == NULL) {
      fprintf(stderr, "Input file \"%s\" not found\n", param->origFileName);
      exit(1);
    }
    origFile->u = origFile->v = origFile->y;

    /* Length of the filename tells if parameter for second file has been given */
    secondFilePresent = strlen(param->origFileName2);

    if(secondFilePresent)
    {
      if ((origFile2->y = fopen(param->origFileName2, "rb")) == NULL) {
        fprintf(stderr, "Input file #2 \"%s\" not found\n", param->origFileName2);
        exit(1);
      }
      
      origFile2->u = origFile2->v = origFile2->y;
    }
    
    break;
  }

  origFile->format = param->seqFormat;

  /*
   * Open reconstruction file if requested
   */
  if (strlen(param->recoFileName) != 0) {

    switch (param->recoFormat) {

    case SEPARATE_YUV_FILES:
      sprintf(tmpName, "%s%s", param->recoFileName, ".y");
      if ((recoFile->y = fopen(tmpName, "wb")) == NULL) {
        fprintf(stderr, "Cannot open reconstruction file \"%s\"\n", tmpName);
        exit(1);
      }
      sprintf(tmpName, "%s%s", param->recoFileName, ".u");
      if ((recoFile->u = fopen(tmpName, "wb")) == NULL) {
        fprintf(stderr, "Cannot open reconstruction file \"%s\"\n", tmpName);
        exit(1);
      }
      sprintf(tmpName, "%s%s", param->recoFileName, ".v");
      if ((recoFile->v = fopen(tmpName, "wb")) == NULL) {
        fprintf(stderr, "Cannot open reconstruction file \"%s\"\n", tmpName);
        exit(1);
      }
      recoFile->format = SEPARATE_YUV_FILES;
      break;

    case COMBINED_YUV_FILE:
      if ((recoFile->y = fopen(param->recoFileName, "wb")) == NULL) {
        fprintf(stderr, "Cannot open reconstruction file \"%s\"\n", param->recoFileName);
        exit(1);
      }
      recoFile->u = recoFile->v = recoFile->y;
      recoFile->format = COMBINED_YUV_FILE;
      break;

    }
    writeReco = 1;
  }

  if ((*stream = fopen(param->outFileName, "wb")) == NULL) {
    fprintf(stderr, "Cannot open output bitstream\n");
    exit(1);
  }

  origFile2->format = COMBINED_YUV_FILE;

  return writeReco;
}


/*
 * closeFiles:
 *
 * Parameters:
 *      origFile              Source file
 *      recoFile              Reconstruction file
 *      recoFlag              Rec. frames were written to file if true
 *      stream                bitsream file
 *
 * Function:
 *      Close raw video files
 *      
 * Returns:
 *      1 if reconstructed frames are written to file(s), 0 otherwise
 *
 */
static void closeFiles(videoFile_s *origFile, videoFile_s *origFile2,	
					   videoFile_s *recoFile,
                       int recoFlag, FILE *stream)
{
  fclose(origFile->y);
  fclose(origFile2->y);
  
  if (origFile->format == SEPARATE_YUV_FILES) {
    fclose(origFile->u);
    fclose(origFile->v);
  }
  // otherwise, u/v are the same file as y if it is COMBINED_YUV_FILE

  if (recoFlag) {
    fclose(recoFile->y);
    if (recoFile->format == SEPARATE_YUV_FILES) {
      fclose(recoFile->u);
      fclose(recoFile->v);
    }
  }

  fclose(stream);
}


/*
 * readFrame:
 *
 * Parameters:
 *      buf                   Frame buffer
 *      width                 Frame luma width
 *      height                Frame luma height
 *      inFile                Source file
 *
 * Function:
 *      Read frame from file
 *      
 * Returns:
 *      1 for success
 *      0 for failure
 *
 */
static int readFrame(avceYUVbuffer_s *buf, int width, int height,
                     videoFile_s *inFile, int frameIdx)
{
  unsigned nPixels = (unsigned)width * (unsigned)height;


  switch (inFile->format) {
  case SEPARATE_YUV_FILES:
    if (fseek(inFile->y, (long)frameIdx * (long)nPixels,   SEEK_SET) != 0)
      return 0;
    if (fseek(inFile->u, (long)frameIdx * (long)nPixels/4, SEEK_SET) != 0)
      return 0;
    if (fseek(inFile->v, (long)frameIdx * (long)nPixels/4, SEEK_SET) != 0)
      return 0;
    break;
  case COMBINED_YUV_FILE:
    if (fseek(inFile->y, ((long)frameIdx * (long)nPixels * 3)/2, SEEK_SET) != 0)
      return 0;
    break;
  }

  if (fread(buf->y, sizeof(unsigned char), nPixels,   inFile->y) != nPixels)
    return 0;
  if (fread(buf->u, sizeof(unsigned char), nPixels/4, inFile->u) != nPixels/4)
    return 0;
  if (fread(buf->v, sizeof(unsigned char), nPixels/4, inFile->v) != nPixels/4)
    return 0;

  return 1;
}


static void writeCroppedFrameComponent(FILE *outFile,
                                       unsigned char *frameBuf,
                                       int bufWidth,
                                       int leftOffset,
                                       int topOffset,
                                       int outWidth,
                                       int outHeight)
{
  int i;


  for (i = topOffset; i < (topOffset + outHeight); i ++)
  {
    fwrite(frameBuf + i * bufWidth + leftOffset, sizeof(unsigned char), 
      outWidth, outFile);
  }
}


/*
 * writeFrame:
 *
 * Parameters:
 *      buf                   Frame buffer
 *      seqParam              Encoding parameters
 *      outFile               Destination file
 *
 * Function:
 *      Writes frame to the file.
 *      The frame cropping is applied.
 *      
 * Returns:
 *      -
 */
static void writeFrame(avceYUVbuffer_s  *buf, 
                       avceOpenParams_s *seqParam,
                       videoFile_s      *outFile, 
                       int              frameIdx)
{
  unsigned nPixels;
  int width, height;


  width  = seqParam->picWidth - 
    seqParam->cropOffsets[0] - seqParam->cropOffsets[1];

  height = seqParam->picHeight - 
    seqParam->cropOffsets[2] - seqParam->cropOffsets[3];

  nPixels = (unsigned)width * (unsigned)height;

  switch (outFile->format) {
  case SEPARATE_YUV_FILES:
    fseek(outFile->y, (long)frameIdx * (long)nPixels,   SEEK_SET);
    fseek(outFile->u, (long)frameIdx * (long)nPixels/4, SEEK_SET);
    fseek(outFile->v, (long)frameIdx * (long)nPixels/4, SEEK_SET);
    break;
  case COMBINED_YUV_FILE:
    fseek(outFile->y, ((long)frameIdx * (long)nPixels * 3)/2, SEEK_SET);
    break;
  }

  // take care of the frame cropping
  writeCroppedFrameComponent(outFile->y, buf->y, 
    seqParam->picWidth,
    seqParam->cropOffsets[0], seqParam->cropOffsets[2], width, height);

  writeCroppedFrameComponent(outFile->u, buf->u, 
    seqParam->picWidth >> 1,
    seqParam->cropOffsets[0] >> 1, seqParam->cropOffsets[2] >> 1, width >> 1, height >> 1);

  writeCroppedFrameComponent(outFile->v, buf->v, 
    seqParam->picWidth >> 1,
    seqParam->cropOffsets[0] >> 1, seqParam->cropOffsets[2] >> 1, width >> 1, height >> 1);
}


/*
* putBytesByteStream:
*
* Parameters:
*      stream          Bitsream file
*      data            Data to be written
*      len             Length of data
*
* Function:
*      Write bytes to bitstream file
*      
*
* Returns:
*      -
*
*/
void putBytesByteStream(FILE *stream, void *data, int len)
{
  fwrite(data, len, 1, stream);
}


static int readNextSceneCut(FILE *scFile)
{
  int nextScFrameidx, scType, readCount;


  scType = 0;
  do
  {
    readCount = fscanf(scFile, "%d:%1d\n", & nextScFrameidx, & scType);
  } while ((readCount == 2) && (scType != 1 && scType != 3));

  // the end of the file is reached
  if (readCount < 2)
    return MAX_FRM_NUM;     // a large number
  else
    return nextScFrameidx;
}


/*
 * main:
 *
 * Parameters:
 *      argc                  Number of parameters
 *      argv                  Parameter strings
 *
 * Function:
 *      Encoder main function
 *
 * Returns:
 *         0 ok
 *      <> 0 error
 */
int main(int argc, char **argv)
{
  userParam_s param;      /* Parameters from user */
  avceOpenParams_s seqParam;    /* Parameters passed to encoder */
  avceEncoder_t *encoder;    /* Encoder instance */
  avceStatistics_s frmStat;
  videoFile_s origFile;
  videoFile_s origFile2;
  videoFile_s recoFile;
  int viewId = 0;
  int recoFlag;
  FILE *stream;
  FILE *cumuFp;
  int srcPicNum, dstPicNum,numSkippedFrames=0;
  int intraFlag, idrFlag;
  int qp;
  avceYUVbuffer_s origBuf, prevOrigBuf;
  avceYUVbuffer_s recoBuf;
  void *nalBuf;
  int nalBufSize;
  int result;
  int targetFpsTimes1000;
  int pType;
  int nalRefIdc;
  int intraComing;      /* 
                         * Old name: scenecutComing. The next frame will be intra coded. 
                         * Either a refreshed picture or a scene cut picture.
                         */
  int intraFrm;         /* Old name: scenecutFrm. Current frame is intra coded. */
  int sceneId;          /* Newly defined var */
  int scenecutComing;   /* Newly defined var: Indicates the coming of a scene cut picture */
  int nextScFrameidx;   /* The skipped pic in the orig seq is counted by the idx */

  int lastIdrFrm;       /* The frame idx of the last IDR picture */
  int k;


  /* Parse command line arguments  */
  processCommands(argc, argv, &param, &seqParam);

    targetFpsTimes1000 = seqParam.origFpsTimes1000/(param.frmSkip + 1);

    /* Open video files */
    recoFlag = openVideoFiles(&param, &origFile, &origFile2, &recoFile, &stream);

    /* Initialize encoder constants common to all encoder instances */
    avceLoad();

    /*
    * Open (encoder) sequence
    */
    seqParam.offsetForRefFrame = param.frmSkip + 1;
    seqParam.numFrms = param.numFrms;
    seqParam.intraFreq = param.intraFreq;
    seqParam.idrFreq = param.idrFreq;
    seqParam.numNonref = param.numNonref;
    
#ifdef ENABLE_SEARCH_WINDOW
    /* internal search window */
    seqParam.srx = param.srx;
    seqParam.sry = param.sry;
#endif
    encoder = avceOpen(&seqParam,&nalBuf,&nalBufSize);
  	putBytesByteStream(stream, nalBuf, nalBufSize);
  
    if (encoder == NULL) {
      fprintf(stderr, "Could not open sequence\n");
      exit(1);
    }

    /* Allocate memory for original frame data */
    allocOrigFrame(&origBuf, seqParam.picWidth, seqParam.picHeight);  

    if (param.fScenecut && !param.fScenecut_Create)
      ScutCheck(& param);
    if (param.fScenecut_Create)
      allocOrigFrame(& prevOrigBuf, seqParam.picWidth, seqParam.picHeight);
    else
      prevOrigBuf.y = prevOrigBuf.u = prevOrigBuf.v = NULL;

    pType = 0;

    // if create scene cut file, the first frame is always a scene cut
    if (param.fScenecut && param.fScenecut_Create)
      fprintf(param.scutfile, "%d:%1d\n", param.startFrm, 1);

    // the first frame is always handled as the scene cut
    nextScFrameidx = 0;
    dstPicNum = 0;
    intraComing = 1;
    sceneId = -1;
    scenecutComing = 1;
    lastIdrFrm = -1;

    while (dstPicNum < param.numFrms) {
      int i, groupLen;
      int ltrCandidate;


      if (intraComing) {
        intraComing = 0;
        intraFrm = 1;
        groupLen = 1;       // process this frame only
        
        // move the scene cut pointer to pass the current IDR frame
        if (param.fScenecut && (! param.fScenecut_Create)) {
          srcPicNum = param.startFrm + dstPicNum * (param.frmSkip + 1);
          // scene cut picture!
          if (srcPicNum >= nextScFrameidx) {
            scenecutComing = 1;
            sceneId++;
          }
          while (srcPicNum >= nextScFrameidx) 
            nextScFrameidx = readNextSceneCut(param.scutfile);
        }
      }
      else
      {
        intraFrm = 0;
        groupLen = param.numNonref + 1;
        
        // group can not include next IDR 
        if (param.idrFreq > 0) {
          int nextIdr;
          
          nextIdr = ROUND_UP(dstPicNum, param.idrFreq);
          
          // if the next IDR refresh picture is too close to another IDR picture,
          // it will not be a refresh IDR picture
          if (param.minIdrDistance > 0 && lastIdrFrm >= 0) {
            int nextSc = nextScFrameidx / (param.frmSkip + 1);
            
            if (nextIdr - lastIdrFrm < param.minIdrDistance ||
              nextSc  - nextIdr    < param.minIdrDistance)
              nextIdr = nextSc;
          }
          
          if (nextIdr >= param.numFrms)
            nextIdr = param.numFrms;
          if (dstPicNum + groupLen - 1 >= nextIdr)
            groupLen = nextIdr - dstPicNum;
          
          if (groupLen == 0)
            intraComing = 1;
        }
        
        // groupLen will be adjusted again if there is a scene cut
        if ((param.fScenecut) && (groupLen > 0)) {
          if ((param.fScenecut_Create) && (dstPicNum != 0)) {
            int pType;
            
            // have a scene cut in the group? should be done backward
            // but we want to use this process to generate a scene cut file also
            pType = 0;
            for (nextScFrameidx = dstPicNum; 
            nextScFrameidx < (dstPicNum + groupLen); nextScFrameidx ++) {
              srcPicNum = param.startFrm + nextScFrameidx * (param.frmSkip + 1);
              readFrame(& origBuf, seqParam.picWidth, seqParam.picHeight,
                & origFile, srcPicNum);
              
              param.Sumuv = param.Sumy = 0;
              pType = scdSceneCut(origBuf.y, origBuf.u, origBuf.v,
                prevOrigBuf.y, prevOrigBuf.u, prevOrigBuf.v,
                seqParam.picWidth, seqParam.picHeight, 4, & param.Sumy, & param.Sumuv);
              
              fprintf(param.scutfile, "%d:%1d\n", srcPicNum, pType);
              if (pType)
                break;
            }
          }
          
          // this is the last frame in the group
          srcPicNum = param.startFrm + (dstPicNum + groupLen - 1) * (param.frmSkip + 1);
          
          // does the next scene cut fall within the group
          if (srcPicNum >= nextScFrameidx * (param.frmSkip + 1)) {
            intraComing = 1;
            
            // the last frame whould be the one right before scene cut
            groupLen = (nextScFrameidx - 1 - param.startFrm)/(param.frmSkip + 1) - dstPicNum + 1;
            if (groupLen < 0)
              // scene cut happens between this frame and the last encoded frame
              groupLen = 0;
          }
        }
      }
      
      if (groupLen == 0)
        continue;         // leave it to the next iteration

      // decide number of pp frames,
      for (i = 0; i < groupLen; i++ ) {
        int srcPicIdx;
        
        /* Loop on the views */
        for (k=0; k<2; k++) {
          viewId = k;
          
          intraFlag = 0;
          idrFlag   = 0;
          
          if (i == 0) {
            intraFlag = idrFlag = (intraFrm) ? 1 : 0;
            
            // for intraFrm, groupLen == 1
            srcPicIdx = dstPicNum + groupLen - 1;
            nalRefIdc = 1;
            
            // store the last idr picture idx
            if (idrFlag)
              lastIdrFrm = srcPicIdx;
            
            // create the scene info SEI message here
            if ( scenecutComing && param.fScenecutSei) {
              fprintf(stderr, "writing scene info sei (%d)\n", sceneId);
              avceEncodeSceneInfo(encoder, sceneId, &nalBuf, &nalBufSize);
              putBytesByteStream(stream, nalBuf, nalBufSize);
            }
          }
          else
          {
            srcPicIdx = dstPicNum + i - 1;
            nalRefIdc = 0;
          }
          
          // we may want to insert intra frame, not idr frame for testing
          if (param.intraFreq > 0) {
            if ((srcPicIdx % param.intraFreq) == 0 && (intraFlag == 0))
              intraFlag = 1;
          }
          
          // if there is no reference frame, this frame is always intra
          if ((intraFlag == 0) && (seqParam.maxNumRefFrms == 0))
            intraFlag = 1;
          
          srcPicNum = param.startFrm + srcPicIdx * (param.frmSkip + 1);
          
          if(viewId == 0)
          {
            if (! readFrame(& origBuf, seqParam.picWidth, seqParam.picHeight,
              & origFile, srcPicNum))
              break;
            
#ifdef DEBUG_PRINT
            printf("view0: %d\n",srcPicNum);
#endif
            
          }
          else
          {
            /* For second view, read from the same time as the first one */
            if (intraFrm) {
              
              /* Let the first frame of the non-base intraview be intra */
              intraFlag = 1;
              idrFlag = 0;
            }
            
#ifdef DEBUG_PRINT
            printf("view1: %d\n",srcPicNum);
#endif
            
            if (! readFrame(& origBuf, seqParam.picWidth, seqParam.picHeight,
              & origFile2, srcPicNum))
              break;
          }
          
          // use this frame as the previous frame in scene cut detection
          if (param.fScenecut_Create && (i == 0))
          {
            int lumaSize;
            
            lumaSize = seqParam.picWidth * seqParam.picHeight;
            memcpy(prevOrigBuf.y, origBuf.y,  lumaSize);
            memcpy(prevOrigBuf.u, origBuf.u,  lumaSize/4);
            memcpy(prevOrigBuf.v, origBuf.v,  lumaSize/4);
          }
          
          // decide the qp to use for the frame
          // qpIntra is not used if intra frame is after q2Start
          if ((dstPicNum + i) >= param.q2Start)
            qp = param.qpInter2;
          else
            qp = intraFlag ? param.qpIntra : param.qpInter;
          
          if (nalRefIdc == 0)
            qp = param.qpNonref;
          
          // will this frame used as long term reference frame
          // this is a reference picture, however this should still be stored if this is not to be outputted
          ltrCandidate = 0;
          if (param.ltrFreq > 0) {
            if (((srcPicIdx - param.ltrStart) % param.ltrFreq) == 0)
              ltrCandidate = 1;
          }
          
          // modify the frame number
          if (idrFlag && (param.ltrIdr))
            ltrCandidate = 1;
          
          /* Encoder one frame */
          result = avceEncodeOneFrame(encoder, &origBuf, &recoBuf, 
            intraFlag, idrFlag, scenecutComing, nalRefIdc, ltrCandidate, srcPicNum - param.startFrm, 
            qp, &nalBuf, &nalBufSize, viewId);
          
          
          if (result == AVCE_ERROR) {
            fprintf(stderr, "Error occured while encoding\n");
            exit(1);
          }
          
          /* If frame was not skipped, bits are written to file */
          if (result != AVCE_FRAME_SKIPPED) {
            
            avceGetFrmStat(encoder, &frmStat);
            
            // change output layout, easier to load it into excel to do data analysis
            if (param.fInfo) {
              if (srcPicNum == 0) {
                int bits;
                bits = avceGetBitsSPS(encoder) + avceGetBitsPPS(encoder) + 10*8;
                printf(" %d\t %d\t %d \n", srcPicNum, (bits + frmStat.bits)/8, intraFlag);			
              }
              else
                printf(" %d\t %d\t %d \n", srcPicNum, frmStat.bits/8, intraFlag);
            }
            else {
              {
#ifdef DEBUG_PRINT
                if(intraFlag ||idrFlag)
                  printf("%3d(%s)\tbits\t%6d\tPsnrYUV\t%5.2f\t%5.2f\t%5.2f\tintraMb\t%d\t%5d  %1d\n", 
                  srcPicNum, "I", frmStat.bits, frmStat.psnrY, frmStat.psnrU, 
                  frmStat.psnrV, frmStat.numIntraMbs, frmStat.bufFullness, intraFlag);
                else if(nalRefIdc == 1)
                  printf("%3d(%s)\tbits\t%6d\tPsnrYUV\t%5.2f\t%5.2f\t%5.2f\tintraMb\t%d\t%5d  %1d\n", 
                  srcPicNum, "P", frmStat.bits, frmStat.psnrY, frmStat.psnrU, 
                  frmStat.psnrV, frmStat.numIntraMbs, frmStat.bufFullness, intraFlag);
                else if(nalRefIdc == 0)
                  printf("%3d(%s)\tbits\t%6d\tPsnrYUV\t%5.2f\t%5.2f\t%5.2f\tintraMb\t%d\t%5d  %1d\n", 
                  srcPicNum, "p", frmStat.bits, frmStat.psnrY, frmStat.psnrU, 
                  frmStat.psnrV, frmStat.numIntraMbs, frmStat.bufFullness, intraFlag);
#endif
              }
            }
            
            putBytesByteStream(stream, nalBuf, nalBufSize);
            
            if (recoFlag)
            {
              writeFrame(& recoBuf, & seqParam, & recoFile, 
                (srcPicNum - (numSkippedFrames*(param.frmSkip + 1)) - param.startFrm)/(param.frmSkip + 1));      
            }
          }
          else
          {
            if(intraFlag == 1)
              intraComing = 1;
            numSkippedFrames++;
          }
        }
      }

      if (viewId)
      {
        dstPicNum += groupLen;	// Only increase after view 1
      intraFrm = 0;
      }

      scenecutComing = 0;
    }
    
    fprintf(stderr," took %5.3f seconds                \n", (double)clock()/CLOCKS_PER_SEC);
    
    /* Append short sequence statistics to -cumul file if file present */
    if (strlen(param.cumuFileName) != 0) {
      if ((cumuFp = fopen(param.cumuFileName, "a")) != NULL) {
        printSeqStat(encoder, param.qpIntra, param.qpInter, targetFpsTimes1000, numSkippedFrames, cumuFp);
        fclose(cumuFp);
      }
    }
    
    /* Print a bit more detailed statistics */
    if(!param.fInfo) dumpStatistics(encoder, targetFpsTimes1000, numSkippedFrames);
    
    /* Close sequence */
    avceClose(encoder);
    
    /* Free memory of original frame data */
    freeOrigFrame(&origBuf);
    if (param.fScenecut_Create)
      freeOrigFrame(&prevOrigBuf);

    closeFiles(&origFile, &origFile2, &recoFile, recoFlag, stream);  
        
    /* Print timing information */
  if(param.fScenecut) 
  {
    if(param.scutfile != NULL) 
      fclose(param.scutfile);
  }
  
  return 0;
}

