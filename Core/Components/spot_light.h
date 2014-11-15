#pragma once

#include "point_light.h"

class SpotLight : public PointLight
{
	public:
		SpotLight(PointLight& init_point = PointLight(), float init_cutoff = 0.5)
			: PointLight(init_point), cutoff(init_cutoff) {};
		virtual ~SpotLight() {};
		glm::vec3& getDirection() { return getTransform()->getForward(); };
		float getCutOff() { return cutoff; };
		void setCutOff(float new_cut) { cutoff = new_cut; };
		Shader* getShader() override;
	private:
		float cutoff;
		glm::vec3 direction;
};

