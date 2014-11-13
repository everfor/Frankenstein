#include "forward_ambientshader.h"
#include "resource_manager.h"

bool ForwardAmbientShader::_is_initialized = false;
std::unique_ptr<ForwardAmbientShader> ForwardAmbientShader::_shader;

ForwardAmbientShader::ForwardAmbientShader() : Shader()
{
	std::string vertex_shader, fragment_shader;
	ResourceManager::LoadShader("./res/shaders/forward-ambient.vs", vertex_shader);
	ResourceManager::LoadShader("./res/shaders/forward-ambient.fs", fragment_shader);
	addVertexShader(vertex_shader);
	addFragmentShader(fragment_shader);

	compileAllShaders();

	addUniform("MVP");
	addUniform("ambientIntensity");
}

ForwardAmbientShader::~ForwardAmbientShader()
{
}

void ForwardAmbientShader::updateUniforms(Transform& transform, Camera& camera, Material& material)
{
	if (material.haveTexture())
	{
		material.getTexture().bind();
	}

	setUniform("MVP", camera.getCameraProjection() * transform.getTransformation());
	setUniform("ambientIntensity", color);
}

ForwardAmbientShader* ForwardAmbientShader::GetShader(glm::vec3& color)
{
	if (!_is_initialized)
	{
		_shader = std::unique_ptr<ForwardAmbientShader>(new ForwardAmbientShader());
		_is_initialized = true;
	}

	_shader.get()->setColor(color);
	return _shader.get();
}
