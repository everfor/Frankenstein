#pragma once

#include "component.h"
#include "transform.h"
#include "camera.h"
#include "shader.h"

#include <memory>
#include <vector>

class Object
{
	public:
		Object();
		virtual ~Object();
		void addChild(Object *child);
		void addComponent(Component *component);
		void input();
		void update();
		void render(Shader *shader, Camera *camera);
		Transform& getTransform() { return transform; };
	private:
		Transform transform;
		std::vector<std::unique_ptr<Object>> children;
		std::vector<std::unique_ptr<Component>> components;
};

