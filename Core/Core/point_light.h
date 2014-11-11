#pragma once

#include "base_light.h"

#include <glm/glm.hpp>

class PointLight : public BaseLight
{
	public:
		PointLight(BaseLight& init_base, glm::vec3& init_pos, float init_constant = 0.0f, float init_linear = 0.0f, float init_exp = 0.0f, float init_range = 10.0f) :
			BaseLight(init_base), position(init_pos), constant(init_constant), linear(init_linear), exponent(init_exp), range(init_range) {};
		virtual ~PointLight() {};
		glm::vec3& getPos() { return position; };
		void setPos(glm::vec3& new_pos) { position = new_pos; };
		float getConstant() { return constant; };
		void setConstant(float new_const) { constant = new_const; };
		float getLinear() { return linear; };
		void setLinear(float new_linear) { linear = new_linear; };
		float getExponent() { return exponent; };
		void setExponent(float new_exp) { exponent = new_exp; };
		float getRange() { return range; };
		void setRange(float new_range) { range = new_range; };
	private:
		glm::vec3 position;
		// Attenuation
		float constant;
		float linear;
		float exponent;
		float range;
};

