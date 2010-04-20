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
 * globals.h
 *
 * Contains:
 *    Interface for data and functions common to all modules
 *
 */

#ifndef _GLOBALS_H_
#define _GLOBALS_H_


#include <stdlib.h>
#include "nrctypes.h"

//#define DEBUG_DUMP
//#define MOTION_ANALYSIS

// in some places, 4 bytes are copied as an integer, watch how to put bytes
#define LITTLE_ENDIAN_MVC

#define DEBUG_PRINT

//#define TRACE_AE

/* DT: must be 1, if we need not raw byte sequence without encapsulation. It will be deleted later if agreed. */
#define ENCAPSULATED_NAL_PAYLOAD  1    

#define CONSTRAINED_INTRA_PRED    0
#define FORCE_INTRA_FREQUENCY 80 //How many frames should be passed to force the MB as INTRA, if Intra Refresh is in use

/*
 * General macros
 */
#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif

#define  clip(min, max, val) (((val)<(min))? (min):(((val)>(max))? (max):(val)))

#define SIGN(x)  ((x) < 0 ? -1 : 1)


/*
 * Defines for frame
 */
#define MIN_QP 0
#define MAX_QP 51

//#define IMG_INTRA  0
//#define IMG_INTER  1
//#define IMG_IDR_INTRA 2
//#define IS_INTRA(x) ( (x)==IMG_INTRA || (x)==IMG_IDR_INTRA )

#define FRM_MAX_REF_FRAMES   16     // must be <= 16
#define MAX_SLICE_GROUP_NUM  8      /* Given in Annex A Profiles, for baseline profile & extended profile, the maximum slice group number is 8 */

/*
 * Defines for slice
 */
#define SLICE_MIN 0
#define SLICE_P   0 // P (P slice)
#define SLICE_B   1 // B (B slice)
#define SLICE_I   2 // I (I slice)
#define SLICE_SP  3 // SP (SP slice)
#define SLICE_SI  4 // SI (SI slice)
#define SLICE_P1  5	// P (P slice)
#define SLICE_B1  6	// B (B slice)
#define SLICE_I1  7	// I (I slice)
#define SLICE_SP1 8	// SP (SP slice)
#define SLICE_SI1 9	// SI (SI slice)
#define SLICE_MAX 9
#define IS_SLICE_I(x) ((x) == SLICE_I || (x) == SLICE_I1 || (x) == SLICE_SI || (x) == SLICE_SI1)
#define IS_SLICE_P(x) ((x) == SLICE_P || (x) == SLICE_P1 || (x) == SLICE_SP || (x) == SLICE_SP1)
#define IS_SLICE_B(x) ((x) == SLICE_B || (x) == SLICE_B1)

/* 
 * Define slice group map type
 */
#define SLICE_MAP_INTERLEAVED       0
#define SLICE_MAP_DISPERSED         1
#define SLICE_MAP_FOREGROUND        2
#define SLICE_MAP_BOX_OUT           3
#define SLICE_MAP_RASTER            4
#define SLICE_MAP_WIPE              5
#define SLICE_MAP_BITMAP            6

/*
 * Defines for macroblock
 */
#define MBK_SIZE    16
#define BLK_SIZE    4
#define BLK_PER_MB  (MBK_SIZE/BLK_SIZE)

#define MBK_INTRA  0
#define MBK_INTER  1

#define MBK_INTRA_TYPE1         0
#define MBK_INTRA_TYPE2         1

// define all possible intra/inter modes using just 1 variable
#define MB_TYPE_INTRA_4x4       0
#define MB_TYPE_INTRA_16x16     1
#define MB_TYPE_INTER_SKIPPED   2
#define MB_TYPE_INTER_16x16     3
#define MB_TYPE_INTER_16x8      4
#define MB_TYPE_INTER_8x16      5
#define MB_TYPE_INTER_8x8       6


#define MAX_MODES 10

/*
 * Defines for Intra Refresh Types
 */
#define PDT_IR          1 //Potential Distortion Tracking IR
#define PDT_IR_LC       2 // Low ComplexityPotential Distortion Tracking IR
#define RIR             3 // Random Intra Refresh

