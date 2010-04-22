#ifndef _CONFIG_H_
#define _CONFIG_H_

using namespace std;

// screen and image size
int gImageWidth = 1280;
int	gImageHeight = 720;
wstring filenameWstrL,filenameWstrR;
string filenameStrL,filenameStrR;
LPCWSTR filenameL,filenameR;
LPCSTR filenameLL,filenameRR;

// knight's quest test
// RAM DISK
//string prefixR = "R:/Knights_Quest/L/Knights_Quest_576p";
//string prefixL = "R:/Knights_Quest/R/Knights_Quest_576p";
// HDD
string prefixR = "E:/FTProot/MVC/incoming/imgSeq/Knights_Quest/L/Knights_Quest_576p";
string prefixL = "E:/FTProot/MVC/incoming/imgSeq/Knights_Quest/R/Knights_Quest_576p";
string suffix = ".jpg";
int totalFrames = 2615;

//// twoeye test
//// RAM DISK
////string prefixR = "R:/twoeye/L/twoeye_432x240";
////string prefixL = "R:/twoeye/R/twoeye_432x240";
//// HDD
//string prefixR = "E:/FTProot/MVC/incoming/imgSeq/twoeye/L/twoeye_432x240";
//string prefixL = "E:/FTProot/MVC/incoming/imgSeq/twoeye/R/twoeye_432x240";
//string suffix = ".jpg";
//int totalFrames = 1608;

// video playback settings
double fps = 100;

// debug output
ofstream fout;

#endif