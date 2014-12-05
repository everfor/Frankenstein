#include "base_light.h"
#include "directional_light.h"
#include "point_light.h"
#include "spot_light.h"

#include "rendering_engine.h"
#include "core_engine.h"
#include "shader.h"

#include <glm/gtc/matrix_transform.hpp>

#define PI 3.1415926

void BaseLight::addToEngine(CoreEngine *engine)
{
	engine->getRenderingEngine()->addLight(this);
}

DirectionalLight::DirectionalLight(BaseLight& init_base) : BaseLight(init_base)
{
	setShadow(new Shadow(glm::ortho<float>(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f), 0.0002, 0.05, true));
}

SpotLight::SpotLight(PointLight& init_point, float init_view_angle)
	: PointLight(init_point), cutoff(cosf(init_view_angle * PI / 360.0f))
{
	setShadow(new Shadow(glm::perspective(init_view_angle, 1.0f, 0.01f, getRange()), 0.00001, 0.05, false));
}

Shader* DirectionalLight::getShader()
{
	return Shader::GetShader(Shader::_shader_type::DIRECTIONAL_LIGHT, this);
}

Shader* PointLight::getShader()
{
	return Shader::GetShader(Shader::_shader_type::POINT_LIGHT, this);
}

Shader* SpotLight::getShader()
{
	return Shader::GetShader(Shader::_shader_type::SPOT_LIGHT, this);
}