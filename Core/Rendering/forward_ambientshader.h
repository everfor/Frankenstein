#pragma once

#include "shader.h"

#include <memory>

class ForwardAmbientShader : public Shader
{
	public:
		virtual ~ForwardAmbientShader();
		glm::vec3& getColor() { return color; };
		void setColor(glm::vec3& new_color) { color = new_color; };
		void updateUniforms(Transform& transform, Camera& camera, Material& material) override;
		// Singleton
		static ForwardAmbientShader* GetShader(glm::vec3& init_color = glm::vec3());
	private:
		ForwardAmbientShader(glm::vec3& init_color);
		glm::vec3 color;
		// Singleton
		static std::unique_ptr<ForwardAmbientShader> _shader;
		static bool _is_initialized;
};

