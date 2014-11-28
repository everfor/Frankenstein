#pragma once

#include "texture_resource.h"

#include <gl/glew.h>
#include <string>
#include <map>

// Texture slots
#define DIFFUSE_TEXTEURE_SLOT		0
#define NORMAL_TEXTURE_SLOT			1
#define DISP_TEXTURE_SLOT			2
#define SHADOW_TEXTURE_SLOT			3

class Texture
{
	public:
		Texture(const std::string& fileName, const GLenum target = GL_TEXTURE_2D, const GLenum internal_format = GL_RGBA, const GLenum format = GL_RGBA, const GLfloat filter = GL_LINEAR, bool clmap = false, const GLenum attachments = GL_NONE);
		Texture(const std::string *fileNames, const int num_textures, const GLenum *targets, const GLenum *internal_formats, const GLenum *formats, const GLfloat *filters, bool *clamps, const GLenum *attachments);
		virtual ~Texture();
		void setTexture(const std::string& fileName);
		TextureResource* getResource() { return resources[0]; };
		void bind(int unit);
		void bindAsRenderTarget();
	private:
		int numTextures;
		std::vector<TextureResource*> resources;
};

