#include "texture_resource.h"
#include "resource_manager.h"

std::vector<std::string> TextureResource::_resource_files;
std::vector<GLuint*> TextureResource::_texture_ids;

TextureResource::TextureResource(const std::string& fileName) : Resource()
{
	increaseRefCout();
	_resource_files.push_back(fileName);
	_texture_ids.push_back(&id);
}

TextureResource::~TextureResource()
{
}

void TextureResource::_load_all()
{
	GLuint *ids = (GLuint*)malloc(_texture_ids.size() * sizeof(GLuint));
	glGenTextures(_texture_ids.size(), ids);

	// Generate texture ids
	for (int i = 0; i < _texture_ids.size(); i++)
	{
		*_texture_ids[i] = ids[i];
	}

	free(ids);

	// Bind resources
	for (int i = 0; i < _texture_ids.size(); i++)
	{
		ResourceManager::LoadTexture(_resource_files[i], *_texture_ids[i]);
	}
}

void TextureResource::_clear()
{
	GLuint *ids = (GLuint*)malloc(_texture_ids.size() * sizeof(GLuint));
	for (int i = 0; i < _texture_ids.size(); i++)
	{
		ids[i] = *_texture_ids[i];
	}

	glDeleteTextures(_texture_ids.size(), ids);

	_texture_ids.clear();
	_resource_files.clear();
}