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
		GLuint getFrameBufferID() { return frame_buffer_id; };
		void setFrameBufferID(GLuint new_id) { frame_buffer_id = new_id; };
		GLenum getTarget() { return target; };
		GLfloat getFilter() { return filter; };
		GLenum getAttachments() { return attachments; };
		// Frame Buffer
		void bindAsFrameBuffer(int width, int height);
		// Static methods
		static void _load_all();
		static void _clear();
		// Factory
		static TextureResource* _get_resource(const std::string& fileName, GLenum target, GLfloat filter, GLenum attachments = GL_NONE);
		static void _remove_resource(const std::string& fileName);
	private:
		GLuint id;
		GLenum target;
		GLfloat filter;
		GLuint frame_buffer_id;
		GLenum attachments;
		// Factory
		TextureResource(GLenum init_target = GL_TEXTURE_2D, GLfloat init_filter = GL_LINEAR, GLenum attachments = GL_NONE);
		static std::map<std::string, std::unique_ptr<TextureResource>> _resources;
};

