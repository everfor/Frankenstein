#include "texture.h"
#include "resource_manager.h"

unsigned int Texture::_active_textures = 0;

Texture::Texture()
{
	activeTextureID = 0;
	glGenTextures(1, &texture);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::setTexture(const std::string& fileName)
{
	ResourceManager::LoadTexture(fileName, GL_TEXTURE_2D);
	activeTextureID = ++_active_textures;
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0 + activeTextureID);
	glBindTexture(GL_TEXTURE_2D, texture);
}
