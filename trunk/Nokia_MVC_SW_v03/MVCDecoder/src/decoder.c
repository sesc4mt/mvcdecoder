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
 * decoder.c
 *
 * Contains:
 *    Decoder main
 *
 */

//#define LINUX_BUILD
//#define MAEMO_EMULATOR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "avcdecoder.h"
#include "globals.h"

#ifdef LINUX_BUILD
#include <unistd.h>
#include <X11/Xlib.h> 
#include <X11/Xutil.h> 
#include <X11/Xatom.h> 
#include <X11/extensions/Xvlib.h> 
#endif

#define DISPLAY_WIDTH	800 
#define DISPLAY_HEIGHT	480 
 
#ifdef LINUX_BUILD
char	yuyv[DISPLAY_HEIGHT][DISPLAY_WIDTH][2]; 
#endif

#define MAX_FILENAME_LEN      200
#define COMBINED_YUV_FILE     1
#define NALBUF_INITIAL_SIZE   4096
#define NALBUF_BLOCK_SIZE     512
#define READ_FRAME_BITS       1
#define BYTE_STREAM           0
#define RTP_STREAM            1


typedef struct _userParam_s 
{
  char *inFile;
  char writeOutYUV;
  int quiet;
} userParam_s;


typedef struct _byteStream_s 
{
  FILE *fn;                     /* Bitstream file pointer */

  long bytesRead;               /* The number of bytes read from the file */
  unsigned char *bitbuf;        /* Buffer for stream bits */
  int bitbufLen;                /* Size of the bit buffer in bytes */
  int bitbufDataPos;
  int bitbufDataLen;            /* Length of all the data in the bit buffer in bytes */

  unsigned char *bitbufNalunit; /* Pointer to first NAL unit in the bitbuffer */
  int bitbufNalunitLen;         /* Length of the first NAL unit in the bit buffer in bytes,
                                   including variable size start code, nal head byte and the
                                   RBSP payload. It will help to find the RBSP length. */
} byteStream_s;


typedef struct _statOverall_s 
{
  long numBitsI;
  long numBitsP;
  long numIframes;
  long numPframes;
} statOverall_s;


/*
 *
 * usage:
 *
 * Parameters:
 *      -
 *
 * Function:
 *      Print decoder usage information.
 *
 * Returns:
 *      -
 */
static void usage(void)
{
  fprintf(stderr,"\nUsage: decode [options] -i <fn> [options]\n\n");
  fprintf(stderr," Option          Desciption\n");
  fprintf(stderr," -i <fn>         Input bitstream file (mandatory)\n");
  fprintf(stderr," -recoyuv <fn>   Write decoded pictures to file, the left view\n");
  fprintf(stderr,"                 will be in OutLeft.yuv and right in OutRight.yuv\n");
  fprintf(stderr," -quiet          Disable statistics printing\n");
  fprintf(stderr,"                 in the bitstream\n");
}


/*
 *
 * parseArg:
 *
 * Parameters:
 *      argc                  Number of parameters
 *      argv                  Parameter strings
 *      param                 Structure where parameters will be stored
 *
 * Function:
 *      Parse decoder parameters
 *
 * Returns:
 *      0 error
 *      1 ok
 *
 */
static int parseArg(int argc, char **argv, userParam_s *param)
{
  int i;

  param->inFile    = NULL;
  param->quiet     = 0;
  param->writeOutYUV = 0;

  for (i = 1; i < argc; i++) {

    if (strcmp(argv[i], "-i") == 0) {
      if (++i == argc) {
        return 0;
      }
      param->inFile = argv[i];
    }
    else if (strcmp(argv[i], "-recoyuv") == 0) {
      param->writeOutYUV = 1;
    }
    else if (strcmp(argv[i], "-quiet") == 0) {
      param->quiet = 1;
    }
    else {
      return 0;
    }
  }

  if (param->inFile == NULL) {
    return 0;
  }

  return 1;
}


