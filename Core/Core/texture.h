#pragma once

#include <gl/glew.h>
#include <string>

class Texture
{
	public:
		Texture();
		virtual ~Texture();
		void setTexture(const std::string& fileName);
		void bind();
	private:
		GLuint texture;
};

