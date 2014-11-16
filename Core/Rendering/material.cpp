#include "material.h"

Material::Material()
{
}

Material::~Material()
{
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