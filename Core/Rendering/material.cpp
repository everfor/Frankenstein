#include "material.h"
#include "resource_manager.h"

std::vector<Material*> Material::_materials;

Material::Material()
{
	_materials.push_back(this);
}

Material::~Material()
{
}

bool Material::hasTexture(const std::string& key)
{
	return textureMap.find(key) != textureMap.end();
}

Texture& Material::getTexture(const std::string& key)
{
	return textureMap.at(key);
}

glm::vec3& Material::getVector(const std::string& key)
{
	return vectorMap.at(key);
}

float Material::getFloat(const std::string& key)
{
	if (floatMap.find(key) != floatMap.end())
	{
		return floatMap.at(key);
	}

	return 0.0f;
}

void Material::_load_textures()
{
	int num = _materials.size();
	
	for (int i = 0; i < num; i++)
	{
		if (!_materials[i]->hasTexture(MATERIAL_NORMAL_TEXTURE))
		{
			_materials[i]->addTexture(MATERIAL_NORMAL_TEXTURE, Texture(DEFAULT_NORMAL_TEXTURE));
		}
	}

	TextureResource::_load_all();
}