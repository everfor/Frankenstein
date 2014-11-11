#include "basic_shader.h"
#include "resource_manager.h"

std::unique_ptr<BasicShader> BasicShader::_basic_shader;
bool BasicShader::_is_initialized = false;

BasicShader::BasicShader() : Shader()
{
	// Initialize shaders
	std::string vertex_shader_str, fragment_shader_str;
	ResourceManager::LoadShader("./res/shaders/basicShader.vs", vertex_shader_str);
	ResourceManager::LoadShader("./res/shaders/basicShader.fs", fragment_shader_str);
	addVertexShader(vertex_shader_str);
	addFragmentShader(fragment_shader_str);
	compileAllShaders();

	addUniform("transform");
}

BasicShader::~BasicShader()
{
}

void BasicShader::updateUniforms(Transform& transform, Camera& camera, Material& material)
{
	setUniform("transform", camera.getCameraProjection() * transform.getTransformation());
}

BasicShader* BasicShader::GetShader()
{
	if (!_is_initialized)
	{
		_basic_shader.reset(new BasicShader());
		_is_initialized = true;
	}

	return _basic_shader.get();
}

void BasicShader::DestroyShader()
{
	_basic_shader.reset();
	_is_initialized = false;
}
