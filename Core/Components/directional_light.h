#pragma once

#include "base_light.h"

#include <glm/glm.hpp>

class DirectionalLight : public BaseLight
{
	public:
		DirectionalLight(BaseLight& init_base = BaseLight(), glm::vec3& init_dir = glm::vec3()) : BaseLight(init_base), direction(glm::normalize(init_dir)) { };
		virtual ~DirectionalLight() {};
		glm::vec3& getDirection() { return direction; }
		void setDirection(glm::vec3& new_dir) { direction = glm::normalize(new_dir); };
		Shader* getShader() override;
	private:
		glm::vec3 direction;
};

