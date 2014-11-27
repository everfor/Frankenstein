#pragma once

#include "component.h"

class Transform;
class Movement : public Component
{
	public:
		Movement(float init_sensitivity = 1.5f) : sensitivity(init_sensitivity) {};
		virtual ~Movement() {};
		void input(Transform* transform, float delta) override;
	private:
		float sensitivity;
};

