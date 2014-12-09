#include "base_light.h"
#include "directional_light.h"
#include "point_light.h"
#include "spot_light.h"

#include "rendering_engine.h"
#include "core_engine.h"
#include "shader.h"
#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

#define PI 3.1415926

void BaseLight::addToEngine(CoreEngine *engine)
{
	engine->getRenderingEngine()->addLight(this);
}

glm::vec3& BaseLight::getShadowTranslation(Camera *cam)
{
	return getTransform()->getTransformedTranslation();
}

glm::quat& BaseLight::getShadowRotation(Camera *cam)
{
	return getTransform()->getTransformedRotation();
}

DirectionalLight::DirectionalLight(BaseLight& init_base, float init_shadow_area) : BaseLight(init_base), half_shadow_area(init_shadow_area / 2.0f)
{
	setShadow(new Shadow(glm::ortho<float>(-half_shadow_area, half_shadow_area, -half_shadow_area, half_shadow_area, -half_shadow_area, half_shadow_area), 0.0002, 0.1, true));
}

glm::vec3& DirectionalLight::getShadowTranslation(Camera* cam)
{
	shadow_translation = cam->getTransform()->getTransformedTranslation() + cam->getTransform()->getTransformedForward() * half_shadow_area;

	// Rotate shadow translation in light space
	shadow_translation = glm::mat3_cast(glm::conjugate(cam->getTransform()->getTransformedRotation())) * shadow_translation;

	float texelSize = (2.0f * half_shadow_area) / 1024.0f;
	shadow_translation.x = texelSize * floor(shadow_translation.x / texelSize);
	shadow_translation.y = texelSize * floor(shadow_translation.y / texelSize);

	// Restore rotation
	shadow_translation = glm::mat3_cast(cam->getTransform()->getTransformedRotation()) * shadow_translation;

	return shadow_translation;
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