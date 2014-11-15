#pragma once

#include "transform.h"
#include <cstdarg>

// Forward Declaration
class RenderingEngine;
class Camera;
class Shader;
class Transform;

class Component
{
	public:
		Component() {};
		virtual ~Component() {};
		virtual void input(Transform& transform, float delta) {};
		virtual void update(Transform& transform, float delta) {};
		virtual void render(Shader *shader, Camera *camera) {};
		void setTransform(Transform* new_trans) { transform = new_trans; };
		Transform* getTransform() { return transform; };
		virtual void addToRenderingEngine(RenderingEngine *engine) {};
	private:
		Transform *transform;
};

