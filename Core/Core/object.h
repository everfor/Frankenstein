#pragma once

#include "component.h"
#include "transform.h"
#include "shader.h"

#include <memory>
#include <vector>
#include <cstdarg>

// Forward Declaration
class CoreEngine;
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
		void render(Shader *shader, RenderingEngine *rendering_engine);
		Transform& getTransform() { return transform; };
		// Add necessary components to rendering engine
		void setEngine(CoreEngine *engine);
	protected:
		CoreEngine *engine;
	private:
		Transform transform;
		std::vector<std::unique_ptr<Object>> children;
		std::vector<std::unique_ptr<Component>> components;
};

