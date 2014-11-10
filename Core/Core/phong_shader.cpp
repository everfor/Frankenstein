#include "phong_shader.h"
#include "resource_manager.h"

std::unique_ptr<PhongShader> PhongShader::_basic_shader;
bool PhongShader::_is_initialized = false;
glm::vec3 PhongShader::_ambient_light = glm::vec3(0.2, 0.2, 0.2);
DirectionalLight PhongShader::_directional_light(BaseLight(glm::vec3(1, 1, 1), 0), glm::vec3(0, 0, 0));

PhongShader::PhongShader() : Shader()
{
	// Initialize shaders
	std::string vertex_shader_str, fragment_shader_str;
	ResourceManager::LoadShader("./res/shaders/phongShader.vs", vertex_shader_str);
	ResourceManager::LoadShader("./res/shaders/phongShader.fs", fragment_shader_str);
	addVertexShader(vertex_shader_str);
	addFragmentShader(fragment_shader_str);
	compileAllShaders();

	addUniform("transform");
	addUniform("projection");
	addUniform("baseColor");
	addUniform("ambientLight");
	addUniform("directionalLight.base.color");
	addUniform("directionalLight.base.intensity");
	addUniform("directionalLight.direction");
}

PhongShader::~PhongShader()
{
}

void PhongShader::updateUniforms(const glm::mat4& world, const glm::mat4& projection, Material& material)
{
	if (material.haveTexture())
	{
		material.getTexture().bind();
	}

	setUniform("transform", world);
	setUniform("projection", projection);
	setUniform("baseColor", material.getColor());
	setUniform("ambientLight", _ambient_light);
	setLightUniform("directionalLight", _directional_light);
}

PhongShader* PhongShader::GetShader()
{
	if (!_is_initialized)
	{
		_basic_shader.reset(new PhongShader());
		_is_initialized = true;
	}

	return _basic_shader.get();
}

void PhongShader::DestroyShader()
{
	_basic_shader.reset();
	_is_initialized = false;
}

void PhongShader::setLightUniform(const std::string& uniform, BaseLight& baseLight)
{
	setUniform(uniform + ".color", baseLight.getColor());
	setUniformf(uniform + ".intensity", baseLight.getIntensity());
}

void PhongShader::setLightUniform(const std::string& uniform, DirectionalLight& directionalLight)
{
	setLightUniform(uniform + ".base", directionalLight.getBaseLight());
	setUniform(uniform + ".direction", directionalLight.getDirection());
}