#pragma once

#include <GL/glew.h>
#include <SDL/SDL.h>
#include <string>
#include <memory>

#include "display.h"
#include "game.h"
#include "rendering_engine.h"

#define FRAME_CAP			1000
#define MIN_SLEEP_TIME		1

class CoreEngine
{
	public:
		CoreEngine(int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, std::string& title = std::string(DEFAULT_TITLE), int frame_rate = FRAME_CAP);
		virtual ~CoreEngine();
		void setGame(Game *new_game);
		void start();
		void stop();
	private:
		void run();
		void render();
		Display window;
		bool is_running;
		unsigned int frame_rate;
		RenderingEngine renderingEngine;
		std::unique_ptr<Game> game;
};

