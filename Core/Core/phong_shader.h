#pragma once

#include "shader.h"
#include "base_light.h"
#include "directional_light.h"
#include "point_light.h"
#include "spot_light.h"

#include <memory>
#include <vector>
#include <glm/glm.hpp>

#define MAX_POINT_LIGHTS		4
#define MAX_SPOT_LIGHTS			4

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
		static std::vector<PointLight>& getPointLights() { return _point_lights; };
		static void setPointLights(std::vector<PointLight> new_points) { _point_lights = new_points; };
		static void addPointLight(PointLight& new_point) { _point_lights.push_back(new_point); };
		static std::vector<SpotLight>& getSpotLights() { return _spot_lights; };
		static void setSpotLights(std::vector<SpotLight> new_spots) { _spot_lights = new_spots; };
		static void addSpotLight(SpotLight& new_spot) { _spot_lights.push_back(new_spot); };
		void setLightUniform(const std::string& uniform, BaseLight& baseLight);
		void setLightUniform(const std::string& uniform, DirectionalLight& directionalLight);
		void setLightUniform(const std::string& uniform, PointLight& pointLight);
		void setLightUniform(const std::string& uniform, SpotLight& spotLight);
		void updateUniforms(Transform& transform, Camera& camera, Material& material) override;
	private:
		PhongShader();
		static std::unique_ptr<PhongShader> _basic_shader;
		static bool _is_initialized;
		static glm::vec3 _ambient_light;
		static DirectionalLight _directional_light;
		static std::vector<PointLight> _point_lights;
		static std::vector<SpotLight> _spot_lights;
};

