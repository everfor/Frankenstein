#pragma once

#include "shader.h"

#include <memory>

/*
* Singleton Basic Shader
*/
class BasicShader : public Shader
{
	public:
		virtual ~BasicShader();
		static BasicShader* GetShader();
		static void DestroyShader();
		void updateUniforms(const glm::mat4& world, const glm::mat4& projection);
	private:
		BasicShader();
		static std::unique_ptr<BasicShader> _basic_shader;
		static bool _is_initialized;
};