/*
 * Defines for debug statistics
 */
#define PRINT_DETAILED_SEQ_STATISTICS   1
#define PRINT_IMG_TYPE                  0
#define PRINT_MBMODE                    0
#if PRINT_MBMODE
#define ROW_NEWLINE                     1
#else
#define ROW_NEWLINE                     0
#endif
#define PRINT_MOTVECS                   0
#define MOTION_FIELD_DRAWING            0

// amount of bias used for zero motion vector, in inter16x16 mode
#define ZERO_VEC_SAD              4

/*
 * Defines for transform and quantization
 */
#define USE_COEF_ELIM             1
#define COEF_ELIM_TH_MB           5
#define COEF_ELIM_TH_BLK8x8       4
#define COEF_ELIM_TH_CHROMA       3

/*
 * Intra prediction modes
 */

/* Luma 4x4 prediction modes */
#define IPR_NUM_MODES1            9
#define IPR_MODE_VERT             0
#define IPR_MODE_HOR              1
#define IPR_MODE_DC               2
#define IPR_MODE_DIAG_DOWN_LEFT   3
#define IPR_MODE_DIAG_DOWN_RIGHT  4
#define IPR_MODE_VERT_RIGHT       5
#define IPR_MODE_HOR_DOWN         6
#define IPR_MODE_VERT_LEFT        7
#define IPR_MODE_HOR_UP           8
#define IPR_MODE_NA               0x7F   // make it large to do some trick

/* Luma 16x16 prediction modes */
#define IPR_NUM_MODES2            4
#define IPR_MODE2_VERT            0
#define IPR_MODE2_HOR             1
#define IPR_MODE2_DC              2
#define IPR_MODE2_PLANE           3

/* Chroma 8x8 prediction modes */
#define IPR_CHROMA_NUM_MODES      4
#define IPR_CHROMA_MODE_DC        0
#define IPR_CHROMA_MODE_HOR       1
#define IPR_CHROMA_MODE_VERT      2
#define IPR_CHROMA_MODE_PLANE     3

/* profile definition for performance/speed trade-off */
#define PROF_CODING_EFFICIENCY    0
#define PROF_CODING_SPEED         1
#define PROF_CODING_LC3           2
#define PROF_CODING_LC4           3

/* The number of views, currently two */
#define NUM_VIEWS 2

/*
 * Structures
 */
typedef struct _rectRegion_s
{
  int16 x0;
  int16 y0;
  int16 x1;
  int16 y1;
} rectRegion_s;


typedef struct _searchRange_s
{
  // this is the intended search range
  int x0;
  int y0;
  int x1;
  int y1;

  // this is the legal search range, within the extended frame boundaries
  int lx0;
  int lx1;
  int ly0;
  int ly1;
} searchRange_s;


// ----------------------------------------------------------------------------
// when the global RDO flag is set, at least perform mode decision among
//   inter/intra4x4/intra16x16
//
// use flags to enable/disable lower level RDO components
#define RDO_INTRA_LUMA_4x4          0x10
#define RDO_INTRA_LUMA_16x16        0x20
#define RDO_INTRA_CHROMA            0x40
#define RDO_INTER                   0x80

typedef struct _frmBuf_s {
  int16 width;
  int16 height;
  u_int8 *y;
  u_int8 *u;
  u_int8 *v;
  int32  *channelDistortion;
} frmBuf_s;


typedef struct _motVec_s {
  int16 x;
  int16 y;
} motVec_s;


typedef struct _blkState_s
{
  motVec_s mv;
  int8     ref;
  u_int8   i4x4Mode;
  int8     numLumaCoefs;
} blkState_s;


typedef struct _mbState_s
{
  int32  cbp;

  blkState_s blkInfo[4][4];
  int8   numChromaCoefs[2][2][2];

#ifdef MOTION_ANALYSIS
  int8 subMbType[4];        // DBG, mostly
#endif

  int16 sliceMap;
  int8  mbType;
  int8  intraModeChroma;
  int8  qp;
  int8  filterMode;
  int8  alphaOffset;
  int8  betaOffset;
} mbState_s;


