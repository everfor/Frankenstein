#pragma once

#include "base_light.h"
#include "utils.h"

#include <glm/glm.hpp>

#define COLOR_DEPTH			256

class PointLight : public BaseLight
{
	public:
		PointLight(BaseLight& init_base = BaseLight(), float init_constant = 0.0f, float init_linear = 0.0f, float init_exp = 1.0f) :
			BaseLight(init_base), constant(init_constant), linear(init_linear), exponent(init_exp)
		{
			range = (-linear + sqrtf(linear * linear - 4.0 * exponent * (constant - (float)COLOR_DEPTH * getIntensity() * _max_component(getColor())))) / (2.0 * exponent);
		};
		virtual ~PointLight() {};
		float getConstant() { return constant; };
		void setConstant(float new_const) { constant = new_const; };
		float getLinear() { return linear; };
		void setLinear(float new_linear) { linear = new_linear; };
		float getExponent() { return exponent; };
		void setExponent(float new_exp) { exponent = new_exp; };
		float getRange() { return range; };
		void setRange(float new_range) { range = new_range; };
		Shader* getShader() override;
	private:
		// Attenuation
		float constant;
		float linear;
		float exponent;
		float range;
};

