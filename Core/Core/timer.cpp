#include "timer.h"

#ifdef _WIN32
#include <Windows.h>
#endif

Timer::Timer()
{
}


Timer::~Timer()
{
}

// Get current time in milliseconds
long Timer::getCurrentTime()
{
#ifdef _WIN32
	SYSTEMTIME time;
	GetSystemTime(&time);
	return time.wSecond * 1000 + time.wMilliseconds;
#else
	return 0;
#endif
}
