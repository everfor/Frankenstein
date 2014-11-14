#include "base_light.h"
#include "directional_light.h"
#include "point_light.h"
#include "spot_light.h"

#include "rendering_engine.h"
#include "forward_directionalshader.h"
#include "forward_pointshader.h"
#include "forward_spotshader.h"

void BaseLight::addToRenderingEngine(RenderingEngine *engine)
{
	engine->addLight(this);
}

Shader* DirectionalLight::getShader()
{
	return ForwardDirectionalShader::GetShader(*this);
}

Shader* PointLight::getShader()
{
	return ForwardPointShader::GetShader(*this);
}

Shader* SpotLight::getShader()
{
	return ForwardSpotShader::GetShader(*this);
}