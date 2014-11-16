#include "forward_pointshader.h"
#include "resource_manager.h"
#include "camera.h"

bool ForwardPointShader::_is_initialized = false;
std::unique_ptr<ForwardPointShader> ForwardPointShader::_shader;

ForwardPointShader::ForwardPointShader() : Shader()
{
	std::string vertex_shader, fragment_shader;
	ResourceManager::LoadShader("./res/shaders/forward-point.vs", vertex_shader);
	ResourceManager::LoadShader("./res/shaders/forward-point.fs", fragment_shader);
	addVertexShader(vertex_shader);
	addFragmentShader(fragment_shader);

	compileAllShaders();

	addUniform("model");
	addUniform("MVP");
	addUniform("eyePos");
	addUniform("specularIntensity");
	addUniform("specularExponent");
	addUniform("pointLight.base.color");
	addUniform("pointLight.base.intensity");
	addUniform("pointLight.atten.constant");
	addUniform("pointLight.atten.linear");
	addUniform("pointLight.atten.exponent");
	addUniform("pointLight.position");
	addUniform("pointLight.range");
}

ForwardPointShader::~ForwardPointShader()
{
}

void ForwardPointShader::updateUniforms(Transform *transform, Camera *camera, Material *material)
{
	setUniform("model", transform->getTransformation());
	setUniform("MVP", camera->getCameraProjection() * transform->getTransformation());
	setUniform("eyePos", camera->getTransform()->getTransformedTranslation());

	setUniformf("specularIntensity", material->getFloat(MATERIAL_SPECULAR_INTENSITY));
	setUniformf("specularExponent", material->getFloat(MATERIAL_SPECULAR_EXPONENT));

	setLightUniform("pointLight", pointLight);
}

void ForwardPointShader::setLightUniform(const std::string& uniform, PointLight& pointLight)
{
	setLightUniform(uniform + ".base", (BaseLight)pointLight);
	setUniform(uniform + ".position", pointLight.getTransform()->getTransformedTranslation());
	setUniformf(uniform + ".atten.constant", pointLight.getConstant());
	setUniformf(uniform + ".atten.linear", pointLight.getLinear());
	setUniformf(uniform + ".atten.exponent", pointLight.getExponent());
	setUniformf(uniform + ".range", pointLight.getRange());
}

void ForwardPointShader::setLightUniform(const std::string& uniform, BaseLight& base)
{
	setUniform(uniform + ".color", base.getColor());
	setUniformf(uniform + ".intensity", base.getIntensity());
}

ForwardPointShader* ForwardPointShader::GetShader(PointLight& light)
{
	if (!_is_initialized)
	{
		_shader.reset(new ForwardPointShader());
		_is_initialized = true;
	}

	_shader.get()->setLight(light);
	return _shader.get();
}
