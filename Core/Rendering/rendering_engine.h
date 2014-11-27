#pragma once

#include "camera.h"
#include "base_light.h"

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <map>

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
		// map operations
		void setTexture(const std::string& key, Texture *value) { textures[key] = value; };
		void setFloat(const std::string& key, float value) { floats[key] = value; };
		void setVector(const std::string& key, const glm::vec3& value) { vectors[key] = value; };
		Texture* getTexture(const std::string& key) { return textures.at(key); };
		float getFloat(const std::string& key) { return floats.at(key); };
		glm::vec3& getVector(const std::string& key) { return vectors.at(key); };
	private:
		Camera *mainCamera;
		std::vector<BaseLight*> lights;
		std::unique_ptr<Camera> altCamera;
		std::unique_ptr<Object> altCameraObject;
		std::unique_ptr<Material> planeMaterial;
		std::unique_ptr<Mesh> plane;
		std::unique_ptr<Texture> planeTexture;
		// maps
		std::map<std::string, Texture*> textures;
		std::map<std::string, float> floats;
		std::map<std::string, glm::vec3> vectors;
};

