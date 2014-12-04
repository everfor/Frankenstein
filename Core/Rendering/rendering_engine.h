#pragma once

#include "camera.h"
#include "base_light.h"

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <map>

// Keys for vectors/textures
#define RENDERING_ENGINE_AMBIENT_LIGHT			"ambient"
#define RENDERING_ENGINE_SHADOW_MAP				"shadow_map"
#define RENDERING_ENGINE_TEMP_TARGET			"temp_target"
#define RENDERING_ENGINE_FILTER_TARGET			"filter_target"

// Forward Declaraion
class Object;
class Texture;
class Material;
class Mesh;

class RenderingEngine
{
	public:
		RenderingEngine();
		virtual ~RenderingEngine();
		void clearScreen();
		void render(Object& object);
		Camera* getMainCamera() { return mainCamera; };
		void addLight(BaseLight *light);
		void addCamera(Camera *camera);
		void clearLight();
		void applyFilter(Shader *shader, Texture *src, Texture *dest);
		// map operations
		void setTexture(const std::string& key, Texture *value);
		void setFloat(const std::string& key, float value) { floats[key] = value; };
		void setVector(const std::string& key, const glm::vec3& value) { vectors[key] = value; };
		Texture* getTexture(const std::string& key) { return textures.at(key); };
		float getFloat(const std::string& key) { return floats.at(key); };
		glm::vec3& getVector(const std::string& key) { return vectors.at(key); };
		glm::mat4& getLightMatrix() { return lightMatrix; };
	private:
		Camera *mainCamera;
		std::vector<BaseLight*> lights;
		std::unique_ptr<Camera> altCamera;
		std::unique_ptr<Object> altCameraObject;
		std::unique_ptr<Material> planeMaterial;
		std::unique_ptr<Mesh> plane;
		std::unique_ptr<Texture> planeTexture;
		std::unique_ptr<Transform> planeTransform;
		// maps
		std::map<std::string, Texture*> textures;
		std::map<std::string, float> floats;
		std::map<std::string, glm::vec3> vectors;
		glm::mat4 lightMatrix;
};

