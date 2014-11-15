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
};

