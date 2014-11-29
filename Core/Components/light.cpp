#include "base_light.h"
#include "directional_light.h"
#include "point_light.h"
#include "spot_light.h"

#include "rendering_engine.h"
#include "core_engine.h"
#include "shader.h"

#include <glm/gtc/matrix_transform.hpp>

void BaseLight::addToEngine(CoreEngine *engine)
{
	engine->getRenderingEngine()->addLight(this);
}

DirectionalLight::DirectionalLight(BaseLight& init_base) : BaseLight(init_base)
{
	setShadow(new Shadow(glm::ortho<float>(-40.0f, 40.0f, -40.0f, 40.0f, -40.0f, 40.0f)));
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