typedef struct _mbAttributes_s {
  int       blksPerLine;
  mbState_s *mbStateArr;
  int *mapRIR;
} mbAttributes_s;


typedef struct _statSlice_s {
  int nFrames;
  double psnrY;
  double psnrU;
  double psnrV;
  int bitsNAL;
  int bitsHdr;
  int bitsSkipLen;
  int bitsMBtype;
  int bitsPred;
  int bitsVec;
  int bitsCBP;
  int bitsCoefLumaDC;
  int bitsCoefLuma;
  int bitsCoefChromaDC;
  int bitsCoefChroma;
  int bitsArithmeticStream;
  int interModeCtr[MAX_MODES];
  int intraModeCtr1;
  int intraModeCtr2[MAX_MODES];
} statSlice_s;

// DT: check
//     More statistics needed?
typedef struct _statNonSliceNal_s
{
  int bitsNAL;
  int bitsPPS;
  int bitsSPS;
  int bitsSEI;
} statNonSliceNal_s;

typedef struct _costMeasure_s
{
  int32 mse;
  int32 edgeMse;
  int32 bits;
  int32 lumaCoeffBits;
  int32 sad;
  int32 cDistortion;  // channel distortion
  int32 cost;
} costMeasure_s;

extern const costMeasure_s initCostMeasure;

// Definitions of NAL types
#define UNSPECIFIED_NAL_TYPE        0
#define CODED_SLICE_NAL_TYPE        1
#define CODED_SLICE_P_A_NAL_TYPE    2
#define CODED_SLICE_P_B_NAL_TYPE    3
#define CODED_SLICE_P_C_NAL_TYPE    4
#define CODED_SLICE_IDR_NAL_TYPE    5
#define SEI_NAL_TYPE                6
#define SPS_NAL_TYPE                7
#define PPS_NAL_TYPE                8
#define PIC_DELIMITER_NAL_TYPE      9
#define END_SEQ_NAL_TYPE            10
#define END_STREAM_NAL_TYPE         11
#define FILLER_DATA_NAL_TYPE        12
#define INVALID_NAL_TYPE            13
#define SUBSET_SPS_TYPE				      15
#define PREFIX_NAL_TYPE				      14
#define NON_BASE_VIEW_SLICE         20

// constants used in mode decision
#define MODE_DECISION_HADAMARD      0   // use sad after Hadamard
#define MODE_DECISION_RDO           1   // based on actual distortion & rate
#define MODE_DECISION_SIMPLE        2   // the test mode, simple SAD

/*
 * Motion modes
 */
#define MOT_NUM_MODES     7
#define MOT_COPY          0
#define MOT_16x16         1
#define MOT_16x8          2   
#define MOT_8x16          3
#define MOT_8x8           4
#define MOT_8x4           5   
#define MOT_4x8           6
#define MOT_4x4           7

/* these are the sub-MB mode as they are encoded */
#define P_L0_8x8          0
#define P_L0_8x4          1
#define P_L0_4x8          2
#define P_L0_4x4          3

// Coefficient block categories
#define BLK_CAT_Y_I16x16_DC   0     // block category, luma, intra16x16, DC
#define BLK_CAT_Y_I16x16_AC   1     // block category, luma, intra16x16, DC
#define BLK_CAT_Y             2     // block category, luma, intra16x16, DC
#define BLK_CAT_C_DC          3     // block category, luma, intra16x16, DC
#define BLK_CAT_C_AC          4     // block category, luma, intra16x16, DC

#define COMP_LUMA             0
#define COMP_CB               1
#define COMP_CR               2

// LOW_COMPLEX_PROF3
#define TH_QPEL           1 // threshold for qpel 
#define TH_HPEL_GAIN      15 // gain in half pel needed to continue qpel
#define TH_QP1            40
#define TH_QP2            28

// for intra pred
#define TH_IPR_MODE       100   
#define TH_IPR_16x16      1000
#define TH_IPR_4x4        2000

// for multi-step search 
#define NUM_POS_16x16_FastMot   24
#define NUM_POS_16x16           14
#define NUM_POS_16x8_FastMot    8   
#define NUM_POS_16x8            4  
#define TH_FastMot        24  
#define TH_FastMot_16x8   12

