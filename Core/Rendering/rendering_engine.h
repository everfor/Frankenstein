#pragma once

#include "camera.h"
#include "base_light.h"

#include <glm/glm.hpp>
#include <vector>
#include <memory>

// Forward Declaraion
class Object;

class RenderingEngine
{
	public:
		RenderingEngine(Camera& init_camera = Camera(80.0f, 800.0f / 600.0f, 0.1f, 1000));
		virtual ~RenderingEngine();
		void clearScreen();
		void render(Object& object);
		Camera& getMainCamera() { return mainCamera; };
		void setMainCamera(Camera& new_camera) { mainCamera = new_camera; };
		void addLight(BaseLight *light);
		void clearLight();
	private:
		Camera mainCamera;
		std::vector<BaseLight*> lights;
};

