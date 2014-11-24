#pragma once

#include "texture_resource.h"

#include <gl/glew.h>
#include <string>
#include <map>

// Texture slots
#define DIFFUSE_TEXTEURE_SLOT		0
#define NORMAL_TEXTURE_SLOT			1
#define DISP_TEXTURE_SLOT			2

class Texture
{
	public:
		Texture(const std::string& fileName);
		virtual ~Texture();
		void setTexture(const std::string& fileName);
		std::string& getTexture() { return fileName; };
		TextureResource* getResource() { return resource; };
		void bind(int unit);
	private:
		std::string fileName;
		TextureResource *resource;
};

