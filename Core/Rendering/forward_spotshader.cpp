#include "forward_spotshader.h"
#include "resource_manager.h"
#include "camera.h"

bool ForwardSpotShader::_is_initialized = false;
std::unique_ptr<ForwardSpotShader> ForwardSpotShader::_shader;

ForwardSpotShader::ForwardSpotShader() : Shader("./res/shaders/forward-spot.vs", "./res/shaders/forward-spot.fs")
{
}

ForwardSpotShader::~ForwardSpotShader()
{
}

void ForwardSpotShader::updateUniforms(Transform *transform, Camera *camera, Material *material)
{
	setUniform("model", transform->getTransformation());
	setUniform("MVP", camera->getCameraProjection() * transform->getTransformation());
	setUniform("eyePos", camera->getTransform()->getTransformedTranslation());

	setUniformf("specularIntensity", material->getFloat(MATERIAL_SPECULAR_INTENSITY));
	setUniformf("specularExponent", material->getFloat(MATERIAL_SPECULAR_EXPONENT));

	setLightUniform("spotLight", spotLight);
}

void ForwardSpotShader::setLightUniform(const std::string& uniform, SpotLight& spotLight)
{
	setLightUniform(uniform + ".pointLight", (PointLight)spotLight);
	setUniform(uniform + ".direction", spotLight.getDirection());
	setUniformf(uniform + ".cutoff", spotLight.getCutOff());
}

void ForwardSpotShader::setLightUniform(const std::string& uniform, PointLight& pointLight)
{
	setLightUniform(uniform + ".base", (BaseLight)pointLight);
	setUniform(uniform + ".position", pointLight.getTransform()->getTransformedTranslation());
	setUniformf(uniform + ".atten.constant", pointLight.getConstant());
	setUniformf(uniform + ".atten.linear", pointLight.getLinear());
	setUniformf(uniform + ".atten.exponent", pointLight.getExponent());
	setUniformf(uniform + ".range", pointLight.getRange());
}

void ForwardSpotShader::setLightUniform(const std::string& uniform, BaseLight& base)
{
	setUniform(uniform + ".color", base.getColor());
	setUniformf(uniform + ".intensity", base.getIntensity());
}

ForwardSpotShader* ForwardSpotShader::GetShader(SpotLight& light)
{
	if (!_is_initialized)
	{
		_shader.reset(new ForwardSpotShader());
		_is_initialized = true;
	}

	_shader.get()->setLight(light);
	return _shader.get();
}