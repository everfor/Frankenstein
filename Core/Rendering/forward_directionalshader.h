#pragma once

#include "shader.h"
#include "base_light.h"
#include "directional_light.h"

#include <memory>

class ForwardDirectionalShader : public Shader
{
	public:
		virtual ~ForwardDirectionalShader();
		void updateUniforms(Transform& transform, Camera& camera, Material& material) override;
		DirectionalLight& getLight() { return directionalLight; };
		void setLight(DirectionalLight& new_light) { directionalLight = new_light; };
		// Singleton
		static ForwardDirectionalShader* GetShader(DirectionalLight& light = DirectionalLight());
	private:
		ForwardDirectionalShader();
		void setLightUniform(const std::string& uniform, BaseLight& base);
		void setLightUniform(const std::string& uniform, DirectionalLight& directionalLight);
		DirectionalLight directionalLight;
		// Singleton
		static std::unique_ptr<ForwardDirectionalShader> _shader;
		static bool _is_initialized;
};

