#pragma once

#include "texture_resource.h"

#include <gl/glew.h>
#include <string>
#include <map>

class Texture
{
	public:
		Texture(const std::string& fileName);
		virtual ~Texture();
		void setTexture(const std::string& fileName);
		void bind();
	private:
		std::string fileName;
		TextureResource *resource;
};

