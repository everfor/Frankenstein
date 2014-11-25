#include "texture.h"
#include "texture_resource.h"
#include "resource_manager.h"

Texture::Texture(const std::string& init_fileName, GLenum target, GLfloat filter, GLenum attachments) : numTextures(1)
{
	resources.push_back(TextureResource::_get_resource(init_fileName, target, filter, attachments));
}

Texture::Texture(const std::string *fileNames, const int num_textures, const GLenum *targets, const GLfloat *filters, const GLenum *attachments) : numTextures(num_textures)
{
	assert(num_textures >= 1);

	for (int i = 0; i < numTextures; i++)
	{
		resources.push_back(TextureResource::_get_resource(fileNames[i], targets[i], filters[i], attachments[i]));
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

}