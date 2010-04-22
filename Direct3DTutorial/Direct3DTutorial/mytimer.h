#ifndef _MYTIMER_H_
#define _MYTIMER_H_
#include <windows.h>

class MyTimer {
private:
    LONGLONG _freq;
    LARGE_INTEGER _begin;
    LARGE_INTEGER _current;
    LARGE_INTEGER _end;

public:
    LONGLONG costTime;            // 花费的时间(精确到ms)

public:
    MyTimer() {
        LARGE_INTEGER tmp;
        QueryPerformanceFrequency(&tmp);
        _freq = tmp.QuadPart;
        costTime = 0;
    }

    void Start() {
        QueryPerformanceCounter(&_begin);
    }

    void End() {
        QueryPerformanceCounter(&_end);
        costTime = (LONGLONG)((_end.QuadPart - _begin.QuadPart) * 1000000 / _freq);
    }

    LONGLONG getElapsedTime() {
        QueryPerformanceCounter(&_current);
        return (LONGLONG)((_current.QuadPart * 1000000 - _begin.QuadPart* 1000000)  / _freq);
    }

    void Reset() {
        costTime = 0;
    }

    inline unsigned __int64 GetCycleCount() {
        __asm _emit 0x0F
        __asm _emit 0x31
    }
};
#endif