#define ME_START_16x8     -12
#define ME_START_16x16    -28
#define SMALL_SEARCH_WIN  8

#define LC3_RANGE         8

typedef struct MMCO_struct {
  int mmco;
  int diffPicNumMinus1;
  int longTermPicNum;
  int longTermFrmIdx;
  int maxLongTermFrmIdxPlus1;

  struct MMCO_struct *next;
} MMCO_s;

// data structure for all LC3 variables
typedef struct _lowComplexProf3_s
{
  // low complex profile 3 or not
  int low_complex_prof3; 

  int spec_search_pos;

  // flag for skipping opertation
  int16 do_qpel_mode_2_3;
  int16 do_qpel_mode_4;
  int16 do_16x8;

  // macroblock counter
  int16 cnt;
  int16 old_cnt;
  int16 old_cnt2;
  
  int16 thre_change[MOT_8x8+1];

  int16 qp;
  int16 mode;       //16x16, 8x16, ...

  int16 useProf4; //Whether to use profile 4 or not
//Below parameters are related to the profile-4
  int16 skipThreMultiple; //4 is safe, 8-10 provides some quality degradation but more improvement in speed (set to 4 currently)
  int16 sadThreMultiple_1;  // 6-7 is conservative, 8 is provides more speed with more quality degradation (set to 7 currently)
  int16 sadThreMultiple_2;  // Disables ME for certain partitions. 5-6 is conservative, this does not provide too much gain though.
                            // Check data_ME_prun2x.xls the difference between 4 & 5.
  
  int16 exitToIntraTh;    //If the 16x16 cost is too high, exit to intra. Useful in football-like sequences. 
                          //Unlike above, this does not depend on QP highly (linear).
                          //5000 provides good tradeoff. Lower means, less complexity, with higher degradation
  
  int16 skipSad[2][2],zeroMotSad[2][2],sad16x16[2][2];
  
  int16 lc4_pruneTreeTh;  // qp>30 ==> pruneThUnit*(QP-21)*2
                          // qp<30 ==> pruneThUnit*(QP-12)

  int16 performME[3][2]; // 2 modes (16x16, 16x8, 8x16), 2 partitions

  // Used for performance analysis. Define DEBUG_COMPLEXITY to make use of these.
   int16 numQPEL;
   int16 numMEs;

   /* 
---Conservative---
skipThreMultiple  : 4
sadThreMultiple_1 : 7
sadThreMultiple_2 : 4
exitToIntraTh     : 5000

---Less Complexity (Default)---
skipThreMultiple  : 6
sadThreMultiple_1 : 8
sadThreMultiple_2 : 4
exitToIntraTh     : 4200

---Extremely Less Complexity---
skipThreMultiple  : 7
sadThreMultiple_1 : 9
sadThreMultiple_2 : 5
exitToIntraTh     : 3500


*/
} lowComplexProf3_s;


#ifdef ENABLE_SEARCH_WINDOW
// internal search window
typedef struct _searchWin_s
{
  // use internal search window or not
  int     useSearchWin; 

  // internal search window information
  u_int8  *searchWindow;        // the internal search window
  int     searchWinWidth;
  int     searchWinHeight; 
  int     locX;                 // where the searchWindow starts w.r.t. the original frame
  int     locY;
  int     srx;                  // search range: e.g. srx=16 means -14.00 to 14.00 motion vector
  int     sry;

  u_int8  *refFrm;

  // encoding information
  int     picHeight;           
  int     picWidth;
  int     mbksPerLine;

  // for overlapping search window
  int16   *auxBuf;

} searchWin_s;
#endif

// part of MB, contains 1 or more 4x4 blocks
typedef struct _mbPart_s
{
  int    x0, x1, y0, y1;
  u_int8 *orig;
  int    width;
  int    height;

  int    *partSum;

  u_int8 *ref;
  int    refWidth;

  // the width of buffer refPartSum is the same as "ref"
  u_int16 *refPartSum;

  int   lambda;
  int   lambdaCoarse;
  int   profile;

  int   mode;
  int   range;
  const int8 *vlcMvBitsX;
  const int8 *vlcMvBitsY; 

  // estimated motion vector, may not be predicted vector, at integer boundary
  int16 estVec4[2];

  // motion vector nominal range, typically within this range
  int16 p0[2];
  int16 p1[2];

  // search vector limit, mapped from area to block
  int16 vecLmt0[2];
  int16 vecLmt1[2];

#ifdef ENABLE_SEARCH_WINDOW

  // for partial sum, since refWidth is different now
  int refPsWidth;

#endif

  /* LOW_COMPLEX_PROF3 */
  lowComplexProf3_s *plc3;

} mbPart_s;

