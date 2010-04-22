#ifndef _CONFIG_H_
#define _CONFIG_H_

using namespace std;

// screen and image size
int gImageWidth = 720;
int	gImageHeight = 576;
wstring filenameWstrL,filenameWstrR;
string filenameStrL,filenameStrR;

//// knight's quest test
//string prefixR = "R:/Knights_Quest/L/Knights_Quest_576p";
//string prefixL = "R:/Knights_Quest/R/Knights_Quest_576p";
//string suffix = ".jpg";

// twoeye test
string prefixR = "R:/twoeye/L/twoeye_432x240";
string prefixL = "R:/twoeye/R/twoeye_432x240";
string suffix = ".jpg";

// video playback settings
double fps = 200;
int totalFrames = 1608;

// debug output
ofstream fout;

#endif