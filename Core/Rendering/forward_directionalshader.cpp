#include "forward_directionalshader.h"
#include "resource_manager.h"
#include "camera.h"

bool ForwardDirectionalShader::_is_initialized = false;
std::unique_ptr<ForwardDirectionalShader> ForwardDirectionalShader::_shader;

ForwardDirectionalShader::ForwardDirectionalShader() : Shader()
{
	std::string vertex_shader, fragment_shader;
	ResourceManager::LoadShader("./res/shaders/forward-directional.vs", vertex_shader);
	ResourceManager::LoadShader("./res/shaders/forward-directional.fs", fragment_shader);
	addVertexShader(vertex_shader);
	addFragmentShader(fragment_shader);

	compileAllShaders();

	addUniform("model");
	addUniform("MVP");
	addUniform("eyePos");
	addUniform("specularIntensity");
	addUniform("specularExponent");
	addUniform("directionalLight.base.color");
	addUniform("directionalLight.base.intensity");
	addUniform("directionalLight.direction");
}

ForwardDirectionalShader::~ForwardDirectionalShader()
{
}

void ForwardDirectionalShader::updateUniforms(Transform *transform, Camera *camera, Material *material)
{
	setUniform("model", transform->getTransformation());
	setUniform("MVP", camera->getCameraProjection() * transform->getTransformation());
	setUniform("eyePos", camera->getPosition());

	setUniformf("specularIntensity", material->getSpecularIntensity());
	setUniformf("specularExponent", material->getSpecularExponent());

	setLightUniform("directionalLight", directionalLight);
}

void ForwardDirectionalShader::setLightUniform(const std::string& uniform, DirectionalLight& directionalLight)
{
	setLightUniform(uniform + ".base", (BaseLight)directionalLight);
	setUniform(uniform + ".direction", directionalLight.getDirection());
}

void ForwardDirectionalShader::setLightUniform(const std::string& uniform, BaseLight& base)
{
	setUniform(uniform + ".color", base.getColor());
	setUniformf(uniform + ".intensity", base.getIntensity());
}

ForwardDirectionalShader* ForwardDirectionalShader::GetShader(DirectionalLight& light)
{
	if (!_is_initialized)
	{
		_shader.reset(new ForwardDirectionalShader());
		_is_initialized = true;
	}

	_shader.get()->setLight(light);
	return _shader.get();
}
