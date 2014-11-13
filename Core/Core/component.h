#pragma once

#include "transform.h"
#include "shader.h"

class Component
{
	public:
		Component() {};
		virtual ~Component() {};
		virtual void input(Transform& transform) {};
		virtual void update(Transform& transform) {};
		virtual void render(Shader *shader, Transform *transform, Camera *camera) {};
};

