#pragma once

#include "component.h"

// Max mouse cursor shoot between frames
#define MAX_MOUSE_SHOOT			200

class Transform;
class Rotation : public Component
{
	public:
		Rotation(float init_sensitivity = 7.0f) : sensitivity(init_sensitivity) {};
		virtual ~Rotation() {};
		void input(Transform *transform, float delta);
	private:
		float sensitivity;
};

