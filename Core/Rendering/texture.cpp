#include "texture.h"
#include "texture_resource.h"
#include "resource_manager.h"

Texture::Texture(const std::string& init_fileName, const GLenum target, const GLenum internal_format, const GLenum format, const GLfloat filter, bool clamp, GLenum attachments) : numTextures(1)
{
	resources.push_back(TextureResource::_get_resource(init_fileName, target, internal_format, format, filter, clamp, attachments));
}

Texture::Texture(const std::string *fileNames, const int num_textures, const GLenum *targets, const GLenum *internal_formats, const GLenum *formats, const GLfloat *filters, bool *clamps, const GLenum *attachments) : numTextures(num_textures)
{
	assert(num_textures >= 1);

	for (int i = 0; i < numTextures; i++)
	{
		resources.push_back(TextureResource::_get_resource(fileNames[i], targets[i], internal_formats[i], formats[i], filters[i], clamps[i], attachments[i]));
	}
}

Texture::~Texture()
{
}

void Texture::bind(int unit)
{
	assert(unit >= 0 && unit <= 31);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, resources[0]->getTextureID());
}

void Texture::bindAsRenderTarget()
{
	glBindTexture(GL_TEXTURE_2D, resources[0]->getTextureID());
	glBindFramebuffer(GL_FRAMEBUFFER, resources[0]->getFrameBufferID());
	glViewport(0, 0, 1024, 1024);
}