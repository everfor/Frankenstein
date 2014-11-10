#pragma once

#include "shader.h"

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
		void updateUniforms(const glm::mat4& world, const glm::mat4& projection, Material& material) override;
	private:
		PhongShader();
		static std::unique_ptr<PhongShader> _basic_shader;
		static bool _is_initialized;
		static glm::vec3 _ambient_light;
};

