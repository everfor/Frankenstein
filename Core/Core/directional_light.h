#pragma once

#include "base_light.h"

#include <glm/glm.hpp>

class DirectionalLight
{
	public:
		// HACK: Need to reverse x direction for some reason.
		DirectionalLight(BaseLight& init_base, glm::vec3& init_dir) : base(init_base), direction(glm::normalize(init_dir)) { };
		virtual ~DirectionalLight() {};
		BaseLight& getBaseLight() { return base; };
		void setBaseLight(BaseLight& new_base) { base = new_base; };
		glm::vec3& getDirection() { return direction; }
		void setDirection(glm::vec3& new_dir) { direction = glm::normalize(new_dir); };
	private:
		BaseLight base;
		glm::vec3 direction;
};