/*
 *
 * openFiles:
 *
 * Parameters:
 *      param                 Parameters
 *      refBuf                Work buffer for reference comparison
 *      strByte               Bitsream
 *
 * Function:
 *      Open raw video files
 *      
 * Returns:
 *      -
 *
 */
static void openFiles(userParam_s *param, byteStream_s *strByte)
{
  /*
   * open bitstream file
   */
  if ((strByte->fn = fopen(param->inFile, "rb")) == NULL) {
    fprintf(stderr, "Cannot open input bitstream\n");
    exit(1);
  }

  if ((strByte->bitbuf = malloc(NALBUF_INITIAL_SIZE)) == NULL) {
    fprintf(stderr, "Cannot allocate memory for bitstream\n");
    exit(1);
  }

  strByte->bytesRead           = 0;
  strByte->bitbufLen           = NALBUF_INITIAL_SIZE;
  strByte->bitbufDataLen       = 0;
  strByte->bitbufDataPos       = 0;
  strByte->bitbufNalunitLen    = 0;
}


/*
 *
 * closeFiles:
 *
 * Parameters:
 *      str                   Bitsream
 *
 * Function:
 *      Close raw video files
 *      
 * Returns:
 *      -
 *
 */
static void closeFiles(byteStream_s *str)
{
  fclose(str->fn);
  free(str->bitbuf);
}


/*
 *
 * readBytesFromFile:
 *
 * Parameters:
 *      str                   Bitbuffer object
 *
 * Function:
 *      Read bytes from the bistream file
 *
 * Returns:
 *      Number of bytes read
 *
 */
static int readBytesFromFile(byteStream_s *str)
{
  int n;


  if (str->bitbufLen - str->bitbufDataLen < NALBUF_BLOCK_SIZE) {

    /* Buffer is too small -> allocate bigger buffer */
    str->bitbuf = realloc(str->bitbuf, str->bitbufLen+NALBUF_BLOCK_SIZE);

    if (str->bitbuf == NULL) {
      fprintf(stderr, "Cannot resize bitbuffer\n");
      exit(1);
    }
    str->bitbufLen += NALBUF_BLOCK_SIZE;
  }

  /* Read block of data */
  n = fread(str->bitbuf + str->bitbufDataLen, 1, NALBUF_BLOCK_SIZE, str->fn);

  str->bytesRead     += n;
  str->bitbufDataLen += n;

  return n;
}


/*
 *
 * findStartCode:
 *
 * Parameters:
 *      str                   Bitbuffer object
 *
 * Function:
 *      First next start code in AVC byte stream
 *
 * Returns:
 *      Length of start code
 *
 *      str->bitbufDataPos will point to first byte that follows start code
 */
static int findStartCode(byteStream_s *str)
{
  int numZeros;
  int startCodeFound;
  int i;
  int currByte;


  numZeros       = 0;
  startCodeFound = 0;

  i = str->bitbufDataPos;

  while (!startCodeFound) {

    if (i == str->bitbufDataLen) {
      /* We are at the end of data -> read more from the bitstream file */

      int n = readBytesFromFile(str);

      if (n == 0)
        /* End of bitstream -> stop search */
        break;
    }

    /* Find sequence of 0x00 ... 0x00 0x01 */
    while (i < str->bitbufDataLen) {

      currByte = str->bitbuf[i];
      i++;

      if (currByte > 1) /* If current byte is > 1, it cannot be part of a start code */
        numZeros = 0;
      else if (currByte == 0)  /* If current byte is 0, it could be part of a start code */
        numZeros++;
      else {                    /* currByte == 1 */
        if (numZeros > 1) {  /* currByte == 1. If numZeros > 1, we found a start code */
          startCodeFound = 1;
          break;
        }
        numZeros = 0;
      }
    }
  }

  str->bitbufDataPos = i;

  if (startCodeFound)
    return (numZeros + 1);
  else
    return 0;
}


