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
		GLuint getRenderBufferID() { return render_buffer_id; };
		void setRenderBufferID(GLuint new_id) { render_buffer_id = new_id; };
		GLenum getTarget() { return target; };
		GLfloat getFilter() { return filter; };
		GLenum getAttachments() { return attachments; };
		GLenum getInternalFormat() { return internal_format; };
		GLenum getFormat() { return format; };
		bool getClamp() { return clamp; };
		// Frame Buffer
		void bindAsFrameBuffer(int width, int height);
		// Static methods
		static void _load_all();
		static void _clear();
		// Factory
		static TextureResource* _get_resource(const std::string& fileName, GLenum target, GLenum internal_format, GLenum format, GLfloat filter, bool clamp, GLenum attachments = GL_NONE);
		static void _remove_resource(const std::string& fileName);
	private:
		GLuint id;
		GLenum target;
		GLfloat filter;
		GLuint frame_buffer_id;
		GLuint render_buffer_id;
		GLenum internal_format;
		GLenum format;
		bool clamp;
		GLenum attachments;
		// Factory
		TextureResource(GLenum init_target = GL_TEXTURE_2D, GLenum init_internal_format = GL_RGBA, GLenum init_format = GL_RGBA, GLfloat init_filter = GL_LINEAR_MIPMAP_LINEAR, bool init_clamp = false, GLenum attachments = GL_NONE);
		static std::map<std::string, std::unique_ptr<TextureResource>> _resources;
};

