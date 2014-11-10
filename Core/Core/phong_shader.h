#pragma once

#include "shader.h"

#include <memory>

class PhongShader : public Shader
{
	public:
		virtual ~PhongShader();
		static PhongShader* GetShader();
		static void DestroyShader();
		void updateUniforms(const glm::mat4& world, const glm::mat4& projection, Material& material) override;
	private:
		PhongShader();
		static std::unique_ptr<PhongShader> _basic_shader;
		static bool _is_initialized;
};