/*
 *
 * getNalunitBits_ByteStream:
 *
 * Parameters:
 *      strIn                 Bytestream pointer
 *
 * Function:
 *      Read one NAL unit from bitstream file.
 *
 * Returns:
 *      1: No errors
 *      0: Could not read bytes (end of file)
 */
int getNalunitBits_ByteStream(void *strIn)
{
  byteStream_s *str;
  int numRemainingBytes;
  int startCodeLen;
  int nalUnitStartPos;


  str = (byteStream_s *)strIn;

  /*
   * Copy valid data to the beginning of the buffer
   */
  numRemainingBytes = str->bitbufDataLen - str->bitbufDataPos;

  if (numRemainingBytes > 0) {
    memcpy(str->bitbuf, str->bitbuf + str->bitbufDataPos, numRemainingBytes);
  }

  /* Update bitbuffer variables */
  str->bitbufDataLen = numRemainingBytes;
  str->bitbufDataPos = 0;

  /*
   * Find NAL unit boundaries
   */

  /* Find first start code */
  startCodeLen = findStartCode(str);

  if (startCodeLen == 0)
    return 0;

  /* Start address of the NAL unit */
  nalUnitStartPos = str->bitbufDataPos - startCodeLen;

  /* Find second start code */
  startCodeLen = findStartCode(str);

  /* Set data pointer to the beginning of the second start code */
  /* (i.e. to the end of the NAL unit)                          */
  if (startCodeLen != 0)
    str->bitbufDataPos -= startCodeLen;

  str->bitbufNalunit    = str->bitbuf + nalUnitStartPos;
  str->bitbufNalunitLen = str->bitbufDataPos;

  return 1;
}


#ifdef LINUX_BUILD
void SetFullScreen(Display* display, Window window)
{
  XEvent tmp;
  
  tmp.xclient.type = ClientMessage;
  tmp.xclient.serial = 0;
  tmp.xclient.send_event = True;
  tmp.xclient.message_type = XInternAtom(display, "_NET_WM_STATE", False);
  tmp.xclient.window = window;
  tmp.xclient.format = 32;
  tmp.xclient.data.l[0] = 1;
  tmp.xclient.data.l[1] = XInternAtom(
    display, "_NET_WM_STATE_FULLSCREEN", 0);
  tmp.xclient.data.l[2] = 0;
  tmp.xclient.data.l[3] = 0;
  tmp.xclient.data.l[4] = 0;
  
  if (!XSendEvent(
    display, 
    DefaultRootWindow(display), 
    0, 
    SubstructureRedirectMask | SubstructureNotifyMask, 
    &tmp))
  { printf("Cannot set into fullscreen mode"); }
  
  XSync(display, False);
}
#endif


/*
 *
 * main:
 *
 * Parameters:
 *      argc                  Number of parameters
 *      argv                  Parameter strings
 *
 * Function:
 *      Decoder main function
 *
 * Returns:
 *         0 ok
 *      <> 0 error
 *
 */
