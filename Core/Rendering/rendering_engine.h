#pragma once

#include "object.h"
#include "camera.h"

#include <glm/glm.hpp>

class RenderingEngine
{
	public:
		RenderingEngine(Camera& init_camera = Camera(80.0f, 800.0f / 600.0f, 0.1f, 1000), glm::vec3& init_ambient = glm::vec3(0.2, 0.2, 0.2));
		virtual ~RenderingEngine();
		void clearScreen();
		void render(Object& object);
		Camera& getMainCamera() { return mainCamera; };
		void setMainCamera(Camera& new_camera) { mainCamera = new_camera; };
	private:
		Camera mainCamera;
		glm::vec3 ambientLight;
};

