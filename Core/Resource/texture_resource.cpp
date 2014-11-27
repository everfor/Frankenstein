#include "texture_resource.h"
#include "resource_manager.h"
#include "exceptions.h"

std::map<std::string, std::unique_ptr<TextureResource>> TextureResource::_resources;

TextureResource::TextureResource(GLenum init_target, GLenum init_internal_format, GLenum init_format, GLfloat init_filter, bool init_clamp, GLenum init_attachments) :
			Resource(), target(init_target), filter(init_filter), frame_buffer_id(0), internal_format(init_internal_format), format(init_format), clamp(init_clamp), attachments(init_attachments)
{
	increaseRefCout();
}

TextureResource::~TextureResource()
{
}

void TextureResource::bindAsFrameBuffer(int width, int height)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frame_buffer_id);
	glViewport(0, 0, width, height);
}

void TextureResource::_load_all()
{
	// Generate textures
	GLuint *ids = (GLuint*)malloc(_resources.size() * sizeof(GLuint));
	glGenTextures(_resources.size(), ids);

	int index = 0;
	int frame_buffer_count = 0;
	// Used for setting draw buffers for frame buffers
	GLenum *drawBuffers = (GLuint*)malloc(_resources.size() * sizeof(GLuint));
	for (std::map<std::string, std::unique_ptr<TextureResource>>::iterator it = _resources.begin();
		it != _resources.end();
		it++)
	{	
		// Store texture IDs
		it->second.get()->setTextureID(ids[index]);
		// Bind resources
		ResourceManager::LoadTexture(it->second.get()->getTextureID(), it->first, it->second.get());

		drawBuffers[index++] = it->second.get()->getAttachments() == GL_DEPTH_ATTACHMENT || it->second.get()->getAttachments() == GL_STENCIL_ATTACHMENT ?
																					GL_NONE :
																					it->second.get()->getAttachments();

		if (it->second.get()->getAttachments() != GL_NONE)
		{
			++frame_buffer_count;

			// Generate frame buffer
			GLuint buffer;
			glGenFramebuffers(1, &buffer);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, buffer);
			it->second.get()->setFrameBufferID(buffer);

			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, it->second.get()->getAttachments(), it->second.get()->getTarget(), it->second.get()->getTextureID(), 0);
		}
	}

	if (frame_buffer_count > 0)
	{
		glDrawBuffers(_resources.size(), drawBuffers);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			throw ResourceException("Failed to generate frame buffer.");
		}
	}

	free(drawBuffers);
	free(ids);
}

void TextureResource::_clear()
{
	GLuint *ids = (GLuint*)malloc(_resources.size() * sizeof(GLuint));
	int index = 0;
	for (std::map<std::string, std::unique_ptr<TextureResource>>::iterator it = _resources.begin();
		it != _resources.end();
		it++)
	{
		ids[index++] = it->second.get()->getTextureID();

		if (it->second.get()->getAttachments() != GL_NONE)
		{
			// Delete frame buffer
			GLuint buffer = it->second.get()->getFrameBufferID();
			glDeleteFramebuffers(1, &buffer);
		}
	}

	glDeleteTextures(_resources.size(), ids);

	_resources.clear();
}

TextureResource* TextureResource::_get_resource(const std::string& fileName, GLenum target, GLenum internal_format, GLenum format, GLfloat filter, bool clamp, GLenum attachments)
{
	if (_resources.find(fileName) != _resources.end())
	{
		_resources.at(fileName).get()->increaseRefCout();
		return _resources.at(fileName).get();
	}

	_resources.insert(std::pair<std::string, std::unique_ptr<TextureResource>>(fileName, std::unique_ptr<TextureResource>(new TextureResource(target, internal_format, format, filter, clamp, attachments))));
	return _resources.at(fileName).get();
}

void TextureResource::_remove_resource(const std::string& fileName)
{
	if (_resources.find(fileName) == _resources.end())
	{
		throw ResourceException("No texture resource named " + fileName + " found.");
	}

	_resources.at(fileName).get()->decreaseRefCout();
}