#pragma once

#include <GL/glew.h>
#include <SDL/SDL.h>
#include <string>
#include <memory>

#include "display.h"
#include "game.h"

#define FRAME_CAP			1000
#define MIN_SLEEP_TIME		1

class Core
{
	public:
		Core(int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, std::string& title = std::string(DEFAULT_TITLE), int frame_rate = FRAME_CAP);
		virtual ~Core();
		void setGame(Game *new_game);
		void start();
		void stop();
	private:
		void run();
		void render();
		Display window;
		bool is_running;
		unsigned int frame_rate;
		std::unique_ptr<Game> game;
};

