#pragma once

#include "spot_light.h"
#include "forward_pointshader.h"
#include "shader.h"
#include "base_light.h"
#include "spot_light.h"

#include <memory>

// Forward declaration
class Camera;

class ForwardSpotShader : public Shader
{
	public:
		virtual ~ForwardSpotShader();
		SpotLight& getLight() { return spotLight; };
		void updateUniforms(Transform *transform, Camera *camera, Material *material) override;
		// Singleton
		static ForwardSpotShader* GetShader(SpotLight& light = SpotLight());
	private:
		ForwardSpotShader();
		void setLightUniform(const std::string& uniform, BaseLight& base);
		void setLightUniform(const std::string& uniform, PointLight& point);
		void setLightUniform(const std::string& uniform, SpotLight& light);
		void setLight(SpotLight& new_light) { spotLight = new_light; };
		SpotLight spotLight;
		// Singleton
		static std::unique_ptr<ForwardSpotShader> _shader;
		static bool _is_initialized;
};