#define REF_NA      -2   // Reference not available, because MB not available
#define MAX_COST        ((int32)1 << 25)

// define the tools that are used mainly for performing the trade-off 
// between the speed and coding efficiency. 
typedef struct _meProfile_s
{
  int profile;

  // those values usually does not depend on macro block, may be adjusted 
  // for running time complexity control
  int16 range[2][2];     // search ranges for different scenarios
  int pruneTreeFlag;    // stop search, if it does not make sense to continue
  int pruneTreeTh;      // threshold
  int pruneThUnit;      // 
  int interModeFlags;   // the smallest mode supported
  
  int hadamard;         // should be transfered from encParams_s

  // subsampling for integer search, 4, all position, > 4, subsampling
  int subsampling;

  // for running time complexity control
  int16 area0[2];           // search area
  int16 area1[2];
  
  // search vector limit, mapped from area to block
  int16 vecLmt0[2];
  int16 vecLmt1[2];

  // 0, pred MV, 1, pred MV for 16x16, average for other
  int searchCtrFlag;

  /* LOW_COMPLEX_PROF3 */
  lowComplexProf3_s lc3;

#ifdef ENABLE_SEARCH_WINDOW
  // information for internal search window
  searchWin_s sWin;
#endif

  // These are AVC level limitations
  int subMbRectSizeFlag;  
  int maxVerticalMvRange;
  //It means either SKIP or 16x16 with zero motion provides good match
  int8 goodEarlyMatch;

} meProfile_s;


typedef struct _vlcCode_s
{
  int8 code;
  int8 len;
} vlcCode_s;


/*
 * Fucntions and data
 */
void staClear(statSlice_s *stat);
void staNonSliceClear(statNonSliceNal_s *pstat);
void staAccumulate(statSlice_s *stat1, statSlice_s *stat2);
int staGetTotalBits(statSlice_s *stat);
void staSaveState(statSlice_s *stat, statSlice_s *statSave);
void staRestoreState(statSlice_s *stat, statSlice_s *statSaved);

extern const int8 QP2QUANT[52];
extern const int8 qpChroma[52];
extern const int8 blkRasterOrder[16];

void initSea(u_int8 *frmBuf, u_int16 *seaBuf,
             int picWidth, int picHeight, int blkSize);

int32 CalculateSsd(u_int8 *orig, 
                   int    origBufWidth, 
                   u_int8 *reco, 
                   int    recoBufWidth,
                   int    width, 
                   int    height);

int32 CalculateEdgeSsd(u_int8 *orig, 
                       int    origBufWidth, 
                       u_int8 *reco, 
                       int    recoBufWidth,
                       int    width, 
                       int    height,
                       int    rightMb,
                       int    bottomMb);

int32 CalculateSad(u_int8 *orig, 
                   int    origBufWidth, 
                   u_int8 *reco, 
                   int    recoBufWidth,
                   int    width, 
                   int    height);


/* SSE instructions are not supported in VC 6, so we need emit opcodes manually */
#ifdef X86MMX
#define PSHUFW(mmreg1,mmreg2,imm8) __asm __emit 0x0F __asm __emit 0x70 __asm __emit (0xC0+8*(mmreg1)+(mmreg2)) __asm __emit (imm8)
#define PSADBW(mmreg1,mmreg2) __asm __emit 0x0F __asm __emit 0xF6 __asm __emit 0xC0+8*(mmreg1)+(mmreg2)
#define PAVGB(mmreg1,mmreg2) __asm __emit 0x0F __asm __emit 0xE0 __asm __emit 0xC0+8*(mmreg1)+(mmreg2)
#endif


#endif
