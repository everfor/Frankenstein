#pragma once

#include "resource.h"

#include <GL/glew.h>
#include <map>
#include <memory>
#include <vector>

class TextureResource;

class TextureResource : public Resource
{
	public:
		virtual ~TextureResource();
		GLuint getTextureID() { return id; };
		void setTextureID(GLuint new_id) { id = new_id; };
		static void _load_all();
		static void _clear();
		// Factory
		static TextureResource* _get_resource(const std::string& fileName);
		static void _remove_resource(const std::string& fileName);
	private:
		GLuint id;
		// Factory
		TextureResource();
		static std::map<std::string, std::unique_ptr<TextureResource>> _resources;
};

