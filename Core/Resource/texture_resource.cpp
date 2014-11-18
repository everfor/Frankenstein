#include "texture_resource.h"
#include "resource_manager.h"
#include "exceptions.h"

std::map<std::string, std::unique_ptr<TextureResource>> TextureResource::_resources;

TextureResource::TextureResource() : Resource()
{
	increaseRefCout();
}

TextureResource::~TextureResource()
{
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
		ResourceManager::LoadTexture(it->first, it->second.get()->getTextureID());
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
	}

	glDeleteTextures(_resources.size(), ids);

	_resources.clear();
}

TextureResource* TextureResource::_get_resource(const std::string& fileName)
{
	if (_resources.find(fileName) != _resources.end())
	{
		_resources.at(fileName).get()->increaseRefCout();
		return _resources.at(fileName).get();
	}

	_resources.insert(std::pair<std::string, std::unique_ptr<TextureResource>>(fileName, std::unique_ptr<TextureResource>(new TextureResource())));
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