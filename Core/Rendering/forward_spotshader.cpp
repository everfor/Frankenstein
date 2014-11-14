#include "forward_spotshader.h"
#include "resource_manager.h"

bool ForwardSpotShader::_is_initialized = false;
std::unique_ptr<ForwardSpotShader> ForwardSpotShader::_shader;

ForwardSpotShader::ForwardSpotShader() : Shader()
{
	std::string vertex_shader, fragment_shader;
	ResourceManager::LoadShader("./res/shaders/forward-spot.vs", vertex_shader);
	ResourceManager::LoadShader("./res/shaders/forward-spot.fs", fragment_shader);
	addVertexShader(vertex_shader);
	addFragmentShader(fragment_shader);

	compileAllShaders();

	addUniform("model");
	addUniform("MVP");
	addUniform("eyePos");
	addUniform("specularIntensity");
	addUniform("specularExponent");
	addUniform("spotLight.pointLight.base.color");
	addUniform("spotLight.pointLight.base.intensity");
	addUniform("spotLight.pointLight.atten.constant");
	addUniform("spotLight.pointLight.atten.linear");
	addUniform("spotLight.pointLight.atten.exponent");
	addUniform("spotLight.pointLight.position");
	addUniform("spotLight.pointLight.range");
	addUniform("spotLight.direction");
	addUniform("spotLight.cutoff");
}

ForwardSpotShader::~ForwardSpotShader()
{
}

void ForwardSpotShader::updateUniforms(Transform& transform, Camera& camera, Material& material)
{
	setUniform("model", transform.getTransformation());
	setUniform("MVP", camera.getCameraProjection() * transform.getTransformation());
	setUniform("eyePos", camera.getPos());

	setUniformf("specularIntensity", material.getSpecularIntensity());
	setUniformf("specularExponent", material.getSpecularExponent());

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
	setUniform(uniform + ".position", pointLight.getTransform()->getTranslation());
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