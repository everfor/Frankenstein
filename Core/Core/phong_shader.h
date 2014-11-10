#pragma once

#include "shader.h"
#include "base_light.h"
#include "directional_light.h"

#include <memory>
#include <glm/glm.hpp>

class PhongShader : public Shader
{
	public:
		virtual ~PhongShader();
		static PhongShader* GetShader();
		static void DestroyShader();
		static glm::vec3& getAmbientLight() { return _ambient_light; };
		static void setAmbientLight(const glm::vec3& new_light) { _ambient_light = new_light; };
		static DirectionalLight& getDirectionalLight() { return _directional_light; };
		static void setDirectionalLight(const DirectionalLight& new_dir_light) { _directional_light = new_dir_light; };
		void setLightUniform(const std::string& uniform, BaseLight& baseLight);
		void setLightUniform(const std::string& uniform, DirectionalLight& directionalLight);
		void updateUniforms(const glm::mat4& world, const glm::mat4& projection, Material& material) override;
	private:
		PhongShader();
		static std::unique_ptr<PhongShader> _basic_shader;
		static bool _is_initialized;
		static glm::vec3 _ambient_light;
		static DirectionalLight _directional_light;
};

