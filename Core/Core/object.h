#pragma once

#include "component.h"
#include "transform.h"
#include "camera.h"
#include "shader.h"

#include <memory>
#include <vector>
#include <cstdarg>

// Forward Declaration
class RenderingEngine;

class Object
{
	public:
		Object();
		virtual ~Object();
		void addChild(Object *child);
		void addComponent(Component *component);
		void input(float delta);
		void update(float delta);
		void render(Shader *shader, Camera *camera);
		Transform& getTransform() { return transform; };
		// Add necessary components to rendering engine
		void addToRenderingEngine(RenderingEngine *engine);
	private:
		Transform transform;
		std::vector<std::unique_ptr<Object>> children;
		std::vector<std::unique_ptr<Component>> components;
};

