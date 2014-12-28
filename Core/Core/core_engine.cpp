#include "core_engine.h"
#include "timer.h"
#include "input.h"
#include "rendering_engine.h"
#include "physics_engine.h"

// Platform dependent include for sleep function
#ifdef _WIN32
#include <Windows.h>
#include <WinBase.h>	// Win 7 and lower
#include <synchapi.h>	// Win 8 and higher
#endif

#include <iostream>

CoreEngine::CoreEngine(int width, int height, std::string& title, int init_frame_rate, float camera_fov, float camera_z_near, float camera_z_far, glm::vec3& camera_pos) :
			window(Display::GetDisplay(width, height, title)), is_running(false), frame_rate(init_frame_rate), 
			renderingEngine(RenderingEngine()), physicsEngine(PhysicsEngine())
{
}

CoreEngine::~CoreEngine()
{
}

void CoreEngine::setGame(Game *new_game)
{
	game = new_game;
}

void CoreEngine::start()
{
	if (is_running)
	{
		return;
	}

	run();
}

void CoreEngine::run()
{
	// For counting frames
	int frames = 0;
	double frame_counter = 0.0;

	is_running = true;

	const double frame_time = 1.0 / (double)frame_rate;

	bool if_render = false;
	double last_time = Timer::getCurrentTime();
	double start_time = 0;
	double unprocessed_time = 0.0;

	while (is_running)
	{
		if_render = false;
		start_time = Timer::getCurrentTime();
		unprocessed_time += (start_time - last_time);
		frame_counter += start_time - last_time;
		last_time = start_time;

		while (unprocessed_time > frame_time)
		{
			if_render = true;
			unprocessed_time -= frame_time;

			if (window->closed())
			{
				stop();
				break;
			}

			// Update inputs
			Input::Update();
			// Update the game
			game->input(frame_time);
			game->update(frame_time);

			if (frame_counter >= 1.0)
			{
				// Display Profiling info for Rendering engine
				renderingEngine.displayProfilerInfo((double)frames);
				renderingEngine.displayWindowSyncProfilerInfo((double)frames);

				// Total time each frame
				std::cout << "Total time:" << "\t\t\t" << (1000.0 * frame_counter) / (double)frames << "ms." << std::endl << std::endl;

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

void CoreEngine::stop()
{
	if (!is_running)
	{
		return;
	}

	is_running = false;
}

void CoreEngine::render()
{
	game->render();
	window->update();
}
