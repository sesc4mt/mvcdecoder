#include <Windows.h>
#include <iostream>
#include "mytimer.h"

using namespace std;

int main(){
	MyTimer timerIns;

	double fps = 29.97;

	int totalFrames = 100;

	timerIns.Start();

	//begin rendering
	LONGLONG _start = timerIns.getElapsedTime();
	LONGLONG _current;
	int frameToRender;
	int lastRenderedFrame = -1;
	while (true)
	{
		_current = timerIns.getElapsedTime() - _start;
		frameToRender = _current * fps / 1000000;
		if(frameToRender > totalFrames)
			break;
		if(frameToRender!=lastRenderedFrame)
		{
			cout << "render frame "<< frameToRender<<endl;
			lastRenderedFrame = frameToRender;
		}
	}
	
	return 0;
}