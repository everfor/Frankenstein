#pragma once

#include "point_light.h"

class SpotLight : public PointLight
{
	public:
		SpotLight(PointLight& init_point = PointLight(), float init_cutoff = 0.5)
			: PointLight(init_point), cutoff(init_cutoff) {};
		virtual ~SpotLight() {};
		glm::vec3& getDirection() { direction = glm::normalize(glm::mat3_cast(getTransform()->getRotation()) * FORWARD_DIR); return direction; };
		float getCutOff() { return cutoff; };
		void setCutOff(float new_cut) { cutoff = new_cut; };
		Shader* getShader() override;
	private:
		float cutoff;
		glm::vec3 direction;
};

