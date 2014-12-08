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
	for (std::map<std::string, std::unique_ptr<TextureResource>>::iterator it = _resources.begin();
		it != _resources.end();
		it++)
	{	
		// Store texture IDs
		it->second.get()->setTextureID(ids[index++]);
		// Bind resources
		ResourceManager::LoadTexture(it->second.get()->getTextureID(), it->first, it->second.get());

		// Mipmapping
		if (it->second.get()->getFilter() == GL_LINEAR_MIPMAP_NEAREST ||
			it->second.get()->getFilter() == GL_LINEAR_MIPMAP_LINEAR ||
			it->second.get()->getFilter() == GL_NEAREST_MIPMAP_NEAREST ||
			it->second.get()->getFilter() == GL_NEAREST_MIPMAP_LINEAR)
		{
			glGenerateMipmap(it->second.get()->getTarget());
		}
		else
		{
			glTexParameteri(it->second.get()->getTarget(), GL_TEXTURE_BASE_LEVEL, 0);
			glTexParameteri(it->second.get()->getTarget(), GL_TEXTURE_MAX_LEVEL, 0);
		}

		if (it->second.get()->getAttachments() != GL_NONE)
		{
			GLenum drawBuffers[1];
			drawBuffers[0] = it->second.get()->getAttachments() == GL_DEPTH_ATTACHMENT || it->second.get()->getAttachments() == GL_STENCIL_ATTACHMENT ?
														GL_NONE :
														it->second.get()->getAttachments();

			// Generate frame buffer
			GLuint buffer;
			glGenFramebuffers(1, &buffer);
			glBindFramebuffer(GL_FRAMEBUFFER, buffer);

			// RENDER BUFFER GOES BEFORE TEXUTURE2D BIDNING!!!
			if (it->second.get()->getAttachments() != GL_DEPTH_ATTACHMENT)
			{
				GLuint render_buffer;
				glGenRenderbuffers(1, &render_buffer);
				glBindRenderbuffer(GL_RENDERBUFFER, render_buffer);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 1024);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, render_buffer);
				
				it->second.get()->setRenderBufferID(render_buffer);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, it->second.get()->getAttachments(), it->second.get()->getTarget(), it->second.get()->getTextureID(), 0);
			glDrawBuffers(1, drawBuffers);
			it->second.get()->setFrameBufferID(buffer);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
			{
				throw ResourceException("Failed to create frame buffer.");
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}

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

			if (it->second.get()->getAttachments() != GL_DEPTH_ATTACHMENT)
			{
				GLuint render_buffer = it->second.get()->getRenderBufferID();
				glDeleteRenderbuffers(1, &render_buffer);
			}
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