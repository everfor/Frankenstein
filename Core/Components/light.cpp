#include "base_light.h"
#include "directional_light.h"
#include "point_light.h"
#include "spot_light.h"

#include "rendering_engine.h"
#include "shader.h"

void BaseLight::addToRenderingEngine(RenderingEngine *engine)
{
	engine->addLight(this);
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