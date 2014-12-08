#pragma once

#include "point_light.h"

class SpotLight : public PointLight
{
	public:
		SpotLight(PointLight& init_point = PointLight(), float init_view_angle = 170.0f);
		virtual ~SpotLight() {};
		glm::vec3& getDirection() { return getTransform()->getTransformedForward(); };
		float getCutOff() { return cutoff; };
		void setCutOff(float new_cut) { cutoff = new_cut; };
		Shader* getShader() override;
	private:
		float cutoff;
		glm::vec3 direction;
};

