#pragma once

#include "texture.h"

#include <glm/glm.hpp>
#include <string>
#include <map>

#define MATERIAL_DIFFUSE_TEXTURE			"diffuse_texture"
#define MATERIAL_SPECULAR_INTENSITY			"specular_intensity"
#define MATERIAL_SPECULAR_EXPONENT			"specular_exponent"

class Material
{
	public:
		Material();
		virtual ~Material();
		void addTexture(const std::string& key, const Texture& value) { textureMap.insert(std::pair<std::string, Texture>(key, value)); };
		void addVector(const std::string& key, const glm::vec3& value) { vectorMap.insert(std::pair<std::string, glm::vec3>(key, value)); };
		void addFloat(const std::string& key, const float value) { floatMap.insert(std::pair<std::string, float>(key, value)); };
		Texture& getTexture(const std::string& key);
		glm::vec3& getVector(const std::string& key);
		float getFloat(const std::string& key);
	private:
		std::map<std::string, Texture> textureMap;
		std::map<std::string, glm::vec3> vectorMap;
		std::map<std::string, float> floatMap;
};

