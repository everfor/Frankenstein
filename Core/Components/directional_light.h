#pragma once

#include "base_light.h"

#include <glm/glm.hpp>

class DirectionalLight : public BaseLight
{
	public:
		DirectionalLight(BaseLight& init_base = BaseLight(), float init_shadow_area = 20.0f);
		virtual ~DirectionalLight() {};
		glm::vec3& getDirection() { return getTransform()->getTransformedForward(); }
		Shader* getShader() override;
		virtual glm::vec3& getShadowTranslation(Camera *cam) override;
	private:
		float half_shadow_area;
		// Store shadow translation calculation results
		glm::vec3 shadow_translation;
};

