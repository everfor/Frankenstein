#include "phong_shader.h"
#include "resource_manager.h"

std::unique_ptr<PhongShader> PhongShader::_basic_shader;
bool PhongShader::_is_initialized = false;
glm::vec3 PhongShader::_ambient_light = glm::vec3(0.2, 0.2, 0.2);
DirectionalLight PhongShader::_directional_light(BaseLight(glm::vec3(1, 1, 1), 0), glm::vec3(0, 0, 0));
std::vector<PointLight> PhongShader::_point_lights;
std::vector<SpotLight> PhongShader::_spot_lights;

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
	addUniform("eyePos");

	addUniform("ambientLight");
	addUniform("specularIntensity");
	addUniform("specularExponent");
	addUniform("directionalLight.base.color");
	addUniform("directionalLight.base.intensity");
	addUniform("directionalLight.direction");

	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		addUniform("pointLights[" + std::to_string(i) + "].base.color");
		addUniform("pointLights[" + std::to_string(i) + "].base.intensity");
		addUniform("pointLights[" + std::to_string(i) + "].atten.constant");
		addUniform("pointLights[" + std::to_string(i) + "].atten.linear");
		addUniform("pointLights[" + std::to_string(i) + "].atten.exponent");
		addUniform("pointLights[" + std::to_string(i) + "].position");
		addUniform("pointLights[" + std::to_string(i) + "].range");
	}

	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		addUniform("spotLights[" + std::to_string(i) + "].pointLight.base.color");
		addUniform("spotLights[" + std::to_string(i) + "].pointLight.base.intensity");
		addUniform("spotLights[" + std::to_string(i) + "].pointLight.atten.constant");
		addUniform("spotLights[" + std::to_string(i) + "].pointLight.atten.linear");
		addUniform("spotLights[" + std::to_string(i) + "].pointLight.atten.exponent");
		addUniform("spotLights[" + std::to_string(i) + "].pointLight.position");
		addUniform("spotLights[" + std::to_string(i) + "].pointLight.range");
		addUniform("spotLights[" + std::to_string(i) + "].direction");
		addUniform("spotLights[" + std::to_string(i) + "].cutoff");
	}
}

PhongShader::~PhongShader()
{
}

void PhongShader::updateUniforms(Transform& transform, Camera& camera, Material& material)
{
	if (material.haveTexture())
	{
		material.getTexture().bind();
	}

	setUniform("transform", transform.getTransformation());
	setUniform("projection", camera.getCameraProjection() * transform.getTransformation());
	setUniform("baseColor", material.getColor());

	// Lighting
	setUniform("ambientLight", _ambient_light);
	setLightUniform("directionalLight", _directional_light);

	// Specular Reflection
	setUniform("eyePos", camera.getPos());
	setUniformf("specularIntensity", material.getSpecularIntensity());
	setUniformf("specularExponent", material.getSpecularExponent());

	// Point Light
	int num_point_lights = _point_lights.size() < MAX_POINT_LIGHTS ? _point_lights.size() : MAX_POINT_LIGHTS;
	for (int i = 0; i < num_point_lights; i++)
	{
		setLightUniform("pointLights[" + std::to_string(i) + "]", _point_lights[i]);
	}

	int num_spot_lights = _spot_lights.size() < MAX_SPOT_LIGHTS ? _spot_lights.size() : MAX_SPOT_LIGHTS;
	for (int i = 0; i < num_spot_lights; i++)
	{
		setLightUniform("spotLights[" + std::to_string(i) + "]", _spot_lights[i]);
	}
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
	setLightUniform(uniform + ".base", (BaseLight)directionalLight);
	setUniform(uniform + ".direction", directionalLight.getDirection());
}

void PhongShader::setLightUniform(const std::string& uniform, PointLight& pointLight)
{
	setLightUniform(uniform + ".base", (BaseLight)pointLight);
	setUniform(uniform + ".position", pointLight.getPos());
	setUniformf(uniform + ".atten.constant", pointLight.getConstant());
	setUniformf(uniform + ".atten.linear", pointLight.getLinear());
	setUniformf(uniform + ".atten.exponent", pointLight.getExponent());
	setUniformf(uniform + ".range", pointLight.getRange());
}

void PhongShader::setLightUniform(const std::string& uniform, SpotLight& spotLight)
{
	setLightUniform(uniform + ".pointLight", (PointLight)spotLight);
	setUniform(uniform + ".direction", spotLight.getDirection());
	setUniformf(uniform + ".cutoff", spotLight.getCutOff());
}