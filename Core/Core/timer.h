#pragma once

/*
*	This class is platform dependent
*/

#define MILLISEC_IN_SEC			1000

class Timer
{
	public:
		Timer();
		virtual ~Timer();
		static long getCurrentTime();
		static long getDelta();
	private:
		static long last;
		static long current;
};

