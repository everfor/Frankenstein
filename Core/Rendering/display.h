#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include <exception>
#include <string>
#include <memory>

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
		virtual ~Display();
		unsigned int getWidth() const { return width; };
		unsigned int getHeight() const { return height; };
		std::string getTitle() const { return title; };
		glm::vec2& getCenter() { return center; };
		bool closed() const { return isClosed; }
		void update();
		// Static methods
		static Display* GetDisplay(unsigned int init_width = 0, unsigned int init_height = 0, std::string& init_title = std::string());
		static unsigned int GetWidth() { return _window.get()->getWidth(); };
		static unsigned int GetHeight() { return _window.get()->getHeight(); };
		static std::string GetTitle() { return _window.get()->getTitle(); };
		static glm::vec2& GetCenter() { return _window.get()->getCenter(); };
		static void BindAsRenderTarget();
	private:
		Display(unsigned int init_width = DEFAULT_WIDTH, unsigned int init_height = DEFAULT_HEIGHT, std::string& init_name = std::string(DEFAULT_TITLE));
		std::string title;
		unsigned int width, height;
		bool isClosed;
		glm::vec2 center;
		SDL_Window* window;
		SDL_GLContext context;
		// Singleton
		static std::unique_ptr<Display> _window;
		static bool _is_initialized;
};

