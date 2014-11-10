#include "phong_shader.h"
#include "resource_manager.h"

std::unique_ptr<PhongShader> PhongShader::_basic_shader;
bool PhongShader::_is_initialized = false;

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
	addUniform("color");
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

	setUniform("transform", projection);
	setUniform("color", material.getColor());
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
