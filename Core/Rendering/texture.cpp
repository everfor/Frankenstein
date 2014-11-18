#include "texture.h"
#include "resource_manager.h"

std::map<std::string, TextureResource*> Texture::_resources;

Texture::Texture(const std::string& init_fileName) : fileName(init_fileName)
{
	if (_resources.find(fileName) != _resources.end())
	{
		resource = _resources.at(fileName);
		resource->increaseRefCout();
	}
	else
	{
		resource = new TextureResource(fileName);
		_resources.insert(std::pair<std::string, TextureResource*>(fileName, resource));
	}
}

Texture::~Texture()
{
	resource->decreaseRefCout();
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_2D, resource->getTextureID());
}
