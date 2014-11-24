#pragma once

#include "texture.h"

#include <glm/glm.hpp>
#include <string>
#include <map>
#include <vector>

#define MATERIAL_DIFFUSE_TEXTURE			"diffuse_texture"
#define MATERIAL_NORMAL_TEXTURE				"normal_texture"
#define MATERIAL_DISP_TEXTURE				"disp_texture"
#define MATERIAL_SPECULAR_INTENSITY			"specular_intensity"
#define MATERIAL_SPECULAR_EXPONENT			"specular_exponent"
#define MATERIAL_DISP_SCALE					"disp_scale"
#define MATERIAL_DISP_BIAS					"disp_bias"
#define MATERIAL_DISP_OFFSET				"disp_offset"

#define DEFAULT_NORMAL_TEXTURE				"./res/textures/default_normal.jpg"
#define DEFAULT_DISP_TEXTURE				"./res/textures/default_disp.png"

class Material
{
	public:
		Material(float specular_intensity, float specular_exponent,
				const std::string& diffuse_texture,
				const std::string& normal_texture = DEFAULT_NORMAL_TEXTURE,
				const std::string& disp_texture = DEFAULT_DISP_TEXTURE,
				float disp_scale = 0.0f, float disp_offset = 0.0f);
		virtual ~Material();
		void addTexture(const std::string& key, const Texture& value) { textureMap.insert(std::pair<std::string, Texture>(key, value)); };
		void addVector(const std::string& key, const glm::vec3& value) { vectorMap.insert(std::pair<std::string, glm::vec3>(key, value)); };
		void addFloat(const std::string& key, const float value) { floatMap.insert(std::pair<std::string, float>(key, value)); };
		bool hasTexture(const std::string& key);
		Texture& getTexture(const std::string& key);
		glm::vec3& getVector(const std::string& key);
		float getFloat(const std::string& key);
		// Static methods
		static void _load_textures();
	private:
		std::map<std::string, Texture> textureMap;
		std::map<std::string, glm::vec3> vectorMap;
		std::map<std::string, float> floatMap;
		// Keeps track of all materials
		static std::vector<Material*> _materials;
};

