#pragma once

#include "base_light.h"

#include <glm/glm.hpp>

class DirectionalLight : public BaseLight
{
	public:
		DirectionalLight(BaseLight& init_base = BaseLight()) : BaseLight(init_base) { };
		virtual ~DirectionalLight() {};
		glm::vec3& getDirection() { return getTransform()->getTransformedForward(); }
		Shader* getShader() override;
};

