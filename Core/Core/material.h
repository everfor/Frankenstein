#pragma once

#include "texture.h"

#include <glm/glm.hpp>
#include <string>

class Material
{
	public:
		Material(const Texture& init_texture, const glm::vec3& init_color);
		virtual ~Material();
		Texture& getTexture() { return texture; };
		void setTexture(const Texture& new_texture) { texture = new_texture; hasTexture = true; };
		void setTexture(const std::string& fileName) { texture.setTexture(fileName); hasTexture = true; };
		glm::vec3& getColor() { return color; };
		void setColor(const glm::vec3& new_color) { color = new_color; };
		bool haveTexture() { return hasTexture; };
	private:
		Texture texture;
		glm::vec3 color;
		bool hasTexture;
};

