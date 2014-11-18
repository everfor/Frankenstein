#pragma once

#include "resource.h"

#include <GL/glew.h>
#include <map>
#include <vector>

class TextureResource : public Resource
{
	public:
		TextureResource(const std::string& fileName);
		virtual ~TextureResource();
		GLuint getTextureID() { return id; };
		static void _load_all();
		static void _clear();
	private:
		GLuint id;
		static std::vector<std::string> _resource_files;
		static std::vector<GLuint*> _texture_ids;
};

