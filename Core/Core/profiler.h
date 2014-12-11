#pragma once

#include <string>

class Profiler
{
	public:
		Profiler() : num_invocations(0), total_time(0.0), start_time(0.0) {};
		virtual ~Profiler() {};
		void startInvocation();
		void stopInvocation();
		double displayAndReset(const std::string& message, double dividend = 0.0);
	private:
		int num_invocations;
		double total_time;
		double start_time;
};

