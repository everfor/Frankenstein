#pragma once

#include "base_light.h"

#include <glm/glm.hpp>

class DirectionalLight : public BaseLight
{
	public:
		DirectionalLight(BaseLight& init_base, glm::vec3& init_dir) : BaseLight(init_base), direction(glm::normalize(init_dir)) { };
		virtual ~DirectionalLight() {};
		glm::vec3& getDirection() { return direction; }
		void setDirection(glm::vec3& new_dir) { direction = glm::normalize(new_dir); };
	private:
		glm::vec3 direction;
};
