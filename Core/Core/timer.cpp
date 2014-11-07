#include "timer.h"

#ifdef _WIN32
#include <Windows.h>
#endif

long Timer::last = 0;
long Timer::current = 0;

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

long Timer::getDelta()
{
	last = current;
	current = getCurrentTime();

	return current - last;
}