int main(int argc, char **argv)
{
  userParam_s param;
  avcdDecoder_t *decoder;
  byteStream_s strByte;
  avcdYUVbuffer_s recoBuf;
  statOverall_s globalStat;
  int result, seqEndFlag;
  avcdTimingInfo_s timingInfo = {0, 0, 0, 0};
  double interTime, frameTime;
  int		width, height; 
  char *outputRGB = NULL;    /* Contains the interleaved RGB with 16bits per pixel */
  char windowNotInitialized = 1;
  
#ifdef LINUX_BUILD
  Display *dpy; 
  int num_adaptors; 
  XvAdaptorInfo *adaptor_info; 
  int	screen; 
  Window root, win; 
  int a; 
  XvPortID port; 
  XSetWindowAttributes    wattr; 
  XEvent event; 
  GC gc; 
  XImage *ximage;
  XImage *ximage2;
  XTextProperty wm_name, icon_name; 
  XSizeHints sizeHints; 
  XWMHints wmHints; 
  int	x, y, p; 
  int originX, originY;
  char *adaptor_name = NULL; 
#endif

  
	/* Parse command line arguments  */
	if (!parseArg(argc, argv, &param)) {
		usage();
		exit(1);
	}

  /* This is mainly to disable compiler warning, width & height will be taken from the video stream */
  width = DISPLAY_WIDTH;
  height = DISPLAY_HEIGHT;

	/* Open video & bitstream files */
	openFiles(&param, &strByte);
	
	/* Zero out statistics */
	memset(&globalStat, 0, sizeof(statOverall_s));
	
	/* Open sequence */
	decoder = avcdOpen();
	
	if (decoder == NULL) {
		fprintf(stderr, "Could not open sequence\n");
		exit(1);
	}
	
#ifdef LINUX_BUILD
  originX = originY = 0;

  /* Initialize the xv stuff */
  wm_name.value = (unsigned char *) argv[0]; 
  wm_name.encoding = XA_STRING; 
  wm_name.format = 8; 
  wm_name.nitems = strlen (wm_name.value) + 1; 
  icon_name = wm_name; 
  
  dpy = XOpenDisplay (getenv("DISPLAY")); 
  screen = DefaultScreen (dpy); 
  root = RootWindow (dpy, screen); 
  
  XvQueryAdaptors (dpy, root, &num_adaptors, &adaptor_info); 
  port = None; 
  for (a = 0; a < num_adaptors && port == None; a++) 
  { 
    if (adaptor_name && !strcasestr (adaptor_info[a].name, adaptor_name)) 
      continue; 
#ifdef DEBUG_PRINT
    printf ("Adaptor \"%s\" has %d ports\n",  
      adaptor_info[a].name, 
      (int)(adaptor_info[a].num_ports)); 
#endif
    for (p = 0; p < adaptor_info[a].num_ports; p++) 
    { 
      if (XvGrabPort (dpy, adaptor_info[a].base_id + p, CurrentTime) == Success) 
      { 
        port = adaptor_info[a].base_id + p; 
        break; 
      } 
    } 
  } 
  
#ifndef MAEMO_EMULATOR    /* This crashes on Maemo emulator */
  if (port == None) 
  { 
    fprintf (stderr, "No port available on %s\n", 
      adaptor_info[a].name); 
    exit (1); 
  } 
#endif
  
  wattr.event_mask = NoEventMask; 
  win = XCreateSimpleWindow (dpy, root,  0, 0, 800, 480, 0, 0, 0); 
  
  sizeHints.flags = 0; 
  wmHints.flags = InputHint; 
  wmHints.input = True; 
  XSetWMProperties (dpy, win, 
    &wm_name, &icon_name, 
    argv, argc, 
    &sizeHints, &wmHints, 0); 
  
  XMapWindow (dpy, win); 
  SetFullScreen(dpy,win);
  
  gc = XCreateGC (dpy, win, 0, NULL); 
  
  ximage2 = XCreateImage (dpy, CopyFromParent, 16, ZPixmap, 0, (char *)(&yuyv[0][0][0]), 800, 480, 16, 800*2); 
  
  for (y = 0; y < 480; y++) 
  {
    for (x = 0; x < 800; x++) 
    { 
      yuyv[y][x][0] = 0; 
      yuyv[y][x][1] = 0; 
    }
  } 
  
  while(XPending(dpy))
  {
    XNextEvent (dpy, &event);
    printf(",");
  }
  
  XPutImage (dpy, win, gc, ximage2, 0, 0, 0, 0, 800, 480); 
#endif
  
  /*
   * Main decoder loop. Frames are decoded until there are no more frames.
   */
  seqEndFlag = 0;
  result     = AVCD_OK;
  
  while (!seqEndFlag) {
    
    /* result == AVCD_OK_STREAM_NOT_DECODED -> don't update bitbuffer */
    if (result != AVCD_OK_STREAM_NOT_DECODED) {
      if (!getNalunitBits_ByteStream(&strByte)) {
        strByte.bitbufNalunit    = 0;
        strByte.bitbufNalunitLen = 0;
      }
    }
    
    /* Decode one NAL unit */
    interTime = (double)clock()/CLOCKS_PER_SEC;
    result = avcdDecodeOneNal(decoder, strByte.bitbufNalunit,
      strByte.bitbufNalunitLen, &recoBuf, &timingInfo, outputRGB, param.writeOutYUV);
    
    frameTime = ((double)clock()/CLOCKS_PER_SEC) - interTime;
#ifdef DEBUG_PRINT
    printf("Frame decoding took %3.3f seconds\n", frameTime);
#endif
    
    switch (result) {
    case AVCD_OK:
    case AVCD_OK_STREAM_NOT_DECODED:
      
#ifdef LINUX_BUILD
      XPutImage (dpy, win, gc, ximage, 0, 0, originX, originY, width, height); 
#endif
      break;
      
    case AVCD_OK_FRAME_NOT_AVAILABLE:
      if (strByte.bitbufNalunit == 0 && strByte.bitbufNalunitLen == 0)
        seqEndFlag = 1;
      break;
      
    case AVCD_OK_RESOLUTION_AVAILABLE:
      if (strByte.bitbufNalunit == 0 && strByte.bitbufNalunitLen == 0)
        seqEndFlag = 1;
      else
      {
        /* Get the resolution and prepare output window */
        avcdGetResolution(decoder, &width, &height);

        if (windowNotInitialized) {
          windowNotInitialized = 0;

          /* Initialize the window */
          if(width == 0)
            width = DISPLAY_WIDTH;
          else
            width = width * 2;

          if(height == 0)
            height = DISPLAY_HEIGHT;
          else
            height = height * 2;
          
          if ((outputRGB = (char *)calloc((height*width*2), sizeof(char))) == NULL)
            return 0;
          
#ifdef LINUX_BUILD
          ximage = XCreateImage (dpy, CopyFromParent, 16, ZPixmap, 0, outputRGB, width, height, 16, width*2); 
          
          if(width < DISPLAY_WIDTH)
            originX = (DISPLAY_WIDTH - width)/2;
          if(height < DISPLAY_HEIGHT)
            originY = (DISPLAY_HEIGHT - height)/2;
          
          /* Make sure that the originX is even, otherwise the views will be switched */
          if(originX % 1)
            originX -= 1;
          
#ifdef DEBUG_PRINT
          printf("Width: %d, Height: %d origin: %d,%d\n",width,height,originX,originY);
#endif

#endif
        }
      }
      break;
      
    case AVCD_ERROR:
    default:
      printf("Error occured in AVC decoder\n");
      seqEndFlag = 1;
      break;
    }
  }
  
#ifdef DEBUG_PRINT
  printf("Close sequence\n");	
#endif
  
  /* Close sequence */
  avcdClose(decoder);
  
  /* Close video & bitstream files */
  closeFiles(&strByte);
  
  /* Free output array */
  if (outputRGB)
    free(outputRGB);

  if (!param.quiet) {
    /* Print decoding time */
    printf("took %3.3f seconds\n", (double)clock()/CLOCKS_PER_SEC);
  }
  
#ifdef DEBUG_PRINT
  if (!param.quiet) {
    /* print a brief report */
    printf("Total frames being decoded: %d\nI: %d, P: %d\n",
      (int)(globalStat.numIframes + globalStat.numPframes), (int)globalStat.numIframes, (int)globalStat.numPframes);
    printf("Total bits: %d\nI: %d, P: %d\n",
      (int)(globalStat.numBitsI + globalStat.numBitsP), (int)globalStat.numBitsI, (int)globalStat.numBitsP);
  }
#endif
  
  if (result == AVCD_ERROR) {
    printf("Decoder returned an error while decoding \"%s\"\n", param.inFile);
  }
  
  return 0;
}

