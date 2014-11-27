#include "display.h"
#include "exceptions.h"

bool Display::_is_initialized = false;
std::unique_ptr<Display> Display::_window;

Display* Display::GetDisplay(unsigned int init_width, unsigned int init_height, std::string& init_title)
{
	if (!_is_initialized)
	{
		_window.reset(new Display(init_width, init_height, init_title));
		_is_initialized = true;
	}

	return _window.get();
}

Display::Display(unsigned int init_width, unsigned int init_height, std::string& init_title) :
			width(init_width), height(init_height), title(init_title), isClosed(false), center(glm::vec2(width / 2.0, height / 2.0))
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

	glewExperimental = GL_TRUE;
	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		throw DisplayException("Failed to initialize OpenGL.");
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

void Display::BindAsRenderTarget()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glViewport(0, 0, GetWidth(), GetHeight());
}