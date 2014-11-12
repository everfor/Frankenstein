#pragma once

#include <glm/glm.hpp>

class BaseLight
{
	public:
		BaseLight(glm::vec3& init_color, float init_intensity) : color(init_color), intensity(init_intensity) {};
		virtual ~BaseLight() {};
		glm::vec3& getColor() { return color; };
		void setColor(glm::vec3& new_color) { color = new_color; };
		float getIntensity() { return intensity; };
		void setIntensity(float new_intensity) { intensity = new_intensity; };
	private:
		glm::vec3 color;
		float intensity;
};

