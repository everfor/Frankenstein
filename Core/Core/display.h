#pragma once

#include <GL/glew.h>
#include <SDL/SDL.h>
#include <exception>
#include <string>

// Default display parameters
#define COLOR_SIZE						8
#define ALPHA_SIZE						8
#define USE_DOUBLE_BUFFER				1
// Default values for window
#define DEFAULT_WIDTH					800
#define DEFAULT_HEIGHT					600
#define DEFAULT_TITLE					"Frankenstein"

class Display
{
	public:
		Display(unsigned int init_width = DEFAULT_WIDTH, unsigned int init_height = DEFAULT_HEIGHT, std::string& init_name = std::string(DEFAULT_TITLE));
		virtual ~Display();
		unsigned int getWidth() const { return width; };
		unsigned int getHeight() const { return height; };
		std::string getTitle() const { return title; };
		bool closed() const { return isClosed; }
		void update();
	private:
		std::string title;
		unsigned int width, height;
		bool isClosed;

		SDL_Window* window;
		SDL_GLContext context;
};

