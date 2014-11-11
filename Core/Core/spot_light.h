#pragma once

#include "point_light.h"

class SpotLight : public PointLight
{
	public:
		SpotLight(PointLight& init_point, glm::vec3& init_dir, float init_cutoff = 0.5)
			: PointLight(init_point), direction(glm::normalize(init_dir)), cutoff(init_cutoff) {};
		virtual ~SpotLight() {};
		glm::vec3& getDirection() { return direction; };
		void setDirection(glm::vec3& new_dir) { direction =glm::normalize(new_dir); };
		float getCutOff() { return cutoff; };
		void setCutOff(float new_cut) { cutoff = new_cut; };
	private:
		glm::vec3 direction;
		float cutoff;
};

