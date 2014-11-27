#pragma once

#include "camera.h"
#include "base_light.h"

#include <glm/glm.hpp>
#include <vector>
#include <memory>

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
	private:
		Camera *mainCamera;
		std::vector<BaseLight*> lights;
		std::unique_ptr<Camera> altCamera;
		std::unique_ptr<Object> altCameraObject;
		std::unique_ptr<Material> planeMaterial;
		std::unique_ptr<Mesh> plane;
		std::unique_ptr<Texture> planeTexture;
};

