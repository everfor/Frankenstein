#pragma once

#include "transform.h"
#include "shader.h"

class Component
{
	public:
		Component() {};
		virtual ~Component() {};
		virtual void input(Transform& transform, float delta) {};
		virtual void update(Transform& transform, float delta) {};
		virtual void render(Shader *shader, Transform *transform, Camera *camera) {};
};

