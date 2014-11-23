#include "texture.h"
#include "texture_resource.h"
#include "resource_manager.h"

Texture::Texture(const std::string& init_fileName) : fileName(init_fileName)
{
	resource = TextureResource::_get_resource(fileName);
}

Texture::~Texture()
{
}

void Texture::bind(int unit)
{
	assert(unit >= 0 && unit <= 31);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, resource->getTextureID());
}
