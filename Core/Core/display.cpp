#include "display.h"

const std::string DisplayException::_HEADER = "DISPLAY ERROR: ";

Display::Display(unsigned int init_width, unsigned int init_height, std::string& init_title) :
	width(init_width), height(init_height), title(init_title), isClosed(false)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, COLOR_SIZE);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, COLOR_SIZE);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, COLOR_SIZE);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, ALPHA_SIZE);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 3 * COLOR_SIZE + ALPHA_SIZE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, USE_DOUBLE_BUFFER);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);

	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		throw;
	}
}

Display::~Display()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Display::update()
{
	SDL_GL_SwapWindow(window);

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			isClosed = true;
		}
	}
}