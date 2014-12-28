#include "profiler.h"

#include <cassert>
#include <string>
#include <iostream>

#include "timer.h"

void Profiler::startInvocation()
{
	start_time = Timer::getCurrentTime();
}

void Profiler::stopInvocation()
{
	assert(start_time != 0.0);
	++num_invocations;
	total_time += Timer::getCurrentTime() - start_time;
	start_time = 0.0;
}

double Profiler::displayAndReset(const std::string& message, double dividend)
{
	double result;
	double div = dividend == 0 ? (double)num_invocations : dividend;

	if (div == 0.0)
	{
		result = 0.0;
	}
	else
	{
		result = (1000.0 * total_time) / div;
	}

	// Print out profiling info
	std::cout << message << ": " << "\t\t\t" << result << "ms." << std::endl;
	
	total_time = 0.0;
	num_invocations = 0;
	return result;
}