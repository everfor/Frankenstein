#include "texture.h"
#include "resource_manager.h"

Texture::Texture()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::setTexture(const std::string& fileName)
{
	ResourceManager::LoadTexture(fileName, GL_TEXTURE_2D);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, texture);
}
