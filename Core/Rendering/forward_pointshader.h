#pragma once

#include "shader.h"
#include "base_light.h"
#include "point_light.h"

#include <memory>

// Forward declaration
class Camera;

class ForwardPointShader : public Shader
{
	public:
		virtual ~ForwardPointShader();
		void updateUniforms(Transform *transform, Camera *camera, Material *material) override;
		PointLight& getLight() { return pointLight; };
		// Singleton
		static ForwardPointShader* GetShader(PointLight& light = PointLight());
	private:
		ForwardPointShader();
		void setLight(PointLight& new_light) { pointLight = new_light; };
		void setLightUniform(const std::string& uniform, BaseLight& base);
		void setLightUniform(const std::string& uniform, PointLight& pointLight);
		PointLight pointLight;
		// Singleton
		static std::unique_ptr<ForwardPointShader> _shader;
		static bool _is_initialized;
};

