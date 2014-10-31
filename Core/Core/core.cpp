#include "core.h"
#include "timer.h"

// Platform dependent include for sleep function
#ifdef _WIN32
#include <Windows.h>
#include <WinBase.h>	// Win 7 and lower
#include <synchapi.h>	// Win 8 and higher
#endif

#include <iostream>

Core::Core(int width, int height, std::string& title, int init_frame_rate) :
			window(Display(width, height, title)), is_running(false), frame_rate(init_frame_rate)
{
}

Core::~Core()
{
}

void Core::start()
{
	if (is_running)
	{
		return;
	}

	run();
}

void Core::run()
{
	// For counting frames
	int frames = 0;
	long frame_counter = 0.0;

	is_running = true;

	const double frame_time = 1.0 / (double)frame_rate;

	bool if_render = false;
	long last_time = Timer::getCurrentTime();
	long start_time = 0;
	double unprocessed_time = 0.0;

	while (is_running)
	{
		if_render = false;
		start_time = Timer::getCurrentTime();
		unprocessed_time += (start_time - last_time) / (double)MILLISEC_IN_SEC;
		frame_counter += start_time - last_time;
		last_time = start_time;

		while (unprocessed_time > frame_time)
		{
			if_render = true;
			unprocessed_time -= frame_time;

			if (window.closed())
			{
				stop();
				break;
			}

			// TODO: Update the game

			if (frame_counter >= MILLISEC_IN_SEC)
			{
				std::cout << frames << std::endl;
				frames = 0;
				frame_counter = 0;
			}
		}

		if (if_render)
		{
			render();
			frames++;
		}
		else
		{
			#ifdef _WIN32
			Sleep(MIN_SLEEP_TIME);
			#endif
		}
	}
}

void Core::stop()
{
	if (!is_running)
	{
		return;
	}

	is_running = false;
}

void Core::render()
{
	this->window.update();
}
