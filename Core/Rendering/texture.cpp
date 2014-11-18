#include "texture.h"
#include "texture_resource.h"
#include "resource_manager.h"

Texture::Texture(const std::string& init_fileName) : fileName(init_fileName)
{
	resource = TextureResource::_get_resource(fileName);
}

Texture::~Texture()
{
	TextureResource::_remove_resource(fileName);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_2D, resource->getTextureID());
}
