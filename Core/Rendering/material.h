#pragma once

#include "texture.h"

#include <glm/glm.hpp>
#include <string>

class Material
{
	public:
		Material(const Texture& init_texture, const glm::vec3& init_color, float init_specular_intensity = 2.0f, float init_specular_exp = 32.0f);
		virtual ~Material();
		Texture& getTexture() { return texture; };
		void setTexture(const Texture& new_texture) { texture = new_texture; hasTexture = true; };
		void setTexture(const std::string& fileName) { texture.setTexture(fileName); hasTexture = true; };
		glm::vec3& getColor() { return color; };
		void setColor(const glm::vec3& new_color) { color = new_color; };
		float getSpecularIntensity() { return specularIntensity; };
		void setSpecularIntensity(float new_intensity) { specularIntensity = new_intensity; };
		float getSpecularExponent() { return specularExponent; };
		void setSpecularExponent(float new_exp) { specularExponent = new_exp; };
		bool haveTexture() { return hasTexture; };
	private:
		Texture texture;
		glm::vec3 color;
		bool hasTexture;
		float specularIntensity;
		float specularExponent;
};

