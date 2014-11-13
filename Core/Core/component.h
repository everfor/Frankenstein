#pragma once

#include "transform.h"

class Component
{
	public:
		Component() {};
		virtual ~Component() {};
		virtual void input(Transform& transform) {};
		virtual void update(Transform& transform) {};
		virtual void render(Transform& transform, Camera& camera) {};
};

