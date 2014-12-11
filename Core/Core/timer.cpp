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

// Get current time in seconds
double Timer::getCurrentTime()
{
#ifdef _WIN32
	DWORD current_time;
	current_time = GetTickCount();

	return (double)current_time / (double)MILLISEC_IN_SEC;
#else
	return 0;
#endif
}
